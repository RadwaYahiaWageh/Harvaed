#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    char *key = argv[1];

    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    bool seen[26] = {false};
    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must contain only alphabetic characters.\n");
            return 1;
        }
        int index = tolower(key[i]) - 'a';
        if (seen[index])
        {
            printf("Key must not contain repeated characters.\n");
            return 1;
        }
        seen[index] = true;
    }

    char plaintext[100];
    printf("plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("ciphertext: ");

    for (int i = 0; i < strlen(plaintext); i++)
    {
        char c = plaintext[i];
        if (isalpha(c))
        {
            char cipher_char = key[tolower(c) - 'a'];
            printf("%c", isupper(c) ? toupper(cipher_char) : cipher_char);}
        else{
            printf("%c", c); }}
    printf("\n");

    return 0;}