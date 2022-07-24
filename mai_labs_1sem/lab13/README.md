# Отчет по лабораторной работе N 13 по курсу
# "Фундаментальная информатика"

Студент группы: M80-107Б, Павлов Иван Дмитриевич\
Контакты: pavlov.id.2003@mail.ru\
Работа выполнена: 25.09.2021\
Преподаватель: Найденов Иван Евгеньевич\

## 1. Тема

Битовые множества в языке Си.

## 2. Цель работы

Составить программу на языке Си ,которая проверяет наличие/отсутствие среди входных слов слова, все согласные буквы которого звонкие.

## 3. Задание

№23.

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

По условию звонкие согласные - "b", "v", "g", "d', "z". 
1) Напишем функцию **set_symbol()**, создающую битовые множества - числа типа undigned long long, состоящие из цифр 0 и 1, причем 1 ставится в номер разряда числа, соответствующего номеру буквы в алфавите.
2) Так как на вход могут поступать и заглавные, и строчные буквы, для простоты будем приводить все заглавные буквы к строчному виду. Для этого напишем функцию **to_lowercase()**
3) Напишем функцию **is_alpha()**, которая проверяет, является ли символ разделителем.
4) Из двух массивов (в первом находятся звонкие согласные, во втором - все остальные согласные) составим 2 битсета; создадим пустой битсет.
5) Напишем функцию, которая проверяет слово согласно условию (возвращает 0 или 1).
6) Используя метод конечных автоматов и описанные выше функции, проверим поток ввода согласно условию.

## 7. Сценарий выполнения работы

**Тесты**
| Ввод | Вывод | 
| ---- | ----- | 
| alter ego| Yes |
| anathemus | No |
| EOF | No |
| \n EOF | Yes |

## 8. Распечатка протокола

```
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define set unsigned long long

set son_set = 0;
set not_set = 0;
set lu = 1;

set set_symbol(set s, char c)
{
    return s | (lu << ((set) c - (set) 'a'));
}

char to_lowercase(char c)
{
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 'a';
    } else {
        return c;
    }
}

bool is_alpha(char c)
{
    c = to_lowercase(c);
    if (c == ' ' || c == '\t' || c == '\n' || c == EOF || c == ',' || c == '\r') {
        return false;
    }
    return true;
}

int is_son(set n_set)
{
    set pr = 0;
    if ((n_set & not_set) == pr) {
        return 1;
    } else {
        return 0;
    }
}

int main(void)
{
    char son[] = {'b', 'v', 'g', 'd', 'z'};
    char notson[] = {'c', 'f', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'x', 'y', 'w'};
    for (int i = 0; i < 5; i++) {
        son_set = set_symbol(son_set, son[i]);
    }
    for (int i = 0; i < 16; i++) {
        not_set = set_symbol(not_set, notson[i]);
    }
    set n_set = 0;
    char c;
    bool result = false, flag = true, empt = true , iseof = false;
    int state = 0;
    while (flag) {
        c = getchar();
        c = to_lowercase(c);
        switch (state) {
            case 0:
                if (c == EOF) {
                    iseof = true;
                } else {
                    state = 1;
                }
                break;
            case 1:
                if (is_alpha(c)) {
                    state = 2;
                    n_set = set_symbol(n_set, c);
                } else {
                    state = 1;
                }
                break;
            case 2:
                empt = false;
                if (is_alpha(c)) {
                    n_set = set_symbol(n_set, c);
                } else {
                    result = result || is_son(n_set);
                    n_set = 0;
                    state = 1;
                }
                break;

        }
        if (c == EOF) {
            flag = false;
        }

    }
    if ((result || empt) && !(iseof)) {
        printf("Yes\n");
        return 0;
    }
    printf("No\n");
    return 0;
}
```

## 9. Дневник отладки

| № | Лаб. или дом. | Дата | Время | Событие | Действие по исправлению | Примечание |
| - | ------------- | ---- | ----- | ------- | ----------------------- | ---------- |
| 1 | Дом | 30.11.2021 | 18:27 | Ошибка на тесте 3 | Пустая строка должна давать Yes | Исправил |
| 2 | Лаб | 04.12.2021 | 09:25 | Ошибка на тесте 4 | Символ EOF должен давать NO | Исправил |
| 3 | Лаб | 04.11.2021 | 09:57 | Ошибка на тесте 10 | Ошибка чекера | Исправлено преподавателем |

## 10. Замечания автора по существу работы

## 11. Выводы

В ходе выполнения данной ЛР я познакомился с битовыми множествами в языке Си, научился их реализовывать и закрепил тему конечных автоматов.