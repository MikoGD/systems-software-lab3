#include <stdio.h>

int main()
{
  FILE *logs = fopen("logs.txt", "a+");
  char *line;
  size_t line_length;
  ssize_t read;

  read = getline(&line, &line_length, logs);

  do
  {
    printf("%s", line);
    read = getline(&line, &line_length, logs);
  } while (read != -1);
  return 0;
}