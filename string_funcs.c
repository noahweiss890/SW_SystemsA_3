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
    int left, right, target = 0, flag, sum;
    for (int i = 0; i < strlen(w); i++) { //finds gematria of word
        target += gematria_helper(w[i]);
    }
    left = 0;
    right = 0;
    flag = 0;
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

//reverses the string
char *reverse(char *str) {
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

void func3(char w[WORD + 1], char t[TXT + 1]){
    char* temp[WORD + 1];

}


