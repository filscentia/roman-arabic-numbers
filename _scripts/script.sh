#!/bin/bash
set -ev
set -o pipefail

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}")" && pwd )"
GENERAL="${DIR}/../_general"
 
cd ${GENERAL}
for LNG in nodejs java;
do
  cd ${GENERAL}/${LNG}
  pwd
  npm run build
done
