<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * pmc.h
 * Copyright (C) 2004  David Gibson, IBM Corporation
 */
#अगर_अघोषित _POWERPC_PMC_H
#घोषणा _POWERPC_PMC_H
#अगर_घोषित __KERNEL__

#समावेश <यंत्र/ptrace.h>

प्रकार व्योम (*perf_irq_t)(काष्ठा pt_regs *);
बाह्य perf_irq_t perf_irq;

पूर्णांक reserve_pmc_hardware(perf_irq_t new_perf_irq);
व्योम release_pmc_hardware(व्योम);
व्योम ppc_enable_pmcs(व्योम);

#अगर_घोषित CONFIG_PPC_BOOK3S_64
#समावेश <यंत्र/lppaca.h>
#समावेश <यंत्र/firmware.h>

अटल अंतरभूत व्योम ppc_set_pmu_inuse(पूर्णांक inuse)
अणु
#अगर defined(CONFIG_PPC_PSERIES) || defined(CONFIG_KVM_BOOK3S_HV_POSSIBLE)
	अगर (firmware_has_feature(FW_FEATURE_LPAR)) अणु
#अगर_घोषित CONFIG_PPC_PSERIES
		get_lppaca()->pmcregs_in_use = inuse;
#पूर्ण_अगर
	पूर्ण
#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
	get_paca()->pmcregs_in_use = inuse;
#पूर्ण_अगर
#पूर्ण_अगर
पूर्ण

बाह्य व्योम घातer4_enable_pmcs(व्योम);

#अन्यथा /* CONFIG_PPC64 */

अटल अंतरभूत व्योम ppc_set_pmu_inuse(पूर्णांक inuse) अणु पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _POWERPC_PMC_H */
