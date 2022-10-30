// Čtečka novinek ve formátu Atom a RSS s podporou TLS
// Projekt ISA
// VUT FIT v Brno
//
// Autor: Pavel Hurdalek (xhurda01)
// Datum: 30.10.2022

#ifndef _SSH_H_
#define _SSH_H_

#include <stdio.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include "error_handling.h"

#define HTTPS 0
#define HTTP 1


#ifndef is
#define is ==
#endif

#ifndef BUFFER
#define BUFFER 1024
#endif

#ifndef BUFFER_SMALL
#define BUFFER_SMALL 256
#endif

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

int http_conection (const char *conn_hostname);
int https_conection (const char *conn_hostname, char *certaddr, char *certfile);

#endif

// Konec souboru ssl.h