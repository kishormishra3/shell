using namespace std;
int check(string str)
{
	int l=str.length(),c=0;
	for(int i=0;i<l;i++)
	{
		if(str[i]!=32)
		{
			if(str[i+1]==32||str[i+1]=='\0')
			c++;
		}
	}
	return c;
}

