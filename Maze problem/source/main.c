#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1

int main(int argc,char* argv[])
{
    char line[100];
    int count=0,n=0;
    int o,u,z,e,d;
    char c;

    FILE *file;
    file = fopen(argv[1], "r");  /// i open file
    if (file != NULL)
    {
        while( fgets(line, sizeof line, file) != NULL )
        {
            count++;    ///i found count of line
        }
    }
    fclose(file);
    char tablo[count][count];

    file = fopen(argv[1], "r");
    if(file){
        for(o=0;o<count;o++){
            int u=0;
            for(z=0;z<count;z++){
                    fscanf(file,"%c ",&c);
                    if( c=="\n"){n++;}
                    else{tablo[n][u]=c;u++;     /// i fill matris with files data
                        }
            }
            n++;
        }
    }
    else{
        printf("Failed open the file");
    }
        fclose(file); ///Close the input file.
    int x,y;
    int deneme;
    int start;
    int a=0;
    int b=0;
    int num=0;
    char keys[20];  ///i put keys in this array
    char anahtar[25];
	for(x=0;x<count;x++){
        for(y=0;y<count;y++){
            if((tablo [x][y]>='a' &&tablo [x][y]<='z') || (tablo[x][y]>='A' &&tablo[x][y]<='Z') && tablo[x][y]!='S'&& tablo[x][y]!='E'){
                    anahtar[a]=x +'0';a++;
                    anahtar[a]=y +'0';a++;
                    anahtar[a]=tablo [x][y];a++;/// i put keys index and doors index
            }
        }
    }
    start=findStart(count,tablo);  ///  find index of start
    if ( find_path(count,tablo,0,start,keys,num) == TRUE ){  /// find true way and put '+' instead of '0'
        	///	Success!
    }
	else
		printf("\nYou could not find exit. \n");

     printf("\nStart ");
     tellTheWay(count,tablo,0,start,anahtar);  /// tell the direction as for that '+'
}
int checkKey(char door,char keys[]){     /// check is there any key suitable door
    int i;
    int intDoor=door-'0'; /// convert char to integer
    intDoor=intDoor+32;    /// convert uppercase to lowercase
    char newDoor=intDoor+'0'; ///convert integer to char
    for(i=0;i<20;i++){
        if(keys[i]==newDoor){ /// controled key and door
            return 3;
            }
     }
}
int
find_path(int count ,char tablo[][count],int x, int y,char keys[],int num)
{
	if (x<0 || x>(count-1) || y<0 || y>(count-1) ) return FALSE;  /// check matris's bounds

	if ( tablo[x][y] == 'E' ) return TRUE;   /// found the exit

	if(tablo [x][y]>='a' &&tablo [x][y]<='z' ){
        keys[num]=tablo [x][y];  /// find to key and put keys list and go on.
        tablo [x][y]='0';
        num++;
	}
	if(tablo[x][y]>='A' &&tablo[x][y]<='Z' && (checkKey(tablo[x][y],keys)==3)){
        tablo [x][y]='0';           /// if path is true,write '0'
	}
	if( tablo [x][y] != '0') return FALSE;

	tablo[x][y] = '+';       /// marked true way

	if ( find_path(count,tablo,x, y - 1,keys,num) == TRUE ) return TRUE;   ///find to north direction

	if ( find_path(count,tablo,x + 1, y,keys,num) == TRUE ) return TRUE;   ///find to east direction

	if ( find_path(count,tablo,x, y + 1,keys,num) == TRUE ) return TRUE;   ///find to south direction.

	if ( find_path(count,tablo,x - 1, y,keys,num) == TRUE ) return TRUE;   ///find to west direction.

	tablo[x][y] = '*';       ///marked false way

	return FALSE;
}

int findStart(int count ,char tablo[][count]){    /// return index of start
    int k;
    for(k=0;k<7;k++){
        if(tablo[0][k]=='S'){
            tablo[0][k]='0';
            return k;
        }
    }
}
void tellKey(int row,int column,char anahtar[]){   /// tell the key
    int k;
    char row1=row+48;
    char column1=column +48;
    for(k=0;k<25;k++){
        if(anahtar[k]==row1 && anahtar[k+1]==column1){
            printf("%c ",anahtar[k+2]);
        }
            }
}
int tellKeys(int row,int column,char anahtar[]){   ///check is key in my key list
    int k;
    char row1=row+48;
    char column1=column +48;
    for(k=0;k<25;k++){
        if(anahtar[k]==row1 && anahtar[k+1]==column1){
            return TRUE;
        }    }
}
void tellTheWay(int count,char tablo[][count],int row,int column,char anahtar[]){   /// tell the direction as for that '+'
    if(tablo[row][column+1]=='+'){
            printf("E ");
            tablo[row][column]='.';
            if(tellKeys(row,column+1,anahtar)==TRUE){
                tellKey(row,column+1,anahtar);
                }
            tellTheWay(count,tablo,row,column+1,anahtar);
        }
    else if(tablo[row+1][column]=='+'){
            printf("S ");
            tablo[row][column]='.';
            if(tellKeys(row+1,column,anahtar)==TRUE){
                tellKey(row+1,column,anahtar);
                }
            tellTheWay(count,tablo,row+1,column,anahtar);
        }
    else if(tablo[row][column-1]=='+'){
            printf("W ");
            tablo[row][column]='.';
            if(tellKeys(row,column-1,anahtar)==TRUE){
                tellKey(row,column-1,anahtar);
                }
            tellTheWay(count,tablo,row,column-1,anahtar);
        }
        else if(tablo[row-1][column]=='+'){
            printf("N ");
            tablo[row][column]='.';
           if(tellKeys(row-1,column,anahtar)==TRUE){
                tellKey(row-1,column,anahtar);
                }
            tellTheWay(count,tablo,row-1,column,anahtar);
        }
        else if(tablo[row][column+1]=='E'){
            printf("E ");
            tablo[row][column]='.';
            printf("Exit ");
        }
        else if(tablo[row+1][column]=='E'){
            printf("S ");
            tablo[row][column]='.';
            printf("Exit ");
        }
        else if(tablo[row][column-1]=='E'){
            printf("W ");
            tablo[row][column]='.';
            printf("Exit ");
        }
        else if(tablo[row-1][column]=='E'){
            printf("N ");
            tablo[row][column]='.';
            printf("Exit ");
        }
}
