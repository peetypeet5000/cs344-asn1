#include "interface.h"

void user_menu(struct movie* list) {
    bool done = false;
    int selection = 0;

    while(done != true) {
        printf("\n1. Show movies released in the specified year\n2. Show highest rated movie for each year\n3. Show the title and year of release of all movies in a specific language\n4. Exit from the program\n\n");
        printf("Enter a choice from 1 to 4: ");
        scanf ("%d", &selection);

        switch(selection) {
            // Get movies for a certain year
            case 1:
                get_movies_year(list);
                break;
            
            case 2:
                get_movies_rating(list);
                break;

            // Get movies for a certain language
            case 3:
                get_movies_lang(list);
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


void get_movies_lang(struct movie* list) {
    char lang[20];
    int movies_printed = 0;
    struct movie* curr = list;

    // Get user language input
    printf("\nEnter the language for which you want to see movies: ");
    scanf ("%19s", &lang);

    while (curr != NULL) {
        for(int i = 0; i < curr->num_langs; i++) {
            if(strncmp(curr->langs[i], lang, strlen(curr->langs[i])) == 0) {
                printf("\n%d %s", curr->year, curr->title);
                movies_printed++;
            }
        }

        // Move to next node in list
        curr = curr->next;
    }
    printf("\n");

    if(movies_printed == 0) {
        printf("No movies were found for the entered language.\n");
    }
}


void get_movies_rating(struct movie* list) {
    struct movie* curr = list;
    struct movie highest;

    // Loop thru each year 
    for(int i = 1900; i < 2022; i++) {
        // Reset highst rating tracker
        highest.rating = 0.0;
        
        // Loop thru list, keep track of highest
        while (curr != NULL) {
            if(curr->year == i) {
                // If found a higher, record the rating and title
                if(curr->rating > highest.rating){
                    //highest.title = calloc(strlen(curr->title), sizeof(char));
                    highest.title = curr->title;
                    highest.rating = curr->rating;
                }
            }
        // Move to next node in list
        curr = curr->next;
        }

        //Once traversed whole list, print highest(if any)
        if(highest.rating > 0.0) {
            printf("\n%d %.1f %s", i, highest.rating, highest.title);
        }

        // Reset to head of list
        curr = list;
    }
    printf("\n");
}