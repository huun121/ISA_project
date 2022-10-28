#ifndef _SSH_H_
#define _SSH_H_

#include <stdio.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include "error_handling.h"

#define is ==
#define BUFFER 1024

SSL_CTX* ctx;
BIO *web, *out_file;
SSL *ssl;

char *host_domain;
char *host_port;
char *host_path;

void init_ssl ();
void free_ssl ();
int ctx_ctor ();
void ctx_dtor ();
int ctx_set_cert_location (char *certaddr, char *certfile);
void make_conn_hostname (char *conn_hostname, const char *host_domain, const char *host_port);
int ssl_url_process (char *tmp_filename, char *url_adress, char *certaddr, char *certfile);

int url_split (const char *prefix, char *url_address);
int url_parse (char *url_address);

int remove_tmp_file (char *tmp_filename);

#endif