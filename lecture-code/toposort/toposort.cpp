#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

// khan's algorithm for topological sort implementation

vector<int> toposort(vector<int> *graph, int V)
{ // *graph is the same thing as graph[]
    int *indegree = new int[V];

    fill(indegree, indegree + V, 0); // from algorithms header; same thing as writing a loop and filling in each value with 0

    for (int v1 = 0; v1 < V; v1++)
    {
        // Way #1
        for (int v2 : graph[v1])
        {                   // graph[v1]: corresponding adjacency list
            indegree[v2]++; // for each one found, increase indegree
        }

        // Way #2
        // for (size_t i = 0; i < graph[v1].size(); i++)
        // {
        //     int v2 = graph[v1][i];
        //     indegree[v2]++;
        // }
    }

    queue<int> S;

    for (int vertex = 0; vertex < V; vertex++)
    {
        if (indegree[vertex] == 0)
        {
            S.push(vertex);
        }
    }

    vector<int> L;

    // staring toposort!
    while (!S.empty())
    {
        int vertex = S.front(); // front copies from the queue, does NOT remove it
        S.pop();                // now vertex has been removed from the front of the queue

        L.push_back(vertex);

        for (int adjacent : graph[vertex])
        {
            indegree[adjacent]--; // simulate removing

            if (indegree[adjacent] == 0)
            {
                S.push(adjacent);
            }
        }
    }
    // end of toposort!

    // need to check every indegree to make sure that each one is 0

    // Way #1
    // if(L.size() == V){
    //     // if every vertex is in L, then we have successfully completed toposort

    // }

    // Way #2
    for (int vertex = 0; vertex < V; vertex++)
    {
        if (indegree[vertex] != 0)
        {
            L.clear();
            break; // no need to keep looping, we know that topo failed
        }
    }

    delete[] indegree;
    return L;
}

int main()
{
    int V, E;
    cin >> V >> E;
    vector<int> *graph = new vector<int>[V];

    while (E--)
    {
        int v1, v2;
        cin >> v1 >> v2;
        graph[v1].push_back(v2);
    }

    vector<int> order = toposort(graph, V);

    // if order is empty, then toposort failed
    if (order.size() > 0)
    {
        for (int vertex : order)
        {
            cout << vertex << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "failed" << endl;
    }

    delete[] graph;
    return 0;
}