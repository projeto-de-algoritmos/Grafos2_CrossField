#pragma once
#include <Dijkstra.h>
#include <ctime>

class Solution {
private:
    std::vector<adjList*> graph;
    solution* sol;
    
    void generateRandomMatrix();
    void generateGraph();
public:
    Solution();
    ~Solution();

    int gameMatrix[10][10];

    int** getGameMatrix();
    int getSolution();
    void newGame();
    std::vector<int> getPath();

};
