#include <iostream>
#include <string>
#include <cctype>

using namespace std;

void encrypt();
void decrypt();

int main() {

    cout << "Encrypt or Decrypt ? (E/D): ";
    char choice;
    cin >> choice;
    cin.ignore();

    if (choice == 'E' || choice == 'e'){
        encrypt();
    }
    else if (choice == 'D' || choice == 'd'){
        decrypt();
    }
    else {
        cout << "Invalid choice. Please enter E or D." << endl;
    }

    return 0;
}

void decrypt(){
    
    cout << "Enter Some code to decrypt: " << endl;
    string text;
    getline(cin, text);
    for (char &c : text) {
        c = toupper(c);
    }

    cout << "Enter the key: " << endl;
    string key;
    getline(cin, key);
    for (char &c : key) {
        c = toupper(c);
    }

    string decrypted_text;
    int key_length = key.length();
    int key_index = 0;
    for (char c : text) {
        if (isalpha(c)) {
            char key_char = key[key_index % key_length];
            char decrypted_char = (c - key_char + 26) % 26 + 'A';
            decrypted_text += decrypted_char;
            key_index++;    
        } else {
            decrypted_text += c; 
        }
    }
    cout << "Decrypted text: " << decrypted_text << endl;
}

void encrypt(){
        
    cout << "Enter Some code to encrypt: " << endl;
    string text;
    getline(cin, text);
    for (char &c : text) {
        c = toupper(c);
    }

    cout << "Enter the key: " << endl;
    string key;
    getline(cin, key);
    for (char &c : key) {
        c = toupper(c);
    }

    string encrypted_text;
    int key_length = key.length();
    int key_index = 0;
    for (char c : text) {
        if (isalpha(c)) {
            char key_char = key[key_index % key_length];
            char encrypted_char = (c - 'A' + key_char - 'A') % 26 + 'A';
            encrypted_text += encrypted_char;
            key_index++;    
        } else {
            encrypted_text += c; 
        }
    }
    cout << "Encrypted text: " << encrypted_text << endl;
}

