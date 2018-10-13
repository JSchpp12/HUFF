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
	int powersOf2[8]; 

	huff_node* rootNode; 
	huff_node nodeStorage[2000];


	//use this to store the binary representation of each character in the encoding table 
	string binaryRepList[256]; 

	//use this array to build the tree and stuff
	huff_node* focus_list[2000]; 

	huff_node* leafNodes[256]; 

	//store the single 0s that still need to be matched here
	huff_node* singleZeroes[256]; 
	//going to store the matched symbols that have 0 weight here 
	huff_node* matchedZeroes[256];  

	int symbolRep_weights[255]; 

	//store tree building data here
	char treeBuilder[510]; 
	int treeBuilder_counter = 0; 

	int focus_listCounter = 0; 
	int arrayCounter = 0;
	int numOfCharacters = 0; 
	int binaryArrayCounter = 0; 
	int numOfParentsCreated = 0; 
	int weightArray[256];
	unsigned char symbolArray[256];

	Huffman();
	~Huffman();
	void MakeTreeBuilder(string inputFile, string OutputFile); 
	void EncodeFile(string inputFile, string OutputFile); 
	void DecodeFile(string inputFile, string OutputFile); 
	void EncodeFileWithTree(string inputFile, string OutputFile); 
	void DisplayHelp();
	void foundBinaryPath(string binaryPath); 
	

private: 
	void createParentOfZeroes(huff_node* node1, huff_node* node2, int lowerIndex); 
	void openFile(string fileName); 
	void buildTreeOfNonZeros(); 
	void buildTreeOfZeros(); 
	void printArrays();
	void printFOCUS(); 
	void createInitialNodes(); 
	void createParentNode(int index1, int index2); 
	huff_node* findNextLowest(int lowestVal); 
	void trimFocus(int empty_index); 
	void buildEncodingTable();
	void traverseForChar(huff_node* currentNode, char focus);
	void printBinaryTable(); 
	string findPath(huff_node* leaf_node); 
	void _traverse(huff_node * in_node); 
	void write_incodedInput(string inputFile, string outputFile);
	void writeTreeBuildingDataToFile(string outputFile); 
};

