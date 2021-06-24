<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * IRQ subप्रणाली पूर्णांकernal functions and variables:
 *
 * Do not ever include this file from anything अन्यथा than
 * kernel/irq/. Do not even think about using any inक्रमmation outside
 * of this file क्रम your non core code.
 */
#समावेश <linux/irqdesc.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/sched/घड़ी.h>

#अगर_घोषित CONFIG_SPARSE_IRQ
# define IRQ_BITMAP_BITS	(NR_IRQS + 8196)
#अन्यथा
# define IRQ_BITMAP_BITS	NR_IRQS
#पूर्ण_अगर

#घोषणा istate core_पूर्णांकernal_state__करो_not_mess_with_it

बाह्य bool noirqdebug;

बाह्य काष्ठा irqaction chained_action;

/*
 * Bits used by thपढ़ोed handlers:
 * IRQTF_RUNTHREAD - संकेतs that the पूर्णांकerrupt handler thपढ़ो should run
 * IRQTF_WARNED    - warning "IRQ_WAKE_THREAD w/o thread_fn" has been prपूर्णांकed
 * IRQTF_AFFINITY  - irq thपढ़ो is requested to adjust affinity
 * IRQTF_FORCED_THREAD  - irq action is क्रमce thपढ़ोed
 */
क्रमागत अणु
	IRQTF_RUNTHREAD,
	IRQTF_WARNED,
	IRQTF_AFFINITY,
	IRQTF_FORCED_THREAD,
पूर्ण;

/*
 * Bit masks क्रम desc->core_पूर्णांकernal_state__करो_not_mess_with_it
 *
 * IRQS_AUTODETECT		- स्वतःdetection in progress
 * IRQS_SPURIOUS_DISABLED	- was disabled due to spurious पूर्णांकerrupt
 *				  detection
 * IRQS_POLL_INPROGRESS		- polling in progress
 * IRQS_ONESHOT			- irq is not unmasked in primary handler
 * IRQS_REPLAY			- irq is replayed
 * IRQS_WAITING			- irq is रुकोing
 * IRQS_PENDING			- irq is pending and replayed later
 * IRQS_SUSPENDED		- irq is suspended
 * IRQS_NMI			- irq line is used to deliver NMIs
 */
क्रमागत अणु
	IRQS_AUTODETECT		= 0x00000001,
	IRQS_SPURIOUS_DISABLED	= 0x00000002,
	IRQS_POLL_INPROGRESS	= 0x00000008,
	IRQS_ONESHOT		= 0x00000020,
	IRQS_REPLAY		= 0x00000040,
	IRQS_WAITING		= 0x00000080,
	IRQS_PENDING		= 0x00000200,
	IRQS_SUSPENDED		= 0x00000800,
	IRQS_TIMINGS		= 0x00001000,
	IRQS_NMI		= 0x00002000,
पूर्ण;

#समावेश "debug.h"
#समावेश "settings.h"

बाह्य पूर्णांक __irq_set_trigger(काष्ठा irq_desc *desc, अचिन्हित दीर्घ flags);
बाह्य व्योम __disable_irq(काष्ठा irq_desc *desc);
बाह्य व्योम __enable_irq(काष्ठा irq_desc *desc);

#घोषणा IRQ_RESEND	true
#घोषणा IRQ_NORESEND	false

#घोषणा IRQ_START_FORCE	true
#घोषणा IRQ_START_COND	false

बाह्य पूर्णांक irq_activate(काष्ठा irq_desc *desc);
बाह्य पूर्णांक irq_activate_and_startup(काष्ठा irq_desc *desc, bool resend);
बाह्य पूर्णांक irq_startup(काष्ठा irq_desc *desc, bool resend, bool क्रमce);

