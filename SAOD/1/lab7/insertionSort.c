#include <stdio.h>

int main(void) {
  int n;
  int j;
  int d=0;
  int temp;

  printf("Input length of the array: ");
  scanf("%d",&n);
  int arr[n];

  for(int i=0;i<n;i++){
    scanf("%d",&arr[i]);
  }

  for (int i=1;i<n;i++){ 
    temp = arr[i];
    j = i;

    while (j > 0 && arr[j-1] > temp){ 
      arr[j] = arr[j-1];
      arr[j-1] = temp;
      j--;
      d++;
    }
  }
  
  for(int i=0;i<n;i++){
    printf("%d ",arr[i]);
  }
  printf("\nIterations: %d\n",d);

  return 0;
}