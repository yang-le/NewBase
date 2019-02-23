#! /bin/sh

for d in `ls -F | grep "/$"`; do make -C $d $*; done

