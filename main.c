#include <stdio.h>
#include <string.h>
#include "string_funcs.h"

#define TXT 1024
#define WORD 30

int main() {
    char word[WORD + 1];
    char txt[TXT + 1];
//    char fulltext[TXT + 1];
    char c;
    c = (char)getchar();
    while(c != ' ' && c != '\n' && c != '\t') {
        strcat(word, &c);
        c = (char)getchar();
    }
    c = (char)getchar();
    while(c != '~') {
        strcat(txt, &c);
        c = (char)getchar();
    }
//    gets(word);
//    gets(fulltext);
//    char *end = strchr(fulltext, '~');
//    int i = 0;
//    while(fulltext + i < end) {
//        txt[i] = fulltext[i];
//        i++;
//    }
//    printf("%s", txt);

    printf("Gematria Sequences: ");
    func1(word, txt);
    putchar('\n');

    printf("Atbash Sequences: ");
    func2(word, txt);
    putchar('\n');

//
    printf("Anagram Sequences: ");
    func3(word, txt);
    putchar('\n');

    return 0;
}