/*
 *  假设:
 *     1)N个元素的整数数组, 其中已知有一个元素的个数超过了N/2个
 *  问题:
 *     基于算法复杂度O(logN),找出这个元素
 *
 *  扩展:
 *     有k个元素,他们的数量超过n/k, 计算得到这k个元素及各自数量
 * */

#include <stdio.h>
#include <stdlib.h>

#define bool char
#define true 1
#define false 0

bool find3Majority(int *array, int len, int *number1, int *cnt1, int *number2, int *cnt2) {
    int major1 = -1, major2 = -1, count1 = 0, count2 = 0;
    int i;
    for(i = 0; i < len; i++) {
        if(major1 == array[i]) {
            count1++; 
        } else if(major2 == array[i]) {
            count2++; 
        } else if (count1 == 0) {
            major1 = array[i];
            count1++; 
        } else if (count2 == 0) {
            major2 = array[i]; 
            count2++;
        } else {
            count1--; 
            count2--;
        }
    }

    for(i = 0; i < len; i++) {
        if (array[i] == major1) *cnt1 = *cnt1 + 1;
        if (array[i] == major2) *cnt2 = *cnt2 + 1;
    }

    if (*cnt1 > len/3 && *cnt2 > len/3) {
        *number1 = major1; 
        *number2 = major2; 
        return true;
    }
    return false;
}

bool findMajority(int *array, int len, int *number, int *cnt) {
   int major,count,i;
   major = array[0];
   count = 1;
   for(i = 1; i < len; i++) {
        if (array[i] == major) {
            count++;
        } else if (array[i] != major && count != 0) {
            count--;
        } else {
            major = array[i];    
        }
   }

   //double check
   for(i = 0; i < len; i++) {
        if (array[i] == major) *cnt = *cnt + 1;
   }
   if(*cnt > len/2) {
       *number = major;   
       return true;
   }
   return false;
}

int main(int argc, char *argv[]) {
   int array[] = {1,23,3,45,78,32,21,89,2,3,8,3,3,3,3,3,3,3,3,3};
   int i, count, major, len;
   len = sizeof(array)/sizeof(int);

   int number = 0, total = 0;
   if (findMajority(array, len, &number, &total)) {
        printf("Number: %d, occur %d times, exceed(n/2): %d\n", number, total, len/2); 
   } else {
        fprintf(stderr, "Not found such number which exceeds n/2!"); 
   }
   //bool find3Majority(int *array, int len, int *number1, int *cnt1, int *number2, int *cnt2) {
   int array2[] = {1,2,3,1,1,1,1,1,1,10,11,12,1l,11,11,11,11,11};
   int number1 = 0, total1 = 0;
   int number2 = 0, total2 = 0;
   if (find3Majority(array2, len, &number1, &total1, &number2, &total2)) {
        printf("Number1: %d, occur %d times, Number2: %d, occur %d times, exceed(n/2): %d\n", number1, total1, number2, total2, len/3); 
   } else {
        fprintf(stderr, "Not found such number which exceeds n/3!"); 
   }
   return 0;
   
}
