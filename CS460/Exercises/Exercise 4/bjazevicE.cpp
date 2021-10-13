#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int main(int argc, char * argv[]){
    double sum_of_val = 0;
    double number = 0;
    vector <double> list_numbers;
    fstream numbers_file;
    numbers_file.open(argv[1]);
    if(!numbers_file.is_open()){
        cout << "Unable to open numbers file" << ".\nExiting..." << endl;
        exit(1);
    }
    while(numbers_file >> setprecision(10) >> fixed >> number)
    {
        list_numbers.push_back(number);
    }

    for(int i=0; i < list_numbers.size();i++)
    {
        sum_of_val += list_numbers[i];
    }

    cout << "The sum of the unsorted values is: " << setprecision(10);
    cout << fixed << sum_of_val << endl;

    sort(list_numbers.begin(), list_numbers.end(), greater<double>());

    sum_of_val = 0;

    for(int i=0; i < list_numbers.size();i++)
    {
        sum_of_val += list_numbers[i];
    }

    cout << "The sum of the descending values is: " << setprecision(10);
    cout << fixed << sum_of_val << endl;
    sort(list_numbers.begin(), list_numbers.end());

    sum_of_val = 0;

    for(int i=0; i < list_numbers.size();i++)
    {
        sum_of_val += list_numbers[i];
    }

    cout << "The sum of the ascending values is: " << setprecision(10) ;
    cout << fixed << sum_of_val << endl;
    cout << "In ascending order, the values are: " << endl;

    for(int i=0; i < list_numbers.size();i++)
    {
        cout << setw(21) << setprecision(10) << fixed << list_numbers[i] << endl;
    }


    return 0;
}
