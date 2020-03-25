#pragma once
#include <list>
#include<iostream>

using namespace std;

class Graph
{
	int V; 
	list<int>* adj; 
	void bridge_rec(int v, bool visited[], int discovered[], int low[], int parent[]);
public:
	Graph(int V); 
	void add_edge(int v, int w);  
	void bridge(); 
};
