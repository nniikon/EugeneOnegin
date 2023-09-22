# Eugene Onegin
<p align='center'>
    <img src="./media/giphy.gif" alt="drawing" width="400"/>
</p>

## Description
This GitHub repository contains a simple text processing tool that takes input from a file and provides three different text sorting options: lexicographical sorting, lexicographical sorting starting from the last character, and displaying the original text. To use this tool, specify the sorting mode with one of the following options [-s|-r|-o], and provide the input and output file paths as follows:

```bash
.\build\EugeneOnegin.exe [-s|-r|-o] [-qsort|-bubble] [-t|-h] -input <input_file> -output <output_file> 
```

## Usage
- `-s`: Sort the text lexicographically.
- `-r`: Sort the text lexicographically starting from the last character.
- `-o`: Display the original text (set by default).
- `[-qsort]`: use quick sort algorithm (set by default).
- `[-bubble]`: use bubble sort algorithm.
- `-h`: for help.

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

## Note on Character Handling

The program focuses specifically on alphabetic characters and is not case-sensitive. It ignores any special characters, digits, or spaces, concentrating only on the letters within the lines.

Feel free to contribute to this project or provide feedback. Happy sorting!
