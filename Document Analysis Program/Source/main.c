#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define NULL -1
struct Second{
    char secondWord[30];
    struct Second* link;
    int secondCount;
};
struct Node{
    char word[30];
    struct Node* next;
    struct Node* liste;
    int count;
    struct Second ikinci;
};

void similarity(struct Node *head,struct Node *head2,char array[20][20]){
    int q,w,s,k,esit;
    int y=10;
    struct Node* temp=head;
    struct Node* temp2=head2;
    struct Node* temp3=head;
    struct Node* degisken=head;
    struct Node* degisken2=head2;
    for(q=0;q<10;q++){
        strcpy(array[q],temp->word);
        temp=temp->next;
    }
    esit=0;
    for(k=0;k<10;k++){
        for(s=0;s<10;s++){
            if(strcmp(array[s],temp2->word)==0){
                esit++;
            }
        }
        if(esit!=0){
            temp2=temp2->next;
            esit=0;
        }
        else{
            strcpy(array[y],temp2->word);
            esit=0;
            y++;
            temp2=temp2->next;
        }
    }

        for(w=0;w<y;w++){


        }

    char matrix[3][y+1][20];
    int f,j;
    char degis;
    *matrix[1][0]='d1';
    *matrix[2][0]='d2';
    for(f=1;f<y+1;f++){
        strcpy(matrix[0][f],array[f-1]);
    }

    for(j=1;j<y+1;j++){
            if(j<11){
                if(degisken->next==NULL){
                    *matrix[1][j]='0';

                }
                else{
                    degis=degisken->count +'0';
                    *matrix[1][j]=degis;
                    degisken=degisken->next;
                    }
            }
            else{
                *matrix[1][j]='0';
            }
    }

    struct Node* bas2=head2;
    char yaz;
    int var=0;
    for(k=0;k<y;k++){
        degisken2=bas2;
        while(degisken2->next!=NULL){
            if(strcmp(array[k],degisken2->word)==0){
                //kontrol++;
                yaz=degisken2->count +'0';
                *matrix[2][k+1]=yaz;
                break;

            }
            else{
                degisken2=degisken2->next;
                *matrix[2][k+1]='0';
            }
        }
        if(degisken2->next==NULL){
            if(strcmp(array[k],degisken2->word)==0){
                yaz=degisken2->count +'0';
                *matrix[2][k+1]=yaz;
            }
            else{
                *matrix[2][k+1]='0';
            }
        }
    }


    for(f=1;f<y+1;f++){
    }
    ///   SIMILARITY
    int sayim;
    int pay=0;
    int paydaA=0;
    int one;
    int two;
    for(sayim=1; sayim<y;sayim++){
            one=*matrix[1][sayim] -'0';
            two=*matrix[2][sayim] -'0';
            pay=pay+(one*two);
    }

    int bir;
    int sey;
    for(sey=1;sey<y+1;sey++){///payda A
        bir=*matrix[1][sey] - '0';

        paydaA=paydaA + (bir*bir);

    }

    int iki;
    int paydaB=0;
    int tut;
    for(tut=1;tut<y+1;tut++){///payda B
        iki=*matrix[2][tut] - '0';
        paydaB=paydaB + (iki*iki);
    }

    float sonuc=pay/(sqrt(paydaA)*sqrt(paydaB));
    printf("\nCosine Similarity of d1.txt and d2.txt is : %f \n",sonuc);


}
void ekleme(struct Node **start_ref,char data[],int countt){
    struct Node *ptr1 = (struct Node*)malloc(sizeof(struct Node));
    ptr1->count=countt;
    strcpy(ptr1->word,data);
    ptr1->next=*start_ref;
    *start_ref = ptr1;


}
void sil(struct Node **start_ref,char data[]){
    int i=0;
    struct Node *end=*start_ref;
    struct Node *ptrx=*start_ref;
    struct Node *temp=*start_ref;
    while(end!=NULL){
        if(i==0){
            if(strcmp(ptrx->word,data)==0){
                *start_ref = ptrx->next;
                i++;
                free(ptrx);
                break;
            }
            else{
                ptrx=ptrx->next;
                end=end->next;
                i++;
                }
        }
        else{
            if(strcmp(ptrx->word,data)==0){
                end=end->next;
                temp->next=end;
                free(ptrx);
                break;
            }
            else{
                ptrx=ptrx->next;
                end=end->next;
                temp=temp->next;

            }
        }


    }
}
void Insert(struct Node **head_ref,char data[],int *num)
{
    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
    struct Node *travel = *head_ref;
    if(*num!=0 )
    {
        while(travel->next!=NULL){
                if(strcmp(travel->word,data)==0){
                    travel->count++;
                    break;
                }
                else{
                      travel=travel->next;
                  }
        }
        if(travel->next==NULL){
                  if(strcmp(travel->word,data)==0){
                      travel->count++;
                  }
        else{
                    strcpy(temp->word,data);
                    temp->next = *head_ref;
                    temp->count= 1;
                    *head_ref = temp;
                    (*num)++;
                  }
              }
    }
    else{
        strcpy(temp->word,data);
        temp->next = *head_ref;
        temp->count= 1;
        *head_ref = temp;
        (*num)++;
    }
}
void Print(struct Node *head){

    struct Node* temp2=head;
    printf("List is: \n \n");
    while(temp2!=NULL){
        printf("%s %d \n", temp2->word,temp2->count);
        temp2=temp2->next;
    }
}
void Sort(struct Node *start){
    int swapped, i;
    struct Node *ptr1;
    struct Node *lptr = NULL;
    if (ptr1 == NULL)
        return;
    do
    {
        swapped = 0;
        ptr1 = start;

        while (ptr1->next != lptr)
        {
            if (ptr1->count < ptr1->next->count)
            {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}
void swap(struct Node *a, struct Node *b)
{
    int k,l,m;
    char temp1[30];
    strcpy(temp1,a->word);
    int temp = a->count;

    a->count = b->count;
    for(k=0;k<30;k++){
        a->word[k]=b->word[k];
    }
    b->count = temp;
    for(l=0;l<30;l++){
        b->word[l]=temp1[l];
    }
}
int main()
{
    struct Node* head=NULL;
    struct Node* head2=NULL;
    char array[20][20];

    printf("Enter commands: ");
    char giris[2];
    char option[20];
    char kelime[20];
    int count;

    //scanf("%s", &giris);
    while (strcmp(giris,"-q")!=0){
        scanf("%s", &giris);
        if(strcmp(giris,"-r")==0){
          //  printf("okundu ");
            scanf("%s", &option);
            if(strcmp(option,"d1.txt")==0){
                //printf("d1 i okundu: ");
                FILE *fp1;
                if((fp1=fopen(option,"r"))== NULL){
                    printf("Dosya acilamadi!\n");
                    exit(1);
                }
                int g=0;
                char kelime[30];
                while(fscanf(fp1, "%*[^A-Za-z0-9]"), fscanf(fp1, "%199[a-zA-Z0-9]", kelime) > 0){
                   // strlwr(kelime);
                    Insert(&head,kelime,&g);
                    Sort(head);
                    //Print(head);
                }
               // fclose(fp1);

            }
            else if(strcmp(option,"d2.txt")==0){
               // printf("d2 i okundu: ");
                FILE *fp2;
                if((fp2=fopen(option,"r"))== NULL){
                    printf("Dosya acilamadi!\n");
                    exit(1);
                }
                int a=0;
                char kelime2[30];
                while(fscanf(fp2, "%*[^A-Za-z0-9]"), fscanf(fp2, "%199[a-zA-Z0-9]", kelime2) > 0){
               // strlwr(kelime2);
                Insert(&head2,kelime2,&a);
                Sort(head2);
                // Print(head2);
                }
                // fclose(fp2);
            }

        }
        else if(strcmp(giris,"-a")==0){
           // printf("a komutu ");
            scanf("%s", kelime);  ///kelime
          //  printf("kelime :%s",kelime);
            scanf("%d", &count);   ///count
           // printf("count :%d",count);
            scanf("%s", &option);   ///nereye

            if(strcmp(option,"d1.txt")==0){
               // strlwr(kelime);
                ekleme(&head,kelime,count);
                Sort(head);
               // printf("d1.txt :%s",option);
                //Print(head);
            }
            else if(strcmp(option,"d2.txt")==0){
               // strlwr(kelime);
                ekleme(&head2,kelime,count);
                Sort(head2);
               // printf("d2.txt :%s",option);
                // Print(head2);
            }

        }
        else if(strcmp(giris,"-n2")==0){
          //  printf("n2 komutu ");


        }
        else if(strcmp(giris,"-d")==0){
           // printf("d komutu ");
            scanf("%s", kelime);  ///kelime
           // printf("kelime :%s",kelime);
            scanf("%s", &option);   ///nereye
            if(strcmp(option,"d1.txt")==0){
               // strlwr(kelime);
               // printf("d1.txt :%s",option);
                sil(&head,kelime);
                //Print(head);
            }
            if(strcmp(option,"d2.txt")==0){
               // strlwr(kelime);
               // printf("d2.txt :%s",option);
                sil(&head2,kelime);
                // Print(head2);
            }

        }
        else if(strcmp(giris,"-s")==0){
         //   printf("s komutu ");
            scanf("%s", &option);
            scanf("%s", &option);
            similarity(head,head2,array);
        }
    }

    return 0;

}

