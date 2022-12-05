#pragma once
#include <cstdlib>
#include <vector>
#include <queue>
#include <map>

typedef struct adjListNode adjListNode;
typedef struct adjList adjList;

adjListNode* newAdjListNode(int x, int y, int weight);
adjList* newAdjList(int x, int y);
void setAdjs(int m[10][10], adjList* l);

class Dijkstra
{
private:
    
    static void setPq(std::priority_queue<std::vector<int>, 
                                          std::vector<std::vector<int>>,
                                          std::greater<std::vector<int>>> *minHeap, 
                      adjList* l, 
                      std::map<int, std::pair<int, int>> w);
public:

    Dijkstra(/* args */);
    ~Dijkstra();

    static int run(std::vector<adjList*> graph, int src, int dest);
};