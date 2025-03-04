#!/bin/bash

# Compile the program
make clean
make

# Test Case 1: Simple Input Test
echo "Running Test Case 1: Simple Input Test (LRU)"
echo "1" | ./cachemeifyoucan_lru rod_lengths.txt
echo "3" | ./cachemeifyoucan_lru rod_lengths.txt
echo "5" | ./cachemeifyoucan_lru rod_lengths.txt

echo "Running Test Case 1: Simple Input Test (RR)"
echo "1" | ./cachemeifyoucan_rr rod_lengths.txt
echo "3" | ./cachemeifyoucan_rr rod_lengths.txt
echo "5" | ./cachemeifyoucan_rr rod_lengths.txt

# Test Case 2: Rod Length Exceeds Available Pieces
echo "Running Test Case 2: Rod Length Exceeds Available Pieces (LRU)"
echo "6" | ./cachemeifyoucan_lru rod_lengths.txt
echo "7" | ./cachemeifyoucan_lru rod_lengths.txt
echo "8" | ./cachemeifyoucan_lru rod_lengths.txt

echo "Running Test Case 2: Rod Length Exceeds Available Pieces (RR)"
echo "6" | ./cachemeifyoucan_rr rod_lengths.txt
echo "7" | ./cachemeifyoucan_rr rod_lengths.txt
echo "8" | ./cachemeifyoucan_rr rod_lengths.txt

# Test Case 3: Larger Rod Length with No Matching Pieces
echo "Running Test Case 3: Larger Rod Length with No Matching Pieces (LRU)"
echo "15" | ./cachemeifyoucan_lru rod_lengths.txt
echo "20" | ./cachemeifyoucan_lru rod_lengths.txt
echo "25" | ./cachemeifyoucan_lru rod_lengths.txt

echo "Running Test Case 3: Larger Rod Length with No Matching Pieces (RR)"
echo "15" | ./cachemeifyoucan_rr rod_lengths.txt
echo "20" | ./cachemeifyoucan_rr rod_lengths.txt
echo "25" | ./cachemeifyoucan_rr rod_lengths.txt

# Cleanup
make clean
