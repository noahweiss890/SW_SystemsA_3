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
    } else {
        return 0;
    }
}

//gematria
void func1(char w[WORD + 1], char t[TXT + 1]) {

    int left, right, target, flag, sum;
    target = 0;
    for (int i=0; i < strlen(w); i++) { //finds gematria
        target += gematria_helper(w[i]);
    }
    left = 0;
    right = 0;
    flag = 0;
    sum = gematria_helper(t[0]);
    while (left < strlen(t)) {
        if (sum < target) {
            right++;
            while (gematria_helper(t[right]) == 0) {
                right++;
            }
            sum += gematria_helper(t[right]);
        }
        else if (sum > target) {
            if(left == right) {
                left++;
                while (gematria_helper(t[left]) == 0) {
                    left++;
                }
                right = left;
                sum = gematria_helper(t[left]);
            }
            else {
                sum -= gematria_helper(t[left]);
                left++;
                while (gematria_helper(t[left]) == 0) {
                    left++;
                }
            }
        }
        else {
            if(!flag){
                flag = 1;
            }
            else{
                printf("~");
            }
            for(int i = left; i < right+1; i++) {
                printf("%s", t[i]);
            }
            sum += gematria_helper(t[++right]) - gematria_helper(t[left++]);
            while (gematria_helper(t[left]) == 0) {
                left++;
            }
            while (gematria_helper(t[right]) == 0) {
                right++;
            }
        }
    }
}

//reverses the string
char* reverse(char *str) {
    int l;
    char *beginning_ptr, *end_ptr, temp;

    l = strlen(str);
    beginning_ptr = str;
    end_ptr = str;
    for (int i = 0; i < l - 1; i++) {
        end_ptr++;
    }
    for (int j = 0; j < l / 2; j++) {
        temp = *beginning_ptr;
        *beginning_ptr = *end_ptr;
        *end_ptr = temp;
    }
    return 0;
}
