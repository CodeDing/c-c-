#include <iostream>

template <class T>
T GetMax(T a, T b) {
    T result;
    result = (a>b) ? (a):(b);
    return (result);
}

using namespace std;

int main() {

    int i=5,j=6;
    auto k = GetMax(i,j);
    std::cout<<k<<std::endl;
    return 0;
}
