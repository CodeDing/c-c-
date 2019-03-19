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
        //int flag = false; // 多余
        for(j=i+1; j<n; j++){
            if(arr[j] >= maxn){
                //flag = true;
                index = j;
                maxn = arr[j];
            }
        }
        if(maxn > arr[i]){
            printf("=== swap ===");
            swap(&arr[i], &arr[index]);
            //交换过则退出
            return toInt(arr, n);
        }
    }
    return num;
}

int main(int argc, char *argv[]) {
    int num = 897214;
    printf("origin number: %d\n", num);
    printf("swap number: %d\n", maximumSwap(num));

    num = 127294;
    printf("origin number: %d\n", num);
    printf("swap number: %d\n", maximumSwap(num));
    return 0;
}
