/*
 * Name: Ayodeji Daramola
 * Course: CMSC140
 * Project: Project 3 - Statistics Calculator
 * Date: April 1, 2026
 * Description: This program validates a user's name, the number of scores,
 * and each score entered. It calculates the total, average, highest, and
 * lowest score, then allows the user to process another set of scores.
 Integrity Pledge: I pledge that I have completed the programming assignment independently.
  I have not copied the code from a student or any source.
  I have not given my code to any student.
  Print your Name here: Ayodeji Daramola


 */

#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>
#include <string>
#include <cctype>

using namespace std;

const int MIN_COUNT = 1;
const int MAX_COUNT = 30;
const double MIN_SCORE = 0.0;
const double MAX_SCORE = 100.0;

string trim(const string& text)
{
    size_t start = text.find_first_not_of(" \t\r\n");
    if (start == string::npos)
    {
        return "";
    }

    size_t end = text.find_last_not_of(" \t\r\n");
    return text.substr(start, end - start + 1);
}

bool tryParseInt(const string& text, int& value)
{
    istringstream input(text);
    char extra;

    if (!(input >> value))
    {
        return false;
    }

    if (input >> extra)
    {
        return false;
    }

    return true;
}

bool tryParseDouble(const string& text, double& value)
{
    istringstream input(text);
    char extra;

    if (!(input >> value))
    {
        return false;
    }

    if (input >> extra)
    {
        return false;
    }

    return true;
}

string getValidatedName()
{
    string name;

    while (true)
    {
        cout << "Please enter your name: ";
        getline(cin, name);
        name = trim(name);

        if (!name.empty())
        {
            return name;
        }

        cout << "Invalid name. Please enter a non-empty name." << endl;
    }
}

int getValidatedCount()
{
    string line;
    int count;

    cout << endl;
    cout << "How many scores will you enter (" << MIN_COUNT << " - " << MAX_COUNT << ")? ";
    getline(cin, line);

    while (!tryParseInt(trim(line), count) || count < MIN_COUNT || count > MAX_COUNT)
    {
        cout << "Invalid count. Please enter a value between "
             << MIN_COUNT << " and " << MAX_COUNT << "." << endl;
        cout << "How many scores will you enter (" << MIN_COUNT << " - " << MAX_COUNT << ")? ";
        getline(cin, line);
    }

    return count;
}

char getValidatedRunAgain()
{
    string line;

    cout << endl;
    cout << "Do you want to process another set? (Y/N): ";
    getline(cin, line);
    line = trim(line);

    while (line.length() != 1 || (toupper(line[0]) != 'Y' && toupper(line[0]) != 'N'))
    {
        cout << "Invalid response. Please enter Y or N." << endl;
        cout << "Do you want to process another set? (Y/N): ";
        getline(cin, line);
        line = trim(line);
    }

    return static_cast<char>(toupper(line[0]));
}

int main()
{
    cout << "Welcome to the Statistics Calculator!" << endl << endl;

    string userName = getValidatedName();
    cout << "Hello, " << userName << "!" << endl;

    char runAgain;

    do
    {
        int scoreCount = getValidatedCount();
        double total = 0.0;
        double highest = 0.0;
        double lowest = 0.0;

        for (int i = 1; i <= scoreCount; i++)
        {
            string line;
            double score;

            cout << endl;
            cout << "Enter score #" << i << " (0 - 100): ";
            getline(cin, line);

            while (!tryParseDouble(trim(line), score) || score < MIN_SCORE || score > MAX_SCORE)
            {
                cout << "Invalid score. Please enter a value between 0 and 100." << endl;
                cout << "Enter score #" << i << " (0 - 100): ";
                getline(cin, line);
            }

            total += score;

            if (i == 1)
            {
                highest = score;
                lowest = score;
            }
            else
            {
                if (score > highest)
                {
                    highest = score;
                }

                if (score < lowest)
                {
                    lowest = score;
                }
            }
        }

        double average = total / scoreCount;

        cout << endl;
        cout << "----- Statistics Report -----" << endl;
        cout << "User:    " << userName << endl;
        cout << "Count:   " << scoreCount << endl;
        cout << fixed << setprecision(2);
        cout << "Total:   " << total << endl;
        cout << "Average: " << average << endl;
        cout << "Highest: " << highest << endl;
        cout << "Lowest:  " << lowest << endl;
        cout << "-----------------------------" << endl;

        runAgain = getValidatedRunAgain();
    }
    while (runAgain == 'Y');

    cout << endl;
    cout << "Thank you for using the Statistics Calculator. Goodbye!" << endl;

    return 0;
}

