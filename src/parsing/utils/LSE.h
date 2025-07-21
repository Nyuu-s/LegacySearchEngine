#ifndef LSE_H
#define LSE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
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
#define BASE_FILENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define LSELOGMSG(level,format,  ...)  log_message(level, BASE_FILENAME, __LINE__, format, ##__VA_ARGS__)                        


static void log_message(const char* level, const char* file, int line, const char* format, ...) {

    char timebuffer[10];                                        
    char msgbuffer[1024];
    time_t now = time(NULL);                                
    struct tm *local = localtime(&now);                     
    strftime(timebuffer, sizeof(timebuffer), "%H:%M:%S", local); 
    
    va_list args;
    va_start(args, format);
    vsnprintf(msgbuffer, sizeof(msgbuffer), format, args);
    va_end(args);
    
    printf("[%s] %s:%d - %s: %s\n",timebuffer,file, line, level, msgbuffer);           
}

#define ERROR_LOG(format, ...) LSELOGMSG("ERROR",format, ##__VA_ARGS__)
#define WARNING_LOG(format, ...) LSELOGMSG("WARNING", format, ##__VA_ARGS__)
#define INFO_LOG(format, ...) LSELOGMSG("INFO", format, ##__VA_ARGS__)
#define LSE_ASSERT(condition, format, ...)                  \
do{                                                     \
    if (!(condition))                                   \
    {                                                   \
        LSELOGMSG("ASSERTION FAILED", format, ##__VA_ARGS__);        \
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
    LSE_ASSERT(arena, "Arena creation failed, probably a malloc failure");
    if (!arena) { return NULL; }
    arena->data = (char*) (arena + 1);
    arena->capacity = size;
    arena->offset = 0;
    memset(arena->data, 0, size);

    return arena;
}

void* arena_alloc(LSEArena* arena, size_t size){
    LSE_ASSERT(arena, "Cannot allocate in a NULL arena");
    if (!arena) { return NULL; }
    size_t aligned_size  = (size + 7) & ~7;
    if(arena->offset + aligned_size > arena->capacity){
        LSE_ASSERT(0, "Arena is full !");
        return NULL;
    }
    void* result = arena->data + arena->offset;
    arena->offset += aligned_size;
    return result;
}

void arena_release(LSEArena* arena)
{
    LSE_ASSERT(arena, "Cannot free a NULL arena");
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
    LSE_ASSERT(arena, "Cannot initilize a dynamic array with a NULL arena");
    if(!arena) {return NULL;}
    LSE_ASSERT(item_size > 0, "Item size should not be 0 when calling dyna_init!");
    if (item_size == 0) { return NULL; }

    if(capacity == 0) {capacity = DYNA_INITIAL_CAPACITY;}
    LSEDYNA* res = (LSEDYNA*) arena_alloc(arena, (capacity * item_size) + sizeof(LSEDYNA));
    LSE_ASSERT(res, "Arena allocation failed in dyna_init !");
    if(!res){return NULL;}
    res->capacity = capacity;
    res->length = 0;
    res->region = arena;
    res->data = res + 1;
    return res->data;
}

void dyna_free(void* arr_data) {
    LSE_ASSERT(arr_data, "NULL has been passed to dyna_free");
    if (!arr_data) { return; }
    LSEDYNA* array = ((LSEDYNA*) arr_data) - 1;
    arena_release(array->region);
}

void* dyna_append_item(void* arr_data, void* ptr_item, size_t item_size){
    LSE_ASSERT(arr_data, "Cannot append to a NULL array");
    LSE_ASSERT(ptr_item, "Cannot append a NULL item to the array");
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
        LSE_ASSERT(array->region, "The region pointer in the array is NULL");
        if(!array->region) {return NULL;}
        size_t new_size = sizeof(LSEDYNA) + new_cap * item_size;
        if(array->region->capacity < new_size){
            LSEArena* new_arena = arena_create(new_size);
            LSE_ASSERT(new_arena, "Failed to create a new arena in dyna_append_item");
            if(!new_arena){return NULL;}
            LSEDYNA* new_arr = (LSEDYNA*) arena_alloc(new_arena, new_size);
            LSE_ASSERT(new_arr, "Failed to allocate new size in the new arena in dyna_append_item");
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

typedef struct StringBuilder{
    void* data;
    size_t capacity;
    size_t length;
    LSEArena* region;
} StringBuilder;

StringBuilder* sb_init(size_t initial_capacity){
    LSEArena* region = arena_create(sizeof(StringBuilder)+(initial_capacity+1) * sizeof(char));
    LSE_ASSERT(region ,"error stringbuilder");
    if(!region){
        ERROR_LOG("error sb");
        return;
    }
    StringBuilder* sb = arena_alloc(region, sizeof(StringBuilder));
    LSE_ASSERT(sb, "error allocate sb");
    if(!sb){
        ERROR_LOG("error allocate sb");
        return;
    }
    sb->data = sb+1;
    sb->length = 0;
    sb->capacity = initial_capacity;
    sb->region = region;
    return sb;
}

void sb_free(StringBuilder* sb){
    arena_release(sb->region);
}

void sb_append_char(StringBuilder* sb, char c){
    if(sb->length >= sb->capacity){
        size_t new_cap = sb->capacity * 2;
        char* new_data = arena_alloc(sb->region, new_cap * sizeof(char));
        if(!new_data){
            WARNING_LOG("Sb arena is full copying all to new arena");
            StringBuilder* new_sb = sb_init(sizeof(StringBuilder) + (new_cap+1) * sizeof(char));
            LSE_ASSERT(new_sb, "error when sb full new region failed");
            memcpy(new_sb, sb->data, sb->length * sizeof(char));
            new_sb->length = sb->length;
            sb_free(sb);
            sb = new_sb;
        } else{
            memcpy(new_data, sb->data, sb->length * sizeof(char));
            sb->data = new_data;
            sb->capacity = new_cap;
        }
        sb->data[sb->length++] = c;
    }
}


char* sb_to_string(StringBuilder* sb, LSEArena* region){
    char* str = arena_alloc(region, (sb->length+1) * sizeof(char));
    memcpy(str, sb->data, sb->length * sizeof(char));
    str[sb->length+1] = '\0';
    sb->length = 0;
    return str;
}
// #############################
// #		File IO
// #############################

struct LSEFileHandle
{
    FILE* descriptor;
    unsigned long offset;
    unsigned long size;

}typedef LSEFileHandle;

LSEFileHandle open_file_handle(char* file_path){
    LSEFileHandle file = {0};
    FILE* fd = fopen(file_path, "rb");
    LSE_ASSERT(fd, "Failed to open file %s !", file_path);
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
#endif