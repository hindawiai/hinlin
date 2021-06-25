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
#समावेश <यंत्र/mipsmtregs.h>
#समावेश <यंत्र/msa.h>
#समावेश <यंत्र/watch.h>
#समावेश <यंत्र/elf.h>
#समावेश <यंत्र/pgtable-bits.h>
#समावेश <यंत्र/spram.h>
#समावेश <यंत्र/traps.h>
#समावेश <linux/uaccess.h>

#समावेश "fpu-probe.h"

#समावेश <यंत्र/mach-loongson64/cpucfg-emul.h>

/* Hardware capabilities */
अचिन्हित पूर्णांक elf_hwcap __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(elf_hwcap);

अटल अंतरभूत अचिन्हित दीर्घ cpu_get_msa_id(व्योम)
अणु
	अचिन्हित दीर्घ status, msa_id;

	status = पढ़ो_c0_status();
	__enable_fpu(FPU_64BIT);
	enable_msa();
	msa_id = पढ़ो_msa_ir();
	disable_msa();
	ग_लिखो_c0_status(status);
	वापस msa_id;
पूर्ण

अटल पूर्णांक mips_dsp_disabled;

अटल पूर्णांक __init dsp_disable(अक्षर *s)
अणु
	cpu_data[0].ases &= ~(MIPS_ASE_DSP | MIPS_ASE_DSP2P);
	mips_dsp_disabled = 1;

	वापस 1;
पूर्ण

__setup("nodsp", dsp_disable);

अटल पूर्णांक mips_htw_disabled;

अटल पूर्णांक __init htw_disable(अक्षर *s)
अणु
	mips_htw_disabled = 1;
	cpu_data[0].options &= ~MIPS_CPU_HTW;
	ग_लिखो_c0_pwctl(पढ़ो_c0_pwctl() &
		       ~(1 << MIPS_PWCTL_PWEN_SHIFT));

	वापस 1;
पूर्ण

__setup("nohtw", htw_disable);

अटल पूर्णांक mips_ftlb_disabled;
अटल पूर्णांक mips_has_ftlb_configured;

क्रमागत ftlb_flags अणु
	FTLB_EN		= 1 << 0,
	FTLB_SET_PROB	= 1 << 1,
पूर्ण;

अटल पूर्णांक set_ftlb_enable(काष्ठा cpuinfo_mips *c, क्रमागत ftlb_flags flags);

अटल पूर्णांक __init ftlb_disable(अक्षर *s)
अणु
	अचिन्हित पूर्णांक config4, mmuextdef;

	/*
	 * If the core hasn't करोne any FTLB configuration, there is nothing
	 * क्रम us to करो here.
	 */
	अगर (!mips_has_ftlb_configured)
		वापस 1;

	/* Disable it in the boot cpu */
	अगर (set_ftlb_enable(&cpu_data[0], 0)) अणु
		pr_warn("Can't turn FTLB off\n");
		वापस 1;
	पूर्ण

	config4 = पढ़ो_c0_config4();

	/* Check that FTLB has been disabled */
	mmuextdef = config4 & MIPS_CONF4_MMUEXTDEF;
	/* MMUSIZEEXT == VTLB ON, FTLB OFF */
	अगर (mmuextdef == MIPS_CONF4_MMUEXTDEF_FTLBSIZEEXT) अणु
		/* This should never happen */
		pr_warn("FTLB could not be disabled!\n");
		वापस 1;
	पूर्ण

	mips_ftlb_disabled = 1;
	mips_has_ftlb_configured = 0;

	/*
	 * noftlb is मुख्यly used क्रम debug purposes so prपूर्णांक
	 * an inक्रमmative message instead of using pr_debug()
	 */
	pr_info("FTLB has been disabled\n");

	/*
	 * Some of these bits are duplicated in the decode_config4.
	 * MIPS_CONF4_MMUEXTDEF_MMUSIZEEXT is the only possible हाल
	 * once FTLB has been disabled so unकरो what decode_config4 did.
	 */
	cpu_data[0].tlbsize -= cpu_data[0].tlbsizeftlbways *
			       cpu_data[0].tlbsizeftlbsets;
	cpu_data[0].tlbsizeftlbsets = 0;
	cpu_data[0].tlbsizeftlbways = 0;

	वापस 1;
पूर्ण

__setup("noftlb", ftlb_disable);

/*
 * Check अगर the CPU has per tc perf counters
 */
अटल अंतरभूत व्योम cpu_set_mt_per_tc_perf(काष्ठा cpuinfo_mips *c)
अणु
	अगर (पढ़ो_c0_config7() & MTI_CONF7_PTC)
		c->options |= MIPS_CPU_MT_PER_TC_PERF_COUNTERS;
पूर्ण

अटल अंतरभूत व्योम check_errata(व्योम)
अणु
	काष्ठा cpuinfo_mips *c = &current_cpu_data;

	चयन (current_cpu_type()) अणु
	हाल CPU_34K:
		/*
		 * Erratum "RPS May Cause Incorrect Instruction Execution"
		 * This code only handles VPE0, any SMP/RTOS code
		 * making use of VPE1 will be responsable क्रम that VPE.
		 */
		अगर ((c->processor_id & PRID_REV_MASK) <= PRID_REV_34K_V1_0_2)
			ग_लिखो_c0_config7(पढ़ो_c0_config7() | MIPS_CONF7_RPS);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम __init check_bugs32(व्योम)
अणु
	check_errata();
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

अटल अंतरभूत व्योम set_elf_base_platक्रमm(स्थिर अक्षर *plat)
अणु
	अगर (__elf_base_platक्रमm == शून्य) अणु
		__elf_base_platक्रमm = plat;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cpu_probe_vmbits(काष्ठा cpuinfo_mips *c)
अणु
#अगर_घोषित __NEED_VMBITS_PROBE
	ग_लिखो_c0_entryhi(0x3fffffffffffe000ULL);
	back_to_back_c0_hazard();
	c->vmbits = fls64(पढ़ो_c0_entryhi() & 0x3fffffffffffe000ULL);
#पूर्ण_अगर
पूर्ण

अटल व्योम set_isa(काष्ठा cpuinfo_mips *c, अचिन्हित पूर्णांक isa)
अणु
	चयन (isa) अणु
	हाल MIPS_CPU_ISA_M64R5:
		c->isa_level |= MIPS_CPU_ISA_M32R5 | MIPS_CPU_ISA_M64R5;
		set_elf_base_platक्रमm("mips64r5");
		fallthrough;
	हाल MIPS_CPU_ISA_M64R2:
		c->isa_level |= MIPS_CPU_ISA_M32R2 | MIPS_CPU_ISA_M64R2;
		set_elf_base_platक्रमm("mips64r2");
		fallthrough;
	हाल MIPS_CPU_ISA_M64R1:
		c->isa_level |= MIPS_CPU_ISA_M32R1 | MIPS_CPU_ISA_M64R1;
		set_elf_base_platक्रमm("mips64");
		fallthrough;
	हाल MIPS_CPU_ISA_V:
		c->isa_level |= MIPS_CPU_ISA_V;
		set_elf_base_platक्रमm("mips5");
		fallthrough;
	हाल MIPS_CPU_ISA_IV:
		c->isa_level |= MIPS_CPU_ISA_IV;
		set_elf_base_platक्रमm("mips4");
		fallthrough;
	हाल MIPS_CPU_ISA_III:
		c->isa_level |= MIPS_CPU_ISA_II | MIPS_CPU_ISA_III;
		set_elf_base_platक्रमm("mips3");
		अवरोध;

	/* R6 incompatible with everything अन्यथा */
	हाल MIPS_CPU_ISA_M64R6:
		c->isa_level |= MIPS_CPU_ISA_M32R6 | MIPS_CPU_ISA_M64R6;
		set_elf_base_platक्रमm("mips64r6");
		fallthrough;
	हाल MIPS_CPU_ISA_M32R6:
		c->isa_level |= MIPS_CPU_ISA_M32R6;
		set_elf_base_platक्रमm("mips32r6");
		/* Break here so we करोn't add incompatible ISAs */
		अवरोध;
	हाल MIPS_CPU_ISA_M32R5:
		c->isa_level |= MIPS_CPU_ISA_M32R5;
		set_elf_base_platक्रमm("mips32r5");
		fallthrough;
	हाल MIPS_CPU_ISA_M32R2:
		c->isa_level |= MIPS_CPU_ISA_M32R2;
		set_elf_base_platक्रमm("mips32r2");
		fallthrough;
	हाल MIPS_CPU_ISA_M32R1:
		c->isa_level |= MIPS_CPU_ISA_M32R1;
		set_elf_base_platक्रमm("mips32");
		fallthrough;
	हाल MIPS_CPU_ISA_II:
		c->isa_level |= MIPS_CPU_ISA_II;
		set_elf_base_platक्रमm("mips2");
		अवरोध;
	पूर्ण
पूर्ण

अटल अक्षर unknown_isa[] = KERN_ERR \
	"Unsupported ISA type, c0.config0: %d.";

अटल अचिन्हित पूर्णांक calculate_ftlb_probability(काष्ठा cpuinfo_mips *c)
अणु

	अचिन्हित पूर्णांक probability = c->tlbsize / c->tlbsizevtlb;

	/*
	 * 0 = All TLBWR inकाष्ठाions go to FTLB
	 * 1 = 15:1: For every 16 TBLWR inकाष्ठाions, 15 go to the
	 * FTLB and 1 goes to the VTLB.
	 * 2 = 7:1: As above with 7:1 ratio.
	 * 3 = 3:1: As above with 3:1 ratio.
	 *
	 * Use the linear midpoपूर्णांक as the probability threshold.
	 */
	अगर (probability >= 12)
		वापस 1;
	अन्यथा अगर (probability >= 6)
		वापस 2;
	अन्यथा
		/*
		 * So FTLB is less than 4 बार bigger than VTLB.
		 * A 3:1 ratio can still be useful though.
		 */
		वापस 3;
पूर्ण

