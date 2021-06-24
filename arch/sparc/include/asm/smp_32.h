<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* smp.h: Sparc specअगरic SMP stuff.
 *
 * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)
 */

#अगर_अघोषित _SPARC_SMP_H
#घोषणा _SPARC_SMP_H

#समावेश <linux/thपढ़ोs.h>
#समावेश <यंत्र/head.h>

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/cpumask.h>

#पूर्ण_अगर /* __ASSEMBLY__ */

#अगर_घोषित CONFIG_SMP

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/asi.h>
#समावेश <linux/atomic.h>

/*
 *	Private routines/data
 */

बाह्य अचिन्हित अक्षर boot_cpu_id;
बाह्य अस्थिर अचिन्हित दीर्घ cpu_callin_map[NR_CPUS];
बाह्य cpumask_t smp_commenced_mask;
बाह्य काष्ठा linux_prom_रेजिस्टरs smp_penguin_ctable;

प्रकार व्योम (*smpfunc_t)(अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ,
		       अचिन्हित दीर्घ, अचिन्हित दीर्घ);

व्योम cpu_panic(व्योम);

/*
 *	General functions that each host प्रणाली must provide.
 */

व्योम sun4m_init_smp(व्योम);
व्योम sun4d_init_smp(व्योम);

व्योम smp_callin(व्योम);
व्योम smp_store_cpu_info(पूर्णांक);

व्योम smp_resched_पूर्णांकerrupt(व्योम);
व्योम smp_call_function_single_पूर्णांकerrupt(व्योम);
व्योम smp_call_function_पूर्णांकerrupt(व्योम);

काष्ठा seq_file;
व्योम smp_bogo(काष्ठा seq_file *);
व्योम smp_info(काष्ठा seq_file *);

काष्ठा sparc32_ipi_ops अणु
	व्योम (*cross_call)(smpfunc_t func, cpumask_t mask, अचिन्हित दीर्घ arg1,
			   अचिन्हित दीर्घ arg2, अचिन्हित दीर्घ arg3,
			   अचिन्हित दीर्घ arg4);
	व्योम (*resched)(पूर्णांक cpu);
	व्योम (*single)(पूर्णांक cpu);
	व्योम (*mask_one)(पूर्णांक cpu);
पूर्ण;
बाह्य स्थिर काष्ठा sparc32_ipi_ops *sparc32_ipi_ops;

अटल अंतरभूत व्योम xc0(smpfunc_t func)
अणु
	sparc32_ipi_ops->cross_call(func, *cpu_online_mask, 0, 0, 0, 0);
पूर्ण

अटल अंतरभूत व्योम xc1(smpfunc_t func, अचिन्हित दीर्घ arg1)
अणु
	sparc32_ipi_ops->cross_call(func, *cpu_online_mask, arg1, 0, 0, 0);
पूर्ण
अटल अंतरभूत व्योम xc2(smpfunc_t func, अचिन्हित दीर्घ arg1, अचिन्हित दीर्घ arg2)
अणु
	sparc32_ipi_ops->cross_call(func, *cpu_online_mask, arg1, arg2, 0, 0);
पूर्ण

अटल अंतरभूत व्योम xc3(smpfunc_t func, अचिन्हित दीर्घ arg1, अचिन्हित दीर्घ arg2,
		       अचिन्हित दीर्घ arg3)
अणु
	sparc32_ipi_ops->cross_call(func, *cpu_online_mask,
				    arg1, arg2, arg3, 0);
पूर्ण

अटल अंतरभूत व्योम xc4(smpfunc_t func, अचिन्हित दीर्घ arg1, अचिन्हित दीर्घ arg2,
		       अचिन्हित दीर्घ arg3, अचिन्हित दीर्घ arg4)
अणु
	sparc32_ipi_ops->cross_call(func, *cpu_online_mask,
				    arg1, arg2, arg3, arg4);
पूर्ण

व्योम arch_send_call_function_single_ipi(पूर्णांक cpu);
व्योम arch_send_call_function_ipi_mask(स्थिर काष्ठा cpumask *mask);

अटल अंतरभूत पूर्णांक cpu_logical_map(पूर्णांक cpu)
अणु
	वापस cpu;
पूर्ण

पूर्णांक hard_smp_processor_id(व्योम);

#घोषणा raw_smp_processor_id()		(current_thपढ़ो_info()->cpu)

व्योम smp_setup_cpu_possible_map(व्योम);

#पूर्ण_अगर /* !(__ASSEMBLY__) */

/* Sparc specअगरic messages. */
#घोषणा MSG_CROSS_CALL         0x0005       /* run func on cpus */

/* Empirical PROM processor mailbox स्थिरants.  If the per-cpu mailbox
 * contains something other than one of these then the ipi is from
 * Linux's active_kernel_processor.  This facility exists so that
 * the boot monitor can capture all the other cpus when one catches
 * a watchकरोg reset or the user enters the monitor using L1-A keys.
 */
#घोषणा MBOX_STOPCPU          0xFB
#घोषणा MBOX_IDLECPU          0xFC
#घोषणा MBOX_IDLECPU2         0xFD
#घोषणा MBOX_STOPCPU2         0xFE

#अन्यथा /* SMP */

#घोषणा hard_smp_processor_id()		0
#घोषणा smp_setup_cpu_possible_map() करो अणु पूर्ण जबतक (0)

#पूर्ण_अगर /* !(SMP) */
#पूर्ण_अगर /* !(_SPARC_SMP_H) */
