ARGS=-std=gnu99 -Wall -Wextra -Werror
SSL_ARGS=-lssl -lcrypto
XML_ARGS=-lxml2
PROJ_NAME=feedreader
SRC_FILES=$(PROJ_NAME).c xml.c ssl.c
HEADER_FILES=$(PROJ_NAME).h xml.h ssl.h error_handling.h

.PHONY: clean feedreader

$(PROJ_NAME): clean
	gcc $(SRC_FILES) $(HEADER_FILES) -o $(PROJ_NAME) $(ARGS) $(shell xml2-config --cflags) $(XML_ARGS) $(SSL_ARGS)

clean:
	rm $(PROJ_NAME) -f *.o