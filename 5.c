#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PATH_LENGTH 256
#define MAX_CONTENT_LENGTH 1024

void create_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка: Не удалось создать файл '%s'\n", filename);
        return;
    }
    fclose(file);
    printf("Файл '%s' успешно создан\n", filename);
}

void delete_file(const char *filename) {
    if (remove(filename) == 0) {
        printf("Файл '%s' успешно удален\n", filename);
    } else {
        printf("Ошибка: Не удалось удалить файл '%s'\n", filename);
    }
}


void modify_file(const char *filename) {
    printf("Введите содержимое для файла '%s' (макс. %d символов):\n", filename, MAX_CONTENT_LENGTH);
    
    char content[MAX_CONTENT_LENGTH];
    fgets(content, MAX_CONTENT_LENGTH, stdin); // Чтение предыдущего перевода строки
    fgets(content, MAX_CONTENT_LENGTH, stdin);
    
    
    content[strcspn(content, "\n")] = '\0';
    
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка: Не удалось открыть файл '%s' для записи\n", filename);
        return;
    }
    
    fprintf(file, "%s", content);
    fclose(file);
    printf("Содержимое файла '%s' успешно изменено\n", filename);
}

void view_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка: Не удалось открыть файл '%s' для чтения\n", filename);
        return;
    }
    
    printf("Содержимое файла '%s':\n", filename);
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    printf("\n");
    fclose(file);
}

int main() {
    printf("Добро пожаловать в простую файловую систему!\n");
    printf("Доступные команды:\n");
    printf("создать <путь_до_файла>\n");
    printf("удалить <путь_до_файла>\n");
    printf("изменить <путь_до_файла>\n");
    printf("просмотреть <путь_до_файла>\n");
    printf("выход - для завершения работы\n\n");
    
    char command[20];
    char filename[MAX_PATH_LENGTH];
    
    while (true) {
        printf("> ");
        scanf("%19s", command);
        
        if (strcmp(command, "выход") == 0) {
            break;
        }
        
        scanf("%255s", filename);
        
        if (strcmp(command, "создать") == 0) {
            create_file(filename);
        } 
        else if (strcmp(command, "удалить") == 0) {
            delete_file(filename);
        } 
        else if (strcmp(command, "изменить") == 0) {
            modify_file(filename);
        } 
        else if (strcmp(command, "просмотреть") == 0) {
            view_file(filename);
        } 
        else {
            printf("Неизвестная команда: %s\n", command);
            printf("Доступные команды: создать, удалить, изменить, просмотреть, выход\n");
        }
    }
    
    printf("Работа файловой системы завершена.\n");
    return 0;
}
