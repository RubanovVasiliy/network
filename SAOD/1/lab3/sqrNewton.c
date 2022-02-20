#include <stdio.h>

double sqr1(int n){
    float xi;
    float x=1;
    for(;;){
      xi = (x + n / x) / 2;
      if(x==xi){
        break;
      }
      x = xi;
    }
    return x;
  }

int main(void) {
  printf("Input n:");
  int n;
  scanf("%d",&n);
  printf("%.4f\n",sqr1(n));

  return 0;
}