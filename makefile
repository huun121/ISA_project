ARGS=-std=gnu99 -Wall -Wextra -Werror
SSL_ARGS=-lssl -lcrypto
PROJ_NAME=feedreader

.PHONY: clean feedreader

$(PROJ_NAME): clean
	gcc $(PROJ_NAME).c $(PROJ_NAME).h error_handling.h $(ARGS) -o $(PROJ_NAME) $(SSL_ARGS)

clean:
	rm $(PROJ_NAME) -f *.o