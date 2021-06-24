<शैली गुरु>
/*
 * include/यंत्र-xtensa/bitops.h
 *
 * Atomic operations that C can't guarantee us.Useful क्रम resource counting etc.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2007 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_BITOPS_H
#घोषणा _XTENSA_BITOPS_H

#अगर_अघोषित _LINUX_BITOPS_H
#त्रुटि only <linux/bitops.h> can be included directly
#पूर्ण_अगर

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/barrier.h>

#समावेश <यंत्र-generic/bitops/non-atomic.h>

#अगर XCHAL_HAVE_NSA

अटल अंतरभूत अचिन्हित दीर्घ __cntlz (अचिन्हित दीर्घ x)
अणु
	पूर्णांक lz;
	यंत्र ("nsau %0, %1" : "=r" (lz) : "r" (x));
	वापस lz;
पूर्ण

/*
 * ffz: Find first zero in word. Undefined अगर no zero exists.
 * bit 0 is the LSB of addr; bit 32 is the LSB of (addr+1).
 */

अटल अंतरभूत पूर्णांक ffz(अचिन्हित दीर्घ x)
अणु
	वापस 31 - __cntlz(~x & -~x);
पूर्ण

/*
 * __ffs: Find first bit set in word. Return 0 क्रम bit 0
 */

अटल अंतरभूत अचिन्हित दीर्घ __ffs(अचिन्हित दीर्घ x)
अणु
	वापस 31 - __cntlz(x & -x);
पूर्ण

/*
 * ffs: Find first bit set in word. This is defined the same way as
 * the libc and compiler builtin ffs routines, thereक्रमe
 * dअगरfers in spirit from the above ffz (man ffs).
 */

अटल अंतरभूत पूर्णांक ffs(अचिन्हित दीर्घ x)
अणु
	वापस 32 - __cntlz(x & -x);
पूर्ण

/*
 * fls: Find last (most-signअगरicant) bit set in word.
 * Note fls(0) = 0, fls(1) = 1, fls(0x80000000) = 32.
 */

अटल अंतरभूत पूर्णांक fls (अचिन्हित पूर्णांक x)
अणु
	वापस 32 - __cntlz(x);
पूर्ण

/**
 * __fls - find last (most-signअगरicant) set bit in a दीर्घ word
 * @word: the word to search
 *
 * Undefined अगर no set bit exists, so code should check against 0 first.
 */
अटल अंतरभूत अचिन्हित दीर्घ __fls(अचिन्हित दीर्घ word)
अणु
	वापस 31 - __cntlz(word);
पूर्ण
#अन्यथा

/* Use the generic implementation अगर we करोn't have the nsa/nsau inकाष्ठाions. */

# include <यंत्र-generic/bitops/ffs.h>
# include <यंत्र-generic/bitops/__ffs.h>
# include <यंत्र-generic/bitops/ffz.h>
# include <यंत्र-generic/bitops/fls.h>
# include <यंत्र-generic/bitops/__fls.h>

#पूर्ण_अगर

#समावेश <यंत्र-generic/bitops/fls64.h>

#अगर XCHAL_HAVE_EXCLUSIVE

#घोषणा BIT_OP(op, insn, inv)						\
अटल अंतरभूत व्योम op##_bit(अचिन्हित पूर्णांक bit, अस्थिर अचिन्हित दीर्घ *p)\
अणु									\
	अचिन्हित दीर्घ पंचांगp;						\
	अचिन्हित दीर्घ mask = 1UL << (bit & 31);				\
									\
	p += bit >> 5;							\
									\
	__यंत्र__ __अस्थिर__(						\
			"1:     l32ex   %[tmp], %[addr]\n"		\
			"      "insn"   %[tmp], %[tmp], %[mask]\n"	\
			"       s32ex   %[tmp], %[addr]\n"		\
			"       getex   %[tmp]\n"			\
			"       beqz    %[tmp], 1b\n"			\
			: [पंचांगp] "=&a" (पंचांगp)				\
			: [mask] "a" (inv mask), [addr] "a" (p)		\
			: "memory");					\
पूर्ण

