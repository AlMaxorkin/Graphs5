 #include<iostream> 
#include "Graphs.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	int	vertex, edge, u, v;

	cout << "������� ����� ������: ";
	cin >> edge;
	cout << "������� ����� �����: ";
	cin >> vertex;

	Graph g(edge);

	for (int i = 0; i < vertex; i++)
	{
		cout << "������� ������� (������ ������� ���������� ��� 0) : " << endl;
		cin >> u >> v;
		cout << endl;
		g.add_edge(u, v);
	}

	g.bridge();

	return 0;
}
