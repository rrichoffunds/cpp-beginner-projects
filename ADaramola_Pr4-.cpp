/*
 Class: CMSC140 CRN 20326
 Program: Project #4 Design
 Instructor: Professor Ping Wei
 Summary of Description: File-Based Report Generator that reads student records from an input file,
 computes tuition, letter grades, academic standing, and writes a formatted report to the screen
 and an output file.
 Due Date: Spring 2026
 Integrity Pledge: I pledge that I have completed the programming assignment independently.
 I have not copied the code from a student or any source.
 I have not given my code to any student.
 Print your Name here: Ayodeji Daramola
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

void displayWelcome();
string promptFileName(const string& prompt, bool isInput);
bool openInputFile(ifstream& inFile, const string& fileName);
bool openOutputFile(ofstream& outFile, const string& fileName);
char getLetterGrade(double grade);
string getStanding(double grade);
double computeTotalDue(int credits, double costPerCredit);
bool isValidRecord(int credits, double costPerCredit, double grade);
void writeStudentReport(ostream& out, const string& name, int credits, double costPerCredit,
                        double grade, char letter, const string& standing, double totalDue);
void writeSummary(ostream& out, int validCount, double gradeTotal, double minGrade, double maxGrade);

int main()
{
    displayWelcome();

    string inputFileName = promptFileName("Enter input file name: ", true);
    string outputFileName = promptFileName("Enter output file name: ", false);

    ifstream inFile;
    ofstream outFile;

    if (!openInputFile(inFile, inputFileName))
    {
        cout << "Unable to open input file.\n";
        return 1;
    }

    if (!openOutputFile(outFile, outputFileName))
    {
        cout << "Unable to open output file.\n";
        return 1;
    }

    string name;
    int credits;
    double costPerCredit;
    double grade;

    int validCount = 0;
    int invalidCount = 0;
    double gradeTotal = 0.0;
    double minGrade = 101.0;
    double maxGrade = -1.0;

    while (inFile >> name >> credits >> costPerCredit >> grade)
    {
        if (!isValidRecord(credits, costPerCredit, grade))
        {
            invalidCount++;
            continue;
        }

        char letter = getLetterGrade(grade);
        string standing = getStanding(grade);
        double totalDue = computeTotalDue(credits, costPerCredit);

        writeStudentReport(cout, name, credits, costPerCredit, grade, letter, standing, totalDue);
        writeStudentReport(outFile, name, credits, costPerCredit, grade, letter, standing, totalDue);

        validCount++;
        gradeTotal += grade;

        if (grade < minGrade)
            minGrade = grade;
        if (grade > maxGrade)
            maxGrade = grade;
    }

    writeSummary(cout, validCount, gradeTotal, minGrade, maxGrade);
    writeSummary(outFile, validCount, gradeTotal, minGrade, maxGrade);

    if (invalidCount > 0)
    {
        cout << "Invalid rows skipped: " << invalidCount << endl;
        outFile << "Invalid rows skipped: " << invalidCount << endl;
    }

    cout << "Report also written to: " << outputFileName << endl;
    cout << "Thank you for using the MC File-Based Student Report Generator." << endl;

    inFile.close();
    outFile.close();
    return 0;
}

void displayWelcome()
{
    cout << "============================================" << endl;
    cout << " MC File-Based Student Report Generator" << endl;
    cout << "============================================" << endl;
}

string promptFileName(const string& prompt, bool isInput)
{
    string fileName;
    bool valid = false;

    do
    {
        cout << prompt;
        cin >> fileName;

        if (fileName.length() == 0)
        {
            cout << "Filename cannot be blank. Try again." << endl;
        }
        else
        {
            valid = true;
        }
    } while (!valid);

    return fileName;
}

bool openInputFile(ifstream& inFile, const string& fileName)
{
    inFile.open(fileName);
    return inFile.is_open();
}

bool openOutputFile(ofstream& outFile, const string& fileName)
{
    outFile.open(fileName);
    return outFile.is_open();
}

char getLetterGrade(double grade)
{
    if (grade >= 90)
        return 'A';
    else if (grade >= 80)
        return 'B';
    else if (grade >= 70)
        return 'C';
    else if (grade >= 60)
        return 'D';
    else
        return 'F';
}

string getStanding(double grade)
{
    if (grade >= 60)
        return "Good Standing";
    else
        return "See Advisor";
}

double computeTotalDue(int credits, double costPerCredit)
{
    return credits * costPerCredit;
}

bool isValidRecord(int credits, double costPerCredit, double grade)
{
    return (credits >= 0 && costPerCredit >= 0 && grade >= 0 && grade <= 100);
}

void writeStudentReport(ostream& out, const string& name, int credits, double costPerCredit,
                        double grade, char letter, const string& standing, double totalDue)
{
    out << fixed << setprecision(2);
    out << "Student Name: " << name << endl;
    out << "Credits: " << credits << endl;
    out << "Cost/Credit: $" << costPerCredit << endl;
    out << "Grade: " << grade << " (" << letter << ")" << endl;
    out << "Standing: " << standing << endl;
    out << "Total Due: $" << totalDue << endl;
    out << "----------------------------------------" << endl;
}

void writeSummary(ostream& out, int validCount, double gradeTotal, double minGrade, double maxGrade)
{
    out << fixed << setprecision(2);
    out << "\n======== Summary Report ========" << endl;
    out << "Valid Students: " << validCount << endl;

    if (validCount > 0)
    {
        out << "Average Grade: " << (gradeTotal / validCount) << endl;
        out << "Min Grade: " << minGrade << endl;
        out << "Max Grade: " << maxGrade << endl;
    }
    else
    {
        out << "Average Grade: 0.00" << endl;
        out << "Min Grade: 0.00" << endl;
        out << "Max Grade: 0.00" << endl;
    }

    out << "================================" << endl;
}
