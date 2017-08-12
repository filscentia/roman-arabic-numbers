#!/bin/bash
set -ev
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}")" && pwd )"
GENERAL="${DIR}/../_general"
 
cd ${GENERAL}
for LNG in *;
do
  cd ${GENERAL}/${LNG}
  pwd
  npm install
done




