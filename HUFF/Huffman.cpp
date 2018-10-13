#include "pch.h"
#include "Huffman.h"


//public methods 
Huffman::Huffman()
{
	
	for (int i = 0; i <= 256; i++)
	{
		symbolRep_weights[i] = 0; 
		//symbolArray[i] = NULL; 
	}

	powersOf2[0] = 1; 
	powersOf2[1] = 2; 
	powersOf2[2] = 4; 
	powersOf2[3] = 8; 
	powersOf2[4] = 16; 
	powersOf2[5] = 32; 
	powersOf2[6] = 64; 
	powersOf2[7] = 128; 
	powersOf2[8] = 256; 
}


Huffman::~Huffman()
{
}

void Huffman::EncodeFile(string inputFile, string OutputFile)
{
	//this will build a tree based on input file and write tree building data and compressed stream to outputFile
	this->openFile(inputFile);
	this->buildTreeOfNonZeros(); 
	this->buildEncodingTable(); 
	this->printBinaryTable(); 
	this->writeTreeBuildingDataToFile(OutputFile);
	this->write_incodedInput(inputFile, "OUTPUT_TEST.TXT");
	this->readFromFile("OUTPUT_TEST.TXT"); 
	return; 
}


//private methods 

void Huffman::openFile(string fileName)
{
	//this will open a file and read in data building tree table information 

	unsigned char c;
	int temp; 
	int numTimes = 0; 
	//create the stream and open the file in read mode
	ifstream inStream; 
	inStream.open(fileName, ios::in); 

	while (inStream >> noskipws >> c)
	{
		//cout << c << "\n";
		numOfCharacters++;
		temp = c;
		symbolRep_weights[temp]++;
	}

	numTimes++; 
	printArrays(); 
	createInitialNodes();

	//cout << "Building Tree"; 
	//buildTree(); 
	//writeTreeBuildingDataToFile("OUTPUT_TEST.TXT"); 
	//cout << "Finished Building Tree";
}

void Huffman::printArrays()
{
	char temp; 

	for (int i = 0; i <= 256; i++)
	{
		temp = i; 
		std::cout << i << " : " << symbolRep_weights[i] << "\n"; 
		//cout << symbolArray[i] << " : " << weightArray[i] << "\n"; 
	}
}

void Huffman::createInitialNodes()
{
	unsigned char tempConverter; 

	//need to create inital nodes for all items in arrays so that tree can be built
	for (int i = 0; i < 256; i++)
	{
		tempConverter = i; 

		huff_node newNode;
		newNode.symbol = i; 
		newNode.weight = symbolRep_weights[i]; 
		newNode.leftChild = nullptr; 
		newNode.rightChild = nullptr; 

		nodeStorage[i] = newNode;
		focus_list[i] = &nodeStorage[i];
		leafNodes[i] = &nodeStorage[i]; 
	}
	arrayCounter = 256; 
	nodeStorageCounter = 256; 
	focus_listCounter = 256;
}

void Huffman::buildTreeOfNonZeros()
{
	bool complete; 
	int prevFound; 
	int index1, index2; 
	int maxFound = 0; 
	int smallestFound = 0;
	int smallestFound2 = 0; 
	while (focus_listCounter > 1)
	{
		if (focus_listCounter == 122)
		{
			cout << "Warning"; 
		}
		std::cout << focus_listCounter << " : " << " \n"; 
		//need to find the two smallest values in the focus array

		smallestFound = 1000000000; 
		smallestFound2 = 1000000000;
		index1 = 0;


		for (int i = 0; i < focus_listCounter; i++)
		{
			if ((focus_list[i]->weight <= smallestFound))
			{
				index2 = index1;
				index1 = i;
				smallestFound = focus_list[i]->weight;
			}
		}

		//both values are the same, need to look for one that is larger than the other but still the smallest
		if (index1 == index2)
		{
			smallestFound2 = 100000000; 
			for (int m = 0; m < focus_listCounter; m++)
			{
				if ((focus_list[m]->weight <= smallestFound2) && (focus_list[m]->weight > smallestFound))
				{
					smallestFound2 = focus_list[m]->weight;
					index2 = m;
				}
			}
		}
		//if (focus_list[index1]->weight != 0)
		//{
			std::cout << "lowest values : " << focus_list[index1]->symbol << " : " << focus_list[index1]->weight << "index :" << index1 << "\n";
			std::cout << "lowest value 2 : " << focus_list[index2]->symbol << " : " << focus_list[index2]->weight << "index : " << index2 << "\n";
		//}
		treeBuilder[treeBuilder_counter] = index1;
		treeBuilder_counter++;
		treeBuilder[treeBuilder_counter] = index2;
		treeBuilder_counter++;

		createParentNode(index1, index2);

		//found the lowest stuff
		//cout << "UPDATED LIST --------------------------------------------------\n"; 
	}
	printFOCUS(); 
	//the last element in the focus list should be the root node
	rootNode = focus_list[0]; 
	rootNode->parent = nullptr; 
	//cout << "COMPLETE !!!!!" << "\n"; 
	//cout << "rootNode weight " << rootNode->weight;
	//cout << "NUM : " << numOfCharacters << "\n"; 

	//_traverse(rootNode);	
	//buildEncodingTable(); 
	//printBinaryTable(); 
} 

