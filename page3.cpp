#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <algorithm>
#include <unordered_map>
#include <stack>
#include <fstream>
#include <sstream>
#include <string.h>
#include "demo.cpp"

#define int_max 9999
#define int_min -9999

int totalCost = 0;

using namespace std;
const string filename1 = "graph.dot";
const string file = "graph.png";
template <class T>
class Vertex
{
public:
    T data;
    vector<Vertex<T> *> adj;
    vector<pair<Vertex *, int>> wadj;
    int dist;
    vector<Vertex<T> *> path;
    bool known;
    int indeg;
    int outdeg;

    Vertex(T value) : data(value), dist(0), indeg(0), outdeg(0), known(false) {}
};

template <class T>
class Graph
{
public:
    int V;
    vector<Vertex<T> *> graph;

    Graph()
    {
        V = 0;
    }
    ~Graph()
    {
        for (auto v : graph)
        {
            delete v;
        }
    }

    void insert(T t)
    {
        Vertex<T> *v = new Vertex<T>(t);
        graph.push_back(v);
        V++;
        // cout << "inserted\n";
    }

    void insertEdge(T src, T dest, int cost)
    {
        Vertex<T> *source = nullptr;
        Vertex<T> *destination = nullptr;

        for (auto v : graph)
        {
            if (v->data == src)
            {
                source = v;
            }
            if (v->data == dest)
            {
                destination = v;
            }
        }

        if (source && destination)
        {
            source->wadj.push_back(make_pair(destination, cost));
            destination->indeg++;
            source->outdeg++;
        }
        else
        {
            if (source)
            {
                cout << "dest not found";
            }
            else
            {
                cout << "Z not found";
            }
        }
        dest = src;
    }

    void adjlist()
    {
        cout << "\nADJ_LIST : \n";

        for (auto v : graph)
        {
            cout << v->data << "->";
            for (auto u : v->adj)
            {
                cout << u->data << "->";
            }
            cout << "\n|\n";
        }
    }

    void displayAllPathsUtil(Vertex<T> *u, Vertex<T> *d, vector<Vertex<T> *> &path)
    {
        u->known = true;
        path.push_back(u);

        if (u == d)
        {
            for (auto v : path)
            {
                cout << v->data << "->";
            }
            cout << endl;
        }
        else
        {
            for (auto i : u->wadj)
            {
                if (!i.first->known)
                {
                    displayAllPathsUtil(i.first, d, path);
                }
            }
        }

        path.pop_back();
        u->known = false;
    }

    void displayAllPaths(T src, T dest)
    {
        Vertex<T> *source = nullptr;
        Vertex<T> *destination = nullptr;

        for (auto v : graph)
        {
            if (v->data == src)
            {
                source = v;
            }
            if (v->data == dest)
            {
                destination = v;
            }
        }

        if (source && destination)
        {
            vector<Vertex<T> *> path;
            displayAllPathsUtil(source, destination, path);
        }
        else
        {
            cout << "Source or destination not found\n";
        }
    }

    void dijkstra(T src)
    {
        // Implementation of Dijkstra's algorithm
        // ...
    }

    void calculateShortestPath(T src, T dest)
    {
        // Initialize distances and known flags
        for (auto v : graph)
        {
            v->dist = int_max;
            v->known = false;
            v->path.clear();
        }

        // Set distance of source vertex to 0
        for (auto v : graph)
        {
            if (v->data == src)
            {
                v->dist = 0;
                break;
            }
        }

        // Priority queue to store vertices with their distances
        priority_queue<pair<int, Vertex<T> *>, vector<pair<int, Vertex<T> *>>, greater<pair<int, Vertex<T> *>>> pq;

        // Push all vertices into priority queue
        for (auto v : graph)
        {
            pq.push(make_pair(v->dist, v));
        }

        // Dijkstra's algorithm
        while (!pq.empty())
        {
            Vertex<T> *u = pq.top().second;
            pq.pop();

            if (!u->known)
            {
                u->known = true;

                // Relaxation of edges
                for (auto edge : u->wadj)
                {
                    Vertex<T> *v = edge.first;
                    int weight = edge.second;

                    if (u->dist + weight < v->dist)
                    {
                        v->dist = u->dist + weight;
                        v->path = u->path;
                        v->path.push_back(u);
                        pq.push(make_pair(v->dist, v));
                    }
                }
            }
        }
        ofstream file(filename1, ios::app);
        // Display shortest path to destination vertex
        cout << "Shortest Path from " << src << " to " << dest << ":\n";
        for (auto v : graph)
        {
            if (v->data == dest)
            {
                if (v->dist == int_max)
                {
                    cout << "No path exists from " << src << " to " << dest << endl;
                }
                else
                {
                    cout << "Cost: " << v->dist << endl
                         << " Path: ";
                    for (auto vertex : v->path)
                    {
                        cout << vertex->data << " -> ";
                    }
                    // for (auto vertex : v->path)
                    // {

                    //     if (file.is_open())
                    //     {
                    //         file << vertex->data << " -> ";
                    //         file.close();
                    //     }
                    // }
                    cout << dest << endl;
                    // file << dest << endl;
                    break;
                }
            }
        }
    }

