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
	cout << "Finished Reading File";
}

void Huffman::printArrays()
{
	for (int i = 0; i <= 256; i++)
	{
		cout << symbolArray[i] << " : " << weightArray[i] << "\n"; 
	}
}
