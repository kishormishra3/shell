#include<bits/stdc++.h>
#include "headerfile.h"
#include <unistd.h>
using namespace std;
void handle(int sig)
{
}
int main()
{
	map<string,string> env;
	map<string,string> ali;
	bashfix(env);
	auto it=env.find("PS1");
	string promt=it->second;
	//chdir(getenv("HOME"));
	int status=0;
	string com;
	int pid=getpgrp();
	cout<<"\n\n\n\n\n\t\t******************Welcome to my shell*************************\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	while(1)
	{
		string s1="",file="";
		int fd[2];	
		if(pipe(fd)<0)
		exit(1);
		char buff[1024]={0};
		auto it=env.find("PS1");
		string promt=it->second;
		cout<<promt<<" ";
		getline(cin,com);
		if(com=="")
		continue;
		bool t=true,nn=true,nnn=true;
		for(int i=0;i<com.length();i++)
		if(com[i]=='&')
		{
				t=false;
		}
		for(int i=0;i<com.length();i++)
		{
			
			
			if(com[i]=='>'&&com[i+1]=='>')
			{
				i=i+2;
				nnn=false;
				while(i<com.length())
				{
					if(com[i]!=32)
					{
						file+=com[i];
					}
				i++;
				}
			}
			else if(com[i]=='>')
			{
				i++;
				nn=false;
				while(i<com.length())
				{
					if(com[i]!=32)
					{
						file+=com[i];
					}
				i++;
				}
			}
			else
			{	
				s1=s1+com[i];
			}
		}
		com=s1;
		if(nnn==false)
		nn=false;
		int p=fork();
		if(p)
		{
			if(t==true)
			{
				pid_t p=waitpid(-1,&status,0);

				if(WEXITSTATUS(status)==1)
				{
					cout<<"Error\n";
				}
				else if(WEXITSTATUS(status)==0)
				{
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
				else if(WEXITSTATUS(status)==7)
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
					auto it=ali.find(key);	
					if(it!=ali.end())
					ali.erase(it);
					ali.insert(make_pair(key,val));
					close(fd[0]);
				}
			}
			else
			{
				read(fd[0],buff,1024);
				cout<<buff<<endl;
				close(fd[0]);
				t=true;
			}
		}
		else
		{
			for(int i=0;i<com.length();i++)
			{
				if(com[i]=='&')
				{
					string s=to_string(getpid());
					setpgid(0,1);
					char al[10]={0};
					strcpy (al,s.c_str());
					write(fd[1],al,100);
					close(fd[1]);					
				}
			}
			solve(com,ali);
			int flag=check(com,ali);
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
						char c;
						int fd=open("t.txt",O_RDWR,0644);
						int f1=open("temp.txt",O_RDWR|O_CREAT|O_TRUNC,0644);
						while(read(fd,&c,1)!=0)
						write(f1,&c,1);
						close(f1);
						close(fd);
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
								cout<<sub<<endl;							
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
				if(nn==false)
				{				
					int fd;
					char *fi=new char[file.length()];
					strcpy(fi, file.c_str());
					if(nnn=false)
					{
						fd=open(fi,O_CREAT|O_APPEND,0644);					
					}
					else
						fd=open(fi,O_RDWR|O_CREAT,0644);
					while (p!=0)
					{
						if(signal(SIGINT,handle)==SIG_ERR);
						if(count==10)
						{
							cout<<command<<" : command not found\n";
							exit(1);
						}
						p = std::strtok(NULL,":");
						string s(p);
						s=s+"/"+command;
						char al[1024]={0};
						strcpy(al, s.c_str());
						dup2(fd,1);
						if(execv(al,d)!=-1)
						{
							break;
						}
						count++;
					}
				close(fd);
				}
				else
				{
					while (p!=0)
					{
						if(count==10)
						{
							cout<<command<<" : command not found\n";
							exit(1);
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
				bool b=false,r=false,rr=false;
				string c="";
				int l=com.length();
				for(int i=0;i<l;i++)
				{
					if(com[i]=='$'&&com[i+1]=='$')
					{
						r=true;
					}
					if(com[i]=='$'&&com[i+1]=='?')
					{
						rr=true;
					}
					if(com[i]=='$')
					{
						b=true;
					}
					else if(b==true)
					c=c+com[i];
					else if(com[i]==' ')
					b=false;
				}
				if(rr==true)
				{
					cout<<status<<endl;
					exit(0);
				}
				if(r==true)
				{
					cout<<getppid()<<endl;
					exit(0);
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
				exit(8);
			}
			else if(flag==-7)
			{
				string s="",key="",val="";
				int b=1;
				for(int i=0;i<com.length();i++)
				{
					if(b==1&&(com[i]==' '))
						b++;
					else if(b==2&&com[i]=='=')
					b++;
					else if(b==2&&com[i]!='"'&&com[i]!=39)
					{
						key+=com[i];	
					}
					else if(b>2&&com[i]!='"'&&com[i]!=39)
					{
						val+=com[i];	
					}
					
				}
				key=key+"+"+val;
				char al[1024]={0};
				strcpy (al,key.c_str());
				write(fd[1],al,1024);
				close(fd[1]);
				exit(7);
			}
			exit(0);
		}
	}
return 0;
}
