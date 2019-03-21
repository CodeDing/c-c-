#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>


#define MAXLEN 100000

void reverse(char *str, int len) {
    int i;
    for(i = 0; i < len/2; i++) {
       char temp;
       temp = str[i];
       str[i] = str[len-1-i];
       str[len-1-i] =temp;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "You should run as: ./two_big arg1 arg2\n"); 
        exit(-1);
    }
    char *multiplierfactor1 = argv[1];
    char *multiplierfactor2 = argv[2];
    char result[MAXLEN];
    memset(result, 0, MAXLEN);
    int len1 = strlen(multiplierfactor1);
    int len2 = strlen(multiplierfactor2);
    int i,j;
    int carrier = 0;  //进位标识

    int max_bit=0;
    //下标从1开始计数
    for(i = len1; i > 0; i--) {
        for(j = len2; j > 0; j--) {
            int ret = (multiplierfactor1[i-1]-0x30)*(multiplierfactor2[j-1]-0x30);
            int temp = ret + result[len1+len2-i-j];
            result[len1+len2-i-j] = temp%10;
            result[len1+len2-i-j+1] = result[len1+len2-i-j+1] + temp/10;

        }
    }

    if (result[len1+len2-1] > 0) {
        max_bit = len1+len2; 
    } else {
        max_bit = len1+len2-1; 
    }

    for (i=0; i < max_bit; i++) {
        result[i] += 0x30; 
    }

    reverse(result, strlen(result));
    fprintf(stdout, "%s * %s = %s\n", argv[1], argv[2], result);

    return 0;
}
