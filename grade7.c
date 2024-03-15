#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#include <ctype.h>
#if defined __USE_MISC || defined __USE_BSD || defined __USE_XOPEN_EXTENDED
extern int mknod (const char *__path, __mode_t __mode, __dev_t __dev)
__THROW __nonnull ((1));
#endif

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

const char* name_first = "first_pipe.fifo";
const char* name_second = "second_pipe.fifo";

const int mas_size = 5000;
int main(int argc, char *argv[]) {
    char str_buf[mas_size];
    char answer[10];
    if(argc != 3){
        printf("execute programm with three param: './prog.out input.txt output.txt'\n");
        return 0;
    }

    int first_channel, second_channel, result;
    int size;

    mknod(name_first, S_IFIFO | 0666, 0);
    mknod(name_second, S_IFIFO | 0666, 0);

    second_channel = 0;

    result = fork(); // создаем первый и второй процессы
    if (result < 0) {
        printf("Cant fork child\n");
        exit(-1);
    } else if (result > 0) { // Первый процесс
        int file_to_read = 0;

        if ((file_to_read = open(argv[1], O_RDONLY, 0666)) < 0) {
            printf("Cant open the file\n");
            exit(-1);
        }
        size = read(file_to_read, str_buf, mas_size);
        if (close(file_to_read) < 0) {
            printf("Cant close the file\n");
            exit(-1);
        }

        if ((first_channel = open(name_first, O_WRONLY)) < 0) {
            printf("Cant open FIFO for writing\n");
            exit(-1);
        }

        size = write(first_channel, str_buf, mas_size);
        if (size != mas_size) {
            printf("Cant write all string to FIFO\n");
            exit(-1);
        }

        if (close(first_channel) < 0) {
            printf("Cant close FIFO");
            exit(-1);
        }
    } else {
        // Второй процесс
        if((first_channel = open(name_first, O_RDONLY)) < 0)
        {
            printf("Child: cant open FIFO for reading\n");
            exit(-1);
        }
        size = read(first_channel, str_buf, mas_size);
        if (size < 0) {
            printf("child: cant read from FIFO\n");
        }
        int32_t number = function(str_buf);
        if (close(first_channel) < 0) {
            printf("child: Cant close the FIFO\n");
            exit(-1);
        }
        if ((second_channel = open(name_second, O_WRONLY)) < 0) {
            printf("child: cant open for reading 2_FIFO\n");
            exit(-1);
        }
        recording_response(number, answer);
        size = write(second_channel, answer, 10);
        printf("%s \n", answer);
        if (size != 10) {
            printf("child: Cant write all in 2_FIFO\n");
            exit(-1);
        }
        if (close(second_channel)) {
            printf("child: cant close 2_FIFO\n");
            exit(-1);
        }
        exit(0);
    }
    // Первый процесс
    if ((second_channel = open(name_second, O_RDONLY)) < 0) {
        printf("child/child: cant open 2_FIFO\n");
        exit(-1);
    }

    size = read(second_channel, str_buf, 10);
    if (size < 0) {
        printf("child/child: cant read from 2_FIFO\n");
        exit(-1);
    }

    if (close(second_channel) < 0) {
        printf("child/child: cant close 2_FiFO\n");
        exit(-1);
    }

    int file_to_write = 0;

    if ((file_to_write = open(argv[2], O_WRONLY | O_CREAT, 0666)) < 0) {
        printf("child/child: cant open out file to write\n");
        exit(-1);
    }

    size = write(file_to_write, str_buf, 10);
    if (size != 10) {
        printf("child/child: cant write to out file\n");
        exit(-1);
    }
    if (close(file_to_write) < 0) {
        printf("child/child: cant close out file\n");
        exit(-1);
    }
    return 0;
}