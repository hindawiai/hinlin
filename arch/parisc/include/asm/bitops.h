<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PARISC_BITOPS_H
#घोषणा _PARISC_BITOPS_H

#अगर_अघोषित _LINUX_BITOPS_H
#त्रुटि only <linux/bitops.h> can be included directly
#पूर्ण_अगर

#समावेश <linux/compiler.h>
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/barrier.h>
#समावेश <linux/atomic.h>

/* See http://marc.theaimsgroup.com/?t=108826637900003 क्रम discussion
 * on use of अस्थिर and __*_bit() (set/clear/change):
 *	*_bit() want use of अस्थिर.
 *	__*_bit() are "relaxed" and करोn't use spinlock or अस्थिर.
 */

अटल __अंतरभूत__ व्योम set_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ * addr)
अणु
	अचिन्हित दीर्घ mask = BIT_MASK(nr);
	अचिन्हित दीर्घ flags;

	addr += BIT_WORD(nr);
	_atomic_spin_lock_irqsave(addr, flags);
	*addr |= mask;
	_atomic_spin_unlock_irqrestore(addr, flags);
पूर्ण

अटल __अंतरभूत__ व्योम clear_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ * addr)
अणु
	अचिन्हित दीर्घ mask = BIT_MASK(nr);
	अचिन्हित दीर्घ flags;

	addr += BIT_WORD(nr);
	_atomic_spin_lock_irqsave(addr, flags);
	*addr &= ~mask;
	_atomic_spin_unlock_irqrestore(addr, flags);
पूर्ण

अटल __अंतरभूत__ व्योम change_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ * addr)
अणु
	अचिन्हित दीर्घ mask = BIT_MASK(nr);
	अचिन्हित दीर्घ flags;

	addr += BIT_WORD(nr);
	_atomic_spin_lock_irqsave(addr, flags);
	*addr ^= mask;
	_atomic_spin_unlock_irqrestore(addr, flags);
पूर्ण

अटल __अंतरभूत__ पूर्णांक test_and_set_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ * addr)
अणु
	अचिन्हित दीर्घ mask = BIT_MASK(nr);
	अचिन्हित दीर्घ old;
	अचिन्हित दीर्घ flags;
	पूर्णांक set;

	addr += BIT_WORD(nr);
	_atomic_spin_lock_irqsave(addr, flags);
	old = *addr;
	set = (old & mask) ? 1 : 0;
	अगर (!set)
		*addr = old | mask;
	_atomic_spin_unlock_irqrestore(addr, flags);

	वापस set;
पूर्ण

अटल __अंतरभूत__ पूर्णांक test_and_clear_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ * addr)
अणु
	अचिन्हित दीर्घ mask = BIT_MASK(nr);
	अचिन्हित दीर्घ old;
	अचिन्हित दीर्घ flags;
	पूर्णांक set;

	addr += BIT_WORD(nr);
	_atomic_spin_lock_irqsave(addr, flags);
	old = *addr;
	set = (old & mask) ? 1 : 0;
	अगर (set)
		*addr = old & ~mask;
	_atomic_spin_unlock_irqrestore(addr, flags);

	वापस set;
पूर्ण

अटल __अंतरभूत__ पूर्णांक test_and_change_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ * addr)
अणु
	अचिन्हित दीर्घ mask = BIT_MASK(nr);
	अचिन्हित दीर्घ oldbit;
	अचिन्हित दीर्घ flags;

	addr += BIT_WORD(nr);
	_atomic_spin_lock_irqsave(addr, flags);
	oldbit = *addr;
	*addr = oldbit ^ mask;
	_atomic_spin_unlock_irqrestore(addr, flags);

	वापस (oldbit & mask) ? 1 : 0;
पूर्ण

#समावेश <यंत्र-generic/bitops/non-atomic.h>

#अगर_घोषित __KERNEL__

/**
 * __ffs - find first bit in word. वापसs 0 to "BITS_PER_LONG-1".
 * @word: The word to search
 *
 * __ffs() वापस is undefined अगर no bit is set.
 *
 * 32-bit fast __ffs by LaMont Jones "lamont At hp com".
 * 64-bit enhancement by Grant Grundler "grundler At parisc-linux org".
 * (with help from willy/jejb to get the semantics right)
 *
 * This algorithm aव्योमs branches by making use of nullअगरication.
 * One side effect of "extr" inकाष्ठाions is it sets PSW[N] bit.
 * How PSW[N] (nullअगरy next insn) माला_लो set is determined by the 
 * "condition" field (eg "<>" or "TR" below) in the extr* insn.
 * Only the 1st and one of either the 2cd or 3rd insn will get executed.
 * Each set of 3 insn will get executed in 2 cycles on PA8x00 vs 16 or so
 * cycles क्रम each mispredicted branch.
 */

