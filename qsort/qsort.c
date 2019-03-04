#include <stdio.h>
void quicksort(int *arr, int left, int right) {
    int i, j, t, temp;
    if(left > right)
        return;
    temp = arr[left]; 
    i = left;
    j = right;
    while(i != j) { 
        while(arr[j] >= temp && i < j)
            j--;
        while(arr[i] <= temp && i < j)
            i++;       
        if(i < j) {
            t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
        }
    }
    arr[left] = arr[i];
    arr[i] = temp;
    quicksort(arr,left, i-1);//继续处理左边的，这里是一个递归的过程
    quicksort(arr, i+1, right);//继续处理右边的 ，这里是一个递归的过程
}
int main() {
    int i;
    //读入数据
    //scanf("%d", &n);
    //for(i = 0; i < n; i++)
    //    scanf("%d", &a[i]);
    int n=10;
    int a[10] = {
        23,34,9,8,2,
        25,78,34,65,0
    };
    quicksort(a,0,n-1); 
    for(i = 0; i < n; i++)
        printf("%d ", a[i]);
    fprintf(stdout, "\n");
    //printf("%d\n", a[n]);
    return 0;
}
