#include <stdio.h>
#include <stdbool.h>

#define MAX_NODES 10
#define INFINITY 999

// Function to perform the Distance Vector Routing algorithm
void distanceVectorRouting(int costMatrix[MAX_NODES][MAX_NODES], int numNodes) {
    int distance[MAX_NODES];
    int nextHop[MAX_NODES];
    bool updated;
    
    // Initialize distance and nextHop arrays
    for (int i = 0; i < numNodes; i++) {
        distance[i] = INFINITY;
        nextHop[i] = -1;
    }
    
    // Update distance array with initial cost matrix values
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            if (costMatrix[i][j] < INFINITY) {
                distance[i] = costMatrix[i][j];
                nextHop[i] = j;
            }
        }
    }
    
    // Perform distance vector routing algorithm
    do {
        updated = false;
        
        for (int i = 0; i < numNodes; i++) {
            for (int j = 0; j < numNodes; j++) {
                if (i != j && costMatrix[i][j] + distance[j] < distance[i]) {
                    distance[i] = costMatrix[i][j] + distance[j];
                    nextHop[i] = j;
                    updated = true;
                }
            }
        }
    } while (updated);
    
    // Print the routing table
    printf("Routing Table:\n");
    printf("Node\tDistance\tNext Hop\n");
    for (int i = 0; i < numNodes; i++) {
        printf("%d\t%d\t\t%d\n", i, distance[i], nextHop[i]);
    }
}

int main() {
    int costMatrix[MAX_NODES][MAX_NODES];
    int numNodes;
    
    printf("Enter the number of nodes: ");
    scanf("%d", &numNodes);
    
    printf("Enter the cost matrix:\n");
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            scanf("%d", &costMatrix[i][j]);
        }
    }
    
    distanceVectorRouting(costMatrix, numNodes);
    
    return 0;
}

