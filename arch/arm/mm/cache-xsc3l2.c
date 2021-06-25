<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/mm/cache-xsc3l2.c - XScale3 L2 cache controller support
 *
 * Copyright (C) 2007 ARM Limited
 */
#समावेश <linux/init.h>
#समावेश <linux/highस्मृति.स>
#समावेश <यंत्र/cp15.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/cacheflush.h>

#घोषणा CR_L2	(1 << 26)

#घोषणा CACHE_LINE_SIZE		32
#घोषणा CACHE_LINE_SHIFT	5
#घोषणा CACHE_WAY_PER_SET	8

#घोषणा CACHE_WAY_SIZE(l2ctype)	(8192 << (((l2ctype) >> 8) & 0xf))
#घोषणा CACHE_SET_SIZE(l2ctype)	(CACHE_WAY_SIZE(l2ctype) >> CACHE_LINE_SHIFT)

अटल अंतरभूत पूर्णांक xsc3_l2_present(व्योम)
अणु
	अचिन्हित दीर्घ l2ctype;

	__यंत्र__("mrc p15, 1, %0, c0, c0, 1" : "=r" (l2ctype));

	वापस !!(l2ctype & 0xf8);
पूर्ण

अटल अंतरभूत व्योम xsc3_l2_clean_mva(अचिन्हित दीर्घ addr)
अणु
	__यंत्र__("mcr p15, 1, %0, c7, c11, 1" : : "r" (addr));
पूर्ण

अटल अंतरभूत व्योम xsc3_l2_inv_mva(अचिन्हित दीर्घ addr)
अणु
	__यंत्र__("mcr p15, 1, %0, c7, c7, 1" : : "r" (addr));
पूर्ण

अटल अंतरभूत व्योम xsc3_l2_inv_all(व्योम)
अणु
	अचिन्हित दीर्घ l2ctype, set_way;
	पूर्णांक set, way;

	__यंत्र__("mrc p15, 1, %0, c0, c0, 1" : "=r" (l2ctype));

	क्रम (set = 0; set < CACHE_SET_SIZE(l2ctype); set++) अणु
		क्रम (way = 0; way < CACHE_WAY_PER_SET; way++) अणु
			set_way = (way << 29) | (set << 5);
			__यंत्र__("mcr p15, 1, %0, c7, c11, 2" : : "r"(set_way));
		पूर्ण
	पूर्ण

	dsb();
पूर्ण

अटल अंतरभूत व्योम l2_unmap_va(अचिन्हित दीर्घ va)
अणु
#अगर_घोषित CONFIG_HIGHMEM
	अगर (va != -1)
		kunmap_atomic((व्योम *)va);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ l2_map_va(अचिन्हित दीर्घ pa, अचिन्हित दीर्घ prev_va)
अणु
#अगर_घोषित CONFIG_HIGHMEM
	अचिन्हित दीर्घ va = prev_va & PAGE_MASK;
	अचिन्हित दीर्घ pa_offset = pa << (32 - PAGE_SHIFT);
	अगर (unlikely(pa_offset < (prev_va << (32 - PAGE_SHIFT)))) अणु
		/*
		 * Switching to a new page.  Because cache ops are
		 * using भव addresses only, we must put a mapping
		 * in place क्रम it.
		 */
		l2_unmap_va(prev_va);
		va = (अचिन्हित दीर्घ)kmap_atomic_pfn(pa >> PAGE_SHIFT);
	पूर्ण
	वापस va + (pa_offset >> (32 - PAGE_SHIFT));
#अन्यथा
	वापस __phys_to_virt(pa);
#पूर्ण_अगर
पूर्ण

अटल व्योम xsc3_l2_inv_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ vaddr;

	अगर (start == 0 && end == -1ul) अणु
		xsc3_l2_inv_all();
		वापस;
	पूर्ण

	vaddr = -1;  /* to क्रमce the first mapping */

	/*
	 * Clean and invalidate partial first cache line.
	 */
	अगर (start & (CACHE_LINE_SIZE - 1)) अणु
		vaddr = l2_map_va(start & ~(CACHE_LINE_SIZE - 1), vaddr);
		xsc3_l2_clean_mva(vaddr);
		xsc3_l2_inv_mva(vaddr);
		start = (start | (CACHE_LINE_SIZE - 1)) + 1;
	पूर्ण

	/*
	 * Invalidate all full cache lines between 'start' and 'end'.
	 */
	जबतक (start < (end & ~(CACHE_LINE_SIZE - 1))) अणु
		vaddr = l2_map_va(start, vaddr);
		xsc3_l2_inv_mva(vaddr);
		start += CACHE_LINE_SIZE;
	पूर्ण

	/*
	 * Clean and invalidate partial last cache line.
	 */
	अगर (start < end) अणु
		vaddr = l2_map_va(start, vaddr);
		xsc3_l2_clean_mva(vaddr);
		xsc3_l2_inv_mva(vaddr);
	पूर्ण

	l2_unmap_va(vaddr);

	dsb();
पूर्ण

अटल व्योम xsc3_l2_clean_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ vaddr;

	vaddr = -1;  /* to क्रमce the first mapping */

	start &= ~(CACHE_LINE_SIZE - 1);
	जबतक (start < end) अणु
		vaddr = l2_map_va(start, vaddr);
		xsc3_l2_clean_mva(vaddr);
		start += CACHE_LINE_SIZE;
	पूर्ण

	l2_unmap_va(vaddr);

	dsb();
पूर्ण

/*
 * optimize L2 flush all operation by set/way क्रमmat
 */
अटल अंतरभूत व्योम xsc3_l2_flush_all(व्योम)
अणु
	अचिन्हित दीर्घ l2ctype, set_way;
	पूर्णांक set, way;

	__यंत्र__("mrc p15, 1, %0, c0, c0, 1" : "=r" (l2ctype));

	क्रम (set = 0; set < CACHE_SET_SIZE(l2ctype); set++) अणु
		क्रम (way = 0; way < CACHE_WAY_PER_SET; way++) अणु
			set_way = (way << 29) | (set << 5);
			__यंत्र__("mcr p15, 1, %0, c7, c15, 2" : : "r"(set_way));
		पूर्ण
	पूर्ण

	dsb();
पूर्ण

अटल व्योम xsc3_l2_flush_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ vaddr;

	अगर (start == 0 && end == -1ul) अणु
		xsc3_l2_flush_all();
		वापस;
	पूर्ण

	vaddr = -1;  /* to क्रमce the first mapping */

	start &= ~(CACHE_LINE_SIZE - 1);
	जबतक (start < end) अणु
		vaddr = l2_map_va(start, vaddr);
		xsc3_l2_clean_mva(vaddr);
		xsc3_l2_inv_mva(vaddr);
		start += CACHE_LINE_SIZE;
	पूर्ण

	l2_unmap_va(vaddr);

	dsb();
पूर्ण

अटल पूर्णांक __init xsc3_l2_init(व्योम)
अणु
	अगर (!cpu_is_xsc3() || !xsc3_l2_present())
		वापस 0;

	अगर (get_cr() & CR_L2) अणु
		pr_info("XScale3 L2 cache enabled.\n");
		xsc3_l2_inv_all();

		outer_cache.inv_range = xsc3_l2_inv_range;
		outer_cache.clean_range = xsc3_l2_clean_range;
		outer_cache.flush_range = xsc3_l2_flush_range;
	पूर्ण

	वापस 0;
पूर्ण
core_initcall(xsc3_l2_init);
