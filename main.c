// (89110, Spring 2023, Assignment #6, Tom Sasson, 209379239, sassont5)

#include "Functions.h"
#include <stdio.h>

/**
 * @brief Main function that runs as a menu for the user to complete series of tasks.
 * @return 0 if the program ends.
 */

int main() {
    //declare variable for menu option
    char menuOption;

    //initialize linked list of family heads
    FamilyTree familyHeads;
    familyHeads.nextHead = NULL;
    familyHeads.children = NULL;
    familyHeads.siblings = NULL;
    familyHeads.spouse = NULL;
    familyHeads.data = NULL;
    familyHeads.parent = NULL;

    //print menu at least once, and get user's input in a loop
    do
    {
        //call function to print menu and receive input from user
        printMenu();
        scanf("%c", &menuOption);

        //put user's input into switch case
        switch (menuOption)
        {
            //exit menu
            case '0':
            {
                //free memory of all the program and exit
                freeAll(&familyHeads);
                break;
            }

                //Add a head
            case '1':
            {
                //call for function to handle case and return to menu
                case1(&familyHeads);
                break;
            }

                //Marry two people
            case '2':
            {
                //call for function to handle case and return to menu
                case2(&familyHeads);
                break;
            }

                //Add an offspring
            case '3':
            {
                //call for function to handle case and return to menu
                case3(&familyHeads);
                break;
            }

                //Print family top-down
            case '4':
            {
                //call for function to handle case and return to menu
                case4(&familyHeads);
                break;
            }

                //Years pass
            case '5':
            {
                //call for function to handle case and return to menu
                case5(&familyHeads);
                break;
            }

                //Count people
            case '6':
            {
                //call for function to handle case and return to menu
                countAll(&familyHeads);
                break;
            }

                //Print cousins
            case '7':
            {
                //call for function to handle case and return to menu
                case7(&familyHeads);
                break;
            }

                //new line entered
            case '\n':
            {
                scanf("%*c");
                printf("Invalid option\n");
                break;
            }

                //default - invalid input
            default:
            {
                printf("Invalid option\n");
                scanf("%*c");
                break;
            }
        }
    }

        //as long as zero is not entered, continue the loop
    while (menuOption != '0');

    //end of program
    return 0;
}