#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdbool.h>

bool is_valid_identifier(char *str, int start, int end) {
    if (!isalpha(str[start])) // Проверяем, начинается ли идентификатор с буквы
        return false;

    for (int i = start; i <= end; i++) {
        if (!(isalnum(str[i]))) // Проверяем, состоит ли идентификатор из букв и цифр
            return false;
    }

    return true;
}

int32_t function(char string[]) {
    int count = 0;
    int len = strlen(string);
    bool in_word = false;
    int word_start = 0;

    for (int i = 0; i < len; i++) {
        if (isalnum(string[i])) { // Если символ - буква или цифра
            if (!in_word) { // Если начинается новый идентификатор
                in_word = true;
                word_start = i;
            }
        } else { // Если символ - разделитель
            if (in_word) { // Если завершается идентификатор
                if (is_valid_identifier(string, word_start, i - 1)) // Проверяем, является ли он валидным
                    count++;
                in_word = false;
            }
        }
    }

    // Проверка последнего идентификатора, если строка заканчивается на него
    if (in_word && is_valid_identifier(string, word_start, len - 1))
        count++;
    return count;
}

void recording_response(int32_t number, char *answer) {
    int index = 0;
    while (number != 0) {
        int digit = number % 10;
        answer[index++] = digit + '0';
        number /= 10;
    }
    while (index < 10) {
        answer[index++] = ' ';
    }
    answer[9] = '\0';
}

const int mas_size = 5000;
int main(int argc, char *argv[]) {
    char str_buf[mas_size];
    char answer[10];
    if(argc != 3){
        printf("execute program with three param: './prog.out input.txt output.txt'\n");
        return 0;
    }

    int second_channel[2], first_channel[2], result;
    int size;

    if(pipe(first_channel) < 0) { // Создаем первый канал для передачи во второй процесс
        printf("Cant open pipe\n");
        exit(-1);
    }
    if(pipe(second_channel) < 0) { // Создаем второй канал для передачи в третий процесс
        printf("Cant open pipe\n");
        exit(-1);
    }

    result = fork(); // создаем первый и второй процессы
    if(result < 0) {
        printf("Cant fork child\n");
        exit(-1);
    } else if (result > 0) { // Первый процесс
        if(close(first_channel[0]) < 0){
            printf("parent: Cant close reading side of pipe\n");
            exit(-1);
        }

        int file_to_read = 0;
        if((file_to_read = open(argv[1], O_RDONLY , 0666)) < 0) {
            printf("Cant open file\n");
            exit(-1);
        }
        size = read(file_to_read, str_buf, mas_size); // считываем из файла
        if(close(file_to_read) < 0) {
            printf("Cant close file\n");
        }
        size = write(first_channel[1], str_buf, mas_size); // записываем в первый канал
        if(size != mas_size){
            printf("Cant write all string to pipe\n");
            exit(-1);
        }
        if(close(first_channel[1]) < 0) {
            printf("parent: Cant close writing side of pipe\n");
            exit(-1);
        }
    } else {  // второй процесс
        int result1 = fork(); // создаем 3-ий процесс из второго
        if(result1 < 0) {
            printf("Cant fork child\n");
            exit(-1);
        } else if(result1 > 0){ // второй процесс
            if(close(first_channel[1]) < 0){
                printf("child: Cant close writing side of pipe\n");
                exit(-1);
            }
            size = read(first_channel[0], str_buf, mas_size); // считываем из первого канала
            if(size < 0){
                printf("Cant read string from pipe\n");
                exit(-1);
            }
            int32_t number = function(str_buf); // находим кол-во 'индикаторов'
            if(close(first_channel[0]) < 0){
                printf("child: Cant close reading side of pipe\n");
                exit(-1);
            }
            recording_response(number, answer); // записываем ответ
            size = write(second_channel[1], answer, 10); // записываем во второй канал

            if(size != 10){
                printf("Cant write all string to pipe\n (size = %d)",size);
                exit(-1);
            }
            if(close(second_channel[1]) < 0) {
                printf("parent: Cant close writing side of pipe\n");
                exit(-1);
            }
        } else{ // 3-ий процесс
            if(close(second_channel[1]) < 0){
                printf("child: Cant close writing side of pipe\n");
                exit(-1);
            }

            size = read(second_channel[0], str_buf, 10);// считываем из 2-го канала
            if(size < 0){
                printf("Cant read string from pipe\n");
                exit(-1);
            }
            if(close(second_channel[0]) < 0){
                printf("child: Cant close reading side of pipe\n");
                exit(-1);
            }
            int file_to_write = 0;

            if((file_to_write = open(argv[2], O_WRONLY | O_CREAT, 0666)) < 0) {
                printf("Cant open file 1\n");
                exit(-1);
            }
            printf("%s \n", str_buf); // вывод результата в консоль
            size = write(file_to_write, str_buf, 10); // записываем в файл
            if(size != 10) {
                printf("Cant write all string\n");
                exit(-1);
            }
            if(close(file_to_write) < 0) {
                printf("Cant close file\n");
            }
        }
    }
    return 0;
}