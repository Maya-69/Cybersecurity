# Phase 1: Reconnaissance

## What is Reconnaissance? (Simple Explanation)
Think of it like being a detective before breaking into a building (legally, of course!). You walk around the outside, look at windows, check public records, but you DON'T touch anything yet. You're just gathering information that's already public.

## Goals
- Find subdomains (like developer.blender.org, wiki.blender.org)
- Identify email addresses
- Find technologies they use
- Map out their public infrastructure

---

## Task 1: Google Dorking

### What is it?
Using special Google search tricks to find hidden but public information.

### Commands to Try
```
site:blender.org
site:blender.org filetype:pdf
site:blender.org inurl:admin
site:blender.org intext:"email"
```

### How to Do It
1. Open Google in a browser
2. Type each command above
3. Record what you find

### Results
```

Example:

- Found subdomain: developer.blender.org
- Found subdomain: wiki.blender.org
- Found email format: name@blender.org
```

---

## Task 2: Subdomain Enumeration

### What is it?
Finding all the "sub-websites" under blender.org (like store.blender.org, cloud.blender.org)

### Tools
- **Online**: crt.sh (certificate transparency logs)
- **Command Line**: theHarvester

### How to Do It

#### Method 1: Certificate Transparency (Easy, No Install)
1. Go to https://crt.sh
2. Search for: `%.blender.org`
3. Record all subdomains you find

#### Method 2: theHarvester (Requires Install)
```bash
# Install (if you have Python)
pip install theHarvester

# Run command
theHarvester -d blender.org -b all -l 500
```

### Results
```

Example:
- www.blender.org
- cloud.blender.org
- developer.blender.org
- wiki.blender.org
```

---

## Task 3: WHOIS Lookup

### What is it?
Finding who owns the domain and when it was registered.

### How to Do It
1. Go to https://who.is
2. Search for: blender.org
3. Record the information

### Results
```
Domain Registrar: 
Creation Date: 
Registrant Organization: 
Name Servers: 
```

---

## Task 4: Technology Stack Detection

### What is it?
Finding out what software and frameworks the website uses.

### Tools
- **Browser Extension**: Wappalyzer
- **Online**: builtwith.com

### How to Do It
1. Install Wappalyzer browser extension
2. Visit blender.org
3. Click the Wappalyzer icon
4. Record the technologies

### Results
```
Web Server: 
Programming Language: 
JavaScript Frameworks: 
CDN: 
Analytics: 
```

---

## Task 5: Email Harvesting

### What is it?
Finding email addresses associated with the organization (from public sources only).

### How to Do It
```bash
# Using theHarvester
theHarvester -d blender.org -b google,bing -l 100
```

Or manually search:
- LinkedIn profiles of Blender employees
- GitHub commits
- Public blog posts

### Results
```
[List email addresses or email format]

Example:
- security@blender.org
- support@blender.org
- Email format: firstname@blender.org
```

---

## Summary Report

### Information Gathered
- **Subdomains Found**: [number]
- **Email Addresses**: [number]
- **Technologies Identified**: [number]

### Risk Assessment
- **Critical Findings**: None (passive recon)
- **Notes**: All information gathered from public sources

### Next Steps
Proceed to Phase 2: Scanning (local installation only)

---

## 📝 Notes
- All activities performed are PASSIVE
- No direct interaction with Blender servers
- Only public information collected
- Date completed: ___________
