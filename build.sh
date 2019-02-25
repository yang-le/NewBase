#! /bin/sh
export LC_ALL=C
for d in `ls -F | grep "/$"`; do make -C $d $*; done

