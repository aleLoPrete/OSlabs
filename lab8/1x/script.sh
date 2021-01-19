#!/bin/bash

directory=$1
function=$2
file=$3

grep -Hnr "$function *(.*)" $directory | sort -t ':' -k 1 -k 2rn > $file

exit 0
