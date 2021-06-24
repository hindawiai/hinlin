<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Tick related global functions
 */
#अगर_अघोषित _LINUX_TICK_H
#घोषणा _LINUX_TICK_H

#समावेश <linux/घड़ीchips.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/percpu.h>
#समावेश <linux/context_tracking_state.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/sched.h>
#समावेश <linux/rcupdate.h>

#अगर_घोषित CONFIG_GENERIC_CLOCKEVENTS
बाह्य व्योम __init tick_init(व्योम);
/* Should be core only, but ARM BL चयनer requires it */
बाह्य व्योम tick_suspend_local(व्योम);
/* Should be core only, but XEN resume magic and ARM BL चयनer require it */
बाह्य व्योम tick_resume_local(व्योम);
बाह्य व्योम tick_hanकरोver_करो_समयr(व्योम);
बाह्य व्योम tick_cleanup_dead_cpu(पूर्णांक cpu);
#अन्यथा /* CONFIG_GENERIC_CLOCKEVENTS */
अटल अंतरभूत व्योम tick_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम tick_suspend_local(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम tick_resume_local(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम tick_hanकरोver_करो_समयr(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम tick_cleanup_dead_cpu(पूर्णांक cpu) अणु पूर्ण
#पूर्ण_अगर /* !CONFIG_GENERIC_CLOCKEVENTS */

#अगर defined(CONFIG_GENERIC_CLOCKEVENTS) && defined(CONFIG_SUSPEND)
बाह्य व्योम tick_मुक्तze(व्योम);
बाह्य व्योम tick_unमुक्तze(व्योम);
#अन्यथा
अटल अंतरभूत व्योम tick_मुक्तze(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम tick_unमुक्तze(व्योम) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_TICK_ONESHOT
बाह्य व्योम tick_irq_enter(व्योम);
#  अगरndef arch_needs_cpu
#   define arch_needs_cpu() (0)
#  endअगर
# अन्यथा
अटल अंतरभूत व्योम tick_irq_enter(व्योम) अणु पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_GENERIC_CLOCKEVENTS_BROADCAST) && defined(CONFIG_TICK_ONESHOT)
बाह्य व्योम hotplug_cpu__broadcast_tick_pull(पूर्णांक dead_cpu);
#अन्यथा
अटल अंतरभूत व्योम hotplug_cpu__broadcast_tick_pull(पूर्णांक dead_cpu) अणु पूर्ण
#पूर्ण_अगर

क्रमागत tick_broadcast_mode अणु
	TICK_BROADCAST_OFF,
	TICK_BROADCAST_ON,
	TICK_BROADCAST_FORCE,
पूर्ण;

क्रमागत tick_broadcast_state अणु
	TICK_BROADCAST_EXIT,
	TICK_BROADCAST_ENTER,
पूर्ण;

#अगर_घोषित CONFIG_GENERIC_CLOCKEVENTS_BROADCAST
बाह्य व्योम tick_broadcast_control(क्रमागत tick_broadcast_mode mode);
#अन्यथा
अटल अंतरभूत व्योम tick_broadcast_control(क्रमागत tick_broadcast_mode mode) अणु पूर्ण
#पूर्ण_अगर /* BROADCAST */

#अगर defined(CONFIG_GENERIC_CLOCKEVENTS_BROADCAST) && defined(CONFIG_HOTPLUG_CPU)
बाह्य व्योम tick_offline_cpu(अचिन्हित पूर्णांक cpu);
#अन्यथा
अटल अंतरभूत व्योम tick_offline_cpu(अचिन्हित पूर्णांक cpu) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_GENERIC_CLOCKEVENTS
बाह्य पूर्णांक tick_broadcast_oneshot_control(क्रमागत tick_broadcast_state state);
#अन्यथा
अटल अंतरभूत पूर्णांक tick_broadcast_oneshot_control(क्रमागत tick_broadcast_state state)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम tick_broadcast_enable(व्योम)
अणु
	tick_broadcast_control(TICK_BROADCAST_ON);
पूर्ण
अटल अंतरभूत व्योम tick_broadcast_disable(व्योम)
अणु
	tick_broadcast_control(TICK_BROADCAST_OFF);
पूर्ण
अटल अंतरभूत व्योम tick_broadcast_क्रमce(व्योम)
अणु
	tick_broadcast_control(TICK_BROADCAST_FORCE);
पूर्ण
अटल अंतरभूत पूर्णांक tick_broadcast_enter(व्योम)
अणु
	वापस tick_broadcast_oneshot_control(TICK_BROADCAST_ENTER);
पूर्ण
अटल अंतरभूत व्योम tick_broadcast_निकास(व्योम)
अणु
	tick_broadcast_oneshot_control(TICK_BROADCAST_EXIT);
पूर्ण

क्रमागत tick_dep_bits अणु
	TICK_DEP_BIT_POSIX_TIMER	= 0,
	TICK_DEP_BIT_PERF_EVENTS	= 1,
	TICK_DEP_BIT_SCHED		= 2,
	TICK_DEP_BIT_CLOCK_UNSTABLE	= 3,
	TICK_DEP_BIT_RCU		= 4,
	TICK_DEP_BIT_RCU_EXP		= 5
पूर्ण;
#घोषणा TICK_DEP_BIT_MAX TICK_DEP_BIT_RCU_EXP

#घोषणा TICK_DEP_MASK_NONE		0
#घोषणा TICK_DEP_MASK_POSIX_TIMER	(1 << TICK_DEP_BIT_POSIX_TIMER)
#घोषणा TICK_DEP_MASK_PERF_EVENTS	(1 << TICK_DEP_BIT_PERF_EVENTS)
#घोषणा TICK_DEP_MASK_SCHED		(1 << TICK_DEP_BIT_SCHED)
#घोषणा TICK_DEP_MASK_CLOCK_UNSTABLE	(1 << TICK_DEP_BIT_CLOCK_UNSTABLE)
#घोषणा TICK_DEP_MASK_RCU		(1 << TICK_DEP_BIT_RCU)
#घोषणा TICK_DEP_MASK_RCU_EXP		(1 << TICK_DEP_BIT_RCU_EXP)

#अगर_घोषित CONFIG_NO_HZ_COMMON
बाह्य bool tick_nohz_enabled;
बाह्य bool tick_nohz_tick_stopped(व्योम);
बाह्य bool tick_nohz_tick_stopped_cpu(पूर्णांक cpu);
बाह्य व्योम tick_nohz_idle_stop_tick(व्योम);
बाह्य व्योम tick_nohz_idle_retain_tick(व्योम);
बाह्य व्योम tick_nohz_idle_restart_tick(व्योम);
बाह्य व्योम tick_nohz_idle_enter(व्योम);
बाह्य व्योम tick_nohz_idle_निकास(व्योम);
बाह्य व्योम tick_nohz_irq_निकास(व्योम);
बाह्य bool tick_nohz_idle_got_tick(व्योम);
बाह्य kसमय_प्रकार tick_nohz_get_next_hrसमयr(व्योम);
बाह्य kसमय_प्रकार tick_nohz_get_sleep_length(kसमय_प्रकार *delta_next);
बाह्य अचिन्हित दीर्घ tick_nohz_get_idle_calls(व्योम);
बाह्य अचिन्हित दीर्घ tick_nohz_get_idle_calls_cpu(पूर्णांक cpu);
बाह्य u64 get_cpu_idle_समय_us(पूर्णांक cpu, u64 *last_update_समय);
बाह्य u64 get_cpu_ioरुको_समय_us(पूर्णांक cpu, u64 *last_update_समय);

अटल अंतरभूत व्योम tick_nohz_idle_stop_tick_रक्षित(व्योम)
अणु
	local_irq_disable();
	tick_nohz_idle_stop_tick();
	local_irq_enable();
पूर्ण

#अन्यथा /* !CONFIG_NO_HZ_COMMON */
#घोषणा tick_nohz_enabled (0)
अटल अंतरभूत पूर्णांक tick_nohz_tick_stopped(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक tick_nohz_tick_stopped_cpu(पूर्णांक cpu) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम tick_nohz_idle_stop_tick(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम tick_nohz_idle_retain_tick(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम tick_nohz_idle_restart_tick(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम tick_nohz_idle_enter(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम tick_nohz_idle_निकास(व्योम) अणु पूर्ण
अटल अंतरभूत bool tick_nohz_idle_got_tick(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत kसमय_प्रकार tick_nohz_get_next_hrसमयr(व्योम)
अणु
	/* Next wake up is the tick period, assume it starts now */
	वापस kसमय_add(kसमय_get(), TICK_NSEC);
पूर्ण
अटल अंतरभूत kसमय_प्रकार tick_nohz_get_sleep_length(kसमय_प्रकार *delta_next)
अणु
	*delta_next = TICK_NSEC;
	वापस *delta_next;
पूर्ण
अटल अंतरभूत u64 get_cpu_idle_समय_us(पूर्णांक cpu, u64 *unused) अणु वापस -1; पूर्ण
अटल अंतरभूत u64 get_cpu_ioरुको_समय_us(पूर्णांक cpu, u64 *unused) अणु वापस -1; पूर्ण

अटल अंतरभूत व्योम tick_nohz_idle_stop_tick_रक्षित(व्योम) अणु पूर्ण
#पूर्ण_अगर /* !CONFIG_NO_HZ_COMMON */

#अगर_घोषित CONFIG_NO_HZ_FULL
बाह्य bool tick_nohz_full_running;
बाह्य cpumask_var_t tick_nohz_full_mask;

अटल अंतरभूत bool tick_nohz_full_enabled(व्योम)
अणु
	अगर (!context_tracking_enabled())
		वापस false;

	वापस tick_nohz_full_running;
पूर्ण

अटल अंतरभूत bool tick_nohz_full_cpu(पूर्णांक cpu)
अणु
	अगर (!tick_nohz_full_enabled())
		वापस false;

	वापस cpumask_test_cpu(cpu, tick_nohz_full_mask);
पूर्ण

अटल अंतरभूत व्योम tick_nohz_full_add_cpus_to(काष्ठा cpumask *mask)
अणु
	अगर (tick_nohz_full_enabled())
		cpumask_or(mask, mask, tick_nohz_full_mask);
पूर्ण

बाह्य व्योम tick_nohz_dep_set(क्रमागत tick_dep_bits bit);
बाह्य व्योम tick_nohz_dep_clear(क्रमागत tick_dep_bits bit);
बाह्य व्योम tick_nohz_dep_set_cpu(पूर्णांक cpu, क्रमागत tick_dep_bits bit);
बाह्य व्योम tick_nohz_dep_clear_cpu(पूर्णांक cpu, क्रमागत tick_dep_bits bit);
बाह्य व्योम tick_nohz_dep_set_task(काष्ठा task_काष्ठा *tsk,
				   क्रमागत tick_dep_bits bit);
बाह्य व्योम tick_nohz_dep_clear_task(काष्ठा task_काष्ठा *tsk,
				     क्रमागत tick_dep_bits bit);
बाह्य व्योम tick_nohz_dep_set_संकेत(काष्ठा संकेत_काष्ठा *संकेत,
				     क्रमागत tick_dep_bits bit);
बाह्य व्योम tick_nohz_dep_clear_संकेत(काष्ठा संकेत_काष्ठा *संकेत,
				       क्रमागत tick_dep_bits bit);

/*
 * The below are tick_nohz_[set,clear]_dep() wrappers that optimize off-हालs
 * on top of अटल keys.
 */
अटल अंतरभूत व्योम tick_dep_set(क्रमागत tick_dep_bits bit)
अणु
	अगर (tick_nohz_full_enabled())
		tick_nohz_dep_set(bit);
पूर्ण

अटल अंतरभूत व्योम tick_dep_clear(क्रमागत tick_dep_bits bit)
अणु
	अगर (tick_nohz_full_enabled())
		tick_nohz_dep_clear(bit);
पूर्ण

अटल अंतरभूत व्योम tick_dep_set_cpu(पूर्णांक cpu, क्रमागत tick_dep_bits bit)
अणु
	अगर (tick_nohz_full_cpu(cpu))
		tick_nohz_dep_set_cpu(cpu, bit);
पूर्ण

अटल अंतरभूत व्योम tick_dep_clear_cpu(पूर्णांक cpu, क्रमागत tick_dep_bits bit)
अणु
	अगर (tick_nohz_full_cpu(cpu))
		tick_nohz_dep_clear_cpu(cpu, bit);
पूर्ण

अटल अंतरभूत व्योम tick_dep_set_task(काष्ठा task_काष्ठा *tsk,
				     क्रमागत tick_dep_bits bit)
अणु
	अगर (tick_nohz_full_enabled())
		tick_nohz_dep_set_task(tsk, bit);
पूर्ण
अटल अंतरभूत व्योम tick_dep_clear_task(काष्ठा task_काष्ठा *tsk,
				       क्रमागत tick_dep_bits bit)
अणु
	अगर (tick_nohz_full_enabled())
		tick_nohz_dep_clear_task(tsk, bit);
पूर्ण
अटल अंतरभूत व्योम tick_dep_set_संकेत(काष्ठा संकेत_काष्ठा *संकेत,
				       क्रमागत tick_dep_bits bit)
अणु
	अगर (tick_nohz_full_enabled())
		tick_nohz_dep_set_संकेत(संकेत, bit);
पूर्ण
अटल अंतरभूत व्योम tick_dep_clear_संकेत(काष्ठा संकेत_काष्ठा *संकेत,
					 क्रमागत tick_dep_bits bit)
अणु
	अगर (tick_nohz_full_enabled())
		tick_nohz_dep_clear_संकेत(संकेत, bit);
पूर्ण

बाह्य व्योम tick_nohz_full_kick_cpu(पूर्णांक cpu);
बाह्य व्योम __tick_nohz_task_चयन(व्योम);
बाह्य व्योम __init tick_nohz_full_setup(cpumask_var_t cpumask);
#अन्यथा
अटल अंतरभूत bool tick_nohz_full_enabled(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत bool tick_nohz_full_cpu(पूर्णांक cpu) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम tick_nohz_full_add_cpus_to(काष्ठा cpumask *mask) अणु पूर्ण

अटल अंतरभूत व्योम tick_nohz_dep_set_cpu(पूर्णांक cpu, क्रमागत tick_dep_bits bit) अणु पूर्ण
अटल अंतरभूत व्योम tick_nohz_dep_clear_cpu(पूर्णांक cpu, क्रमागत tick_dep_bits bit) अणु पूर्ण

अटल अंतरभूत व्योम tick_dep_set(क्रमागत tick_dep_bits bit) अणु पूर्ण
अटल अंतरभूत व्योम tick_dep_clear(क्रमागत tick_dep_bits bit) अणु पूर्ण
अटल अंतरभूत व्योम tick_dep_set_cpu(पूर्णांक cpu, क्रमागत tick_dep_bits bit) अणु पूर्ण
अटल अंतरभूत व्योम tick_dep_clear_cpu(पूर्णांक cpu, क्रमागत tick_dep_bits bit) अणु पूर्ण
अटल अंतरभूत व्योम tick_dep_set_task(काष्ठा task_काष्ठा *tsk,
				     क्रमागत tick_dep_bits bit) अणु पूर्ण
अटल अंतरभूत व्योम tick_dep_clear_task(काष्ठा task_काष्ठा *tsk,
				       क्रमागत tick_dep_bits bit) अणु पूर्ण
अटल अंतरभूत व्योम tick_dep_set_संकेत(काष्ठा संकेत_काष्ठा *संकेत,
				       क्रमागत tick_dep_bits bit) अणु पूर्ण
अटल अंतरभूत व्योम tick_dep_clear_संकेत(काष्ठा संकेत_काष्ठा *संकेत,
					 क्रमागत tick_dep_bits bit) अणु पूर्ण

अटल अंतरभूत व्योम tick_nohz_full_kick_cpu(पूर्णांक cpu) अणु पूर्ण
अटल अंतरभूत व्योम __tick_nohz_task_चयन(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम tick_nohz_full_setup(cpumask_var_t cpumask) अणु पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम tick_nohz_task_चयन(व्योम)
अणु
	अगर (tick_nohz_full_enabled())
		__tick_nohz_task_चयन();
पूर्ण

अटल अंतरभूत व्योम tick_nohz_user_enter_prepare(व्योम)
अणु
	अगर (tick_nohz_full_cpu(smp_processor_id()))
		rcu_nocb_flush_deferred_wakeup();
पूर्ण

#पूर्ण_अगर
