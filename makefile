SSL_ARGS=-lssl -lcrypto
PROJ_NAME=feedreader
SRC_FILES=$(PROJ_NAME).c xml.c ssl.c
HEADER_FILES=$(PROJ_NAME).h xml.h ssl.h error_handling.h
XMLLDFLAGS!=xml2-config --cflags --libs
XMLLDFLAGS?=$(shell xml2-config --cflags --libs)
ARGS:=-std=gnu99 -Wall -Wextra -Werror $(XMLLDFLAGS) 

.PHONY: clean feedreader

$(PROJ_NAME): clean
	gcc $(SRC_FILES) $(HEADER_FILES) -o $(PROJ_NAME) $(ARGS) $(SSL_ARGS)

clean:
	rm -f *.o $(PROJ_NAME)
