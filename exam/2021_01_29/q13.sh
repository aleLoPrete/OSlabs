#!/bin/bash

max=0;
maxword=" "

for word in $(ps -e | tr -s " " | cut -d " " -f 5 ); do
    wordLenght=${#word}
    echo $word [$wordLenght]
    if test $wordLenght -ge $max; then
        max=$wordLenght
        maxword=$word
    fi
    echo maxword: $maxword [$max]
done



echo process with longest name: $maxword