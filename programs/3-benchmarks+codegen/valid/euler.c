#include <stdio.h>
#include <string.h>
void main(){
	float e = 1.000000;
	int n = 1;
	char *message = "Enter the number of iterations:\n";
	printf("%s",message);
	scanf("%d",&n);
	while ((n>0)){
		e = (e*(1.000000+(1.000000/n)));
		n = (n-1);
	}
	printf("%f",e);
}
