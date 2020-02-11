#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
void buildp(unsigned int n, unsigned int s, unsigned char pavement[1024][1024]);
void* ivmemcopy(unsigned char* dest, unsigned char* src, size_t count);
 
int main(int argc, char **argv){
    unsigned int n, s, i;
    unsigned char pavement[1024][1024];
    while(scanf("%u %u",&n,&s)==2){
        s&=3;
        buildp(n,s,pavement);
        n=1<<n;
        for(i=0;i<n;i++){
            fwrite(pavement[i],n,sizeof(unsigned char),stdout); fputc(10,stdout);
        }
    }
    return 0;
}
 
void buildp(unsigned int n, unsigned int s,unsigned char pavement[1024][1024]){
    unsigned int i, n0;
    n0=(1<<n)>>1;
    if(n<1){
        **pavement=48;
    }
    else{
        buildp(n-1,s,pavement);
        switch(s){
            case(0):
                for(i=0;i<n0;i++){
                    memcpy(pavement[i]+n0,pavement[i],n0);/*front*/
                    memcpy(pavement[n0+i],pavement[i],n0);/*down-L*/
                    ivmemcopy(pavement[n0+i]+n0,pavement[i],n0); /*down-R*/
                }
                break;
            case(1):
                for(i=0;i<n0;i++){
                    ivmemcopy(pavement[i]+n0,pavement[i],n0);/*front*/ 
                    memcpy(pavement[n0+i],pavement[i],n0);/*down-L*/
                    memcpy(pavement[n0+i]+n0,pavement[i],n0);/*down-R*/
                }
                break;
            case(2):
                for(i=0;i<n0;i++){
                    memcpy(pavement[i]+n0,pavement[i],n0);/*front*/
                    memcpy(pavement[n0+i],pavement[i],n0);/*down-L*/
                    memcpy(pavement[n0+i]+n0,pavement[i],n0);/*down-R*/
                    ivmemcopy(pavement[i],pavement[n0+i]+n0,n0);/*Negate Source*/
                }
                break;
            case(3):
                for(i=0;i<n0;i++){   
                    memcpy(pavement[i]+n0,pavement[i],n0);/*front*/
                    ivmemcopy(pavement[n0+i],pavement[i],n0);/*down-L*/
                    memcpy(pavement[n0+i]+n0,pavement[i],n0);/*down-R*/
                }
                break;
            break;
        }
    }
}
 
void* ivmemcopy(unsigned char* dest, unsigned char* src, size_t count){ 
    while (count--) *dest++ = 97-*src++; return dest;
}