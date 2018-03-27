COS_PP_MAX_N 63

COS_PP_NARG(...)

COS_PP_DUPSEQ_N(...)

COS_PP_NUMSEQ_N(...)

COS_PP_REVSEQ_N(...)

COS_PP_ID(...)       __VA_ARGS__
COS_PP_EAT(...)      /* nothing */
COS_PP_PART(...)     __VA_ARGS__,
COS_PP_PPART(...)   (__VA_ARGS__),
COS_PP_PAIR(a,...) a __VA_ARGS__
COS_PP_SWAP(a,...)   __VA_ARGS__ a
COS_PP_REST(a,...)   __VA_ARGS__
COS_PP_EMPTY()       /* empty */
COS_PP_COMMA()       ,
COS_PP_LPAR()        (
COS_PP_RPAR()        )
COS_PP_BRACE(...)   { __VA_ARGS__ }

COS_PP_ARG1(a,                ...)  a
COS_PP_ARG2(a,b,              ...)  b
COS_PP_ARG3(a,b,c,            ...)  c
COS_PP_ARG4(a,b,c,d,          ...)  d
COS_PP_ARG5(a,b,c,d,e,        ...)  e
COS_PP_ARG6(a,b,c,d,e,f,      ...)  f
COS_PP_ARG7(a,b,c,d,e,f,g,    ...)  g
COS_PP_ARG8(a,b,c,d,e,f,g,h,  ...)  h
COS_PP_ARG9(a,b,c,d,e,f,g,h,i,...)  i

COS_PP_STR(...)        COS_PP_STR_(__VA_ARGS__)
COS_PP_STR1(a,...)     #a
COS_PP_STR2(a,b,...)   #b
COS_PP_STR3(a,b,c,...) #c

COS_PP_CAT(a,...)      COS_PP_CAT_ (a,    __VA_ARGS__)
COS_PP_CAT3(a,b,...)   COS_PP_CAT3_(a,b,  __VA_ARGS__)
COS_PP_CAT4(a,b,c,...) COS_PP_CAT4_(a,b,c,__VA_ARGS__)

COS_PP_CAT_NARG(a,...) COS_PP_CAT(a,COS_PP_NARG(__VA_ARGS__))

COS_PP_DUP(n,...)      COS_PP_CAT_(COS_PP_DUP_,n)(__VA_ARGS__)

// length of tuple, i.e COS_PP_LEN(()) is 1
COS_PP_LEN(T)

// expand tuple to sequence (e.g curry)
COS_PP_SEQ(T)

// build tuple from sequence (e.g uncurry)
COS_PP_TUPLE(...)

// eval function F() up to n times on tuple (run in O(n))
COS_PP_EVAL(n,T,F)

// split a tuple at position n into a tuple of 2 tuples (T1,T2)
COS_PP_SPLIT(n,T)

// reverse tuple T
COS_PP_REV(T)

/***********************************************************
 * Getters (assume that element exists)
 */

// elements accessors
COS_PP_1ST(T)  COS_PP_PAIR(COS_PP_ARG1,(COS_PP_ID T,))
COS_PP_2ND(T)  COS_PP_PAIR(COS_PP_ARG2,(COS_PP_ID T,))
COS_PP_3RD(T)  COS_PP_PAIR(COS_PP_ARG3,(COS_PP_ID T,))
COS_PP_4TH(T)  COS_PP_PAIR(COS_PP_ARG4,(COS_PP_ID T,))
COS_PP_5TH(T)  COS_PP_PAIR(COS_PP_ARG5,(COS_PP_ID T,))
COS_PP_6TH(T)  COS_PP_PAIR(COS_PP_ARG6,(COS_PP_ID T,))
COS_PP_7TH(T)  COS_PP_PAIR(COS_PP_ARG7,(COS_PP_ID T,))
COS_PP_8TH(T)  COS_PP_PAIR(COS_PP_ARG8,(COS_PP_ID T,))
COS_PP_9TH(T)  COS_PP_PAIR(COS_PP_ARG9,(COS_PP_ID T,))
COS_PP_LAST(T) COS_PP_1ST(COS_PP_REV(T))

// elements indexed accessor in range 1..length(T)
COS_PP_ELEM(n,T)

// take first n <= length(T) elements of tuple
COS_PP_TAKE(n,T)

// take last n <= length(T) elements of tuple
COS_PP_RTAKE(n,T)

// drop first n < length(T) elements of tuple
COS_PP_DROP(n,T)

// drop last n < length(T) elements of tuple
COS_PP_RDROP(n,T)

/***********************************************************
 * Setters
 */

// concat element a in front of tuple
COS_PP_CONS(a,T)

// concat element a at the end of tuple (reverse CONS)
COS_PP_RCONS(T,a)

