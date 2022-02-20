#include <stdio.h>
#include <math.h>

int main(void) {

  for(int q=10000;q<100000;q++){
    if(pow(q%10 + q/10%10 + q/100%10 + q/1000%10 + q/10000,3)==q){
      printf("(%d + %d + %d + %d + %d)^3 = %d\n",
      q/10000,q/1000%10,q/100%10,q/10%10,q%10,q);
    }
  }

  return 0;
}