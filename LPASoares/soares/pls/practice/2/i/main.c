#include <stdlib.h>
#include <stdio.h>

int deps[301], depcourses[4501][2], cects[2][30001];
int ovssat(int ndep, int ects);
int main(int argc, char *argv[]){
	int ndep, ects, *current=depcourses[0], i, j, depc;
	scanf("%d %d",&ndep,&ects);
	for(i=1;i<=ndep;i++){
		scanf("%d",&depc);
		deps[i]=deps[i-1]+depc;
		for(j=0;j<depc;j++){
			scanf("%d %d",&current[0],&current[1]);
			current+=2;
		}
	}
	printf("%d\n",ovssat(ndep,ects));
	return 0;
}

int ovssat(int ndep, int ects){
	int *current=cects[0], *previous=cects[1], *temp, i, j, c, sol;
	for(i=1;i<=ndep;i++){
		temp=current;
		current=previous;
		previous=temp;
		for(j=1;j<=ects;j++){
			current[j]=previous[j];
			for(c=deps[i-1];c<deps[i];c++){
				if(depcourses[c][0]<j){
					sol=depcourses[c][1]+previous[j-depcourses[c][0]];
					if(sol>current[j]){
						current[j]=sol;
					}
				}
			}
		}
	}
	return current[ects];
}