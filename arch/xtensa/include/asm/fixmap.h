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

#अगर_घोषित CONFIG_HIGHMEM
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/kmap_size.h>

/* The map slots क्रम temporary mappings via kmap_atomic/local(). */
क्रमागत fixed_addresses अणु
	FIX_KMAP_BEGIN,
	FIX_KMAP_END = FIX_KMAP_BEGIN +
		(KM_MAX_IDX * NR_CPUS * DCACHE_N_COLORS) - 1,
	__end_of_fixed_addresses
पूर्ण;

#घोषणा FIXADDR_END     (XCHAL_KSEG_CACHED_VADDR - PAGE_SIZE)
#घोषणा FIXADDR_SIZE	(__end_of_fixed_addresses << PAGE_SHIFT)
/* Enक्रमce that FIXADDR_START is PMD aligned to handle cache aliasing */
#घोषणा FIXADDR_START	((FIXADDR_END - FIXADDR_SIZE) & PMD_MASK)
#घोषणा FIXADDR_TOP	(FIXADDR_START + FIXADDR_SIZE - PAGE_SIZE)

#समावेश <यंत्र-generic/fixmap.h>

#पूर्ण_अगर /* CONFIG_HIGHMEM */
#पूर्ण_अगर
