/*
 * Class: CMSC140 CRN 20326
 * Instructor: Ping Wei
 * Project: Classwork 7
 * Name: Ayodeji Daramola
 * Description: This program uses a function named largerThanN to display all numbers
 *              in an integer array that are greater than a number entered by the user.
 * Due Date: Not specified
 * I pledge that I have completed the programming assignment independently.
   I have not copied the code from a student or any source.
   I have not given my code to any student.
   Print your Name here: Ayodeji Daramola
*/

#include <iostream>
using namespace std;

// Function prototype
void largerThanN(const int numbers[], int size, int n);

int main()
{
    const int ARRAY_SIZE = 10;
    int numbers[ARRAY_SIZE] = {30, 20, 50, 2, -1, 44, 3, 12, 90, 32};
    int userNumber;

    cout << "Enter a number: ";
    cin >> userNumber;

    largerThanN(numbers, ARRAY_SIZE, userNumber);

    return 0;
}

// This function displays all numbers in the array that are greater than n.
void largerThanN(const int numbers[], int size, int n)
{
    bool found = false;

    cout << "Numbers greater than " << n << ": ";

    for (int index = 0; index < size; index++)
    {
        if (numbers[index] > n)
        {
            cout << numbers[index] << " ";
            found = true;
        }
    }

    if (!found)
    {
        cout << "No numbers are greater than " << n << ".";
    }

    cout << endl;
}
