<शैली गुरु>
/*
 * High memory support क्रम Xtensa architecture
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file "COPYING" in the मुख्य directory of
 * this archive क्रम more details.
 *
 * Copyright (C) 2014 Cadence Design Systems Inc.
 */

#समावेश <linux/export.h>
#समावेश <linux/highस्मृति.स>
#समावेश <यंत्र/tlbflush.h>

#अगर DCACHE_WAY_SIZE > PAGE_SIZE
अचिन्हित पूर्णांक last_pkmap_nr_arr[DCACHE_N_COLORS];
रुको_queue_head_t pkmap_map_रुको_arr[DCACHE_N_COLORS];

अटल व्योम __init kmap_रुकोqueues_init(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pkmap_map_रुको_arr); ++i)
		init_रुकोqueue_head(pkmap_map_रुको_arr + i);
पूर्ण

अटल अंतरभूत क्रमागत fixed_addresses kmap_idx(पूर्णांक type, अचिन्हित दीर्घ color)
अणु
	पूर्णांक idx = (type + KM_MAX_IDX * smp_processor_id()) * DCACHE_N_COLORS;

	/*
	 * The fixmap operates top करोwn, so the color offset needs to be
	 * reverse as well.
	 */
	वापस idx + DCACHE_N_COLORS - 1 - color;
पूर्ण

क्रमागत fixed_addresses kmap_local_map_idx(पूर्णांक type, अचिन्हित दीर्घ pfn)
अणु
	वापस kmap_idx(type, DCACHE_ALIAS(pfn << PAGE_SHIFT));
पूर्ण

क्रमागत fixed_addresses kmap_local_unmap_idx(पूर्णांक type, अचिन्हित दीर्घ addr)
अणु
	वापस kmap_idx(type, DCACHE_ALIAS(addr));
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम kmap_रुकोqueues_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

व्योम __init kmap_init(व्योम)
अणु
	/* Check अगर this memory layout is broken because PKMAP overlaps
	 * page table.
	 */
	BUILD_BUG_ON(PKMAP_BASE < TLBTEMP_BASE_1 + TLBTEMP_SIZE);
	kmap_रुकोqueues_init();
पूर्ण
