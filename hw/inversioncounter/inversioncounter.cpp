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
    long numInversions = 0;

    for (int i = 0; i < length - 1; i++)
    {
        for (int j = i + 1; j < length; j++)
        {
            if (array[i] > array[j])
            {
                numInversions++;
            }
        }
    }

    return numInversions;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length)
{
    // initializing an empty array that has the same length as array
    int *scratch = new int[length];

    long numInversions = mergesort(array, scratch, 0, length - 1);

    delete[] scratch; // need to delete since scratch was allocated on the heap
    return numInversions;
}

static long mergesort(int array[], int scratch[], int low, int high)
{
    long numInversions = 0;

    // mergesort algorithm written according to pseudocode provided by prof borowski
    // in the lecture video on canvas

    if (low < high)
    {
        int mid = low + (high - low) / 2;

        //                       left side recursion                     right side recursion
        numInversions += mergesort(array, scratch, low, mid) + mergesort(array, scratch, mid + 1, high);

        int L = low;
        int H = mid + 1;

        for (int i = low; i <= high; i++)
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

                // if we need to take from the right side, then that means every number before array[H] is an inversion of array[H]
                numInversions += mid - L + 1; // formula taken from prof borowski's canvas video
            }
        }

        for (int i = low; i <= high; i++)
        {
            // copy the sorted scratch array into the original array
            array[i] = scratch[i];
        }
    }
    return numInversions;
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
    { // if the second arg isn't "slow", print error
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

    if (values.empty())
    {
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }

    if (argc == 2)
    {
        cout << "Number of inversions: " << count_inversions_slow(&values[0], values.size()) << endl;
    }
    else
    {
        cout << "Number of inversions: " << count_inversions_fast(&values[0], values.size()) << endl;
    }

    return 0;
}
