#include <stdio.h>
#include <math.h>

void qs(int* arr, int n)
{
  int temp;
  int j;
    for (int i=1;i<n;i++){ 
    temp = arr[i];
    j = i;

    while (j > 0 && arr[j-1] > temp){ 
      arr[j] = arr[j-1];
      arr[j-1] = temp;
      j--;
    }
  }
}

int compareMass(int* arr1,int* arr2,int len){
  for(int i=0;i<len;i++){
    if(arr1[i]!=arr2[i]){
      return 0;
    }
  }
  return 1;
}

int main(void) {
  int n;
  int s=1;

  printf("Enter sudoku rank: ");
  
  if(scanf("%d",&n)){
    n=pow(n,2);
    int m=sqrt(n);  
    int arr[n][n];
    int sArr[n];
    int dArr[n];
    printf("Enter sudoku:\n");
    for(int i=0;i<n;i++){
      sArr[i]=i+1;
      for(int j=0;j<n;j++){
        scanf("%d",&arr[i][j]);
      }
    }

    for(int i=0;i<n && s!=0;i++){
      for(int j=0;j<n && s!=0;j++){
        dArr[j]=arr[i][j];
      }
      qs(dArr,n);
      if(!compareMass(sArr,dArr,n)){
        s=0;
      }
    }
    
    for(int i=0;i<n && s!=0;i++){
      for(int j=0;j<n && s!=0;j++){
        dArr[j]=arr[j][i];
      }
      qs(dArr,n);
      if(!compareMass(sArr,dArr,n)){
        s=0;
      }
    }
    int inc=0;
    for(int q=0;q<m && s!=0;q++){
      for(int w=0;w<m && s!=0;w++){
        inc=0;
        for(int i=0+q*m;i<m+q*m;i++){
          for(int j=0+w*m;j<m+w*m;j++){
            dArr[inc]=arr[i][j];
            inc++;
          }
        }
        qs(dArr,n);
        if(!compareMass(sArr,dArr,n)){
          s=0;
        }
      }
    }
 
    if(s==1){    
      printf("Access\n");
    }else{
      printf("U have mistake\n");
    }
  }
  return 0;
}