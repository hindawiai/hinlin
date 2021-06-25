<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/sched.h>
#समावेश <linux/sched/घड़ी.h>

#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cpufeature.h>

#समावेश "cpu.h"

#घोषणा MSR_ZHAOXIN_FCR57 0x00001257

#घोषणा ACE_PRESENT	(1 << 6)
#घोषणा ACE_ENABLED	(1 << 7)
#घोषणा ACE_FCR		(1 << 7)	/* MSR_ZHAOXIN_FCR */

#घोषणा RNG_PRESENT	(1 << 2)
#घोषणा RNG_ENABLED	(1 << 3)
#घोषणा RNG_ENABLE	(1 << 8)	/* MSR_ZHAOXIN_RNG */

अटल व्योम init_zhaoxin_cap(काष्ठा cpuinfo_x86 *c)
अणु
	u32  lo, hi;

	/* Test क्रम Extended Feature Flags presence */
	अगर (cpuid_eax(0xC0000000) >= 0xC0000001) अणु
		u32 पंचांगp = cpuid_edx(0xC0000001);

		/* Enable ACE unit, अगर present and disabled */
		अगर ((पंचांगp & (ACE_PRESENT | ACE_ENABLED)) == ACE_PRESENT) अणु
			rdmsr(MSR_ZHAOXIN_FCR57, lo, hi);
			/* Enable ACE unit */
			lo |= ACE_FCR;
			wrmsr(MSR_ZHAOXIN_FCR57, lo, hi);
			pr_info("CPU: Enabled ACE h/w crypto\n");
		पूर्ण

		/* Enable RNG unit, अगर present and disabled */
		अगर ((पंचांगp & (RNG_PRESENT | RNG_ENABLED)) == RNG_PRESENT) अणु
			rdmsr(MSR_ZHAOXIN_FCR57, lo, hi);
			/* Enable RNG unit */
			lo |= RNG_ENABLE;
			wrmsr(MSR_ZHAOXIN_FCR57, lo, hi);
			pr_info("CPU: Enabled h/w RNG\n");
		पूर्ण

		/*
		 * Store Extended Feature Flags as word 5 of the CPU
		 * capability bit array
		 */
		c->x86_capability[CPUID_C000_0001_EDX] = cpuid_edx(0xC0000001);
	पूर्ण

	अगर (c->x86 >= 0x6)
		set_cpu_cap(c, X86_FEATURE_REP_GOOD);
पूर्ण

अटल व्योम early_init_zhaoxin(काष्ठा cpuinfo_x86 *c)
अणु
	अगर (c->x86 >= 0x6)
		set_cpu_cap(c, X86_FEATURE_CONSTANT_TSC);
#अगर_घोषित CONFIG_X86_64
	set_cpu_cap(c, X86_FEATURE_SYSENTER32);
#पूर्ण_अगर
	अगर (c->x86_घातer & (1 << 8)) अणु
		set_cpu_cap(c, X86_FEATURE_CONSTANT_TSC);
		set_cpu_cap(c, X86_FEATURE_NONSTOP_TSC);
	पूर्ण

	अगर (c->cpuid_level >= 0x00000001) अणु
		u32 eax, ebx, ecx, edx;

		cpuid(0x00000001, &eax, &ebx, &ecx, &edx);
		/*
		 * If HTT (EDX[28]) is set EBX[16:23] contain the number of
		 * apicids which are reserved per package. Store the resulting
		 * shअगरt value क्रम the package management code.
		 */
		अगर (edx & (1U << 28))
			c->x86_coreid_bits = get_count_order((ebx >> 16) & 0xff);
	पूर्ण

पूर्ण

अटल व्योम init_zhaoxin(काष्ठा cpuinfo_x86 *c)
अणु
	early_init_zhaoxin(c);
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

	अगर (c->x86 >= 0x6)
		init_zhaoxin_cap(c);
#अगर_घोषित CONFIG_X86_64
	set_cpu_cap(c, X86_FEATURE_LFENCE_RDTSC);
#पूर्ण_अगर

	init_ia32_feat_ctl(c);
पूर्ण

#अगर_घोषित CONFIG_X86_32
अटल अचिन्हित पूर्णांक
zhaoxin_size_cache(काष्ठा cpuinfo_x86 *c, अचिन्हित पूर्णांक size)
अणु
	वापस size;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा cpu_dev zhaoxin_cpu_dev = अणु
	.c_venकरोr	= "zhaoxin",
	.c_ident	= अणु "  Shanghai  " पूर्ण,
	.c_early_init	= early_init_zhaoxin,
	.c_init		= init_zhaoxin,
#अगर_घोषित CONFIG_X86_32
	.legacy_cache_size = zhaoxin_size_cache,
#पूर्ण_अगर
	.c_x86_venकरोr	= X86_VENDOR_ZHAOXIN,
पूर्ण;

cpu_dev_रेजिस्टर(zhaoxin_cpu_dev);
