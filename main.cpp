/*
 * GPS vs RADAR Error Checker
 * Author: Yasmine Elsisi
 * Date: April 2025
 *
 * Description:
 * This program compares GPS and RADAR 3D coordinate data to detect inconsistencies
 * by checking if the distance between corresponding coordinates exceeds a user-defined tolerance.
 * Discrepancies are logged in an ERR.LOG file with timestamps.
 */

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

void calculateError();
void displayErrorLog();

int main() {
    char choice;
    bool repeat = true;

    while (repeat) {
        cout << "\n========== MENU ==========" << endl;
        cout << "1. Calculate error between sensors" << endl;
        cout << "2. Display error log" << endl;
        cout << "3. Exit program" << endl;
        cout << "===========================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                calculateError();
                break;
            case '2':
                displayErrorLog();
                break;
            case '3':
                cout << "Exiting program..." << endl;
                repeat = false;
                break;
            default:
                cout << "Invalid input. Please choose 1, 2, or 3." << endl;
        }

        if (repeat)
            cout << "\n...BACK TO MAIN MENU...\n";
    }

    return 0;
}

void calculateError() {
    string file1, file2;
    float tolerance;
    double x1, y1, z1, x2, y2, z2, distance;
    double time = 0;

    // Input
    cout << "Enter GPS file name: ";
    cin >> file1;
    cout << "Enter RADAR file name: ";
    cin >> file2;
    cout << "Enter tolerance value: ";
    cin >> tolerance;

    while (tolerance < 0) {
        cout << "Invalid tolerance. Please enter a positive value: ";
        cin >> tolerance;
    }

    ifstream fin1(file1);
    while (fin1.fail()) {
        cout << "Unable to open GPS file. Re-enter filename: ";
        cin >> file1;
        fin1.open(file1);
    }

    ifstream fin2(file2);
    while (fin2.fail()) {
        cout << "Unable to open RADAR file. Re-enter filename: ";
        cin >> file2;
        fin2.open(file2);
    }

    ofstream fout("ERR.LOG");
    if (!fout) {
        cerr << "Error: Unable to create ERR.LOG file." << endl;
        return;
    }

    // Processing
    while (fin1 >> x1 >> y1 >> z1 && fin2 >> x2 >> y2 >> z2) {
        distance = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2));
        if (distance > tolerance)
            fout << fixed << setprecision(2) << time << setw(12) << setprecision(5) << distance << endl;
        time += 0.25;
    }

    cout << "✅ ERR.LOG created with discrepancies (if any)." << endl;

    fin1.close();
    fin2.close();
    fout.close();
}

void displayErrorLog() {
    string time, error;
    ifstream fin("ERR.LOG");

    if (fin.fail()) {
        cout << "Error: Unable to open ERR.LOG. Run option 1 first." << endl;
        return;
    }

    cout << "\n=========== ERR.LOG ============" << endl;
    cout << setw(10) << left << "Time (s)" << setw(25) << right << "Distance Exceeding Tolerance (m)" << endl;
    cout << "--------------------------------" << endl;

    while (fin >> time >> error)
        cout << setw(10) << left << time << setw(25) << right << error << endl;

    fin.close();
}
