#include<iostream>
#include<sstream>
#include<fstream>
#include<iomanip>
using namespace std;
#include"OPTABX.H"

void splitString(string line, string& LABEL, string& OPCODE, string& OPERAND)
{
	LABEL="";OPCODE="",OPERAND="";
	int count=0,prev=0;
	for(int i=0;i<=line.length();i++)
	{
		if(line[i]=='\t'||line[i]=='\0')
		{
			if(count==0) LABEL=line.substr(prev,i-prev);
			else if(count==1) OPCODE=line.substr(prev,i-prev);
			else if(count==2) OPERAND=line.substr(prev,i-prev);
			prev=i+1;
			count++;
		}
	}
}
void splitString2(string line, string& address, string& LABEL, string& OPCODE, string& OPERAND)
{
	address="";LABEL="";OPCODE="",OPERAND="";
	int count=0,prev=0;
	for(int i=0;i<=line.length();i++)
	{
		if(line[i]=='\t'||line[i]=='\0')
		{
			if(count==0) address=line.substr(prev,i-prev);
			else if(count==1) LABEL=line.substr(prev,i-prev);
			else if(count==2) OPCODE=line.substr(prev,i-prev);
			else if(count==3) OPERAND=line.substr(prev,i-prev);
			prev=i+1;
			count++;
		}
	}
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

string intToHex(int value)
{
	if(value<0)
	{
		value=4095+value+1;
	}
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
	for(int i=0;i<58;i++) if(line==OPTAB[i][0]) return true;
	return false;
}
string getOPCODE(string op)
{
	for(int i=0;i<58;i++) if(op==OPTAB[i][0]) return OPTAB[i][1];
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

bool isExtendedFormat(string& OPCODE)
{
	if(OPCODE[0]=='+')
	{
		OPCODE=OPCODE.substr(1,OPCODE.length());
		return true;
	}
	else return false;
}

int getFormat(string op)
{
	for(int i=0;i<58;i++) if(op==OPTAB[i][0]) return OPTAB[i][2][0]-'0';
	return 0;
}

bool isIndirect(string op)
{
	if(op[0]=='@') return true;
	else return false;
}

bool isImmediate(string op)
{
	if(op[0]=='#') return true;
	else return false;
}

bool isNumber(string op)
{
	if(op[0]>='0'&&op[0]<='9') return true;
	else return false;
}

string getRegValues(string reg)
{
	if(reg=="A") return "0";
	else if(reg=="X") return "1";
	else if(reg=="L") return "2";
	else if(reg=="B") return "3";
	else if(reg=="S") return "4";
	else if(reg=="T") return "5";
	else if(reg=="F") return "6";
	else if(reg=="PC") return "8";
	else if(reg=="SW") return "9";
}

void getRegisters(string op, string& r1, string& r2)
{
	for(int i=0;i<op.length();i++)
	{
		if(op[i]==',')
		{
			r1=getRegValues(op.substr(0,i));
			r2=getRegValues(op.substr(i+1,op.length()));
			return;
		}
	}
	r1=getRegValues(op);
	r2="0";
}
bool isLiteral(string op)
{
	if(op[0]=='=') return true;
	else return false;
}

void addLiteral(string literal,LITTAB& lt)
{
	lt.LTS[lt.number]=literal;
	lt.number++;
}

void displayLiteral(LITTAB lt)
{
	for(int i=0;i<lt.number;i++) cout<<lt.LTS[i]<<endl;
}

bool alreadyExistsLT(string lit, LITTAB lt)
{
	for(int i=0;i<lt.number;i++) if(lt.LTS[i]==lit) return true;
	return false;
}

bool isExpression(string op)
{
	for(int i=0;i<op.length();i++) if(op[i]=='+'||'-'||'/'||'*') return true;
	else return false;
}

int solveExpression(string op)
{
	int val=0,prev=0,temp=0;
	char prevchar=0;
	for(int i=0;i<=op.length();i++)
	{
		if(op[i]=='+'||op[i]=='-'||op[i]=='/'||op[i]=='*'||op[i]=='\0')
		{
			string sym = op.substr(prev,i-prev);
			if(findSYMTAB(sym)) temp = getSYMVAL(sym);
			else if(isNumber(sym)) temp = extractInt(sym);
			else throw string("Error: Undefined symbol ").append(sym);
			if(prevchar==0) val=temp;
			else if(prevchar=='+') val+=temp;
			else if(prevchar=='-') val-=temp;
			else if(prevchar=='*') val*=temp;
			else if(prevchar=='/') val/=temp;
			prev=i+1;
			prevchar=op[i];
		}
	}
	return val;
}

void setAbsolute(string op,bool absolute)
{
	for(int i=0;i<100;i++)
	{
		if(SYMTAB[i]==op) 
		{
			SYMTAB_abs[i]=absolute;
			return;
		}
	}
}

bool isRelative(string op)
{
	for(int i=0;i<100;i++)
	{
		if(SYMTAB[i]==op) return !SYMTAB_abs[i];
	}
}

int main(int argc,char* argv[])
{
	int lineNo=0;
	try{
		/*----------------PASS1-------------------*/
		if(argc==1)
		{
			cout<<"SIC/XE assembler"<<endl;
			cout<<"Usage: ./a.out [FILENAME]";
			throw "";
		}

		ifstream input;
		ofstream output;
		input.open(argv[1]);
		output.open("intermidiate.tmp");
		LITTAB lt;
		string line,ADDRESS,LABEL,OPCODE,OPERAND,OBJCODE;
		int LOCCTR,startAddress,programLength,endAddress;
		if(input.is_open())
		{
			getline(input,line);
	        splitString(line,LABEL,OPCODE,OPERAND);
	        lineNo++;

	        if(OPCODE=="START")
	        {
	        		startAddress=hexToInt(OPERAND);
	        		LOCCTR=hexToInt(OPERAND);
	        		output<<setfill('0')<<setw(4)<<hex<<uppercase<<LOCCTR<<"\t"<<LABEL<<"\t"<<OPCODE<<"\t"<<OPERAND<<"\n";
	        		getline(input,line);
	        		splitString(line,LABEL,OPCODE,OPERAND);
	        		lineNo++;
	        }
	        else 
	        {	
	        	LOCCTR=0;
	        	startAddress=0;
	        }

	        while(OPCODE!="END")
	        {
	        	bool isExtFormat=false;
	        	if(!isCommentLine(line))
	        	{
	        		int currentLoc=LOCCTR;
	        		if(LABEL!=""&&OPCODE!="EQU") 
	        		{
	        			if(!findSYMTAB(LABEL)) insertSYMTAB(LABEL,LOCCTR);
	        			else throw string("Error: Symbol ").append(LABEL).append(" already defined");
	        		}

	        		if(isExtendedFormat(OPCODE)) isExtFormat=true;
	        		if(isLiteral(OPERAND)) addLiteral(OPERAND,lt);

	        		if(findOPTAB(OPCODE))
	        		{
	        			if(isExtFormat) LOCCTR = LOCCTR + 4;
	        			else LOCCTR = LOCCTR + getFormat(OPCODE);

	        			if(isExtFormat) OPCODE.insert(0,"+");
	        		}
	        		else if(OPCODE=="WORD") LOCCTR = LOCCTR + 3;
	        		else if(OPCODE=="RESW") LOCCTR = LOCCTR + 3*extractInt(OPERAND);
	        		else if(OPCODE=="RESB")	LOCCTR = LOCCTR + extractInt(OPERAND);
	        		else if(OPCODE=="BYTE") LOCCTR = LOCCTR + lengthOfConst(OPERAND);
	       			else if(OPCODE=="BASE");
	       			else if(OPCODE=="LTORG")
	       			{
	       				for(int i=0;i<lt.number;i++)
	       				{
	       					string literal=lt.LTS[i];
	       					string charConst=literal.substr(1,literal.length());
	       					if(!findSYMTAB(literal)) 
	       					{
	       						insertSYMTAB(literal,LOCCTR);
	       						int length=lengthOfConst(charConst);
	       						output<<setfill('0')<<setw(4)<<hex<<uppercase<<LOCCTR<<"\t"<<literal<<"\t"<<"BYTE"<<"\t"<<charConst<<"\n";
	       						LOCCTR=LOCCTR+length;
	       					}
	       				}
	       				lt.number=0;
	       			}
	       			else if(OPCODE=="EQU")
	       			{
	       				if(isNumber(OPERAND)) insertSYMTAB(LABEL,extractInt(OPERAND));
	       				else if(OPERAND=="*") 
	       				{
	       					insertSYMTAB(LABEL,LOCCTR);
	       					setAbsolute(LABEL,false);
	       				}
	       				else if(isExpression(OPERAND))
	       				{
	    					insertSYMTAB(LABEL,solveExpression(OPERAND));
	    					if(findSYMTAB(OPERAND)) setAbsolute(LABEL,false);
	       					else setAbsolute(LABEL,true);
	    				}
	       			}
					else throw string("Error: Unidentified symbol ").append(OPCODE).append(" in opcode field");

	        		if(OPCODE!="LTORG")output<<setfill('0')<<setw(4)<<hex<<uppercase<<currentLoc<<"\t"<<LABEL<<"\t"<<OPCODE<<"\t"<<OPERAND<<"\n";
	        	}
	        	else output<<line<<endl;

	        	getline(input,line);
				splitString(line,LABEL,OPCODE,OPERAND);
				lineNo++;
	        }
	        for(int i=0;i<lt.number;i++)
	       	{
	       		string literal=lt.LTS[i];
	       		string charConst=literal.substr(1,literal.length());
	       		if(!findSYMTAB(literal))
	       		{
	       			insertSYMTAB(literal,LOCCTR);
	       			int length=lengthOfConst(charConst);
	       			output<<setfill('0')<<setw(4)<<hex<<uppercase<<LOCCTR<<"\t"<<literal<<"\t"<<"BYTE"<<"\t"<<charConst<<"\n";
	       			LOCCTR=LOCCTR+length;
	       		}
	       	}
	       	lt.number=0;
	        output<<setfill('0')<<setw(4)<<hex<<uppercase<<LOCCTR<<"\t"<<LABEL<<"\t"<<OPCODE<<"\t"<<OPERAND<<"\n";
	        endAddress=LOCCTR;
	        programLength= LOCCTR - startAddress;
	        //showSYMTAB();
	        input.close();
	        output.close();
		}
		else 
		{
			cout<<"Usage ./a.out [FILENAME]"<<endl;
			throw "Either file does not exist or you do not have sufficient permissions to read the file";
		}
		/*---------------------------------------------</PASS1>--------------------------------------------------*/

		/*----------------------------------------------<PASS2>--------------------------------------------------*/
		input.open("intermidiate.tmp");
		output.open("listing.tmp");
		ofstream object;
		object.open("OBJFILE.O");
		string HEAD,TEXT,END,MODIF;
		bool isFirst=true,isBaseSet=false;
		int base=0;
		lineNo=0;
		if(input.is_open()&&object.is_open()&&output.is_open())
		{
			getline(input,line);
			splitString2(line,ADDRESS,LABEL,OPCODE,OPERAND);
			lineNo++;
			string assembled;
			if(OPCODE=="START")
			{
				OBJCODE="";
				output<<setfill('0')<<setw(4)<<hex<<uppercase<<ADDRESS<<"\t"<<LABEL<<"\t"<<OPCODE<<"\t"<<OPERAND<<"\t"<<OBJCODE<<"\n";
				getline(input,line);
				lineNo++;
			}
			object<<"H"<<left<<setfill(' ')<<setw(6)<<LABEL<<right<<setfill('0')<<setw(6)<<hex<<uppercase<<startAddress<<right<<setfill('0')<<setw(6)<<hex<<programLength<<endl;
			splitString2(line,ADDRESS,LABEL,OPCODE,OPERAND);
			TEXT="T";
			string address;
			address=intToHex(startAddress);
			padHex(address,6);
			TEXT.append(address);
			while(OPCODE!="END")
			{
				if(!isCommentLine(line))
				{
					cout<<ADDRESS<<"\t"<<LABEL<<"\t"<<OPCODE<<"\t"<<OPERAND<<endl;
					bool IsIndexed=false,IsImmediate=false,IsIndirect=false,isExtFormat=false;
					if(isExtendedFormat(OPCODE))
					{
						isExtFormat=true;
					}
					if(findOPTAB(OPCODE))
					{
						int format=getFormat(OPCODE);
						/*--------------------------<FORMAT 3>--------------------------------------*/
						if(format==3)
						{
							int symval;
							assembled=getOPCODE(OPCODE);
							if(isIndexed(OPERAND))
							{
								OPERAND=OPERAND.substr(0,OPERAND.length()-2);
								IsIndexed=true;
							}
							if(isImmediate(OPERAND))
							{
								OPERAND=OPERAND.substr(1,OPERAND.length());
								IsImmediate=true;
								assembled[1] = assembled[1]+1;
							}
							else if(isIndirect(OPERAND))
							{
								OPERAND=OPERAND.substr(1,OPERAND.length());
								IsIndirect=true;
								if(assembled[1]!='8') assembled[1] = assembled[1]+2;
								else assembled[1] = 'A';
							}
							else
							{
								if(assembled[1]!='8') assembled[1]=assembled[1]+3;
								else assembled[1]='B';
							}

							if(!isExtFormat)
							{
								if(findSYMTAB(OPERAND))
								{
									int current=hexToInt(ADDRESS)+3;
									int operand=getSYMVAL(OPERAND);
									if(operand-current<=2047&&operand-current>=-2048)
									{
										symval=operand-current;
										string symvalue = intToHex(symval);
										padHex(symvalue,3);
										if(IsIndexed) assembled.append("A");
										else assembled.append("2");
										assembled.append(symvalue);
									}
									else if(isBaseSet&&operand-base<=4095&&operand-base>=0)
									{
										symval=operand-base;
										string symvalue = intToHex(symval);
										padHex(symvalue,3);
										if(IsIndexed) assembled.append("C");
										else assembled.append("4");
										assembled.append(symvalue);
									}
									else if(OPERAND=="") assembled.append("0000");

									else throw string("Error: Cannot assemble operand is out of range, use extended format");
								}
								else if(IsImmediate&&isNumber(OPERAND))
								{
									symval=extractInt(OPERAND);
									string symvalue = intToHex(symval);
									padHex(symvalue,4);
									assembled.append(symvalue);
								}
								else throw string("Error: Undefined symbol ").append(OPERAND);				
							}			
							else
							{
								if(findSYMTAB(OPERAND))
								{
									symval=getSYMVAL(OPERAND);
									string symvalue = intToHex(symval);
									padHex(symvalue,5);
									assembled.append("1").append(symvalue);
									int temp=hexToInt(ADDRESS);
									temp++;
									string newAddress=intToHex(temp);
									padHex(newAddress,6);
									if(isRelative(OPERAND)) MODIF.append("M").append(newAddress).append("05").append("\n");
								}
								else if(IsImmediate&&isNumber(OPERAND))
								{
									symval=extractInt(OPERAND);
									string symvalue = intToHex(symval);
									padHex(symvalue,5);
									assembled.append("1").append(symvalue);
								}
							}
							if(IsIndexed) OPERAND.append(",X");
							if(isExtFormat) OPCODE.insert(0,"+");
							if(IsImmediate) OPERAND.insert(0,"#");
							else if(IsIndirect) OPERAND.insert(0,"@");
						}

						//Code for format 1
						else if(format==1) assembled=getOPCODE(OPCODE);
						/*--------------------------</FORMAT1>--------------------------------------*/

						/*--------------------------<FORMAT2>--------------------------------------*/
						else if(format==2)
						{
							assembled=getOPCODE(OPCODE);
							string reg1,reg2;
							getRegisters(OPERAND,reg1,reg2);
							assembled.append(reg1).append(reg2);
						}
						/*--------------------------</FORMAT2>--------------------------------------*/
					}

					//if opcode is assembler directive
					else if(OPCODE=="BYTE"||OPCODE=="WORD")
					{
						assembled="";
						if(OPCODE=="WORD") 
						{
							int op;
							op=extractInt(OPERAND);
							assembled=intToHex(op);
							padHex(assembled,6);
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
							}
							else if(OPERAND[0]=='X')
							{
								assembled=OPERAND.substr(2,2);
							}
						}
					}
					else if(OPCODE=="RESW"||OPCODE=="RESB") assembled="";
					else if(OPCODE=="BASE")
					{
						isBaseSet=true;
						base=getSYMVAL(OPERAND);
						assembled="";
					}
					else if(OPCODE=="NOBASE")
					{
						isBaseSet=false;
						base=0;
						assembled="";
					}
					else if(OPCODE=="EQU") intToHex(getSYMVAL(LABEL));

					//generate new text record
					if(TEXT.length()+assembled.length()>68||(OPCODE=="RESW"||OPCODE=="RESB")&&TEXT!="T")
					{
						string length=intToHex((TEXT.length()-7)/2);
						padHex(length,2);
						TEXT.insert(7,length);
						object<<TEXT<<endl;
						TEXT="T";
					}

					//append assembled instruction to current text record
					if(TEXT=="T"&&(OPCODE!="RESW"&&OPCODE!="RESB"))
					{
						address=ADDRESS;
						padHex(address,6);
						TEXT.append(address);
					}
					TEXT.append(assembled);
				}

				//write to listing file
				if(!isCommentLine(line)&&(OPCODE!="RESW"&&OPCODE!="RESB")) output<<setfill('0')<<setw(4)<<hex<<uppercase<<ADDRESS<<"\t"<<LABEL<<"\t"<<OPCODE<<"\t"<<OPERAND<<"\t"<<assembled<<"\n";
				else output<<line<<endl;
				getline(input,line);
				splitString2(line,ADDRESS,LABEL,OPCODE,OPERAND);
				lineNo++;
			}

			//write last text record
			if(TEXT!="T")
			{
				string length=intToHex((TEXT.length()-7)/2);
				padHex(length,2);
				TEXT.insert(7,length);
				object<<TEXT<<endl;
			}

			//write modification record
			object<<MODIF;

			//write end record
			object<<"E";
			if(OPERAND!="")
			{
				int value;
				if(findSYMTAB(OPERAND))  value=getSYMVAL(OPERAND);
				else throw string("Undefined symbol ").append(OPERAND);
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

			//write end record into listing file
			output<<"\t\t"<<OPCODE<<"\t"<<OPERAND;
			cout<<"---------------------------------------"<<endl;
			cout<<"assembled "<<argv[1]<<" succesfully"<<endl;
			cout<<"---------------------------------------"<<endl;
		}
		else throw "Could not open file for writing";
	}
	/*----------------------------------------------</PASS2>-------------------------------------------------*/
	catch(std::string e)
	{
		cout<<e<<" on line number "<<lineNo<<endl;
	}
	catch(const char* e)
	{
		cout<<e<<endl;
	}
}