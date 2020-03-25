#include <list>
#include<iostream>
#include <algorithm>
#include "Graphs.h"

using namespace std;

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

void Graph::add_edge(int v, int w)
{
	adj[v].push_back(w);
	adj[w].push_back(v);  
}

/* Рекурсивная функция, которая находит все мосты используя обход в глубину
 u - следующая вершина
 visited[] - список посещенных вершин 
 disc[] - хранит время открытия посещенных вершин 
 parent[] - хранит предков в дереве поиска в глубину */ 

void Graph::bridge_rec(int u, bool visited[], int discovered[], int low[], int parent[])
{
	static int time = 0;

	// Текущая вершина отмечается как посещенная 
	visited[u] = true;

	discovered[u] = low[u] = ++time;

	list<int>::iterator i;
	for (i = adj[u].begin(); i != adj[u].end(); i++ )
	{
		int v = *i; 

		if (!visited[v])
		{
			//Отмечается, что вершина u соединена с v
			parent[v] = u;
			
			//Рекурсивный вызов функции, чтобы посетить v
			bridge_rec(v, visited, discovered, low, parent);

			//Обновление параметра low
			low[u] = min(low[u], low[v]);

			//Проверка моста между u и v
			if (low[v] > discovered[u])
				cout << u << " " << v << endl;
		}
		//Если смежная вершина уже посещена, проверяется, раньше ли она был посещена чем предыдущая
		// и обновляется параметр low
		else if (v != parent[u])
			low[u] = min(low[u], discovered[v]);
	}
}

void Graph::bridge()
{
	// Все вершины отмечаются как непосещенные 
	bool* visited = new bool[V];
	int* disc = new int[V];
	int* low = new int[V];
	int* parent = new int[V];

	// Инициализация  
	for (int i = 0; i < V; i++)
	{
		parent[i] = -1;
		visited[i] = false;
	}

	for (int i = 0; i < V; i++)
		if (visited[i] == false)
			bridge_rec(i, visited, disc, low, parent);
}