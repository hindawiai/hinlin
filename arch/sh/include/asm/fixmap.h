<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * fixmap.h: compile-समय भव memory allocation
 *
 * Copyright (C) 1998 Ingo Molnar
 *
 * Support of BIGMEM added by Gerhard Wichert, Siemens AG, July 1999
 */

#अगर_अघोषित _ASM_FIXMAP_H
#घोषणा _ASM_FIXMAP_H

#समावेश <linux/kernel.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <यंत्र/page.h>

/*
 * Here we define all the compile-समय 'special' भव
 * addresses. The poपूर्णांक is to have a स्थिरant address at
 * compile समय, but to set the physical address only
 * in the boot process. We allocate these special  addresses
 * from the end of P3 backwards.
 * Also this lets us करो fail-safe vदो_स्मृति(), we
 * can guarantee that these special addresses and
 * vदो_स्मृति()-ed addresses never overlap.
 *
 * these 'compile-time allocated' memory buffers are
 * fixed-size 4k pages. (or larger अगर used with an increment
 * highger than 1) use fixmap_set(idx,phys) to associate
 * physical memory with fixmap indices.
 *
 * TLB entries of such buffers will not be flushed across
 * task चयनes.
 */

/*
 * on UP currently we will have no trace of the fixmap mechanizm,
 * no page table allocations, etc. This might change in the
 * future, say framebuffers क्रम the console driver(s) could be
 * fix-mapped?
 */
क्रमागत fixed_addresses अणु
	/*
	 * The FIX_CMAP entries are used by kmap_coherent() to get भव
	 * addresses which are of a known color, and so their values are
	 * important. __fix_to_virt(FIX_CMAP_END - n) must give an address
	 * which is the same color as a page (n<<PAGE_SHIFT).
	 */
#घोषणा FIX_N_COLOURS 8
	FIX_CMAP_BEGIN,
	FIX_CMAP_END = FIX_CMAP_BEGIN + (FIX_N_COLOURS * NR_CPUS) - 1,

#अगर_घोषित CONFIG_IOREMAP_FIXED
	/*
	 * FIX_IOREMAP entries are useful क्रम mapping physical address
	 * space beक्रमe ioremap() is useable, e.g. really early in boot
	 * beक्रमe kदो_स्मृति() is working.
	 */
#घोषणा FIX_N_IOREMAPS	32
	FIX_IOREMAP_BEGIN,
	FIX_IOREMAP_END = FIX_IOREMAP_BEGIN + FIX_N_IOREMAPS - 1,
#पूर्ण_अगर

	__end_of_fixed_addresses
पूर्ण;

बाह्य व्योम __set_fixmap(क्रमागत fixed_addresses idx,
			 अचिन्हित दीर्घ phys, pgprot_t flags);
बाह्य व्योम __clear_fixmap(क्रमागत fixed_addresses idx, pgprot_t flags);

/*
 * used by vदो_स्मृति.c.
 *
 * Leave one empty page between vदो_स्मृति'ed areas and
 * the start of the fixmap, and leave one page empty
 * at the top of mem..
 */
#घोषणा FIXADDR_TOP	(P4SEG - PAGE_SIZE)
#घोषणा FIXADDR_SIZE	(__end_of_fixed_addresses << PAGE_SHIFT)
#घोषणा FIXADDR_START	(FIXADDR_TOP - FIXADDR_SIZE)

#घोषणा FIXMAP_PAGE_NOCACHE PAGE_KERNEL_NOCACHE

#समावेश <यंत्र-generic/fixmap.h>

#पूर्ण_अगर