अटल पूर्णांक set_ftlb_enable(काष्ठा cpuinfo_mips *c, क्रमागत ftlb_flags flags)
अणु
	अचिन्हित पूर्णांक config;

	/* It's implementation dependent how the FTLB can be enabled */
	चयन (c->cputype) अणु
	हाल CPU_PROAPTIV:
	हाल CPU_P5600:
	हाल CPU_P6600:
		/* proAptiv & related cores use Config6 to enable the FTLB */
		config = पढ़ो_c0_config6();

		अगर (flags & FTLB_EN)
			config |= MTI_CONF6_FTLBEN;
		अन्यथा
			config &= ~MTI_CONF6_FTLBEN;

		अगर (flags & FTLB_SET_PROB) अणु
			config &= ~(3 << MTI_CONF6_FTLBP_SHIFT);
			config |= calculate_ftlb_probability(c)
				  << MTI_CONF6_FTLBP_SHIFT;
		पूर्ण

		ग_लिखो_c0_config6(config);
		back_to_back_c0_hazard();
		अवरोध;
	हाल CPU_I6400:
	हाल CPU_I6500:
		/* There's no way to disable the FTLB */
		अगर (!(flags & FTLB_EN))
			वापस 1;
		वापस 0;
	हाल CPU_LOONGSON64:
		/* Flush ITLB, DTLB, VTLB and FTLB */
		ग_लिखो_c0_diag(LOONGSON_DIAG_ITLB | LOONGSON_DIAG_DTLB |
			      LOONGSON_DIAG_VTLB | LOONGSON_DIAG_FTLB);
		/* Loongson-3 cores use Config6 to enable the FTLB */
		config = पढ़ो_c0_config6();
		अगर (flags & FTLB_EN)
			/* Enable FTLB */
			ग_लिखो_c0_config6(config & ~LOONGSON_CONF6_FTLBDIS);
		अन्यथा
			/* Disable FTLB */
			ग_लिखो_c0_config6(config | LOONGSON_CONF6_FTLBDIS);
		अवरोध;
	शेष:
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mm_config(काष्ठा cpuinfo_mips *c)
अणु
	अचिन्हित पूर्णांक config0, update, mm;

	config0 = पढ़ो_c0_config();
	mm = config0 & MIPS_CONF_MM;

	/*
	 * It's implementation dependent what type of ग_लिखो-merge is supported
	 * and whether it can be enabled/disabled. If it is settable lets make
	 * the merging allowed by शेष. Some platक्रमms might have
	 * ग_लिखो-through caching unsupported. In this हाल just ignore the
	 * CP0.Config.MM bit field value.
	 */
	चयन (c->cputype) अणु
	हाल CPU_24K:
	हाल CPU_34K:
	हाल CPU_74K:
	हाल CPU_P5600:
	हाल CPU_P6600:
		c->options |= MIPS_CPU_MM_FULL;
		update = MIPS_CONF_MM_FULL;
		अवरोध;
	हाल CPU_1004K:
	हाल CPU_1074K:
	हाल CPU_INTERAPTIV:
	हाल CPU_PROAPTIV:
		mm = 0;
		fallthrough;
	शेष:
		update = 0;
		अवरोध;
	पूर्ण

	अगर (update) अणु
		config0 = (config0 & ~MIPS_CONF_MM) | update;
		ग_लिखो_c0_config(config0);
	पूर्ण अन्यथा अगर (mm == MIPS_CONF_MM_SYSAD) अणु
		c->options |= MIPS_CPU_MM_SYSAD;
	पूर्ण अन्यथा अगर (mm == MIPS_CONF_MM_FULL) अणु
		c->options |= MIPS_CPU_MM_FULL;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक decode_config0(काष्ठा cpuinfo_mips *c)
अणु
	अचिन्हित पूर्णांक config0;
	पूर्णांक isa, mt;

	config0 = पढ़ो_c0_config();

	/*
	 * Look क्रम Standard TLB or Dual VTLB and FTLB
	 */
	mt = config0 & MIPS_CONF_MT;
	अगर (mt == MIPS_CONF_MT_TLB)
		c->options |= MIPS_CPU_TLB;
	अन्यथा अगर (mt == MIPS_CONF_MT_FTLB)
		c->options |= MIPS_CPU_TLB | MIPS_CPU_FTLB;

	isa = (config0 & MIPS_CONF_AT) >> 13;
	चयन (isa) अणु
	हाल 0:
		चयन ((config0 & MIPS_CONF_AR) >> 10) अणु
		हाल 0:
			set_isa(c, MIPS_CPU_ISA_M32R1);
			अवरोध;
		हाल 1:
			set_isa(c, MIPS_CPU_ISA_M32R2);
			अवरोध;
		हाल 2:
			set_isa(c, MIPS_CPU_ISA_M32R6);
			अवरोध;
		शेष:
			जाओ unknown;
		पूर्ण
		अवरोध;
	हाल 2:
		चयन ((config0 & MIPS_CONF_AR) >> 10) अणु
		हाल 0:
			set_isa(c, MIPS_CPU_ISA_M64R1);
			अवरोध;
		हाल 1:
			set_isa(c, MIPS_CPU_ISA_M64R2);
			अवरोध;
		हाल 2:
			set_isa(c, MIPS_CPU_ISA_M64R6);
			अवरोध;
		शेष:
			जाओ unknown;
		पूर्ण
		अवरोध;
	शेष:
		जाओ unknown;
	पूर्ण

	वापस config0 & MIPS_CONF_M;

unknown:
	panic(unknown_isa, config0);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक decode_config1(काष्ठा cpuinfo_mips *c)
अणु
	अचिन्हित पूर्णांक config1;

	config1 = पढ़ो_c0_config1();

	अगर (config1 & MIPS_CONF1_MD)
		c->ases |= MIPS_ASE_MDMX;
	अगर (config1 & MIPS_CONF1_PC)
		c->options |= MIPS_CPU_PERF;
	अगर (config1 & MIPS_CONF1_WR)
		c->options |= MIPS_CPU_WATCH;
	अगर (config1 & MIPS_CONF1_CA)
		c->ases |= MIPS_ASE_MIPS16;
	अगर (config1 & MIPS_CONF1_EP)
		c->options |= MIPS_CPU_EJTAG;
	अगर (config1 & MIPS_CONF1_FP) अणु
		c->options |= MIPS_CPU_FPU;
		c->options |= MIPS_CPU_32FPR;
	पूर्ण
	अगर (cpu_has_tlb) अणु
		c->tlbsize = ((config1 & MIPS_CONF1_TLBS) >> 25) + 1;
		c->tlbsizevtlb = c->tlbsize;
		c->tlbsizeftlbsets = 0;
	पूर्ण

	वापस config1 & MIPS_CONF_M;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक decode_config2(काष्ठा cpuinfo_mips *c)
अणु
	अचिन्हित पूर्णांक config2;

	config2 = पढ़ो_c0_config2();

	अगर (config2 & MIPS_CONF2_SL)
		c->scache.flags &= ~MIPS_CACHE_NOT_PRESENT;

	वापस config2 & MIPS_CONF_M;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक decode_config3(काष्ठा cpuinfo_mips *c)
अणु
	अचिन्हित पूर्णांक config3;

	config3 = पढ़ो_c0_config3();

	अगर (config3 & MIPS_CONF3_SM) अणु
		c->ases |= MIPS_ASE_SMARTMIPS;
		c->options |= MIPS_CPU_RIXI | MIPS_CPU_CTXTC;
	पूर्ण
	अगर (config3 & MIPS_CONF3_RXI)
		c->options |= MIPS_CPU_RIXI;
	अगर (config3 & MIPS_CONF3_CTXTC)
		c->options |= MIPS_CPU_CTXTC;
	अगर (config3 & MIPS_CONF3_DSP)
		c->ases |= MIPS_ASE_DSP;
	अगर (config3 & MIPS_CONF3_DSP2P) अणु
		c->ases |= MIPS_ASE_DSP2P;
		अगर (cpu_has_mips_r6)
			c->ases |= MIPS_ASE_DSP3;
	पूर्ण
	अगर (config3 & MIPS_CONF3_VINT)
		c->options |= MIPS_CPU_VINT;
	अगर (config3 & MIPS_CONF3_VEIC)
		c->options |= MIPS_CPU_VEIC;
	अगर (config3 & MIPS_CONF3_LPA)
		c->options |= MIPS_CPU_LPA;
	अगर (config3 & MIPS_CONF3_MT)
		c->ases |= MIPS_ASE_MIPSMT;
	अगर (config3 & MIPS_CONF3_ULRI)
		c->options |= MIPS_CPU_ULRI;
	अगर (config3 & MIPS_CONF3_ISA)
		c->options |= MIPS_CPU_MICROMIPS;
	अगर (config3 & MIPS_CONF3_VZ)
		c->ases |= MIPS_ASE_VZ;
	अगर (config3 & MIPS_CONF3_SC)
		c->options |= MIPS_CPU_SEGMENTS;
	अगर (config3 & MIPS_CONF3_BI)
		c->options |= MIPS_CPU_BADINSTR;
	अगर (config3 & MIPS_CONF3_BP)
		c->options |= MIPS_CPU_BADINSTRP;
	अगर (config3 & MIPS_CONF3_MSA)
		c->ases |= MIPS_ASE_MSA;
	अगर (config3 & MIPS_CONF3_PW) अणु
		c->htw_seq = 0;
		c->options |= MIPS_CPU_HTW;
	पूर्ण
	अगर (config3 & MIPS_CONF3_CDMM)
		c->options |= MIPS_CPU_CDMM;
	अगर (config3 & MIPS_CONF3_SP)
		c->options |= MIPS_CPU_SP;

	वापस config3 & MIPS_CONF_M;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक decode_config4(काष्ठा cpuinfo_mips *c)
अणु
	अचिन्हित पूर्णांक config4;
	अचिन्हित पूर्णांक newcf4;
	अचिन्हित पूर्णांक mmuextdef;
	अचिन्हित पूर्णांक ftlb_page = MIPS_CONF4_FTLBPAGESIZE;
	अचिन्हित दीर्घ asid_mask;

	config4 = पढ़ो_c0_config4();

	अगर (cpu_has_tlb) अणु
		अगर (((config4 & MIPS_CONF4_IE) >> 29) == 2)
			c->options |= MIPS_CPU_TLBINV;

		/*
		 * R6 has dropped the MMUExtDef field from config4.
		 * On R6 the fields always describe the FTLB, and only अगर it is
		 * present according to Config.MT.
		 */
		अगर (!cpu_has_mips_r6)
			mmuextdef = config4 & MIPS_CONF4_MMUEXTDEF;
		अन्यथा अगर (cpu_has_ftlb)
			mmuextdef = MIPS_CONF4_MMUEXTDEF_VTLBSIZEEXT;
		अन्यथा
			mmuextdef = 0;

		चयन (mmuextdef) अणु
		हाल MIPS_CONF4_MMUEXTDEF_MMUSIZEEXT:
			c->tlbsize += (config4 & MIPS_CONF4_MMUSIZEEXT) * 0x40;
			c->tlbsizevtlb = c->tlbsize;
			अवरोध;
		हाल MIPS_CONF4_MMUEXTDEF_VTLBSIZEEXT:
			c->tlbsizevtlb +=
				((config4 & MIPS_CONF4_VTLBSIZEEXT) >>
				  MIPS_CONF4_VTLBSIZEEXT_SHIFT) * 0x40;
			c->tlbsize = c->tlbsizevtlb;
			ftlb_page = MIPS_CONF4_VFTLBPAGESIZE;
			fallthrough;
		हाल MIPS_CONF4_MMUEXTDEF_FTLBSIZEEXT:
			अगर (mips_ftlb_disabled)
				अवरोध;
			newcf4 = (config4 & ~ftlb_page) |
				(page_size_ftlb(mmuextdef) <<
				 MIPS_CONF4_FTLBPAGESIZE_SHIFT);
			ग_लिखो_c0_config4(newcf4);
			back_to_back_c0_hazard();
			config4 = पढ़ो_c0_config4();
			अगर (config4 != newcf4) अणु
				pr_err("PAGE_SIZE 0x%lx is not supported by FTLB (config4=0x%x)\n",
				       PAGE_SIZE, config4);
				/* Switch FTLB off */
				set_ftlb_enable(c, 0);
				mips_ftlb_disabled = 1;
				अवरोध;
			पूर्ण
			c->tlbsizeftlbsets = 1 <<
				((config4 & MIPS_CONF4_FTLBSETS) >>
				 MIPS_CONF4_FTLBSETS_SHIFT);
			c->tlbsizeftlbways = ((config4 & MIPS_CONF4_FTLBWAYS) >>
					      MIPS_CONF4_FTLBWAYS_SHIFT) + 2;
			c->tlbsize += c->tlbsizeftlbways * c->tlbsizeftlbsets;
			mips_has_ftlb_configured = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	c->kscratch_mask = (config4 & MIPS_CONF4_KSCREXIST)
				>> MIPS_CONF4_KSCREXIST_SHIFT;

	asid_mask = MIPS_ENTRYHI_ASID;
	अगर (config4 & MIPS_CONF4_AE)
		asid_mask |= MIPS_ENTRYHI_ASIDX;
	set_cpu_asid_mask(c, asid_mask);

	/*
	 * Warn अगर the computed ASID mask करोesn't match the mask the kernel
	 * is built क्रम. This may indicate either a serious problem or an
	 * easy optimisation opportunity, but either way should be addressed.
	 */
	WARN_ON(asid_mask != cpu_asid_mask(c));

	वापस config4 & MIPS_CONF_M;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक decode_config5(काष्ठा cpuinfo_mips *c)
