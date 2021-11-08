#include "fattylib.h"
#include <stdlib.h>
#include <stdio.h>

char* GetLine(char* head){
    return NULL;    
}

char* GetFilesLines(FILE* fp){
    int filelen=0;
    char* lines;

    fseek(fp,0,SEEK_END); 
    filelen=ftell(fp);
    lines=(char*)malloc(sizeof(char)*(filelen+1)); 
    fseek(fp,0,SEEK_SET);
    fread(lines,filelen,sizeof(char),fp); 
    *(lines+filelen)='\0';

    return lines;
}

char* Strip(char* ptr,char* str){
    
}