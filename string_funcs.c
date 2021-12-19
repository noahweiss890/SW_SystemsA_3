// Noah Weiss 326876786
// Rashi Pachino 345174478

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
 * It at any point checks if the gematria of letters in the range is too big or too small and moves the range accordingly forward. When it equals it is printed.
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
            for (int i = left; i < right + 1; i++) { // put all of the chars between lef t and right in str to be printed
                str[i - left] = t[i];
            }
            str[right-left+1] = '\0';
            if (flag) { // if its not the first time printing an answer
                printf("~%s", str);
            } else { // if its the first time printing an answer
                printf("%s", str);
                flag = 1;
            }
            int next = right + 1;
            while (gematria_helper(t[next]) == 0) { // while the next char is not a letter
                if (next == strlen(t) - 1) {
                    next = -1;
                    break;
                }
                next++;
            }
            if (next != -1) { // if a letter is found
                right = next; // move the right bound to next
                sum += gematria_helper(t[right]); // add the gematria value to sum
            } else {
                sum -= gematria_helper(t[left]); // take off the gematria of the the left bound
                left++;
                while (gematria_helper(t[left]) == 0) { // while its not a letter
                    left++;
                }
            }
        }
    }
}

/**
 * This function prints all of the sequences in the given text that equal the atbash of the given word or the reverse of it.
 * @param w is a single word
 * @param t is a text
 */
void func2(char w[WORD + 1], char t[TXT + 1]) {
    char forward[WORD + 1], backward[WORD + 1];
    int flag = 0;
    strcpy(forward, w);
    strcpy(backward, w);
    reverse(backward); // reverse the word
    for(int i = 0; i < strlen(w); i++) { // puts the atbash of the letters in w in forward and backwards
        forward[i] = atbash_helper(forward[i]);
        backward[i] = atbash_helper(backward[i]);
    }
    for(char *start = t; start < t + strlen(t); start++) {
        if (strcmp(forward, backward) || start[0] == forward[0]) { // if w is a palindrome or the first letter is equal to the first letter in forward
            int i, count = 0;
            for (i = 0; i < strlen(start) && count < strlen(w); i++) {
                if (start[i] != ' ' && start[i] != '\t' && start[i] != '\n') { // if the char at i isnt a whitespace
                    if (start[i] != forward[count]) { // if the char is different than forward
                        break;
                    }
                    count++;
                }
            }
            if (count == strlen(w)) { // if the count is the length of w then we found a match
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
        if (start[0] == backward[0]) { // if the first letter is equal to the first letter in backward
            int i, count = 0;
            for (i = 0; i < strlen(start) && count < strlen(w); i++) {
                if (start[i] != ' ' && start[i] != '\t' && start[i] != '\n') { // if the char at i isnt a whitespace
                    if (start[i] != backward[count]) { // if the char is different than forward
                        break;
                    }
                    count++;
                }
            }
            if (count == strlen(w)) { // if the count is the length of w then we found a match
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
/**
 * returns all anagram minimum sequences containing only the letters from the specified word
 * @param w is a single word
 * @param t is a text
 */
void func3(char w[WORD + 1], char t[TXT + 1]) {
    char *start = t; // the starting point
    char tempWord[WORD + 1]; // to be used for checking if a potential string is an anagram
    int flag = 0; // to know if its the first time printing an answer
    while(start < t + strlen(t)) {
        if (*start != ' ' && *start != '\n' && *start != '\t') { // only go in if the first char isn't a white space
            strcpy(tempWord, w);
            int i = 0, count = 0;
            for (i = 0; i < strlen(start); i++) {
                if (start[i] != ' ' && start[i] != '\n' && start[i] != '\t') {
                    if (strchr(tempWord, start[i]) == NULL) { // checks if the char is in tempWord and return a pointer to the char in tempWord, if its doesnt exist returns null
                        break;  // when the current char isnt apart of the anagram of w
                    }
                    *(strchr(tempWord, start[i])) = ' '; // change the char that was found in tempWord to ' ' (spacebar)
                    count++; // count the amount of letters found so far
                }
            }
            if(count == strlen(w)) { // if count equals the length of w then we found an answer
                char ans[i + 1]; // to hold the answer
                ans[0] = '\0';
                strncpy(ans, start, i);
                ans[i] = '\0';
                int last = strlen(ans) - 1;
                while(ans[last] == ' ' || ans[last] == '\t' || ans[last] == '\n') { //checks for extra spaces at the end
                    ans[last--] = '\0';
                }
                //sequence passes all requirements, therefore is printed
                if (flag == 0) {
                    flag = -1;
                    printf("%s", ans);
                } else {
                    printf("~%s", ans);
                }
            }
        }
        start++;
    }
}

/**
 * This function receives a pointer to a string and reverses the string
 * @param str
 */
void reverse(char *str) {
    char temp;
    for (char *start = str, *end = str + strlen(str) - 1; start < end; start++, end--) {
        temp = *start;
        *start = *end;
        *end = temp;
    }
}