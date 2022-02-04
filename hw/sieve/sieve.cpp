/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Eleni Rotsides
 * Date        : January 27, 2022
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve
{
public:
    PrimesSieve(int limit);

    // destructor
    ~PrimesSieve()
    {
        delete[] is_prime_;
    }

    int num_primes() const
    {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool *const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

// initialization list
PrimesSieve::PrimesSieve(int limit) : is_prime_{new bool[limit + 1]}, limit_{limit}
{
    sieve();
}

void PrimesSieve::display_primes() const
{
    const int max_prime_width = num_digits(max_prime_);
    const int primes_per_row = 80 / (max_prime_width + 1);

    int occupiedSpaces = 0;
    for (int i = 2; i <= limit_; i++)
    {
        if (is_prime_[i]) // if the number is prime, there are one of two situations that can occur:
        {
            if (num_primes() > primes_per_row)
            { // 1. when there will be more than one line of primes

                cout << setw(max_prime_width) << i;
                occupiedSpaces++;

                if (occupiedSpaces == primes_per_row)
                { // if there are no more spaces available on a line, reset the space counter and move to the next line
                    occupiedSpaces = 0;
                    cout << endl;
                }
                else if(i != max_prime_)
                { // otherwise, print a space so the numbers aren't glued together
                    cout << " ";
                }
            }
            else
            { // 2. when there will only be one line of primes
                cout << i;
                occupiedSpaces++;

                if (occupiedSpaces == num_primes())
                { // if the number of spaces occupied happens to be equal to the number of primes that exist,
                // then do not print a space after the last num and instead, reset the counter
                    occupiedSpaces = 0;
                }
                else
                {
                    cout << " ";
                }
            }
        }
    }
}

int PrimesSieve::count_num_primes() const
{
    /* counting the number of primes found using a for loop
     starting at 2 and then going until limit_ is reached
     storing the number of primes in a num counter variable */
    int num = 0;
    for (int i = 2; i <= limit_; i++)
    {
        if (is_prime_[i])
        {
            num++;
        }
    }

    return num;
}

void PrimesSieve::sieve()
{
    // set 0 and 1 to be false since these are both false, every other value assumed to be true
    is_prime_[0] = false;
    is_prime_[1] = false;

    // initialize every element in the is_prime_ array to be true except for 0 and 1 (start counting at 2)
    for (int i = 2; i <= limit_; i++)
    {
        is_prime_[i] = true;
    }

    // after initializing the array, now its time to execute the sieve algorithm as indicated in the requirements doc
    for (int i = 2; i <= sqrt(limit_); i++)
    {
        if (is_prime_[i])
        {
            for (int j = pow(i, 2); j <= limit_; j += i)
            {
                is_prime_[j] = false;
            }
        }
    }

    // counting backwards to find the max prime, so set counter equal to limit and then decrement until it is found
    int backwardsCounter = limit_;
    while (!is_prime_[backwardsCounter]) // iterating backwards until a prime is found using a while loop
    {
        backwardsCounter--; // decrement counter
    }

    // when the while loop breaks, the max prime has been found so, now max_prime_ needs to be assigned
    max_prime_ = backwardsCounter;

    // now that primes have been found, we need to find the count and assign it to num_primes
    num_primes_ = count_num_primes();
}

int PrimesSieve::num_digits(int num)
{
    /* counter variable will keep track of the number of loop iterations which will be the number of digits that exists
    dividing by 10 each time cuts the num by a factor of 10, which is a way of counting the digits
    returns the value of counter once num equals 0 */

    int counter = 0;

    while (num > 0)
    {
        num /= 10;
        counter++;
    }
    return counter;
}

int main()
{
    cout << "**************************** "
         << "Sieve of Eratosthenes"
         << " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if (!(iss >> limit))
    {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2)
    {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // create instance of the PrimesSieve class and then display the information 
    // (num of primes, the limit, and the list of primes in the appropriate format)
    PrimesSieve ps = PrimesSieve(limit);
    cout << endl;
    cout << "Number of primes found: " << ps.num_primes() << '\n';
    cout << "Primes up to " << limit << ":" << endl;
    ps.display_primes();

    return 0;
}
