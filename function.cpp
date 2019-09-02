#include <fcntl.h> 
#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <termios.h> 
#include <unistd.h> 
#include<map>
using namespace std;
int check(string str)
{
	int l=str.length(),c=0;
	char * cstr = new char [str.length()+1];
  	strcpy (cstr, str.c_str());
	char *p=strtok(cstr," ");
	string s(p);
	if(s=="cd")
	return -2;
	for(int i=0;i<l;i++)
	{
		if(str[i]=='$')
		return -1;
		else if(str[i]=='=')
		return -3;
		if(str[i]!=32)
		{
			if(str[i+1]==32||str[i+1]=='\0')
			c++;
		}
	}
	return c;
}
int kbhit(void) 
{ 
    struct termios oldt, newt; 
    int ch; 
    int oldf; 
  
    tcgetattr(STDIN_FILENO, &oldt); 
    newt = oldt; 
    newt.c_lflag &= ~(ICANON | ECHO); 
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); 
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0); 
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK); 
  
    ch = getchar(); 
  
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); 
    fcntl(STDIN_FILENO, F_SETFL, oldf); 
  
    if (ch != EOF) { 
        ungetc(ch, stdin); 
        return 1; 
    } 
  
    return 0; 
}
void bashfix(map<string,string> &m)
{
	string str="/home/kishor/Desktop/TASK/shell/.brc";
	char p[1024]={0};	
	strcpy (p, str.c_str());
	int h=open(p,O_RDONLY);
	if(h==-1)
	{
		cout<<".brc not open\n";	
	}	
	int count=0;
	char c;
	string key="",val="";
	while((read(h,&c,1))!=0)
	{
		if(c=='=')
		{
			count=1;
		}
		else if(c=='\n')
		{
			m.insert(make_pair(key,val));
			key="";
			val="";
			count=0;
		}
		else if(count==0)
		{
			key=key+c;
		}
		else if(count==1)
		{
			val=val+c;
		}		
	}
	close(h);
}
string setVal(string c,map<string,string> &ma)
{
	string key="",val="";
	bool b=true;
	for(int i=0;i<c.length();i++)
	{
		if(c[i]!=32)
		{
			if(c[i]=='=')
			b=false;
			else if(b==true&&c[i]!='"')
			{
				key=key+c[i];
			}
			else if(b==false&&c[i]!='"')
			{
				val=val+c[i];
			}
		}
	}
	auto it=ma.find(key);
	ma.erase(it);
	ma.insert(make_pair(key,val));
	return key;
}




















 
