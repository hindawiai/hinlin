<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित __ASM_ARC_SMP_H
#घोषणा __ASM_ARC_SMP_H

#अगर_घोषित CONFIG_SMP

#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/thपढ़ोs.h>

#घोषणा raw_smp_processor_id() (current_thपढ़ो_info()->cpu)

/* including cpumask.h leads to cyclic deps hence this Forward declaration */
काष्ठा cpumask;

/*
 * APIs provided by arch SMP code to generic code
 */
बाह्य व्योम arch_send_call_function_single_ipi(पूर्णांक cpu);
बाह्य व्योम arch_send_call_function_ipi_mask(स्थिर काष्ठा cpumask *mask);

/*
 * APIs provided by arch SMP code to rest of arch code
 */
बाह्य व्योम __init smp_init_cpus(व्योम);
बाह्य व्योम first_lines_of_secondary(व्योम);
बाह्य स्थिर अक्षर *arc_platक्रमm_smp_cpuinfo(व्योम);

/*
 * API expected BY platक्रमm smp code (FROM arch smp code)
 *
 * smp_ipi_irq_setup:
 *	Takes @cpu and @hwirq to which the arch-common ISR is hooked up
 */
बाह्य पूर्णांक smp_ipi_irq_setup(पूर्णांक cpu, irq_hw_number_t hwirq);

/*
 * काष्ठा plat_smp_ops	- SMP callbacks provided by platक्रमm to ARC SMP
 *
 * @info:		SoC SMP specअगरic info क्रम /proc/cpuinfo etc
 * @init_early_smp:	A SMP specअगरic h/w block can init itself
 * 			Could be common across platक्रमms so not covered by
 * 			mach_desc->init_early()
 * @init_per_cpu:	Called क्रम each core so SMP h/w block driver can करो
 * 			any needed setup per cpu (e.g. IPI request)
 * @cpu_kick:		For Master to kickstart a cpu (optionally at a PC)
 * @ipi_send:		To send IPI to a @cpu
 * @ips_clear:		To clear IPI received at @irq
 */
काष्ठा plat_smp_ops अणु
	स्थिर अक्षर 	*info;
	व्योम		(*init_early_smp)(व्योम);
	व्योम		(*init_per_cpu)(पूर्णांक cpu);
	व्योम		(*cpu_kick)(पूर्णांक cpu, अचिन्हित दीर्घ pc);
	व्योम		(*ipi_send)(पूर्णांक cpu);
	व्योम		(*ipi_clear)(पूर्णांक irq);
पूर्ण;

/* TBD: stop exporting it क्रम direct population by platक्रमm */
बाह्य काष्ठा plat_smp_ops  plat_smp_ops;

#अन्यथा /* CONFIG_SMP */

अटल अंतरभूत व्योम smp_init_cpus(व्योम) अणुपूर्ण
अटल अंतरभूत स्थिर अक्षर *arc_platक्रमm_smp_cpuinfo(व्योम)
अणु
	वापस "";
पूर्ण

#पूर्ण_अगर  /* !CONFIG_SMP */

/*
 * ARC700 करोesn't support atomic Read-Modअगरy-Write ops.
 * Originally Interrupts had to be disabled around code to gaurantee atomicity.
 * The LLOCK/SCOND insns allow writing पूर्णांकerrupt-hassle-मुक्त based atomic ops
 * based on retry-अगर-irq-in-atomic (with hardware assist).
 * However despite these, we provide the IRQ disabling variant
 *
 * (1) These insn were पूर्णांकroduced only in 4.10 release. So क्रम older released
 *	support needed.
 *
 * (2) In a SMP setup, the LLOCK/SCOND atomicity across CPUs needs to be
 *	gaurantted by the platक्रमm (not something which core handles).
 *	Assuming a platक्रमm won't, SMP Linux needs to use spinlocks + local IRQ
 *	disabling क्रम atomicity.
 *
 *	However exported spinlock API is not usable due to cyclic hdr deps
 *	(even after प्रणाली.h disपूर्णांकegration upstream)
 *	यंत्र/bitops.h -> linux/spinlock.h -> linux/preempt.h
 *		-> linux/thपढ़ो_info.h -> linux/bitops.h -> यंत्र/bitops.h
 *
 *	So the workaround is to use the lowest level arch spinlock API.
 *	The exported spinlock API is smart enough to be NOP क्रम !CONFIG_SMP,
 *	but same is not true क्रम ARCH backend, hence the need क्रम 2 variants
 */
#अगर_अघोषित CONFIG_ARC_HAS_LLSC

#समावेश <linux/irqflags.h>
#अगर_घोषित CONFIG_SMP

#समावेश <यंत्र/spinlock.h>

बाह्य arch_spinlock_t smp_atomic_ops_lock;
बाह्य arch_spinlock_t smp_bitops_lock;

#घोषणा atomic_ops_lock(flags)	करो अणु		\
	local_irq_save(flags);			\
	arch_spin_lock(&smp_atomic_ops_lock);	\
पूर्ण जबतक (0)

#घोषणा atomic_ops_unlock(flags) करो अणु		\
	arch_spin_unlock(&smp_atomic_ops_lock);	\
	local_irq_restore(flags);		\
पूर्ण जबतक (0)

#घोषणा bitops_lock(flags)	करो अणु		\
	local_irq_save(flags);			\
	arch_spin_lock(&smp_bitops_lock);	\
पूर्ण जबतक (0)

#घोषणा bitops_unlock(flags) करो अणु		\
	arch_spin_unlock(&smp_bitops_lock);	\
	local_irq_restore(flags);		\
पूर्ण जबतक (0)

#अन्यथा /* !CONFIG_SMP */

#घोषणा atomic_ops_lock(flags)		local_irq_save(flags)
#घोषणा atomic_ops_unlock(flags)	local_irq_restore(flags)

#घोषणा bitops_lock(flags)		local_irq_save(flags)
#घोषणा bitops_unlock(flags)		local_irq_restore(flags)

#पूर्ण_अगर /* !CONFIG_SMP */

#पूर्ण_अगर	/* !CONFIG_ARC_HAS_LLSC */

#पूर्ण_अगर
