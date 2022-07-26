# Отчет по лабораторной работе N 14 по курсу
# "Фундаментальная информатика"

Студент группы: M80-107Б, Павлов Иван Дмитриевич\
Контакты: pavlov.id.2003@mail.ru\
Работа выполнена: 25.09.2021\
Преподаватель: Найденов Иван Евгеньевич\

## 1. Тема

Операционная среда ОС UNIX

## 2. Цель работы

Изучение и освоение программного обеспечения ОС UNIX и приобритение навыков, необходимых для выполнения курсовых и лабораторных работ в среде UNIX.

## 3. Задание

№16.

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

1) Зададим количество тестов и максимальный размер матрицы, затем в цикле for, задав условие на счетчик t < cnt, где cnt - количество тестов, введем размер матриц и сами матрицы.
2) Если размер матрицы 0, то continue. Если размер матрицы 1, то выведем элемент с индексом [0][0]. 
3) Выведем главную диагональ матрицы, начиная с последнего элемента массива.
4) Следуя заданному условием порядку вывода выведем все остальные элементы. 

## 7. Сценарий выполнения работы

### Тесты:

| Ввод | Вывод | 
| ---- | ----- | 
| 2 4 <br> 4 <br> 4   5 11 15 <br> 10  3  6 12 <br> 14  9  2  7 <br> 16 13  8  1 <br> 1 <br> 1000  | 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 <br> 1000 |


## 8. Распечатка протокола

```
#include <stdio.h>

int main(void)
{
    int cnt, max;
    scanf("%d%d", &cnt, &max);
    int a[max][max];
    for (int t = 0; t < cnt; ++t) {
        int n;
        scanf("%d", &n);
        if (n == 0) {
            continue;
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                scanf("%d", &a[i][j]);
            }
        }
        if (n == 1) {
            printf("%d\n", a[0][0]);
            continue;
        }
        int p = n - 1;
        int i, j;
        while (p >= 0) {
            printf("%d ", a[p][p]);
            p--;
        }
        p = n - 1;
        while (p > 0) {
            i = 0;
            j = n - p;
            while (j <= n - 1) {
                printf("%d ", a[i][j]);
                ++i;
                ++j;
            }
            i = n - 1;
            j = p - 1;
            while (j >= 0) {
                printf("%d ", a[i][j]);
                --i;
                --j;
            }
            p--;
        }
        printf("\n");
    }
    return 0;
}
```

## 9. Дневник отладки

## 10. Замечания автора по существу работы

## 11. Выводы
В ходе лабораторной работы я научился работать с матрицами в си и приводить их к линейному виду. Думаю, данные навыки помогут мне справиться со следующей лабораторной, при этом не совершив те же ошибки в порядке считывания матриц.