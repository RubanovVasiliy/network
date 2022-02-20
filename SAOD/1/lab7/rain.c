#include <stdio.h>
#include <math.h>

int main(void) {
  //int mas[]= {3,2,4,2,2,5,4,5,4,5,7};
  int mas[]= {7,6,5,6,2,4,2,4,1};
  int size = sizeof (mas)/ sizeof (mas[0]);

  int max=0;
  int maxi=0;

  int maxL=mas[0];
  int iL=0;

  int maxR=mas[0];
  int iR=0;

  int s=0;
  
  for(int i=0;i < size;i++){
    if(mas[i] >= max){
      max=mas[i];
      maxi=i;
    }
  }

  for(int i=1;i < maxi+1;i++){
    if(mas[i] >= maxR){

      maxL=maxR;
      iL=iR;
      maxR=mas[i];
      iR=i;  

      if(abs(iR-iL)>1){
        for(int j=iL;j<iR;j++){
          s+=maxL-mas[j];
        }

        maxL=mas[i];
        iL=i;
        maxR=mas[i];
        iR=i;
      } 
    }
  }

  maxL=mas[size-1];
  iL=size-1;

  maxR=mas[size-1];
  iR=size-1;

 for(int i=size-2;i > maxi-1;i--){
    if(mas[i] >= maxL){

      maxR=maxL;
      iR=iL;
      maxL=mas[i];
      iL=i;  

      if(abs(iR-iL)>1){
        for(int j=iR;j>iL;j--){
          s+=maxR-mas[j];  
        }

        maxR=mas[i];
        iR=i;
        maxL=mas[i];
        iL=i;
      } 
    }
  }

  printf("s: %d\n",s);
  return 0;
}