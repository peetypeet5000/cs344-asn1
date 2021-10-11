#include "main.h"

/*
*   Process the file provided as an argument to the program to
*   create a linked list of movie structs and print out the list.
*/

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("You must provide the name of the file to process\n");
        printf("Example usage: ./movies movies_sample_1.csv\n");
        return EXIT_FAILURE;
    }
    struct movie *list = processFile(argv[1]);

    user_menu(list);
    
    return EXIT_SUCCESS;
}