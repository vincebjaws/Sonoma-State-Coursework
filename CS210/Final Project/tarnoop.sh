#!/bin/bash

FILE=$1
FILENAME=$(file $1)

if [! $# -eq 1]; then
    echo "Not enough information" 1>&2
    exit 1
fi
if [$#-gt 2]; then
    echo "Too many inputs" 1>&2
    exit 2
fi
if [-f "${FILE}"]; then
    echo "File: $1"
    echo "Type: $FILENAME"
else
    echo "Not Valid"
    exit 3
fi
