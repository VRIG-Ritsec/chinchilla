# KVM_Chinchilla 
![image](https://github.com/user-attachments/assets/230c13db-b55e-4a03-8a92-cd14de266f9f)

## Install 
### Prerequisites
The project requires a cross-compilation toolchain for both i386 and x86_64 architectures. These toolchains are downloaded and extracted automatically by the `setup.sh` script. Ensure you have `git`, `make`, and `bash` installed on your system.

To set up the project, follow these steps:
```bash 
git clone https://github.com/ex4722/KVM_Chinchilla
cd KVM_Chinchilla
bash setup.sh
```

This script will download the necessary toolchains and extract them into the following directories:
- `toolchain/i386`
- `toolchain/x64_86`

## Building 

The provided Makefile handles the kernel setup and compilation for both architectures. All build artifacts are placed in their respective `build` directories:
- `x64_86/build`
- `i386/build`

To build the project, simply run:
```bash 
make
```
This will compile all required objects and binaries for both architectures.

## Running the kernel
You can launch the kernel using the `start.sh` script, which is also invoked automatically by the `Makefile` when running the kernel.

**Note**: The kernel is launched in a `tmux` session, so ensure that tmux is installed on your system. If no session is active, the script will fail to run as expected.

Additionally, the kernel is started with the `-s -S` flag, which pauses execution and waits for a `gdbserver` connection before proceeding. The `gdb.sh` script is a wrapper around `gdb` and the project's custom `gdbscript`, allowing easy connection to the waiting `gdbserver`.

**To start the kernel:**
You have a few options to start the kernel:
```bash 
chmod +x ./run_kernel.sh
./run_kernel.sh
```
or: 
```bash 
make run
```
This will launch the kernel in a paused state, awaiting gdb connection. You can connect gdb to the kernel using the provided gdb.sh script manually or just the run the `Makefile` or `start.sh` to automatically connect.
