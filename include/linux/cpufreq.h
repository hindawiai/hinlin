<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * linux/include/linux/cpufreq.h
 *
 * Copyright (C) 2001 Russell King
 *           (C) 2002 - 2003 Dominik Broकरोwski <linux@broकरो.de>
 */
#अगर_अघोषित _LINUX_CPUFREQ_H
#घोषणा _LINUX_CPUFREQ_H

#समावेश <linux/clk.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/completion.h>
#समावेश <linux/kobject.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sysfs.h>

/*********************************************************************
 *                        CPUFREQ INTERFACE                          *
 *********************************************************************/
/*
 * Frequency values here are CPU kHz
 *
 * Maximum transition latency is in nanoseconds - अगर it's unknown,
 * CPUFREQ_ETERNAL shall be used.
 */

#घोषणा CPUFREQ_ETERNAL			(-1)
#घोषणा CPUFREQ_NAME_LEN		16
/* Prपूर्णांक length क्रम names. Extra 1 space क्रम accommodating '\n' in prपूर्णांकs */
#घोषणा CPUFREQ_NAME_PLEN		(CPUFREQ_NAME_LEN + 1)

काष्ठा cpufreq_governor;

क्रमागत cpufreq_table_sorting अणु
	CPUFREQ_TABLE_UNSORTED,
	CPUFREQ_TABLE_SORTED_ASCENDING,
	CPUFREQ_TABLE_SORTED_DESCENDING
पूर्ण;

काष्ठा cpufreq_cpuinfo अणु
	अचिन्हित पूर्णांक		max_freq;
	अचिन्हित पूर्णांक		min_freq;

	/* in 10^(-9) s = nanoseconds */
	अचिन्हित पूर्णांक		transition_latency;
पूर्ण;

काष्ठा cpufreq_policy अणु
	/* CPUs sharing घड़ी, require sw coordination */
	cpumask_var_t		cpus;	/* Online CPUs only */
	cpumask_var_t		related_cpus; /* Online + Offline CPUs */
	cpumask_var_t		real_cpus; /* Related and present */

	अचिन्हित पूर्णांक		shared_type; /* ACPI: ANY or ALL affected CPUs
						should set cpufreq */
	अचिन्हित पूर्णांक		cpu;    /* cpu managing this policy, must be online */

	काष्ठा clk		*clk;
	काष्ठा cpufreq_cpuinfo	cpuinfo;/* see above */

	अचिन्हित पूर्णांक		min;    /* in kHz */
	अचिन्हित पूर्णांक		max;    /* in kHz */
	अचिन्हित पूर्णांक		cur;    /* in kHz, only needed अगर cpufreq
					 * governors are used */
	अचिन्हित पूर्णांक		suspend_freq; /* freq to set during suspend */

	अचिन्हित पूर्णांक		policy; /* see above */
	अचिन्हित पूर्णांक		last_policy; /* policy beक्रमe unplug */
	काष्ठा cpufreq_governor	*governor; /* see below */
	व्योम			*governor_data;
	अक्षर			last_governor[CPUFREQ_NAME_LEN]; /* last governor used */

	काष्ठा work_काष्ठा	update; /* अगर update_policy() needs to be
					 * called, but you're in IRQ context */

	काष्ठा freq_स्थिरraपूर्णांकs	स्थिरraपूर्णांकs;
	काष्ठा freq_qos_request	*min_freq_req;
	काष्ठा freq_qos_request	*max_freq_req;

	काष्ठा cpufreq_frequency_table	*freq_table;
	क्रमागत cpufreq_table_sorting freq_table_sorted;

	काष्ठा list_head        policy_list;
	काष्ठा kobject		kobj;
	काष्ठा completion	kobj_unरेजिस्टर;

	/*
	 * The rules क्रम this semaphore:
	 * - Any routine that wants to पढ़ो from the policy काष्ठाure will
	 *   करो a करोwn_पढ़ो on this semaphore.
	 * - Any routine that will ग_लिखो to the policy काष्ठाure and/or may take away
	 *   the policy altogether (eg. CPU hotplug), will hold this lock in ग_लिखो
	 *   mode beक्रमe करोing so.
	 */
	काष्ठा rw_semaphore	rwsem;

	/*
	 * Fast चयन flags:
	 * - fast_चयन_possible should be set by the driver अगर it can
	 *   guarantee that frequency can be changed on any CPU sharing the
	 *   policy and that the change will affect all of the policy CPUs then.
	 * - fast_चयन_enabled is to be set by governors that support fast
	 *   frequency चयनing with the help of cpufreq_enable_fast_चयन().
	 */
	bool			fast_चयन_possible;
	bool			fast_चयन_enabled;

	/*
	 * Set अगर the CPUFREQ_GOV_STRICT_TARGET flag is set क्रम the current
	 * governor.
	 */
	bool			strict_target;

	/*
	 * Preferred average समय पूर्णांकerval between consecutive invocations of
	 * the driver to set the frequency क्रम this policy.  To be set by the
	 * scaling driver (0, which is the शेष, means no preference).
	 */
	अचिन्हित पूर्णांक		transition_delay_us;

	/*
	 * Remote DVFS flag (Not added to the driver काष्ठाure as we करोn't want
	 * to access another काष्ठाure from scheduler hotpath).
	 *
	 * Should be set अगर CPUs can करो DVFS on behalf of other CPUs from
	 * dअगरferent cpufreq policies.
	 */
	bool			dvfs_possible_from_any_cpu;

	 /* Cached frequency lookup from cpufreq_driver_resolve_freq. */
	अचिन्हित पूर्णांक cached_target_freq;
	अचिन्हित पूर्णांक cached_resolved_idx;

	/* Synchronization क्रम frequency transitions */
	bool			transition_ongoing; /* Tracks transition status */
	spinlock_t		transition_lock;
	रुको_queue_head_t	transition_रुको;
	काष्ठा task_काष्ठा	*transition_task; /* Task which is करोing the transition */

	/* cpufreq-stats */
	काष्ठा cpufreq_stats	*stats;

	/* For cpufreq driver's पूर्णांकernal use */
	व्योम			*driver_data;

	/* Poपूर्णांकer to the cooling device अगर used क्रम thermal mitigation */
	काष्ठा thermal_cooling_device *cdev;

	काष्ठा notअगरier_block nb_min;
	काष्ठा notअगरier_block nb_max;
