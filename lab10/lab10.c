// MC202 - Lab02
// Felipe Costa Amaral - Ra:249239

#include <stdio.h>

int main(void) {
  while (1) {
    int no_elements;
    if (scanf("%d", &no_elements) == EOF || no_elements == 0) break;
    int elements[no_elements];

    for (int i = 0; i < no_elements; i++) {
      scanf("%d", &elements[i]);
    }

    int queue[no_elements][2];
    queue[0][0] = 0;
    queue[0][1] = no_elements;
    int q_size = 1;        // queue size
    int q_first = 0;       // index of the first element in the queue
    int next_lvl_pos = 1;  // index of the first element in the next level.
    while (q_size != 0) {
      int a = queue[q_first][0];
      int b = queue[q_first][1];
      if (++q_first >= no_elements) q_first -= no_elements;
      q_size--;

      int smallest = elements[a];
      int pos = a;
      for (int i = a + 1; i < b; i++) {
        if (elements[i] < smallest) {
          smallest = elements[i];
          pos = i;
        }
      }
      printf("%d ", pos);

      int insertPos;
      if (pos > a) {
        insertPos = q_first + q_size;
        if (insertPos >= no_elements) insertPos -= no_elements;
        queue[insertPos][0] = a;
        queue[insertPos][1] = pos;
        q_size++;
      }
      if (pos < b - 1) {
        insertPos = q_first + q_size;
        if (insertPos >= no_elements) insertPos -= no_elements;
        queue[insertPos][0] = pos + 1;
        queue[insertPos][1] = b;
        q_size++;
      }
      if (q_first == next_lvl_pos) {
        printf("\n");
        next_lvl_pos = q_first + q_size;
        if (next_lvl_pos >= no_elements) next_lvl_pos -= no_elements;
      }
    }
    printf("\n");
  }
}