#include <stdio.h>
#include <ctype.h>

int main(void) {
  char s[50];
  char ch;
  int lenght=0;  
  int i=0;
  int p=1;
  int haveAlpha=0;

  printf("Введите строку: ");

  while((ch=getchar()) && ch!='\n'){
    s[lenght]=ch;
    lenght++;
  }
  
  for(int j = 0;j<lenght;j++){
    if(isalpha(s[j])){
      haveAlpha++;
    }
  }

  lenght-=1;
  

  if(haveAlpha==0){
    printf("erorr\n");
  }else{
    while(i!=lenght && p && i<lenght){
      if(!isalpha(s[i])){
        i++;
      }else if(!isalpha(s[lenght])){
        lenght--;
      }else if(tolower(s[i])==tolower(s[lenght])){
        i++;
        lenght--;
      }else{
        p=0;
      }
    }
  
    if(p){
      printf("palindrom\n");
    }else{
      printf("ne palindrom\n");
    }
  }
  return 0;
}