# Steganography (Steghide)

Practical steganography using Steghide on Windows.

## 1) Download the Windows Binary
1. Open: http://steghide.sourceforge.net/download.php
2. Download the Windows ZIP (e.g., steghide-0.5.1-win32.zip).
3. Save it to your PC.

## 2) Extract the ZIP
1. Right-click the ZIP and choose Extract All.
2. Extract to a folder like:
   - `C:\Tools\steghide`

## 3) Run Steghide from Command Prompt
1. Open Command Prompt.
2. Navigate to the extracted folder:
   ```bash
   cd C:\Tools\steghide
   ```
3. Test installation:
   ```bash
   steghide --help
   ```

## 4) Embed Data into an Image
```bash
steghide embed -cf cover.jpg -ef secret.txt
```

## 5) Extract Hidden Data
```bash
steghide extract -sf stg.jpg
```
If embedded with passphrase, you'll be prompted to enter it.

## 6) Embed with Passphrase Protection
```bash
steghide embed -cf original.jpg -ef secret.txt -p mypassphrase
```

## 7) Extract with Passphrase
```bash
steghide extract -sf stg.jpg -p mypassphrase
```

## 8) Get Info About Embedded Data
```bash
steghide info stg.jpg
```
Shows the filename and size of hidden data without extracting.

## 9) Batch Processing
```bash
# Embed multiple files
steghide embed -cf image1.jpg -ef file1.txt -p pass1
steghide embed -cf image2.jpg -ef file2.txt -p pass2

# Extract all
steghide extract -sf image1.jpg -p pass1 -f
steghide extract -sf image2.jpg -p pass2 -f
```

## 10) Supported Formats
- **Images:** JPG, BMP, WAV, AU
- **File Types:** Any text, binary, or document files

## Use Cases
- Secure message exchange (combine with OpenSSL encryption)
- Covert communication
- Watermarking documents
- Security testing & auditing

## Notes
- Always use passphrases for real scenarios
- Combine with encryption (OpenSSL) for defense-in-depth
- Use `-f` flag to overwrite output files without prompting

