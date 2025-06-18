#include <stdio.h>
#include "LSE.h"
#include <stdlib.h>

#define READ_CHUNK_SIZE KB(1)

int main()
{

    LSEArena filearena = arena_create(KB(10));
    LSEFileHandle file = open_file_handle("E:/Projects/C/LegacySearchEngine/src/parsing/LR1/grammar.gmr");
    char* readBufferWindow = arena_alloc(&filearena, READ_CHUNK_SIZE);

    size_t eof = 0;
    while((eof = read_bufferchunk(&file, readBufferWindow, READ_CHUNK_SIZE)) != 0){
        printf("Reading chunk: %s", readBufferWindow);
    }

    
    printf("read done");
    


}