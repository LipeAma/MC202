// MC202 - Lab04
// Felipe Costa Amaral - Ra:249239

#include <stdio.h>
#include <stdlib.h>
#define TXT_STR_SIZE 400000
#define NUM_STR_SIZE 6
#define IS_FIRST_CONSONANT -1
#define IS_FIRST_VOWEL -2
#define IS_LETTER -3
#define IS_NUMBER -4
#define IS_SPACE -5
#define IS_LINEBREAK -6
#define IS_SYMBOL -7
#define IS_EOF -7

int inputCases(char, char);

int main(void) {
  // Resumo:
  // Resolve o problema enunciado utilizando dois arrays. Os caracteres são
  // lidos, processados para eliminar os irrelevantes, e armazenados no
  // primeiro array, que vai enchendo aos poucos. Os valores já armazenados
  // não são processados, apenas a entrada é. Os digitos lidos são armazenados
  // no segundo array. Quando os digitos do número acabam, o array é
  // inerpretado como um int, o valor obtido é somado ao total, e o array é
  // reinicializado. Quando acaba a linha do input, o primeiro array é
  // imprimido, prefixiado pelo total somado e pela string "goat says:". Após
  // isso os dois arrays são reinicializados, e o total da soma é zerado. A
  // leitura é feita charactere por charactere, que são classificados em casos
  // definidos na função inputCases.
  //
  // As variáveis estão bem nomeadas, então leia o código para mais detalhes.

  char *textStr = (char *)calloc(TXT_STR_SIZE, sizeof(char));
  char numStr[NUM_STR_SIZE];
  char inputChar, lastWas = IS_SPACE, wordFirstLetter = IS_SPACE;
  int lineSum = 0, wordSize = 0, textPos = 0, numPos = 0;

  while ((inputChar = getchar()) != EOF) {
    if (numPos && (lastWas != IS_NUMBER || inputChar == '\n')) {
      lineSum += atoi(numStr);
      numPos = 0;
      numStr[0] = '\0';
    }

    switch (inputCases(inputChar, wordSize == 0)) {
      case IS_FIRST_CONSONANT:
        wordFirstLetter = inputChar;
        wordSize += 1;
        lastWas = IS_LETTER;
        textStr[textPos++] = ' ';
        break;

      case IS_FIRST_VOWEL:
        textStr[textPos++] = ' ';

      // Não há break no caso anterior, pois ambos os casos tem código
      // semelhante que será reutilizado.
      case IS_LETTER:
        textStr[textPos++] = inputChar;
        textStr[textPos] = '\0';
        wordSize += 1;
        lastWas = IS_LETTER;
        break;

      case IS_NUMBER:
        numStr[numPos++] = inputChar;
        numStr[numPos] = '\0';
        lastWas = IS_NUMBER;
        break;

      case IS_LINEBREAK:
        if (lastWas == IS_SPACE) break;
        lastWas = IS_LINEBREAK;

      // Não há break no caso anterior, pois ambos os casos tem código
      // semelhante que será reutilizado.
      case IS_SPACE:
        if (wordFirstLetter != IS_SPACE) textStr[textPos++] = wordFirstLetter;
        wordFirstLetter = IS_SPACE;

        if (wordSize) {
          textStr[textPos++] = 'm';
          for (char i = 0; i <= wordSize; i++) textStr[textPos++] = 'a';
          textStr[textPos] = '\0';
        }
        if (lastWas == IS_LINEBREAK) {
          if (lineSum == 1)
            printf("1 goat says:%s\n", textStr);
          else
            printf("%d goats say:%s\n", lineSum, textStr);
          textPos = 0, numPos = 0, lineSum = 0;
          textStr[0] = '\0', numStr[0] = '\0';
        }
        wordSize = 0;
        lastWas = IS_SPACE;
        break;

      case IS_SYMBOL:
        lastWas = IS_SYMBOL;
        break;
    }
  }
}

int inputCases(char c, char isFirstLetter) {
  // Separa o charactere de entrada nos casos importantes para o probelma, e
  // retorna um inteiro que que codifica esse caso.
  // As variáveis estão bem nomeadas, então leia o código para mais detalhes.

  if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')) {
    if (isFirstLetter) {
      if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' ||
          c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        return IS_FIRST_VOWEL;
      return IS_FIRST_CONSONANT;
    }
    return IS_LETTER;
  }
  if ('0' <= c && c <= '9') return IS_NUMBER;
  if (c == ' ') return IS_SPACE;
  if (c == '\n') return IS_LINEBREAK;
  return IS_SYMBOL;
}
