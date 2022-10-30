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

#ifndef OUT
#define OUT stdout
#endif

#ifndef ERROUT
#define ERROUT stderr
#endif

#ifndef is
#define is ==
#endif

#define FEED_END 66 
#define TMP_FILENAME "_tmp.feedreader"

int feedreader_url ();
int feedreader_feedfile ();
int xml_process ();
int get_new_url(FILE *file, char *line, int buffer);
void check_args ();
void parse_args (int argc, char **argv);
int feedreader ();

#endif

// Konec souboru feedreader_logic.h