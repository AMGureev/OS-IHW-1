#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LEN 1000

bool is_valid_identifier(char *str, int start, int end) {
    if (!isalpha(str[start])) // Проверяем, начинается ли идентификатор с буквы
        return false;

    for (int i = start; i <= end; i++) {
        if (!(isalnum(str[i]))) // Проверяем, состоит ли идентификатор из букв и цифр
            return false;
    }

    return true;
}

int main() {
    char input[MAX_LEN];
    printf("Введите строку: ");
    fgets(input, sizeof(input), stdin);

    int count = 0;
    int len = strlen(input);
    bool in_word = false;
    int word_start = 0;

    for (int i = 0; i < len; i++) {
        if (isalnum(input[i])) { // Если символ - буква или цифра
            if (!in_word) { // Если начинается новый идентификатор
                in_word = true;
                word_start = i;
            }
        } else { // Если символ - разделитель
            if (in_word) { // Если завершается идентификатор
                if (is_valid_identifier(input, word_start, i - 1)) // Проверяем, является ли он валидным
                    count++;
                in_word = false;
            }
        }
    }

    // Проверка последнего идентификатора, если строка заканчивается на него
    if (in_word && is_valid_identifier(input, word_start, len - 1))
        count++;

    printf("Количество идентификаторов: %d\n", count);

    return 0;
}