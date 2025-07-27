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
    GToken* tokens = dyna_init(tokens_mem, 200, sizeof(GToken));

    
    size_t bytesRead = 0;
    unsigned long buffer_cursor = 0;
    while((bytesRead = read_bufferchunk(&file, readBufferWindow, READ_CHUNK_SIZE)) != 0){
        INFO_LOG("Reading chunk: %s", readBufferWindow);

        StringBuilder* sb = sb_init(100);
        GToken t = {};
        for (size_t i = 0; i < bytesRead; i++)
        {
            if (readBufferWindow[i] != ' ')
            {
                sb_append_char(sb, readBufferWindow[i]);
            }
            else
            {
                t.value = sb_to_string(sb, filearena);
                dyna_append_item(tokens, &t, sizeof(GToken));
                memset(&t, 0, sizeof(GToken));
                
            }
        }
        t.value = sb_to_string(sb, filearena);
        dyna_append_item(tokens, &t, sizeof(GToken));
       
    }
    for (size_t i = 0; i < 4; i++)
    {
        printf("%s", tokens[i].value);
    }
    
   

}