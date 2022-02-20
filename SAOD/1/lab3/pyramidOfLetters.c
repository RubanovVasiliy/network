#include <stdio.h>
#include <ctype.h>

int main(void) {

  char letter;
  printf("Input letter\n");

  if(scanf("%c",&letter) && isalpha(letter)){

    if(letter>90){
      letter-=32;
    }

    int delta = letter -'A';
    int symbol;

    for(int i = 0; i < delta + 1; i++){
    
      symbol = 'A'-delta + i;
      
      for(int j = 0; j < delta * 2 + 1; j++){

        if(symbol<'A'){
          printf("%c",' ');
        }else{
          printf("%c",symbol); 
        }

        if(j<delta){
          symbol++;
        }else{
          symbol--;
        }
      }
      printf("\n");
    }
  }
  return 0;
}