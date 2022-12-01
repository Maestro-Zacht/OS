#!/bin/bash

if  [ $# -eq 0 ]; then
    echo "Insert file name:"
    read file
elif [ $# -eq 1 ]; then
    file=$1
else
    echo "$0 file or $0 and insert file"
    exit 1
fi

declare -A parole

for parola in $(cat "$file"); do
    if [ -v "parole[$parola]" ]; then
        let parole["$parola"]=parole["$parola"]+1
    else
        parole["$parola"]=1
    fi
done

for parola in ${!parole[*]}; do
    echo "$parola: ${parole[$parola]}"
done