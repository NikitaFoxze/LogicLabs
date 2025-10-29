#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct node {
    char inf[256];
    int priority;
    struct node* next;
};

struct node* priority_head = NULL;
struct node* queue_front = NULL;
struct node* queue_rear = NULL;
struct node* stack_top = NULL;

// Флаг направления приоритета (1 - по убыванию, 0 - по возрастанию)
int priority_direction = 1; // по умолчанию: чем больше число - тем выше приоритет

// Функции для работы с приоритетной очередью
struct node* get_priority_struct(void);
void insert_by_priority(void);
void display_priority(void);
void delete_highest_priority(void);
void destroy_priority_queue(void);
void change_priority_direction(void); // new: изменение направления приоритетов
void change_element_priority(void);   // new: изменение приоритета элемента по имени
void delete_element_by_name(void);    // new: удаление элемента по названию

// Функции для работы с обычной очередью
struct node* get_queue_struct(void);
void enqueue(void);
void dequeue(void);
void display_queue(void);
void destroy_queue(void);

// Функции для работы со стеком
struct node* get_stack_struct(void);
void push(void);
void pop(void);
void display_stack(void);
void destroy_stack(void);

void display_menu(void);

int main() {
    setlocale(LC_ALL, "");
    int choice, structure_choice;

    while (1) {
        display_menu();
        scanf_s("%d", &structure_choice);

        switch (structure_choice) {
        case 1: // Приоритетная очередь
            while (1) {
                printf("\n=== ПРИОРИТЕТНАЯ ОЧЕРЕДЬ ===\n");
                printf("1. Добавить элемент с приоритетом\n");
                printf("2. Просмотреть очередь\n");
                printf("3. Удалить элемент с наивысшим приоритетом\n");
                printf("4. Очистить очередь\n");
                printf("5. Изменить направление приоритетов\n");     // НОВЫЙ ПУНКТ
                printf("6. Изменить приоритет элемента по имени\n");  // НОВЫЙ ПУНКТ
                printf("7. Удалить элемент по названию\n");           // НОВЫЙ ПУНКТ
                printf("8. Вернуться в главное меню\n");
                printf("Выберите действие: ");
                scanf_s("%d", &choice);

                if (choice == 8) break;

                switch (choice) {
                case 1: insert_by_priority(); break;
                case 2: display_priority(); break;
                case 3: delete_highest_priority(); break;
                case 4: destroy_priority_queue(); break;
                case 5: change_priority_direction(); break;  // НОВЫЙ ВЫЗОВ
                case 6: change_element_priority(); break;    // НОВЫЙ ВЫЗОВ
                case 7: delete_element_by_name(); break;     // НОВЫЙ ВЫЗОВ
                default: printf("Неверный выбор\n");
                }
            }
            break;

        case 2: // Обычная очередь
            while (1) {
                printf("\n=== ОБЫЧНАЯ ОЧЕРЕДЬ (FIFO) ===\n");
                printf("1. Добавить элемент в конец (enqueue)\n");
                printf("2. Удалить элемент из начала (dequeue)\n");
                printf("3. Просмотреть очередь\n");
                printf("4. Очистить очередь\n");
                printf("5. Вернуться в главное меню\n");
                printf("Выберите действие: ");
                scanf_s("%d", &choice);

                if (choice == 5) break;

                switch (choice) {
                case 1: enqueue(); break;
                case 2: dequeue(); break;
                case 3: display_queue(); break;
                case 4: destroy_queue(); break;
                default: printf("Неверный выбор\n");
                }
            }
            break;

        case 3: // Стек
            while (1) {
                printf("\n=== СТЕК (LIFO) ===\n");
                printf("1. Добавить элемент в вершину (push)\n");
                printf("2. Удалить элемент из вершины (pop)\n");
                printf("3. Просмотреть стек\n");
                printf("4. Очистить стек\n");
                printf("5. Вернуться в главное меню\n");
                printf("Выберите действие: ");
                scanf_s("%d", &choice);

                if (choice == 5) break;

                switch (choice) {
                case 1: push(); break;
                case 2: pop(); break;
                case 3: display_stack(); break;
                case 4: destroy_stack(); break;
                default: printf("Неверный выбор\n");
                }
            }
            break;

        case 4:
            // Очистка всех структур перед выходом
            destroy_priority_queue();
            destroy_queue();
            destroy_stack();
            printf("Выход из программы.\n");
            exit(0);

        default:
            printf("Неверный выбор\n");
        }
    }
    return 0;
}

