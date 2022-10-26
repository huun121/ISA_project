#ifndef FEEDREADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define is ==
#define BUFFER 1024

#define TMP_FILE_NAME "_tmp.feedreader"

int write_time = 0;
int write_author = 0;
int write_url = 0;
char *certfile = NULL;
char *certaddr = NULL;
char *url = NULL;
char *feedfile = NULL;

char *host_name = NULL;
char *host_port = NULL;
char *host_resource = NULL;

SSL_CTX* ctx = NULL;
BIO *web = NULL, *out = NULL;
SSL *ssl = NULL;

#endif