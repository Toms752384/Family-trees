//
// Created by toms7 on 3/30/2024.
//

#include "Functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/**
 * @brief printMenu function that prints a menu for the user.
 * @return void.
 */

void printMenu() {
    //print menu
    printf("Choose an option:\n");
    printf("0. Exit\n");
    printf("1. Add a head\n");
    printf("2. Marry two people\n");
    printf("3. New offspring\n");
    printf("4. Print family top-down\n");
    printf("5. Years pass\n");
    printf("6. Count people\n");
    printf("7. Print cousins\n");
}

/**
 * @brief freeAll take a pointer to the main linked list and using two local pointers and a
 * temp pointer to iterate on all the elements of the list and free them. Also uses recursive function
 * to free children.
 * @param familyHeads is a pointer to the main linked list.
 * @return void.
 */

void freeAll(FamilyTree *familyHeads) {
    //create a pointer to the head of the list and a temp pointer
    FamilyTree *currentHead = familyHeads->nextHead;
    FamilyTree *temp = NULL;

    //loop to delete every element in the list
    while (currentHead != NULL) {
        //advance the temp pointer and current head
        temp = currentHead;
        currentHead = currentHead->nextHead;

        //check if current head has children. if so, free them
        if(temp->children != NULL) {
            freeChild(temp->children);
        }

        //when finished with the children of the family head, free the head
        free(temp->data->name);
        free(temp->data);
        free(temp);
    }
}

/**
 * @brief freeChild takes a pointer to a child, frees of all it's siblings, and checks if one of the
 * siblings has children. if so, calls the function again to free all of it's children.
 * @param child is a pointer to the child we want to delete.
 * @return void.
 */

void freeChild(FamilyTree *child) {
    //create pointer to the beginning of the list of children, and a temp pointer
    FamilyTree *currentChild = child;
    FamilyTree *temp = NULL;

    //loop on all the siblings
    while (currentChild != NULL) {
        //advance the temp pointer and the current child
        temp = currentChild;
        currentChild = currentChild->siblings;

        //check if the current child has children, and call function if so
        if(temp->children != NULL) {
            freeChild(temp->children);
        }

        //free the current child
        free(temp->data->name);
        free(temp->data);
        free(temp);
    }
}

/**
 * @brief case1 handles the case of adding new family heads.
 * @param familyHeads is a pointer to the linked list.
 * @return void.
 */

void case1(FamilyTree *familyHeads) {
    //ignore new line
    scanf("%*c");

    //create new person
    Person *newPerson = createPerson(familyHeads);

    //ignore new line
    scanf("%*c");

    //check if the name already is taken
    if(checkName(newPerson->name, familyHeads) != NULL) {
        //print message for user, free memory and return
        printf("The name is already taken\n");
        free(newPerson->name);
        newPerson->name = NULL;
        free(newPerson);
        return;
    }

    //if not taken, add new family head
    addHead(&(familyHeads->nextHead), newPerson, familyHeads);
}

/**
 * @brief receiveString takes a pointer a string,receives user input for a name and
 * allocates memory to the string with every input.
 * @param familyHeads is a pointer to the linked list.
 * @param name is a pointer to a string.
 * @return the pointer to the string.
 */

char* receiveString(char *name, FamilyTree *familyHeads) {
    //declare variable for a letter, and a variable to help keep track of the length of the string
    char letter;
    int length = 0;

    //assign null value to initialize string
    name[0] = '\0';

    //in a loop, receive user input for the letters and allocate memory for each letter
    while(1) {
        //receive input of letters
        scanf("%c", &letter);

        //if new line entered - exit loop
        if(letter == '\n') {
            break;
        }

        //declare pointer to check if realloc function failed
        char *checkPointer = name;

        //allocate memory for a new letter and check if failed
        checkPointer = (char*) realloc(name, (strlen(name)+2)* sizeof(char));
        if(checkPointer == NULL) {
            free(name);
            freeAll(familyHeads);
            exit(1);
        }

        else {
            name = checkPointer;
        }

        //assign letter to the string
        strncat(name, &letter, 1);

        //increase length by 1
        length++;
    }

    //assign null to the end of the string
    name[length] = '\0';

    //return finished string
    return name;
}

/**
 * @brief checkName takes the list of family heads and check if a given name is already taken
 * in the list.
 * @param familyHeads is a pointer to the linked list.
 * @param name is a pointer to a string.
 * @return NULL if did not find a name, or a pointer to the family tree containing it.
 */

FamilyTree *checkName(char *name, FamilyTree *familyHeads) {
    //declare pointer to the head of the list
    FamilyTree *currentHead = familyHeads->nextHead;

    //loop on all the heads
    while (currentHead != NULL) {
        //compare the string to the string in the head
        if(strcmp(name, currentHead->data->name) == 0) {
            return currentHead;
        }

        //check if the current head has children. if so, call function to check them as well
        if(currentHead->children != NULL) {
            FamilyTree *temp = NULL;
            temp = checkChild(name, currentHead->children);

            //if the current head isn't null, return it
            if(temp != NULL) {
                return temp;
            }
        }

        //advance pointer to the next node
        currentHead = currentHead->nextHead;
    }

    //if did not find a matching name, return NULL
    return NULL;
}