बाह्य व्योम irq_shutकरोwn(काष्ठा irq_desc *desc);
बाह्य व्योम irq_shutकरोwn_and_deactivate(काष्ठा irq_desc *desc);
बाह्य व्योम irq_enable(काष्ठा irq_desc *desc);
बाह्य व्योम irq_disable(काष्ठा irq_desc *desc);
बाह्य व्योम irq_percpu_enable(काष्ठा irq_desc *desc, अचिन्हित पूर्णांक cpu);
बाह्य व्योम irq_percpu_disable(काष्ठा irq_desc *desc, अचिन्हित पूर्णांक cpu);
बाह्य व्योम mask_irq(काष्ठा irq_desc *desc);
बाह्य व्योम unmask_irq(काष्ठा irq_desc *desc);
बाह्य व्योम unmask_thपढ़ोed_irq(काष्ठा irq_desc *desc);

#अगर_घोषित CONFIG_SPARSE_IRQ
अटल अंतरभूत व्योम irq_mark_irq(अचिन्हित पूर्णांक irq) अणु पूर्ण
#अन्यथा
बाह्य व्योम irq_mark_irq(अचिन्हित पूर्णांक irq);
#पूर्ण_अगर

बाह्य पूर्णांक __irq_get_irqchip_state(काष्ठा irq_data *data,
				   क्रमागत irqchip_irq_state which,
				   bool *state);

बाह्य व्योम init_kstat_irqs(काष्ठा irq_desc *desc, पूर्णांक node, पूर्णांक nr);

irqवापस_t __handle_irq_event_percpu(काष्ठा irq_desc *desc, अचिन्हित पूर्णांक *flags);
irqवापस_t handle_irq_event_percpu(काष्ठा irq_desc *desc);
irqवापस_t handle_irq_event(काष्ठा irq_desc *desc);

/* Resending of पूर्णांकerrupts :*/
पूर्णांक check_irq_resend(काष्ठा irq_desc *desc, bool inject);
bool irq_रुको_क्रम_poll(काष्ठा irq_desc *desc);
व्योम __irq_wake_thपढ़ो(काष्ठा irq_desc *desc, काष्ठा irqaction *action);

#अगर_घोषित CONFIG_PROC_FS
बाह्य व्योम रेजिस्टर_irq_proc(अचिन्हित पूर्णांक irq, काष्ठा irq_desc *desc);
बाह्य व्योम unरेजिस्टर_irq_proc(अचिन्हित पूर्णांक irq, काष्ठा irq_desc *desc);
बाह्य व्योम रेजिस्टर_handler_proc(अचिन्हित पूर्णांक irq, काष्ठा irqaction *action);
बाह्य व्योम unरेजिस्टर_handler_proc(अचिन्हित पूर्णांक irq, काष्ठा irqaction *action);
#अन्यथा
अटल अंतरभूत व्योम रेजिस्टर_irq_proc(अचिन्हित पूर्णांक irq, काष्ठा irq_desc *desc) अणु पूर्ण
अटल अंतरभूत व्योम unरेजिस्टर_irq_proc(अचिन्हित पूर्णांक irq, काष्ठा irq_desc *desc) अणु पूर्ण
अटल अंतरभूत व्योम रेजिस्टर_handler_proc(अचिन्हित पूर्णांक irq,
					 काष्ठा irqaction *action) अणु पूर्ण
अटल अंतरभूत व्योम unरेजिस्टर_handler_proc(अचिन्हित पूर्णांक irq,
					   काष्ठा irqaction *action) अणु पूर्ण
#पूर्ण_अगर

बाह्य bool irq_can_set_affinity_usr(अचिन्हित पूर्णांक irq);

बाह्य व्योम irq_set_thपढ़ो_affinity(काष्ठा irq_desc *desc);

बाह्य पूर्णांक irq_करो_set_affinity(काष्ठा irq_data *data,
			       स्थिर काष्ठा cpumask *dest, bool क्रमce);

#अगर_घोषित CONFIG_SMP
बाह्य पूर्णांक irq_setup_affinity(काष्ठा irq_desc *desc);
#अन्यथा
अटल अंतरभूत पूर्णांक irq_setup_affinity(काष्ठा irq_desc *desc) अणु वापस 0; पूर्ण
#पूर्ण_अगर

