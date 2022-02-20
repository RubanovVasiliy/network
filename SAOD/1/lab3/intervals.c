#include <stdio.h>

int main(void) {

  int x;
  printf("Input x:");
  scanf("%d",&x);

  //x1
  for(;x>=0;){
    printf("x belongs to x1\n");
    break;
  }

  //x5
  for(;(x>=5 && x<15) || x==0 || x==20 || x==100 || x==1000;){
    printf("x belongs to x5\n");

    //x4
    for(;(x>=5 && x<15) || x==0;){
      printf("x belongs to x4\n");

      //x2
      for(;x>=5 && x<15;){
        printf("x belongs to x2\n");
        break;
      }

      //x3
      for(;x==0;){
        printf("x belongs to x3\n");
        break;
      }
      break;
    }
    break;
  }

  return 0;
}