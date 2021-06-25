<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_PROCESSOR_H
#घोषणा __ASM_SH_PROCESSOR_H

#समावेश <यंत्र/cpu-features.h>
#समावेश <यंत्र/segment.h>
#समावेश <यंत्र/cache.h>

#अगर_अघोषित __ASSEMBLY__
/*
 *  CPU type and hardware bug flags. Kept separately क्रम each CPU.
 *
 *  Each one of these also needs a CONFIG_CPU_SUBTYPE_xxx entry
 *  in arch/sh/mm/Kconfig, as well as an entry in arch/sh/kernel/setup.c
 *  क्रम parsing the subtype in get_cpu_subtype().
 */
क्रमागत cpu_type अणु
	/* SH-2 types */
	CPU_SH7619, CPU_J2,

	/* SH-2A types */
	CPU_SH7201, CPU_SH7203, CPU_SH7206, CPU_SH7263, CPU_SH7264, CPU_SH7269,
	CPU_MXG,

	/* SH-3 types */
	CPU_SH7705, CPU_SH7706, CPU_SH7707,
	CPU_SH7708, CPU_SH7708S, CPU_SH7708R,
	CPU_SH7709, CPU_SH7709A, CPU_SH7710, CPU_SH7712,
	CPU_SH7720, CPU_SH7721, CPU_SH7729,

	/* SH-4 types */
	CPU_SH7750, CPU_SH7750S, CPU_SH7750R, CPU_SH7751, CPU_SH7751R,
	CPU_SH7760, CPU_SH4_202, CPU_SH4_501,

	/* SH-4A types */
	CPU_SH7763, CPU_SH7770, CPU_SH7780, CPU_SH7781, CPU_SH7785, CPU_SH7786,
	CPU_SH7723, CPU_SH7724, CPU_SH7757, CPU_SH7734, CPU_SHX3,

	/* SH4AL-DSP types */
	CPU_SH7343, CPU_SH7722, CPU_SH7366, CPU_SH7372,

	/* Unknown subtype */
	CPU_SH_NONE
पूर्ण;

क्रमागत cpu_family अणु
	CPU_FAMILY_SH2,
	CPU_FAMILY_SH2A,
	CPU_FAMILY_SH3,
	CPU_FAMILY_SH4,
	CPU_FAMILY_SH4A,
	CPU_FAMILY_SH4AL_DSP,
	CPU_FAMILY_UNKNOWN,
पूर्ण;

/*
 * TLB inक्रमmation काष्ठाure
 *
 * Defined क्रम both I and D tlb, per-processor.
 */
काष्ठा tlb_info अणु
	अचिन्हित दीर्घ दीर्घ next;
	अचिन्हित दीर्घ दीर्घ first;
	अचिन्हित दीर्घ दीर्घ last;

	अचिन्हित पूर्णांक entries;
	अचिन्हित पूर्णांक step;

	अचिन्हित दीर्घ flags;
पूर्ण;

काष्ठा sh_cpuinfo अणु
	अचिन्हित पूर्णांक type, family;
	पूर्णांक cut_major, cut_minor;
	अचिन्हित दीर्घ loops_per_jअगरfy;
	अचिन्हित दीर्घ asid_cache;

	काष्ठा cache_info icache;	/* Primary I-cache */
	काष्ठा cache_info dcache;	/* Primary D-cache */
	काष्ठा cache_info scache;	/* Secondary cache */

	/* TLB info */
	काष्ठा tlb_info itlb;
	काष्ठा tlb_info dtlb;

	अचिन्हित पूर्णांक phys_bits;
	अचिन्हित दीर्घ flags;
पूर्ण __attribute__ ((aligned(L1_CACHE_BYTES)));

बाह्य काष्ठा sh_cpuinfo cpu_data[];
#घोषणा boot_cpu_data cpu_data[0]
#घोषणा current_cpu_data cpu_data[smp_processor_id()]
#घोषणा raw_current_cpu_data cpu_data[raw_smp_processor_id()]

