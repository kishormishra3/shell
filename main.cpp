#include<bits/stdc++.h>
#include "headerfile.h"
#include <unistd.h>
char buff[1024];
using namespace std;
int main()
{
	int fd[2];
	int status;
	string com;
	if(pipe(fd)<0)
	exit(1);
	cout<<"\n\n\n\n\n\t\t******************Welcome to my shell*************************\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	while(1)
	{	
		cout<<"@ ";
		getline(cin,com);
		int p=fork();	
		if(p)
		{
			pid_t p=waitpid(-1,&status,0);
			if(WEXITSTATUS(status))
			{
				cout<<"Error\n";
			}
			else
			{
				//read(fd[0],buff,1024);
				cout<<"Done";
			}
		}
		else
		{
			int flag=check(com);
			char *d[flag];
			if(flag)
			{	
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
							strcpy(d[k], sub.c_str());
							k++;
							c=i+2;
							m=0;							
						}
					}
					m++;
				}
				d[k]=NULL;
				char *r="./copy";
				if(execv(r,d)<0)
				{
					cout<<"Fail\n";
					exit(1);
				}
				//
				//cout<<flag<<endl;
				//char a[]="Done\n";
				//write(fd[1],a,5);
			}
			else
			{
				exit(1);
			}
			exit(0);
		}
	}
return 0;
}
