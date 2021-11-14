#include "fattylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* GetLine(char* head){
    return NULL;    
}

char* GetFilesLines(FILE* fp){
    long filelen=0;
    char* lines;

    fseek(fp,0,SEEK_END); 
    filelen=ftell(fp);
    lines=(char*)malloc(sizeof(char)*(filelen+1)); 
    fseek(fp,0,SEEK_SET);
    fread(lines,filelen,sizeof(char),fp); 
    *(lines+filelen)='\0';

    return lines;
}

char* Strip(char* ptr,char ch){
    char* start=ptr;
    int len=0;
    int startptr=0;
    int endptr;

    len = strlen(ptr);
    endptr = len-1;
    while(*start==ch){
        if(*start=='\0'){
            return NULL;
        }
        startptr++;
        start=ptr+startptr;
    }
    while(*(ptr+endptr)==ch){
        *(ptr+endptr) = '\0';
        endptr --;
    }
    
    return start;
}

char* Format(char* str){
    long len;
    long i;
    char* new;
    short comment=0;
    long index=0;
    int count=0;

    len = strlen(str);
    new = (char*)malloc((len+1)*sizeof(char));
    for(i=0;i<len;i++){
        if(*(str+i)=='/'){
            comment = 1;
            continue;
        }else if(*(str+i)=='\n'){
            comment = 0;
            continue;
        }
        if(comment==0&&*(str+i)!='\r'&&*(str+i)!='\n'&&*(str+i)!=' '){
            *(new+index) = *(str+i);
            index ++;
        }
        else ;

        if(*(str+i)=='=') count ++;
        else if(*(str+i)==';') count --;
        else ;
    } 
    if(count){
        printf("please input a string which start with'assign' and with end with ';'");
        exit(1);
    }
    *(new+index) = '\0';

    return new;
}

/*initial*/
int InitElement(char* str,node **head){
    node* node_index;
    node* node_tmp;
    long ch_index=6;

    *head = GetANode(str,&ch_index);
    node_index = *head;
    node_index->nxt = NULL;
    //PrintNode(node_index);

    while(*(str+ch_index)!='\0'&&*(str+ch_index+1)!='\0'){
        if(*(str+ch_index)==';'){
            ch_index +=7;
            node_tmp = GetANode(str,&ch_index);
            node_index->nxt = node_tmp;
            node_index = node_tmp;
            node_index->nxt = NULL;
        }
    }
    PrintNode(*head);
    return 1;
}

node *GetANode(char* str,long*  ch){
    node* head;
    branch* branch_index;
    branch* branch_tmp;

    head = (node*)malloc(sizeof(node));
    char* name_tmp=str+*ch;
    unsigned int name_len = GetNameLen(str,ch);
    head->name = (char*)malloc((name_len+1)*sizeof(char));
    memcpy(head->name,name_tmp,name_len);
    *(head->name+name_len) = '\0';
    *ch = *ch+1;
    head->branch_start = GetAllBranch(str,ch);

    return head;
}
branch* GetAllBranch(char* str,long* ch){
    branch* branchhead=(branch*)malloc(sizeof(leaf));
    branch* tmp;
    branch* index=branchhead;
     
    branchhead->leaf_start = GetAllLeaf(str,ch);
    branchhead->nxt = NULL;
    while(*(str+*ch)!=';'){
        if(*(str+*ch)=='|'){
            *ch = *ch+1;
        }
        tmp = (branch*)malloc(sizeof(branch));
        index->nxt = tmp;
        index = tmp;
        index->leaf_start = GetAllLeaf(str,ch);
        index->nxt = NULL;
    }

    return branchhead;
}
int GetNameLen(char *a,long* ch){
    int len=0;
    while(*(a+*ch+len)!='='){
        len ++; 
    }
    *ch = *ch+len;
    return len;
}

static int count_node=0;
static int count_branch=0;
static int count_leaf=0;

void PrintNode(node* h){
    node* index=h;

    while(index!=NULL){
        PrintBranch(index->branch_start);
        index = index->nxt;
        count_node ++;
    }
}
void PrintBranch(branch* br){
    branch* index=br;

    while(index!=NULL){
        PrintLeaf(index->leaf_start);
        index = index->nxt;
        count_branch ++;
    }
}
void PrintLeaf(leaf* l){
    leaf* index=l;

    while(index!=NULL){
        printf("%dth node %dth branch %dth leaf's name is %s\n",count_node,count_branch,count_leaf,index->pr);
        printf("%dth node %dth branch %dth leaf's set is %c\n",count_node,count_branch,count_leaf,index->set);
        printf("%dth node %dth branch %dth leaf's offset is %d\n",count_node,count_branch,count_leaf,index->offset);
        count_leaf ++;
        index = index->nxt;
    }

}

leaf* GetALeaf(char* str,long* ch){
    int leaflen;
    leaf* aleaf=(leaf*)malloc(sizeof(leaf));
    aleaf->set = '1';
    if(*(str+*ch)=='!'||*(str+*ch)=='~'){
        aleaf->set = '0';
        *ch = *ch+1;
    }
    leaflen = GetALeafLen(str+*ch);
    aleaf->pr = (char*)malloc((leaflen+1)*sizeof(char));
    memcpy(aleaf->pr,str+*ch,leaflen);
    *(aleaf->pr+leaflen) = '\0';
    aleaf->offset = 0;
    aleaf->nxt = NULL;
    *ch = *ch+leaflen;


    if(*(str+*ch)=='['){
        *ch = *ch+1;
        while(*(str+*ch)!=']'){
            aleaf->offset = aleaf->offset*10+*(str+*ch)-'0';
            *ch = *ch+1;
        }
        *ch = *ch+1;
    }
    
    return aleaf;
}

leaf* GetAllLeaf(char* str,long* ch){
    unsigned int i=0;
    leaf* tmp;
    leaf* leafhead=NULL; 
    leaf* index =leafhead;
    int leaflen=0;

    leafhead = GetALeaf(str,ch);
    index = leafhead;
    while(*(str+*ch)!='|'){
        if(*(str+*ch)=='&'){
            *ch = *ch+1;
            tmp = GetALeaf(str,ch);
            index->nxt = tmp;
            index = tmp;
        }else if(*(str+*ch)==';') {
            break;
        }
    }
    return leafhead;
}

int GetALeafLen(char* ch){
    int len=0;

    while(*(ch+len)>='0'&&*(ch+len)<='9'
        ||*(ch+len)>='a'&&*(ch+len)<='z'
        ||*(ch+len)>='A'&&*(ch+len)<='Z'
        ||*(ch+len)=='_'){
        len ++;
    }
    return len;
}