# Polyalphabetic (Vigenère) Cipher

A polyalphabetic substitution cipher that uses a keyword to encrypt text. Each letter in the keyword shifts different letters in the plaintext by varying amounts.

## How It Works

### Theory
The Vigenère Cipher is a polyalphabetic substitution cipher, meaning multiple substitution alphabets are used. Unlike the Caesar Cipher (which uses a single shift), the Vigenère Cipher repeats a keyword to determine the shift for each letter.

**Encryption Formula:**
```
Encrypted_i = (Plaintext_i + Key_(i mod key_length)) mod 26
```

**Decryption Formula:**
```
Decrypted_i = (Ciphertext_i - Key_(i mod key_length) + 26) mod 26
```

### Key Table (Vigenère Square)
The Vigenère square is a 26×26 grid where:
- Rows represent plaintext letters (A-Z)
- Columns represent key letters (A-Z)
- The intersection gives the ciphertext letter

**Example with Key = "LEMON":**
```
Key repeats: L E M O N L E M O N ...
Plaintext:  A T T A C K A T D A W N
Keyshift:   11 4 12 14 13 11 11 4 12 14 23 13
Ciphertext: L X F O P V L X P O T A
```

### Plaintext vs Ciphertext
- **Plaintext**: `ATTACK AT DAWN`
- **Key**: `LEMON`
- **Ciphertext**: `LXFOPV EF RNHR`

## Features
- Encrypts and decrypts using a keyword (Vigenère)
- Uppercase-only processing; non-letters are preserved (spaces, punctuation)
- Interactive prompt: choose Encrypt or Decrypt, then enter text and key
- Much stronger than Caesar Cipher (exponential keyspace with key length)

## File
- `code/polyalphabetic_cipher.cpp`

## Build (Windows, PowerShell)
Using the existing helper:
```powershell
.\build.bat .\polyalphabetic_cipher.cpp
```

Manual build with MSVC `cl.exe` (if needed):
```powershell
cl.exe /EHsc /nologo /Fe:build\polyalphabetic_cipher\polyalphabetic_cipher.exe .\polyalphabetic_cipher.cpp
```

## Run
```powershell
.\build\polyalphabetic_cipher\polyalphabetic_cipher.exe
```

## Examples

### Encrypt
- Choice: `E`
- Text: `ATTACK AT DAWN`
- Key: `LEMON`
- Output: `LXFOPV EF RNHR`

### Decrypt
- Choice: `D`
- Text: `LXFOPV EF RNHR`
- Key: `LEMON`
- Output: `ATTACK AT DAWN`

## Security Notes
- **Strength**: Much stronger than Caesar Cipher (key-dependent keyspace)
- **Vulnerability**: Still vulnerable to frequency analysis with long ciphertexts
- **Kasiski Examination**: Can break if key length is discovered
- **Index of Coincidence**: Statistical method to estimate key length
- **Historical Use**: Used by military forces until WWII (Enigma superseded it)
- **Key Management**: Security depends on keeping the key secret and changing it regularly

## Caesar vs Polyalphabetic

| Feature | Caesar | Polyalphabetic (Vigenère) |
|---------|--------|---------------------------|
| Key Type | Single shift (0-25) | Keyword or phrase |
| Encryption | Same shift for all letters | Different shift per letter |
| Security | Very weak (26 possibilities) | Much stronger (26^key_length) |
| Frequency Analysis | Easy to break | Harder to break initially |
| Pattern Recognition | Obvious letter patterns | Hides frequency patterns |
| Real-world Use | None (insecure) | Historical military use |
| Key Length Impact | None (always 1) | Exponential increase |

## Notes
- Input is uppercased automatically; key is uppercased too
- Only A–Z are shifted; other characters pass through unchanged
- Non-alphabetic characters are preserved in their original positions
- Key repeats cyclically throughout the plaintext
