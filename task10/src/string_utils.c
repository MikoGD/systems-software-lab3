#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "string_utils.h"

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