// Čtečka novinek ve formátu Atom a RSS s podporou TLS
// Projekt ISA
// VUT FIT v Brno
//
// Autor: Pavel Hurdalek (xhurda01)
// Datum: 30.10.2022

#include "feedreader_logic.h"

int write_time = 0;
int write_author = 0;
int write_url = 0;
char *certfile = NULL;
char *certaddr = NULL;
char *url = NULL;
char *feedfile = NULL;

void print_help () {
    fprintf(OUT, \
    "\rČtečka novinek ve formátu Atom a RSS s podporou TLS\n\
    \rPoužití:\n\
    ./feedreader <URL | -f <feedfile>> [-c <certfile>] [-C <certaddr>] [-T] [-a] [-u]\n\
    ./feedreader <-h | --help>\n\
    \n\
    \rArgumenty:\n\
    - URL -> Url adresa zdroje\n\
    - -f <feedfile> -> název souboru s url adresami zdrojů\n\
    - -c <certfile> -> soubor s certifikáty pro ověření platnosti certifikátu SSL/TLS\n\
    - -C <certaddr> -> adresář, ve kterém se mají vyhledávat certifikáty (SSL/TLS)\n\
    - -T -> pro každý záznam zobrazí navíc informace o čase změny záznamu\n\
    - -a -> pro každý záznam zobrazí jméno autora, či jeho e-mailová adresa\n\
    - -u -> pro každý záznam zobrazí asociované URL\n\
    - -h | --help -> zobrazí tuto nápovědu\n\
    \n\
    \rNávratové hodnoty:\n\
    - 0 -> průběh bez chyby\n\
    - > 0 -> objevila se chyba\n\
    \n\
    \rChybové hlášky jsou vypisovány na standartní chybový výstup.\n");
}

void parse_args (int argc, char **argv) {
    (void) argc;
    for (int i = 1; i < argc; i++) {

        char *argument = argv[i];

        if (!strcmp(argument, "-T")) {
            if (!write_time) write_time = 1;
            else ERROR_MESSAGE_WITH_ARG(ERR_M_SAME_ARGS, argument);
        } else if (!strcmp(argument, "-a")) {
            if (!write_author) write_author = 1;
            else ERROR_MESSAGE_WITH_ARG(ERR_M_SAME_ARGS, argument);
        } else if (!strcmp(argument, "-u")) {
            if (!write_url) write_url = 1;
            else ERROR_MESSAGE_WITH_ARG(ERR_M_SAME_ARGS, argument);
        } else if (!strcmp(argument, "-c")) {
            i++;
            if (i >= argc) {
                ERROR_MESSAGE_WITH_ARG(ERR_M_NO_PARAM, argument);
                exit(ERROR_ARGUMENT_PARSE);
            }
            if (!certfile) certfile = argv[i];
            else ERROR_MESSAGE_WITH_ARG(ERR_M_SAME_ARGS, argument);
        } else if (!strcmp(argument, "-C")) {
            i++;
            if (i >= argc) {
                ERROR_MESSAGE_WITH_ARG(ERR_M_NO_PARAM, argument);
                exit(ERROR_ARGUMENT_PARSE);
            }
            if (!certaddr) certaddr = argv[i];
            else ERROR_MESSAGE_WITH_ARG(ERR_M_SAME_ARGS, argument);
        } else if (!strcmp(argument, "-f")) {
            i++;
            if (i >= argc) {
                ERROR_MESSAGE_WITH_ARG(ERR_M_NO_PARAM, argument);
                exit(ERROR_ARGUMENT_PARSE);
            }
            if (!feedfile) feedfile = argv[i];
            else ERROR_MESSAGE_WITH_ARG(ERR_M_SAME_ARGS, argument);
        } else if (!strcmp(argument, "-h") || !strcmp(argument, "--help")) {
            print_help();
            exit(SUCCESS);
        } else {
            if (!url) url = argv[i];
            else {argument = "URL adresa"; ERROR_MESSAGE_WITH_ARG(ERR_M_SAME_ARGS, argument);}
        }
    }
}

void check_args () {
    if (!feedfile && !url){
        ERROR_MESSAGE_EXIT(ERR_M_NO_SOURCE, ERROR_ARGUMENT_PARSE);
    }
    if (feedfile && url){
        ERROR_MESSAGE_EXIT(ERR_M_TWO_SOURCES, ERROR_ARGUMENT_PARSE);
    }
}

int get_new_url(FILE *file, char *line, int buffer) {
    while (1) {
        if (fgets(line, buffer - 1, file) == NULL) return FEED_END;
        
        if (line[0] is '#' || line[0] is '\n') continue;

        return SUCCESS;
    }
}

int xml_process () {
    xmlDoc *doc = NULL;
    xmlNode *root_node = NULL;

    // otestování kompability
    LIBXML_TEST_VERSION

    doc = xmlReadFile(TMP_FILENAME, NULL, 0);
    if (doc == NULL) {
        ERROR_MESSAGE(ERR_M_XML);
        return ERROR_XML;
    }

    // zisk kořene a výpis
    root_node = xmlDocGetRootElement(doc);

    if (!strcmp((char *)root_node->name, "feed")) {
        atom_root_parse(root_node, write_time, write_url, write_author);
    } else if (!strcmp((char *)root_node->name, "rss")) {
        rss_root_parse(root_node, write_time, write_url, write_author);
    } else {
        ERROR_MESSAGE(ERR_M_XML_UNKNOWN);
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return ERROR_XML;
    }

    // vyčištění
    xmlFreeDoc(doc);
    xmlCleanupParser();

    return SUCCESS;
}

int feedreader_url () {
    int return_code = ssl_url_process(TMP_FILENAME, url, certaddr, certfile);
    free_ssl();
    if (return_code) {
        remove_tmp_file(TMP_FILENAME);
        return return_code;
    }

    if (xml_process(TMP_FILENAME, write_time, write_url, write_author)) {
        remove_tmp_file(TMP_FILENAME);
        return ERROR_XML;
    }

    remove_tmp_file(TMP_FILENAME); 
    return SUCCESS;
}

int feedreader_feedfile () {
    int return_code = SUCCESS;
    int error_code = SUCCESS;

    FILE *file = fopen(feedfile, "r");
    if (file is NULL) {
        ERROR_MESSAGE_WITH_ARG(ERR_M_FEEDFILE_OPEN, feedfile);
        return ERROR_ARGUMENT_PARSE;
    }

    char line[BUFFER];
    int write_new_line = 0;
    while (get_new_url(file, line, BUFFER) is SUCCESS) {
        if (write_new_line) fprintf(OUT, "\n");
        url = line;

        // Odstranění případného znaku '\n'

        // -----              -----
        // Taken code from stackoverflow.com
        // url: https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input
        // answer author: https://stackoverflow.com/users/485088/tim-%c4%8cas
        url[strcspn(url, "\n")] = 0;
        // -----              -----

        error_code = ssl_url_process(TMP_FILENAME, url, certaddr, certfile);
        free_ssl();
        if (error_code) {
            return_code = error_code;
            continue;
        }

        error_code = xml_process();
        if (error_code) {
            return_code = error_code;
            continue;
        }
        write_new_line = 1;            
    }

    fclose(file);
    remove_tmp_file(TMP_FILENAME); 

    return return_code;
}

int feedreader () {
    init_ssl ();

    // pouze URL
    if (feedfile is NULL) {
        return feedreader_url(); 
    } else {    // feedfile
        return feedreader_feedfile();        
    }
}
// Konec souboru feedreader_logic.c