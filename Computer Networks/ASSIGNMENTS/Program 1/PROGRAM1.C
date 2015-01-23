//FRAME CONSTRUCTION

#include<iostream.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<string.h>
#include<fstream.h>

#define N 64
#define DLE 16
#define STX 2
#define ETX 3

void check(char*);

char *str;
char *data;			//Final data retrieved from Output File
char* fram=new char[N+7];
int sqno=1,x=0,d=0;
void error(int,int,char*);

//Size of File
int size()
{
ofstream outf;
outf.open("test.txt",ios::app);
outf.seekp(0,ios::end);
int c=outf.tellp();
outf.close();
return c;

}


//Frame Setup
void setup(char* fram)
{       int i;

	str[0]=DLE; str[1]=STX; str[2]=char(sqno);
	sqno++;
	for(i=0;i<=N+2;i++)
		str[3+i]=fram[i];

	unsigned int a,b;
	a=fram[0];
	for(int j=1;j<strlen(fram);j++)
		a=a^fram[j];			    //Modulo 2 Arithmetic

	if(int(a)==0) str[i++]='N';
	else if(int(a)==8) str[i++]='B';
	else if(int(a)==9) str[i++]='T';
	else if(int(a)==10) str[i++]='L';
	else if(int(a)==11) str[i++]='V';
	else if(int(a)==12) str[i++]='F';
	else if(int(a)==13) str[i++]='C';
	else str[i++]=a;
				    //Taking Care of Backspace
	str[i++]=DLE; str[i++]=ETX;
	str[i]='\0';

	for(int k=0;k<N+7;k++)
		fram[k]=str[k];
}


int main(int argc, char* argv[])
{
	clrscr();
	getch();

	if(argc!=3)
	{
	 cout<<"Incorrect number of arguments!!!";
	 exit(1);
	}

	if(argv[1][0]=='-' && argv[1][1]=='p')
	     check(argv[2]);

	if(argv[1][0]=='-' && argv[1][1]=='n') {

	int check=0,sz=size();

	cout<<"\nFile Size = "<<sz<<endl<<endl;

	ifstream fin("test.txt");
	cout<<"\nFILE CONTENTS:\n";

	ofstream fout;
	fout.open((strcat(argv[2],".output")),ios::out);


//Writing Frames to File
	int fno=1,i;

	while(1)
	{
		if(!fin.eof())
		{
			for(i=0;i<N+6;i++)
				fram[i]='\0';

			fin.getline(fram,N+1);
			cout<<"\n\nFRAME NO. "<<fno++<<":";

			for(i=0;i<N;i++)
			{
				check=fram[i];
				if(fram[i]!='\0')
				{	//cout<<"\n"<<fram[i]<<" --> "<<check;
					d++;
				}
				else
				{	//cout<<"\nNULL --> 0";
					fram[i]='*';
				}
			}

			setup(fram);
			cout<<"\nFrame to be written: "<<fram;
			fout<<fram;

		}
		else if(fin.eof())
		{
			cout<<"\n\n\t\tFrames Successfully Constructed";
			break;
		}
	}

	fout.close();
	fin.close();

	}
	else
	{
	     cout<<"Incorrect number of arguments!!!";
	     exit(1);
	}

	getch();
	return 0;
}



//Reading Written Frame File For Verification
void check(char *filename)
{
	cout<<filename;

	ifstream fin;
	fin.open((strcat(filename,".output")),ios::in);
	fin.seekg(0,ios::beg);

	int fno=0;
	int errno=0;

	cout<<"\nOriginal Data: "<<endl<<endl;

	while(1)
	{
	if(!fin.eof())
	{    fno++;

	for(int i=0;i<N+7;i++)
		fram[i]='\0';

	fin.getline(fram,N+7);

	if(fram[0]!=DLE) break;
	cout<<"\n\nFRAME NO: "<<fno;
	cout<<"\nFrame: "<<fram<<endl<<endl;

	if(fram[0]!=DLE || fram[3+N+1]!=DLE)
		{ error(fno,errno,"No DLE Flag"); errno++; }

	if(fram[1]!=STX)
		{ error(fno,errno,"No Start Text Flag"); errno++; }

	if(fram[3+N+2]!=ETX)
		{ error(fno,errno,"No End Text Flag"); errno++; }

	if(fram[2]!=char(fno))
		{ error(fno,errno,"Sequence No. Error"); errno++; }

	unsigned int a,b;
	a=fram[3];
	for(int j=1;j<N;j++)
		a=a^fram[3+j];	     //Modulo 2 Arithmetic

	if(a==0) a=78;              //78=ASCII('N')
	else if(a==8) a=66;         //66=ASCII('B')
	else if(a==9) a=84;         //84=ASCII('T')
	else if(a==10) a=76;        //76=ASCII('L')
	else if(a==11) a=86;	    //86=ASCII('V')
	else if(a==12) a=70;        //70=ASCII('F')
	else if(a==13) a=67;        //67=ASCII('C')

	if(fram[3+N]!=char(a))
		{ error(fno,errno,"Checksum Error"); errno++; }

	//Output Data
	if(!errno)
	{
		for(int k=3;k<N+3;)
		{
			if(fram[k]!='*')   {
				cout<<fram[k];
				k++; 	   }
			else k++;
		}

	}

	}
	else if(fin.eof()) break;
	}

	if(!errno)
	{	cout<<"\n\n\t\tFrames Successfully Verified";

	}

	getch();
	//fin.close();
}


void error(int f,int e,char* msg)
{                              cout<<"error()";
	cout<<endl<<msg<<endl;
	ofstream fout;
	fout.open("error.txt", ios::out | ios::app);
	char *s=" --- ";
	fout<<f;
	fout<<s;
	fout<<e; e++;
	fout<<s;
	fout<<msg;
	fout<<"\n";

	fout.close();
}
