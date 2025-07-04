#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



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




typedef struct LSEArena
{
    char* data;
    size_t offset;
    size_t capacity;
    // struct LSEArena* next; // remove ? maybe keep it simple

} LSEArena;

LSEArena arena_create(size_t size);
void* arena_alloc(LSEArena* arena, size_t size);
void arena_release(LSEArena* arena);



LSEArena arena_create(size_t size){
    LSEArena arena = {0};
    arena.data = (char*) malloc(size);
    if(arena.data){
        arena.capacity = size;
        memset(arena.data, 0, size);
    }
    return arena;
}

void* arena_alloc(LSEArena* arena, size_t size){
    void* result = NULL;
    size_t allignment = (size + 7) & ~7;
    if(arena->offset + allignment > arena->capacity){
        return NULL;
    }
    result = arena->data + arena->offset;
    arena->offset += size;
    return result;
}
//TODO arenaRelease


// #############################
// #		Data Structures
// #############################
#define DYNA_INITIAL_CAPACITY 256
#define DYNA_INIT(T, cap, arena) (T*)(dyna_init(cap, sizeof(T), arena))
typedef struct DYNA_ARRAY
{
    size_t size;
    size_t capacity;
    size_t item_size;
    LSEArena* arena;
} DYNA_ARRAY;

void* dyna_init(size_t capacity, size_t item_size, LSEArena* arena){
    size_t total_size = sizeof(DYNA_ARRAY) + capacity * item_size;
    if(arena == NULL || arena->offset + total_size > arena->capacity) return NULL;

    DYNA_ARRAY* array = arena_alloc(arena, total_size);
    if(!array) return NULL;
    
    array->arena = arena;
    array->capacity = capacity;
    array->size = 0;
    array->item_size = item_size;
    array += 1;
    return array;
}
void* dyna_resize_if_needed(DYNA_ARRAY* array, size_t item_count){

    //check if desired capacity do not exeed array capacity
    //yes -> rturn the array as is
    //no -> proceed
    if(array->size + item_count <= array->capacity){
        return array;
    }

    //check if desired capacity exeeds arenas available region (capacity - used)
    //no  -> extends last allocation by bumbing arenas offset
    //yes -> create new arena, copy data and free old
    size_t new_item_size = array->item_size * item_count;
    if (new_item_size > (array->arena->capacity - array->arena->offset))
    {
        // create new arena
    }
    
    //check if desired capacity exeeds arena's capacity
    //yes -> create new arena, copy data back return new pointer to array, free the old array /!\ will invalidate pointer to the old array
    //no -> proceed

    //return the pointer to the data in the array
}
void* dyna_append(void* array, void* element){
    //todo: check if array is SETTLED, no more appending allowed

    array = dyna_resize_if_needed();
    DYNA_ARRAY* header = (DYNA_ARRAY*)array - 1; 

    //copy value to end of array and avoid using memcpy, maybe less perf but usable in more env
    char* dest = (char*)array + header->size * header->item_size;
    char* src =  (char*)element;
    for(size_t i = 0; i<header->item_size; i++){
        dest[i] = src[i];
    }
    header->size++;
}

void t(){
   int* p = dyna_init(10, sizeof(int), NULL);
   int a =5;
   dyna_append(p, &a);
}

// #define ARRAY(T, a) (T*)dyna_init(sizeof(T), initial_capacity, a)
// #define GET_DYNA_HEADER(arr) ((DYNA_HEADER*) (arr) - 1)

// #define DYNA_APPEND(arr, value)\
//     ((arr) = dyna_check_capacity_and_realloc(arr, 1, sizeof(value)),\
//     (a)[GET_DYNA_HEADER(arr)->size] = (value),\
//     &(a)[GET_DYNA_HEADER(arr)->size++])
    

// void* dyna_check_capacity_and_realloc(void* array, size_t item_count, size_t item_size){
//     DYNA_HEADER* h = GET_DYNA_HEADER(array);
//     size_t desired_cap = h->size + item_count;

//     if(h->capacity < desired_cap){
//         size_t new_cap = h->capacity * 2;
//         while(h->capacity < desired_cap){
//             new_cap *= 2;
//         }
//         size_t new_size = sizeof(DYNA_HEADER) + new_cap * item_size;
//         DYNA_HEADER* new_h = arena_alloc(h->arena, new_size);
//         if(!new_h){
//             h = 0;
//             return h;
//         }
//         size_t old_size = h->size * item_size + sizeof(DYNA_HEADER);
//         // memcpy(new)
//     }
//     else {
//        h += 1; 
//     }
//     return h;

// }
// void* dyna_init(size_t item_size, size_t capacity, LSEArena* arena ){
//     void* ptr = 0;
//     size_t size = item_size * capacity + sizeof(DYNA_HEADER);
//     DYNA_HEADER *h = arena_alloc(arena, size);
//     if(h){
//         h->capacity = capacity;
//         h->size = 0;
//         h->arena = arena;
//         ptr = h + 1;
//     }
//     return ptr;
// }
// //todo append
// typedef struct DYNA_HEADER
// {
//     size_t capacity;
//     size_t size;
//     LSEArena* arena;
// } DYNA_HEADER;






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
