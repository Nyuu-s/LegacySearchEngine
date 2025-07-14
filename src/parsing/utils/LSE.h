#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define KB(x) ((unsigned long long)1024 * x)
#define MB(x) ((unsigned long long)1024 * KB(x))
#define GB(x) ((unsigned long long)1024 * MB(x))
#define KBSIZE KB(1)
#define MBSIZE MB(1)
#define GBSIZE GB(1)

#define MAX_OPEN_FILESIZE MB(500)

// #############################
// #		LOGGING
// #############################

#define LSELOGMSG(level, msg)                               \
do {                                                        \
    char buffer[10];                                         \
    time_t now = time(NULL);                                \
    struct tm *local = localtime(&now);                     \
    strftime(buffer, sizeof(buffer), "%H:%M:%S", local);         \
    printf("[%s]-%s: %s\n", buffer,level, msg);          \
} while(0);

#define ERROR_LOG(msg) LSELOGMSG("ERROR",msg)
#define WARNING_LOG(msg) LSELOGMSG("WARNING", msg)
#define INFO_LOG(msg) LSELOGMSG("INFO", msg)
#define LSE_ASSERT(condition, message)                  \
do{                                                     \
    if (!(condition))                                   \
    {                                                   \
        LSELOGMSG("ASSERTION FAILED", message);        \
        exit(1);                                        \
    }                                                   \
}while(0)


// #############################
// #		Allocators
// #############################


typedef struct LSEArena
{
    char* data;
    size_t offset;
    size_t capacity;
    
} LSEArena;

LSEArena* arena_create(size_t size);
void* arena_alloc(LSEArena* arena, size_t size);
void arena_release(LSEArena* arena);

LSEArena* arena_create(size_t size){
    LSEArena* arena = (LSEArena*) malloc(sizeof(LSEArena) + size);
    if (!arena) { return NULL; }
    arena->data = (char*) (arena + 1);
    arena->capacity = size;
    arena->offset = 0;
    memset(arena->data, 0, size);

    return arena;
}

void* arena_alloc(LSEArena* arena, size_t size){
    if (!arena) { return NULL; }
    size_t aligned_size  = (size + 7) & ~7;
    if(arena->offset + aligned_size > arena->capacity){
        return NULL;
    }
    void* result = arena->data + arena->offset;
    arena->offset += aligned_size;
    return result;
}

void arena_release(LSEArena* arena)
{
    if(!arena){return;}
    free(arena);
}


// #############################
// #		Data Structures
// #############################
#define DYNA_INITIAL_CAPACITY 256


typedef struct LSEDYNA{
    void* data;
    size_t capacity;
    size_t length;
    LSEArena* region;
} LSEDYNA;


void* dyna_init(LSEArena* arena, size_t capacity, size_t item_size){
    if(!arena) {return NULL;}
    if (item_size == 0) { return NULL; }

    if(capacity == 0) {capacity = DYNA_INITIAL_CAPACITY;}
    LSEDYNA* res = (LSEDYNA*) arena_alloc(arena, (capacity * item_size) + sizeof(LSEDYNA));
    if(!res){return NULL;}
    res->capacity = capacity;
    res->length = 0;
    res->region = arena;
    res->data = res + 1;
    return res->data;
}

void dyna_free(void* arr_data) {
    if (!arr_data) { return; }
    LSEDYNA* array = ((LSEDYNA*) arr_data) - 1;
    arena_release(array->region);
}

void* dyna_append_item(void* arr_data, void* ptr_item, size_t item_size){
    if(!arr_data || !ptr_item){return NULL;}
    LSEDYNA* array = ((LSEDYNA*) arr_data)-1;
    if (array->length >= array->capacity)
    {
        size_t new_cap = array->capacity == 0 ? DYNA_INITIAL_CAPACITY : array->capacity * 2;
        // Only necessary for append_many function where length can grow beyonf capacity
        // while (new_cap < array->length)
        // {
        //     new_cap *= 2;
        // }
        if(!array->region) {return NULL;}
        size_t new_size = sizeof(LSEDYNA) + new_cap * item_size;
        if(array->region->capacity < new_size){
            LSEArena* new_arena = arena_create(new_size);
            if(!new_arena){return NULL;}
            LSEDYNA* new_arr = (LSEDYNA*) arena_alloc(new_arena, new_size);
            if(!new_arr){
                arena_release(new_arena);
                return NULL;
            }
            memcpy(new_arr, array, (array->length * item_size) + sizeof(LSEDYNA));      
            new_arr->data = new_arr + 1;
            new_arr->capacity = new_cap;
            new_arr->length = array->length;
            new_arr->region = new_arena;
            dyna_free(arr_data);
            array = new_arr;
        }
        else
        {
            array->capacity = new_cap;
        }
        
    }
    memcpy((char*)array->data + (array->length * item_size), ptr_item, item_size);
    array->length++;
    return array->data;
}


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
        printf("Error: Couldn't open file %s\n", file_path);
        return file;
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
