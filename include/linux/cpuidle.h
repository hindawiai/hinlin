<शैली गुरु>
/*
 * cpuidle.h - a generic framework क्रम CPU idle घातer management
 *
 * (C) 2007 Venkatesh Pallipadi <venkatesh.pallipadi@पूर्णांकel.com>
 *          Shaohua Li <shaohua.li@पूर्णांकel.com>
 *          Adam Belay <abelay@novell.com>
 *
 * This code is licenced under the GPL.
 */

#अगर_अघोषित _LINUX_CPUIDLE_H
#घोषणा _LINUX_CPUIDLE_H

#समावेश <linux/percpu.h>
#समावेश <linux/list.h>
#समावेश <linux/hrसमयr.h>

#घोषणा CPUIDLE_STATE_MAX	10
#घोषणा CPUIDLE_NAME_LEN	16
#घोषणा CPUIDLE_DESC_LEN	32

काष्ठा module;

काष्ठा cpuidle_device;
काष्ठा cpuidle_driver;


/****************************
 * CPUIDLE DEVICE INTERFACE *
 ****************************/

#घोषणा CPUIDLE_STATE_DISABLED_BY_USER		BIT(0)
#घोषणा CPUIDLE_STATE_DISABLED_BY_DRIVER	BIT(1)

काष्ठा cpuidle_state_usage अणु
	अचिन्हित दीर्घ दीर्घ	disable;
	अचिन्हित दीर्घ दीर्घ	usage;
	u64			समय_ns;
	अचिन्हित दीर्घ दीर्घ	above; /* Number of बार it's been too deep */
	अचिन्हित दीर्घ दीर्घ	below; /* Number of बार it's been too shallow */
	अचिन्हित दीर्घ दीर्घ	rejected; /* Number of बार idle entry was rejected */
#अगर_घोषित CONFIG_SUSPEND
	अचिन्हित दीर्घ दीर्घ	s2idle_usage;
	अचिन्हित दीर्घ दीर्घ	s2idle_समय; /* in US */
#पूर्ण_अगर
पूर्ण;

काष्ठा cpuidle_state अणु
	अक्षर		name[CPUIDLE_NAME_LEN];
	अक्षर		desc[CPUIDLE_DESC_LEN];

	s64		निकास_latency_ns;
	s64		target_residency_ns;
	अचिन्हित पूर्णांक	flags;
	अचिन्हित पूर्णांक	निकास_latency; /* in US */
	पूर्णांक		घातer_usage; /* in mW */
	अचिन्हित पूर्णांक	target_residency; /* in US */

	पूर्णांक (*enter)	(काष्ठा cpuidle_device *dev,
			काष्ठा cpuidle_driver *drv,
			पूर्णांक index);

	पूर्णांक (*enter_dead) (काष्ठा cpuidle_device *dev, पूर्णांक index);

	/*
	 * CPUs execute ->enter_s2idle with the local tick or entire समयkeeping
	 * suspended, so it must not re-enable पूर्णांकerrupts at any poपूर्णांक (even
	 * temporarily) or attempt to change states of घड़ी event devices.
	 *
	 * This callback may poपूर्णांक to the same function as ->enter अगर all of
	 * the above requirements are met by it.
	 */
	पूर्णांक (*enter_s2idle)(काष्ठा cpuidle_device *dev,
			    काष्ठा cpuidle_driver *drv,
			    पूर्णांक index);
पूर्ण;

/* Idle State Flags */
#घोषणा CPUIDLE_FLAG_NONE       	(0x00)
#घोषणा CPUIDLE_FLAG_POLLING		BIT(0) /* polling state */
#घोषणा CPUIDLE_FLAG_COUPLED		BIT(1) /* state applies to multiple cpus */
#घोषणा CPUIDLE_FLAG_TIMER_STOP 	BIT(2) /* समयr is stopped on this state */
#घोषणा CPUIDLE_FLAG_UNUSABLE		BIT(3) /* aव्योम using this state */
#घोषणा CPUIDLE_FLAG_OFF		BIT(4) /* disable this state by शेष */
#घोषणा CPUIDLE_FLAG_TLB_FLUSHED	BIT(5) /* idle-state flushes TLBs */
#घोषणा CPUIDLE_FLAG_RCU_IDLE		BIT(6) /* idle-state takes care of RCU */

काष्ठा cpuidle_device_kobj;
काष्ठा cpuidle_state_kobj;
काष्ठा cpuidle_driver_kobj;

