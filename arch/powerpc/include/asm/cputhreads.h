<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_CPUTHREADS_H
#घोषणा _ASM_POWERPC_CPUTHREADS_H

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/cpumask.h>
#समावेश <यंत्र/cpu_has_feature.h>

/*
 * Mapping of thपढ़ोs to cores
 *
 * Note: This implementation is limited to a घातer of 2 number of
 * thपढ़ोs per core and the same number क्रम each core in the प्रणाली
 * (though it would work अगर some processors had less thपढ़ोs as दीर्घ
 * as the CPU numbers are still allocated, just not brought online).
 *
 * However, the API allows क्रम a dअगरferent implementation in the future
 * अगर needed, as दीर्घ as you only use the functions and not the variables
 * directly.
 */

#अगर_घोषित CONFIG_SMP
बाह्य पूर्णांक thपढ़ोs_per_core;
बाह्य पूर्णांक thपढ़ोs_per_subcore;
बाह्य पूर्णांक thपढ़ोs_shअगरt;
बाह्य cpumask_t thपढ़ोs_core_mask;
#अन्यथा
#घोषणा thपढ़ोs_per_core	1
#घोषणा thपढ़ोs_per_subcore	1
#घोषणा thपढ़ोs_shअगरt		0
#घोषणा has_big_cores		0
#घोषणा thपढ़ोs_core_mask	(*get_cpu_mask(0))
#पूर्ण_अगर

/* cpu_thपढ़ो_mask_to_cores - Return a cpumask of one per cores
 *                            hit by the argument
 *
 * @thपढ़ोs:	a cpumask of online thपढ़ोs
 *
 * This function वापसs a cpumask which will have one online cpu's
 * bit set क्रम each core that has at least one thपढ़ो set in the argument.
 *
 * This can typically be used क्रम things like IPI क्रम tlb invalidations
 * since those need to be करोne only once per core/TLB
 */
अटल अंतरभूत cpumask_t cpu_thपढ़ो_mask_to_cores(स्थिर काष्ठा cpumask *thपढ़ोs)
अणु
	cpumask_t	पंचांगp, res;
	पूर्णांक		i, cpu;

	cpumask_clear(&res);
	क्रम (i = 0; i < NR_CPUS; i += thपढ़ोs_per_core) अणु
		cpumask_shअगरt_left(&पंचांगp, &thपढ़ोs_core_mask, i);
		अगर (cpumask_पूर्णांकersects(thपढ़ोs, &पंचांगp)) अणु
			cpu = cpumask_next_and(-1, &पंचांगp, cpu_online_mask);
			अगर (cpu < nr_cpu_ids)
				cpumask_set_cpu(cpu, &res);
		पूर्ण
	पूर्ण
	वापस res;
पूर्ण

अटल अंतरभूत पूर्णांक cpu_nr_cores(व्योम)
अणु
	वापस nr_cpu_ids >> thपढ़ोs_shअगरt;
पूर्ण

अटल अंतरभूत cpumask_t cpu_online_cores_map(व्योम)
अणु
	वापस cpu_thपढ़ो_mask_to_cores(cpu_online_mask);
पूर्ण

#अगर_घोषित CONFIG_SMP
पूर्णांक cpu_core_index_of_thपढ़ो(पूर्णांक cpu);
पूर्णांक cpu_first_thपढ़ो_of_core(पूर्णांक core);
#अन्यथा
अटल अंतरभूत पूर्णांक cpu_core_index_of_thपढ़ो(पूर्णांक cpu) अणु वापस cpu; पूर्ण
अटल अंतरभूत पूर्णांक cpu_first_thपढ़ो_of_core(पूर्णांक core) अणु वापस core; पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक cpu_thपढ़ो_in_core(पूर्णांक cpu)
अणु
	वापस cpu & (thपढ़ोs_per_core - 1);
पूर्ण

अटल अंतरभूत पूर्णांक cpu_thपढ़ो_in_subcore(पूर्णांक cpu)
अणु
	वापस cpu & (thपढ़ोs_per_subcore - 1);
पूर्ण

अटल अंतरभूत पूर्णांक cpu_first_thपढ़ो_sibling(पूर्णांक cpu)
अणु
	वापस cpu & ~(thपढ़ोs_per_core - 1);
पूर्ण

अटल अंतरभूत पूर्णांक cpu_last_thपढ़ो_sibling(पूर्णांक cpu)
अणु
	वापस cpu | (thपढ़ोs_per_core - 1);
पूर्ण

अटल अंतरभूत u32 get_tensr(व्योम)
अणु
#अगर_घोषित	CONFIG_BOOKE
	अगर (cpu_has_feature(CPU_FTR_SMT))
		वापस mfspr(SPRN_TENSR);
#पूर्ण_अगर
	वापस 1;
पूर्ण

व्योम book3e_start_thपढ़ो(पूर्णांक thपढ़ो, अचिन्हित दीर्घ addr);
व्योम book3e_stop_thपढ़ो(पूर्णांक thपढ़ो);

#पूर्ण_अगर /* __ASSEMBLY__ */

#घोषणा INVALID_THREAD_HWID	0x0fff

#पूर्ण_अगर /* _ASM_POWERPC_CPUTHREADS_H */

