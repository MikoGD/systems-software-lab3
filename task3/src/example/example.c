#include <stdio.h>
#include <unistd.h>

int main()
{
  printf("Starting loop\n");
  for (int i = 0; i < 100; i++)
  {
    printf("iteration: %d\n", i);
    sleep(10);
  }

  return 0;
}