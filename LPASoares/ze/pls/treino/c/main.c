#include <stdlib.h>
#include <stdio.h>
void readInput();
void printOrderedGuests(int *guestList, int size);

int main(){
    readInput();
    return 0;
}

int compareDecreasing (const void * a, const void * b) {
   return ( *(int*)b - *(int*)a );
}

void calculateDifference(int *guestList, int size){
    int i;
    for(i=0; i < size-1; i++){
        int j=i+1;
        int k= size-1;
        while(j!=k){
            if(guestList[i]+guestList[j]+guestList[k]==0){
                printf("Fair\n");
                return ;
            }
            else if(guestList[i]+guestList[j]+guestList[k]>0){
                j++;
            }
            else{
                k--;
            }
        }   
    }
    printf("Rigged\n");
    return ;
}

void sortGuests(int *guestList, int size){
    qsort(guestList, size, sizeof(int), compareDecreasing);
    
}

void printOrderedGuests(int *guestList, int size){
    int j;
    for(j=0; j < size; j++){
            printf("Guestlist[%d]: %d\n",j,guestList[j]);
    }   
}
void readInput(){
    int size;
    int i;
    while(scanf("%d", &size) == 1)
	{
	    int guestList[size];
        for(i = 0; i < size; i++){
            scanf("%d",&guestList[i]);
        }
        sortGuests(guestList,size);
        calculateDifference(guestList,size);
        scanf("%d", &size);
    }
}