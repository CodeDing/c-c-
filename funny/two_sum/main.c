#include <stdio.h>
#include <string.h>
#define max 1024
void target(int a[],int len,int target)
{
    fprintf(stdout,"\n*****给定的数组为%p,数组长度为%d,给定的数值为%d*****************\n",a,len,target);
    int i,j=0;
    int tmp[max];//把a的值作为tmp下标
    int flag[max];
    memset(&tmp,-1,sizeof(int)*max);
    memset(&flag,-1,sizeof(int)*max);
    fprintf(stdout,"\n***************source array*******************\n");
    for(i = 0; i < len; i++)
    {
        //tmp[1] = 0;tmp[2]=1;tmp[7]=3;tmp[8]=4;tmp[9]=5;
        tmp[a[i]] = i;
        fprintf(stdout,"  -->%d[index=%d]\n",a[i],i);
    }
    fprintf(stdout,"\n*************给定一个数，该数等于数组中任意2个元素之和，输出元素下标*******************\n");
    for(i = 0; i < len; i++)
    {
        int v = target - a[i];//求出目标值减去数组值得差值
        if(v <= 0 || target <= a[i])
            continue;
        if(tmp[v] >= 0 && flag[a[i]] == -1 && flag[v] == -1)
        {
            fprintf(stdout," target = %d (%d,%d)  --> [%d,%d]\n",target,a[i],a[tmp[v]],i,tmp[v]);
            flag[a[i]] = (j++);
            flag[v] = j;
        }
    }
    fprintf(stdout,"********************算法的时间效率为O(n)*********************\n");
}
int main(void)
{
    int a[10] = {1,2,7,9,8,3,4,6,5,4,10};
    target(a,10,9);
    return 0;
}

