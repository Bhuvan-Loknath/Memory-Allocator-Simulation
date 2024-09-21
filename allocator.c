#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/****** Global Declarations ******/
typedef struct MemoryBlock {
    int start_address;
    int size;
    char process_id[10];
    struct MemoryBlock* next;
} MemoryBlock;

MemoryBlock* memory_head = NULL;
int max_memory = 0;

/*
 * Allocates memory based on the specified algorithm:
 * First Fit (F), Best Fit (B), or Worst Fit (W).
 */
void allocate_memory(char process_id[], int size, char strategy) {
    MemoryBlock* current = memory_head;
    MemoryBlock* best_fit = NULL;

    while (current != NULL) {
        if (strcmp(current->process_id, "Unused") == 0 && current->size >= size) {
            if (strategy == 'F') {
                break;
            } else if (strategy == 'B') {
                if (best_fit == NULL || current->size < best_fit->size) {
                    best_fit = current;
                }
            } else if (strategy == 'W') {
                if (best_fit == NULL || current->size > best_fit->size) {
                    best_fit = current;
                }
            }
        }
        current = current->next;
    }

    if (current == NULL) {
        if (strategy == 'F') {
            printf("Error: Not enough memory for process %s.\n", process_id);
            return;
        } else if (strategy == 'B' || strategy == 'W') {
            if (best_fit == NULL) {
                printf("Error: Not enough memory for process %s.\n", process_id);
                return;
            }
            current = best_fit;
        }
    }

    if (current->size == size) {
        strcpy(current->process_id, process_id);
    } else {
        MemoryBlock* new_block = (MemoryBlock*)malloc(sizeof(MemoryBlock));
        new_block->start_address = current->start_address + size;
        new_block->size = current->size - size;
        strcpy(new_block->process_id, "Unused");
        new_block->next = current->next;
        
        current->size = size;
        strcpy(current->process_id, process_id);
        current->next = new_block;
    }
    printf("Memory allocation successful for process %s\n", process_id);
}

/*
 * Releases the memory of a specified process.
 */
void release_memory(char process_id[]) {
    MemoryBlock* current = memory_head;

    while (current != NULL && strcmp(current->process_id, process_id) != 0) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Error: Process %s not found.\n", process_id);
        return;
    }

    strcpy(current->process_id, "Unused");
}

/*
 * Compacts all unused memory blocks into one.
 */
void compact_memory() {
    MemoryBlock* current = memory_head;
    MemoryBlock* prev_unused = NULL;
    MemoryBlock* prev_allocated = NULL;
    int start_address = 0;

    while (current != NULL) {
        if (strcmp(current->process_id, "Unused") == 0) {
            if (prev_unused != NULL) {
                prev_unused->size += current->size;
                prev_unused->next = current->next;
                free(current);
                current = prev_unused;
            } else {
                current->start_address = 0;
            }
            prev_unused = current;
        } else {
            if (prev_allocated != NULL) {
                prev_allocated->next = current;
            } else {
                memory_head = current;
            }
            current->start_address = start_address;
            start_address += current->size;
            prev_allocated = current;
        }
        current = current->next;
    }

    if (prev_allocated != NULL) {
        prev_allocated->next = NULL;
    }
}

/*
 * Displays the current memory allocation state.
 */
void print_memory_status() {
    MemoryBlock* current = memory_head;
    int end_address = 0;

    while (current != NULL) {
        printf("Addresses [%d:%d] Process %s\n", current->start_address, current->start_address + current->size - 1, current->process_id);
        end_address = current->start_address + current->size;
        current = current->next;
    }

    if (end_address < max_memory) {
        printf("Addresses [%d:%d] Unused\n", end_address, max_memory - 1);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <max_memory_size>\n", argv[0]);
        return 1;
    }

    max_memory = atoi(argv[1]);
    if (max_memory <= 0) {
        printf("Invalid max memory size.\n");
        return 1;
    }

    memory_head = (MemoryBlock*)malloc(sizeof(MemoryBlock));
    memory_head->start_address = 0;
    memory_head->size = max_memory;
    strcpy(memory_head->process_id, "Unused");
    memory_head->next = NULL;

    char command[20];
    char process_id[10];
    int size;
    char strategy;

    while (1) {
        printf("allocator> ");
        scanf("%s", command);

        if (strcmp(command, "RQ") == 0) {
            scanf("%s %d %c", process_id, &size, &strategy);
            if (strategy == 'W') {
                allocate_memory(process_id, size, 'W');
            } else {
                allocate_memory(process_id, size, strategy);
            }
        } else if (strcmp(command, "RL") == 0) {
            scanf("%s", process_id);
            release_memory(process_id);
        } else if (strcmp(command, "C") == 0) {
            compact_memory();
        } else if (strcmp(command, "STAT") == 0) {
            print_memory_status();
        } else if (strcmp(command, "X") == 0 || strcmp(command, "exit") == 0) {
            break;
        } else {
            printf("Invalid command.\n");
        }
    }

    MemoryBlock* current = memory_head;
    while (current != NULL) {
        MemoryBlock* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
