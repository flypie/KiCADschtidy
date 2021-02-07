#include "Sch.h"

#define MAXSHEETBLOCKSTRINGS 10

Sch::Sch()
{
	Sub=NULL;
}

void Sch::Process()
{
	string Str;
	string SheetBlockStr[MAXSHEETBLOCKSTRINGS];

	bool	InSheetBlock=false;
	bool	InCompBlock=false;
	bool	PrintOut;
	int	SheetBlockLine;

	while(!Infile.eof())
	{
		PrintOut=true;
		getline(Infile,Str);

		if(Str=="$Sheet")
		{
			InSheetBlock=true;
			SheetBlockLine=0;
		}
		else if(Str=="$EndSheet")
		{
			InSheetBlock=false;
			unsigned long Number=stoi(SheetBlockStr[1].substr(2),nullptr,16);
			string File = SheetBlockStr[3].substr(4);
			File.resize(File.find_first_of("\""));
			
			Sub=new Sch(File,Number);
			if(Sub)
			{
				delete Sub;
			}
		}
		else if(Str=="$Comp")
		{
			InCompBlock=true;
		}
		else if(Str=="$EndComp")
		{
			InSheetBlock=false;
		}
		else if(InSheetBlock)
		{
			SheetBlockStr[SheetBlockLine++]=Str;
		}
		else if(InCompBlock)
		{
			if(Str.substr(0,3)=="AR ")
			{
				unsigned long Number=stoi(Str.substr(10),nullptr,16);
				if(Number!=UUID)
				{
					PrintOut=false;
				}
			}
		}

		if(PrintOut)
		{
			Outfile<<Str<<endl;
		}
	}
}


Sch::Sch(const string FileName,const unsigned long UUIDIn)
{
	string		BckFileName=FileName.substr(0,FileName.find_last_of(".")+1)+"bck";

	UUID=UUIDIn;

	remove(BckFileName.c_str());
	rename(FileName.c_str(),BckFileName.c_str());

	Infile.open(BckFileName);

	if(Infile)
	{
		Outfile.open(FileName,ofstream::out|ofstream::trunc);
		if(Outfile)
		{
			Process();
			Outfile.close();
		}
		Infile.close();
	}
}


