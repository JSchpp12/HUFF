#include "pch.h"
#include "Huffman.h"


//public methods 
Huffman::Huffman()
{
	/*
	for (int i = 0; i < 256; i++)
	{
		weightArray[i] = 0; 
		symbolArray[i] = NULL; 
	}
	*/ 
}


Huffman::~Huffman()
{
}

void Huffman::EncodeFile(string inputFile, string OutputFile)
{
	this->openFile(inputFile); 
	this->buildTree(); 
}


//private methods 

void Huffman::openFile(string fileName)
{
	//this will open a file and read in data building tree table information 

	char c;
	int numTimes = 0; 
	//create the stream and open the file in read mode
	ifstream inStream; 
	inStream.open(fileName, ios::in); 

	while (inStream >> noskipws >> c)
	{
		//cout << c << "\n";
		
		for (int i = 0; i < 256; i++)
		{
			if (i == arrayCounter)
			{
				//hit the last element in the array 
				symbolArray[i] = c; 
				weightArray[i] = 1; 
				arrayCounter++; 
				break; 
			}
			else if ((symbolArray[i] == c))
			{
				weightArray[i]++;
				break; 
			}
			else
			{
				//cout << "An error occured "<< c << "\n"; 
			}
			/*
			else if (isblank(symbolArray[i]))
			{
				symbolArray[i] = c; 
				weightArray[i] = 1; 
				arrayCounter++; 
				break; 
			}
			*/
		}
		numTimes++; 
	}
	printArrays(); 
	createInitialNodes(); 

	cout << "Finished Reading File";
}

void Huffman::printArrays()
{
	for (int i = 0; i <= 256; i++)
	{
		cout << symbolArray[i] << " : " << weightArray[i] << "\n"; 
	}
}

void Huffman::createInitialNodes()
{
	//need to create inital nodes for all items in arrays so that tree can be built
	for (int i = 0; i <= arrayCounter; i++)
	{
		huff_node newNode; 
		newNode.symbol = symbolArray[i]; 
		newNode.weight = weightArray[i];

		nodeStorage[i] = newNode; 
		focus_list[i] = &nodeStorage[i]; 
	}
}

void Huffman::buildTree()
{
	int index1, index2; 
	int smallestFound = 0;

	//need to find the two smallest values in the focus array
	for (int i = 0; i <= arrayCounter; i++)
	{
		if (smallestFound == 0)
		{
			smallestFound = focus_list[i]->weight;
			index1 = i; 
		}
		else if (focus_list[i]->weight < smallestFound)
		{
			smallestFound = focus_list[i]->weight; 
			if (index1 != 0)
			{
				index2 = index1; 
			}
			index1 = i; 
		}
	}
	cout << "lowest values : " << focus_list[index1]->symbol << " : " << focus_list[index1]->weight; 
}

void Huffman::createParentNode(huff_node* node1, huff_node* node2)
{

}
