#!/bin/sh
# Script to run tests
#
# Version: 20201121

if test -f ${PWD}/libcdirectory/.libs/libcdirectory.1.dylib && test -f ./pycdirectory/.libs/pycdirectory.so;
then
	install_name_tool -change /usr/local/lib/libcdirectory.1.dylib ${PWD}/libcdirectory/.libs/libcdirectory.1.dylib ./pycdirectory/.libs/pycdirectory.so;
fi

make check CHECK_WITH_STDERR=1;
RESULT=$?;

if test ${RESULT} -ne 0 && test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi
exit ${RESULT};