/* Inline functions क्रम support of irq chips on slow busses */
अटल अंतरभूत व्योम chip_bus_lock(काष्ठा irq_desc *desc)
अणु
	अगर (unlikely(desc->irq_data.chip->irq_bus_lock))
		desc->irq_data.chip->irq_bus_lock(&desc->irq_data);
पूर्ण

अटल अंतरभूत व्योम chip_bus_sync_unlock(काष्ठा irq_desc *desc)
अणु
	अगर (unlikely(desc->irq_data.chip->irq_bus_sync_unlock))
		desc->irq_data.chip->irq_bus_sync_unlock(&desc->irq_data);
पूर्ण

#घोषणा _IRQ_DESC_CHECK		(1 << 0)
#घोषणा _IRQ_DESC_PERCPU	(1 << 1)

#घोषणा IRQ_GET_DESC_CHECK_GLOBAL	(_IRQ_DESC_CHECK)
#घोषणा IRQ_GET_DESC_CHECK_PERCPU	(_IRQ_DESC_CHECK | _IRQ_DESC_PERCPU)

#घोषणा क्रम_each_action_of_desc(desc, act)			\
	क्रम (act = desc->action; act; act = act->next)

काष्ठा irq_desc *
__irq_get_desc_lock(अचिन्हित पूर्णांक irq, अचिन्हित दीर्घ *flags, bool bus,
		    अचिन्हित पूर्णांक check);
व्योम __irq_put_desc_unlock(काष्ठा irq_desc *desc, अचिन्हित दीर्घ flags, bool bus);

अटल अंतरभूत काष्ठा irq_desc *
irq_get_desc_buslock(अचिन्हित पूर्णांक irq, अचिन्हित दीर्घ *flags, अचिन्हित पूर्णांक check)
अणु
	वापस __irq_get_desc_lock(irq, flags, true, check);
पूर्ण

अटल अंतरभूत व्योम
irq_put_desc_busunlock(काष्ठा irq_desc *desc, अचिन्हित दीर्घ flags)
अणु
	__irq_put_desc_unlock(desc, flags, true);
पूर्ण

अटल अंतरभूत काष्ठा irq_desc *
irq_get_desc_lock(अचिन्हित पूर्णांक irq, अचिन्हित दीर्घ *flags, अचिन्हित पूर्णांक check)
अणु
	वापस __irq_get_desc_lock(irq, flags, false, check);
पूर्ण

अटल अंतरभूत व्योम
irq_put_desc_unlock(काष्ठा irq_desc *desc, अचिन्हित दीर्घ flags)
अणु
	__irq_put_desc_unlock(desc, flags, false);
पूर्ण

#घोषणा __irqd_to_state(d) ACCESS_PRIVATE((d)->common, state_use_accessors)

अटल अंतरभूत अचिन्हित पूर्णांक irqd_get(काष्ठा irq_data *d)
अणु
	वापस __irqd_to_state(d);
पूर्ण

/*
 * Manipulation functions क्रम irq_data.state
 */
अटल अंतरभूत व्योम irqd_set_move_pending(काष्ठा irq_data *d)
अणु
	__irqd_to_state(d) |= IRQD_SETAFFINITY_PENDING;
पूर्ण

अटल अंतरभूत व्योम irqd_clr_move_pending(काष्ठा irq_data *d)
अणु
	__irqd_to_state(d) &= ~IRQD_SETAFFINITY_PENDING;
पूर्ण

अटल अंतरभूत व्योम irqd_set_managed_shutकरोwn(काष्ठा irq_data *d)
अणु
	__irqd_to_state(d) |= IRQD_MANAGED_SHUTDOWN;
पूर्ण

अटल अंतरभूत व्योम irqd_clr_managed_shutकरोwn(काष्ठा irq_data *d)
अणु
	__irqd_to_state(d) &= ~IRQD_MANAGED_SHUTDOWN;
पूर्ण

अटल अंतरभूत व्योम irqd_clear(काष्ठा irq_data *d, अचिन्हित पूर्णांक mask)
अणु
	__irqd_to_state(d) &= ~mask;
