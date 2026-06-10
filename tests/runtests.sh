#!/bin/sh
# Script to run tests
#
# Version: 20260609

if test -f ${PWD}/libcdirectory/.libs/libcdirectory.1.dylib && test -f ./pycdirectory/.libs/pycdirectory.so
then
	install_name_tool -change /usr/local/lib/libcdirectory.1.dylib ${PWD}/libcdirectory/.libs/libcdirectory.1.dylib ./pycdirectory/.libs/pycdirectory.so
fi

make check-build > /dev/null

make check $@
RESULT=$?

if test ${RESULT} -ne 0
then
	find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

