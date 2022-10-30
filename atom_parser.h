#ifndef _ATOM_PARSER_H_
#define _ATOM_PARSER_H_

#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

void atom_root_parse (xmlNode *root_node, int write_updated, int write_link, int write_autor);
void atom_entry_print (xmlNode *entry_node, int write_updated, int write_link, int write_autor, int *write_new_line);
void atom_author_print (xmlNode *author_node);
void atom_link_print (xmlNode *link_node);

#endif