# Test Cases for Rod Cutting with Cache Policies

## Test Case 1: Simple Input Test
### Input
Rod lengths: `1 3 5`
Pieces:
1, 2 2, 5 3, 7 4, 8 5, 10


### Expected Output for LRU Policy:
Choose a policy (1 for LRU, 2 for RR): 1 Rod Length: 1, Max Value: 2 Rod Length: 3, Max Value: 7 Rod Length: 5, Max Value: 10



### Expected Output for RR Policy:
Choose a policy (1 for LRU, 2 for RR): 2 Rod Length: 1, Max Value: 2 Rod Length: 3, Max Value: 7 Rod Length: 5, Max Value: 10


---

## Test Case 2: Rod Length Exceeds Available Pieces
### Input
Rod lengths: `6 7 8`
Pieces:
1, 2 2, 5 3, 7 4, 8 5, 10



### Expected Output for LRU Policy:
Choose a policy (1 for LRU, 2 for RR): 1 Rod Length: 6, Max Value: 12 Rod Length: 7, Max Value: 14 Rod Length: 8, Max Value: 15



### Expected Output for RR Policy:
Choose a policy (1 for LRU, 2 for RR): 2 Rod Length: 6, Max Value: 12 Rod Length: 7, Max Value: 14 Rod Length: 8, Max Value: 15


---

## Test Case 3: Larger Rod Length with No Matching Pieces
### Input
Rod lengths: `15 20 25`
Pieces:
1, 1 2, 3 3, 5 4, 8 5, 12


### Expected Output for LRU Policy:
Choose a policy (1 for LRU, 2 for RR): 1 Rod Length: 15, Max Value: 28 Rod Length: 20, Max Value: 39 Rod Length: 25, Max Value: 49


### Expected Output for RR Policy:
Choose a policy (1 for LRU, 2 for RR): 2 Rod Length: 15, Max Value: 28 Rod Length: 20, Max Value: 39 Rod Length: 25, Max Value: 49