काष्ठा cpuidle_device अणु
	अचिन्हित पूर्णांक		रेजिस्टरed:1;
	अचिन्हित पूर्णांक		enabled:1;
	अचिन्हित पूर्णांक		poll_समय_limit:1;
	अचिन्हित पूर्णांक		cpu;
	kसमय_प्रकार			next_hrसमयr;

	पूर्णांक			last_state_idx;
	u64			last_residency_ns;
	u64			poll_limit_ns;
	u64			क्रमced_idle_latency_limit_ns;
	काष्ठा cpuidle_state_usage	states_usage[CPUIDLE_STATE_MAX];
	काष्ठा cpuidle_state_kobj *kobjs[CPUIDLE_STATE_MAX];
	काष्ठा cpuidle_driver_kobj *kobj_driver;
	काष्ठा cpuidle_device_kobj *kobj_dev;
	काष्ठा list_head 	device_list;

#अगर_घोषित CONFIG_ARCH_NEEDS_CPU_IDLE_COUPLED
	cpumask_t		coupled_cpus;
	काष्ठा cpuidle_coupled	*coupled;
#पूर्ण_अगर
पूर्ण;

DECLARE_PER_CPU(काष्ठा cpuidle_device *, cpuidle_devices);
DECLARE_PER_CPU(काष्ठा cpuidle_device, cpuidle_dev);

/****************************
 * CPUIDLE DRIVER INTERFACE *
 ****************************/

काष्ठा cpuidle_driver अणु
	स्थिर अक्षर		*name;
	काष्ठा module 		*owner;

        /* used by the cpuidle framework to setup the broadcast समयr */
	अचिन्हित पूर्णांक            bस_समयr:1;
	/* states array must be ordered in decreasing घातer consumption */
	काष्ठा cpuidle_state	states[CPUIDLE_STATE_MAX];
	पूर्णांक			state_count;
	पूर्णांक			safe_state_index;

	/* the driver handles the cpus in cpumask */
	काष्ठा cpumask		*cpumask;

	/* preferred governor to चयन at रेजिस्टर समय */
	स्थिर अक्षर		*governor;
पूर्ण;

#अगर_घोषित CONFIG_CPU_IDLE
बाह्य व्योम disable_cpuidle(व्योम);
बाह्य bool cpuidle_not_available(काष्ठा cpuidle_driver *drv,
				  काष्ठा cpuidle_device *dev);

बाह्य पूर्णांक cpuidle_select(काष्ठा cpuidle_driver *drv,
			  काष्ठा cpuidle_device *dev,
			  bool *stop_tick);
बाह्य पूर्णांक cpuidle_enter(काष्ठा cpuidle_driver *drv,
			 काष्ठा cpuidle_device *dev, पूर्णांक index);
बाह्य व्योम cpuidle_reflect(काष्ठा cpuidle_device *dev, पूर्णांक index);
बाह्य u64 cpuidle_poll_समय(काष्ठा cpuidle_driver *drv,
			     काष्ठा cpuidle_device *dev);

बाह्य पूर्णांक cpuidle_रेजिस्टर_driver(काष्ठा cpuidle_driver *drv);
बाह्य काष्ठा cpuidle_driver *cpuidle_get_driver(व्योम);
बाह्य व्योम cpuidle_driver_state_disabled(काष्ठा cpuidle_driver *drv, पूर्णांक idx,
					bool disable);
बाह्य व्योम cpuidle_unरेजिस्टर_driver(काष्ठा cpuidle_driver *drv);
बाह्य पूर्णांक cpuidle_रेजिस्टर_device(काष्ठा cpuidle_device *dev);
बाह्य व्योम cpuidle_unरेजिस्टर_device(काष्ठा cpuidle_device *dev);
बाह्य पूर्णांक cpuidle_रेजिस्टर(काष्ठा cpuidle_driver *drv,
			    स्थिर काष्ठा cpumask *स्थिर coupled_cpus);
बाह्य व्योम cpuidle_unरेजिस्टर(काष्ठा cpuidle_driver *drv);
बाह्य व्योम cpuidle_छोड़ो_and_lock(व्योम);
बाह्य व्योम cpuidle_resume_and_unlock(व्योम);
बाह्य व्योम cpuidle_छोड़ो(व्योम);
बाह्य व्योम cpuidle_resume(व्योम);
बाह्य पूर्णांक cpuidle_enable_device(काष्ठा cpuidle_device *dev);
बाह्य व्योम cpuidle_disable_device(काष्ठा cpuidle_device *dev);
बाह्य पूर्णांक cpuidle_play_dead(व्योम);

