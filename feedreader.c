#include "feedreader.h"

void feedreader_init () {
    write_time = 0;
    write_author = 0;
    write_url = 0;
    certfile = NULL;
    certaddr = NULL;
    url = NULL;
    feedfile = NULL;
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

int feedfile_open (FILE *file) {
    file = fopen(feedfile, "r");
    if (file is NULL) {
        return ERROR_INTERN;
    }
    return SUCCESS;
}

void feedfile_close (FILE *file) {
    fclose(file);
}

int get_new_url(FILE *file, char *line, int buffer) {
    while (1) {
        if (fgets(line, buffer - 1, file) != NULL) return FEED_END;
        
        if (line[0] is '#' || line[0] is '\n') continue;

        return SUCCESS;
    }
}

int main (int argc, char **argv) {
    int return_code;

    parse_args (argc, argv);

    check_args ();

    init_ssl ();

    // pouze URL
    if (feedfile is NULL) {
                
        return_code = ssl_url_process(TMP_FILENAME, url, certaddr, certfile);
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

    } else {    // feedfile

        FILE *file = NULL;
        if (feedfile_open(file)) {
            ERROR_MESSAGE_WITH_ARG(ERR_M_FEEDFILE_OPEN, feedfile);
            return ERROR_ARGUMENT_PARSE;
        }

        char line[BUFFER];
        while (get_new_url(file, line, BUFFER) is SUCCESS) {
            url = line;

            return_code = ssl_url_process(TMP_FILENAME, url, certaddr, certfile);
            free_ssl();
            if (return_code) {
                printf("\n");
                continue;
            }

            if (xml_process(TMP_FILENAME, write_time, write_url, write_author)) {
                printf("\n");
                continue;
            }

            printf("\n");
        }

        feedfile_close(file);
    }
        
    return SUCCESS;
}