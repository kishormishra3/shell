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
	int pid=getpgrp();
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
		bool t=true;
		for(int i=0;i<com.length();i++)
			{
				if(com[i]=='&')
				{
					t=false;
				}
			}
		int p=fork();		
		if(p)
		{
			if(t==true){
			pid_t p=waitpid(0,&status,0);

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
			}else
			{
				read(fd[0],buff,1024);
				cout<<buff<<endl;
				close(fd[0]);
			}
		}
		else
		{
			for(int i=0;i<com.length();i++)
			{
				if(com[i]=='&')
				{
					if(fork()>0)
					exit(0);
					string s=to_string(getpid());
					setpgid(0,1);
					char al[10]={0};
					strcpy (al,s.c_str());
					write(fd[1],al,100);
					close(fd[1]);					
				}
			}
			int flag=check(com);
			if(flag==-5)
			{
				string s="";
				bool b=true;
				for(int i=0;i<com.length();i++)
				{
					if(com[i]=='|')
					{
						if(b==true)
						{
							if(fork()==0)
							run(s,1);
							else
							wait(NULL);
						}
						else 
						{
							if(fork()==0)
							run(s,2);
							else
							wait(NULL);
						}
						s="";
						b=false;
					}
					else
					{
						s=s+com[i];
						
					}
				}
				if(fork()==0)
				run(s,3);
				else
				wait(NULL);
			}
			else if(flag>0)
			{	
				char *d[flag];
				bool first=false;
				string command="";
				int l=com.length(),c=0,m=1,k=0;
				for(int i=0;i<l;i++)
				{
					if(com[i]!=32)
					{
						if(com[i+1]==32||com[i+1]=='\0')
						{	
							char dist[1024]={0};
							string sub=com.substr(c,m);
							d[k]=new char[sub.length()];
							if(!first)
							{
								command=sub;
								first=true;
							}
							strcpy(d[k], sub.c_str());
							k++;
							c=i+2;
							m=-1;							
						}
					}
				m++;
				}
				d[k]=NULL;
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
				for(int i=0;i<k;i++)
				delete d[i];
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
			else if(flag==-6)
			{
				string s="";
				bool b=false;
				for(int i=0;i<com.length();i++)
				{
					if(com[i]==' ')
					b=true;
					else if(b==true)
					s+=com[i];
				}
				int x=stoi(s);
				setpgid(x,pid);
				tcsetpgrp(0,pid);
			}
			exit(0);
		}
	}
return 0;
}
