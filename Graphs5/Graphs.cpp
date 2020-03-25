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

/* ����������� �������, ������� ������� ��� ����� ��������� ����� � �������
 u - ��������� �������
 visited[] - ������ ���������� ������ 
 disc[] - ������ ����� �������� ���������� ������ 
 parent[] - ������ ������� � ������ ������ � ������� */ 

void Graph::bridge_rec(int u, bool visited[], int discovered[], int low[], int parent[])
{
	static int time = 0;

	// ������� ������� ���������� ��� ���������� 
	visited[u] = true;

	discovered[u] = low[u] = ++time;

	list<int>::iterator i;
	for (i = adj[u].begin(); i != adj[u].end(); i++ )
	{
		int v = *i; 

		if (!visited[v])
		{
			//����������, ��� ������� u ��������� � v
			parent[v] = u;
			
			//����������� ����� �������, ����� �������� v
			bridge_rec(v, visited, discovered, low, parent);

			//���������� ��������� low
			low[u] = min(low[u], low[v]);

			//�������� ����� ����� u � v
			if (low[v] > discovered[u])
				cout << u << " " << v << endl;
		}
		//���� ������� ������� ��� ��������, �����������, ������ �� ��� ��� �������� ��� ����������
		// � ����������� �������� low
		else if (v != parent[u])
			low[u] = min(low[u], discovered[v]);
	}
}

void Graph::bridge()
{
	// ��� ������� ���������� ��� ������������ 
	bool* visited = new bool[V];
	int* disc = new int[V];
	int* low = new int[V];
	int* parent = new int[V];

	// �������������  
	for (int i = 0; i < V; i++)
	{
		parent[i] = -1;
		visited[i] = false;
	}

	for (int i = 0; i < V; i++)
		if (visited[i] == false)
			bridge_rec(i, visited, disc, low, parent);
}