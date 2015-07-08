#!/bin/bash

for FOO in bar fud 43
do
    echo $FOO
done

for FILE in $(ls)
do
    echo $FILE
done
exit 0