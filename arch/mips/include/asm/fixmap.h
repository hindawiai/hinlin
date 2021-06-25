<शैली गुरु>
/*
 * fixmap.h: compile-समय भव memory allocation
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1998 Ingo Molnar
 *
 * Support of BIGMEM added by Gerhard Wichert, Siemens AG, July 1999
 */

#अगर_अघोषित _ASM_FIXMAP_H
#घोषणा _ASM_FIXMAP_H

#समावेश <यंत्र/page.h>
#समावेश <spaces.h>
#अगर_घोषित CONFIG_HIGHMEM
#समावेश <linux/thपढ़ोs.h>
#समावेश <यंत्र/kmap_size.h>
#पूर्ण_अगर

/*
 * Here we define all the compile-समय 'special' भव
 * addresses. The poपूर्णांक is to have a स्थिरant address at
 * compile समय, but to set the physical address only
 * in the boot process. We allocate these special  addresses
 * from the end of भव memory (0xfffff000) backwards.
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
#घोषणा FIX_N_COLOURS 8
	FIX_CMAP_BEGIN,
	FIX_CMAP_END = FIX_CMAP_BEGIN + (FIX_N_COLOURS * 2),
#अगर_घोषित CONFIG_HIGHMEM
	/* reserved pte's क्रम temporary kernel mappings */
	FIX_KMAP_BEGIN = FIX_CMAP_END + 1,
	FIX_KMAP_END = FIX_KMAP_BEGIN + (KM_MAX_IDX * NR_CPUS) - 1,
#पूर्ण_अगर
	__end_of_fixed_addresses
पूर्ण;

/*
 * used by vदो_स्मृति.c.
 *
 * Leave one empty page between vदो_स्मृति'ed areas and
 * the start of the fixmap, and leave one page empty
 * at the top of mem..
 */
#घोषणा FIXADDR_SIZE	(__end_of_fixed_addresses << PAGE_SHIFT)
#घोषणा FIXADDR_START	(FIXADDR_TOP - FIXADDR_SIZE)

#समावेश <यंत्र-generic/fixmap.h>

/*
 * Called from pgtable_init()
 */
बाह्य व्योम fixrange_init(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
	pgd_t *pgd_base);


#पूर्ण_अगर
