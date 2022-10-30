PROJ_NAME=feedreader
SRC_FILES=$(PROJ_NAME).c rss_parser.c atom_parser.c ssl.c
HEADER_FILES=$(PROJ_NAME).h rss_parser.h atom_parser.h ssl.h error_handling.h
XMLAGS!=xml2-config --cflags --libs
XMLAGS?=$(shell xml2-config --cflags --libs)
SSL_ARGS=-lssl -lcrypto

ARGS:=-std=gnu99 -Wall -Wextra -Werror $(XMLAGS) $(SSL_ARGS)

.PHONY: clean feedreader

$(PROJ_NAME): clean
	gcc $(SRC_FILES) $(HEADER_FILES) -o $(PROJ_NAME) $(ARGS)

clean:
	rm -f *.o $(PROJ_NAME)
