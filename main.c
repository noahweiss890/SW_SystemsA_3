#include <stdio.h>
#include <string.h>

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
    func1(word[WORD+1], txt[TXT + 1]);

    printf("Gematria Sequences: ");
    func2(word[WORD+1], txt[TXT + 1]);

    printf("Gematria Sequences: ");
    func3(word[WORD+1], txt[TXT + 1]);

    return 0;
}
