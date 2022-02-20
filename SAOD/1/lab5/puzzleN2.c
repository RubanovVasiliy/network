#include <stdio.h>
#include <math.h>

int main(void) {
  int s;

  for(int i=1;i<10;i++){
    for(int j=1;j<10;j++){
      s=pow(i,j);

      if(s%10==i && s/10000==j){
          printf("(%d)^%d = %d\n",i,j,s);
      }
    }
  }

  return 0;
}