अणु
	अचिन्हित पूर्णांक config5, max_mmid_width;
	अचिन्हित दीर्घ asid_mask;

	config5 = पढ़ो_c0_config5();
	config5 &= ~(MIPS_CONF5_UFR | MIPS_CONF5_UFE);

	अगर (cpu_has_mips_r6) अणु
		अगर (!__builtin_स्थिरant_p(cpu_has_mmid) || cpu_has_mmid)
			config5 |= MIPS_CONF5_MI;
		अन्यथा
			config5 &= ~MIPS_CONF5_MI;
	पूर्ण

	ग_लिखो_c0_config5(config5);

	अगर (config5 & MIPS_CONF5_EVA)
		c->options |= MIPS_CPU_EVA;
	अगर (config5 & MIPS_CONF5_MRP)
		c->options |= MIPS_CPU_MAAR;
	अगर (config5 & MIPS_CONF5_LLB)
		c->options |= MIPS_CPU_RW_LLB;
	अगर (config5 & MIPS_CONF5_MVH)
		c->options |= MIPS_CPU_MVH;
	अगर (cpu_has_mips_r6 && (config5 & MIPS_CONF5_VP))
		c->options |= MIPS_CPU_VP;
	अगर (config5 & MIPS_CONF5_CA2)
		c->ases |= MIPS_ASE_MIPS16E2;

	अगर (config5 & MIPS_CONF5_CRCP)
		elf_hwcap |= HWCAP_MIPS_CRC32;

	अगर (cpu_has_mips_r6) अणु
		/* Ensure the ग_लिखो to config5 above takes effect */
		back_to_back_c0_hazard();

		/* Check whether we successfully enabled MMID support */
		config5 = पढ़ो_c0_config5();
		अगर (config5 & MIPS_CONF5_MI)
			c->options |= MIPS_CPU_MMID;

		/*
		 * Warn अगर we've hardcoded cpu_has_mmid to a value unsuitable
		 * क्रम the CPU we're running on, or अगर CPUs in an SMP प्रणाली
		 * have inconsistent MMID support.
		 */
		WARN_ON(!!cpu_has_mmid != !!(config5 & MIPS_CONF5_MI));

		अगर (cpu_has_mmid) अणु
			ग_लिखो_c0_memorymapid(~0ul);
			back_to_back_c0_hazard();
			asid_mask = पढ़ो_c0_memorymapid();

			/*
			 * We मुख्यtain a biपंचांगap to track MMID allocation, and
			 * need a sensible upper bound on the size of that
			 * biपंचांगap. The initial CPU with MMID support (I6500)
			 * supports 16 bit MMIDs, which gives us an 8KiB
			 * biपंचांगap. The architecture recommends that hardware
			 * support 32 bit MMIDs, which would give us a 512MiB
			 * biपंचांगap - that's too big in most हालs.
			 *
			 * Cap MMID width at 16 bits क्रम now & we can revisit
			 * this अगर & when hardware supports anything wider.
			 */
			max_mmid_width = 16;
			अगर (asid_mask > GENMASK(max_mmid_width - 1, 0)) अणु
				pr_info("Capping MMID width at %d bits",
					max_mmid_width);
				asid_mask = GENMASK(max_mmid_width - 1, 0);
			पूर्ण

			set_cpu_asid_mask(c, asid_mask);
		पूर्ण
	पूर्ण

	वापस config5 & MIPS_CONF_M;
पूर्ण

अटल व्योम decode_configs(काष्ठा cpuinfo_mips *c)
अणु
	पूर्णांक ok;

	/* MIPS32 or MIPS64 compliant CPU.  */
	c->options = MIPS_CPU_4KEX | MIPS_CPU_4K_CACHE | MIPS_CPU_COUNTER |
		     MIPS_CPU_DIVEC | MIPS_CPU_LLSC | MIPS_CPU_MCHECK;

	c->scache.flags = MIPS_CACHE_NOT_PRESENT;

	/* Enable FTLB अगर present and not disabled */
	set_ftlb_enable(c, mips_ftlb_disabled ? 0 : FTLB_EN);

	ok = decode_config0(c);			/* Read Config रेजिस्टरs.  */
	BUG_ON(!ok);				/* Arch spec violation!	 */
	अगर (ok)
		ok = decode_config1(c);
	अगर (ok)
		ok = decode_config2(c);
	अगर (ok)
		ok = decode_config3(c);
	अगर (ok)
		ok = decode_config4(c);
	अगर (ok)
		ok = decode_config5(c);

	/* Probe the EBase.WG bit */
	अगर (cpu_has_mips_r2_r6) अणु
		u64 ebase;
		अचिन्हित पूर्णांक status;

		/* अणुपढ़ो,ग_लिखोपूर्ण_c0_ebase_64() may be UNDEFINED prior to r6 */
		ebase = cpu_has_mips64r6 ? पढ़ो_c0_ebase_64()
					 : (s32)पढ़ो_c0_ebase();
		अगर (ebase & MIPS_EBASE_WG) अणु
			/* WG bit alपढ़ोy set, we can aव्योम the clumsy probe */
			c->options |= MIPS_CPU_EBASE_WG;
		पूर्ण अन्यथा अणु
			/* Its UNDEFINED to change EBase जबतक BEV=0 */
			status = पढ़ो_c0_status();
			ग_लिखो_c0_status(status | ST0_BEV);
			irq_enable_hazard();
			/*
			 * On pre-r6 cores, this may well clobber the upper bits
			 * of EBase. This is hard to aव्योम without potentially
			 * hitting UNDEFINED dm*c0 behaviour अगर EBase is 32-bit.
			 */
			अगर (cpu_has_mips64r6)
				ग_लिखो_c0_ebase_64(ebase | MIPS_EBASE_WG);
			अन्यथा
				ग_लिखो_c0_ebase(ebase | MIPS_EBASE_WG);
			back_to_back_c0_hazard();
			/* Restore BEV */
			ग_लिखो_c0_status(status);
			अगर (पढ़ो_c0_ebase() & MIPS_EBASE_WG) अणु
				c->options |= MIPS_CPU_EBASE_WG;
				ग_लिखो_c0_ebase(ebase);
			पूर्ण
		पूर्ण
	पूर्ण

	/* configure the FTLB ग_लिखो probability */
	set_ftlb_enable(c, (mips_ftlb_disabled ? 0 : FTLB_EN) | FTLB_SET_PROB);

	mips_probe_watch_रेजिस्टरs(c);

#अगर_अघोषित CONFIG_MIPS_CPS
	अगर (cpu_has_mips_r2_r6) अणु
		अचिन्हित पूर्णांक core;

		core = get_ebase_cpunum();
		अगर (cpu_has_mipsmt)
			core >>= fls(core_nvpes()) - 1;
		cpu_set_core(c, core);
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * Probe क्रम certain guest capabilities by writing config bits and पढ़ोing back.
 * Finally ग_लिखो back the original value.
 */
#घोषणा probe_gc0_config(name, maxconf, bits)				\
करो अणु									\
	अचिन्हित पूर्णांक पंचांगp;						\
	पंचांगp = पढ़ो_gc0_##name();					\
	ग_लिखो_gc0_##name(पंचांगp | (bits));					\
	back_to_back_c0_hazard();					\
	maxconf = पढ़ो_gc0_##name();					\
	ग_लिखो_gc0_##name(पंचांगp);						\
पूर्ण जबतक (0)

/*
 * Probe क्रम dynamic guest capabilities by changing certain config bits and
 * पढ़ोing back to see अगर they change. Finally ग_लिखो back the original value.
 */
#घोषणा probe_gc0_config_dyn(name, maxconf, dynconf, bits)		\
करो अणु									\
	maxconf = पढ़ो_gc0_##name();					\
	ग_लिखो_gc0_##name(maxconf ^ (bits));				\
	back_to_back_c0_hazard();					\
	dynconf = maxconf ^ पढ़ो_gc0_##name();				\
	ग_लिखो_gc0_##name(maxconf);					\
	maxconf |= dynconf;						\
पूर्ण जबतक (0)

अटल अंतरभूत अचिन्हित पूर्णांक decode_guest_config0(काष्ठा cpuinfo_mips *c)
अणु
	अचिन्हित पूर्णांक config0;

	probe_gc0_config(config, config0, MIPS_CONF_M);

	अगर (config0 & MIPS_CONF_M)
		c->guest.conf |= BIT(1);
	वापस config0 & MIPS_CONF_M;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक decode_guest_config1(काष्ठा cpuinfo_mips *c)
अणु
	अचिन्हित पूर्णांक config1, config1_dyn;

	probe_gc0_config_dyn(config1, config1, config1_dyn,
			     MIPS_CONF_M | MIPS_CONF1_PC | MIPS_CONF1_WR |
			     MIPS_CONF1_FP);

	अगर (config1 & MIPS_CONF1_FP)
		c->guest.options |= MIPS_CPU_FPU;
	अगर (config1_dyn & MIPS_CONF1_FP)
		c->guest.options_dyn |= MIPS_CPU_FPU;

	अगर (config1 & MIPS_CONF1_WR)
		c->guest.options |= MIPS_CPU_WATCH;
	अगर (config1_dyn & MIPS_CONF1_WR)
		c->guest.options_dyn |= MIPS_CPU_WATCH;

	अगर (config1 & MIPS_CONF1_PC)
		c->guest.options |= MIPS_CPU_PERF;
	अगर (config1_dyn & MIPS_CONF1_PC)
		c->guest.options_dyn |= MIPS_CPU_PERF;

	अगर (config1 & MIPS_CONF_M)
		c->guest.conf |= BIT(2);
	वापस config1 & MIPS_CONF_M;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक decode_guest_config2(काष्ठा cpuinfo_mips *c)
