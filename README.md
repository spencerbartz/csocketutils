# csocketutils
Socket interface written in C to make networking and programming in C less painful.

# Usage (To work on the socket module only)
1. Find or create an empty directory and clone the repo with the following command:

2. $ git clone https://github.com/spencerbartz/csocketutils.git

3. Locate the directory named "csocketutils/" in your empty directory from step 1

4. Enter the csocketutils/ directory from the command line like this: $ cd csocketutils

5. Once inside the directory, run the following: 
   $ make clean    (Removes residual compiled files)
   $ make cleanlib (Removes libraries used by csockutils)
   $ make all      (Compiles csocketutils.c, creates libsocketutils.a library)
   $ make package  (Wraps library for usage by programmers)

