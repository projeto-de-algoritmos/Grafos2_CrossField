#include <Dijkstra.h>

typedef struct adjListNode
{
    std::pair <int, int> cords;
    int node, weight;
    struct adjListNode* next;
    
}adjListNode;

typedef struct adjList
{
    std::pair <int, int> cords;
    int node;
    adjListNode* head;
    bool visited;
}adjList;

adjListNode* newAdjListNode(int x, int y, int weight)
{
    adjListNode* newNode = (adjListNode*) malloc(sizeof(adjListNode));
    newNode->weight = weight;
    newNode->cords = std::make_pair(x, y);
    newNode->node = x*10+y;
    newNode->next = NULL;
    return newNode;
}

adjList* newAdjList(int x, int y){
    adjList* newList = (adjList*) malloc(sizeof(adjList));
    newList->cords = std::make_pair(x, y);
    newList->node = x*10+y;
    newList->head = NULL;
    newList->visited = false;
    return newList;
}

void setAdjs(int m[10][10], adjList* l){
    int x = l->cords.first, y=l->cords.second;

    if(x-1 >= 0) {
        adjListNode* node = newAdjListNode(x-1, y, m[x-1][y]);
        node->next = l->head;
        l->head = node;
    }

    if(x+1 < 10) {
        adjListNode* node = newAdjListNode(x+1, y, m[x+1][y]);
        node->next = l->head;
        l->head = node;
    }

    if(y-1 >= 0) {
        adjListNode* node = newAdjListNode(x, y-1, m[x][y-1]);
        node->next = l->head;
        l->head = node;
    }

    if(y+1 < 10) {
        adjListNode* node = newAdjListNode(x, y+1, m[x][y+1]);
        node->next = l->head;
        l->head = node;
    }
}

solution* Dijkstra::run(std::vector<adjList*> graph, int src, int dest){
    std::map<int, std::pair<int, int>> weightSet;
    
    std::priority_queue<std::vector<int>, 
                        std::vector<std::vector<int>>,
                        std::greater<std::vector<int>>> minHeap;

    weightSet[src] = std::make_pair(0, src);
        
    setPq(&minHeap, graph[src], weightSet);

    while (!minHeap.empty())
    {   
        int n = minHeap.top()[2];
        if(!graph[n]->visited){
            std::pair<int, int> p = std::make_pair(minHeap.top()[0], minHeap.top()[1]);
            weightSet[n] = p;
            setPq(&minHeap, graph[n], weightSet);
        }
        minHeap.pop();
    }

    solution *sol = (solution*) std::malloc(sizeof(solution));

    sol->path.push_back(dest);
    int t = weightSet[dest].second;
    while (t)
    {
        sol->path.push_back(t);
        t=weightSet[t].second;
    }
    sol->path.push_back(t);
    sol->amount = weightSet[dest].first;
return sol;
}

void Dijkstra::setPq(std::priority_queue<std::vector<int>, 
                                    std::vector<std::vector<int>>,
                                    std::greater<std::vector<int>>> *minHeap, 
                     adjList* l, 
                     std::map<int, std::pair<int, int>> w)
{
    adjListNode *node = l->head;
    l->visited = true;
    
    while (node)
    {
        std::vector<int> v;
        int wt = w[l->node].first;
        v.push_back(node->weight + wt);
        v.push_back(l->node);
        v.push_back(node->node);
        minHeap->push(v);       
        node = node->next;
    }  
}