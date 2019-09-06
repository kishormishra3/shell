#include <stdlib.h> 
#include <termios.h> 
#include <sys/fsuid.h>
#include <fcntl.h> 
#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <termios.h> 
#include <unistd.h> 
#include<map>
using namespace std;
void solve(string &com,map<string,string> ali)
{
	stringstream str(com);
	string s="",word;
	int c=0;
	while(str >> word)
	{
		auto it=ali.find(word);
		if(it!=ali.end()&&c==0)
		{
			s=s+(it->second);
			c++;
		}
		else if((it!=ali.end()))
		{
			s=s+" "+(it->second);
		}
		else if(c==0)
		{
			s=s+word;
			c++;
		}
		else
		{
			s=s+" "+word;
		}
	}
	com=s;
}
void run(string com,int flag)
{
	stringstream s(com);
	char *d[1024];
	string word;
	int i=0;	
	if(flag!=3)
	{
		int fd=open("t.txt",O_RDWR|O_CREAT|O_TRUNC,0644);
		dup2(fd,1);
		close(fd);
	}
	while(s >> word)
	{
		d[i]=new char[word.length()];
		strcpy (d[i],word.c_str());		
		i++;	
	}
	if(flag!=1)
	{
		word="temp.txt";
		d[i]=new char[word.length()];
		strcpy (d[i],word.c_str());
		i++;
	}
	d[i]=NULL;
	string command=d[0];
	char * cstr= getenv("PATH");
	char * p = std::strtok (cstr,":");
	int count=0;
	while (p!=0)
	{
		if(count==10)
		{
			cout<<command<<" : command not found\n";
			exit(0);
		}
		p = std::strtok(NULL,":");
		string s(p);
		s=s+"/"+command;
		char al[1024]={0};
		strcpy(al, s.c_str());
		if(execv(al,d)!=-1)
		{
			break;
		}
		count++;
	}
	close(1);
	exit(0);
}
int check(string &str,map<string,string> ali)
{
	string a="";
	int l=str.length(),c=0;
	char * cstr = new char [str.length()+1];
  	strcpy (cstr, str.c_str());
	char *p=strtok(cstr," ");
	string s(p);
	bool b=false;
	for(int i=0;i<l;i++)
	{
		if(str[i]!='"'&&str[i]!=39&&str[i]!='&')
		a=a+str[i];
		if(str[i]=='|')
		b=true; 
	}
	str=a;	
	auto it = ali.find(s);
	if(it!=ali.end()&&(it->first=="cd"))
	{
		return -2;
	}
	else if(s=="cd")
	return -2;
	if(it!=ali.end()&&(it->first=="alias"))
	return -7;
	else if(s=="alias")
	return -7;
	if(s=="fg")
	return -6;
	if(b==true)
	return -5;
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
	str=a;
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
