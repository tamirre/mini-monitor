dir="$1"
tmpfile="tmp.txt"
> "$tmpfile"

find "$dir" -type f -print0 | while IFS= read -r -d '' f; do
    printf "%s:\n" "$f" >> "$tmpfile"
    cat "$f" >> "$tmpfile"
    printf "\n" >> "$tmpfile"
done
