# Caesar Cipher

A simple substitution cipher that shifts each letter by a fixed number of positions in the alphabet.

## How It Works

### Theory
The Caesar Cipher is one of the oldest and simplest encryption methods. Each letter is shifted by a fixed number (the key) along the alphabet.

**Encryption Formula:**
```
Encrypted = (Original + Key) mod 26
```

**Decryption Formula:**
```
Decrypted = (Encrypted - Key + 26) mod 26
```

**Example (Key = 3):**
- A → D
- B → E
- Z → C (wraps around)

### Plaintext vs Ciphertext
- **Plaintext**: `ATTACK AT DAWN`
- **Key**: 3
- **Ciphertext**: `DWWDFN DW GDZQ`

## Features
- Encrypts and decrypts using a shift key (integer 0-25)
- Uppercase-only processing; non-letters are preserved (spaces, punctuation)
- Interactive prompt: choose Encrypt or Decrypt, then enter text and key
- Simple but vulnerable to brute force (only 26 possible keys)

## File
- `code/caesar_cipher.cpp`

## Build (Windows, PowerShell)
Using the existing helper:
```powershell
.\build.bat .\caesar_cipher.cpp
```

Manual build with MSVC `cl.exe` (if needed):
```powershell
cl.exe /EHsc /nologo /Fe:build\caesar_cipher\caesar_cipher.exe .\caesar_cipher.cpp
```

## Run
```powershell
.\build\caesar_cipher\caesar_cipher.exe
```

## Examples

### Encrypt (Key = 3)
- Choice: `E`
- Text: `ATTACK AT DAWN`
- Key: `3`
- Output: `DWWDFN DW GDZQ`

### Decrypt (Key = 3)
- Choice: `D`
- Text: `DWWDFN DW GDZQ`
- Key: `3`
- Output: `ATTACK AT DAWN`

## Security Notes
- **Vulnerability**: Only 26 possible keys (trivial brute force)
- **No Key Distribution Problem**: Unlike polyalphabetic, uses only one number
- **Pattern Recognition**: Frequency analysis reveals patterns
- **Historical Use**: Used by Julius Caesar in military communications
- **Modern Use**: Educational only, never use for real security

## Caesar vs Polyalphabetic

| Feature | Caesar | Polyalphabetic (Vigenère) |
|---------|--------|---------------------------|
| Key Type | Single shift (0-25) | Keyword or phrase |
| Encryption | Same shift for all letters | Different shift per letter |
| Security | Very weak (26 possibilities) | Much stronger (large keyspace) |
| Complexity | O(1) per letter | O(key_length) per letter |
| Frequency Analysis | Easy to break | Harder to break |
| Real-world Use | None (insecure) | Historical military use |

## Notes
- Input is uppercased automatically
- Only A–Z are shifted; other characters pass through unchanged
- Non-alphabetic characters are preserved in their original positions