/**
 * @brief checkChild takes the list of family heads and checks if a given name is already taken
 * in the list of it's siblings. if has chlidren, checks them too, bt calling the function again.
 * Base of recursion: if reached the end of the list of siblings, and no one has children, return null.
 * step: check the children of the given child.
 * @param familyHeads is a pointer to the linked list.
 * @param name is a pointer to a string.
 * @return NULL if did not find a name, or a pointer to the family tree containing if it is.
 */

FamilyTree *checkChild(char *name, FamilyTree *children) {
    //create pointer to the beginning of the list of children
    FamilyTree *currentChild = children;

    //loop on all it's siblings, and check if name is taken
    while (currentChild != NULL) {
        //compare the current child to the given name
        if(strcmp(currentChild->data->name, name) == 0 ) {
            return currentChild;
        }

        //check if the current child has children
        if(currentChild->children != NULL) {
            FamilyTree *temp = NULL;
            temp = checkChild(name, currentChild->children);

            //if the current head isn't null, return it
            if(temp != NULL) {
                return temp;
            }
        }

        //advance to the next child in the list
        currentChild = currentChild->siblings;
    }

    //if passed all tests, return null
    return NULL;
}

/**
 * @brief createNewHead receives pointer to data - struct, and a pointer to
 * the linked list of family heads, allocates new memory for a new family head, and returns a pointer to it.
 * @param data receives data to add to node - a struct.
 * @param familyHead is a pointer to the bank.
 * @return pointer to family head.
 */

FamilyTree *createNewHead(Person *data, FamilyTree *familyHead) {
    //create new node and a pointer to its memory in the heap
    FamilyTree *newHead = (FamilyTree*) malloc(sizeof(FamilyTree));

    //check if allocation failed
    if(newHead == NULL) {
        freeAll(familyHead);
        exit(1);
    }

    //if allocation worked, assign value of data, and a null values
    newHead->data = data;
    newHead->nextHead = NULL;
    newHead->children = NULL;
    newHead->siblings = NULL;
    newHead->spouse = NULL;
    newHead->parent = NULL;

    //return the pointer
    return newHead;
}

/**
 * @brief addHead receives pointer to a struct of a person, address of the linked list of family heads
 * and a pointer to the main linked list, and adds the new node in the end of the linked list.
 * @param trees is the address of the linked list of family heads.
 * @param data is a pointer to person struct.
 * @param familyHeads is a pointer to the main linked list
 * @return void.
 */

void addHead(FamilyTree **trees, Person *data, FamilyTree *familyHeads) {
    //create a family head using the createNewHead function and assign pointer to it
    FamilyTree *newHead = createNewHead(data, familyHeads);

    //if the list is empty then assign the head directly
    if(*trees == NULL) {
        *trees = newHead;
    }

        //if the list is not empty
    else {
        //create a temp pointer and point to the head of the list, and a counter
        FamilyTree *temp = *trees;

        //loop until we reach the end of the list
        while (temp->nextHead != NULL) {
            //advance the temp pointer to point to the next element, and increase counter
            temp = temp->nextHead;
        }

        //assign the new head into the temp
        temp->nextHead = newHead;
    }
}

/**
 * @brief createPerson receives a pointer to the linked list of heads, receives user input for
 * unsigned int for age, a string for name, creates a person struct and returns a pointer to this struct.
 * @param familyHeads is a pointer to the linked list.
 * @return pointer to the new person.
 */

Person *createPerson(FamilyTree *familyHeads) {
    //allocate memory for person and assign a pointer to it
    Person *newPerson = (Person*) malloc(sizeof(Person));

    //check if allocation failed
    if(newPerson == NULL) {
        freeAll(familyHeads);
        exit(1);
    }

    //allocate memory for new name and check if failed
    newPerson->name = (char*) malloc(sizeof(char));
    if(newPerson->name == NULL) {
        free(newPerson);
        freeAll(familyHeads);
        exit(1);
    }

    //print message for user and receive string
    printf("Enter a name:\n");
    newPerson->name = receiveString(newPerson->name, familyHeads);

    //print message for user and receive number
    printf("Enter age:\n");
    scanf("%u", &(newPerson->age));

    //return the pointer to the new person
    return newPerson;
}

/**
 * @brief case2 handles the case of marrying two people.
 * @param familyHeads is a pointer to the linked list.
 * @return void.
 */

