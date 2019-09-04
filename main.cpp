#include<bits/stdc++.h>
#include "headerfile.h"
#include <unistd.h>
using namespace std;
int main()
{
	map<string,string> env;
	bashfix(env);
	auto it=env.find("PS1");
	string promt=it->second;
	//chdir(getenv("HOME"));
	int status;
	string com;
	cout<<"\n\n\n\n\n\t\t******************Welcome to my shell*************************\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	while(1)
	{
		int fd[2];	
		if(pipe(fd)<0)
		exit(1);
		char buff[1024]={0};
		auto it=env.find("PS1");
		string promt=it->second;
		cout<<promt<<" ";
		fflush(stdin);
		getline(cin,com);
		if(com=="")
		continue;
		int p=fork();		
		if(p)
		{
			pid_t p=waitpid(-1,&status,0);
			if(WEXITSTATUS(status)==1)
			{
				cout<<"Error\n";
			}
			else if(WEXITSTATUS(status)==0)
			{
				//read(fd[0],buff,1024);
				continue;
			}
			else if(WEXITSTATUS(status)==5)
			{
				read(fd[0],buff,1024);
				chdir(buff);
				close(fd[0]);
			}
			else if(WEXITSTATUS(status)==6)
			{
				read(fd[0],buff,1024);
				string key="",val="";
				bool b=true;
				for(int i=0;buff[i]!='\0';i++)
				{
					if(buff[i]=='+')
					b=false;
					else if(b==true)
					key=key+buff[i];
					else 
					val=val+buff[i];
				}
				auto it=env.find(key);	
				if(it!=env.end())
				env.erase(it);
				env.insert(make_pair(key,val));
				close(fd[0]);
			}
		}
		else
		{
			int flag=check(com);
			if(flag==-5)
			{
				string s="";
				bool b=true;
				for(int i=0;i<com.length();i++)
				{
					if(com[i]=='|')
					{
						int fd=open("t.txt",O_CREAT|O_TRUNC|O_RDONLY|O_WRONLY,0644);
						dup2(fd,1);
						close(fd);
						if(b==true)
						{
							int y=run(s,10);
							cout<<y<<endl;
						}
						else 
						{
							s=(s+" t.txt");
							run(s,10);
						}
						s="";
						b=false;
					}
					else
					{
						s=s+com[i];
					}
				}
				s=(s+" t.txt");
				run(s,10);
				exit(1);
			}
			else if(flag>0)
			{	
				run(com,flag);
			}
			else if(flag==-2)
			{
				string str=com;
				char al[1024]={0};
				char * cstr = new char [str.length()+1];
			  	strcpy (cstr, str.c_str());
				char *p=strtok(cstr," ");
				p = std::strtok(NULL," ");
				if(p==NULL)
				{	
					auto it=env.find("HOME");
					str=(it->second);						
					strcpy (al,str.c_str());
					write(fd[1],al,100);
					close(fd[1]);			
					exit(5);
				}
				if(chdir(p)<0)
				{
					cout<<"No such dir exists!\n";
				}
				getcwd(al,100);
				write(fd[1],al,100);
				close(fd[1]);
				exit(5);
			}
			else if(flag==-1)
			{
				bool b=false;
				string c="";
				int l=com.length();
				for(int i=0;i<l;i++)
				{
					if(com[i]=='$')
					{
						b=true;
					}
					else if(b==true)
					c=c+com[i];
					else if(com[i]==' ')
					b=false;
				}
				it=env.find(c);
				if(it==env.end())
				{
					char cstr[1024]={0};
					strcpy(cstr, c.c_str());
					char *p=getenv(cstr);
					if(p==NULL)
					{
						exit(0);
					}
					cout<<p<<endl;
					exit(0);
				}
				else
				{
					cout<<it->second<<endl;
					exit(0);
				}			
			}
			else if(flag==-3)
			{
				bool b=false,k=false;
				string s="",key="",val="";
				int l=com.length();
				for(int i=0;i<l;i++)
				if(com[i]=='$'&&b==true)
				k=true;
				else if(com[i]=='=')
				b=true;
				else if(k==true)
				s+=com[i];
				else if(b==false)
				key+=com[i];
				else if(b==true)
				{
					val=val+com[i];
				}
				if(k==true)
				{
					auto it =env.find(s);
					s=it->second;
					key=key+"+"+s;
					char al[1024]={0};
					strcpy (al,key.c_str());
					write(fd[1],al,100);
					close(fd[1]);
				}
				else
				{
					char al[1024]={0};
					key=key+"+"+val;
					strcpy (al,key.c_str());
					write(fd[1],al,1024);
					close(fd[1]);
				}
				exit(6);
			}
			exit(0);
		}
	}
return 0;
}
