#!/bin/bash
set -ev
set -o pipefail

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}")" && pwd )"

TEST="${DIR}/../_test"
GENERAL="${DIR}/../_general"

cd ${GENERAL}
for LNG in nodejs java;
do
  cd "${GENERAL}/${LNG}"
  pwd
  npm test -- --file "${TEST}/input.csv" | awk '/--START--/{flag=1;next}/--END--/{flag=0;}flag' > temp.out
  diff --side-by-side  --suppress-common-lines temp.out "${TEST}/results.csv"

  if [ $? == 0 ]; then
    echo "${LNG} - Correct results"
    echo 
  else 
    echo "${LNG} - Fail; some errors"
  fi
done