बाह्य काष्ठा cpuidle_driver *cpuidle_get_cpu_driver(काष्ठा cpuidle_device *dev);
अटल अंतरभूत काष्ठा cpuidle_device *cpuidle_get_device(व्योम)
अणुवापस __this_cpu_पढ़ो(cpuidle_devices); पूर्ण
#अन्यथा
अटल अंतरभूत व्योम disable_cpuidle(व्योम) अणु पूर्ण
अटल अंतरभूत bool cpuidle_not_available(काष्ठा cpuidle_driver *drv,
					 काष्ठा cpuidle_device *dev)
अणुवापस true; पूर्ण
अटल अंतरभूत पूर्णांक cpuidle_select(काष्ठा cpuidle_driver *drv,
				 काष्ठा cpuidle_device *dev, bool *stop_tick)
अणुवापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक cpuidle_enter(काष्ठा cpuidle_driver *drv,
				काष्ठा cpuidle_device *dev, पूर्णांक index)
अणुवापस -ENODEV; पूर्ण
अटल अंतरभूत व्योम cpuidle_reflect(काष्ठा cpuidle_device *dev, पूर्णांक index) अणु पूर्ण
अटल अंतरभूत u64 cpuidle_poll_समय(काष्ठा cpuidle_driver *drv,
			     काष्ठा cpuidle_device *dev)
अणुवापस 0; पूर्ण
अटल अंतरभूत पूर्णांक cpuidle_रेजिस्टर_driver(काष्ठा cpuidle_driver *drv)
अणुवापस -ENODEV; पूर्ण
अटल अंतरभूत काष्ठा cpuidle_driver *cpuidle_get_driver(व्योम) अणुवापस शून्य; पूर्ण
अटल अंतरभूत व्योम cpuidle_driver_state_disabled(काष्ठा cpuidle_driver *drv,
					       पूर्णांक idx, bool disable) अणु पूर्ण
अटल अंतरभूत व्योम cpuidle_unरेजिस्टर_driver(काष्ठा cpuidle_driver *drv) अणु पूर्ण
अटल अंतरभूत पूर्णांक cpuidle_रेजिस्टर_device(काष्ठा cpuidle_device *dev)
अणुवापस -ENODEV; पूर्ण
अटल अंतरभूत व्योम cpuidle_unरेजिस्टर_device(काष्ठा cpuidle_device *dev) अणु पूर्ण
अटल अंतरभूत पूर्णांक cpuidle_रेजिस्टर(काष्ठा cpuidle_driver *drv,
				   स्थिर काष्ठा cpumask *स्थिर coupled_cpus)
