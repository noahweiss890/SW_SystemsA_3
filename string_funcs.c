#include <stdio.h>
#include <string.h>
#include "string_funcs.h"

#define TXT 1024
#define WORD 30

//finds the gematria of the char
int gematria_helper(char x) {
    if (x >= 'A' && x <= 'Z') {
        return (x - 'A') + 1;
    } else if (x >= 'a' && x <= 'z') {
        return (x - 'a') + 1;
    }
    return 0;
}

char atbash_helper(char x) {
    if(x >= 'A' && x <= 'Z'){
        return (('Z' - gematria_helper(x)) + 1);
    }
    if(x >= 'a' && x <= 'z'){
        return (('z' - gematria_helper(x)) + 1);
    }
    return x;
}

//gematria
void func1(char w[WORD + 1], char t[TXT + 1]) {
    int left = 0, right = 0, target = 0, flag = 0, sum;
    for (int i = 0; i < strlen(w); i++) { //finds gematria of word
        target += gematria_helper(w[i]);
    }
    sum = gematria_helper(t[0]);
    int last = strlen(t)-1;
    while(gematria_helper(t[last]) == 0 && last > -1) {
        last--;
    }
    if(last == -1) {
        return;
    }
    while (left < last || right < last) {
        if(sum < target) {
            int next = right + 1;
            while(gematria_helper(t[next]) == 0) {
                if(next == strlen(t) - 1) {
                    next = -1;
                    break;
                }
                next++;
            }
            if(next != -1) {
                right = next;
                sum += gematria_helper(t[right]);
            }
            else {
                break;
            }
        }
        else if(sum > target) {
            if(left < right) {
                sum -= gematria_helper(t[left]);
                left++;
                while(gematria_helper(t[left]) == 0) {
                    left++;
                }
            }
            else {
                int next = right + 1;
                while(gematria_helper(t[next]) == 0) {
                    if(next == strlen(t) - 1) {
                        next = -1;
                        break;
                    }
                    next++;
                }
                if(next != -1) {
                    right = next;
                    sum += gematria_helper(t[right]);
                }
            }
        }
        if(sum == target) {
            char str[right - left + 1];
            for (int i = left; i < right + 1; i++) {
                str[i - left] = t[i];
            }
            if (flag) {
                printf("~%s", str);
            } else {
                printf("%s", str);
                flag = 1;
            }
            int next = right + 1;
            while (gematria_helper(t[next]) == 0) {
                if (next == strlen(t) - 1) {
                    next = -1;
                    break;
                }
                next++;
            }
            if (next != -1) {
                right = next;
                sum += gematria_helper(t[right]);
            } else {
                sum -= gematria_helper(t[left]);
                left++;
                while (gematria_helper(t[left]) == 0) {
                    left++;
                }
            }
        }
    }
}

void func2(char w[WORD + 1], char t[TXT + 1]) {
    char forward[WORD + 1], backward[WORD + 1];
    int flag = 0;
    strcpy(forward, w);
    strcpy(backward, w);
    reverse(backward);
    for(int i = 0; i < strlen(w); i++) {
        forward[i] = atbash_helper(forward[i]);
        backward[i] = atbash_helper(backward[i]);
    }
    for(char *start = t; start < t + strlen(t); start++) {
        if (strcmp(forward, backward) || start[0] == forward[0]) {
            int i, count = 0;
            for (i = 0; i < strlen(start) && count < strlen(w); i++) {
                if (start[i] != ' ' && start[i] != '\t' && start[i] != '\n') {
                    if (start[i] != forward[count]) {
                        break;
                    }
                    count++;
                }
            }
            if (count == strlen(w)) {
                char str[i + 1];
                strncat(str, start, i);
                if (flag) {
                    printf("~%s", str);
                } else {
                    printf("%s", str);
                    flag = 1;
                }
                continue;
            }
        }
        if (start[0] == backward[0]) {
            int i, count = 0;
            for (i = 0; i < strlen(start) && count < strlen(w); i++) {
                if (start[i] != ' ' && start[i] != '\t' && start[i] != '\n') {
                    if (start[i] != backward[count]) {
                        break;
                    }
                    count++;
                }
            }
            if (count == strlen(w)) {
                char str[i + 1];
                strncat(str, start, i);
                if (flag) {
                    printf("~%s", str);
                } else {
                    printf("%s", str);
                    flag = 1;
                }
            }
        }
    }
}

void func3(char w[WORD + 1], char t[TXT + 1]) {
    char first;
    int countF, fInWord, flag = 0;
    for(char *start = t; start < t + strlen(t); start++) {
        if (*start != ' ' && *start != '\n' && *start != '\t') {
            int i;
            first = '\0';
            for (i = 0; i < strlen(start); i++) {
                if (start[i] != ' ' && start[i] != '\n' && start[i] != '\t') {
                    if (strchr(w, start[i]) == NULL) {
                        break;
                    }
                    if (first == '\0') {
                        first = start[i];
                        countF = 1;
                        fInWord = 0;
                        for (int k = 0; k < strlen(w); k++) {
                            if (w[k] == first) {
                                fInWord++;
                            }
                        }
                    } else if (start[i] == first) {
                        countF++;
                        if (countF > fInWord) {
                            break;
                        }
                    }
                }
            }
            if (countF <= fInWord) {
                char ans[i + 1];
                ans[0] = '\0';
                strncpy(ans, start, i);
                ans[i] = '\0';
                int k;
                char *res;
                for (k = 0; k < strlen(w); k++) {
                    res = strchr(ans, w[k]);
                    if (res == NULL) {
                        break;
                    }
                    *res = ' ';
                }
                if (res != NULL) {
                    int last = strlen(ans) - 1;
                    while (ans[last] != ' ') {
                        last--;
                    }
                    strncpy(ans, start, last + 1);
                    ans[last + 1] = '\0';
                    while(ans[last] == ' ' || ans[last] == '\t' || ans[last] == '\n') {
                        ans[last--] = '\0';
                    }
//                    printf("last ans: %s", ans);
                    if (flag == 0) {
                        flag = -1;
                        printf("%s", ans);
                    } else {
                        printf("~%s", ans);
                    }
                }
            }
        }
    }
}

//reverses the string
void reverse(char *str) {
    char temp;
    for (char *start = str, *end = str + strlen(str) - 1; start < end; start++, end--) {
        temp = *start;
        *start = *end;
        *end = temp;
    }
}