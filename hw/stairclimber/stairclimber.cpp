/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Eleni Rotsides
 * Date        : February 18, 2022
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector<vector<int>> get_ways(int num_stairs)
{
    // Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.

    // will contain all the possible combinations of ways to climb the stairs after the algorithm below executes
    vector<vector<int>> ways;

    // algorithm adapted from the provided stairclimber.py file
    // I tried to make the algorithm almost exactly identical to the python one, so I won't go into too much detail in my explanation here

    if (num_stairs <= 0)
    { // base case, inserting empty vector
        ways.push_back(vector<int>());
    }

    for (int i = 1; i < 4; i++) // only possible to move 1, 2 or 3 stairs at a time, so this loop should only execute 3 times
    {
        if (num_stairs >= i)
        {
            vector<vector<int>> result = get_ways(num_stairs - i); // recursive call

            for (auto &vector : result)
            {
                // need to prepend the value to the beginning of the vector
                vector.insert(vector.begin(), i);
            }
            // ready to insert the result
            ways.insert(ways.end(), result.begin(), result.end());
        }
    }
    return ways;
}

// resuing my num_digits function from the sieve PA; used to determine the width needed for formatting the ordered list in the output
int num_digits(int num)
{

    int counter = 0;

    while (num > 0)
    {
        num /= 10;
        counter++;
    }

    return counter;
}

void display_ways(const vector<vector<int>> &ways)
{
    // Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.

    // since the sum of values inside each vector is equal to the number of stairs, I need to calculate this
    // so that I can display the correct number in the output
    vector<int> num_stairs_vector = ways.at(0);
    int num_stairs = 0;

    for (const auto &num : num_stairs_vector)
    {
        // here is where I do the computation mentioned above; using a for loop to add num the result of the previous loop
        num_stairs += num;
    }

    // the number of possible combinations is equal to the length of the ways vector
    int numOfWays = ways.size();

    if (numOfWays == 1)
    { // need to display with proper grammer, so if there is one way, then the words in the output will be singular
        cout << numOfWays << " way to climb " << num_stairs << " stair." << endl;
    }
    else
    {
        cout << numOfWays << " ways to climb " << num_stairs << " stairs." << endl;
    }

    // doing some fun string concatination so that I can display the results in the proper output:

    // using a for loop to iterate over the size of ways, ie, perform the concatination for each vector,
    // so that I can just put the result as a string into a cout below
    for (size_t i = 0; i < ways.size(); i++)
    {
        string wayString = ""; // starts empty

        // for each number inside each vector, i
        for (size_t j = 0; j < ways[i].size(); j++)
        { // convert the number, ways[i][j] to a string, and then concat that with wayString
            // this will be done for each number inside the vector at ways[i] and a comma will also be added to the end of each number
            wayString += to_string(ways[i][j]) + ", ";
        }

        // it doesn't make sense to have a comma and a space after the last 'number' in the string wayString, so here,
        // I'm reassigning wayString to be the substring where the comma and space are cut out ie, wayString.length() - 2
        // since the last two chars are the comma and space
        wayString = wayString.substr(0, wayString.length() - 2);

        // ready to display the output after all that fun concatination!
        // using setw to right align the ordered list in the output and calling num_digits inside to determine how many spaces I need for this formatting
        cout << setw(num_digits(numOfWays)) << i + 1 << "."
             << " [" << wayString << "]" << endl;
    }
}

int main(int argc, char *const argv[])
{

    int num;
    istringstream iss;

    // only allowed two arugments, all other inputs are invalid
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <number of stairs>" << endl;
        return 1;
    }

    // need to ensure that num is an int, so using istringstream to make this determination
    iss.str(argv[1]);
    if (!(iss >> num) || num <= 0)
    { // if the number given isn't an int or if it is less than or equal to 0, output an error
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }

    // ready to call the function and display the results since we've ensured that the input given is valid
    display_ways(get_ways(num));

    return 0;
}
