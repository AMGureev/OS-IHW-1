# IHW-1 Operating-Systems
# Работу выполнил ступдент 2 курса БПИ227 Гуреев Александр
## `Вариант 26. Условие` : разработать программу, которая определяет в ASCII–строке количество различных идентификаторов, являющихся словами, состоящими из букв и цифр, начинающихся с буквы. Разделителями являются все другие символы. Для тестирования можно использовать программы, написанные на различных языках программирования.
### Задание выполнено на `9` баллов. В работе представлены `6` программ, в которых покрываются все условия для получения высокой оценки.

## Запуск программ

Сборка файла:
```
gcc file -o name
```
где `file` - один из файлов на языке `c`, `name` - имя файла сборки
Запуск файла:
```
./name input_file.txt output_file.txt
```

### Работа программы (без оценки)
Перед тем, как приступить к выполнению заданий на оценку, была написана программа `program.c`. В ней продемонтрирована логика поиска программой количества идентификаторов, являющихся словами, состоящими из букв и цифр, начинающихся с буквы.

#### Примеры тестов с одним *возможным* индикатором:

 *Слово* | *Результат* | *Объяснение* |
|----------|----------|----------|
| Hello    |     `True`    | Индикатор начианается с буквы и содержит буквы|
| Hello1   |     `True`    | Индикатор начианается с буквы и содержит буквы и цифры|
| 1Hello   |     `False`   | Индикатор начианается с цифры, что не удовлетворяет условию|
| He1llo   |     `True`    | Индикатор начианается с буквы и содержит буквы и цифры   |

### Работа на оценку [4](https://github.com/AMGureev/OS-IHW-1/tree/main/grade4)

#### Файлы:

- `grade4.c` - исполняемый файл.
- `input1.txt`, `input2.txt`, `input3.txt`, `input4.txt`, `input5.txt` - примеры входных файлов.
- `output1.txt`, `output2.txt`, `output3.txt`, `output4.txt`, `output5.txt` - примеры выходных файлов.

#### Схема решения:

- Первый процесс читает текстовые данные из заданного файла и через неименованный канал передает их второму процессу.
- Второй процесс осуществляет обработку данных в соответствии с условием и передает результат обработки через неименованный канал третьему процессу.
- Третий процесс осуществляет вывод данных в заданный файл.

#### Результаты работы:

 **№ Теста** | **Входные данные** | **Результат** |
|----------|----------|----------|
| 1   |     `Hello, I love you!`    | `4` |
| 2   |     `Maybe y0u can dr1ve 11y car?`    | `5` |
| 3   |     `111 + 111 = 200`   | `0` |
| 4   |     `h0W are 78ou?`    |  `2`  |
| 5   |     `1geg1 hello 1hello hello1 ghg11hfhd 111 dddd d11`    |  `5`  |

### Работа на оценку [5](https://github.com/AMGureev/OS-IHW-1/tree/main/grade5)

#### Файлы:

- `grade5.c` - исполняемый файл.
- `input1.txt`, `input2.txt`, `input3.txt`, `input4.txt`, `input5.txt` - примеры входных файлов.
- `output1.txt`, `output2.txt`, `output3.txt`, `output4.txt`, `output5.txt` - примеры выходных файлов.

#### Схема решения:

- Первый процесс читает текстовые данные из заданного файла и через именованный канал передает их второму процессу.
- Второй процесс осуществляет обработку данных в соответствии с условием и передает результат обработки через именованный канал третьему процессу.
- Третий процесс осуществляет вывод данных в заданный файл.

#### Результаты работы:

 **№ Теста** | **Входные данные** | **Результат** |
|----------|----------|----------|
| 1   |     `Hello, I love you!`    | `4` |
| 2   |     `Maybe y0u can dr1ve 11y car?`    | `5` |
| 3   |     `111 + 111 = 200`   | `0` |
| 4   |     `h0W are 78ou?`    |  `2`  |
| 5   |     `1geg1 hello 1hello hello1 ghg11hfhd 111 dddd d11`    |  `5`  |

### Работа на оценку [6](https://github.com/AMGureev/OS-IHW-1/tree/main/grade6)

#### Файлы:

- `grade6.c` - исполняемый файл.
- `input1.txt`, `input2.txt`, `input3.txt`, `input4.txt`, `input5.txt` - примеры входных файлов.
- `output1.txt`, `output2.txt`, `output3.txt`, `output4.txt`, `output5.txt` - примеры выходных файлов.

#### Схема решения:

- Первый процесс читает текстовые данные из заданного файла и через неименованный канал передает их второму процессу.
- Второй процесс осуществляет обработку данных в соответствии с условием и передает результат обработки через неименованный канал обратно первому процессу.
- Первый процесс осуществляет вывод данных в заданный файл.
Для синхронизации процессов используются `семафоры`.

