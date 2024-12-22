#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include <stdio.h>

// Define a structure for a node in Huffman tree
typedef struct Node
{
        char data;
        int freq;
        struct Node *left;
        struct Node *right;
} Node;

// Define a min heap structure for a Huffman tree
typedef struct MinHeap
{
        int capacity;
        int size;
        Node **array;
} MinHeap;

// Function signatures for Huffman coding
Node *buildHuffmanTree(char data[], int freq[], int size);

// Function signatures for min heap
MinHeap *createMinHeap(int capacity);
Node *createNode(char data, int freq);
void minHeapify(MinHeap *minHeap, int index);
void insertHelper(MinHeap *heap, int index);
void insertMinHeap(MinHeap *heap, Node *node);
Node *extractMin(MinHeap *heap);
void buildMinHeap(MinHeap *heap);
void printHeap(MinHeap *heap);

#endif