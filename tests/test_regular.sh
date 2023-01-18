#!/usr/bin/env bash

MY_ARGS=("libft" "srcs" "obj" "$HOME" "" "/tmp")
MY_EXECUTABLE="./ft_ls -l"
REFERENCE_EXECUTABLE="ls -l"

for arg in "${MY_ARGS[@]}"; do
  diff <($MY_EXECUTABLE $arg) <($REFERENCE_EXECUTABLE $arg)
  if [[ $? -ne 0 ]]; then
    echo "Test '$MY_EXECUTABLE $arg' failed"
    exit 1
  fi
done
