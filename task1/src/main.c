#include <stdlib.h>

/*
  Not safe as environment variables can be atlered.
  Not safe when using with user input as malicious code or script can be ran from here. Must
  sanitize the input first.
*/
int main()
{
  system("ls -l");
  
  return 0;
}