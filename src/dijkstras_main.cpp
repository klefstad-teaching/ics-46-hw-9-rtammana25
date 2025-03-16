#include "dijkstras.h"

using namespace std;

int main() {
    Graph G;

    file_to_graph("src/small.txt", G);

    vector<int> previous(G.numVertices, -1);
    vector<int> distance = dijkstra_shortest_path(G, 0, previous);

    for (int destination = 0; destination < G.numVertices; ++destination) {
        vector<int> shortestPath = extract_shortest_path(distance, previous, destination);
        print_path(shortestPath, distance[destination]);
    }

    return 0;
}