    void graphviz(T src, T dest)
    {
        // Initialize distances and known flags
        for (auto v : graph)
        {
            v->dist = int_max;
            v->known = false;
            v->path.clear();
        }

        // Set distance of source vertex to 0
        for (auto v : graph)
        {
            if (v->data == src)
            {
                v->dist = 0;
                break;
            }
        }

        // Priority queue to store vertices with their distances
        priority_queue<pair<int, Vertex<T> *>, vector<pair<int, Vertex<T> *>>, greater<pair<int, Vertex<T> *>>> pq;

        // Push all vertices into priority queue
        for (auto v : graph)
        {
            pq.push(make_pair(v->dist, v));
        }

        // Dijkstra's algorithm
        while (!pq.empty())
        {
            Vertex<T> *u = pq.top().second;
            pq.pop();

            if (!u->known)
            {
                u->known = true;

                // Relaxation of edges
                for (auto edge : u->wadj)
                {
                    Vertex<T> *v = edge.first;
                    int weight = edge.second;

                    if (u->dist + weight < v->dist)
                    {
                        v->dist = u->dist + weight;
                        v->path = u->path;
                        v->path.push_back(u);
                        pq.push(make_pair(v->dist, v));
                    }
                }
            }
        }
        ofstream file(filename1, ios::app);
        // Display shortest path to destination vertex
        // cout << "Shortest Path from " << src << " to " << dest << ":\n";
        for (auto v : graph)
        {
            if (v->data == dest)
            {
                if (v->dist == int_max)
                {
                    cout << "No path exists from " << src << " to " << dest << endl;
                }
                else
                {
                    file << "digraph {\n ";

                    for (auto vertex : v->path)
                    {

                        if (file.is_open())
                        {
                            file << vertex->data << " -> ";
                        }
                    }
                    // cout << dest << endl;
                    file << dest << endl;
                    file << "}\n";
                    file.close();
                    break;
                }
            }
        }
    }

    void displayIndegree()
    {
        cout << "Indegree of vertices:\n";
        for (auto v : graph)
        {
            cout << v->data << ": " << v->indeg << endl;
        }
    }

    void displayOutdegree()
    {
        cout << "Outdegree of vertices:\n";
        for (auto v : graph)
        {
            cout << v->data << ": " << v->outdeg << endl;
        }
    }

    void allTopologicalSortUtil(vector<Vertex<T> *> &res, bool visited[], vector<int> &indegree)
    {
        bool flag = false;

        for (auto v : graph)
        {
            if (indegree[getIndex(v)] == 0 && !visited[getIndex(v)])
            {
                for (auto adj : v->adj)
                {
                    indegree[getIndex(adj)]--;
                }

                res.push_back(v);
                visited[getIndex(v)] = true;
                allTopologicalSortUtil(res, visited, indegree);

                visited[getIndex(v)] = false;
                res.pop_back();
                for (auto adj : v->adj)
                {
                    indegree[getIndex(adj)]++;
                }

                flag = true;
            }
        }

        if (!flag)
        {
            for (auto v : res)
            {
                cout << v->data << " ";
            }
            cout << endl;
        }
    }

