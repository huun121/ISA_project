// Čtečka novinek ve formátu Atom a RSS s podporou TLS
// Projekt ISA
// VUT FIT v Brno
//
// Autor: Pavel Hurdalek (xhurda01)
// Datum: 5.11.2022

#include "feedreader_tester.h"

FILE *test_output;

int success_tests = 0;
int failed_tests = 0;

int test_setup() {
    freopen(TEST_STDERR, "w", stderr);

    return SUCCESS;
}

void wrong_params_test_process(int argc, char *argv[], const char *name) {
    int errcode = SUCCESS;
    
    errcode = parse_args (argc, argv);
    if (!errcode) errcode = check_args();

    if (errcode == ERROR_ARGUMENT_PARSE) {
        printf("Test %s uspěl.\n", name);
        success_tests++;
    } else {
        printf("Test %s neuspěl!!! Parametry: ", name);
        failed_tests++;
        for (int i = 0; i < argc; i++) {
            printf("%s ", argv[i]);
        }
        printf("\n");
    }
}

void params_tests() {
    printf("Testy parametrů:\n");
    /*                            {""},
                                {"http://www.exaple.com", "-C"},
                                {"http://www.exaple.com", "-c"},
                                {"http://www.exaple.com", "-f"},
                                {"http://www.exaple.com", "-f", "soubor"},
                                {"-f"},
                                {"-f", "soubor", "-C"},
                                {"-f", "soubor", "-c"},
                            };*/
    char **argv = (char **){"-a", "-T"};
    wrong_params_test_process((int) (sizeof(argv)/sizeof(char*)), argv,
                        "Žádný parametr");
    argv = (char **) {"-a", "-T"};
    wrong_params_test_process((int) (sizeof(argv)/sizeof(char*)), argv,
                        "Žádná URL");

}


int main () {
    printf("Spouští se testy...\n\n");

    test_setup();

    params_tests();

    printf("\nPočet úspěšných testů: %d\nPočet neúspěšných testů: %d\n", success_tests, failed_tests);
    
    fclose(stderr);
    remove(TEST_STDERR);
    return 0;
}

// Konec souboru feedreader_tester.c