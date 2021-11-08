#include <stdio.h>
#include <string.h>
#include "fattylib.h"

int main(void){
    FILE* fp;
    char* alllines;

    fp = fopen("template.in","rb");
    alllines = GetFilesLines(fp);
    printf("%s",alllines);

    return 0;
}