#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../src/lee.h"

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, beginlee, NULL);  // Запускаем алгоритм Ли в отдельном потоке

    pthread_join(thread, NULL);  // Ожидаем завершения работы потока

    // Мониторинг ресурсов и запись в файл
    FILE *file = fopen("files/log.txt", "w");
    if (file) {
        fprintf(file, "Resource usage monitoring information:\n");

        // Тут можно добавить код для мониторинга ресурсов
        // Например, использовать функции для получения информации о потреблении ресурсов.

        fclose(file);
    } else {
        printf("Ошибка открытия файла журнала\n");
    }

    return 0;
}
