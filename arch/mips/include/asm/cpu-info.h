<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1994 Walकरोrf GMBH
 * Copyright (C) 1995, 1996, 1997, 1998, 1999, 2001, 2002, 2003 Ralf Baechle
 * Copyright (C) 1996 Paul M. Antoine
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 * Copyright (C) 2004  Maciej W. Rozycki
 */
#अगर_अघोषित __ASM_CPU_INFO_H
#घोषणा __ASM_CPU_INFO_H

#समावेश <linux/cache.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/mipsregs.h>

/*
 * Descriptor क्रम a cache
 */
काष्ठा cache_desc अणु
	अचिन्हित पूर्णांक waysize;	/* Bytes per way */
	अचिन्हित लघु sets;	/* Number of lines per set */
	अचिन्हित अक्षर ways;	/* Number of ways */
	अचिन्हित अक्षर linesz;	/* Size of line in bytes */
	अचिन्हित अक्षर waybit;	/* Bits to select in a cache set */
	अचिन्हित अक्षर flags;	/* Flags describing cache properties */
पूर्ण;

काष्ठा guest_info अणु
	अचिन्हित दीर्घ		ases;
	अचिन्हित दीर्घ		ases_dyn;
	अचिन्हित दीर्घ दीर्घ	options;
	अचिन्हित दीर्घ दीर्घ	options_dyn;
	पूर्णांक			tlbsize;
	u8			conf;
	u8			kscratch_mask;
पूर्ण;

/*
 * Flag definitions
 */
#घोषणा MIPS_CACHE_NOT_PRESENT	0x00000001
#घोषणा MIPS_CACHE_VTAG		0x00000002	/* Virtually tagged cache */
#घोषणा MIPS_CACHE_ALIASES	0x00000004	/* Cache could have aliases */
#घोषणा MIPS_CACHE_IC_F_DC	0x00000008	/* Ic can refill from D-cache */
#घोषणा MIPS_IC_SNOOPS_REMOTE	0x00000010	/* Ic snoops remote stores */
#घोषणा MIPS_CACHE_PINDEX	0x00000020	/* Physically indexed cache */

काष्ठा cpuinfo_mips अणु
	u64			asid_cache;
#अगर_घोषित CONFIG_MIPS_ASID_BITS_VARIABLE
	अचिन्हित दीर्घ		asid_mask;
#पूर्ण_अगर

	/*
	 * Capability and feature descriptor काष्ठाure क्रम MIPS CPU
	 */
	अचिन्हित दीर्घ		ases;
	अचिन्हित दीर्घ दीर्घ	options;
	अचिन्हित पूर्णांक		udelay_val;
	अचिन्हित पूर्णांक		processor_id;
	अचिन्हित पूर्णांक		fpu_id;
	अचिन्हित पूर्णांक		fpu_csr31;
	अचिन्हित पूर्णांक		fpu_msk31;
	अचिन्हित पूर्णांक		msa_id;
	अचिन्हित पूर्णांक		cputype;
	पूर्णांक			isa_level;
	पूर्णांक			tlbsize;
	पूर्णांक			tlbsizevtlb;
	पूर्णांक			tlbsizeftlbsets;
	पूर्णांक			tlbsizeftlbways;
	काष्ठा cache_desc	icache; /* Primary I-cache */
	काष्ठा cache_desc	dcache; /* Primary D or combined I/D cache */
	काष्ठा cache_desc	vcache; /* Victim cache, between pcache and scache */
	काष्ठा cache_desc	scache; /* Secondary cache */
	काष्ठा cache_desc	tcache; /* Tertiary/split secondary cache */
	पूर्णांक			srsets; /* Shaकरोw रेजिस्टर sets */
	पूर्णांक			package;/* physical package number */
	अचिन्हित पूर्णांक		globalnumber;
#अगर_घोषित CONFIG_64BIT
	पूर्णांक			vmbits; /* Virtual memory size in bits */
#पूर्ण_अगर
	व्योम			*data;	/* Additional data */
	अचिन्हित पूर्णांक		watch_reg_count;   /* Number that exist */
	अचिन्हित पूर्णांक		watch_reg_use_cnt; /* Usable by ptrace */
#घोषणा NUM_WATCH_REGS 4
	u16			watch_reg_masks[NUM_WATCH_REGS];
	अचिन्हित पूर्णांक		kscratch_mask; /* Usable KScratch mask. */
	/*
	 * Cache Coherency attribute क्रम ग_लिखो-combine memory ग_लिखोs.
	 * (shअगरted by _CACHE_SHIFT)
	 */
	अचिन्हित पूर्णांक		ग_लिखोcombine;
	/*
	 * Simple counter to prevent enabling HTW in nested
	 * htw_start/htw_stop calls
	 */
	अचिन्हित पूर्णांक		htw_seq;

	/* VZ & Guest features */
	काष्ठा guest_info	guest;
	अचिन्हित पूर्णांक		gtoffset_mask;
	अचिन्हित पूर्णांक		guestid_mask;
	अचिन्हित पूर्णांक		guestid_cache;

