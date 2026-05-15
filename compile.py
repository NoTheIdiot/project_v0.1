1# remember that it's .img not .iso because you want to use FAT16
# and inject files

# oops i forgor that compile.py wasn't empty because i scrolled too far
# and now there are many import statements last time
# import modules
import subprocess
import shutil
import os

# global variables, like the full gcc command
gcc = "gcc -m32 -ffreestanding -nostdlib -Wall -Wextra -Werror -O2"

# define functions
def run_cmd(command):
    # run command using subprocess since it can output error messages
    subprocess.run(command, shell=True)

# main so it can infact, compile
with open("compilefile", "r") as file:
    random_var = 1                              # loop var for readability
    for doge in file:
        doge = doge.strip()                     # strip away newlines or spaces
        if doge.startswith("#") or not doge:    # if it's a comment or nothing
            continue                            # then continue

        elif doge.startswith("dogec"):
            shibe = doge.replace("32gcc", gcc)  # replace dogec with all of this bullshit

            random_string = str(random_var) + ""
            print(random_string + shibe)
            result = run_cmd(shibe)
            random_var += 1

        else:
            random_string = str(random_var) + ""
            print(random_string + shibe)
            result = run_cmd(shibe)
            random_var += 1

create_img = "dd if=/dev/zero of=windoge.img bs=1M count=256";
inject_windoge = "mcopy -i windoge.img windoge.bin a:"
run_cmd(create_img)
