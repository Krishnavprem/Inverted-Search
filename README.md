# Inverted-Search

A C-based inverted search system that indexes words from multiple text files and provides efficient searching capabilities using a hash table implementation.

## 📋 Overview

This project implements an inverted index search engine that processes multiple text files, creates a hash table database of words, and allows users to search for words across all indexed files. The system efficiently tracks word frequencies and file occurrences with collision handling using linked lists.

## ✨ Features

- **Hash Table Indexing**: Uses hash functions for efficient word storage and retrieval
- **Multi-file Support**: Indexes words from multiple text files simultaneously
- **Case Insensitive Search**: Normalizes all words to lowercase for consistent searching
- **Collision Handling**: Implements separate chaining with linked lists
- **Database Operations**:
  - Create database from input files
  - Search for words across all indexed files
  - Display complete database
  - Update database with new files
  - Save/Load database to/from file
- **Memory Management**: Proper cleanup of all dynamically allocated memory
- **Input Validation**: Validates file formats and prevents duplicates

## 🏗️ Project Structure
inverted-search/
├── main.c # Main program with menu interface
├── assist.c # Helper functions (hashing, node creation, insertion)
├── invert.c # Database operations (create, search, update, save)
├── main.h # Header file with declarations and structures
├── Makefile # Build automation (to be created)
├── file1.txt # Sample input file 1
├── file2.txt # Sample input file 2
├── file3.txt # Sample input file 3
├── file4.txt # Sample input file 4
└── README.md # This file

## 🧠 Data Structures

### 1. **File List Node**
```c
typedef struct node {
    char filename[MAX_FILENAME_LEN];
    struct node *link;
} file_list;
2. Main Node (Word Node)
c
typedef struct main {
    char word[MAX_WORD_LEN];
    int filecount;
    struct main *main_link;      // Next word in hash bucket
    struct sub *sub_link;        // Pointer to sub-nodes (files)
} main_node;
3. Sub Node (File Node)
c
typedef struct sub {
    char word[MAX_FILENAME_LEN]; // Actually stores filename
    int wordcount;               // Frequency in this file
    struct sub *sub_link;        // Next file for this word
} sub_node;
🔧 Compilation & Usage
Compilation
bash
gcc main.c assist.c invert.c -o inverted_search
Basic Usage
bash
# Index multiple files
./inverted_search file1.txt file2.txt file3.txt

# Index single file
./inverted_search documents.txt

# With sample files
./inverted_search file1.txt file2.txt file3.txt file4.txt
Program Menu Options
Create Database: Index words from input files

Search Database: Search for a word across all files

Display Database: Show complete indexed data

Update Database: Add new file to existing database

Save Database: Export database to file

Exit: Cleanup and exit program

📊 Sample Output
Search Results
text
Word found at the index 42
Word: hello | Files: 1
   ->file1.txt : 4
Database Display
text
-----DATABASE-----
42 Word: hello             | Files: 1
   ->file1.txt | 4
23 Word: world             | Files: 1
   ->file1.txt | 3
67 Word: test              | Files: 1
   ->file1.txt | 2
