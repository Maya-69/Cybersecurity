# Polyalphabetic (Vigenère) Cipher

Minimal repo for a simple, interactive Vigenère cipher implementation in C++.

## Features
- Encrypts and decrypts using a keyword (Vigenère).
- Uppercase-only processing; non-letters are preserved (spaces, punctuation).
- Interactive prompt: choose Encrypt or Decrypt, then enter text and key.

## File
- `codes/polyalphabetic_cipher.cpp`

## Build (Windows, PowerShell)
Using the existing helper:
```powershell
.\n+build.bat .\codes\polyalphabetic_cipher.cpp
```

Manual build with MSVC `cl.exe` (if needed):
```powershell
cl.exe /EHsc /nologo /Fe:build\polyalphabetic_cipher\polyalphabetic_cipher.exe .\codes\polyalphabetic_cipher.cpp
```

## Run
```powershell
.
build\polyalphabetic_cipher\polyalphabetic_cipher.exe
```

## Examples
- Encrypt
	- Choice: `E`
	- Text: `ATTACK AT DAWN`
	- Key: `LEMON`
	- Output: `LXFOPV EF RNHR`

- Decrypt
	- Choice: `D`
	- Text: `LXFOPV EF RNHR`
	- Key: `LEMON`
	- Output: `ATTACK AT DAWN`

## Notes
- Input is uppercased automatically; key is uppercased too.
- Only A–Z are shifted; other characters pass through unchanged.