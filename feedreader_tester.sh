#!/bin/bash

# Čtečka novinek ve formátu Atom a RSS s podporou TLS
# Projekt ISA
# VUT FIT v Brno
#
# Autor: Pavel Hurdalek (xhurda01)
# Datum: 5.11.2022

RED='\033[0;31m'
GREEN='\033[0;32m'
NOCOLOR='\033[0m'

if [ $# -lt 1 ]; then
    echo -e "Použití: $0 <aplikace>\n" 
    exit 1
fi

app="$1"
diff="diff -ia --strip-trailing-cr"
folder="./tests/"

success_tests=0
failed_tests=0

echo -e "Spouští se testy...\n\n";
declare -a tests_types=("./tests/tests_parameters" "./tests/tests_URL")

# pro každý typ testu
for type in ./tests/*; do
    type_name=${type#$folder}
    echo -e "Typ testů: $type_name\n"

    # pro každý test
    for test in $type/*; do
        test_name=${test#"$type/"}

        test_command="$test/command.txt"
        test_ret="$test/return.txt"
        test_out="$test/output.txt"
        test_err="$test/error.txt"
        test_correct_out="$test/corr_output.txt"

        if [ ! -f "$test_command" ]; then
            echo -e "$RED Soubor $test_command chybí!\n$NOCOLOR"
            ((failed_tests++))
            continue;
        fi

        if [ ! -f "$test_ret" ]; then
            echo -e "$RED Soubor $test_ret chybí!\n$NOCOLOR"
            ((failed_tests++))
            continue;
        fi

        # spuštění
        command=$(cat "$test_command")
        eval "$command" > "$test_out" 2>"$test_err"

        err_code=$?

        $diff "$test_ret" <(echo "$err_code") 
        if [ $? != 0 ]; then
                echo -e "$RED TEST $test_name neuspěl.\n$NOCOLOR"
                ((failed_tests++))
                continue;
        fi

        if [ $err_code != 0 ]; then
            echo -e "$GREEN TEST $test_name uspěl.\n$NOCOLOR"
            ((success_tests++))
            continue;
        fi

        $diff "$test_correct_out" "$test_out"
        if [ $? != 0 ]; then
                echo -e "$RED TEST $test_name neuspěl.\n$NOCOLOR"
                ((failed_tests++))
        else
                echo -e "$GREEN TEST $test_name uspěl.\n$NOCOLOR"
                ((success_tests++))
                rm -f "$test_out" "$test_err"
        fi

    done
done

echo -e "\nPočet úspěšných testů: $success_tests\n"
echo -e "Počet neúspěšných testů: $failed_tests\n"

exit 0

# Konec souboru feedreader_tester.sh