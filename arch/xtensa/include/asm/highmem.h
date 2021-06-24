<शैली गुरु>
/*
 * include/यंत्र-xtensa/highस्मृति.स
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file "COPYING" in the मुख्य directory of
 * this archive क्रम more details.
 *
 * Copyright (C) 2003 - 2005 Tensilica Inc.
 * Copyright (C) 2014 Cadence Design Systems Inc.
 */

#अगर_अघोषित _XTENSA_HIGHMEM_H
#घोषणा _XTENSA_HIGHMEM_H

#अगर_घोषित CONFIG_HIGHMEM
#समावेश <linux/रुको.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/fixmap.h>

#घोषणा PKMAP_BASE		((FIXADDR_START -			\
				  (LAST_PKMAP + 1) * PAGE_SIZE) & PMD_MASK)
#घोषणा LAST_PKMAP		(PTRS_PER_PTE * DCACHE_N_COLORS)
#घोषणा LAST_PKMAP_MASK		(LAST_PKMAP - 1)
#घोषणा PKMAP_NR(virt)		(((virt) - PKMAP_BASE) >> PAGE_SHIFT)
#घोषणा PKMAP_ADDR(nr)		(PKMAP_BASE + ((nr) << PAGE_SHIFT))

#घोषणा kmap_prot		PAGE_KERNEL_EXEC

#अगर DCACHE_WAY_SIZE > PAGE_SIZE
#घोषणा get_pkmap_color get_pkmap_color
अटल अंतरभूत पूर्णांक get_pkmap_color(काष्ठा page *page)
अणु
	वापस DCACHE_ALIAS(page_to_phys(page));
पूर्ण

बाह्य अचिन्हित पूर्णांक last_pkmap_nr_arr[];

अटल अंतरभूत अचिन्हित पूर्णांक get_next_pkmap_nr(अचिन्हित पूर्णांक color)
अणु
	last_pkmap_nr_arr[color] =
		(last_pkmap_nr_arr[color] + DCACHE_N_COLORS) & LAST_PKMAP_MASK;
	वापस last_pkmap_nr_arr[color] + color;
पूर्ण

अटल अंतरभूत पूर्णांक no_more_pkmaps(अचिन्हित पूर्णांक pkmap_nr, अचिन्हित पूर्णांक color)
अणु
	वापस pkmap_nr < DCACHE_N_COLORS;
पूर्ण

अटल अंतरभूत पूर्णांक get_pkmap_entries_count(अचिन्हित पूर्णांक color)
अणु
	वापस LAST_PKMAP / DCACHE_N_COLORS;
पूर्ण

बाह्य रुको_queue_head_t pkmap_map_रुको_arr[];

अटल अंतरभूत रुको_queue_head_t *get_pkmap_रुको_queue_head(अचिन्हित पूर्णांक color)
अणु
	वापस pkmap_map_रुको_arr + color;
पूर्ण

क्रमागत fixed_addresses kmap_local_map_idx(पूर्णांक type, अचिन्हित दीर्घ pfn);
#घोषणा arch_kmap_local_map_idx		kmap_local_map_idx

क्रमागत fixed_addresses kmap_local_unmap_idx(पूर्णांक type, अचिन्हित दीर्घ addr);
#घोषणा arch_kmap_local_unmap_idx	kmap_local_unmap_idx

#पूर्ण_अगर

बाह्य pte_t *pkmap_page_table;

अटल अंतरभूत व्योम flush_cache_kmaps(व्योम)
अणु
	flush_cache_all();
पूर्ण

#घोषणा arch_kmap_local_post_unmap(vaddr)	\
	local_flush_tlb_kernel_range(vaddr, vaddr + PAGE_SIZE)

व्योम kmap_init(व्योम);

#पूर्ण_अगर /* CONFIG_HIGHMEM */
#पूर्ण_अगर