पूर्ण

अटल अंतरभूत व्योम irqd_set(काष्ठा irq_data *d, अचिन्हित पूर्णांक mask)
अणु
	__irqd_to_state(d) |= mask;
पूर्ण

अटल अंतरभूत bool irqd_has_set(काष्ठा irq_data *d, अचिन्हित पूर्णांक mask)
अणु
	वापस __irqd_to_state(d) & mask;
पूर्ण

अटल अंतरभूत व्योम irq_state_set_disabled(काष्ठा irq_desc *desc)
अणु
	irqd_set(&desc->irq_data, IRQD_IRQ_DISABLED);
पूर्ण

अटल अंतरभूत व्योम irq_state_set_masked(काष्ठा irq_desc *desc)
अणु
	irqd_set(&desc->irq_data, IRQD_IRQ_MASKED);
पूर्ण

#अघोषित __irqd_to_state

अटल अंतरभूत व्योम __kstat_incr_irqs_this_cpu(काष्ठा irq_desc *desc)
अणु
	__this_cpu_inc(*desc->kstat_irqs);
	__this_cpu_inc(kstat.irqs_sum);
पूर्ण

अटल अंतरभूत व्योम kstat_incr_irqs_this_cpu(काष्ठा irq_desc *desc)
अणु
	__kstat_incr_irqs_this_cpu(desc);
	desc->tot_count++;
पूर्ण

अटल अंतरभूत पूर्णांक irq_desc_get_node(काष्ठा irq_desc *desc)
अणु
	वापस irq_common_data_get_node(&desc->irq_common_data);
पूर्ण

अटल अंतरभूत पूर्णांक irq_desc_is_chained(काष्ठा irq_desc *desc)
अणु
	वापस (desc->action && desc->action == &chained_action);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
bool irq_pm_check_wakeup(काष्ठा irq_desc *desc);
व्योम irq_pm_install_action(काष्ठा irq_desc *desc, काष्ठा irqaction *action);
व्योम irq_pm_हटाओ_action(काष्ठा irq_desc *desc, काष्ठा irqaction *action);
#अन्यथा
अटल अंतरभूत bool irq_pm_check_wakeup(काष्ठा irq_desc *desc) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम
irq_pm_install_action(काष्ठा irq_desc *desc, काष्ठा irqaction *action) अणु पूर्ण
अटल अंतरभूत व्योम
irq_pm_हटाओ_action(काष्ठा irq_desc *desc, काष्ठा irqaction *action) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_IRQ_TIMINGS

#घोषणा IRQ_TIMINGS_SHIFT	5
#घोषणा IRQ_TIMINGS_SIZE	(1 << IRQ_TIMINGS_SHIFT)
#घोषणा IRQ_TIMINGS_MASK	(IRQ_TIMINGS_SIZE - 1)

/**
 * काष्ठा irq_timings - irq timings storing काष्ठाure
 * @values: a circular buffer of u64 encoded <बारtamp,irq> values
 * @count: the number of elements in the array
 */
काष्ठा irq_timings अणु
	u64	values[IRQ_TIMINGS_SIZE];
	पूर्णांक	count;
पूर्ण;

DECLARE_PER_CPU(काष्ठा irq_timings, irq_timings);

बाह्य व्योम irq_timings_मुक्त(पूर्णांक irq);
बाह्य पूर्णांक irq_timings_alloc(पूर्णांक irq);

अटल अंतरभूत व्योम irq_हटाओ_timings(काष्ठा irq_desc *desc)
अणु
	desc->istate &= ~IRQS_TIMINGS;

	irq_timings_मुक्त(irq_desc_get_irq(desc));
पूर्ण

