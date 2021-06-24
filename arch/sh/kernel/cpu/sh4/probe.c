<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/cpu/sh4/probe.c
 *
 * CPU Subtype Probing क्रम SH-4.
 *
 * Copyright (C) 2001 - 2007  Paul Mundt
 * Copyright (C) 2003  Riअक्षरd Curnow
 */
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/cache.h>

व्योम cpu_probe(व्योम)
अणु
	अचिन्हित दीर्घ pvr, prr, cvr;
	अचिन्हित दीर्घ size;

	अटल अचिन्हित दीर्घ sizes[16] = अणु
		[1] = (1 << 12),
		[2] = (1 << 13),
		[4] = (1 << 14),
		[8] = (1 << 15),
		[9] = (1 << 16)
	पूर्ण;

	pvr = (__raw_पढ़ोl(CCN_PVR) >> 8) & 0xffffff;
	prr = (__raw_पढ़ोl(CCN_PRR) >> 4) & 0xff;
	cvr = (__raw_पढ़ोl(CCN_CVR));

	/*
	 * Setup some sane SH-4 शेषs क्रम the icache
	 */
	boot_cpu_data.icache.way_incr		= (1 << 13);
	boot_cpu_data.icache.entry_shअगरt	= 5;
	boot_cpu_data.icache.sets		= 256;
	boot_cpu_data.icache.ways		= 1;
	boot_cpu_data.icache.linesz		= L1_CACHE_BYTES;

	/*
	 * And again क्रम the dcache ..
	 */
	boot_cpu_data.dcache.way_incr		= (1 << 14);
	boot_cpu_data.dcache.entry_shअगरt	= 5;
	boot_cpu_data.dcache.sets		= 512;
	boot_cpu_data.dcache.ways		= 1;
	boot_cpu_data.dcache.linesz		= L1_CACHE_BYTES;

	/* We करोn't know the chip cut */
	boot_cpu_data.cut_major = boot_cpu_data.cut_minor = -1;

	/*
	 * Setup some generic flags we can probe on SH-4A parts
	 */
	अगर (((pvr >> 16) & 0xff) == 0x10) अणु
		boot_cpu_data.family = CPU_FAMILY_SH4A;

		अगर ((cvr & 0x10000000) == 0) अणु
			boot_cpu_data.flags |= CPU_HAS_DSP;
			boot_cpu_data.family = CPU_FAMILY_SH4AL_DSP;
		पूर्ण

		boot_cpu_data.flags |= CPU_HAS_LLSC | CPU_HAS_PERF_COUNTER;
		boot_cpu_data.cut_major = pvr & 0x7f;

		boot_cpu_data.icache.ways = 4;
		boot_cpu_data.dcache.ways = 4;
	पूर्ण अन्यथा अणु
		/* And some SH-4 शेषs.. */
		boot_cpu_data.flags |= CPU_HAS_PTEA | CPU_HAS_FPU;
		boot_cpu_data.family = CPU_FAMILY_SH4;
	पूर्ण

	/* FPU detection works क्रम almost everyone */
	अगर ((cvr & 0x20000000))
		boot_cpu_data.flags |= CPU_HAS_FPU;

	/* Mask off the upper chip ID */
	pvr &= 0xffff;

	/*
	 * Probe the underlying processor version/revision and
	 * adjust cpu_data setup accordingly.
	 */
	चयन (pvr) अणु
	हाल 0x205:
		boot_cpu_data.type = CPU_SH7750;
		boot_cpu_data.flags |= CPU_HAS_P2_FLUSH_BUG |
				       CPU_HAS_PERF_COUNTER;
		अवरोध;
	हाल 0x206:
		boot_cpu_data.type = CPU_SH7750S;
		boot_cpu_data.flags |= CPU_HAS_P2_FLUSH_BUG |
				       CPU_HAS_PERF_COUNTER;
		अवरोध;
	हाल 0x1100:
		boot_cpu_data.type = CPU_SH7751;
		अवरोध;
	हाल 0x2001:
	हाल 0x2004:
		boot_cpu_data.type = CPU_SH7770;
		अवरोध;
	हाल 0x2006:
	हाल 0x200A:
		अगर (prr == 0x61)
			boot_cpu_data.type = CPU_SH7781;
		अन्यथा अगर (prr == 0xa1)
			boot_cpu_data.type = CPU_SH7763;
		अन्यथा
			boot_cpu_data.type = CPU_SH7780;

		अवरोध;
	हाल 0x3000:
	हाल 0x3003:
	हाल 0x3009:
		boot_cpu_data.type = CPU_SH7343;
		अवरोध;
	हाल 0x3004:
	हाल 0x3007:
		boot_cpu_data.type = CPU_SH7785;
		अवरोध;
	हाल 0x4004:
	हाल 0x4005:
		boot_cpu_data.type = CPU_SH7786;
		boot_cpu_data.flags |= CPU_HAS_PTEAEX | CPU_HAS_L2_CACHE;
		अवरोध;
	हाल 0x3008:
		चयन (prr) अणु
		हाल 0x50:
		हाल 0x51:
			boot_cpu_data.type = CPU_SH7723;
			boot_cpu_data.flags |= CPU_HAS_L2_CACHE;
			अवरोध;
		हाल 0x70:
			boot_cpu_data.type = CPU_SH7366;
			अवरोध;
		हाल 0xa0:
		हाल 0xa1:
			boot_cpu_data.type = CPU_SH7722;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 0x300b:
		चयन (prr) अणु
		हाल 0x20:
			boot_cpu_data.type = CPU_SH7724;
			boot_cpu_data.flags |= CPU_HAS_L2_CACHE;
			अवरोध;
		हाल 0x10:
		हाल 0x11:
			boot_cpu_data.type = CPU_SH7757;
			अवरोध;
		हाल 0xd0:
		हाल 0x40: /* yon-ten-go */
			boot_cpu_data.type = CPU_SH7372;
			अवरोध;
		हाल 0xE0: /* 0x4E0 */
			boot_cpu_data.type = CPU_SH7734; /* SH7733/SH7734 */
			अवरोध;

		पूर्ण
		अवरोध;
	हाल 0x4000:	/* 1st cut */
	हाल 0x4001:	/* 2nd cut */
		boot_cpu_data.type = CPU_SHX3;
		अवरोध;
	हाल 0x700:
		boot_cpu_data.type = CPU_SH4_501;
		boot_cpu_data.flags &= ~CPU_HAS_FPU;
		boot_cpu_data.icache.ways = 2;
		boot_cpu_data.dcache.ways = 2;
		अवरोध;
	हाल 0x600:
		boot_cpu_data.type = CPU_SH4_202;
		boot_cpu_data.icache.ways = 2;
		boot_cpu_data.dcache.ways = 2;
		अवरोध;
	हाल 0x500 ... 0x501:
		चयन (prr) अणु
		हाल 0x10:
			boot_cpu_data.type = CPU_SH7750R;
			अवरोध;
		हाल 0x11:
			boot_cpu_data.type = CPU_SH7751R;
			अवरोध;
		हाल 0x50 ... 0x5f:
			boot_cpu_data.type = CPU_SH7760;
			अवरोध;
		पूर्ण

		boot_cpu_data.icache.ways = 2;
		boot_cpu_data.dcache.ways = 2;

		अवरोध;
	पूर्ण

	/*
	 * On anything that's not a direct-mapped cache, look to the CVR
	 * क्रम I/D-cache specअगरics.
	 */
	अगर (boot_cpu_data.icache.ways > 1) अणु
		size = sizes[(cvr >> 20) & 0xf];
		boot_cpu_data.icache.way_incr	= (size >> 1);
		boot_cpu_data.icache.sets	= (size >> 6);

	पूर्ण

	/* And the rest of the D-cache */
	अगर (boot_cpu_data.dcache.ways > 1) अणु
		size = sizes[(cvr >> 16) & 0xf];
		boot_cpu_data.dcache.way_incr	= (size >> 1);
		boot_cpu_data.dcache.sets	= (size >> 6);
	पूर्ण

	/*
	 * SH-4A's have an optional PIPT L2.
	 */
	अगर (boot_cpu_data.flags & CPU_HAS_L2_CACHE) अणु
		/*
		 * Verअगरy that it really has something hooked up, this
		 * is the safety net क्रम CPUs that have optional L2
		 * support yet करो not implement it.
		 */
		अगर ((cvr & 0xf) == 0)
			boot_cpu_data.flags &= ~CPU_HAS_L2_CACHE;
		अन्यथा अणु
			/*
			 * Silicon and specअगरications have clearly never
			 * met..
			 */
			cvr ^= 0xf;

			/*
			 * Size calculation is much more sensible
			 * than it is क्रम the L1.
			 *
			 * Sizes are 128KB, 256KB, 512KB, and 1MB.
			 */
			size = (cvr & 0xf) << 17;

			boot_cpu_data.scache.way_incr		= (1 << 16);
			boot_cpu_data.scache.entry_shअगरt	= 5;
			boot_cpu_data.scache.ways		= 4;
			boot_cpu_data.scache.linesz		= L1_CACHE_BYTES;

			boot_cpu_data.scache.entry_mask	=
				(boot_cpu_data.scache.way_incr -
				 boot_cpu_data.scache.linesz);

			boot_cpu_data.scache.sets	= size /
				(boot_cpu_data.scache.linesz *
				 boot_cpu_data.scache.ways);

			boot_cpu_data.scache.way_size	=
				(boot_cpu_data.scache.sets *
				 boot_cpu_data.scache.linesz);
		पूर्ण
	पूर्ण
पूर्ण
