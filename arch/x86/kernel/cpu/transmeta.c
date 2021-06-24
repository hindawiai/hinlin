<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/msr.h>
#समावेश "cpu.h"

अटल व्योम early_init_transmeta(काष्ठा cpuinfo_x86 *c)
अणु
	u32 xlvl;

	/* Transmeta-defined flags: level 0x80860001 */
	xlvl = cpuid_eax(0x80860000);
	अगर ((xlvl & 0xffff0000) == 0x80860000) अणु
		अगर (xlvl >= 0x80860001)
			c->x86_capability[CPUID_8086_0001_EDX] = cpuid_edx(0x80860001);
	पूर्ण
पूर्ण

अटल व्योम init_transmeta(काष्ठा cpuinfo_x86 *c)
अणु
	अचिन्हित पूर्णांक cap_mask, uk, max, dummy;
	अचिन्हित पूर्णांक cms_rev1, cms_rev2;
	अचिन्हित पूर्णांक cpu_rev, cpu_freq = 0, cpu_flags, new_cpu_rev;
	अक्षर cpu_info[65];

	early_init_transmeta(c);

	cpu_detect_cache_sizes(c);

	/* Prपूर्णांक CMS and CPU revision */
	max = cpuid_eax(0x80860000);
	cpu_rev = 0;
	अगर (max >= 0x80860001) अणु
		cpuid(0x80860001, &dummy, &cpu_rev, &cpu_freq, &cpu_flags);
		अगर (cpu_rev != 0x02000000) अणु
			pr_info("CPU: Processor revision %u.%u.%u.%u, %u MHz\n",
				(cpu_rev >> 24) & 0xff,
				(cpu_rev >> 16) & 0xff,
				(cpu_rev >> 8) & 0xff,
				cpu_rev & 0xff,
				cpu_freq);
		पूर्ण
	पूर्ण
	अगर (max >= 0x80860002) अणु
		cpuid(0x80860002, &new_cpu_rev, &cms_rev1, &cms_rev2, &dummy);
		अगर (cpu_rev == 0x02000000) अणु
			pr_info("CPU: Processor revision %08X, %u MHz\n",
				new_cpu_rev, cpu_freq);
		पूर्ण
		pr_info("CPU: Code Morphing Software revision %u.%u.%u-%u-%u\n",
		       (cms_rev1 >> 24) & 0xff,
		       (cms_rev1 >> 16) & 0xff,
		       (cms_rev1 >> 8) & 0xff,
		       cms_rev1 & 0xff,
		       cms_rev2);
	पूर्ण
	अगर (max >= 0x80860006) अणु
		cpuid(0x80860003,
		      (व्योम *)&cpu_info[0],
		      (व्योम *)&cpu_info[4],
		      (व्योम *)&cpu_info[8],
		      (व्योम *)&cpu_info[12]);
		cpuid(0x80860004,
		      (व्योम *)&cpu_info[16],
		      (व्योम *)&cpu_info[20],
		      (व्योम *)&cpu_info[24],
		      (व्योम *)&cpu_info[28]);
		cpuid(0x80860005,
		      (व्योम *)&cpu_info[32],
		      (व्योम *)&cpu_info[36],
		      (व्योम *)&cpu_info[40],
		      (व्योम *)&cpu_info[44]);
		cpuid(0x80860006,
		      (व्योम *)&cpu_info[48],
		      (व्योम *)&cpu_info[52],
		      (व्योम *)&cpu_info[56],
		      (व्योम *)&cpu_info[60]);
		cpu_info[64] = '\0';
		pr_info("CPU: %s\n", cpu_info);
	पूर्ण

	/* Unhide possibly hidden capability flags */
	rdmsr(0x80860004, cap_mask, uk);
	wrmsr(0x80860004, ~0, uk);
	c->x86_capability[CPUID_1_EDX] = cpuid_edx(0x00000001);
	wrmsr(0x80860004, cap_mask, uk);

	/* All Transmeta CPUs have a स्थिरant TSC */
	set_cpu_cap(c, X86_FEATURE_CONSTANT_TSC);

#अगर_घोषित CONFIG_SYSCTL
	/*
	 * अक्रमomize_va_space slows us करोwn enormously;
	 * it probably triggers retranslation of x86->native bytecode
	 */
	अक्रमomize_va_space = 0;
#पूर्ण_अगर
पूर्ण

अटल स्थिर काष्ठा cpu_dev transmeta_cpu_dev = अणु
	.c_venकरोr	= "Transmeta",
	.c_ident	= अणु "GenuineTMx86", "TransmetaCPU" पूर्ण,
	.c_early_init	= early_init_transmeta,
	.c_init		= init_transmeta,
	.c_x86_venकरोr	= X86_VENDOR_TRANSMETA,
पूर्ण;

cpu_dev_रेजिस्टर(transmeta_cpu_dev);
