#include<iostream>
using namespace std;
void swap(int &a,int &b){
    int tmp;
    tmp = a;
    a = b;
    b = tmp;
}
void cal(int *a,int first,int length){
    if(first == length){
        for(int i = 0; i <= length; i++){
            std::cout<<a[i]<<' ';
        }
        std::cout<<endl;
    }
    else{
        for(int i = first; i <= length; i++){
           //循环遍历使得当前位置后边的每一个元素都和当前深度的第一个元素交换一次
           std::cout<<"first="<<first<<", i="<<i<<std::endl;
           std::cout<<"a[first]="<<a[first]<<", a[i]="<<a[i]<<std::endl;
           swap(a[first],a[i]);//使得与第一个元素交换
           cal(a,first+1,length);//深入递归，此时已确定前边的元素，处理后边子序列的全排列形式。
           swap(a[first],a[i]);//恢复交换之前的状态
        }
    }
}
int main(){
    int a[6] = {1,2,3,4,5,6};
    cal(a,0,5);
    return 0;
}
