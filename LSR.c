#include <stdio.h>
#include <limits.h>

int main() {
    int H;
    printf("LINK STATE ROUTING PROTOCOL:\nEnter the number of hops: ");
    scanf("%d", &H);

    int adj[50][50];
    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < H; i++)
        for (int j = 0; j < H; j++)
            scanf("%d", &adj[i][j]);

    int dist[H], visited[H];
    for (int i = 0; i < H; i++) {
        dist[i] = INT_MAX;  // Initialize distances as infinity
        visited[i] = 0;     // Mark all nodes as unvisited
    }
    dist[0] = 0;  // Distance to source is 0

    // Main loop to find shortest paths
    for (int round = 0; round < H - 1; round++) {
        int u = -1, min = INT_MAX;

        // Find the closest unvisited node
        for (int v = 0; v < H; v++)
            if (!visited[v] && dist[v] < min) {
                min = dist[v];
                u = v;
            }

        if (u == -1) break;  // All remaining nodes are unreachable
        visited[u] = 1;

        // Update distances to adjacent nodes
        for (int v = 0; v < H; v++)
            if (!visited[v] && adj[u][v] && dist[u] + adj[u][v] < dist[v])
                dist[v] = dist[u] + adj[u][v];
    }

    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < H; i++)
        printf("%d\t\t%d\n", i, dist[i]);

    return 0;
}
