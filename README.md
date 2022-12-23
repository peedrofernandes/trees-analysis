[🇧🇷 Ver em Português](./README-ptbr.md)

# Trees Analysis

## What is this repository about?

This repository is related to a project that was developed during the **Data Structure** discipline of the Bachelor at Computer Science course in University of State of Santa Catarina by [Pedro Fernandes](https://github.com/peedrofernandes) and [André Fidelis](), in November 2022.

Its main goal is to measure the complexity of insertion operations in the most used trees data structures: **AVL tree**, **Red-Black** tree and **B tree**. The project was divided into two parts: One in **C programming language**, the another in **Python**.

## First part (C)

To create and use the trees, we create the structure of each tree in C laguage. They're under the `./trees` directory, and each has its own subfolder. Inside each subfolder, there is a regular version of the tree data structure, composed by functions at `.c` files and data types and function signatures at `.h` files and another version, containing the same functions and data types except that every function receives an additional parameter, which is a pointer to an integer. This aditional parameter has the purpose of count each operation performed by the method. These operations include, among others:
- Logic tests;
- Variable attributions;
- Function calls;
- Return statements.

It is worth note that the tree versions with counter is denoted by `tree-counter.c` or `tree-counter.h` (where 'tree' is the name of the tree itself).

Again inside the `./trees` folder, there is a `main.c` file which responsibility is to use every tree data structure in order to generate files containing the **number of operations** compared to the **input size**. We used an instance of AVL tree, another of Red Black tree and three of B tree, with orders of 1, 5 and 10. We consider **every single size of input from 1 to 1000**, craving to, afterwards, generate a **set of scattered points** in a 2D graphic (that's the second part of the project, that was done in Python). We did two cases for each tree: A **worst case** of insertion operations, which is the case that the input is sorted (requiring more balancing operacions of each tree) and a **average case** that pseudo-randomly generates the input data. To gain statistical significance, we did the average case 10 times, generating random data in each time, and considering the final result as the arithmetic average of every previous result.

## Second part (Python)

Inside `./image-generator` folder, there's 3 elements: 
- A `venv` folder which responsibility is to provide a virtual environment for Python, handling Python packages;
- `generateScatteredPoints.py` - A file which main goal is to generate the corresponding files with with scattered points. It generates two files at `./files` folder:
  - `avgCaseScattered.png` - Average case points scattered across a graphic;
  - `worstCaseScattered.png` - Worst case points scattered across a graphic: 
- `generateRegression.py` - A file which main goal is to use **polynomial regression** to calculate functions that approximates the behavior of the insertion operation complexity of each tree. It generates two files at `./files` folder:
  - `avgCaseFunctions.png` - Average case functions generated by polynomial regressions;
  - `worstCaseFunctions.png` - Worst case functions generated by polynomial regressions.

# How to run

To run the project yourself, simply clone the repository to your local machine, using:

```
git clone https://github.com/peedrofernandes/trees-analysis.git
```

Then navigate to the directory in which you just cloned the repository and run the following command:

```
./run.sh
```

It will automatically run everything that it needs to run. After that, check the result files (especially the .png files) and see if the result is according to this:

![worstCaseScattered](https://user-images.githubusercontent.com/82897023/209393267-f071480d-7624-4a4c-bb6e-ec9c66c74264.png)
![worstCaseFunctions](https://user-images.githubusercontent.com/82897023/209393228-454b65f9-cdb3-4589-a004-a6d8b2557576.png)

![avgCaseScattered](https://user-images.githubusercontent.com/82897023/209393218-152be260-e3d7-4526-8f14-137f04aefc1f.png)
![avgCaseFunctions](https://user-images.githubusercontent.com/82897023/209393263-894f8a1a-21a9-44bb-8a65-5b3b352a2bd4.png)




In case of any errors, please contact me:


[![GitHub](https://img.shields.io/badge/github-%23121011.svg?style=for-the-badge&logo=github&logoColor=white)](https://github.com/peedrofernandes)
[![Gmail](https://img.shields.io/badge/Gmail-D14836?style=for-the-badge&logo=gmail&logoColor=white)](gm.pedro.fernandes@gmail.com)
[![LinkedIn](https://img.shields.io/badge/linkedin-%230077B5.svg?style=for-the-badge&logo=linkedin&logoColor=white)](https://linkedin.com/in/pedrofariafernandes)

Thank you!