अणुवापस -ENODEV; पूर्ण
अटल अंतरभूत व्योम cpuidle_unरेजिस्टर(काष्ठा cpuidle_driver *drv) अणु पूर्ण
अटल अंतरभूत व्योम cpuidle_छोड़ो_and_lock(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम cpuidle_resume_and_unlock(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम cpuidle_छोड़ो(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम cpuidle_resume(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक cpuidle_enable_device(काष्ठा cpuidle_device *dev)
अणुवापस -ENODEV; पूर्ण
अटल अंतरभूत व्योम cpuidle_disable_device(काष्ठा cpuidle_device *dev) अणु पूर्ण
अटल अंतरभूत पूर्णांक cpuidle_play_dead(व्योम) अणुवापस -ENODEV; पूर्ण
अटल अंतरभूत काष्ठा cpuidle_driver *cpuidle_get_cpu_driver(
	काष्ठा cpuidle_device *dev) अणुवापस शून्य; पूर्ण
अटल अंतरभूत काष्ठा cpuidle_device *cpuidle_get_device(व्योम) अणुवापस शून्य; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_IDLE
बाह्य पूर्णांक cpuidle_find_deepest_state(काष्ठा cpuidle_driver *drv,
				      काष्ठा cpuidle_device *dev,
				      u64 latency_limit_ns);
बाह्य पूर्णांक cpuidle_enter_s2idle(काष्ठा cpuidle_driver *drv,
				काष्ठा cpuidle_device *dev);
बाह्य व्योम cpuidle_use_deepest_state(u64 latency_limit_ns);
#अन्यथा
अटल अंतरभूत पूर्णांक cpuidle_find_deepest_state(काष्ठा cpuidle_driver *drv,
					     काष्ठा cpuidle_device *dev,
					     u64 latency_limit_ns)
अणुवापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक cpuidle_enter_s2idle(काष्ठा cpuidle_driver *drv,
				       काष्ठा cpuidle_device *dev)
अणुवापस -ENODEV; पूर्ण
अटल अंतरभूत व्योम cpuidle_use_deepest_state(u64 latency_limit_ns)
अणु
पूर्ण
#पूर्ण_अगर

/* kernel/sched/idle.c */
बाह्य व्योम sched_idle_set_state(काष्ठा cpuidle_state *idle_state);
बाह्य व्योम शेष_idle_call(व्योम);

#अगर_घोषित CONFIG_ARCH_NEEDS_CPU_IDLE_COUPLED
व्योम cpuidle_coupled_parallel_barrier(काष्ठा cpuidle_device *dev, atomic_t *a);
#अन्यथा
अटल अंतरभूत व्योम cpuidle_coupled_parallel_barrier(काष्ठा cpuidle_device *dev, atomic_t *a)
अणु
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_IDLE) && defined(CONFIG_ARCH_HAS_CPU_RELAX)
व्योम cpuidle_poll_state_init(काष्ठा cpuidle_driver *drv);
#अन्यथा
अटल अंतरभूत व्योम cpuidle_poll_state_init(काष्ठा cpuidle_driver *drv) अणुपूर्ण
#पूर्ण_अगर

/******************************
 * CPUIDLE GOVERNOR INTERFACE *
 ******************************/

काष्ठा cpuidle_governor अणु
	अक्षर			name[CPUIDLE_NAME_LEN];
	काष्ठा list_head 	governor_list;
	अचिन्हित पूर्णांक		rating;

	पूर्णांक  (*enable)		(काष्ठा cpuidle_driver *drv,
					काष्ठा cpuidle_device *dev);
	व्योम (*disable)		(काष्ठा cpuidle_driver *drv,
					काष्ठा cpuidle_device *dev);

	पूर्णांक  (*select)		(काष्ठा cpuidle_driver *drv,
					काष्ठा cpuidle_device *dev,
					bool *stop_tick);
	व्योम (*reflect)		(काष्ठा cpuidle_device *dev, पूर्णांक index);
पूर्ण;

बाह्य पूर्णांक cpuidle_रेजिस्टर_governor(काष्ठा cpuidle_governor *gov);
बाह्य s64 cpuidle_governor_latency_req(अचिन्हित पूर्णांक cpu);

#घोषणा __CPU_PM_CPU_IDLE_ENTER(low_level_idle_enter,			\
				idx,					\
				state,					\
				is_retention)				\
(अणु									\
	पूर्णांक __ret = 0;							\
									\
	अगर (!idx) अणु							\
		cpu_करो_idle();						\
		वापस idx;						\
	पूर्ण								\
									\
	अगर (!is_retention)						\
		__ret =  cpu_pm_enter();				\
	अगर (!__ret) अणु							\
		__ret = low_level_idle_enter(state);			\
		अगर (!is_retention)					\
			cpu_pm_निकास();					\
	पूर्ण								\
									\
	__ret ? -1 : idx;						\
पूर्ण)

#घोषणा CPU_PM_CPU_IDLE_ENTER(low_level_idle_enter, idx)	\
	__CPU_PM_CPU_IDLE_ENTER(low_level_idle_enter, idx, idx, 0)

#घोषणा CPU_PM_CPU_IDLE_ENTER_RETENTION(low_level_idle_enter, idx)	\
	__CPU_PM_CPU_IDLE_ENTER(low_level_idle_enter, idx, idx, 1)

#घोषणा CPU_PM_CPU_IDLE_ENTER_PARAM(low_level_idle_enter, idx, state)	\
	__CPU_PM_CPU_IDLE_ENTER(low_level_idle_enter, idx, state, 0)

#घोषणा CPU_PM_CPU_IDLE_ENTER_RETENTION_PARAM(low_level_idle_enter, idx, state)	\
	__CPU_PM_CPU_IDLE_ENTER(low_level_idle_enter, idx, state, 1)

#पूर्ण_अगर /* _LINUX_CPUIDLE_H */
