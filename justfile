# Main justfile to run all the scripts
#
# To install 'just' see https://github.com/casey/just#installation
# Apache-2.0

# Ensure all properties are exported as shell env-vars
set export

# set the current directory, and the location of the test dats
DIR := justfile_directory()
TEST := join(justfile_directory(),"_test")

# record some of the colour formatting
bold :='\033[1m'
normal:='\033[0m'
red:='\033[0;31m'
blue:='\033[0;34m'

# Default with basic intro text
_default:
    @echo "{{blue}}{{bold}}Roman-Arabic Numeral Conversions{{normal}}" && echo
    @echo "Available Languages:"
    @just list
    @echo
    @just --list

# List all languages currently available
list: 
    #!/bin/bash
    set -eu -o pipefail
    for i in $(find $DIR/code/ -mindepth 1 -maxdepth 1 -type d)
    do 
        echo "  $(basename ${i})"
    done

# Run all the tests, optional set of tests [full, medium, small]
test-all set="full": (_all "test" set)

# Build all the programs
build-all: (_all "build" )

# Show information (the README.md) of all the programs
info-all: (_all "info" ) 


_all action set="":
    #!/bin/bash
    set -eu -o pipefail
    for i in $(find $DIR/code/ -mindepth 1 -maxdepth 1 -type d)
    
    do 
        just {{action}} $(basename ${i}) {{set}}
    done

# Information about the implementation for 'lang'
info lang:
    #!/bin/bash
    set -eu -o pipefail
    README=${DIR}/code/{{lang}}/README.md
    if [ -f ${README} ]; then
       cat "${README}"
    else
       echo "!! {{lang}} does not have a README.md" 
    fi

# Run tests for the specified language
# just test <language> [setoftests]
test lang set="full":
    #!/bin/bash
    set -eu -o pipefail
    echo "   Running tests {{set}}"
    pushd ${DIR}/code/{{lang}} > /dev/null 
    if [ -f 'run.sh' ]; then
        echo -e "\n{{bold}}>> {{lang}}{{normal}}"
        /usr/bin/time -f "   {{lang}} - Run complete in %e seconds" ./run.sh "${TEST}/input-{{set}}.csv" > {{lang}}_test.log
        cat {{lang}}_test.log | awk '/--START--/{flag=1;next}/--END--/{flag=0;}flag' | diff --side-by-side  --suppress-common-lines - "${TEST}/results-{{set}}.csv"
    
        if [ $? == 0 ]; then
            echo "   {{lang}} - Correct results"
            # cat ${LANG}.log
        else 
            echo "   {{lang}} - Fail; some errors"
        fi
        echo -e "{{bold}}<< {{lang}}{{normal}}\n"
    else 
        echo "!! {{lang}} does not have a run.sh" 
    fi
    popd > /dev/null 

# Build the code for the specified language
# just test <language> 
build lang:
    #!/bin/bash
    set -eu -o pipefail

    pushd ${DIR}/code/{{lang}} > /dev/null 
    if [ -f 'build.sh' ]; then
        echo -e "\n{{bold}}>> {{lang}}{{normal}}"
        ./build.sh
        echo -e "{{bold}}<< {{lang}}{{normal}}\n"
    else 

        echo "!! {{lang}} does not have a build.sh" 
    fi
    popd > /dev/null

# run interactively
repl lang:
    #!/bin/bash
    set -eu -o pipefail

    pushd ${DIR}/code/{{lang}} > /dev/null 
    if [ -f 'repl.sh' ]; then
        ./repl.sh
    else 
        echo "!! {{lang}} does not have a repl.sh" 
    fi
    popd > /dev/null    