<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sc-rm7k.c: RM7000 cache management functions.
 *
 * Copyright (C) 1997, 2001, 2003, 2004 Ralf Baechle (ralf@linux-mips.org)
 */

#अघोषित DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/bcache.h>
#समावेश <यंत्र/cacheops.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/cacheflush.h> /* क्रम run_uncached() */

/* Primary cache parameters. */
#घोषणा sc_lsize	32
#घोषणा tc_pagesize	(32*128)

/* Secondary cache parameters. */
#घोषणा scache_size	(256*1024)	/* Fixed to 256KiB on RM7000 */

/* Tertiary cache parameters */
#घोषणा tc_lsize	32

बाह्य अचिन्हित दीर्घ icache_way_size, dcache_way_size;
अटल अचिन्हित दीर्घ tcache_size;

#समावेश <यंत्र/r4kcache.h>

अटल पूर्णांक rm7k_tcache_init;

/*
 * Writeback and invalidate the primary cache dcache beक्रमe DMA.
 * (XXX These need to be fixed ...)
 */
अटल व्योम rm7k_sc_wback_inv(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ end, a;

	pr_debug("rm7k_sc_wback_inv[%08lx,%08lx]", addr, size);

	/* Catch bad driver code */
	BUG_ON(size == 0);

	blast_scache_range(addr, addr + size);

	अगर (!rm7k_tcache_init)
		वापस;

	a = addr & ~(tc_pagesize - 1);
	end = (addr + size - 1) & ~(tc_pagesize - 1);
	जबतक(1) अणु
		invalidate_tcache_page(a);	/* Page_Invalidate_T */
		अगर (a == end)
			अवरोध;
		a += tc_pagesize;
	पूर्ण
पूर्ण

अटल व्योम rm7k_sc_inv(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ end, a;

	pr_debug("rm7k_sc_inv[%08lx,%08lx]", addr, size);

	/* Catch bad driver code */
	BUG_ON(size == 0);

	blast_inv_scache_range(addr, addr + size);

	अगर (!rm7k_tcache_init)
		वापस;

	a = addr & ~(tc_pagesize - 1);
	end = (addr + size - 1) & ~(tc_pagesize - 1);
	जबतक(1) अणु
		invalidate_tcache_page(a);	/* Page_Invalidate_T */
		अगर (a == end)
			अवरोध;
		a += tc_pagesize;
	पूर्ण
पूर्ण

अटल व्योम blast_rm7k_tcache(व्योम)
अणु
	अचिन्हित दीर्घ start = CKSEG0ADDR(0);
	अचिन्हित दीर्घ end = start + tcache_size;

	ग_लिखो_c0_taglo(0);

	जबतक (start < end) अणु
		cache_op(Page_Invalidate_T, start);
		start += tc_pagesize;
	पूर्ण
पूर्ण

/*
 * This function is executed in uncached address space.
 */
अटल व्योम __rm7k_tc_enable(व्योम)
अणु
	पूर्णांक i;

	set_c0_config(RM7K_CONF_TE);

	ग_लिखो_c0_taglo(0);
	ग_लिखो_c0_taghi(0);

	क्रम (i = 0; i < tcache_size; i += tc_lsize)
		cache_op(Index_Store_Tag_T, CKSEG0ADDR(i));
पूर्ण

अटल व्योम rm7k_tc_enable(व्योम)
अणु
	अगर (पढ़ो_c0_config() & RM7K_CONF_TE)
		वापस;

	BUG_ON(tcache_size == 0);

	run_uncached(__rm7k_tc_enable);
पूर्ण

/*
 * This function is executed in uncached address space.
 */
अटल व्योम __rm7k_sc_enable(व्योम)
अणु
	पूर्णांक i;

	set_c0_config(RM7K_CONF_SE);

	ग_लिखो_c0_taglo(0);
	ग_लिखो_c0_taghi(0);

	क्रम (i = 0; i < scache_size; i += sc_lsize)
		cache_op(Index_Store_Tag_SD, CKSEG0ADDR(i));
पूर्ण

अटल व्योम rm7k_sc_enable(व्योम)
अणु
	अगर (पढ़ो_c0_config() & RM7K_CONF_SE)
		वापस;

	pr_info("Enabling secondary cache...\n");
	run_uncached(__rm7k_sc_enable);

	अगर (rm7k_tcache_init)
		rm7k_tc_enable();
पूर्ण

अटल व्योम rm7k_tc_disable(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	blast_rm7k_tcache();
	clear_c0_config(RM7K_CONF_TE);
	local_irq_restore(flags);
पूर्ण

अटल व्योम rm7k_sc_disable(व्योम)
अणु
	clear_c0_config(RM7K_CONF_SE);

	अगर (rm7k_tcache_init)
		rm7k_tc_disable();
पूर्ण

अटल काष्ठा bcache_ops rm7k_sc_ops = अणु
	.bc_enable = rm7k_sc_enable,
	.bc_disable = rm7k_sc_disable,
	.bc_wback_inv = rm7k_sc_wback_inv,
	.bc_inv = rm7k_sc_inv
पूर्ण;

/*
 * This is a probing function like the one found in c-r4k.c, we look क्रम the
 * wrap around poपूर्णांक with dअगरferent addresses.
 */
अटल व्योम __probe_tcache(व्योम)
अणु
	अचिन्हित दीर्घ flags, addr, begin, end, घात2;

	begin = (अचिन्हित दीर्घ) &_stext;
	begin  &= ~((8 * 1024 * 1024) - 1);
	end = begin + (8 * 1024 * 1024);

	local_irq_save(flags);

	set_c0_config(RM7K_CONF_TE);

	/* Fill size-multiple lines with a valid tag */
	घात2 = (256 * 1024);
	क्रम (addr = begin; addr <= end; addr = (begin + घात2)) अणु
		अचिन्हित दीर्घ *p = (अचिन्हित दीर्घ *) addr;
		__यंत्र__ __अस्थिर__("nop" : : "r" (*p));
		घात2 <<= 1;
	पूर्ण

	/* Load first line with a 0 tag, to check after */
	ग_लिखो_c0_taglo(0);
	ग_लिखो_c0_taghi(0);
	cache_op(Index_Store_Tag_T, begin);

	/* Look क्रम the wrap-around */
	घात2 = (512 * 1024);
	क्रम (addr = begin + (512 * 1024); addr <= end; addr = begin + घात2) अणु
		cache_op(Index_Load_Tag_T, addr);
		अगर (!पढ़ो_c0_taglo())
			अवरोध;
		घात2 <<= 1;
	पूर्ण

	addr -= begin;
	tcache_size = addr;

	clear_c0_config(RM7K_CONF_TE);

	local_irq_restore(flags);
पूर्ण

व्योम rm7k_sc_init(व्योम)
अणु
	काष्ठा cpuinfo_mips *c = &current_cpu_data;
	अचिन्हित पूर्णांक config = पढ़ो_c0_config();

	अगर ((config & RM7K_CONF_SC))
		वापस;

	c->scache.linesz = sc_lsize;
	c->scache.ways = 4;
	c->scache.waybit= __ffs(scache_size / c->scache.ways);
	c->scache.waysize = scache_size / c->scache.ways;
	c->scache.sets = scache_size / (c->scache.linesz * c->scache.ways);
	prपूर्णांकk(KERN_INFO "Secondary cache size %dK, linesize %d bytes.\n",
	       (scache_size >> 10), sc_lsize);

	अगर (!(config & RM7K_CONF_SE))
		rm7k_sc_enable();

	bcops = &rm7k_sc_ops;

	/*
	 * While we're at it let's deal with the tertiary cache.
	 */

	rm7k_tcache_init = 0;
	tcache_size = 0;

	अगर (config & RM7K_CONF_TC)
		वापस;

	/*
	 * No efficient way to ask the hardware क्रम the size of the tcache,
	 * so must probe क्रम it.
	 */
	run_uncached(__probe_tcache);
	rm7k_tc_enable();
	rm7k_tcache_init = 1;
	c->tcache.linesz = tc_lsize;
	c->tcache.ways = 1;
	pr_info("Tertiary cache size %ldK.\n", (tcache_size >> 10));
पूर्ण