अटल अंतरभूत व्योम irq_setup_timings(काष्ठा irq_desc *desc, काष्ठा irqaction *act)
अणु
	पूर्णांक irq = irq_desc_get_irq(desc);
	पूर्णांक ret;

	/*
	 * We करोn't need the measurement because the idle code alपढ़ोy
	 * knows the next expiry event.
	 */
	अगर (act->flags & __IRQF_TIMER)
		वापस;

	/*
	 * In हाल the timing allocation fails, we just want to warn,
	 * not fail, so letting the प्रणाली boot anyway.
	 */
	ret = irq_timings_alloc(irq);
	अगर (ret) अणु
		pr_warn("Failed to allocate irq timing stats for irq%d (%d)",
			irq, ret);
		वापस;
	पूर्ण

	desc->istate |= IRQS_TIMINGS;
पूर्ण

बाह्य व्योम irq_timings_enable(व्योम);
बाह्य व्योम irq_timings_disable(व्योम);

DECLARE_STATIC_KEY_FALSE(irq_timing_enabled);

/*
 * The पूर्णांकerrupt number and the बारtamp are encoded पूर्णांकo a single
 * u64 variable to optimize the size.
 * 48 bit समय stamp and 16 bit IRQ number is way sufficient.
 *  Who cares an IRQ after 78 hours of idle समय?
 */
अटल अंतरभूत u64 irq_timing_encode(u64 बारtamp, पूर्णांक irq)
अणु
	वापस (बारtamp << 16) | irq;
पूर्ण

अटल अंतरभूत पूर्णांक irq_timing_decode(u64 value, u64 *बारtamp)
अणु
	*बारtamp = value >> 16;
	वापस value & U16_MAX;
पूर्ण

अटल __always_अंतरभूत व्योम irq_timings_push(u64 ts, पूर्णांक irq)
अणु
	काष्ठा irq_timings *timings = this_cpu_ptr(&irq_timings);

	timings->values[timings->count & IRQ_TIMINGS_MASK] =
		irq_timing_encode(ts, irq);

	timings->count++;
पूर्ण

/*
 * The function record_irq_समय is only called in one place in the
 * पूर्णांकerrupts handler. We want this function always अंतरभूत so the code
 * inside is embedded in the function and the अटल key branching
 * code can act at the higher level. Without the explicit
 * __always_अंतरभूत we can end up with a function call and a small
 * overhead in the hotpath क्रम nothing.
 */
अटल __always_अंतरभूत व्योम record_irq_समय(काष्ठा irq_desc *desc)
अणु
	अगर (!अटल_branch_likely(&irq_timing_enabled))
		वापस;

	अगर (desc->istate & IRQS_TIMINGS)
		irq_timings_push(local_घड़ी(), irq_desc_get_irq(desc));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम irq_हटाओ_timings(काष्ठा irq_desc *desc) अणुपूर्ण
अटल अंतरभूत व्योम irq_setup_timings(काष्ठा irq_desc *desc,
				     काष्ठा irqaction *act) अणुपूर्ण;
अटल अंतरभूत व्योम record_irq_समय(काष्ठा irq_desc *desc) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_IRQ_TIMINGS */


#अगर_घोषित CONFIG_GENERIC_IRQ_CHIP
व्योम irq_init_generic_chip(काष्ठा irq_chip_generic *gc, स्थिर अक्षर *name,
			   पूर्णांक num_ct, अचिन्हित पूर्णांक irq_base,
			   व्योम __iomem *reg_base, irq_flow_handler_t handler);
#अन्यथा
अटल अंतरभूत व्योम
irq_init_generic_chip(काष्ठा irq_chip_generic *gc, स्थिर अक्षर *name,
		      पूर्णांक num_ct, अचिन्हित पूर्णांक irq_base,
		      व्योम __iomem *reg_base, irq_flow_handler_t handler) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_GENERIC_IRQ_CHIP */

#अगर_घोषित CONFIG_GENERIC_PENDING_IRQ
अटल अंतरभूत bool irq_can_move_pcntxt(काष्ठा irq_data *data)
अणु
	वापस irqd_can_move_in_process_context(data);
पूर्ण
अटल अंतरभूत bool irq_move_pending(काष्ठा irq_data *data)
अणु
	वापस irqd_is_setaffinity_pending(data);
