<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/sh/mm/cache-sh2a.c
 *
 * Copyright (C) 2008 Yoshinori Sato
 */

#समावेश <linux/init.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/पन.स>

/*
 * The maximum number of pages we support up to when करोing ranged dcache
 * flushing. Anything exceeding this will simply flush the dcache in its
 * entirety.
 */
#घोषणा MAX_OCACHE_PAGES	32
#घोषणा MAX_ICACHE_PAGES	32

#अगर_घोषित CONFIG_CACHE_WRITEBACK
अटल व्योम sh2a_flush_oc_line(अचिन्हित दीर्घ v, पूर्णांक way)
अणु
	अचिन्हित दीर्घ addr = (v & 0x000007f0) | (way << 11);
	अचिन्हित दीर्घ data;

	data = __raw_पढ़ोl(CACHE_OC_ADDRESS_ARRAY | addr);
	अगर ((data & CACHE_PHYSADDR_MASK) == (v & CACHE_PHYSADDR_MASK)) अणु
		data &= ~SH_CACHE_UPDATED;
		__raw_ग_लिखोl(data, CACHE_OC_ADDRESS_ARRAY | addr);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल व्योम sh2a_invalidate_line(अचिन्हित दीर्घ cache_addr, अचिन्हित दीर्घ v)
अणु
	/* Set associative bit to hit all ways */
	अचिन्हित दीर्घ addr = (v & 0x000007f0) | SH_CACHE_ASSOC;
	__raw_ग_लिखोl((addr & CACHE_PHYSADDR_MASK), cache_addr | addr);
पूर्ण

/*
 * Write back the dirty D-caches, but not invalidate them.
 */
अटल व्योम sh2a__flush_wback_region(व्योम *start, पूर्णांक size)
अणु
#अगर_घोषित CONFIG_CACHE_WRITEBACK
	अचिन्हित दीर्घ v;
	अचिन्हित दीर्घ begin, end;
	अचिन्हित दीर्घ flags;
	पूर्णांक nr_ways;

	begin = (अचिन्हित दीर्घ)start & ~(L1_CACHE_BYTES-1);
	end = ((अचिन्हित दीर्घ)start + size + L1_CACHE_BYTES-1)
		& ~(L1_CACHE_BYTES-1);
	nr_ways = current_cpu_data.dcache.ways;

	local_irq_save(flags);
	jump_to_uncached();

	/* If there are too many pages then flush the entire cache */
	अगर (((end - begin) >> PAGE_SHIFT) >= MAX_OCACHE_PAGES) अणु
		begin = CACHE_OC_ADDRESS_ARRAY;
		end = begin + (nr_ways * current_cpu_data.dcache.way_size);

		क्रम (v = begin; v < end; v += L1_CACHE_BYTES) अणु
			अचिन्हित दीर्घ data = __raw_पढ़ोl(v);
			अगर (data & SH_CACHE_UPDATED)
				__raw_ग_लिखोl(data & ~SH_CACHE_UPDATED, v);
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक way;
		क्रम (way = 0; way < nr_ways; way++) अणु
			क्रम (v = begin; v < end; v += L1_CACHE_BYTES)
				sh2a_flush_oc_line(v, way);
		पूर्ण
	पूर्ण

	back_to_cached();
	local_irq_restore(flags);
#पूर्ण_अगर
पूर्ण

/*
 * Write back the dirty D-caches and invalidate them.
 */
अटल व्योम sh2a__flush_purge_region(व्योम *start, पूर्णांक size)
अणु
	अचिन्हित दीर्घ v;
	अचिन्हित दीर्घ begin, end;
	अचिन्हित दीर्घ flags;

	begin = (अचिन्हित दीर्घ)start & ~(L1_CACHE_BYTES-1);
	end = ((अचिन्हित दीर्घ)start + size + L1_CACHE_BYTES-1)
		& ~(L1_CACHE_BYTES-1);

	local_irq_save(flags);
	jump_to_uncached();

	क्रम (v = begin; v < end; v+=L1_CACHE_BYTES) अणु
#अगर_घोषित CONFIG_CACHE_WRITEBACK
		पूर्णांक way;
		पूर्णांक nr_ways = current_cpu_data.dcache.ways;
		क्रम (way = 0; way < nr_ways; way++)
			sh2a_flush_oc_line(v, way);
#पूर्ण_अगर
		sh2a_invalidate_line(CACHE_OC_ADDRESS_ARRAY, v);
	पूर्ण

	back_to_cached();
	local_irq_restore(flags);
पूर्ण

/*
 * Invalidate the D-caches, but no ग_लिखो back please
 */
अटल व्योम sh2a__flush_invalidate_region(व्योम *start, पूर्णांक size)
अणु
	अचिन्हित दीर्घ v;
	अचिन्हित दीर्घ begin, end;
	अचिन्हित दीर्घ flags;

	begin = (अचिन्हित दीर्घ)start & ~(L1_CACHE_BYTES-1);
	end = ((अचिन्हित दीर्घ)start + size + L1_CACHE_BYTES-1)
		& ~(L1_CACHE_BYTES-1);

	local_irq_save(flags);
	jump_to_uncached();

	/* If there are too many pages then just blow the cache */
	अगर (((end - begin) >> PAGE_SHIFT) >= MAX_OCACHE_PAGES) अणु
		__raw_ग_लिखोl(__raw_पढ़ोl(SH_CCR) | CCR_OCACHE_INVALIDATE,
			     SH_CCR);
	पूर्ण अन्यथा अणु
		क्रम (v = begin; v < end; v += L1_CACHE_BYTES)
			sh2a_invalidate_line(CACHE_OC_ADDRESS_ARRAY, v);
	पूर्ण

	back_to_cached();
	local_irq_restore(flags);
पूर्ण

/*
 * Write back the range of D-cache, and purge the I-cache.
 */
अटल व्योम sh2a_flush_icache_range(व्योम *args)
अणु
	काष्ठा flusher_data *data = args;
	अचिन्हित दीर्घ start, end;
	अचिन्हित दीर्घ v;
	अचिन्हित दीर्घ flags;

	start = data->addr1 & ~(L1_CACHE_BYTES-1);
	end = (data->addr2 + L1_CACHE_BYTES-1) & ~(L1_CACHE_BYTES-1);

#अगर_घोषित CONFIG_CACHE_WRITEBACK
	sh2a__flush_wback_region((व्योम *)start, end-start);
#पूर्ण_अगर

	local_irq_save(flags);
	jump_to_uncached();

	/* I-Cache invalidate */
	/* If there are too many pages then just blow the cache */
	अगर (((end - start) >> PAGE_SHIFT) >= MAX_ICACHE_PAGES) अणु
		__raw_ग_लिखोl(__raw_पढ़ोl(SH_CCR) | CCR_ICACHE_INVALIDATE,
			     SH_CCR);
	पूर्ण अन्यथा अणु
		क्रम (v = start; v < end; v += L1_CACHE_BYTES)
			sh2a_invalidate_line(CACHE_IC_ADDRESS_ARRAY, v);
	पूर्ण

	back_to_cached();
	local_irq_restore(flags);
पूर्ण

व्योम __init sh2a_cache_init(व्योम)
अणु
	local_flush_icache_range	= sh2a_flush_icache_range;

	__flush_wback_region		= sh2a__flush_wback_region;
	__flush_purge_region		= sh2a__flush_purge_region;
	__flush_invalidate_region	= sh2a__flush_invalidate_region;
पूर्ण
