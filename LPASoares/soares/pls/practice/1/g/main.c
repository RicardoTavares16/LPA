#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int arraysum(unsigned char* array, unsigned char size){
	unsigned int arraysum=0;
	while(size>0){
		arraysum+=array[--size];
	}
	return arraysum;
}

unsigned char search(unsigned char table[102][102], unsigned char r, unsigned char c){
	unsigned char leplace;
	if(r==0){
		printf("(%d,%d)", r+1, c+1);
		return 1;
	}
	leplace=table[r][c];
	table[r][c]='#';
	if(leplace=='|'){
		r--;
		if(table[r][c]=='|' && search(table,r,c)){
			printf(",(%d,%d)",r+2,c+1);
			return 1;
		}
		if(table[r][c+1]=='/' && search(table,r,c+1)){
			printf(",(%d,%d)",r+2,c+1);
			return 1;
		}
		if(c>0 && table[r][c-1]=='\\' && search(table,r,c-1)){
			printf(",(%d,%d)",r+2,c+1);
			return 1;
		}
	}
	else if(leplace=='\\'){
		if(table[r-1][c]=='/' && search(table,r-1,c)){
			printf(",(%d,%d)",r+1,c+1);
			return 1;
		}
		if(table[r][c+1]=='/' && search(table,r,c+1)){
			printf(",(%d,%d)",r+1,c+1);
			return 1;
		}
		if(c>0&&table[r][c-1]=='/' && search(table,r,c-1)){
			printf(",(%d,%d)",r+1,c+1);
			return 1;
		}
		if(c>0 && (table[r-1][c-1]=='\\' || table[r-1][c-1]=='|') && search(table,r-1,c-1)){
			printf(",(%d,%d)",r+1,c+1);
			return 1;
		}
	}
	else if(leplace=='/'){
		if( table[r-1][c] =='\\'&& search(table,r-1,c)){
			printf(",(%d,%d)",r+1,c+1);
			return 1;
		}
		if(table[r][c+1]=='\\' && search(table,r,c+1)){
			printf(",(%d,%d)",r+1,c+1);
			return 1;
		}
		if(c>0 && table[r][c-1]=='\\' && search(table,r,c-1)){
			printf(",(%d,%d)",r+1,c+1);
			return 1;
		}
		if((table[r-1][c+1]=='/' || table[r-1][c+1]=='|') && search(table,r-1,c+1)){
			printf(",(%d,%d)",r+1,c+1);
			return 1;
		}
	}
	return 0;
}

int main(int argc, char *argv[]){
	unsigned char r, c, i, emptyl;
	unsigned char buff[16];
	unsigned char table[102][102];
	unsigned int tarraysum;
	while(fgets((char*)buff,10,stdin)){
		if(buff[0]!='\n'){
			sscanf((char*)buff,"%hhu %hhu",&r,&c);
			tarraysum=35*c;
			emptyl=0;
			for(i=0;i<r;i++){
				fgets((char*)table[i],102,stdin);
				if(arraysum(table[i],c)==tarraysum){
					emptyl=1;
					break;
				}
			}
			if(!emptyl){
				emptyl=1;
				for(i=0;i<c;i++){
					if(search(table,r-1,i)){
						printf("\n");
						emptyl=0;
						break;
					}
				}

			}
			if(emptyl){
				printf("No Path!\n");
			}
		}

	}
	return 0;
}