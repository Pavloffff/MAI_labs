# Отчет по лабораторной работе N 10 по курсу
# "Фундаментальная информатика"

Студент группы: M80-107Б, Павлов Иван Дмитриевич\
Контакты: pavlov.id.2003@mail.ru\
Работа выполнена: 25.09.2021\
Преподаватель: Найденов Иван Евгеньевич\

## 1. Тема

Отладчик системы программирования ОС UNIX

## 2. Цель работы

Научиться работать с отладчиком  в некоторой программе на изучаемом языке программирования.

## 3. Задание

Используя отладчик gdb найти и исправить финальную ошибку, допущенную в процессе написания кода для ЛР №9. 

## 4. Оборудование

Процессор: AMD Ryzen 5 4600H with Radeon Graphics\
ОП: 7851 Мб\
НМД: 256 Гб\
Монитор: 1920x1080\

## 5. Программное обеспечение

Операционная система семейства: **linux (ubuntu)**, версия **20.04.3 LTS**\
Интерпретатор команд: **bash**, версия **5.0.17(1)-release**.\
Система программирования: *gcc**, версия **17**\
Редактор текстов: **emacs**, версия **25.2.2**\
Утилиты операционной системы: **--**\
Прикладные системы и программы: **--**\
Местонахождение и имена файлов программ и данных на домашнем компьютере: **--**\

## 6. Идея, метод, алгоритм решения задачи

Пусть в данном коде допущена ошибка, приводящая к неправильному ответу при входных значениях 0 0 0, при этом вместо корректного Yes 7 -6 9 45 программа выдает Yes 5 -7 11 42. К этому моменту уже исправлены все ошибки, связанные с функциями, поэтому предположим, что ошибка скрывается где-то внутри цикла и связана с синтаксисом написания формул, заданных в условии. Исправлять ее будем следующим образом:
1) Вручную вычислим значения i, j, l, k для каждой иттерации, пользуясь данными формулами.
2) Используя отладчик, итеративно прогоним код, анализируя, с чего началось расхождение значений.
3) Выявим и исправим найденную ошибку.

## 7. Сценарий выполнения работы

### Процесс поиска ошибки:

1) Рассмотрим список команд с помощью (gdb) help.
2) Запустим с помощью run.
3) Зададим точки останова с помощью break.
4) Запустим с помощью run и выведем значения переменных с помощью print.
5) Сравним выведенные значения переменных со значениями, полученными вручную: 

| k | i (вручную) | j (вручную) | l (вручную) | i (отладчик)  | j (отладчик) | l (отладчик) |
| - | ------------- | ---- | ----- | ------- | ----------------------- | ---------- |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0 | -5 | 0 | 0 | -5 | 0 | 0 |
| 1 | -4 | 0 | 0 | -4 | -1 | 0 |
| 2 | -5 | 0 | 10 | -5 | -1 | 10 |

Видно, что значения переменной j не совпадают уже на первой итерации, а так как эта переменная входит в формулы переменных i и l, то в дальнейшем это и приводит к неправильному ответу. Рассмотрим подробнее строку кода где задается j:
j2 = floor(-(j+k) / 5.0f) + abs(mod(i * l , 8));
Проанализировав синтаксис языка, я понял, что выражение -(j+k) не является корректным на С. Заменим строку на j2 = (-1) * floor((j + k) / 5.0) + abs(mod(i * l, 8)); и заново запустим в чекере.
Таким образом мы нашли и исправили ошибку.

## 8. Распечатка протокола
*Подклеить листинг окончательного варианта программы с тестовыми примерами, подписанный преподавателем.*

Сюда вставляем листинг программы, если есть + примеры запуска. Для второй лабы в качестве листинга нужен протокол из терминала в следующем виде:

