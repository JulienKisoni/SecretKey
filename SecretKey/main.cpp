#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <openssl/evp.h>
#include <openssl/sha.h>

using namespace std;

string hashPassword(const string& password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password.c_str(), password.size());
    SHA256_Final(hash, &sha256);

    // Convert hash to a hex string
    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}

// Function to compare the hashed password with a plaintext password
bool comparePassword(const string& hashedPassword, const string& plainPassword) {
    // Hash the plaintext password
    string hashedInput = hashPassword(plainPassword);

    // Compare the two hashed strings
    return hashedPassword == hashedInput;
}

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
            bool equal = comparePassword(line, input);
            if (equal) {
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
