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

// The COS_PP_NARG() macro seems to be responsible for this warning from ucpp
// test_2ARGS.h: warning: line 35: operator '##' produced the invalid token ',15'
//
// No errors from running cpp -E -I ../../include in its place

COS_PP_2ARGS(a,b,c)

COS_PP_2ARGS(a,b)

COS_PP_2ARGS(a)

COS_PP_2ARGS()
