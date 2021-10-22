#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sig_handler(int sigNum);

int main()
{
  if (signal(SIGTERM, sig_handler) == SIG_ERR)
  {
    printf("\nSomething went wrong\n");
  }
  else
  {
    printf("Child process is return with: %d\n", 0);
  }

  pid_t pid = fork();

  if (pid == 0)
  {
    FILE *logs = fopen("logs.txt", "a+");
    pid_t ppid = getpid();

    if (logs == NULL)
    {
      perror("Error opening file");
      kill(ppid, SIGTERM);
    }
    else
    {
      fprintf(logs, "%s", "Mikael");
    }

    fclose(logs);
  }

  return 0;
}

void sig_handler(int sigNum)
{
  if (sigNum == SIGTERM)
  {
    printf("SIGINT interrupt Received - File IO failed\n");
  }
}