/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : Eleni Rotsides, Julio Lora
 * Version     : 1.0
 * Date        : April 25, 2022
 * Description : Implementation of Floyd's Algorithm.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <climits>
#include <algorithm>
using namespace std;

vector<string> alphabet{"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

#define INF INT_MAX

vector<string> parse(string line) // "A C 2"
{

    vector<string> parsed_string{};
    string element;       // declare string variables
    stringstream X(line); // X is an object of stringstream that references the S string

    // use while loop to check the getline() function condition
    while (getline(X, element, ' '))
    {
        /* X represents to read the string from stringstream, T use for store the token string and,
         ' ' whitespace represents to split the string where whitespace is found. */

        parsed_string.push_back(element);
    }
    return parsed_string;
}

// Checks that the line has 3 components
int check_number_of_components(vector<string> component_list, int line_number, string line)
{
    if (component_list.size() != 3)
    {
        cerr << "Error: Invalid edge data '" << line << "' on line " << to_string(line_number) << "." << endl;
        return 1;
    }
    return 0;
}

// Checks that the starting vertex is within the range set by the first line of the text file
int check_starting_vertex(string component, int line_number, vector<string> vertex_range)
{
    if (!(find(vertex_range.begin(), vertex_range.end(), component) != vertex_range.end()))
    {
        cerr << "Error: Starting vertex '" << component << "' on line " << to_string(line_number) << " is not among valid values A-" << vertex_range.back() << "." << endl;
        return 1;
    }
    return 0;
}

// Checks that the starting vertex is within the range set by the first line of the text file
int check_ending_vertex(string component, int line_number, vector<string> vertex_range)
{
    if (!(find(vertex_range.begin(), vertex_range.end(), component) != vertex_range.end()))
    {
        cerr << "Error: Ending vertex '" << component << "' on line " << to_string(line_number) << " is not among valid values A-" << vertex_range.back() << "." << endl;
        return 1;
    }
    return 0;
}

// Checks that the weight given is a positive integer
int check_weight(string weight, int line_number)
{
    stringstream ss;
    long weightNum;
    ss << weight;

    if (!(ss >> weightNum) || weightNum < 1)
    {
        cerr << "Error: Invalid edge weight '" << weight << "' on line " << to_string(line_number) << "." << endl;
        return 1;
    }
    return 0;
}

int len(int num)
{
    int counter = 0;

    while (num > 0)
    {
        num /= 10;
        counter++;
    }
    return counter;
}

/**
 * Displays the matrix on the screen formatted as a table.
 */
//------------Taken from HW Doc ----------------
void display_table(long **const matrix, const string &label, bool use_letters, int num_vertices)
{
    cout << label << endl; // name of table
    long max_val = 0;
    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = 0; j < num_vertices; j++)
        {
            long cell = matrix[i][j];
            if (cell < INF && cell > max_val)
            {
                max_val = matrix[i][j];
            }
        }
    }
    int max_cell_width = use_letters ? len(max_val) : len(max(static_cast<long>(num_vertices), max_val));
    cout << ' ';
    for (int j = 0; j < num_vertices; j++)
    {
        cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
    }
    cout << endl;
    for (int i = 0; i < num_vertices; i++)
    {
        cout << static_cast<char>(i + 'A');
        for (int j = 0; j < num_vertices; j++)
        {
            cout << " " << setw(max_cell_width);
            if (matrix[i][j] == INF)
            {
                cout << "-";
            }
            else if (use_letters)
            {
                cout << static_cast<char>(matrix[i][j] + 'A');
            }
            else
            {
                cout << matrix[i][j];
            }
        }
        cout << endl;
    }
    cout << endl;
}

void floyd(long **distance_matrix, int num_vertices)
{
    long **D = distance_matrix;
    long **interm = new long *[num_vertices];

    // For each row, make an array of 'some_other_size' longs.
    for (int i = 0; i < num_vertices; i++)
    {
        interm[i] = new long[num_vertices];

        // Initialize the new row.
        fill(interm[i], interm[i] + num_vertices, INF);
    }
    // TODO: take out the trash!!

    for (int k = 1; k < num_vertices; k++)
    {
        for (int i = 1; i < num_vertices; i++)
        {
            for (int j = 1; j < num_vertices; j++)
            {
                if (D[i][k] + D[k][j] < D[i][j])
                {
                    // we know its gonna be overwritten! setting the interm index
                    interm[i][j] = k;
                }
                D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
            }
        }
    }

    // set every vertex pointing to itself to 0
    for (int i = 0; i < num_vertices; i++)
    {
        distance_matrix[i][i] = 0;
        D[i][i] = 0;
    }

    display_table(distance_matrix, "Distance matrix:", false, num_vertices);
    display_table(D, "Path lengths:", false, num_vertices);
    display_table(interm, "Intermediate vertices:", true, num_vertices);

    // backtrack
    // for (int i = 0; i < num_vertices; i++)
    // {
    //     for (int j = 0; i < num_vertices; j++)
    //     {
    //         vector<string> path = backtracker(interm[i][j], interm, alphabet[i], alphabet[j]);

    //         string pathString = "";
            
    //         for(size_t i = 0; i < path.size(); i++){
    //             if(i == path.size() - 1 ){
    //                 pathString += alphabet[i];
    //             } else {
    //                 pathString += alphabet[i] + " -> ";
    //             }
    //         }

    //         cout << alphabet[i] << " -> " << alphabet[j] << ", distance: " << count_distance(path, interm) << ", path: " << pathString << endl;
    //     }
    // }
}
// vector<string> pathInBacktracker;
// vector<string> backtracker(long index, long ** matrix, string to, string from)
// {
    
