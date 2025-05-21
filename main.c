#include "filesystem.h"
#include <stdio.h>

int main() {
    // 1. Создаём новый файл
    const char* filename = "example.txt";
    const char* content = "This is file content\nLine 2\nLine 3";
    
    create_file(filename, content);
    printf("Файл '%s' создан\n", filename);

    // 2. Читаем и выводим содержимое
    printf("\nСодержимое файла:\n");
    read_file(filename);

    // 3. Удаляем файл (опционально)
    delete_file(filename);
    
    return 0;
}
