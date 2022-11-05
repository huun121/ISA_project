PROJ_NAME=feedreader
PROJ_TESTER=feedreader_tester
SRC_FILES=$(PROJ_NAME).c $(PROJ_NAME)_logic.c rss_parser.c atom_parser.c ssl.c
HEADER_FILES=$(PROJ_NAME)_logic.h rss_parser.h atom_parser.h ssl.h error_handling.h
SRC_FILES_TESTER=$(PROJ_TESTER).c $(PROJ_NAME)_logic.c rss_parser.c atom_parser.c ssl.c
HEADER_FILES_TESTER=$(PROJ_TESTER).h $(PROJ_NAME)_logic.h rss_parser.h atom_parser.h ssl.h error_handling.h
XMLAGS!=xml2-config --cflags --libs
XMLAGS?=$(shell xml2-config --cflags --libs)
SSL_ARGS=-lssl -lcrypto

ARGS:=-std=gnu99 -Wall -Wextra -Werror $(XMLAGS) $(SSL_ARGS)

.PHONY: clean feedreader

$(PROJ_NAME): clean
	gcc $(SRC_FILES) $(HEADER_FILES) -o $(PROJ_NAME) $(ARGS)

clean:
	@rm -f *.o $(PROJ_NAME)

test: clean_tester build_tester
	@./$(PROJ_TESTER)

build_tester:
	@gcc $(SRC_FILES_TESTER) $(HEADER_FILES_TESTER) -o $(PROJ_TESTER) $(ARGS)

clean_tester:
	@rm -f *.o $(PROJ_TESTER)
