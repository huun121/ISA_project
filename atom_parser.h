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

/**
 *  Zpracování kořenového uzlu ve formátu atom.
 * 
 * Výpis informací podle zadaných příznaků.
 * 
 * @param root_node kořenový uzel
 * @param write_updated příznak - výpis aktualizace
 * @param write_link příznak - výpis url
 * @param write_autor příznak - výpis autora
*/
void atom_root_parse (xmlNode *root_node, int write_updated, int write_link, int write_autor);

/**
 * Zpracování uzlu 'entry' ve formátu atom.
 * 
 * Průchod celým uzlem a poté výpis v pevně daném pořadí:
 * titulek, aktualizace, autor a url
 * 
 * @param entry_node kořenový uzel
 * @param write_updated příznak - výpis aktualizace
 * @param write_link příznak - výpis url
 * @param write_autor příznak - výpis autora
 * @param write_new_line příznak - výpis oddělujícího prázdného řádku
*/
void atom_entry_print (xmlNode *entry_node, int write_updated, int write_link, int write_autor, int *write_new_line);

/**
 * Zpracování uzlu 'author' ve formátu atom
 *
 * Vypíše jméno a email, pokud jsou tyto informace k dispozici
 * 
 * @param author_node kořenový uzel
*/
void atom_author_print (xmlNode *author_node);

/**
 * Zpracování uzlu 'link' ve formátu atom
 *
 * Vypíše url adresu, pokud je tato informace k dispozici
 * 
 * @param link_node kořenový uzel
*/
void atom_link_print (xmlNode *link_node);

#endif

// Konec souboru atom_parser.h