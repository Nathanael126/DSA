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
	int i = 1;
	for(char c : a){
		x = x + (static_cast<int>(c)*i++);
	}
	return x;
}

map<double, string> hashMap(string *a, int n){
	map<double, string> hashTable;
	for(int i; i < n; i++){
		hashTable.insert(pair<double,string>(hashFunction(a[i]),a[i]));
	}
	return hashTable;
}

void hashSearch(map<double, string> x, string a){
	double search = hashFunction(a);
	map<double, string>::iterator itr = x.find(search);
	if(itr->first >= 1){
		cout << "Found results: " << endl;
		cout << itr->first << " " << itr->second << endl;
	}
	else{
		cout<< "Not found!" << endl;
	}	
}

void printMap(map<double, string> x){
	cout << "Printing full map:" << endl;
	map<double, string>::iterator itr;
	for (itr = x.begin(); itr != x.end(); ++itr) {
        cout << itr->first << " " << itr->second << endl;
    }
}

map<double, string> createIDTable(string *a, int n){
	map<double, string> IDTable;
	for(int i; i < n; i++){
		IDTable.insert(pair<double,string>(i,a[i]));
	}
	return IDTable;
}

void linearStringSearch(map<double, string> x, string a){
	map<double, string>::iterator itr;
	for (itr = x.begin(); itr != x.end(); ++itr) {
        if(itr->second == a){
        	cout << "Found results: " << endl;
			cout << itr->first << " " << itr->second << endl;
			return;
		}
    }
    cout << "Not found!";
}

void linearIndexSearch(map<double, string> x, double a){
		map<double, string>::iterator itr;
	for (itr = x.begin(); itr != x.end(); ++itr) {
        if(itr->first == a){
        	cout << "Found results: " << endl;
			cout << itr->first << " " << itr->second << endl;
			return;
		}
    }
    cout << "Not found!";
}

void binarySearch(map<double, string> x, double a, double left, double right){
	if(right >= left){
		double middle = left + (right - 1) / 2;
		if (middle == a){
			map<double, string>::iterator itr = x.find(middle);
			cout << "Found results: " << endl;
			cout << itr->first << " " << itr->second << endl;
			return;
		}
		
		
		if(a < middle){
			binarySearch(x, a, left, middle-1);
		}
		binarySearch(x, a, middle+1, right);
		
	}
	cout << "Not found!" << endl;
	return;
}

void read(){
	ifstream in("anime.csv");

    	string line, field;

   	vector< vector<string> > animeData;  // the 2D array
    	vector<string> data;                // array of values for one line only

    	while ( getline(in,line) ){    // get next line in file
        	data.clear();
        	stringstream ss(line);

        	while (getline(ss,field,',')){  // break line into comma delimitted field {
            	data.push_back(field);  // add each field to the 1D array
        }

        animeData.push_back(data);  // add the 1D array to the 2D array
    }

    // print out what was read in

    for (size_t i=0; i<animeData.size(); ++i){
        cout << animeData[i][1] << "|"; // (separate fields by |) (and names only)
        cout << "\n";
    }
}

int main(){
	int n = 5;
	string a[n] = {"Boku no Hero Academia","Naruto","Shingeki no Kyojin","YuGiOh!","One Piece"};
	map<double, string> hashTable = hashMap(a,n);
	map<double, string> IDTable = createIDTable(a,n);
	
	printMap(hashTable);
	printMap(IDTable);
	
	hashSearch(hashMap, "Naruto");
	linearIndexSearch(IDTable, 1);
	linearStringSearch(IDTable, "Naruto");
    binarySearch(IDTable, 1, 0, n);
    
    
	return 0;
}
