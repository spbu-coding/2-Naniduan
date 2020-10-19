#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

extern void sort(long long *unsorted_array, long long *result_array, int size_of_array);

int enter_args(int *from, int *to, bool *there_is_from, bool *there_is_to, int argc, char **argv){
    const char *strfrom = "--from=", *strto = "--to=";
    if (argc < 2) return -1; //введено 0 параметров
    if (argc > 3) return -2; //введено 3 и более параметров
    for (int i = 1; i < argc; i++){
        char *current_parameter = argv[i], *end_of_current_parameter = current_parameter + strlen(current_parameter);
        if (strncmp(current_parameter, strfrom, strlen(strfrom)) == 0){
            if (*there_is_from) return -3; //from введён более 1-ого раза
            *there_is_from = 1;
            *from = strtol(current_parameter + strlen(strfrom), &end_of_current_parameter, 10);
        }
        if (strncmp(current_parameter, strto, strlen(strto)) == 0) {
            if (*there_is_to) return -3; //to введён более 1-ого раза
            *there_is_to = 1;
            *to = strtol(current_parameter + strlen(strto), &end_of_current_parameter, 10);
        }
    }
    if ((*there_is_from || *there_is_to) == 0) return -4; //нет ни одного корректного аргумента
    else return 0; //всё хорошо
}

void get_rid_of(int *initial_array_length, long long *initial_array,
                int *array_length, long long *array,
                bool there_is_from, bool there_is_to,
                int *from, int *to){
    for (int i = 0; i<*initial_array_length; i++){
        int from_to_checker = 1;
        if (there_is_from && initial_array[i] <= *from) {
            fprintf(stdout, "%lld ", initial_array[i]);
            from_to_checker = 0;
        }
        if (there_is_to && initial_array[i] >= *to) {
            fprintf(stderr, "%lld ", initial_array[i]);
            from_to_checker = 0;
        }
        if (from_to_checker) {
            array[*array_length] = initial_array[i];
            *array_length = *array_length+1;
        }
    }
}

int compare(long long *array1, long long *array2, int length){
    int amount_of_changes = 0;
    for (int i=0; i<length; i++){
        if (array1[i]!=array2[i]) amount_of_changes++;
    }
    return amount_of_changes;
}

int main(int argc, char **argv){
    int from = 0, to = 0;
    bool there_is_from = false, there_is_to = false;
    int verdict = enter_args(&from, &to, &there_is_from, &there_is_to, argc, argv);
    if (verdict != 0) return verdict; //что-то пошло не так и надо вернуть код ошибки

    const int max_length = 100;
    int initial_array_length = 0;
    long long initial_array[max_length];
    long long current_element;

    int eof_check = scanf("%lld", &current_element);
    while (eof_check != EOF){
        initial_array[initial_array_length] = current_element;
        initial_array_length++;
        eof_check = scanf("%lld", &current_element);
    }

    long long array[max_length];
    int array_length = 0;
    get_rid_of(&initial_array_length, initial_array, &array_length, array, there_is_from, there_is_to, &from, &to);

    long long sorted_array[max_length];
    sort(array, sorted_array, array_length);

    fprintf(stdout, "\n");
    for (int i = 0; i<array_length; i++) fprintf(stdout, "%lld ", array[i]);

    fprintf(stdout, "\n");
    for (int i = 0; i<array_length; i++) fprintf(stdout, "%lld ", sorted_array[i]);

    return compare(array, sorted_array, array_length);
}