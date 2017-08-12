#!/bin/bash
set -ev
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}")" && pwd )"
GENERAL="${DIR}/../_general"

for LNG in *;
do
  cd ${GENERAL}/${LNG}
  npm install
done




