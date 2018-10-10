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
	cout << "Building Tree"; 
	buildTree(); 

	//cout << "Finished Building Tree";
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
	for (int i = 0; i < arrayCounter; i++)
	{
		huff_node newNode; 
		newNode.symbol = symbolArray[i]; 
		newNode.weight = weightArray[i];

		nodeStorage[i] = newNode; 
		focus_list[i] = &nodeStorage[i]; 
	}
	focus_listCounter = arrayCounter; 
	printFOCUS(); 
}

void Huffman::buildTree()
{
	bool complete; 
	int prevFound; 
	int index1, index2; 
	int maxFound = 0; 
	int smallestFound = 0;
	int smallestFound2 = 0; 
	while (focus_listCounter > 1)
	{
		//need to find the two smallest values in the focus array

		//maybe set smallestfound to the max in the list 
		/*
		for (int m = 0; m < focus_listCounter; m++)
		{
			if (focus_list[m]->weight > maxFound) 
			{
				smallestFound = focus_list[m]->weight; 
				index1 = m; 
			}
		}*/ 
			
			smallestFound = focus_list[0]->weight;
			smallestFound2 = focus_list[0]->weight;
			index1 = 0;
			

			for (int i = 0; i < focus_listCounter; i++)
			{
				if ((focus_list[i]->weight <= smallestFound) && (focus_list[i]->weight != 0))
				{
					/*
					if (index1 != 0)
					{
						//shift up found value
						index2 = index1;
					}
					*/
					index2 = index1;
					index1 = i;
					smallestFound = focus_list[i]->weight;
				}

			}
			if (index1 == index2)
			{
				smallestFound2 = 100000000; 
				//both values are the same, need to look for one that is larger than the other but still the smallest
				for (int m = 0; m < focus_listCounter; m++)
				{
					if ((focus_list[m]->weight <= smallestFound2) && (focus_list[m]->weight > smallestFound) && (focus_list[m]->weight != 0))
					{
						smallestFound2 = focus_list[m]->weight; 
						index2 = m; 
					}
				}
			}
		
		cout << "lowest values : " << focus_list[index1]->symbol << " : " << focus_list[index1]->weight << "\n";
		cout << "lowest value 2 : " << focus_list[index2]->symbol << " : " << focus_list[index2]->weight << "\n";

		createParentNode(index1, index2);
		
		//found the lowest stuff
		cout << "UPDATED LIST --------------------------------------------------\n"; 
		printFOCUS(); 
	}

	//the last element in the focus list should be the root node
	rootNode = focus_list[0]; 
	cout << "COMPLETE !!!!!" << "\n"; 
	cout << "rootNode weight " << rootNode->weight;
}

void Huffman::printFOCUS() 
{
	cout << "PRINTING FOCUS \n"; 
	for (int i = 0; i < focus_listCounter; i++)
	{
		cout << focus_list[i]->symbol << " : " << focus_list[i]->weight << "\n";
	}
}

void Huffman::createParentNode(int index1, int index2)
{
	huff_node* node1;
	huff_node*node2; 
	huff_node newNode; 
	int weight1, weight2; 

	node1 = focus_list[index1];
	node2 = focus_list[index2];
	newNode.leftChild = node1; 
	newNode.rightChild = node2; 
	weight1 = node1->weight; 
	weight2 = node2->weight; 
	newNode.weight = weight1 + weight2; 
	nodeStorage[arrayCounter] = newNode; 
	//need to trim list of the two values I am reaplacing 
	//index 1 will contain the new node, index 2 will be empty hole 
	//need to fill the hole 
	focus_list[index1] = &nodeStorage[arrayCounter];
	numOfParentsCreated++; 
	arrayCounter++; 
	trimFocus(index2); 
}

void Huffman::trimFocus(int empty_index)
{
	//remove empty hole from focus array
	huff_node* tempHolder; 
	int a = empty_index; 

	while (a <= focus_listCounter)
	{
		focus_list[a] = focus_list[a + 1]; 
		//tempHolder = focus_list[a+1]; 
		//focus_list[a] = focus_list[a + 1]; 
		a++; 
	}
	focus_listCounter--; 
}