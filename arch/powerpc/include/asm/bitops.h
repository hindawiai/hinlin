<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * PowerPC atomic bit operations.
 *
 * Merged version by David Gibson <david@gibson.dropbear.id.au>.
 * Based on ppc64 versions by: Dave Engebretsen, Todd Inglett, Don
 * Reed, Pat McCarthy, Peter Bergner, Anton Blanअक्षरd.  They
 * originally took it from the ppc32 code.
 *
 * Within a word, bits are numbered LSB first.  Lot's of places make
 * this assumption by directly testing bits with (val & (1<<nr)).
 * This can cause confusion क्रम large (> 1 word) biपंचांगaps on a
 * big-endian प्रणाली because, unlike little endian, the number of each
 * bit depends on the word size.
 *
 * The bitop functions are defined to work on अचिन्हित दीर्घs, so क्रम a
 * ppc64 प्रणाली the bits end up numbered:
 *   |63..............0|127............64|191...........128|255...........192|
 * and on ppc32:
 *   |31.....0|63....32|95....64|127...96|159..128|191..160|223..192|255..224|
 *
 * There are a few little-endian macros used mostly क्रम fileप्रणाली
 * biपंचांगaps, these work on similar bit arrays layouts, but
 * byte-oriented:
 *   |7...0|15...8|23...16|31...24|39...32|47...40|55...48|63...56|
 *
 * The मुख्य dअगरference is that bit 3-5 (64b) or 3-4 (32b) in the bit
 * number field needs to be reversed compared to the big-endian bit
 * fields. This can be achieved by XOR with 0x38 (64b) or 0x18 (32b).
 */

#अगर_अघोषित _ASM_POWERPC_BITOPS_H
#घोषणा _ASM_POWERPC_BITOPS_H

#अगर_घोषित __KERNEL__

#अगर_अघोषित _LINUX_BITOPS_H
#त्रुटि only <linux/bitops.h> can be included directly
#पूर्ण_अगर

#समावेश <linux/compiler.h>
#समावेश <यंत्र/यंत्र-compat.h>
#समावेश <यंत्र/synch.h>

/* PPC bit number conversion */
#घोषणा PPC_BITLSHIFT(be)	(BITS_PER_LONG - 1 - (be))
#घोषणा PPC_BIT(bit)		(1UL << PPC_BITLSHIFT(bit))
#घोषणा PPC_BITMASK(bs, be)	((PPC_BIT(bs) - PPC_BIT(be)) | PPC_BIT(bs))

/* Put a PPC bit पूर्णांकo a "normal" bit position */
#घोषणा PPC_BITEXTRACT(bits, ppc_bit, dst_bit)			\
	((((bits) >> PPC_BITLSHIFT(ppc_bit)) & 1) << (dst_bit))

#घोषणा PPC_BITLSHIFT32(be)	(32 - 1 - (be))
#घोषणा PPC_BIT32(bit)		(1UL << PPC_BITLSHIFT32(bit))
#घोषणा PPC_BITMASK32(bs, be)	((PPC_BIT32(bs) - PPC_BIT32(be))|PPC_BIT32(bs))

#घोषणा PPC_BITLSHIFT8(be)	(8 - 1 - (be))
#घोषणा PPC_BIT8(bit)		(1UL << PPC_BITLSHIFT8(bit))
#घोषणा PPC_BITMASK8(bs, be)	((PPC_BIT8(bs) - PPC_BIT8(be))|PPC_BIT8(bs))

#समावेश <यंत्र/barrier.h>

/* Macro क्रम generating the ***_bits() functions */
#घोषणा DEFINE_BITOP(fn, op, prefix)		\
अटल अंतरभूत व्योम fn(अचिन्हित दीर्घ mask,	\
		अस्थिर अचिन्हित दीर्घ *_p)	\
अणु						\
	अचिन्हित दीर्घ old;			\
	अचिन्हित दीर्घ *p = (अचिन्हित दीर्घ *)_p;	\
	__यंत्र__ __अस्थिर__ (			\
	prefix					\
"1:"	PPC_LLARX(%0,0,%3,0) "\n"		\
	stringअगरy_in_c(op) "%0,%0,%2\n"		\
	PPC_STLCX "%0,0,%3\n"			\
	"bne- 1b\n"				\
	: "=&r" (old), "+m" (*p)		\
	: "r" (mask), "r" (p)			\
	: "cc", "memory");			\
