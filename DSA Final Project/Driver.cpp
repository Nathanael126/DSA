#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <vector>
#include <iterator>
#include <map>
#include <string>
#include <chrono>
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
		cout << "ID \t Title" << endl; 
		cout << itr->first << "\t" << itr->second << endl;
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
        	cout << "ID \t Title" << endl; 
			cout << itr->first << "\t" << itr->second << endl;
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
        	cout << "ID \t Title" << endl; 
			cout << itr->first << "\t" << itr->second << endl;
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
			cout << "ID \t Title" << endl; 
			cout << itr->first << "\t" << itr->second << endl;
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

void menu(map<double, string> hashTable, map<double, string> IDTable){
	int x = 0;
	int j = 0;
	string i;
	while(true){
		cout << endl;
		cout << "Enter your selection\n1)Print entire map\n2)Hash search using title\n3)Linear search using title\n4)Linear search using ID\n5)Binary search using ID\n6)Exit\nEnter selection: ";
		cin >> x;
		cout << endl;
		switch(x){
			case 1:
				cout << "Which map?\n1)HashMap\n2)IDMap\nEnter selection: ";
				cin >> j;
				if(j == 1){
					printMap(hashTable);
				}
				else if(j == 2){
					printMap(IDTable);
				}
				else{
					cout << "Wrong selection!" << endl;
				}
				break;
			case 2:
				cout << "Insert title: ";
				cin >> i;
				hashSearch(hashTable,i);
				break;
			case 3:
				cout << "Insert title: ";
				cin >> i;
				linearStringSearch(IDTable,i);
				break;
			case 4:
				cout << "Insert index: ";
				cin >> j;
				linearIndexSearch(IDTable,j);
				break;
			case 5:
				cout << "Insert index: ";
				cin >> j;
				binarySearch(IDTable,j,0,12295);
				break;
			case 6:
				cout << "Exiting program" << endl;
				return;
			default:
				cout << "Wrong selection!" << endl;
	}
	}
}

string * read(){
	static string a[12295];
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


    for (size_t i=0; i<animeData.size(); ++i){
        a[i] = animeData[i][1];
    }
    return a;
}

int main(){
	string *a = read();
	int n = 12295;
	map<double, string> hashTable = hashMap(a,n);
	map<double, string> IDTable = createIDTable(a,n);
	menu(hashTable, IDTable);
    
	return 0;
}
