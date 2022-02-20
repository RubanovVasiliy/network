#include <stdio.h>

int main(void) {
  int k;
  int n;
 
  printf("Input first number and count: ");
  scanf("%d %d",&k,&n);
 
  for(int i=0;i<n;i++){
    printf("%d, ",k);
    k*=2;
  }
  printf("\n");
  return 0;
}