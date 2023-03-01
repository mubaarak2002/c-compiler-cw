#!/bin/bash

# Try to find a portable way of getting rid of
# any stray carriage returns
if which dos2unix ; then
    DOS2UNIX="dos2unix"
elif which fromdos ; then
    DOS2UNIX="fromdos"
else
    >&2 echo "warning: dos2unix is not installed."
    # This should work on Linux and MacOS, it matches all the carriage returns with sed and removes
    # them.  `tr` is used instead of `sed` because some versions of `sed` don't recognize the
    # carriage return symbol.  Something similar could be implemented with `sed` if necessary or
    # worst case it could be disabled by substituting it with `cat`.  One other thing to note is
    # that there are no quotes around the \r, which is so that it gets converted by bash.
    DOS2UNIX="tr -d \r"
    # DOS2UNIX="sed -e s/\r//g"
    # DOS2UNIX="cat"
fi

echo "========================================"
echo " Cleaning the temporaries and outputs"
make clean
echo " Force building histogram"
make lexer -B
if [[ "$?" -ne 0 ]]; then
    echo "Build failed.";
fi
echo ""
mkdir -p test/lexer

echo "========================================="

PASSED=0
CHECKED=0

for i in ../compiler_tests/**/*_driver.c; do
    echo "==========================="
    echo ""
    echo "Input file : ${i}"
    BASENAME=$(basename $i .txt);
    cat $i | ${DOS2UNIX} | ./lexer  > test/lexer/$BASENAME.stdout.txt  2> test/lexer/$BASENAME.stderr.txt

done

