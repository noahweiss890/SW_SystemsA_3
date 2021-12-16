// Noah Weiss 326876786
// Rashi Pachino 345174478

#include <stdio.h>
#include <string.h>
#include "string_funcs.h"

#define TXT 1024
#define WORD 30

int main() {
    char word[WORD + 1];
    char txt[TXT + 1];
    char c;
    c = (char)getchar();
    while(c != ' ' && c != '\n' && c != '\t') { // while the char inputted isnt a whitespace
        strcat(word, &c);
        c = (char)getchar();
    }
    c = (char)getchar();
    while(c != '~') { // input chars until a '~' is inputted
        strcat(txt, &c);
        c = (char)getchar();
    }

    printf("Gematria Sequences: ");
    func1(word, txt);
    putchar('\n');

    printf("Atbash Sequences: ");
    func2(word, txt);
    putchar('\n');

    printf("Anagram Sequences: ");
    func3(word, txt);

    return 0;
}