function realpath_int() {
    wdir="$PWD"; [ "$PWD" = "/" ] && wdir=""
    arg=$1
    case "$arg" in
        /*) scriptdir="${arg}";;
        *) scriptdir="$wdir/${arg#./}";;
    esac
    scriptdir="${scriptdir%/*}"
    echo "$scriptdir"
}


function baremetal_export_main() {
    # The file doesn't have executable permissions, so this shouldn't really happen.
    # Doing this in case someone tries to chmod +x it and execute...
    if [[ -n "${BASH_SOURCE}" && ( "${BASH_SOURCE[0]}" == "${0}" ) ]]; then
        echo "This script should be sourced, not executed:"
        echo ". ${BASH_SOURCE[0]}"
        return 1
    fi

    if [[ -z "${BAREMETAL_PATH}" ]]
    then
        # BAREMETAL_PATH not set in the environment.
        # If using bash or zsh, try to guess BAREMETAL_PATH from script location.
        self_path=""
        if [[ -n "${BASH_SOURCE}" ]]
        then
            self_path="${BASH_SOURCE}"
        elif [[ -n "${ZSH_VERSION}" ]]
        then
            self_path="${(%):-%x}"
        else
            echo "Could not detect BAREMETAL_PATH. Please set it before sourcing this script:"
            echo "  export BAREMETAL_PATH=(add path here)"
            return 1
        fi

        if [[ "$OSTYPE" == "darwin"* ]]; then
            # convert possibly relative path to absolute
            script_dir="$(realpath_int ${self_path})"
            # resolve any ../ references to make the path shorter
            script_dir="$(cd ${script_dir}; pwd)"
        else
            # convert to full path and get the directory name of that
            script_name="$(readlink -f ${self_path})"
            script_dir="$(dirname ${script_name})"
        fi
        export BAREMETAL_PATH="${script_dir}"
        echo "Setting BAREMETAL_PATH to '${BAREMETAL_PATH}'"
    else
        # BAREMETAL_PATH came from the environment, check if the path is valid
        if [[ ! -d "${BAREMETAL_PATH}" ]]
        then
            echo "BAREMETAL_PATH is set to '${BAREMETAL_PATH}', but it is not a valid directory."
            echo "If you have set BAREMETAL_PATH manually, check if the path is correct."
            return 1
        fi
        # Check if this path looks like an BAREMETAL directory
        if [[ ! -f "${BAREMETAL_PATH}/tools/make/rules.mk" || ! -d "${BAREMETAL_PATH}/tools/kconfig" ]]
        then
            echo "BAREMETAL_PATH is set to '${BAREMETAL_PATH}', but it doesn't look like an baremetal directory."
            echo "If you have set BAREMETAL_PATH manually, check if the path is correct."
            return 1
        fi

        # The varible might have been set (rather than exported), re-export it to be sure
        export BAREMETAL_PATH="${BAREMETAL_PATH}"
    fi

    if [[ -z "${MICROMON_PATH}" ]]
    then
        export MICROMON_PATH="${BAREMETAL_PATH}/tools/micromon"
    fi

    old_path="$PATH"

    echo "Adding baremetal tools to PATH..."
    export PATH="$BAREMETAL_PATH/tools:$PATH"
    export PATH="$BAREMETAL_PATH/tools/kconfig/:$PATH"
    export PATH="$BAREMETAL_PATH/tools/micromon/:$PATH"

    if [[ -n "$BASH" ]]
    then
        path_prefix=${PATH%%${old_path}}
        paths="${path_prefix//:/ }"
        if [ -n "${paths}" ]; then
            echo "Added the following directories to PATH:"
        else
            echo "All paths are already set."
        fi
        for path_entry in ${paths}
        do
            echo "  ${path_entry}"
        done
    else
        echo "Updated PATH variable:"
        echo "  ${PATH}"
    fi

    # Clean up
    unset old_path
    unset paths
    unset path_prefix
    unset path_entry

    echo "Done! You can now compile baremetal projects."
    echo "Go to the project directory and run:"
    echo ""
    echo "  baremetal.py build"
    echo ""
}

baremetal_export_main

unset realpath_int
unset baremetal_export_main
