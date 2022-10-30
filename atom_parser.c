#include "atom_parser.h"

void atom_root_parse (xmlNode *root_node, int write_updated, int write_link, int write_autor) {
    xmlNode *current_node = NULL;
    int write_new_line = 0;

    for (current_node = root_node->children; current_node; current_node = current_node->next) {
        if (current_node->type == XML_ELEMENT_NODE) {
            if (!strcmp((char *)current_node->name, "title")) {
                printf("*** %s ***\n", xmlNodeGetContent(current_node));
            } else if (!strcmp((char *)current_node->name, "entry")) {
                atom_entry_print (current_node, write_updated, 
                        write_link, write_autor, &write_new_line);
            }
        }
        
    }
}
void atom_entry_print (xmlNode *entry_node, int write_updated, 
            int write_link, int write_autor, int *write_new_line) {
    xmlNode *current_node = NULL;

    xmlNode *title = NULL;
    xmlNode *updated = NULL;
    xmlNode *author = NULL;
    xmlNode *link = NULL;


    for (current_node = entry_node->children; current_node; current_node = current_node->next) {
        if (current_node->type == XML_ELEMENT_NODE) {
            if (!strcmp((char *)current_node->name, "title")) {
                title = current_node;
            } else if (!strcmp((char *)current_node->name, "updated")) {
                updated = current_node;
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
        if (*write_new_line && (write_updated || write_autor || write_link)) printf("\n");

        printf("%s\n", xmlNodeGetContent(title));
        if (updated != NULL && write_updated) printf("Aktualizace: %s\n", xmlNodeGetContent(updated));
        if (author != NULL && write_autor) atom_author_print(author);
        if (link != NULL && write_link) atom_link_print(link);

        *write_new_line = 1;
    }
}

void atom_author_print (xmlNode *author_node) {
    xmlNode *current_node = NULL;

    xmlNode *name = NULL;
    xmlNode *email = NULL;

    for (current_node = author_node->children; current_node; current_node = current_node->next) {
        if (current_node->type == XML_ELEMENT_NODE) {
            if (!strcmp((char *)current_node->name, "name")) {
                name = current_node;
            } else if (!strcmp((char *)current_node->name, "email")) {
                email = current_node;
            }
        }
    }

    if (name != NULL && email != NULL) {
        printf("Autor: %s (%s)\n", xmlNodeGetContent(name), xmlNodeGetContent(email));  
    } else if (name != NULL) {
        printf("Autor: %s\n", xmlNodeGetContent(name));
    } else if (email != NULL) {
        printf("Autor: %s\n", xmlNodeGetContent(email));
    } else {
        printf("Autor: není uvedeno\n"); 
    }
}

void atom_link_print (xmlNode *link_node) {
    xmlAttr* attr = link_node->properties;
    while (attr != NULL) {
        if (!strcmp((char *)attr->name, "href")) {
            printf("URL: %s\n", (char*)attr->children->content);
            return;
        }
        attr = attr->next;
    }
    printf("URL: není uvedena\n");
}

