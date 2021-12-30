#!/bin/bash

tests=("test" "plus" "braces" "andandorandnot" "quotes" "lowercasetf" "funkybraces")

make

for t in "${tests[@]}"
do
  printf "### $t ###\n"
  ./pyxx "testing/$t.pyxx"
  python3 "testing/$t.py"
done
