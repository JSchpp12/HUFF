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
	//create tree building data from file 

	this->openFile(inputFile);
	this->buildTree(); 
	this->buildEncodingTable(); 
	this->writeTreeBuildingDataToFile(OutputFile);
	this->write_incodedInput(inputFile, OutputFile);
	//this->readFromFile("TEST.TXT.huf"); 
}

void Huffman::MakeTreeBuilder(string inputFile, string outputFile)
{
	//generate tree building data from input file and write out to file 
	this->openFile(inputFile); 
	this->buildTree(); 
	this->writeTreeBuildingDataToFile(outputFile); 
}

void Huffman::EncodeFileWithTree(string treeBuildingFile, string targetFile, string outputFile)
{
	//treeBuildingFile - should contain the target tree building information
	//targetFile - should be the file that is being encoded with the tree building information

	//take an exsisting tree and encode a file using that 
	//need to start by building tree from tree building data 
	this->readTreeBuildingData(treeBuildingFile); 
	this->writeTreeBuildingDataToFile(outputFile); 
	this->write_incodedInput(targetFile, outputFile);
}

void Huffman::DisplayHelp()
{
	cout << "Welcome... \n"; 
	cout << "To use this program, give an argument type followed by 1 to 3 file names \n "; 
	cout << "HUFF [argument] [fileName1] [fileName2] [fileName3] \n"; 
	cout << "Proper arguments are... \n";
	cout << "Available arguments: \n"; 
	cout << "-e -- Encode Directly From Input File (2 filenames) \n"; 
	cout << "-d -- Decode input file : decode file1 into file2 (2 filenames) \n"; 
	cout << "-t -- Create a tree building file (1 required - 1 optional fileName) \n"; 
	cout << "-et -- Encode file2 with tree building data from file1 (2 required - 1 optional filnames) \n"; 

}

void Huffman::DecodeFile(string inputFile, string outputFile)
{
	//read encoded file for tree building data 
	//decode the file 
	//this->readFromFile(inputFile); 

	this->readTreeBuildingData(inputFile); 
	this->buildEncodingTable(); 
	this->printBinaryTable(); 
	this->decodeFile(inputFile, outputFile); 
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
	inStream.open(fileName, ios::in | ios::binary); 

	while (inStream >> noskipws >> c)
	{
		//cout << c << "\n";
		numOfCharacters++;
		temp = c;
		symbolRep_weights[temp]++;
		//cout << c; 
	}

	numTimes++; 
	printArrays(); 
	createInitialNodes();
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
		treeBuilder[treeBuilder_counter] = index1;
		treeBuilder_counter++;
		treeBuilder[treeBuilder_counter] = index2;
		treeBuilder_counter++;

		createParentNode(index1, index2);

		//found the lowest stuff
	}
	printFOCUS(); 

	//the last element in the focus list should be the root node
	rootNode = focus_list[0]; 
	rootNode->parent = nullptr;  
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
	//these are working 
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

	std::reverse(constructedPath.begin(), constructedPath.end());
	return constructedPath; 
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
		//cout << c << " : " << binaryRepList[c] << "\n";
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
			//cout << "writing block " << block << " \n";
			outStream.put(block);
			block = '\0';
			position = 0; 

		}
	}
	else if (input == 0)
	{
		//set the next bit as 0 
		block = block & ~(1 << (7 - position)); 
		position++; 
		if ((position%8) == 0)
		{
			//cout << "writing block " << block << " \n"; 
			outStream.put(block); 
			block = '\0'; 
			position = 0; 

		}
	}
	else
	{
		//this should be end of file

		//need to add padding if not full
		if ((position%8) != 0)
		{
			//find padding bits 
			numOfBits = 8 - position; 
			string padding = findPaddingBits(numOfBits); 
			if (padding != "")
			{
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
				//outStream.write((const char*)&block, 1); 
			}
		}
		outStream.put(block); 
		//outStream.write((const char*)&block, 1);
	}
}

string Huffman::findPaddingBits(int numBitsNeeded)
{
	int level = 0; 
	string paddingBits; 
	bool found = false; 
	huff_node* currentNode;

	//start at the root 
	currentNode = rootNode;

	//need to find a path that does not lead to a leaf 
	while (level != numBitsNeeded)
	{
		if (currentNode->leftChild != nullptr)
		{
			paddingBits = paddingBits + "0"; 
			currentNode = currentNode->leftChild; 
			level++; 
		}
		else if (currentNode->rightChild != nullptr)
		{
			paddingBits = paddingBits + "1"; 
			currentNode = currentNode->rightChild; 
			level++; 
		}
		else
		{
			currentNode = currentNode->parent; 
			currentNode = currentNode->rightChild; 
			paddingBits = paddingBits + "1"; 
		}
	}
	return paddingBits; 
}

