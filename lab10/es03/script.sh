#!/bin/bash

if [ $# -ne 2 ] ; then
    echo "Usage: ./script.sh <user> <dir>"
    exit 1
fi

files=$(find $2 -user $1 -type f -exec grep -E -l -e "^\*\*\*Da modificare" \{} \;)

OIFS=$IFS
IFS=$'\n'

for file in files
do
    newfn="${file}_mod"
    grep -E -v -e "^\*\*\*Da modificare" $file > $newfn
    rm $file
done

IFS=$OIFS