void case2(FamilyTree *familyHeads) {
    //ignore new line
    scanf("%*c");

    //allocate memory for first string and check if failed
    char *firstPerson = (char*) malloc(sizeof(char));
    if(firstPerson == NULL) {
        freeAll(familyHeads);
        exit(1);
    }

    //receive user input for first string
    printf("Enter the name of the first person:\n");
    firstPerson = receiveString(firstPerson, familyHeads);

    //allocate memory second string and check if failed
    char *secondPerson = (char*) malloc(sizeof(char));
    if(secondPerson == NULL) {
        free(firstPerson);
        freeAll(familyHeads);
        exit(1);
    }

    //receive user input for second string
    printf("Enter the name of the second person:\n");
    secondPerson = receiveString(secondPerson, familyHeads);

    //call function to handle given string
    checkAndMarry(firstPerson, secondPerson, familyHeads);

    //free memory
    free(firstPerson);
    free(secondPerson);
}

/**
 * @brief checkAndMarry take two names and the main linked list, and check if the
 * names exist in the list. if they exist, points them to each other in the spouse pointer.
 * @param familyHeads is a pointer to the linked list.
 * @param firstPerson is the name of the first person.
 * @param secondPerson is the name of the second person.
 * @return void.
 */

void checkAndMarry(char *firstPerson, char *secondPerson, FamilyTree *familyHeads) {
    //declare valid age for marriage
    unsigned int const VALID_AGE = 18;

    //traverse all the trees and assign their struct to the pointers
    FamilyTree *bride = checkName(firstPerson, familyHeads);
    FamilyTree *groom = checkName(secondPerson, familyHeads);

    //check is both exist
    if(bride == NULL || groom == NULL) {
        printf("One of the persons does not exist\n");
        return;
    }

    //if both exist, check if they are in the right age
    if(bride->data->age < VALID_AGE || groom->data->age < VALID_AGE) {
        printf("Invalid marriage\n");
        return;
    }

    //check if they are the same person
    if(strcmp(bride->data->name, groom->data->name) == 0) {
        printf("Invalid marriage\n");
        return;
    }

    //check if one of them is already married
    if(bride->spouse != NULL || groom->spouse != NULL) {
        printf("Invalid marriage\n");
        return;
    }

    //check if they belong to the same family
    if(checkCommonAncestor(firstPerson, secondPerson, familyHeads) == 0) {
        printf("Invalid marriage\n");
        return;
    }

    //if passed all test, point them to each other and print message for user
    bride->spouse = groom;
    groom->spouse = bride;
    printf("%s and %s are now married\n", bride->data->name, groom->data->name);
}

/**
 * @brief checkCommonAncestor take two names and the main linked list, and checks if the
 * both of the names belong to the same family tree.
 * @param familyHeads is a pointer to the linked list.
 * @param firstPerson is the name of the first person.
 * @param secondPerson is the name of the second person.
 * @return 1 if they don't belong to the same tree, 0 if they do.
 */

int checkCommonAncestor(const char *firstPerson, const char *secondPerson, FamilyTree *familyHeads) {
    //declare const
    int const COMMON_ANCESTOR = 2;

    //loop on all the heads
    FamilyTree *currentHead = familyHeads->nextHead;
    while (currentHead != NULL) {
        //declare counter variable to keep count of the family tree
        int counter = 0;

        //compare the string to the string in the head
        if(strcmp(firstPerson, currentHead->data->name) == 0 ||
           strcmp(secondPerson,currentHead->data->name) == 0) {
            counter++;
        }

        //check if current head points to a spouse
        if(currentHead->spouse != NULL) {

            //if the current head points to children, check them too
            if(currentHead->children != NULL){
                counter += checkChildrenList(firstPerson, secondPerson, currentHead->children);
            }

                //check his spouse
            else if(currentHead->spouse->children != NULL) {
                counter += checkChildrenList(firstPerson, secondPerson, currentHead->spouse->children);
            }
        }

        //check counter
        if(counter == COMMON_ANCESTOR) return 0;

        //advance pointer to the next node
        currentHead = currentHead->nextHead;
    }

    //if passed all tests, return 1
    return 1;
}

/**
 * @brief checkChildrenList take two names and a linked list of children, and checks if the
 * both of the names belong to the same family tree, while calling the function recursively to check
 * the children of the children.
 * @param children is a pointer to the linked list of children.
 * @param firstPerson is the name of the first person.
 * @param secondPerson is the name of the second person.
 * @return the number of times found the names in the list..
 */

int checkChildrenList(const char *firstPerson,const char *secondPerson, FamilyTree *children) {
    //declare counter
    int counter = 0;

    //create pointer to the beginning of the list of children
    FamilyTree *currentChild = children;

    //loop on all it's siblings, and check if name is taken
    while (currentChild != NULL) {
        //compare the current child to the given name
        if(strcmp(currentChild->data->name, firstPerson) == 0 ||
           strcmp(currentChild->data->name, secondPerson) == 0) {
            counter++;
        }

        //check if the current child points to a spouse
        if(currentChild->spouse != NULL) {
            //if the current head points to children, call function to check them
            if(currentChild->children != NULL) {
                counter += checkChildrenList(firstPerson, secondPerson, currentChild->children);
            }

                //check his spouse
            else if(currentChild->spouse->children != NULL) {
                counter += checkChildrenList(firstPerson, secondPerson, currentChild->spouse->children);
            }
        }

        //advance to the next child in the list
        currentChild = currentChild->siblings;
    }

    //return the number of times found names
    return counter;
}

