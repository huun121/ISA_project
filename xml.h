#ifndef _XML_H_
#define _XML_H_

#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "error_handling.h"

int xml_process (char *filename, int write_updated, int write_link, int write_autor);
void xml_print_root (xmlNode *root_node, int write_updated, int write_link, int write_autor);
void xml_print_child (xmlNode *child_node, int write_updated, int write_link, int write_autor, int *write_new_line);
void xml_print_link (xmlNode *node);
void xml_print_author (xmlNode *node);

#endif