#include <iostream>
#include <string>

using namespace std;

string caesarCipherEncrypt(const string &text, int shift);
string caesarCipherDecrypt(const string &text, int shift);

int main() {
    
    cout << "Encrypt or decrypt? (e/d): ";
    char choice;
    cin >> choice;
    cin.ignore();

    cout << "Enter the text: ";
    string text;
    getline(cin, text);

    cout << "Enter the shift value (1-25): ";
    int shift;
    cin >> shift;

    if (shift < 1 || shift > 25) {
        cout << "Invalid shift value. Please enter a value between 1 and 25." << endl;
        return 1;
    }
    if (choice == 'e') {
        string encryptedText = caesarCipherEncrypt(text, shift);
        cout << "Encrypted text: " << encryptedText << endl;
    } else if (choice == 'd') {
        string decryptedText = caesarCipherDecrypt(text, shift);
        cout << "Decrypted text: " << decryptedText << endl;
    } else {
        cout << "Invalid choice. Please enter 'e' for encrypt or 'd' for decrypt." << endl;
        return 1;
    }

    return 0;
}

string caesarCipherEncrypt(const string &text, int shift) {
    string result = "";

    // Traverse each character in the input text
    for (char c : text) {
        // Encrypt uppercase letters
        if (isupper(c)) {
            result += char(int((c + shift - 65) % 26 + 65));
        }
        // Encrypt lowercase letters
        else if (islower(c)) {
            result += char(int((c + shift - 97) % 26 + 97));
        }
        // Non-alphabetic characters remain unchanged
        else {
            result += c;
        }
    }
    return result;
}

string caesarCipherDecrypt(const string &text, int shift) {
    return caesarCipherEncrypt(text, 26 - shift);
}