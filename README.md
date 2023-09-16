# Eugene Onegin README

## Description
This GitHub repository contains a simple text processing tool that takes input from a file and provides three different text sorting options: lexicographical sorting, lexicographical sorting starting from the last character, and displaying the original text. To use this tool, you can specify the sorting mode using one of the following options: `[-s|-r|-o]`, and provide input and output file paths as follows:

```bash
.\build\EugeneOnegin.exe [-s|-r|-o] -input <input_file> -output <output_file>
```

## Usage
- `-s`: Sort the text lexicographically.
- `-r`: Sort the text lexicographically starting from the last character.
- `-o`: Display the original text.

## Installation
1. Clone this repository to your local machine using the following command:
   ```bash
   git clone https://github.com/nniikon/EugeneOnegin
   ```

2. Navigate to the project directory and compile the project:
   ```bash
   cd .\EugeneOnegin
   make
   ```

3. Run the tool with your desired options. For example, to sort the text lexicographically from an input file and save it to an output file:
   ```bash
   .\build\EugeneOnegin.exe -s -input input.txt -output output.txt
   ```

4. You can also choose other sorting options (`-r` or `-o`) as per your requirements.

Feel free to contribute to this project or provide feedback. Happy sorting!
