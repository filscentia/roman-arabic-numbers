#!/bin/bash
set -ev
set -o pipefail


# --------------------------------------------------------------------------------------------
# Issuing test per all the languages
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}")" && pwd )"

TEST="${DIR}/../_test"
GENERAL="${DIR}/../code"

cd ${GENERAL}
for LNG in c nodejs java;
do
  cd "${GENERAL}/${LNG}"
  pwd
  npm test -- --file "${TEST}/input.csv" | awk '/--START--/{flag=1;next}/--END--/{flag=0;}flag' > temp.out
  diff --side-by-side  --suppress-common-lines temp.out "${TEST}/results.csv"
  rm temp.out

  if [ $? == 0 ]; then
    echo
    echo ">>>> ${LNG} - Correct results"
    echo 
  else 
    echo
    echo ">>>> ${LNG} - Fail; some errors"
    echo
  fi
done
# --------------------------------------------------------------------------------------------





