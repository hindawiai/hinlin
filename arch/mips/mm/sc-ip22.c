<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sc-ip22.c: Indy cache management functions.
 *
 * Copyright (C) 1997, 2001 Ralf Baechle (ralf@gnu.org),
 * derived from r4xx0.c by David S. Miller (davem@davemloft.net).
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/bcache.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/sgi/ip22.h>
#समावेश <यंत्र/sgi/mc.h>

/* Secondary cache size in bytes, अगर present.  */
अटल अचिन्हित दीर्घ scache_size;

#अघोषित DEBUG_CACHE

#घोषणा SC_SIZE 0x00080000
#घोषणा SC_LINE 32
#घोषणा CI_MASK (SC_SIZE - SC_LINE)
#घोषणा SC_INDEX(n) ((n) & CI_MASK)

अटल अंतरभूत व्योम indy_sc_wipe(अचिन्हित दीर्घ first, अचिन्हित दीर्घ last)
अणु
	अचिन्हित दीर्घ पंचांगp;

	__यंत्र__ __अस्थिर__(
	"	.set	push			# indy_sc_wipe		\n"
	"	.set	noreorder					\n"
	"	.set	mips3						\n"
	"	.set	noat						\n"
	"	mfc0	%2, $12						\n"
	"	li	$1, 0x80		# Go 64 bit		\n"
	"	mtc0	$1, $12						\n"
	"								\n"
	"	#							\n"
	"	# Open code a dli $1, 0x9000000080000000		\n"
	"	#							\n"
	"	# Required because binutils 2.25 will happily accept	\n"
	"	# 64 bit instructions in .set mips3 mode but puke on	\n"
	"	# 64 bit constants when generating 32 bit ELF		\n"
	"	#							\n"
	"	lui	$1,0x9000					\n"
	"	dsll	$1,$1,0x10					\n"
	"	ori	$1,$1,0x8000					\n"
	"	dsll	$1,$1,0x10					\n"
	"								\n"
	"	or	%0, $1			# first line to flush	\n"
	"	or	%1, $1			# last line to flush	\n"
	"	.set	at						\n"
	"								\n"
	"1:	sw	$0, 0(%0)					\n"
	"	bne	%0, %1, 1b					\n"
	"	 daddu	%0, 32						\n"
	"								\n"
	"	mtc0	%2, $12			# Back to 32 bit	\n"
	"	nop				# pipeline hazard	\n"
	"	nop							\n"
	"	nop							\n"
	"	nop							\n"
	"	.set	pop						\n"
	: "=r" (first), "=r" (last), "=&r" (पंचांगp)
	: "0" (first), "1" (last));
पूर्ण

अटल व्योम indy_sc_wback_invalidate(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ first_line, last_line;
	अचिन्हित दीर्घ flags;

#अगर_घोषित DEBUG_CACHE
	prपूर्णांकk("indy_sc_wback_invalidate[%08lx,%08lx]", addr, size);
#पूर्ण_अगर

	/* Catch bad driver code */
	BUG_ON(size == 0);

	/* Which lines to flush?  */
	first_line = SC_INDEX(addr);
	last_line = SC_INDEX(addr + size - 1);

	local_irq_save(flags);
	अगर (first_line <= last_line) अणु
		indy_sc_wipe(first_line, last_line);
		जाओ out;
	पूर्ण

	indy_sc_wipe(first_line, SC_SIZE - SC_LINE);
	indy_sc_wipe(0, last_line);
out:
	local_irq_restore(flags);
पूर्ण

अटल व्योम indy_sc_enable(व्योम)
अणु
	अचिन्हित दीर्घ addr, पंचांगp1, पंचांगp2;

	/* This is really cool... */
#अगर_घोषित DEBUG_CACHE
	prपूर्णांकk("Enabling R4600 SCACHE\n");
#पूर्ण_अगर
	__यंत्र__ __अस्थिर__(
	".set\tpush\n\t"
	".set\tnoreorder\n\t"
	".set\tmips3\n\t"
	"mfc0\t%2, $12\n\t"
	"nop; nop; nop; nop;\n\t"
	"li\t%1, 0x80\n\t"
	"mtc0\t%1, $12\n\t"
	"nop; nop; nop; nop;\n\t"
	"li\t%0, 0x1\n\t"
	"dsll\t%0, 31\n\t"
	"lui\t%1, 0x9000\n\t"
	"dsll32\t%1, 0\n\t"
	"or\t%0, %1, %0\n\t"
	"sb\t$0, 0(%0)\n\t"
	"mtc0\t$0, $12\n\t"
	"nop; nop; nop; nop;\n\t"
	"mtc0\t%2, $12\n\t"
	"nop; nop; nop; nop;\n\t"
	".set\tpop"
	: "=r" (पंचांगp1), "=r" (पंचांगp2), "=r" (addr));
पूर्ण

अटल व्योम indy_sc_disable(व्योम)
अणु
	अचिन्हित दीर्घ पंचांगp1, पंचांगp2, पंचांगp3;

#अगर_घोषित DEBUG_CACHE
	prपूर्णांकk("Disabling R4600 SCACHE\n");
#पूर्ण_अगर
	__यंत्र__ __अस्थिर__(
	".set\tpush\n\t"
	".set\tnoreorder\n\t"
	".set\tmips3\n\t"
	"li\t%0, 0x1\n\t"
	"dsll\t%0, 31\n\t"
	"lui\t%1, 0x9000\n\t"
	"dsll32\t%1, 0\n\t"
	"or\t%0, %1, %0\n\t"
	"mfc0\t%2, $12\n\t"
	"nop; nop; nop; nop\n\t"
	"li\t%1, 0x80\n\t"
	"mtc0\t%1, $12\n\t"
	"nop; nop; nop; nop\n\t"
	"sh\t$0, 0(%0)\n\t"
	"mtc0\t$0, $12\n\t"
	"nop; nop; nop; nop\n\t"
	"mtc0\t%2, $12\n\t"
	"nop; nop; nop; nop\n\t"
	".set\tpop"
	: "=r" (पंचांगp1), "=r" (पंचांगp2), "=r" (पंचांगp3));
पूर्ण

अटल अंतरभूत पूर्णांक __init indy_sc_probe(व्योम)
अणु
	अचिन्हित पूर्णांक size = ip22_eeprom_पढ़ो(&sgimc->eeprom, 17);
	अगर (size == 0)
		वापस 0;

	size <<= PAGE_SHIFT;
	prपूर्णांकk(KERN_INFO "R4600/R5000 SCACHE size %dK, linesize 32 bytes.\n",
	       size >> 10);
	scache_size = size;

	वापस 1;
पूर्ण

/* XXX Check with wje अगर the Indy caches can dअगरferentiate between
   ग_लिखोback + invalidate and just invalidate.	*/
अटल काष्ठा bcache_ops indy_sc_ops = अणु
	.bc_enable = indy_sc_enable,
	.bc_disable = indy_sc_disable,
	.bc_wback_inv = indy_sc_wback_invalidate,
	.bc_inv = indy_sc_wback_invalidate
पूर्ण;

व्योम indy_sc_init(व्योम)
अणु
	अगर (indy_sc_probe()) अणु
		indy_sc_enable();
		bcops = &indy_sc_ops;
	पूर्ण
पूर्ण
