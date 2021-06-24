<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Processor capabilities determination functions.
 *
 * Copyright (C) xxxx  the Anonymous
 * Copyright (C) 1994 - 2006 Ralf Baechle
 * Copyright (C) 2003, 2004  Maciej W. Rozycki
 * Copyright (C) 2001, 2004, 2011, 2012	 MIPS Technologies, Inc.
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/smp.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/export.h>

#समावेश <यंत्र/bugs.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cpu-features.h>
#समावेश <यंत्र/cpu-type.h>
#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/elf.h>
#समावेश <यंत्र/traps.h>

#समावेश "fpu-probe.h"

/* Hardware capabilities */
अचिन्हित पूर्णांक elf_hwcap __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(elf_hwcap);

व्योम __init check_bugs32(व्योम)
अणु

पूर्ण

/*
 * Probe whether cpu has config रेजिस्टर by trying to play with
 * alternate cache bit and see whether it matters.
 * It's used by cpu_probe to distinguish between R3000A and R3081.
 */
अटल अंतरभूत पूर्णांक cpu_has_confreg(व्योम)
अणु
#अगर_घोषित CONFIG_CPU_R3000
	बाह्य अचिन्हित दीर्घ r3k_cache_size(अचिन्हित दीर्घ);
	अचिन्हित दीर्घ size1, size2;
	अचिन्हित दीर्घ cfg = पढ़ो_c0_conf();

	size1 = r3k_cache_size(ST0_ISC);
	ग_लिखो_c0_conf(cfg ^ R30XX_CONF_AC);
	size2 = r3k_cache_size(ST0_ISC);
	ग_लिखो_c0_conf(cfg);
	वापस size1 != size2;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम set_elf_platक्रमm(पूर्णांक cpu, स्थिर अक्षर *plat)
अणु
	अगर (cpu == 0)
		__elf_platक्रमm = plat;
पूर्ण

स्थिर अक्षर *__cpu_name[NR_CPUS];
स्थिर अक्षर *__elf_platक्रमm;
स्थिर अक्षर *__elf_base_platक्रमm;

व्योम cpu_probe(व्योम)
अणु
	काष्ठा cpuinfo_mips *c = &current_cpu_data;
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	/*
	 * Set a शेष elf platक्रमm, cpu probe may later
	 * overग_लिखो it with a more precise value
	 */
	set_elf_platक्रमm(cpu, "mips");

	c->processor_id = PRID_IMP_UNKNOWN;
	c->fpu_id	= FPIR_IMP_NONE;
	c->cputype	= CPU_UNKNOWN;
	c->ग_लिखोcombine = _CACHE_UNCACHED;

	c->fpu_csr31	= FPU_CSR_RN;
	c->fpu_msk31	= FPU_CSR_RSVD | FPU_CSR_ABS2008 | FPU_CSR_न_अंक2008 |
			  FPU_CSR_CONDX | FPU_CSR_FS;

	c->srsets = 1;

	c->processor_id = पढ़ो_c0_prid();
	चयन (c->processor_id & (PRID_COMP_MASK | PRID_IMP_MASK)) अणु
	हाल PRID_COMP_LEGACY | PRID_IMP_R2000:
		c->cputype = CPU_R2000;
		__cpu_name[cpu] = "R2000";
		c->options = MIPS_CPU_TLB | MIPS_CPU_3K_CACHE |
			     MIPS_CPU_NOFPUEX;
		अगर (__cpu_has_fpu())
			c->options |= MIPS_CPU_FPU;
		c->tlbsize = 64;
		अवरोध;
	हाल PRID_COMP_LEGACY | PRID_IMP_R3000:
		अगर ((c->processor_id & PRID_REV_MASK) == PRID_REV_R3000A) अणु
			अगर (cpu_has_confreg()) अणु
				c->cputype = CPU_R3081E;
				__cpu_name[cpu] = "R3081";
			पूर्ण अन्यथा अणु
				c->cputype = CPU_R3000A;
				__cpu_name[cpu] = "R3000A";
			पूर्ण
		पूर्ण अन्यथा अणु
			c->cputype = CPU_R3000;
			__cpu_name[cpu] = "R3000";
		पूर्ण
		c->options = MIPS_CPU_TLB | MIPS_CPU_3K_CACHE |
			     MIPS_CPU_NOFPUEX;
		अगर (__cpu_has_fpu())
			c->options |= MIPS_CPU_FPU;
		c->tlbsize = 64;
		अवरोध;
	हाल PRID_COMP_LEGACY | PRID_IMP_TX39:
		c->options = MIPS_CPU_TLB | MIPS_CPU_TX39_CACHE;

		अगर ((c->processor_id & 0xf0) == (PRID_REV_TX3927 & 0xf0)) अणु
			c->cputype = CPU_TX3927;
			__cpu_name[cpu] = "TX3927";
			c->tlbsize = 64;
		पूर्ण अन्यथा अणु
			चयन (c->processor_id & PRID_REV_MASK) अणु
			हाल PRID_REV_TX3912:
				c->cputype = CPU_TX3912;
				__cpu_name[cpu] = "TX3912";
				c->tlbsize = 32;
				अवरोध;
			हाल PRID_REV_TX3922:
				c->cputype = CPU_TX3922;
				__cpu_name[cpu] = "TX3922";
				c->tlbsize = 64;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

	BUG_ON(!__cpu_name[cpu]);
	BUG_ON(c->cputype == CPU_UNKNOWN);

	/*
	 * Platक्रमm code can क्रमce the cpu type to optimize code
	 * generation. In that हाल be sure the cpu type is correctly
	 * manually setup otherwise it could trigger some nasty bugs.
	 */
	BUG_ON(current_cpu_type() != c->cputype);

	अगर (mips_fpu_disabled)
		c->options &= ~MIPS_CPU_FPU;

	अगर (c->options & MIPS_CPU_FPU)
		cpu_set_fpu_opts(c);
	अन्यथा
		cpu_set_nofpu_opts(c);

	reserve_exception_space(0, 0x400);
पूर्ण

व्योम cpu_report(व्योम)
अणु
	काष्ठा cpuinfo_mips *c = &current_cpu_data;

	pr_info("CPU%d revision is: %08x (%s)\n",
		smp_processor_id(), c->processor_id, cpu_name_string());
	अगर (c->options & MIPS_CPU_FPU)
		pr_info("FPU revision is: %08x\n", c->fpu_id);
पूर्ण
