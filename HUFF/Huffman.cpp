#include "pch.h"
#include "Huffman.h"


//public methods 
Huffman::Huffman()
{
	
	for (int i = 0; i <= 256; i++)
	{
		weightArray[i] = 0; 
		//symbolArray[i] = NULL; 
	}
	 
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
	buildTree(); 

	cout << "Finished Building Tree";
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
	bool complete; 
	int prevFound; 
	int index1, index2; 
	int smallestFound = 0;
	int smallestFound2 = 0; 

	//need to find the two smallest values in the focus array
	for (int m = 0; m < 1; m++)
	{
		smallestFound = focus_list[0]->weight;
		smallestFound2 = focus_list[0]->weight; 
		index1 = 0; 

		for (int i = 0; i <= arrayCounter; i++)
		{
			if (m == 0)
			{
				if ((focus_list[i]->weight < smallestFound) && (focus_list[i]->weight != 0))
				{
					if (index1 != 0)
					{
						//shift up found value
						index2 = index1;
					}
					index1 = i;
					smallestFound = focus_list[i]->weight;
				}
			}
		}
	}
	createParentNode(index1, index2); 

	//found the lowest stuff
	cout << "lowest values : " << focus_list[index1]->symbol << " : " << focus_list[index1]->weight << "\n"; 
	cout << "lowest value 2 : " << focus_list[index2]->symbol << " : " << focus_list[index2]->weight << "\n"; 
}

void Huffman::createParentNode(int index1, int index2)
{
	huff_node* node1;
	huff_node*node2; 
	huff_node newNode; 

	node1 = focus_list[index1];
	node2 = focus_list[index2];
	newNode.leftChild = node1; 
	newNode.rightChild = node2; 
	newNode.weight = node1->weight + node2->weight;
	nodeStorage[arrayCounter] = newNode; 
	//need to trim list of the two values I am reaplacing 
}

void Huffman::trimFocus()
{

}