void display_menu(void) {
    printf("\n=== ГЛАВНОЕ МЕНЮ ===\n");
    printf("1. Работа с приоритетной очередью\n");
    printf("2. Работа с обычной очередью (FIFO)\n");
    printf("3. Работа со стеком (LIFO)\n");
    printf("4. Выход\n");
    printf("Выберите структуру данных: ");
}

// ==================== ПРИОРИТЕТНАЯ ОЧЕРЕДЬ ====================

struct node* get_priority_struct(void) {
    struct node* p = (struct node*)malloc(sizeof(struct node));
    char s[256];
    int prio;

    if (p == NULL) {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }

    printf("Введите название объекта: ");
    scanf_s("%s", s, (unsigned)sizeof(s));
    if (*s == 0) {
        printf("Запись не была произведена\n");
        free(p);
        return NULL;
    }

    printf("Введите приоритет (целое число): ");
    scanf_s("%d", &prio);

    strcpy_s(p->inf, sizeof(p->inf), s);
    p->priority = prio;
    p->next = NULL;

    return p;
}

void insert_by_priority(void) {
    struct node* p = get_priority_struct();
    if (p == NULL) return;

    struct node* current = priority_head;
    struct node* prev = NULL;

    if (priority_head == NULL) {
        priority_head = p;
        printf("Элемент '%s' с приоритетом %d добавлен\n", p->inf, p->priority);
        return;
    }

    // Вставка с учетом направления приоритета
    if (priority_direction) {
        // По убыванию (чем больше число - тем выше приоритет)
        if (p->priority > priority_head->priority) {
            p->next = priority_head;
            priority_head = p;
        }
        else {
            while (current != NULL && current->priority >= p->priority) {
                prev = current;
                current = current->next;
            }
            prev->next = p;
            p->next = current;
        }
    }
    else {
        // По возрастанию (чем меньше число - тем выше приоритет)
        if (p->priority < priority_head->priority) {
            p->next = priority_head;
            priority_head = p;
        }
        else {
            while (current != NULL && current->priority <= p->priority) {
                prev = current;
                current = current->next;
            }
            prev->next = p;
            p->next = current;
        }
    }

    printf("Элемент '%s' с приоритетом %d добавлен\n", p->inf, p->priority);
}

void display_priority(void) {
    struct node* current = priority_head;

    if (priority_head == NULL) {
        printf("Приоритетная очередь пуста\n");
        return;
    }

    printf("\n=== ПРИОРИТЕТНАЯ ОЧЕРЕДЬ ===\n");
    printf("Направление: %s\n", priority_direction ?
        "по убыванию (чем БОЛЬШЕ число - тем ВЫШЕ приоритет)" :
        "по возрастанию (чем МЕНЬШЕ число - тем ВЫШЕ приоритет)");
    printf("Приоритет | Данные\n");
    printf("----------|--------\n");

    while (current != NULL) {
        printf("%9d | %s\n", current->priority, current->inf);
        current = current->next;
    }
}

void delete_highest_priority(void) {
    if (priority_head == NULL) {
        printf("Приоритетная очередь пуста\n");
        return;
    }

    struct node* temp = priority_head;
    printf("Удален элемент: '%s' с приоритетом %d\n", temp->inf, temp->priority);
    priority_head = priority_head->next;
    free(temp);
}

void destroy_priority_queue(void) {
    struct node* current = priority_head;
    struct node* next;
    int count = 0;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
        count++;
    }

    priority_head = NULL;
    printf("Приоритетная очередь очищена. Удалено элементов: %d\n", count);
}

