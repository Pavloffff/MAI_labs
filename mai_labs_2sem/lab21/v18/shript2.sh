#!/usr/bin/env bash

RecursiveDirectory(){
	text=''
    for fileName in `ls $1/`
    do
    	text="$( echo $1 | sed 's/\//\\/g')"
		if [[ -f "$1/$fileName" ]]; then
			ismk=$( echo $fileName | cut -c1-8)
			if [ "$ismk" = "Makefile" ]; then
				echo "$text\\$fileName" | sed 's/\\\\/\\/g'
				text=''
				continue
			else
				echo "$1/$fileName" | sed 's/\/\//\//g'
				continue
			fi
		fi
		
    if [ -d "$1/$fileName" ]; then
        RecursiveDirectory "$1/$fileName"
        continue
    fi
    
    done
}

if [[ $1 = "-p" ]]; then
	read -p "Continue (y/n)?" cont
	if [ "$cont" = "y" ]; then
	  if [ -z "$2" ]; then
	  	RecursiveDirectory . 
	  else
	  	RecursiveDirectory $2

	  fi
	  exit 0
	else
	  exit 1
	fi
else
	if [ -z "$1" ]; then
	  	RecursiveDirectory .
	else
	  	RecursiveDirectory $1
	fi
fi