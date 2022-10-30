#ifndef _RSS_PARSER_H_
#define _RSS_PARSER_H_

#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

void rss_root_parse (xmlNode *root_node, int write_updated, int write_link, int write_autor);
void rss_channel_parse (xmlNode *channel_node, int write_pubDate, int write_link, int write_autor);
void rss_item_print (xmlNode *item_node, int write_pubDate, int write_link, int write_autor, int *write_new_line);

#endif