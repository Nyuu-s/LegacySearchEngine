
#include <stdio.h>

#define KB(x) ((unsigned long long)1024 * x)
#define MB(x) ((unsigned long long)1024 * KB(x))
#define GB(x) ((unsigned long long)1024 * MB(x))
#define KBSIZE KB(1)
#define MBSIZE MB(1)
#define GBSIZE GB(1)

#define MAX_OPEN_FILESIZE MB(500)

void load_file_in(char* file_path, void* out){
    
    FILE* fd = fopen(file_path, "r");
    if(fd == NULL){
        printf("Couldn't open file");
        return;
    }
    fseek(fd, 0, SEEK_END);
    long size = ftell(fd);
    fclose(fd);

    if(size < MAX_OPEN_FILESIZE){
        printf("%lld Small file: read all in memory", size/KBSIZE);
    } 
    else
    {
        printf("%lld Large file: read in blocs", size/KBSIZE);
    }
    

}