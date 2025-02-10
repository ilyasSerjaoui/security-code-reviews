#include <stdio.h>
#include <string.h>

#define S 100
#define N 1000

int main(int argc, char *argv[]) {
  char out[S];
  char buf[N] = {0};  // Initialize buf to prevent garbage data
  char msg[] = "Welcome to the argument echoing program\n";

  printf("%s", msg);  // Correct way to print a string safely

  while (--argc > 0) {  // Loop through arguments safely
    snprintf(out, sizeof(out), "argument %d is %s\n", argc, argv[argc]);  
    strncat(buf, out, sizeof(buf) - strlen(buf) - 1);  
  }

  printf("%s", buf);  // Print the result safely
  return 0;
}
