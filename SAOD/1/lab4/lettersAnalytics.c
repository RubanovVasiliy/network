#include <stdio.h>
#include <ctype.h>

int main(void) {
  int vowles=0;
  int digits=0;
  int punctuation=0;
  char ch;
  int letters=0;
  float lenght=0;
  
  while((ch=getchar())&& ch!='\n'){
    lenght++;
    if(isdigit(ch)){
      digits++;
    }

    if(ispunct(ch)){
      punctuation++;
    }

    if(isalpha(ch)){
      letters++;
    }

    ch = tolower(ch);
    if(ch=='a' || ch=='e' || ch=='y' || ch=='u' || ch=='i' || ch=='o'){
      vowles++;
    }
  }

  printf("Vowels: %d\n",vowles);
  printf("Digits: %d\n",digits);
  printf("Punctuation: %d\n",punctuation);
  printf("Letters / Lenght = %: %d / %.0f = %f\n",letters,lenght,letters/lenght);
  
  return 0;
}