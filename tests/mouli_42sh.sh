#!/usr/bin/env bash
##
## EPITECH PROJECT, 2020
## Functional test
## File description:
## Head script
##

## Color def
RED='\e[91;1m'
GREEN='\e[92;1m'
BLUE='\e[94;1m'
NC='\e[0m'

##### Var def ####
## Built-ins
SCORE_BUILT_INS=0
BUILT_INS=0
## Error handling
SCORE_ERROR_HANDLING=0
ERROR_HANDLING=0
## Basic
SCORE_BASIC=0
BASIC=0
## Hard
SCORE_HARD=0
HARD=0
## Total
SCORE=0
TOTAL=0
#################

## Option
[[ $1 = "-v" ]] && VERBOSE=1 || VERBOSE=0
[[ $2 = "--mute" ]] && MUTE=1 || MUTE=0

#################################################################################

## Help
if [[ $1 = "-h" ]]; then
    echo -e " # 42SH HOME MOULI #\n"
    echo "Option:"
    echo "\$1  -v     Display difference between your output and tcsh output"
    echo "\$2  --mute Mute the print of test"
    echo -e "\nCredit:"
    echo "  Made by Episauce."
    exit
fi

function display_info()
{
  echo -e "---- Expected ----"
  cat .exp
  echo -e "----  My shit ----"
  cat .my
}

#################################################################################

function result()
{
    echo -e "\n----------------  PART ------------------"
    echo -e "print(f'Error handling: {$SCORE_ERROR_HANDLING/$ERROR_HANDLING*100:.2f}%')" | python3
    echo -e "print(f'Built-ins: {$SCORE_BUILT_INS/$BUILT_INS*100:.2f}%')" | python3
    echo -e "print(f'Basic: {$SCORE_BASIC/$BASIC*100:.2f}%')" | python3
    echo -e "print(f'Hard: {$SCORE_HARD/$HARD*100:.2f}%')" | python3
    echo -e "---------------- RESULT ----------------"
    echo -e "${BLUE}Done${NC}:    ${TOTAL}"
    echo -e "${GREEN}Success${NC}: ${SCORE}"
    echo -e "${RED}Failed${NC}:  $((TOTAL-SCORE))"
    echo -e "print(f'Score total:   {$SCORE/$TOTAL*100:.2f}%')" | python3
}

#################################################################################

## Test
function test_error_handling()
{
    TOTAL=$((TOTAL+1))
    ERROR_HANDLING=$((ERROR_HANDLING+1))
    if [[ ${MUTE} -eq 0 ]]; then echo -e "\nInput: [$1]"; fi
    echo -e "$1" | ./42sh &> .my
    echo -e "$1" | tcsh &> .exp
    diff .my .exp &> /dev/null

    if [[ -$? -eq 1 ]]; then
        if [[ ${MUTE} -eq 0 ]]; then echo -e "Result: ${RED}KO${NC}"; fi
        if [[ ${VERBOSE} -eq 1 ]]; then
            display_info .my .exp
        fi
    else
        if [[ ${MUTE} -eq 0 ]]; then echo -e "Result: ${GREEN}OK${NC}"; fi
        SCORE=$((SCORE+1))
        SCORE_ERROR_HANDLING=$((SCORE_ERROR_HANDLING + 1))
    fi
    rm .my .exp
}

function test_basic()
{
    TOTAL=$((TOTAL+1))
    BASIC=$((BASIC+1))
    if [[ ${MUTE} -eq 0 ]]; then echo -e "\nInput: [$1]"; fi

    echo -e "$1" | ./42sh &> .my
    echo -e "$1" | tcsh &> .exp
    diff .my .exp &> /dev/null

    if [[ $? -eq 1 ]]; then
        echo -e "Result: ${RED}KO${NC}"
        if [[ ${VERBOSE} -eq "-v" ]]; then
            display_info .my .exp
        fi
    else
        if [[ ${MUTE} -eq 0 ]]; then echo -e "Result: ${GREEN}OK${NC}"; fi
        SCORE=$((SCORE+1))
        SCORE_BASIC=$((SCORE_BASIC + 1))
    fi
    rm .my .exp
}

function test_built_ins()
{
    TOTAL=$((TOTAL+1))
    BUILT_INS=$((BUILT_INS+1))

    if [[ ${MUTE} -eq 0 ]]; then echo -e "\nInput: [$1]"; fi
    echo -e "$1" | ./42sh &> .my
    echo -e "$1" | tcsh &> .exp
    diff .my .exp &> /dev/null

    if [[ $? -eq 1 ]] ; then
        if [[ ${MUTE} -eq 0 ]]; then echo -e "Result: ${RED}KO${NC}"; fi
        if [[ ${VERBOSE} -eq "-v" ]]; then
            display_info .my .exp
        fi
    else
        if [[ ${MUTE} -eq 0 ]]; then echo -e "Result: ${GREEN}OK${NC}"; fi
        SCORE=$((SCORE+1))
        SCORE_BUILT_INS=$((SCORE_BUILT_INS + 1))
    fi
    rm .my .exp
}

function test_hard()
{
    TOTAL=$((TOTAL+1))
    HARD=$((HARD+1))

    if [[ ${MUTE} -eq 0 ]]; then echo -e "\nInput: [$1]"; fi
    echo -e "$1" | ./42sh &> .my
    echo -e "$1" | tcsh &> .exp
    diff .my .exp &> /dev/null

    if [[ $? -eq 1 ]]; then
        if [[ ${MUTE} -eq 0 ]]; then echo -e "Result: ${RED}KO${NC}"; fi
        if [[ ${VERBOSE} -eq "-v" ]]; then
            display_info .my .exp
        fi
    else
        if [[ ${MUTE} -eq 0 ]]; then echo -e "Result: ${GREEN}OK${NC}"; fi
        SCORE=$((SCORE+1))
        SCORE_HARD=$((SCORE_HARD + 1))
    fi
    rm .my .exp
}

