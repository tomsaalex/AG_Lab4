#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


vector<int> generateParentFrequency(vector<int> p)
{
	vector<int> parentFrequency;

	for (int i = 0; i < p.size(); i++)
	{
		parentFrequency.push_back(0);
	}

	for (int i = 0; i < p.size(); i++)
	{
		if (p[i] != -1 && p[i] != -3)
			parentFrequency[p[i]]++;
	}

	return parentFrequency;
}

int findMinimumIndexLeaf(vector<int> parentFrequency, vector<int> parents)
{
	for (int i = 0; i < parentFrequency.size(); i++)
	{
		if (parentFrequency[i] == 0 && parents[i] != -3)
		{
			return i;
		}
	}
}

int main(int argc, char* argv[])
{
	if (argc <= 2)
	{
		cout << "Trebuie sa introduci un fisier de input si unul de output";
		return -1;
	}
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);

	int n;

	fin >> n;

	vector<int> parents;
	for (int i = 1; i <= n; i++)
	{
		parents.push_back(-2);
	}
	
	int i = 0, x;
	while (fin >> x)
	{
		parents[i++] = x;
	}

	
	vector<int> prufer;
	int copyN = n;
	while (copyN > 1)
	{
		vector<int> parentFrequency = generateParentFrequency(parents);
		int v = findMinimumIndexLeaf(parentFrequency, parents);
		int k = parents[v];
		prufer.push_back(k);
		parents[v] = -3;
		copyN--;
	}
	fout << prufer.size() << endl;
	for (int i = 0; i < prufer.size(); i++)
		fout << prufer[i] << ' ';

}