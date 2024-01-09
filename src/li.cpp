#include <stdio.h>
#include <stdlib.h>

#define ROWS 10
#define COLS 10
#define MAX_QUEUE_SIZE 100

int grid[ROWS][COLS] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 0, 0, 1, 1, 0},
    {0, 0, 0, 1, 1, 1, 0, 1, 1, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
    {0, 1, 0, 0, 1, 1, 1, 0, 1, 0},
    {0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 1, 1, 0, 1, 1, 1, 0},
    {0, 1, 1, 0, 1, 0, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point items[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Queue;

void initQueue(Queue *q) {
    q->front = 0;
    q->rear = 0;
}

int isQueueEmpty(Queue *q) {
    return q->front == q->rear;
}

void enqueue(Queue *q, int x, int y) {
    q->items[q->rear].x = x;
    q->items[q->rear].y = y;
    q->rear++;
}

void dequeue(Queue *q, int *x, int *y) {
    *x = q->items[q->front].x;
    *y = q->items[q->front].y;
    q->front++;
}

int isInsideGrid(int x, int y) {
    return x >= 0 && x < ROWS && y >= 0 && y < COLS;
}

void printGrid(int grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

void leeAlgorithm(int grid[ROWS][COLS], Point start, Point end) {
    Queue q;
    initQueue(&q);

    if (grid[start.x][start.y] == 1 || grid[end.x][end.y] == 1) {
        printf("Invalid start or end point\n");
        return;
    }

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    grid[start.x][start.y] = 2;
    enqueue(&q, start.x, start.y);

    while (!isQueueEmpty(&q)) {
        int x, y;
        dequeue(&q, &x, &y);

        for (int i = 0; i < 4; i++) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (isInsideGrid(newX, newY) && grid[newX][newY] == 0) {
                grid[newX][newY] = grid[x][y] + 1;
                enqueue(&q, newX, newY);
            }
        }
    }
}

void logResourceUsage() {
    // TODO: Implement monitoring of resource usage and write to log file
    // Example: write resource usage to log.txt in files directory
    FILE *file = fopen("files/log.txt", "w");
    if (file) {
        // Write resource usage to log file
        fprintf(file, "Resource usage monitoring information\n");
        fclose(file);
    } else {
        printf("Error opening log file\n");
    }
}

int main() {
    Point start = {1, 1};
    Point end = {8, 8};

    leeAlgorithm(grid, start, end);
    printGrid(grid);

    logResourceUsage();

    return 0;
}
