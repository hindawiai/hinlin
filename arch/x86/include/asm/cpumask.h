<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_CPUMASK_H
#घोषणा _ASM_X86_CPUMASK_H
#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/cpumask.h>

बाह्य cpumask_var_t cpu_callin_mask;
बाह्य cpumask_var_t cpu_callout_mask;
बाह्य cpumask_var_t cpu_initialized_mask;
बाह्य cpumask_var_t cpu_sibling_setup_mask;

बाह्य व्योम setup_cpu_local_masks(व्योम);

/*
 * NMI and MCE exceptions need cpu_is_offline() _really_ early,
 * provide an arch_ special क्रम them to aव्योम instrumentation.
 */
#अगर NR_CPUS > 1
अटल __always_अंतरभूत bool arch_cpu_online(पूर्णांक cpu)
अणु
	वापस arch_test_bit(cpu, cpumask_bits(cpu_online_mask));
पूर्ण
#अन्यथा
अटल __always_अंतरभूत bool arch_cpu_online(पूर्णांक cpu)
अणु
	वापस cpu == 0;
पूर्ण
#पूर्ण_अगर

#घोषणा arch_cpu_is_offline(cpu)	unlikely(!arch_cpu_online(cpu))

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_X86_CPUMASK_H */
