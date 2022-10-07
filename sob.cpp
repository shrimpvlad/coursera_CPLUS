#include <iostream>
using namespace std;

int main() {
    int n,a,b;
    cin>>n>>a>>b;
    int x1 = b-a-1;
    int x2 = n-b+a-1;
    (x1 >= x2) ? cout << x2 << endl : cout << x1 << endl;
}