    void allTopologicalSort()
    {
        vector<int> indegree(graph.size(), 0);
        bool *visited = new bool[graph.size()];
        vector<Vertex<T> *> res;

        for (auto v : graph)
        {
            visited[getIndex(v)] = false;
            for (auto adj : v->adj)
            {
                indegree[getIndex(adj)]++;
            }
        }

        allTopologicalSortUtil(res, visited, indegree);

        delete[] visited;
    }

    int getIndex(Vertex<T> *v)
    {
        for (int i = 0; i < graph.size(); ++i)
        {
            if (graph[i] == v)
            {
                return i;
            }
        }
        return -1;
    }

    void traversePath(T start)
    {
        Vertex<T> *current = nullptr;

        // Find the starting vertex
        for (auto v : graph)
        {
            if (v->data == start)
            {
                current = v;
                break;
            }
        }

        if (!current)
        {
            cout << "Start vertex not found!\n";
            return;
        }

        // Traverse until reaching a vertex with no outgoing edges
        while (current && current->outdeg > 0)
        {
            cout << "Options:\n";
            int optionNum = 1;
            for (auto i : current->wadj)
            {
                if (i.second != 0)
                {
                    cout << optionNum << ". " << i.first->data << " (Cost: " << i.second << ")\n";
                    optionNum++;
                }
            }
            cout << "Select an option: ";
            int choice;
            cin >> choice;

            // Validate user input
            if (choice < 1 || choice > current->wadj.size())
            {
                cout << "Invalid choice!\n";
                continue;
            }

            // Find the next vertex based on user's choice
            auto nextVertex = current->wadj[choice - 1].first;
            totalCost += current->wadj[choice - 1].second; // Add edge cost to total
            current = nextVertex;                          // Move to the next vertex
        }

        // Reached a vertex with no outgoing edges
        cout << endl
             << GREEN << "Reached end of path. " << RESET << endl
             << BLUE << "Total cost: " << totalCost << RESET << endl;
    }

    void topologicalSortUtil(Vertex<T> *v, stack<Vertex<T> *> &stack)
    {
        v->known = true;

        for (auto &adj : v->adj)
        {
            if (!adj->known)
            {
                topologicalSortUtil(adj, stack);
            }
        }

        stack.push(v);
    }

    void topologicalSort(vector<Vertex<T> *> &sortedVertices)
    {
        stack<Vertex<T> *> stack;

        for (auto &v : graph)
        {
            if (!v->known)
            {
                topologicalSortUtil(v, stack);
            }
        }

        while (!stack.empty())
        {
            sortedVertices.push_back(stack.top());
            stack.pop();
        }
    }

    void longestPath(T src, T dest)
    {
        // Find the source vertex pointer
        Vertex<T> *srcVertex = nullptr;
        for (auto v : graph)
        {
            if (v->data == src)
            {
                srcVertex = v;
                break;
            }
        }

        if (!srcVertex)
        {
            cout << "Source vertex not found!\n";
            return;
        }

        // Perform topological sort
        vector<Vertex<T> *> sortedVertices;
        topologicalSort(sortedVertices);

        // Initialize distances
        unordered_map<Vertex<T> *, int> dist;
        for (auto v : graph)
        {
            dist[v] = int_min;
        }
        dist[srcVertex] = 0;

        // Update distances
        for (auto u : sortedVertices)
        {
            if (dist[u] != int_min)
            {
                for (auto edge : u->wadj)
                {
                    Vertex<T> *v = edge.first;
                    int weight = edge.second;
                    dist[v] = max(dist[v], dist[u] + weight);
                }
            }
        }

        // Display longest path to destination vertex
        cout << "Longest Path from " << src << " to " << dest << ":\n";
        for (auto v : graph)
        {
            if (v->data == dest)
            {
                if (dist[v] == int_min)
                {
                    cout << "No path exists from " << src << " to " << dest << endl;
                }
                else
                {
                    cout << "Cost: " << dist[v] << endl;
                }
                break;
            }
        }
    }
};

void showMenu()
{
    cout << "Main Menu:\n";

    cout << "1. Complete graph\n";
    cout << "2. Insert customized process from file \n";
    cout << "3. Calculate shortest path\n";
    cout << "4. Track path\n";
    cout << "5. Display indegree\n";
    cout << "6. Display outdegree\n";
    cout << "7. Display all possible paths\n";
    cout << "8. Get the graph in png format\n";
    cout << "9. Exit\n";

    cout
        << endl;
    cout << "Enter your choice: ";
}

