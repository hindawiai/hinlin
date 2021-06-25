<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ppc_cbe_cpufreq.h
 *
 * This file contains the definitions used by the cbe_cpufreq driver.
 *
 * (C) Copyright IBM Deutschland Entwicklung GmbH 2005-2007
 *
 * Author: Christian Krafft <krafft@de.ibm.com>
 *
 */

#समावेश <linux/cpufreq.h>
#समावेश <linux/types.h>

पूर्णांक cbe_cpufreq_set_pmode(पूर्णांक cpu, अचिन्हित पूर्णांक pmode);
पूर्णांक cbe_cpufreq_get_pmode(पूर्णांक cpu);

पूर्णांक cbe_cpufreq_set_pmode_pmi(पूर्णांक cpu, अचिन्हित पूर्णांक pmode);

#अगर IS_ENABLED(CONFIG_CPU_FREQ_CBE_PMI)
बाह्य bool cbe_cpufreq_has_pmi;
व्योम cbe_cpufreq_pmi_policy_init(काष्ठा cpufreq_policy *policy);
व्योम cbe_cpufreq_pmi_policy_निकास(काष्ठा cpufreq_policy *policy);
व्योम cbe_cpufreq_pmi_init(व्योम);
व्योम cbe_cpufreq_pmi_निकास(व्योम);
#अन्यथा
#घोषणा cbe_cpufreq_has_pmi (0)
अटल अंतरभूत व्योम cbe_cpufreq_pmi_policy_init(काष्ठा cpufreq_policy *policy) अणुपूर्ण
अटल अंतरभूत व्योम cbe_cpufreq_pmi_policy_निकास(काष्ठा cpufreq_policy *policy) अणुपूर्ण
अटल अंतरभूत व्योम cbe_cpufreq_pmi_init(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम cbe_cpufreq_pmi_निकास(व्योम) अणुपूर्ण
#पूर्ण_अगर
