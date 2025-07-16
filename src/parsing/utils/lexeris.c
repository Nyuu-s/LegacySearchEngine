#include <stdio.h>
#include "LSE.h"
#include <stdlib.h>

#define READ_CHUNK_SIZE KB(1)

int main()
{

    ERROR_LOG("TEST ERR");
    LSEArena* filearena = arena_create(KB(10));
    LSEFileHandle file = open_file_handle("E:/Projects/C/LegacySearchEngine/src/parsing/LR1/gramkmar.gmr");
    // char* readBufferWindow = arena_alloc(&filearena, READ_CHUNK_SIZE);
    // if(readBufferWindow == NULL){
    //     printf("Failed to allocate memory");
    //     return -1;
    // }
    // size_t eof = 0;
    // while((eof = read_bufferchunk(&file, readBufferWindow, READ_CHUNK_SIZE)) != 0){
    //     printf("Reading chunk: %s", readBufferWindow);
    // }
    // double *p;


    // WARNING_LOG("TEST WARN");
    // INFO_LOG("TEST INFO");

    // int a = 1;
    // LSE_ASSERT(a == 6, "a should be 6");
    
    printf("read done");
    


}