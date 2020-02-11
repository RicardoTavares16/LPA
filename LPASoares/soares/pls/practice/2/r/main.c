#include <stdio.h>
#include <stdlib.h>

unsigned char nprinters(unsigned long long network[36], unsigned long long printers, unsigned long long all, unsigned char nodes, unsigned char solution, unsigned char wnode, unsigned char lvl);

int main(int argc, char **argv){
	unsigned char sn, tn, nodes, i;
	unsigned long long network[36]={0}, mask=1, printers=0, all;
	scanf("%hhu",&nodes);
	all=((mask<<nodes)-1)<<1;
	if(nodes<4){printf("1\n");return 0;}/*LESS THAN 4*/
	for(i=1;i<=nodes;i++){mask<<=1; network[i]|=mask;}/*Diagonal 1's*/
	mask=1;
	while(scanf("%hhu %hhu",&sn,&tn)==2){
		network[sn]|=mask<<tn; network[tn]|=mask<<sn;
	}
	printf("%d\n",nprinters(network,printers,all,nodes,12,1,0));
	return 0;
}

unsigned char nprinters(unsigned long long network[36],unsigned long long printers, unsigned long long all, unsigned char nodes, unsigned char solution, unsigned char wnode, unsigned char lvl) {
	unsigned char i;
	unsigned long long tprinters;
	lvl++;
	for (i = wnode; i <= nodes; i++) {
		tprinters = printers | network[i];
		if (tprinters == all) {
			return lvl;
		} else if (lvl < solution - 1) {
			solution = nprinters(network, tprinters, all, nodes, solution, i + 1, lvl);
		}
	}
	return solution;
}
