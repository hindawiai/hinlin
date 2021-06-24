<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  linux/include/linux/nmi.h
 */
#अगर_अघोषित LINUX_NMI_H
#घोषणा LINUX_NMI_H

#समावेश <linux/sched.h>
#समावेश <यंत्र/irq.h>
#अगर defined(CONFIG_HAVE_NMI_WATCHDOG)
#समावेश <यंत्र/nmi.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_LOCKUP_DETECTOR
व्योम lockup_detector_init(व्योम);
व्योम lockup_detector_soft_घातeroff(व्योम);
व्योम lockup_detector_cleanup(व्योम);
bool is_hardlockup(व्योम);

बाह्य पूर्णांक watchकरोg_user_enabled;
बाह्य पूर्णांक nmi_watchकरोg_user_enabled;
बाह्य पूर्णांक soft_watchकरोg_user_enabled;
बाह्य पूर्णांक watchकरोg_thresh;
बाह्य अचिन्हित दीर्घ watchकरोg_enabled;

बाह्य काष्ठा cpumask watchकरोg_cpumask;
बाह्य अचिन्हित दीर्घ *watchकरोg_cpumask_bits;
#अगर_घोषित CONFIG_SMP
बाह्य पूर्णांक sysctl_softlockup_all_cpu_backtrace;
बाह्य पूर्णांक sysctl_hardlockup_all_cpu_backtrace;
#अन्यथा
#घोषणा sysctl_softlockup_all_cpu_backtrace 0
#घोषणा sysctl_hardlockup_all_cpu_backtrace 0
#पूर्ण_अगर /* !CONFIG_SMP */