#घोषणा cpu_sleep()	__यंत्र__ __अस्थिर__ ("sleep" : : : "memory")
#घोषणा cpu_relax()	barrier()

व्योम शेष_idle(व्योम);
व्योम stop_this_cpu(व्योम *);

/* Forward decl */
काष्ठा seq_operations;
काष्ठा task_काष्ठा;

बाह्य काष्ठा pt_regs fake_swapper_regs;

बाह्य व्योम cpu_init(व्योम);
बाह्य व्योम cpu_probe(व्योम);

/* arch/sh/kernel/process.c */
बाह्य अचिन्हित पूर्णांक xstate_size;
बाह्य व्योम मुक्त_thपढ़ो_xstate(काष्ठा task_काष्ठा *);
बाह्य काष्ठा kmem_cache *task_xstate_cachep;

/* arch/sh/mm/alignment.c */
बाह्य पूर्णांक get_unalign_ctl(काष्ठा task_काष्ठा *, अचिन्हित दीर्घ addr);
बाह्य पूर्णांक set_unalign_ctl(काष्ठा task_काष्ठा *, अचिन्हित पूर्णांक val);

#घोषणा GET_UNALIGN_CTL(tsk, addr)	get_unalign_ctl((tsk), (addr))
#घोषणा SET_UNALIGN_CTL(tsk, val)	set_unalign_ctl((tsk), (val))

/* arch/sh/mm/init.c */
बाह्य अचिन्हित पूर्णांक mem_init_करोne;

/* arch/sh/kernel/setup.c */
स्थिर अक्षर *get_cpu_subtype(काष्ठा sh_cpuinfo *c);
बाह्य स्थिर काष्ठा seq_operations cpuinfo_op;

/* thपढ़ो_काष्ठा flags */
#घोषणा SH_THREAD_UAC_NOPRINT	(1 << 0)
#घोषणा SH_THREAD_UAC_SIGBUS	(1 << 1)
#घोषणा SH_THREAD_UAC_MASK	(SH_THREAD_UAC_NOPRINT | SH_THREAD_UAC_SIGBUS)

/* processor boot mode configuration */
#घोषणा MODE_PIN0 (1 << 0)
#घोषणा MODE_PIN1 (1 << 1)
#घोषणा MODE_PIN2 (1 << 2)
#घोषणा MODE_PIN3 (1 << 3)
#घोषणा MODE_PIN4 (1 << 4)
#घोषणा MODE_PIN5 (1 << 5)
#घोषणा MODE_PIN6 (1 << 6)
#घोषणा MODE_PIN7 (1 << 7)
#घोषणा MODE_PIN8 (1 << 8)
#घोषणा MODE_PIN9 (1 << 9)
#घोषणा MODE_PIN10 (1 << 10)
#घोषणा MODE_PIN11 (1 << 11)
#घोषणा MODE_PIN12 (1 << 12)
#घोषणा MODE_PIN13 (1 << 13)
#घोषणा MODE_PIN14 (1 << 14)
#घोषणा MODE_PIN15 (1 << 15)

पूर्णांक generic_mode_pins(व्योम);
पूर्णांक test_mode_pin(पूर्णांक pin);

#अगर_घोषित CONFIG_VSYSCALL
पूर्णांक vsyscall_init(व्योम);
#अन्यथा
#घोषणा vsyscall_init() करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * SH-2A has both 16 and 32-bit opcodes, करो lame encoding checks.
 */
#अगर_घोषित CONFIG_CPU_SH2A
बाह्य अचिन्हित पूर्णांक inकाष्ठाion_size(अचिन्हित पूर्णांक insn);
#अन्यथा
#घोषणा inकाष्ठाion_size(insn)	(2)
#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */

#समावेश <यंत्र/processor_32.h>

#पूर्ण_अगर /* __ASM_SH_PROCESSOR_H */