अणु
	अचिन्हित पूर्णांक config2;

	probe_gc0_config(config2, config2, MIPS_CONF_M);

	अगर (config2 & MIPS_CONF_M)
		c->guest.conf |= BIT(3);
	वापस config2 & MIPS_CONF_M;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक decode_guest_config3(काष्ठा cpuinfo_mips *c)
अणु
	अचिन्हित पूर्णांक config3, config3_dyn;

	probe_gc0_config_dyn(config3, config3, config3_dyn,
			     MIPS_CONF_M | MIPS_CONF3_MSA | MIPS_CONF3_ULRI |
			     MIPS_CONF3_CTXTC);

	अगर (config3 & MIPS_CONF3_CTXTC)
		c->guest.options |= MIPS_CPU_CTXTC;
	अगर (config3_dyn & MIPS_CONF3_CTXTC)
		c->guest.options_dyn |= MIPS_CPU_CTXTC;

	अगर (config3 & MIPS_CONF3_PW)
		c->guest.options |= MIPS_CPU_HTW;

	अगर (config3 & MIPS_CONF3_ULRI)
		c->guest.options |= MIPS_CPU_ULRI;

	अगर (config3 & MIPS_CONF3_SC)
		c->guest.options |= MIPS_CPU_SEGMENTS;

	अगर (config3 & MIPS_CONF3_BI)
		c->guest.options |= MIPS_CPU_BADINSTR;
	अगर (config3 & MIPS_CONF3_BP)
		c->guest.options |= MIPS_CPU_BADINSTRP;

	अगर (config3 & MIPS_CONF3_MSA)
		c->guest.ases |= MIPS_ASE_MSA;
	अगर (config3_dyn & MIPS_CONF3_MSA)
		c->guest.ases_dyn |= MIPS_ASE_MSA;

	अगर (config3 & MIPS_CONF_M)
		c->guest.conf |= BIT(4);
	वापस config3 & MIPS_CONF_M;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक decode_guest_config4(काष्ठा cpuinfo_mips *c)
अणु
	अचिन्हित पूर्णांक config4;

	probe_gc0_config(config4, config4,
			 MIPS_CONF_M | MIPS_CONF4_KSCREXIST);

	c->guest.kscratch_mask = (config4 & MIPS_CONF4_KSCREXIST)
				>> MIPS_CONF4_KSCREXIST_SHIFT;

	अगर (config4 & MIPS_CONF_M)
		c->guest.conf |= BIT(5);
	वापस config4 & MIPS_CONF_M;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक decode_guest_config5(काष्ठा cpuinfo_mips *c)
अणु
	अचिन्हित पूर्णांक config5, config5_dyn;

	probe_gc0_config_dyn(config5, config5, config5_dyn,
			 MIPS_CONF_M | MIPS_CONF5_MVH | MIPS_CONF5_MRP);

	अगर (config5 & MIPS_CONF5_MRP)
		c->guest.options |= MIPS_CPU_MAAR;
	अगर (config5_dyn & MIPS_CONF5_MRP)
		c->guest.options_dyn |= MIPS_CPU_MAAR;

	अगर (config5 & MIPS_CONF5_LLB)
		c->guest.options |= MIPS_CPU_RW_LLB;

	अगर (config5 & MIPS_CONF5_MVH)
		c->guest.options |= MIPS_CPU_MVH;

	अगर (config5 & MIPS_CONF_M)
		c->guest.conf |= BIT(6);
	वापस config5 & MIPS_CONF_M;
पूर्ण

अटल अंतरभूत व्योम decode_guest_configs(काष्ठा cpuinfo_mips *c)
अणु
	अचिन्हित पूर्णांक ok;

	ok = decode_guest_config0(c);
	अगर (ok)
		ok = decode_guest_config1(c);
	अगर (ok)
		ok = decode_guest_config2(c);
	अगर (ok)
		ok = decode_guest_config3(c);
	अगर (ok)
		ok = decode_guest_config4(c);
	अगर (ok)
		decode_guest_config5(c);
पूर्ण

अटल अंतरभूत व्योम cpu_probe_guestctl0(काष्ठा cpuinfo_mips *c)
अणु
	अचिन्हित पूर्णांक guestctl0, temp;

	guestctl0 = पढ़ो_c0_guestctl0();

	अगर (guestctl0 & MIPS_GCTL0_G0E)
		c->options |= MIPS_CPU_GUESTCTL0EXT;
	अगर (guestctl0 & MIPS_GCTL0_G1)
		c->options |= MIPS_CPU_GUESTCTL1;
	अगर (guestctl0 & MIPS_GCTL0_G2)
		c->options |= MIPS_CPU_GUESTCTL2;
	अगर (!(guestctl0 & MIPS_GCTL0_RAD)) अणु
		c->options |= MIPS_CPU_GUESTID;

		/*
		 * Probe क्रम Direct Root to Guest (DRG). Set GuestCtl1.RID = 0
		 * first, otherwise all data accesses will be fully भवised
		 * as अगर they were perक्रमmed by guest mode.
		 */
		ग_लिखो_c0_guestctl1(0);
		tlbw_use_hazard();

		ग_लिखो_c0_guestctl0(guestctl0 | MIPS_GCTL0_DRG);
		back_to_back_c0_hazard();
		temp = पढ़ो_c0_guestctl0();

		अगर (temp & MIPS_GCTL0_DRG) अणु
			ग_लिखो_c0_guestctl0(guestctl0);
			c->options |= MIPS_CPU_DRG;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cpu_probe_guestctl1(काष्ठा cpuinfo_mips *c)
अणु
	अगर (cpu_has_guestid) अणु
		/* determine the number of bits of GuestID available */
		ग_लिखो_c0_guestctl1(MIPS_GCTL1_ID);
		back_to_back_c0_hazard();
		c->guestid_mask = (पढ़ो_c0_guestctl1() & MIPS_GCTL1_ID)
						>> MIPS_GCTL1_ID_SHIFT;
		ग_लिखो_c0_guestctl1(0);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cpu_probe_gtoffset(काष्ठा cpuinfo_mips *c)
अणु
	/* determine the number of bits of GTOffset available */
	ग_लिखो_c0_gtoffset(0xffffffff);
	back_to_back_c0_hazard();
	c->gtoffset_mask = पढ़ो_c0_gtoffset();
	ग_लिखो_c0_gtoffset(0);
पूर्ण

अटल अंतरभूत व्योम cpu_probe_vz(काष्ठा cpuinfo_mips *c)
अणु
	cpu_probe_guestctl0(c);
	अगर (cpu_has_guestctl1)
		cpu_probe_guestctl1(c);

	cpu_probe_gtoffset(c);

	decode_guest_configs(c);
पूर्ण

#घोषणा R4K_OPTS (MIPS_CPU_TLB | MIPS_CPU_4KEX | MIPS_CPU_4K_CACHE \
		| MIPS_CPU_COUNTER)

