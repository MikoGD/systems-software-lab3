#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int find_index(char *, int, char *, int);
char *get_column(char *, int, int, int);
int get_column_name_index(char *, int, char *, int);
int get_column_start(char *, int, int);
int get_end_of_string_index(char *);
int get_pid_for_command(FILE *, char *);
char *get_substring(char *, int, int);
int is_strings_equal(char *, char *);
void list_processes();

int main(int argc, char *argv[])
{
  if (argc <= 1)
  {
    list_processes();
  }

  if (argc == 3 && is_strings_equal(argv[1], "search\0") == 1)
  {
    FILE *f = popen("ps -ef", "r");
    int pid = get_pid_for_command(f, argv[2]);
    printf("pid: %d\n", pid);
    fclose(f);
  }

  return 0;
}

int find_index(char *string, int string_length, char *substring, int substring_length)
{
  int substring_index = -1;
  for (int i = 0; i < string_length - 1; i++)
  {
    char *curr_substring = get_substring(string, i, i + substring_length - 1);
    int is_equal = is_strings_equal(substring, curr_substring);

    if (is_equal == 1)
    {
      substring_index = i;
      return substring_index;
    }
  }

  return substring_index;
}

char *get_column(char *row, int max_row_length, int column_start, int column_end)
{
  if (column_start >= 0)
  {
    char *column = get_substring(row, column_start, column_end);

    return column;
  }
  else
  {
    int column_start = get_column_start(row, max_row_length, column_end);
    char *column = get_substring(row, column_start, column_end);

    return column;
  }
}

int get_column_name_index(char *columns, int max_columns_length, char *target_column, int max_target_column_length)
{
  int target_column_index = find_index(columns, max_columns_length, target_column, max_target_column_length);

  return target_column_index;
}

int get_column_start(char *line, int line_max_length, int end)
{
  int start;
  for (start = end - 1; start > 0; start--)
  {
    char curr_letter = *(line + start);

    if (curr_letter == ' ')
    {
      return start + 1;
    }
  }

  return end;
}

int get_end_of_string_index(char *string)
{
  int i;
  for (i = 0; *(string + i) != '\0'; i++)
  {
    char character = *(string + i);
    if ((character >= 0 && character <= 31) || character == 127)
    {
      return i;
    }
  }

  return i;
}

int get_pid_for_command(FILE *processes, char *command)
{
  char *row = NULL;
  size_t row_length;
  ssize_t read;

  read = getline(&row, &row_length, processes);

  int pid_index = get_column_name_index(row, row_length, "PID\0", 4);
  int cmd_index = get_column_name_index(row, row_length, "CMD\0", 4);

  do
  {
    read = getline(&row, &row_length, processes);
    char *pid = get_column(row, row_length, -1, pid_index + 3);
    char *curr_command = get_column(row, row_length, cmd_index, -1);
    int is_equal = is_strings_equal(command, curr_command);

    if (is_equal == 1)
    {
      return atoi(pid);
    }
  } while (read != -1);

  return -1;
}

char *get_substring(char *string, int start, int end)
{
  int end_index;
  if (end == -1)
  {
    end_index = (int)get_end_of_string_index(string);
  }
  else
  {
    end_index = end;
  }

  size_t length = (end_index - start);
  char *substring = (char *)malloc(length + 1);
  memcpy(substring, (string + start), length);
  *(substring + length) = '\0';

  return substring;
}

int is_strings_equal(char *string1, char *string2)
{
  int i;
  for (i = 0; *(string1 + i) && *(string2 + i); i++)
  {
    if (*(string1 + i) != *(string2 + i))
    {
      return -1;
    }
  }

  if (*(string1 + i) == '\0' && *(string2 + i) == '\0')
  {
    return 1;
  }

  return -1;
}

void list_processes()
{
  char *args[] = {"ps", "-aux", NULL};
  execvp("/bin/ps", args);
}