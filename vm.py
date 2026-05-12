# import files
import subprocess

# functions to stop repeating subprocess.run(cmd, shell=True)
def run_cmd(command):
    subprocess.run(command, shell=True)

# main
qemu_command = "qemu-system-x86_64 -cdrom windoge.iso -m 16M -vga std"
run_cmd(qemu_command`)
