<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * This file contains the routines क्रम initializing the MMU
 * on the 4xx series of chips.
 *  -- paulus
 *
 *  Derived from arch/ppc/mm/init.c:
 *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)
 *
 *  Modअगरications by Paul Mackerras (PowerMac) (paulus@cs.anu.edu.au)
 *  and Cort Dougan (PReP) (cort@cs.nmt.edu)
 *    Copyright (C) 1996 Paul Mackerras
 *
 *  Derived from "arch/i386/mm/init.c"
 *    Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds
 */

#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/mman.h>
#समावेश <linux/mm.h>
#समावेश <linux/swap.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/mmu.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/bootx.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/setup.h>

#समावेश <mm/mmu_decl.h>

बाह्य पूर्णांक __map_without_ltlbs;
/*
 * MMU_init_hw करोes the chip-specअगरic initialization of the MMU hardware.
 */
व्योम __init MMU_init_hw(व्योम)
अणु
	/*
	 * The Zone Protection Register (ZPR) defines how protection will
	 * be applied to every page which is a member of a given zone. At
	 * present, we utilize only two of the 4xx's zones.
	 * The zone index bits (of ZSEL) in the PTE are used क्रम software
	 * indicators, except the LSB.  For user access, zone 1 is used,
	 * क्रम kernel access, zone 0 is used.  We set all but zone 1
	 * to zero, allowing only kernel access as indicated in the PTE.
	 * For zone 1, we set a 01 binary (a value of 10 will not work)
	 * to allow user access as indicated in the PTE.  This also allows
	 * kernel access as indicated in the PTE.
	 */

        mtspr(SPRN_ZPR, 0x10000000);

	flush_inकाष्ठाion_cache();

	/*
	 * Set up the real-mode cache parameters क्रम the exception vector
	 * handlers (which are run in real-mode).
	 */

        mtspr(SPRN_DCWR, 0x00000000);	/* All caching is ग_लिखो-back */

        /*
	 * Cache inकाष्ठाion and data space where the exception
	 * vectors and the kernel live in real-mode.
	 */

        mtspr(SPRN_DCCR, 0xFFFF0000);	/* 2GByte of data space at 0x0. */
        mtspr(SPRN_ICCR, 0xFFFF0000);	/* 2GByte of instr. space at 0x0. */
पूर्ण

#घोषणा LARGE_PAGE_SIZE_16M	(1<<24)
#घोषणा LARGE_PAGE_SIZE_4M	(1<<22)

अचिन्हित दीर्घ __init mmu_mapin_ram(अचिन्हित दीर्घ base, अचिन्हित दीर्घ top)
अणु
	अचिन्हित दीर्घ v, s, mapped;
	phys_addr_t p;

	v = KERNELBASE;
	p = 0;
	s = total_lowmem;

	अगर (__map_without_ltlbs)
		वापस 0;

	जबतक (s >= LARGE_PAGE_SIZE_16M) अणु
		pmd_t *pmdp;
		अचिन्हित दीर्घ val = p | _PMD_SIZE_16M | _PAGE_EXEC | _PAGE_RW;

		pmdp = pmd_off_k(v);
		*pmdp++ = __pmd(val);
		*pmdp++ = __pmd(val);
		*pmdp++ = __pmd(val);
		*pmdp++ = __pmd(val);

		v += LARGE_PAGE_SIZE_16M;
		p += LARGE_PAGE_SIZE_16M;
		s -= LARGE_PAGE_SIZE_16M;
	पूर्ण

	जबतक (s >= LARGE_PAGE_SIZE_4M) अणु
		pmd_t *pmdp;
		अचिन्हित दीर्घ val = p | _PMD_SIZE_4M | _PAGE_EXEC | _PAGE_RW;

		pmdp = pmd_off_k(v);
		*pmdp = __pmd(val);

		v += LARGE_PAGE_SIZE_4M;
		p += LARGE_PAGE_SIZE_4M;
		s -= LARGE_PAGE_SIZE_4M;
	पूर्ण

	mapped = total_lowmem - s;

	/* If the size of RAM is not an exact घातer of two, we may not
	 * have covered RAM in its entirety with 16 and 4 MiB
	 * pages. Consequently, restrict the top end of RAM currently
	 * allocable so that calls to the MEMBLOCK to allocate PTEs क्रम "tail"
	 * coverage with normal-sized pages (or other reasons) करो not
	 * attempt to allocate outside the allowed range.
	 */
	memblock_set_current_limit(mapped);

	वापस mapped;
पूर्ण

व्योम setup_initial_memory_limit(phys_addr_t first_memblock_base,
				phys_addr_t first_memblock_size)
अणु
	/* We करोn't currently support the first MEMBLOCK not mapping 0
	 * physical on those processors
	 */
	BUG_ON(first_memblock_base != 0);

	/* 40x can only access 16MB at the moment (see head_40x.S) */
	memblock_set_current_limit(min_t(u64, first_memblock_size, 0x00800000));
पूर्ण