/**
 * @brief case3 handles the case of adding an offspring.
 * @param familyHeads is a pointer to the linked list.
 * @return void.
 */

void case3(FamilyTree *familyHeads) {
    //ignore new line
    scanf("%*c");

    //allocate memory first string and check if failed
    char *firstParent = (char*) malloc(sizeof(char));
    if(firstParent == NULL) {
        freeAll(familyHeads);
        exit(1);
    }

    //receive user input for first string
    printf("Enter the name of the first parent:\n");
    firstParent = receiveString(firstParent, familyHeads);

    //allocate memory second string and check if failed
    char *secondParent = (char*) malloc(sizeof(char));
    if(secondParent == NULL) {
        free(firstParent);
        freeAll(familyHeads);
        exit(1);
    }

    //receive user input for second string
    printf("Enter the name of the second parent:\n");
    secondParent = receiveString(secondParent, familyHeads);

    //allocate memory for new baby and check if failed
    Person *newBaby = (Person*) malloc(sizeof(Person));
    if(newBaby == NULL) {
        free(firstParent);
        free(secondParent);
        freeAll(familyHeads);
        exit(1);
    }

    //allocate memory for third string and check if failed
    newBaby->name = (char*) malloc(sizeof(char));
    if(newBaby->name == NULL) {
        free(firstParent);
        free(secondParent);
        freeAll(familyHeads);
        exit(1);
    }

    //receive user input for third string
    printf("Enter offspring");
    printf("'s name:\n");
    newBaby->name = receiveString(newBaby->name, familyHeads);
    newBaby->age = 0;

    //call for function to handle the names
    checkValidity(firstParent, secondParent, newBaby, familyHeads);

    //free memory when finished
    free(firstParent);
    free(secondParent);
}

/**
 * @brief checkValidity takes three string, check if the two parents exist and married,
 * and checks if the baby's name is not already taken. if passes all tests, adds new offspring to the
 * parent's list of children.
 * @param familyHeads is a pointer to the linked list.
 * @param firstParent is a pointer to the first parent name.
 * @param secondParent is a pointer to the second parent name.
 * @param newBaby is a pointer to the child's struct of data.
 * @return void.
 */

void checkValidity(char *firstParent, char *secondParent, Person *newBaby, FamilyTree *familyHeads){
    //declare pointers for parents
    FamilyTree *father = checkName(firstParent, familyHeads);
    FamilyTree *mother = checkName(secondParent, familyHeads);

    //check is both exist, print message and free memory
    if(father == NULL || mother == NULL) {
        printf("One of the parents does not exist\n");
        free(newBaby->name);
        free(newBaby);
        return;
    }

        //check if they are married to each other, print message and free memory
    else if(mother->spouse != father) {
        printf("The parents are not married\n");
        free(newBaby->name);
        free(newBaby);
        return;
    }

        //check if the baby's name is taken, print message and free memory
    else if(checkName(newBaby->name, familyHeads) != NULL) {
        printf("The name is already taken\n");
        free(newBaby->name);
        free(newBaby);
        return;
    }

    //check if it is the first child
    if(father->children == NULL && mother->children == NULL) {
        //use the father's list to add the child and return
        addNewChild(&(father->children), newBaby, familyHeads, father);
        printf("%s was born\n", newBaby->name);
        return;
    }

        //check if the father already points to existing children
    else if(father->children != NULL && mother->children == NULL) {
        //use the father's list to add the child and return
        addNewChild(&(father->children), newBaby, familyHeads, father);
        printf("%s was born\n", newBaby->name);
        return;
    }

        //check if the mother already points to children
    else if(mother->children != NULL && father->children == NULL) {
        //use the mother's list to add the child and return
        addNewChild(&(mother->children), newBaby, familyHeads, mother);
        printf("%s was born\n", newBaby->name);
        return;
    }
}

/**
 * @brief createNewChild receives pointer to data - struct, and a pointer to
 * the linked list of family heads, allocates new memory for a new child, and returns a pointer to it.
 * @param data receives data to add to node - a struct.
 * @param familyHead is a pointer to the bank.
 * @return pointer to new child.
 */

FamilyTree *createNewChild(Person *data, FamilyTree *familyHeads) {
    //create new node and a pointer to its memory in the heap
    FamilyTree *newChild = (FamilyTree*) malloc(sizeof(FamilyTree));

    //check if allocation failed
    if(newChild == NULL) {
        freeAll(familyHeads);
        exit(1);
    }

    //if allocation worked, assign value of data, and a null values
    newChild->data = data;
    newChild->nextHead = NULL;
    newChild->children = NULL;
    newChild->siblings = NULL;
    newChild->spouse = NULL;

    //return the pointer
    return newChild;
}

