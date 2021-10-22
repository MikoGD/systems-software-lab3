#include <dirent.h>
#include <stdio.h>
#include "string_utils.h"

int main(int argc, char *argv[])
{
  DIR *d;
  struct dirent *dir;
  char *file_extension = NULL;
  d = opendir(".");

  if (argc == 2)
  {
    file_extension = argv[1];
  }

  if (d)
  {
    while ((dir = readdir(d)) != NULL)
    {
      if (is_strings_equal(".\0", dir->d_name) == 1 || is_strings_equal("..\0", dir->d_name) == 1)
      {
        continue;
      }

      if (file_extension)
      {
        size_t extension_length = get_end_of_string_index(file_extension) + 1;
        size_t curr_file_length = get_end_of_string_index(dir->d_name) + 1;

        // int test = find_index(dir->d_name, curr_file_length, file_extension, extension_length);

        // printf("file extension: %s\n", file_extension);
        // printf("length: %ld\n", extension_length);
        // printf("current file: %s\n", dir->d_name);
        // printf("length: %ld\n", curr_file_length);
        // printf("Contains extension: %d\n", test);
        // printf("~~~~~~~\n\n");

        if (find_index(dir->d_name, curr_file_length, file_extension, extension_length) != -1)
        {
          printf("%s\n", dir->d_name);
        }
      }
      else
      {
        printf("%s\n", dir->d_name);
      }
    }
    closedir(d);
  }

  return 0;
}