/* 20220314 reverseV2.c */
/* https://www.geeksforgeeks.org/reverse-a-linked-list/ */
/* Ylläolevasta linkistä haettua apua joka näkyy riveillä 97-103 */
/* */
/* https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input */
/* Ylläolevasta linkistä haettua apua kuinka poistaa rivinvaihtomerkki */
/* Tämä näkyy rivillä 66 */



#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 50
#define MAX 200

typedef struct list{
    char line[MAXLEN];
    struct list *pNext;
}LIST;

LIST *readToLinkedList(LIST *pH, char* file);
LIST *inReverseOrder(LIST *pH);
LIST *freeMemory(LIST *pH);



int main(int argc, char * argv[]){
    LIST* pHead=NULL;

    if(argc>1){

        if(argc==2){
            printf("Reading file '%s' to linked list.\n\n",argv[1]);
            pHead=readToLinkedList(pHead,argv[1]);
            inReverseOrder(pHead);
            pHead=freeMemory(pHead);
        }if(argc>2){    
            printf("You gave too many arguments.\n");
        }
    }else
        printf("You didn't gave enough arguments.\n");

    return(0);

}
LIST *readToLinkedList(LIST *pHead,char* file){
    LIST *pNew,*ptr;
    char row[MAX];

    FILE *readFile;
    
    //Opens file
    if((readFile=fopen(file,"r"))==NULL){
        fprintf(stderr,"Error: cannot  open file '%s",file);
        exit(1);
    }
    //Reads file to linked list
    while(fgets(row,MAX,readFile)!=NULL){
        if((pNew=(LIST *)malloc(sizeof(LIST)))==NULL){
            fprintf(stderr,"Malloc failed.");
            exit(1);
        }
        //Removes newline character 
        row[strcspn(row,"\n")]=0;
        strcpy(pNew->line,row);
  
        pNew->pNext=NULL;
        if(pHead==NULL){
            pHead=pNew;
        }else{
            ptr=pHead;
            while(ptr->pNext!=NULL)
                ptr=ptr->pNext;
            ptr->pNext=pNew;
        }

    }
    printf("This is before reverse.\n");

    LIST *pTemp = pHead;
    while(pTemp!=NULL){
        printf("%s\n",pTemp->line);
        pTemp=pTemp->pNext;
    }
    printf("\n");
    
    fclose(readFile);
    return pHead;
}
//Makes linked list in reverse order
LIST *inReverseOrder(LIST *pHead){

    LIST *pPrev=NULL,*pCurrent=pHead,*pNext=NULL,*ptr;
    printf("This is after reverse.\n");
    while(pCurrent!=NULL){
        pNext=pCurrent->pNext;
        pCurrent->pNext=pPrev;
        pPrev=pCurrent;
        pCurrent=pNext;
    }
    pHead=pPrev;

    ptr=pHead;
    while(ptr != NULL){
        printf("%s\n",ptr->line);
        ptr=ptr->pNext;
    }
    return pHead;
}
//Frees memory
LIST *freeMemory(LIST *pH){
    LIST *ptr=pH;
    while(ptr!=NULL){
        pH=ptr->pNext;
        free(ptr);
        ptr=pH;
    }

    return pH;
}



/* eof */