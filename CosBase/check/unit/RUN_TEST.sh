#!/usr/bin/sh
#
# This is the command to run a unit test.
# ucpp -l -I ../../include/ test_1ARG.h | grep -v '^ *$'
ucpp -l -I ../../include/ $1 2>&1 | grep -v '^ *$' | grep -v 'warning:'