#अगर_घोषित CONFIG_CPU_LOONGSON3_CPUCFG_EMULATION
	/* CPUCFG data क्रम this CPU, synthesized at probe समय.
	 *
	 * CPUCFG select 0 is PRId, 4 and above are unimplemented क्रम now.
	 * So the only stored values are क्रम CPUCFG selects 1-3 inclusive.
	 */
	u32 loongson3_cpucfg_data[3];
#पूर्ण_अगर
पूर्ण __attribute__((aligned(SMP_CACHE_BYTES)));

बाह्य काष्ठा cpuinfo_mips cpu_data[];
#घोषणा current_cpu_data cpu_data[smp_processor_id()]
#घोषणा raw_current_cpu_data cpu_data[raw_smp_processor_id()]
#घोषणा boot_cpu_data cpu_data[0]

बाह्य व्योम cpu_probe(व्योम);
बाह्य व्योम cpu_report(व्योम);

बाह्य स्थिर अक्षर *__cpu_name[];
#घोषणा cpu_name_string()	__cpu_name[raw_smp_processor_id()]

काष्ठा seq_file;
काष्ठा notअगरier_block;

बाह्य पूर्णांक रेजिस्टर_proc_cpuinfo_notअगरier(काष्ठा notअगरier_block *nb);
बाह्य पूर्णांक proc_cpuinfo_notअगरier_call_chain(अचिन्हित दीर्घ val, व्योम *v);

#घोषणा proc_cpuinfo_notअगरier(fn, pri)					\
(अणु									\
	अटल काष्ठा notअगरier_block fn##_nb = अणु			\
		.notअगरier_call = fn,					\
		.priority = pri						\
	पूर्ण;								\
									\
	रेजिस्टर_proc_cpuinfo_notअगरier(&fn##_nb);			\
पूर्ण)

काष्ठा proc_cpuinfo_notअगरier_args अणु
	काष्ठा seq_file *m;
	अचिन्हित दीर्घ n;
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक cpu_cluster(काष्ठा cpuinfo_mips *cpuinfo)
अणु
	/* Optimisation क्रम प्रणालीs where multiple clusters aren't used */
	अगर (!IS_ENABLED(CONFIG_CPU_MIPSR5) && !IS_ENABLED(CONFIG_CPU_MIPSR6))
		वापस 0;

	वापस (cpuinfo->globalnumber & MIPS_GLOBALNUMBER_CLUSTER) >>
		MIPS_GLOBALNUMBER_CLUSTER_SHF;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक cpu_core(काष्ठा cpuinfo_mips *cpuinfo)
अणु
	वापस (cpuinfo->globalnumber & MIPS_GLOBALNUMBER_CORE) >>
		MIPS_GLOBALNUMBER_CORE_SHF;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक cpu_vpe_id(काष्ठा cpuinfo_mips *cpuinfo)
अणु
	/* Optimisation क्रम प्रणालीs where VP(E)s aren't used */
	अगर (!IS_ENABLED(CONFIG_MIPS_MT_SMP) && !IS_ENABLED(CONFIG_CPU_MIPSR6))
		वापस 0;

	वापस (cpuinfo->globalnumber & MIPS_GLOBALNUMBER_VP) >>
		MIPS_GLOBALNUMBER_VP_SHF;
पूर्ण

बाह्य व्योम cpu_set_cluster(काष्ठा cpuinfo_mips *cpuinfo, अचिन्हित पूर्णांक cluster);
बाह्य व्योम cpu_set_core(काष्ठा cpuinfo_mips *cpuinfo, अचिन्हित पूर्णांक core);
बाह्य व्योम cpu_set_vpe_id(काष्ठा cpuinfo_mips *cpuinfo, अचिन्हित पूर्णांक vpe);

अटल अंतरभूत bool cpus_are_siblings(पूर्णांक cpua, पूर्णांक cpub)
अणु
	काष्ठा cpuinfo_mips *infoa = &cpu_data[cpua];
	काष्ठा cpuinfo_mips *infob = &cpu_data[cpub];
	अचिन्हित पूर्णांक gnuma, gnumb;

	अगर (infoa->package != infob->package)
		वापस false;

	gnuma = infoa->globalnumber & ~MIPS_GLOBALNUMBER_VP;
	gnumb = infob->globalnumber & ~MIPS_GLOBALNUMBER_VP;
	अगर (gnuma != gnumb)
		वापस false;

	वापस true;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ cpu_asid_inc(व्योम)
अणु
	वापस 1 << CONFIG_MIPS_ASID_SHIFT;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ cpu_asid_mask(काष्ठा cpuinfo_mips *cpuinfo)
अणु
#अगर_घोषित CONFIG_MIPS_ASID_BITS_VARIABLE
	वापस cpuinfo->asid_mask;
#पूर्ण_अगर
	वापस ((1 << CONFIG_MIPS_ASID_BITS) - 1) << CONFIG_MIPS_ASID_SHIFT;
पूर्ण

अटल अंतरभूत व्योम set_cpu_asid_mask(काष्ठा cpuinfo_mips *cpuinfo,
				     अचिन्हित दीर्घ asid_mask)
अणु
#अगर_घोषित CONFIG_MIPS_ASID_BITS_VARIABLE
	cpuinfo->asid_mask = asid_mask;
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* __ASM_CPU_INFO_H */
