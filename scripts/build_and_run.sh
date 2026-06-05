
#!/usr/bin/env bash

# Exit immediately if a command exits with a non-zero status
set -euo pipefail




# Variables
ROOT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." &> /dev/null && pwd)
BUILD_DIR="$ROOT_DIR/build"
APPS_DIR="$BUILD_DIR/apps"
TEST_DIR="$BUILD_DIR/tests"
NUM_WORKERS=21
# Enables remaking the build directory from scratch
CLEAN=false
# Enables running of unit tests
RUN_TESTS=false



show_help()
{
    printf "%b\n" \
        "Usage: $(basename "${BASH_SOURCE[0]}") [OPTIONS] -- [ARGUMENTS]\n" \
        "Builds and runs the executable and or the unit tests\n" \
        "Options:" \
        "-h, --help                        Display this help message" \
        "-c, --clean                       Enables the deletion and remaking of the entire build directory" \
        "-t, --test                        Runs the unit tests" \
        "NOTE: Any arguments after the initial \"--\" are passed through to the executable"
    exit 0
}






# Parse the input arguments
while getopts ":hct-:" opt; do
    case $opt in
        h)
            show_help
            ;;
        c)
            CLEAN=true
            ;;
        t)
            RUN_TESTS=true
            ;;
        -)
            case "${OPTARG}" in
                help)
                    show_help
                    ;;
                clean)
                    CLEAN=true
                    ;;
                test)
                    RUN_TESTS=true
                    ;;
                "")
                    break
                    ;;
                *)
                    printf "Invalid option: --${OPTARG}\n" >&2
                    exit 1
                    ;;
            esac
            ;;
        *)
            printf "Invalid option: -$opt\n" >&2
            exit 1
            ;;
    esac
done




# Strip parsed options from "$@"
shift $((OPTIND - 1))
# Everything remaining in "$@" after this point is to be forwarded to the executable as flags
FORWARD_ARGS=("$@")




if [[ "$CLEAN" = true || ! -f "$BUILD_DIR/CMakeCache.txt" ]]; then
    printf "Deleting the $(basename "$BUILD_DIR") directory and then rebuilding\n"
    
    rm -rf "$BUILD_DIR"
    mkdir -p "$BUILD_DIR"

    cmake -DBUILD_DEBUG=ON -S "$ROOT_DIR" -B "$BUILD_DIR"
fi
cmake --build "$BUILD_DIR" -j "$NUM_WORKERS"



if [[ "$RUN_TESTS" = true ]]; then
    # Run the unit tests
    "$TEST_DIR/tests" "${FORWARD_ARGS[@]}"
else
    # Run the executable
    "$APPS_DIR/aec" "${FORWARD_ARGS[@]}"
fi




