# Отчет по лабораторной работе N 12 по курсу
# "Фундаментальная информатика"

Студент группы: M80-107Б, Павлов Иван Дмитриевич\
Контакты: pavlov.id.2003@mail.ru\
Работа выполнена: 25.09.2021\
Преподаватель: Найденов Иван Евгеньевич\

## 1. Тема

Техника работы с целыми числами. Системы счисления. 

## 2. Цель работы

Составить программу на языке Си в целом типе данных, которая для любых допустимых и корректно записанных чисел этого типа в десятичном изображении, поступающих на стандартный ввод программы, выполняет указанное вариантом действие над их значениями.

## 3. Задание

№28 (Получить двоично-кодированное десятичное представление числа. При решении задачи необходимо использовать методы работы с находящимися в памяти целыми числами.)

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

Чтобы получить двоично-кодированное представление десятичного числа, необходимо выделить на каждую цифру по 4 бита, т.к 3 < log(2)10 < 4. Код каждой цифры будет лежать в диапазоне от 0000 до 1010. Далее надо разбить вводимое число типа int на цифры, при этом надо брать цифры начиная со старшего бита, чтобы не получился реверс числа. Для этого нам понадобятся функции: 
1) Определение длины числа. Циклически делим число не равное 0 на 10, каждой итерацией увеличивая счетчик. Если число равно 0, то функция выдаст 0.
2) Возведение 10 в степень, равную длине числа, для выделения цифр числа со старшего разряда.
3) Функции abs и sign для разделения знака и значения числа.

В функции int main циклически уменьшаем  переменную y, отвечающую за длину числа, при этом деля абсолютную величину х на у (перед этим выведем знак) и вычисляя mod(x/y , 10), выделяем цифру, и с помощью 10 if-ов выводим для каждой из цифр двоичный код. 

## 7. Сценарий выполнения работы

### Тесты

| Ввод | Вывод | 
| ---- | ----- | 
| 1234567 <br>-192837<br>+9<br>100<br>1111<br>268953<br>123123 | 0001001000110100010101100111<br>-000110010010100000110111<br>1001<br>000100000000<br>0001000100010001<br>001001101000100101010011<br>000100100011000100100011 |

## 8. Распечатка протокола

```
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

long long absc(long long x)
{
    return (x < 0) ? (-1) * x : x;
}

long long powd(long long x)
{
    long long res = 1;
    for (long long i = 0; i < x; i++) {
        res *= 10;
    }
    return res;
}

long long len(long long x)
{
    if (x == 0) {
        return 1;
    } else {
        int res = 0;
        while (x != 0) {
            x /= 10;
            res++;
        }
        return res;
    }
}

long long sign(long long a)
{
    if (a == 0) {
        return 0;
    } else {
        return (a > 0) ? 1 : -1;
    }
}

int main(void)
{
    long long x, y;
    while ((scanf("%lld", &x)) != EOF) {
        if (sign(x) == -1) {
            printf("-");
        }
        x = absc(x);
        y = len(x) - 1;
        while (y >= 0) {
            if ((x / powd(y)) % 10 == 0) {
                printf("%d%d%d%d", 0, 0, 0, 0);
            } else if ((x / powd(y)) % 10 == 1) {
                printf("%d%d%d%d", 0, 0, 0, 1);
            } else if ((x / powd(y)) % 10 == 2) {
                printf("%d%d%d%d", 0, 0, 1, 0);
            } else if ((x / powd(y)) % 10 == 3) {
                printf("%d%d%d%d", 0, 0, 1, 1);
            } else if ((x / powd(y)) % 10 == 4) {
                printf("%d%d%d%d", 0, 1, 0, 0);
            } else if ((x / powd(y)) % 10 == 5) {
                printf("%d%d%d%d", 0, 1, 0, 1);
            } else if ((x / powd(y)) % 10 == 6) {
                printf("%d%d%d%d", 0, 1, 1, 0);
            } else if ((x / powd(y)) % 10 == 7) {
                printf("%d%d%d%d", 0, 1, 1, 1);
            } else if ((x / powd(y)) % 10 == 8) {
                printf("%d%d%d%d", 1, 0, 0, 0);
            } else if ((x / powd(y)) % 10 == 9) {
                printf("%d%d%d%d", 1, 0, 0, 1);
            }
            y -= 1;
        }
        printf("\n");
    }
    return 0;
}
```

## 9. Дневник отладки

*Должен содержать дату и время сеансов отладки и основные события (ошибки в сценарии и программе, нестандартные ситуации) и краткие комментарии к ним. В дневнике отладки приводятся сведения об использовании других ЭВМ, существенном участии преподавателя и других лиц в написании и отладке программы.*

| № | Лаб. или дом. | Дата | Время | Событие | Действие по исправлению | Примечание |
| - | ------------- | ---- | ----- | ------- | ----------------------- | ---------- |
| 1 | Дом | 05.11.2021 | 21:30 | Ошибка на тесте 1 | произошел реверс числа, переписал код | получен правильный ответ |

## 10. Замечания автора по существу работы

## 11. Выводы

Благодаря данной лабораторной работе я научился вводить неограниченное количество чисел на входе, над которыми будут выполняться условия, данные в задании. Лабораторная работа учит разбираться в коде и дает хорошую практику. 