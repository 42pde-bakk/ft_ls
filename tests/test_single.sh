#!/usr/bin/env bash

RED=$'\e[1;31m'
GREEN=$'\e[1;32m'
MAGENTA=$'\e[1;35m'
CYN=$'\e[1;36m'
END=$'\e[0m'

MY_EXECUTABLE="./ft_ls"
REFERENCE_EXECUTABLE="ls"

echo "Testing '" "$@" "'."
diff <($MY_EXECUTABLE "$@") <($REFERENCE_EXECUTABLE "$@")
if [[ $? -ne 0 ]]; then
    echo "${RED}Test '$MY_EXECUTABLE" "$@" "' failed ${END}"
    mkdir -p /tmp/errlog
    $MY_EXECUTABLE "$@" > /tmp/errlog/ft_ls.log
    $REFERENCE_EXECUTABLE "$@" > /tmp/errlog/real_ls.log
exit 1
fi
echo "${GREEN}Test passed${END}"
