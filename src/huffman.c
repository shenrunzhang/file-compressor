#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>

#include "../include/utils.h"
#include "../include/huffman.h"

// Function to create a min heap of given capacity
MinHeap *createMinHeap(int capacity)
{
    MinHeap *minHeap = (MinHeap *)Malloc(sizeof(MinHeap));
    minHeap->capacity = capacity;
    minHeap->size = 0;
    minHeap->array = (Node **)Malloc(capacity * sizeof(Node *));
    return minHeap;
}

// Min heapify function
void minHeapify(MinHeap *minHeap, int index)
{
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int min = index;

    // Checking whether our left or child element
    // is at right index or not to avoid index error
    if (left >= minHeap->size || left < 0)
        left = -1;
    if (right >= minHeap->size || right < 0)
        right = -1;

    // store left or right element in min if
    // any of these is smaller that its parent
    if (left != -1 && minHeap->array[left] < minHeap->array[index])
        min = left;
    if (right != -1 && minHeap->array[right] < minHeap->array[min])
        min = right;

    // Swapping the nodes
    if (min != index)
    {
        Node *temp = minHeap->array[min];
        minHeap->array[min] = minHeap->array[index];
        minHeap->array[index] = temp;

        // recursively calling for their child elements
        // to maintain min heap
        minHeapify(minHeap, min);
    }
}

/**
 * Helper function to insert a node into the min heap
 */
void insertHelper(MinHeap *heap, int index)
{

    // Store parent of element at index
    // in parent variable
    int parent = (index - 1) / 2;

    if (heap->array[parent]->freq > heap->array[index]->freq)
    {
        // Swapping when child is smaller
        // than parent element
        Node *temp = heap->array[parent];
        heap->array[parent] = heap->array[index];
        heap->array[index] = temp;

        // Recursively calling insertHelper
        insertHelper(heap, parent);
    }
}

/**
 * Builds a min heap from a given array of nodes
 */
void insertMinHeap(MinHeap *heap, Node *node)
{
    if (heap->size == heap->capacity)
    {
        app_error("Heap Overflow\n");
        return;
    }

    // Increase size and add node
    heap->array[heap->size] = node;
    // Calling insertHelper function
    insertHelper(heap, heap->size);
    // Incrementing size of array
    heap->size++;
}

/**
 * Extracts the minimum node from the min heap
 */
Node *extractMin(MinHeap *heap)
{
    // Base cases
    if (heap->size <= 0)
        return NULL;
    if (heap->size == 1)
    {
        heap->size--;
        return heap->array[0];
    }

    // Store the root node and remove it from heap
    Node *root = heap->array[0];
    Node *lastNode = heap->array[heap->size - 1];
    heap->array[0] = lastNode;
    heap->size--;
    minHeapify(heap, 0);

    return root;
}

/**
 * Build min heap from unordered array of nodes
 */
void buildMinHeap(MinHeap *heap)
{
    int n = heap->size;
    int i;
    for (i = (n / 2) - 1; i >= 0; i--)
        minHeapify(heap, i);
}

// Function to create a new node
Node *createNode(char data, int freq)
{
    Node *node = (Node *)Malloc(sizeof(Node));
    node->data = data;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}

/**
 * Function to build Huffman tree from given frequencies.
 * Build a min heap of nodes, then construct the huffman tree with the min heap.
 */
Node *buildHuffmanTree(char data[], int freq[], int size)
{

    // Define recurring variables
    Node *left, *right, *parent;

    // Create a new min heap
    MinHeap *heap = createMinHeap(size);

    // Create a node for each character and insert it into the min heap
    for (int i = 0; i < size; ++i)
        insertMinHeap(heap, createNode(data[i], freq[i]));

    while (heap->size != 1)
    {
        // Get two minimum nodes from min heap
        left = extractMin(heap);
        right = extractMin(heap);

        // Create new node and add it to min heap
        parent = createNode('$', left->freq + right->freq);
        parent->left = left;
        parent->right = right;

        insertMinHeap(heap, parent);
    }

    return extractMin(heap);
}

void printHeap(MinHeap *heap)
{
    printf("Min-Heap Structure:\n");
    for (int i = 0; i < heap->size; i++)
    {
        printf("Node[%d]: {data: %c, freq: %d}", i, heap->array[i]->data, heap->array[i]->freq);

        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < heap->size)
        {
            printf(", Left: {data: %c, freq: %d}", heap->array[left]->data, heap->array[left]->freq);
        }

        if (right < heap->size)
        {
            printf(", Right: {data: %c, freq: %d}", heap->array[right]->data, heap->array[right]->freq);
        }

        printf("\n");
    }
}
