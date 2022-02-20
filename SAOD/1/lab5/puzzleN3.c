#include <stdio.h>
#include <math.h>

int main(void) {
  int n;
  int s;

  for(int i=1;i<10;i++){
    for(int j=1;j<10;j++){
      n=j+j*10;
      s=j+i*10+i*100+j*1000;

      if(pow(n,i)==s){
          printf("(%d)^%d = %d\n ",n,i,s);
      }
    }
  }

  return 0;
}