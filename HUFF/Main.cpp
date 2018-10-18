// HUFF.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Huffman.h"
#include <iostream>
using namespace std; 

//int argc, char* argv[]

string stringSnipping(string inString, string targetExtension); 

int main(int argc, char* argv[])
{
	string fileName1, fileName2, fileName3, argumentType; 
	Huffman huffmanTree; 

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
				stringSnipping(fileName1, ".htree"); 
			}
			huffmanTree.MakeTreeBuilder(fileName1, fileName2); 
			return 0; 
		}
		else if (argumentType == "-e")
		{
			//build tree file and encode
			if (fileName2 == "")
			{
				stringSnipping(fileName1, ".huf"); 
			}
			huffmanTree.EncodeFile(fileName1, fileName2);
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
			if (fileName2 != "" )
			{
				return 1; 
			}
			else
			{
				huffmanTree.DecodeFile(fileName1, fileName2);
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