/**
 * @brief addNewChild receives pointer to a struct of a person, address of the linked list of a parent's
 * childrens and a pointer to the main linked list, and adds the new node in the end of the linked list.
 * @param parent is the address of the linked list of children.
 * @param data is a pointer to person struct.
 * @param familyHeads is a pointer to the main linked list
 * @param head is a pointer to the parent that creates the child.
 * @return void.
 */

void addNewChild(FamilyTree **parent, Person *data, FamilyTree *familyHeads, FamilyTree *head) {

    //create a family head using the createNewHead function and assign pointer to it
    FamilyTree *newChild = createNewChild(data, familyHeads);

    //assign his parent
    newChild->parent = head;

    //if the list is empty then assign the head directly
    if(*parent == NULL) {
        *parent = newChild;
    }

        //if the list is not empty
    else {
        //create a temp pointer and point to the head of the list, and a counter
        FamilyTree *temp = *parent;

        //loop until we reach the end of the list
        while (temp->siblings != NULL) {
            //advance the temp pointer to point to the next element, and increase counter
            temp = temp->siblings;
        }

        //assign the new head into the temp
        temp->siblings = newChild;
    }
}

/**
 * @brief case4 handles the case of printing a family.
 * @param familyHeads is a pointer to the linked list.
 * @return void.
 */

void case4(FamilyTree *familyHeads) {
    //ignore new line
    scanf("%*c");

    //allocate memory for a string and check if failed
    char *name = (char *) malloc(sizeof(char));
    if(name == NULL) {
        freeAll(familyHeads);
        exit(1);
    }

    //receive input from user
    printf("Enter the name of the person:\n");
    name = receiveString(name, familyHeads);

    //check if exists
    FamilyTree *person = checkName(name, familyHeads);
    if(person == NULL) {
        printf("The person does not exist\n");
        free(name);
        return;
    }

    //if exists print his name and age
    printf("%s (%u)", person->data->name, person->data->age);

    //if he has a spouse, print them as well
    if(person->spouse != NULL) {
        printf(" - %s (%u)\n", person->spouse->data->name, person->spouse->data->age);
    }

        //if he does not have a spouse, free memory and return
    else {
        printf("\n");
        free(name);
        return;
    }

    //check if the couple don't have children
    FamilyTree *firstTry = person->children;
    FamilyTree *secondTry = person->spouse->children;
    if(firstTry == NULL && secondTry == NULL) {
        free(name);
        return;
    }

        //if they do have children, use the pointers to print the children
    else {
        //declare variable to print tabs
        int tabs = 1;

        if(firstTry != NULL) {
            printFamily(firstTry, familyHeads, tabs);
        }

        else {
            printFamily(secondTry, familyHeads, tabs);
        }
    }

    //free memory
    free(name);
}

/**
 * @brief printFamily takes a pointer to a person in the program, and prints its
 * family downwards, using recursion to print all of his children (if he has any).
 * @param person is a pointer to the person we want to print his family.
 * @param familyHeads is a pointer to the linked list.
 * @param tabs is the number of tabs to print according to the stack.
 * @return void.
 */

void printFamily(FamilyTree *person, FamilyTree *familyHeads, int tabs) {
    //create pointer to the first child in the list
    FamilyTree *currentChild = person;

    //loop on all the siblings in the family
    while (currentChild != NULL) {
        //print tabs according to current place in the stack
        for (int i = 0; i < tabs; ++i) {
            printf("\t");
        }

        //print the child
        printf("%s (%u)", currentChild->data->name, currentChild->data->age);

        //check if the child has a spouse, if so, print it
        if(currentChild->spouse != NULL) {
            printf(" - %s (%u)\n", currentChild->spouse->data->name, currentChild->spouse->data->age);

            //check if they have children
            if(currentChild->children != NULL || currentChild->spouse->children != NULL) {
                //try the first parent, and add one more tab
                if(currentChild->children != NULL) {
                    printFamily(currentChild->children, familyHeads, tabs + 1);
                }

                    //try the second parent, and add one more tab
                else {
                    printFamily(currentChild->spouse->children, familyHeads, tabs + 1);
                }
            }
        }

        else {
            printf("\n");
        }

        //advance to the next sibling in the list
        currentChild = currentChild->siblings;
    }
}

/**
 * @brief case5 handles the case of adding years to everyone's age.
 * @param familyHeads is a pointer to the linked list.
 * @return void.
 */

void case5(FamilyTree *familyHeads) {
    //ignore new line
    scanf("%*c");

    //declare variable for years and receive user input for it
    unsigned int years = 0;

    printf("Enter number of years:\n");
    scanf("%u", &years);

    //ignore new line
    scanf("%*c");

    //call for function to handle adding years to every person in the program
    ageAll(years, familyHeads);
}

/**
 * @brief ageAll take a pointer to the main linked list, iterate on all the elements of the list and adds years to their age.
 * Also uses recursive function to add years to their children.
 * @param familyHeads is a pointer to the main linked list.
 * @param years in the number of years to add to everyone.
 * @return void.
 */