अटल अंतरभूत व्योम cpu_probe_legacy(काष्ठा cpuinfo_mips *c, अचिन्हित पूर्णांक cpu)
अणु
	चयन (c->processor_id & PRID_IMP_MASK) अणु
	हाल PRID_IMP_R2000:
		c->cputype = CPU_R2000;
		__cpu_name[cpu] = "R2000";
		c->fpu_msk31 |= FPU_CSR_CONDX | FPU_CSR_FS;
		c->options = MIPS_CPU_TLB | MIPS_CPU_3K_CACHE |
			     MIPS_CPU_NOFPUEX;
		अगर (__cpu_has_fpu())
			c->options |= MIPS_CPU_FPU;
		c->tlbsize = 64;
		अवरोध;
	हाल PRID_IMP_R3000:
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
		c->fpu_msk31 |= FPU_CSR_CONDX | FPU_CSR_FS;
		c->options = MIPS_CPU_TLB | MIPS_CPU_3K_CACHE |
			     MIPS_CPU_NOFPUEX;
		अगर (__cpu_has_fpu())
			c->options |= MIPS_CPU_FPU;
		c->tlbsize = 64;
		अवरोध;
	हाल PRID_IMP_R4000:
		अगर (पढ़ो_c0_config() & CONF_SC) अणु
			अगर ((c->processor_id & PRID_REV_MASK) >=
			    PRID_REV_R4400) अणु
				c->cputype = CPU_R4400PC;
				__cpu_name[cpu] = "R4400PC";
			पूर्ण अन्यथा अणु
				c->cputype = CPU_R4000PC;
				__cpu_name[cpu] = "R4000PC";
			पूर्ण
		पूर्ण अन्यथा अणु
			पूर्णांक cca = पढ़ो_c0_config() & CONF_CM_CMASK;
			पूर्णांक mc;

			/*
			 * SC and MC versions can't be reliably told apart,
			 * but only the latter support coherent caching
			 * modes so assume the firmware has set the KSEG0
			 * coherency attribute reasonably (अगर uncached, we
			 * assume SC).
			 */
			चयन (cca) अणु
			हाल CONF_CM_CACHABLE_CE:
			हाल CONF_CM_CACHABLE_COW:
			हाल CONF_CM_CACHABLE_CUW:
				mc = 1;
				अवरोध;
			शेष:
				mc = 0;
				अवरोध;
			पूर्ण
			अगर ((c->processor_id & PRID_REV_MASK) >=
			    PRID_REV_R4400) अणु
				c->cputype = mc ? CPU_R4400MC : CPU_R4400SC;
				__cpu_name[cpu] = mc ? "R4400MC" : "R4400SC";
			पूर्ण अन्यथा अणु
				c->cputype = mc ? CPU_R4000MC : CPU_R4000SC;
				__cpu_name[cpu] = mc ? "R4000MC" : "R4000SC";
			पूर्ण
		पूर्ण

		set_isa(c, MIPS_CPU_ISA_III);
		c->fpu_msk31 |= FPU_CSR_CONDX;
		c->options = R4K_OPTS | MIPS_CPU_FPU | MIPS_CPU_32FPR |
			     MIPS_CPU_WATCH | MIPS_CPU_VCE |
			     MIPS_CPU_LLSC;
		c->tlbsize = 48;
		अवरोध;
	हाल PRID_IMP_VR41XX:
		set_isa(c, MIPS_CPU_ISA_III);
		c->fpu_msk31 |= FPU_CSR_CONDX;
		c->options = R4K_OPTS;
		c->tlbsize = 32;
		चयन (c->processor_id & 0xf0) अणु
		हाल PRID_REV_VR4111:
			c->cputype = CPU_VR4111;
			__cpu_name[cpu] = "NEC VR4111";
			अवरोध;
		हाल PRID_REV_VR4121:
			c->cputype = CPU_VR4121;
			__cpu_name[cpu] = "NEC VR4121";
			अवरोध;
		हाल PRID_REV_VR4122:
			अगर ((c->processor_id & 0xf) < 0x3) अणु
				c->cputype = CPU_VR4122;
				__cpu_name[cpu] = "NEC VR4122";
			पूर्ण अन्यथा अणु
				c->cputype = CPU_VR4181A;
				__cpu_name[cpu] = "NEC VR4181A";
			पूर्ण
			अवरोध;
		हाल PRID_REV_VR4130:
			अगर ((c->processor_id & 0xf) < 0x4) अणु
				c->cputype = CPU_VR4131;
				__cpu_name[cpu] = "NEC VR4131";
			पूर्ण अन्यथा अणु
				c->cputype = CPU_VR4133;
				c->options |= MIPS_CPU_LLSC;
				__cpu_name[cpu] = "NEC VR4133";
			पूर्ण
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_INFO "Unexpected CPU of NEC VR4100 series\n");
			c->cputype = CPU_VR41XX;
			__cpu_name[cpu] = "NEC Vr41xx";
			अवरोध;
		पूर्ण
		अवरोध;
	हाल PRID_IMP_R4300:
		c->cputype = CPU_R4300;
		__cpu_name[cpu] = "R4300";
		set_isa(c, MIPS_CPU_ISA_III);
		c->fpu_msk31 |= FPU_CSR_CONDX;
		c->options = R4K_OPTS | MIPS_CPU_FPU | MIPS_CPU_32FPR |
			     MIPS_CPU_LLSC;
		c->tlbsize = 32;
		अवरोध;
	हाल PRID_IMP_R4600:
		c->cputype = CPU_R4600;
		__cpu_name[cpu] = "R4600";
		set_isa(c, MIPS_CPU_ISA_III);
		c->fpu_msk31 |= FPU_CSR_CONDX;
		c->options = R4K_OPTS | MIPS_CPU_FPU | MIPS_CPU_32FPR |
			     MIPS_CPU_LLSC;
		c->tlbsize = 48;
		अवरोध;
	#अगर 0
	हाल PRID_IMP_R4650:
		/*
		 * This processor करोesn't have an MMU, so it's not
		 * "real easy" to run Linux on it. It is left purely
		 * क्रम करोcumentation.  Commented out because it shares
		 * it's c0_prid id number with the TX3900.
		 */
		c->cputype = CPU_R4650;
		__cpu_name[cpu] = "R4650";
		set_isa(c, MIPS_CPU_ISA_III);
		c->fpu_msk31 |= FPU_CSR_CONDX;
		c->options = R4K_OPTS | MIPS_CPU_FPU | MIPS_CPU_LLSC;
		c->tlbsize = 48;
		अवरोध;
	#पूर्ण_अगर
	हाल PRID_IMP_TX39:
		c->fpu_msk31 |= FPU_CSR_CONDX | FPU_CSR_FS;
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
	हाल PRID_IMP_R4700:
		c->cputype = CPU_R4700;
		__cpu_name[cpu] = "R4700";
		set_isa(c, MIPS_CPU_ISA_III);
		c->fpu_msk31 |= FPU_CSR_CONDX;
		c->options = R4K_OPTS | MIPS_CPU_FPU | MIPS_CPU_32FPR |
			     MIPS_CPU_LLSC;
		c->tlbsize = 48;
		अवरोध;
	हाल PRID_IMP_TX49:
		c->cputype = CPU_TX49XX;
		__cpu_name[cpu] = "R49XX";
		set_isa(c, MIPS_CPU_ISA_III);
		c->fpu_msk31 |= FPU_CSR_CONDX;
		c->options = R4K_OPTS | MIPS_CPU_LLSC;
		अगर (!(c->processor_id & 0x08))
			c->options |= MIPS_CPU_FPU | MIPS_CPU_32FPR;
		c->tlbsize = 48;
		अवरोध;
	हाल PRID_IMP_R5000:
		c->cputype = CPU_R5000;
		__cpu_name[cpu] = "R5000";
		set_isa(c, MIPS_CPU_ISA_IV);
		c->options = R4K_OPTS | MIPS_CPU_FPU | MIPS_CPU_32FPR |
			     MIPS_CPU_LLSC;
		c->tlbsize = 48;
		अवरोध;
	हाल PRID_IMP_R5500:
		c->cputype = CPU_R5500;
		__cpu_name[cpu] = "R5500";
		set_isa(c, MIPS_CPU_ISA_IV);
		c->options = R4K_OPTS | MIPS_CPU_FPU | MIPS_CPU_32FPR |
			     MIPS_CPU_WATCH | MIPS_CPU_LLSC;
		c->tlbsize = 48;
		अवरोध;
	हाल PRID_IMP_NEVADA:
		c->cputype = CPU_NEVADA;
		__cpu_name[cpu] = "Nevada";
		set_isa(c, MIPS_CPU_ISA_IV);
		c->options = R4K_OPTS | MIPS_CPU_FPU | MIPS_CPU_32FPR |
			     MIPS_CPU_DIVEC | MIPS_CPU_LLSC;
		c->tlbsize = 48;
		अवरोध;
	हाल PRID_IMP_RM7000:
		c->cputype = CPU_RM7000;
		__cpu_name[cpu] = "RM7000";
		set_isa(c, MIPS_CPU_ISA_IV);
		c->options = R4K_OPTS | MIPS_CPU_FPU | MIPS_CPU_32FPR |
			     MIPS_CPU_LLSC;
		/*
		 * Unकरोcumented RM7000:	 Bit 29 in the info रेजिस्टर of
		 * the RM7000 v2.0 indicates अगर the TLB has 48 or 64
		 * entries.
		 *
		 * 29	   1 =>	   64 entry JTLB
		 *	   0 =>	   48 entry JTLB
		 */
		c->tlbsize = (पढ़ो_c0_info() & (1 << 29)) ? 64 : 48;
		अवरोध;
	हाल PRID_IMP_R10000:
		c->cputype = CPU_R10000;
		__cpu_name[cpu] = "R10000";
		set_isa(c, MIPS_CPU_ISA_IV);
		c->options = MIPS_CPU_TLB | MIPS_CPU_4K_CACHE | MIPS_CPU_4KEX |
			     MIPS_CPU_FPU | MIPS_CPU_32FPR |
			     MIPS_CPU_COUNTER | MIPS_CPU_WATCH |
			     MIPS_CPU_LLSC;
		c->tlbsize = 64;
		अवरोध;
	हाल PRID_IMP_R12000:
		c->cputype = CPU_R12000;
		__cpu_name[cpu] = "R12000";
		set_isa(c, MIPS_CPU_ISA_IV);
		c->options = MIPS_CPU_TLB | MIPS_CPU_4K_CACHE | MIPS_CPU_4KEX |
			     MIPS_CPU_FPU | MIPS_CPU_32FPR |
			     MIPS_CPU_COUNTER | MIPS_CPU_WATCH |
			     MIPS_CPU_LLSC;
		c->tlbsize = 64;
		ग_लिखो_c0_r10k_diag(पढ़ो_c0_r10k_diag() | R10K_DIAG_E_GHIST);
		अवरोध;
	हाल PRID_IMP_R14000:
		अगर (((c->processor_id >> 4) & 0x0f) > 2) अणु
			c->cputype = CPU_R16000;
			__cpu_name[cpu] = "R16000";
		पूर्ण अन्यथा अणु
			c->cputype = CPU_R14000;
			__cpu_name[cpu] = "R14000";
		पूर्ण
		set_isa(c, MIPS_CPU_ISA_IV);
		c->options = MIPS_CPU_TLB | MIPS_CPU_4K_CACHE | MIPS_CPU_4KEX |
			     MIPS_CPU_FPU | MIPS_CPU_32FPR |
			     MIPS_CPU_COUNTER | MIPS_CPU_WATCH |
			     MIPS_CPU_LLSC;
		c->tlbsize = 64;
		ग_लिखो_c0_r10k_diag(पढ़ो_c0_r10k_diag() | R10K_DIAG_E_GHIST);
		अवरोध;
	हाल PRID_IMP_LOONGSON_64C:  /* Loongson-2/3 */
		चयन (c->processor_id & PRID_REV_MASK) अणु
		हाल PRID_REV_LOONGSON2E:
			c->cputype = CPU_LOONGSON2EF;
			__cpu_name[cpu] = "ICT Loongson-2";
			set_elf_platक्रमm(cpu, "loongson2e");
			set_isa(c, MIPS_CPU_ISA_III);
			c->fpu_msk31 |= FPU_CSR_CONDX;
			अवरोध;
		हाल PRID_REV_LOONGSON2F:
			c->cputype = CPU_LOONGSON2EF;
			__cpu_name[cpu] = "ICT Loongson-2";
			set_elf_platक्रमm(cpu, "loongson2f");
			set_isa(c, MIPS_CPU_ISA_III);
			c->fpu_msk31 |= FPU_CSR_CONDX;
			अवरोध;
		हाल PRID_REV_LOONGSON3A_R1:
			c->cputype = CPU_LOONGSON64;
			__cpu_name[cpu] = "ICT Loongson-3";
			set_elf_platक्रमm(cpu, "loongson3a");
			set_isa(c, MIPS_CPU_ISA_M64R1);
			c->ases |= (MIPS_ASE_LOONGSON_MMI | MIPS_ASE_LOONGSON_CAM |
				MIPS_ASE_LOONGSON_EXT);
			अवरोध;
		हाल PRID_REV_LOONGSON3B_R1:
		हाल PRID_REV_LOONGSON3B_R2:
			c->cputype = CPU_LOONGSON64;
			__cpu_name[cpu] = "ICT Loongson-3";
			set_elf_platक्रमm(cpu, "loongson3b");
			set_isa(c, MIPS_CPU_ISA_M64R1);
			c->ases |= (MIPS_ASE_LOONGSON_MMI | MIPS_ASE_LOONGSON_CAM |
				MIPS_ASE_LOONGSON_EXT);
			अवरोध;
		पूर्ण

		c->options = R4K_OPTS |
			     MIPS_CPU_FPU | MIPS_CPU_LLSC |
			     MIPS_CPU_32FPR;
		c->tlbsize = 64;
		set_cpu_asid_mask(c, MIPS_ENTRYHI_ASID);
		c->ग_लिखोcombine = _CACHE_UNCACHED_ACCELERATED;
		अवरोध;
	हाल PRID_IMP_LOONGSON_32:  /* Loongson-1 */
		decode_configs(c);

		c->cputype = CPU_LOONGSON32;

		चयन (c->processor_id & PRID_REV_MASK) अणु
		हाल PRID_REV_LOONGSON1B:
			__cpu_name[cpu] = "Loongson 1B";
			अवरोध;
		पूर्ण

		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cpu_probe_mips(काष्ठा cpuinfo_mips *c, अचिन्हित पूर्णांक cpu)
