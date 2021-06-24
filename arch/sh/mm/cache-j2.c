<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/sh/mm/cache-j2.c
 *
 * Copyright (C) 2015-2016 Smart Energy Instruments, Inc.
 */

#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/cpumask.h>

#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/पन.स>

#घोषणा ICACHE_ENABLE	0x1
#घोषणा DCACHE_ENABLE	0x2
#घोषणा CACHE_ENABLE	(ICACHE_ENABLE | DCACHE_ENABLE)
#घोषणा ICACHE_FLUSH	0x100
#घोषणा DCACHE_FLUSH	0x200
#घोषणा CACHE_FLUSH	(ICACHE_FLUSH | DCACHE_FLUSH)

u32 __iomem *j2_ccr_base;

अटल व्योम j2_flush_icache(व्योम *args)
अणु
	अचिन्हित cpu;
	क्रम_each_possible_cpu(cpu)
		__raw_ग_लिखोl(CACHE_ENABLE | ICACHE_FLUSH, j2_ccr_base + cpu);
पूर्ण

अटल व्योम j2_flush_dcache(व्योम *args)
अणु
	अचिन्हित cpu;
	क्रम_each_possible_cpu(cpu)
		__raw_ग_लिखोl(CACHE_ENABLE | DCACHE_FLUSH, j2_ccr_base + cpu);
पूर्ण

अटल व्योम j2_flush_both(व्योम *args)
अणु
	अचिन्हित cpu;
	क्रम_each_possible_cpu(cpu)
		__raw_ग_लिखोl(CACHE_ENABLE | CACHE_FLUSH, j2_ccr_base + cpu);
पूर्ण

व्योम __init j2_cache_init(व्योम)
अणु
	अगर (!j2_ccr_base)
		वापस;

	local_flush_cache_all = j2_flush_both;
	local_flush_cache_mm = j2_flush_both;
	local_flush_cache_dup_mm = j2_flush_both;
	local_flush_cache_page = j2_flush_both;
	local_flush_cache_range = j2_flush_both;
	local_flush_dcache_page = j2_flush_dcache;
	local_flush_icache_range = j2_flush_icache;
	local_flush_icache_page = j2_flush_icache;
	local_flush_cache_sigtramp = j2_flush_icache;

	pr_info("Initial J2 CCR is %.8x\n", __raw_पढ़ोl(j2_ccr_base));
पूर्ण
