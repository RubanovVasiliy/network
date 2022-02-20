#include <stdio.h>
#include <math.h>

int main(void) {
  int n;
  int d=0;
  int temp=0;
  int max=-pow(2,16);

  printf("Input length of the array: ");
  scanf("%d",&n);
  int arr[n];
  
  for(int i=0;i<n;i++){
    scanf("%d",&arr[i]);

    if(arr[i]>max){
      max=arr[i];
    }
  }

  max++;
  int count[max];

  for(int i=0;i<max;i++){
    count[i]=0;
  }

  for(int i=0;i<n;i++){
    count[arr[i]]=count[arr[i]]+1;
  }

  int currentSortedIndex = 0;
  for (int n = 0; n < max; n++) {
    temp = count[n];
    for (int k = 0; k < temp; k++) {
      arr[currentSortedIndex] = n;
      currentSortedIndex++;
      d++;
    }
  }

  for(int i=0;i<n;i++){
    printf("%d ",arr[i]);
  }
  printf("\nIterations: %d\n",d);

  return 0;
}