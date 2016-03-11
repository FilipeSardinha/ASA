#include<vector>
#include<iostream>

 
#define MAX_NODES 10000
#define INF 2147483646  // represents infity
#define UNINITIALIZED -1 // value for node with no parent
#define MAX_CRITICAL 1000
 using namespace std;
 int ** capacities;
int ** capacitiescopy;
// shows how much flow has passed through an edge 
int ** flowPassed;
int * vectorCriticos;
int * vectorResults;
int * vectorFinal;
int contador = 0;
int empty = 0;
int queue[MAX_NODES];
// represents the graph. The graph must contain the negative edges too!
vector<int> graph[MAX_NODES];
vector<int> graphcopy[MAX_NODES];
// shows the parents of the nodes of the path built by the BFS   
int parentsList[MAX_NODES];       
// shows the maximum flow to a node in the path built by the BFS
int currentPathCapacity[MAX_NODES];
int criticalVector[MAX_CRITICAL];  
int min(int a , int b);

void initmatrix(int number_nodes){

	capacities = new int*[number_nodes]; 
	for (int i = 0; i < number_nodes; i++) 
	capacities[i] = new int[number_nodes]; 
	capacitiescopy = new int*[number_nodes]; 
	for (int i = 0; i < number_nodes; i++) 
	capacitiescopy[i] = new int[number_nodes];
	flowPassed = new int*[number_nodes]; 
	for (int i = 0; i < number_nodes; i++) 
	flowPassed[i] = new int[number_nodes];
} 


int push( int n){
	queue[contador] = n;
	contador++;
	empty++;
	return 1;
}

int pop(){
	int result;
	result = queue[contador];
	contador--;
	empty--;
	return result;
}

int front(){
	if(contador != 0){
		//cout<<queue[contador-1]<<endl;
		return queue[contador-1];
	}
	else
		return -1;
}

void initstack(){
	for(int i = 0; i < MAX_NODES; i++)
	{
		queue[i] = -1;
	}
}

int bfs(int startNode, int endNode)
{
	for(int i = 0; i < MAX_NODES; i++)
	{
		parentsList[i] = UNINITIALIZED;
		currentPathCapacity[i] = 0;
	}
	push(startNode);
	parentsList[startNode]=-2;
	currentPathCapacity[startNode]=INF;
	while(empty != 0)
	{
		int currentNode = front(); pop();
		for(unsigned int i=0; i<graph[currentNode].size(); i++)
		{
			int to = graph[currentNode][i];
			if(parentsList[to] == UNINITIALIZED)
			{
				if(capacities[currentNode][to] - flowPassed[currentNode][to] > 0)
				{
				// we update the parent of the future node to be the current node
					parentsList[to] = currentNode;
					// we check which is the minimum residual edge capacity so far
					currentPathCapacity[to] = min(currentPathCapacity[currentNode], 
						capacities[currentNode][to] - flowPassed[currentNode][to]);
						// if we have reached the end node the bfs should terminate
					if(to == endNode) return currentPathCapacity[endNode];
					// we add our future node to the queue
					push(to);
				}
			}
		}
	}
	return 0;
} 
int edmondsKarp(int startNode, int endNode,int numberofmynodes)
{
	int maxFlow=0;
	int cuts = 0 ;
	while(true)
	{
	// we find an augmented path and the maximum flow corresponding to it
		int flow=bfs(startNode, endNode);
		// if we can't find anymore paths the flow will be 0
		if(flow==0) 
		{
			break;
		}
		cuts++;
		maxFlow +=flow;
		int currentNode=endNode;
		// we update the passed flow matrix
		while(currentNode != startNode)
		{
			int previousNode = parentsList[currentNode];
			flowPassed[previousNode][currentNode] += flow;
			flowPassed[currentNode][previousNode] -= flow;
			currentNode=previousNode;
		}
	}
	for ( int j = 0 ; j < numberofmynodes ; j++)
	{
		for ( int k = 0 ; k < numberofmynodes ; k++)
		{
			flowPassed[j][k]=0;
		}
	}
	return cuts;
}

int copyMatrix(int n)
{
	int i,j;
	for(i = 0 ; i < n ; i++)
	{
		for(j = 0 ; j < n ; j++)
		{
		
				capacities[i][j] = capacitiescopy[i][j];

		}
	}
	return 0;
}

int copyVector(int n)
{
	int i ;
	for ( i = 0 ; i < n ; i++)
	{
			graph[i] = graphcopy[i];
	}
	return 0;
}

int min(int a , int b)
{
	if ( a > b)
	{
		return b;
	}
	else 
	{
		return a;
	}
}



int main(int argc, char * argv[])
{
	initstack();
	int nodesCount, edgesCount,numberproblems,numberofcritics,crit;
	int mincut = INF ;
	cin>>nodesCount>>edgesCount;
	initmatrix(nodesCount);

	for(int edge=0; edge<edgesCount; edge++)
	{
	int from, to ;
	cin>>from>>to;;
	capacities[from][to]=1;
	capacities[to][from]=1;
	capacitiescopy[from][to]=1;
	capacitiescopy[to][from]=1;
	graph[from].push_back(to);
	graphcopy[from].push_back(to);
	//adding the negative edge
	graph[to].push_back(from);
	graphcopy[to].push_back(from);
}
	cin>>numberproblems;
	for ( int i = 0 ; i<numberproblems;i++)
	{
		cin>>numberofcritics;
		vectorCriticos = new int [numberofcritics];
		for(int t = 0; t < numberofcritics; t++)
		{
			cin>>crit;
			vectorCriticos[t] = crit;
		}
		for (int h = 1; h < numberofcritics ; h++)
		{
				{
					mincut = min(mincut, edmondsKarp(vectorCriticos[0],vectorCriticos[h],nodesCount));
					copyMatrix(nodesCount);
					copyVector(nodesCount);
				}
		}
		cout<<mincut<<endl;
		mincut = INF;
		//result =vectorMin(factorial(numberofcritics-1));
		
		//int source, sink;
		//cin>>source>>sink;
		//int maxFlow = edmondsKarp(source, sink); 
		//cout<<maxFlow<<endl;
		//cin>>source>>sink;
		//copyMatrix();
		//copyVector();

		//int max2 = edmondsKarp(source,sink);
		//cout<<max2<<endl;
	}
	return 0;
}