//     // if(index == INF){
//     //     path.push_back(from);
//     // } else{
//     //     path.push_back(from);

//     //     while(index != INF){

//     //     }
//     // }

//     while(index != INF){
//         pathInBacktracker.push_back(from);
//         backtracker(matrix[][index], matrix, alphabet[index], from);
//     }
// }

long count_distance(vector<string> path, long **matrix)
{
    long counter = 0;
    // path example: a b c d
    for (size_t i = 0; i < path.size() - 1; i++)
    {
        auto it_letter = find(alphabet.begin(), alphabet.end(), path.at(i));

        // If element was found
        int index_letter;
        if (it_letter != alphabet.end())
        {

            // calculating the index of starting_vertex
            index_letter = it_letter - alphabet.begin();
        }

        auto it_letter2 = find(alphabet.begin(), alphabet.end(), path.at(i + 1));

        // If element was found
        int index_letter2;
        if (it_letter2 != alphabet.end())
        {

            // calculating the index of starting_vertex
            index_letter2 = it_letter2 - alphabet.begin();
        }
        counter += matrix[index_letter][index_letter2];
    }
    return counter;
}

void take_out_the_trash(long **matrix, int num_vertices)
{
    for (int i = 0; i < num_vertices; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main(int argc, const char *argv[])
{
    // ----Code taken from provided filereader.cpp file-----------------------------
    // Make sure the right number of command line arguments exist.
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    // Create an ifstream object.
    ifstream input_file(argv[1]);
    // If it does not exist, print an error message.
    if (!input_file)
    {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }

    // Add read errors to the list of exceptions the ifstream will handle.
    input_file.exceptions(ifstream::badbit);
    string line;
    try
    {

        // Initialize distance_matrix - not sure how to do that exactly due to syntax
        long **distance; // ??
        int num_vertices;

        unsigned int line_number = 1;
        // Use getline to read in a line.
        // See http://www.cplusplus.com/reference/string/string/getline/

        vector<string> vertex_range;
        while (getline(input_file, line))
        {
            // Checks the first line
            if (line_number == 1)
            {
                stringstream ss; // stringstream object
                long num;        // will store the line as an int
                ss << line;      // extracts the string from the line variable
                ss >> num;       // stores the converted variable into num

                if (num < 1 || num > 26)
                {
                    cerr << "Error: Invalid number of vertices '" << line << "' on line 1.";
                    return 1;
                }

                num_vertices = num;
                // ----------------------------
                // create 2D array, taken from pseudocode provided --------------------//
                distance = new long *[num_vertices];

                // For each row, make an array of 'some_other_size' longs.
                for (int i = 0; i < num_vertices; i++)
                {
                    distance[i] = new long[num_vertices];

                    // Initialize the new row.
                    fill(distance[i], distance[i] + num_vertices, INF);
                }
                //-------------------------------

                ++line_number;

                vector<string> range(alphabet.begin(), alphabet.begin() + num);
                vertex_range = range;
            }
            else
            {
                // Get each part of a line into a vector so we may check each input

                vector<string> components = parse(line);

                if (check_number_of_components(components, line_number, line) == 1)
                {
                    take_out_the_trash(distance, num_vertices);
                    return 1;
                }

                string starting_vertex = components.at(0);

                if (check_starting_vertex(starting_vertex, line_number, vertex_range) == 1)
                {
                    take_out_the_trash(distance, num_vertices);
                    return 1;
                }

                string ending_vertex = components.at(1);
                if (check_ending_vertex(ending_vertex, line_number, vertex_range) == 1)
                {
                    take_out_the_trash(distance, num_vertices);
                    return 1;
                }

                string weight = components.at(2);
                if (check_weight(weight, line_number) == 1)
                {
                    take_out_the_trash(distance, num_vertices);
                    return 1;
                }
                // Once a line has been checked we need to input the edge into the matrices

                auto it_start = find(alphabet.begin(), alphabet.end(), starting_vertex);

                // If element was found
                int index_start;
                if (it_start != alphabet.end())
                {

                    // calculating the index of starting_vertex
                    index_start = it_start - alphabet.begin();
                }

                auto it_end = find(alphabet.begin(), alphabet.end(), ending_vertex);

                // If element was found
                int index_end;
                if (it_end != alphabet.end())
                {

                    // calculating the index of ending_vertex
                    index_end = it_end - alphabet.begin();
                }

                stringstream ss;
                long weightNum;
                ss << weight;
                ss >> weightNum;

                distance[index_start][index_end] = weightNum;

                ++line_number;
            }
        }

        // call floyd
        floyd(distance, num_vertices);

        // Once all of the matrices have been created we can now print the output

        // Don't forget to close the file.
        input_file.close();

        take_out_the_trash(distance, num_vertices);
    }
    catch (const ifstream::failure &f)
    {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }
    // ----Code taken from provided filereader.cpp file-----------------------------

    return 0;
}