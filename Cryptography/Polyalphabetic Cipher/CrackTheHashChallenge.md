# Crack The Hash - TryHackMe Level 1 & 2

- https://tryhackme.com/room/crackthehash

## Prerequisites

**GPU Recommended** (but CPU works too)
- GPU: ~100x faster than CPU
- NVIDIA/AMD/INTEL....
- CPUs: You'll wait longer, but it works

**System Specs Used**
- CPU: Ryzen 5 3600
- GPU: RX 6600 - OpenCL (ROCm had issues, OpenCL worked great)
- Wordlist: rockyou.txt (official from GitHub)
- Optional: rockyou2024.txt (50GB compressed → 150GB uncompressed, takes way longer but covers more passwords) - (~10+hrs)

**Get Rockyou Wordlist**
- Small: https://github.com/brannondorsey/naive-hashcat/releases/download/data/rockyou.txt (~150MB)
- Big: https://github.com/hkphh/rockyou2024.txt?tab=readme-ov-file (~150GB)

## Hashcat Reference

https://hashcat.net/hashcat/

### Common Flags

| Flag | Values | Meaning |
|---|---|---|
| `-m` | 0, 100, 1000, 1400, 1600, 1800, 3200 | Hash mode (MD5=0, SHA1=100, NTLM=1000, SHA256=1400, DES=1600, sha512crypt=1800, bcrypt=3200) |
| `-a` | 0, 1, 3, 6, 7 | Attack mode (0=wordlist, 1=combination, 3=mask, 6=hybrid wordlist+mask, 7=hybrid mask+wordlist) |
| `-w` | 1, 2, 3, 4 | Workload profile (1=Low, 2=Default, 3=High, 4=Nightmare) |
| `-o` | filename | Output file for cracked results |
| `--show` | - | Show cracked results from potfile |
| `--potfile-path` | path | Location of potfile |
| `-O` | - | Kernel loops optimization |
| `-S` | - | Slower hash mode (for large wordlists) |
| `--username` | - | Ignore username field |
| `-r` | rules_file | Apply rules from file |

### Hash Modes (Common)

| Hash Type | Code |
|---|---|
| MD5 | 0 |
| SHA1 | 100 |
| SHA256 | 1400 |
| SHA512 | 1700 |
| NTLM | 1000 |
| LM Hash | 3000 |
| bcrypt | 3200 |
| Kerberos | 13100 |
| WPA2-PBKDF2 | 22000 |

### Attack Modes

| Mode | Code | Description |
|---|---|---|
| Wordlist | 0 | Dictionary attack with wordlist |
| Combination | 1 | Combine two wordlists |
| Mask | 3 | Brute-force with custom charset |
| Hybrid (WL+Mask) | 6 | Wordlist + mask suffix |
| Hybrid (Mask+WL) | 7 | Mask prefix + wordlist |

### Mask Character Sets