अणु
	c->ग_लिखोcombine = _CACHE_UNCACHED_ACCELERATED;
	चयन (c->processor_id & PRID_IMP_MASK) अणु
	हाल PRID_IMP_QEMU_GENERIC:
		c->ग_लिखोcombine = _CACHE_UNCACHED;
		c->cputype = CPU_QEMU_GENERIC;
		__cpu_name[cpu] = "MIPS GENERIC QEMU";
		अवरोध;
	हाल PRID_IMP_4KC:
		c->cputype = CPU_4KC;
		c->ग_लिखोcombine = _CACHE_UNCACHED;
		__cpu_name[cpu] = "MIPS 4Kc";
		अवरोध;
	हाल PRID_IMP_4KEC:
	हाल PRID_IMP_4KECR2:
		c->cputype = CPU_4KEC;
		c->ग_लिखोcombine = _CACHE_UNCACHED;
		__cpu_name[cpu] = "MIPS 4KEc";
		अवरोध;
	हाल PRID_IMP_4KSC:
	हाल PRID_IMP_4KSD:
		c->cputype = CPU_4KSC;
		c->ग_लिखोcombine = _CACHE_UNCACHED;
		__cpu_name[cpu] = "MIPS 4KSc";
		अवरोध;
	हाल PRID_IMP_5KC:
		c->cputype = CPU_5KC;
		c->ग_लिखोcombine = _CACHE_UNCACHED;
		__cpu_name[cpu] = "MIPS 5Kc";
		अवरोध;
	हाल PRID_IMP_5KE:
		c->cputype = CPU_5KE;
		c->ग_लिखोcombine = _CACHE_UNCACHED;
		__cpu_name[cpu] = "MIPS 5KE";
		अवरोध;
	हाल PRID_IMP_20KC:
		c->cputype = CPU_20KC;
		c->ग_लिखोcombine = _CACHE_UNCACHED;
		__cpu_name[cpu] = "MIPS 20Kc";
		अवरोध;
	हाल PRID_IMP_24K:
		c->cputype = CPU_24K;
		c->ग_लिखोcombine = _CACHE_UNCACHED;
		__cpu_name[cpu] = "MIPS 24Kc";
		अवरोध;
	हाल PRID_IMP_24KE:
		c->cputype = CPU_24K;
		c->ग_लिखोcombine = _CACHE_UNCACHED;
		__cpu_name[cpu] = "MIPS 24KEc";
		अवरोध;
	हाल PRID_IMP_25KF:
		c->cputype = CPU_25KF;
		c->ग_लिखोcombine = _CACHE_UNCACHED;
		__cpu_name[cpu] = "MIPS 25Kc";
		अवरोध;
	हाल PRID_IMP_34K:
		c->cputype = CPU_34K;
		c->ग_लिखोcombine = _CACHE_UNCACHED;
		__cpu_name[cpu] = "MIPS 34Kc";
		cpu_set_mt_per_tc_perf(c);
		अवरोध;
	हाल PRID_IMP_74K:
		c->cputype = CPU_74K;
		c->ग_लिखोcombine = _CACHE_UNCACHED;
		__cpu_name[cpu] = "MIPS 74Kc";
		अवरोध;
	हाल PRID_IMP_M14KC:
		c->cputype = CPU_M14KC;
		c->ग_लिखोcombine = _CACHE_UNCACHED;
		__cpu_name[cpu] = "MIPS M14Kc";
		अवरोध;
	हाल PRID_IMP_M14KEC:
		c->cputype = CPU_M14KEC;
		c->ग_लिखोcombine = _CACHE_UNCACHED;
		__cpu_name[cpu] = "MIPS M14KEc";
		अवरोध;
	हाल PRID_IMP_1004K:
		c->cputype = CPU_1004K;
		c->ग_लिखोcombine = _CACHE_UNCACHED;
		__cpu_name[cpu] = "MIPS 1004Kc";
		cpu_set_mt_per_tc_perf(c);
		अवरोध;
	हाल PRID_IMP_1074K:
		c->cputype = CPU_1074K;
		c->ग_लिखोcombine = _CACHE_UNCACHED;
		__cpu_name[cpu] = "MIPS 1074Kc";
		अवरोध;
	हाल PRID_IMP_INTERAPTIV_UP:
		c->cputype = CPU_INTERAPTIV;
		__cpu_name[cpu] = "MIPS interAptiv";
		cpu_set_mt_per_tc_perf(c);
		अवरोध;
	हाल PRID_IMP_INTERAPTIV_MP:
		c->cputype = CPU_INTERAPTIV;
		__cpu_name[cpu] = "MIPS interAptiv (multi)";
		cpu_set_mt_per_tc_perf(c);
		अवरोध;
	हाल PRID_IMP_PROAPTIV_UP:
		c->cputype = CPU_PROAPTIV;
		__cpu_name[cpu] = "MIPS proAptiv";
		अवरोध;
	हाल PRID_IMP_PROAPTIV_MP:
		c->cputype = CPU_PROAPTIV;
		__cpu_name[cpu] = "MIPS proAptiv (multi)";
		अवरोध;
	हाल PRID_IMP_P5600:
		c->cputype = CPU_P5600;
		__cpu_name[cpu] = "MIPS P5600";
		अवरोध;
	हाल PRID_IMP_P6600:
		c->cputype = CPU_P6600;
		__cpu_name[cpu] = "MIPS P6600";
		अवरोध;
	हाल PRID_IMP_I6400:
		c->cputype = CPU_I6400;
		__cpu_name[cpu] = "MIPS I6400";
		अवरोध;
	हाल PRID_IMP_I6500:
		c->cputype = CPU_I6500;
		__cpu_name[cpu] = "MIPS I6500";
		अवरोध;
	हाल PRID_IMP_M5150:
		c->cputype = CPU_M5150;
		__cpu_name[cpu] = "MIPS M5150";
		अवरोध;
	हाल PRID_IMP_M6250:
		c->cputype = CPU_M6250;
		__cpu_name[cpu] = "MIPS M6250";
		अवरोध;
	पूर्ण

	decode_configs(c);

	spram_config();

	mm_config(c);

	चयन (__get_cpu_type(c->cputype)) अणु
	हाल CPU_M5150:
	हाल CPU_P5600:
		set_isa(c, MIPS_CPU_ISA_M32R5);
		अवरोध;
	हाल CPU_I6500:
		c->options |= MIPS_CPU_SHARED_FTLB_ENTRIES;
		fallthrough;
	हाल CPU_I6400:
		c->options |= MIPS_CPU_SHARED_FTLB_RAM;
		fallthrough;
	शेष:
		अवरोध;
	पूर्ण

	/* Recent MIPS cores use the implementation-dependent ExcCode 16 क्रम
	 * cache/FTLB parity exceptions.
	 */
	चयन (__get_cpu_type(c->cputype)) अणु
	हाल CPU_PROAPTIV:
	हाल CPU_P5600:
	हाल CPU_P6600:
	हाल CPU_I6400:
	हाल CPU_I6500:
		c->options |= MIPS_CPU_FTLBPAREX;
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cpu_probe_alchemy(काष्ठा cpuinfo_mips *c, अचिन्हित पूर्णांक cpu)
अणु
	decode_configs(c);
	चयन (c->processor_id & PRID_IMP_MASK) अणु
	हाल PRID_IMP_AU1_REV1:
	हाल PRID_IMP_AU1_REV2:
		c->cputype = CPU_ALCHEMY;
		चयन ((c->processor_id >> 24) & 0xff) अणु
		हाल 0:
			__cpu_name[cpu] = "Au1000";
			अवरोध;
		हाल 1:
			__cpu_name[cpu] = "Au1500";
			अवरोध;
		हाल 2:
			__cpu_name[cpu] = "Au1100";
			अवरोध;
		हाल 3:
			__cpu_name[cpu] = "Au1550";
			अवरोध;
		हाल 4:
			__cpu_name[cpu] = "Au1200";
			अगर ((c->processor_id & PRID_REV_MASK) == 2)
				__cpu_name[cpu] = "Au1250";
			अवरोध;
		हाल 5:
			__cpu_name[cpu] = "Au1210";
			अवरोध;
		शेष:
			__cpu_name[cpu] = "Au1xxx";
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cpu_probe_sibyte(काष्ठा cpuinfo_mips *c, अचिन्हित पूर्णांक cpu)
अणु
	decode_configs(c);

	c->ग_लिखोcombine = _CACHE_UNCACHED_ACCELERATED;
	चयन (c->processor_id & PRID_IMP_MASK) अणु
	हाल PRID_IMP_SB1:
		c->cputype = CPU_SB1;
		__cpu_name[cpu] = "SiByte SB1";
		/* FPU in pass1 is known to have issues. */
		अगर ((c->processor_id & PRID_REV_MASK) < 0x02)
			c->options &= ~(MIPS_CPU_FPU | MIPS_CPU_32FPR);
		अवरोध;
	हाल PRID_IMP_SB1A:
		c->cputype = CPU_SB1A;
		__cpu_name[cpu] = "SiByte SB1A";
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cpu_probe_sandcraft(काष्ठा cpuinfo_mips *c, अचिन्हित पूर्णांक cpu)
अणु
	decode_configs(c);
	चयन (c->processor_id & PRID_IMP_MASK) अणु
	हाल PRID_IMP_SR71000:
		c->cputype = CPU_SR71000;
		__cpu_name[cpu] = "Sandcraft SR71000";
		c->scache.ways = 8;
		c->tlbsize = 64;
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cpu_probe_nxp(काष्ठा cpuinfo_mips *c, अचिन्हित पूर्णांक cpu)
अणु
	decode_configs(c);
	चयन (c->processor_id & PRID_IMP_MASK) अणु
	हाल PRID_IMP_PR4450:
		c->cputype = CPU_PR4450;
		__cpu_name[cpu] = "Philips PR4450";
		set_isa(c, MIPS_CPU_ISA_M32R1);
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cpu_probe_broadcom(काष्ठा cpuinfo_mips *c, अचिन्हित पूर्णांक cpu)
अणु
	decode_configs(c);
	चयन (c->processor_id & PRID_IMP_MASK) अणु
	हाल PRID_IMP_BMIPS32_REV4:
	हाल PRID_IMP_BMIPS32_REV8:
		c->cputype = CPU_BMIPS32;
		__cpu_name[cpu] = "Broadcom BMIPS32";
		set_elf_platक्रमm(cpu, "bmips32");
		अवरोध;
	हाल PRID_IMP_BMIPS3300:
	हाल PRID_IMP_BMIPS3300_ALT:
	हाल PRID_IMP_BMIPS3300_BUG:
		c->cputype = CPU_BMIPS3300;
		__cpu_name[cpu] = "Broadcom BMIPS3300";
		set_elf_platक्रमm(cpu, "bmips3300");
		reserve_exception_space(0x400, VECTORSPACING * 64);
		अवरोध;
	हाल PRID_IMP_BMIPS43XX: अणु
		पूर्णांक rev = c->processor_id & PRID_REV_MASK;

		अगर (rev >= PRID_REV_BMIPS4380_LO &&
				rev <= PRID_REV_BMIPS4380_HI) अणु
			c->cputype = CPU_BMIPS4380;
			__cpu_name[cpu] = "Broadcom BMIPS4380";
			set_elf_platक्रमm(cpu, "bmips4380");
			c->options |= MIPS_CPU_RIXI;
			reserve_exception_space(0x400, VECTORSPACING * 64);
		पूर्ण अन्यथा अणु
			c->cputype = CPU_BMIPS4350;
			__cpu_name[cpu] = "Broadcom BMIPS4350";
			set_elf_platक्रमm(cpu, "bmips4350");
		पूर्ण
		अवरोध;
	पूर्ण
	हाल PRID_IMP_BMIPS5000:
	हाल PRID_IMP_BMIPS5200:
		c->cputype = CPU_BMIPS5000;
		अगर ((c->processor_id & PRID_IMP_MASK) == PRID_IMP_BMIPS5200)
			__cpu_name[cpu] = "Broadcom BMIPS5200";
		अन्यथा
			__cpu_name[cpu] = "Broadcom BMIPS5000";
		set_elf_platक्रमm(cpu, "bmips5000");
		c->options |= MIPS_CPU_ULRI | MIPS_CPU_RIXI;
		reserve_exception_space(0x1000, VECTORSPACING * 64);
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cpu_probe_cavium(काष्ठा cpuinfo_mips *c, अचिन्हित पूर्णांक cpu)
अणु
	decode_configs(c);
	चयन (c->processor_id & PRID_IMP_MASK) अणु
	हाल PRID_IMP_CAVIUM_CN38XX:
	हाल PRID_IMP_CAVIUM_CN31XX:
	हाल PRID_IMP_CAVIUM_CN30XX:
		c->cputype = CPU_CAVIUM_OCTEON;
		__cpu_name[cpu] = "Cavium Octeon";
		जाओ platक्रमm;
	हाल PRID_IMP_CAVIUM_CN58XX:
	हाल PRID_IMP_CAVIUM_CN56XX:
	हाल PRID_IMP_CAVIUM_CN50XX:
	हाल PRID_IMP_CAVIUM_CN52XX:
		c->cputype = CPU_CAVIUM_OCTEON_PLUS;
		__cpu_name[cpu] = "Cavium Octeon+";
