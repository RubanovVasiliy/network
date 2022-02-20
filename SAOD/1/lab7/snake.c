#include <stdio.h>
#include <ctype.h>

int main(void) {
  int rows;
  int cols;
  int d=0;
  printf("Enter rows and cols number: ");
  
  if(scanf("%d %d",&rows,&cols) && cols>0 && rows>0){
    int matrix[rows][cols];
    int i, j;
    for (i = 0; i < rows; ++i) {
      for (j = 0; j < cols; ++j) {
        if(i%2==0){
          matrix[i][j]=j+d;
        }else{
          matrix[i][j]=cols-j+d-1;
        }
        printf("%4d", matrix[i][j]);
      }
      d+=cols;
    printf("\n");
    }
  }else{
    printf("Error\n");
    }
  return 0;
}