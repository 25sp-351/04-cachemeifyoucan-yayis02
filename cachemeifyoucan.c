#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LEN 100

typedef struct {
    int length;
    int value;
} Piece;

typedef struct CacheNode {
    int rodLength;
    int maxValue;
    struct CacheNode *next;
    struct CacheNode *prev;
} CacheNode;

typedef struct {
    CacheNode *head;
    CacheNode *tail;
    int capacity;
    int size;
} Cache;

CacheNode *createCacheNode(int rodLength, int maxValue) {
    CacheNode *newNode = (CacheNode *)malloc(sizeof(CacheNode));
    newNode->rodLength = rodLength;
    newNode->maxValue  = maxValue;
    newNode->next = newNode->prev = NULL;
    return newNode;
}

Cache *createCache(int capacity) {
    Cache *cache = (Cache *)malloc(sizeof(Cache));
    cache->head = cache->tail = NULL;
    cache->capacity           = capacity;
    cache->size               = 0;
    return cache;
}

void removeCacheNode(Cache *cache, CacheNode *node) {
    if (!cache || !node)
        return;

    if (node->prev)
        node->prev->next = node->next;
    if (node->next)
        node->next->prev = node->prev;

    if (node == cache->head)
        cache->head = node->next;
    if (node == cache->tail)
        cache->tail = node->prev;

    free(node);
    cache->size--;
}

void addCacheNode(Cache *cache, int rodLength, int maxValue) {
    if (cache->size == cache->capacity)
        removeCacheNode(cache, cache->head);

    CacheNode *newNode = createCacheNode(rodLength, maxValue);
    if (cache->tail) {
        cache->tail->next = newNode;
        newNode->prev     = cache->tail;
    }
    cache->tail = newNode;
    if (!cache->head)
        cache->head = newNode;
    cache->size++;
}

int getLRUCacheValue(Cache *cache, int rodLength) {
    CacheNode *current = cache->head;
    while (current) {
        if (current->rodLength == rodLength) {

            if (current != cache->tail) {
                removeCacheNode(cache, current);
                addCacheNode(cache, rodLength, current->maxValue);
            }
            return current->maxValue;
        }
        current = current->next;
    }
    return -1;
}

int getRRCacheValue(Cache *cache, int rodLength) {
    CacheNode *current = cache->head;
    while (current) {
        if (current->rodLength == rodLength)
            return current->maxValue;
        current = current->next;
    }
    return -1;
}

void evictRandomCacheNode(Cache *cache) {
    if (cache->size == 0)
        return;

    int randIndex      = rand() % cache->size;
    CacheNode *current = cache->head;

    for (int i = 0; i < randIndex; i++)
        current = current->next;

    removeCacheNode(cache, current);
}

int getRRCacheValueWithEviction(Cache *cache, int rodLength) {
    CacheNode *current = cache->head;
    while (current) {
        if (current->rodLength == rodLength)
            return current->maxValue;
        current = current->next;
    }

    if (cache->size == cache->capacity)
        evictRandomCacheNode(cache);
    return -1;
}

int rodCutting(int rodLength, Piece pieces[], int n, Cache *cache, int policy) {
    int cachedValue;
    if (policy == 1)
        cachedValue = getLRUCacheValue(cache, rodLength);
    else
        cachedValue = getRRCacheValue(cache, rodLength);

    if (cachedValue != -1)
        return cachedValue;

    int *dp = (int *)malloc((rodLength + 1) * sizeof(int));
    dp[0]   = 0;

    for (int i = 1; i <= rodLength; i++) {
        dp[i] = 0;
        for (int j = 0; j < n; j++) {
            if (pieces[j].length <= i) {
                dp[i] = (dp[i] > pieces[j].value + dp[i - pieces[j].length])
                            ? dp[i]
                            : pieces[j].value + dp[i - pieces[j].length];
            }
        }
    }

    if (policy == 1) {
        addCacheNode(cache, rodLength, dp[rodLength]);
    } else if (cache->size < cache->capacity) {
        addCacheNode(cache, rodLength, dp[rodLength]);
    } else {
        evictRandomCacheNode(cache);
        addCacheNode(cache, rodLength, dp[rodLength]);
    }

    free(dp);
    return dp[rodLength];
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
        return 1;
    }

    srand(time(NULL));

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    Piece pieces[MAX_LEN];
    int n = 0;
    while (fscanf(file, "%d, %d\n", &pieces[n].length, &pieces[n].value) == 2)
        n++;
    fclose(file);

    Cache *cache = createCache(5);

    int rodLength;
    int policy;
    printf("Choose a policy (1 for LRU, 2 for RR): ");
    scanf("%d", &policy);

    while (scanf("%d", &rodLength) != EOF) {
        int maxValue = rodCutting(rodLength, pieces, n, cache, policy);
        printf("Rod Length: %d, Max Value: %d\n", rodLength, maxValue);
    }

    return 0;
}
