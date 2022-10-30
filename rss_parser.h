// Čtečka novinek ve formátu Atom a RSS s podporou TLS
// Projekt ISA
// VUT FIT v Brno
//
// Autor: Pavel Hurdalek (xhurda01)
// Datum: 30.10.2022

#ifndef _RSS_PARSER_H_
#define _RSS_PARSER_H_

#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#ifndef OUT
#define OUT stdout
#endif

#ifndef ERROUT
#define ERROUT stderr
#endif

void rss_root_parse (xmlNode *root_node, int write_updated, int write_link, int write_autor);
void rss_channel_parse (xmlNode *channel_node, int write_pubDate, int write_link, int write_autor);
void rss_item_print (xmlNode *item_node, int write_pubDate, int write_link, int write_autor, int *write_new_line);

#endif

// Konec souboru rss_parser.h