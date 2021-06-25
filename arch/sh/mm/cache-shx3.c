<शैली गुरु>
/*
 * arch/sh/mm/cache-shx3.c - SH-X3 optimized cache ops
 *
 * Copyright (C) 2010  Paul Mundt
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/cache.h>

#घोषणा CCR_CACHE_SNM	0x40000		/* Hardware-assisted synonym aव्योमance */
#घोषणा CCR_CACHE_IBE	0x1000000	/* ICBI broadcast */

व्योम __init shx3_cache_init(व्योम)
अणु
	अचिन्हित पूर्णांक ccr;

	ccr = __raw_पढ़ोl(SH_CCR);

	/*
	 * If we've got cache aliases, resolve them in hardware.
	 */
	अगर (boot_cpu_data.dcache.n_aliases || boot_cpu_data.icache.n_aliases) अणु
		ccr |= CCR_CACHE_SNM;

		boot_cpu_data.icache.n_aliases = 0;
		boot_cpu_data.dcache.n_aliases = 0;

		pr_info("Enabling hardware synonym avoidance\n");
	पूर्ण

#अगर_घोषित CONFIG_SMP
	/*
	 * Broadcast I-cache block invalidations by शेष.
	 */
	ccr |= CCR_CACHE_IBE;
#पूर्ण_अगर

	ग_लिखोl_uncached(ccr, SH_CCR);
पूर्ण
