# matrix-calculator-website
A node.js base website that clients can use to carry out basic matrix operations. The homepage is used to collect client data about the matrices and the operation. This is then sent to the web server and the calculation is carried out by a C++ executable that is run in a child_process. The result is then passed back to the browser to modify the page to desiplay the result.

## 0. Proposed works

- None at current.

## 1. Folder structure

- cpp: holds the matrixCalculator directory with the files for building the executable
- public: holds the client side JS, CSS
- views: holds the HTML pages
- index.js: node.js expressJS web server
- calculator.js: launches child_process for running and managing the C++ executable

## 2. Setup

### 2.1 Install

- Ensure that the dependencies are install:
  - A C++ compiler that is C++11 compatible.
  - Node.js (with modules: express, body-parser)
- Create a matrix-calculator directory.
- Download the project from GitHub into this file.
- Install the Node.js modules using the basic package.json file that has been provided. On the command line in the matrix-calculator directory run: npm install
- Build the C++ executable using the files in cpp/matrixCalculator directory and the makefile provided.
- Leave the executable stored in this directory.

### 2.2 Configure

- If desired alter the port that the node.js server will be listneing on. It is located at the bottom of the index.js file and is currentl, 8080.
- If desired create a new package.json with attributes filled out as wanted. Ensure the essential Node.js modules mentioned above are recoreded and installed.

### 2.3 Run

- Using the command line navigate into the matrix-calculator directory (where the index.js is located).
- Run the command: node index.js
- The web server is now running on port 8080 and can be accessed from the brower by entering: http://localhost:8080

## 3. Dependencies

### 3.1 C++ Compiler

- For development of this project the Clang++ compiler was used.
- If using a Mac then the gcc compiler can be installed using the Homebrew package manager by the command (where XY is the version number): brew install gccXY

### 3.2 Node.js

- If on a Mac with Homebrew and Xcode installed then Node.js and its associated package manager npm can be installed through the command: brew install node
- To create a package.json file (which in part is used to document the required dependencies), navigate to matrix-calculator on the command line and run the command following the instructions provided: npm init
- To install Node.js modules locally and save them to the dependency list for the program use the command: npm install module_name --save
