#include <stdio.h>
#include <string.h>
void main(){
	float piX = 0.000000;
	int evenX;
	int prevX;
	int nextX;
	int nX = 1;
	char *messageX = "Enter the number of iterations:\n";
	printf("%s",messageX);
	scanf("%d",&nX);
	int iterX = 1;
	while ((iterX<=nX)){
		evenX = (2*nX);
		prevX = (evenX-1);
		nextX = (evenX+1);
		piX = (((piX*evenX)*evenX)/(nextX*prevX));
		iterX = (iterX+1);
	}
	printf("%f",(piX*2));
}