void Huffman::printFOCUS() 
{
	std::cout << "PRINTING FOCUS \n"; 
	for (int i = 0; i < focus_listCounter; i++)
	{
		std::cout << focus_list[i]->symbol << " : " << focus_list[i]->weight << "\n";
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
	if (node1->weight != 0)
	{
		cout << "warning"; 
	}
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
	focus_list[index2] = nullptr; 
	//focus_list[index2] = nullptr; 
	//set new node as parent to the 2 target nodes 
	node1->parent = &nodeStorage[arrayCounter]; 
	node2->parent = &nodeStorage[arrayCounter];

	numOfParentsCreated++; 
	arrayCounter++; 
	trimFocus(index2); 
}

void Huffman::trimFocus(int empty_index)
{
	//remove empty hole from focus array
	huff_node* tempHolder; 
	int a = empty_index ; 

	while (a <= focus_listCounter)
	{

		focus_list[a] = focus_list[a + 1];
		//tempHolder = focus_list[a+1]; 
		//focus_list[a] = focus_list[a + 1]; 
		a++;
	}
	focus_list[focus_listCounter] = nullptr;
	focus_listCounter--; 
}


void Huffman::buildEncodingTable()
{
	//build binary encoding table from the complete table
	//traverse the tree for this
	//right child = 1
	//left child = 2
	for (int i = 0; i < 256; i++)
	{
		//binaryRep[i] = traverseForChar(symbolArray[i], "", rootNode);
		//traverseForChar(rootNode, symbolArray[i]);
		binaryRepList[i] = findPath(leafNodes[i]); 
	}

}

string Huffman::findPath(huff_node* leafNode)
{
	huff_node* currentNode, *temp; 
	currentNode = leafNode; 
	string constructedPath = ""; 

	//go up to parent of the node I want and check if the node is the right or left child of the parent and append representative bit 
	while (currentNode->parent != nullptr)
	{
		temp = currentNode->parent; 
		if (temp->rightChild == currentNode)
		{
			constructedPath = constructedPath + "1";
		}
		else if (temp->leftChild == currentNode)
		{
			constructedPath = constructedPath + "0"; 
		}
		currentNode = temp; 
	}
	return constructedPath; 
	//foundBinaryPath(constructedPath); 
}

void Huffman::foundBinaryPath(string binaryPath)
{
	binaryRepList[binaryArrayCounter] = binaryPath; 
	binaryArrayCounter++; 
}

void Huffman::printBinaryTable()
{
	unsigned char tempConverter; 

	std::cout << "Printing binary table \n"; 
	for (int i = 0; i < 256; i++)
	{
		tempConverter = i; 
		//cout << symbolArray[i] << " : " << binaryRepList[i] << "\n"; 
		std::cout << tempConverter << " : " << binaryRepList[i] << "\n"; 
	}
}

void Huffman::write_incodedInput(string inputFile, string outputFile)
{
	//ONLY CALLED AFTER ENCODING TABLE IS CREATED---
	//once encoding table is generated, read the input file and encode into output file 
	//need padding bits if compiled  message is not a multiple of 8
	int numOfBytesWritten = 0;

	int index; 
	unsigned char c, temp; 
	int intOfChar;
	int binaryRepresentative;
	int calculatedPowerOf2;

	//use this to count the number of ints on stack 
	int lengthOfString;

	string binaryString;

	//create the stream and open the file in read mode
	ifstream inStream;
	inStream.open(inputFile, ios::in);
		
	//open the output file as a binary output 
	ofstream outStream;
	outStream.open(outputFile, ios::app | ios::binary);

	while (inStream >> noskipws >> c)
	{
		cout << c << " : " << binaryRepList[c] << "\n";
		intOfChar = c;
		binaryString = binaryRepList[intOfChar]; 

		for (int i = 0; i < binaryString.size(); i++)
		{
			temp = binaryString[i];
			if (temp == '1')
			{
				writeHandler(1, outStream); 
			}
			else if (temp == '0')
			{
				writeHandler(0, outStream); 
			}
		}
	}
	writeHandler(2, outStream); 
}

void Huffman::writeHandler(int input, ofstream &outStream)
{
	//mark where in the block currently at 
	static int position = 0; 

	//the actual block to be written
	static unsigned char block = '\0'; 

	string paddingBits; 
	int numOfBits; 
	unsigned char temp; 

	if (input == 1)
	{
		block = block | (1 << (7 - position)); 
		position++; 
		if ((position % 8) == 0)
		{
			cout << "writing block " << block << " \n";
			outStream.put(block);
			block = '\0';
			position = 0; 

		}
	}
	else if (input == 0)
	{
		//block = block & static_cast<unsigned char> (255 - (1 << (7 - position))); 
		block = block & ~(1 << (7 - position)); 
		position++; 
		if ((position%8) == 0)
		{
			cout << "writing block " << block << " \n"; 
			outStream.put(block); 
			block = '\0'; 
			position = 0; 

		}
	}
	else
	{
		//this should be end of file

		//need to add padding if not full *******************************************************
		if ((position%8) != 0)
		{
			//find padding bits 
			numOfBits = 8 - position; 
			findPaddingBits(numOfBits, 0, rootNode, ""); 
			if (paddingBits != "")
			{
				//the padding bits were successfully set 

				for (int i = 0; i < paddingBits.size(); i++)
				{
					temp = paddingBits[i];
					if (temp == '1')
					{
						block = block | (1 << (7 - position));
						position++;
					}
					else if (temp == '0')
					{
						block = block & ~(1 << (7 - position));
						position++;
					}
				}
				outStream.put(block); 
			}
			else
			{
				//padding bits were not set correctly 

			}
		}
		outStream.put(block); 
	}
	
}

void Huffman::findPaddingBits(int numBitsNeeded, int currentLevel, huff_node* currentNode, string bits)
{
	int level = 0; 
	string paddingBits; 
	bool found = false; 

	//THIS NEEEDS WORKED ON 

	if (currentNode->symbol == -52)
	{
		if (currentLevel != numBitsNeeded)
		{
			currentLevel++;
			bits = bits + "0";
			findPaddingBits(numBitsNeeded, currentLevel, currentNode->leftChild, bits);
			//cout << in_node->key << " " << in_node->counter << "\n";
			bits = bits + "1";
			findPaddingBits(numBitsNeeded, currentLevel, currentNode->rightChild, bits);
		}
		else
		{
			//set the global string 
			foundBits(bits); 
		}
	}
	else
	{
		return;
	}

}

void Huffman::foundBits(string binaryString)
{
	paddingBits = binaryString; 
}

void Huffman::writeTreeBuildingDataToFile(string outputFile)
{
	char temp; 
	int dataToWrite; 
	int* pointerToData; 

	ofstream outStream(outputFile, ios::out | ios::binary);
	//to write: 
	//outStream.write((char*)&my_double, sizeof(double)); 

	//need to write the first 250 bits as the tree building data 
	for (int n = 0; n < 510; n++)
	{
		//outStream << treeBuilder[n]; 
		dataToWrite = treeBuilder[n]; 
		outStream.write(reinterpret_cast<const char *>(&dataToWrite), 1);
	}	

	//close the file 
	outStream.close();
}

void Huffman::readFromFile(string fileName)
{
	cout << "reading file \n"; 

	ifstream inStream; 
	inStream.open(fileName, ios::in); 
	int number; 

	inStream.read((char*)&number, sizeof(number)); 
	cout << number; 
	/*
	while (inStream >> noskipws >> c)
	{
		cout << c << "\n";
	}
	*/
}