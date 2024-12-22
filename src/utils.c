#include <stdio.h>
#include "../include/utils.h"
#include "../include/huffman.h"

/**************************
 * Error-handling functions
 **************************/
/* $begin errorfuns */
/* $begin unixerror */
void unix_error(char *msg) /* Unix-style error */
{
        fprintf(stderr, "%s: %s\n", msg, strerror(errno));
        exit(0);
}
/* $end unixerror */

void posix_error(int code, char *msg) /* Posix-style error */
{
        fprintf(stderr, "%s: %s\n", msg, strerror(code));
        exit(0);
}

void app_error(char *msg) /* Application error */
{
        fprintf(stderr, "%s\n", msg);
        exit(0);
}
/* $end errorfuns */

void dns_error(char *msg) /* Obsolete gethostbyname error */
{
        fprintf(stderr, "%s\n", msg);
        exit(0);
}

/***************************************************
 * Wrappers for dynamic storage allocation functions
 ***************************************************/

void *Malloc(size_t size)
{
        void *p;

        if ((p = malloc(size)) == NULL)
                unix_error("Malloc error");
        return p;
}

void *Realloc(void *ptr, size_t size)
{
        void *p;

        if ((p = realloc(ptr, size)) == NULL)
                unix_error("Realloc error");
        return p;
}

void *Calloc(size_t nmemb, size_t size)
{
        void *p;

        if ((p = calloc(nmemb, size)) == NULL)
                unix_error("Calloc error");
        return p;
}

void Free(void *ptr)
{
        free(ptr);
}

void FreeTree(Node *root)
{
        // Base case return
        if (root == NULL)
        {
                return;
        }

        // Recursively free
        FreeTree(root->left);
        FreeTree(root->right);

        // Free root
        Free(root);
}
