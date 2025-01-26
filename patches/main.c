// PATCH BEGIN:tokenize.c:#include "chibicc.h"
void __hello() {
    printf("Hello world\n");
}
// PATCH END

int main() {

    // PATCH BEGIN:tokenize.c:static char *read_file(char *path) {
    __hello();
    // PATCH END
}