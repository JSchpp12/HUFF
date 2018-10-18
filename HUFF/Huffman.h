//Jacob Schaupp 
//10/17/2018
//EECS 2510 Non-Linear Data Structures 

#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <stack>


using namespace std; 

class Huffman
{
public:
	struct huff_node
	{
		huff_node* parent; 
		huff_node* rightChild; 
		huff_node* leftChild; 
		string contained_symbols; 
		int weight; 
		char symbol; 

		//THIS VALUE ONLY USED WITH SORTING 0s 
		int numOfTimesPaired; 
	};
	int nodeStorageCounter = 0; 
	int numOfZeroes = 0; 
	unsigned int powersOf2[8]; 

	huff_node* rootNode; 
	huff_node nodeStorage[2000];

	//use this to store the binary representation of each character in the encoding table 
	string binaryRepList[256]; 

	//use this array to build the tree and stuff
	huff_node* focus_list[2000]; 

	huff_node* leafNodes[256];  

	int symbolRep_weights[255]; 

	//store tree building data here
	int treeBuilder[510]; 
	int treeBuilder_counter = 0; 

	int focus_listCounter = 0; 
	int arrayCounter = 0;
	int numOfCharacters = 0; 
	int binaryArrayCounter = 0; 
	int numOfParentsCreated = 0; 
	int weightArray[256];
	unsigned char symbolArray[256];
	string paddingBits;

	Huffman();
	~Huffman();
	void MakeTreeBuilder(string inputFile, string OutputFile); 
	void EncodeFile(string inputFile, string OutputFile); 
	void DecodeFile(string inputFile, string OutputFile); 
	void EncodeFileWithTree(string treeBuildingFile, string targetFile, string outputFile); 
	void DisplayHelp();
	void foundBinaryPath(string binaryPath); 
	

private: 
	void openFile(string fileName); 
	void buildTree(); 
	void createInitialNodes(); 
	void createParentNode(int index1, int index2); 
	void trimFocus(int empty_index); 
	void buildEncodingTable();
	string findPath(huff_node* leaf_node); 
	void write_incodedInput(string inputFile, string outputFile);
	void writeTreeBuildingDataToFile(string outputFile); 
	void readFromFile(string fileName); 
	string findPaddingBits(int numBitsNeeded); 
	//bass individual bits to this handler to write out to file 
	void writeHandler(int input, ofstream & outFile);
	void readTreeBuildingData(string inputFile); 
	void decodeFile(string inputFile, string outputFile); 
	string readNextByte(ifstream & inStream); 
};

