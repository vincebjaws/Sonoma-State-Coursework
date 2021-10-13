#!/bin/bash

FILE=$1
AMOUNT=$(grep disaters.csv |
if [ ! $# -lt 2 ]; then
    echo "Not enough inputs"1>&2
    exit 1
fi

if [ $# -gt 2 ]; then
    echo "There are to many inputs" 1>&2
fi

