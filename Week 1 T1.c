#include <stdio.h>

int main() {
    int change;
    int coins = 0;
  
    do {
        printf("Change owed: ");
        scanf("%d", &change);
        
        if (change < 0) {
            printf("Enter a value greater than or equal to 0.\n");}}
    while (change < 0);

    coins += change / 25 ;
    change %= 25 ;

    coins += change / 10; 
    change %= 10; 

    coins += change / 5; 
    change %= 5; 

    coins += change; 
    printf("%d\n", coins);
    return 0; }
