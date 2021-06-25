<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>

#घोषणा add_ssaaaa(sh, sl, ah, al, bh, bl) 				\
  __यंत्र__ ("addcc %r4,%5,%1\n\t"					\
	   "addx %r2,%3,%0\n"						\
	   : "=r" (sh),							\
	     "=&r" (sl)							\
	   : "%rJ" ((USItype)(ah)),					\
	     "rI" ((USItype)(bh)),					\
	     "%rJ" ((USItype)(al)),					\
	     "rI" ((USItype)(bl))					\
	   : "cc")
#घोषणा sub_ddmmss(sh, sl, ah, al, bh, bl) 				\
  __यंत्र__ ("subcc %r4,%5,%1\n\t"					\
	   "subx %r2,%3,%0\n"						\
	   : "=r" (sh),							\
	     "=&r" (sl)							\
	   : "rJ" ((USItype)(ah)),					\
	     "rI" ((USItype)(bh)),					\
	     "rJ" ((USItype)(al)),					\
	     "rI" ((USItype)(bl))					\
	   : "cc")

#घोषणा umul_ppmm(w1, w0, u, v) \
  __यंत्र__ ("! Inlined umul_ppmm\n\t"					\
	"wr	%%g0,%2,%%y	! SPARC has 0-3 delay insn after a wr\n\t" \
	"sra	%3,31,%%g2	! Don't move this insn\n\t"		\
	"and	%2,%%g2,%%g2	! Don't move this insn\n\t"		\
	"andcc	%%g0,0,%%g1	! Don't move this insn\n\t"		\
	"mulscc	%%g1,%3,%%g1\n\t"					\
	"mulscc	%%g1,%3,%%g1\n\t"					\
	"mulscc	%%g1,%3,%%g1\n\t"					\
	"mulscc	%%g1,%3,%%g1\n\t"					\
	"mulscc	%%g1,%3,%%g1\n\t"					\
	"mulscc	%%g1,%3,%%g1\n\t"					\
	"mulscc	%%g1,%3,%%g1\n\t"					\
	"mulscc	%%g1,%3,%%g1\n\t"					\
	"mulscc	%%g1,%3,%%g1\n\t"					\
	"mulscc	%%g1,%3,%%g1\n\t"					\
	"mulscc	%%g1,%3,%%g1\n\t"					\
	"mulscc	%%g1,%3,%%g1\n\t"					\
	"mulscc	%%g1,%3,%%g1\n\t"					\
	"mulscc	%%g1,%3,%%g1\n\t"					\
	"mulscc	%%g1,%3,%%g1\n\t"					\
	"mulscc	%%g1,%3,%%g1\n\t"					\
	"mulscc	%%g1,%3,%%g1\n\t"					\
	"mulscc	%%g1,%3,%%g1\n\t"					\
	"mulscc	%%g1,%3,%%g1\n\t"					\
	"mulscc	%%g1,%3,%%g1\n\t"					\
	"mulscc	%%g1,%3,%%g1\n\t"					\
	"mulscc	%%g1,%3,%%g1\n\t"					\
	"mulscc	%%g1,%3,%%g1\n\t"					\
	"mulscc	%%g1,%3,%%g1\n\t"					\
	"mulscc	%%g1,%3,%%g1\n\t"					\
	"mulscc	%%g1,%3,%%g1\n\t"					\
	"mulscc	%%g1,%3,%%g1\n\t"					\
	"mulscc	%%g1,%3,%%g1\n\t"					\
	"mulscc	%%g1,%3,%%g1\n\t"					\
	"mulscc	%%g1,%3,%%g1\n\t"					\
	"mulscc	%%g1,%3,%%g1\n\t"					\
	"mulscc	%%g1,%3,%%g1\n\t"					\
	"mulscc	%%g1,0,%%g1\n\t" 					\
	"add	%%g1,%%g2,%0\n\t" 					\
	"rd	%%y,%1\n"						\
	   : "=r" (w1),							\
	     "=r" (w0)							\
	   : "%rI" ((USItype)(u)),					\
	     "r" ((USItype)(v))						\
	   : "%g1", "%g2", "cc")

/* It's quite necessary to add this much assembler क्रम the sparc.
   The शेष uभाग_qrnnd (in C) is more than 10 बार slower!  */
#घोषणा uभाग_qrnnd(q, r, n1, n0, d) \
  __यंत्र__ ("! Inlined udiv_qrnnd\n\t"					\
	   "mov	32,%%g1\n\t"						\
	   "subcc	%1,%2,%%g0\n\t"					\
	   "1:	bcs	5f\n\t"						\
	   "addxcc %0,%0,%0	! shift n1n0 and a q-bit in lsb\n\t"	\
	   "sub	%1,%2,%1	! this kills msb of n\n\t"		\
	   "addx	%1,%1,%1	! so this can't give carry\n\t"	\
	   "subcc	%%g1,1,%%g1\n\t"				\
	   "2:	bne	1b\n\t"						\
	   "subcc	%1,%2,%%g0\n\t"					\
	   "bcs	3f\n\t"							\
	   "addxcc %0,%0,%0	! shift n1n0 and a q-bit in lsb\n\t"	\
	   "b		3f\n\t"						\
	   "sub	%1,%2,%1	! this kills msb of n\n\t"		\
	   "4:	sub	%1,%2,%1\n\t"					\
	   "5:	addxcc	%1,%1,%1\n\t"					\
	   "bcc	2b\n\t"							\
	   "subcc	%%g1,1,%%g1\n\t"				\
	   "! Got carry from n.  Subtract next step to cancel this carry.\n\t" \
	   "bne	4b\n\t"							\
	   "addcc	%0,%0,%0	! shift n1n0 and a 0-bit in lsb\n\t" \
	   "sub	%1,%2,%1\n\t"						\
	   "3:	xnor	%0,0,%0\n\t"					\
	   "! End of inline udiv_qrnnd\n"				\
	   : "=&r" (q),							\
	     "=&r" (r)							\
	   : "r" ((USItype)(d)),					\
	     "1" ((USItype)(n1)),					\
	     "0" ((USItype)(n0)) : "%g1", "cc")
#घोषणा UDIV_NEEDS_NORMALIZATION 0

#घोषणा पात()								\
	वापस 0

#अगर_घोषित __BIG_ENDIAN
#घोषणा __BYTE_ORDER __BIG_ENDIAN
#अन्यथा
#घोषणा __BYTE_ORDER __LITTLE_ENDIAN
#पूर्ण_अगर