platक्रमm:
		set_elf_platक्रमm(cpu, "octeon");
		अवरोध;
	हाल PRID_IMP_CAVIUM_CN61XX:
	हाल PRID_IMP_CAVIUM_CN63XX:
	हाल PRID_IMP_CAVIUM_CN66XX:
	हाल PRID_IMP_CAVIUM_CN68XX:
	हाल PRID_IMP_CAVIUM_CNF71XX:
		c->cputype = CPU_CAVIUM_OCTEON2;
		__cpu_name[cpu] = "Cavium Octeon II";
		set_elf_platक्रमm(cpu, "octeon2");
		अवरोध;
	हाल PRID_IMP_CAVIUM_CN70XX:
	हाल PRID_IMP_CAVIUM_CN73XX:
	हाल PRID_IMP_CAVIUM_CNF75XX:
	हाल PRID_IMP_CAVIUM_CN78XX:
		c->cputype = CPU_CAVIUM_OCTEON3;
		__cpu_name[cpu] = "Cavium Octeon III";
		set_elf_platक्रमm(cpu, "octeon3");
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_INFO "Unknown Octeon chip!\n");
		c->cputype = CPU_UNKNOWN;
		अवरोध;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_CPU_LOONGSON64
#समावेश <loongson_regs.h>

अटल अंतरभूत व्योम decode_cpucfg(काष्ठा cpuinfo_mips *c)
अणु
	u32 cfg1 = पढ़ो_cpucfg(LOONGSON_CFG1);
	u32 cfg2 = पढ़ो_cpucfg(LOONGSON_CFG2);
	u32 cfg3 = पढ़ो_cpucfg(LOONGSON_CFG3);

	अगर (cfg1 & LOONGSON_CFG1_MMI)
		c->ases |= MIPS_ASE_LOONGSON_MMI;

	अगर (cfg2 & LOONGSON_CFG2_LEXT1)
		c->ases |= MIPS_ASE_LOONGSON_EXT;

	अगर (cfg2 & LOONGSON_CFG2_LEXT2)
		c->ases |= MIPS_ASE_LOONGSON_EXT2;

	अगर (cfg2 & LOONGSON_CFG2_LSPW) अणु
		c->options |= MIPS_CPU_LDPTE;
		c->guest.options |= MIPS_CPU_LDPTE;
	पूर्ण

	अगर (cfg3 & LOONGSON_CFG3_LCAMP)
		c->ases |= MIPS_ASE_LOONGSON_CAM;
पूर्ण

अटल अंतरभूत व्योम cpu_probe_loongson(काष्ठा cpuinfo_mips *c, अचिन्हित पूर्णांक cpu)
अणु
	decode_configs(c);

	/* All Loongson processors covered here define ExcCode 16 as GSExc. */
	c->options |= MIPS_CPU_GSEXCEX;

	चयन (c->processor_id & PRID_IMP_MASK) अणु
	हाल PRID_IMP_LOONGSON_64R: /* Loongson-64 Reduced */
		चयन (c->processor_id & PRID_REV_MASK) अणु
		हाल PRID_REV_LOONGSON2K_R1_0:
		हाल PRID_REV_LOONGSON2K_R1_1:
		हाल PRID_REV_LOONGSON2K_R1_2:
		हाल PRID_REV_LOONGSON2K_R1_3:
			c->cputype = CPU_LOONGSON64;
			__cpu_name[cpu] = "Loongson-2K";
			set_elf_platक्रमm(cpu, "gs264e");
			set_isa(c, MIPS_CPU_ISA_M64R2);
			अवरोध;
		पूर्ण
		c->ases |= (MIPS_ASE_LOONGSON_MMI | MIPS_ASE_LOONGSON_EXT |
				MIPS_ASE_LOONGSON_EXT2);
		अवरोध;
	हाल PRID_IMP_LOONGSON_64C:  /* Loongson-3 Classic */
		चयन (c->processor_id & PRID_REV_MASK) अणु
		हाल PRID_REV_LOONGSON3A_R2_0:
		हाल PRID_REV_LOONGSON3A_R2_1:
			c->cputype = CPU_LOONGSON64;
			__cpu_name[cpu] = "ICT Loongson-3";
			set_elf_platक्रमm(cpu, "loongson3a");
			set_isa(c, MIPS_CPU_ISA_M64R2);
			अवरोध;
		हाल PRID_REV_LOONGSON3A_R3_0:
		हाल PRID_REV_LOONGSON3A_R3_1:
			c->cputype = CPU_LOONGSON64;
			__cpu_name[cpu] = "ICT Loongson-3";
			set_elf_platक्रमm(cpu, "loongson3a");
			set_isa(c, MIPS_CPU_ISA_M64R2);
			अवरोध;
		पूर्ण
		/*
		 * Loongson-3 Classic did not implement MIPS standard TLBINV
		 * but implemented TLBINVF and EHINV. As currently we're only
		 * using these two features, enable MIPS_CPU_TLBINV as well.
		 *
		 * Also some early Loongson-3A2000 had wrong TLB type in Config
		 * रेजिस्टर, we correct it here.
		 */
		c->options |= MIPS_CPU_FTLB | MIPS_CPU_TLBINV | MIPS_CPU_LDPTE;
		c->ases |= (MIPS_ASE_LOONGSON_MMI | MIPS_ASE_LOONGSON_CAM |
			MIPS_ASE_LOONGSON_EXT | MIPS_ASE_LOONGSON_EXT2);
		c->ases &= ~MIPS_ASE_VZ; /* VZ of Loongson-3A2000/3000 is incomplete */
		अवरोध;
	हाल PRID_IMP_LOONGSON_64G:
		c->cputype = CPU_LOONGSON64;
		__cpu_name[cpu] = "ICT Loongson-3";
		set_elf_platक्रमm(cpu, "loongson3a");
		set_isa(c, MIPS_CPU_ISA_M64R2);
		decode_cpucfg(c);
		अवरोध;
	शेष:
		panic("Unknown Loongson Processor ID!");
		अवरोध;
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम cpu_probe_loongson(काष्ठा cpuinfo_mips *c, अचिन्हित पूर्णांक cpu) अणु पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम cpu_probe_ingenic(काष्ठा cpuinfo_mips *c, अचिन्हित पूर्णांक cpu)
अणु
	decode_configs(c);

	/*
	 * XBurst misses a config2 रेजिस्टर, so config3 decode was skipped in
	 * decode_configs().
	 */
	decode_config3(c);

	/* XBurst करोes not implement the CP0 counter. */
	c->options &= ~MIPS_CPU_COUNTER;
	BUG_ON(__builtin_स्थिरant_p(cpu_has_counter) && cpu_has_counter);

	/* XBurst has भवly tagged icache */
	c->icache.flags |= MIPS_CACHE_VTAG;

	चयन (c->processor_id & PRID_IMP_MASK) अणु

	/* XBurstतऍ1 with MXU1.0/MXU1.1 SIMD ISA */
	हाल PRID_IMP_XBURST_REV1:

		/*
		 * The XBurst core by शेष attempts to aव्योम branch target
		 * buffer lookups by detecting & special casing loops. This
		 * feature will cause BogoMIPS and lpj calculate in error.
		 * Set cp0 config7 bit 4 to disable this feature.
		 */
		set_c0_config7(MIPS_CONF7_BTB_LOOP_EN);

		चयन (c->processor_id & PRID_COMP_MASK) अणु

		/*
		 * The config0 रेजिस्टर in the XBurst CPUs with a processor ID of
		 * PRID_COMP_INGENIC_D0 report themselves as MIPS32r2 compatible,
		 * but they करोn't actually support this ISA.
		 */
		हाल PRID_COMP_INGENIC_D0:
			c->isa_level &= ~MIPS_CPU_ISA_M32R2;
			fallthrough;

		/*
		 * The config0 रेजिस्टर in the XBurst CPUs with a processor ID of
		 * PRID_COMP_INGENIC_D0 or PRID_COMP_INGENIC_D1 has an abanकरोned
		 * huge page tlb mode, this mode is not compatible with the MIPS
		 * standard, it will cause tlbmiss and पूर्णांकo an infinite loop
		 * (line 21 in the tlb-funcs.S) when starting the init process.
		 * After chip reset, the शेष is HPTLB mode, Write 0xa9000000
		 * to cp0 रेजिस्टर 5 sel 4 to चयन back to VTLB mode to prevent
		 * getting stuck.
		 */
		हाल PRID_COMP_INGENIC_D1:
			ग_लिखो_c0_page_ctrl(XBURST_PAGECTRL_HPTLB_DIS);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
		fallthrough;

	/* XBurstतऍ1 with MXU2.0 SIMD ISA */
	हाल PRID_IMP_XBURST_REV2:
		/* Ingenic uses the WA bit to achieve ग_लिखो-combine memory ग_लिखोs */
		c->ग_लिखोcombine = _CACHE_CACHABLE_WA;
		c->cputype = CPU_XBURST;
		__cpu_name[cpu] = "Ingenic XBurst";
		अवरोध;

	/* XBurstतऍ2 with MXU2.1 SIMD ISA */
	हाल PRID_IMP_XBURST2:
		c->cputype = CPU_XBURST;
		__cpu_name[cpu] = "Ingenic XBurst II";
		अवरोध;

	शेष:
		panic("Unknown Ingenic Processor ID!");
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cpu_probe_netlogic(काष्ठा cpuinfo_mips *c, पूर्णांक cpu)
अणु
	decode_configs(c);

	अगर ((c->processor_id & PRID_IMP_MASK) == PRID_IMP_NETLOGIC_AU13XX) अणु
		c->cputype = CPU_ALCHEMY;
		__cpu_name[cpu] = "Au1300";
		/* following stuff is not क्रम Alchemy */
		वापस;
	पूर्ण

	c->options = (MIPS_CPU_TLB	 |
			MIPS_CPU_4KEX	 |
			MIPS_CPU_COUNTER |
			MIPS_CPU_DIVEC	 |
			MIPS_CPU_WATCH	 |
			MIPS_CPU_EJTAG	 |
			MIPS_CPU_LLSC);

	चयन (c->processor_id & PRID_IMP_MASK) अणु
	हाल PRID_IMP_NETLOGIC_XLP2XX:
	हाल PRID_IMP_NETLOGIC_XLP9XX:
	हाल PRID_IMP_NETLOGIC_XLP5XX:
		c->cputype = CPU_XLP;
		__cpu_name[cpu] = "Broadcom XLPII";
		अवरोध;

	हाल PRID_IMP_NETLOGIC_XLP8XX:
	हाल PRID_IMP_NETLOGIC_XLP3XX:
		c->cputype = CPU_XLP;
		__cpu_name[cpu] = "Netlogic XLP";
		अवरोध;

	हाल PRID_IMP_NETLOGIC_XLR732:
	हाल PRID_IMP_NETLOGIC_XLR716:
	हाल PRID_IMP_NETLOGIC_XLR532:
	हाल PRID_IMP_NETLOGIC_XLR308:
	हाल PRID_IMP_NETLOGIC_XLR532C:
	हाल PRID_IMP_NETLOGIC_XLR516C:
	हाल PRID_IMP_NETLOGIC_XLR508C:
	हाल PRID_IMP_NETLOGIC_XLR308C:
		c->cputype = CPU_XLR;
		__cpu_name[cpu] = "Netlogic XLR";
		अवरोध;

	हाल PRID_IMP_NETLOGIC_XLS608:
	हाल PRID_IMP_NETLOGIC_XLS408:
	हाल PRID_IMP_NETLOGIC_XLS404:
	हाल PRID_IMP_NETLOGIC_XLS208:
	हाल PRID_IMP_NETLOGIC_XLS204:
	हाल PRID_IMP_NETLOGIC_XLS108:
	हाल PRID_IMP_NETLOGIC_XLS104:
	हाल PRID_IMP_NETLOGIC_XLS616B:
	हाल PRID_IMP_NETLOGIC_XLS608B:
	हाल PRID_IMP_NETLOGIC_XLS416B:
	हाल PRID_IMP_NETLOGIC_XLS412B:
	हाल PRID_IMP_NETLOGIC_XLS408B:
	हाल PRID_IMP_NETLOGIC_XLS404B:
		c->cputype = CPU_XLR;
		__cpu_name[cpu] = "Netlogic XLS";
		अवरोध;

	शेष:
		pr_info("Unknown Netlogic chip id [%02x]!\n",
		       c->processor_id);
		c->cputype = CPU_XLR;
		अवरोध;
	पूर्ण

	अगर (c->cputype == CPU_XLP) अणु
		set_isa(c, MIPS_CPU_ISA_M64R2);
		c->options |= (MIPS_CPU_FPU | MIPS_CPU_ULRI | MIPS_CPU_MCHECK);
		/* This will be updated again after all thपढ़ोs are woken up */
		c->tlbsize = ((पढ़ो_c0_config6() >> 16) & 0xffff) + 1;
	पूर्ण अन्यथा अणु
		set_isa(c, MIPS_CPU_ISA_M64R1);
		c->tlbsize = ((पढ़ो_c0_config1() >> 25) & 0x3f) + 1;
	पूर्ण
	c->kscratch_mask = 0xf;
