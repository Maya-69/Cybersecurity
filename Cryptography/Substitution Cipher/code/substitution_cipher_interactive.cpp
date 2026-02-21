#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <map>

using namespace std;

int main() {
    cout << "============================================================\n";
    cout << "         Substitution Cipher Decryption Tool\n";
    cout << "============================================================\n\n";

    // Step 1: Get encrypted text from user
    string encryptedText;
    cout << "Enter the encrypted text: ";
    getline(cin, encryptedText);

    // Step 2: Choose manual or automatic mode
    int choice;
    cout << "\nChoose decryption mode:\n";
    cout << "1. Manual (user provides substitution alphabet)\n";
    cout << "2. Automatic (use provided alphabets)\n";
    cout << "Enter choice (1 or 2): ";
    cin >> choice;
    cin.ignore();

    string encryptionAlphabet = "XCDQRLPKWAOUFTEYJHNVISGZBM";
    string decryptionAlphabet = "JYBCOMWRUQHFZSKGDEVNLTIAPX";
    string plainAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string resultDecryption;

    if (choice == 1) {
        // MANUAL MODE
        cout << "\n============================================================\n";
        cout << "                    MANUAL MODE\n";
        cout << "============================================================\n\n";
        cout << "For each letter in the encrypted text, enter what it decrypts to.\n";
        cout << "Format: X n (means X decrypts to n)\n\n";

        resultDecryption = "";

        // Get unique letters from encrypted text
        string uniqueLetters = "";
        for (char c : encryptedText) {
            if (isalpha(c)) {
                char upper = toupper(c);
                if (uniqueLetters.find(upper) == string::npos) {
                    uniqueLetters += upper;
                }
            }
        }

        // Build decryption map
        map<char, char> decryptMap;
        for (char letter : uniqueLetters) {
            string input;
            cout << "What does '" << letter << "' decrypt to? ";
            getline(cin, input);
            
            if (input.length() > 0) {
                decryptMap[letter] = toupper(input[0]);
            }
        }

        // Decrypt using the map
        for (char c : encryptedText) {
            if (isalpha(c)) {
                char upper = toupper(c);
                if (decryptMap.find(upper) != decryptMap.end()) {
                    resultDecryption += decryptMap[upper];
                } else {
                    resultDecryption += '?';
                }
            } else {
                resultDecryption += c;
            }
        }

    } else if (choice == 2) {
        // AUTOMATIC MODE
        cout << "\n============================================================\n";
        cout << "                  AUTOMATIC MODE\n";
        cout << "============================================================\n\n";
        cout << "Enter the cipher and plaintext alphabets.\n";
        cout << "Example: If ciphertext 'X' decrypts to plaintext 'J', etc.\n\n";
        
        string cipherAlphabet, plainAlphabet;
        cout << "Original alphabet (abcd.....): ";
        getline(cin, cipherAlphabet);
        
        cout << "Enter Decryption alphabet (jybc.....): ";
        getline(cin, plainAlphabet);
        
        // Convert to uppercase
        transform(cipherAlphabet.begin(), cipherAlphabet.end(), cipherAlphabet.begin(), ::toupper);
        transform(plainAlphabet.begin(), plainAlphabet.end(), plainAlphabet.begin(), ::toupper);
        
        cout << "\nUsing:\n";
        cout << "Cipher: " << cipherAlphabet << endl;
        cout << "Plain:  " << plainAlphabet << endl << endl;

        resultDecryption = "";

        // Decrypt: find encrypted char in cipher alphabet, get corresponding char from plain alphabet
        for (char c : encryptedText) {
            if (isalpha(c)) {
                char upper = toupper(c);
                // Find position of encrypted letter in CIPHER alphabet
                int pos = cipherAlphabet.find(upper);
                if (pos != string::npos) {
                    // Get character at same position in PLAIN alphabet
                    resultDecryption += plainAlphabet[pos];
                } else {
                    resultDecryption += '?';
                }
            } else {
                resultDecryption += c;
            }
        }
    } else {
        cout << "Invalid choice!\n";
        return 1;
    }

    // Step 3: Display results
    cout << "\n============================================================\n";
    cout << "                     RESULTS\n";
    cout << "============================================================\n\n";
    cout << "Encrypted Text: " << encryptedText << endl;
    cout << endl;
    cout << "Decrypted Text: " << resultDecryption << endl;
    cout << "\n============================================================\n";

    return 0;
}