// НОВАЯ ФУНКЦИЯ: Изменение направления приоритетов
void change_priority_direction(void) {
    if (priority_head == NULL) {
        printf("Очередь пуста. Направление изменено.\n");
        priority_direction = !priority_direction;
        printf("Текущее направление: %s\n", priority_direction ?
            "по убыванию (чем БОЛЬШЕ число - тем ВЫШЕ приоритет)" :
            "по возрастанию (чем МЕНЬШЕ число - тем ВЫШЕ приоритет)");
        return;
    }

    printf("Текущее направление: %s\n", priority_direction ?
        "по убыванию (чем БОЛЬШЕ число - тем ВЫШЕ приоритет)" :
        "по возрастанию (чем МЕНЬШЕ число - тем ВЫШЕ приоритет)");

    priority_direction = !priority_direction;
    printf("Направление изменено на: %s\n", priority_direction ?
        "по убыванию (чем БОЛЬШЕ число - тем ВЫШЕ приоритет)" :
        "по возрастанию (чем МЕНЬШЕ число - тем ВЫШЕ приоритет)");

    // Пересортировка очереди при изменении направления
    struct node* new_head = NULL;
    struct node* current = priority_head;

    while (current != NULL) {
        struct node* next = current->next;
        struct node* temp_current = new_head;
        struct node* temp_prev = NULL;

        if (new_head == NULL) {
            new_head = current;
            current->next = NULL;
        }
        else {
            if (priority_direction) {
                // По убыванию
                while (temp_current != NULL && temp_current->priority >= current->priority) {
                    temp_prev = temp_current;
                    temp_current = temp_current->next;
                }
            }
            else {
                // По возрастанию
                while (temp_current != NULL && temp_current->priority <= current->priority) {
                    temp_prev = temp_current;
                    temp_current = temp_current->next;
                }
            }

            if (temp_prev == NULL) {
                current->next = new_head;
                new_head = current;
            }
            else {
                temp_prev->next = current;
                current->next = temp_current;
            }
        }
        current = next;
    }

    priority_head = new_head;
    printf("Очередь пересортирована в соответствии с новым направлением приоритетов.\n");
}

// НОВАЯ ФУНКЦИЯ: Изменение приоритета элемента по имени
void change_element_priority(void) {
    if (priority_head == NULL) {
        printf("Приоритетная очередь пуста\n");
        return;
    }

    char name[256];
    printf("Введите название элемента для изменения приоритета: ");
    scanf_s("%s", name, (unsigned)sizeof(name));

    // Поиск элемента
    struct node* current = priority_head;
    struct node* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->inf, name) == 0) {
            // Элемент найден
            int new_priority;
            printf("Найден элемент '%s' с текущим приоритетом %d\n", current->inf, current->priority);
            printf("Введите новый приоритет: ");
            scanf_s("%d", &new_priority);

            // Удаляем элемент из текущей позиции
            if (prev == NULL) {
                priority_head = current->next;
            }
            else {
                prev->next = current->next;
            }

            // Обновляем приоритет
            current->priority = new_priority;
            current->next = NULL;

            // Вставляем элемент обратно с новым приоритетом
            struct node* insert_current = priority_head;
            struct node* insert_prev = NULL;

            if (priority_head == NULL) {
                priority_head = current;
            }
            else {
                if (priority_direction) {
                    // По убыванию
                    if (current->priority > priority_head->priority) {
                        current->next = priority_head;
                        priority_head = current;
                    }
                    else {
                        while (insert_current != NULL && insert_current->priority >= current->priority) {
                            insert_prev = insert_current;
                            insert_current = insert_current->next;
                        }
                        insert_prev->next = current;
                        current->next = insert_current;
                    }
                }
                else {
                    // По возрастанию
                    if (current->priority < priority_head->priority) {
                        current->next = priority_head;
                        priority_head = current;
                    }
                    else {
                        while (insert_current != NULL && insert_current->priority <= current->priority) {
                            insert_prev = insert_current;
                            insert_current = insert_current->next;
                        }
                        insert_prev->next = current;
                        current->next = insert_current;
                    }
                }
            }

            printf("Приоритет элемента '%s' изменен на %d\n", name, new_priority);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Элемент с названием '%s' не найден\n", name);
}

