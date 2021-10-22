#include <stdio.h>
#include <unistd.h>

void print1();
void print2();

int main()
{
  for (int i = 0; i < 100; i++)
  {
    if (i % 10 == 0)
    {
      print2();
    }
    else
    {
      print1();
    }
  }
}

void print1()
{
  printf("Print 1\n");
};

void print2()
{
  printf("Print 2\n");
};