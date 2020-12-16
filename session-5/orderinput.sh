#!/bin/sh

if [[ "$#" -lt 1 ]]; then
  echo "Usage: $0 (at least 1 alphabetical argument)" >&2
  exit 1
fi

arguments=( "$@" )
IFS=$'\n' sorted=($(sort <<<"${arguments[*]}")); unset IFS

echo "Ordered array: ${sorted[@]}"