पूर्ण
अटल अंतरभूत व्योम
irq_copy_pending(काष्ठा irq_desc *desc, स्थिर काष्ठा cpumask *mask)
अणु
	cpumask_copy(desc->pending_mask, mask);
पूर्ण
अटल अंतरभूत व्योम
irq_get_pending(काष्ठा cpumask *mask, काष्ठा irq_desc *desc)
अणु
	cpumask_copy(mask, desc->pending_mask);
पूर्ण
अटल अंतरभूत काष्ठा cpumask *irq_desc_get_pending_mask(काष्ठा irq_desc *desc)
अणु
	वापस desc->pending_mask;
पूर्ण
अटल अंतरभूत bool handle_enक्रमce_irqctx(काष्ठा irq_data *data)
अणु
	वापस irqd_is_handle_enक्रमce_irqctx(data);
पूर्ण
bool irq_fixup_move_pending(काष्ठा irq_desc *desc, bool क्रमce_clear);
#अन्यथा /* CONFIG_GENERIC_PENDING_IRQ */
अटल अंतरभूत bool irq_can_move_pcntxt(काष्ठा irq_data *data)
अणु
	वापस true;
पूर्ण
अटल अंतरभूत bool irq_move_pending(काष्ठा irq_data *data)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत व्योम
irq_copy_pending(काष्ठा irq_desc *desc, स्थिर काष्ठा cpumask *mask)
अणु
पूर्ण
अटल अंतरभूत व्योम
irq_get_pending(काष्ठा cpumask *mask, काष्ठा irq_desc *desc)
अणु
पूर्ण
अटल अंतरभूत काष्ठा cpumask *irq_desc_get_pending_mask(काष्ठा irq_desc *desc)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत bool irq_fixup_move_pending(काष्ठा irq_desc *desc, bool fclear)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत bool handle_enक्रमce_irqctx(काष्ठा irq_data *data)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* !CONFIG_GENERIC_PENDING_IRQ */

#अगर !defined(CONFIG_IRQ_DOMAIN) || !defined(CONFIG_IRQ_DOMAIN_HIERARCHY)
अटल अंतरभूत पूर्णांक irq_करोमुख्य_activate_irq(काष्ठा irq_data *data, bool reserve)
अणु
	irqd_set_activated(data);
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम irq_करोमुख्य_deactivate_irq(काष्ठा irq_data *data)
अणु
	irqd_clr_activated(data);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत काष्ठा irq_data *irqd_get_parent_data(काष्ठा irq_data *irqd)
अणु
#अगर_घोषित CONFIG_IRQ_DOMAIN_HIERARCHY
	वापस irqd->parent_data;
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_GENERIC_IRQ_DEBUGFS
#समावेश <linux/debugfs.h>

व्योम irq_add_debugfs_entry(अचिन्हित पूर्णांक irq, काष्ठा irq_desc *desc);
अटल अंतरभूत व्योम irq_हटाओ_debugfs_entry(काष्ठा irq_desc *desc)
अणु
	debugfs_हटाओ(desc->debugfs_file);
	kमुक्त(desc->dev_name);
पूर्ण
व्योम irq_debugfs_copy_devname(पूर्णांक irq, काष्ठा device *dev);
# अगरdef CONFIG_IRQ_DOMAIN
व्योम irq_करोमुख्य_debugfs_init(काष्ठा dentry *root);
# अन्यथा
अटल अंतरभूत व्योम irq_करोमुख्य_debugfs_init(काष्ठा dentry *root)
अणु
पूर्ण
# endअगर
#अन्यथा /* CONFIG_GENERIC_IRQ_DEBUGFS */
अटल अंतरभूत व्योम irq_add_debugfs_entry(अचिन्हित पूर्णांक irq, काष्ठा irq_desc *d)
अणु
पूर्ण
अटल अंतरभूत व्योम irq_हटाओ_debugfs_entry(काष्ठा irq_desc *d)
अणु
पूर्ण
अटल अंतरभूत व्योम irq_debugfs_copy_devname(पूर्णांक irq, काष्ठा device *dev)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_GENERIC_IRQ_DEBUGFS */
