<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * arch/sparc64/math-emu/sfp-util.h
 *
 * Copyright (C) 1999 Jakub Jelinek (jj@ultra.linux.cz)
 * Copyright (C) 1999 David S. Miller (davem@redhat.com)
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>

#घोषणा add_ssaaaa(sh, sl, ah, al, bh, bl) 	\
  __यंत्र__ ("addcc %4,%5,%1\n\t"			\
	   "add %2,%3,%0\n\t"			\
  	   "bcs,a,pn %%xcc, 1f\n\t"		\
  	   "add %0, 1, %0\n"			\
  	   "1:"					\
	   : "=r" (sh),				\
	     "=&r" (sl)				\
	   : "r" ((UDItype)(ah)),		\
	     "r" ((UDItype)(bh)),		\
	     "r" ((UDItype)(al)),		\
	     "r" ((UDItype)(bl))		\
	   : "cc")
	   
#घोषणा sub_ddmmss(sh, sl, ah, al, bh, bl) 	\
  __यंत्र__ ("subcc %4,%5,%1\n\t"			\
  	   "sub %2,%3,%0\n\t"			\
  	   "bcs,a,pn %%xcc, 1f\n\t"		\
  	   "sub %0, 1, %0\n"			\
  	   "1:"					\
	   : "=r" (sh),				\
	     "=&r" (sl)				\
	   : "r" ((UDItype)(ah)),		\
	     "r" ((UDItype)(bh)),		\
	     "r" ((UDItype)(al)),		\
	     "r" ((UDItype)(bl))		\
	   : "cc")

#घोषणा umul_ppmm(wh, wl, u, v)				\
  करो अणु							\
	  UDItype पंचांगp1, पंचांगp2, पंचांगp3, पंचांगp4;		\
	  __यंत्र__ __अस्थिर__ (			\
		   "srl %7,0,%3\n\t"			\
		   "mulx %3,%6,%1\n\t"			\
		   "srlx %6,32,%2\n\t"			\
		   "mulx %2,%3,%4\n\t"			\
		   "sllx %4,32,%5\n\t"			\
		   "srl %6,0,%3\n\t"			\
		   "sub %1,%5,%5\n\t"			\
		   "srlx %5,32,%5\n\t"			\
		   "addcc %4,%5,%4\n\t"			\
		   "srlx %7,32,%5\n\t"			\
		   "mulx %3,%5,%3\n\t"			\
		   "mulx %2,%5,%5\n\t"			\
		   "sethi %%hi(0x80000000),%2\n\t"	\
		   "addcc %4,%3,%4\n\t"			\
		   "srlx %4,32,%4\n\t"			\
		   "add %2,%2,%2\n\t"			\
		   "movcc %%xcc,%%g0,%2\n\t"		\
		   "addcc %5,%4,%5\n\t"			\
		   "sllx %3,32,%3\n\t"			\
		   "add %1,%3,%1\n\t"			\
		   "add %5,%2,%0"			\
	   : "=r" (wh),					\
	     "=&r" (wl),				\
	     "=&r" (पंचांगp1), "=&r" (पंचांगp2), "=&r" (पंचांगp3), "=&r" (पंचांगp4) \
	   : "r" ((UDItype)(u)),			\
	     "r" ((UDItype)(v))				\
	   : "cc");					\
  पूर्ण जबतक (0)
  
#घोषणा uभाग_qrnnd(q, r, n1, n0, d) 			\
  करो अणु                                                  \
    UWtype __d1, __d0, __q1, __q0, __r1, __r0, __m;     \
    __d1 = (d >> 32);                                   \
    __d0 = (USItype)d;                                  \
                                                        \
    __r1 = (n1) % __d1;                                 \
    __q1 = (n1) / __d1;                                 \
    __m = (UWtype) __q1 * __d0;                         \
    __r1 = (__r1 << 32) | (n0 >> 32);                   \
    अगर (__r1 < __m)                                     \
      अणु                                                 \
        __q1--, __r1 += (d);                            \
        अगर (__r1 >= (d)) /* i.e. we didn't get carry when adding to __r1 */ \
          अगर (__r1 < __m)                               \
            __q1--, __r1 += (d);                        \
      पूर्ण                                                 \
    __r1 -= __m;                                        \
                                                        \
    __r0 = __r1 % __d1;                                 \
    __q0 = __r1 / __d1;                                 \
    __m = (UWtype) __q0 * __d0;                         \
    __r0 = (__r0 << 32) | ((USItype)n0);                \
    अगर (__r0 < __m)                                     \
      अणु                                                 \
        __q0--, __r0 += (d);                            \
        अगर (__r0 >= (d))                                \
          अगर (__r0 < __m)                               \
            __q0--, __r0 += (d);                        \
      पूर्ण                                                 \
    __r0 -= __m;                                        \
                                                        \
    (q) = (UWtype) (__q1 << 32)  | __q0;                \
    (r) = __r0;                                         \
  पूर्ण जबतक (0)

#घोषणा UDIV_NEEDS_NORMALIZATION 1  

#घोषणा पात() \
	वापस 0

#अगर_घोषित __BIG_ENDIAN
#घोषणा __BYTE_ORDER __BIG_ENDIAN
#अन्यथा
#घोषणा __BYTE_ORDER __LITTLE_ENDIAN
#पूर्ण_अगर
