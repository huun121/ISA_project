#include "ssl.h"

    SSL_CTX* ctx = NULL;
    BIO *web = NULL;
    BIO * out_file = NULL;
    SSL *ssl = NULL;

    char *host_domain = NULL;
    char *host_port = NULL;
    char *host_path = NULL;

int ssl_url_process (char *tmp_filename, char *url_address, char *certaddr, char *certfile) {
    char conn_hostname[BUFFER] = {};
    char request[BUFFER] = {};

    if (url_parse(url_address)) return ERROR_ARGUMENT_PARSE;

    ctx_ctor();

    if (ctx_set_cert_location(certaddr, certfile)) {
        return ERROR_SSL;
    }
    
    web = BIO_new_ssl_connect(ctx);
    if (web is NULL) {
        ERROR_MESSAGE(ERR_M_SSL_TLS);
        return ERROR_SSL;
    }

    make_conn_hostname(conn_hostname, host_domain, host_port);
    
    if (!BIO_set_conn_hostname(web, conn_hostname)) {
        ERROR_MESSAGE(ERR_M_SSL_TLS);
        return ERROR_SSL;
    }

    BIO_get_ssl(web, &ssl);
    SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);

    if (ssl is NULL) {
        ERROR_MESSAGE(ERR_M_SSL_TLS);
        return ERROR_SSL;
    }

    // vytvoření dočasného souboru
    out_file = BIO_new_file(tmp_filename, "w");
    if (out_file is NULL) {
        ERROR_MESSAGE(ERR_M_SSL_TLS);
        return ERROR_SSL;
    }
    
    if (!BIO_do_connect(web)) {
        ERROR_MESSAGE(ERR_M_SSL_TLS);
        return ERROR_SSL;
    }

    if(SSL_get_verify_result(ssl) != X509_V_OK) {
        ERROR_MESSAGE(ERR_M_SSL_TLS);
        return ERROR_SSL;
    }

    sprintf(request, "GET %s HTTP/1.0\r\nHost:  %s \r\nConnection: close\r\n\r\n", host_path, host_domain);
    BIO_puts(web, request);

    int len = 0;
    int header = 0;
    do {
        char buff[BUFFER] = {};

        len = BIO_read(web, buff, sizeof(buff));
        
        if(len > 0) {
            // odebrání http hlavičky
            if (!header){
                char *end_of_header = strstr(buff, "\r\n\r\n");
                if (end_of_header != NULL) {
                    BIO_printf(out_file, "%s", end_of_header + strlen("\r\n\r\n"));
                    header = 1;
                } else {
                    continue;
                }
            } else {
                BIO_write(out_file, buff, len);
            }
        }
    } while (len > 0 || BIO_should_retry(web));

    BIO_reset(out_file);
    BIO_reset(web);

    return SUCCESS;
}

void init_ssl () {
    SSL_library_init();
    SSL_load_error_strings();
    ERR_load_BIO_strings();
    OpenSSL_add_all_algorithms();
}

void free_ssl () {
    if(out_file != NULL) {
        BIO_free(out_file);
        out_file = NULL;
    }
    
    if(web != NULL) {
        BIO_free_all(web);
        web = NULL;
    }
    
    if(ctx != NULL) {
        SSL_CTX_free(ctx); 
        ctx = NULL;
    }
}

int ctx_ctor () {
    ctx = SSL_CTX_new(SSLv23_client_method());
    if (ctx is NULL) {
        ERROR_MESSAGE(ERR_M_SSL_TLS);
        return ERROR_INTERN;
    }
    return SUCCESS;
}

void ctx_dtor () {
    if(ctx != NULL) {
        SSL_CTX_free(ctx); 
        ctx = NULL;
    }
}

// nastaví certifikáty, vrací 1 v případě chyby
int ctx_set_cert_location (char *certaddr, char *certfile) {
    if (certaddr is NULL && certfile is NULL) {
        if (!SSL_CTX_set_default_verify_paths(ctx)) {
            ERROR_MESSAGE(ERR_M_SSL_TLS);
            return ERROR_INTERN;
        }
    } else {
        if (!SSL_CTX_load_verify_locations(ctx, certfile, certaddr)) {
            ERROR_MESSAGE(ERR_M_SSL_TLS);
            return ERROR_INTERN;
        }
    }
    return SUCCESS;
}

void make_conn_hostname (char *conn_hostname, const char *host_domain, const char *host_port) {
    strcpy(conn_hostname, host_domain);
    strcat(conn_hostname, ":");
    strcat(conn_hostname, host_port);
}

int url_parse (char *url_address) {
    // https nebo http
    if (!strncmp(url_address, "https://", strlen("https://"))) {
        host_port = "443";
        if (url_split("https://", url_address)) {
            ERROR_MESSAGE(ERR_WRONG_URL);
            return ERROR_INTERN;
        }
    } else if (!strncmp(url_address, "http://", strlen("http://"))) {
        host_port = "80";
        if (url_split("http://", url_address)) {
            ERROR_MESSAGE(ERR_WRONG_URL);
            return ERROR_INTERN;
        }
    } else {
        ERROR_MESSAGE(ERR_WRONG_URL);
        return ERROR_INTERN;
    }
    return SUCCESS;
}

int url_split (const char *prefix, char *url_address) {
    //začíná se po http prefixu
	host_domain = strtok(url_address + strlen(prefix), "/");

    // pokud není pouze prefix
	if(host_domain != NULL) {
		host_path = strtok(NULL, "\0");
        if(host_path == NULL)
            host_path = "/";
	} else {
        ERROR_MESSAGE(ERR_WRONG_URL);
        return ERROR_INTERN;
    }
    return SUCCESS;
}

int remove_tmp_file (char *tmp_filename) {
    if (!remove(tmp_filename)) {
        return ERROR_INTERN;
    }
    return SUCCESS;
}