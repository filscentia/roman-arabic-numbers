# Roman and Arabic Numerals - An exercise in programming

To learn a new programming language, the best way I find is to jump in and try and write a useful program. After reading the basics, and trying 'Hello World'.  Actually trying to solve a problem is a great way of learning.

This project contains programs in different languages to solve the problem of converting Roman to/from Arabic numbers. Simple problem, but can be taxing to get the algorthm correct. 

There is a standard set of test data that can be used to validate any example, and ideally all versions would have an interactive mode to run from the command line. 

## Getting Started 

Firslty install the 'just' task runner; specify where to put the tool. If unsure, just use `.` for the current directory. See the [full installation](https://github.com/casey/just#installation) notes

```shell
curl --proto '=https' --tlsv1.2 -sSf https://just.systems/install.sh | bash -s -- --to DEST
```

Then clone this repo, and run `just` to get the welcome text

```shell
git clone https://github.com/filscentia/roman-numerals.git
./just

Roman-Arabic Numeral Conversions

Available Languages:
  c
  java
  javascript
  python

Available recipes:
    build lang           # just test <language>
    build-all            # Build all the programs
    info lang            # Information about the implementation for 'lang'
    info-all             # Show information (the README.md) of all the programs
    list                 # List all languages currently available
    test lang set="full" # just test <language> [setoftests]
    test-all set="full"  # Run all the tests, optional set of tests [full, medium, small]

```

> This repo contains code written in a lot of languages, so you might not have everything that is needed; if any language script fails, the rest carry on. 

To build and test all the languages

```shell
just build-all
just test-all
```

For one specifc language eg, Java with the medium-sized data set

```shell
just build java 
just test java medium
```

### Structure
 - The `code` folder  contains implementations in general purpose languages, eg JavaScript, C, Java
 - The `_test` foler has all the test data, including the answers!

Within `code` there is a directory for each language. Within this there are the program code itself, and also two shell scripts. `run.sh` and `buid.sh`/

These two scripts are common to all languages, to make it easier to run everything. Each language can use whatever make/run system is applicable. 

## Roman Number syntax

The general priciple of Roman Number is quite simple, *I* means 1, *V* means five so 6 is represented as *VI*.

But what about 4? Typically it is represented as *IV*, but also (look at clocks) it could be written as *IIII*.

Is 45, *XXXXV*, or is it *XLV* or *VL*?  

For this set of test data, the conversion from Roman to Arabic is expected to handle all the above cases. Converting to Roman pick in this case the *XLV* format - the number that is the subtractor, in this case the X, should be of the same order of magnitude.  


## Program Design guidelines

The following are the principles behind the design of the applications

- Standard Language features only (at level of language as defined)
- Custom libraries 3rd party libraries kept to a minimum
- All code to be ideomatic of the language, but well engineered. i.e. use the language features efficiently - but still well engineered. 
- For testing, applications should take a simple input file and produce output to a set format (see below)
- Command line interactive mode recommened
- One implementation per directory, `build.sh` and `run.sh` to define the build and test. Actual build system can be per language.
- Conversion algorthms do not have to be the ones used for other languages. Alternatives are suggested. Each run is timed!


## Contributing Information

### Pull requests
More then welcome, please create an issue saying what you want to do - or take ownership of an existing one.  PRs will be accepted if they can pass all the tests! 

When a PR is made, this will trigger a github actions, if this completes ok, then the PR can be submitted for merege (after a review)

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

As an example, these are the accpeted command line arguments for javscript
```
  -i, --interactive  Run in interactive mode
  -f, --file         File to load the input from
```

## Checklist for new languages

- make sure that it can convert of course ;-)
- add any temporary or binary files to the `.gitignore` (put this in the actual program directory)
- ensure that the build.sh first checks any prereqs that are needed
- add to the github actions the required setup steps
    - if this is tricky, please create the PR and then tag me to assist
- one PR per language please
- ideally applications should accept a `--file` argument to give the name of the input data. Output data is sent to stdout.  (though as the `run.sh` script is within the control of each langauge, this is not 100% mandated)