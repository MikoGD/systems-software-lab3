#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include "string_utils.h"

char *get_column(char *, int, int, int);
int get_column_name_index(char *, int, char *, int);
int get_column_start(char *, int, int);
int get_end_of_string_index(char *);
int get_pid_for_command(FILE *, char *);
void list_processes();

int main(int argc, char *argv[])
{
  if (argc <= 1)
  {
    list_processes();
  }
  else if (argc == 3 && is_strings_equal(argv[1], "search\0") == 1)
  {
    FILE *f = popen("ps -ef", "r");
    int pid = get_pid_for_command(f, argv[2]);
    printf("pid: %d\n", pid);
    fclose(f);
  }
  else if (argc == 3 && is_strings_equal(argv[1], "kill\0") == 1)
  {
    int pid = atoi(argv[2]);
    int status = kill(pid, SIGKILL);
    if (status == 0)
    {
      printf("Successfully terminated process: %d\n", pid);
    }
    else
    {
      printf("Failed to terminate process: %d\n", pid);
    }
  }

  return 0;
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

void list_processes()
{
  char *args[] = {"ps", "-aux", NULL};
  execvp("/bin/ps", args);
}