реализация утилиты cat  и grep

## Chapter I

 - Программы должны быть разработаны на языке С стандарта C11 с использованием компилятора gcc
 - Код программ cat и grep должен находиться в ветке develop в папках src/cat/ и src/grep/ соответственно.
 - Не используй устаревшие и выведенные из употребления конструкции языка и библиотечные функции. Обращай внимание на пометки legacy и obsolete в официальной документации по языку и используемым библиотекам. Ориентируйся на стандарт POSIX.1-2017.
 - При написании кода необходимо придерживаться Google Style.
 - Программы должны представлять собой исполняемый файл с аргументами командной строки
 - Сборка программ должна быть настроена с помощью Makefile с соответствующими целями: s21_cat, s21_grep.
 - Если используешь сторонние библиотеки, в Makefile должны быть заложены сценарии сборки, предусматривающие их подключение/загрузку.
 - Необходимо покрытие интеграционными тестами для всех вариантов флагов и входных значений, на базе сравнения с поведением реальных утилит Bash.
 - Программа должна быть разработана в соответствии с принципами структурного программирования.
 - Необходимо исключить дублирование кода, переиспользовать общие модули между утилитами. Общие модули можно вынести в отдельную папку src/common.
 - Можно использовать стандартные и нестандартные библиотеки языка С, а можно собственноручно разработанные библиотеки из других проектов.
 - Формулировка сообщения при возникновении ошибочной ситуации не имеет значения.
 - Ввод через stdin обрабатывать не обязательно.


## Part 1. Работа с утилитой cat

  Тебе необходимо разработать утилиту cat:

- Она должна поддерживать все флаги (включая GNU версии), указанные выше

- Исходные, заголовочные и сборочный файлы должны располагаться в директории src/cat/
  
- Итоговый исполняемый файл должен располагаться в директории src/cat/ и называться s21_cat

## Part 2. Работа с утилитой grep

 Тебе необходимо разработать утилиту grep:

- Поддержка следующих флагов: -e, -i, -v, -c, -l, -n
- Для регулярных выражений можно использовать только библиотеки pcre или regex
- Исходные, заголовочные и make файлы должны располагаться в директории src/grep/
- Итоговый исполняемый файл должен располагаться в директории src/grep/ и называться s21_grep

## Part 3. Дополнительно. Реализация некоторых флагов утилиты grep

  А это необязательное задание на дополнительные баллы: разработай утилиту grep:

- Поддержка всех флагов, включая: -h, -s, -f, -o
- Для регулярных выражений можно использовать только библиотеки pcre или regex
- Исходные, заголовочные и make файлы должны располагаться в директории src/grep/
- Итоговый исполняемый файл должен располагаться в директории src/grep/ и называться s21_grep

 ## Part 4. Дополнительно. Реализация комбинаций флагов утилиты grep

 А это необязательное задание на дополнительные баллы: разработай утилиту grep:

- Поддержка всех флагов, включая их парные комбинации (например, -iv, -in)
- Для регулярных выражений можно использовать только библиотеки pcre или regex
- Исходные, заголовочные и make файлы должны располагаться в директории src/grep/
- Итоговый исполняемый файл должен располагаться в директории src/grep/ и называться s21_grep
