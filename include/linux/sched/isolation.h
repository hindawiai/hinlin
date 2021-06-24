<शैली गुरु>
#अगर_अघोषित _LINUX_SCHED_ISOLATION_H
#घोषणा _LINUX_SCHED_ISOLATION_H

#समावेश <linux/cpumask.h>
#समावेश <linux/init.h>
#समावेश <linux/tick.h>

क्रमागत hk_flags अणु
	HK_FLAG_TIMER		= 1,
	HK_FLAG_RCU		= (1 << 1),
	HK_FLAG_MISC		= (1 << 2),
	HK_FLAG_SCHED		= (1 << 3),
	HK_FLAG_TICK		= (1 << 4),
	HK_FLAG_DOMAIN		= (1 << 5),
	HK_FLAG_WQ		= (1 << 6),
	HK_FLAG_MANAGED_IRQ	= (1 << 7),
	HK_FLAG_KTHREAD		= (1 << 8),
पूर्ण;

#अगर_घोषित CONFIG_CPU_ISOLATION
DECLARE_STATIC_KEY_FALSE(housekeeping_overridden);
बाह्य पूर्णांक housekeeping_any_cpu(क्रमागत hk_flags flags);
बाह्य स्थिर काष्ठा cpumask *housekeeping_cpumask(क्रमागत hk_flags flags);
बाह्य bool housekeeping_enabled(क्रमागत hk_flags flags);
बाह्य व्योम housekeeping_affine(काष्ठा task_काष्ठा *t, क्रमागत hk_flags flags);
बाह्य bool housekeeping_test_cpu(पूर्णांक cpu, क्रमागत hk_flags flags);
बाह्य व्योम __init housekeeping_init(व्योम);

#अन्यथा

अटल अंतरभूत पूर्णांक housekeeping_any_cpu(क्रमागत hk_flags flags)
अणु
	वापस smp_processor_id();
पूर्ण

अटल अंतरभूत स्थिर काष्ठा cpumask *housekeeping_cpumask(क्रमागत hk_flags flags)
अणु
	वापस cpu_possible_mask;
पूर्ण

अटल अंतरभूत bool housekeeping_enabled(क्रमागत hk_flags flags)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम housekeeping_affine(काष्ठा task_काष्ठा *t,
				       क्रमागत hk_flags flags) अणु पूर्ण
अटल अंतरभूत व्योम housekeeping_init(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_CPU_ISOLATION */

अटल अंतरभूत bool housekeeping_cpu(पूर्णांक cpu, क्रमागत hk_flags flags)
अणु
#अगर_घोषित CONFIG_CPU_ISOLATION
	अगर (अटल_branch_unlikely(&housekeeping_overridden))
		वापस housekeeping_test_cpu(cpu, flags);
#पूर्ण_अगर
	वापस true;
पूर्ण

#पूर्ण_अगर /* _LINUX_SCHED_ISOLATION_H */
