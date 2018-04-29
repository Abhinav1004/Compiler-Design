//Question 5
#include<bits/stdc++.h>
#include<iostream>
#include<string.h>
using namespace std;
int main(void)
{
	int j,k, s,v, tmp,len,count,cur, i,f[10]={0},g[10][10]={0};
	char sen[100],c;

	ifstream inp;            
	string inp_str;          
	inp.open("input.txt");  
	getline(inp,inp_str);   
 	i=int(inp_str[0])-48;//i-initial state
 						 //initialize i with 0 as in first line of input

	getline(inp,inp_str);
	len=inp_str.size();//takes the size of the set of final states 

	for(j=0;j<len;j++)
	{
		tmp=int(inp_str[j++])-48;
		f[tmp]=1;
	}//f[] stores the set of final states and mark them as 1
	//1,2,... corresponds to a,b,c... and indicates the set of final states
	getline(inp,inp_str);//reads the first line of regular grammar
	s=0;
	while(inp)
	{
	    len=inp_str.size();
		for(count=0,v=0,j=0;j<len;j++)// j iterates over the length of the line 
		{
			if(inp_str[j]=='-')	{
                        g[s][v++]=-1;j+=2;	//s-state, v-input variable g[][]- transition table
                        					//s denotes states traverse horizontally and v vertically
						}					//-1 indicates no value
			else
			{
			tmp=int(inp_str[j++])-48;
			g[s][v++]=tmp;
			}
			count++;
		}
		s++;//per line indicates a,b,c.... transition 
		getline(inp,inp_str);
	}
//unlock the below code to print the set of final states	
cout<<"\n";
	for(j=0;j<10;j++)
		cout<<f[j]<<" ";
	cout<<endl;

//unlock the below code to print the transition table
cout<<"\n";
	for(j=0;j<s;j++)
		{for(k=0;k<count;k++)
			cout<<g[j][k]<<" ";
		cout<<endl;
}
	while(1)
	{
	cout<<"Enter a sentence: ";
	cin>>sen;
	if(sen[0]=='-')	break;//cur initially starts with initial position
	for(j=0,cur=i;j<strlen(sen);j++)
	{
		tmp=int(sen[j])-97; //converted to its integer value
		if(g[cur][tmp]==-1)
		{
			cout<<"String Rejected!\n";
			break;
		}
		else
		{
			cur=g[cur][tmp];
			cout<<"\n"<<cur;//cur value is updated by the output got by the transititon table
		}
	}
	if(j==strlen(sen) && f[cur]==1)	cout<<"String Accepted!\n"; //if reached end and cur is also the final state 
	else if(j==strlen(sen))		cout<<"String Rejected!\n";//if reached end but not the final state
	}
	return 0;
}