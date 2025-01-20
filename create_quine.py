if __name__ != '__main__':
    exit(0)

special_chars = {
    "\t": ("9", "%c"),
    "\n": ("10", "%c"),
    "\"": ("34", "%c"),
    "%": ("37", "%c"),
    "\\": ("92", "%c"),
}
from sys import argv, stderr
from pathlib import Path
import re

REGEX = r"char ([^ []+)+ *\[\d*\]"

if len(argv) != 2:
    print(f"Usage python {argv[0]} file", file=stderr)
    exit(1)

file: Path = Path(argv[1])
if not file.is_file():
    print(f"{file} is not a file", file=stderr)
    exit(1)

dest_bufname = "f"

format_args = []
normal = []
format_string = []
bufname = None
normal_insert_index = None
format_insert_index = None
with open(file, "r") as f:
    for line in f:
        normal += line
        format_line = ""
        for char in line:
            if char in special_chars.keys():
                format_args.append(special_chars[char][0])
                format_line += special_chars[char][1]
            else:
                format_line += char
                
        format_string.append(format_line)
        if line.endswith("// QUINE\n"):
            match = re.search(REGEX, line)
            if match is None:
                print("Expected buffer declaration on line ending with // QUINE", file=stderr)
                exit(0)
            bufname = match.group(1)
            normal_insert_index = len(normal)
            normal.append(None) # char* f = "format_string"
            normal.append(None) # sprintf(bufname, f, format_args...)
            format_string.append(f"char* {dest_bufname} = %c%s%c;")
            format_args.append("34")
            format_args.append(dest_bufname)
            format_args.append("34")
            format_insert_index = len(format_string)
            format_string.append(None) # sprintf(bufname, f, format_args...))

if bufname == None:
    print("No QUINE insertion point found", file=stderr)
    exit(1)
sprintf = f"sprintf({bufname}, {dest_bufname}, {",".join(format_args)});"
format_string[format_insert_index] = sprintf
normal[normal_insert_index] = f"char* {dest_bufname} = \"{"".join(format_string)}\";"
normal[normal_insert_index+1] = sprintf
print("".join(normal))
# char_f_equals = f"char* {dest_bufname} = "

    
# print("___NORMAL__")
# print(normal)
# print()
# print("___Format string___")
# print(format_string)
# print()
# print("___Format args___")
# print(format_args)