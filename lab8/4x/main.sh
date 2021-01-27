#!/bin/bash

file="file.txt"

words=()
frequencies=()

for fileWord in `cat file.txt`
do
    i=0; # index of the arrays, resetted every time
    flag=0;
    for word in ${words[@]};do
        if [ "$fileWord" = "$word" ];then # se la parola è già presente ne aumento la frequenza
            (( frequencies[i]++ ))
            flag=1;
            break;
        fi
        i=($i+1); # aumento l'indice
    done

    if test $flag -eq 0; then # se la parola non è presente l'aggiungo all'array words e inserisco 1 frq
        words+=($fileWord)
        frequencies+=(1)
    fi

    #echo $fileWord 
    #if test $flag -eq 1 ;then
        #echo Frequenza aumentata ${frequencies[i]}
    #else
        #echo Nuova Parola Aggiunta!
    #fi
    #sleep 1
done

i=0
for word in ${words[*]}; do
    echo $word - ${frequencies[i]}  
    (( i++ ))
done
