#!/bin/sh

countfilelines() {
  local count=$(wc -l $1 | awk '{print $1}')
  echo $count
}

if [[ "$#" -ne 2 ]]; then
  echo "Usage: $0 file1 file2" >&2
  exit 1
fi

for file in $@
do
  if [[ ! -f "${file}" ]]; then
    echo "file ${file} does not exist."
    exit -1
  fi
done

LINES1=$(countfilelines $1)
LINES2=$(countfilelines $2)
if [[ $LINES1 -eq $LINES2 ]]; then
  echo "Both files have the same number of lines."
else
  if [[ $LINES -gt $LINES2 ]]; then
    echo "${1} has more lines (${LINES1}) than $2 (${LINES2})"
  else
    echo "${2} has more lines (${LINES2}) than $1 (${LINES1})"
  fi
fi