# Отчет по лабораторной работе N 2 по курсу
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

Приобретение основных навыков работы в OC UNIX

## 4. Оборудование

*В формах: словесной, псевдокода, графической [блок схема, диаграмма, рисунок, таблица] или формальные спецификации с пред- и постусловиями.*

В данной лабораторной работе была цель изучить некоторые команды UNIX, для этого была взята идея создания нескольких вложенных директорий,в которых должны были содержатся файлы с наполненными ими данными.
Также  должны быть выполнены несколько сложных команд с конвейером,выполняющие определенные операции с содержимым файлов.

Поставленная мной задача в данной лабораторной работе заключалась в том, чтобы создать структуру директорий и с помощью BASH-скриптов провести над ней ряд действий в обучающих целях. Для примера я решил взять отбор на ЧМ-2022 по футболу: список участвующих команд и их набранные очки. Я создал директорию 'qualifycation', где хранятся списки футбольных команд и их рейтинг. Используя такие команды, как 'sort', 'head', 'grep', я буду выбирать из данной структуры списки команд, подходящих под определенные критерии. 


## 7. Сценарий выполнения работы 

*[план работы, первоначальный текст программы в черновике (можно на отдельном листе) и тесты либо соображения по тестированию]*

В своей работе я решил помочь UEFA с организацией футбольных мероприятий. Создадим директорию 'qualifycation', внутри которой будут храниться данные об отборочном этапе: группы, команды, рейтинг. В директории 'qualifycation' создадим 10 директроий: 'groupA', 'groupB', 'groupC', 'groupD', 'groupE', 'groupF', 'groupG', 'groupH', 'groupI', 'groupJ'. Внутрь каждой из этих директорий я поместил файл 'rating.txt', содержащий список команд группы в случайном порядке, а так же их очки. BASH-скрипты я использовал для отбора команд на чемпионат мира (вывести на экран топ-20 команд с наибольшим количеством очков, используя 'sort' и 'head'), а так же для создания группы слабейших команд (используя 'grep'). 


## 8. Распечатка протокола 

*Подклеить листинг окончательного варианта программы с тестовыми примерами, подписанный преподавателем.*

