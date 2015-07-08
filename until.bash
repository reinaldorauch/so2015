#!/bin/bash

echo "Is it morning? Please answer yes or no"
read TIMEOFDAY

case "$TIMEOFDAY" in
    "yes" ) echo "Good morning";;
    "no"  ) echo "Good Afternoon";;
    "y"   ) echo "Good morning";;
    "n"   ) echo "Good Afternoon";;
esac


case "$TIMEOFDAY" in
    "yes" | "y" | "Yes" | "YES" ) echo "Good morning";;
    "n*"  | "N*"  )               echo "Good Afternoon";;
    "*"   )                       echo "Dont know";;
esac

exit 0