void ageAll(unsigned int years, FamilyTree *familyHeads) {
    //create a pointer to the head of the main linked list
    FamilyTree *currentHead = familyHeads->nextHead;

    //loop on all the family heads
    while (currentHead != NULL) {
        //add age to the current family head
        currentHead->data->age += years;

        //checks if he has children, adds years using a function to them as well if so
        if(currentHead->children != NULL) {
            ageChildren(years, currentHead->children);
        }

        //advance pointer to the next head
        currentHead = currentHead->nextHead;
    }
}

/**
 * @brief ageChildren take a pointer the first child in a linked list of siblings and adds to everyone's age the number of years.
 * if one of the siblings has children, call function recursively to add years to them too.
 * @param child is a pointer to the linked list of children.
 * @param years in the number of years to add to everyone.
 * @return void.
 */

void ageChildren(unsigned int years, FamilyTree *child) {
    //create pointer to the list of children
    FamilyTree *currentChild = child;

    //loop on all the siblings
    while (currentChild != NULL) {
        //add years to the current child
        currentChild->data->age += years;

        //check if he has children - if so, call function again to add years to them as well
        if(currentChild->children != NULL) {
            ageChildren(years, currentChild->children);
        }

        //advance to the next child in the family
        currentChild = currentChild->siblings;
    }
}

/**
 * @brief countAll take a pointer to the main linked list, iterate on all the people in the list and counts them.
 * if one of the has children, calls recursive function to add them as well.
 * @param familyHeads is a pointer to the main linked list.
 * @return void.
 */

void countAll(FamilyTree *familyHeads) {
    //ignore new line
    scanf("%*c");

    //declare variable for counter, and a pointer to the head of the list
    int counter = 0;
    FamilyTree *currentHead = familyHeads->nextHead;

    //loop on all the family heads
    while (currentHead != NULL) {
        //add to counter
        counter++;

        //checks if he has children, calls function to add them to counter if it does
        if(currentHead->children != NULL) {
            counter += countChildren(currentHead->children);
        }

        //advance pointer to the next head
        currentHead = currentHead->nextHead;
    }

    //if counter is only 1, print special message
    if(counter == 1) {
        printf("There is one person\n");
    }

    else {
        printf("There are %d people\n", counter);
    }
}

/**
 * @brief ageChildren take a pointer the first child in a linked list and counts how many siblings he has.
 * in addition, checks if one of the siblings has children, and calls itself again if so.
 * @param child is a pointer to the linked list of children.
 * @return number of children in the family.
 */

int countChildren(FamilyTree *child) {
    //declare variable for counter and a pointer to the first child
    int counter = 0;
    FamilyTree *currentChild = child;

    //loop on all the siblings
    while (currentChild != NULL) {
        //increase counter
        counter++;

        //check if he has children, and calls function again if so to add them too
        if(currentChild->children != NULL) {
            counter += countChildren(currentChild->children);
        }

        //advance to the next sibling
        currentChild = currentChild->siblings;
    }

    //when finished, return counter
    return counter;
}

/**
 * @brief case7 handles the case of printing cousins of a given person in the program,
 * of changing degrees.
 * @param familyHeads is a pointer to the linked list.
 * @return void.
 */

void case7(FamilyTree *familyHeads) {
    //ignore new line
    scanf("%*c");

    //allocate memory for user's input of name, and check if failed
    char *checkPerson = (char *) malloc(sizeof(char));
    if(checkPerson == NULL)
    {
        freeAll(familyHeads);
        exit(1);
    }

    //receive user input for name
    printf("Enter the name of the person:\n");
    checkPerson = receiveString(checkPerson, familyHeads);

    //declare variable for degree
    unsigned int degree = 0;

    //receive user input of degree
    printf("Enter degree:\n");
    scanf("%u", &degree);

    //ignore new line
    scanf("%*c");

    //check if name exists
    FamilyTree *person = checkName(checkPerson, familyHeads);

    //if name does not exist, return to menu
    if(person == NULL)
    {
        printf("The person does not exist\n");
        free(checkPerson);
        return;
    }

    //free memory of name
    free(checkPerson);

    //create a pointer to a list of ancestors, and a temp varible for degree
    Ancestor ancestorsList;
    ancestorsList.next = NULL;
    unsigned int realDegree = degree;

    //call function to find the person's ancestors and store them
    findAllAncestors(degree, realDegree, person, &(ancestorsList.next), familyHeads);

    //create a pointer to a list of cousins
    Cousin cousinsList;
    cousinsList.next = NULL;

    //call function to find the person's cousins and store them in the cousins list
    traverseAncestors(degree, &ancestorsList, &(cousinsList.next), familyHeads);

    //call function to sort and print the list in lexicographic order
    sortAndPrintList(&cousinsList);

    //free the lists
    freeAncestorsList(&ancestorsList);
    freeCousinsList(&cousinsList);
}

