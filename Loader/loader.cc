#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

int hexToInt(string hex)
{
	int val=0,i=hex.length()-1,j=hex.length()-1;
	int powerOfSixteen[]={1,16,256,4096,65536,1048576};
	while(i>=0)
	{
		switch(hex[i])
		{
			case '0':
				break;
			case '1':
				val=val+powerOfSixteen[j-i];
				break;
			case '2':
				val=val+powerOfSixteen[j-i]*2;
				break;
			case '3':
				val=val+powerOfSixteen[j-i]*3;
				break;
			case '4':
				val=val+powerOfSixteen[j-i]*4;
				break;
			case '5':
				val=val+powerOfSixteen[j-i]*5;
				break;
			case '6':
				val=val+powerOfSixteen[j-i]*6;
				break;
			case '7':
				val=val+powerOfSixteen[j-i]*7;
				break;
			case '8':
				val=val+powerOfSixteen[j-i]*8;
				break;
			case '9':
				val=val+powerOfSixteen[j-i]*9;
				break;
			case 'A':
				val=val+powerOfSixteen[j-i]*10;
				break;
			case 'B':
				val=val+powerOfSixteen[j-i]*11;
				break;
			case 'C':
				val=val+powerOfSixteen[j-i]*12;
				break;
			case 'D':
				val=val+powerOfSixteen[j-i]*13;
				break;
			case 'E':
				val=val+powerOfSixteen[j-i]*14;
				break;
			case 'F':
				val=val+powerOfSixteen[j-i]*15;
				break;
		}
		i--;
	}
	
	return val;
}

int main(int argc, char* argv[])
{
	try
	{
		ifstream input;
		input.open(argv[1]);
		string line;
		unsigned char mem[32768];	//memory where program will be loaded
		for(int i=0;i<32768;i++) mem[i]=255;
		if(input.is_open())
		{
			getline(input,line);
			getline(input,line);
			while(line[0]!='E')
			{
				int ADDRESS = hexToInt(line.substr(1,6));
				string OBJ=line.substr(9,line.length()-9);
				for(int i=0;i<OBJ.length();i=i+2)
				{
					string a=OBJ.substr(i,2);
					int val=hexToInt(a);
					mem[ADDRESS]=val;
					ADDRESS++;
				}
				getline(input,line);
			}
			
			/*Show memory after loading the program*/
			
			for(int i=0;i<1024;i++)
			{
				cout<<setfill('0')<<setw(4)<<hex<<uppercase<<i*16<<" ";
				cout<<setfill('0')<<setw(2)<<hex<<uppercase<<(int)mem[i*16]<<setfill('0')<<setw(2)<<(int)mem[i*16+1]<<setfill('0')<<setw(2)<<(int)mem[i*16+2]<<setfill('0')<<setw(2)<<(int)mem[i*16+3];
				cout<<" ";
				cout<<setfill('0')<<setw(2)<<hex<<uppercase<<(int)mem[i*16+4]<<setfill('0')<<setw(2)<<(int)mem[i*16+5]<<setfill('0')<<setw(2)<<(int)mem[i*16+6]<<setfill('0')<<setw(2)<<(int)mem[i*16+7];
				cout<<" ";
				cout<<setfill('0')<<setw(2)<<hex<<uppercase<<(int)mem[i*16+8]<<setfill('0')<<setw(2)<<(int)mem[i*16+9]<<setfill('0')<<setw(2)<<(int)mem[i*16+10]<<setfill('0')<<setw(2)<<(int)mem[i*16+11];
				cout<<" ";
				cout<<setfill('0')<<setw(2)<<hex<<uppercase<<(int)mem[i*16+12]<<setfill('0')<<setw(2)<<(int)mem[i*16+13]<<setfill('0')<<setw(2)<<(int)mem[i*16+14]<<setfill('0')<<setw(2)<<(int)mem[i*16+15];
				cout<<endl;
			}
		}
		else throw string("Could not open the file for reading");
	}
	catch(string e)
	{
		cout<<e<<endl;
	}
}