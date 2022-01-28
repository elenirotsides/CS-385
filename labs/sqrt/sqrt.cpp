/*******************************************************************************
 * Filename: sqrt.cpp
 * Author  : Eleni Rotsides
 * Version : 1.0
 * Date    : January 21, 2022
 * Description : Computes the square root of a double using Newton's method with an allowed difference of epsilon, if provided.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>
using namespace std;

double sqrt(double num, double epsilon)
{
    if (num < 0)
    {
        return numeric_limits<double>::quiet_NaN();
    }
    else if (num == 0 || num == 1)
    {
        return num;
    }

    double last_guess = 1;
    double next_guess = (last_guess + num / last_guess) / 2;

    for (int i = 0; abs(last_guess - next_guess) > epsilon; i++)
    {
        last_guess = next_guess;
        next_guess = (last_guess + num / last_guess) / 2;
    }

    return next_guess;
}

int main(int argc, char *argv[])
{
    double n, e;
    istringstream iss;

    if (argc < 2 || argc > 3)
    {
        cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
        return 1;
    }

    iss.str(argv[1]);
    if (!(iss >> n))
    {
        cerr << "Error: Value argument must be a double." << endl;
        return 1;
    }

    iss.clear();

    if (argc == 3)
    {
        iss.str(argv[2]);
        if (!(iss >> e) || e <= 0)
        {
            cerr << "Error: Epsilon argument must be a positive double." << endl;
            return 1;
        }
        cout << fixed << setprecision(8) << sqrt(n, e) << endl;
    }
    else
    {
        cout << fixed << setprecision(8) << sqrt(n, 1e-7) << endl;
    }

    return 0;
}
