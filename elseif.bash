#!/bin/bash

echo "Is it morning? Please answer yes or no:"

read TIMEOFDAY

if [ "$TIMEOFDAY" = "yes" ]
then
    echo "Good morning"
elif [ "$TIMEOFDAY" = "no" ]
then
    echo "Good afternoon"
else
    echo "Sorry, $TIMEOFDAY not recognized."
    echo "Enter yes or no"
    exit 1
fi

exit 0