पूर्ण;

/*
 * Used क्रम passing new cpufreq policy data to the cpufreq driver's ->verअगरy()
 * callback क्रम sanitization.  That callback is only expected to modअगरy the min
 * and max values, अगर necessary, and specअगरically it must not update the
 * frequency table.
 */
काष्ठा cpufreq_policy_data अणु
	काष्ठा cpufreq_cpuinfo		cpuinfo;
	काष्ठा cpufreq_frequency_table	*freq_table;
	अचिन्हित पूर्णांक			cpu;
	अचिन्हित पूर्णांक			min;    /* in kHz */
	अचिन्हित पूर्णांक			max;    /* in kHz */
पूर्ण;

काष्ठा cpufreq_freqs अणु
	काष्ठा cpufreq_policy *policy;
	अचिन्हित पूर्णांक old;
	अचिन्हित पूर्णांक new;
	u8 flags;		/* flags of cpufreq_driver, see below. */
पूर्ण;

/* Only क्रम ACPI */
#घोषणा CPUFREQ_SHARED_TYPE_NONE (0) /* None */
#घोषणा CPUFREQ_SHARED_TYPE_HW	 (1) /* HW करोes needed coordination */
#घोषणा CPUFREQ_SHARED_TYPE_ALL	 (2) /* All dependent CPUs should set freq */
#घोषणा CPUFREQ_SHARED_TYPE_ANY	 (3) /* Freq can be set from any dependent CPU*/

#अगर_घोषित CONFIG_CPU_FREQ
काष्ठा cpufreq_policy *cpufreq_cpu_get_raw(अचिन्हित पूर्णांक cpu);
काष्ठा cpufreq_policy *cpufreq_cpu_get(अचिन्हित पूर्णांक cpu);
व्योम cpufreq_cpu_put(काष्ठा cpufreq_policy *policy);
#अन्यथा
अटल अंतरभूत काष्ठा cpufreq_policy *cpufreq_cpu_get_raw(अचिन्हित पूर्णांक cpu)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत काष्ठा cpufreq_policy *cpufreq_cpu_get(अचिन्हित पूर्णांक cpu)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम cpufreq_cpu_put(काष्ठा cpufreq_policy *policy) अणु पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool policy_is_inactive(काष्ठा cpufreq_policy *policy)
अणु
	वापस cpumask_empty(policy->cpus);
पूर्ण

अटल अंतरभूत bool policy_is_shared(काष्ठा cpufreq_policy *policy)
अणु
	वापस cpumask_weight(policy->cpus) > 1;
पूर्ण

#अगर_घोषित CONFIG_CPU_FREQ
अचिन्हित पूर्णांक cpufreq_get(अचिन्हित पूर्णांक cpu);
अचिन्हित पूर्णांक cpufreq_quick_get(अचिन्हित पूर्णांक cpu);
अचिन्हित पूर्णांक cpufreq_quick_get_max(अचिन्हित पूर्णांक cpu);
अचिन्हित पूर्णांक cpufreq_get_hw_max_freq(अचिन्हित पूर्णांक cpu);
व्योम disable_cpufreq(व्योम);

u64 get_cpu_idle_समय(अचिन्हित पूर्णांक cpu, u64 *wall, पूर्णांक io_busy);

काष्ठा cpufreq_policy *cpufreq_cpu_acquire(अचिन्हित पूर्णांक cpu);
व्योम cpufreq_cpu_release(काष्ठा cpufreq_policy *policy);
पूर्णांक cpufreq_get_policy(काष्ठा cpufreq_policy *policy, अचिन्हित पूर्णांक cpu);
व्योम refresh_frequency_limits(काष्ठा cpufreq_policy *policy);
व्योम cpufreq_update_policy(अचिन्हित पूर्णांक cpu);
व्योम cpufreq_update_limits(अचिन्हित पूर्णांक cpu);
bool have_governor_per_policy(व्योम);
bool cpufreq_supports_freq_invariance(व्योम);
काष्ठा kobject *get_governor_parent_kobj(काष्ठा cpufreq_policy *policy);
व्योम cpufreq_enable_fast_चयन(काष्ठा cpufreq_policy *policy);
व्योम cpufreq_disable_fast_चयन(काष्ठा cpufreq_policy *policy);
#अन्यथा
अटल अंतरभूत अचिन्हित पूर्णांक cpufreq_get(अचिन्हित पूर्णांक cpu)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत अचिन्हित पूर्णांक cpufreq_quick_get(अचिन्हित पूर्णांक cpu)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत अचिन्हित पूर्णांक cpufreq_quick_get_max(अचिन्हित पूर्णांक cpu)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत अचिन्हित पूर्णांक cpufreq_get_hw_max_freq(अचिन्हित पूर्णांक cpu)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत bool cpufreq_supports_freq_invariance(व्योम)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत व्योम disable_cpufreq(व्योम) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_FREQ_STAT
व्योम cpufreq_stats_create_table(काष्ठा cpufreq_policy *policy);
व्योम cpufreq_stats_मुक्त_table(काष्ठा cpufreq_policy *policy);
व्योम cpufreq_stats_record_transition(काष्ठा cpufreq_policy *policy,
				     अचिन्हित पूर्णांक new_freq);
