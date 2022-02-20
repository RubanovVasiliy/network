#include <stdio.h>

int main(void) {
  int n;
  int d=0;
  int temp;

  printf("Input length of the array: ");
  scanf("%d",&n);
  int arr[n];

  for(int i=0;i<n;i++){
    scanf("%d",&arr[i]);
  }

  int swapped;
  do{
    swapped = 0;
    for(int i=0;i<n-1;i++){

      if (arr[i] > arr[i+1]){
        
        temp=arr[i];
        arr[i]=arr[i+1];
        arr[i+1]=temp;
        swapped = 1;
        d++;
      }
    }
  }while (swapped);
  
  for(int i=0;i<n;i++){
    printf("%d ",arr[i]);
  }
  printf("\nIterations: %d\n",d);

  return 0;
}