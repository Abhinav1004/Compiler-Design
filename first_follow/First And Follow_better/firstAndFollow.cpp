//
//  main.cpp
//  CompilerDesignLab
//
//  Created by Shivanshu Chaudhary on 07/04/18.
//  Copyright © 2018 Shivanshu Chaudhary. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;
int num_of_productions;
vector<string> productions;
vector<char> terminals;
vector<char> nonTerminals;
vector<vector <char> > firsts;
vector<vector <char> > follows;
vector<int> flag;
int globalCount=0;    //to counter chain productions
char ttc;
char startSymbol;

int positionOfNonTerminal(char c){
    for(int i=0;i<nonTerminals.size();i++){
        if(nonTerminals[i]==c){
            return i;
        }
    }
    return -23;
}

int isInTerminal(char c){//Check if a value is a valid Terminal
    if(find(terminals.begin(),terminals.end(),c)!=terminals.end()){
        return 1;
    }
    return 0;
}


int isInNonTerminal(char c){//Check if a value is a valid NonTerminal
    if(find(nonTerminals.begin(),nonTerminals.end(),c)!=nonTerminals.end()){
        return 1;
    }
    return 0;
}

int isTerminal(char tem){//Assume Capital Letters As non terminals and small letters as terminals
    if(tem>='A' && tem<='Z'){
        return 0;
    }else{
        return 1;
    }
}

int prepareListOfCharacter(){//Prepare List Of Valid Characters
    for(int i=0;i<productions.size()-1;i++){
        string tempString=productions[i];
        int tempStringLen = tempString.length();
        for(int j=0;j<tempStringLen;j++){
            char t = tempString[j];
            if(!(t==' ')){
                if(isInNonTerminal(t)||isInTerminal(t)){
                    continue;
                }else{
                    //Check if Terminal Or Non Terminal.
                    // Add in the respective Vector
                    if(isTerminal(t)){
                        terminals.push_back(t);
                    }else{
                        nonTerminals.push_back(t);
                        flag.push_back(0);
                        vector<char> tV;
                        tV.push_back('@');
                        firsts.push_back(tV);
                        follows.push_back(tV);
                    }
                }
            }
        }
    }
    return 1;
}

int ifExists(int i,char c){
    for(int j=0;j<firsts[i].size();j++){
        if(firsts[i][j]==c){
            return 1;
        }
    }
    return 0;
}

int readProductions(){
    //Function to read the productions from the input file


    //READING BEGINS
    string fileName;
    cout<<"Enter Filename : ";
    getline(cin, fileName);
    getline(cin, fileName);
    ifstream input(fileName.c_str());
    string tempString;
    input>>num_of_productions;
    getline(input, tempString, '\n');
    while (getline(input, tempString, '\n')) {
        productions.push_back(tempString);
    }
    cout<<"DATA FROM INPUT FILE BEGINS: "<<endl;
    cout<<"Num Of Productions : "<<num_of_productions<<endl;
    for(int i=0;i<productions.size();i++){
        cout<<productions[i]<<endl;
    }
    cout<<"DATA FROM INPUT FILE ENDS: "<<endl<<endl;
    //READING ENDS


    prepareListOfCharacter();
    cout<<"\nAll The Terminals     : ";
    for(int i=0;i<terminals.size();i++){
        cout<<terminals[i]<<" ";
    }
    cout<<"\nAll The Non Terminals : ";
    for(int i=0;i<nonTerminals.size();i++){
        cout<<nonTerminals[i]<<" ";
    }
    cout<<"...";
    cout<<"\n";

    return 1;
}

int isFlagTrue(int i){
    return flag[i];
}


int firstCalcB(char c, int i){
    //TODO
    //Rectify for input.txt chain productions

    if((ttc==c)&&(globalCount!=0)){
        if(!ifExists(i,'#')){
            firsts[i].push_back('#');
        }
        return 1;
    }
    globalCount++;
    //cout<<"\ninside firstcalcb for"<<c;
    int posNonTerm = positionOfNonTerminal(c);
    //cout<<"\tPosition : "<<posNonTerm;
    if(isFlagTrue(posNonTerm)){
        int tempFlag=0;
        //Already Calculated the First
        vector<char> tempFirsts;
        tempFirsts = firsts[posNonTerm];
        for(int j=0;j<tempFirsts.size();j++){
            char tempC = tempFirsts[j];
            if(tempC=='@'){
                continue;
            }else if(tempC == '#'){
                tempFlag=1;
            }else{
                if(!ifExists(i,tempC)){
                    firsts[i].push_back(tempC);
                }
            }
        }
        if(tempFlag==1){
            return 22;
        }else{
            return 1;
        }
    }else{
        //Need To Calculate Now
        vector<string> tempProductions;
        int tempFlag3 = 0;
        for(int j=0;j<productions.size();j++){
            if(productions[j][0]==c){
                tempProductions.push_back(productions[j]);
            }
        }

        for(int j=0;j<tempProductions.size();j++){
            string tempProduction = tempProductions[j];
            if(isTerminal(tempProduction[2])){
                if(tempProduction[2]=='#'){
                    tempFlag3 = 1;
                }else{
                    if(!ifExists(i,tempProduction[2])){
                        firsts[i].push_back(tempProduction[2]);
                    }
                    
                }
            }else{
                int k=2;
                int tempFlag2=22;
                while(tempFlag2==22){
                    //cout<<"\nCalling for tempProduction["<<k<<"] = "<<tempProduction[k];
                    if(isTerminal(tempProduction[k])){
                        if(!ifExists(i,tempProduction[k])){
                            firsts[i].push_back(tempProduction[k]);
                        }
                        tempFlag2=1;
                    }
                    tempFlag2=firstCalcB(tempProduction[k++],i);
                    //cout<<"\nTempFlag2 = "<<tempFlag2<<endl;
                    if(tempFlag2==22){
                        if(k==tempProduction.length()){
                            if(!ifExists(i,'#')){
                                firsts[i].push_back('#');
                            }
                        }
                    }
                }
            }
        }
        if(tempFlag3==1){
            return 22;
        }else{
            return 1;
        }
    }
    return 1;
}