/**
 * @brief findAllAncestors finds all of the given person's ancestors of a certain degree and adds them to
 * a list of ancestors.
 * Base of recursion: if the person has no parents (family head) or we reached to desired degree.
 * Step: call for function with each of the parents and minus one the degree.
 * @param familyHeads is a pointer to the main linked list.
 * @param ancestorsList is a linked list contains the ancestors of a person.
 * @param person is a pointer to the person we want to find his ancestors.
 * @param degree is the degree which we want to find the ancestors.
 * @param realDegree is the real degree of the ancestor.
 * @return void.
 */

void findAllAncestors(unsigned int degree, unsigned int realDegree, FamilyTree *person, Ancestor **ancestorsList,
                      FamilyTree *familyHeads) {
    //base case - if the given person is a head, or we reached the highest possible ancestor, store him in the list
    if(person->parent == NULL || degree == 0) {
        //store the real degree
        realDegree = realDegree - degree;

        //call function to store the person in the ancestor's list and return
        addAncestor(realDegree, person, ancestorsList, familyHeads);
        return;
    }

    //step of recursion - store his parents in pointers
    FamilyTree *mother = person->parent;
    FamilyTree *father = person->parent->spouse;

    //call for function with one less degree and the parents
    findAllAncestors(degree - 1, realDegree, mother, ancestorsList, familyHeads);
    findAllAncestors(degree - 1, realDegree, father, ancestorsList, familyHeads);
}

/**
 * @brief addAncestor takes a pointer to a person and adds it to a list of ancestors.
 * @param familyHeads is a pointer to the main linked list.
 * @param ancestorsList is a linked list contains the ancestors of a person.
 * @param person is a pointer to the person we want to add.
 * @param realDegree is the height of the ancestor compared to his offspring.
 * @return void.
 */

void addAncestor(unsigned int realDegree, FamilyTree *person, Ancestor **ancestorsList, FamilyTree *familyHeads) {
    //allocate memory for a new node in the list
    Ancestor *newAncestor = (Ancestor *) malloc(sizeof(Ancestor));

    //check if failed
    if(newAncestor == NULL) {
        freeAll(familyHeads);
        freeAncestorsList(*ancestorsList);
        exit(1);
    }

    //assign values to new ancestor
    newAncestor->ancestor = person;
    newAncestor->realDegree = realDegree;
    newAncestor->next = NULL;

    //add to the list of ancestors
    //if we are in the head of the list, add immediately
    if(*ancestorsList == NULL) {
        *ancestorsList = newAncestor;
    }

    else {
        //if not empty, assign a temp pointer to traverse the list
        Ancestor *currentAncestor = *ancestorsList;

        //reach the end of the list in a loop
        while (currentAncestor->next != NULL) {
            currentAncestor = currentAncestor->next;
        }

        //assign value of new node
        currentAncestor->next = newAncestor;
    }
}

/**
 * @brief freeAncestorsList take a pointer a linked list, iterates on all the elements of the list and frees them.
 * @param ancestorsList is a pointer to the linked list.
 * @return void.
 */

void freeAncestorsList(Ancestor *ancestorsList) {
    //create a pointer to head of the list and a temp pointer
    Ancestor *currentAncestor = ancestorsList->next;
    Ancestor *temp = NULL;

    //traverse the list and free nodes
    while (currentAncestor != NULL) {
        //move the temp pointer one node ahead, and then the current one
        temp = currentAncestor;
        currentAncestor = currentAncestor->next;

        //free the node
        free(temp);
    }
}

/**
 * @brief traverseAncestors loops on all the ancestors list, and calls a recursive function to handle each
 * one - adding his offsprings to a list of cousins.
 * @param degree is the user's input for degree.
 * @param familyHeads is a pointer to the main linked list.
 * @param ancestorsList is a linked list contains the ancestors of a person.
 * @param cousinsList is a linked list contains the cousins of a person.
 * @return void.
 */

void traverseAncestors(unsigned int degree, Ancestor *ancestorsList, Cousin **cousinsList, FamilyTree *familyHeads) {
    //check if the degree is zero
    if(degree == 0) {
        //add the only person in the list and exit
        FamilyTree *add = ancestorsList->next->ancestor;
        addCousin(add, cousinsList, ancestorsList, familyHeads);
        return;
    }

    //if degree is not zero, loop on all the ancestors list
    Ancestor *currentAncestor = ancestorsList->next;
    while (currentAncestor != NULL) {
        //declare variable for degree
        unsigned int realDegree = currentAncestor->realDegree;

        //call for function to add the children of the ancestor
        findCousins(realDegree - 1, currentAncestor->ancestor->children, cousinsList, ancestorsList, familyHeads);

        //move the pointer one node ahead
        currentAncestor = currentAncestor->next;
    }
}

/**
 * @brief findCousins takes a pointer to a children's list and add them or their offsprings to the cousins list,
 * according to the given degree.
 * Base of recursion: if degree is 0, add all the children in the list.
 * Step: call for function for each child that has children, with degree minus 1.
 * @param degree is the degree we want to achieve.
 * @param child is a pointer to a linked list of children.
 * @param cousinsList is the address of the cousins list.
 * @param ancestorsList is a pointer to the ancestors list
 * @param familyHeads is a pointer to the main linked list.
 * @return void.
 */

