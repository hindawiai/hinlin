<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Definitions क्रम measuring cpuसमय on घातerpc machines.
 *
 * Copyright (C) 2006 Paul Mackerras, IBM Corp.
 *
 * If we have CONFIG_VIRT_CPU_ACCOUNTING_NATIVE, we measure cpu समय in
 * the same units as the समयbase.  Otherwise we measure cpu समय
 * in jअगरfies using the generic definitions.
 */

#अगर_अघोषित __POWERPC_CPUTIME_H
#घोषणा __POWERPC_CPUTIME_H

#अगर_घोषित CONFIG_VIRT_CPU_ACCOUNTING_NATIVE

#समावेश <linux/types.h>
#समावेश <linux/समय.स>
#समावेश <यंत्र/भाग64.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/param.h>

प्रकार u64 __nocast cpuसमय_प्रकार;
प्रकार u64 __nocast cpuसमय64_t;

#घोषणा cmpxchg_cpuसमय(ptr, old, new) cmpxchg(ptr, old, new)

#अगर_घोषित __KERNEL__
/*
 * Convert cpuसमय <-> microseconds
 */
बाह्य u64 __cpuसमय_usec_factor;

अटल अंतरभूत अचिन्हित दीर्घ cpuसमय_प्रकारo_usecs(स्थिर cpuसमय_प्रकार ct)
अणु
	वापस mulhdu((__क्रमce u64) ct, __cpuसमय_usec_factor);
पूर्ण

#घोषणा cpuसमय_प्रकारo_nsecs(cpuसमय) tb_to_ns((__क्रमce u64)cpuसमय)

/*
 * PPC64 uses PACA which is task independent क्रम storing accounting data जबतक
 * PPC32 uses काष्ठा thपढ़ो_info, thereक्रमe at task चयन the accounting data
 * has to be populated in the new task
 */
#अगर_घोषित CONFIG_PPC64
#घोषणा get_accounting(tsk)	(&get_paca()->accounting)
#घोषणा raw_get_accounting(tsk)	(&local_paca->accounting)
अटल अंतरभूत व्योम arch_vसमय_प्रकारask_चयन(काष्ठा task_काष्ठा *tsk) अणु पूर्ण

#अन्यथा
#घोषणा get_accounting(tsk)	(&task_thपढ़ो_info(tsk)->accounting)
#घोषणा raw_get_accounting(tsk)	get_accounting(tsk)
/*
 * Called from the context चयन with पूर्णांकerrupts disabled, to अक्षरge all
 * accumulated बार to the current process, and to prepare accounting on
 * the next process.
 */
अटल अंतरभूत व्योम arch_vसमय_प्रकारask_चयन(काष्ठा task_काष्ठा *prev)
अणु
	काष्ठा cpu_accounting_data *acct = get_accounting(current);
	काष्ठा cpu_accounting_data *acct0 = get_accounting(prev);

	acct->startसमय = acct0->startसमय;
पूर्ण
#पूर्ण_अगर

/*
 * account_cpu_user_entry/निकास runs "unreconciled", so can't trace,
 * can't use get_paca()
 */
अटल notrace अंतरभूत व्योम account_cpu_user_entry(व्योम)
अणु
	अचिन्हित दीर्घ tb = mftb();
	काष्ठा cpu_accounting_data *acct = raw_get_accounting(current);

	acct->uसमय += (tb - acct->startसमय_user);
	acct->startसमय = tb;
पूर्ण

अटल notrace अंतरभूत व्योम account_cpu_user_निकास(व्योम)
अणु
	अचिन्हित दीर्घ tb = mftb();
	काष्ठा cpu_accounting_data *acct = raw_get_accounting(current);

	acct->sसमय += (tb - acct->startसमय);
	acct->startसमय_user = tb;
पूर्ण

अटल notrace अंतरभूत व्योम account_stolen_समय(व्योम)
अणु
#अगर_घोषित CONFIG_PPC_SPLPAR
	अगर (firmware_has_feature(FW_FEATURE_SPLPAR)) अणु
		काष्ठा lppaca *lp = local_paca->lppaca_ptr;

		अगर (unlikely(local_paca->dtl_ridx != be64_to_cpu(lp->dtl_idx)))
			accumulate_stolen_समय();
	पूर्ण
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* __KERNEL__ */
#अन्यथा /* CONFIG_VIRT_CPU_ACCOUNTING_NATIVE */
अटल अंतरभूत व्योम account_cpu_user_entry(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम account_cpu_user_निकास(व्योम)
अणु
पूर्ण
अटल notrace अंतरभूत व्योम account_stolen_समय(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_VIRT_CPU_ACCOUNTING_NATIVE */
#पूर्ण_अगर /* __POWERPC_CPUTIME_H */
