#!/bin/bash
set -ev
set -o pipefail


# --------------------------------------------------------------------------------------------
# Issuing the run build per all the languages
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}")" && pwd )"
GENERAL="${DIR}/../_general"
 
cd ${GENERAL}
for LNG in c nodejs java;
do
  cd ${GENERAL}/${LNG}
  pwd
  npm run build
done

# --------------------------------------------------------------------------------------------
