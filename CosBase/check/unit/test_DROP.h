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

COS_PP_DROP(3, (t1,t2,t3,t4,t5,t6,t7,t8,t9,t10))
COS_PP_DROP(8, (t1,t2,t3,t4,t5,t6,t7,t8,t9,t10))
COS_PP_DROP(9, (t1,t2,t3,t4,t5,t6,t7,t8,t9,t10))
// COS_PP_DROP(10, (t1,t2,t3,t4,t5,t6,t7,t8,t9,t10)) // doesn't work, need to have non-empty tuple result

