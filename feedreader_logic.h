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

/**
 * Zpracování zdroje ve tvaru url adresy
 * 
 * @returns 0 průběh bez chyby
*/
int feedreader_url ();

/**
 * Zpracování souboru feedfile
 * 
 * @returns 0 průběh bez chyby
*/
int feedreader_feedfile ();

/**
 * Zpracování a výpis xml z dočasného souboru.
 * 
 * @returns 0 průběh bez chyby
*/
int xml_process ();

/**
 * Načtení url adresy z feedfile souboru
 * 
 * @param file feedfile
 * @param line destinace pro url adresu
 * @param buffer velikost line
 * @returns 0 stále je co číst
 * @returns 66 konec souboru
*/
int get_new_url(FILE *file, char *line, int buffer);

/**
 * Kontrola sémantiky parametrů.
*/
void check_args ();

/**
 * Zpracování parametrů z příkazové řádky.
 * 
 * @param argc počet parametrů
 * @param argv parametry
*/
void parse_args (int argc, char **argv);

/**
 * Inicializace openssl a zpracování zdrojů.
 * 
 * @returns 0 průběh bez chyby
*/
int feedreader ();

#endif

// Konec souboru feedreader_logic.h