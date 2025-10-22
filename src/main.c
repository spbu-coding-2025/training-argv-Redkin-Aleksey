#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define error_print(...) (fprintf(stderr, __VA_ARGS__))

long parse_arg(const char *arg, const char *prefix) {
    if (strncmp(arg, prefix, strlen(prefix)) != 0) {
        error_print("Ошибка: ожидался аргумент вида %s<число>\n", prefix);
        exit(EXIT_FAILURE);
    }

    const char *num_str = arg + strlen(prefix);
    if (*num_str == '\0') {
        error_print("Ошибка: не указано значение после %s\n", prefix);
        exit(EXIT_FAILURE);
    }

    char *end;
    errno = 0;
    long value = strtol(num_str, &end, 10);

    if (errno != 0 || *end != '\0') {
        error_print("Ошибка: некорректное число в аргументе %s\n", arg);
        exit(EXIT_FAILURE);
    }

    return value;
}


int main(int argc, char* argv[]) {
    if (argc == 1) {
        error_print("No flags found.\n");
        return 1;
    }
    if (argc == 2) {
        if (strncmp(argv[1], "--lower_bound=", 14) == 0) {
            error_print("Flag --upper_bound is missing.\n");
        } else {
            error_print("Flag --lower_bound is missing.\n");
        }
        return 1;
    }
    long lower_bound = 0, upper_bound = 0;

    for (int i = 1; i < argc; ++i) {
        if (strncmp(argv[i], "--lower_bound=", 14) == 0) {
            lower_bound = parse_arg(argv[i], "--lower_bound=");
        } else {
            upper_bound = parse_arg(argv[i], "--upper_bound=");
        }
    }
    if (lower_bound > upper_bound) {
        error_print("The lower bound is greater than the upper bound.");
        return 1;
    }
    for (long i = lower_bound; i <= upper_bound; ++i) {
        printf("%ld ", i);
    }
    printf("\n");
    return 0;
}
