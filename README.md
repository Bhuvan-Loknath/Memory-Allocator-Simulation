# Memory-Allocator-Simulation

This repository contains an implementation of a memory allocator that supports **First Fit**, **Best Fit**, and **Worst Fit** memory allocation strategies.

## Files in the Repository

- `allocator.c` - The main C program implementing the memory allocator.
- `Makefile` - A Makefile to compile `allocator.c`.
- `README.md` - Documentation for this project.

---

## Compilation, Usage, and Cleanup

The following code snippet will **compile**, **run**, and **clean up** the project:

```bash
# 1. Compile the code
make

# 2. Run the allocator with a maximum memory size (in bytes)
./allocator <max_memory_size>

# Example:
./allocator 1000

# 3. Enter commands to allocate, release, or compact memory:
# - 'RQ <process_id> <size> <strategy>' to request memory for a process
#   Example: RQ P1 100 F   # First Fit
# - 'RL <process_id>' to release memory from a process
#   Example: RL P1
# - 'C' to compact memory by merging all free blocks
# - 'STAT' to display the current memory allocation status
# - 'X' or 'exit' to quit the program

# 4. Clean up the compiled files
make clean
