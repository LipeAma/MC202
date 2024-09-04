#include <stdio.h>
#include <stdlib.h>

int main(void) {
  long str_size = sizeof(char[2e5]); // A linha não excede 2e5 caracteres
  char *str = (char*) malloc(str_size);
  str[0] = '\0'

  char c;
  int linesum = 0 // O tipo é int pois irá armazenar no máximo o valor (2e5 / 6) * 9 = 3e5 
  while ((c = getchar()) != EOF) {
    if ('0' <= c <= '9') {
      linesum += c - '0'
    }
    else if (c == ' ')
    
    if c == '\n'
      print
    }   
  }
}
