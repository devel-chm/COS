/*
 o---------------------------------------------------------------------o
 |
 | COS Array - algorithms using functors
 |
 o---------------------------------------------------------------------o
 |
 | C Object System
 |
 | Copyright (c) 2006+ Laurent Deniau, laurent.deniau@cern.ch
 |
 | For more information, see:
 | http://cern.ch/laurent.deniau/cos.html
 |
 o---------------------------------------------------------------------o
 |
 | This file is part of the C Object System framework.
 |
 | The C Object System is free software; you can redistribute it and/or
 | modify it under the terms of the GNU Lesser General Public License
 | as published by the Free Software Foundation; either version 3 of
 | the License, or (at your option) any later version.
 |
 | The C Object System is distributed in the hope that it will be
 | useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 | of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 |
 | See <http://www.gnu.org/licenses> for more details.
 |
 o---------------------------------------------------------------------o
 |
 | $Id: Array_fun.c,v 1.1 2009/02/03 17:44:52 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Array.h>
#include <cos/Value.h>
#include <cos/Slice.h>
#include <cos/Number.h>
#include <cos/Vector.h>
#include <cos/Functor.h>
#include <cos/gen/algorithm.h>
#include <cos/gen/container.h>
#include <cos/gen/accessor.h>
#include <cos/gen/functor.h>
#include <cos/gen/object.h>
#include <cos/gen/value.h>
#include <cos/gen/init.h>

#include <stdlib.h>

// ----- shared private implementation

#include "./Array_p.h"

// ----- apply (in place)

defmethod(void, gapply, Functor, Array)
  OBJ *obj = self2->object;
  OBJ *end = self2->object+self2->size;

  while(obj < end) geval1(_1, *obj++);
endmethod

// ----- map, map2, map3, map4

defmethod(OBJ, gmap, Functor, Array)
  struct Array* arr = array_alloc(self2->size);
  OBJ _arr = (OBJ)arr; PRT(_arr);
  OBJ *obj = arr  ->object;
  OBJ *end = arr  ->object+arr->size;
  OBJ *src = self2->object;

  while(obj < end)
    *obj++ = gretain( geval1(_1,*src++) );

  UNPRT(_arr);
  retmethod(gautoRelease(_arr));
endmethod

defmethod(OBJ, gmap2, Functor, Array, Array)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
  struct Array* arr = array_alloc(size);
  OBJ _arr  = (OBJ)arr; PRT(_arr);
  OBJ *obj  = arr  ->object;
  OBJ *end  = arr  ->object+arr->size; 
  OBJ *src1 = self2->object;
  OBJ *src2 = self3->object;

  while(obj < end)
    *obj++ = gretain( geval2(_1,*src1++,*src2++) );

  UNPRT(_arr);
  retmethod(gautoRelease(_arr));
endmethod

defmethod(OBJ, gmap3, Functor, Array, Array, Array)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
  if (size > self4->size) size = self4->size;
  struct Array* arr = array_alloc(size);
  OBJ _arr  = (OBJ)arr; PRT(_arr);
  OBJ *obj  = arr  ->object;
  OBJ *end  = arr  ->object+arr->size; 
  OBJ *src1 = self2->object;
  OBJ *src2 = self3->object;
  OBJ *src3 = self4->object;

  while(obj < end)
    *obj++ = gretain( geval3(_1,*src1++,*src2++,*src3++) );

  UNPRT(_arr);
  retmethod(gautoRelease(_arr));
endmethod

defmethod(OBJ, gmap4, Functor, Array, Array, Array, Array)
  U32 size = self2->size < self3->size ? self2->size : self3->size;
  if (size > self4->size) size = self4->size;
  if (size > self5->size) size = self5->size;
  struct Array* arr = array_alloc(size);
  OBJ _arr  = (OBJ)arr; PRT(_arr);
  OBJ *obj  = arr  ->object;
  OBJ *end  = arr  ->object+arr->size; 
  OBJ *src1 = self2->object;
  OBJ *src2 = self3->object;
  OBJ *src3 = self4->object;
  OBJ *src4 = self5->object;

  while(obj < end)
    *obj++ = gretain( geval4(_1,*src1++,*src2++,*src3++,*src4++) );

  UNPRT(_arr);
  retmethod(gautoRelease(_arr));
endmethod

// ----- all, any

defmethod(OBJ, gall, Functor, Array)
  OBJ *obj = self2->object;
  OBJ *end = self2->object+self2->size;

  for (; obj < end; obj++)
    if (geval1(_1, *obj) == False)
      retmethod(False);
      
  retmethod(True);
endmethod

defmethod(OBJ, gany, Functor, Array)
  OBJ *obj = self2->object;
  OBJ *end = self2->object+self2->size;

  for (; obj < end; obj++)
    if (geval1(_1, *obj) == True)
      retmethod(True);
      
  retmethod(False);
endmethod

// ----- filter, reduce, accumulate

defmethod(OBJ, gfilter, Functor, Array)
  struct Array* arr = dynarray_alloc(self2->size);
  OBJ _arr = (OBJ)arr; PRT(_arr);
  OBJ *end = self2->object+self2->size;
  OBJ *obj = arr  ->object;
  OBJ *src = self2->object;

  for (; src < end; src++)
    if (geval1(_1, *src) == True)
      *obj++ = gretain(*src), ++arr->size;

  gadjust(_arr);
  UNPRT(_arr);
  retmethod(gautoRelease(_arr));
endmethod

defmethod(OBJ, greduce, Functor, Any, Array)
  OBJ  obj = _2;
  OBJ *src = self3->object;
  OBJ *end = self3->object+self3->size;
  
  while (src < end)
    obj = geval2(_1, obj, *src++);

  retmethod(obj);
endmethod

defmethod(OBJ, gaccumulate, Functor, Any, Array)
  struct Array* arr = array_alloc(self3->size+1);
  OBJ _arr = (OBJ)arr; PRT(_arr);
  OBJ *obj = arr  ->object;
  OBJ *end = arr  ->object+arr->size;
  OBJ *src = self3->object;

  *obj++ = gretain(_2);
  
  for (; obj < end; obj++)
    *obj = gretain( geval2(_1,obj[-1],*src++) );

  UNPRT(_arr);
  retmethod(gautoRelease(_arr));
endmethod

// ----- finding

defmethod(OBJ, gfind, Functor, Any, Array)
  useclass(Lesser, Equal, Greater);

  if (self3->size == 0)
    retmethod(0);

  OBJ *obj = self3->object;
  OBJ  res = geval2(_1, _2, *obj);

  if (res == True || res == Equal) // found
    retmethod(*obj);

  // linear search
  if (res == False) {
    OBJ *end = self3->object+self3->size;
    
    for (++obj; obj < end; obj++)
      if (geval2(_1, _2, *obj) == True) // found
        retmethod(*obj);

    retmethod(0);
  }

  // binary search
  if (res == Lesser)
    retmethod(0);
  
  test_assert( res == Greater,
    "gfind expects functor returning TrueFalse or Ordered predicates" );

  U32 lo = 1, hi = self3->size-1;
    
  while(lo <= hi) {
    U32 i = (lo + hi) / 2;
    res = geval2(_1, _2, obj[i]);

    if (res == Equal)
      retmethod(obj[i]); // found

    if (res == Lesser)
      hi = i-1;
    else
      lo = i+1;
  }

  retmethod(0);  
endmethod

// ----- sorting (in place)

#define NETSORT(a,r) \
  do { \
    switch(r) { \
    case 1: \
      SORT(a[0],a[1]); \
      return; \
    \
    case 2: \
      SORT(a[0],a[1]); \
      SORT(a[0],a[2]); \
      SORT(a[1],a[2]); \
      return; \
    \
    case 3: \
      SORT(a[0],a[2]); SORT(a[1],a[3]); \
      SORT(a[0],a[1]); SORT(a[2],a[3]); \
      SORT(a[1],a[2]); \
      return; \
    \
    case 4: \
      SORT(a[0],a[4]); SORT(a[1],a[3]); \
      SORT(a[0],a[2]); \
      SORT(a[2],a[4]); SORT(a[0],a[1]); \
      SORT(a[2],a[3]); SORT(a[1],a[4]); \
      SORT(a[1],a[2]); SORT(a[3],a[4]); \
      return; \
    \
    case 5: \
      SORT(a[0],a[4]); SORT(a[1],a[5]); \
      SORT(a[0],a[2]); SORT(a[1],a[3]); \
      SORT(a[2],a[4]); SORT(a[3],a[5]); \
      SORT(a[0],a[1]); SORT(a[4],a[5]); \
      SORT(a[1],a[4]); SORT(a[2],a[3]); \
      SORT(a[1],a[2]); SORT(a[3],a[4]); \
      return; \
    } \
  } while(0)

/* from "Quicksort Is Optimal", R. Sedgwick & J. Bentley, 2002
   plus some practical improvements.
 */

