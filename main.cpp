#include<bits/stdc++.h>
#include "headerfile.h"
#include <unistd.h>
using namespace std;
int main()
{
	chdir(getenv("HOME"));
	int status;
	string com;
	cout<<"\n\n\n\n\n\t\t******************Welcome to my shell*************************\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	while(1)
	{
		int fd[2];	
		if(pipe(fd)<0)
		exit(1);
		char buff[1024]={0};
		cout<<"@ ";
		getline(cin,com);
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
		}
		else
		{
			int flag=check(com);
			char *d[flag];
			if(flag>0)
			{	
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
							//cout<<sub<<sub.length()<<endl;
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
				while (p!=0)
				{
					p = std::strtok(NULL,":");
					string s(p);
					s=s+"/"+command;
					char al[1024];
					strcpy(al, s.c_str());
					if(execv(al,d)!=-1)
					break;
				}
				//
				//cout<<flag<<endl;
				//char a[]="Done\n";
			}
			else if(flag==-2)
			{
				string str=com;
				char al[1024]={0};
				char * cstr = new char [str.length()+1];
			  	strcpy (cstr, str.c_str());
				char *p=strtok(cstr," ");
				p = std::strtok(NULL," ");
				if(chdir(p)<0)
				{
					cout<<"No such dir exists!\n";
				}
				getcwd(al,100);
				write(fd[1],al,100);
				close(fd[1]);
				exit(5);
			}
			exit(0);
		}
	}
return 0;
}
