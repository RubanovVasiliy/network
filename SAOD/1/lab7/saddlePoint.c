#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(void) {
  int rows;
  int cols;
  int max;
  int min;

  srand(time(NULL));
  printf("Enter rows and cols number: ");
  
  if(scanf("%d %d",&rows,&cols) && cols>0 && rows>0){
    int matrix[rows][cols];
    int m2[rows][cols];
    int i, j;
    for (i = 0; i < rows; ++i) {
      for (j = 0; j < cols; ++j) {
        matrix[i][j]=rand()%20;
        m2[i][j]=0;
        printf("%4d", matrix[i][j]);
      }
    printf("\n");
    }

    for (i = 0; i < rows; ++i) {
      min=pow(2,16)-1;
      for (j = 0; j < cols; ++j) {
        if(min>matrix[i][j]){
          min=matrix[i][j];
        }
      }
      for (j = 0; j < cols; ++j) {
        if(matrix[i][j]==min){
          m2[i][j]++;
        }
      }
    }

    for (i = 0; i < cols; ++i) {
      max=-pow(2,16);
      for (j = 0; j < rows; ++j) {
        if(max<matrix[j][i]){
          max=matrix[j][i];
        }
      }
      for (j = 0; j < rows; ++j) {
        if(matrix[j][i]==max && m2[j][i]==1){
          m2[j][i]++;
        }
      }
    }

    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        if(m2[i][j]==2){
          printf("(%d, %d) = %4d\n",j,i,matrix[i][j]);
        }
      }
    }
  }else{
    printf("Error\n");
  }

  return 0;
}