#include <stdio.h>
#include <ctype.h>

int main(void) {
  char ch;
  int lenght=0;
  while((ch=getchar())!='\n'){
    if(isalpha(ch)){
      ch=toupper(ch);
      putchar(ch);
      lenght++;
    }
  }

  printf("\n");
  printf("%d\n",lenght);
  return 0;
}