######################################## TEST ###########################################

###### ERROR HANDLING
test_error_handling "|"
test_error_handling "ls > file > file2"
test_error_handling "echo test ||| echo lol"
test_error_handling "<<<"
test_error_handling ">>>"
test_error_handling "<"
test_error_handling ">"
test_error_handling "cat inexistant"
test_error_handling "cat main.c"
test_error_handling "cat ls"
test_error_handling "bite"
echo "int main() {return 1/0;}" > .test0.c; gcc -w .test0.c
test_error_handling "./a.out"
rm -f .test0.c a.out
echo "main;" > .test0.c; gcc -w .test0.c
test_error_handling "./a.out"
rm -f .test0.c a.out
test_error_handling "./lib"
test_error_handling "cat < ZKNDAKD"
test_error_handling "ls >"
test_error_handling "ls >>"
test_error_handling "ls <<"
test_error_handling "ls <"
test_error_handling "<< ls"
test_error_handling "< ls"
test_error_handling "> ls"
test_error_handling ">> ls"
test_error_handling "| ls"
test_error_handling "ls >>>>>>>>>>>>>"
test_error_handling "ls ><<<>>>>>>"
test_error_handling "ls ; &&&&&&&& echo &&&"
test_error_handling "ls ; ~qsddserfcs &&&&&&&&&"
test_error_handling "ls &&& marche po"
test_error_handling "catwoman :)"
test_error_handling "ls \" echo test"
test_error_handling "ls (()"
test_error_handling "ls ((()"
test_error_handling "ls \`"
test_error_handling "echo '"
test_error_handling "echo \"test \" \""

###### BASIC
test_basic "ls"
test_basic "echo test"
test_basic "ls"
test_basic "ls -l"
test_basic "cd"
test_basic "cat main.c"
test_basic "cd .."
test_basic "cd include"
test_basic "ls | cat"
test_basic "&&&&&&&&&&& ls ; &&&&&&&& echo test"
test_basic "./42sh"
test_basic "/bin/tree"
test_basic "rien"
test_basic "                        ls                 "
test_basic "                       ls                                     -l"
test_basic "                          ls                                                mo"
test_basic "&&&&&&&&&&&&&&&&&& ls"
test_basic ";;;;;;;;;;;;;;;;;;;;; ls"
test_basic "                           cd"
test_basic "cd il"
test_basic "lokiiiiiiils"
test_basic "  "
test_basic "ls cat main"
test_basic "                                                 ls"
test_basic " -l ls "
test_basic "                  cd                                 include"
test_basic " ls -            d"
test_basic "ls -hehe"
test_basic "                              "
test_basic ""
test_basic " \t"
test_basic "\t"
test_basic " \t     \t"
test_basic ";"
test_basic "ls;ls"
test_basic "ls;  ;ls;"
test_basic ";;;;;;;;;;ls;        ; ;            ;;     ls;;; ;"
test_basic "ls | cat -e"
test_basic "ls > file ; rm -f file"
test_basic "ls < file"
test_basic "cat < main.c > result && rm result"
test_basic "false && echo fail"
test_basic "false || echo yes"
test_basic "true && echo yes"
test_basic "true || echo lol"

###### BUILT-INS
### Which
## Valid
test_built_ins "which 3 4 5"
test_built_ins "which cat lol"
## Invalid
test_built_ins "which"

### Where
## Valid
test_built_ins "where cat"
test_built_ins "where cat cat"
## Invalid
test_built_ins "where"

### Repeat
## Valid
test_built_ins "repeat 34 echo pute"
test_built_ins "repeat 23 aaaa"
test_built_ins "repeat -1 echo lol"
test_built_ins "repeat 0 echo lol"
# Invalid
test_built_ins "repeat"
test_built_ins "repeat aaa"
test_built_ins "repeat aa 23"

### Setenv
## Valid
test_built_ins "setenv test && setenv | grep \"test\""
test_built_ins "setenv test 4 && setenv | grep \"test\""
## Invalid
test_built_ins "setenv 4 test"
test_built_ins "setenv a4# test"

### Unsetenv
## Valid
test_built_ins "unsetenv _ && unsetenv SHLVL && setenv pute 4 && setenv && unsetenv pute && setenv"
test_built_ins "unsetenv USER PATH _ && unsetenv SHLVL && etenv"
## Invalid
test_built_ins "unsetenv"

### Exit
## Valid
test_built_ins "exit"
test_built_ins "exit 54"
## Invalid
test_built_ins "exit 45 65 1234"
test_built_ins "exit a44"
test_built_ins "exit 46a"

### Cd
## Invalid
test_built_ins "cd test 4"
test_built_ins "cd inexistant"
test_built_ins "mkdir test && chmod 000 test && cd test ;  rm -rf test"

### echo
## Valid
test_built_ins "echo test"
test_built_ins "echo 4 lol"

###### HARD
test_hard "ls | cat && echo \"succes task boy\""
test_hard "mkdir test ; cd test ; ls -a ; ls | cat | wc -c > tutu ; cat tutu; rm -f tutu; cd ..; rm -rf test"
test_hard "ls > lol; cat lol; rm -f lol"
test_hard "ls > lol; ls >> lol; cat lol; rm -f lol"
test_hard "cd ; </etc/hosts od -c | grep xx | wc >> /tmp/z -l ; cd - && echo \“OK\”"
test_hard "find /etc -type f -exec cat '{}' \; | tr -c '.[:digit:]' '\n' | grep '^[^.][^.]*\.[^.][^.]*\.[^.][^.]*\.[^.][^.]*$'"

rm ls
result
