#include "dijkstras.h"
#include <algorithm>

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;

    vector<int> distance(n, INF);
    previous.assign(n, -1);
    vector<int> visited(n, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});
    distance[source] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u])
            continue;

        visited[u] = true;

        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;

            if (!visited[v] && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push({distance[v], v});
            }
        }
    }

    return distance;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> shortestPath;

    for (int curr = destination; curr != -1; curr = previous[curr])
        shortestPath.push_back(curr);

    std::reverse(shortestPath.begin(), shortestPath.end());
    return shortestPath;
}

void print_path(const vector<int>& v, int total) {
    if (v.empty()) {
        std::cout << "No Path!" << std::endl;
        return;
    }

    for (int vertex : v)
        std::cout << vertex << " ";

    std::cout << std::endl;
    std::cout << "Total cost is " << total << std::endl;
}