#अन्यथा /* CONFIG_LOCKUP_DETECTOR */
अटल अंतरभूत व्योम lockup_detector_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम lockup_detector_soft_घातeroff(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम lockup_detector_cleanup(व्योम) अणु पूर्ण
#पूर्ण_अगर /* !CONFIG_LOCKUP_DETECTOR */

#अगर_घोषित CONFIG_SOFTLOCKUP_DETECTOR
बाह्य व्योम touch_softlockup_watchकरोg_sched(व्योम);
बाह्य व्योम touch_softlockup_watchकरोg(व्योम);
बाह्य व्योम touch_softlockup_watchकरोg_sync(व्योम);
बाह्य व्योम touch_all_softlockup_watchकरोgs(व्योम);
बाह्य अचिन्हित पूर्णांक  softlockup_panic;

बाह्य पूर्णांक lockup_detector_online_cpu(अचिन्हित पूर्णांक cpu);
बाह्य पूर्णांक lockup_detector_offline_cpu(अचिन्हित पूर्णांक cpu);
#अन्यथा /* CONFIG_SOFTLOCKUP_DETECTOR */
अटल अंतरभूत व्योम touch_softlockup_watchकरोg_sched(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम touch_softlockup_watchकरोg(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम touch_softlockup_watchकरोg_sync(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम touch_all_softlockup_watchकरोgs(व्योम) अणु पूर्ण

#घोषणा lockup_detector_online_cpu	शून्य
#घोषणा lockup_detector_offline_cpu	शून्य
#पूर्ण_अगर /* CONFIG_SOFTLOCKUP_DETECTOR */

#अगर_घोषित CONFIG_DETECT_HUNG_TASK
व्योम reset_hung_task_detector(व्योम);
#अन्यथा
अटल अंतरभूत व्योम reset_hung_task_detector(व्योम) अणु पूर्ण
#पूर्ण_अगर

/*
 * The run state of the lockup detectors is controlled by the content of the
 * 'watchdog_enabled' variable. Each lockup detector has its dedicated bit -
 * bit 0 क्रम the hard lockup detector and bit 1 क्रम the soft lockup detector.
 *
 * 'watchdog_user_enabled', 'nmi_watchdog_user_enabled' and
 * 'soft_watchdog_user_enabled' are variables that are only used as an
 * 'interface' between the parameters in /proc/sys/kernel and the पूर्णांकernal
 * state bits in 'watchdog_enabled'. The 'watchdog_thresh' variable is
 * handled dअगरferently because its value is not boolean, and the lockup
 * detectors are 'suspended' while 'watchdog_thresh' is equal zero.
 */
#घोषणा NMI_WATCHDOG_ENABLED_BIT   0
#घोषणा SOFT_WATCHDOG_ENABLED_BIT  1
#घोषणा NMI_WATCHDOG_ENABLED      (1 << NMI_WATCHDOG_ENABLED_BIT)
#घोषणा SOFT_WATCHDOG_ENABLED     (1 << SOFT_WATCHDOG_ENABLED_BIT)

#अगर defined(CONFIG_HARDLOCKUP_DETECTOR)
बाह्य व्योम hardlockup_detector_disable(व्योम);
बाह्य अचिन्हित पूर्णांक hardlockup_panic;
#अन्यथा
अटल अंतरभूत व्योम hardlockup_detector_disable(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_HAVE_NMI_WATCHDOG) || defined(CONFIG_HARDLOCKUP_DETECTOR)
# define NMI_WATCHDOG_SYSCTL_PERM	0644
#अन्यथा
# define NMI_WATCHDOG_SYSCTL_PERM	0444
#पूर्ण_अगर

#अगर defined(CONFIG_HARDLOCKUP_DETECTOR_PERF)
बाह्य व्योम arch_touch_nmi_watchकरोg(व्योम);
बाह्य व्योम hardlockup_detector_perf_stop(व्योम);
बाह्य व्योम hardlockup_detector_perf_restart(व्योम);
बाह्य व्योम hardlockup_detector_perf_disable(व्योम);
बाह्य व्योम hardlockup_detector_perf_enable(व्योम);
बाह्य व्योम hardlockup_detector_perf_cleanup(व्योम);
बाह्य पूर्णांक hardlockup_detector_perf_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम hardlockup_detector_perf_stop(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम hardlockup_detector_perf_restart(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम hardlockup_detector_perf_disable(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम hardlockup_detector_perf_enable(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम hardlockup_detector_perf_cleanup(व्योम) अणु पूर्ण
# अगर !defined(CONFIG_HAVE_NMI_WATCHDOG)
अटल अंतरभूत पूर्णांक hardlockup_detector_perf_init(व्योम) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत व्योम arch_touch_nmi_watchकरोg(व्योम) अणुपूर्ण
# अन्यथा
अटल अंतरभूत पूर्णांक hardlockup_detector_perf_init(व्योम) अणु वापस 0; पूर्ण
# endअगर
#पूर्ण_अगर

व्योम watchकरोg_nmi_stop(व्योम);
व्योम watchकरोg_nmi_start(व्योम);
पूर्णांक watchकरोg_nmi_probe(व्योम);
पूर्णांक watchकरोg_nmi_enable(अचिन्हित पूर्णांक cpu);
व्योम watchकरोg_nmi_disable(अचिन्हित पूर्णांक cpu);

/**
 * touch_nmi_watchकरोg - restart NMI watchकरोg समयout.
 *
 * If the architecture supports the NMI watchकरोg, touch_nmi_watchकरोg()
 * may be used to reset the समयout - क्रम code which पूर्णांकentionally
 * disables पूर्णांकerrupts क्रम a दीर्घ समय. This call is stateless.
 */
अटल अंतरभूत व्योम touch_nmi_watchकरोg(व्योम)
अणु
	arch_touch_nmi_watchकरोg();
	touch_softlockup_watchकरोg();
पूर्ण

/*
 * Create trigger_all_cpu_backtrace() out of the arch-provided
 * base function. Return whether such support was available,
 * to allow calling code to fall back to some other mechanism:
 */
#अगर_घोषित arch_trigger_cpumask_backtrace
अटल अंतरभूत bool trigger_all_cpu_backtrace(व्योम)
अणु
	arch_trigger_cpumask_backtrace(cpu_online_mask, false);
	वापस true;
पूर्ण

अटल अंतरभूत bool trigger_allbutself_cpu_backtrace(व्योम)
अणु
	arch_trigger_cpumask_backtrace(cpu_online_mask, true);
	वापस true;
पूर्ण

अटल अंतरभूत bool trigger_cpumask_backtrace(काष्ठा cpumask *mask)
अणु
	arch_trigger_cpumask_backtrace(mask, false);
	वापस true;
पूर्ण

अटल अंतरभूत bool trigger_single_cpu_backtrace(पूर्णांक cpu)
अणु
	arch_trigger_cpumask_backtrace(cpumask_of(cpu), false);
	वापस true;
पूर्ण

/* generic implementation */
व्योम nmi_trigger_cpumask_backtrace(स्थिर cpumask_t *mask,
				   bool exclude_self,
				   व्योम (*उठाओ)(cpumask_t *mask));
bool nmi_cpu_backtrace(काष्ठा pt_regs *regs);

#अन्यथा
अटल अंतरभूत bool trigger_all_cpu_backtrace(व्योम)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत bool trigger_allbutself_cpu_backtrace(व्योम)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत bool trigger_cpumask_backtrace(काष्ठा cpumask *mask)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत bool trigger_single_cpu_backtrace(पूर्णांक cpu)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_HARDLOCKUP_DETECTOR_PERF
u64 hw_nmi_get_sample_period(पूर्णांक watchकरोg_thresh);
#पूर्ण_अगर

#अगर defined(CONFIG_HARDLOCKUP_CHECK_TIMESTAMP) && \
    defined(CONFIG_HARDLOCKUP_DETECTOR)
व्योम watchकरोg_update_hrसमयr_threshold(u64 period);
#अन्यथा
अटल अंतरभूत व्योम watchकरोg_update_hrसमयr_threshold(u64 period) अणु पूर्ण
#पूर्ण_अगर

काष्ठा ctl_table;
पूर्णांक proc_watchकरोg(काष्ठा ctl_table *, पूर्णांक, व्योम *, माप_प्रकार *, loff_t *);
पूर्णांक proc_nmi_watchकरोg(काष्ठा ctl_table *, पूर्णांक , व्योम *, माप_प्रकार *, loff_t *);
पूर्णांक proc_soft_watchकरोg(काष्ठा ctl_table *, पूर्णांक , व्योम *, माप_प्रकार *, loff_t *);
पूर्णांक proc_watchकरोg_thresh(काष्ठा ctl_table *, पूर्णांक , व्योम *, माप_प्रकार *, loff_t *);
पूर्णांक proc_watchकरोg_cpumask(काष्ठा ctl_table *, पूर्णांक, व्योम *, माप_प्रकार *, loff_t *);

#अगर_घोषित CONFIG_HAVE_ACPI_APEI_NMI
#समावेश <यंत्र/nmi.h>
#पूर्ण_अगर

#पूर्ण_अगर
