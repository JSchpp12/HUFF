//Jacob Schaupp 
//10/17/2018
//EECS 2510 Non-Linear Data Structures 

#include "pch.h"
#include "Huffman.h"
#include "ctime"
#include <iostream>
using namespace std; 

string stringSnipping(string inString, string targetExtension); 
int getFileSize(string fileName); 
void complete(clock_t begin, string inputFile, string outputFile); 


int main(int argc, char* argv[])
{
	string fileName1, fileName2, fileName3, argumentType; 
	Huffman huffmanTree; 

	clock_t begin = clock(); 

	//cin >> argumentType >> fileName1; 

	for (int i = 0; i < argc; i++)
	{
		if (i == 1)
		{
			argumentType = argv[i]; 
		}
		else if (i == 2)
		{
			argumentType = argv[i]; 
		}
		else if (i == 3)
		{
			fileName1 = argv[i]; 
		}
		else if (i == 4)
		{
			fileName2 = argv[i]; 
		}
		else if (i == 5)
		{
			fileName3 = argv[i]; 
		}
	}

	if ((fileName1 != "") && (fileName1 != fileName2))
	{
		//deal with arguments here 
		if (argumentType == "-t")
		{
			//build the tree file
			if (fileName2 == "")
			{
				fileName2 = stringSnipping(fileName1, ".htree"); 
			}
			huffmanTree.MakeTreeBuilder(fileName1, fileName2); 

			complete(begin, fileName1, fileName2); 
			return 0; 
		}

		else if (argumentType == "-e")
		{
			//build tree file and encode
			if (fileName2 == "")
			{
				fileName2 = stringSnipping(fileName1, ".huf"); 
			}
			huffmanTree.EncodeFile(fileName1, fileName2);

			complete(begin, fileName1, fileName2); 
			return 0; 
		}

		else if (argumentType == "-et")
		{
			//encode from exsisting tree
			if (fileName3 == "")
			{
				fileName3 = stringSnipping(fileName1, ".huf"); 
			}
			huffmanTree.EncodeFileWithTree(fileName1, fileName2, fileName3); 
			return 0; 
		}

		else if (argumentType == "-d")
		{
			//decode
			if (fileName2 == "" )
			{
				return 1; 
			}
			else
			{
				huffmanTree.DecodeFile(fileName1, fileName2);
				
				complete(begin, fileName1, fileName2); 
				return 0; 
			}
		}
		else if ((argumentType == "-h") | (argumentType == "?") | (argumentType == "-help"))
		{
			//help
			huffmanTree.DisplayHelp(); 
		}
	}
	else
	{
		//no file given 
		return 1;
	}
}


string stringSnipping(string inString, string targetExtension)
{
	int lengthToRemove; 

	//remove the extension from the file and return the new file 
	for (int i = 0; i < inString.length(); i++)
	{
		if (inString[i] == '.')
		{
			lengthToRemove = inString.length() - i; 
			inString.erase(i, lengthToRemove); 
			break; 
		}
	}

	inString = inString + targetExtension;
	return inString; 
}

int getFileSize(string fileName)
{
	ifstream file(fileName, ios::binary | ios::ate);
	return file.tellg();
}

void complete(clock_t begin, string inputFile, string outputFile)
{
	int size1, size2; 

	size1 = getFileSize(inputFile); 
	size2 = getFileSize(outputFile); 

	//print clock times 
	clock_t end = clock();
	double elapsed_secs = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "Elapsed time: " << elapsed_secs << " seconds. " << size1 << " bytes in / " << size2 << " bytes out \n";
}