#define EXCH(a,b) (t=(a),(a)=(b),(b)=t)
#define SORT(a,b) if (GCMP(b,a) == Lesser) EXCH(a,b)
#define GCMP(a,b) geval2(fun,a,b)

static inline U32
pivot(void)
{
  static U32 x = 1; // no need to be thread safe
  
  return x = x * 2621124293u + 1;
}

static void
quicksort_fun(OBJ a[], I32 r, OBJ fun)
{
  useclass(Lesser, Equal);
  I32 i, j, p, q;
  OBJ t, ri, rj;

  // nothing to do
  if (r <= 0) return;

  // optimized sort for small sizes
  NETSORT(a,r);

  // select pivot as the median-of-three taken pseudo-randomly
  i = pivot() % (r+1) + 0, EXCH(a[i],a[0  ]);
  i = pivot() % (r  ) + 1, EXCH(a[i],a[r  ]);
  i = pivot() % (r-1) + 1, EXCH(a[i],a[r-1]);
  SORT(a[0],a[r-1]);
  if ((ri = GCMP(a[r  ],a[0])) == Lesser) EXCH(a[r],a[0  ]);
  if ((rj = GCMP(a[r-1],a[r])) == Lesser) EXCH(a[r],a[r-1]);

  // partitioning initialization
  i = 0, j = r-1;
  p = ri == Equal ? i : -1;
  q = rj == Equal ? j :  r;

  // three-way partitioning
  for (;;) {
    while ((rj = GCMP(a[++i],a[  r])) == Lesser     ) ;
    while ((ri = GCMP(a[  r],a[--j])) == Lesser && j) ;

    if (i >= j) break;

    EXCH(a[i], a[j]);
    if (ri == Equal) ++p, EXCH(a[p],a[i]);
    if (rj == Equal) --q, EXCH(a[q],a[j]);
  }

  // move pivot to center
  EXCH(a[i], a[r]);

  // move equal partition from borders to center
  for (j = i-1; p-- > 0; j--) EXCH(a[p],a[j]);
  for (i = i+1; ++q < r; i++) EXCH(a[q],a[i]);

  // divide & conquer (small first)
  OBJ *s, *l;
  
  if (j < r-i)
    s = a, l = a+i, p = j, q = r-i;
  else
    l = a, s = a+i, q = j, p = r-i;

  quicksort_fun(s,p,fun);
  quicksort_fun(l,q,fun); // tail recursion
}

defmethod(void, gsortBy, Array, Functor)
  quicksort_fun(self->object, self->size-1, _2);
endmethod

