#!/usr/bin/env bash

MY_ARGS=("libft" "srcs" "obj" "$HOME" "" "/tmp")
MY_EXECUTABLE="./ft_ls -l"
REFERENCE_EXECUTABLE="ls -l"
ARG="/tmp/specialstuff"

mkdir -p /tmp/specialstuff
touch /tmp/specialstuff/userid_on /tmp/specialstuff/userid_off
touch /tmp/specialstuff/userid_dir_on /tmp/specialstuff/userid_dir_off
touch /tmp/specialstuff/groupid_on /tmp/specialstuff/groupid_off
touch /tmp/specialstuff/groupid_dir_on /tmp/specialstuff/groupid_dir_off
touch /tmp/specialstuff/stickybit_on /tmp/specialstuff/stickbit_off
touch /tmp/specialstuff/stickybit_dir_on /tmp/specialstuff/stickbit_dir_off

chmod u+s /tmp/specialstuff/userid_on /tmp/specialstuff/userid_dir_on
chmod g+s /tmp/specialstuff/groupid_on /tmp/specialstuff/groupid_dir_on
chmod +t /tmp/specialstuff/stickybit_on /tmp/specialstuff/stickybit_dir_on

diff <($MY_EXECUTABLE "$ARG") <($REFERENCE_EXECUTABLE "$ARG")
if [[ $? -ne 0 ]]; then
    echo "Test '$MY_EXECUTABLE $ARG' failed"
exit 1
fi
