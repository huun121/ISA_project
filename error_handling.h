#ifndef ERROR_HANDLING

#define ERR_M_SAME_ARGS "Chyba: dvakrát zadán stejný argument: %s\n"
#define ERR_M_NO_PARAM "Chyba: nebyl zadán povinný parametr k argumentu: %s\n"
#define ERR_M_NO_SOURCE "Chyba: nebyl zadán feedfile ani URL\n"
#define ERR_M_TWO_SOURCES "Chyba: byl zadán feedfile i URL\n"
#define ERR_WRONG_URL "Chyba: chybně zadaná url\n"
#define ERR_SSL_TLS "Chyba: nepodařilo se ověřit platnost certifikátu\n"
#define ERR_INTERN "Chyba: interní chyba programu\n"

#define ERROR_HANDLE(message, errorCode) {\
    fprintf(stderr, message);\
    exit(errorCode);\
}

#define ARG_TWO_TIMES fprintf(stderr, ERR_M_SAME_ARGS, argument)
#define ARG_NO_PARAM fprintf(stderr, ERR_M_NO_PARAM, argument)

#define SUCCESS 0
#define ERROR 1

#endif