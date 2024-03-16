#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

const int size = 128;

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
    if (number == 0) {
        answer[0] = 0 + '0';
        index = 1;
        while (index < 10) {
            answer[index++] = ' ';
        }
        answer[9] = '\0';
        return;
    }
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

int main(int argc, char** argv){
    char reader2Handler[] = "first_pipe.fifo";
    char handler2Reader[] = "second_pipe.fifo";

    char str_buf[size + 1];
    char answer[10];
    int fd1, fd2;

    if((fd1 = open(reader2Handler, O_RDONLY)) < 0 || (fd2 = open(handler2Reader, O_WRONLY)) < 0){
        printf("Can't open FIFO\n");
        exit(-1);
    }

    ssize_t readFromFifo;
    do {
        readFromFifo = read(fd1, str_buf, size);
        if(readFromFifo < 0){
            printf("Can't read string from FIFO\n");
            exit(-1);
        }
        str_buf[readFromFifo] = '\0';
        int32_t number = function(str_buf);
        recording_response(number, answer);
        ssize_t writeSize = write(fd2, answer, 10);
        if(writeSize != 10){
            printf("Can't write all string to FIFO\n");
            exit(-1);
        }
    } while (readFromFifo == size);

    if(close(fd1) < 0) {
        printf("Can't close FIFO\n");
        exit(-1);
    }

    if(close(fd2) < 0) {
        printf("Can't close FIFO\n");
        exit(-1);
    }
    return 0;
}
