#!/bin/bash

echo "Enter password"
read TRYTHIS

while [ "$TRYTHIS" != "secret" ]
do
    echo "Sorry, try again"
    read TRYTHIS
done

FOO=1

while [ "$FOO" -le 20 ]
do
    echo "Here we go again"
    FOO=$(($FOO + 1))
done

exit 0