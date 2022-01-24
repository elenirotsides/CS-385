#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int x;
    cout << "enter x : " << endl;
    cin >> x;
    cout << "You entered : " << x << endl;
    cout << fixed;
    cout << setprecision(20);
    cout << 3.0 / 734141243.0 << endl;
    return 0;
}