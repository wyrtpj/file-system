#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filesystem.h"
/* 1.1. Открытие (или создание и открытие) файла файловой системы.*/
    int fs_load(const char *fname, FileSystem *fs) {
    FILE *f = fopen(fname, "r");
    if (!f) { 
        fs->entries = NULL;
        fs->count = 0;
        return 0;  
    }
   
    char *line = NULL, *cur_path = NULL, *cur_buf = NULL;
    size_t nline = 0, cur_cap = 0, cur_len = 0;

    while (getline(&line, &nline, f) != -1) {
        if (line[0] == '/') { 
            if (cur_path) {    
                fs_insert(fs, cur_path);
                fs_update(fs, cur_path, cur_buf ? cur_buf : "");
            }
            
           
            free(cur_path);
            cur_path = strdup(line);
            
            
            size_t L = strlen(cur_path);
            if (L && (cur_path[L-1] == '\n' || cur_path[L-1] == '\r')) 
                cur_path[L-1] = '\0';

        
            free(cur_buf);
            cur_buf = NULL; 
            cur_cap = cur_len = 0;
        } else { 
            size_t l = strlen(line);
            
            if (cur_len + l + 1 > cur_cap) {
                cur_cap = (cur_cap ? cur_cap * 2 : 4096) + l;
                cur_buf = realloc(cur_buf, cur_cap);
            }
            
            memcpy(cur_buf + cur_len, line, l);
            cur_len += l;
            cur_buf[cur_len] = '\0';
        }
    }

    
    if (cur_path) {
        fs_insert(fs, cur_path);
        fs_update(fs, cur_path, cur_buf ? cur_buf : "");
    }

  
    free(cur_path);
    free(cur_buf);
    free(line);
    fclose(f);
    return 0;
}

/* 1.2. Просмотр содержимого файла в файловой системе.*/
    int fs_select(const FileSystem *fs, const char *path, char **out_content) {
    int idx = find_index(fs, path);
    if (idx < 0) return -1;
    
    *out_content = strdup(fs->entries[idx].content);  
    return 0;
}
/* 1.3. Удаление файла из файловой системы.*/
    int fs_delete(FileSystem *fs, const char *path) {
    int idx = find_index(fs, path);
    if (idx < 0) return -1;
    

    free(fs->entries[idx].path);
    free(fs->entries[idx].content);
    

    memmove(
        &fs->entries[idx], 
        &fs->entries[idx + 1],
        (fs->count - idx - 1) * sizeof(FileEntry)
    );
    
    fs->count--;  
    return 0;
}

static int find_index(const FileSystem *fs, const char *path) {
    for (size_t i = 0; i < fs->count; ++i)
        if (strcmp(fs->entries[i].path, path) == 0)
            return (int)i;
    return -1;
}

int fs_save(const char *fname, const FileSystem *fs) {
    FILE *f = fopen(fname, "w");
    if (!f) return -1;
    
    for (size_t i = 0; i < fs->count; ++i) {
        fprintf(f, "%s\n", fs->entries[i].path); 
        
        fputs(fs->entries[i].content, f);
        size_t L = strlen(fs->entries[i].content);
        if (L == 0 || fs->entries[i].content[L-1] != '\n')
            fputc('\n', f);
    }
    fclose(f);
    // 1.1. Функция для создания нового файла
void create_new_file(const char* filename, const char* content) {
    FILE* fs = fopen("filesystem.txt", "a");
    if (!fs) {
        perror("Failed to open filesystem");
        return;
    }
    
    fprintf(fs, "\nFILE: %s\n", filename);
    fprintf(fs, "%s", content);
    
    fclose(fs);
}

// 1.2. Функция для изменения существующего файла
void modify_file(const char* filename, const char* new_content) {
    FILE* fs = fopen("filesystem.txt", "r");
    if (!fs) {
        perror("Failed to open filesystem for reading");
        return;
    }
    
    FILE* temp = fopen("temp.txt", "w");
    if (!temp) {
        perror("Failed to create temp file");
        fclose(fs);
        return;
    }
    
    char line[256];
    int in_target_file = 0;
    
    while (fgets(line, sizeof(line), fs)) {
        if (strstr(line, "FILE: ") == line) {
            char current_file[256];
            sscanf(line, "FILE: %255s", current_file);
            
            if (strcmp(current_file, filename) == 0) {
                in_target_file = 1;
                fprintf(temp, "%s", line); 
                fprintf(temp, "%s\n", new_content); 
            } else {
                in_target_file = 0;
                fprintf(temp, "%s", line); 
            }
        } else if (!in_target_file) {
            fprintf(temp, "%s", line);
        }
    }
    
    fclose(fs);
    fclose(temp);

    remove("filesystem.txt");
    rename("temp.txt", "filesystem.txt");
}
    return 0;
}
    
