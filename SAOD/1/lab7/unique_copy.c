#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int *unique_copy(int arr[],int lenght){
  int j=1;
  int *var = malloc(sizeof(int)*lenght+1);
  var[1]=arr[0];
  for(int i=1;i<lenght+1;i++){
    if(arr[i]!=var[j]){
      var[j+1]=arr[i];
      j++;
    }
  }
  var[0]=j;

  int *v = malloc(sizeof(int)*j);
  for(int i=0;i<j;i++){
    v[i]=var[i];
  }
  free(var);
  var=NULL;
  
  return v;
}

int *insertionSort(int arr[],int lenght){
  int temp;
  int j=0;
  for (int i=1;i<lenght;i++){ 
    temp = arr[i];
    j = i;

    while (j > 0 && arr[j-1] > temp){ 
      arr[j] = arr[j-1];
      arr[j-1] = temp;
      j--;
    }
  }
  return arr;
} 

int *unique_copy_unstable(int arr[],int lenght){
  return unique_copy(insertionSort(arr,lenght),lenght);
} 

int main(void) {
  int *a;
  int arr1[] = {1,4,0,0,0,0,4,4,4,2,2,3,2,2,4,5,5,6,7};

printf("Example, test array.\nArray items:");
 for(int i=0;i<sizeof(arr1)/sizeof(int);i++){
    printf(" %d",arr1[i]);
  }
  printf("\n");

  printf("Unique:");
  a = unique_copy(arr1,sizeof(arr1)/sizeof(int));
  for(int i=1;i<a[0];i++){
    printf(" %d",a[i]);
  }
  printf("\n");

  printf("Unique unstable:");
  a = unique_copy_unstable(arr1,sizeof(arr1)/sizeof(int));
  for(int i=1;i<a[0];i++){
    printf(" %d",a[i]);
  }
  printf("\n\n");

  int n;
  printf("Enter size of array: ");
  scanf("%d",&n);



  int arr2[n];
  printf("Enter items:");
  for(int i=0;i<n;i++){
    scanf("%d",&arr2[i]);
  }
  
  printf("Unique:");
  a = unique_copy(arr2,sizeof(arr2)/sizeof(int));
  for(int i=1;i<a[0];i++){
    printf(" %d",a[i]);
  }
  printf("\n");

  printf("Unique unstable:");
  a = unique_copy_unstable(arr2,sizeof(arr2)/sizeof(int));
  for(int i=1;i<a[0];i++){
    printf(" %d",a[i]);
  }
  printf("\n");  

  return 0;
}