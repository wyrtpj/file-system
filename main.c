#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "filesystem.h"

static const char *FS_PATH = "disk.filesystem";

int main(void) {
    FileSystem fs = {0};

    if (fs_load(FS_PATH, &fs) != 0) {
        printf("Создаем новую файловую систему\n");
    }

    const char *filename = "test.txt";
    const char *content = "Это содержимое тестового файла\nВторая строка";
    
    if (fs_insert(&fs, filename) == 0) {
        fs_update(&fs, filename, content);
        printf("Файл '%s' создан\n", filename);
    } else {
        printf("Файл '%s' уже существует\n", filename);
    }

    char *file_content = NULL;
    if (fs_select(&fs, filename, &file_content) == 0) {
        printf("\nСодержимое файла '%s':\n%s\n", filename, file_content);
        free(file_content);
    } else {
        printf("Не удалось прочитать файл '%s'\n", filename);
    }

    fs_save(FS_PATH, &fs);
    fs_free(&fs);
    
    return 0;
}
