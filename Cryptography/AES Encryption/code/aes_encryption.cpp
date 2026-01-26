#include <iostream>
#include <string>

using namespace std;

class AESCryptography {

    private:

        // **Private Members and Constants**

        // AES S-Box (Substitution Box) standard
        static const unsigned char sBox[256];

        // Keys and Round Constants
        unsigned char mainKey[16];        // Original 128-bit key (16 bytes)
        unsigned char roundKeys[176];     // 11 round keys × 16 bytes = 176 bytes
        static const unsigned char Rcon[10];  // Round constants

        // State Matrix
        unsigned char state[4][4];  // 4×4 state matrix for current block

        // **Private Methods**

        // AES Transformation Methods
        void rotWord(unsigned char* word);      // Rotate 4-byte word left by 1
        void subWord(unsigned char* word);      // Apply S-box to 4-byte word
        unsigned char getRcon(int round);       // Get round constant

        // AES Round Operations
        void addRoundKey(int round);                           // XOR state with round key
        void copyToState(unsigned char* input);                // Copy 16-byte input to state
        void copyFromState(unsigned char* output);             // Copy state to 16-byte output

        // AES Round Transformations
        void subBytes();  // Apply S-box to all 16 bytes in state
        void shiftRows();  // Cyclically shift rows left row 0 not shifted, row 1 by 1, row 2 by 2, row 3 by 3
        void mixColumns();  // Mix columns transformation

        // Helper method for mix columns transformation
        unsigned char gfMul(unsigned char a, unsigned char b);  // Galois Field multiplication

    public:

        // **Public Members and Constants**

        // **Public Methods**

        // Key setting and expansion
        void setKey(unsigned char* key);        // Store the main key
        void keyExpansion();                    // Generate all round keys

        // Encryption process
        void encrypt(unsigned char* input, unsigned char* output);  // Main encryption function



};

// Definition of the static member sBox
const unsigned char AESCryptography::sBox[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xd9,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x7e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

// Definition of the static member Rcon (Round Constants)
const unsigned char AESCryptography::Rcon[10] = {
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36
};

// Copy 16 bytes from the input key to the mainKey
void AESCryptography::setKey(unsigned char* key) {
    for (int i = 0; i < 16; i++) {
        mainKey[i] = key[i];
    }
}

// Rotate a 4-byte word left by 1 byte
void AESCryptography::rotWord(unsigned char* word) {
    unsigned char temp = word[0];
    word[0] = word[1];
    word[1] = word[2];
    word[2] = word[3];
    word[3] = temp;
}

// Apply S-Box to 4bytes
void AESCryptography::subWord(unsigned char* word) {
    for (int i = 0; i < 4; i++) {
        word[i] = sBox[word[i]];
    }
}

// Return Round Constants
unsigned char AESCryptography::getRcon(int round) {
    return Rcon[round - 1];  // round is 1-indexed, array is 0-indexed
}

// Generate all round keys from the main key
void AESCryptography::keyExpansion() {
    // Step 1: Copy the original key into first 16 bytes of roundKeys
    for (int i = 0; i < 16; i++) {
        roundKeys[i] = mainKey[i];
    }
    
    // Step 2: Generate the remaining 160 bytes (176 - 16 = 160)
    // Process in 4-byte words
    for (int i = 16; i < 176; i += 4) {
        // Create temporary word from previous 4 bytes
        unsigned char temp[4];
        temp[0] = roundKeys[i - 4];
        temp[1] = roundKeys[i - 3];
        temp[2] = roundKeys[i - 2];
        temp[3] = roundKeys[i - 1];
        
        // Every 16 bytes (every 4th word), apply special transformation
        if ((i - 16) % 16 == 0) {
            rotWord(temp);              // Rotate left by 1
            subWord(temp);              // S-box substitution
            temp[0] ^= getRcon((i - 16) / 16 + 1); // XOR first byte with Rcon
        }
        
        // XOR temp with bytes from 16 positions back
        roundKeys[i]     = roundKeys[i - 16] ^ temp[0];
        roundKeys[i + 1] = roundKeys[i - 15] ^ temp[1];
        roundKeys[i + 2] = roundKeys[i - 14] ^ temp[2];
        roundKeys[i + 3] = roundKeys[i - 13] ^ temp[3];
    }
}

// Converts 16-byte linear array into 4×4 matrix in column-major order
void AESCryptography::copyToState(unsigned char* input) {
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            state[row][col] = input[col * 4 + row];
        }
    }
}

