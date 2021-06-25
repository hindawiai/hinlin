<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/sched.h>
#समावेश <linux/sched/घड़ी.h>

#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/mtrr.h>
#समावेश <यंत्र/msr.h>

#समावेश "cpu.h"

#घोषणा ACE_PRESENT	(1 << 6)
#घोषणा ACE_ENABLED	(1 << 7)
#घोषणा ACE_FCR		(1 << 28)	/* MSR_VIA_FCR */

#घोषणा RNG_PRESENT	(1 << 2)
#घोषणा RNG_ENABLED	(1 << 3)
#घोषणा RNG_ENABLE	(1 << 6)	/* MSR_VIA_RNG */

अटल व्योम init_c3(काष्ठा cpuinfo_x86 *c)
अणु
	u32  lo, hi;

	/* Test क्रम Centaur Extended Feature Flags presence */
	अगर (cpuid_eax(0xC0000000) >= 0xC0000001) अणु
		u32 पंचांगp = cpuid_edx(0xC0000001);

		/* enable ACE unit, अगर present and disabled */
		अगर ((पंचांगp & (ACE_PRESENT | ACE_ENABLED)) == ACE_PRESENT) अणु
			rdmsr(MSR_VIA_FCR, lo, hi);
			lo |= ACE_FCR;		/* enable ACE unit */
			wrmsr(MSR_VIA_FCR, lo, hi);
			pr_info("CPU: Enabled ACE h/w crypto\n");
		पूर्ण

		/* enable RNG unit, अगर present and disabled */
		अगर ((पंचांगp & (RNG_PRESENT | RNG_ENABLED)) == RNG_PRESENT) अणु
			rdmsr(MSR_VIA_RNG, lo, hi);
			lo |= RNG_ENABLE;	/* enable RNG unit */
			wrmsr(MSR_VIA_RNG, lo, hi);
			pr_info("CPU: Enabled h/w RNG\n");
		पूर्ण

		/* store Centaur Extended Feature Flags as
		 * word 5 of the CPU capability bit array
		 */
		c->x86_capability[CPUID_C000_0001_EDX] = cpuid_edx(0xC0000001);
	पूर्ण
#अगर_घोषित CONFIG_X86_32
	/* Cyrix III family needs CX8 & PGE explicitly enabled. */
	अगर (c->x86_model >= 6 && c->x86_model <= 13) अणु
		rdmsr(MSR_VIA_FCR, lo, hi);
		lo |= (1<<1 | 1<<7);
		wrmsr(MSR_VIA_FCR, lo, hi);
		set_cpu_cap(c, X86_FEATURE_CX8);
	पूर्ण

	/* Beक्रमe Nehemiah, the C3's had 3dNOW! */
	अगर (c->x86_model >= 6 && c->x86_model < 9)
		set_cpu_cap(c, X86_FEATURE_3DNOW);
#पूर्ण_अगर
	अगर (c->x86 == 0x6 && c->x86_model >= 0xf) अणु
		c->x86_cache_alignment = c->x86_clflush_size * 2;
		set_cpu_cap(c, X86_FEATURE_REP_GOOD);
	पूर्ण

	अगर (c->x86 >= 7)
		set_cpu_cap(c, X86_FEATURE_REP_GOOD);
पूर्ण

क्रमागत अणु
		ECX8		= 1<<1,
		EIERRINT	= 1<<2,
		DPM		= 1<<3,
		DMCE		= 1<<4,
		DSTPCLK		= 1<<5,
		ELINEAR		= 1<<6,
		DSMC		= 1<<7,
		DTLOCK		= 1<<8,
		EDCTLB		= 1<<8,
		EMMX		= 1<<9,
		DPDC		= 1<<11,
		EBRPRED		= 1<<12,
		DIC		= 1<<13,
		DDC		= 1<<14,
		DNA		= 1<<15,
		ERETSTK		= 1<<16,
		E2MMX		= 1<<19,
		EAMD3D		= 1<<20,
पूर्ण;

अटल व्योम early_init_centaur(काष्ठा cpuinfo_x86 *c)
अणु
#अगर_घोषित CONFIG_X86_32
	/* Emulate MTRRs using Centaur's MCR. */
	अगर (c->x86 == 5)
		set_cpu_cap(c, X86_FEATURE_CENTAUR_MCR);
#पूर्ण_अगर
	अगर ((c->x86 == 6 && c->x86_model >= 0xf) ||
	    (c->x86 >= 7))
		set_cpu_cap(c, X86_FEATURE_CONSTANT_TSC);

#अगर_घोषित CONFIG_X86_64
	set_cpu_cap(c, X86_FEATURE_SYSENTER32);
#पूर्ण_अगर
	अगर (c->x86_घातer & (1 << 8)) अणु
		set_cpu_cap(c, X86_FEATURE_CONSTANT_TSC);
		set_cpu_cap(c, X86_FEATURE_NONSTOP_TSC);
	पूर्ण
पूर्ण

अटल व्योम init_centaur(काष्ठा cpuinfo_x86 *c)
अणु
#अगर_घोषित CONFIG_X86_32
	अक्षर *name;
	u32  fcr_set = 0;
	u32  fcr_clr = 0;
	u32  lo, hi, newlo;
	u32  aa, bb, cc, dd;

	/*
	 * Bit 31 in normal CPUID used क्रम nonstandard 3DNow ID;
	 * 3DNow is IDd by bit 31 in extended CPUID (1*32+31) anyway
	 */
	clear_cpu_cap(c, 0*32+31);
