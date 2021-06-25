<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/cpu/sh3/probe.c
 *
 * CPU Subtype Probing क्रम SH-3.
 *
 * Copyright (C) 1999, 2000  Niibe Yutaka
 * Copyright (C) 2002  Paul Mundt
 */

#समावेश <linux/init.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/पन.स>

व्योम cpu_probe(व्योम)
अणु
	अचिन्हित दीर्घ addr0, addr1, data0, data1, data2, data3;

	jump_to_uncached();
	/*
	 * Check अगर the entry shaकरोws or not.
	 * When shaकरोwed, it's 128-entry प्रणाली.
	 * Otherwise, it's 256-entry प्रणाली.
	 */
	addr0 = CACHE_OC_ADDRESS_ARRAY + (3 << 12);
	addr1 = CACHE_OC_ADDRESS_ARRAY + (1 << 12);

	/* First, ग_लिखो back & invalidate */
	data0  = __raw_पढ़ोl(addr0);
	__raw_ग_लिखोl(data0&~(SH_CACHE_VALID|SH_CACHE_UPDATED), addr0);
	data1  = __raw_पढ़ोl(addr1);
	__raw_ग_लिखोl(data1&~(SH_CACHE_VALID|SH_CACHE_UPDATED), addr1);

	/* Next, check अगर there's shaकरोw or not */
	data0 = __raw_पढ़ोl(addr0);
	data0 ^= SH_CACHE_VALID;
	__raw_ग_लिखोl(data0, addr0);
	data1 = __raw_पढ़ोl(addr1);
	data2 = data1 ^ SH_CACHE_VALID;
	__raw_ग_लिखोl(data2, addr1);
	data3 = __raw_पढ़ोl(addr0);

	/* Lastly, invaliate them. */
	__raw_ग_लिखोl(data0&~SH_CACHE_VALID, addr0);
	__raw_ग_लिखोl(data2&~SH_CACHE_VALID, addr1);

	back_to_cached();

	boot_cpu_data.dcache.ways		= 4;
	boot_cpu_data.dcache.entry_shअगरt	= 4;
	boot_cpu_data.dcache.linesz		= L1_CACHE_BYTES;
	boot_cpu_data.dcache.flags		= 0;

	/*
	 * 7709A/7729 has 16K cache (256-entry), जबतक 7702 has only
	 * 2K(direct) 7702 is not supported (yet)
	 */
	अगर (data0 == data1 && data2 == data3) अणु	/* Shaकरोw */
		boot_cpu_data.dcache.way_incr	= (1 << 11);
		boot_cpu_data.dcache.entry_mask	= 0x7f0;
		boot_cpu_data.dcache.sets	= 128;
		boot_cpu_data.type = CPU_SH7708;

		boot_cpu_data.flags |= CPU_HAS_MMU_PAGE_ASSOC;
	पूर्ण अन्यथा अणु				/* 7709A or 7729  */
		boot_cpu_data.dcache.way_incr	= (1 << 12);
		boot_cpu_data.dcache.entry_mask	= 0xff0;
		boot_cpu_data.dcache.sets	= 256;
		boot_cpu_data.type = CPU_SH7729;

#अगर defined(CONFIG_CPU_SUBTYPE_SH7706)
		boot_cpu_data.type = CPU_SH7706;
#पूर्ण_अगर
#अगर defined(CONFIG_CPU_SUBTYPE_SH7710)
		boot_cpu_data.type = CPU_SH7710;
#पूर्ण_अगर
#अगर defined(CONFIG_CPU_SUBTYPE_SH7712)
		boot_cpu_data.type = CPU_SH7712;
#पूर्ण_अगर
#अगर defined(CONFIG_CPU_SUBTYPE_SH7720)
		boot_cpu_data.type = CPU_SH7720;
#पूर्ण_अगर
#अगर defined(CONFIG_CPU_SUBTYPE_SH7721)
		boot_cpu_data.type = CPU_SH7721;
#पूर्ण_अगर
#अगर defined(CONFIG_CPU_SUBTYPE_SH7705)
		boot_cpu_data.type = CPU_SH7705;

#अगर defined(CONFIG_SH7705_CACHE_32KB)
		boot_cpu_data.dcache.way_incr	= (1 << 13);
		boot_cpu_data.dcache.entry_mask	= 0x1ff0;
		boot_cpu_data.dcache.sets	= 512;
		__raw_ग_लिखोl(CCR_CACHE_32KB, CCR3_REG);
#अन्यथा
		__raw_ग_लिखोl(CCR_CACHE_16KB, CCR3_REG);
#पूर्ण_अगर
#पूर्ण_अगर
	पूर्ण

	/*
	 * SH-3 करोesn't have separate caches
	 */
	boot_cpu_data.dcache.flags |= SH_CACHE_COMBINED;
	boot_cpu_data.icache = boot_cpu_data.dcache;

	boot_cpu_data.family = CPU_FAMILY_SH3;
पूर्ण
