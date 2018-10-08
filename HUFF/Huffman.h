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
		huff_node* parentChild; 
		huff_node* rightChild; 
		huff_node* leftChild; 
		int weight; 
		char symbol; 
	};

	int arrayCounter = 0; 
	int freqArray[256];

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
	void printArrays(); 
};

