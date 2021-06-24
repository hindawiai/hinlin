<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 1999 Cort Dougan <cort@cs.nmt.edu>
 */
#अगर_अघोषित _ASM_POWERPC_RUNLATCH_H
#घोषणा _ASM_POWERPC_RUNLATCH_H

#अगर_घोषित CONFIG_PPC64

बाह्य व्योम __ppc64_runlatch_on(व्योम);
बाह्य व्योम __ppc64_runlatch_off(व्योम);

/*
 * We manually hard enable-disable, this is called
 * in the idle loop and we करोn't want to mess up
 * with soft-disable/enable & पूर्णांकerrupt replay.
 */
#घोषणा ppc64_runlatch_off()					\
	करो अणु							\
		अगर (cpu_has_feature(CPU_FTR_CTRL) &&		\
		    test_thपढ़ो_local_flags(_TLF_RUNLATCH)) अणु	\
			अचिन्हित दीर्घ msr = mfmsr();		\
			__hard_irq_disable();			\
			__ppc64_runlatch_off();			\
			अगर (msr & MSR_EE)			\
				__hard_irq_enable();		\
		पूर्ण      						\
	पूर्ण जबतक (0)

#घोषणा ppc64_runlatch_on()					\
	करो अणु							\
		अगर (cpu_has_feature(CPU_FTR_CTRL) &&		\
		    !test_thपढ़ो_local_flags(_TLF_RUNLATCH)) अणु	\
			अचिन्हित दीर्घ msr = mfmsr();		\
			__hard_irq_disable();			\
			__ppc64_runlatch_on();			\
			अगर (msr & MSR_EE)			\
				__hard_irq_enable();		\
		पूर्ण      						\
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा ppc64_runlatch_on()
#घोषणा ppc64_runlatch_off()
#पूर्ण_अगर /* CONFIG_PPC64 */

#पूर्ण_अगर /* _ASM_POWERPC_RUNLATCH_H */