#पूर्ण_अगर
	early_init_centaur(c);
	init_पूर्णांकel_cacheinfo(c);
	detect_num_cpu_cores(c);
#अगर_घोषित CONFIG_X86_32
	detect_ht(c);
#पूर्ण_अगर

	अगर (c->cpuid_level > 9) अणु
		अचिन्हित पूर्णांक eax = cpuid_eax(10);

		/*
		 * Check क्रम version and the number of counters
		 * Version(eax[7:0]) can't be 0;
		 * Counters(eax[15:8]) should be greater than 1;
		 */
		अगर ((eax & 0xff) && (((eax >> 8) & 0xff) > 1))
			set_cpu_cap(c, X86_FEATURE_ARCH_PERFMON);
	पूर्ण

#अगर_घोषित CONFIG_X86_32
	अगर (c->x86 == 5) अणु
		चयन (c->x86_model) अणु
		हाल 4:
			name = "C6";
			fcr_set = ECX8|DSMC|EDCTLB|EMMX|ERETSTK;
			fcr_clr = DPDC;
			pr_notice("Disabling bugged TSC.\n");
			clear_cpu_cap(c, X86_FEATURE_TSC);
			अवरोध;
		हाल 8:
			चयन (c->x86_stepping) अणु
			शेष:
			name = "2";
				अवरोध;
			हाल 7 ... 9:
				name = "2A";
				अवरोध;
			हाल 10 ... 15:
				name = "2B";
				अवरोध;
			पूर्ण
			fcr_set = ECX8|DSMC|DTLOCK|EMMX|EBRPRED|ERETSTK|
				  E2MMX|EAMD3D;
			fcr_clr = DPDC;
			अवरोध;
		हाल 9:
			name = "3";
			fcr_set = ECX8|DSMC|DTLOCK|EMMX|EBRPRED|ERETSTK|
				  E2MMX|EAMD3D;
			fcr_clr = DPDC;
			अवरोध;
		शेष:
			name = "??";
		पूर्ण

		rdmsr(MSR_IDT_FCR1, lo, hi);
		newlo = (lo|fcr_set) & (~fcr_clr);

		अगर (newlo != lo) अणु
			pr_info("Centaur FCR was 0x%X now 0x%X\n",
				lo, newlo);
			wrmsr(MSR_IDT_FCR1, newlo, hi);
		पूर्ण अन्यथा अणु
			pr_info("Centaur FCR is 0x%X\n", lo);
		पूर्ण
		/* Emulate MTRRs using Centaur's MCR. */
		set_cpu_cap(c, X86_FEATURE_CENTAUR_MCR);
		/* Report CX8 */
		set_cpu_cap(c, X86_FEATURE_CX8);
		/* Set 3DNow! on Winchip 2 and above. */
		अगर (c->x86_model >= 8)
			set_cpu_cap(c, X86_FEATURE_3DNOW);
		/* See अगर we can find out some more. */
		अगर (cpuid_eax(0x80000000) >= 0x80000005) अणु
			/* Yes, we can. */
			cpuid(0x80000005, &aa, &bb, &cc, &dd);
			/* Add L1 data and code cache sizes. */
			c->x86_cache_size = (cc>>24)+(dd>>24);
		पूर्ण
		प्र_लिखो(c->x86_model_id, "WinChip %s", name);
	पूर्ण
#पूर्ण_अगर
	अगर (c->x86 == 6 || c->x86 >= 7)
		init_c3(c);
#अगर_घोषित CONFIG_X86_64
	set_cpu_cap(c, X86_FEATURE_LFENCE_RDTSC);
#पूर्ण_अगर

	init_ia32_feat_ctl(c);
पूर्ण

#अगर_घोषित CONFIG_X86_32
अटल अचिन्हित पूर्णांक
centaur_size_cache(काष्ठा cpuinfo_x86 *c, अचिन्हित पूर्णांक size)
अणु
	/* VIA C3 CPUs (670-68F) need further shअगरting. */
	अगर ((c->x86 == 6) && ((c->x86_model == 7) || (c->x86_model == 8)))
		size >>= 8;

	/*
	 * There's also an erratum in Nehemiah stepping 1, which
	 * वापसs '65KB' instead of '64KB'
	 *  - Note, it seems this may only be in engineering samples.
	 */
	अगर ((c->x86 == 6) && (c->x86_model == 9) &&
				(c->x86_stepping == 1) && (size == 65))
		size -= 1;
	वापस size;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा cpu_dev centaur_cpu_dev = अणु
	.c_venकरोr	= "Centaur",
	.c_ident	= अणु "CentaurHauls" पूर्ण,
	.c_early_init	= early_init_centaur,
	.c_init		= init_centaur,
#अगर_घोषित CONFIG_X86_32
	.legacy_cache_size = centaur_size_cache,
#पूर्ण_अगर
	.c_x86_venकरोr	= X86_VENDOR_CENTAUR,
पूर्ण;

cpu_dev_रेजिस्टर(centaur_cpu_dev);