// concat tuples T1 and T2
COS_PP_CONCAT(T1,T2)

/***********************************************************
 * Sequences
 */

// sequence of n elements from duplication of va_args elements
COS_PP_DUPSEQ(n,...)

// numbered sequence of n elements from duplication of va_args elements
COS_PP_NUMSEQ(n,...)

// reverse numbered sequence of n elements from duplication of va_args elements
COS_PP_REVSEQ(n,...)

// the following macros expect b{1,2} to be 0 or 1
// see COS_PP_BOOL for conversion

// evaluate first element of the following tuple, otherwise evaluate the rest
COS_PP_IF(b)

COS_PP_IFDEF(m)

COS_PP_IFNDEF(m)

COS_PP_NOT(b)

COS_PP_AND(b1,b2)

COS_PP_OR(b1,b2)

COS_PP_XOR(b1,b2)

// the following macros expect 0 <= m,n <= 63

// m >= n
COS_PP_GE(m,n)

// m <= n
COS_PP_LE(m,n)

// m > n
COS_PP_GT(m,n)

// m < n
COS_PP_LT(m,n)

// m == n
COS_PP_EQ(m,n)

// m != n
COS_PP_NE(m,n)

// min(m,n)
COS_PP_MIN(m,n)

// max(m,n)
COS_PP_MAX(m,n)

// the following macros expect 'a' to be concatenable (not a symbol)

// return 1 if 'a' is non-zero, including numbers and tokens, 0 otherwise
COS_PP_BOOL(a)

// return 1 if 'a' is 0 or 1, 0 otherwise
COS_PP_ISBOOL(a)

// return 1 if 'a' is blank (empty), 0 otherwise
COS_PP_ISBLANK(a)

// return 1 if 'a' is 0, 0 otherwise
COS_PP_ISZERO(a)

// return 1 if 'a' is not 0, 0 otherwise
COS_PP_ISNZERO(a)

// return 1 if 'a' is 1, 0 otherwise
COS_PP_ISONE(a)

// return 1 if 'a' is 2, 0 otherwise
COS_PP_ISTWO(a)

// return 1 if the token 'a' is a recognized token, 0 otherwise
// the '#define COS_PP_TOKEN_tok ()' define the set of recognized tokens
COS_PP_ISTOKEN(a)

// return 1 if its *first* argument is/starts-with a tuple, 0 otherwise
COS_PP_ISTUPLE(...)

COS_PP_ISNTUPLE(...)

// return 1 if it has no 'effective' argument, 0 otherwise
// WARNING: if the last argument is the name of a function-like macro,
//          the latter will be evaluated
COS_PP_NOARG(...)

// return 1 if at least one 'effective' argument is present, 0 otherwise
// WARNING: uses COS_PP_NOARG()
COS_PP_1ARG(...)

// return 1 if at least two arguments are present, 0 otherwise
COS_PP_2ARGS(...)

// increment integer 0 <= n <= COS_PP_MAX_N, saturates at COS_PP_MAX_N
COS_PP_INCR(n)

// decrement integer 0 <= n <= COS_PP_MAX_N, saturates at zero
COS_PP_DECR(n)

// add two integers m >= 0, n >= 0, m+n <= COS_PP_MAX_N
COS_PP_ADD(m,n)

// substract two integers m >= 0, n >= 0, (m,n,m-n) <= COS_PP_MAX_N
COS_PP_SUB(m,n)

// multiply two integers m >= 0, n >= 0, (m,n,m*n)<=COS_PP_MAX_N
COS_PP_MUL(m,n)


// fold left elements of tuple using function F(a,b)
COS_PP_FOLDL(T,a0,F)

// fold right elements of tuple using function F(a,b)
COS_PP_FOLDR(T,a0,F)

// scan left elements of tuple using function F(a,b)
COS_PP_SCANL(T,a0,F)

// scan right elements of tuple using function F(a,b)
COS_PP_SCANR(T,a0,F)

// filter elements of tuple using the predicate function PF(A)
COS_PP_FILTER(T,PF)

// map function F(a) on elements of tuple T
COS_PP_MAP(T,F)

// map function F(a1,a2) on elements of tuples T1,T2 up to length(T1)
COS_PP_MAP2(T1,T2,F)

// map function F(a1,a2,a3) on elements of tuples T1,T2,T3 up to length(T1)
COS_PP_MAP3(T1,T2,T3,F)

// flatten tuple T to sequence using s as separator, i.e. (a,b,c) -> a b c
COS_PP_SEP(T)
        COS_PP_FOLDL(T,,COS_PP_PAIR)

// flatten tuple T to sequence using s as separator, i.e. (a,b,c),; -> a ; b ; c
COS_PP_SEPWITH(T,s)
