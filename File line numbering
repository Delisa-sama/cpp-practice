#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int main(int argc ,char* argv[])
{
	if (argc < 2)
	{
		
		cout << "Please enter the one argument, it's filename" << '\n';
		cout << "Exmample: ./mynl test.txt" << '\n';
	
	}
	else
	{
		
		if (argc > 2)
		{
		
			cout << "Too many arguments" << '\n';
		
		}
		else
		{
	
			string bufStr;	
			ifstream file(argv[1]);
			if (file.is_open())
			{
				
				int count = 0;
				while (getline(file, bufStr) && (!(file.eof()) && !(file.fail()))) 
				{
					
					count++;
					cout << count << " | " << bufStr << '\n';
				
				}
		
				file.close();			
			
			}
			else
			{
			
				cout << "Failed to open file" << '\n';
			
			}
		}
	}
	return 0;
}
