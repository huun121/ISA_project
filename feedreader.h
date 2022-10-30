// Čtečka novinek ve formátu Atom a RSS s podporou TLS
// Projekt ISA
// VUT FIT v Brno
//
// Autor: Pavel Hurdalek (xhurda01)
// Datum: 30.10.2022

#ifndef _FEEDREADER_H_
#define _FEEDREADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "error_handling.h"
#include "rss_parser.h"
#include "atom_parser.h"
#include "ssl.h"

#define is ==

#define FEED_END 66 
#define TMP_FILENAME "_tmp.feedreader"

int write_time;
int write_author;
int write_url;
char *certfile;
char *certaddr;
char *url;
char *feedfile;

#endif

// Konec souboru feedreader.h