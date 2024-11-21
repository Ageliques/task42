#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int priority;
    char* message;
    struct Node* next;
} Node;

typedef struct PriorityQueue {
    Node* head;
} PriorityQueue;

// Функция для создания нового узла
Node* create_node(int priority, const char* message) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->priority = priority;
    new_node->message = strdup(message);
    new_node->next = NULL;
    return new_node;
}

// Функция для инициализации очереди с приоритетом
PriorityQueue* create_priority_queue() {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->head = NULL;
    return pq;
}

// Функция для добавления элемента в очередь
void enqueue(PriorityQueue* pq, int priority, const char* message) {
    Node* new_node = create_node(priority, message);
    
    if (pq->head == NULL || pq->head->priority < priority) {
        // Вставка в начало очереди
        new_node->next = pq->head;
        pq->head = new_node;
    } else {
        // Поиск места для вставки
        Node* current = pq->head;
        while (current->next != NULL && current->next->priority >= priority) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

// Функция для извлечения элемента с самым высоким приоритетом
char* dequeue(PriorityQueue* pq) {
    if (pq->head == NULL) {
        return NULL; // Очередь пуста
    }
    
    Node* temp = pq->head;
    pq->head = pq->head->next;
    
    char* message = temp->message; // Сохранение сообщения для возврата
    free(temp); // Освобождение памяти
    return message;
}

// Функция для извлечения элемента с указанным приоритетом
char* dequeue_with_priority(PriorityQueue* pq, int priority) {
    Node* current = pq->head;
    Node* previous = NULL;

    while (current != NULL) {
        if (current->priority == priority) {
            if (previous == NULL) {
                // Удаление первого элемента
                pq->head = current->next;
            } else {
                previous->next = current->next;
            }
            char* message = current->message; // Сохранение сообщения для возврата
            free(current); // Освобождение памяти
            return message;
        }
        previous = current;
        current = current->next;
    }
    
    return NULL; // Элемент с указанным приоритетом не найден
}

// Функция для извлечения элемента с приоритетом не ниже заданного
char* dequeue_with_min_priority(PriorityQueue* pq, int min_priority) {
    Node* current = pq->head;

    while (current != NULL) {
        if (current->priority >= min_priority) {
            // Удаление этого элемента
            if (current == pq->head) {
                pq->head = current->next; // Удаление первого элемента
            } else {
                Node* previous = pq->head;
                while (previous->next != current) {
                    previous = previous->next;
                }
                previous->next = current->next; // Удаление текущего элемента
            }
            char* message = current->message; // Сохранение сообщения для возврата
            free(current); // Освобождение памяти
            return message;
        }
        current = current->next;
    }
    
    return NULL; // Элемент с подходящим приоритетом не найден
}

// Функция для освобождения памяти, занятой очередью
void free_priority_queue(PriorityQueue* pq) {
    Node* current = pq->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp->message); // Освобождение памяти для сообщения
        free(temp);
    }
    free(pq);
}

int main() {
    PriorityQueue* pq = create_priority_queue();
    int choice, priority, min_priority;
    char message[256];

    while (1) {
        printf("Select an action:\n");
        printf("1. Add an item\n");
        printf("2. Extract the item with the highest priority\n");
        printf("3. Extract the item with the specified priority\n");
        printf("4. Extract an element with a priority not lower than the specified one\n");
        printf("5. Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the priority (0-255): ");
                scanf("%d", &priority);
                printf("Enter a message: ");
                scanf(" %[^\n]s", message); // Чтение строки с пробелами
                enqueue(pq, priority, message);
                break;

            case 2:
                printf("The extracted element: %s\n", dequeue(pq));
                break;

            case 3:
                printf("Enter the priority for extraction: ");
                scanf("%d", &priority);
                printf("The extracted element: %s\n", dequeue_with_priority(pq, priority));
                break;

            case 4:
                printf("Enter the minimum priority: ");
                scanf("%d", &min_priority);
                printf("The extracted element: %s\n", dequeue_with_min_priority(pq, min_priority));
                break;

            case 5:
                free_priority_queue(pq);
                exit(0);

            default:
                printf("Wrong choice. Try again.\n");
                break;
        }
    }

    return 0;
}
