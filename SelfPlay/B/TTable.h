#ifndef __TTABLE_H
#define __TTABLE_H

#include <pthread.h>
#include "Board.h"

#define EXACT 1
#define LOWERBOUND 2
#define UPPERBOUND 3

#define MAX_NODES 16777216
#define NUM_BUCKETS 2097152
#define BUCKET_SIZE 2

#define KEY_SIZE 9

typedef struct Node{
	int * key;
	int value;
	int depth;
	int type;
	int turn;
} Node;

typedef struct Bucket{
	int max;
	int size;
	pthread_mutex_t lock;
	Node ** nodes;
} Bucket;

typedef struct TTable{
	int size;
	int totalNodes;
	Bucket * buckets[NUM_BUCKETS];
} TTable;

Node * createNode(int * key, int value, int depth, int type, int turn);
Bucket * createBucket(int num);
TTable * createTTable();

int getNonEmptyBucketCount(TTable * table);

int getNodeType(int alpha, int beta, int value);
void setNodeType(Node * node, int alpha, int beta, int value);
Node * getNode(TTable * table, int hash, int * key);
void storeNode(TTable * table, int hash, Node * node);

int * createKey(Board * board);
int createHash(int * key);
 
#endif