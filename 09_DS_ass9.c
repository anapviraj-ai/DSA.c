
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

// Structure for adjacency list node
struct Node {
    int dest;
    int cost;
    struct Node *next;
};

// Array of city names
char cities[MAX][50];

// Array of adjacency list pointers
struct Node *adjList[MAX];

int visited[MAX];
int n;

// Function to find city index
int findCity(char name[]) {
    int i;

    for (i = 0; i < n; i++) {
        if (strcmp(cities[i], name) == 0)
            return i;
    }

    return -1;
}

// Function to add an edge
void addEdge(int src, int dest, int cost) {
    struct Node *newNode;

    // Add destination to source list
    newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->dest = dest;
    newNode->cost = cost;
    newNode->next = adjList[src];
    adjList[src] = newNode;

    // Add source to destination list
    // Because the graph is undirected
    newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->dest = src;
    newNode->cost = cost;
    newNode->next = adjList[dest];
    adjList[dest] = newNode;
}

// DFS traversal
void DFS(int cityIndex) {
    struct Node *temp;

    visited[cityIndex] = 1;

    temp = adjList[cityIndex];

    while (temp != NULL) {
        if (visited[temp->dest] == 0) {
            DFS(temp->dest);
        }

        temp = temp->next;
    }
}

// Function to check connectivity
void isGraphConnected() {
    int i;

    // Initialize visited array
    for (i = 0; i < n; i++) {
        visited[i] = 0;
    }

    // Start DFS from first city
    DFS(0);

    // Check whether all cities are visited
    for (i = 0; i < n; i++) {
        if (visited[i] == 0) {
            printf("\nGraph is NOT connected.\n");
            return;
        }
    }

    printf("\nGraph is connected.\n");
}

// Function to display graph
void displayGraph() {
    int i;
    struct Node *temp;

    printf("\nFlight Graph (Adjacency List):\n");

    for (i = 0; i < n; i++) {
        printf("%s -> ", cities[i]);

        temp = adjList[i];

        while (temp != NULL) {
            printf("%s(%d) -> ",
                   cities[temp->dest], temp->cost);

            temp = temp->next;
        }

        printf("NULL\n");
    }
}

// Main function
int main() {
    int i, edges, cost;
    char srcName[50], destName[50];
    int src, dest;

    // Initialize adjacency list
    for (i = 0; i < MAX; i++) {
        adjList[i] = NULL;
    }

    printf("Enter number of cities: ");
    scanf("%d", &n);

    // Input city names
    for (i = 0; i < n; i++) {
        printf("Enter city %d name: ", i + 1);
        scanf("%49s", cities[i]);
    }

    // Input number of flights
    printf("\nEnter number of flights: ");
    scanf("%d", &edges);

    // Input flight details
    for (i = 0; i < edges; i++) {
        printf("\nEnter source city: ");
        scanf("%49s", srcName);

        printf("Enter destination city: ");
        scanf("%49s", destName);

        printf("Enter flight cost: ");
        scanf("%d", &cost);

        src = findCity(srcName);
        dest = findCity(destName);

        if (src == -1 || dest == -1) {
            printf("Invalid city name! Try again.\n");
            i--;
            continue;
        }

        addEdge(src, dest, cost);
    }

    // Display graph
    displayGraph();

    // Check connectivity
    isGraphConnected();

    return 0;
}
