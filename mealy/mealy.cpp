//Question 2 part of mealy
#include<iostream>
#include<bits/stdc++.h>
#include<string.h>
using namespace std;
void ParseText(int ns[][2],int op[][2],int* count){
	ifstream inp;string inp_str;
	inp.open("input_mealy.txt");
	getline(inp,inp_str);
	int len;int i,j,cs=0;
	getline(inp,inp_str);
	while(inp){
		len = inp_str.size();
		for(j=3,i=0;j<len;i++,j++){
			ns[cs][i] = int(inp_str[++j])-48;
			j+=2;
			if(inp_str[j]=='-')
				{op[cs][i]=-1;j+=2;}
			else{
				op[cs][i] = int(inp_str[j++])-48;
			}
		}
		getline(inp,inp_str);
		cs++;
	}
	*count= cs;
}
void PrintArray(int ar[][2],int m){
	for(int i=0;i<m;i++){
		for(int j=0;j<=1;j++){
			cout<<ar[i][j]<<" ";
		}
		cout<<"\n";
	}
}
void NextState(int ns[][2],int op[][2]){
	int cs=0;char sentence[20];int j,i;char ch='y';
	while(1){
		cout<<"\nEnter the sentence";
		cin>>sentence;
		if(sentence[0]=='-'){
			break;
		}
		for(j=0,cs=0;j<strlen(sentence);j++){
			i=int(sentence[j])-48;
			if(op[cs][i]==-1)
				cout<<"\nCan't go further ";
			else
			{
				cout<<"\nThe next state is "<<ns[cs][i]<<"and has output "<<op[cs][i]<<"\n";
				cs=ns[cs][i];
			}

		}
		cout<<"\nDo you want to enter again";
		cin>>ch;
		if(ch=='n'||ch=='N')
			break;
		}	
}
int main(){
	int ns[5][2]={0};int op[5][2]={0};
	int count;
	ParseText(ns,op,&count);
	cout<<"\nOutput table is \n"; 
	PrintArray(op,count);
	cout<<"\nNext state table \n";
	PrintArray(ns,count);
	NextState(ns,op);	
	return 0;
}