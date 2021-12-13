#include <stdio.h>
#include <string.h>
#include "string_funcs.h"

#define TXT 1024
#define WORD 30

int main() {
    char word[WORD + 1];
    char txt[TXT + 1];
    char c;
    c = getchar();
    while(c != ' ' && c != '\n' && c != '\t') {
        strcat(word, &c);
        c = getchar();
    }
    while(c != '~') {
        strcat(txt, &c);
        c = getchar();
    }

    printf("Gematria Sequences: ");
    func1(word, txt);

//    printf("Gematria Sequences: ");
//    func2(word, txt);
//
//    printf("Gematria Sequences: ");
//    func3(word, txt);

    return 0;
}
