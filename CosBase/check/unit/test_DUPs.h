/* This is a sample input for testing cpp macros.
 *
 *  Run with the following command:
 * 
 *    ucpp.exe -I<path to CosBase/include> -l test.in | grep -v '^ *$'  
 * 
 *  where -l skips #line output, -C includes comments in the
 *  output, and the grep command removes lots of whitespace
 *  lines in the output.  I would like to run this from perl
 *  so the grep could be done at the perl level.  Some issues
 *  to work out:
 * 
 *  - Would like to show input and output
 *  - File and routine completion (incremental?)
 *  - Call ucpp as a lexer directly with XS
 *  - Implement tests with error outputs
 */

#include "cos/cpp/cpp.h"  // This must be adapted for actual locations

COS_PP_DUP(3, a1, b2);      // have whitespace between repeats
COS_PP_DUP(5, a1, b2);      // have whitespace between repeats

COS_PP_DUPSEQ(2, a1, b2);   // have commas between repeats
COS_PP_DUPSEQ(4, a1, b2);   // have commas between repeats

COS_PP_DUPSEQ_N(a1);       // same as COS_PP_DUPSEQ(63,a1)

