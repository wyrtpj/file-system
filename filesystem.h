#ifndef FILESYSTEM_H
#define FILESYSTEM_H

void create_file(const char* name, const char* data);
void read_file(const char* name);
void delete_file(const char* name);
void update_file(const char* name, const char* new_data);

#endif
