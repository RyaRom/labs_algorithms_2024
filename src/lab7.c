#include <stdio.h>
#include <stdbool.h>

#define MAX_STUDENTS 100
#define MAX_EDGES 1000

typedef struct {
    int from, to;
} Edge;

typedef struct {
    int students;
    int connections;
    int vertices[MAX_STUDENTS];
    Edge edges[MAX_EDGES];
} Graph;

void initGraph(Graph *graph, int n) {
    graph->students = n;
    graph->connections = 0;
    for (int i = 0; i < n; i++) {
        graph->vertices[i] = i;
    }
}

void addEdge(Graph *graph, int u, int v) {
    graph->edges[graph->connections].from = u;
    graph->edges[graph->connections].to = v;
    graph->connections++;
}

bool canAddToSet(Graph *graph, int node, bool *inSet) {
    for (int i = 0; i < graph->connections; i++) {
        if (graph->edges[i].from == node && inSet[graph->edges[i].to]) {
            return false;
        }
        if (graph->edges[i].to == node && inSet[graph->edges[i].from]) {
            return false;
        }
    }
    return true;
}

int findIndependentSet(Graph *graph, bool *visited, bool *inSet, int maxTeamSize, int *currentTeamSize) {
    int count = 0;
    for (int i = 0; i < graph->students; i++) {
        if (!visited[i] && canAddToSet(graph, i, inSet)) {
            if (*currentTeamSize < maxTeamSize) {
                inSet[i] = true;
                visited[i] = true;
                (*currentTeamSize)++;
                count++;
            }
        }
    }
    return count;
}

int findMinimumTeams(Graph *graph, int maxTeamSize) {
    bool visited[MAX_STUDENTS] = {0};
    int teams = 0;

    while (1) {
        bool inSet[MAX_STUDENTS] = {0};
        int currentTeamSize = 0;
        int count = findIndependentSet(graph, visited, inSet, maxTeamSize, &currentTeamSize);
        if (count == 0) {
            break;
        }
        teams++;
    }

    return teams;
}

bool canDivideIntoTeams(Graph *graph, int teams_count) {
    int n = graph->students;
    if (n < teams_count) {
        return false;
    }

    int maxTeamSize = (n + teams_count + 1) / teams_count;
    int teams = findMinimumTeams(graph, maxTeamSize);
    return teams <= teams_count;
}

void lab7() {
    int n = 6;
    int m = 3;

    Graph graph;
    initGraph(&graph, n);

    addEdge(&graph, 0, 1);
    addEdge(&graph, 1, 2);
    addEdge(&graph, 2, 3);
    addEdge(&graph, 3, 4);
    addEdge(&graph, 4, 5);

    int maxTeamSize = (n + m + 1) / m;
    int minTeams = findMinimumTeams(&graph, maxTeamSize);
    printf("Minimum number of teams: %d\n", minTeams);

    if (canDivideIntoTeams(&graph, m)) {
        printf("It is possible to divide into %d teams.\n", m);
    } else {
        printf("It is not possible to divide into %d teams.\n", m);
    }
}
