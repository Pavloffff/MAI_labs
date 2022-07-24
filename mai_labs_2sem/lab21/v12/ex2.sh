#!/bin/bash

chr() {
  [ "$1" -lt 256 ] || return 1
  printf "\\$(printf '%03o' "$1")"
}

ord() {
  LC_CTYPE=C printf '%d' "'$1"
}

func() {
	modul=26
	alf=0
	lower=0
	text=''
	point=0
	word=0
	digit=0
	num=$3

	if [[ $1 == *"."* ]]; then
		point=1
	fi 

	if [ ! -z "${num##*[!0-9]*}" ]; then
		digit=1
		cnt=$2
		start=$3
	else
		word=1
		cnt=$2
		start=$(ord $3)
	fi

	if [ $word = 1 ]; then
		if [ $start -ge 97 ] && [ $start -le 122 ]; then
			lower=1
		fi
	fi

	if [ $point = 1 ]; then
		if [ $digit = 1 ]; then
			for (( number = $start; number < $[ $start + $cnt ] ; number++ ))
			do
					cp "$1" "$( echo $1 | cut -d"." -f1)$number.$( echo $1 | cut -d"." -f2)"
			done
		else
			if [ $lower = 1 ]; then
				for (( number = $[ start - 97 ]; number < $[ $start + $cnt - 97 ] ; number++ ))
				do
						alf=$(($number%$modul))
						cp "$1" "$( echo $1 | cut -d"." -f1)$text$(chr $[ $alf + 97 ]).$( echo $1 | cut -d"." -f2)"
						if [ $alf = 25 ]; then
							text+="a"
						fi
				done
			else
				for (( number = $[ start - 65 ]; number < $[ $start + $cnt - 65 ] ; number++ ))
				do
						alf=$(($number%$modul))
						cp "$1" "$( echo $1 | cut -d"." -f1)$text$(chr $[ $alf + 65 ]).$( echo $1 | cut -d"." -f2)"
						if [ $alf = 25 ]; then
							text+="A"
						fi
				done
			fi
		fi
	else
		if [ $digit = 1 ]; then
			for (( number = $start; number < $[ $start + $cnt ] ; number++ ))
			do
					cp "$1" "$1$number"
			done
		else
			if [ $lower = 1 ]; then
				for (( number = $[ start - 97 ]; number < $[ $start + $cnt - 97 ] ; number++ ))
				do
					#echo $number
						alf=$(($number%$modul))
						#echo $alf
						
						cp "$1" "$1$text$(chr $[ $alf + 97 ])"
						if [ $alf = 25 ]; then
							text+="a"
						fi
				done
			else
				for (( number = $[ start - 65 ]; number < $[ $start + $cnt - 65 ] ; number++ ))
				do
						alf=$(($number%$modul))
						echo $alf
						cp "$1" "$1$text$(chr $[ $alf + 65 ])"
						if [ $alf = 25 ]; then
							text+="A"
						fi
				done
			fi
		fi
	fi
}

if [[ $1 = "--help" ]]; then
	echo "Создание копий указанного файла, начиная с некоторой нумерации. Принимает name k n (имя файла, кол-во копий, номер с которого начинается нумерация копий.) "
	shift 1
	func $1 $2 $3
fi

if [[ $1 = "-p" ]]; then
	read -p "Continue (y/n)? " cont
	if [ "$cont" = "y" ]; then
		func $2 $3 $4
	else
		exit 1
	fi
else
	func $1 $2 $3
fi
