<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ARM specअगरic SMP header, this contains our implementation
 * details.
 */
#अगर_अघोषित __ASMARM_SMP_PLAT_H
#घोषणा __ASMARM_SMP_PLAT_H

#समावेश <linux/cpumask.h>
#समावेश <linux/err.h>

#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cputype.h>

/*
 * Return true अगर we are running on a SMP platक्रमm
 */
अटल अंतरभूत bool is_smp(व्योम)
अणु
#अगर_अघोषित CONFIG_SMP
	वापस false;
#या_अगर defined(CONFIG_SMP_ON_UP)
	बाह्य अचिन्हित पूर्णांक smp_on_up;
	वापस !!smp_on_up;
#अन्यथा
	वापस true;
#पूर्ण_अगर
पूर्ण

/**
 * smp_cpuid_part() - वापस part id क्रम a given cpu
 * @cpu:	logical cpu id.
 *
 * Return: part id of logical cpu passed as argument.
 */
अटल अंतरभूत अचिन्हित पूर्णांक smp_cpuid_part(पूर्णांक cpu)
अणु
	काष्ठा cpuinfo_arm *cpu_info = &per_cpu(cpu_data, cpu);

	वापस is_smp() ? cpu_info->cpuid & ARM_CPU_PART_MASK :
			  पढ़ो_cpuid_part();
पूर्ण

/* all SMP configurations have the extended CPUID रेजिस्टरs */
#अगर_अघोषित CONFIG_MMU
#घोषणा tlb_ops_need_broadcast()	0
#अन्यथा
अटल अंतरभूत पूर्णांक tlb_ops_need_broadcast(व्योम)
अणु
	अगर (!is_smp())
		वापस 0;

	वापस ((पढ़ो_cpuid_ext(CPUID_EXT_MMFR3) >> 12) & 0xf) < 2;
पूर्ण
#पूर्ण_अगर

#अगर !defined(CONFIG_SMP) || __LINUX_ARM_ARCH__ >= 7
#घोषणा cache_ops_need_broadcast()	0
#अन्यथा
अटल अंतरभूत पूर्णांक cache_ops_need_broadcast(व्योम)
अणु
	अगर (!is_smp())
		वापस 0;

	वापस ((पढ़ो_cpuid_ext(CPUID_EXT_MMFR3) >> 12) & 0xf) < 1;
पूर्ण
#पूर्ण_अगर

/*
 * Logical CPU mapping.
 */
बाह्य u32 __cpu_logical_map[];
#घोषणा cpu_logical_map(cpu)	__cpu_logical_map[cpu]
/*
 * Retrieve logical cpu index corresponding to a given MPIDR[23:0]
 *  - mpidr: MPIDR[23:0] to be used क्रम the look-up
 *
 * Returns the cpu logical index or -EINVAL on look-up error
 */
अटल अंतरभूत पूर्णांक get_logical_index(u32 mpidr)
अणु
	पूर्णांक cpu;
	क्रम (cpu = 0; cpu < nr_cpu_ids; cpu++)
		अगर (cpu_logical_map(cpu) == mpidr)
			वापस cpu;
	वापस -EINVAL;
पूर्ण

/*
 * NOTE ! Assembly code relies on the following
 * काष्ठाure memory layout in order to carry out load
 * multiple from its base address. For more
 * inक्रमmation check arch/arm/kernel/sleep.S
 */
काष्ठा mpidr_hash अणु
	u32	mask; /* used by sleep.S */
	u32	shअगरt_aff[3]; /* used by sleep.S */
	u32	bits;
पूर्ण;

बाह्य काष्ठा mpidr_hash mpidr_hash;

अटल अंतरभूत u32 mpidr_hash_size(व्योम)
अणु
	वापस 1 << mpidr_hash.bits;
पूर्ण

बाह्य पूर्णांक platक्रमm_can_secondary_boot(व्योम);
बाह्य पूर्णांक platक्रमm_can_cpu_hotplug(व्योम);

#अगर_घोषित CONFIG_HOTPLUG_CPU
बाह्य पूर्णांक platक्रमm_can_hotplug_cpu(अचिन्हित पूर्णांक cpu);
#अन्यथा
अटल अंतरभूत पूर्णांक platक्रमm_can_hotplug_cpu(अचिन्हित पूर्णांक cpu)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
