#!/usr/bin/env bash

MY_ARGS=( "libft" "srcs" "obj" "/$HOME")
FLAGS=( "Rl" "l" "lt" "tl" "al" "la" "rl" "lr" "Rl" "lart" "tral" "latr" "lat")
EXTRA_FLAGS=("a" "r" "t" "ta" "at" "ra" "ar" "rt" "tr" "f" "fr" "rf" "tf" "ft" "fa" "af" "fr" "rf" "rat" "art" "tra")
MY_EXECUTABLE="./ft_ls"
REFERENCE_EXECUTABLE="ls"

for arg in "${MY_ARGS[@]}"; do
  for flag in "${FLAGS[@]}"; do

    diff <($MY_EXECUTABLE "-$flag" "$arg") <($REFERENCE_EXECUTABLE "-$flag" "$arg")
    if [[ $? -ne 0 ]]; then
      echo "Test '$MY_EXECUTABLE -$flag $arg' failed"
      mkdir -p /tmp/errlog
      $MY_EXECUTABLE "-$flag" "$arg" > /tmp/errlog/ft_ls.log
      $REFERENCE_EXECUTABLE "-$flag" "$arg" > /tmp/errlog/real_ls.log
      exit 1
    fi
  done
done

#for arg in "${MY_ARGS[@]}"; do
#  for flag in "${EXTRA_FLAGS[@]}"; do
#
#    diff <($MY_EXECUTABLE "-$flag" "$arg") <($REFERENCE_EXECUTABLE "-$flag" "$arg" | tr '\n' ' ')
#    if [[ $? -ne 0 ]]; then
#      echo "Test '$MY_EXECUTABLE -$flag $arg' failed"
#      mkdir -p /tmp/errlog
#      $MY_EXECUTABLE "-$flag" "$arg" > /tmp/errlog/ft_ls.log
#      $REFERENCE_EXECUTABLE "-$flag" "$arg" > /tmp/errlog/real_ls.log
#      exit 1
#    fi
#  done
#done
