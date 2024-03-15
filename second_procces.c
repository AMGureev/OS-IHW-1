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

const int mas_size = 10000;
int main(int argc, char *argv[]) {
    char str_buf[mas_size];
    char answer[10];

    int first_channel, second_channel, result;
    int size;

    mknod(name_first, S_IFIFO | 0666, 0);
    mknod(name_second, S_IFIFO | 0666, 0);

    second_channel = 0;

    // Второй процесс
    if((first_channel = open(name_first, O_RDONLY)) < 0)
    {
        printf("cant open FIFO for reading\n");
        exit(-1);
    }
    size = read(first_channel, str_buf, mas_size);
    if (size < 0) {
        printf("cant read from FIFO\n");
    }
    int32_t number = function(str_buf);
    if (close(first_channel) < 0) {
        printf("Cant close the FIFO\n");
        exit(-1);
    }
    if ((second_channel = open(name_second, O_WRONLY)) < 0) {
        printf("cant open for reading 2_FIFO\n");
        exit(-1);
    }
    recording_response(number, answer);
    size = write(second_channel, answer, 10);
    printf("%s \n", answer);
    if (size != 10) {
        printf("Cant write all in 2_FIFO\n");
        exit(-1);
    }
    if (close(second_channel)) {
        printf("cant close 2_FIFO\n");
        exit(-1);
    }
    exit(0);

    return 0;
}