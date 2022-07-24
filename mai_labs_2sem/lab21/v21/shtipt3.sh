#!/usr/bin/env bash

RecursiveRm(){																			#Функция, вызываемая от имя дирректории ($1) и суффикса ($2)
    for fileName in `ls $1/`															#Проходим циклом по списку содержимого директории (ls)
    do
		if [[ -f "$1/$fileName" ]]; then												#Проверяем, является ли счетчик файлом
			if [[ $( echo $fileName	 | cut -d"." -f2) = $2 ]]; then						#Если это файл и его расширение равно переменной суффикс,
				rm "$1/$fileName"														#То удаляем
			fi
		fi
		
    if [ -d "$1/$fileName" ]; then														#Если счетчик является директорией
        RecursiveRm "$1/$fileName" $2                                                   #То вызываем функцию от счетчика и суффикса
        continue																		#И затем переходим к следующему элементу
    fi
    
    done
}

if [[ $1 = "-p" ]]; then																#Установка режима подтверждения (задание 5) с помощью флага -p
	if [[ $2 = "-d" ]]; then															#Установка режима диалогового окна (задание 6) с помощью флага -d
		while true; do                                                                  #Запускаем диалоговое окно (бесконечный цикл с возможностью выхода)
			#read -p "Continue (y/n)? " 
			read -p "Input directory and suffix or q to quit: " dirname suffix			#Принимаем на вход новые данные
			if [[ $1 = "q" ]]; then														#Выход из цикла с помощью q
				exit 0											
			else
				read -p "Continue (y/n)? " cont                                         #Реализация диалогового окна и режима подтверждения вместе
				if [ "$cont" = "y" ]; then												#На каждом шаге спрашиваем разрешение
					if [[ "$dirname" = "q" ]]; then										
						exit 0
					else	
						RecursiveRm $dirname $suffix									#Наконец вызываем функцию от заданных в диалоговом окне значений
					fi 																	#(dirname это $1 в функции, а $suffix это $2 в функции)		
				else
					exit 1
				fi
			fi
		done
	else
		read -p "Continue (y/n)?" cont 													#Режим подтверждения без диалогового окна
		if [ "$cont" = "y" ]; then  													#$1 здесь это флаг -p
		  	RecursiveRm $2 $3															#Поэтому вызываем от $2 и $3
		  exit 0
		else
		  exit 1
		fi
	fi
elif [[ $1 = "-d" ]]; then																#То же самое, но если -d идет первым
	if [[ $2 = "-p" ]]; then
		while true; do
			#read -p "Continue (y/n)? " cont
			read -p "Input directory and suffix or q to quit: " dirname suffix
			if [[ $1 = "q" ]]; then
				exit 0
			else
				read -p "Continue (y/n)? " cont
				if [ "$cont" = "y" ]; then
					if [[ "$dirname" = "q" ]]; then
						exit 0	
					else	
						RecursiveRm $dirname $suffix
					fi
				else
					exit 1
				fi
			fi
		done
	else
		while true; do   																#Режим диалогового окна без режима подтверждения
			read -p "Input directory and suffix or q to quit: " dirname suffix
				if [[ "$dirname" = "q" ]]; then
					exit 0
				else	
					RecursiveRm $dirname $suffix
				fi
		done
	fi
else
	  	RecursiveRm $1 $2 																#Если скрипт вызван без флагов, то просто вызываем функцию 
fi
