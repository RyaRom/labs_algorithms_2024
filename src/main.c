#include <stdio.h>
#include <stdlib.h>

void lab1();

void lab2();

void lab3();

void lab4();

void lab5();

void lab6();

int main(void) {
    int lab;
    printf("Select\n"
        "1. lab 1\n"
        "2. lab 2\n"
        "3. lab 3\n"
        "4. lab 4\n"
        "5. lab 5\n"
        "6. lab 6\n");
    scanf("%d", &lab);
    switch (lab) {
        case 1: lab1();
            break;
        case 2: lab2();
            break;
        case 3: lab3();
            break;
        case 4: lab4();
            break;
        // case 5: lab5();
        //     break;
        // case 6: lab6();
        //     break;
        default: return 0;
    }
}
