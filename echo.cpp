#include<bits/stdc++.h>
using namespace std;

void echo(char input[4096]){
    int i=0;
    int j=4095;
    while(i<4095){
        if(input[i]=='"') break;
        i++;
    }
    while(j>=0){
        if(input[j]=='"') break;
        j--;
    }
    for(int k=i; k<=j;k++)
   {  cout<<input[k]; }
    cout<<"\n"; 
}