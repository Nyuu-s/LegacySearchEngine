#pragma once

#include <stdio.h>
#ifdef WIN32
#include "window.h"
#endif


#define KB(x) ((unsigned long long)1024 * x)
#define MB(x) ((unsigned long long)1024 * KB(x))
#define GB(x) ((unsigned long long)1024 * MB(x))
#define KBSIZE KB(1)
#define MBSIZE MB(1)
#define GBSIZE GB(1)

#define MAX_OPEN_FILESIZE MB(500)

// #############################
// #		Arena Alocator
// #############################
struct LSEArena
{
    char* data;
    int offset;
    int capacity;
    LSEArena* next;

} typedef LSEArena;

void arena_create(int size);
void arena_alloc(void* obj, int size);


// #############################
// #		Data Structures
// #############################

// #############################
// #		File IO
// #############################

struct LSEFileHandle
{
    FILE* descriptor;
    long offset;
    long size;

}typedef LSEFileHandle;

LSEFileHandle open_file_handle(char* file_path){
    LSEFileHandle file = {0};
    FILE* fd = fopen(file_path, "rb");
    if(fd == NULL)
    {
        printf("Error: Couldn't open file %s", *file_path);
        return;
    }
    //TODO: replace by OS api
    fseek(fd, 0, SEEK_END);
    long size = ftell(fd);
    fseek(fd, 0, SEEK_SET);

    file.descriptor = fd;
    file.size = size;
    return file;
}

void close_file_handle(LSEFileHandle file){
    fclose(file.descriptor);
}

size_t read_chunk(LSEFileHandle* file, char* buffer, long chunk_size){
    if(file->descriptor != NULL && buffer != NULL ){
        size_t bytesRead = fread(buffer, sizeof(char), chunk_size, file->descriptor);
        return bytesRead;
    }
    return 0;
}