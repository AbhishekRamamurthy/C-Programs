#include<stdlib.h>
#include<stdio.h>
/*
	Program for addition of format
	111 -> each stored in a[0],a[1],a[2]
	integer b=1
	add a+b -> 111+1 = 112
	overflow condition is taken care
*/
int main() {
	int a[3]={9,9,9};
	int b=5;
	int temp=0, temp1=0;
	int k=0;
	int l=0,of=0;
	int i=(sizeof(a)/sizeof(a[0]))-1;
	a[i]=b+a[i];
	for(k=i;k>=0;k--) {
		if(a[k] != 0) {
			if(a[k] >9) {
				if(k ==0) {
					of=1;
				}
				temp=a[k]%10;
				temp1=a[k]/10;
				a[k]=temp;
			} 
			a[k-1]=temp1+a[k-1];
		}
	}
	for(k=0;k<=i;k++) {
		if(a[k] !=0 || l == 1 || of == 1) {
			l=1;
			printf("a =%d\n",a[k]);
		}
	}
	return 0;
}
