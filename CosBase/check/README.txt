This directory contains work to extract and document the
set of CPP macros used to implement the COS language
extensions implemented in CosBase/include/cos/cpp .

Eventually I would like to have a test suite using
perl and ucpp to docment usage for each of the
macros.  Maybe even with macro completion and a shell
to allow playing around with things easier.

Directory contents:
  README.txt - this file
  all_defines_noimpl.h - ucpp -d macro definitions output
  all_defines_noimpl.hh - macros with args and descriptions
  defines/ - output from 'ucpp -ICosBase/include -d file.h'
  old/     - old results, to be removed once not needed
  test.in.h - start input for cpp tests
  work/    - intermediate files to generate the above

TO DO:
- add location of file/concept
- fill in missing explanations
- clarify docs

DEFINITIONS:
 sequence - a list of comma separated tokens, e.g. a,b,c
 tuple    - a sequence within parentheses, e.g. (a,b,c)
            Limited to 63 elements (C99 limits)