```
ggame@ggame:~/lab1$ mkdir qualification
ggame@ggame:~/lab1$ rmdir qualification
ggame@ggame:~/lab1$ mkdir qualifycation
ggame@ggame:~/lab1$ cd qualifycation
ggame@ggame:~/lab1/qualifycation$ mkdir groupA
ggame@ggame:~/lab1/qualifycation$ mkdir groupB
ggame@ggame:~/lab1/qualifycation$ mkdir groupC
ggame@ggame:~/lab1/qualifycation$ mkdir groupD
ggame@ggame:~/lab1/qualifycation$ mkdir groupE
ggame@ggame:~/lab1/qualifycation$ mkdir groupF
ggame@ggame:~/lab1/qualifycation$ mkdir groupG
ggame@ggame:~/lab1/qualifycation$ mkdir groupH
ggame@ggame:~/lab1/qualifycation$ mkdir groupI
ggame@ggame:~/lab1/qualifycation$ mkdir groupJ
ggame@ggame:~/lab1/qualifycation$ cat > ./groupA/rating
ggame@ggame:~/lab1/qualifycation$ cat > ./groupA/rating.txt
Azerbaijan 1   
Luxembourg 6
Portugal 10
Irish 1
Serbia 10
ggame@ggame:~/lab1/qualifycation$ cat > ./groupB/rating.txt
Georgia 1
Kosovo 3
Spain 7
Sweden 9
Greece 2
ggame@ggame:~/lab1/qualifycation$ cat > ./groupC/rating.txt
Italy 10
Northen Ireland 4
Switzerland 6
Lithuania 0
Bulgaria 2
ggame@ggame:~/lab1/qualifycation$ cat > ./groupD/rating.txt
Bosnia and Herzegovina 2
Finland 5
Ukraine 5
Kazakhstan 2
France 9
ggame@ggame:~/lab1/qualifycation$ cat > ./groupE/rating.txt
Wales 3
Estonia 0
Czech 7
Belgium 10
Belarus 3
ggame@ggame:~/lab1/qualifycation$ cat > ./groupF/rating.txt
Israel 10
Scotland 8
Moldova 1
Faroe Islands 1
Denmark 15
Austria 7
ggame@ggame:~/lab1/qualifycation$ cat > ./groupG/rating.txt
Netherlands 10
Norway 10
Gibraltar 0
Turkey 11
Montenegro 7
Latvian 4
ggame@ggame:~/lab1/qualifycation$ cat > ./groupH/rating.txt
Cyprus 4     
Russia 10
Malta 4        
Croatia 10
Slovenia 7
Slovakia 6
ggame@ggame:~/lab1/qualifycation$ cat > ./groupI/rating.txt
England 12
San-Marino 0
Albania 6
Andorra 3
Poland 7
Hungary 7
ggame@ggame:~/lab1/qualifycation$ cat > ./groupJ/rating.txt
Romania 6
Northern Macedonia 7
Germany 9
Liechtenstein 0
Armenia 10
Iceland 3
ggame@ggame:~/lab1$ cat > SelectingToQatar.sh
cat ./qualifycation/groupA/* ./qualifycation/groupB/* ./qualifycation/groupC/* ./qualifycation/groupD/* ./qualifycation/groupE/* ./qualifycation/groupF/* ./qualifycation/groupG/* ./qualifycation/groupH/* ./qualifycation/groupI/* ./qualifycation/groupJ/* > selected.txt
less selected.txt | sort -r -nk2 | head -n20
ggame@ggame:~/lab1$ bash SelectingToQatar.sh
Denmark 15
England 12
Turkey 11
Serbia 10
Russia 10
Portugal 10
Norway 10
Netherlands 10
Italy 10
Israel 10
Croatia 10
Belgium 10
Armenia 10
Sweden 9
Germany 9
France 9
Scotland 8
Spain 7
Slovenia 7
Poland 7
ggame@ggame:~/lab1$ cat > losegroup.sh
cat ./qualifycation/groupA/* ./qualifycation/groupB/* ./qualifycation/groupC/* ./qualifycation/groupD/* ./qualifycation/groupE/* ./qualifycation/groupF/* ./qualifycation/groupG/* ./qualifycation/groupH/* ./qualifycation/groupI/* ./qualifycation/groupJ/* > losegroup.txt
cat losegroup.txt | grep '0' -w
ggame@ggame:~/lab1$ bash losegroup.sh
Lithuania 0
Estonia 0
Gibraltar 0
San-Marino 0
Liechtenstein 0
```

## 9. Дневник отладки

*Должен содержать дату и время сеансов отладки и основные события (ошибки в сценарии и программе, нестандартные ситуации) и краткие комментарии к ним. В дневнике отладки приводятся сведения об использовании других ЭВМ, существенном участии преподавателя и других лиц в написании и отладке программы.*

+---+---------------+------------+-----------+---------------------------------------------------------------------------------------------------+-------------------------+------------------+
| № | Лаб. или дом. | Дата       | Время     | Событие                                                                                           | Действие по исправлению | Примечание       |
+===+===============+============+===========+===================================================================================================+=========================+=============+
|1  | Дом           | 05.09.2021 | 21:30     | При выполнении команды 'grep' терминал отобразил команды у которых 10 очков вместе с "нулевыми"   | добавил -w              |  Надо учить linux|
+-------------------+------------+-----------+---------------------------------------------------------------------------------------------------+----------------

## 10. Замечания автора по существу работы

Одна из самых важных частей лр. Опишите,  чем вам работа понравилась, чем не понравилась. Расскажите, как по вашему мнению вам пригодятся полученные знания. Что было интересно, а что не очень .
## 11. Выводы

Подведите итог:  чему вы научились (кроме того, что написано в целях ЛР)  потратив время на разработку решения, тестов, картинок и прочего.
В ходе лабораторной работы я познакомился с конструированием диаграмм Тьюринга. Мне понравилось, что возможен и такой более высокоуровневый способ написания кода на машине Тьюринга в четверках, однако, обычное представление кода, на мой взгляд, намного проще.

Благодаря этой лабораторной работе я научился использовать основные команды OC UNIX. Это поможет мне в дальнейшем при работе с более сложными проектами, посвещенными этой ОС, которая будет моей основной ОС. В частности, благодаря этим утилитам я смогу быстро находить и анализировать данные.