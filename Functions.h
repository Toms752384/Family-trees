//
// Created by toms7 on 3/30/2024.
//

#ifndef UNTITLED3_FUNCTIONS_H
#define UNTITLED3_FUNCTIONS_H

#endif //UNTITLED3_FUNCTIONS_H

typedef struct Person {
    char *name;
    unsigned int age;
}Person;

typedef struct FamilyTree {
    Person *data;
    struct FamilyTree *spouse;
    struct FamilyTree *children;
    struct FamilyTree *siblings;
    struct FamilyTree *nextHead;
    struct FamilyTree *parent;
} FamilyTree;

typedef struct Ancestor {
    FamilyTree *ancestor;
    struct Ancestor *next;
    unsigned int realDegree;
} Ancestor;

typedef struct Cousin {
    FamilyTree *cousin;
    struct Cousin *next;
} Cousin;

void printMenu();

void freeAll(FamilyTree *familyHeads);

void freeChild(FamilyTree *child);

void case1(FamilyTree *familyHeads);

char* receiveString(char *name, FamilyTree *familyHeads);

FamilyTree *checkName(char *name, FamilyTree *familyHeads);

FamilyTree *checkChild(char *name, FamilyTree *children);

FamilyTree *createNewHead(Person *data, FamilyTree *familyHeads);

void addHead(FamilyTree **trees, Person *data, FamilyTree *familyHeads);

Person *createPerson(FamilyTree *familyHeads);

void case2(FamilyTree *familyHeads);

void checkAndMarry(char *firstPerson, char *secondPerson, FamilyTree *familyHeads);

int checkCommonAncestor(const char *firstPerson,const char *secondPerson, FamilyTree *familyHeads);

int checkChildrenList(const char *firstPerson,const char *secondPerson, FamilyTree *children);

void case3(FamilyTree *familyHeads);

void checkValidity(char *firstParent, char *secondParent, Person *newBaby, FamilyTree *familyHeads);

FamilyTree *createNewChild(Person *data, FamilyTree *familyHeads);

void addNewChild(FamilyTree **parent, Person *data, FamilyTree *familyHeads, FamilyTree *head);

void case4(FamilyTree *familyHeads);

void printFamily(FamilyTree *person, FamilyTree *familyHeads, int tabs);

void case5(FamilyTree *familyHeads);

void ageAll(unsigned int years, FamilyTree *familyHeads);

void ageChildren(unsigned int years, FamilyTree *child);

void countAll(FamilyTree *familyHeads);

int countChildren(FamilyTree *child);

void case7(FamilyTree *familyHeads);

void findAllAncestors(unsigned int degree, unsigned int realDegree, FamilyTree *person, Ancestor **ancestorsList,
                      FamilyTree *familyHeads);

void addAncestor(unsigned int realDegree, FamilyTree *person, Ancestor **ancestorsList, FamilyTree *familyHeads);

void freeAncestorsList(Ancestor *ancestorsList);

void traverseAncestors(unsigned int degree, Ancestor *ancestorsList, Cousin **cousinsList, FamilyTree *familyHeads);

void findCousins(unsigned int degree, FamilyTree *child, Cousin **cousinsList, Ancestor *ancestorsList,
                 FamilyTree *familyHeads);

void addCousin(FamilyTree *person, Cousin **cousinsList, Ancestor *ancestorsList, FamilyTree *familyHeads);

void freeCousinsList(Cousin *cousinsList);

void sortAndPrintList(Cousin *cousinsList);