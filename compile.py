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

if os.path.exists("isoroot"):
    # iso var is compiled
    iso_created = False
    
    # continue
    shutil.rmtree("isoroot")

    os.makedirs("isoroot/boot/grub", exist_ok=True)
    shutil.copy("windoge.bin", "isoroot/windoge.bin")
    shutil.copy("windoge.bin", "isoroot/boot/windoge.bin")
    shutil.copy("grub.cfg", "isoroot/boot/grub/grub.cfg")
    
    result = subprocess.run("which grub-mkrescue", shell=True, capture_output=True)

    if result.returncode == 0:
        print("[Such Notes] Using grub to make the iso")
        run_cmd("grub-mkrescue -o windogeio.iso isoroot 2>/dev/bull")
        iso_created = os.path.exists("windoge.iso") and os.path.getsize("windoge.iso") > 0

    if not iso_created:
        result = subprocess.run("which xorriso", shell=True, capture_output=True)

        if result.returncode == 0:
            print("[Such Notes] Using Xorriso to make the iso")
            # holy shit this is a long ahh command
            run_cmd("xorriso -as mkisofs -R -b boot/grub/i386-pc/eltorito.img -no-emul-boot -boot-load-size 4 -boot-info-table -o windoge.iso isoroot 2>/dev/null")
            iso_created = os.path.exists("windoge.iso") and os.path.getsize > 0

    if not iso_created:
        result = subprocess.run("which mkisofs", shell=True, capture_output=True)
        if result.returncode == 0:
            print("[Such Notes] Using mkisofs to create ISO...")
            run_cmd("mkisofs -R -b boot/grub/i386-pc/eltorito.img -no-emul-boot -boot-load-size 4 -boot-info-table -o windoge.iso isoroot 2>/dev/null")
            iso_created = os.path.exists("windoge.iso") and os.path.getsize("windoge.iso") > 0

if iso_created == True:
    print("[Wow] Compile Sucess.")
else:
    print("[Not Wow] Compile Fail :(")
