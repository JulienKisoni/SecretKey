#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, const char * argv[]) {
    
    string input;
    cout << "Enter the key" << endl;
    cin >> input;
    
    fstream myFile;
    
    string filePath = "secretFile.txt";
    myFile.open(filePath, ios::in);
    
    if (myFile.is_open()) {
        // Read line by line
        string line;
        while (getline(myFile, line)) {
            cout << "This is the line: " << line << endl;
            
            if (input == line) {
                cout << "OK" << endl;
            } else {
                cout << "ERR" << endl;
            }
        }
    } else {
        cout << "File not opened" << endl;
    }
    
    myFile.close();
    
    return 0;
}
