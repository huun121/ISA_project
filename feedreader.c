// Čtečka novinek ve formátu Atom a RSS s podporou TLS
// Projekt ISA
// VUT FIT v Brno
//
// Autor: Pavel Hurdalek (xhurda01)
// Datum: 30.10.2022

#include "feedreader_logic.h"

int main (int argc, char **argv) {
    int errcode = parse_args (argc, argv);
    if (errcode) return errcode;

    errcode = check_args ();
    if (errcode) return errcode;

    return feedreader ();
}

// Konec souboru feedreader.c