vector<string> getWordsFromLine(const string &line)
{
    vector<string> words;
    stringstream ss(line);
    string word;
    while (ss >> word)
    {
        words.push_back(word);
    }
    return words;
}

template <class T>
void showOptions(Graph<T> &thegraph, int pchoice)
{

    int choice;
    T src, dest;
    int cost;
    int x;

    while (true)
    {

        showMenu();
        cin >> choice;

        switch (choice)
        {
        case 0:
            cout << "Okay done";
            break;
        case 1:
        {
            cout << endl;
            if (pchoice == 1)
            {
                string src = "Tshirt";
                string src1, src2, src3;
                thegraph.insert(src);
                ifstream file("processes.txt");

                // Check if file is opened successfully
                if (!file.is_open())
                {
                    cerr << "Unable to open file\n";
                    // return 1;
                }
                vector<string> srcarray;

                string line;
                int count = 1;
                while (getline(file, line))
                {
                    vector<string> array;
                    vector<string> words = getWordsFromLine(line);

                    // Print the words
                    for (const string &word : words)
                    {
                        // cout << word << "\n";
                        array.push_back(word);
                    }
                    // cout << "size - " << array.size() << "\n";
                    if (array.size() == 1)
                    {
                        thegraph.insert(array[0]);

                        // cout << "\nSIZE OF SOURCE ARRAY:" << srcarray.size() << "\n\n";
                        cost = 0;
                        // cout << "there\n";

                        thegraph.insertEdge(src, array[0], cost);
                        src = array[0];
                        // cout << "______" << src << "___----";

                        for (int j = 0; j < srcarray.size(); j++)
                        {
                            // cout << "pop" << srcarray[j] << " ";
                            thegraph.insertEdge(srcarray[j], array[0], cost);
                        }
                        srcarray.resize(0);
                    }
                    else
                    {
                        int j = 0;
                        for (int i = 0; i < array.size(); i++)
                        {

                            thegraph.insert(array[i]);

                            // cout << src << array[i] << "-" << array[i + 1] << "\n";
                            srcarray.push_back(array[i]);

                            thegraph.insertEdge(src, array[j], stoi(array[++i]));
                            // cout << "yes";
                            // cout << "\nPUSH INTO SORUCE\n\n";
                            j = j + 2;
                        }
                    }
                    // cout << "WHILE DONE" << endl;
                }

                file.close();
            }

            if (pchoice == 2)
            {
                cout << endl;
                string src = "Uthappam";
                thegraph.insert(src);
                ifstream file("process2.txt");

                // Check if file is opened successfully
                if (!file.is_open())
                {
                    cerr << "Unable to open file\n";
                    // return 1;
                }

                string line;
                int count = 1;
                while (getline(file, line))
                {
                    vector<string> array;
                    // Get words from the line
                    vector<string> words = getWordsFromLine(line);

                    // Print the words
                    for (const string &word : words)
                    {
                        array.push_back(word);
                    }
                    for (const string &a : array)
                    {
                        cout << count << ".";
                        cout << a;

                        cout << endl;
                        count++;
                    }
                    count = 1;
                    int n;
                    int cost;
                    cout << "Select the process :";
                    cin >> n;
                    if (n == 2)
                    {
                        cout << "Enter the cost :";
                        cin >> cost;
                        thegraph.insert(array[1]);
                        thegraph.insertEdge(src, array[1], cost);
                        src = array[1];
                    }
                    else if (n == 3)
                    {
                        cout << "Enter the cost :";
                        cin >> cost;
                        thegraph.insert(array[2]);
                        thegraph.insertEdge(src, array[2], cost);
                        src = array[2];
                    }
                    else if (n == 4)
                    {
                        cout << "Enter the cost :";
                        cin >> cost;
                        thegraph.insert(array[3]);
                        thegraph.insertEdge(src, array[3], cost);
                        src = array[3];
                    }
                    cout << endl;
                }

                file.close();
            }

            if (pchoice == 3)
            {
                cout << endl;
                cout << endl;
                string src = "Pallanguzhi_board";
                thegraph.insert(src);
                ifstream file("process3.txt");

                // Check if file is opened successfully
                if (!file.is_open())
                {
                    cerr << "Unable to open file\n";
                    // return 1;
                }

                string line;
                int count = 1;
                while (getline(file, line))
                {
                    vector<string> array;
                    // Get words from the line
                    vector<string> words = getWordsFromLine(line);

                    // Print the words
                    for (const string &word : words)
                    {
                        array.push_back(word);
                    }
                    for (const string &a : array)
                    {
                        cout << count << ".";
                        cout << a;

                        cout << endl;
                        count++;
                    }
                    count = 1;
                    int n;
                    int cost;
                    cout << "Select the process :";
                    cin >> n;
                    if (n == 2)
                    {
                        cout << "Enter the cost :";
                        cin >> cost;
                        thegraph.insert(array[1]);
                        thegraph.insertEdge(src, array[1], cost);
                        src = array[1];
                    }
                    else if (n == 3)
                    {
                        cout << "Enter the cost :";
                        cin >> cost;
                        thegraph.insert(array[2]);
                        thegraph.insertEdge(src, array[2], cost);
                        src = array[2];
                    }
                    else if (n == 4)
                    {
                        cout << "Enter the cost :";
                        cin >> cost;
                        thegraph.insert(array[3]);
                        thegraph.insertEdge(src, array[3], cost);
                        src = array[3];
                    }
                    cout << endl;
                }

                file.close();
            }
            break;
        }
        case 2:
        {
            cout << endl;
            if (pchoice == 1)
            {
                string src = "Tshirt";
                thegraph.insert(src);
                ifstream file("process1.txt");

                // Check if file is opened successfully
                if (!file.is_open())
                {
                    cerr << "Unable to open file\n";
                    // return 1;
                }

                string line;
                int count = 1;
                while (getline(file, line))
                {
                    vector<string> array;
                    // Get words from the line
                    vector<string> words = getWordsFromLine(line);

                    // Print the words
                    for (const string &word : words)
                    {
                        array.push_back(word);
                    }
                    for (const string &a : array)
                    {
                        cout << count << ".";
                        cout << a;

                        cout << endl;
                        count++;
                    }
                    count = 1;
                    int n;
                    int cost;
                    cout << "Select the process :";
                    cin >> n;
                    if (n == 2)
                    {
                        cout << "Enter the cost :";
                        cin >> cost;
                        thegraph.insert(array[1]);
                        thegraph.insertEdge(src, array[1], cost);
                        src = array[1];
                    }
                    else if (n == 3)
                    {
                        cout << "Enter the cost :";
                        cin >> cost;
                        thegraph.insert(array[2]);
                        thegraph.insertEdge(src, array[2], cost);
                        src = array[2];
                    }
                    else if (n == 4)
                    {
                        cout << "Enter the cost :";
                        cin >> cost;
                        thegraph.insert(array[3]);
                        thegraph.insertEdge(src, array[3], cost);
                        src = array[3];
                    }
                    cout << endl;
                }

                file.close();
            }

            if (pchoice == 2)
            {
                cout << endl;
                string src = "Uthappam";
                thegraph.insert(src);
                ifstream file("process2.txt");

                // Check if file is opened successfully
                if (!file.is_open())
                {
                    cerr << "Unable to open file\n";
                    // return 1;
                }

                string line;
                int count = 1;
                while (getline(file, line))
                {
                    vector<string> array;
                    // Get words from the line
                    vector<string> words = getWordsFromLine(line);

                    // Print the words
                    for (const string &word : words)
                    {
                        array.push_back(word);
                    }
                    for (const string &a : array)
                    {
                        cout << count << ".";
                        cout << a;

                        cout << endl;
                        count++;
                    }
                    count = 1;
                    int n;
                    int cost;
                    cout << "Select the process :";
                    cin >> n;
                    if (n == 2)
                    {
                        cout << "Enter the cost :";
                        cin >> cost;
                        thegraph.insert(array[1]);
                        thegraph.insertEdge(src, array[1], cost);
                        src = array[1];
                    }
                    else if (n == 3)
                    {
                        cout << "Enter the cost :";
                        cin >> cost;
                        thegraph.insert(array[2]);
                        thegraph.insertEdge(src, array[2], cost);
                        src = array[2];
                    }
                    else if (n == 4)
                    {
                        cout << "Enter the cost :";
                        cin >> cost;
                        thegraph.insert(array[3]);
                        thegraph.insertEdge(src, array[3], cost);
                        src = array[3];
                    }
                    cout << endl;
                }

                file.close();
            }

            if (pchoice == 3)
            {
                cout << endl;
                string src = "Pallanguzhi_board";
                thegraph.insert(src);
                ifstream file("process3.txt");

                // Check if file is opened successfully
                if (!file.is_open())
                {
                    cerr << "Unable to open file\n";
                    // return 1;
                }

                string line;
                int count = 1;
                while (getline(file, line))
                {
                    vector<string> array;
                    // Get words from the line
                    vector<string> words = getWordsFromLine(line);

                    // Print the words
                    for (const string &word : words)
                    {
                        array.push_back(word);
                    }
                    for (const string &a : array)
                    {
                        cout << count << ".";
                        cout << a;

                        cout << endl;
                        count++;
                    }
                    count = 1;
                    int n;
                    int cost;
                    cout << "Select the process :";
                    cin >> n;
                    if (n == 2)
                    {
                        cout << "Enter the cost :";
                        cin >> cost;
                        thegraph.insert(array[1]);
                        thegraph.insertEdge(src, array[1], cost);
                        src = array[1];
                    }
                    else if (n == 3)
                    {
                        cout << "Enter the cost :";
                        cin >> cost;
                        thegraph.insert(array[2]);
                        thegraph.insertEdge(src, array[2], cost);
                        src = array[2];
                    }
                    else if (n == 4)
                    {
                        cout << "Enter the cost :";
                        cin >> cost;
                        thegraph.insert(array[3]);
                        thegraph.insertEdge(src, array[3], cost);
                        src = array[3];
                    }
                    cout << endl;
                }

                file.close();
            }
            break;

            break;
        }
        case 3:
        {
            cout << endl;
            cout << "Enter source and dest: ";
            cin >> src >> dest;
            thegraph.calculateShortestPath(src, dest);
            break;
        }
        case 4:
        {
            cout << endl;
            cout << "Enter starting source: ";
            cin >> src;
            thegraph.traversePath(src);
            break;
        }
        case 5:
        {
            cout << endl;
            thegraph.displayIndegree();
            break;
        }
        case 6:
        {
            cout << endl;
            thegraph.displayOutdegree();
            break;
        }
        case 7:
        {
            cout << endl;
            cout << "Enter source and dest: ";
            cin >> src >> dest;
            thegraph.displayAllPaths(src, dest);
            break;
        }
        case 8:
        {
            cout << endl;
            cout << "All Topological Sorts:\n";
            thegraph.allTopologicalSort(); // works wrongly please ignore
            break;
        }
        case 9:
        {
            cout << endl;
            cout << "Enter source and dest: ";
            cin >> src >> dest;
            thegraph.longestPath(src, dest); // want to change sometin not working properly
            break;
        }
        case 10:
            cout << endl;
            cout << "Enter the source and destination :";
            cin >> src >> dest;
            thegraph.graphviz(src, dest);
            system(file.c_str());
            break;
        case 11:
            return;
        default:
            cout << "Invalid choice!\n";
        }
    }
}

int main()
{

    int pchoice;

    vector<string> products = {"Tshirt", "Uttappam", "Pallanguzhi_Board"};

    cout << "Select a product:\n";
    for (int i = 0; i < products.size(); ++i)
    {
        cout << i + 1 << ". " << products[i] << "\n";
    }
    cout << endl;
    cout << "Enter your choice: ";
    cin >> pchoice;

    if (pchoice < 1 || pchoice > products.size())
    {
        cout << "Invalid choice!\n";
        return 0;
    }
    cout << endl;
    cout << "Selected product: " << products[pchoice - 1] << "\n";
    cout << endl;
    switch (pchoice)
    {
    case 1:
    {
        Graph<string> shirt;
        showOptions(shirt, pchoice);
        break;
    }
    case 2:
    {
        Graph<string> food;
        showOptions(food, pchoice);
        break;
    }
    case 3:
    {
        Graph<string> board;
        showOptions(board, pchoice);
        break;
    }
    default:
        cout << "Invalid choice!\n";
    }

    return 0;
}
