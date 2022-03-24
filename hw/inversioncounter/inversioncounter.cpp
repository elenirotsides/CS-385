/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Eleni Rotsides
 * Version     : 1.0
 * Date        : March 23, 2022
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length)
{
    // TODO
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length)
{
    // TODO
    // Hint: Use mergesort!
}

static long mergesort(int array[], int scratch[], int low, int high)
{
    // TODO
    if (low < high)
    {
        int mid = low + (high - low) / 2;

        mergesort(array, scratch, low, mid);
        mergesort(array, scratch, mid + 1, high);

        int L = low;
        int H = mid + 1;

        for (size_t i = low; i < high; i++)
        {
            if (L <= mid && (H > high || array[L] <= array[H]))
            {
                scratch[i] = array[L];
                L++;
            }
            else
            {
                scratch[i] = array[H];
                H++;
            }
        }

        for (size_t i = low; i < high; i++)
        {
            array[i] = scratch[i];
        }
    }
}

int main(int argc, char *argv[])
{

    if (argc > 2)
    {
        cerr << "Usage: " << argv[0] << " [slow]" << endl;
        return 1;
    }

    string secondArg;
    istringstream iss;

    if (argc == 2)
    {
        iss.str(argv[1]);
        if (!(iss >> secondArg) || secondArg != "slow")
        {
            cerr << "Error: Unrecognized option "
                 << "'" << argv[1] << "'." << endl;
            return 1;
        }
        iss.clear();
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true)
    {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln)
        {
            if (str.length() > 0)
            {
                iss.str(str);
                if (iss >> value)
                {
                    values.push_back(value);
                }
                else
                {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln)
            {
                break;
            }
            str.clear();
        }
        else
        {
            str += c;
        }
    }

    // TODO: produce output

    if (values.empty())
    {
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }

    if (argc == 2)
    {
    // cout << "Number of inversions: 0" << endl;
    TODO:
    }
    else
    {
    // cout << "Number of inversions: 0" << endl;
    TODO:
    }

    return 0;
}
