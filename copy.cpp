#include "headerfile.h"
struct stat file,file1;
char char_array[10240],writebuff[1024];
ssize_t byte,b=0;
int main(int argc, char *argv[])
{
	vector<string> nameFile;
	clock_t t1,t2;
	int fileHandle1=0,fileHandle2=0;
	for(int i=1;i<argc;i++)
	{
		string a(argv[i]);
		nameFile.push_back(a);
	}
	int size=0;
	char dist[100]={0};
	string u=nameFile[nameFile.size()-1];
	strcpy(dist, nameFile[nameFile.size()-1].c_str());
	stat(dist,&file1);
	bool dis;
	string last1,ff="";	
	if(S_ISREG(file1.st_mode))
	{
		dis=true;
		
	}
	else if(S_ISDIR(file1.st_mode))
	{
		last1= nameFile[nameFile.size()-1];
		strcpy(dist, last1.c_str());
		dis=false;
	}
	else
	{
		if(argc>3)
		{
			last1= nameFile[nameFile.size()-1];
			strcpy(dist, last1.c_str());
			dis=false;
			mkdir(dist,0777);
		}
		else
		dis=true;
	}
	t1=clock();
	string ext="";
	for(int i=0;i<argc-2;i++)
	{
		for(int j=nameFile[i].size()-1;j>=0;j--)
		{
			if(j==0||nameFile[i][j]=='/')
			{
				if(nameFile[i][j]!='/')
				{
					ext+=nameFile[i][j];
				}
				ext+='/';
				break;
			}
			else if(nameFile[i][j]!='/')
			{
				ext+=nameFile[i][j];
			}
		}		
		reverse(ext.begin(),ext.end());
		strcpy(char_array,nameFile[i].c_str());
		fileHandle1=open(char_array,O_RDWR,0777);
		system("pwd");
		if(fileHandle1==-1)
		{
			cout<<char_array<<endl;
			cout<<"File not found!";
			return 0;
		}		
		if (fstat(fileHandle1, &file) < 0)
		{
		    int err = errno;
		    cout<<err<<endl;
		    exit(EXIT_FAILURE);
		}
		if(S_ISREG(file.st_mode))
		{
			cout<<"HI";
			if(dis==true)
			{
				fileHandle2=open(dist,O_WRONLY | O_CREAT | O_APPEND,0777);
				if(fileHandle2==-1)
				{
					cout<<"File not found!";
					return 0;
				}
				while((byte=read(fileHandle1,writebuff,1024))!=0)
				{
					write(fileHandle2,writebuff,1024);
				}
				close(fileHandle1);
				close(fileHandle2);
			}
			else if(dis==false)
			{
				string last=last1+ext;
				strcpy(dist, last.c_str());
				fileHandle1=open(char_array,O_RDWR,0666);
				if(fileHandle1==-1)
				{
					cout<<"File not found!";
					return 0;
				}
				int dirid;
				dirid=open(dist,O_WRONLY | O_CREAT | O_APPEND,0666);
				while((byte=read(fileHandle1,writebuff,1024))!=0)
				{
					write(dirid,writebuff,1024);
				}
				close(fileHandle1);
				close(dirid);
			}
				
		}
		else if(S_ISDIR(file.st_mode))
		{
			if(dis==true)
			{
				cout<<"Wrong Input";
			}
			else
			{
				char ff[100];
				DIR *dir;
				struct dirent *dep;
				string s=nameFile[i];
				strcpy(ff, s.c_str());
				if((dir=opendir(ff))==NULL)
				cout<<"NOT OPEN";
				while((dep=readdir(dir))!=NULL)
				{
					string h=dep->d_name;
					if(h!="."&&h!="..")
					{
						string r=u+"/"+h;
						char rr[100];
						char y[100];
						string f=nameFile[i]+"/"+h;
						strcpy(y, f.c_str());
						strcpy(rr, r.c_str());
						int h1=open(y,O_RDONLY);	
						int h2=open(rr,O_WRONLY | O_CREAT | O_APPEND,0666);
						while((read(h1,writebuff,1024))!=0)
						{
							write(h2,writebuff,1024);
						}
						close(h1);
						close(h2);
					}
				}
				closedir(dir);	
			}		
		}
		else
		{
			cout<<"Not Found";
		}
	ext="";
	}
		t2=clock();
		cout<<"\nTime required to copy one file to another file: "<<(((float)(t2-t1)/CLOCKS_PER_SEC)*100)<<" sec"<<endl;

return 0;
}
