#!/bin/bash
set -eu -o pipefail

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}")" && pwd )"

pushd "${DIR}"
#--
./romanarabic test $1 
#--
popd