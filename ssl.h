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

#ifndef OUT
#define OUT stdout
#endif

#ifndef ERROUT
#define ERROUT stderr
#endif

#ifndef is
#define is ==
#endif

#ifndef BUFFER
#define BUFFER 1024
#endif

#ifndef BUFFER_SMALL
#define BUFFER_SMALL 256
#endif

/**
 * Inicializace knihovny openssl.
*/
void init_ssl ();

/**
 * Uvolnění zdrojů požívaných modulem.
*/
void free_ssl ();

/**
 * Vytvoření objektu SSL_CTX *
 * 
 * @returns 0 průběh bez chyby
*/
int ctx_ctor ();

/**
 * Dealokace objektu SSL_CTX *
*/
void ctx_dtor ();

/**
 * Nastaví umístění certifikátů.
 * 
 * @param certaddr adresář s certifikáty
 * @param certfile soubor s certifikáty
 * @returns 0 průběh bez chyby
*/
int ctx_set_cert_location (char *certaddr, char *certfile);

/**
 * Sestrojí hostname pro připojení (doména:port).
 * 
 * @param conn_hostname destinace
 * @param host_domain doména
 * @param host_port port
*/
void make_conn_hostname (char *conn_hostname, const char *host_domain, const char *host_port);

/**
 * Zpracování url adresy. Navázání spojení (ověření platnosti SSL/TLS) stžení dat do souboru.
 *
 * @param tmp_filename jmeno souboru
 * @param url_adress url adresa
 * @param certaddr adresář s certifikáty
 * @param certfile soubor s certifikáty
 * @returns 0 průběh bez chyby
*/
int ssl_url_process (char *tmp_filename, char *url_adress, char *certaddr, char *certfile);

/**
 * Odtrhnutí prefixu od url adresy (např. http://)
 * 
 * @param url_adress url adresa
 * @param prefix prefix k odstranění
 * @returns 0 průběh bez chyby
*/
int url_split (const char *prefix, char *url_address);

/**
 * Zjištění protokolu a odtrhnutí prefixu.
 * 
 * @param url_adress url adresa
 * @returns 0 průběh bez chyby
*/
int url_parse (char *url_address);

/**
 * Odstranění dočasného souboru
 * 
 * @returns 0 soubor odstraněn
*/
int remove_tmp_file (char *tmp_filename);

/**
 * Navázaní http spojení.
 * 
 * @param conn_hostname hostname pro připojení
 * @returns 0 průběh bez chyby
*/
int http_conection (const char *conn_hostname);

/**
 * Navázaní https spojení.
 * 
 * @param conn_hostname hostname pro připojení
 * @param certaddr adresář s certifikáty
 * @param certfile soubor s certifikáty
 * @returns 0 průběh bez chyby
*/
int https_conection (const char *conn_hostname, char *certaddr, char *certfile);

#endif

// Konec souboru ssl.h