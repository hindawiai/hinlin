<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (c) 1994 - 1997, 99, 2000, 06, 07  Ralf Baechle (ralf@linux-mips.org)
 * Copyright (c) 1999, 2000  Silicon Graphics, Inc.
 */
#अगर_अघोषित _ASM_BITOPS_H
#घोषणा _ASM_BITOPS_H

#अगर_अघोषित _LINUX_BITOPS_H
#त्रुटि only <linux/bitops.h> can be included directly
#पूर्ण_अगर

#समावेश <linux/bits.h>
#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/byteorder.h>		/* sigh ... */
#समावेश <यंत्र/compiler.h>
#समावेश <यंत्र/cpu-features.h>
#समावेश <यंत्र/isa-rev.h>
#समावेश <यंत्र/llsc.h>
#समावेश <यंत्र/sgidefs.h>
#समावेश <यंत्र/war.h>

#घोषणा __bit_op(mem, insn, inमाला_दो...) करो अणु			\
	अचिन्हित दीर्घ __temp;					\
								\
	यंत्र अस्थिर(						\
	"	.set		push			\n"	\
	"	.set		" MIPS_ISA_LEVEL "	\n"	\
	"	" __SYNC(full, loongson3_war) "		\n"	\
	"1:	" __LL		"%0, %1			\n"	\
	"	" insn		"			\n"	\
	"	" __SC		"%0, %1			\n"	\
	"	" __SC_BEQZ	"%0, 1b			\n"	\
	"	.set		pop			\n"	\
	: "=&r"(__temp), "+" GCC_OFF_SMALL_ASM()(mem)		\
	: inमाला_दो						\
	: __LLSC_CLOBBER);					\
पूर्ण जबतक (0)

#घोषणा __test_bit_op(mem, ll_dst, insn, inमाला_दो...) (अणु		\
	अचिन्हित दीर्घ __orig, __temp;				\
								\
	यंत्र अस्थिर(						\
	"	.set		push			\n"	\
	"	.set		" MIPS_ISA_LEVEL "	\n"	\
	"	" __SYNC(full, loongson3_war) "		\n"	\
	"1:	" __LL		ll_dst ", %2		\n"	\
	"	" insn		"			\n"	\
	"	" __SC		"%1, %2			\n"	\
	"	" __SC_BEQZ	"%1, 1b			\n"	\
	"	.set		pop			\n"	\
	: "=&r"(__orig), "=&r"(__temp),				\
	  "+" GCC_OFF_SMALL_ASM()(mem)				\
	: inमाला_दो						\
	: __LLSC_CLOBBER);					\
								\
	__orig;							\
पूर्ण)

/*
 * These are the "slower" versions of the functions and are in bitops.c.
 * These functions call raw_local_irq_अणुsave,restoreपूर्ण().
 */
व्योम __mips_set_bit(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr);
व्योम __mips_clear_bit(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr);
व्योम __mips_change_bit(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr);
पूर्णांक __mips_test_and_set_bit_lock(अचिन्हित दीर्घ nr,
				 अस्थिर अचिन्हित दीर्घ *addr);
पूर्णांक __mips_test_and_clear_bit(अचिन्हित दीर्घ nr,
			      अस्थिर अचिन्हित दीर्घ *addr);
पूर्णांक __mips_test_and_change_bit(अचिन्हित दीर्घ nr,
			       अस्थिर अचिन्हित दीर्घ *addr);


/*
 * set_bit - Atomically set a bit in memory
 * @nr: the bit to set
 * @addr: the address to start counting from
 *
 * This function is atomic and may not be reordered.  See __set_bit()
 * अगर you करो not require the atomic guarantees.
 * Note that @nr may be almost arbitrarily large; this function is not
 * restricted to acting on a single-word quantity.
 */