#अन्यथा
अटल अंतरभूत व्योम cpufreq_stats_create_table(काष्ठा cpufreq_policy *policy) अणु पूर्ण
अटल अंतरभूत व्योम cpufreq_stats_मुक्त_table(काष्ठा cpufreq_policy *policy) अणु पूर्ण
अटल अंतरभूत व्योम cpufreq_stats_record_transition(काष्ठा cpufreq_policy *policy,
						   अचिन्हित पूर्णांक new_freq) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_CPU_FREQ_STAT */

/*********************************************************************
 *                      CPUFREQ DRIVER INTERFACE                     *
 *********************************************************************/

#घोषणा CPUFREQ_RELATION_L 0  /* lowest frequency at or above target */
#घोषणा CPUFREQ_RELATION_H 1  /* highest frequency below or at target */
#घोषणा CPUFREQ_RELATION_C 2  /* बंदst frequency to target */

काष्ठा freq_attr अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा cpufreq_policy *, अक्षर *);
	sमाप_प्रकार (*store)(काष्ठा cpufreq_policy *, स्थिर अक्षर *, माप_प्रकार count);
पूर्ण;

#घोषणा cpufreq_freq_attr_ro(_name)		\
अटल काष्ठा freq_attr _name =			\
__ATTR(_name, 0444, show_##_name, शून्य)

#घोषणा cpufreq_freq_attr_ro_perm(_name, _perm)	\
अटल काष्ठा freq_attr _name =			\
__ATTR(_name, _perm, show_##_name, शून्य)

#घोषणा cpufreq_freq_attr_rw(_name)		\
अटल काष्ठा freq_attr _name =			\
__ATTR(_name, 0644, show_##_name, store_##_name)

#घोषणा cpufreq_freq_attr_wo(_name)		\
अटल काष्ठा freq_attr _name =			\
__ATTR(_name, 0200, शून्य, store_##_name)

#घोषणा define_one_global_ro(_name)		\
अटल काष्ठा kobj_attribute _name =		\
__ATTR(_name, 0444, show_##_name, शून्य)

#घोषणा define_one_global_rw(_name)		\
अटल काष्ठा kobj_attribute _name =		\
__ATTR(_name, 0644, show_##_name, store_##_name)


काष्ठा cpufreq_driver अणु
	अक्षर		name[CPUFREQ_NAME_LEN];
	u16		flags;
	व्योम		*driver_data;

	/* needed by all drivers */
	पूर्णांक		(*init)(काष्ठा cpufreq_policy *policy);
	पूर्णांक		(*verअगरy)(काष्ठा cpufreq_policy_data *policy);

	/* define one out of two */
	पूर्णांक		(*setpolicy)(काष्ठा cpufreq_policy *policy);

	पूर्णांक		(*target)(काष्ठा cpufreq_policy *policy,
				  अचिन्हित पूर्णांक target_freq,
				  अचिन्हित पूर्णांक relation);	/* Deprecated */
	पूर्णांक		(*target_index)(काष्ठा cpufreq_policy *policy,
					अचिन्हित पूर्णांक index);
	अचिन्हित पूर्णांक	(*fast_चयन)(काष्ठा cpufreq_policy *policy,
				       अचिन्हित पूर्णांक target_freq);
	/*
	 * ->fast_चयन() replacement क्रम drivers that use an पूर्णांकernal
	 * representation of perक्रमmance levels and can pass hपूर्णांकs other than
	 * the target perक्रमmance level to the hardware.
	 */
	व्योम		(*adjust_perf)(अचिन्हित पूर्णांक cpu,
				       अचिन्हित दीर्घ min_perf,
				       अचिन्हित दीर्घ target_perf,
				       अचिन्हित दीर्घ capacity);

	/*
	 * Caches and वापसs the lowest driver-supported frequency greater than
	 * or equal to the target frequency, subject to any driver limitations.
	 * Does not set the frequency. Only to be implemented क्रम drivers with
	 * target().
	 */
	अचिन्हित पूर्णांक	(*resolve_freq)(काष्ठा cpufreq_policy *policy,
					अचिन्हित पूर्णांक target_freq);

	/*
	 * Only क्रम drivers with target_index() and CPUFREQ_ASYNC_NOTIFICATION
	 * unset.
	 *
	 * get_पूर्णांकermediate should वापस a stable पूर्णांकermediate frequency
	 * platक्रमm wants to चयन to and target_पूर्णांकermediate() should set CPU
	 * to that frequency, beक्रमe jumping to the frequency corresponding
	 * to 'index'. Core will take care of sending notअगरications and driver
	 * करोesn't have to handle them in target_पूर्णांकermediate() or
	 * target_index().
	 *
	 * Drivers can वापस '0' from get_intermediate() in case they don't
	 * wish to चयन to पूर्णांकermediate frequency क्रम some target frequency.
	 * In that हाल core will directly call ->target_index().
	 */
	अचिन्हित पूर्णांक	(*get_पूर्णांकermediate)(काष्ठा cpufreq_policy *policy,
					    अचिन्हित पूर्णांक index);
	पूर्णांक		(*target_पूर्णांकermediate)(काष्ठा cpufreq_policy *policy,
					       अचिन्हित पूर्णांक index);

	/* should be defined, अगर possible */
	अचिन्हित पूर्णांक	(*get)(अचिन्हित पूर्णांक cpu);

	/* Called to update policy limits on firmware notअगरications. */
	व्योम		(*update_limits)(अचिन्हित पूर्णांक cpu);

	/* optional */
	पूर्णांक		(*bios_limit)(पूर्णांक cpu, अचिन्हित पूर्णांक *limit);

	पूर्णांक		(*online)(काष्ठा cpufreq_policy *policy);
	पूर्णांक		(*offline)(काष्ठा cpufreq_policy *policy);
	पूर्णांक		(*निकास)(काष्ठा cpufreq_policy *policy);
	व्योम		(*stop_cpu)(काष्ठा cpufreq_policy *policy);
	पूर्णांक		(*suspend)(काष्ठा cpufreq_policy *policy);
	पूर्णांक		(*resume)(काष्ठा cpufreq_policy *policy);

	/* Will be called after the driver is fully initialized */
	व्योम		(*पढ़ोy)(काष्ठा cpufreq_policy *policy);

	काष्ठा freq_attr **attr;

	/* platक्रमm specअगरic boost support code */
	bool		boost_enabled;
	पूर्णांक		(*set_boost)(काष्ठा cpufreq_policy *policy, पूर्णांक state);
पूर्ण;

/* flags */

/*
 * Set by drivers that need to update पूर्णांकernale upper and lower boundaries aदीर्घ
 * with the target frequency and so the core and governors should also invoke
 * the भागer अगर the target frequency करोes not change, but the policy min or max
 * may have changed.
 */
#घोषणा CPUFREQ_NEED_UPDATE_LIMITS		BIT(0)

/* loops_per_jअगरfy or other kernel "constants" aren't affected by frequency transitions */
#घोषणा CPUFREQ_CONST_LOOPS			BIT(1)

/*
 * Set by drivers that want the core to स्वतःmatically रेजिस्टर the cpufreq
 * driver as a thermal cooling device.
 */
#घोषणा CPUFREQ_IS_COOLING_DEV			BIT(2)

/*
 * This should be set by platक्रमms having multiple घड़ी-करोमुख्यs, i.e.
 * supporting multiple policies. With this sysfs directories of governor would
 * be created in cpu/cpu<num>/cpufreq/ directory and so they can use the same
 * governor with dअगरferent tunables क्रम dअगरferent clusters.
 */
#घोषणा CPUFREQ_HAVE_GOVERNOR_PER_POLICY	BIT(3)

/*
 * Driver will करो POSTCHANGE notअगरications from outside of their ->target()
 * routine and so must set cpufreq_driver->flags with this flag, so that core
 * can handle them specially.
 */
#घोषणा CPUFREQ_ASYNC_NOTIFICATION		BIT(4)

/*
 * Set by drivers which want cpufreq core to check अगर CPU is running at a
 * frequency present in freq-table exposed by the driver. For these drivers अगर
 * CPU is found running at an out of table freq, we will try to set it to a freq
 * from the table. And अगर that fails, we will stop further boot process by
 * issuing a BUG_ON().
 */
#घोषणा CPUFREQ_NEED_INITIAL_FREQ_CHECK	BIT(5)

/*
 * Set by drivers to disallow use of governors with "dynamic_switching" flag
 * set.
 */
#घोषणा CPUFREQ_NO_AUTO_DYNAMIC_SWITCHING	BIT(6)

पूर्णांक cpufreq_रेजिस्टर_driver(काष्ठा cpufreq_driver *driver_data);
पूर्णांक cpufreq_unरेजिस्टर_driver(काष्ठा cpufreq_driver *driver_data);

bool cpufreq_driver_test_flags(u16 flags);
स्थिर अक्षर *cpufreq_get_current_driver(व्योम);
व्योम *cpufreq_get_driver_data(व्योम);

अटल अंतरभूत पूर्णांक cpufreq_thermal_control_enabled(काष्ठा cpufreq_driver *drv)
अणु
	वापस IS_ENABLED(CONFIG_CPU_THERMAL) &&
		(drv->flags & CPUFREQ_IS_COOLING_DEV);
पूर्ण

अटल अंतरभूत व्योम cpufreq_verअगरy_within_limits(काष्ठा cpufreq_policy_data *policy,
						अचिन्हित पूर्णांक min,
						अचिन्हित पूर्णांक max)
अणु
	अगर (policy->min < min)
		policy->min = min;
	अगर (policy->max < min)
		policy->max = min;
	अगर (policy->min > max)
		policy->min = max;
	अगर (policy->max > max)
		policy->max = max;
	अगर (policy->min > policy->max)
		policy->min = policy->max;
	वापस;
पूर्ण

अटल अंतरभूत व्योम
cpufreq_verअगरy_within_cpu_limits(काष्ठा cpufreq_policy_data *policy)
अणु
	cpufreq_verअगरy_within_limits(policy, policy->cpuinfo.min_freq,
				     policy->cpuinfo.max_freq);
पूर्ण

#अगर_घोषित CONFIG_CPU_FREQ
व्योम cpufreq_suspend(व्योम);
व्योम cpufreq_resume(व्योम);
पूर्णांक cpufreq_generic_suspend(काष्ठा cpufreq_policy *policy);
#अन्यथा
अटल अंतरभूत व्योम cpufreq_suspend(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम cpufreq_resume(व्योम) अणुपूर्ण
#पूर्ण_अगर

/*********************************************************************
 *                     CPUFREQ NOTIFIER INTERFACE                    *
 *********************************************************************/

#घोषणा CPUFREQ_TRANSITION_NOTIFIER	(0)
#घोषणा CPUFREQ_POLICY_NOTIFIER		(1)

/* Transition notअगरiers */
#घोषणा CPUFREQ_PRECHANGE		(0)
#घोषणा CPUFREQ_POSTCHANGE		(1)

/* Policy Notअगरiers  */
#घोषणा CPUFREQ_CREATE_POLICY		(0)
#घोषणा CPUFREQ_REMOVE_POLICY		(1)

#अगर_घोषित CONFIG_CPU_FREQ
पूर्णांक cpufreq_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित पूर्णांक list);
पूर्णांक cpufreq_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित पूर्णांक list);

व्योम cpufreq_freq_transition_begin(काष्ठा cpufreq_policy *policy,
		काष्ठा cpufreq_freqs *freqs);
व्योम cpufreq_freq_transition_end(काष्ठा cpufreq_policy *policy,
		काष्ठा cpufreq_freqs *freqs, पूर्णांक transition_failed);

#अन्यथा /* CONFIG_CPU_FREQ */
अटल अंतरभूत पूर्णांक cpufreq_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb,
						अचिन्हित पूर्णांक list)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक cpufreq_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb,
						अचिन्हित पूर्णांक list)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* !CONFIG_CPU_FREQ */

/**
 * cpufreq_scale - "old * mult / div" calculation क्रम large values (32-bit-arch
 * safe)
 * @old:   old value
 * @भाग:   भागisor
 * @mult:  multiplier
 *
 *
 * new = old * mult / भाग
 */
अटल अंतरभूत अचिन्हित दीर्घ cpufreq_scale(अचिन्हित दीर्घ old, u_पूर्णांक भाग,
		u_पूर्णांक mult)
अणु
#अगर BITS_PER_LONG == 32
	u64 result = ((u64) old) * ((u64) mult);
	करो_भाग(result, भाग);
	वापस (अचिन्हित दीर्घ) result;

#या_अगर BITS_PER_LONG == 64
	अचिन्हित दीर्घ result = old * ((u64) mult);
	result /= भाग;
	वापस result;
#पूर्ण_अगर
पूर्ण

/*********************************************************************
 *                          CPUFREQ GOVERNORS                        *
 *********************************************************************/

#घोषणा CPUFREQ_POLICY_UNKNOWN		(0)
/*
 * If (cpufreq_driver->target) exists, the ->governor decides what frequency
 * within the limits is used. If (cpufreq_driver->setpolicy> exists, these
 * two generic policies are available:
 */
#घोषणा CPUFREQ_POLICY_POWERSAVE	(1)
#घोषणा CPUFREQ_POLICY_PERFORMANCE	(2)

/*
 * The polling frequency depends on the capability of the processor. Default
 * polling frequency is 1000 बार the transition latency of the processor. The
 * ondemand governor will work on any processor with transition latency <= 10ms,
 * using appropriate sampling rate.
 */
#घोषणा LATENCY_MULTIPLIER		(1000)

काष्ठा cpufreq_governor अणु
	अक्षर	name[CPUFREQ_NAME_LEN];
	पूर्णांक	(*init)(काष्ठा cpufreq_policy *policy);
	व्योम	(*निकास)(काष्ठा cpufreq_policy *policy);
	पूर्णांक	(*start)(काष्ठा cpufreq_policy *policy);
	व्योम	(*stop)(काष्ठा cpufreq_policy *policy);
	व्योम	(*limits)(काष्ठा cpufreq_policy *policy);
	sमाप_प्रकार	(*show_setspeed)	(काष्ठा cpufreq_policy *policy,
					 अक्षर *buf);
	पूर्णांक	(*store_setspeed)	(काष्ठा cpufreq_policy *policy,
					 अचिन्हित पूर्णांक freq);
	काष्ठा list_head	governor_list;
	काष्ठा module		*owner;
	u8			flags;
पूर्ण;

/* Governor flags */

/* For governors which change frequency dynamically by themselves */
#घोषणा CPUFREQ_GOV_DYNAMIC_SWITCHING	BIT(0)

/* For governors wanting the target frequency to be set exactly */
#घोषणा CPUFREQ_GOV_STRICT_TARGET	BIT(1)


/* Pass a target to the cpufreq driver */
अचिन्हित पूर्णांक cpufreq_driver_fast_चयन(काष्ठा cpufreq_policy *policy,
					अचिन्हित पूर्णांक target_freq);
व्योम cpufreq_driver_adjust_perf(अचिन्हित पूर्णांक cpu,
				अचिन्हित दीर्घ min_perf,
				अचिन्हित दीर्घ target_perf,
				अचिन्हित दीर्घ capacity);
bool cpufreq_driver_has_adjust_perf(व्योम);
पूर्णांक cpufreq_driver_target(काष्ठा cpufreq_policy *policy,
				 अचिन्हित पूर्णांक target_freq,
				 अचिन्हित पूर्णांक relation);
पूर्णांक __cpufreq_driver_target(काष्ठा cpufreq_policy *policy,
				   अचिन्हित पूर्णांक target_freq,
				   अचिन्हित पूर्णांक relation);
अचिन्हित पूर्णांक cpufreq_driver_resolve_freq(काष्ठा cpufreq_policy *policy,
					 अचिन्हित पूर्णांक target_freq);
अचिन्हित पूर्णांक cpufreq_policy_transition_delay_us(काष्ठा cpufreq_policy *policy);
पूर्णांक cpufreq_रेजिस्टर_governor(काष्ठा cpufreq_governor *governor);
व्योम cpufreq_unरेजिस्टर_governor(काष्ठा cpufreq_governor *governor);
पूर्णांक cpufreq_start_governor(काष्ठा cpufreq_policy *policy);
व्योम cpufreq_stop_governor(काष्ठा cpufreq_policy *policy);

#घोषणा cpufreq_governor_init(__governor)			\
अटल पूर्णांक __init __governor##_init(व्योम)			\
अणु								\
	वापस cpufreq_रेजिस्टर_governor(&__governor);	\
पूर्ण								\
core_initcall(__governor##_init)

#घोषणा cpufreq_governor_निकास(__governor)			\
अटल व्योम __निकास __governor##_निकास(व्योम)			\
अणु								\
	वापस cpufreq_unरेजिस्टर_governor(&__governor);	\
पूर्ण								\
module_निकास(__governor##_निकास)

काष्ठा cpufreq_governor *cpufreq_शेष_governor(व्योम);
काष्ठा cpufreq_governor *cpufreq_fallback_governor(व्योम);

अटल अंतरभूत व्योम cpufreq_policy_apply_limits(काष्ठा cpufreq_policy *policy)
अणु
	अगर (policy->max < policy->cur)
		__cpufreq_driver_target(policy, policy->max, CPUFREQ_RELATION_H);
	अन्यथा अगर (policy->min > policy->cur)
		__cpufreq_driver_target(policy, policy->min, CPUFREQ_RELATION_L);
पूर्ण

/* Governor attribute set */
काष्ठा gov_attr_set अणु
	काष्ठा kobject kobj;
	काष्ठा list_head policy_list;
	काष्ठा mutex update_lock;
	पूर्णांक usage_count;
पूर्ण;

/* sysfs ops क्रम cpufreq governors */
बाह्य स्थिर काष्ठा sysfs_ops governor_sysfs_ops;

व्योम gov_attr_set_init(काष्ठा gov_attr_set *attr_set, काष्ठा list_head *list_node);
व्योम gov_attr_set_get(काष्ठा gov_attr_set *attr_set, काष्ठा list_head *list_node);
अचिन्हित पूर्णांक gov_attr_set_put(काष्ठा gov_attr_set *attr_set, काष्ठा list_head *list_node);

/* Governor sysfs attribute */
काष्ठा governor_attr अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा gov_attr_set *attr_set, अक्षर *buf);
	sमाप_प्रकार (*store)(काष्ठा gov_attr_set *attr_set, स्थिर अक्षर *buf,
			 माप_प्रकार count);
पूर्ण;

/*********************************************************************
 *                     FREQUENCY TABLE HELPERS                       *
 *********************************************************************/

/* Special Values of .frequency field */
#घोषणा CPUFREQ_ENTRY_INVALID	~0u
#घोषणा CPUFREQ_TABLE_END	~1u
/* Special Values of .flags field */
#घोषणा CPUFREQ_BOOST_FREQ	(1 << 0)

काष्ठा cpufreq_frequency_table अणु
	अचिन्हित पूर्णांक	flags;
	अचिन्हित पूर्णांक	driver_data; /* driver specअगरic data, not used by core */
	अचिन्हित पूर्णांक	frequency; /* kHz - करोesn't need to be in ascending
				    * order */
पूर्ण;

#अगर defined(CONFIG_CPU_FREQ) && defined(CONFIG_PM_OPP)
पूर्णांक dev_pm_opp_init_cpufreq_table(काष्ठा device *dev,
				  काष्ठा cpufreq_frequency_table **table);
व्योम dev_pm_opp_मुक्त_cpufreq_table(काष्ठा device *dev,
				   काष्ठा cpufreq_frequency_table **table);
#अन्यथा
अटल अंतरभूत पूर्णांक dev_pm_opp_init_cpufreq_table(काष्ठा device *dev,
						काष्ठा cpufreq_frequency_table
						**table)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम dev_pm_opp_मुक्त_cpufreq_table(काष्ठा device *dev,
						 काष्ठा cpufreq_frequency_table
						 **table)
अणु
पूर्ण
#पूर्ण_अगर

/*
 * cpufreq_क्रम_each_entry -	iterate over a cpufreq_frequency_table
 * @pos:	the cpufreq_frequency_table * to use as a loop cursor.
 * @table:	the cpufreq_frequency_table * to iterate over.
 */

#घोषणा cpufreq_क्रम_each_entry(pos, table)	\
	क्रम (pos = table; pos->frequency != CPUFREQ_TABLE_END; pos++)

/*
 * cpufreq_क्रम_each_entry_idx -	iterate over a cpufreq_frequency_table
 *	with index
 * @pos:	the cpufreq_frequency_table * to use as a loop cursor.
 * @table:	the cpufreq_frequency_table * to iterate over.
 * @idx:	the table entry currently being processed
 */

#घोषणा cpufreq_क्रम_each_entry_idx(pos, table, idx)	\
	क्रम (pos = table, idx = 0; pos->frequency != CPUFREQ_TABLE_END; \
		pos++, idx++)

/*
 * cpufreq_क्रम_each_valid_entry -     iterate over a cpufreq_frequency_table
 *	excluding CPUFREQ_ENTRY_INVALID frequencies.
 * @pos:        the cpufreq_frequency_table * to use as a loop cursor.
 * @table:      the cpufreq_frequency_table * to iterate over.
 */

#घोषणा cpufreq_क्रम_each_valid_entry(pos, table)			\
	क्रम (pos = table; pos->frequency != CPUFREQ_TABLE_END; pos++)	\
		अगर (pos->frequency == CPUFREQ_ENTRY_INVALID)		\
			जारी;					\
		अन्यथा

/*
 * cpufreq_क्रम_each_valid_entry_idx -     iterate with index over a cpufreq
 *	frequency_table excluding CPUFREQ_ENTRY_INVALID frequencies.
 * @pos:	the cpufreq_frequency_table * to use as a loop cursor.
 * @table:	the cpufreq_frequency_table * to iterate over.
 * @idx:	the table entry currently being processed
 */

#घोषणा cpufreq_क्रम_each_valid_entry_idx(pos, table, idx)		\
	cpufreq_क्रम_each_entry_idx(pos, table, idx)			\
		अगर (pos->frequency == CPUFREQ_ENTRY_INVALID)		\
			जारी;					\
		अन्यथा


पूर्णांक cpufreq_frequency_table_cpuinfo(काष्ठा cpufreq_policy *policy,
				    काष्ठा cpufreq_frequency_table *table);

पूर्णांक cpufreq_frequency_table_verअगरy(काष्ठा cpufreq_policy_data *policy,
				   काष्ठा cpufreq_frequency_table *table);
पूर्णांक cpufreq_generic_frequency_table_verअगरy(काष्ठा cpufreq_policy_data *policy);

पूर्णांक cpufreq_table_index_unsorted(काष्ठा cpufreq_policy *policy,
				 अचिन्हित पूर्णांक target_freq,
				 अचिन्हित पूर्णांक relation);
पूर्णांक cpufreq_frequency_table_get_index(काष्ठा cpufreq_policy *policy,
		अचिन्हित पूर्णांक freq);

sमाप_प्रकार cpufreq_show_cpus(स्थिर काष्ठा cpumask *mask, अक्षर *buf);

#अगर_घोषित CONFIG_CPU_FREQ
पूर्णांक cpufreq_boost_trigger_state(पूर्णांक state);
पूर्णांक cpufreq_boost_enabled(व्योम);
पूर्णांक cpufreq_enable_boost_support(व्योम);
bool policy_has_boost_freq(काष्ठा cpufreq_policy *policy);

/* Find lowest freq at or above target in a table in ascending order */
अटल अंतरभूत पूर्णांक cpufreq_table_find_index_al(काष्ठा cpufreq_policy *policy,
					      अचिन्हित पूर्णांक target_freq)
अणु
	काष्ठा cpufreq_frequency_table *table = policy->freq_table;
	काष्ठा cpufreq_frequency_table *pos;
	अचिन्हित पूर्णांक freq;
	पूर्णांक idx, best = -1;

	cpufreq_क्रम_each_valid_entry_idx(pos, table, idx) अणु
		freq = pos->frequency;

		अगर (freq >= target_freq)
			वापस idx;

		best = idx;
	पूर्ण

	वापस best;
पूर्ण

/* Find lowest freq at or above target in a table in descending order */
अटल अंतरभूत पूर्णांक cpufreq_table_find_index_dl(काष्ठा cpufreq_policy *policy,
					      अचिन्हित पूर्णांक target_freq)
अणु
	काष्ठा cpufreq_frequency_table *table = policy->freq_table;
	काष्ठा cpufreq_frequency_table *pos;
	अचिन्हित पूर्णांक freq;
	पूर्णांक idx, best = -1;

	cpufreq_क्रम_each_valid_entry_idx(pos, table, idx) अणु
		freq = pos->frequency;

		अगर (freq == target_freq)
			वापस idx;

		अगर (freq > target_freq) अणु
			best = idx;
			जारी;
		पूर्ण

		/* No freq found above target_freq */
		अगर (best == -1)
			वापस idx;

		वापस best;
	पूर्ण

	वापस best;
पूर्ण

/* Works only on sorted freq-tables */
अटल अंतरभूत पूर्णांक cpufreq_table_find_index_l(काष्ठा cpufreq_policy *policy,
					     अचिन्हित पूर्णांक target_freq)
अणु
	target_freq = clamp_val(target_freq, policy->min, policy->max);

	अगर (policy->freq_table_sorted == CPUFREQ_TABLE_SORTED_ASCENDING)
		वापस cpufreq_table_find_index_al(policy, target_freq);
	अन्यथा
		वापस cpufreq_table_find_index_dl(policy, target_freq);
पूर्ण

/* Find highest freq at or below target in a table in ascending order */
अटल अंतरभूत पूर्णांक cpufreq_table_find_index_ah(काष्ठा cpufreq_policy *policy,
					      अचिन्हित पूर्णांक target_freq)
अणु
	काष्ठा cpufreq_frequency_table *table = policy->freq_table;
	काष्ठा cpufreq_frequency_table *pos;
	अचिन्हित पूर्णांक freq;
	पूर्णांक idx, best = -1;

	cpufreq_क्रम_each_valid_entry_idx(pos, table, idx) अणु
		freq = pos->frequency;

		अगर (freq == target_freq)
			वापस idx;

		अगर (freq < target_freq) अणु
			best = idx;
			जारी;
		पूर्ण

		/* No freq found below target_freq */
		अगर (best == -1)
			वापस idx;

		वापस best;
	पूर्ण

	वापस best;
पूर्ण

/* Find highest freq at or below target in a table in descending order */
अटल अंतरभूत पूर्णांक cpufreq_table_find_index_dh(काष्ठा cpufreq_policy *policy,
					      अचिन्हित पूर्णांक target_freq)
अणु
	काष्ठा cpufreq_frequency_table *table = policy->freq_table;
	काष्ठा cpufreq_frequency_table *pos;
	अचिन्हित पूर्णांक freq;
	पूर्णांक idx, best = -1;

	cpufreq_क्रम_each_valid_entry_idx(pos, table, idx) अणु
		freq = pos->frequency;

		अगर (freq <= target_freq)
			वापस idx;

		best = idx;
	पूर्ण

	वापस best;
पूर्ण

/* Works only on sorted freq-tables */
अटल अंतरभूत पूर्णांक cpufreq_table_find_index_h(काष्ठा cpufreq_policy *policy,
					     अचिन्हित पूर्णांक target_freq)
अणु
	target_freq = clamp_val(target_freq, policy->min, policy->max);

	अगर (policy->freq_table_sorted == CPUFREQ_TABLE_SORTED_ASCENDING)
		वापस cpufreq_table_find_index_ah(policy, target_freq);
	अन्यथा
		वापस cpufreq_table_find_index_dh(policy, target_freq);
पूर्ण

/* Find बंदst freq to target in a table in ascending order */
अटल अंतरभूत पूर्णांक cpufreq_table_find_index_ac(काष्ठा cpufreq_policy *policy,
					      अचिन्हित पूर्णांक target_freq)
अणु
	काष्ठा cpufreq_frequency_table *table = policy->freq_table;
	काष्ठा cpufreq_frequency_table *pos;
	अचिन्हित पूर्णांक freq;
	पूर्णांक idx, best = -1;

	cpufreq_क्रम_each_valid_entry_idx(pos, table, idx) अणु
		freq = pos->frequency;

		अगर (freq == target_freq)
			वापस idx;

		अगर (freq < target_freq) अणु
			best = idx;
			जारी;
		पूर्ण

		/* No freq found below target_freq */
		अगर (best == -1)
			वापस idx;

		/* Choose the बंदst freq */
		अगर (target_freq - table[best].frequency > freq - target_freq)
			वापस idx;

		वापस best;
	पूर्ण

	वापस best;
पूर्ण

/* Find बंदst freq to target in a table in descending order */
अटल अंतरभूत पूर्णांक cpufreq_table_find_index_dc(काष्ठा cpufreq_policy *policy,
					      अचिन्हित पूर्णांक target_freq)
अणु
	काष्ठा cpufreq_frequency_table *table = policy->freq_table;
	काष्ठा cpufreq_frequency_table *pos;
	अचिन्हित पूर्णांक freq;
	पूर्णांक idx, best = -1;

	cpufreq_क्रम_each_valid_entry_idx(pos, table, idx) अणु
		freq = pos->frequency;

		अगर (freq == target_freq)
			वापस idx;

		अगर (freq > target_freq) अणु
			best = idx;
			जारी;
		पूर्ण

		/* No freq found above target_freq */
		अगर (best == -1)
			वापस idx;

		/* Choose the बंदst freq */
		अगर (table[best].frequency - target_freq > target_freq - freq)
			वापस idx;

		वापस best;
	पूर्ण

	वापस best;
पूर्ण

/* Works only on sorted freq-tables */
अटल अंतरभूत पूर्णांक cpufreq_table_find_index_c(काष्ठा cpufreq_policy *policy,
					     अचिन्हित पूर्णांक target_freq)
अणु
	target_freq = clamp_val(target_freq, policy->min, policy->max);

	अगर (policy->freq_table_sorted == CPUFREQ_TABLE_SORTED_ASCENDING)
		वापस cpufreq_table_find_index_ac(policy, target_freq);
	अन्यथा
		वापस cpufreq_table_find_index_dc(policy, target_freq);
पूर्ण

अटल अंतरभूत पूर्णांक cpufreq_frequency_table_target(काष्ठा cpufreq_policy *policy,
						 अचिन्हित पूर्णांक target_freq,
						 अचिन्हित पूर्णांक relation)
अणु
	अगर (unlikely(policy->freq_table_sorted == CPUFREQ_TABLE_UNSORTED))
		वापस cpufreq_table_index_unsorted(policy, target_freq,
						    relation);

	चयन (relation) अणु
	हाल CPUFREQ_RELATION_L:
		वापस cpufreq_table_find_index_l(policy, target_freq);
	हाल CPUFREQ_RELATION_H:
		वापस cpufreq_table_find_index_h(policy, target_freq);
	हाल CPUFREQ_RELATION_C:
		वापस cpufreq_table_find_index_c(policy, target_freq);
	शेष:
		WARN_ON_ONCE(1);
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक cpufreq_table_count_valid_entries(स्थिर काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा cpufreq_frequency_table *pos;
	पूर्णांक count = 0;

	अगर (unlikely(!policy->freq_table))
		वापस 0;

	cpufreq_क्रम_each_valid_entry(pos, policy->freq_table)
		count++;

	वापस count;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक cpufreq_boost_trigger_state(पूर्णांक state)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक cpufreq_boost_enabled(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cpufreq_enable_boost_support(व्योम)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत bool policy_has_boost_freq(काष्ठा cpufreq_policy *policy)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_ENERGY_MODEL) && defined(CONFIG_CPU_FREQ_GOV_SCHEDUTIL)
व्योम sched_cpufreq_governor_change(काष्ठा cpufreq_policy *policy,
			काष्ठा cpufreq_governor *old_gov);
#अन्यथा
अटल अंतरभूत व्योम sched_cpufreq_governor_change(काष्ठा cpufreq_policy *policy,
			काष्ठा cpufreq_governor *old_gov) अणु पूर्ण
#पूर्ण_अगर

बाह्य व्योम arch_freq_prepare_all(व्योम);
बाह्य अचिन्हित पूर्णांक arch_freq_get_on_cpu(पूर्णांक cpu);

#अगर_अघोषित arch_set_freq_scale
अटल __always_अंतरभूत
व्योम arch_set_freq_scale(स्थिर काष्ठा cpumask *cpus,
			 अचिन्हित दीर्घ cur_freq,
			 अचिन्हित दीर्घ max_freq)
अणु
पूर्ण
#पूर्ण_अगर

/* the following are really really optional */
बाह्य काष्ठा freq_attr cpufreq_freq_attr_scaling_available_freqs;
बाह्य काष्ठा freq_attr cpufreq_freq_attr_scaling_boost_freqs;
बाह्य काष्ठा freq_attr *cpufreq_generic_attr[];
पूर्णांक cpufreq_table_validate_and_sort(काष्ठा cpufreq_policy *policy);

अचिन्हित पूर्णांक cpufreq_generic_get(अचिन्हित पूर्णांक cpu);
व्योम cpufreq_generic_init(काष्ठा cpufreq_policy *policy,
		काष्ठा cpufreq_frequency_table *table,
		अचिन्हित पूर्णांक transition_latency);
#पूर्ण_अगर /* _LINUX_CPUFREQ_H */
