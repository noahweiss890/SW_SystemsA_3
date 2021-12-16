#include <stdio.h>
#include <string.h>
#include "string_funcs.h"

#define TXT 1024
#define WORD 30

/**
 *
 * @param x is a char
 * @return the gematria value of the given char, if not an alphabetic letter returns 0
 */
int gematria_helper(char x) {
    if (x >= 'A' && x <= 'Z') { // if upper case latter
        return (x - 'A') + 1;
    } else if (x >= 'a' && x <= 'z') { // if lower case latter
        return (x - 'a') + 1;
    }
    return 0; // if not an alphabetic letter
}

/**
 *
 * @param x is a char
 * @return if x is an alphabetic letter, return the atbash version of the letter (A -> Z, b -> y...)
 */
char atbash_helper(char x) {
    if(x >= 'A' && x <= 'Z'){
        return (('Z' - gematria_helper(x)) + 1);
    }
    if(x >= 'a' && x <= 'z'){
        return (('z' - gematria_helper(x)) + 1);
    }
    return x;
}


/**
 * This function prints out a list of words that from the text that have an equal gematria to the given word.
 * @param w is a single word
 * @param t is a text
 */
void func1(char w[WORD + 1], char t[TXT + 1]) {
    int left = 0, right = 0, target = 0, flag = 0, sum;
    for (int i = 0; i < strlen(w); i++) { //finds gematria of w
        target += gematria_helper(w[i]);
    }
    sum = gematria_helper(t[0]);
    int last = strlen(t)-1;
    while(gematria_helper(t[last]) == 0 && last > -1) { // to know how many chars at the end are not possible answers
        last--;
    }
    if(last == -1) { // if there are no alphabetic letters in t
        return;
    }
    while (left < last || right < last) { // while the pointers are in bounds
        if(sum < target) { // if the current sum is too small
            int next = right + 1; // add the next char to my sum
            while(gematria_helper(t[next]) == 0) { // while the next char is not a letter
                if(next == strlen(t) - 1) {
                    next = -1;
                    break;
                }
                next++; // move the right bound forward
            }
            if(next != -1) {
                right = next; // add next to my potential answer
                sum += gematria_helper(t[right]); // add the gematria value to sum
            }
            else {
                break; // right went out of bounds
            }
        }
        else if(sum > target) { // if the current sum is too big
            if(left < right) {
                sum -= gematria_helper(t[left]); // take off the left bound from sum
                left++; // move the left bound forward
                while(gematria_helper(t[left]) == 0) { // move forward while left isn't pointing at a letter
                    left++;
                }
            }
            else { // if left equals the same
                int next = right + 1; // used to move forward until a letter is found
                while(gematria_helper(t[next]) == 0) { // while the next char is not a letter
                    if(next == strlen(t) - 1) {
                        next = -1;
                        break;
                    }
                    next++;
                }
                if(next != -1) { // if a letter is found
                    right = next; // move the right bound to next
                    sum += gematria_helper(t[right]); // add the gematria value to sum
                }
            }
        }
        if(sum == target) { // if the current sum equals the target
            char str[right - left + 1];
            str[0] = '\0';
            for (int i = left; i < right + 1; i++) {
                str[i - left] = t[i];
            }
            str[right-left+1] = '\0';
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
                str[0] = '\0';
                strncat(str, start, i);
                str[i+1] = '\0';
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
                str[0] = '\0';
                strncat(str, start, i);
                str[i+1] = '\0';
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