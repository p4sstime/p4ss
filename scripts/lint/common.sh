# Shared helpers for the lint scripts. Source this file, don't execute it.

if [[ -t 2 && -z ${NO_COLOR:-} ]]; then
  RED=$'\e[1;31m' BOLD=$'\e[1m' DIM=$'\e[2m' RESET=$'\e[0m'
else
  RED='' BOLD='' DIM='' RESET=''
fi

# Prints "label|value" rows, aligning values after the longest label.
print_rows() {
  local width=0 row label
  for row in "$@"; do label=${row%%|*}; ((${#label} > width)) && width=${#label}; done
  for row in "$@"; do
    label=${row%%|*}
    printf '%s%s%s%*s %s\n' "$BOLD" "$label" "$RESET" $((width - ${#label})) '' "${row#*|}"
  done
}

# Prints a failure report to stderr and exits 1. Args: headline, reason, [body].
die() {
  {
    echo "$RED$1. See output for more details.$RESET"
    echo ""
    echo "$2"
    echo
    [[ -z ${3:-} ]] || echo "$3"
    echo "$DIM---$RESET"
  } >&2
  exit 1
}
