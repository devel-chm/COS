#define COS_PP_1ARG(...)                                // return 1 if at least one 'effective' argument is present, 0 otherwise
#define COS_PP_1ST(T)                                   // get 1st element of tuple
#define COS_PP_2ARGS(...)                               // return 1 if at least two arguments are present, 0 otherwise
#define COS_PP_2ND(T)                                   // get 2nd element of tuple
#define COS_PP_3RD(T)                                   // get 3rd element of tuple
#define COS_PP_4TH(T)                                   // get 4th element of tuple
#define COS_PP_5TH(T)                                   // get 5th element of tuple
#define COS_PP_6TH(T)                                   // get 6th element of tuple
#define COS_PP_7TH(T)                                   // get 7th element of tuple
#define COS_PP_8TH(T)                                   // get 8th element of tuple
#define COS_PP_9TH(T)                                   // get 9th element of tuple
#define COS_PP_ADD(m, n)                                // add two integers m >= 0, n >= 0, m+n <= COS_PP_MAX_N
#define COS_PP_AND(b1, b2)                              // evaluate first element of the following tuple, otherwise evaluate the rest
#define COS_PP_ARG1(a, ...)                             // arg #1 of sequence
#define COS_PP_ARG2(a, b, ...)                          // arg #2 of sequence
#define COS_PP_ARG3(a, b, c, ...)                       // arg #3 of sequence
#define COS_PP_ARG4(a, b, c, d, ...)                    // arg #4 of sequence
#define COS_PP_ARG5(a, b, c, d, e, ...)                 // arg #5 of sequence
#define COS_PP_ARG6(a, b, c, d, e, f, ...)              // arg #6 of sequence
#define COS_PP_ARG7(a, b, c, d, e, f, g, ...)           // arg #7 of sequence
#define COS_PP_ARG8(a, b, c, d, e, f, g, h, ...)        // arg #8 of sequence
#define COS_PP_ARG9(a, b, c, d, e, f, g, h, i, ...)     // arg #9 of sequence
#define COS_PP_BOOL(a)                                  // return 1 if 'a' is non-zero, including numbers and tokens, 0 otherwise ("to bool")
#define COS_PP_BRACE(...)                               // { around ... }
#define COS_PP_CAT(a, ...)                              // concatenate arg1 and rest
#define COS_PP_CAT3(a, b, ...)                          // concatenate arg1, arg2, and rest
#define COS_PP_CAT4(a, b, c, ...)                       // concatenate arg1, arg2, arg3, and rest
#define COS_PP_CAT_NARG(a, ...)                         // concatenate arg1 and the number of remaining args
#define COS_PP_COMMA()                                  // ,
#define COS_PP_CONCAT(T1, T2)                           // concat tuples T1 and T2
#define COS_PP_CONS(a, T)                               // return tuple formed by concat element a in front of input tuple
#define COS_PP_DECR(n)                                  // decrement integer 0 <= n <= COS_PP_MAX_N, saturates at zero
#define COS_PP_DROP(n, T)                               // drop first n < length(T) elements of tuple
#define COS_PP_DUP(n, ...)                              // repeat ... n times in a row (white space between)
#define COS_PP_DUPSEQ(n, ...)                           // sequence of length n elements from comma separated duplication of va_args elements
#define COS_PP_DUPSEQ_N(...)                            // same as COS_PP_DUPSEQ(63, ...)
#define COS_PP_EAT(...)                                 // replaces args by /* nothing */
#define COS_PP_ELEM(n, T)                               // elements indexed accessor in range 1..length(T)
#define COS_PP_EMPTY()                                  // expands to /* empty */
#define COS_PP_EQ(m, n)                                 // m == n where 0 <= m,n <= 63
#define COS_PP_EVAL(n, T, F)                            // eval function F() up to n times on tuple (run in O(n)) (see FOLD, MAP, and FILTER routines)
#define COS_PP_FILTER(T, PF)                            // filter elements of tuple using the predicate function PF(A)
#define COS_PP_FOLDL(T, a0, F)                          // fold left elements of tuple using function F(a,b)
#define COS_PP_FOLDR(T, a0, F)                          // fold right elements of tuple using function F(a,b)
#define COS_PP_GE(m, n)                                 // m >= n where 0 <= m,n <= 63
#define COS_PP_GT(m, n)                                 // m > n where 0 <= m,n <= 63
#define COS_PP_HANOI(n)                                 // tower of Hanoi moves for N disks (N<=20)
#define COS_PP_ID(...)                                  // returns args
#define COS_PP_IF(b)                                    // evaluate first element of the following tuple, otherwise evaluate the rest
#define COS_PP_IFDEF(m)                                 // macro defined, not empty, eval first element of the following tuple, else eval the rest
#define COS_PP_IFNDEF(m)                                // macro defined, but empty, eval first element of the following tuple, else eval the rest
#define COS_PP_INCR(n)                                  // increment integer 0 <= n <= COS_PP_MAX_N, saturates at COS_PP_MAX_N
#define COS_PP_ISALNUM(a)                               // [A-Za-z0-9] predicate function
#define COS_PP_ISALPHA(a)                               // [A-Za-z] predicate function
#define COS_PP_ISBLANK(a)                               // return 1 if 'a' is blank (empty), 0 otherwise
#define COS_PP_ISBOOL(a)                                // return 1 if 'a' is 0 or 1, 0 otherwise
#define COS_PP_ISCODE(a)                                // codes are [A-Za-z0-9_] and space
#define COS_PP_ISDIGIT(a)                               // [0-9] predicate function
#define COS_PP_ISLOWER(a)                               // [a-z] predicate function
#define COS_PP_ISNTUPLE(...)                            // return 0 if its *first* argument is/starts-with a tuple, 1 otherwise
#define COS_PP_ISNZERO(a)                               // return 1 if 'a' is not 0, 0 otherwise
#define COS_PP_ISONE(a)                                 // return 1 if 'a' is 1, 0 otherwise
#define COS_PP_ISSPACE(a)                               // space predicate function
#define COS_PP_ISTOKEN(a)                               // return 1 if the token 'tok' has '#define COS_PP_TOKEN_tok ()'
#define COS_PP_ISTUPLE(...)                             // return 1 if its *first* argument is/starts-with a tuple, 0 otherwise
#define COS_PP_ISTWO(a)                                 // return 1 if 'a' is 2, 0 otherwise
#define COS_PP_ISUNDERSCORE(a)                          // _ predicate function
#define COS_PP_ISUPPER(a)                               // [A-Z] predicate function
#define COS_PP_ISXDIGIT(a)                              // [0-9A-Fa-f] predicate function
#define COS_PP_ISZERO(a)                                // return 1 if 'a' is 0, 0 otherwise
#define COS_PP_LAST(T)                                  // get last element of tuple
#define COS_PP_LE(m, n)                                 // m <= n where 0 <= m,n <= 63
#define COS_PP_LEN(T)                                   // length of tuple, i.e. COS_PP_LEN(()) is 1
#define COS_PP_LPAR()                                   // (
#define COS_PP_LT(m, n)                                 // m < n where 0 <= m,n <= 63
#define COS_PP_MAP(T, F)                                // map function F(a) on elements of tuple T
#define COS_PP_MAP2(T1, T2, F)                          // map function F(a1,a2) on elements of tuples T1,T2 up to length(T1)
#define COS_PP_MAP3(T1, T2, T3, F)                      // map function F(a1,a2,a3) on elements of tuples T1,T2,T3 up to length(T1)
#define COS_PP_MAX(m, n)                                // max(m,n) where 0 <= m,n <= 63
#define COS_PP_MAX_N 63 COS_PP_MAX_N                    // 63 is largest N
#define COS_PP_MIN(m, n)                                // min(m,n) where 0 <= m,n <= 63
#define COS_PP_MORSE(a)                                 // convert code to morse code
#define COS_PP_MUL(m, n)                                // multiply two integers m >= 0, n >= 0, (m,n,m*n)<=COS_PP_MAX_N
#define COS_PP_NARG(...)                                // returns number of args in (...) or (__VA_ARGS__)
#define COS_PP_NE(m, n)                                 // m != n where 0 <= m,n <= 63
#define COS_PP_NOARG(...)                               // return 1 if it has no 'effective' argument, 0 otherwise
#define COS_PP_NOT(b)                                   // evaluate first element of the following tuple, otherwise evaluate the rest
#define COS_PP_NUMSEQ(n, ...)                           // numbered sequence of n elements from duplication of va_args elements
#define COS_PP_NUMSEQ_N(...)                            // same as COS_PP_NUMSEQ(63,...), with one arg you get arg1, arg2, ..., arg63 out
#define COS_PP_OR(b1, b2)                               // evaluate first element of the following tuple, otherwise evaluate the rest
#define COS_PP_ORD(a)                                   // convert code to base64 ord
#define COS_PP_PAIR(a, ...)                             // extract arg1 and rest and place adjacent (remove comma)
#define COS_PP_PART(...)                                // __VA_ARGS__,
#define COS_PP_PPART(...)                               // (__VA_ARGS__),
#define COS_PP_RCONS(T, a)                              // concat element a at the end of tuple (reverse CONS)
#define COS_PP_RDROP(n, T)                              // drop last n < length(T) elements of tuple
#define COS_PP_REST(a, ...)                             // 2..n args
#define COS_PP_REV(T)                                   // reverse tuple T
#define COS_PP_REVSEQ(n, ...)                           // reverse numbered sequence of n elements from duplication of va_args elements
#define COS_PP_REVSEQ_N(...)                            // same as COS_PP_REVSEQ(63,...)
#define COS_PP_RPAR()                                   // )
#define COS_PP_RTAKE(n, T)                              // take last n <= length(T) elements of tuple
#define COS_PP_SCANL(T, a0, F)                          // scan left elements of tuple using function F(a,b)
#define COS_PP_SCANR(T, a0, F)                          // scan right elements of tuple using function F(a,b)
#define COS_PP_SEP(T)                                   // flatten tuple T to sequence using space as separator, i.e. (a,b,c) -> a b c
#define COS_PP_SEPWITH(T, s)                            // flatten tuple T to sequence using s as separator, i.e. (a,b,c),; -> a ; b ; c
#define COS_PP_SEQ(T)                                   // expand tuple to sequence (e.g curry)
#define COS_PP_SPELL(a)                                 // convert code to NATO phonetic alphabet
#define COS_PP_SPLIT(n, T)                              // split a tuple at position n into a tuple of 2 tuples (T1,T2)
#define COS_PP_STR(...)                                 // makes string of all args
#define COS_PP_STR1(a, ...)                             // makes string of arg #1
#define COS_PP_STR2(a, b, ...)                          // makes string of arg #2
#define COS_PP_STR3(a, b, c, ...)                       // makes string of arg #3
#define COS_PP_SUB(m, n)                                // substract two integers m >= 0, n >= 0, (m,n,m-n) <= COS_PP_MAX_N
#define COS_PP_SWAP(a, ...)                             // puts 1st arg after remaining args
#define COS_PP_TAKE(n, T)                               // take first n <= length(T) elements of tuple
#define COS_PP_TOLOWER(a)                               // convert code to lower case
#define COS_PP_TOUPPER(a)                               // convert code to upper case
#define COS_PP_TUPLE(...)                               // build tuple from sequence (e.g uncurry)
#define COS_PP_XOR(b1, b2)                              // evaluate first element of the following tuple, otherwise evaluate the rest
