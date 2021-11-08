#ifndef __FATTYLIB_H__
#define __FATTYLIB_H__

#include <stdio.h>

typedef struct LINEHEAD{
    char* str;
    struct LINEHEAD* nxt;
}linehead;

char* GetLine(char* head);
char* GetFilesLines(FILE* fp);
char* Strip(char* ptr,char* str);
#endif