अटल __अंतरभूत__ अचिन्हित दीर्घ __ffs(अचिन्हित दीर्घ x)
अणु
	अचिन्हित दीर्घ ret;

	__यंत्र__(
#अगर_घोषित CONFIG_64BIT
		" ldi       63,%1\n"
		" extrd,u,*<>  %0,63,32,%%r0\n"
		" extrd,u,*TR  %0,31,32,%0\n"	/* move top 32-bits करोwn */
		" addi    -32,%1,%1\n"
#अन्यथा
		" ldi       31,%1\n"
#पूर्ण_अगर
		" extru,<>  %0,31,16,%%r0\n"
		" extru,TR  %0,15,16,%0\n"	/* xxxx0000 -> 0000xxxx */
		" addi    -16,%1,%1\n"
		" extru,<>  %0,31,8,%%r0\n"
		" extru,TR  %0,23,8,%0\n"	/* 0000xx00 -> 000000xx */
		" addi    -8,%1,%1\n"
		" extru,<>  %0,31,4,%%r0\n"
		" extru,TR  %0,27,4,%0\n"	/* 000000x0 -> 0000000x */
		" addi    -4,%1,%1\n"
		" extru,<>  %0,31,2,%%r0\n"
		" extru,TR  %0,29,2,%0\n"	/* 0000000y, 1100b -> 0011b */
		" addi    -2,%1,%1\n"
		" extru,=  %0,31,1,%%r0\n"	/* check last bit */
		" addi    -1,%1,%1\n"
			: "+r" (x), "=r" (ret) );
	वापस ret;
पूर्ण

#समावेश <यंत्र-generic/bitops/ffz.h>

/*
 * ffs: find first bit set. वापसs 1 to BITS_PER_LONG or 0 (अगर none set)
 * This is defined the same way as the libc and compiler builtin
 * ffs routines, thereक्रमe dअगरfers in spirit from the above ffz (man ffs).
 */
अटल __अंतरभूत__ पूर्णांक ffs(पूर्णांक x)
अणु
	वापस x ? (__ffs((अचिन्हित दीर्घ)x) + 1) : 0;
पूर्ण

/*
 * fls: find last (most signअगरicant) bit set.
 * fls(0) = 0, fls(1) = 1, fls(0x80000000) = 32.
 */

अटल __अंतरभूत__ पूर्णांक fls(अचिन्हित पूर्णांक x)
अणु
	पूर्णांक ret;
	अगर (!x)
		वापस 0;

	__यंत्र__(
	"	ldi		1,%1\n"
	"	extru,<>	%0,15,16,%%r0\n"
	"	zdep,TR		%0,15,16,%0\n"		/* xxxx0000 */
	"	addi		16,%1,%1\n"
	"	extru,<>	%0,7,8,%%r0\n"
	"	zdep,TR		%0,23,24,%0\n"		/* xx000000 */
	"	addi		8,%1,%1\n"
	"	extru,<>	%0,3,4,%%r0\n"
	"	zdep,TR		%0,27,28,%0\n"		/* x0000000 */
	"	addi		4,%1,%1\n"
	"	extru,<>	%0,1,2,%%r0\n"
	"	zdep,TR		%0,29,30,%0\n"		/* y0000000 (y&3 = 0) */
	"	addi		2,%1,%1\n"
	"	extru,=		%0,0,1,%%r0\n"
	"	addi		1,%1,%1\n"		/* अगर y & 8, add 1 */
		: "+r" (x), "=r" (ret) );

	वापस ret;
पूर्ण

#समावेश <यंत्र-generic/bitops/__fls.h>
#समावेश <यंत्र-generic/bitops/fls64.h>
#समावेश <यंत्र-generic/bitops/hweight.h>
#समावेश <यंत्र-generic/bitops/lock.h>
#समावेश <यंत्र-generic/bitops/sched.h>

#पूर्ण_अगर /* __KERNEL__ */

#समावेश <यंत्र-generic/bitops/find.h>

#अगर_घोषित __KERNEL__

#समावेश <यंत्र-generic/bitops/le.h>
#समावेश <यंत्र-generic/bitops/ext2-atomic-setbit.h>

#पूर्ण_अगर	/* __KERNEL__ */

#पूर्ण_अगर /* _PARISC_BITOPS_H */
