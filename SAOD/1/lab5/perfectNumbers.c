#include <stdio.h>
#include <math.h>

int main(void) {
  for(int n=2;n<10000;n++){
    int s =1;
    for(int d=2;d<=n/2;d++){
      if(n%d==0){
        s+=d;
      }
    }
    if(s==n){
      printf("%d\n",n);
    }    
  }
  return 0;
}