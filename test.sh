#!/bin/bash

tests=("test" "plus" "braces" "andandorandnot" "quotes")

make

for t in "${tests[@]}"
do
  printf "### $t ###\n"
  ./pyxx "testing/$t.pyxx"
  python3 "testing/$t.py"
done
