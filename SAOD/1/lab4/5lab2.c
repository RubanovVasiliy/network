#include <stdio.h>
#include <ctype.h>

int main(void) {
  int day;
  int mounth;
  int year;
  int v=0;

  printf("Input date dd/mm/yyyy: ");
  scanf("%d %d %d",&day,&mounth,&year);
  
  if((year%4==0 && year%100!=0) || year%400==0){
    v=1;
  }
  int sum = day;
  
  switch(mounth-1){
  case 11:
      sum+=30;
  case 10:
      sum+=31;
  case 9:
      sum+=30;
  case 8:
      sum+=31;
  case 7:
      sum+=31;
  case 6:
      sum+=30;
  case 5:
      sum+=31;
  case 4:
      sum+=30;
  case 3:
      sum+=31;
  case 2:
      sum+=28+v;
      
  case 1:
     sum+=31;
  }


  printf("%d\n",sum);
  //printf("%d\n",lenght);
  return 0;
}