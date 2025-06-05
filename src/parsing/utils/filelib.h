
#include <stdio.h>

#define ASKB(k) k/1024
#define ASMB(k) ASKB(k)/1024
#define ASGB(k) ASMB(k)/1024

#define KB(k) k*1024
#define MB(k) KB(k)*1024
#define GB(k) MB(k)*1024

#define MAX_OPEN_FILESIZE MB(500)

void open_file(char* file_path){
    
    FILE* fd = fopen(file_path, "r");
    if(fd == NULL){
        return;
    }
    fseek(fd, 0, SEEK_END);
    long size = ftell(fd);
    fclose(fd);

    if(size < MAX_OPEN_FILESIZE){
        printf("Small file: load all in memory");
    } 
    else
    {
        printf("%ld Large file: read in blocs", KB(size));
    }
    

}