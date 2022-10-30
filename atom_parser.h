// Čtečka novinek ve formátu Atom a RSS s podporou TLS
// Projekt ISA
// VUT FIT v Brno
//
// Autor: Pavel Hurdalek (xhurda01)
// Datum: 30.10.2022

#ifndef _ATOM_PARSER_H_
#define _ATOM_PARSER_H_

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

void atom_root_parse (xmlNode *root_node, int write_updated, int write_link, int write_autor);
void atom_entry_print (xmlNode *entry_node, int write_updated, int write_link, int write_autor, int *write_new_line);
void atom_author_print (xmlNode *author_node);
void atom_link_print (xmlNode *link_node);

#endif

// Konec souboru atom_parser.h