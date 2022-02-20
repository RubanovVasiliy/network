#include <stdio.h>

int main(void) {
  int day;
  int mounth; 
  printf("Input date dd/mm: ");
  scanf("%d %d",&day,&mounth);

  switch(mounth){
    case 3:
      if(day<21){
        printf("Riba\n");
      }else{
        printf("Oven\n");
      }
      break;

      case 4:
      if(day<21){
        printf("Oven\n");
      }else{
        printf("Telec\n");
      }
      break;

      case 5:
      if(day<21){
        printf("Telec\n");
      }else{
        printf("Blizneci\n");
      }
      break;

      case 6:
      if(day<21){
        printf("Blizneci\n");
      }else{
        printf("Rak\n");
      }
      break;

      case 7:
      if(day<23){
        printf("Rak\n");
      }else{
        printf("Lev\n");
      }
      break;

      case 8:
      if(day<23){
        printf("Lev\n");
      }else{
        printf("Deva\n");
      }
      break;

      case 9:
      if(day<24){
        printf("Deva\n");
      }else{
        printf("Veci\n");
      }
      break;

      case 10:
      if(day<24){
        printf("Veci\n");
      }else{
        printf("Scorpion\n");
      }
      break;

      case 11:
      if(day<22){
        printf("Scorpion\n");
      }else{
        printf("Strelec\n");
      }
      break;

      case 12:
      if(day<22){
        printf("Strelec\n");
      }else{
        printf("Kozerog\n");
      }
      break;

      case 1:
      if(day<22){
        printf("Kozerog\n");
      }else{
        printf("Vodoley\n");
      }
      break;

      case 2:
      if(day<19){
        printf("Vodoley\n");
      }else{
        printf("Riba\n");
      }
      break;
  }

  return 0;
}