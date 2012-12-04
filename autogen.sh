#!/bin/sh
# could be replaced with autoreconf
aclocal
#autoheader
automake --add-missing
autoconf