#### Результаты работы:

 **№ Теста** | **Входные данные** | **Результат** |
|----------|----------|----------|
| 1   |     `Hello, I love you!`    | `4` |
| 2   |     `Maybe y0u can dr1ve 11y car?`    | `5` |
| 3   |     `111 + 111 = 200`   | `0` |
| 4   |     `h0W are 78ou?`    |  `2`  |
| 5   |     `1geg1 hello 1hello hello1 ghg11hfhd 111 dddd d11`    |  `5`  |

### Работа на оценку [7](https://github.com/AMGureev/OS-IHW-1/tree/main/grade7)

#### Файлы:

- `grade7.c` - исполняемый файл.
- `input1.txt`, `input2.txt`, `input3.txt`, `input4.txt`, `input5.txt` - примеры входных файлов.
- `output1.txt`, `output2.txt`, `output3.txt`, `output4.txt`, `output5.txt` - примеры выходных файлов.

#### Схема решения:

- Первый процесс читает текстовые данные из заданного файла и через именованный канал передает их второму процессу.
- Второй процесс осуществляет обработку данных в соответствии с условием и передает результат обработки через именованный канал обратно первому процессу.
- Первый процесс осуществляет вывод данных в заданный файл.
Для синхронизации процессов используются `семафоры`.

#### Результаты работы:

 **№ Теста** | **Входные данные** | **Результат** |
|----------|----------|----------|
| 1   |     `Hello, I love you!`    | `4` |
| 2   |     `Maybe y0u can dr1ve 11y car?`    | `5` |
| 3   |     `111 + 111 = 200`   | `0` |
| 4   |     `h0W are 78ou?`    |  `2`  |
| 5   |     `1geg1 hello 1hello hello1 ghg11hfhd 111 dddd d11`    |  `5`  |

## 

### Работа на оценку [8](https://github.com/AMGureev/OS-IHW-1/tree/main/grade8)

#### Файлы:

- `grade8.c` - исполняемый файл для подсчета индикаторов.
- `second_procces.c` - исполняемый файл для чтения из файла и записи результата в файла.
- `input1.txt`, `input2.txt`, `input3.txt`, `input4.txt`, `input5.txt` - примеры входных файлов.
- `output1.txt`, `output2.txt`, `output3.txt`, `output4.txt`, `output5.txt` - примеры выходных файлов.

#### Схема решения:

- Первый процесс читает текстовые данные из заданного файла и через именованный канал передает их второму процессу
- Второй процесс осуществляет обработку данных в соответствии с условием и передает результат обработки через именованный канал обратно первому процессу
- Первый процесс осуществляет вывод данных в заданный файл
Для синхронизации процессов используются `семафоры`. Процессы не являются родственными.

#### Результаты работы:

 **№ Теста** | **Входные данные** | **Результат** |
|----------|----------|----------|
| 1   |     `Hello, I love you!`    | `4` |
| 2   |     `Maybe y0u can dr1ve 11y car?`    | `5` |
| 3   |     `111 + 111 = 200`   | `0` |
| 4   |     `h0W are 78ou?`    |  `2`  |
| 5   |     `1geg1 hello 1hello hello1 ghg11hfhd 111 dddd d11`    |  `5`  |

### Работа на оценку [9](https://github.com/AMGureev/OS-IHW-1/tree/main/grade9)

#### Файлы:

- `headl.c` - исполняемый файл для подсчета индикаторов.
- `readW.c` - исполняемый файл для чтения из файла и записи результата в файла.
- `input1.txt`, `input2.txt`, `input3.txt`, `input4.txt`, `input5.txt` - примеры входных файлов.
- `output1.txt`, `output2.txt`, `output3.txt`, `output4.txt`, `output5.txt` - примеры выходных файлов.

#### Схема решения:

- Первый процесс считывает содержимое файла частично (первые 16 байт), передает через именованный канал второму процессору.
- Второй процесс осуществляет обработку данных в соответствии с условием и передает результат обработки через именованный канал обратно первому процессу.
- Первый процесс записывает результат в файл (записывает 16 байт), после чего этот процесс снова считывает 16 байт из входного файла, передает их по именовонному каналу второму процессу. Так продолжается по циклу, пока во входном файле есть непрочитанные символы.
Для синхронизации процессов используются `семафоры`. Процессы не являются родственными.

#### Результаты работы:

 **№ Теста** | **Входные данные** | **Результат** |
|----------|----------|----------|
| 1   |     `Hello, I love you!`    | `4` |
| 2   |     `Maybe y0u can dr1ve 11y car?`    | `5` |
| 3   |     `111 + 111 = 200`   | `0` |
| 4   |     `h0W are 78ou?`    |  `2`  |
| 5   |     `1geg1 hello 1hello hello1 ghg11hfhd 111 dddd d11`    |  `5`  |

