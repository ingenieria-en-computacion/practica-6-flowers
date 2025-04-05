#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// ----------------------------
// Definición de la lista enlazada genérica
// ----------------------------

typedef struct Node {
    void* data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    size_t length;
} List;

Node* node_create(void* data) {
    Node* new_node = malloc(sizeof(Node));
    if (!new_node) return NULL;
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Creacion de  una nueva lista
List* list_create(void) {
    List* list = malloc(sizeof(List));
    if (!list) return NULL;
    list->head = list->tail = NULL;
    list->length = 0;
    return list;
}

// Insertar al final de la lista
bool list_append(List* list, void* data) {
    if (!list) return false;

    Node* new_node = node_create(data);
    if (!new_node) return false;

    if (list->length == 0) {
        list->head = list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->length++;
    return true;
}


bool list_remove_front(List* list) {
    if (!list || list->length == 0) return false;

    Node* temp = list->head;
    list->head = list->head->next;
    free(temp);
    list->length--;
    if (list->length == 0) list->tail = NULL;
    return true;
}

// Obtener el primer elemento de la lista
void* list_front(const List* list) {
    if (list && list->length > 0) {
        return list->head->data;
    }
    return NULL;
}

// la lista está vacía
bool list_is_empty(const List* list) {
    return list && list->length == 0;
}


void list_print(const List* list, void (*print_fn)(void*)) {
    if (!list || !print_fn) return;

    printf("[");
    Node* current = list->head;
    while (current) {
        print_fn(current->data);
        if (current->next) printf(", ");
        current = current->next;
    }
    printf("]\n");
}

// ----------------------------
// Cola Circular
// ----------------------------

typedef struct {
    List* list;
} CircularQueue;

CircularQueue* circular_queue_create(void) {
    CircularQueue* queue = malloc(sizeof(CircularQueue));
    if (!queue) return NULL;
    queue->list = list_create();
    return queue;
}

bool circular_queue_enqueue(CircularQueue* queue, void* data) {
    if (!queue) return false;
    return list_append(queue->list, data);
}

bool circular_queue_dequeue(CircularQueue* queue) {
    if (!queue) return false;
    return list_remove_front(queue->list);
}

void* circular_queue_front(const CircularQueue* queue) {
    return list_front(queue->list);
}

bool circular_queue_is_empty(const CircularQueue* queue) {
    return list_is_empty(queue->list);
}

void circular_queue_print(const CircularQueue* queue, void (*print_fn)(void*)) {
    if (!queue) return;
    list_print(queue->list, print_fn);
}

// ----------------------------
// Bicola
// ----------------------------

typedef struct {
    List* front_list;
    List* back_list;
} Deque;

Deque* deque_create(void) {
    Deque* deque = malloc(sizeof(Deque));
    if (!deque) return NULL;
    deque->front_list = list_create();
    deque->back_list = list_create();
    return deque;
}

bool deque_push_front(Deque* deque, void* data) {
    if (!deque) return false;
    return list_append(deque->front_list, data);
}

bool deque_push_back(Deque* deque, void* data) {
    if (!deque) return false;
    return list_append(deque->back_list, data);
}

bool deque_pop_front(Deque* deque) {
    if (!deque || list_is_empty(deque->front_list)) return false;
    return list_remove_front(deque->front_list);
}

bool deque_pop_back(Deque* deque) {
    if (!deque || list_is_empty(deque->back_list)) return false;
    return list_remove_front(deque->back_list);
}

void* deque_front(const Deque* deque) {
    if (deque && !list_is_empty(deque->front_list)) {
        return list_front(deque->front_list);
    }
    return NULL;
}

void* deque_back(const Deque* deque) {
    if (deque && !list_is_empty(deque->back_list)) {
        return list_front(deque->back_list);
    }
    return NULL;
}

bool deque_is_empty(const Deque* deque) {
    return list_is_empty(deque->front_list) && list_is_empty(deque->back_list);
}

void deque_print(const Deque* deque, void (*print_fn)(void*)) {
    if (!deque) return;
    printf("Front: ");
    list_print(deque->front_list, print_fn);
    printf("Back: ");
    list_print(deque->back_list, print_fn);
}

// ----------------------------
// Funciones para imprimir
// ----------------------------

void print_int(void* data) {
    printf("%d", *((int*)data));
}

int main() {
    
    CircularQueue* queue = circular_queue_create();
    int data1 = 10, data2 = 20, data3 = 30;

    circular_queue_enqueue(queue, &data1);
    circular_queue_enqueue(queue, &data2);
    circular_queue_enqueue(queue, &data3);

    circular_queue_print(queue, print_int);
    printf("Front: %d\n", *((int*)circular_queue_front(queue)));

    circular_queue_dequeue(queue);
    circular_queue_print(queue, print_int);

    
    Deque* deque = deque_create();
    int data4 = 40, data5 = 50, data6 = 60;

    deque_push_front(deque, &data4);
    deque_push_back(deque, &data5);
    deque_push_front(deque, &data6);

    deque_print(deque, print_int);
    printf("Front: %d\n", *((int*)deque_front(deque)));
    printf("Back: %d\n", *((int*)deque_back(deque)));

    deque_pop_front(deque);
    deque_print(deque, print_int);

    return 0;
}
