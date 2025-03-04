# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Executables
EXE_LRU = cachemeifyoucan_lru
EXE_RR  = cachemeifyoucan_rr

# Source file
SRC = cachemeifyoucan.c
OBJ = cachemeifyoucan.o

# Default rule (build both LRU and RR executables)
all: $(EXE_LRU) $(EXE_RR)

# Rule for compiling the LRU version
$(EXE_LRU): $(OBJ)
	$(CC) $(OBJ) -o $(EXE_LRU)

# Rule for compiling the RR version (define RR_POLICY macro for RR policy)
$(EXE_RR): $(OBJ)
	$(CC) $(OBJ) -DRR_POLICY -o $(EXE_RR)

# Rule for compiling the object file
cachemeifyoucan.o: cachemeifyoucan.c
	$(CC) $(CFLAGS) -c cachemeifyoucan.c

# Clean rule to remove compiled files
clean:
	rm -f $(EXE_LRU) $(EXE_RR) $(OBJ)

# Phony targets (not actual files)
.PHONY: all clean
