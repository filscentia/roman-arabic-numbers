#!/bin/bash
set -eu -o pipefail

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}")" && pwd )"

cd "${DIR}"
#--
node index.js --interactive
#--
cd -