# TESS - Text Entry Suggestion System

TESS is a collaborative project developed by Kawtar El Mamoun and myself. The primary goal of TESS is to create a user-friendly human-machine interface that offers intelligent word suggestions for incomplete user input. To achieve this, we have employed hash tables as the underlying data structure. TESS is designed to capture and store user-entered words, keeping track of the most frequently used ones. Additionally, the system ensures spelling accuracy and allows users to add custom names and acronyms.

## Introduction

TESS aims to enhance text entry experiences by providing contextually relevant word suggestions as users type. The system leverages the power of hash tables, allowing efficient storage and retrieval of words for prediction. Our primary focus was to develop a user-friendly interface that seamlessly integrates with the typing process, helping users compose text more quickly and accurately.

## Key Features

1. **Intelligent Word Prediction**: TESS offers three highly relevant word suggestions based on the user's incomplete input. The system builds a prediction dictionary from user-entered words and a pre-existing French dictionary.

2. **Dynamic Word Collection**: As users input words, TESS dynamically captures and stores them in the prediction dictionary. Frequent words receive higher priority in the suggestions.

3. **Spell Check and Auto-Correction**: To ensure accurate suggestions, TESS performs real-time spell checks on user input. The system automatically corrects misspelled words when possible.

4. **Custom Entries**: TESS allows users to add custom names, acronyms, or specific vocabulary to the prediction dictionary, enabling personalized suggestions.

5. **User-Friendly Interface**: The interface is designed to be intuitive and visually appealing. Users can seamlessly interact with the system and easily access its features.

## Directory Content

- **REPORT EL-MAMOUN-GACHET.pdf**: Our project report; we highly recommend reading it to understand the program's functionality.
- **Sujet.pdf**: The project statement provided on the School's website.
- **main_avec_interface.c**: Main code file with interactions based on both the terminal and an interactive graphical user interface.
- **main_sans_interface.c**: Main code file with interactions based solely on the terminal (in case of graphical module issues or personal preference).
- **hachage.c / hachage.h**: Module containing useful structures and functions for the hash table.
- **liste.c / liste.h**: Module containing functions to manipulate linked lists.
- **user.c / user.h**: Module containing functions to handle user requests.
- **Makefile**: File enabling modular compilation and maintaining code structure during compilation.
- **mines.png**: Image used for the graphical interface.
- **README**: This document.
- **mots_courants.txt**: Initial prediction dictionary provided on CAMPUS.
- **dictionnaire.txt**: French language dictionary.

## Execution Instructions

To execute the code with a terminal interface, use the following commands:
```
make all_without_interface
./all_without_interface
```

To execute the code with a GTK interface, you first need to install the GTK library:
```
sudo apt-get update
sudo apt-get install libgtk-3-dev
```

Once the library is installed, you can display the interactive interface with the following commands:
```
make all_w_interface
./all_w_interface
```

## Choosing the Hash Table Size

Compression Factor: fc = k / n (where fc = 0.75 is the optimal value)
k = number of occupied slots
n = total number of slots (equals the size of the table)
The sizes of the hash tables are prime numbers to reduce collisions and avoid common divisors.
