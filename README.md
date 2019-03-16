# CTC2

# Installation
The scripts can be compiled simply by running the make command which will
result in an executable 'ctc' program. The program can then be invoked from
a unix shell of your choice with './ctc'. The makefile includes a 'make clean'
routine which removes this executable along with any .txt files in the base
directory. .txt files within subdirectories will not be touched.

# Usage
## -caesar <text/file> (offset)
This command runs a simple Caesar Cipher on the input text. The text can
be supplied as a string argument or as an input file to read. The offset
is ADDED to the text to produce the shift. If the shift is known and you
wish to decrypt, use a negative offset. The offset can be ommited to test
all 26 possibilites.

## -pa <text/file> <key/file> (-de)
This command runs a Polyalphabetic Block Cipher on the input text using the
following key. Both the input text and keys can be input using files or an
argument. In the case of a file, each line of the input file is encrypted 
individually using each of the keys. A 5 line input file run against a 10
line key file will produce 50 possible outputs. If the optional '-de' flag
is given at the END of the command, it will instead subtract the key value
from the text.

## -match <text/file> <key/file> (index)
This command attempts to match the string given by the 'key' argument to
the (index)'th matching substring within 'text'. (index) can be ommited, and
in this case it will default to the first match. No output is printed if no
match is found.

## -len \<file\> \<length\>
This command reads through each line of the input file and only outputs the
lines that exactly match length characters.

## -freq <text/file>
This command counts the frequencies of all letters in the input text or file.
The only symbols counted are [a-z][A-Z], and case is ignored.

## -sanitize \<file\>
This command reads the input file and for each line removes all characters
that are not a letter. Uppercase letters are coverted to lowercase. This does
not overwrite the file, and the output should be redirected to a new file.
This should be run if the user wants to use the text as a key for a
polyalphabetic cipher.

