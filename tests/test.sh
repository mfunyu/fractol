#!/bin/bash

FRACTOL=./fractol
LOGFILE=./tests/instruction_log

TYPES=(
"Mandelbrot"
"Julia"
)

ARGS=(
#OK tests
""
"1"
"10"
"0.3"
"-0.5"
"10000000000"
"-11111111111111111111111111"
"2 0"
"1 1"
"-1 0"
"0 1"
"0.2 0.52"
"-0.3 0.69"
"a b c d e f g"
"aaaaaaa aaaaaaaa ttttt ee"
# extras
"-r high"
"-r mid"
"-r low"
"-r high -r low"
"-s 10"
"-s 100"
"-s 341"
"-s 1000"
"-s 10 -s 213"
"-r high -s 100"
"-s 200 -r low"
)

ERRS=(
# error tests
"-r wrongtype"
"-s 100000000000000"
"-s 0"
"-s -20"
"-s non-numeric"
"-s 20 -r hoge"
"-r mid -s high"
"100 -r mid -s high"
"0.3 0.6 -r mid -s -20"
"0.2 0.5 -r midddd -s 200"
)

#definitions
THICK="\033[1m"
CYAN="\033[1;36m"
RED="\033[31m"
GREEN="\033[32m"
RESET="\033[m"
PROMPT="${CYAN}$>${RESET} "


# Normal Tests
normal_tests(){
	printf "${THICK}<NORMAL TESTS>${RESET}\n"
	for type in "${TYPES[@]}"
	do
		printf "${CYAN}${type}${RESET}\n"
		for arg in "${ARGS[@]}"
		do
			printf "${PROMPT}${FRACTOL} ${type} ${arg}\n"
			${FRACTOL} $type $arg
			if [ $? != 0 ] ; then
				printf "${RED}KO :(${RESET}\n"
			fi
		done
	done
}

# Error Tests
error_tests(){
	printf "${THICK}<ERROR TESTS>${RESET}\n"
	for type in "${TYPES[@]}"
	do
		printf "${CYAN}${type}${RESET}\n"
		for arg in "${ERRS[@]}"
		do
			printf "${PROMPT}${FRACTOL} ${type} ${arg}"
			${FRACTOL} $type $arg > $LOGFILE
			size=`cat tests/instruction_log | wc | awk '{print$2}'`
			if [ $size == 0 ] ; then
				printf "${RED}	KO :(${RESET}\n"
			else
				printf "${GREEN}	OK :)${RESET}\n"
			fi
		done
	done
}

normal_tests
error_tests