#include <fcntl.h> 
#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <termios.h> 
#include <unistd.h> 
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
