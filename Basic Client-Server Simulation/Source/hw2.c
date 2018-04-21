#include <stdio.h>
#include <stdlib.h>
typedef struct {
        char *queue;
        char *stack;
        int rear;
        int front;
        int q_size;
        int s_size;
        int stack_indice;
        char *history;
        int hist;

    }data;
///**************************       Stack       ********************************

int isEmptyStack(char *stack,int *stack_indice){        //check is stack empty
    if(*stack_indice==-1){
      return 1;
    }
    else
        return 0;
}

int pop(char *stack,int *stack_indice){     // delete last element from stack
        char sent =(*(stack+  (*stack_indice)   ));
        int send=sent - '0';
        (*stack_indice)--;
        return send;
}

int push(char *stack,int *stack_indice,char eleman,int *s_size){        //add new element to stack's end
    if((*stack_indice)==(*s_size)-1){
        return 0;
    }
    else{
        (*stack_indice)++;
        *(stack+(*stack_indice))=eleman;
        return 1;
    }
}

///**************************       Queue      ********************************

int dequeue(char *queue,int *front,int *rear,int *q_size ){     //delete first element from queue
    char ele;
    int element;
    ele=*(queue+(*front));
    element=ele -'0';
    if(*front == *rear){
        *front=-1;
        *rear=-1;
    }
    else{
        *front=((*front)+1) % *q_size;
    }
    return element;
}

int isEmptyQueue(int *front,int *rear,int *q_size){     //check is queue empty
    if(*front == -1){
        return 1;
    }
    else
        return 0;
}

int isFullQueue(int *front,int *rear,int *q_size){      //check is queue full
    if((*front ==((*rear)+1)) || (*front == 0 && *rear == ((*q_size)-1))){
        return 0;
    }
    else{
        return 1;
    }
}

int enqueue(char *queue,int *front,int *rear,char eleman,int *q_size){      //add new element to last in queue
  if((*front ==((*rear)+1)) || (*front == 0 && *rear == ((*q_size)-1))){
    return 0;
    }
  else{
    if(*front==-1){*front=0;}
    *rear=((*rear)+1) % *q_size;
    *(queue+(*rear))=eleman;
    return 1;
  }
}

void write(char *history,int *hist,char deger){      //write history to element's history list
    *(history+(*hist))=deger;
    (*hist)++;
}

