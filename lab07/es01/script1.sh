#!/bin/bash

if  [ $# -ne 3 ]
then
    echo "$0 directory function output_file"
    exit 1
fi

files=$(find "$1" -type f -exec grep -H -n "$2" \{} \; | tr : " " | sort -k1,1 -k2,2n)
echo "$files" > "$3"