int printFirsts(){
    cout<<"NonTerminal\tFirsts\n";
    for(int i=0;i<nonTerminals.size();i++){
        vector<char> tempFirsts = firsts[i];
        cout<<nonTerminals[i]<<"\t\t";
        for(int j=0;j<tempFirsts.size()-1;j++){
            if(tempFirsts[j]=='@'){
                continue;
            }
            cout<<tempFirsts[j]<<", ";
        }
        int fin=tempFirsts.size()-1;
        if(fin>=0){
            if(tempFirsts[fin]!='@'){
                cout<<tempFirsts[fin]<<endl;
            }
        }    
    }
    return 1;
}


int exists(char c, int i){
    for(int j=0;j<follows[i].size();j++){
        if(follows[i][j]==c){
            return 1;
        }
    }
    return 0;
}


int followCalcB(char c, int i){
    
    int p = positionOfNonTerminal(c);
    if(flag[p]==1){
        
        for(int j=0;j<follows[p].size();j++){
            if(!exists(follows[p][j],i)){
                follows[i].push_back(follows[p][j]);
            }
        }
    }else{
        //cout<<"\n\nFor Character : "<<c;
    
        if(c==startSymbol){
            if(!exists('$',i)){
                //cout<<"\n\t\tAdding $ to follow";
                follows[i].push_back('$');
            }
        }

        if((ttc==c)&&(globalCount!=0)){
            return 1;
        }

        vector<string> tempProductions;
        for(int j=0;j<productions.size();j++){
            for(int k=2;k<productions[j].length();k++){
                if(productions[j][k]==c){
                    tempProductions.push_back(productions[j]);
                }
            }
        }

        
        for(int j=0;j<tempProductions.size();j++){
            string production=tempProductions[j];

            int pos=0;
            for(int k=2;k<production.length();k++){
                if(production[k]==c){
                    pos=k;
                    //cout<<"\n\t"<<c<<" Found At Position : "<<pos<<" In String : "<<production;
                    while(true){
                        char tempChar = production[pos];
                        if(pos==production.length()-1){
                            //End Of String Reached
                            if(isTerminal(tempChar)){
                                if(!exists(tempChar,i)){
                                    //cout<<"\n\t\tAdding "<<tempChar<<" to follow";
                                    follows[i].push_back(tempChar);
                                }
                            }else{
                                if(production[0]!=tempChar){
                                    ttc=production[0];
                                    globalCount++;
                                    followCalcB(production[0],i);
                                }
                            }
                            break;
                        }else if(isTerminal(production[pos+1])){
                            if(!exists(production[pos+1],i)){
                                //cout<<"\n\t\tAdding "<<production[pos+1]<<" to follow";
                                follows[i].push_back(production[pos+1]);
                            }
                            break;
                        }else{
                            int tempFlag=0;
                            vector<char> tempFirst = firsts[positionOfNonTerminal(production[pos+1])];
                            for(int l=0;l<tempFirst.size();l++){
                                char ch = tempFirst[l];
                                if(ch!='#'){
                                    if(!exists(ch,i)){
                                        //cout<<"\n\t\tAdding "<<ch<<" to follow";
                                        follows[i].push_back(ch);
                                    }
                                }else{
                                        tempFlag=1;
                                }
                            }
                            if(tempFlag==1){
                                pos++;
                            }else{
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    
    return 1;
}


int printFollows(){
    cout<<"\nNonTerminal\tFollows\n";
    for(int i=0;i<nonTerminals.size();i++){
        vector<char> tempFollows = follows[i];
        cout<<nonTerminals[i]<<"\t\t";
        for(int j=0;j<tempFollows.size()-1;j++){
            if(tempFollows[j]=='@'){
                continue;
            }
            cout<<tempFollows[j]<<", ";
        }
        int fin=tempFollows.size()-1;
        if(fin>=0){
            if(tempFollows[fin]!='@'){
                cout<<tempFollows[fin]<<endl;
            }
        }    
    }
    return 1;
}


int main(){

    cout<<"# represents epsilon"<<endl;
    cout<<"\n\nEnter The Start Symbol : ";
    cin>>startSymbol;
    //Read All The Productions
    readProductions();
    //Calculating Firsts BEGINS
    for(int i=0;i<nonTerminals.size();i++){
        //cout<<"\tFirst For Non Terminal["<<i<<"] : "<<nonTerminals[i]<<endl;
        int retVal = 0;
        ttc=nonTerminals[i];
        retVal = firstCalcB(nonTerminals[i],i);
        globalCount=0;
        if(retVal==22){
            firsts[i].push_back('#');
        }
        flag[i]=1;
    }
    //printFirsts();
    printFirsts();
    //Calculating Firsts ENDS

    //Reset Flag
    for(int i=0;i<nonTerminals.size();i++){
        flag[i]=0;
    }

    //Calculating Follows BEGINS
    for(int i=0;i<nonTerminals.size();i++){
        followCalcB(nonTerminals[i],i);
        flag[i]=1;
        globalCount=0;
    }
    printFollows();
    //Calculating Follows ENDS
    

    return 1;
}
