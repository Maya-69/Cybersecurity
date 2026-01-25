# RSA Encryption

RSA (Rivest–Shamir–Adleman) is an asymmetric cryptography algorithm that uses a pair of public and private keys for encryption and decryption.

## How It Works

### Theory
RSA is based on the difficulty of factoring large numbers. The algorithm uses two keys:
- **Public Key (e, n)**: Used for encryption, shared with everyone
- **Private Key (d, n)**: Used for decryption, kept secret

**Key Generation:**
1. Choose two large prime numbers: p and q
2. Compute n = p × q
3. Compute φ(n) = (p-1) × (q-1)
4. Choose e such that 1 < e < φ(n) and gcd(e, φ(n)) = 1
5. Compute d = e^(-1) mod φ(n) (modular multiplicative inverse)

**Encryption Formula:**
```
Ciphertext = (Plaintext^e) mod n
```

**Decryption Formula:**
```
Plaintext = (Ciphertext^d) mod n
```

### Example
- **p = 61, q = 53**
- **n = 3233, φ(n) = 3120**
- **e = 17** (chosen, gcd(17, 3120) = 1)
- **d = 2753** (inverse of 17 mod 3120)

**Encrypt "HI":**
- H (7): 7^17 mod 3233 = 558
- I (8): 8^17 mod 3233 = 2790
- Ciphertext: `558 2790`

**Decrypt:**
- 558^2753 mod 3233 = 7 (H)
- 2790^2753 mod 3233 = 8 (I)
- Plaintext: `HI`

## Features
- Asymmetric encryption (public/private key pair)
- Secure key exchange without pre-shared secrets
- Mathematically proven security (factoring hardness)
- Used in real-world applications (HTTPS, digital signatures)
- Uppercase letters only (A-Z)

## File
- `code/RSA_Encryption.cpp`

## Build (Windows, PowerShell)
Using the existing helper:
```powershell
.\build.bat .\RSA_Encryption.cpp
```

Manual build with MSVC `cl.exe` (if needed):
```powershell
cl.exe /EHsc /nologo /Fe:build\RSA_Encryption\RSA_Encryption.exe .\RSA_Encryption.cpp
```

## Run
```powershell
.\build\RSA_Encryption\RSA_Encryption.exe
```

## Options

### P: Generate Encryption Pair
Generates a random public key (e, n) using random prime selection.

**Output:**
```
Primes: p=61, q=53
n: 3233
phi: 3120
Public key (e, n): (17, 3233)
```

### Q: Generate Decryption Pair
Calculates the private key d from public key e and primes p, q.

**Input:**
```
Encryption exponent e: 17
First prime (p): 61
Second prime (q): 53
```

**Output:**
```
n: 3233
Public key (e, n): (17, 3233)
Private key (d, n): (2753, 3233)
Verification: (e * d) mod phi = 1
```

### E: Encrypt
Encrypts plaintext using the public key (e, n).

**Example:**
- Plaintext: `HELLO`
- Public key: `(17, 3233)`
- Ciphertext: `558 2790 1671 1671 2262`

### D: Decrypt
Decrypts ciphertext using the private key (d, n).

**Example:**
- Ciphertext: `558 2790 1671 1671 2262`
- Private key: `d = 2753`
- Modulus: `n = 3233`
- Plaintext: `HELLO`

## Security Notes
- **Key Size**: Demonstration uses small primes (up to 97). Real RSA uses 2048+ bit keys.
- **Integer Size**: Limited by C++ `long long` (64-bit). Production systems use arbitrary precision.
- **Vulnerability**: For small n, the ciphertext can be brute-forced
- **Modern Use**: RSA is slower than symmetric encryption; typically used for key exchange

## Implementation Details
- **Modular Exponentiation**: Uses binary exponentiation for efficiency
- **Extended Euclidean Algorithm**: Computes modular multiplicative inverse for d
- **Random Selection**: Randomly picks valid e values from all coprimes

- **Kasiski Examination**: Can break if key length is discovered
- **Index of Coincidence**: Statistical method to estimate key length
- **Historical Use**: Used by military forces until WWII (Enigma superseded it)
- **Key Management**: Security depends on keeping the key secret and changing it regularly

