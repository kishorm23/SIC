#include<iostream>
#include<sstream>
#include<fstream>
#include<iomanip>
using namespace std;
#include"OPTAB.H"

void splitString(string line, string& LABEL, string& OPCODE, string& OPERAND)
{
	if(line[0]=='\t'&&line[line.length()-1]!='\t')
	{
		istringstream iss(line);
		LABEL="";
		iss>>OPCODE;
		iss>>OPERAND;
	}
	else if(line[0]!='\t'&&line[line.length()-1]=='\t')
	{
		istringstream iss(line);
		iss>>LABEL;
		iss>>OPCODE;
		OPERAND="";
	}
	else if(line[0]=='\t'&&line[line.length()-1]=='\t')
	{
		istringstream iss(line);
		LABEL="";
		iss>>OPCODE;
		OPERAND="";
	}
	else
	{
		istringstream iss(line);
		iss>>LABEL;
		iss>>OPCODE;
		iss>>OPERAND;
	}
}
void splitString2(string line, string& address, string& LABEL, string& OPCODE, string& OPERAND)
{
	if(line[4]=='\t'&&line[5]=='\t'&&line[line.length()-1]=='\t')
	{
		istringstream iss(line);
		iss>>address;
		iss>>OPCODE;
		LABEL="";
		OPERAND="";
	}

	else if(line[4]=='\t'&&line[5]=='\t'&&line[line.length()-1]!='\t')
	{
		istringstream iss(line);
		iss>>address;
		iss>>OPCODE;
		iss>>OPERAND;
		LABEL="";
	}

	else if(line[4]=='\t'&&line[5]!='\t'&&line[line.length()-1]=='\t')
	{
		istringstream iss(line);
		iss>>address;
		iss>>LABEL;
		iss>>OPCODE;
		LABEL="";
	}

	else if(line[4]=='\t'&&line[5]!='\t'&&line[line.length()-1]!='\t')
	{
		istringstream iss(line);
		iss>>address;
		iss>>LABEL;
		iss>>OPCODE;
		iss>>OPERAND;
	}


}

string intToHex(int value)
{
	int rmndr=value;
	string val;
	if(value==0) val="0";
	else
	{
		while(rmndr>0)
		{
			int digit=rmndr%16;
			if(digit<10) val.insert(0,1,'0'+digit);
			else
			{
				digit=digit-10;
				val.insert(0,1,'A'+digit);
			}
			rmndr=rmndr/16;
		}
	}
	return val;
}

void padHex(string& hex,int num)
{
	if(num>hex.size())
    hex.insert(0, num-hex.size(), '0');
	
}

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

bool isCommentLine(string line)
{
	if(line[0]=='.') return true;
	else return false;
}
int lengthOfConst(string line)
{
	if(line[0]=='X') return (line.length()-3)/2;
	else return line.length()-3;
}

bool findSYMTAB(string line)
{
	for(int i=0;i<90;i++) if(line==SYMTAB[i]) return true;
	return false;
}

int getSYMVAL(string line)
{
	for(int i=0;i<100;i++) if(line==SYMTAB[i]) return SYMTAB_add[i];
	return 0;
}

bool findOPTAB(string line)
{
	for(int i=0;i<26;i++) if(line==OPTAB[i][0]) return true;
	return false;
}
string getOPCODE(string op)
{
	for(int i=0;i<26;i++) if(op==OPTAB[i][0]) return OPTAB[i][1];
	return NULL;
}
void insertSYMTAB(string line, int address)
{
	int i;
	for(i=0;i<100;i++) if(SYMTAB[i]=="") break;
	SYMTAB[i]=line;
	SYMTAB_add[i]=address;
}

void showSYMTAB()
{
	for(int i=0;i<100;i++) cout<<SYMTAB[i]<<" "<<SYMTAB_add[i]<<endl;
}

bool isIndexed(string OPERAND)
{
	if(OPERAND[OPERAND.length()-2]==','&&OPERAND[OPERAND.length()-1]=='X') return true;
	else return false;
}

