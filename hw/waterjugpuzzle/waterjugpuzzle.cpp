/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Julio Lora, Eleni Rotsides
 * Date        : February 27, 2022
 * Description : Water Jug Puzzle
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

// Struct to represent state of water in the jugs.
struct State
{
    int a, b, c;
    string directions; // "pour from blank to blank" ...used for printing
    State *parent;

    State(int _a, int _b, int _c, string _directions) : a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} {}

    // String representation of state in tuple form.
    string to_string()
    {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

/**
 * @brief Helper function that returns the directions for the path of the pours with the minimum number of moves
 *
 * @param poppedCurrent - the state where the goal has been reached
 * @return string
 */
string backtrackHelper(State *poppedCurrent)
{
    stack<State *> reversed; // will hold the reversed queue of parents
    string directions = "";  // will hold all the directions of the parents

    reversed.push(poppedCurrent); // push the current state

    while (poppedCurrent->parent) // while the current state has a parent
    {
        reversed.push(poppedCurrent->parent); // push that the stack

        poppedCurrent = poppedCurrent->parent; // reset poppedCurrent to be its parent
    }

    while (!reversed.empty()) // while the stack contains states
    {
        State *current = reversed.top();                                       // make copy of the first state
        reversed.pop();                                                        // now remove that state from the stack
        directions += current->directions + " " + current->to_string() + "\n"; // add directions of current to directions string
    }

    return directions; // return the directions
}

// global variable that holds every state we create that has memory allocated to the heap; needs to be deleted before the program terminates execution
vector<State *> statesToDelete;

/**
 * @brief Helper function that attempts to pour from one jug to another jug in the order indicated by the algorithm we're supposed
 * to follow. Adds each state that has been created as a result of a successful pour, to the queue. Returns that queue.
 *
 * @param q - queue containing all the pours
 * @param currentState - the current state
 * @param maxA - maximum capacity of jug A
 * @param maxB - maximum capacity of jug B
 * @param maxC - maximum capacity of jug C
 * @return queue<State *>
 */
queue<State *> pourHelper(queue<State *> &q, State currentState, int maxA, int maxB, int maxC)
{
    // set the available capacities
    int availCapacityA = maxA - currentState.a;
    int availCapacityB = maxB - currentState.b;
    int availCapacityC = maxC - currentState.c;
    int amountToPour; // amount to pour in a jug, will be calculated in the following if blocks

    // make copy of currentState; after every successfull  pour, this becomes the parent of the new state we create
    State *parent = new State(currentState.a, currentState.b, currentState.c, currentState.directions);
    statesToDelete.push_back(parent);     // we need to delete this state before the program terminates execution, so push this new state to this queue
    parent->parent = currentState.parent; // set the parent

    // The following is attempting to pour in the order indicated in the requirements on the document provided.
    // Logic for all can be carried over to the next, meaning, we're only commenting on the first block "c to a", and those
    // comments can be transferred over to the other pour attempts; no need for redundant comments!

    // c to a
    if (currentState.c != 0 && availCapacityA > 0) // checks if c is not empty and there is space to pour in a
    {
        if (currentState.c >= availCapacityA) // checks if a fills up first
        {
            amountToPour = availCapacityA; // amount to pour is all of the available capacity

            currentState.a += amountToPour; // increase a by amountToPour
            currentState.c -= amountToPour; // decrease c by amountToPour
        }
        else if (availCapacityA > currentState.c) // checks if c empties out first
        {
            amountToPour = currentState.c; // amount to pour is all of c

            currentState.a += amountToPour; // increase a by amountToPour
            currentState.c -= amountToPour; // decrease c by amountToPour
        }

        if (amountToPour == 1) // checks if there is only 1 gallon to pour, we need proper grammar!
        {
            State *s = new State(currentState.a, currentState.b, currentState.c, "Pour " + to_string(amountToPour) + " gallon from C to A.");
            s->parent = parent;
            q.push(s);
            statesToDelete.push_back(s);
        }
        else // if there is more than 1 gallon to pour, create new state, set the parent, push that state to the queue, and push it to the statesToDelete queue
        {
            State *s = new State(currentState.a, currentState.b, currentState.c, "Pour " + to_string(amountToPour) + " gallons from C to A.");
            s->parent = parent;
            q.push(s);
            statesToDelete.push_back(s);
        }

        currentState = *parent; // reset original state
    }

    // b to a
    if (currentState.b != 0 && availCapacityA > 0)
    {

        if (currentState.b >= availCapacityA)
        {
            amountToPour = availCapacityA;

            currentState.a += amountToPour;
            currentState.b -= amountToPour;
        }
        else if (availCapacityA > currentState.b)
        {
            amountToPour = currentState.b;

            currentState.a += amountToPour;
            currentState.b -= amountToPour;
        }

        if (amountToPour == 1)
        {
            State *s = new State(currentState.a, currentState.b, currentState.c, "Pour " + to_string(amountToPour) + " gallon from B to A.");
            s->parent = parent;
            q.push(s);
            statesToDelete.push_back(s);
        }
        else
        {
            State *s = new State(currentState.a, currentState.b, currentState.c, "Pour " + to_string(amountToPour) + " gallons from B to A.");
            s->parent = parent;
            q.push(s);
            statesToDelete.push_back(s);
        }

        currentState = *parent;
    }

    // c to b
    if (currentState.c != 0 && availCapacityB > 0)
    {

        if (currentState.c >= availCapacityB)
        {
            amountToPour = availCapacityB;

            currentState.b += amountToPour;
            currentState.c -= amountToPour;
        }
        else if (availCapacityB > currentState.c)
        {
            amountToPour = currentState.c;

            currentState.b += amountToPour;
            currentState.c -= amountToPour;
        }

        if (amountToPour == 1)
        {
            State *s = new State(currentState.a, currentState.b, currentState.c, "Pour " + to_string(amountToPour) + " gallon from C to B.");
            s->parent = parent;
            q.push(s);
            statesToDelete.push_back(s);
        }
        else
        {
            State *s = new State(currentState.a, currentState.b, currentState.c, "Pour " + to_string(amountToPour) + " gallons from C to B.");
            s->parent = parent;
            q.push(s);
            statesToDelete.push_back(s);
        }

        currentState = *parent;
    }

    // a to b
    if (currentState.a != 0 && availCapacityB > 0)
    {
        if (currentState.a >= availCapacityB)
        {
            amountToPour = availCapacityB;

            currentState.b += amountToPour;
            currentState.a -= amountToPour;
        }
        else if (availCapacityB > currentState.a)
        {
            amountToPour = currentState.a;

            currentState.b += amountToPour;
            currentState.a -= amountToPour;
        }

        if (amountToPour == 1)
        {
            State *s = new State(currentState.a, currentState.b, currentState.c, "Pour " + to_string(amountToPour) + " gallon from A to B.");
            s->parent = parent;
            q.push(s);
            statesToDelete.push_back(s);
        }
        else
        {
            State *s = new State(currentState.a, currentState.b, currentState.c, "Pour " + to_string(amountToPour) + " gallons from A to B.");
            s->parent = parent;
            q.push(s);
            statesToDelete.push_back(s);
        }

        currentState = *parent;
    }

    // b to c
    if (currentState.b != 0 && availCapacityC > 0)
    {
        if (currentState.b >= availCapacityC)
        {
            amountToPour = availCapacityC;

            currentState.c += amountToPour;
            currentState.b -= amountToPour;
        }
        else if (availCapacityC > currentState.b)
        {
            amountToPour = currentState.b;

            currentState.c += amountToPour;
            currentState.b -= amountToPour;
        }

        if (amountToPour == 1)
        {
            State *s = new State(currentState.a, currentState.b, currentState.c, "Pour " + to_string(amountToPour) + " gallon from B to C.");
            s->parent = parent;
            q.push(s);
            statesToDelete.push_back(s);
        }
        else
        {
            State *s = new State(currentState.a, currentState.b, currentState.c, "Pour " + to_string(amountToPour) + " gallons from B to C.");
            s->parent = parent;
            q.push(s);
            statesToDelete.push_back(s);
        }

        currentState = *parent;
    }

    // a to c
    if (currentState.a != 0 && availCapacityC > 0)
    {
        if (currentState.a >= availCapacityC)
        {
            amountToPour = availCapacityC;

            currentState.c += amountToPour;
            currentState.a -= amountToPour;
        }
        else if (availCapacityC > currentState.a)
        {
            amountToPour = currentState.a;

            currentState.c += amountToPour;
            currentState.a -= amountToPour;
        }

        if (amountToPour == 1)
        {
            State *s = new State(currentState.a, currentState.b, currentState.c, "Pour " + to_string(amountToPour) + " gallon from A to C.");
            s->parent = parent;
            q.push(s);
            statesToDelete.push_back(s);
        }
        else
        {
            State *s = new State(currentState.a, currentState.b, currentState.c, "Pour " + to_string(amountToPour) + " gallons from A to C.");
            s->parent = parent;
            q.push(s);
            statesToDelete.push_back(s);
        }

        currentState = *parent;
    }

    return q;
}

/**
 * @brief A function that performs a  breadth-first search to find the minimum number of moves
 * to go from the initial state to the goal state. Returns the directions to achieve the min num of moves
 * or 'No Solution' if there is no solution.
 *
 * @param a - maximum capacity of A
 * @param b - maximum capacity of B
 * @param c - maximum capacity of C
 * @param goalA - the goal of jug A
 * @param goalB - the goal of jug B
 * @param goalC - the goal of jug C
 * @return string
 */
string bfs(int a, int b, int c, int goalA, int goalB, int goalC)
{
    queue<State *> q;                                // queue of current states
    State *s = new State(0, 0, c, "Initial state."); // initial state
    q.push(s);                                       // add initial state to queue
    statesToDelete.push_back(s);                     // need to delete the memory later!

    // create 2D array, taken from pseudocode provided --------------------//
    bool **graph = new bool *[a + 1];

    // For each row, make an array of 'some_other_size' booleans.
    for (int i = 0; i < a + 1; i++)
    {
        graph[i] = new bool[b + 1];

        // Initialize the new row.
        fill(graph[i], graph[i] + b + 1, false);
    }
    // --------------------------------------------------------------------//

    State *goal = new State(goalA, goalB, goalC, "goal state"); // the goal we need to reach
    statesToDelete.push_back(goal);                             // need to delete the memory later!

    while (!q.empty()) // bfs algorithm provided in the pseudocode
    {
        State *current = q.front();
        q.pop();

        if (current->to_string() == goal->to_string()) // checks if the goal has been reached
        {
            // Delete each row first. Taken from provided pseudocode
            for (int i = 0; i < a + 1; i++)
            {
                delete[] graph[i];
            }
            delete[] graph;
            string directions = backtrackHelper(current); // call helper so we can get directions

            // delete all the states we created
            for (size_t i = 0; i < statesToDelete.size(); i++)
            {
                delete statesToDelete[i];
            }
            return directions;
        }

        // reference the 2D array here to check if been seen
        if (graph[current->a][current->b])
        {
            continue;
        }

        graph[current->a][current->b] = true;

        // helper function for pouring
        q = pourHelper(q, *current, a, b, c);
    }

    // Delete each row first. Taken from provided pseudocode
    for (int i = 0; i < a + 1; i++)
    {
        delete[] graph[i];
    }
    delete[] graph;

    // delete all the states we created
    for (size_t i = 0; i < statesToDelete.size(); i++)
    {
        delete statesToDelete[i];
    }

    return "No solution.";
}

/**
 * @brief Function that checks user input, called inside of main before bfs is called
 *
 * @param argv - user input array from command line
 * @return int - 0 if all inputs are valid and 1 if there is an invalid input
 */
int check_inputs(char *argv[])
{ // we realize this can be written better...but this was painful and we're leaving this as is!
    int n;
    istringstream iss;

    string arguments[3] = {"A", "B", "C"};

    for (size_t i = 1; i < 4; i++) // checks the first three numeric inputs (capacities)
    {
        iss.str(argv[i]);
        if (!(iss >> n) || n < 1)
        {
            cerr << "Error: Invalid capacity "
                 << "'" << argv[i] << "'"
                 << " for jug " << arguments[i - 1] << "." << endl;
            return 1;
        }
        iss.clear();
    }

    for (size_t i = 4; i < 7; i++) // checks last three numeric inputs (goals)
    {
        iss.str(argv[i]);
        if (!(iss >> n) || n < 0)
        {
            cerr << "Error: Invalid goal "
                 << "'" << argv[i] << "'"
                 << " for jug " << arguments[i - 4] << "." << endl;
            return 1;
        }
        iss.clear();
    }

    for (size_t i = 4; i < 7; i++) // checks to see if the goal is exceeding the capacity
    {
        int x = atoi(argv[i]);
        int y = atoi(argv[i - 3]);

        if (x > y)
        {
            cerr << "Error: Goal cannot exceed capacity of jug " << arguments[i - 4] << "." << endl;
            return 1;
        }
    }

    int a = atoi(argv[4]);
    int b = atoi(argv[5]);
    int c = atoi(argv[6]);

    int goal = a + b + c;
    int maxCapacity = atoi(argv[3]);

    if (goal != maxCapacity) // checks if the goal state is not equal to the capacity of jug C
    {
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
        return 1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 7) // only 7 args allowed
    {
        cerr << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return 1;
    }

    if (check_inputs(argv) == 1) // if there was an error in user input, terminate execution
    {
        return 1;
    }

    int goalA = atoi(argv[4]);
    int goalB = atoi(argv[5]);
    int goalC = atoi(argv[6]);
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int c = atoi(argv[3]);

    cout << bfs(a, b, c, goalA, goalB, goalC) << endl; // get the directions!!!

    return 0;
}