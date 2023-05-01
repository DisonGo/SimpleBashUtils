#!/bin/bash

SUCCESS=0
FAIL=0
DIFF_RES=""
FLAGS="b e n s t v"
RED="$(tput setaf 1)"
GREEN="$(tput setaf 2)"
BASE="$(tput setaf 7)"
declare -a tests=(
    "VAR test_case_cat.txt"
)
declare -a extra=(
    "-s test_1_cat.txt"
    "-b -e -n -s -t -v test_1_cat.txt"
    "-t test_3_cat.txt"
    "-n test_2_cat.txt"
    "no_file.txt"
    "-n -b test_1_cat.txt"
    "-s -n -e test_4_cat.txt"
    "-n test_1_cat.txt"
    "-n -e test_1_cat.txt"
    "-n test_1_cat.txt test_2_cat.txt"
    "-v test_5_cat.txt"
)
testing() {
    t=$(echo $@ | sed "s/VAR/$var/")
    ./s21_cat $t > test_s21_cat.log
    cat $t > test_sys_cat.log
    DIFF_RES="$(diff -s test_s21_cat.log test_sys_cat.log)"
    RESULT="SUCCESS"
    if [ "$DIFF_RES" == "Files test_s21_cat.log and test_sys_cat.log are identical" ]
    then
      (( SUCCESS++ ))
        RESULT="SUCCESS"
    else
      (( FAIL++ ))
        RESULT="FAIL"
    fi
    echo "[${GREEN}${SUCCESS}${BASE}/${RED}${FAIL}${BASE}] ${GREEN}${RESULT}${BASE} cat $t"
    rm test_s21_cat.log test_sys_cat.log
}

# специфические тесты
for i in "${extra[@]}"
do
    var="-"
    testing $i
done

# 1 параметр
for var1 in $FLAGS
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        testing $i
    done
done

# 2 параметра
for var1 in $FLAGS
do
    for var2 in $FLAGS
    do
        if [ $var1 != $var2 ]
        then
            for i in "${tests[@]}"
            do
                var="-$var1 -$var2"
                testing $i
            done
        fi
    done
done

# 3 параметра
for var1 in $FLAGS
do
    for var2 in $FLAGS
    do
        for var3 in $FLAGS
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then
                for i in "${tests[@]}"
                do
                    var="-$var1 -$var2 -$var3"
                    testing $i
                done
            fi
        done
    done
done

# 4 параметра
for var1 in $FLAGS
do
    for var2 in $FLAGS
    do
        for var3 in $FLAGS
        do
            for var4 in $FLAGS
            do
                if [ $var1 != $var2 ] && [ $var2 != $var3 ] \
                && [ $var1 != $var3 ] && [ $var1 != $var4 ] \
                && [ $var2 != $var4 ] && [ $var3 != $var4 ]
                then
                    for i in "${tests[@]}"
                    do
                        var="-$var1 -$var2 -$var3 -$var4"
                        testing $i
                    done
                fi
            done
        done
    done
done

echo "${RED}FAIL: ${FAIL}${BASE}"
echo "${GREEN}SUCCESS: ${SUCCESS}${BASE}"
