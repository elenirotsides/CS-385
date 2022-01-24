#include <iostream>
#include <sstream>
using namespace std;

int max(int n, int m)
{
    // if(n > m){
    //     return n;
    // } else {
    //     return m;
    // }

    return n > m ? n : m;
}

int main(int argc, char *argv[])
{
    int n, m;
    istringstream iss; //input string

    if (argc != 3)
    {
        // argv[0] -> name of program
        cerr << "Usage: " << argv[0] << " <integer n> <integer m>" << endl;
        return 1; // 1 means something went wrong
    }

    iss.str(argv[1]); // initialize iss to read argv[1]
    if (!(iss >> n))
    { // storing into n. if it fails (if user types a string or something), give error
        cerr << "First command line argument must be an integer" << endl;
        return 1;
    }

    // IMPORTANT: need to reset the object correctly if reading from the same iss object
    iss.clear();

    iss.str(argv[2]);
    if (!(iss >> m))
    {
        cerr << "Second command line argument must be an integer" << endl;
        return 1;
    }

    cout << "n is: " << n << endl;
    cout << "m is: " << m << endl;

    cout << "max(" << n << ", " << m << ") is: " << max(n, m) << endl;

    return 0; // terminated correctly
}
