#include <stdio.h>
#include <string.h>
void main(){
	float pi = 0.000000;
	int even;
	int prev;
	int next;
	int n = 1;
	char *message = "Enter the number of iterations:\n";
	printf("%s",message);
	scanf("%d",&n);
	int iter = 1;
	while ((iter<=n)){
		even = (2*n);
		prev = (even-1);
		next = (even+1);
		pi = (((pi*even)*even)/(next*prev));
		iter = (iter+1);
	}
	printf("%f",(pi*2));
}
