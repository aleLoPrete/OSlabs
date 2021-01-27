#!/bin/bash

echo "Inser a file name:"

#read file
file="file.txt"

lines=$(wc -l $file)

echo "Number of lines: ${lines}"

# reading file line by line, counting character and saving max char line 
maxChar=0

while read line 
do 
    nChar=${#line}
    #echo "nChar: ${nChar}"
    if test $nChar -gt $maxChar
    then
        maxChar=$nChar
        maxLine=$line
    fi
done <$file

echo "longest line and its character count:"
echo $maxLine
echo character count:$maxChar