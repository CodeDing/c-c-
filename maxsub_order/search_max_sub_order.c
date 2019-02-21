//#include<iostream>
//#include<vector>
//
//using namespace std;
//
#include<stdio.h>
#include<malloc.h>

//b[i]表示以第i个元素a[i]为结尾的最大子序列值
//b[i+1] = b[i] > 0 ? b[i] + a[i+1]: a[i+1]
//
const char* SEPERATOR = "*********************************\n";
void printArray(char *msg, int arr[], int start, int end) {
    printf(SEPERATOR);
    printf("%s: ", msg);
    int i;
    for(i = start; i < end; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return;
}

int searchMax(int arr[], int n) {
     int *b = (int *)malloc(n*sizeof(int));
     int i;
     //[firstIndex, lastIndex)
     int max, firstIndex, lastIndex;
     b[0] = arr[0];
     for (i = 0; i < n; i++) {
        b[i+1] = b[i] > 0 ? b[i] + arr[i+1]:arr[i+1]; 
     }

     max = b[0];
     firstIndex = 0;
     lastIndex = 0;
     for(i = 1; i < n; i++) {
         if (b[i] > max) {
             max = b[i];
             lastIndex = i + 1;
         }
         if (b[i-1] < 0) {
             firstIndex = i; 
         }
     }
     printArray("b[i]", b, 0, 10);
     printf("firstIndex = %d, lastIndex = %d\n", firstIndex, lastIndex);
     printArray("Max order", b, firstIndex, lastIndex);
     printf("Max sum: %d\n", b[lastIndex-1]);
     return b[lastIndex-1];
     
}

int main(int argc, char *argv[]) {


     int arr[10] = {2,-3,5,7,-9,20,30,-4,90,-7};
     int i;
     printArray("a[i]", arr, 0, 10);
     searchMax(arr, 10); 

     return 0;

}
