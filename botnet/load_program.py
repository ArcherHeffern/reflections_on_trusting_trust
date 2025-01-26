INPUT = "install_botnet.c"
DEST = "install_botnet_loaded.c"
PROG_PATH = "./hello.py"
with open(INPUT, "r") as inf, open(DEST, "w+") as outf:
    for line in inf:
        if line == "#define PROGRAM \"\"\n":
            with open(PROG_PATH, "rb") as progf:
                prog = progf.read()
            prog = prog.decode()
            prog = prog.replace("\"", "\\\"")
            prog = prog.replace("\'", "\\'")
            prog = prog.replace("\n", "\\n")
            prog = prog.replace("\t", "\\t")
            line = f"#define PROGRAM \"{prog}\"\n"
        outf.write(line)
    