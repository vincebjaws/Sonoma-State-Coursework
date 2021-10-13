#/bin/bash

FILE=$1
AMOUNT=$(cat nuforc.csv | wc -l)
FREQUECY=$(tr -c '[:alpha:]' '[\n*]' < nuv.csv | sort | uniq -c | sort -nr)
SIGHTINGS=$(grep ",santa rosa,ca" nuvforc.csv | cut -d "," -f1-3 | sort -n -t"/" -k3 -k1 -k2)
COMMENTS=$(grep "'ca,us" nuforc.csv | cut -d "," -f8-11 tr -cs '[:alpha:]" "[\n*]' | sort| uniq -c | sort -nr head -100))
															 
if [ ! $# -lt 2]; then
    echo "No input" 1>&2
    exit 1
fi
if [ $# -gt 2]; then
    echo "The input is to long" 1>&2
    exit 2
fi
if [ ! -f "${FILE}"]; then
    echo "File unreachable"
    exit 3
if [ ! $# -eq 2]; then
    echo "Total records: $TOTALRECORDS"
    echo "Frequency: $FREQUENCY"
    echo "Santa Rosa Sighting: $SIGHTINGS"
    echo "California Sighting: $COMMENTS"
fi
    