// НОВАЯ ФУНКЦИЯ: Удаление элемента по названию
void delete_element_by_name(void) {
    if (priority_head == NULL) {
        printf("Приоритетная очередь пуста\n");
        return;
    }

    char name[256];
    printf("Введите название элемента для удаления: ");
    scanf_s("%s", name, (unsigned)sizeof(name));

    struct node* current = priority_head;
    struct node* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->inf, name) == 0) {
            // Элемент найден
            if (prev == NULL) {
                // Удаление первого элемента
                priority_head = current->next;
            }
            else {
                prev->next = current->next;
            }

            printf("Элемент '%s' с приоритетом %d удален\n", current->inf, current->priority);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Элемент с названием '%s' не найден\n", name);
}

// ==================== ОБЫЧНАЯ ОЧЕРЕДЬ (FIFO) ====================

struct node* get_queue_struct(void) {
    struct node* p = (struct node*)malloc(sizeof(struct node));
    char s[256];

    if (p == NULL) {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }

    printf("Введите название объекта: ");
    scanf_s("%s", s, (unsigned)sizeof(s));
    if (*s == 0) {
        printf("Запись не была произведена\n");
        free(p);
        return NULL;
    }

    strcpy_s(p->inf, sizeof(p->inf), s);
    p->next = NULL;

    return p;
}

void enqueue(void) {
    struct node* p = get_queue_struct();
    if (p == NULL) return;

    if (queue_rear == NULL) {
        queue_front = queue_rear = p;
    }
    else {
        queue_rear->next = p;
        queue_rear = p;
    }
    printf("Элемент '%s' добавлен в конец очереди\n", p->inf);
}

void dequeue(void) {
    if (queue_front == NULL) {
        printf("Очередь пуста\n");
        return;
    }

    struct node* temp = queue_front;
    printf("Удален элемент из начала очереди: '%s'\n", temp->inf);

    queue_front = queue_front->next;

    if (queue_front == NULL) {
        queue_rear = NULL;
    }

    free(temp);
}

void display_queue(void) {
    struct node* current = queue_front;

    if (queue_front == NULL) {
        printf("Очередь пуста\n");
        return;
    }

    printf("\n=== ОЧЕРЕДЬ (FIFO) ===\n");
    printf("Данные\n");
    printf("------\n");

    while (current != NULL) {
        printf("%s\n", current->inf);
        current = current->next;
    }
}

void destroy_queue(void) {
    struct node* current = queue_front;
    struct node* next;
    int count = 0;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
        count++;
    }

    queue_front = queue_rear = NULL;
    printf("Очередь очищена. Удалено элементов: %d\n", count);
}

// ==================== СТЕК (LIFO) ====================

struct node* get_stack_struct(void) {
    struct node* p = (struct node*)malloc(sizeof(struct node));
    char s[256];

    if (p == NULL) {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }

    printf("Введите название объекта: ");
    scanf_s("%s", s, (unsigned)sizeof(s));
    if (*s == 0) {
        printf("Запись не была произведена\n");
        free(p);
        return NULL;
    }

    strcpy_s(p->inf, sizeof(p->inf), s);
    p->next = NULL;

    return p;
}

void push(void) {
    struct node* p = get_stack_struct();
    if (p == NULL) return;

    p->next = stack_top;
    stack_top = p;
    printf("Элемент '%s' добавлен в вершину стека\n", p->inf);
}

void pop(void) {
    if (stack_top == NULL) {
        printf("Стек пуст\n");
        return;
    }

    struct node* temp = stack_top;
    printf("Удален элемент из вершины стека: '%s'\n", temp->inf);

    stack_top = stack_top->next;
    free(temp);
}

void display_stack(void) {
    struct node* current = stack_top;

    if (stack_top == NULL) {
        printf("Стек пуст\n");
        return;
    }

    printf("\n=== СТЕК (LIFO) ===\n");
    printf("Данные\n");
    printf("------\n");

    while (current != NULL) {
        printf("%s\n", current->inf);
        current = current->next;
    }
}

void destroy_stack(void) {
    struct node* current = stack_top;
    struct node* next;
    int count = 0;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
        count++;
    }

    stack_top = NULL;
    printf("Стек очищен. Удалено элементов: %d\n", count);
}