```
ggame@ggame:~/lab7$ gcc -g 7.c -lm -o main
ggame@ggame:~/lab7$ gdb ./main
GNU gdb (Ubuntu 9.2-0ubuntu1~20.04) 9.2
Copyright (C) 2020 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from ./main...
(gdb) help
List of classes of commands:

aliases -- Aliases of other commands.
breakpoints -- Making program stop at certain points.
data -- Examining data.
files -- Specifying and examining files.
internals -- Maintenance commands.
obscure -- Obscure features.
running -- Running the program.
stack -- Examining the stack.
status -- Status inquiries.
support -- Support facilities.
tracepoints -- Tracing of program execution without stopping the program.
user-defined -- User-defined commands.

Type "help" followed by a class name for a list of commands in that class.
Type "help all" for the list of all commands.
Type "help" followed by command name for full documentation.
Type "apropos word" to search for commands related to "word".
Type "apropos -v word" for full documentation of commands related to "word".
Command name abbreviations are allowed if unambiguous.
(gdb) run
Starting program: /home/ggame/lab7/main 
0 0 0
Yes
5 -7 11 42
[Inferior 1 (process 18857) exited normally]
(gdb) b 39
Breakpoint 1 at 0x5555555553bf: file 7.c, line 39.
(gdb) b 33
Breakpoint 2 at 0x5555555552c3: file 7.c, line 33.
(gdb) run
Starting program: /home/ggame/lab7/main 
0 0 0

Breakpoint 2, main () at 7.c:33
33	    for (k = 0; k < 50 && check(i, j) == false; k++) {
(gdb) next
34	        i2 = abs(k - 15) - min(floor(i / 3.0f) , mod(j + l , 10)) - 20;
(gdb) print i2
$1 = 21845
(gdb) print i
$2 = 0
(gdb) next
35	        j2 = floor(-(j+k) / 5.0f) + abs(mod(i * l , 8));
(gdb) next
36	        l2 = max(mod(i + j , 15) , mod(i + k , 14));
(gdb) next
37	        i = i2;
(gdb) next
38	        j = j2;
(gdb) next

Breakpoint 1, main () at 7.c:39
39	        l = l2;
(gdb) print i
$3 = -5
(gdb) print j
$4 = 0
(gdb) print l
$5 = 0
(gdb) next
33	    for (k = 0; k < 50 && check(i, j) == false; k++) {
(gdb) next
34	        i2 = abs(k - 15) - min(floor(i / 3.0f) , mod(j + l , 10)) - 20;
(gdb) next
35	        j2 = floor(-(j+k) / 5.0f) + abs(mod(i * l , 8));
(gdb) next
36	        l2 = max(mod(i + j , 15) , mod(i + k , 14));
(gdb) next
37	        i = i2;
(gdb) next
38	        j = j2;
(gdb) next

Breakpoint 1, main () at 7.c:39
39	        l = l2;
(gdb) print i
$6 = -4
(gdb) print j
$7 = -1
(gdb) print l
$8 = 0
(gdb) print k
$9 = 1
(gdb) next
33	    for (k = 0; k < 50 && check(i, j) == false; k++) {
(gdb) next
34	        i2 = abs(k - 15) - min(floor(i / 3.0f) , mod(j + l , 10)) - 20;
(gdb) next
35	        j2 = floor(-(j+k) / 5.0f) + abs(mod(i * l , 8));
(gdb) next
36	        l2 = max(mod(i + j , 15) , mod(i + k , 14));
(gdb) next
37	        i = i2;
(gdb) next
38	        j = j2;
(gdb) next

Breakpoint 1, main () at 7.c:39
39	        l = l2;
(gdb) print i
$10 = -5
(gdb) print j
$11 = -1
(gdb) print l
$12 = 10
(gdb) print k
$13 = 2
ggame@ggame:~/lab7$ gcc -g 7.c -lm -o main
ggame@ggame:~/lab7$ gdb ./main
GNU gdb (Ubuntu 9.2-0ubuntu1~20.04) 9.2
Copyright (C) 2020 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from ./main...
(gdb) run
Starting program: /home/ggame/lab7/main 
0 0 0
Yes
7 -6 9 45
[Inferior 1 (process 21052) exited normally]

```

## 9. Дневник отладки
## 10. Замечания автора по существу работы
## 11. Выводы

В ходе лабораторной работе я научился пользовать отладчиком gdb, и находить ошибки в своём коде, что в дальнейшем поможет быстрее находить и исправлять какие-либо недочеты в своей программе