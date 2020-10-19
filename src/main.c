#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

extern void sort(long long *unsorted_array, long long *result_array, int size_of_array);

/*int the_string_starts_with(char *string, char *substring){
    unsigned int length_of_substring = strlen(substring);
    if (strlen(string) < length_of_substring) return 0;
    for (int i = 0; i<length_of_substring; i++){
        if (string[i] != substring[i]) return 0;
    }
    return 1;
}*/

int enter_args(int *from, int *to, bool *there_is_from, bool *there_is_to, int argc, char **argv){
    char strfrom[8] = "--from=", strto[6] = "--to=";
    if (argc < 2) return -1; //введено 0 параметров
    if (argc > 3) return -2; //введено 3 и более параметров
    for (int i = 1; i < argc; i++){
        if (strncmp(argv[i], strfrom, strlen(strfrom)) == 0){
            if (*there_is_from) return -3; //from введён более 1-ого раза
            *there_is_from = 1;
            *from = strtol(argv[i] + strlen(strfrom), argv[i] + strlen(argv[i]), 10);
        }
        if (strncmp(argv[i], strto, strlen(strto)) == 0) {
            if (*there_is_to) return -3; //to введён более 1-ого раза
            *there_is_to = 1;
            *to = strtol(argv[i] + strlen(strto), argv[i] + strlen(argv[i]), 10);
        }
    }
    if (*there_is_from || *there_is_to == 0) return -4; //нет ни одного корректного аргумента
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
            *array_length = *array_length+1;
            array[*array_length] = initial_array[i];
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

    return compare(array, sorted_array, array_length);
}