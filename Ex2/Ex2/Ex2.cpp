#include <iostream>
#include <fstream>
#include <vector>

#define MAX_INT 1000000000

using namespace std;

ofstream fout("out.txt");

vector<int> K;
vector<int> parents;
int n;

int getLowestNodNotInVector(vector<int> vector)
{
	int x = 0;
	while (true)
	{
		if (find(vector.begin(), vector.end(), x) == vector.end())
			return x;
		x++;
	}
}

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		cout << "Nu a fost dat un fisier de intrare sau de iesire.\n";
		return -1;
	}

	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	fin >> n;
	int nod;
	
	for (int i = 0; i < n; i++)
	{
		fin >> nod;
		K.push_back(nod);
	}

	for(int i = 0; i <=n; i++)
		parents.push_back(-1);

	int firstNod, lowestNod = 0;

	for (int i = 1; i <= n; i++)
	{
		firstNod = K.front();
		lowestNod = getLowestNodNotInVector(K);

		cout << lowestNod << endl;

		K.push_back(lowestNod);
		K.erase(K.begin());
		parents[lowestNod] = firstNod;
	}

	fout << n + 1 << endl;
	for (int i = 0; i <= n; i++)
	{
		fout << parents[i] << " ";
	}


	return 0;
}