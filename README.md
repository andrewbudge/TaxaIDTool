# TaxaIDTool

# TaxaIDTool

#### TaxaIDTool is a C++ program designed for Bioinformatics pipelines. It manipulates the sequence ID's in fasta files by either renaming the ID's or removing ID's and their associated sequences.

## **Installation**

Clone this repository with the following command line:
```
git clone https://github.com/andrewbudge/TaxaIDTool.git
```

##  **Compilation**

Make sure you have a C++ compiler installed (g++ recommended). Run the following command to compile the source code:

```
g++ TaxaIDTool.cpp -o TaxaIDTool
```

This will create the executable file.

## **Usage**

Once complied, TaxaIDTool is usable from the command line:

```
./TaxaIDTool -i <input_file> -a <alias_file> -r <remove_file> -o <output_file>
```

### **Arguments**

- `-i <input_file>`:  
    The path to the **input FASTA file**. This file should contain sequences in standard FASTA format, where each sequence begins with a header line starting with `>`.
    
- `-o <output_file>`:  
    The **path to the output file** where the processed FASTA content will be saved. The program will write the renamed and filtered sequences to this file.
    
- `-a <alias_file>`:  
    The **file containing the alias list**. This file should have one header-alias pair per line, with the original header and the new alias separated by a space. Example:

- `-r <remove_file>`:  
    The **file containing the taxa to be removed**. This file should contain one header per line. Any sequences with headers listed in this file will be removed from the output. 
