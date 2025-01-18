Based on Ken Thompsons 1984 AM Turing Award Speech, "Reflections on Trusting Trust"  

This project is split into 3 steps:
1. Directly modifying login.c source code with a backdoor
2. Modifying the compiler to inject a backdoor into login.c during comptime

3. Modifying the compiler to inject a backdoor into itself during comptime, to inject the backdoor into login.c. This makes the backdoor undetectable, even with login.c and the compiler source code. 

Thank you @Rui314 for the C compiler source code. All I did was make the backdoor modifications. 

# Part 2 
```bash
cd login_mod_hidden
make
cp chibicc ..
cd ..
./chibicc -Ilogin_mod_hidden/include/ -o login login.c
./login
```
