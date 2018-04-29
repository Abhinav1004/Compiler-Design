//Question 1
//To check the grammar consist of only even number of b* 
#include<bits/stdc++.h>
using namespace std;
int main(){
	string inp_str;
	ifstream inp;int count = 0;
	inp.open("input.txt");
	getline(inp,inp_str);
	int len = inp_str.size();
	for(int j=0;j<len;j++){
		if(inp_str[j]=='b')
			count++;
	}
	if(count%2 == 0){
		cout<<"\nThe string is accepted by the grammar ";
	}
	else
		cout<<"\nThe string is not accepted by the grammar";
	return 0;
}