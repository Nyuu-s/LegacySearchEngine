#include <stdio.h>
#include "LSE.h"
#include <stdlib.h>

#define READ_CHUNK_SIZE KB(1)

typedef enum GTokenType{
    RULE_NAME,
    TERMINAL,
    NON_TERMINAL,
    PUNCTUATION
} GTokenType;
//grammar token
typedef struct GToken
{
    char* value;
    GTokenType type;
    
} GToken;


int main()
{

    ERROR_LOG("TEST ERR");
    LSEArena* filearena = arena_create(KB(10));
    LSEFileHandle file = open_file_handle("E:/Projects/C/LegacySearchEngine/src/parsing/LR1/grammar.gmr");
    char* readBufferWindow = arena_alloc(filearena, READ_CHUNK_SIZE);
    if(readBufferWindow == NULL){
        printf("Failed to allocate memory");
        return 1;
    }
    LSEArena* tokens_mem = arena_create(KB(10));
    char* tokens = dyna_init(tokens_mem, 200, sizeof(GToken));

    size_t bytesRead = 0;
    unsigned long buffer_cursor = 0;
    while((bytesRead = read_bufferchunk(&file, readBufferWindow, READ_CHUNK_SIZE)) != 0){
        INFO_LOG("Reading chunk: %s", readBufferWindow);
        for (size_t i = 0; i < bytesRead; i++)
        {
            //lexer
        }
    }
   

}