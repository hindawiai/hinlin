<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/sh/mm/cache-sh3.c
 *
 * Copyright (C) 1999, 2000  Niibe Yutaka
 * Copyright (C) 2002 Paul Mundt
 */

#समावेश <linux/init.h>
#समावेश <linux/mman.h>
#समावेश <linux/mm.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/cacheflush.h>

/*
 * Write back the dirty D-caches, but not invalidate them.
 *
 * Is this really worth it, or should we just alias this routine
 * to __flush_purge_region too?
 *
 * START: Virtual Address (U0, P1, or P3)
 * SIZE: Size of the region.
 */

अटल व्योम sh3__flush_wback_region(व्योम *start, पूर्णांक size)
अणु
	अचिन्हित दीर्घ v, j;
	अचिन्हित दीर्घ begin, end;
	अचिन्हित दीर्घ flags;

	begin = (अचिन्हित दीर्घ)start & ~(L1_CACHE_BYTES-1);
	end = ((अचिन्हित दीर्घ)start + size + L1_CACHE_BYTES-1)
		& ~(L1_CACHE_BYTES-1);

	क्रम (v = begin; v < end; v+=L1_CACHE_BYTES) अणु
		अचिन्हित दीर्घ addrstart = CACHE_OC_ADDRESS_ARRAY;
		क्रम (j = 0; j < current_cpu_data.dcache.ways; j++) अणु
			अचिन्हित दीर्घ data, addr, p;

			p = __pa(v);
			addr = addrstart | (v & current_cpu_data.dcache.entry_mask);
			local_irq_save(flags);
			data = __raw_पढ़ोl(addr);

			अगर ((data & CACHE_PHYSADDR_MASK) ==
			    (p & CACHE_PHYSADDR_MASK)) अणु
				data &= ~SH_CACHE_UPDATED;
				__raw_ग_लिखोl(data, addr);
				local_irq_restore(flags);
				अवरोध;
			पूर्ण
			local_irq_restore(flags);
			addrstart += current_cpu_data.dcache.way_incr;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Write back the dirty D-caches and invalidate them.
 *
 * START: Virtual Address (U0, P1, or P3)
 * SIZE: Size of the region.
 */
अटल व्योम sh3__flush_purge_region(व्योम *start, पूर्णांक size)
अणु
	अचिन्हित दीर्घ v;
	अचिन्हित दीर्घ begin, end;

	begin = (अचिन्हित दीर्घ)start & ~(L1_CACHE_BYTES-1);
	end = ((अचिन्हित दीर्घ)start + size + L1_CACHE_BYTES-1)
		& ~(L1_CACHE_BYTES-1);

	क्रम (v = begin; v < end; v+=L1_CACHE_BYTES) अणु
		अचिन्हित दीर्घ data, addr;

		data = (v & 0xfffffc00); /* _Virtual_ address, ~U, ~V */
		addr = CACHE_OC_ADDRESS_ARRAY |
			(v & current_cpu_data.dcache.entry_mask) | SH_CACHE_ASSOC;
		__raw_ग_लिखोl(data, addr);
	पूर्ण
पूर्ण

व्योम __init sh3_cache_init(व्योम)
अणु
	__flush_wback_region = sh3__flush_wback_region;
	__flush_purge_region = sh3__flush_purge_region;

	/*
	 * No ग_लिखो back please
	 *
	 * Except I करोn't think there's any way to aव्योम the ग_लिखोback.
	 * So we just alias it to sh3__flush_purge_region(). dwmw2.
	 */
	__flush_invalidate_region = sh3__flush_purge_region;
पूर्ण
