/*
 * 
Given a non-negative integer, you could swap two digits at most once to get the maximum valued number. Return the maximum valued number you could get.
Example 1: 
Input: 2736 
Output: 7236 
Explanation: Swap the number 2 and the number 7. 
Example 2: 
Input: 9973 
Output: 9973 
Explanation: No swap. 
Note: 
The given number is in the range [0, 108]
*/

/*
 *  思路: 
 *      1)整数分解从低到高, 将每位数字依次存入数组
 *      2)反转数组, 数组低索引存高位数据
 *      3)从索引0扫描数组, 如低位有数字比其大则发生交换, 同时退出; 如没有发生交换,则从索引1开始迭代,如低位有数字比其大则发生交换, 同时退出;
 *      依此迭代
 * */
#include <stdio.h>


int toInt(int* arr, int n){
    int res = 0;
    int i;
    for(i=0; i<n; i++){
        res = res*10 + arr[i];
    }
    return res;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int maximumSwap(int num) {
    int arr[20] = {0};
    int back = num, n = 0;
    while(back){
        arr[n++] = back % 10;
        back /= 10;
    }
    int i,j;
    for(i=0, j=n-1; i<j; i++, j--)
        swap(&arr[i], &arr[j]);
    for(i=0; i<n; i++){
        int maxn = arr[i];
        int index = i;
        for(j=i+1; j<n; j++){
            if(arr[j] >= maxn){
                index = j;
                maxn = arr[j];
            }
        }
        if(maxn > arr[i]){
            swap(&arr[i], &arr[index]);
            //交换过则退出
            return toInt(arr, n);
        }
    }
    return num;
}

/*

这个方法的思路在于：如果有一个低位数字比高位数字要大，那么交换它们肯定能使得当前数变得更大。为了在交换后得到最大的数，不但需要：与可能的最高位交换，也需要：确保你交换到最高位的数要尽量足够大。

算法如下:

从最低位一直遍历到最高位，存储迄今为止最大的数字。

如果当前数字比迄今为止最大的数字小，那么存储swap索引：当前数字的索引 和 迄今为止最大数字的索引。
如果当前数字比迄今为止最大的数字大，那么重置 迄今为止最大的数字。

最后，交换之前存储的两个swap索引。重新计算数字。
*/

int maximumSwapVersion2(int num) {
    int arr[20] = {0};
    int back = num, n = 0;
    while(back){
        arr[n++] = back % 10;
        back /= 10;
    }
    int i, j;
    int maxn = arr[0];
    int index = 0;
    int max_index = 0;
    for(i=1; i < n; i++) {
        if(maxn < arr[i]) {
          for(j = i+1; j < n; j++) {
            if(arr[j] < arr[i]) {
                maxn = arr[i];
                index = i;
                max_index = i;
            }
          }
        } else if(maxn > arr[i]){
            index = i; 
        }
    }

    if (max_index != index) {
        swap(&arr[index], &arr[max_index]);
    }

    int ret=0;
    for(i=n; i > 0; i--) {
        ret = ret*10 + arr[i-1];
    }
    return ret;
}

int maximumSwapVersion3(int num) {
    int arr[20] = {0};
    int back = num, n = 0;
    while(back){
        arr[n++] = back % 10;
        back /= 10;
    }
    int bucket[10] = {-1};
    int i, j;
    for(i=0, j=n-1; i<j; i++, j--)
        swap(&arr[i], &arr[j]);

    for(i=0; i<n; i++) {
        bucket[arr[i]] = i;     
    }
    int index =0;
    int max_index = 0;
    for(i=0; i<n; i++){
        for(j=9; j>0; j--) {
            if(bucket[j]>0 && bucket[j] > i && j > arr[i]) {
               index = i; 
               max_index = bucket[j];
               swap(&arr[index], &arr[max_index]);
               return toInt(arr,n);
            } 
        }
    }
    return num;
}


int main(int argc, char *argv[]) {
    int array[] = {98889292,432143532, 32314489, 7279797, 118923234, 98882701};
    int i;
    for(i = 0; i < sizeof(array)/sizeof(int); i++) {
        printf("origin number: %30d\n", array[i]);
        printf("swap number:     %30d\n", maximumSwap(array[i]));
        printf("swap number(V2): %30d\n", maximumSwapVersion2(array[i]));
        printf("swap number(V3): %30d\n", maximumSwapVersion3(array[i]));
    }
    return 0;
}
