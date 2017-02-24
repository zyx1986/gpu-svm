#include <iostream>

/**
 * test for double free.
 * the result shows that it is wrong
 */
void test_double_free ()
{
    int* a = (int*) malloc( sizeof(int) * 4 );
    int* b = (int*) realloc( a, sizeof(int) * 6 );

    free(b);

    std::cout << "successful in freeing b!" << std::endl;


    free(a);

    std::cout << "successful in freeing a!" << std::endl;
}


int main() {
    std::cout << "Hello, World!" << std::endl;

    test_double_free();



    return 0;
}