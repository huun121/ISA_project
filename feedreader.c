#include "feedreader.h"
#include "error_handling.h"

void url_split (const char *startString) {
	host_name = strtok(url + strlen(startString), "/");

	if(host_name != NULL)	{

		host_resource = strtok(NULL, "\0");
        if(host_name == NULL) 
            host_resource = "/";
	} else {
        fprintf(stderr, ERR_WRONG_URL);
        exit(ERROR);
    }
}

void parse_args (int argc, char **argv) {
    (void) argc;
    for (int i = 1; i < argc; i++) {

        char *argument = argv[i];

        if (!strcmp(argument, "-T")) {
            if (!write_time) write_time = 1;
            else ARG_TWO_TIMES;
        } else if (!strcmp(argument, "-a")) {
            if (!write_author) write_author = 1;
            else ARG_TWO_TIMES;
        } else if (!strcmp(argument, "-u")) {
            if (!write_url) write_url = 1;
            else ARG_TWO_TIMES;
        } else if (!strcmp(argument, "-c")) {
            i++;
            if (i >= argc) {
                ARG_NO_PARAM;
                exit(1);
            }
            if (!certfile) certfile = argv[i];
            else ARG_TWO_TIMES;
        } else if (!strcmp(argument, "-C")) {
            i++;
            if (i >= argc) {
                ARG_NO_PARAM;
                exit(1);
            }
            if (!certaddr) certaddr = argv[i];
            else ARG_TWO_TIMES;
        } else if (!strcmp(argument, "-f")) {
            i++;
            if (i >= argc) {
                ARG_NO_PARAM;
                exit(1);
            }
            if (!feedfile) feedfile = argv[i];
            else ARG_TWO_TIMES;
        } else {
            if (!url) url = argv[i];
            else {argument = "URL adresa"; ARG_TWO_TIMES;}
        }
    }   
}

void check_args () {
    if (!feedfile && !url){
        fprintf(stderr, ERR_M_NO_SOURCE);
        exit(1);
    }
    if (feedfile && url){
        fprintf(stderr, ERR_M_TWO_SOURCES);
        exit(1);
    }
    // TODO
    /*if (certfile && certaddr){
        fprintf(stderr, ERR_M_TWO_SSL);
        exit(1);
    }*/
}

void url_parse () {
    // https nebo http
    if (!strncmp(url, "https://", strlen("https://"))) {
        host_port = "443";
        url_split("https://");
    } else if (!strncmp(url, "http://", strlen("http://"))) {
        host_port = "80";
        url_split("http://");
    } else {
        ERROR_HANDLE(ERR_WRONG_URL, ERROR)
    }
}

// SSl start --------
void init_ssl () {
    SSL_library_init();
    SSL_load_error_strings();
    ERR_load_BIO_strings();
    OpenSSL_add_all_algorithms();
}

void free_ssl () {
    if(out != NULL) {
        BIO_free(out);
        out = NULL;
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

void ctx_ctor () {
    ctx = SSL_CTX_new(SSLv23_client_method());
    if (ctx is NULL) {
        ERROR_HANDLE(ERR_SSL_TLS, ERROR)
    }
}

void ctx_dtor () {
    if(ctx != NULL) {
        SSL_CTX_free(ctx); 
        ctx = NULL;
    }
}

// nastaví certifikáty, vrací 1 v případě chyby
int ctx_set_cert_location () {
    if (certaddr is NULL && certfile is NULL) {
        if (!SSL_CTX_set_default_verify_paths(ctx)) {
            fprintf(stderr, ERR_SSL_TLS);
            return ERROR;
        }
    } else {
        if (!SSL_CTX_load_verify_locations(ctx, certfile, certaddr)) {
            fprintf(stderr, ERR_SSL_TLS);
            return ERROR;
        }
    }
    return SUCCESS;
}

void make_conn_hostname (char *conn_hostname) {
    strcpy(conn_hostname, host_name);
    strcat(conn_hostname, ":");
    strcat(conn_hostname, host_port);
}


int main (int argc, char **argv) {

    parse_args (argc, argv);

    check_args ();

    init_ssl ();
    char conn_hostname[BUFFER] = {};
    char request[BUFFER] = {};

    if (feedfile is NULL) {
        url_parse();

        ctx_ctor();

        if (ctx_set_cert_location()) {
            exit(ERROR);
        }
        
        web = BIO_new_ssl_connect(ctx);
        if (web is NULL) {
            ERROR_HANDLE(ERR_SSL_TLS, ERROR);
        }

        make_conn_hostname(conn_hostname);
        
        if (!BIO_set_conn_hostname(web, conn_hostname)) ERROR_HANDLE(ERR_SSL_TLS, ERROR);
        
        BIO_get_ssl(web, &ssl);
        SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);

        if (ssl is NULL) ERROR_HANDLE(ERR_SSL_TLS, ERROR);

        out = BIO_new_file(TMP_FILE_NAME, "w");
        //out = BIO_new_fp(stdout, BIO_NOCLOSE);
        
        if (out is NULL) ERROR_HANDLE(ERR_SSL_TLS, ERROR);
        
        if (!BIO_do_connect(web)) ERROR_HANDLE(ERR_SSL_TLS, ERROR);

        if(SSL_get_verify_result(ssl) != X509_V_OK) ERROR_HANDLE(ERR_SSL_TLS, ERROR);

        sprintf(request, "GET %s HTTP/1.0\r\nHost:  %s \r\nConnection: close\r\n\r\n", host_resource, host_name);
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
                        BIO_printf(out, "%s", end_of_header + strlen("\r\n\r\n"));
                        header = 1;
                    } else {
                        continue;
                    }
                } else {
                    BIO_write(out, buff, len);
                }
                //BIO_write(out, buff, len);
            }
                
            
        } while (len > 0 || BIO_should_retry(web));
        BIO_reset(out);

    } else {
        // TODO
        printf("UNIMPLEMENTED\n");
    }
    
    free_ssl(); 
    return SUCCESS;
}