void convertToIndexed(string& hexAddress)
{
	if(hexAddress[0]+8<='9') hexAddress[0]=hexAddress[0]+8;
	else
	{
		hexAddress[0]=hexAddress[0]-2+'A';
	}
}

int extractInt(string val)
{
	int product=1,value=0,i=val.length()-1;
	while(i>=0)
	{
		value=value+(val[i]-'0')*product;
		product=product*10;
		i--;
	}
	return value;
}

int main(int argc,char* argv[])
{
	/*----------------PASS1-------------------*/
	ifstream input;
	ofstream output;
	input.open(argv[1]);
	output.open("intermidiate.tmp");

	string line,ADDRESS,LABEL,OPCODE,OPERAND,OBJCODE;
	int LOCCTR,startAddress,programLength,endAddress;
	if(input.is_open())
	{
		getline(input,line);
        splitString(line,LABEL,OPCODE,OPERAND);

        if(OPCODE=="START")
        {
        		startAddress=hexToInt(OPERAND);
        		LOCCTR=hexToInt(OPERAND);
        		output<<setfill('0')<<setw(4)<<hex<<uppercase<<LOCCTR<<"\t"<<LABEL<<"\t"<<OPCODE<<"\t"<<OPERAND<<"\n";
        		getline(input,line);
        		splitString(line,LABEL,OPCODE,OPERAND);
        }
        else LOCCTR=0;

        while(OPCODE!="END")
        {
        	if(!isCommentLine(line))
        	{
        		int currentLoc=LOCCTR;
        		if(LABEL!="") if(!findSYMTAB(LABEL)) insertSYMTAB(LABEL,LOCCTR);

        		if(findOPTAB(OPCODE))	LOCCTR=LOCCTR+3;
        		else if(OPCODE=="WORD") LOCCTR=LOCCTR+3;
        		else if(OPCODE=="RESW") LOCCTR=LOCCTR+3*extractInt(OPERAND);
        		else if(OPCODE=="RESB")	LOCCTR=LOCCTR+extractInt(OPERAND);
        		else if(OPCODE=="BYTE") LOCCTR=LOCCTR+lengthOfConst(OPERAND);

        		output<<setfill('0')<<setw(4)<<hex<<uppercase<<currentLoc<<"\t"<<LABEL<<"\t"<<OPCODE<<"\t"<<OPERAND<<"\n";
        	}
        	else output<<line<<endl;

        	getline(input,line);
			splitString(line,LABEL,OPCODE,OPERAND);
        }

        output<<setfill('0')<<setw(4)<<hex<<uppercase<<LOCCTR<<"\t"<<LABEL<<"\t"<<OPCODE<<"\t"<<OPERAND<<"\n";
        endAddress=LOCCTR;
        programLength= LOCCTR - startAddress;
        //showSYMTAB();
        input.close();
        output.close();
	}
	else throw "Either file does not exist or you do not have sufficient permissions to read the file";
	/*---------------PASS1 ends here-------------------*/

	/*--------------------PASS2------------------------*/
	input.open("intermidiate.tmp");
	output.open("listing.tmp");
	ofstream object;
	object.open("OBJFILE.O");
	string HEAD,TEXT,END;
	bool isFirst=true;
	if(input.is_open()&&object.is_open()&&output.is_open())
	{
		getline(input,line);
		splitString2(line,ADDRESS,LABEL,OPCODE,OPERAND);
		string assembled;
		if(OPCODE=="START")
		{
			OBJCODE="";
			output<<setfill('0')<<setw(4)<<hex<<uppercase<<ADDRESS<<"\t"<<LABEL<<"\t"<<OPCODE<<"\t"<<OPERAND<<"\t"<<OBJCODE<<"\n";
			getline(input,line);
		}
		/*---------------Print header record--------------*/
		cout<<"headerecord"<<endl;
		object<<"H"<<left<<setfill(' ')<<setw(6)<<LABEL<<right<<setfill('0')<<setw(6)<<hex<<uppercase<<startAddress<<right<<setfill('0')<<setw(6)<<hex<<programLength<<endl;
		int symValue;
		splitString2(line,ADDRESS,LABEL,OPCODE,OPERAND);
		TEXT="T";
		string address;
		address=intToHex(startAddress);
		padHex(address,6);
		TEXT.append(address);
		cout<<"Text record1: "<<TEXT<<endl;	
		cout<<"First Text Record: "<<TEXT<<endl;
		while(OPCODE!="END")
		{
			if(!isCommentLine(line))
			{
				bool IsIndexed=false;
				if(findOPTAB(OPCODE))
				{
					cout<<ADDRESS<<" "<<LABEL<<" "<<OPCODE<<" "<<OPERAND<<endl;
					if(isIndexed(OPERAND)) {OPERAND=OPERAND.substr(0,OPERAND.length()-2);IsIndexed=true;}
					if(OPERAND!="")
					{
						if(findSYMTAB(OPERAND)) symValue=getSYMVAL(OPERAND);
						else
						{
							symValue=0;
							throw "Undefined symbol";
						}
					}
					else symValue=0;
					assembled=getOPCODE(OPCODE);
					string hexAddress=intToHex(symValue);
					padHex(hexAddress,4);
					cout<<"new hexAddress: "<<hexAddress<<endl;
					if(IsIndexed)
					{
						convertToIndexed(hexAddress);
						OPERAND.append(",X");
					}
					assembled.append(hexAddress);
					cout<<"assembled: "<<assembled<<endl;
				}
				else if(OPCODE=="BYTE"||OPCODE=="WORD")
				{
					assembled="";
					int op;
					if(OPCODE=="WORD") 
					{
						op=extractInt(OPERAND);
						assembled=intToHex(op);
						padHex(assembled,6);
						cout<<"Assembled: "<<assembled<<endl;
					}
					if(OPCODE=="BYTE")
					{
						if(OPERAND[0]=='C')
						{
							int length=OPERAND.length()-3;
							for(int i=0;i<length;i++)
							{
								string ascii=intToHex(OPERAND[2+i]);
								assembled.append(ascii);
							}
							padHex(assembled,6);
							//cout<<"C'EOF': "<<assembled<<endl;
						}
						else if(OPERAND[0]=='X')
						{
							assembled=OPERAND.substr(2,2);
							//cout<<"X'F1': "<<assembled<<endl;
						}
					}
				}
				else if(OPCODE=="RESW"||OPCODE=="RESB") assembled="";
				if(TEXT.length()+assembled.length()>68||(OPCODE=="RESW"||OPCODE=="RESB")&&TEXT!="T")
				{
					string length=intToHex((TEXT.length()-7)/2);
					padHex(length,2);
					TEXT.insert(7,length);
					cout<<"breaking"<<endl;
					object<<TEXT<<endl;
					TEXT="T";
				}
				if(TEXT=="T"&&(OPCODE!="RESW"&&OPCODE!="RESB"))
				{
					address=ADDRESS;
					padHex(address,6);
					TEXT.append(address);
				}
				TEXT.append(assembled);
			}
			if(!isCommentLine(line)&&(OPCODE!="RESW"&&OPCODE!="RESB")) output<<setfill('0')<<setw(4)<<hex<<uppercase<<ADDRESS<<"\t"<<LABEL<<"\t"<<OPCODE<<"\t"<<OPERAND<<"\t"<<assembled<<"\n";
			else output<<line<<endl;
			getline(input,line);
			splitString2(line,ADDRESS,LABEL,OPCODE,OPERAND);
		}
		string length=intToHex((TEXT.length()-7)/2);
		padHex(length,2);
		TEXT.insert(7,length);
		object<<TEXT<<endl;
		object<<"E";
		if(OPERAND!="")
		{
			int value;
			if(findSYMTAB(OPERAND))  value=getSYMVAL(OPERAND);
			else throw "Undefined symbol";
			string hexaddress=intToHex(value);
			padHex(hexaddress,6);
			object<<hexaddress;
		}
		else
		{
			string hexaddress=intToHex(startAddress);
			padHex(hexaddress,6);
			object<<hexaddress;
			OPERAND="";
		}
		output<<"\t\t"<<OPCODE<<"\t"<<OPERAND;
	}
	else cout<<"intermidiate file is unavailable"<<endl;
}