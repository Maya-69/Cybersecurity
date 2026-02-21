# Phase 2: Scanning

## What is Scanning? (Simple Explanation)
Now you're knocking on doors and windows to see which ones are unlocked. You're testing what services are running and what ports are open. BUT - we're ONLY doing this on YOUR OWN computer where Blender is installed.

## Goals
- Find what ports Blender opens on your local machine
- Identify what network connections Blender makes
- Check if Blender listens for incoming connections

---

## Task 1: Install Blender

### How to Do It
1. Download Blender from https://www.blender.org/download/
2. Install it on your computer
3. Note the installation path

### Results
```
Installation Path: C:\Program Files\Blender Foundation\Blender [version]
Version Installed: 
Installation Date: 
```

---

## Task 2: Local Port Scanning

### What is it?
Checking if Blender opens any network ports when it runs.

### Tool: Nmap

#### Install Nmap
1. Download from https://nmap.org/download.html
2. Install with default settings
3. Add to PATH

#### Scan Steps

**Before Starting Blender:**
```bash
# Scan your own computer to see baseline
nmap -sT -p- localhost
```

**After Starting Blender:**
```bash
# Run Blender application
# Then scan again
nmap -sT -p- localhost
```

### Results
```
Ports Open Before Blender:
[List ports here]

Ports Open After Blender:
[List ports here]

New Ports Opened by Blender:
[Any differences?]
```

---

## Task 3: Network Traffic Analysis

### What is it?
Watching what Blender "talks to" on the internet when you use it.

### Tool: Wireshark

#### Install Wireshark
1. Download from https://www.wireshark.org/download.html
2. Install with Npcap (for Windows)
3. Run as Administrator

#### How to Capture Traffic

1. **Start Wireshark**
   - Select your active network interface (usually WiFi or Ethernet)
   - Click the blue shark fin to start capturing

2. **Start Blender**
   - Open Blender
   - Do some normal activities (open a project, use a tool)
   - Check for updates

3. **Stop Capture**
   - Stop Wireshark after 2-3 minutes

4. **Filter Results**
   - In Wireshark filter bar, type: `http || https || dns`

### Results
```
Connections Made by Blender:

1. Domain: 
   IP Address: 
   Purpose: (Update check? Asset download?)

2. Domain:
   IP Address:
   Purpose:

3. [Add more if found]

Suspicious Activity: Yes/No
Explanation: 
```

---

## Task 4: Process and Permissions Check

### What is it?
Checking if Blender runs with elevated (Administrator) privileges.

### Windows Method

#### Check Running Privileges
1. Start Blender
2. Open Task Manager (Ctrl+Shift+Esc)
3. Go to "Details" tab
4. Right-click column headers > Select "Elevated"
5. Find blender.exe
6. Check if "Elevated" column shows "Yes"

### Results
```
Runs as Administrator: Yes/No
User Privileges Required: 
Risk Level: 

If runs as Admin:
  - Risk: High (should not need admin privileges)
  - Recommendation: Run as standard user

If runs as standard user:
  - Risk: Low
  - Status: Normal operation
```

---

## Task 5: File and Directory Permissions

### What is it?
Checking if Blender's files have secure permissions.

### Windows Method

1. Navigate to Blender installation folder
2. Right-click on main folder > Properties > Security tab
3. Check who has permissions

### Results
```
Installation Directory: 

Users with Access:
- SYSTEM: [Full Control/Read/Write]
- Administrators: [Full Control/Read/Write]
- Users: [Read/Execute]
- Authenticated Users: [permissions]

Configuration Files Location: 
  (Usually: C:\Users\[YourName]\AppData\Roaming\Blender Foundation)

Config Permissions:
- Owner: 
- Access: 

Risk Assessment:
- [ ] Only user can modify config files (Good)
- [ ] Any user can modify config files (Bad - potential malware injection)
```

---

## Task 6: Dependency Analysis

### What is it?
Checking if Blender uses outdated or vulnerable libraries.

### Manual Check

1. **Find Blender's Dependencies**
   - Navigate to Blender installation folder
   - Check the `/lib` or `/2.xx/python/lib` folder

2. **List Major Libraries**
   ```
   Python version: 
   OpenSSL version: 
   FFmpeg version: 
   Other libraries: 
   ```

3. **Check for Known Vulnerabilities**
   - Go to https://nvd.nist.gov/vuln/search
   - Search for each library + version
   - Example: "Python 3.10.2 CVE"

### Results
```
Library Analysis:

1. Python [version]
   - Known CVEs: 
   - Severity: 
   - Exploitable in Blender context: Yes/No

2. OpenSSL [version]
   - Known CVEs: 
   - Severity: 
   - Exploitable in Blender context: Yes/No

3. [Other libraries]

Overall Risk: Low/Medium/High
Recommendation: 
```

---

## Summary Report

### Scanning Results
- **Ports Opened**: [number]
- **Network Connections**: [number]
- **Privilege Level**: Admin/Standard User
- **Vulnerable Dependencies**: [number]

### Risk Findings
| Finding | Severity | Evidence |
|---------|----------|----------|
| [e.g., Runs as Admin] | High | Task Manager shows elevated |
| [e.g., Outdated OpenSSL] | Medium | Version X.X.X has CVE-XXXX |

### Next Steps
Proceed to Phase 3: Vulnerability Analysis

---

## 📝 Notes
- All scans performed on LOCAL machine only
- No remote scanning of blender.org
- Date completed: ___________
