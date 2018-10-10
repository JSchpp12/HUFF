#pragma once
#include <string>
#include <iostream>
#include <fstream>

using namespace std; 

class Huffman
{
public:
	struct huff_node
	{
		huff_node* parent; 
		huff_node* rightChild; 
		huff_node* leftChild; 
		int weight; 
		char symbol; 
	};

	huff_node* rootNode; 
	huff_node nodeStorage[2000];

	//use this array to build the tree and stuff
	huff_node* focus_list[2000]; 
	int focus_listCounter = 0; 
	int arrayCounter = 0; 
	int numOfParentsCreated = 0; 
	int weightArray[256];
	char symbolArray[256];

	Huffman();
	~Huffman();
	void MakeTreeBuilder(string inputFile, string OutputFile); 
	void EncodeFile(string inputFile, string OutputFile); 
	void DecodeFile(string inputFile, string OutputFile); 
	void EncodeFileWithTree(string inputFile, string OutputFile); 
	void DisplayHelp();

private: 
	void openFile(string fileName); 
	void buildTree(); 
	void printArrays();
	void printFOCUS(); 
	void createInitialNodes(); 
	void createParentNode(int index1, int index2); 
	huff_node* findNextLowest(int lowestVal); 
	void trimFocus(int empty_index); 
};

