#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <vector>
#include <iterator>
#include <map>
#include <string>
using namespace std;

double hashFunction(string a){
	double x = 0;
	for(char c : a){
		x = x + static_cast<int>(c);
	}
	x = x*x;
	return x;
}

map<double, string> hashMap(string *a, int n){
	map<double, string> hashTable;
	for(int i; i < n; i++){
		hashTable.insert(pair<double,string>(hashFunction(a[i]),a[i]));
	}
	return hashTable;
}

void read(){
	fstream df;
	df.open("anime.csv", ios::in);
	vector<string> row;
	string line, word, temp;
	
	while (df>>temp){
		row.clear();
		getline(df, line);
		stringstream s(line);
		cout << line << endl;
		
//		while(getline(s, word, ',')){
//			row.push_back(word);
//		};
//		cout << row[0] << endl;
	};
	df.close();
}

int main(){
	int n = 5;
	string a[n] = {"Boku no Hero Academia","Naruto","Shingeki no Kyojin","YuGiOh!","One Piece"};
	map<double, string> hashTable = hashMap(a,n);
	map<double, string>::iterator itr;
	for (itr = hashTable.begin(); itr != hashTable.end(); ++itr) {
        cout << '\t' << itr->first
             << '\t' << itr->second << '\n';
    }
    cout << endl;
	return 0;
}
