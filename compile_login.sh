read -p "Compile unmodified(1) or modified login(2)? " WHICH
case $WHICH in
    1) 
        echo "Compiling unmodified login program (Output:login)"
        ./compiler -I./compiler_patched/include/ -o login ./unmodified/login.c 
        ;;
    2) 
        echo "Compiling modified login program (Output:login)"
        ./compiler -I./compiler_patched/include/ -o login ./unmodified/bad_login.c 
        ;;
    *)
        echo "Option not supported. Exiting..."
        exit 1
esac