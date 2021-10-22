#include <stdio.h>
#include <unistd.h>

int main()
{
  char *args[] = {"chmod", "777", "logs.txt", NULL};
  int status = execvp("/bin/chmod", args);

  if (status == -1)
  {
    printf("Error changing permissions\n");
  }
  return 0;
}