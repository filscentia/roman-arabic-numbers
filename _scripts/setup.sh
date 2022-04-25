#!/bin/bash
set -ev
set -o pipefail

# --------------------------------------------------------------------------------------------
# Issuing npm install per the listed languages.
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}")" && pwd )"
GENERAL="${DIR}/../code"
 
cd ${GENERAL}
for LNG in c nodejs java;
do
  cd ${GENERAL}/${LNG}
  pwd
  npm install
done
# --------------------------------------------------------------------------------------------