void Huffman::writeTreeBuildingDataToFile(string outputFile)
{
	char temp; 
	int dataToWrite; 
	int* pointerToData; 

 	ofstream outStream(outputFile, ios::out | ios::binary);
	//to write: 
	//outStream.write((char*)&my_double, sizeof(double)); 

	//need to write the first 510 bits as the tree building data 
	for (int n = 0; n < 510; n++)
	{
		//outStream << treeBuilder[n]; 
		dataToWrite = treeBuilder[n]; 
		cout << dataToWrite << "\n"; 
		//convert the int into a char 
		int a = dataToWrite; 

		int e = dataToWrite & 0xff;

		outStream.write(reinterpret_cast<const char *>(&e), 1);
	}	

	//close the file 
	outStream.close();
}

void Huffman::readFromFile(string fileName)
{
	cout << "reading file \n"; 

	ifstream inStream; 

	inStream.open(fileName, ios::in | ios::binary); 
	if (!inStream.is_open())
	{
		cout << "unable to open \n"; 
	}
	unsigned char readByte; 
	unsigned int number; 
	inStream.read((char*)&readByte, 1); 
	number = (unsigned int)readByte; 

	cout << number; 
}

void Huffman::readTreeBuildingData(string inputFile)
{
	//read the tree building data from the file
	//build the tree from the data 
	ifstream inStream;
	inStream.open(inputFile, ios::in | ios::binary);

	int numOfBytesRead = 0; 
	unsigned int num1, num2; 
	unsigned char byte1, byte2; 

	//build initial nodes first with the characters and 0 weights -> populate focus list 
	createInitialNodes(); 

	while (numOfBytesRead <	510)
	{
		//read the first two numbers from the file 

		inStream.read((char*)&byte1, 1);
		inStream.read((char*)&byte2, 1); 

		num1 = (unsigned int)byte1;
		num2 = (unsigned int)byte2; 

		//make a parent node for the read children 
		createParentNode(num1, num2); 
		
		treeBuilder[treeBuilder_counter] = num1; 
		treeBuilder_counter++; 
		treeBuilder[treeBuilder_counter] = num2; 
		treeBuilder_counter++; 

		numOfBytesRead = numOfBytesRead + 2; 
	}
	rootNode = focus_list[0];
	rootNode->parent = nullptr; 

	//this->printBinaryTable(); 
}

void Huffman::decodeFile(string inputFile, string outputFile)
{
	cout << outputFile << "\n"; 

	ifstream inStream; 
	inStream.open(inputFile, ios::in | ios::binary); 

	ofstream outStream; 
	outStream.open(outputFile, ios::out); 

	huff_node* currentNode; 
	currentNode = rootNode; 

	//file should start with 510 bytes of tree building data 
	int currentBit = 7;
	int counter = 0; 
	unsigned char c; 
	string returned; 

	//inStream.read((char*)&c, 1);

	for (int j = 0; j < 510; j++)
	{
		inStream.get(); 
	}

	while (!inStream.eof())
	{
		returned = readNextByte(inStream); 

		for (int i = 0; i < 8; i++)
		{
			//check if the current node is a leaf node 

			//if ((currentNode->leftChild == nullptr) && (currentNode->rightChild == nullptr))
			if (currentNode->symbol != -52)
			{
				char temp = currentNode->symbol;
				outStream.write(reinterpret_cast<const char *>(&temp), sizeof(char));
				currentNode = rootNode; 
			}

			//continue reading the file 
			if (returned[i] == '0')
			{
				currentNode = currentNode->leftChild; 
			}
			else
			{
				currentNode = currentNode->rightChild; 	
			}
		}
	}
}

string Huffman::readNextByte(ifstream & instream)
{
	unsigned char readByte; 
	unsigned char tempHolder; 
	static int read_bitPos = 0; 
	unsigned int result; 

	//static unsigned char c = instream.get(); 
	unsigned char bitArray[8]; 

	string binaryString = ""; 

	instream.read((char*)&readByte, 1);

	for (int i = 7; i >=0 ; i--)
	{
		result = 0; 
		result = readByte & powersOf2[i]; 

		if (result == powersOf2[i])
		{
			binaryString = binaryString + "1"; 

		}
		else
		{
			binaryString = binaryString + "0"; 
		}
	}
	//std::cout << binaryString << "\n"; 
	return binaryString;
}