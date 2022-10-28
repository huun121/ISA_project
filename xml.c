#include "xml.h"

void xml_print_author (xmlNode *node) {
    xmlNode *current_node = NULL;

    for (current_node = node->children; current_node; current_node = current_node->next) {
        if (current_node->type == XML_ELEMENT_NODE) {
            if (!strcmp((char *)current_node->name, "name")) {
                printf("Autor: %s\n", xmlNodeGetContent(current_node));
                return;
            } 
        }
    }
    printf("Autor: není uvedeno\n");   
}

void xml_print_link (xmlNode *node) {
    xmlAttr* attr = node->properties;
    while (attr != NULL) {
        if (!strcmp((char *)attr->name, "href")) {
            printf("URL: %s\n", (char*)attr->children->content);
            return;
        }
        attr = attr->next;
    }
    printf("URL: není uvedena\n");
}

void xml_print_child (xmlNode *child_node, int write_updated, int write_link, int write_autor) {
    xmlNode *current_node = NULL;

    xmlNode *title = NULL;
    xmlNode *updated = NULL;
    xmlNode *author = NULL;
    xmlNode *link = NULL;


    for (current_node = child_node->children; current_node; current_node = current_node->next) {
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

    if (title != NULL) {
        printf("%s\n", xmlNodeGetContent(title));
        if (updated != NULL && write_updated) printf("Aktualizace: %s\n", xmlNodeGetContent(updated));
        if (author != NULL && write_autor) xml_print_author(author);
        if (link != NULL && write_link) xml_print_link(link);
        if (write_updated || write_autor || write_link) printf("\n");
    }
}

void xml_print_root (xmlNode *root_node, int write_updated, int write_link, int write_autor) {
    xmlNode *current_node = NULL;

    for (current_node = root_node->children; current_node; current_node = current_node->next) {
        if (current_node->type == XML_ELEMENT_NODE) {
            if (!strcmp((char *)current_node->name, "title")) {
                printf("*** %s ***\n", xmlNodeGetContent(current_node));
            }
        }
        xml_print_child (current_node, write_updated, write_link, write_autor);
    }

}

int xml_process (char *filename, int write_updated, int write_link, int write_autor) {
    xmlDoc *doc = NULL;
    xmlNode *root_node = NULL;

    // otestování kompability
    LIBXML_TEST_VERSION

    doc = xmlReadFile(filename, NULL, 0);
    if (doc == NULL) {
        ERROR_MESSAGE(ERR_M_XML);
        return ERROR_XML;
    }

    // zisk kořene a výpis
    root_node = xmlDocGetRootElement(doc);

    xml_print_root(root_node, write_updated, write_link, write_autor);

    // vyčištění
    xmlFreeDoc(doc);
    xmlCleanupParser();

    return SUCCESS;
}