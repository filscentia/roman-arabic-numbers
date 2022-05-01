#!/bin/bash
set -eu -o pipefail

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}")" && pwd )"

pushd "${DIR}"
#--
java -cp ./build/libs/java.jar App --file $1 
#--
popd