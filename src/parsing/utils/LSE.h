#pragma once

#include <stdio.h>
#include <string.h>
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
    size_t offset;
    size_t capacity;
    LSEArena* next;

} typedef LSEArena;

LSEArena arena_create(size_t size);
char* arena_alloc(LSEArena* arena, size_t size);

LSEArena arena_create(int size){
    LSEArena arena = {0};
    arena.data = (char*) malloc(size);
    if(arena.data){
        arena.capacity = size;
        memset(arena.data, 0, size);
    }
    return arena;
}

char* arena_alloc(LSEArena* arena, size_t size){
    LSEArena* local_arena = arena;
    char* result = NULL;
    size_t allignment = (size + 7) & ~7;
    if(arena->offset + allignment > arena->capacity){
        LSEArena n = arena_create(arena->capacity + allignment);
        arena->next = &n;
        local_arena = arena->next;
    }
    result = local_arena->data + local_arena->offset;
    local_arena->offset += size;
    return result;

}


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
    if(file.descriptor){
        fclose(file.descriptor);
    }
}

size_t read_bufferchunk(LSEFileHandle* file, char* buffer, size_t chunk_size){
    if(file->descriptor != NULL && buffer != NULL ){
        size_t bytesRead = fread(buffer, sizeof(char), chunk_size, file->descriptor);
        return bytesRead;
    }
    return 0;
}
