#!/bin/bash
set -eu -o pipefail

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}")" && pwd )"

cd "${DIR}"
#--
npm test -- --file $1
#--
cd -