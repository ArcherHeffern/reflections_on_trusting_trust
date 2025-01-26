from shutil import copytree, rmtree
from pathlib import Path
from sys import argv, stderr

PATCH_BEGIN = "// PATCH BEGIN"
PATCH_END = "// PATCH END"
SRC = Path("unmodified/c_compiler")
DEST = Path("compiler_patched")

if len(argv) != 2:
    print(f"Usage {argv[0]} patchfile", file=stderr)
    exit(1)
patchfile = Path(argv[1])
if not patchfile.exists():
    print(f"{patchfile} does not exist", file=stderr)
    exit(1)

def ignore(src, names: list[str]):
    ig = [name for name in names if name.endswith(".o")]
    ig.append("gcc")
    return ig

if DEST.exists():
    rmtree(DEST)
copytree(SRC, DEST, ignore=ignore)

with open(SRC / "tokenize.c", "r") as tok_in, open(DEST / "tokenize.c", "w") as tok_out, open(patchfile, "r") as patch_f:
    for line in tok_in:
        tok_out.write(line)
        if line == "    char* line = lines[i];\n":
            while patch_line := patch_f.readline():
                if patch_line.strip() == PATCH_BEGIN:
                    break
            while (patch_line := patch_f.readline()).strip() != PATCH_END:
                tok_out.write(patch_line)
                