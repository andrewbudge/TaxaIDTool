#include <iostream>
#include <fstream>
#include <unordered_map>
#include <set>
#include <string>
#include <getopt.h> 
#include <sstream>  

using namespace std;

// read the alias file and store mappings
unordered_map<string, string> loadAliases(const string& aliasFile) {
    cout << "Creating alias map..." << endl;
    unordered_map<string, string> aliases;
    ifstream file(aliasFile);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);  
        string original, alias;
        ss >> original >> alias;  
        aliases[original] = alias;
    }
    return aliases;
}

// read the remove file and store ID's to be removed
set<string> loadRemoveHeaders(const string& removeFile) {
    set<string> removeHeaders;
    ifstream file(removeFile);
    string line;

    while (getline(file, line)) {
        removeHeaders.insert(line);
    }
    return removeHeaders;
}

// process the input FASTA file
void processFasta(const string& inputFile, const string& outputFile,
                  const unordered_map<string, string>& aliases,
                  const set<string>& removeHeaders) {               
    ifstream input(inputFile);
    ofstream output(outputFile);
    string line;
    bool isHeader = false;
    bool removeThisSeq = false;

    while (getline(input, line)) {
        if (line.empty()) continue;
       
        if (line[0] == '>') {  
            string header = line.substr(1);
            isHeader = true;
            if (aliases.find(header) != aliases.end()) {
                cout << "alias found, rewriting..." << endl;
                line = ">" + aliases.at(header);
            }

            // Check if the header should be removed
            if (removeHeaders.find(header) != removeHeaders.end()) {
                isHeader = false;  // Skip this sequence
                removeThisSeq = true;
            } else {
                removeThisSeq = false;
            }
        }

        // If it's a sequence line under a removed header, skip it
        if (removeThisSeq) {
            continue;  // Skip the sequence associated with the removed header
        }

        // Write the line to the output file if it's not a removed header or assosiated sequence
        if (isHeader || line[0] != '>') {
            output << line << endl;
        }
    }
}

int main(int argc, char* argv[]) {
    string inputFile, outputFile, aliasFile, removeFile;
    int opt;

    // Parse command line arguments
    while ((opt = getopt(argc, argv, "i:o:a:r:")) != -1) {
        switch (opt) {
            case 'i': inputFile = optarg; break;
            case 'o': outputFile = optarg; break;
            case 'a': aliasFile = optarg; break;
            case 'r': removeFile = optarg; break;
            default:
                cerr << "Usage: " << argv[0] << " -i <inputFile> -o <outputFile> -a <aliasFile> -r <removeFile>" << endl;
                return 1;
        }
    }

    if (inputFile.empty() || outputFile.empty()) {
        cerr << "Input and output files are required." << endl;
        return 1;
    }

    cout << "Processing..." << endl;

    unordered_map<string, string> aliases = loadAliases(aliasFile);
    set<string> removeHeaders = loadRemoveHeaders(removeFile);

    processFasta(inputFile, outputFile, aliases, removeHeaders);

    cout << "Processing complete." << endl;
    return 0;
}
