// Čtečka novinek ve formátu Atom a RSS s podporou TLS
// Projekt ISA
// VUT FIT v Brno
//
// Autor: Pavel Hurdalek (xhurda01)
// Datum: 30.10.2022

#include "feedreader_logic.h"

int main (int argc, char **argv) {
    parse_args (argc, argv);

    check_args ();

    return feedreader ();
}

// Konec souboru feedreader.c