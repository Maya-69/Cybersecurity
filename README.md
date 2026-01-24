# Cybersecurity

A collection of C++ cryptography and security tools.

## Projects

### Polyalphabetic Cipher
A C++ implementation of polyalphabetic encryption and decryption using the Vigenère cipher algorithm.

**Features:**
- Encrypt messages using a given key
- Decrypt encrypted messages
- Handles both alphabetic and non-alphabetic characters

**Usage:**
```bash
.\build.bat .\polyalphabetic_cipher.cpp
.\build\polyalphabetic_cipher\polyalphabetic_cipher.exe
```

## Build

Requires:
- Microsoft Visual Studio with MSVC compiler
- Windows 10+ with Windows SDK

Build using the batch script:
```bash
.\build.bat <filename.cpp>
```

Compiled executables are output to `build/<filename>/` directory.

## License

MIT
