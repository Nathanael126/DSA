#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <vector>
#include <iterator>
#include <map>
#include <string>
#include <chrono>
using namespace std;
using namespace std::chrono;

//Hash function (string to int)
double hashFunction(string a){
	double x = 0;
	int i = 2;
//	Character ASCII multiplied by index starting at 2
//Index:	2 3 4 5 6 7
//EG: 		N a r u t o
//ASCII:	78 97 114 117 116 111
//New ASCII:156 291 456 585 696 777
//Total:	2961
	for(char c : a){
		x = x + (static_cast<int>(c)*i++);
		
	}
	return x;
}
//Initialize hashmap
map<double, string> hashMap(string *a, int n){
	map<double, string> hashTable;
	int temp = 0;
	map<double, string>::iterator itr;
//	Hash all entries
	for(int i; i < n; i++){
		temp = hashFunction(a[i]);
		itr = hashTable.find(temp);
//		Collision handler
		while(itr->first >= 1){
			temp = temp + 1;
			itr = hashTable.find(temp);
		}
		hashTable.insert(pair<double,string>(temp,a[i]));
	}
	return hashTable;
}
//Search in hashtable
void hashSearch(map<double, string> x, string a){
	double search = hashFunction(a);
	map<double, string>::iterator itr = x.find(search);
	if(itr->first >= 1){
//		Collision handler
		while(itr->second != a){
			search = search + 1;
			map<double, string>::iterator itr = x.find(search);
		}
		cout << "Found results: " << endl;
		cout << "ID \t Title" << endl; 
		cout << itr->first << "\t" << itr->second << endl;
	}
	else{
		cout<< "Not found!" << endl;
	}	
}
//Map print
void printMap(map<double, string> x){
	cout << "Printing full map:" << endl;
	map<double, string>::iterator itr;
	for (itr = x.begin(); itr != x.end(); ++itr) {
        cout << itr->first << " " << itr->second << endl;
    }
}

//Initialize ID table
map<double, string> createIDTable(string *a, int n){
	map<double, string> IDTable;
	for(int i = 0; i < n; i++){
		IDTable.insert(pair<double,string>(i,a[i]));
	}
	return IDTable;
}

//Search linearly using string
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
//Search linearly using index
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
    cout << "Not found!" << endl;
}
//Search using binary search
//Recursive funtion method
int binarySearch(map<double, string> x, double a, double left, double right){
	if (right >= left) {
        int mid = left + (right - left) / 2;
        if (mid == a){
        	map<double, string>::iterator itr = x.find(mid);
        	cout << "Found results: " << endl;
			cout << "ID \t Title" << endl; 
			cout << itr->first << "\t" << itr->second << endl;
			return 0;
		}
        if (mid > a){
			return binarySearch(x, a, left, mid - 1);
		}
  
        return binarySearch(x, a, mid + 1, right);
    }
    
	return -1;
}
//Initialize .csv
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
//	Initialize variables
	auto start = high_resolution_clock::now();
	auto end = high_resolution_clock::now();
	auto timeElapsed = duration_cast<microseconds>(end - start);
	int x = 0;
	int j = 0;
	int f;
	string i;
//	Menu UI
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
				start = high_resolution_clock::now();
				hashSearch(hashTable,i);
				end = high_resolution_clock::now();
				timeElapsed = duration_cast<microseconds>(end - start);
				cout << "Time taken: " << timeElapsed.count() << " microseconds" << endl;
				break;
			case 3:
				cout << "Insert title: ";
				cin >> i;
				start = high_resolution_clock::now();
				linearStringSearch(IDTable,i);
				end = high_resolution_clock::now();
				timeElapsed = duration_cast<microseconds>(end - start);
				cout << "Time taken: " << timeElapsed.count() << " microseconds" << endl;
				break;
			case 4:
				cout << "Insert index: ";
				cin >> j;
				start = high_resolution_clock::now();
				linearIndexSearch(IDTable,j);
				end = high_resolution_clock::now();
				timeElapsed = duration_cast<microseconds>(end - start);
				cout << "Time taken: " << timeElapsed.count() << " microseconds" << endl;
				break;
			case 5:
				cout << "Insert index: ";
				cin >> j;
				start = high_resolution_clock::now();
				f = binarySearch(IDTable,j,0,12294);
				if(f == -1){
					cout << "Not found!" << endl;
				}
				end = high_resolution_clock::now();
				timeElapsed = duration_cast<microseconds>(end - start);
				cout << "Time taken: " << timeElapsed.count() << " microseconds" << endl;
				break;
			case 6:
				cout << "Exiting program" << endl;
				return 0;
			default:
				cout << "Wrong selection!" << endl;
	}
	}
	return 0;
}