अटल अंतरभूत व्योम set_bit(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अस्थिर अचिन्हित दीर्घ *m = &addr[BIT_WORD(nr)];
	पूर्णांक bit = nr % BITS_PER_LONG;

	अगर (!kernel_uses_llsc) अणु
		__mips_set_bit(nr, addr);
		वापस;
	पूर्ण

	अगर ((MIPS_ISA_REV >= 2) && __builtin_स्थिरant_p(bit) && (bit >= 16)) अणु
		__bit_op(*m, __INS "%0, %3, %2, 1", "i"(bit), "r"(~0));
		वापस;
	पूर्ण

	__bit_op(*m, "or\t%0, %2", "ir"(BIT(bit)));
पूर्ण

/*
 * clear_bit - Clears a bit in memory
 * @nr: Bit to clear
 * @addr: Address to start counting from
 *
 * clear_bit() is atomic and may not be reordered.  However, it करोes
 * not contain a memory barrier, so अगर it is used क्रम locking purposes,
 * you should call smp_mb__beक्रमe_atomic() and/or smp_mb__after_atomic()
 * in order to ensure changes are visible on other processors.
 */
अटल अंतरभूत व्योम clear_bit(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अस्थिर अचिन्हित दीर्घ *m = &addr[BIT_WORD(nr)];
	पूर्णांक bit = nr % BITS_PER_LONG;

	अगर (!kernel_uses_llsc) अणु
		__mips_clear_bit(nr, addr);
		वापस;
	पूर्ण

	अगर ((MIPS_ISA_REV >= 2) && __builtin_स्थिरant_p(bit)) अणु
		__bit_op(*m, __INS "%0, $0, %2, 1", "i"(bit));
		वापस;
	पूर्ण

	__bit_op(*m, "and\t%0, %2", "ir"(~BIT(bit)));
पूर्ण

/*
 * clear_bit_unlock - Clears a bit in memory
 * @nr: Bit to clear
 * @addr: Address to start counting from
 *
 * clear_bit() is atomic and implies release semantics beक्रमe the memory
 * operation. It can be used क्रम an unlock.
 */
अटल अंतरभूत व्योम clear_bit_unlock(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	smp_mb__beक्रमe_atomic();
	clear_bit(nr, addr);
पूर्ण

/*
 * change_bit - Toggle a bit in memory
 * @nr: Bit to change
 * @addr: Address to start counting from
 *
 * change_bit() is atomic and may not be reordered.
 * Note that @nr may be almost arbitrarily large; this function is not
 * restricted to acting on a single-word quantity.
 */
अटल अंतरभूत व्योम change_bit(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अस्थिर अचिन्हित दीर्घ *m = &addr[BIT_WORD(nr)];
	पूर्णांक bit = nr % BITS_PER_LONG;

	अगर (!kernel_uses_llsc) अणु
		__mips_change_bit(nr, addr);
		वापस;
	पूर्ण

	__bit_op(*m, "xor\t%0, %2", "ir"(BIT(bit)));
पूर्ण

/*
 * test_and_set_bit_lock - Set a bit and वापस its old value
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This operation is atomic and implies acquire ordering semantics
 * after the memory operation.
 */
अटल अंतरभूत पूर्णांक test_and_set_bit_lock(अचिन्हित दीर्घ nr,
	अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अस्थिर अचिन्हित दीर्घ *m = &addr[BIT_WORD(nr)];
	पूर्णांक bit = nr % BITS_PER_LONG;
	अचिन्हित दीर्घ res, orig;

	अगर (!kernel_uses_llsc) अणु
		res = __mips_test_and_set_bit_lock(nr, addr);
	पूर्ण अन्यथा अणु
		orig = __test_bit_op(*m, "%0",
				     "or\t%1, %0, %3",
				     "ir"(BIT(bit)));
		res = (orig & BIT(bit)) != 0;
	पूर्ण

	smp_llsc_mb();

	वापस res;
पूर्ण

/*
 * test_and_set_bit - Set a bit and वापस its old value
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This operation is atomic and cannot be reordered.
 * It also implies a memory barrier.
 */
अटल अंतरभूत पूर्णांक test_and_set_bit(अचिन्हित दीर्घ nr,
	अस्थिर अचिन्हित दीर्घ *addr)
अणु
	smp_mb__beक्रमe_atomic();
	वापस test_and_set_bit_lock(nr, addr);
पूर्ण

/*
 * test_and_clear_bit - Clear a bit and वापस its old value
 * @nr: Bit to clear
 * @addr: Address to count from
 *
 * This operation is atomic and cannot be reordered.
 * It also implies a memory barrier.
 */
अटल अंतरभूत पूर्णांक test_and_clear_bit(अचिन्हित दीर्घ nr,
	अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अस्थिर अचिन्हित दीर्घ *m = &addr[BIT_WORD(nr)];
	पूर्णांक bit = nr % BITS_PER_LONG;
	अचिन्हित दीर्घ res, orig;

	smp_mb__beक्रमe_atomic();

	अगर (!kernel_uses_llsc) अणु
		res = __mips_test_and_clear_bit(nr, addr);
	पूर्ण अन्यथा अगर ((MIPS_ISA_REV >= 2) && __builtin_स्थिरant_p(nr)) अणु
		res = __test_bit_op(*m, "%1",
				    __EXT "%0, %1, %3, 1;"
				    __INS "%1, $0, %3, 1",
				    "i"(bit));
	पूर्ण अन्यथा अणु
		orig = __test_bit_op(*m, "%0",
				     "or\t%1, %0, %3;"
				     "xor\t%1, %1, %3",
				     "ir"(BIT(bit)));
		res = (orig & BIT(bit)) != 0;
	पूर्ण

	smp_llsc_mb();

	वापस res;
पूर्ण

/*
 * test_and_change_bit - Change a bit and वापस its old value
 * @nr: Bit to change
 * @addr: Address to count from
 *
 * This operation is atomic and cannot be reordered.
 * It also implies a memory barrier.
 */
अटल अंतरभूत पूर्णांक test_and_change_bit(अचिन्हित दीर्घ nr,
	अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अस्थिर अचिन्हित दीर्घ *m = &addr[BIT_WORD(nr)];
	पूर्णांक bit = nr % BITS_PER_LONG;
	अचिन्हित दीर्घ res, orig;

	smp_mb__beक्रमe_atomic();

	अगर (!kernel_uses_llsc) अणु
		res = __mips_test_and_change_bit(nr, addr);
	पूर्ण अन्यथा अणु
		orig = __test_bit_op(*m, "%0",
				     "xor\t%1, %0, %3",
				     "ir"(BIT(bit)));
		res = (orig & BIT(bit)) != 0;
	पूर्ण

	smp_llsc_mb();

	वापस res;
पूर्ण

#अघोषित __bit_op
#अघोषित __test_bit_op

#समावेश <यंत्र-generic/bitops/non-atomic.h>

/*
 * __clear_bit_unlock - Clears a bit in memory
 * @nr: Bit to clear
 * @addr: Address to start counting from
 *
 * __clear_bit() is non-atomic and implies release semantics beक्रमe the memory
 * operation. It can be used क्रम an unlock अगर no other CPUs can concurrently
 * modअगरy other bits in the word.
 */
अटल अंतरभूत व्योम __clear_bit_unlock(अचिन्हित दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	smp_mb__beक्रमe_llsc();
	__clear_bit(nr, addr);
	nudge_ग_लिखोs();
पूर्ण

/*
 * Return the bit position (0..63) of the most signअगरicant 1 bit in a word
 * Returns -1 अगर no 1 bit exists
 */
अटल __always_अंतरभूत अचिन्हित दीर्घ __fls(अचिन्हित दीर्घ word)
अणु
	पूर्णांक num;

	अगर (BITS_PER_LONG == 32 && !__builtin_स्थिरant_p(word) &&
	    __builtin_स्थिरant_p(cpu_has_clo_clz) && cpu_has_clo_clz) अणु
		__यंत्र__(
		"	.set	push					\n"
		"	.set	"MIPS_ISA_LEVEL"			\n"
		"	clz	%0, %1					\n"
		"	.set	pop					\n"
		: "=r" (num)
		: "r" (word));

		वापस 31 - num;
	पूर्ण

	अगर (BITS_PER_LONG == 64 && !__builtin_स्थिरant_p(word) &&
	    __builtin_स्थिरant_p(cpu_has_mips64) && cpu_has_mips64) अणु
		__यंत्र__(
		"	.set	push					\n"
		"	.set	"MIPS_ISA_LEVEL"			\n"
		"	dclz	%0, %1					\n"
		"	.set	pop					\n"
		: "=r" (num)
		: "r" (word));

		वापस 63 - num;
	पूर्ण

	num = BITS_PER_LONG - 1;

#अगर BITS_PER_LONG == 64
	अगर (!(word & (~0ul << 32))) अणु
		num -= 32;
		word <<= 32;
	पूर्ण
#पूर्ण_अगर
	अगर (!(word & (~0ul << (BITS_PER_LONG-16)))) अणु
		num -= 16;
		word <<= 16;
	पूर्ण
	अगर (!(word & (~0ul << (BITS_PER_LONG-8)))) अणु
		num -= 8;
		word <<= 8;
	पूर्ण
	अगर (!(word & (~0ul << (BITS_PER_LONG-4)))) अणु
		num -= 4;
		word <<= 4;
	पूर्ण
	अगर (!(word & (~0ul << (BITS_PER_LONG-2)))) अणु
		num -= 2;
		word <<= 2;
	पूर्ण
	अगर (!(word & (~0ul << (BITS_PER_LONG-1))))
		num -= 1;
	वापस num;
पूर्ण

/*
 * __ffs - find first bit in word.
 * @word: The word to search
 *
 * Returns 0..SZLONG-1
 * Undefined अगर no bit exists, so code should check against 0 first.
 */
अटल __always_अंतरभूत अचिन्हित दीर्घ __ffs(अचिन्हित दीर्घ word)
अणु
	वापस __fls(word & -word);
पूर्ण

/*
 * fls - find last bit set.
 * @word: The word to search
 *
 * This is defined the same way as ffs.
 * Note fls(0) = 0, fls(1) = 1, fls(0x80000000) = 32.
 */
अटल अंतरभूत पूर्णांक fls(अचिन्हित पूर्णांक x)
अणु
	पूर्णांक r;

	अगर (!__builtin_स्थिरant_p(x) &&
	    __builtin_स्थिरant_p(cpu_has_clo_clz) && cpu_has_clo_clz) अणु
		__यंत्र__(
		"	.set	push					\n"
		"	.set	"MIPS_ISA_LEVEL"			\n"
		"	clz	%0, %1					\n"
		"	.set	pop					\n"
		: "=r" (x)
		: "r" (x));

		वापस 32 - x;
	पूर्ण

	r = 32;
	अगर (!x)
		वापस 0;
	अगर (!(x & 0xffff0000u)) अणु
		x <<= 16;
		r -= 16;
	पूर्ण
	अगर (!(x & 0xff000000u)) अणु
		x <<= 8;
		r -= 8;
	पूर्ण
	अगर (!(x & 0xf0000000u)) अणु
		x <<= 4;
		r -= 4;
	पूर्ण
	अगर (!(x & 0xc0000000u)) अणु
		x <<= 2;
		r -= 2;
	पूर्ण
	अगर (!(x & 0x80000000u)) अणु
		x <<= 1;
		r -= 1;
	पूर्ण
	वापस r;
पूर्ण

#समावेश <यंत्र-generic/bitops/fls64.h>

/*
 * ffs - find first bit set.
 * @word: The word to search
 *
 * This is defined the same way as
 * the libc and compiler builtin ffs routines, thereक्रमe
 * dअगरfers in spirit from the below ffz (man ffs).
 */
अटल अंतरभूत पूर्णांक ffs(पूर्णांक word)
अणु
	अगर (!word)
		वापस 0;

	वापस fls(word & -word);
पूर्ण

#समावेश <यंत्र-generic/bitops/ffz.h>
#समावेश <यंत्र-generic/bitops/find.h>

#अगर_घोषित __KERNEL__

#समावेश <यंत्र-generic/bitops/sched.h>

#समावेश <यंत्र/arch_hweight.h>
#समावेश <यंत्र-generic/bitops/स्थिर_hweight.h>

#समावेश <यंत्र-generic/bitops/le.h>
#समावेश <यंत्र-generic/bitops/ext2-atomic.h>

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* _ASM_BITOPS_H */
