#include <stdio.h>
#include <string.h>
#include <string.h>
 
int main(void) {
  printf("%s", "Please write your string: ");  
  char a[1000];
  gets(a);
  printf("%s", "Reverse: "); 
  for(int i=strlen(a)-1;i>=0;i--){
      printf("%c", a[i]);
  }
  return 0;
}
