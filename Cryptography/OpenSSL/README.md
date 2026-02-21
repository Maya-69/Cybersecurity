# OpenSSL  

Practical cryptography using OpenSSL library.

## Setup
- OpenSSL Location: `D:\OpenSSL\OpenSSL-Win64`
- Include: `D:\OpenSSL\OpenSSL-Win64\include`
- Libraries: `D:\OpenSSL\OpenSSL-Win64\lib`


###  Digital Signatures (RSA)
**Files:**
- `code/digital_signature.cpp` - C++ implementation
- `private_key.pem` / `public_key.pem` - RSA key pair
- `something.txt` - Sample message
- `something.txt.sig` - Digital signature

**Commands:**
```bash
# Sign a file
openssl pkeyutl -sign -inkey private_key.pem -in something.txt -out something.txt.sig

# Verify signature
openssl pkeyutl -verify -inkey public_key.pem -pubin -in something.txt.sig -sigfile something.txt.sig
```

## More OpenSSL Ideas (Learning)

### A. Key Management & Formats
Learn key formats, conversions, and passphrase protection.
- Generate encrypted private key (AES-256):
	- `openssl genpkey -algorithm RSA -aes256 -out private_key_enc.pem`
- Remove passphrase (lab use only):
	- `openssl pkey -in private_key_enc.pem -out private_key_plain.pem`
- Convert PEM to DER:
	- `openssl pkey -in private_key.pem -outform DER -out private_key.der`

### B. Certificates & CSR Workflow
Understand X.509 certificates and self-signed certs.
- Create a CSR:
	- `openssl req -new -key private_key.pem -out request.csr`
- Create a self-signed certificate (lab only):
	- `openssl req -x509 -key private_key.pem -in request.csr -out certificate.crt -days 365`
- Inspect certificate details:
	- `openssl x509 -in certificate.crt -text -noout`

### C. File Encryption (Symmetric)
Learn AES encryption with salt + IV.
- Encrypt a file:
	- `openssl enc -aes-256-cbc -salt -in something.txt -out something.txt.enc`
- Decrypt a file:
	- `openssl enc -aes-256-cbc -d -in something.txt.enc -out something.txt.dec`

### D. Digital Signatures (Hash + Sign)
Compare `pkeyutl` and `dgst` methods.
- Sign with hash:
	- `openssl dgst -sha256 -sign private_key.pem -out something.txt.sha256.sig something.txt`
- Verify:
	- `openssl dgst -sha256 -verify public_key.pem -signature something.txt.sha256.sig something.txt`

### E. Key Fingerprints & Integrity
Learn how to fingerprint keys and verify integrity.
- Public key fingerprint:
	- `openssl pkey -in public_key.pem -pubin -outform DER | openssl dgst -sha256`
- File checksum:
	- `openssl dgst -sha256 something.txt`

### F. Hybrid Encryption Demo (RSA + AES)
Real-world pattern: encrypt data with AES, encrypt AES key with RSA.
1) Generate random AES key and IV.
2) Encrypt file with AES.
3) Encrypt AES key using RSA public key.
4) Decrypt AES key with RSA private key, then decrypt file.

### G. Password Hashing (KDF)
Understand password-based key derivation.
- Derive a key from password (PBKDF2):
	- `openssl enc -aes-256-cbc -pbkdf2 -iter 100000 -salt -in something.txt -out something.pbkdf2.enc`

### H. Basic TLS Lab (Optional)
Use OpenSSL to create a local TLS server and client.
- Create server key + cert (self-signed).
- Run server:
	- `openssl s_server -key private_key.pem -cert certificate.crt -accept 8443`
- Connect client:
	- `openssl s_client -connect localhost:8443`

