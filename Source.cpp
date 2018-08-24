#include <iostream>
#include <string.h>
#include <string>
#include <ctype.h>
#include <conio.h>
#include <sstream>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <vector>
#include <algorithm>
#include <thread>   
#include <fstream>
using namespace std;
vector<int> primes;


template<typename T> void printVector( const vector<T>& v)
{
	for (size_t i = 0; i < v.size(); i++)	{cout << v[i] << " ";}
	cout << endl;
}


vector<int> prime_numbers(int a, int b) 
{
	bool prime = true;
	int count = 0;
	vector<int> v1;
	for (int i = a; i <= b; i++) {
		prime = true;
		double sqrti = sqrt((double)i);
		for (int j = 2; j<sqrti + 1; j++)
			if (i%j == 0) {
				prime = false;
				break;
			}
		if (prime)
		{
			//cout << i << " prime number\n";
			v1.insert(v1.begin() + count, i);
			count++;
		}
	}
	return v1;
}

vector<int> read_xml_file() 
{
	ifstream file("input.xml");
	vector<int> v1;
	string s, find_low_start, find_low_end, find_high_start, find_high_end;
	find_low_start = "<low>";
	find_low_end = "</low>";
	find_high_start = "<high>";
	find_high_end = "</high>";
	char c;
	int pos = 0;
	int pos1 = 0;
	int pos2 = 0;
	int pos3=0;
	if(file.is_open()){
		while (!file.eof()) {  // прочитали его и заполнили им строку
			file.get(c);
			s.push_back(c);
		}
		while (true) 
		{
			pos = s.find(find_low_start, pos + 1);
			if (pos == -1) break;
			pos1 = s.find(find_low_end,pos1+1); // поиск
			pos2 = s.find(find_high_start,pos2+1); // поиск
			pos3 = s.find(find_high_end,pos3+1); // поиск
			string smth;
			for (int i = pos + find_low_start.length(); i<pos1; i++){smth.push_back(s[i]);}
			v1.push_back(atoi(smth.c_str()));
			//cout << smth << endl;
			smth.clear();
			for (int i = pos2 + find_high_start.length(); i<pos3; i++){smth.push_back(s[i]);}
			v1.push_back(atoi(smth.c_str()));
			//cout << smth << endl;
			smth.clear();
		}
		file.close(); // обязательно закрыли
		return v1;
	}
}

void write_to_file(vector<int> v1 ) 
{
	sort(v1.begin(), v1.end());
	auto last = unique(v1.begin(), v1.end());
	v1.erase(last, v1.end());
	ofstream file_write("output.xml");
	if (file_write.is_open())
	{
		file_write << "<root>" << endl;
		file_write << " <primes> ";
		for (size_t i = 0; i < v1.size(); i++) { file_write << v1[i] << " "; }
		file_write << " </primes>" << endl << "</root>" << endl;
		file_write.close();
	}
}


vector<int> v3 = read_xml_file();

void process_interval(int index)
{
	vector<int> v4;
	if (index == 0 || index % 2 == 0)
	{
		v4 = prime_numbers(v3[index], v3[index + 1]);
		copy(v4.begin(), v4.end(), back_inserter(primes));
	}
}

thread count_prime_numbers(int index)
{
	return (std::thread([=] { process_interval(index); }));
}

int main()
{

vector<thread> threads;
for (int i = 0; i < v3.size() -1; i++) threads.push_back(count_prime_numbers(i));
for (int i = 0; i <v3.size() -1; i++) threads[i].join();
//printVector(primes);
write_to_file(primes);

//_getch();
}