// Reverse of copyToState() - converts 4×4 matrix back to 16-byte array
void AESCryptography::copyFromState(unsigned char* output) {
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            output[col * 4 + row] = state[row][col];
        }
    }
}

// XOR the state matrix with the round key for the given round
void AESCryptography::addRoundKey(int round) {
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            state[row][col] ^= roundKeys[round * 16 + col * 4 + row];
        }
    }
}

// Apply S-box substitution to all bytes in the state matrix
void AESCryptography::subBytes() {
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            state[row][col] = sBox[state[row][col]];
        }
    }
}

// Shift rows of the state matrix left by varying offsets -- row 0 not shifted, row 1 by 1, row 2 by 2, row 3 by 3
void AESCryptography::shiftRows() {
    unsigned char temp;
    
    // Row 0: No shift
    
    // Row 1: Shift left by 1
    temp = state[1][0];
    state[1][0] = state[1][1];
    state[1][1] = state[1][2];
    state[1][2] = state[1][3];
    state[1][3] = temp;
    
    // Row 2: Shift left by 2
    temp = state[2][0];
    state[2][0] = state[2][2];
    state[2][2] = temp;
    temp = state[2][1];
    state[2][1] = state[2][3];
    state[2][3] = temp;
    
    // Row 3: Shift left by 3 (or equivalently, shift right by 1)
    temp = state[3][3];
    state[3][3] = state[3][2];
    state[3][2] = state[3][1];
    state[3][1] = state[3][0];
    state[3][0] = temp;
}

// Mix columns of the state matrix using Galois Field multiplication 
unsigned char AESCryptography::gfMul(unsigned char a, unsigned char b) {
    unsigned char result = 0;
    unsigned char highBit;
    
    for (int i = 0; i < 8; i++) {
        if (b & 1) {
            result ^= a;
        }
        highBit = a & 0x80;  // Check if high bit is set
        a <<= 1;              // Shift left
        if (highBit) {
            a ^= 0x1B;        // Reduce modulo AES polynomial
        }
        b >>= 1;
    }
    
    return result;
}

// Mix columns transformation For each column, perform matrix multiplication in GF(2^8)
void AESCryptography::mixColumns() {
    unsigned char temp[4];
    
    for (int col = 0; col < 4; col++) {
        // Copy current column
        temp[0] = state[0][col];
        temp[1] = state[1][col];
        temp[2] = state[2][col];
        temp[3] = state[3][col];
        
        // Apply matrix multiplication in GF(2^8)
        state[0][col] = gfMul(temp[0], 2) ^ gfMul(temp[1], 3) ^ temp[2] ^ temp[3];
        state[1][col] = temp[0] ^ gfMul(temp[1], 2) ^ gfMul(temp[2], 3) ^ temp[3];
        state[2][col] = temp[0] ^ temp[1] ^ gfMul(temp[2], 2) ^ gfMul(temp[3], 3);
        state[3][col] = gfMul(temp[0], 3) ^ temp[1] ^ temp[2] ^ gfMul(temp[3], 2);
    }
}

// Main AES encryption function
void AESCryptography::encrypt(unsigned char* input, unsigned char* output) {
    // Step 1: Load input into state matrix
    copyToState(input);
    
    // Step 2: Initial round - just AddRoundKey with round 0
    addRoundKey(0);
    
    // Step 3: Main rounds (rounds 1-9)
    for (int round = 1; round <= 9; round++) {
        subBytes();
        shiftRows();
        mixColumns();
        addRoundKey(round);
    }
    
    // Step 4: Final round (round 10) - NO MixColumns!
    subBytes();
    shiftRows();
    addRoundKey(10);
    
    // Step 5: Copy state back to output
    copyFromState(output);
}



// Main Obviously 
int main() {
    AESCryptography aes;
    cout << "AES Encryption Module Initialized." << endl;
    
    // Example 16-byte key (exactly 16 bytes)
    unsigned char key[16] = {'T','h','a','t','s',' ','m','y',' ','K','u','n','g',' ','F','u'};
    aes.setKey(key);
    aes.keyExpansion();
    
    // Example 16-byte plaintext (exactly 16 bytes)
    unsigned char input[16] = {'T','w','o',' ','O','n','e',' ','N','i','n','e',' ','T','w','o'};
    unsigned char output[16];
    
    aes.encrypt(input, output);
    
    cout << "Encrypted Output: ";
    for (int i = 0; i < 16; i++) {
        printf("%02x ", output[i]);
    }
    cout << endl;
    
    return 0;
}