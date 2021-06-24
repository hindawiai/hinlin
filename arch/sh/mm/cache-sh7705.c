<शैली गुरु>
/*
 * arch/sh/mm/cache-sh7705.c
 *
 * Copyright (C) 1999, 2000  Niibe Yutaka
 * Copyright (C) 2004  Alex Song
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 */
#समावेश <linux/init.h>
#समावेश <linux/mman.h>
#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/pagemap.h>
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
 * The 32KB cache on the SH7705 suffers from the same synonym problem
 * as SH4 CPUs
 */
अटल अंतरभूत व्योम cache_wback_all(व्योम)
अणु
	अचिन्हित दीर्घ ways, waysize, addrstart;

	ways = current_cpu_data.dcache.ways;
	waysize = current_cpu_data.dcache.sets;
	waysize <<= current_cpu_data.dcache.entry_shअगरt;

	addrstart = CACHE_OC_ADDRESS_ARRAY;

	करो अणु
		अचिन्हित दीर्घ addr;

		क्रम (addr = addrstart;
		     addr < addrstart + waysize;
		     addr += current_cpu_data.dcache.linesz) अणु
			अचिन्हित दीर्घ data;
			पूर्णांक v = SH_CACHE_UPDATED | SH_CACHE_VALID;

			data = __raw_पढ़ोl(addr);

			अगर ((data & v) == v)
				__raw_ग_लिखोl(data & ~v, addr);

		पूर्ण

		addrstart += current_cpu_data.dcache.way_incr;
	पूर्ण जबतक (--ways);
पूर्ण

/*
 * Write back the range of D-cache, and purge the I-cache.
 *
 * Called from kernel/module.c:sys_init_module and routine क्रम a.out क्रमmat.
 */
अटल व्योम sh7705_flush_icache_range(व्योम *args)
अणु
	काष्ठा flusher_data *data = args;
	अचिन्हित दीर्घ start, end;

	start = data->addr1;
	end = data->addr2;

	__flush_wback_region((व्योम *)start, end - start);
पूर्ण

/*
 * Writeback&Invalidate the D-cache of the page
 */
अटल व्योम __flush_dcache_page(अचिन्हित दीर्घ phys)
अणु
	अचिन्हित दीर्घ ways, waysize, addrstart;
	अचिन्हित दीर्घ flags;

	phys |= SH_CACHE_VALID;

	/*
	 * Here, phys is the physical address of the page. We check all the
	 * tags in the cache क्रम those with the same page number as this page
	 * (by masking off the lowest 2 bits of the 19-bit tag; these bits are
	 * derived from the offset within in the 4k page). Matching valid
	 * entries are invalidated.
	 *
	 * Since 2 bits of the cache index are derived from the भव page
	 * number, knowing this would reduce the number of cache entries to be
	 * searched by a factor of 4. However this function exists to deal with
	 * potential cache aliasing, thereक्रमe the optimisation is probably not
	 * possible.
	 */
	local_irq_save(flags);
	jump_to_uncached();

	ways = current_cpu_data.dcache.ways;
	waysize = current_cpu_data.dcache.sets;
	waysize <<= current_cpu_data.dcache.entry_shअगरt;

	addrstart = CACHE_OC_ADDRESS_ARRAY;

	करो अणु
		अचिन्हित दीर्घ addr;

		क्रम (addr = addrstart;
		     addr < addrstart + waysize;
		     addr += current_cpu_data.dcache.linesz) अणु
			अचिन्हित दीर्घ data;

			data = __raw_पढ़ोl(addr) & (0x1ffffC00 | SH_CACHE_VALID);
		        अगर (data == phys) अणु
				data &= ~(SH_CACHE_VALID | SH_CACHE_UPDATED);
				__raw_ग_लिखोl(data, addr);
			पूर्ण
		पूर्ण

		addrstart += current_cpu_data.dcache.way_incr;
	पूर्ण जबतक (--ways);

	back_to_cached();
	local_irq_restore(flags);
पूर्ण

/*
 * Write back & invalidate the D-cache of the page.
 * (To aव्योम "alias" issues)
 */
अटल व्योम sh7705_flush_dcache_page(व्योम *arg)
अणु
	काष्ठा page *page = arg;
	काष्ठा address_space *mapping = page_mapping_file(page);

	अगर (mapping && !mapping_mapped(mapping))
		clear_bit(PG_dcache_clean, &page->flags);
	अन्यथा
		__flush_dcache_page(__pa(page_address(page)));
पूर्ण

अटल व्योम sh7705_flush_cache_all(व्योम *args)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	jump_to_uncached();

	cache_wback_all();
	back_to_cached();
	local_irq_restore(flags);
पूर्ण

/*
 * Write back and invalidate I/D-caches क्रम the page.
 *
 * ADDRESS: Virtual Address (U0 address)
 */
अटल व्योम sh7705_flush_cache_page(व्योम *args)
अणु
	काष्ठा flusher_data *data = args;
	अचिन्हित दीर्घ pfn = data->addr2;

	__flush_dcache_page(pfn << PAGE_SHIFT);
पूर्ण

/*
 * This is called when a page-cache page is about to be mapped पूर्णांकo a
 * user process' address space.  It offers an opportunity क्रम a
 * port to ensure d-cache/i-cache coherency अगर necessary.
 *
 * Not entirely sure why this is necessary on SH3 with 32K cache but
 * without it we get occasional "Memory fault" when loading a program.
 */
अटल व्योम sh7705_flush_icache_page(व्योम *page)
अणु
	__flush_purge_region(page_address(page), PAGE_SIZE);
पूर्ण

व्योम __init sh7705_cache_init(व्योम)
अणु
	local_flush_icache_range	= sh7705_flush_icache_range;
	local_flush_dcache_page		= sh7705_flush_dcache_page;
	local_flush_cache_all		= sh7705_flush_cache_all;
	local_flush_cache_mm		= sh7705_flush_cache_all;
	local_flush_cache_dup_mm	= sh7705_flush_cache_all;
	local_flush_cache_range		= sh7705_flush_cache_all;
	local_flush_cache_page		= sh7705_flush_cache_page;
	local_flush_icache_page		= sh7705_flush_icache_page;
पूर्ण
