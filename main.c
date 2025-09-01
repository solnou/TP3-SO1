#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
//#include "lib/memory/include/log.h"

int main() {
    
    //init_log("calls.log");

    // Test malloc
    void *ptr1 = malloc(100);
    if (ptr1 == NULL) {
        printf("malloc failed\n");
        //log_message("malloc failed");
        return 1;
    }
    printf("malloc successfully\n");

    // Test calloc
    void *ptr2 = calloc(10, 20);
    if (ptr2 == NULL) {
        printf("calloc failed\n");
        //log_message("calloc failed");
        return 1;
    }
    printf("calloc successfully\n");

    // Test realloc
    void *ptr3 = realloc(ptr1, 200);
    if (ptr3 == NULL) {
        printf("realloc failed\n");
        //log_message("realloc failed");
        return 1;
    }

    // Test free
    free(ptr2);
    free(ptr3);

    printf("Memory operations completed successfully\n");
    //close_log();
    
    return 0;
}
