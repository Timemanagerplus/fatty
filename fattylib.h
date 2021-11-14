#ifndef __FATTYLIB_H__
#define __FATTYLIB_H__

#include <stdio.h>

typedef struct LEAF{
    char *pr;
    char set;
    struct LEAF* nxt;
    int offset;
}leaf;

typedef struct BRANCH{
    leaf* leaf_start;
    struct BRANCH* nxt;
}branch;

typedef struct NODE{
    char* name;
    branch* branch_start;
    struct NODE* nxt; 
}node;

char* GetLine(char* head);
char* GetFilesLines(FILE* fp);
char* Strip(char* ptr,char ch);
char* Format(char* str);
int InitElement(char* str,node **head);
int GetNameLen(char *a,long* ch);
node* GetANode(char* str,long* ch);
void PrintNode(node* h);
leaf* GetALeaf(char* str,long* ch);
leaf* GetAllLeaf(char* str,long* ch);
int GetALeafLen(char* ch);
void PrintLeaf(leaf* l);
void PrintBranch(branch* br);
branch* GetAllBranch(char* str,long* ch);
#endif