#include <stdio.h>
#include <stdlib.h>

void remove_newline(char *s, int maxsize) {
  for (int i = 0; i < maxsize && s[i]; i++) {
    if (s[i] == '\n') {
      s[i] = '\0';
      return;
    }
  }
}

int main(int argc, char *argv[]) {
  const int BUFSIZE = 80;
  char buffer[BUFSIZE];
  FILE *infile = NULL;

  if (argc != 2) {
    fprintf(stderr, "calculator needs exactly 1 argument, the input file\n");
    return 1;
  }
  infile = fopen(argv[1], "r");
  if (!infile) {
    fprintf(stderr, "input file %s not found\n", argv[1]);
    return 1;
  }

  // Your code should go here-ish. Feel free to change this loop as you need to.
  // IMPORTANT: your output should either be the single line "ERROR\n", or the
  // single number output, and nothing else.
  while (fgets(buffer, BUFSIZE, infile)) {
    // TODO: implement the calculator.
    remove_newline(buffer, BUFSIZE);

    // You should remove the following line. This is just to show that we are
    // reading in lines from the input file.
    printf("got this line: %s\n", buffer);
  }

  return 0;
}
