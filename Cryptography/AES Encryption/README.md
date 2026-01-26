# AES Encryption

Advanced Encryption Standard (AES) - A symmetric block cipher that encrypts data in 128-bit blocks using 128, 192, or 256-bit keys.

## How It Works

### Theory
  
Best Videos - [AES: How to Design Secure Encryption - Spanning Tree](https://youtu.be/C4ATDMIz5wc?si=hlsgPSHvobk3YhMq) 
              [AES Explained (Advanced Encryption Standard) - Computerphile](https://youtu.be/O4xNJsjtN6E?si=cx2B7fjDf_oAQkBg)
              [AES Encryption and Decryption - NESO Academy](https://youtu.be/4KiwoeDJFiA?si=SuvD245wEVfh5T30)

AES is a symmetric block cipher adopted by the U.S. government in 2001. It operates on fixed-size blocks (128 bits) and uses a series of transformations repeated over multiple rounds.

**AES-128 Structure:**
- **Block Size**: 128 bits (16 bytes)
- **Key Size**: 128 bits (16 bytes)
- **Rounds**: 10 rounds

**Main Transformations (per round):**
1. **SubBytes**: Byte substitution using S-Box (non-linear transformation)
2. **ShiftRows**: Cyclically shift rows left (0, 1, 2, 3 positions)
3. **MixColumns**: Matrix multiplication in Galois Field GF(2⁸)
4. **AddRoundKey**: XOR with round key derived from main key

**Example Transformation:**
```
State Matrix (4×4 bytes):
[00 11 22 33]      [SubBytes]     [63 7c 77 7b]
[44 55 66 77]   →  [ShiftRows]  → [55 c9 9d 92]
[88 99 aa bb]      [MixColumns]   [...transformed...]
[cc dd ee ff]      [AddRoundKey]  [...final state...]
```

### Plaintext vs Ciphertext
- **Plaintext**: `00112233445566778899aabbccddeeff` (hex)
- **Key**: `000102030405060708090a0b0c0d0e0f` (hex)
- **Ciphertext**: `69c4e0d86a7b0430d8cdb78070b4c55a` (hex)

## Features
- Full AES-128 encryption and decryption implementation
- Processes 16-byte blocks with 16-byte keys
- Key expansion generates 11 round keys (176 bytes)
- Implements all core AES transformations and their inverses
- Validated against NIST test vectors

## File
- `code/aes_encryption.cpp`

## Build (Windows, PowerShell)
Using the existing helper:
```powershell
.\build.bat .\aes_encryption.cpp
```

Manual build with MSVC `cl.exe` (if needed):
```powershell
cl.exe /EHsc /nologo /Fe:build\aes_encryption\aes_encryption.exe .\aes_encryption.cpp
```

## Run
```powershell
.\build\aes_encryption\aes_encryption.exe
```

## Examples

### NIST Test Vector
```
Key:       000102030405060708090a0b0c0d0e0f
Plaintext: 00112233445566778899aabbccddeeff
Encrypted: 69c4e0d86a7b0430d8cdb78070b4c55a
Decrypted: 00112233445566778899aabbccddeeff ✓
```

### Text Example
```
Key:       "Thats my Kung Fu" (16 bytes)
Plaintext: "Two One Nine Two" (16 bytes)
Encrypted: 1fa8cf85152415 13a8f52727e6399b75 (hex)
Decrypted: "Two One Nine Two" ✓
```

## Security Notes
- **Strength**: Currently considered secure against all known practical attacks
- **Key Space**: 2¹²⁸ possible keys (340,282,366,920,938,463,463,374,607,431,768,211,456)
- **Brute Force**: Computationally infeasible with current technology
- **Algorithm**: Public and peer-reviewed (not security through obscurity)
- **Modern Use**: Industry standard for sensitive data (banking, government, SSL/TLS)
- **Block Mode**: This implementation uses ECB mode (educational - use CBC/GCM in production)

## AES vs Simple Ciphers

| Feature | AES | Caesar Cipher |
|---------|-----|---------------|
| Key Size | 128/192/256 bits | 5 bits (0-25) |
| Block Size | 128 bits (16 bytes) | 1 character |
| Security | Military-grade | Trivially broken |
| Complexity | 10/12/14 rounds | Single shift |
| Key Space | 2¹²⁸ to 2²⁵⁶ | 26 keys |
| Attack Resistance | Resistant to all known attacks | Broken by frequency analysis |
| Real-world Use | Ubiquitous (HTTPS, VPNs, etc.) | Educational only |

## Technical Details
- **S-Box**: Pre-computed 256-byte substitution table (multiplicative inverse in GF(2⁸))
- **Key Expansion**: Rijndael key schedule with rotation, S-Box, and round constants
- **Galois Field Math**: All operations in GF(2⁸) with polynomial 0x11B
- **State Matrix**: Column-major order (bytes filled vertically, then horizontally)

## Notes
- Input must be exactly 16 bytes (padding required for variable-length data)
- Key must be exactly 16 bytes for AES-128
- Output is binary ciphertext (typically represented in hex)
- This implementation is for educational purposes - use tested libraries in production
