/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Eleni Rotsides
 * Date        : 2/9/22
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>
using namespace std;

bool is_all_lowercase(const string &s)
{
    // returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.

    /* looping over the length of s
     if the char at index i in s is not found in the alphabet,
     then s contains chars that are not lowercase letters so it returns false
     otherwise, the string is valid and it returns true
     uses the isalpha and isupper methods to accomplish this*/
    for (size_t i = 0; i < s.size(); i++)
    {
        if (!isalpha(s[i]) || isupper(s[i]))
        {
            return false;
        }
    }
    return true;
}

bool all_unique_letters(const string &s)
{
    // returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.

    // used letters will be denoted with a 1
    unsigned int vector = 0;

    for (size_t i = 0; i < s.size(); i++)
    {
        // if the letter is unique, edit vector to represent this letter as being used for the next iteration
        if ((vector & (1 << (s[i] - 'a'))) == 0)
        {
            vector = vector | (1 << (s[i] - 'a'));
        }
        else
        { // the letter is not unique, return false
            return false;
        }
    }

    // if this point has been reached, then the string is unique, so return true
    return true;
}

int main(int argc, char *const argv[])
{
    // reads and parses command line arguments.
    // Calls other functions to produce correct output.

    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <string>" << endl;
        return 1;
    }

    if (!is_all_lowercase(argv[1]))
    {
        cerr << "Error: String must contain only lowercase letters." << endl;
        return 1;
    }

    if (!all_unique_letters(argv[1]))
    {
        cerr << "Duplicate letters found." << endl;
        return 1;
    }
    else
    {  // at this point, there is nothing wrong with the input, so the letters must be unique
        cout << "All letters are unique." << endl;
    }

    return 0;
}
