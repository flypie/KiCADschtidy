// KiCAd sch scan.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <filesystem>
//#include <fileapi.h>
//#include <Windows.h>
#include <io.h>
#include <String>

namespace fs=std::filesystem;

#include "Sch.h"

Sch* Root=NULL;

int main(int argc,char* argv[])
{

	for(int i=1; i<argc; i++)
	{

		_finddata_t FData;

		string WCard = argv[i];
		string Path=WCard.substr(0,WCard.find_last_of("\\")+1);

		std::cout<<"The WildCard is "<<WCard<<'\n';
		std::cout<<"The parent path is "<<Path<<'\n';

		int hFind=_findfirst(WCard.c_str(),&FData);

		if(hFind>0)
		{
			do
			{
				string FileName=FData.name;

				if(FileName.substr(FileName.find_last_of(".")+1)=="sch")
				{
					string FullName=Path+FileName;

					std::cout<<"Processing "<<FullName<<'\n';

					Root=new Sch(FullName,0);

					if(Root)
					{
						delete Root;
					}
				}
			}
			while(_findnext(hFind,&FData)==0);
			_findclose(hFind);
		}

	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
