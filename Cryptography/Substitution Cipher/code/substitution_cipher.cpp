#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cmath>

using namespace std;

class SubstitutionCipher {
private:
    string cipherText;
    string currentText;
    map<char, vector<int>> letterIndexes;  // Track positions of each letter
    map<char, char> substitutions;         // Track cipher -> plain mappings
    
    // English letter frequency percentages (standard)
    map<char, double> englishFreq = {
        {'a', 8.167}, {'b', 1.49}, {'c', 2.782}, {'d', 4.253},
        {'e', 12.702}, {'f', 2.228}, {'g', 2.015}, {'h', 6.094},
        {'i', 6.966}, {'j', 0.153}, {'k', 0.772}, {'l', 4.025},
        {'m', 2.406}, {'n', 6.749}, {'o', 7.507}, {'p', 1.929},
        {'q', 0.095}, {'r', 5.987}, {'s', 6.327}, {'t', 9.056},
        {'u', 2.758}, {'v', 0.978}, {'w', 2.360}, {'x', 0.150},
        {'y', 1.974}, {'z', 0.074}
    };
    
public:
    SubstitutionCipher(const string& cipher) {
        cipherText = cipher;
        currentText = cipher;
        buildIndexMap();
    }
    
    // Build index map for each letter
    void buildIndexMap() {
        for (int i = 0; i < cipherText.length(); i++) {
            char ch = tolower(cipherText[i]);
            if (ch >= 'a' && ch <= 'z') {
                letterIndexes[ch].push_back(i);
            }
        }
    }
    
    // Get frequency analysis of ORIGINAL cipher text (counts)
    map<char, int> getFrequencyCounts() {
        map<char, int> freq;
        for (char c : cipherText) {
            char ch = tolower(c);
            if (ch >= 'a' && ch <= 'z') {
                freq[ch]++;
            }
        }
        return freq;
    }
    
    // Get frequency as percentages
    map<char, double> getFrequencyPercent() {
        map<char, int> counts = getFrequencyCounts();
        map<char, double> percentages;
        
        int total = 0;
        for (const auto& p : counts) {
            total += p.second;
        }
        
        if (total == 0) return percentages;
        
        for (const auto& p : counts) {
            percentages[p.first] = (p.second * 100.0) / total;
        }
        
        return percentages;
    }
    
    // Sort letters by frequency percentage (descending)
    vector<pair<char, double>> getSortedFrequency() {
        map<char, double> freq = getFrequencyPercent();
        vector<pair<char, double>> sortedFreq(freq.begin(), freq.end());
        
        sort(sortedFreq.begin(), sortedFreq.end(), 
             [](const pair<char, double>& a, const pair<char, double>& b) {
                 return a.second > b.second;
             });
        
        return sortedFreq;
    }
    
    // Find best match for cipher letter based on frequency
    char findBestMatch(char cipherChar, const map<char, double>& cipherFreq, 
                       map<char, bool>& usedPlain) {
        double cipherPerc = cipherFreq.at(cipherChar);
        char bestMatch = 'a';
        double minDiff = 999999.0;
        
        for (const auto& p : englishFreq) {
            char plainChar = p.first;
            double plainPerc = p.second;
            
            if (usedPlain[plainChar]) continue;
            
            double diff = fabs(cipherPerc - plainPerc);
            if (diff < minDiff) {
                minDiff = diff;
                bestMatch = plainChar;
            }
        }
        
        return bestMatch;
    }
    
    // Generate substitution mapping based on frequency analysis
    map<char, char> generateFrequencyMapping() {
        map<char, char> mapping;
        map<char, double> cipherFreq = getFrequencyPercent();
        map<char, bool> usedPlain;
        
        // Initialize all as unused
        for (char c = 'a'; c <= 'z'; c++) {
            usedPlain[c] = false;
        }
        
        // Sort cipher letters by frequency
        vector<pair<char, double>> sorted = getSortedFrequency();
        
        // Match each cipher letter to closest English frequency
        for (const auto& p : sorted) {
            char cipherChar = p.first;
            char plainChar = findBestMatch(cipherChar, cipherFreq, usedPlain);
            mapping[cipherChar] = plainChar;
            usedPlain[plainChar] = true;
        }
        
        return mapping;
    }
    
    // Show frequency analysis
    void showFrequencyAnalysis() {
        map<char, int> counts = getFrequencyCounts();
        map<char, double> percentages = getFrequencyPercent();
        vector<pair<char, double>> sorted = getSortedFrequency();
        
        cout << "\n=== Ciphertext Frequency Analysis ===" << endl;
        cout << "Letter frequencies in the ciphertext:" << endl;
        
        // Show in alphabetical order like the table
        cout << "\nLetter\t";
        for (char c = 'a'; c <= 'm'; c++) {
            cout << c << "\t";
        }
        cout << endl;
        
        cout << "%\t";
        for (char c = 'a'; c <= 'm'; c++) {
            if (percentages.count(c)) {
                printf("%.3f\t", percentages[c]);
            } else {
                cout << "0.000\t";
            }
        }
        cout << endl;
        
        cout << "\nLetter\t";
        for (char c = 'n'; c <= 'z'; c++) {
            cout << c << "\t";
        }
        cout << endl;
        
        cout << "%\t";
        for (char c = 'n'; c <= 'z'; c++) {
            if (percentages.count(c)) {
                printf("%.3f\t", percentages[c]);
            } else {
                cout << "0.000\t";
            }
        }
        cout << endl;
        
        cout << "\n=== Suggested Substitutions (Based on Frequency Matching) ===" << endl;
        map<char, char> mapping = generateFrequencyMapping();
        
        cout << "Cipher -> Plain (Cipher%, English%)" << endl;
        for (const auto& p : sorted) {
            char cipherChar = p.first;
            double cipherPerc = p.second;
            char plainChar = mapping[cipherChar];
            double plainPerc = englishFreq[plainChar];
            
            printf("%c -> %c (%.3f%%, %.3f%%)\n", 
                   cipherChar, plainChar, cipherPerc, plainPerc);
        }
    }
    