पूर्ण

DEFINE_BITOP(set_bits, or, "")
DEFINE_BITOP(clear_bits, andc, "")
DEFINE_BITOP(clear_bits_unlock, andc, PPC_RELEASE_BARRIER)
DEFINE_BITOP(change_bits, xor, "")

अटल अंतरभूत व्योम arch_set_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	set_bits(BIT_MASK(nr), addr + BIT_WORD(nr));
पूर्ण

अटल अंतरभूत व्योम arch_clear_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	clear_bits(BIT_MASK(nr), addr + BIT_WORD(nr));
पूर्ण

अटल अंतरभूत व्योम arch_clear_bit_unlock(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	clear_bits_unlock(BIT_MASK(nr), addr + BIT_WORD(nr));
पूर्ण

अटल अंतरभूत व्योम arch_change_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	change_bits(BIT_MASK(nr), addr + BIT_WORD(nr));
पूर्ण

/* Like DEFINE_BITOP(), with changes to the arguments to 'op' and the output
 * opeअक्रमs. */
#घोषणा DEFINE_TESTOP(fn, op, prefix, postfix, eh)	\
अटल अंतरभूत अचिन्हित दीर्घ fn(			\
		अचिन्हित दीर्घ mask,			\
		अस्थिर अचिन्हित दीर्घ *_p)		\
अणु							\
	अचिन्हित दीर्घ old, t;				\
	अचिन्हित दीर्घ *p = (अचिन्हित दीर्घ *)_p;		\
	__यंत्र__ __अस्थिर__ (				\
	prefix						\
"1:"	PPC_LLARX(%0,0,%3,eh) "\n"			\
	stringअगरy_in_c(op) "%1,%0,%2\n"			\
	PPC_STLCX "%1,0,%3\n"				\
	"bne- 1b\n"					\
	postfix						\
	: "=&r" (old), "=&r" (t)			\
	: "r" (mask), "r" (p)				\
	: "cc", "memory");				\
	वापस (old & mask);				\
पूर्ण

DEFINE_TESTOP(test_and_set_bits, or, PPC_ATOMIC_ENTRY_BARRIER,
	      PPC_ATOMIC_EXIT_BARRIER, 0)
DEFINE_TESTOP(test_and_set_bits_lock, or, "",
	      PPC_ACQUIRE_BARRIER, 1)
DEFINE_TESTOP(test_and_clear_bits, andc, PPC_ATOMIC_ENTRY_BARRIER,
	      PPC_ATOMIC_EXIT_BARRIER, 0)
DEFINE_TESTOP(test_and_change_bits, xor, PPC_ATOMIC_ENTRY_BARRIER,
	      PPC_ATOMIC_EXIT_BARRIER, 0)

अटल अंतरभूत पूर्णांक arch_test_and_set_bit(अचिन्हित दीर्घ nr,
					अस्थिर अचिन्हित दीर्घ *addr)
अणु
	वापस test_and_set_bits(BIT_MASK(nr), addr + BIT_WORD(nr)) != 0;
पूर्ण

अटल अंतरभूत पूर्णांक arch_test_and_set_bit_lock(अचिन्हित दीर्घ nr,
					     अस्थिर अचिन्हित दीर्घ *addr)
अणु
	वापस test_and_set_bits_lock(BIT_MASK(nr),
				addr + BIT_WORD(nr)) != 0;
पूर्ण

अटल अंतरभूत पूर्णांक arch_test_and_clear_bit(अचिन्हित दीर्घ nr,
					  अस्थिर अचिन्हित दीर्घ *addr)
अणु
	वापस test_and_clear_bits(BIT_MASK(nr), addr + BIT_WORD(nr)) != 0;
पूर्ण

अटल अंतरभूत पूर्णांक arch_test_and_change_bit(अचिन्हित दीर्घ nr,
					   अस्थिर अचिन्हित दीर्घ *addr)
अणु
	वापस test_and_change_bits(BIT_MASK(nr), addr + BIT_WORD(nr)) != 0;
पूर्ण

#अगर_घोषित CONFIG_PPC64
अटल अंतरभूत अचिन्हित दीर्घ
clear_bit_unlock_वापस_word(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अचिन्हित दीर्घ old, t;
	अचिन्हित दीर्घ *p = (अचिन्हित दीर्घ *)addr + BIT_WORD(nr);
	अचिन्हित दीर्घ mask = BIT_MASK(nr);

	__यंत्र__ __अस्थिर__ (
	PPC_RELEASE_BARRIER
"1:"	PPC_LLARX(%0,0,%3,0) "\n"
	"andc %1,%0,%2\n"
	PPC_STLCX "%1,0,%3\n"
	"bne- 1b\n"
	: "=&r" (old), "=&r" (t)
	: "r" (mask), "r" (p)
	: "cc", "memory");

	वापस old;
पूर्ण

/*
 * This is a special function क्रम mm/filemap.c
 * Bit 7 corresponds to PG_रुकोers.
 */
#घोषणा arch_clear_bit_unlock_is_negative_byte(nr, addr)		\
	(clear_bit_unlock_वापस_word(nr, addr) & BIT_MASK(7))

#पूर्ण_अगर /* CONFIG_PPC64 */

#समावेश <यंत्र-generic/bitops/non-atomic.h>

अटल अंतरभूत व्योम arch___clear_bit_unlock(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	__यंत्र__ __अस्थिर__(PPC_RELEASE_BARRIER "" ::: "memory");
	__clear_bit(nr, addr);
पूर्ण

/*
 * Return the zero-based bit position (LE, not IBM bit numbering) of
 * the most signअगरicant 1-bit in a द्विगुन word.
 */
#घोषणा __ilog2(x)	ilog2(x)

#समावेश <यंत्र-generic/bitops/ffz.h>

#समावेश <यंत्र-generic/bitops/builtin-__ffs.h>

#समावेश <यंत्र-generic/bitops/builtin-ffs.h>

/*
 * fls: find last (most-signअगरicant) bit set.
 * Note fls(0) = 0, fls(1) = 1, fls(0x80000000) = 32.
 */
अटल अंतरभूत पूर्णांक fls(अचिन्हित पूर्णांक x)
अणु
	पूर्णांक lz;

	अगर (__builtin_स्थिरant_p(x))
		वापस x ? 32 - __builtin_clz(x) : 0;
	यंत्र("cntlzw %0,%1" : "=r" (lz) : "r" (x));
	वापस 32 - lz;
पूर्ण

#समावेश <यंत्र-generic/bitops/builtin-__fls.h>

/*
 * 64-bit can करो this using one cntlzd (count leading zeroes द्विगुनword)
 * inकाष्ठाion; क्रम 32-bit we use the generic version, which करोes two
 * 32-bit fls calls.
 */
#अगर_घोषित CONFIG_PPC64
अटल अंतरभूत पूर्णांक fls64(__u64 x)
अणु
	पूर्णांक lz;

	अगर (__builtin_स्थिरant_p(x))
		वापस x ? 64 - __builtin_clzll(x) : 0;
	यंत्र("cntlzd %0,%1" : "=r" (lz) : "r" (x));
	वापस 64 - lz;
पूर्ण
#अन्यथा
#समावेश <यंत्र-generic/bitops/fls64.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC64
अचिन्हित पूर्णांक __arch_hweight8(अचिन्हित पूर्णांक w);
अचिन्हित पूर्णांक __arch_hweight16(अचिन्हित पूर्णांक w);
अचिन्हित पूर्णांक __arch_hweight32(अचिन्हित पूर्णांक w);
अचिन्हित दीर्घ __arch_hweight64(__u64 w);
#समावेश <यंत्र-generic/bitops/स्थिर_hweight.h>
#अन्यथा
#समावेश <यंत्र-generic/bitops/hweight.h>
#पूर्ण_अगर

#समावेश <यंत्र-generic/bitops/find.h>

/* wrappers that deal with KASAN instrumentation */
#समावेश <यंत्र-generic/bitops/instrumented-atomic.h>
#समावेश <यंत्र-generic/bitops/instrumented-lock.h>

/* Little-endian versions */
#समावेश <यंत्र-generic/bitops/le.h>

/* Biपंचांगap functions क्रम the ext2 fileप्रणाली */

#समावेश <यंत्र-generic/bitops/ext2-atomic-setbit.h>

#समावेश <यंत्र-generic/bitops/sched.h>

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* _ASM_POWERPC_BITOPS_H */
