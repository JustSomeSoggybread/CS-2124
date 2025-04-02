// Evan Lee
// CS-UY 2124 
// Omar Mansour
// Homework 1 - Decrypt a file encrypted by a classic Caesar cipher

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//Prototyping
char decryptCharacter(int rotDist, char origChar);
void decryptString(int rotDist, string& origString);


int main(){ 
    // Initializes cipher shift
    int cypherDist;
    // Initializes variables for each word (fileLine) 
    string fileLine;
    // Initializes a vector of words (lineList)
    vector<string> lineList;
    // Initializes an input stream set to "encrypted.txt"
    ifstream encryptStream("encrypted.txt");

    // Exits if specified file does not exist
    if (!encryptStream){
        cerr << "File not at location." << endl;
        exit(1);
    }

    // Sets the cipher shift
    encryptStream >> cypherDist;
    
    // Iterates through the file and pushes ciphered words to fileLine
    while (getline(encryptStream, fileLine)){
        lineList.push_back(fileLine);
    }

    // Close input stream
    encryptStream.close();

    // Iteratively calls decryptString on elements in vector,
    // outputs decrypted string.
    // Iterates backwards starting from end of vector.
    for (int i = lineList.size()-1; i > 0; i--){
        decryptString(cypherDist, lineList[i]);
        cout << lineList[i] << endl;
    }
    
}

char decryptCharacter(int rotDist, char origChar){
    // Deciphers the specified character with the specified cipher shift
    return (((origChar -'A') + 26 - rotDist)%26 + 'A');
}

void decryptString(int rotDist, string& origString){
    // For each character in the specified string
    for (char& index : origString){
        // Checks if the character is capitalized 
        // (denotes character was shifted)
        if (index >= 'A' && index <= 'Z'){
            // If character is capitalized, call to decrypt the character 
            // with specified cipher shift
            index = decryptCharacter(rotDist, index);
        }
    }
}