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


void print_value( int* ptr )
{
    std::cout << *ptr << std::endl;
}

void test_pointer()
{
    int* a = new int[5];
    for ( int i = 0; i < 5; i++ )
    {
        a[i] = i;
    }

    for ( int i = 0; i < 5; i++ )
    {
        print_value( &a[i] );
    }
}




int main() {
    std::cout << "Hello, World!" << std::endl;

//    test_double_free();

    test_pointer();


    return 0;
}