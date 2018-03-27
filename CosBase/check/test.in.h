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

COS_PP_EQ(2,2)  // returns 1 since equal

COS_PP_STR(COS_PP_EQ(2,2))  // returns "1" since equal

COS_PP_IF(0) (true, false)  // returns false---actually everything after true

COS_PP_IF(1) (true, false)  // returns true or the first element of the tuple

COS_PP_IF(0) (more, some, stuff)  // no error if not 0 or 1 or missing tuple, error for <2 elements

COS_PP_ISBLANK_

COS_PP_ISTUPLE(COS_PP_CAT_(COS_PP_ISBLANK_, ))

#define COS_METHOD_TRACE 
COS_METHOD_TRACE
COS_PP_IFNDEF(COS_METHOD_TRACE)(COS_MTH_TRC_LOC,"/* no trace */")

// COS_PP_CAT_NARG(hello_,a,b,c,3)

COS_PP_NUMSEQ(63,a) // produces a1,a2,...,a63

COS_PP_NUMSEQ_N(a) // produces a1,a2,...,a63

// COS_PP_NARG(COS_PP_PAIR(COS_PP_REST,(COS_PP_DUP(5,COS_PP_DUP(3,,)))))

