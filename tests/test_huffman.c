#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../include/huffman.h"
#include "../include/utils.h"

void test_createMinHeap()
{
        MinHeap *heap = createMinHeap(10);
        CU_ASSERT_PTR_NOT_NULL(heap);
        CU_ASSERT_EQUAL(heap->capacity, 10);
        CU_ASSERT_EQUAL(heap->size, 0);
        Free(heap);
}

void test_insertAndExtractMin()
{
        MinHeap *heap = createMinHeap(5);
        Node *node1 = createNode('a', 100);
        Node *node2 = createNode('b', 90);
        Node *node3 = createNode('c', 50);
        Node *node4 = createNode('d', 70);
        insertMinHeap(heap, node1);
        printHeap(heap);
        insertMinHeap(heap, node2);
        printHeap(heap);
        insertMinHeap(heap, node3);
        printHeap(heap);
        insertMinHeap(heap, node4);
        printHeap(heap);

        Node *minNode = extractMin(heap);
        CU_ASSERT_EQUAL(minNode->data, 'c');
        CU_ASSERT_EQUAL(minNode->freq, 50);

        Free(minNode);
        Free(heap);
}

void test_buildHuffmanTree()
{
        char data[] = {'a', 'b', 'c', 'd'};
        int freq[] = {5, 9, 12, 13};
        int size = sizeof(data) / sizeof(data[0]);

        Node *root = buildHuffmanTree(data, freq, size);
        CU_ASSERT_PTR_NOT_NULL(root);
        CU_ASSERT_EQUAL(root->freq, 39); // Root frequency is sum of all.

        FreeTree(root);
}

// void test_generateCodes() {
//     char data[] = {'a', 'b', 'c', 'd'};
//     int freq[] = {5, 9, 12, 13};
//     int size = sizeof(data) / sizeof(data[0]);

//     Node* root = buildHuffmanTree(data, freq, size);
//     char* huffmanTable[256] = {NULL};
//     char code[256];
//     generateCodes(root, code, 0, huffmanTable);

//     assert(huffmanTable['a'] != NULL);
//     assert(huffmanTable['b'] != NULL);

//     for (int i = 0; i < 256; i++) {
//         Free(huffmanTable[i]);
//     }
//     FreeTree(root);
// }

// void test_encodeAndDecode() {
//     char input[] = "abcd";
//     char data[] = {'a', 'b', 'c', 'd'};
//     int freq[] = {5, 9, 12, 13};
//     int size = sizeof(data) / sizeof(data[0]);

//     Node* root = buildHuffmanTree(data, freq, size);
//     char* huffmanTable[256] = {NULL};
//     char code[256];
//     generateCodes(root, code, 0, huffmanTable);

//     char* encodedData = encodeData(input, huffmanTable);
//     char* decodedData = decodeData(encodedData, root);

//     assert(strcmp(input, decodedData) == 0);  // Original equals decoded.

//     Free(encodedData);
//     Free(decodedData);
//     for (int i = 0; i < 256; i++) {
//         Free(huffmanTable[i]);
//     }
//     FreeTree(root);
// }

int main()
{
        if (CUE_SUCCESS != CU_initialize_registry())
        {
                return CU_get_error();
        }

        CU_pSuite suite = CU_add_suite("Huffman_Test_Suite", NULL, NULL);
        if (suite == NULL)
        {
                CU_cleanup_registry();
                return CU_get_error();
        }

        if (CU_add_test(suite, "test_createMinHeap", test_createMinHeap) == NULL)
        {
                CU_cleanup_registry();
                return CU_get_error();
        }

        if (CU_add_test(suite, "test_insertAndExtractMin", test_insertAndExtractMin) == NULL)
        {
                CU_cleanup_registry();
                return CU_get_error();
        }
        if (CU_add_test(suite, "test_buildHuffmanTree", test_buildHuffmanTree) == NULL)
        {
                CU_cleanup_registry();
                return CU_get_error();
        }

        CU_basic_set_mode(CU_BRM_VERBOSE); // Verbose mode for test results
        CU_basic_run_tests();
        CU_cleanup_registry();

        return CU_get_error();
}
