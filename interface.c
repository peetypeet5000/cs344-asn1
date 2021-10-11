#include "interface.h"

void user_menu(struct movie* list) {
    bool done = false;
    int selection = 0;

    while(done != true) {
        printf("\n1. Show movies released in the specified year\n2. Show highest rated movie for each year\n3. Show the title and year of release of all movies in a specific language\n4. Exit from the program\n\n");
        printf("Enter a choice from 1 to 4: ");
        scanf ("%d", &selection);

        switch(selection) {
            case 1:
                get_movies_year(list);
                break;
            
            case 2:
                break;

            case 3:
                break;
            // End Program
            case 4:
                done = true;
                break;

            // Invalid Choice
            default:
                printf("\nYou entered an incorrect choice. Try again.\n\n");
                break;
        }
    }
}


void get_movies_year(struct movie* list) {
    int year = 0;
    int movies_printed = 0;
    struct movie* curr = list;

    // Get user year input
    printf("\nEnter the year for which you want to see movies: ");
    scanf ("%d", &year);

    // If a valid year, traverse the linked list
    if (year >= 1900 && year <= 2021) {
        while (curr != NULL) {
            // If in the selected year, print the title
            if(curr->year == year) {
                movies_printed++;
                printf("\n%s", curr->title);
            }

            // Move to next node in list
            curr = curr->next;
        }
        printf("\n");

        if(movies_printed == 0) {
            printf("No movies were found for the selected year.\n");
        }
    } else {
        printf("\nYou entered an invalid year. Please try again\n");
        get_movies_year(list);
    }
}