void findCousins(unsigned int degree, FamilyTree *child, Cousin **cousinsList, Ancestor *ancestorsList,
                 FamilyTree *familyHeads) {
    //Base - check if degree is zero
    if(degree == 0) {
        //loop on all the sibling to add them to the list
        FamilyTree *currentChild = child;
        while (currentChild != NULL) {
            //add to list
            addCousin(currentChild, cousinsList, ancestorsList, familyHeads);

            //move to the next sibling in the list
            currentChild = currentChild->siblings;
        }
    }

        //if degree is not zero, iterate the siblings to find their children
    else {
        //loop on the siblings
        FamilyTree *currentChild = child;
        while (currentChild != NULL) {
            //check if he is married
            if(currentChild->spouse != NULL) {
                //check if he points to children, and call for function again
                if(currentChild->children != NULL) {
                    findCousins(degree - 1, currentChild->children, cousinsList, ancestorsList, familyHeads);
                }

                    //check his spouse, and call for function again
                else if(currentChild->spouse->children != NULL) {
                    findCousins(degree - 1, currentChild->spouse->children, cousinsList, ancestorsList, familyHeads);
                }
            }

            //move to the next sibling
            currentChild = currentChild->siblings;
        }
    }
}

/**
 * @brief addCousin takes a pointer to a person and adds it to a list of cosuins.
 * @param familyHeads is a pointer to the main linked list.
 * @param cousinsList is a linked list contains the cousins of a person.
 * @param ancestorsList is a linked list of the ancestors.
 * @param person is a pointer to the person we want to add.
 * @return void.
 */

void addCousin(FamilyTree *person, Cousin **cousinsList, Ancestor *ancestorsList, FamilyTree *familyHeads) {
    //allocate memory for a new node in the list
    Cousin *newCousin = (Cousin *) malloc(sizeof(Cousin));

    //check if failed
    if(newCousin == NULL) {
        freeAll(familyHeads);
        freeCousinsList(*cousinsList);
        freeAncestorsList(ancestorsList);
        exit(1);
    }

    //assign values to new ancestor
    newCousin->cousin = person;
    newCousin->next = NULL;

    //add to the list of cousins
    //if the list is empty
    if(*cousinsList == NULL) {
        *cousinsList = newCousin;
    }

        //if not
    else {
        //assign a temp pointer to traverse the list
        Cousin *temp = *cousinsList;

        //reach the end of the list using a loop
        while (temp->next != NULL) {
            //check if the name was already added
            if(strcmp(newCousin->cousin->data->name, temp->cousin->data->name) == 0) {
                //free memory of new person and return
                free(newCousin);
                return;
            }

            //advance the pointer one node ahead
            temp = temp->next;
        }

        //check the last node before assigning
        if(strcmp(newCousin->cousin->data->name, temp->cousin->data->name) == 0) {
            //free memory of new person and return
            free(newCousin);
            return;
        }

        //if passed all tests, assign new node
        temp->next = newCousin;
    }
}

/**
 * @brief freeCousinsList take a pointer a linked list, iterates on all the elements of the list and frees them.
 * @param cousinsList is a pointer to the linked list.
 * @return void.
 */

void freeCousinsList(Cousin *cousinsList) {
    //create a pointer to point to the head of the list
    Cousin *currentCousin = cousinsList->next;
    Cousin *temp = NULL;

    //loop on all the elements of the list
    while (currentCousin != NULL) {
        //move the temp pointer one node ahead
        temp = currentCousin;
        currentCousin = currentCousin->next;

        //free the node
        free(temp);
    }
}

/**
 * @brief sortAndPrintList takes a pointer to a linked list, sorts it in lexicographic order,
 * and prints it for user.
 * @param cousinsList is a pointer to the linked list.
 * @return void.
 */

void sortAndPrintList(Cousin *cousinsList) {
    //create a flag variable and pointers to the head of the list
    int flag = 0;
    Cousin *firstCousin = cousinsList->next;

    //if the list is empty, do nothing
    if(cousinsList->next == NULL) {
        return;
    }

    //do while loop to use at least once
    do {
        //initialize flag and a pointer to the head of the list
        flag = 0;
        Cousin *currentCousin = cousinsList->next;

        //loop on the elements
        while (currentCousin->next != NULL) {
            //check if there is need for swap
            if(strcmp(currentCousin->cousin->data->name, currentCousin->next->cousin->data->name) > 0) {
                //swap the elements
                FamilyTree *temp = currentCousin->cousin;
                currentCousin->cousin = currentCousin->next->cousin;
                currentCousin->next->cousin = temp;
                flag = 1;
            }

            //advance the pointer to the next node
            currentCousin = currentCousin->next;
        }
    }
        //continue as long as zero is not entered in flag
    while (flag);

    //print start of list
    printf("Cousins:\n");

    //print cousins in a loop
    while (firstCousin != NULL) {
        printf("%s\n", firstCousin->cousin->data->name);
        firstCousin = firstCousin->next;
    }
}