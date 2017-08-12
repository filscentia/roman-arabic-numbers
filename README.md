
# Roman Numerals - An exercise in programming

To learn a new programming language, the best way I find is to jump in and try and write a useful program.
After reading the basics, and trying 'Hello World'.  Actually trying to solve a problem is a great way of learning.

This project contains programs in different languages to solve the problem of converting Roman to/from Arabic numbers. Simple problem, but can be taxing to get the algorthm correct. 

There is a standard set of test data that can be used to validate any example, and ideally all versions should have an interactive mode to run from the command line. 

## Rules

The following are the principles behind the design of the applications

- Standard Language features only (at level of language as defined)
- Custom libraries 3rd party libraries kept to a minimum
- All code to be ideomatic of the language, but well engineered. i.e. use the language features efficiently - but still well engineered
- For testing, applications should take a simple input file and produce output to a set format
- Command line interactive mode recommened
- One implementation per directory, with an *npm* format `package.json` to define the test, setup and other meta data. Actual build system can be per language - put their invocations into the `package.json` file
- Conversion algorthms do not have to be the ones used for other languages.

## Roman Number syntax

The general priciple of Roman Number is quite simple, *I* means 1, *V* means five so 6 is represented as *VI*.

But what about 4? Typically it is represented as *IV*, but also (look at clocks) it could be written as *IIII*.

Is 45, *XXXXV*, or is it *XLV* or *VL*?  

For this set of test data, the conversion from Roman to Arabic is expected to handle all the above cases. Converting to Roman pick in this case the *XLV* format - the number that is the subtractor, in this case the X, should be of the same order of magnitude.  

## Additional Languages

Current implementations are in the `_general` folder for general purpose languages.

- Javascript using NodeJS 
- Java

Currently planned

- C
- Python
- Ruby
- Go
- php


## Contributing Information

### Pull requests
More then welcome, please create an issue saying what you want to do - or take ownership of an existing one. 
PRs will be accepted if they can pass all the tests. 

### Test format
Data is supplied in a simple file, one input per line. `--file` option is passed that gives the location of this. Format of the file is 

```
DCLXXVIII
xCii
1976
1963
wibble
-9
MMDCLXXVII
846
1343
MCMXXXIII
1201
```

Output should be of the type
```
--START--
DCLXXVIII,678
xCii,92
1976,MCMLXXVI
1963,MCMLXIII
wibble,ERROR
-9,ERROR
MMDCLXXVII,2677
846,DCCCXLVI
1343,MCCCXLIII
MCMXXXIII,1933
1201,MCCI
--END--
```

Note the two error cases marked by `ERROR`

As an example, these are the accpeted command line arguments for Nodejs
```
  -i, --interactive  Run in interactive mode
  -f, --file         File to load the input from
```