पूर्ण

#अगर_घोषित CONFIG_64BIT
/* For use by uaccess.h */
u64 __ua_limit;
EXPORT_SYMBOL(__ua_limit);
#पूर्ण_अगर

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
	c->fpu_msk31	= FPU_CSR_RSVD | FPU_CSR_ABS2008 | FPU_CSR_न_अंक2008;

	c->processor_id = पढ़ो_c0_prid();
	चयन (c->processor_id & PRID_COMP_MASK) अणु
	हाल PRID_COMP_LEGACY:
		cpu_probe_legacy(c, cpu);
		अवरोध;
	हाल PRID_COMP_MIPS:
		cpu_probe_mips(c, cpu);
		अवरोध;
	हाल PRID_COMP_ALCHEMY:
		cpu_probe_alchemy(c, cpu);
		अवरोध;
	हाल PRID_COMP_SIBYTE:
		cpu_probe_sibyte(c, cpu);
		अवरोध;
	हाल PRID_COMP_BROADCOM:
		cpu_probe_broadcom(c, cpu);
		अवरोध;
	हाल PRID_COMP_SANDCRAFT:
		cpu_probe_sandcraft(c, cpu);
		अवरोध;
	हाल PRID_COMP_NXP:
		cpu_probe_nxp(c, cpu);
		अवरोध;
	हाल PRID_COMP_CAVIUM:
		cpu_probe_cavium(c, cpu);
		अवरोध;
	हाल PRID_COMP_LOONGSON:
		cpu_probe_loongson(c, cpu);
		अवरोध;
	हाल PRID_COMP_INGENIC_13:
	हाल PRID_COMP_INGENIC_D0:
	हाल PRID_COMP_INGENIC_D1:
	हाल PRID_COMP_INGENIC_E1:
		cpu_probe_ingenic(c, cpu);
		अवरोध;
	हाल PRID_COMP_NETLOGIC:
		cpu_probe_netlogic(c, cpu);
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

	अगर (cpu_has_rixi) अणु
		/* Enable the RIXI exceptions */
		set_c0_pagegrain(PG_IEC);
		back_to_back_c0_hazard();
		/* Verअगरy the IEC bit is set */
		अगर (पढ़ो_c0_pagegrain() & PG_IEC)
			c->options |= MIPS_CPU_RIXIEX;
	पूर्ण

	अगर (mips_fpu_disabled)
		c->options &= ~MIPS_CPU_FPU;

	अगर (mips_dsp_disabled)
		c->ases &= ~(MIPS_ASE_DSP | MIPS_ASE_DSP2P);

	अगर (mips_htw_disabled) अणु
		c->options &= ~MIPS_CPU_HTW;
		ग_लिखो_c0_pwctl(पढ़ो_c0_pwctl() &
			       ~(1 << MIPS_PWCTL_PWEN_SHIFT));
	पूर्ण

	अगर (c->options & MIPS_CPU_FPU)
		cpu_set_fpu_opts(c);
	अन्यथा
		cpu_set_nofpu_opts(c);

	अगर (cpu_has_mips_r2_r6) अणु
		c->srsets = ((पढ़ो_c0_srsctl() >> 26) & 0x0f) + 1;
		/* R2 has Perक्रमmance Counter Interrupt indicator */
		c->options |= MIPS_CPU_PCI;
	पूर्ण
	अन्यथा
		c->srsets = 1;

	अगर (cpu_has_mips_r6)
		elf_hwcap |= HWCAP_MIPS_R6;

	अगर (cpu_has_msa) अणु
		c->msa_id = cpu_get_msa_id();
		WARN(c->msa_id & MSA_IR_WRPF,
		     "Vector register partitioning unimplemented!");
		elf_hwcap |= HWCAP_MIPS_MSA;
	पूर्ण

	अगर (cpu_has_mips16)
		elf_hwcap |= HWCAP_MIPS_MIPS16;

	अगर (cpu_has_mdmx)
		elf_hwcap |= HWCAP_MIPS_MDMX;

	अगर (cpu_has_mips3d)
		elf_hwcap |= HWCAP_MIPS_MIPS3D;

	अगर (cpu_has_smarपंचांगips)
		elf_hwcap |= HWCAP_MIPS_SMARTMIPS;

	अगर (cpu_has_dsp)
		elf_hwcap |= HWCAP_MIPS_DSP;

	अगर (cpu_has_dsp2)
		elf_hwcap |= HWCAP_MIPS_DSP2;

	अगर (cpu_has_dsp3)
		elf_hwcap |= HWCAP_MIPS_DSP3;

	अगर (cpu_has_mips16e2)
		elf_hwcap |= HWCAP_MIPS_MIPS16E2;

	अगर (cpu_has_loongson_mmi)
		elf_hwcap |= HWCAP_LOONGSON_MMI;

	अगर (cpu_has_loongson_ext)
		elf_hwcap |= HWCAP_LOONGSON_EXT;

	अगर (cpu_has_loongson_ext2)
		elf_hwcap |= HWCAP_LOONGSON_EXT2;

	अगर (cpu_has_vz)
		cpu_probe_vz(c);

	cpu_probe_vmbits(c);

	/* Synthesize CPUCFG data अगर running on Loongson processors;
	 * no-op otherwise.
	 *
	 * This looks at previously probed features, so keep this at bottom.
	 */
	loongson3_cpucfg_synthesize_data(c);

#अगर_घोषित CONFIG_64BIT
	अगर (cpu == 0)
		__ua_limit = ~((1ull << cpu_vmbits) - 1);
#पूर्ण_अगर

	reserve_exception_space(0, 0x1000);
पूर्ण

व्योम cpu_report(व्योम)
अणु
	काष्ठा cpuinfo_mips *c = &current_cpu_data;

	pr_info("CPU%d revision is: %08x (%s)\n",
		smp_processor_id(), c->processor_id, cpu_name_string());
	अगर (c->options & MIPS_CPU_FPU)
		prपूर्णांकk(KERN_INFO "FPU revision is: %08x\n", c->fpu_id);
	अगर (cpu_has_msa)
		pr_info("MSA revision is: %08x\n", c->msa_id);
पूर्ण

व्योम cpu_set_cluster(काष्ठा cpuinfo_mips *cpuinfo, अचिन्हित पूर्णांक cluster)
अणु
	/* Ensure the core number fits in the field */
	WARN_ON(cluster > (MIPS_GLOBALNUMBER_CLUSTER >>
			   MIPS_GLOBALNUMBER_CLUSTER_SHF));

	cpuinfo->globalnumber &= ~MIPS_GLOBALNUMBER_CLUSTER;
	cpuinfo->globalnumber |= cluster << MIPS_GLOBALNUMBER_CLUSTER_SHF;
पूर्ण

व्योम cpu_set_core(काष्ठा cpuinfo_mips *cpuinfo, अचिन्हित पूर्णांक core)
अणु
	/* Ensure the core number fits in the field */
	WARN_ON(core > (MIPS_GLOBALNUMBER_CORE >> MIPS_GLOBALNUMBER_CORE_SHF));

	cpuinfo->globalnumber &= ~MIPS_GLOBALNUMBER_CORE;
	cpuinfo->globalnumber |= core << MIPS_GLOBALNUMBER_CORE_SHF;
पूर्ण

व्योम cpu_set_vpe_id(काष्ठा cpuinfo_mips *cpuinfo, अचिन्हित पूर्णांक vpe)
अणु
	/* Ensure the VP(E) ID fits in the field */
	WARN_ON(vpe > (MIPS_GLOBALNUMBER_VP >> MIPS_GLOBALNUMBER_VP_SHF));

	/* Ensure we're not using VP(E)s without support */
	WARN_ON(vpe && !IS_ENABLED(CONFIG_MIPS_MT_SMP) &&
		!IS_ENABLED(CONFIG_CPU_MIPSR6));

	cpuinfo->globalnumber &= ~MIPS_GLOBALNUMBER_VP;
	cpuinfo->globalnumber |= vpe << MIPS_GLOBALNUMBER_VP_SHF;
पूर्ण