| Placeholder | Characters |
|---|---|
| `?l` | Lowercase (a-z) |
| `?u` | Uppercase (A-Z) |
| `?d` | Digits (0-9) |
| `?s` | Special chars (!@#$...) |
| `?a` | All (l+u+d+s) |

### Example Usage

```bash
# MD5 wordlist attack
hashcat -m 0 -a 0 hash.txt wordlist.txt

# SHA256 mask attack
hashcat -m 1400 -a 3 hash.txt ?l?l?l?l?d?d?s?s

# NTLM hybrid attack with high workload
hashcat -m 1000 -a 6 -w 3 hashes.txt wordlist.txt ?d?d?d?d

# Show results from potfile
hashcat -m 0 --show hashes.txt
```

---

## Level 1: Hash Identification + Answers

### Q1: 48bb6e862e54f2a795ffc4e541caed4d
**Identified**: MD5  
<details>
<summary>▶ Command</summary>

```bash
.\hashcat.exe -m 0 -a 0 "48bb6e862e54f2a795ffc4e541caed4d" rockyou.txt -w 3 --show
```

</details>

<details>
<summary>🔓 Answer</summary>

**easy**
</details>

---

### Q2: CBFDAC6008F9CAB4083784CBD1874F76618D2A97
**Identified**: SHA1  
<details>
<summary>▶ Command</summary>

```bash
.\hashcat.exe -m 100 -a 0 "CBFDAC6008F9CAB4083784CBD1874F76618D2A97" rockyou.txt -w 3 --show
```

</details>

<details>
<summary>🔓 Answer</summary>

**password123**
</details>

---

### Q3: 1C8BFE8F801D79745C4631D09FFF36C82AA37FC4CCE4FC946683D7B336B63032
**Identified**: SHA256  
<details>
<summary>▶ Command</summary>

```bash
.\hashcat.exe -m 1400 -a 0 "1C8BFE8F801D79745C4631D09FFF36C82AA37FC4CCE4FC946683D7B336B63032" rockyou.txt -w 3 --show
```

</details>

<details>
<summary>🔓 Answer</summary>

**letmein**
</details>

---

### Q4: $2y$12$Dwt1BZj6pcyc3Dy1FWZ5ieeUznr71EeNkJkUlypTsgbX1H68wsRom
**Identified**: Bcrypt (Blowfish)  
<details>
<summary>▶ Command</summary>

```bash
.\hashcat.exe -m 3200 -a 0 '$2y$12$Dwt1BZj6pcyc3Dy1FWZ5ieeUznr71EeNkJkUlypTsgbX1H68wsRom' rockyou.txt -w 3 --show
```

</details>

<details>
<summary>🔓 Answer</summary>

**bleh**
</details>

---

### Q5: 279412f945939ba78ce0758d3fd83daa
**Identified**: MD5  
<details>
<summary>▶ Command</summary>

```bash
.\hashcat.exe -m 0 -a 0 "279412f945939ba78ce0758d3fd83daa" rockyou.txt -w 3 --show
```

</details>

<details>
<summary>🔓 Answer</summary>

**Eternity22**
</details>

---

## Level 2: Hashcat Wordlist Attack

Use rockyou.txt from GitHub. If password not found, ~~dont~~ try rockyou2024.txt (bigger, slower).

### Q1: F09EDCB1FCEFC6DFB23DC3505A882655FF77375ED8AA2D1C13F640FCCC2D0C85
**Type**: SHA256 (-m 1400)

<details>
<summary>▶ Command</summary>

```bash
.\hashcat.exe -m 1400 -a 0 "F09EDCB1FCEFC6DFB23DC3505A882655FF77375ED8AA2D1C13F640FCCC2D0C85" rockyou.txt -w 3 --show
```

</details>

<details>
<summary>🔓 Answer</summary>

**paule**
</details>

---

### Q2: 1DFECA0C002AE40B8619ECF94819CC1B
**Type**: NTLM (-m 1000)

<details>
<summary>▶ Command</summary>

```bash
.\hashcat.exe -m 1000 -a 0 "1DFECA0C002AE40B8619ECF94819CC1B" rockyou.txt -w 3 --show
```

</details>

<details>
<summary>🔓 Answer</summary>

**n63umy8lkf4i**
</details>

---

### Q3: $6$aReallyHardSalt$6WKUTqzq.UQQmrm0p/T7MPpMbGNnzXPMAXi4bJMl9be.cfi3/qxIf.hsGpS41BqMhSrHVXgMpdjS6xeKZAs02.
**Type**: SHA512crypt (-m 1800) | Salt embedded in hash

<details>
<summary>▶ Command</summary>

```bash
.\hashcat.exe -m 1800 -a 0 '$6$aReallyHardSalt$6WKUTqzq.UQQmrm0p/T7MPpMbGNnzXPMAXi4bJMl9be.cfi3/qxIf.hsGpS41BqMhSrHVXgMpdjS6xeKZAs02.' rockyou.txt -w 3
```

</details>

⚠️ **Note**: Use single quotes in PowerShell to prevent $ expansion

<details>
<summary>🔓 Answer</summary>

**waka99**
</details>

---

### Q4: e5d8870e5bdd26602cab8dbe07a942c8669e56d6 : tryhackme
**Type**: HMAC-SHA1 (-m 160) | Format: hash:salt

<details>
<summary>▶ Command</summary>

```bash
.\hashcat.exe -m 160 -a 0 'e5d8870e5bdd26602cab8dbe07a942c8669e56d6:tryhackme' rockyou.txt -w 3 --show
```

</details>

<details>
<summary>🔓 Answer</summary>

**481616481616**
</details>

---

## Notes

- **Level 1**: Simple hashes crack instantly with online tools but can also be verified with hashcat 
- **Level 2**: Use hashcat + GPU for speed
- **rockyou.txt** Solves all challenges
- **rockyou2024.txt** (150GB uncompressed) is overkill for this room but fun to experiment with
- Always use **single quotes** in PowerShell for hashes with `$` signs
