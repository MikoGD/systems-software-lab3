#include <stdio.h>

int main()
{
  FILE *logs = fopen("logs.txt", "a+");

  char *user_input;
  size_t input_length;

  getline(&user_input, &input_length, stdin);

  fprintf(logs, "%s\n", user_input);

  return 0;
}