#define LINKED_LIST_IMPLEMENTATION
#include "../include/linked_list.h"
#include <stdio.h>

// Función para imprimir enteros
void print_int(int value) {
    printf("%d ", value);
}

// Función para imprimir caracteres
void print_char(char value) {
    printf("%c ", value);
}

int main() {
    // Lista de enteros
    List_int* nums = list_int_create();
    int a = 10, b = 20, c = 30;
    list_int_append(nums, a);
    list_int_append(nums, b);
    list_int_append(nums, c);

    printf("Lista de enteros: ");
    list_int_print(nums, print_int); // Imprime la lista de enteros
    printf("\n");

    list_int_destroy(nums); // Destrucción de la lista

    // Lista de caracteres
    List_char* chars = list_char_create();
    char x = 'a', y = 'b', z = 'c';
    list_char_append(chars, x);
    list_char_append(chars, y);
    list_char_append(chars, z);

    printf("Lista de caracteres: ");
    list_char_print(chars, print_char); // Imprime la lista de caracteres
    printf("\n");

    list_char_destroy(chars); // Destrucción de la lista

    return 0;
}
