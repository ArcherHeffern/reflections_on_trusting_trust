from shutil import copytree, rmtree
from os import rename
from tempfile import NamedTemporaryFile
from collections import defaultdict
from pathlib import Path
from sys import argv, stderr
from typing import Optional

# PATCH BEGIN:<file>:<line>
PATCH_BEGIN = "// PATCH BEGIN:"
PATCH_END = "// PATCH END"
SRC = Path("unmodified/c_compiler")
DEST = Path("compiler_patched")

blocks: defaultdict[Path, dict[str, str]] = defaultdict(dict) # (file) -> ((line) -> block)

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
    location: Optional[tuple[Path, str]] = None # Path, line
    cur_block = []
    for line in patch_f:
        if PATCH_END in line:
            if location is None:
                raise Exception("PATCH END found without PATCH BEGIN")
            blocks[location[0]][location[1]] = "".join(cur_block)
            location = None
            cur_block.clear()
        elif PATCH_BEGIN in line:
            if location is not None:
                raise Exception("PATCH BEGIN cannot exist in another block")
            try:
                _, f, l = line.split(":", 2)
            except:
                raise Exception(f"Expected {PATCH_BEGIN}:<file>:<line> but found {line}")
            f = DEST / f
            if not f.is_file():
                raise Exception(f"{f} does not exist")
            location = (f, l)
        elif location is not None:
            cur_block.append(line)
    if location is not None:
        raise Exception("PATCH BEGIN left without a closing PATCH END")

for basename, dirs, files in DEST.walk():
    for file in files:
        if basename / file in blocks:
            with open(basename / file, "r") as tok_in, NamedTemporaryFile("w", delete=False) as tf:
                tempname = tf.name
                for line in tok_in:
                    tf.write(line)
                    if (block := blocks[basename/file].get(line)) is not None:
                        print("injecting", line)
                        tf.write(block)
            rename(tempname, basename / file)
                