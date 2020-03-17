#include"Graph.h"
Graph::Graph() {
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j <30; j++) {
			vertex[i][j] = -1;
		}
	}
}
void Graph::AddEdge(int from, int dest, double weight)
{
	vertex[from][dest] = weight;
}
void Graph::RemoveEdge(int from, int dest) {
	vertex[from][dest] = -1;
}
