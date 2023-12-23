#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 10

// Структура для представления вершины графа
struct Node {
    int x, y; // Координаты вершины
    int value; // Значение вершины (0 - свободная вершина, -1 - препятствие)
    int distance; // Расстояние от начальной вершины
};

// Функция для инициализации графа
void initializeGraph(struct Node graph[][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            graph[i][j].x = i;
            graph[i][j].y = j;
            graph[i][j].value = 0;
            graph[i][j].distance = 0;
        }
    }

    // Установка препятствий (пример)
    graph[3][5].value = -1;
    graph[7][2].value = -1;
}

// Функция для вывода графа
void printGraph(struct Node graph[][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (graph[i][j].value == -1) {
                printf("# "); // Препятствие
            } else {
                printf(". "); // Свободная вершина
            }
        }
        printf("\n");
    }
}

// Функция для выполнения алгоритма Ли
void leeAlgorithm(struct Node graph[][SIZE], int startX, int startY, int endX, int endY) {
    // Инициализация начальной вершины
    graph[startX][startY].distance = 1;

    // Очередь для обработки вершин
    struct Node queue[SIZE * SIZE];
    int front = 0, rear = 0;

    // Добавление начальной вершины в очередь
    queue[rear++] = graph[startX][startY];

    // Возможные направления движения
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while (front != rear) {
        // Извлечение вершины из очереди
        struct Node current = queue[front++];
        int currentX = current.x;
        int currentY = current.y;

        // Перебор возможных направлений
        for (int i = 0; i < 4; ++i) {
            int newX = currentX + directions[i][0];
            int newY = currentY + directions[i][1];

            // Проверка на выход за границы и наличие препятствия
            if (newX >= 0 && newX < SIZE && newY >= 0 && newY < SIZE &&
                graph[newX][newY].value == 0 && graph[newX][newY].distance == 0) {
                // Установка расстояния и добавление в очередь
                graph[newX][newY].distance = graph[currentX][currentY].distance + 1;
                queue[rear++] = graph[newX][newY];
            }
        }
    }

    // Вывод расстояний на экран
    printf("\nРасстояния от начальной вершины:\n");
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            printf("%2d ", graph[i][j].distance - 1);
        }
        printf("\n");
    }

    // Вывод кратчайшего пути
    printf("\nКратчайший путь от (%d, %d) до (%d, %d): %d\n", startX, startY, endX, endY,
           graph[endX][endY].distance - 1);
}

int main() {
    struct Node graph[SIZE][SIZE];

    // Инициализация графа
    initializeGraph(graph);

    // Вывод графа на экран
    printf("Планарный граф:\n");
    printGraph(graph);

    // Ввод координат начальной и конечной вершин
    int startX, startY, endX, endY;
    printf("\nВведите координаты начальной вершины (x y): ");
    scanf("%d %d", &startX, &startY);
    printf("Введите координаты конечной вершины (x y): ");
    scanf("%d %d", &endX, &endY);

    // Поиск кратчайшего пути с использованием алгоритма Ли
    leeAlgorithm(graph, startX, startY, endX, endY);

    return 0;
}