#घोषणा TEST_AND_BIT_OP(op, insn, inv)					\
अटल अंतरभूत पूर्णांक							\
test_and_##op##_bit(अचिन्हित पूर्णांक bit, अस्थिर अचिन्हित दीर्घ *p)	\
अणु									\
	अचिन्हित दीर्घ पंचांगp, value;					\
	अचिन्हित दीर्घ mask = 1UL << (bit & 31);				\
									\
	p += bit >> 5;							\
									\
	__यंत्र__ __अस्थिर__(						\
			"1:     l32ex   %[value], %[addr]\n"		\
			"      "insn"   %[tmp], %[value], %[mask]\n"	\
			"       s32ex   %[tmp], %[addr]\n"		\
			"       getex   %[tmp]\n"			\
			"       beqz    %[tmp], 1b\n"			\
			: [पंचांगp] "=&a" (पंचांगp), [value] "=&a" (value)	\
			: [mask] "a" (inv mask), [addr] "a" (p)		\
			: "memory");					\
									\
	वापस value & mask;						\
पूर्ण

#या_अगर XCHAL_HAVE_S32C1I

#घोषणा BIT_OP(op, insn, inv)						\
अटल अंतरभूत व्योम op##_bit(अचिन्हित पूर्णांक bit, अस्थिर अचिन्हित दीर्घ *p)\
अणु									\
	अचिन्हित दीर्घ पंचांगp, value;					\
	अचिन्हित दीर्घ mask = 1UL << (bit & 31);				\
									\
	p += bit >> 5;							\
									\
	__यंत्र__ __अस्थिर__(						\
			"1:     l32i    %[value], %[mem]\n"		\
			"       wsr     %[value], scompare1\n"		\
			"      "insn"   %[tmp], %[value], %[mask]\n"	\
			"       s32c1i  %[tmp], %[mem]\n"		\
			"       bne     %[tmp], %[value], 1b\n"		\
			: [पंचांगp] "=&a" (पंचांगp), [value] "=&a" (value),	\
			  [mem] "+m" (*p)				\
			: [mask] "a" (inv mask)				\
			: "memory");					\
पूर्ण

#घोषणा TEST_AND_BIT_OP(op, insn, inv)					\
अटल अंतरभूत पूर्णांक							\
test_and_##op##_bit(अचिन्हित पूर्णांक bit, अस्थिर अचिन्हित दीर्घ *p)	\
अणु									\
	अचिन्हित दीर्घ पंचांगp, value;					\
	अचिन्हित दीर्घ mask = 1UL << (bit & 31);				\
									\
	p += bit >> 5;							\
									\
	__यंत्र__ __अस्थिर__(						\
			"1:     l32i    %[value], %[mem]\n"		\
			"       wsr     %[value], scompare1\n"		\
			"      "insn"   %[tmp], %[value], %[mask]\n"	\
			"       s32c1i  %[tmp], %[mem]\n"		\
			"       bne     %[tmp], %[value], 1b\n"		\
			: [पंचांगp] "=&a" (पंचांगp), [value] "=&a" (value),	\
			  [mem] "+m" (*p)				\
			: [mask] "a" (inv mask)				\
			: "memory");					\
									\
	वापस पंचांगp & mask;						\
पूर्ण

#अन्यथा

#घोषणा BIT_OP(op, insn, inv)
#घोषणा TEST_AND_BIT_OP(op, insn, inv)

#समावेश <यंत्र-generic/bitops/atomic.h>

#पूर्ण_अगर /* XCHAL_HAVE_S32C1I */

#घोषणा BIT_OPS(op, insn, inv)		\
	BIT_OP(op, insn, inv)		\
	TEST_AND_BIT_OP(op, insn, inv)

BIT_OPS(set, "or", )
BIT_OPS(clear, "and", ~)
BIT_OPS(change, "xor", )

#अघोषित BIT_OPS
#अघोषित BIT_OP
#अघोषित TEST_AND_BIT_OP

#समावेश <यंत्र-generic/bitops/find.h>
#समावेश <यंत्र-generic/bitops/le.h>

#समावेश <यंत्र-generic/bitops/ext2-atomic-setbit.h>

#समावेश <यंत्र-generic/bitops/hweight.h>
#समावेश <यंत्र-generic/bitops/lock.h>
#समावेश <यंत्र-generic/bitops/sched.h>

#पूर्ण_अगर	/* _XTENSA_BITOPS_H */
