<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 1997, 2001 Ralf Baechle (ralf@gnu.org),
 * derived from r4xx0.c by David S. Miller (davem@davemloft.net).
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/bcache.h>
#समावेश <यंत्र/cacheops.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/r4kcache.h>

/* Secondary cache size in bytes, अगर present.  */
अटल अचिन्हित दीर्घ scache_size;

#घोषणा SC_LINE 32
#घोषणा SC_PAGE (128*SC_LINE)

अटल अंतरभूत व्योम blast_r5000_scache(व्योम)
अणु
	अचिन्हित दीर्घ start = INDEX_BASE;
	अचिन्हित दीर्घ end = start + scache_size;

	जबतक(start < end) अणु
		cache_op(R5K_Page_Invalidate_S, start);
		start += SC_PAGE;
	पूर्ण
पूर्ण

अटल व्योम r5k_dma_cache_inv_sc(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ end, a;

	/* Catch bad driver code */
	BUG_ON(size == 0);

	अगर (size >= scache_size) अणु
		blast_r5000_scache();
		वापस;
	पूर्ण

	/* On the R5000 secondary cache we cannot
	 * invalidate less than a page at a समय.
	 * The secondary cache is physically indexed, ग_लिखो-through.
	 */
	a = addr & ~(SC_PAGE - 1);
	end = (addr + size - 1) & ~(SC_PAGE - 1);
	जबतक (a <= end) अणु
		cache_op(R5K_Page_Invalidate_S, a);
		a += SC_PAGE;
	पूर्ण
पूर्ण

अटल व्योम r5k_sc_enable(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	set_c0_config(R5K_CONF_SE);
	blast_r5000_scache();
	local_irq_restore(flags);
पूर्ण

अटल व्योम r5k_sc_disable(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	blast_r5000_scache();
	clear_c0_config(R5K_CONF_SE);
	local_irq_restore(flags);
पूर्ण

अटल अंतरभूत पूर्णांक __init r5k_sc_probe(व्योम)
अणु
	अचिन्हित दीर्घ config = पढ़ो_c0_config();

	अगर (config & CONF_SC)
		वापस 0;

	scache_size = (512 * 1024) << ((config & R5K_CONF_SS) >> 20);

	prपूर्णांकk("R5000 SCACHE size %ldkB, linesize 32 bytes.\n",
			scache_size >> 10);

	वापस 1;
पूर्ण

अटल काष्ठा bcache_ops r5k_sc_ops = अणु
	.bc_enable = r5k_sc_enable,
	.bc_disable = r5k_sc_disable,
	.bc_wback_inv = r5k_dma_cache_inv_sc,
	.bc_inv = r5k_dma_cache_inv_sc
पूर्ण;

व्योम r5k_sc_init(व्योम)
अणु
	अगर (r5k_sc_probe()) अणु
		r5k_sc_enable();
		bcops = &r5k_sc_ops;
	पूर्ण
पूर्ण
