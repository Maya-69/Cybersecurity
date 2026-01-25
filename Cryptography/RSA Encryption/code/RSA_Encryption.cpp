#include <iostream>
#include <string>
#include <cctype>
#include <random>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

int gcd(int a, int b);
int findRandomCoprime(int phi, int n);
int modularInverse(int e, int phi);
long long modularExponentiation(long long base, long long exp, long long mod);

void encrypt();
void decrypt();
void generateEncryptionPair();
void generateDecryptionPair();

int main() {
    char choice;
    cout << "Choose an option (E for Encrypt, D for Decrypt, P for Encryption Pair, Q for Decryption Pair): ";
    cin >> choice;
    choice = toupper(choice);
    cin.ignore();

    switch (choice) {
        case 'E':
            encrypt();
            break;
        case 'D':
            decrypt();
            break;
        case 'P':
            generateEncryptionPair();
            break;
        case 'Q':
            generateDecryptionPair();
            break;
        default:
            cout << "Invalid choice. Please select E, D, P, or Q." << endl;
            break;
    }
    
    return 0;
}

void encrypt() {
    cout << "Enter plaintext to encrypt: " << endl;
    string plaintext;
    getline(cin, plaintext);

    cout << "Do you have a public key? (Y/N): ";  
    char hasKey;
    cin >> hasKey;
    cin.ignore();

    if (toupper(hasKey) == 'Y') {
        cout << "Enter public key (e n) (eg. 17 3233): " << endl;
        int e, n;
        cin >> e >> n;
        cin.ignore();
        
        cout << "Encrypting..." << endl;
        cout << "Ciphertext: ";
        for(char c : plaintext) {
            if (isalpha(c)) {
                // Encrypt: C = (M^e) mod n
                long long encrypted = modularExponentiation(toupper(c) - 'A', e, n);
                cout << encrypted << " ";
            }
        }
        cout << endl;
    } else {
        cout << "Generating new encryption pair..." << endl;
        generateEncryptionPair();
    }
}

void decrypt() {
    cout << "Enter ciphertext to decrypt (space-separated numbers): " << endl;
    string ciphertextInput;
    getline(cin, ciphertextInput);
    
    cout << "Enter private key d: ";
    int d;
    cin >> d;
    
    cout << "Enter modulus n: ";
    int n;
    cin >> n;
    cin.ignore();
    
    cout << "Decrypting..." << endl;
    
    string plaintext;
    stringstream ss(ciphertextInput);
    long long cipherChar;
    
    while (ss >> cipherChar) {
        // Decrypt: M = (C^d) mod n
        long long decrypted = modularExponentiation(cipherChar, d, n);
        plaintext += (char)(decrypted + 'A');
    }
    
    cout << "Plaintext: " << plaintext << endl;
}

void generateEncryptionPair() {
    random_device rd;
    mt19937 gen(rd());
    // Small primes for demonstration (real RSA uses much larger primes)
    
    vector<int> primes = {11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    uniform_int_distribution<> dis(0, primes.size() - 1);
    
    int p = primes[dis(gen)];
    int q = primes[dis(gen)];
    
    while (p == q) {
        q = primes[dis(gen)];
    }

    int n = p * q;
    int phi = (p - 1) * (q - 1);
    int e = findRandomCoprime(phi, n);
    
    if (e == -1) {
        cout << "Error: Could not find valid encryption exponent!" << endl;
        return;
    }
    
    cout << "\n=== Encryption Pair Generated ===" << endl;
    cout << "Primes: p=" << p << ", q=" << q << endl;
    cout << "n: " << n << endl;
    cout << "phi: " << phi << endl;
    cout << "Public key (e, n): (" << e << ", " << n << ")" << endl;
}

void generateDecryptionPair() {
    cout << "Enter encryption exponent e: ";
    int e;
    cin >> e;
    
    cout << "Enter first prime (p): ";
    int p;
    cin >> p;
    
    cout << "Enter second prime (q): ";
    int q;
    cin >> q;
    cin.ignore();
    
    int n = p * q;
    
    // Find d: the modular multiplicative inverse of e modulo phi
    int phi = (p - 1) * (q - 1);
    int d = modularInverse(e, phi);
    
    if (d == -1) {
        cout << "Error: No modular inverse found!" << endl;
        return;
    }
    
    cout << "\n=== RSA Key Pair ===" << endl;
    cout << "n: " << n << endl;
    cout << "Public key (e, n): (" << e << ", " << n << ")" << endl;
    cout << "Private key (d, n): (" << d << ", " << n << ")" << endl;
// Euclidean algorithm for greatest common divisor
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Find a random coprime of e and n that satisfies: gcd(e, phi) = 1 and gcd(e, n) = 1
int findRandomCoprime(int phi, int n) {
    vector<int> validCoprimes;
    
    for (int e = 2; e < phi; e++) {
        if (gcd(e, phi) == 1 && gcd(e, n) == 1) {
            validCoprimes.push_back(e);
        }
    }
    
    if (validCoprimes.empty()) {
        return -1;
    }
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, validCoprimes.size() - 1);
    
    return validCoprimes[dis(gen)];
}

// Extended Euclidean algorithm to find modular multiplicative inverse
// Finds d such that (e * d) mod phi = 1
int modularInverse(int e, int phi) {
    int m0 = phi;
    int x0 = 0, x1 = 1;
    
    if (phi == 1) return 0;
    
    while (e > 1) {
        int q = e / phi;
        int t = phi;
        phi = e % phi;
        e = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    
    if (x1 < 0) x1 += m0;
    return x1;
}

// Binary exponentiation for efficient computation: (base^exp) mod mod    if (x1 < 0) x1 += m0;
    return x1;
}

long long modularExponentiation(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    
    return result;
}
