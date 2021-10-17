#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  int pid;

  if ((pid = fork()) < 0)
  {
    printf("Error with forking process\n");
    exit(1);
  }
  else if (pid == 0)
  {
    printf("Child process calling\n");
    char *args[] = {"ls", "-l", NULL};
    int status = execvp("/bin/ls", args);

    if (status == -1)
    {
      printf("Error occured while calling execp\n");
    }
  }
  else
  {
    printf("parent calling\n");
  }

  return 0;
}