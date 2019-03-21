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
const char* SEPERATOR = "*********************************************************\n";
void printArray(char *msg, int arr[], int start, int end) {
    printf("%s: ", msg);
    int i;
    for(i = start; i < end; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return;
}

int searchMax(int arr[], int n, int *start, int *end) {
     int *b = (int *)malloc(n*sizeof(int));
     int i;
     int max, firstIndex, firstIndexPre, lastIndex;
     b[0] = arr[0];
     for (i = 0; i < n; i++) {
        b[i+1] = b[i] > 0 ? b[i] + arr[i+1]:arr[i+1]; 
     }
     firstIndex = 0;
     firstIndexPre = 0;
     lastIndex = 1;
     max = arr[0];
     for(i = 1; i < n; i++) {
         if (b[i] > max) {
             max = b[i];
             lastIndex = i + 1;
         }
         if (b[i] > 0 && b[i-1] < 0) {
             if (max > b[i]) firstIndexPre = firstIndex;
             firstIndex = i;
         }
     }

     printf("firstIndexPre= %d, firstIndex = %d, lastIndex = %d\n", firstIndexPre, firstIndex, lastIndex);
     if (max < 0) {
        firstIndex = lastIndex - 1; 
     } else {
        if (firstIndex > lastIndex) {
            firstIndex = firstIndexPre; 
        } 
     }
     *start = firstIndex;
     *end = lastIndex;
     return max;
     
}

int main(int argc, char *argv[]) {
     int start, end, sum;
     int arr1[10] = {2,-3,5,7,-9,20,30,-4,90,-7};
     sum = searchMax(arr1, 10, &start, &end); 
     printf(SEPERATOR);
     printArray("arr1[i]", arr1, 0, 10);
     printArray("Max order", arr1, start, end);
     printf("Max sum: %d\n", sum);
     printf("%s\n", SEPERATOR);

     int arr2[10] = {-12,-3,-5,-7,-9,-20,-30,-4,-90,-7};
     sum = searchMax(arr2, 10, &start, &end); 
     printf(SEPERATOR);
     printArray("arr2[i]", arr2, 0, 10);
     printArray("Max order", arr2, start, end);
     printf("Max sum: %d\n", sum);
     printf("%s\n", SEPERATOR);

     int arr3[10] = {-2,3,1005,-1010,9,20,30,4,90,7};
     sum = searchMax(arr3, 10, &start, &end); 
     printf(SEPERATOR);
     printArray("arr3[i]", arr3, 0, 10);
     printArray("Max order", arr3, start, end);
     printf("Max sum: %d\n", sum);
     printf("%s\n", SEPERATOR);

     int arr4[20] = {-2,3,1005,-1010,9,20,30,4,90,7,-100009,1001,1,2,3,4,5,6,7,8};
     sum = searchMax(arr4, 20, &start, &end); 
     printf(SEPERATOR);
     printArray("arr4[i]", arr4, 0, 20);
     printArray("Max order", arr4, start, end);
     printf("Max sum: %d\n", sum);
     printf("%s\n", SEPERATOR);

     int arr5[10] = {2,-3,-1005,-1010,-9,-20,-30,-4,-90,-7};
     sum = searchMax(arr5, 10, &start, &end); 
     printf(SEPERATOR);
     printArray("arr5[i]", arr5, 0, 10);
     printArray("Max order", arr5, start, end);
     printf("Max sum: %d\n", sum);
     printf("%s\n", SEPERATOR);

     return 0;

}
