// Čtečka novinek ve formátu Atom a RSS s podporou TLS
// Projekt ISA
// VUT FIT v Brno
//
// Autor: Pavel Hurdalek (xhurda01)
// Datum: 30.10.2022

#ifndef _ERROR_HANDLING_H_
#define _ERROR_HANDLING_H_

#include <stdio.h>

#ifndef OUT
#define OUT stdout
#endif

#ifndef ERROUT
#define ERROUT stderr
#endif

// chybové hlášky
#define ERR_M_SAME_ARGS "Chyba: dvakrát zadán stejný argument: %s\n"
#define ERR_M_NO_PARAM "Chyba: nebyl zadán povinný parametr k argumentu: %s\n"
#define ERR_M_NO_SOURCE "Chyba: nebyl zadán feedfile ani URL\n"
#define ERR_M_TWO_SOURCES "Chyba: byl zadán feedfile i URL\n"
#define ERR_WRONG_URL "Chyba: chybně zadaná url\n"
#define ERR_M_SSL_TLS "Chyba: nepodařilo se ověřit platnost certifikátu\n"
#define ERR_M_INTERN "Chyba: interní chyba programu\n"
#define ERR_M_XML "Chyba: nebylo možné zpracovat xml soubor\n"
#define ERR_M_XML_UNKNOWN "Chyba: nepodporovaný formát xml\n"
#define ERR_M_FEEDFILE_OPEN "Chyba: nebylo možné otevřít soubor: %s\n"
#define ERR_M_FILE "Chyba: chyba při práci se soubory\n"
#define ERR_M_CONNECTION "Chyba: nepodařilo se navázat spojení s %s\n"

#define ERROR_MESSAGE(_message) fprintf(ERROUT, _message)
    
#define ERROR_MESSAGE_EXIT(_message, _errorCode) {\
    ERROR_MESSAGE(_message);\
    exit(_errorCode);\
}

#define ERROR_MESSAGE_WITH_ARG(_message, _argument) fprintf(ERROUT, _message, _argument)

// návratové hodnoty
#define SUCCESS 0
#define ERROR_ARGUMENT_PARSE 1
#define ERROR_ARGUMENT_PARSE_URL 2
#define ERROR_SSL 3
#define ERROR_XML 4
#define ERROR_UNDEFINED 9
#define ERROR_INTERN 42

#endif

// Konec souboru error_handling.c