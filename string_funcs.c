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


char atbash_helper(char x){
    if(x >= 'A' && x <= 'Z'){

        return (char)(('Z' - gematria_helper(x)) + 1);
    }
    if(x >= 'a' && x <= 'z'){
        return (char)(('z' - gematria_helper(x)) + 1);
    }
    else{
        return x;
    }
}

//reverses the string
int reverse(char *str) {
    int l;
    char *beginning_ptr, *end_ptr, temp;

    l = (int)(strlen(str));
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
                printf("%c", t[i]);
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

void func2(char w[WORD + 1], char t[TXT + 1]){

    char atbsh_w[WORD + 1], atbsh_w_rev[WORD + 1];
    for (int i = 0; i < strlen(atbsh_w); i++) {
        atbsh_w[i] = atbash_helper(w[i]);
    }
    reverse(w);
    for (int i = 0; i < atbsh_w_rev; i++) {
        atbsh_w_rev[i] = atbash_helper(w[i]);
    }
}

void func3(char w[WORD + 1], char t[TXT + 1]){
    char* temp[WORD + 1];
    
}


