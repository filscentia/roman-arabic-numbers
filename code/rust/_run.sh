#!/bin/bash
set -eu -o pipefail

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}")" && pwd )"

pushd "${DIR}"
#--
./target/release/rust run $1 
#--
popd