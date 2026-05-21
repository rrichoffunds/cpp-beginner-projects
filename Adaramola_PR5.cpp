/*
Class: CMSC140 CRN 20326
Program: Project #5
Instructor: Ping Wei
Summary of Description: This program manages student scores using arrays, functions, searching, sorting, statistics, and file output.
Due Date:
Integrity Pledge: I pledge that I have completed the programming assignment independently.
I have not copied the code from a student or any source.
I have not given my code to any student.
Print your Name here: Ayodeji Daramola
*/


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

const int MAX_SCORES = 50;

int getValidatedInt(int minVal, int maxVal);
double getValidatedScore(double minVal, double maxVal);
void inputScores(double scores[], int &count, int maxSize);
void displayScores(double scores[], int count);
void computeStats(double scores[], int count, double &total, double &average, double &minVal, double &maxVal);
int linearSearch(double scores[], int count, double target);
void sortScores(double scores[], int count);
void writeReportToFile(string fileName, string studentName, double scores[], int count, double total, double average, double minVal, double maxVal);
void showMenu();

int main()
{
    double scores[MAX_SCORES];
    int count = 0;
    int choice;
    string studentName;
    string fileName;
    double total = 0.0, average = 0.0, minVal = 0.0, maxVal = 0.0;
    double target;
    int foundIndex;

    cout << "Welcome to the Student Scores Array Manager!" << endl << endl;

    cout << "Enter your name: ";
    getline(cin, studentName);

    cout << "Enter output file name (e.g., report.txt): ";
    getline(cin, fileName);
    cout << endl;

    inputScores(scores, count, MAX_SCORES);

    do
    {
        showMenu();
        choice = getValidatedInt(1, 5);
        cout << endl;

        if (choice == 1)
        {
            displayScores(scores, count);
        }
        else if (choice == 2)
        {
            computeStats(scores, count, total, average, minVal, maxVal);

            cout << fixed << setprecision(2);
            cout << "Statistics:" << endl;
            cout << "Count:   " << count << endl;
            cout << "Total:   " << total << endl;
            cout << "Average: " << average << endl;
            cout << "Min:     " << minVal << endl;
            cout << "Max:     " << maxVal << endl << endl;

            writeReportToFile(fileName, studentName, scores, count, total, average, minVal, maxVal);
            cout << "Report was written to " << fileName << endl << endl;
        }
        else if (choice == 3)
        {
            cout << "Enter value to search for (0 - 100): ";
            target = getValidatedScore(0, 100);

            foundIndex = linearSearch(scores, count, target);

            cout << fixed << setprecision(2);
            if (foundIndex == -1)
            {
                cout << "Value " << target << " not found in the array." << endl << endl;
            }
            else
            {
                cout << "Value " << target << " found at index " << foundIndex << "." << endl << endl;
            }
        }
        else if (choice == 4)
        {
            sortScores(scores, count);
            cout << "Scores have been sorted in ascending order." << endl << endl;
        }
        else if (choice == 5)
        {
            cout << "Exiting program. Goodbye!" << endl;
        }

    } while (choice != 5);

    cout << "Programmer: Ayodeji Daramola" << endl;
    cout << "Project#: 5" << endl;

    return 0;
}

int getValidatedInt(int minVal, int maxVal)
{
    int value;

    while (!(cin >> value) || value < minVal || value > maxVal)
    {
        cout << "Invalid value. Please enter a value between " << minVal << " and " << maxVal << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return value;
}

double getValidatedScore(double minVal, double maxVal)
{
    double value;

    while (!(cin >> value) || value < minVal || value > maxVal)
    {
        cout << "Invalid score. Please enter a value between " << minVal << " and " << maxVal << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return value;
}

void inputScores(double scores[], int &count, int maxSize)
{
    cout << "How many scores do you want to enter (1 - " << maxSize << ")? ";
    count = getValidatedInt(1, maxSize);
    cout << endl;

    for (int i = 0; i < count; i++)
    {
        cout << "Enter score #" << (i + 1) << " (0 - 100): ";
        scores[i] = getValidatedScore(0, 100);
    }

    cout << endl;
}

void displayScores(double scores[], int count)
{
    cout << fixed << setprecision(2);
    cout << "Scores:" << endl;

    for (int i = 0; i < count; i++)
    {
        cout << scores[i] << " ";
    }

    cout << endl << endl;
}

void computeStats(double scores[], int count, double &total, double &average, double &minVal, double &maxVal)
{
    total = 0.0;
    minVal = scores[0];
    maxVal = scores[0];

    for (int i = 0; i < count; i++)
    {
        total = total + scores[i];

        if (scores[i] < minVal)
        {
            minVal = scores[i];
        }

        if (scores[i] > maxVal)
        {
            maxVal = scores[i];
        }
    }

    average = total / count;
}

int linearSearch(double scores[], int count, double target)
{
    for (int i = 0; i < count; i++)
    {
        if (scores[i] == target)
        {
            return i;
        }
    }

    return -1;
}

void sortScores(double scores[], int count)
{
    double temp;

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (scores[j] > scores[j + 1])
            {
                temp = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = temp;
            }
        }
    }
}

void writeReportToFile(string fileName, string studentName, double scores[], int count, double total, double average, double minVal, double maxVal)
{
    ofstream outFile;
    outFile.open(fileName.c_str());

    if (outFile)
    {
        outFile << fixed << setprecision(2);
        outFile << "Student Scores Array Manager Report" << endl;
        outFile << "Student Name: " << studentName << endl;
        outFile << "Project#: 5" << endl << endl;

        outFile << "Scores:" << endl;
        for (int i = 0; i < count; i++)
        {
            outFile << scores[i] << " ";
        }

        outFile << endl << endl;
        outFile << "Statistics:" << endl;
        outFile << "Count:   " << count << endl;
        outFile << "Total:   " << total << endl;
        outFile << "Average: " << average << endl;
        outFile << "Min:     " << minVal << endl;
        outFile << "Max:     " << maxVal << endl;

        outFile.close();
    }
    else
    {
        cout << "Error opening the output file." << endl;
    }
}

void showMenu()
{
    cout << "---------- Main Menu ----------" << endl;
    cout << "1. Display scores" << endl;
    cout << "2. Show statistics" << endl;
    cout << "3. Search for a score" << endl;
    cout << "4. Sort scores (ascending)" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice (1-5): ";
}
