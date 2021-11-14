#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fattylib.h"

int main(void){
    FILE* fp;
    char* alllines;
    node *head;

    printf("hello");
    fp = fopen("template.in","rb");
    alllines = GetFilesLines(fp);
    char* handle = Strip(alllines,' ');
    printf("%s\n",handle);
    char* new = Format(handle);
    printf("convert is:%s\n",new);
    InitElement(new,&head);

    return 0;
}
