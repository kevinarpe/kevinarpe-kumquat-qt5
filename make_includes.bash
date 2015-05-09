#!/usr/bin/env bash

# Exit immediately if a command exits with a non-zero status.
set -e
# Treat unset variables as an error when substituting.
set -u
# the return value of a pipeline is the status of
# the last command to exit with a non-zero status,
# or zero if no command exited with a non-zero status
set -o pipefail
# Print commands and their arguments as they are executed.
# set -x

main()
{
    cd "$(dirname "$0")"
    for classname in $(find src \( -name '*.h' -and -not -name '*.impl.h' \) -type f -exec egrep '^class K' {} \; | egrep -v ';' | sort | perl -p -e 's/^class ([^ ]+).*$/$1/')
    do
        local filepath="include/$classname"
        echo "    $filepath"
        echo "#include \"$(echo "$classname" | perl -p -e '$_ = lc').h\"" > "$filepath"
    done
}

main "$@"