    // Rebuild current text from original based on all substitutions
    void rebuildCurrentText() {
        currentText = cipherText;
        for (const auto& sub : substitutions) {
            char from = sub.first;
            char to = sub.second;
            
            if (letterIndexes.find(from) == letterIndexes.end()) {
                continue;
            }
            
            for (int idx : letterIndexes[from]) {
                if (isupper(cipherText[idx])) {
                    currentText[idx] = toupper(to);
                } else {
                    currentText[idx] = to;
                }
            }
        }
    }
    
    // Substitute a letter
    void substitute(char from, char to) {
        from = tolower(from);
        to = tolower(to);
        
        if (letterIndexes.find(from) == letterIndexes.end()) {
            return;
        }
        
        substitutions[from] = to;
        rebuildCurrentText();
    }
    
    // Manual substitution with user input
    void manualSubstitute() {
        cout << "Enter cipher letter to replace: ";
        char from;
        cin >> from;
        
        cout << "Enter target plain letter: ";
        char to;
        cin >> to;
        cin.ignore();
        
        from = tolower(from);
        to = tolower(to);
        
        if ((from < 'a' || from > 'z') || (to < 'a' || to > 'z')) {
            cout << "Invalid letters." << endl;
            return;
        }
        
        substitute(from, to);
        cout << "Substitution done: " << from << " -> " << to << endl;
    }
    
    // Show current decrypted text
    void showCurrent() {
        cout << "\n=== Current Text ===" << endl;
        cout << currentText << endl;
    }
    
    // Show all substitutions made
    void showSubstitutions() {
        if (substitutions.empty()) {
            cout << "No substitutions made." << endl;
            return;
        }
        
        cout << "\n=== Substitutions Made ===" << endl;
        for (const auto& sub : substitutions) {
            cout << sub.first << " -> " << sub.second << endl;
        }
    }
    
    // Undo a substitution
    void undoSubstitution() {
        if (substitutions.empty()) {
            cout << "Nothing to undo." << endl;
            return;
        }
        
        cout << "Enter cipher letter to undo: ";
        char undo;
        cin >> undo;
        cin.ignore();
        
        undo = tolower(undo);
        
        if (substitutions.find(undo) == substitutions.end()) {
            cout << "That substitution does not exist." << endl;
            return;
        }
        
        substitutions.erase(undo);
        rebuildCurrentText();
        cout << "Undo completed for: " << undo << endl;
    }
    
    // Show menu and handle choices
    void run() {
        // Ask if user wants frequency analysis
        cout << "\nDo you want analysis of most frequent characters? (y/n): ";
        char wantAnalysis;
        cin >> wantAnalysis;
        cin.ignore();
        
        if (tolower(wantAnalysis) == 'y') {
            showFrequencyAnalysis();
            
            cout << "\nDo you want to substitute based on this analysis? (y/n): ";
            char apply;
            cin >> apply;
            cin.ignore();
            
            if (tolower(apply) == 'y') {
                substitutions.clear();  // Clear any previous substitutions
                
                // Use frequency-based mapping
                substitutions = generateFrequencyMapping();
                rebuildCurrentText();
                
                cout << "\nFrequency-based substitutions applied!" << endl;
                showCurrent();
            }
        }
        
        // Main menu loop
        while (true) {
            cout << "\n=== MENU ===" << endl;
            cout << "1. Show current text" << endl;
            cout << "2. Substitute a letter" << endl;
            cout << "3. Show substitutions made" << endl;
            cout << "4. Undo a substitution" << endl;
            cout << "5. Show frequency analysis" << endl;
            cout << "6. Reset all substitutions" << endl;
            cout << "7. Exit" << endl;
            cout << "Choice: ";
            
            int choice;
            cin >> choice;
            cin.ignore();
            
            switch (choice) {
                case 1:
                    showCurrent();
                    break;
                case 2:
                    manualSubstitute();
                    break;
                case 3:
                    showSubstitutions();
                    break;
                case 4:
                    undoSubstitution();
                    break;
                case 5:
                    showFrequencyAnalysis();
                    break;
                case 6:
                    substitutions.clear();
                    currentText = cipherText;
                    cout << "All substitutions reset." << endl;
                    break;
                case 7:
                    cout << "Exiting." << endl;
                    return;
                default:
                    cout << "Invalid choice." << endl;
                    break;
            }
        }
    }
};

int main() {
    cout << "=== Substitution Cipher Decryption Tool ===" << endl;
    cout << "Enter cipher text: " << endl;
    
    string cipherText;
    getline(cin, cipherText);
    
    SubstitutionCipher cipher(cipherText);
    cipher.run();
    
    return 0;
}
