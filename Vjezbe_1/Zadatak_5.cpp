#include<iostream>

using namespace std;

int _my_cube(int number)
{
	int cub;
	cub=number*number*number;
	return cub;
} 

int main() {

 
   int num, cube;
    
   cout << "Enter number \n";
   cin >> num;
   cube = num * num * num;
 
   cout << "Cube of a number is" << _my_cube(num);

   return 0;

}
