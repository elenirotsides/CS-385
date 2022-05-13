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
#include <algorithm>
using namespace std;

vector<string> alphabet{"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

#define INF INT_MAX

int ** floyd(int **weight, int num_vertices){
    //TODO
    int **D = weight;
    for(int k = 1; k < num_vertices; k++){
        for(int i = 1; i < num_vertices; i ++){
            for(int j = 1; j < num_vertices; j++){
                D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
            }
        }
    }
    return D;
}

// vector<string> parse(string str){

//     istringstream ss(str);

//     vector<string> parsed_string{};
  
//     string component;
//     while (ss >> component) 
//     {
//         parsed_string.push_back(component);
//     }

//     return parsed_string;
// }

// Checks that the line has 3 components
void check_number_of_components(vector<string> component_list, int line_number, string line) {
    if (component_list.size() != 3) {
        cerr << "Error: Invalid number of vertices '" << line << "' on line " << to_string(line_number) << "." << endl;
    }
}

// Checks that the starting vertex is within the range set by the first line of the text file
void check_starting_vertex(string component, int line_number, vector<string> vertex_range){
    if (!(find(vertex_range.begin(), vertex_range.end(), component) != vertex_range.end())){
        cerr << "Error: Starting vertex '" << component << "' on line " << to_string(line_number) << "is not among valid values A-" << vertex_range.back() << "." << endl;
    }
}

// Checks that the starting vertex is within the range set by the first line of the text file
void check_ending_vertex(string component, int line_number, vector<string> vertex_range){
    if (!(find(vertex_range.begin(), vertex_range.end(), component) != vertex_range.end())){
        cerr << "Error: Ending vertex '" << component << "' on line " << to_string(line_number) << "is not among valid values A-" << vertex_range.back() << "." << endl;
    }
}

// Checks that the weight given is a positive integer
void check_weight(int weight, int line_number){
    if (weight < 1){
        cerr << "Error: Invalid edge weight '" << weight << "' on line " << to_string(line_number) << "." << endl;
    }
}


// The code for display_table must be EDITED!! That is why it is currently commented out


// /**
// * Displays the matrix on the screen formatted as a table.
// */
// // ------------Taken from HW Doc ----------------
// void display_table(long** const matrix, const string &label, const bool use_letters = false, int num_vertices) {
//     cout << label << endl;
//     long max_val = 0;
//     for (int i = 0; i < num_vertices; i++) {
//         for (int j = 0; j < num_vertices; j++) {
//             long cell = matrix[i][j];
//             if (cell < INF && cell > max_val) {
//                 max_val = matrix[i][j];
//             }
//         }
//     }
//     int max_cell_width = use_letters ? len(max_val) :
//     len(max(static_cast<long>(num_vertices), max_val));
//     cout << ' ';
//     for (int j = 0; j < num_vertices; j++) {
//         cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
//     }
//     cout << endl;
//     for (int i = 0; i < num_vertices; i++) {
//         cout << static_cast<char>(i + 'A');
//         for (int j = 0; j < num_vertices; j++) {
//             cout << " " << setw(max_cell_width);
//             if (matrix[i][j] == INF) {
//                 cout << "-";
//             } else if (use_letters) {
//                 cout << static_cast<char>(matrix[i][j] + 'A');
//             } else {
//                 cout << matrix[i][j];
//             }
//         }
//         cout << endl;
//     }
//     cout << endl;
// }

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

        unsigned int line_number = 1;
        // Use getline to read in a line.
        // See http://www.cplusplus.com/reference/string/string/getline/
        while (getline(input_file, line))
        {
            //Checks the first line
            if (line_number == 1) {
                if ((int) line < 1 || (int) line > 26) {
                    cerr << "Error: Invalid number of vertices '" << line << "' on line 1.";
                }
                ++line_number;
                vector<string> vertex_range(alphabet.begin(), alphabet.begin() + (int) line); 
            }

            // Get each part of a line into a vector so we may check each input
            vector<string> components = parse(line);
            string starting_vertex = components.at(0);
            string ending_vertex = components.at(1);
            int weight = (int) components.at(2);

            // NOTE: We could either pass in the whole vector and extract the specific element we want to check in the function being called

            //       Or we could just pass in the specific elements as input

            check_number_of_components(components, line_number, line);
            check_starting_vertex(starting_vertex, line_number, vertex_range);
            check_ending_vertex(ending_vertex, line_number, vertex_range);
            check_weight(weight, line_number);

            // Once a line has been checked we need to input the edge into the matrices

            ++line_number;
        }

        // Once all of the matrices have been created we can now print the output

        
        // Don't forget to close the file.
        input_file.close();
    }
    catch (const ifstream::failure &f)
    {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }
    // ----Code taken from provided filereader.cpp file-----------------------------

    return 0;
}
