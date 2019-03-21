
/*
 * a[0][0] a[0][1] ... a[0][p] ... a[0][q] ... a[0][n]
 * a[1][0] a[1][0] ... a[1][p] ... a[1][q] ... a[1][n]
 *   .                                            .
 *   .                                            .
 *   .                 ---------------------      .
 * a[i][0] a[i][0] ... |a[i][p] ... a[i][q] |... a[i][n]
 *   .                 |                    |     .
 *   .                 |                    |     .
 *   .                 |                    |     .
 * a[j][0] a[j][0] ... |a[j][p] ... a[j][q] |... a[j][n]
 *   .                 |--------------------|     .
 *   .                                            .
 *   .                                            .
 * a[m][0] a[m][0] ... a[m][p] ... a[m][q] ... a[m][n]
 *
 * 假设最大子矩阵是a[i][p] ... a[j][q]
 * 化归思想:
 *     如果把最大子矩阵同列的加起来，我们可以得到一个一维数组{a[q][i]+······+a[p][i] , ······ ，a[q][j]+······+a[p][j]} ，现在我们可以看出，这其实就是一个一维数组的最大子段问题。如果把二维数组看成是纵向的一维数组和横向的一维数组，那问题不就迎刃而解了吗？把二维转换成了我们刚刚解决了的问题
 *     实际求解问题: max_sub{a[i][p]+...a[j][p], ..., a[i][q]+...a[j][q]} 
 * 分解:
 *     1.假设最大子矩阵从第1行开始, 将依次计算与第2行的和并计算得出最大子序列,最大值用全局变量缓存, 计算与第2行和第3行的和并计算得出最大子序列,
 *       第1步操作得出含有第1行开始的所有子矩阵中, 最大总和及起始中止坐标 ...
 *     2.假设最大子矩阵从第2行开始, 将依次计算与第3行的和并计算得出最大子序列(同步骤1)
 *     3.重复迭代上述过程, 遍历完所有起始行后,得到最大子矩阵的起始和终止坐标
 *
 * */

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

string SEPERATOR("**********************************************************");

void printSeperator() {
    std::cout<<SEPERATOR<<std::endl;
}

void printArray(const char *msg, int arr[], int start, int end) {
    printSeperator();
    std::cout<<msg<<std::endl;
    if (start < end) {
        int i; 
        for(i = start; i < end; i++) {
            std::cout<<arr[i]<<" ";
        }
    }
    std::cout<<std::endl;
    return;
}

//通用性不够
void printMatrix(const string msg, int matrix[][10], int start_row, int start_col, int end_row, int end_col) {
    printSeperator();
    std::cout<<msg<<std::endl;
    int i,j;
    for(i = start_row; i < end_row; i++) {
        for(j = start_col; j < end_col; j++) {
            std::cout<<matrix[i][j]<<" ";
        }
        std::cout<<std::endl; 
    }
    return;
}

int maxsub(int a[],int n, int *start, int *end)   
{
    int i,max=0,b=0,first;
    *start = 0;
    *end = 1;
    for(i=0;i<n;i++)
    {
        if(b > 0)
            b += a[i];
        else {
            if (b < 0 && a[i] > 0) {
                if (b < max) first = *start;
                *start = i;
                //std::cout<<"i="<<i<<", first="<<first<<", start="<<*start<<", b="<<b<<", a[i]="<<a[i]<<std::endl;
            }
            b = a[i];
        }
        if(b > max) {
            *end = i+1;
            max = b;
        }
    }
    if (max < 0) {
        *start = *end - 1; 
    } 
    if (max > 0 && *start > *end) *start = first;
    std::cout<<"first="<<first<<", start="<<*start<<", end="<<*end<<", max="<<max<<std::endl;
    return max;
}


int main()
{
    int max, start, end;
    int array1[10] = {-2,-1,-9,-8,-17,-78,-45,-12,-23,-8};
    max = maxsub(array1, 10, &start, &end);
    printArray("OriginArray: ", array1, 0, 10);
    printArray("MaxSubArray: ", array1, start, end);

    int array2[20] = {-2,3,1005,-1010,9,20,30,4,90,7,-100009,1001,1,2,3,4,5,6,7,8};
    max = maxsub(array2, 20, &start, &end);
    printArray("OriginArray: ", array2, 0, 20);
    printArray("MaxSubArray: ", array2, start, end);

    int n,i,j,k,maxsubrec,maxsubarr;
    int dp[][10] = {
        {2,3,-1,5,10,-18,90,-8,-7,10},
        {2,3,-1,5,10,-18,90,-8,-7,10},
        {2,3,-1,5,10,-18,90,-8,-7,10},
        {2,3,-1,5,10,-180,90,-8,-7,10},
        {2,3,-1,5,10,-18,90,-8,-7,10},
        {2,3,-1,5,10,-18,90,-8,-7,10},
        {2,3,-1,5,10,-18,90,-8,-7,10},
        {2,3,-1,5,10,-18,90,-8,-7,10},
        {2,3,-1,5,10,-18,90,-8,-7,10},
        {2,3,-1,5,10,-18,90,-8,-7,10},
    };
    printMatrix("Origin Matrix: ", dp, 0,0,10,10); 
    int arr[10];
    n = 10;
    maxsubrec = 0;

    int firstRow, firstCol, endRow, endCol;
    for(i=0;i<n;i++) {
        memset(arr,0,sizeof(arr));
        for(j=i;j<n;j++)
        {
            for(k=0;k<n;k++)
                //row j sum
                arr[k] += dp[j][k];
            int firstColTemp, endColTemp;
            maxsubarr = maxsub(arr,n, &firstColTemp, &endColTemp);
            if(maxsubarr > maxsubrec) { 
                std::cout<<"maxsubrec = "<<maxsubarr<<std::endl;
                firstCol = firstColTemp;
                firstRow = i;
                endRow = j+1;
                endCol = endColTemp;
                maxsubrec = maxsubarr;
            }
        }
    }

    std::cout<<"fisrtRow: "<<firstRow<<", firstCol: "<<firstCol<<std::endl;
    std::cout<<"endRow: "<<endRow<<", endCol: "<<endCol<<std::endl;
    std::cout<<SEPERATOR<<std::endl;
    std::cout<<"MaxSubMatrix: "<<std::endl;
    for(i = firstRow; i < endRow; i++) {
        for(j = firstCol; j < endCol; j++) {
            std::cout<<dp[i][j]<<" ";
        }
        std::cout<<std::endl; 
    }

    std::cout<<"MaxSubMatrix: "<<maxsubrec<<std::endl;
}
