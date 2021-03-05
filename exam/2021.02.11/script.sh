#!/bin/bash

cd ~/codingprojects/OSlabs/exam/prova
rm tmp.txt;
touch tmp.txt;

find . -name "*" -exec echo \{} >>tmp.txt  \;

echo ecco il file:
cat tmp.txt

while read line; do 
    grepresult=" ";
    greptest=" ";
    grepresult=$(grep $line -regex "$line");
    echo ecco il greresult: $grepresult
    if [ $greptest != $grepresult ]; then
        mv $line "$line"_new
    fi
done <tmp.txt