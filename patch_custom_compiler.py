from shutil import copytree, rmtree
from pathlib import Path
from sys import argv, stderr

PATCH_BEGIN = "// PATCH BEGIN:"
PATCH_END = "// PATCH END"
SRC = Path("unmodified/c_compiler")
DEST = Path("compiler_patched")

blocks: dict[str, str] = {}

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
    ig.append("compiler")
    ig.append("bad_compiler")
    return ig

if DEST.exists():
    rmtree(DEST)
copytree(SRC, DEST, ignore=ignore)


# Parse Blocks
with open(patchfile, "r") as patch_f:
    cur_block = []
    key = None
    for line in patch_f:
        if PATCH_END in line:
            if key is None:
                raise Exception("PATCH END found without PATCH BEGIN")
            blocks[key] = "".join(cur_block)
            key = None
            cur_block.clear()
        elif PATCH_BEGIN in line:
            if key is not None:
                raise Exception("PATCH BEGIN cannot exist in another block")
            ind = line.index(PATCH_BEGIN)
            key = line[ind+len(PATCH_BEGIN):]
        elif key is not None:
            cur_block.append(line)

with open(SRC / "tokenize.c", "r") as tok_in, open(DEST / "tokenize.c", "w") as tok_out, open(patchfile, "r") as patch_f:
    for line in tok_in:
        tok_out.write(line)
        if (block := blocks.get(line)) is not None:
            print("BOOM")
            tok_out.write(block)
                