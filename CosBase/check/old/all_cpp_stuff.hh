#define 
COS_PP_1ARG            // return 1 if at least one 'effective' argument is present, 0 otherwise
COS_PP_1ST             // get 1st element of tuple
COS_PP_2ARGS           // return 1 if at least two arguments are present, 0 otherwise
COS_PP_2ND             // get 2nd element of tuple
COS_PP_3RD             // get 3rd element of tuple
COS_PP_4TH             // get 4th element of tuple
COS_PP_5TH             // get 5th element of tuple
COS_PP_6TH             // get 6th element of tuple
COS_PP_7TH             // get 7th element of tuple
COS_PP_8TH             // get 8th element of tuple
COS_PP_9TH             // get 9th element of tuple
COS_PP_ADD             // add two integers m >= 0, n >= 0, m+n <= COS_PP_MAX_N
COS_PP_AND             // evaluate first element of the following tuple, otherwise evaluate the rest
COS_PP_ARG1            // arg #1 of sequence
COS_PP_ARG2            // arg #2 of sequence
COS_PP_ARG3            // arg #3 of sequence
COS_PP_ARG4            // arg #4 of sequence
COS_PP_ARG5            // arg #5 of sequence
COS_PP_ARG6            // arg #6 of sequence
COS_PP_ARG7            // arg #7 of sequence
COS_PP_ARG8            // arg #8 of sequence
COS_PP_ARG9            // arg #9 of sequence
COS_PP_BOOL            // return 1 if 'a' is non-zero, including numbers and tokens, 0 otherwise
COS_PP_BRACE           // { around ... }
COS_PP_CAT             // ??
COS_PP_CAT3            // ??
COS_PP_CAT4            // ??
COS_PP_CAT_NARG        // ??
COS_PP_COMMA           // ,
COS_PP_CONCAT          // concat tuples T1 and T2
COS_PP_CONS            // concat element a in front of tuple
COS_PP_DECR            // decrement integer 0 <= n <= COS_PP_MAX_N, saturates at zero
COS_PP_DROP            // drop first n < length(T) elements of tuple
COS_PP_DUP             // ??
COS_PP_DUPSEQ          // sequence of n elements from duplication of va_args elements
COS_PP_DUPSEQ_N        // ??
COS_PP_EAT             // replaces args by /* nothing */
COS_PP_ELEM            // elements indexed accessor in range 1..length(T)
COS_PP_EMPTY           // expands to /* empty */
COS_PP_EQ              // m == n where 0 <= m,n <= 63
COS_PP_EVAL            // eval function F() up to n times on tuple (run in O(n))
COS_PP_FILTER          // filter elements of tuple using the predicate function PF(A)
COS_PP_FOLDL           // fold left elements of tuple using function F(a,b)
COS_PP_FOLDR           // fold right elements of tuple using function F(a,b)
COS_PP_GE              // m >= n where 0 <= m,n <= 63
COS_PP_GT              // m > n where 0 <= m,n <= 63
COS_PP_HANOI           // tower of Hanoi moves for N disks (N<=20)
COS_PP_ID              // returns args
COS_PP_IF              // evaluate first element of the following tuple, otherwise evaluate the rest
COS_PP_IFDEF           // evaluate first element of the following tuple, otherwise evaluate the rest
COS_PP_IFNDEF          // evaluate first element of the following tuple, otherwise evaluate the rest
COS_PP_INCR            // increment integer 0 <= n <= COS_PP_MAX_N, saturates at COS_PP_MAX_N
COS_PP_ISALNUM         // [A-Za-z0-9] predicate function
COS_PP_ISALPHA         // [A-Za-z] predicate function
COS_PP_ISBLANK         // return 1 if 'a' is blank (empty), 0 otherwise
COS_PP_ISBOOL          // return 1 if 'a' is 0 or 1, 0 otherwise
COS_PP_ISCODE          // codes are [A-Za-z0-9_] and space
COS_PP_ISDIGIT         // [0-9] predicate function
COS_PP_ISLOWER         // [a-z] predicate function
COS_PP_ISNTUPLE        // return 0 if its *first* argument is/starts-with a tuple, 1 otherwise
COS_PP_ISNZERO         // return 1 if 'a' is not 0, 0 otherwise
COS_PP_ISONE           // return 1 if 'a' is 1, 0 otherwise
COS_PP_ISSPACE         // space predicate function
COS_PP_ISTOKEN         // return 1 if the token 'tok' has '#define COS_PP_TOKEN_tok ()'
COS_PP_ISTUPLE         // return 1 if its *first* argument is/starts-with a tuple, 0 otherwise
COS_PP_ISTWO           // return 1 if 'a' is 2, 0 otherwise
COS_PP_ISUNDERSCORE    // _ predicate function
COS_PP_ISUPPER         // [A-Z] predicate function
COS_PP_ISXDIGIT        // [0-9A-Fa-f] predicate function
COS_PP_ISZERO          // return 1 if 'a' is 0, 0 otherwise
COS_PP_LAST            // get last element of tuple
COS_PP_LE              // m <= n where 0 <= m,n <= 63
COS_PP_LEN             // length of tuple, i.e. COS_PP_LEN(()) is 1
COS_PP_LPAR            // (
COS_PP_LT              // m < n where 0 <= m,n <= 63
COS_PP_MAP             // map function F(a) on elements of tuple T
COS_PP_MAP2            // map function F(a1,a2) on elements of tuples T1,T2 up to length(T1)
COS_PP_MAP3            // map function F(a1,a2,a3) on elements of tuples T1,T2,T3 up to length(T1)
COS_PP_MAX             // max(m,n) where 0 <= m,n <= 63
COS_PP_MAX_N           // 63 is largest N
COS_PP_MIN             // min(m,n) where 0 <= m,n <= 63
COS_PP_MORSE           // convert code to morse code
COS_PP_MUL             // multiply two integers m >= 0, n >= 0, (m,n,m*n)<=COS_PP_MAX_N
COS_PP_NARG            // returns number of args in (...) or (__VA_ARGS__)
COS_PP_NE              // m != n where 0 <= m,n <= 63
COS_PP_NOARG           // return 1 if it has no 'effective' argument, 0 otherwise
COS_PP_NOT             // evaluate first element of the following tuple, otherwise evaluate the rest
COS_PP_NUMSEQ          // numbered sequence of n elements from duplication of va_args elements
COS_PP_NUMSEQ_N        // ??
COS_PP_OR              // evaluate first element of the following tuple, otherwise evaluate the rest
COS_PP_ORD             // convert code to base64 ord
COS_PP_PAIR            // ??
COS_PP_PART            // __VA_ARGS__,
COS_PP_PPART           // (__VA_ARGS__),
COS_PP_RCONS           // concat element a at the end of tuple (reverse CONS)
COS_PP_RDROP           // drop last n < length(T) elements of tuple
COS_PP_REST            // 2..n args
COS_PP_REV             // reverse tuple T
COS_PP_REVSEQ          // reverse numbered sequence of n elements from duplication of va_args elements
COS_PP_REVSEQ_N        // ??
COS_PP_RPAR            // )
COS_PP_RTAKE           // take last n <= length(T) elements of tuple
COS_PP_SCANL           // scan left elements of tuple using function F(a,b)
COS_PP_SCANR           // scan right elements of tuple using function F(a,b)
COS_PP_SEP             // flatten tuple T to sequence using space as separator, i.e. (a,b,c) -> a b c
COS_PP_SEPWITH         // flatten tuple T to sequence using s as separator, i.e. (a,b,c),; -> a ; b ; c
COS_PP_SEQ             // expand tuple to sequence (e.g curry)
COS_PP_SPELL           // convert code to NATO phonetic alphabet
COS_PP_SPLIT           // split a tuple at position n into a tuple of 2 tuples (T1,T2)
COS_PP_STR             // makes string of all args
COS_PP_STR1            // makes string of arg #1
COS_PP_STR2            // makes string of arg #2
COS_PP_STR3            // makes string of arg #3
COS_PP_SUB             // substract two integers m >= 0, n >= 0, (m,n,m-n) <= COS_PP_MAX_N
COS_PP_SWAP            // puts 1st arg after remaining args
COS_PP_TAKE            // take first n <= length(T) elements of tuple
COS_PP_TOLOWER         // convert code to lower case
COS_PP_TOUPPER         // convert code to upper case
COS_PP_TUPLE           // build tuple from sequence (e.g uncurry)
COS_PP_XOR             // evaluate first element of the following tuple, otherwise evaluate the rest
