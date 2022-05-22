#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <queue>
#include <set>

using namespace std;

#define MAX_NUM 1000000000;

struct Nod {
	int fr;
	char data;
	char minASCII;
	Nod* st;
	Nod* dr;
};

Nod* getMinNode(vector<Nod*>& nodesVector)
{
	int minFr = MAX_NUM;
	Nod* candidate = new Nod;
	auto iteratorToDelete = nodesVector.end();

	int i = 0;

	for (auto& n : nodesVector)
	{
		if (n->fr < minFr)
		{
			minFr = n->fr;
			candidate = n;
			iteratorToDelete = nodesVector.begin() + i;
		}
		if (n->fr == minFr)
		{
			if (n->minASCII < candidate->minASCII)
			{
				candidate = n;
				iteratorToDelete = nodesVector.begin() + i;
			}
		}
		i++;
	}
	
	nodesVector.erase(iteratorToDelete);
	return candidate;
}

void insertAtProperPlace(vector<Nod*>& nodesVector, Nod* newNode)
{
	for (int i = 0; i < nodesVector.size(); i++)
	{
		if (nodesVector.at(i)->fr > newNode->fr)
		{
			nodesVector.insert(nodesVector.begin() + i, newNode);
			return;
		}
	}

	nodesVector.push_back(newNode);
}

string parseTree(Nod* currentNode, string lastDecision, char searchedElem)
{
	if (currentNode->data == searchedElem)
	{
		return lastDecision;
	}
	else if (currentNode->st == NULL && currentNode->dr == NULL)
	{
		return string("NOT FOUND");
	}
	string foundString;
	if (currentNode->st != NULL)
	{
		foundString = parseTree(currentNode->st, string("0"), searchedElem);
		if (foundString != "NOT FOUND")
			return lastDecision + foundString;
	}
	if (currentNode->dr != NULL)
	{
		foundString = parseTree(currentNode->dr, string("1"), searchedElem);
		if (foundString != "NOT FOUND")
			return lastDecision + foundString;
	}

	return string("NOT FOUND");

}

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		cout << "Nu a fost dat un fisier de intrare sau de iesire\n";
		return -1;
	}


	ifstream fin(argv[1]);
	ofstream fout(argv[2]);

	string originalString;

	getline(fin, originalString);

	map<char, int, less<>> alphabetMap;

	for (char& character : originalString)
	{
		auto iteratorToCharacter = alphabetMap.find(character);
		if (iteratorToCharacter != alphabetMap.end())
		{
			iteratorToCharacter.operator*().second++;
		}
		else
		{
			alphabetMap.insert(make_pair(character, 1));
		}
	}
	

	vector<Nod*> nodesVector;

	fout << alphabetMap.size() << endl;

	for (auto& pair : alphabetMap)
	{
		Nod* nod = new Nod;
		nod->data = pair.first;
		nod->fr = pair.second;
		nod->st = NULL;
		nod->dr = NULL;
		nod->minASCII = nod->data;

		nodesVector.push_back(nod);

		fout << pair.first << " " << pair.second << "\n";
	}

	int nodesNum = nodesVector.size();
	

	for (int i = 1; i < nodesNum; i++)
	{
		Nod* z = new Nod;

		z->st = getMinNode(nodesVector);
		z->dr = getMinNode(nodesVector);
		z->fr = z->st->fr + z->dr->fr;
		z->minASCII = min(z->st->minASCII, z->dr->minASCII);
		z->data = NULL;

		insertAtProperPlace(nodesVector, z);
	}

	Nod* root = nodesVector[0];
	string codedPath;
	for (char letter : originalString)
	{
		codedPath += parseTree(root, "", letter);
	}

	fout << codedPath;

	return 0;
}