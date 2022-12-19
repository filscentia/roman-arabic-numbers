# Roman and Arabic Numerals

- **Learn Number Systems and Programming**
- **Lots of different langauges all converting Roman to/from Arabic numbers**

[![asciicast](https://asciinema.org/a/491480.svg)](https://asciinema.org/a/491480)


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
  javascript
  _template
  java

Available recipes:
    build lang           # just test <language>
    build-all            # Build all the programs
    info lang            # Information about the implementation for 'lang'
    info-all             # Show information (the README.md) of all the programs
    install lang         # Checks and then installs the language if needed
    list                 # List all languages currently available
    repl lang            # run interactively
    test lang set="full" # just test <language> [setoftests]
    test-all set="full"  # Run all the tests, optional set of tests [full, medium, small]

```

This repo contains code written in a lot of languages, so you might not have everything that is needed; if any language script fails, the rest carry on. 

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

For information on one of the langauges 
```
just info c
```

To install a local toolchain for the language
```
just install python
```


### Structure
 - The `code` folder  contains implementations 
   - `_run.sh` `_build.sh` are required scripts
   - `_reply.sh `_install.sh` are recommended
   - `README.md` is stronly recommended as well.
 - The `_test` foler has all the test data, including the answers!

These scripts are common to all languages, to make it easier to run everything. Each language can use whatever make/run system is applicable. Note that it might be worth running the programs within a language specific docker image. The `_run.sh` script takes an argument which is the absolute path of the test file.

## Roman Number syntax

The general priciple of Roman Number is quite simple, *I* means 1, *V* means five so 6 is represented as *VI*.

But what about 4? Typically it is represented as *IV*, but also (look at clocks) it could be written as *IIII*.

Is 45, *XXXXV*, or is it *XLV* or *VL*?  

For this set of test data, the conversion from Roman to Arabic is expected to handle all the above cases. Converting to Roman pick in this case the *XLV* format - the number that is the subtractor, in this case the X, should be of the same order of magnitude.  


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



## Checklist for new languages

- make sure that it can convert of course ;-)
- add any temporary or binary files to the `.gitignore` (put this in the actual program directory)
- executable shell scripts `_run.sh` `_build.sh` `_repl.sh` 
- `_build.sh` compiles or does any setup needed. It should first check any prereqs that are needed and advises of how to install them; alternatively you may wish to use a docker image to both build and run the code. Apart from docker, please do NOT install software. If you wish to provide and `_install.sh` script then please do - but NOT call this
- `_run.sh` is given a argument that is the full path of the test file to load. Output data must be sent to stdout. 
- `_repl.sh` is the interactive mode letting humans test
- README.md should be present and will be output on  
- add to the github actions the required setup steps
  - if this is tricky, please create the PR and then tag me to assist
- one PR per language please
 Standard Language features only
  - create a new language-folder if a different style is being used eg functional
- Custom libraries 3rd party libraries kept to a minimum
- Conversion algorthms do not have to be the ones used for other languages. Alternatives are suggested. Each run is timed!
- How the code is run eg CLI with arguments, ini file is entirely upto the implementation.

## License

APACHE-2.0
