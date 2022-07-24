#!/bin/bash

func(){
	for (( i=0; i<$2; i++ )); do
		if [[ $(( $(echo $(stat $1 -c %s)) + $(echo $(stat $1 -c %s)) )) -gt "$3" ]];
		then
			break
		fi
		echo $(cat $1) >> "$1"
	done
}

text="Hello world"

if [[ $1 = "--help" ]]; then
	echo "This script concatinate file (first argument) inputed count of times (second argument)"
	echo "If the size of result file in bytes less or equal then inputed value (third argument)"
	echo "Use flag -d to concatinate default file"
else
	if [[ $1 = "-d" ]]; then
		file="file"
		if  test -f $file
		then
			rm $file
		fi
		touch $file
		echo $text >> $file
		func $file $2 $3
	else
		func $1 $2 $3
	fi
fi
