#include <stdio.h>
#include <string.h>
void main(){
	float eX = 1.000000;
	int nX = 1;
	char *messageX = "Enter the number of iterations:\n";
	printf("%s",messageX);
	scanf("%d",&nX);
	while ((nX>0)){
		eX = (eX*(1.000000+(1.000000/nX)));
		nX = (nX-1);
	}
	printf("%f",eX);
}