int main(int argc,char* argv[])
{
    FILE* fp1;
    fp1 = fopen(argv[1], "r");     //open file to read
    FILE* fp2;
    fp2 = fopen(argv[2], "r");     //open file to read
    FILE* fp3;
    fp3 = fopen(argv[3], "w");     //open file to write
    char line[250];
    char line1[250];
    int n=0;
    int num=0;
    int queueSize;
    int stackSize;
    int serverQueue;
    int serverStack;

    int itemNum;
    fscanf(fp1,"%d ",&itemNum);     //take first line in first input

    data* client;                   //describe pointer from struct
    data* server;
    client =(data*)malloc((itemNum-1)*sizeof(data));      //create area for pointer array
    server =(data*)malloc(1*sizeof(data));

    int i;
    for(i=0;i<itemNum-1;i++){
        fscanf(fp1,"%d %d ",&queueSize,&stackSize);     //read inside to first input and take like queue size and stack size
        client[num].q_size=queueSize;
        client[num].s_size=stackSize;
        client[num].queue=(char*)malloc(queueSize*sizeof (char));
        client[num].stack=(char*)malloc(stackSize*sizeof (char));
        client[num].history=(char*)malloc(1000*sizeof (char));
        client[num].stack_indice=-1;
        client[num].front=-1;
        client[num].rear=-1;
        client[num].hist=0;
        num++;
    }

    fscanf(fp1,"%d %d\n",&serverQueue,&serverStack);       //read inside to first input and take like queue size and stack size
    server[0].q_size=serverQueue;
    server[0].s_size=serverStack;
    server[0].queue=(char*)malloc(serverQueue*sizeof (char));
    server[0].stack=(char*)malloc(serverStack*sizeof (char));
    server[0].history=(char*)malloc(1000*sizeof (char));
    server[0].stack_indice=-1;
    server[0].front=-1;
    server[0].rear=-1;
    server[0].hist=0;

    int satir;
    fscanf(fp2,"%d ",&satir);       //read inside to input 2

    char ilk;
    char ben;
    char ucuncu;
    for(i=0;i<satir;i++){
        fscanf(fp2,"%c %c %c ",&ilk,&ben,&ucuncu);

        if(ilk == 'A'){             //send that is last element in input to enqueue
            int ikinci=ben -'0';
            if(ikinci!=itemNum){
                if(enqueue(client[ikinci-1].queue,&client[ikinci-1].front,&client[ikinci-1].rear,ucuncu,&client[ikinci-1].q_size)==1){

                }
                else{
                    write(client[ikinci-1].history,&client[ikinci-1].hist,'1');
                }
            }
        }

        if(ilk== 'I'){
            int ikinci=ben -'0';
            if(ikinci==itemNum ){
                if(push(server[0].stack,&server[0].stack_indice,ucuncu,&server[0].s_size)==1){//check is stack full and send push function

                }
                else{
                    write(server[0].history,&server[0].hist,'2');
                }
            }
            else{
                if(push(client[ikinci-1].stack,&client[ikinci-1].stack_indice,ucuncu,&client[ikinci-1].s_size)==1){//check is stack full and send push function

                }
                else{
                    write(client[ikinci-1].history,&client[ikinci-1].hist,'2');
                }
            }
        }

        if(ilk== 'S'){
            int ikinci=ben -'0';
            if(isEmptyStack(client[ikinci-1].stack,&client[ikinci-1].stack_indice)==0){  //check is stack empty and send enqueue
                    char gonder =(pop(client[ikinci-1].stack,&client[ikinci-1].stack_indice)) +'0';
                    write(client[ikinci-1].history,&client[ikinci-1].hist,gonder);
                    if(isFullQueue(&server[0].front,&server[0].rear,&server[0].q_size)==1){
                        enqueue(server[0].queue,&server[0].front,&server[0].rear,gonder,&server[0].q_size); // check is queue full
                    }
                    else{
                        write(server[0].history,&server[0].hist,'1');
                    }

            }
            else{
                if(isEmptyQueue(&client[ikinci-1].front,&client[ikinci-1].rear,&client[ikinci-1].q_size)==0){
                    char gonder1 =(dequeue(client[ikinci-1].queue,&client[ikinci-1].front,&client[ikinci-1].rear,&client[ikinci-1].q_size)) +'0';
                    write(client[ikinci-1].history,&client[ikinci-1].hist,gonder1);
                    if(isFullQueue(&server[0].front,&server[0].rear,&server[0].q_size)==1){
                        enqueue(server[0].queue,&server[0].front,&server[0].rear,gonder1,&server[0].q_size); // check is queue full
                    }
                    else{
                        write(server[0].history,&server[0].hist,'1');
                    }
                }
                else{
                    write(client[ikinci-1].history,&client[ikinci-1].hist,'3');
                }
            }
        }

        if(ilk== 'O'){
            if( isEmptyStack( server[0].stack,&server[0].stack_indice)==0){
                char sonuc = ( pop(server[0].stack,&server[0].stack_indice)) + '0';
                write(server[0].history,&server[0].hist,sonuc);
            }
            else{
                if(isEmptyQueue(&server[0].front,&server[0].rear,&server[0].q_size)==0){
                    char go =(dequeue(server[0].queue,&server[0].front,&server[0].rear,&server[0].q_size)) +'0';
                    write(server[0].history,&server[0].hist,go);
                }
                else{
                    write(server[0].history,&server[0].hist,'3');
                }
            }
        }
    }

    int r;
    for(r=0;r<itemNum-1;r++){       //read client history
        int i;
        for(i=0;i<client[r].hist;i++){
            char name =*(client[r].history+i);
            printf("%c ",name);
            fputc(name,fp3);
            fprintf(fp3," ");
        }
        printf("\n");
        fprintf(fp3,"\n");
    }
    int t;
        for(t=0;t<server[0].hist;t++){      //read server history
            char name =*(server[0].history+t);
            printf("%c ",name);
            fputc(name,fp3);
            fprintf(fp3," ");
        }
        printf("\n");
        fprintf(fp3,"\n");

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);

}
