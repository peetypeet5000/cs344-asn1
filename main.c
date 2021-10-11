#include "main.h"

/* Parse the current line which is space delimited and create a
*  movie struct with the data in this line
*/
struct movie *createMovie(char *currLine)
{
    struct movie *currMovie = malloc(sizeof(struct movie));

    // For use with strtok_r
    char *saveptr;
    char *langptr;

    // Get title
    char *token = strtok_r(currLine, ",", &saveptr);
    currMovie->title = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->title, token);

    // Get year
    token = strtok_r(NULL, ",", &saveptr);
    // Convert to an int
    int year_int = atoi(token);
    currMovie->year = year_int;

    // Get lang array
    token = strtok_r(NULL, ",", &saveptr);
    // Allocate space for the array excluding the []
    char* lang_array = calloc(strlen(token) - 1, sizeof(char));
    // Copy string without first and last char
    strncpy(lang_array, token + 1, strlen(token) - 2);

    // Get first language token
    int lang_num = 0;
    token = strtok_r(lang_array, ";", &langptr); 
    // Keep tokenizing until no more
    while(token != NULL) {
        // Allocated space, copy in, get next token
        currMovie->langs[lang_num] = calloc(strlen(token) + 1, sizeof(char));
        strcpy(currMovie->langs[lang_num++], token);
        token = strtok_r(NULL, ";", &langptr);
    }
    // Save the number of languages in the struct
    currMovie->num_langs = lang_num;

    

    // Get rating
    token = strtok_r(NULL, ",", &saveptr);
    // Convert to a float
    float rating_float = atof(token);
    currMovie->rating = rating_float;

    // Set the next node to NULL in the newly created movies entry
    currMovie->next = NULL;

    return currMovie;
}

/*
* Return a linked list of movies by parsing data from
* each line of the specified file.
*/
struct movie *processFile(char *filePath)
{
    // Open the specified file for reading only
    FILE *moviesFile = fopen(filePath, "r");

    char *currLine = NULL;
    size_t len = 0;
    ssize_t nread;

    // The head of the linked list
    struct movie *head = NULL;
    // The tail of the linked list
    struct movie *tail = NULL;

    //Skip first line
    nread = getline(&currLine, &len, moviesFile);

    // Read the file line by line
    while ((nread = getline(&currLine, &len, moviesFile)) != -1)
    {
        // Get a new movie node corresponding to the current line
        struct movie *newNode = createMovie(currLine);

        // Is this the first node in the linked list?
        if (head == NULL)
        {
            // This is the first node in the linked link
            // Set the head and the tail to this node
            head = newNode;
            tail = newNode;
        }
        else
        {
            // This is not the first node.
            // Add this node to the list and advance the tail
            tail->next = newNode;
            tail = newNode;
        }
    }
    free(currLine);
    fclose(moviesFile);
    return head;
}

/*
* Print data for the given movie
*/
void printMovie(struct movie* a_movie){
  printf("%s, %i, %s %s %s %s %s %.1f\n", a_movie->title,
               a_movie->year,
               a_movie->langs[0],
               a_movie->langs[1],
               a_movie->langs[2],
               a_movie->langs[3],
               a_movie->langs[4],
               a_movie->rating);
}
/*
* Print the linked list of movies
*/
void printMoviesList(struct movie *list)
{
    while (list != NULL)
    {
        printMovie(list);
        list = list->next;
    }
}

/*
*   Process the file provided as an argument to the program to
*   create a linked list of movie structs and print out the list.
*   Compile the program as follows:
*       gcc --std=gnu99 -o movies main.c
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
    printMoviesList(list);
    return EXIT_SUCCESS;
}