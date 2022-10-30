#include "rss_parser.h"

void rss_item_print (xmlNode *item_node, int write_pubDate, int write_link, int write_autor, int *write_new_line) {
    xmlNode *current_node = NULL;

    xmlNode *title = NULL;
    xmlNode *pub_date = NULL;
    xmlNode *author = NULL;
    xmlNode *link = NULL;


    for (current_node = item_node->children; current_node; current_node = current_node->next) {
        if (current_node->type == XML_ELEMENT_NODE) {
            if (!strcmp((char *)current_node->name, "title")) {
                title = current_node;
            } else if (!strcmp((char *)current_node->name, "pubDate")) {
                pub_date = current_node;
            } else if (!strcmp((char *)current_node->name, "author")) {
                author = current_node;
            } else if (!strcmp((char *)current_node->name, "link")) {
                link = current_node;
            }
        }
    }

    // pokud není titul nevipisuje
    if (title != NULL) {
        // výpis oddělujícího volného řádku
        if (*write_new_line && (write_pubDate || write_autor || write_link)) printf("\n");

        printf("%s\n", xmlNodeGetContent(title));
        if (pub_date != NULL && write_pubDate) printf("Aktualizace: %s\n", xmlNodeGetContent(pub_date));
        if (author != NULL && write_autor) printf("Autor: %s\n", xmlNodeGetContent(author));;
        if (link != NULL && write_link) printf("URL: %s\n", xmlNodeGetContent(link));;

        *write_new_line = 1;
    }
}

void rss_channel_parse (xmlNode *channel_node, int write_pubDate, int write_link, int write_autor) {
    xmlNode *current_node = NULL;
    int write_new_line = 0;

    for (current_node = channel_node->children; current_node; current_node = current_node->next) {
        if (current_node->type == XML_ELEMENT_NODE) {
            if (!strcmp((char *)current_node->name, "title")) {
                printf("*** %s ***\n", xmlNodeGetContent(current_node));
            } else if (!strcmp((char *)current_node->name, "item")) {
                rss_item_print (current_node, write_pubDate, write_link, write_autor, &write_new_line);
            }
        }
    }
}

void rss_root_parse (xmlNode *root_node, int write_pubDate, int write_link, int write_autor) {
    xmlNode *current_node = NULL;

    for (current_node = root_node->children; current_node; current_node = current_node->next) {
        if (current_node->type == XML_ELEMENT_NODE) {
            if (!strcmp((char *)current_node->name, "channel")) {
                rss_channel_parse (current_node, write_pubDate, write_link, write_autor);
            }
        }
    }
}