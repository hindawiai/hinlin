<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 1992, 1998-2006 Linus Torvalds, Ingo Molnar
 * Copyright (C) 2005-2006, Thomas Gleixner, Russell King
 *
 * This file contains the core पूर्णांकerrupt handling code, क्रम irq-chip based
 * architectures. Detailed inक्रमmation is available in
 * Documentation/core-api/genericirq.rst
 */

#समावेश <linux/irq.h>
#समावेश <linux/msi.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/irqकरोमुख्य.h>

#समावेश <trace/events/irq.h>

#समावेश "internals.h"

अटल irqवापस_t bad_chained_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	WARN_ONCE(1, "Chained irq %d should not call an action\n", irq);
	वापस IRQ_NONE;
पूर्ण

/*
 * Chained handlers should never call action on their IRQ. This शेष
 * action will emit warning अगर such thing happens.
 */
काष्ठा irqaction chained_action = अणु
	.handler = bad_chained_irq,
पूर्ण;

/**
 *	irq_set_chip - set the irq chip क्रम an irq
 *	@irq:	irq number
 *	@chip:	poपूर्णांकer to irq chip description काष्ठाure
 */
पूर्णांक irq_set_chip(अचिन्हित पूर्णांक irq, काष्ठा irq_chip *chip)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा irq_desc *desc = irq_get_desc_lock(irq, &flags, 0);

	अगर (!desc)
		वापस -EINVAL;

	अगर (!chip)
		chip = &no_irq_chip;

	desc->irq_data.chip = chip;
	irq_put_desc_unlock(desc, flags);
	/*
	 * For !CONFIG_SPARSE_IRQ make the irq show up in
	 * allocated_irqs.
	 */
	irq_mark_irq(irq);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(irq_set_chip);

/**
 *	irq_set_irq_type - set the irq trigger type क्रम an irq
 *	@irq:	irq number
 *	@type:	IRQ_TYPE_अणुLEVEL,EDGEपूर्ण_* value - see include/linux/irq.h
 */
पूर्णांक irq_set_irq_type(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक type)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा irq_desc *desc = irq_get_desc_buslock(irq, &flags, IRQ_GET_DESC_CHECK_GLOBAL);
	पूर्णांक ret = 0;

	अगर (!desc)
		वापस -EINVAL;

	ret = __irq_set_trigger(desc, type);
	irq_put_desc_busunlock(desc, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(irq_set_irq_type);

/**
 *	irq_set_handler_data - set irq handler data क्रम an irq
 *	@irq:	Interrupt number
 *	@data:	Poपूर्णांकer to पूर्णांकerrupt specअगरic data
 *
 *	Set the hardware irq controller data क्रम an irq
 */
पूर्णांक irq_set_handler_data(अचिन्हित पूर्णांक irq, व्योम *data)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा irq_desc *desc = irq_get_desc_lock(irq, &flags, 0);

	अगर (!desc)
		वापस -EINVAL;
	desc->irq_common_data.handler_data = data;
	irq_put_desc_unlock(desc, flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(irq_set_handler_data);

/**
 *	irq_set_msi_desc_off - set MSI descriptor data क्रम an irq at offset
 *	@irq_base:	Interrupt number base
 *	@irq_offset:	Interrupt number offset
 *	@entry:		Poपूर्णांकer to MSI descriptor data
 *
 *	Set the MSI descriptor entry क्रम an irq at offset
 */
पूर्णांक irq_set_msi_desc_off(अचिन्हित पूर्णांक irq_base, अचिन्हित पूर्णांक irq_offset,
			 काष्ठा msi_desc *entry)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा irq_desc *desc = irq_get_desc_lock(irq_base + irq_offset, &flags, IRQ_GET_DESC_CHECK_GLOBAL);

	अगर (!desc)
		वापस -EINVAL;
	desc->irq_common_data.msi_desc = entry;
	अगर (entry && !irq_offset)
		entry->irq = irq_base;
	irq_put_desc_unlock(desc, flags);
	वापस 0;
पूर्ण

/**
 *	irq_set_msi_desc - set MSI descriptor data क्रम an irq
 *	@irq:	Interrupt number
 *	@entry:	Poपूर्णांकer to MSI descriptor data
 *
 *	Set the MSI descriptor entry क्रम an irq
 */
पूर्णांक irq_set_msi_desc(अचिन्हित पूर्णांक irq, काष्ठा msi_desc *entry)
अणु
	वापस irq_set_msi_desc_off(irq, 0, entry);
पूर्ण

/**
 *	irq_set_chip_data - set irq chip data क्रम an irq
 *	@irq:	Interrupt number
 *	@data:	Poपूर्णांकer to chip specअगरic data
 *
 *	Set the hardware irq chip data क्रम an irq
 */
पूर्णांक irq_set_chip_data(अचिन्हित पूर्णांक irq, व्योम *data)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा irq_desc *desc = irq_get_desc_lock(irq, &flags, 0);

	अगर (!desc)
		वापस -EINVAL;
	desc->irq_data.chip_data = data;
	irq_put_desc_unlock(desc, flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(irq_set_chip_data);

काष्ठा irq_data *irq_get_irq_data(अचिन्हित पूर्णांक irq)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(irq);

	वापस desc ? &desc->irq_data : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(irq_get_irq_data);

अटल व्योम irq_state_clr_disabled(काष्ठा irq_desc *desc)
अणु
	irqd_clear(&desc->irq_data, IRQD_IRQ_DISABLED);
पूर्ण

अटल व्योम irq_state_clr_masked(काष्ठा irq_desc *desc)
अणु
	irqd_clear(&desc->irq_data, IRQD_IRQ_MASKED);
पूर्ण

अटल व्योम irq_state_clr_started(काष्ठा irq_desc *desc)
अणु
	irqd_clear(&desc->irq_data, IRQD_IRQ_STARTED);
पूर्ण

अटल व्योम irq_state_set_started(काष्ठा irq_desc *desc)
अणु
	irqd_set(&desc->irq_data, IRQD_IRQ_STARTED);
पूर्ण

क्रमागत अणु
	IRQ_STARTUP_NORMAL,
	IRQ_STARTUP_MANAGED,
	IRQ_STARTUP_ABORT,
पूर्ण;

#अगर_घोषित CONFIG_SMP
अटल पूर्णांक
__irq_startup_managed(काष्ठा irq_desc *desc, काष्ठा cpumask *aff, bool क्रमce)
अणु
	काष्ठा irq_data *d = irq_desc_get_irq_data(desc);

	अगर (!irqd_affinity_is_managed(d))
		वापस IRQ_STARTUP_NORMAL;

	irqd_clr_managed_shutकरोwn(d);

	अगर (cpumask_any_and(aff, cpu_online_mask) >= nr_cpu_ids) अणु
		/*
		 * Catch code which fiddles with enable_irq() on a managed
		 * and potentially shutकरोwn IRQ. Chained पूर्णांकerrupt
		 * installment or irq स्वतः probing should not happen on
		 * managed irqs either.
		 */
		अगर (WARN_ON_ONCE(क्रमce))
			वापस IRQ_STARTUP_ABORT;
		/*
		 * The पूर्णांकerrupt was requested, but there is no online CPU
		 * in it's affinity mask. Put it पूर्णांकo managed shutकरोwn
		 * state and let the cpu hotplug mechanism start it up once
		 * a CPU in the mask becomes available.
		 */
		वापस IRQ_STARTUP_ABORT;
	पूर्ण
	/*
	 * Managed पूर्णांकerrupts have reserved resources, so this should not
	 * happen.
	 */
	अगर (WARN_ON(irq_करोमुख्य_activate_irq(d, false)))
		वापस IRQ_STARTUP_ABORT;
	वापस IRQ_STARTUP_MANAGED;
पूर्ण
#अन्यथा
अटल __always_अंतरभूत पूर्णांक
__irq_startup_managed(काष्ठा irq_desc *desc, काष्ठा cpumask *aff, bool क्रमce)
अणु
	वापस IRQ_STARTUP_NORMAL;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __irq_startup(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_data *d = irq_desc_get_irq_data(desc);
	पूर्णांक ret = 0;

	/* Warn अगर this पूर्णांकerrupt is not activated but try nevertheless */
	WARN_ON_ONCE(!irqd_is_activated(d));

	अगर (d->chip->irq_startup) अणु
		ret = d->chip->irq_startup(d);
		irq_state_clr_disabled(desc);
		irq_state_clr_masked(desc);
	पूर्ण अन्यथा अणु
		irq_enable(desc);
	पूर्ण
	irq_state_set_started(desc);
	वापस ret;
पूर्ण

पूर्णांक irq_startup(काष्ठा irq_desc *desc, bool resend, bool क्रमce)
अणु
	काष्ठा irq_data *d = irq_desc_get_irq_data(desc);
	काष्ठा cpumask *aff = irq_data_get_affinity_mask(d);
	पूर्णांक ret = 0;

	desc->depth = 0;

	अगर (irqd_is_started(d)) अणु
		irq_enable(desc);
	पूर्ण अन्यथा अणु
		चयन (__irq_startup_managed(desc, aff, क्रमce)) अणु
		हाल IRQ_STARTUP_NORMAL:
			ret = __irq_startup(desc);
			irq_setup_affinity(desc);
			अवरोध;
		हाल IRQ_STARTUP_MANAGED:
			irq_करो_set_affinity(d, aff, false);
			ret = __irq_startup(desc);
			अवरोध;
		हाल IRQ_STARTUP_ABORT:
			irqd_set_managed_shutकरोwn(d);
			वापस 0;
		पूर्ण
	पूर्ण
	अगर (resend)
		check_irq_resend(desc, false);

	वापस ret;
पूर्ण

पूर्णांक irq_activate(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_data *d = irq_desc_get_irq_data(desc);

	अगर (!irqd_affinity_is_managed(d))
		वापस irq_करोमुख्य_activate_irq(d, false);
	वापस 0;
पूर्ण

पूर्णांक irq_activate_and_startup(काष्ठा irq_desc *desc, bool resend)
अणु
	अगर (WARN_ON(irq_activate(desc)))
		वापस 0;
	वापस irq_startup(desc, resend, IRQ_START_FORCE);
पूर्ण

अटल व्योम __irq_disable(काष्ठा irq_desc *desc, bool mask);

व्योम irq_shutकरोwn(काष्ठा irq_desc *desc)
अणु
	अगर (irqd_is_started(&desc->irq_data)) अणु
		desc->depth = 1;
		अगर (desc->irq_data.chip->irq_shutकरोwn) अणु
			desc->irq_data.chip->irq_shutकरोwn(&desc->irq_data);
			irq_state_set_disabled(desc);
			irq_state_set_masked(desc);
		पूर्ण अन्यथा अणु
			__irq_disable(desc, true);
		पूर्ण
		irq_state_clr_started(desc);
	पूर्ण
पूर्ण


व्योम irq_shutकरोwn_and_deactivate(काष्ठा irq_desc *desc)
अणु
	irq_shutकरोwn(desc);
	/*
	 * This must be called even अगर the पूर्णांकerrupt was never started up,
	 * because the activation can happen beक्रमe the पूर्णांकerrupt is
	 * available क्रम request/startup. It has it's own state tracking so
	 * it's safe to call it unconditionally.
	 */
	irq_करोमुख्य_deactivate_irq(&desc->irq_data);
पूर्ण

व्योम irq_enable(काष्ठा irq_desc *desc)
अणु
	अगर (!irqd_irq_disabled(&desc->irq_data)) अणु
		unmask_irq(desc);
	पूर्ण अन्यथा अणु
		irq_state_clr_disabled(desc);
		अगर (desc->irq_data.chip->irq_enable) अणु
			desc->irq_data.chip->irq_enable(&desc->irq_data);
			irq_state_clr_masked(desc);
		पूर्ण अन्यथा अणु
			unmask_irq(desc);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __irq_disable(काष्ठा irq_desc *desc, bool mask)
अणु
	अगर (irqd_irq_disabled(&desc->irq_data)) अणु
		अगर (mask)
			mask_irq(desc);
	पूर्ण अन्यथा अणु
		irq_state_set_disabled(desc);
		अगर (desc->irq_data.chip->irq_disable) अणु
			desc->irq_data.chip->irq_disable(&desc->irq_data);
			irq_state_set_masked(desc);
		पूर्ण अन्यथा अगर (mask) अणु
			mask_irq(desc);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * irq_disable - Mark पूर्णांकerrupt disabled
 * @desc:	irq descriptor which should be disabled
 *
 * If the chip करोes not implement the irq_disable callback, we
 * use a lazy disable approach. That means we mark the पूर्णांकerrupt
 * disabled, but leave the hardware unmasked. That's an
 * optimization because we aव्योम the hardware access क्रम the
 * common हाल where no पूर्णांकerrupt happens after we marked it
 * disabled. If an पूर्णांकerrupt happens, then the पूर्णांकerrupt flow
 * handler masks the line at the hardware level and marks it
 * pending.
 *
 * If the पूर्णांकerrupt chip करोes not implement the irq_disable callback,
 * a driver can disable the lazy approach क्रम a particular irq line by
 * calling 'irq_set_status_flags(irq, IRQ_DISABLE_UNLAZY)'. This can
 * be used क्रम devices which cannot disable the पूर्णांकerrupt at the
 * device level under certain circumstances and have to use
 * disable_irq[_nosync] instead.
 */
व्योम irq_disable(काष्ठा irq_desc *desc)
अणु
	__irq_disable(desc, irq_settings_disable_unlazy(desc));
पूर्ण

व्योम irq_percpu_enable(काष्ठा irq_desc *desc, अचिन्हित पूर्णांक cpu)
अणु
	अगर (desc->irq_data.chip->irq_enable)
		desc->irq_data.chip->irq_enable(&desc->irq_data);
	अन्यथा
		desc->irq_data.chip->irq_unmask(&desc->irq_data);
	cpumask_set_cpu(cpu, desc->percpu_enabled);
पूर्ण

व्योम irq_percpu_disable(काष्ठा irq_desc *desc, अचिन्हित पूर्णांक cpu)
अणु
	अगर (desc->irq_data.chip->irq_disable)
		desc->irq_data.chip->irq_disable(&desc->irq_data);
	अन्यथा
		desc->irq_data.chip->irq_mask(&desc->irq_data);
	cpumask_clear_cpu(cpu, desc->percpu_enabled);
पूर्ण

अटल अंतरभूत व्योम mask_ack_irq(काष्ठा irq_desc *desc)
अणु
	अगर (desc->irq_data.chip->irq_mask_ack) अणु
		desc->irq_data.chip->irq_mask_ack(&desc->irq_data);
		irq_state_set_masked(desc);
	पूर्ण अन्यथा अणु
		mask_irq(desc);
		अगर (desc->irq_data.chip->irq_ack)
			desc->irq_data.chip->irq_ack(&desc->irq_data);
	पूर्ण
पूर्ण

व्योम mask_irq(काष्ठा irq_desc *desc)
अणु
	अगर (irqd_irq_masked(&desc->irq_data))
		वापस;

	अगर (desc->irq_data.chip->irq_mask) अणु
		desc->irq_data.chip->irq_mask(&desc->irq_data);
		irq_state_set_masked(desc);
	पूर्ण
पूर्ण

व्योम unmask_irq(काष्ठा irq_desc *desc)
अणु
	अगर (!irqd_irq_masked(&desc->irq_data))
		वापस;

	अगर (desc->irq_data.chip->irq_unmask) अणु
		desc->irq_data.chip->irq_unmask(&desc->irq_data);
		irq_state_clr_masked(desc);
	पूर्ण
पूर्ण

व्योम unmask_thपढ़ोed_irq(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = desc->irq_data.chip;

	अगर (chip->flags & IRQCHIP_EOI_THREADED)
		chip->irq_eoi(&desc->irq_data);

	unmask_irq(desc);
पूर्ण

/*
 *	handle_nested_irq - Handle a nested irq from a irq thपढ़ो
 *	@irq:	the पूर्णांकerrupt number
 *
 *	Handle पूर्णांकerrupts which are nested पूर्णांकo a thपढ़ोed पूर्णांकerrupt
 *	handler. The handler function is called inside the calling
 *	thपढ़ोs context.
 */
व्योम handle_nested_irq(अचिन्हित पूर्णांक irq)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(irq);
	काष्ठा irqaction *action;
	irqवापस_t action_ret;

	might_sleep();

	raw_spin_lock_irq(&desc->lock);

	desc->istate &= ~(IRQS_REPLAY | IRQS_WAITING);

	action = desc->action;
	अगर (unlikely(!action || irqd_irq_disabled(&desc->irq_data))) अणु
		desc->istate |= IRQS_PENDING;
		जाओ out_unlock;
	पूर्ण

	kstat_incr_irqs_this_cpu(desc);
	irqd_set(&desc->irq_data, IRQD_IRQ_INPROGRESS);
	raw_spin_unlock_irq(&desc->lock);

	action_ret = IRQ_NONE;
	क्रम_each_action_of_desc(desc, action)
		action_ret |= action->thपढ़ो_fn(action->irq, action->dev_id);

	अगर (!noirqdebug)
		note_पूर्णांकerrupt(desc, action_ret);

	raw_spin_lock_irq(&desc->lock);
	irqd_clear(&desc->irq_data, IRQD_IRQ_INPROGRESS);

out_unlock:
	raw_spin_unlock_irq(&desc->lock);
पूर्ण
EXPORT_SYMBOL_GPL(handle_nested_irq);

अटल bool irq_check_poll(काष्ठा irq_desc *desc)
अणु
	अगर (!(desc->istate & IRQS_POLL_INPROGRESS))
		वापस false;
	वापस irq_रुको_क्रम_poll(desc);
पूर्ण

अटल bool irq_may_run(काष्ठा irq_desc *desc)
अणु
	अचिन्हित पूर्णांक mask = IRQD_IRQ_INPROGRESS | IRQD_WAKEUP_ARMED;

	/*
	 * If the पूर्णांकerrupt is not in progress and is not an armed
	 * wakeup पूर्णांकerrupt, proceed.
	 */
	अगर (!irqd_has_set(&desc->irq_data, mask))
		वापस true;

	/*
	 * If the पूर्णांकerrupt is an armed wakeup source, mark it pending
	 * and suspended, disable it and notअगरy the pm core about the
	 * event.
	 */
	अगर (irq_pm_check_wakeup(desc))
		वापस false;

	/*
	 * Handle a potential concurrent poll on a dअगरferent core.
	 */
	वापस irq_check_poll(desc);
पूर्ण

/**
 *	handle_simple_irq - Simple and software-decoded IRQs.
 *	@desc:	the पूर्णांकerrupt description काष्ठाure क्रम this irq
 *
 *	Simple पूर्णांकerrupts are either sent from a demultiplexing पूर्णांकerrupt
 *	handler or come from hardware, where no पूर्णांकerrupt hardware control
 *	is necessary.
 *
 *	Note: The caller is expected to handle the ack, clear, mask and
 *	unmask issues अगर necessary.
 */
व्योम handle_simple_irq(काष्ठा irq_desc *desc)
अणु
	raw_spin_lock(&desc->lock);

	अगर (!irq_may_run(desc))
		जाओ out_unlock;

	desc->istate &= ~(IRQS_REPLAY | IRQS_WAITING);

	अगर (unlikely(!desc->action || irqd_irq_disabled(&desc->irq_data))) अणु
		desc->istate |= IRQS_PENDING;
		जाओ out_unlock;
	पूर्ण

	kstat_incr_irqs_this_cpu(desc);
	handle_irq_event(desc);

out_unlock:
	raw_spin_unlock(&desc->lock);
पूर्ण
EXPORT_SYMBOL_GPL(handle_simple_irq);

/**
 *	handle_untracked_irq - Simple and software-decoded IRQs.
 *	@desc:	the पूर्णांकerrupt description काष्ठाure क्रम this irq
 *
 *	Untracked पूर्णांकerrupts are sent from a demultiplexing पूर्णांकerrupt
 *	handler when the demultiplexer करोes not know which device it its
 *	multiplexed irq करोमुख्य generated the पूर्णांकerrupt. IRQ's handled
 *	through here are not subjected to stats tracking, अक्रमomness, or
 *	spurious पूर्णांकerrupt detection.
 *
 *	Note: Like handle_simple_irq, the caller is expected to handle
 *	the ack, clear, mask and unmask issues अगर necessary.
 */
व्योम handle_untracked_irq(काष्ठा irq_desc *desc)
अणु
	अचिन्हित पूर्णांक flags = 0;

	raw_spin_lock(&desc->lock);

	अगर (!irq_may_run(desc))
		जाओ out_unlock;

	desc->istate &= ~(IRQS_REPLAY | IRQS_WAITING);

	अगर (unlikely(!desc->action || irqd_irq_disabled(&desc->irq_data))) अणु
		desc->istate |= IRQS_PENDING;
		जाओ out_unlock;
	पूर्ण

	desc->istate &= ~IRQS_PENDING;
	irqd_set(&desc->irq_data, IRQD_IRQ_INPROGRESS);
	raw_spin_unlock(&desc->lock);

	__handle_irq_event_percpu(desc, &flags);

	raw_spin_lock(&desc->lock);
	irqd_clear(&desc->irq_data, IRQD_IRQ_INPROGRESS);

out_unlock:
	raw_spin_unlock(&desc->lock);
पूर्ण
EXPORT_SYMBOL_GPL(handle_untracked_irq);

/*
 * Called unconditionally from handle_level_irq() and only क्रम oneshot
 * पूर्णांकerrupts from handle_fasteoi_irq()
 */
अटल व्योम cond_unmask_irq(काष्ठा irq_desc *desc)
अणु
	/*
	 * We need to unmask in the following हालs:
	 * - Standard level irq (IRQF_ONESHOT is not set)
	 * - Oneshot irq which did not wake the thपढ़ो (caused by a
	 *   spurious पूर्णांकerrupt or a primary handler handling it
	 *   completely).
	 */
	अगर (!irqd_irq_disabled(&desc->irq_data) &&
	    irqd_irq_masked(&desc->irq_data) && !desc->thपढ़ोs_oneshot)
		unmask_irq(desc);
पूर्ण

/**
 *	handle_level_irq - Level type irq handler
 *	@desc:	the पूर्णांकerrupt description काष्ठाure क्रम this irq
 *
 *	Level type पूर्णांकerrupts are active as दीर्घ as the hardware line has
 *	the active level. This may require to mask the पूर्णांकerrupt and unmask
 *	it after the associated handler has acknowledged the device, so the
 *	पूर्णांकerrupt line is back to inactive.
 */
व्योम handle_level_irq(काष्ठा irq_desc *desc)
अणु
	raw_spin_lock(&desc->lock);
	mask_ack_irq(desc);

	अगर (!irq_may_run(desc))
		जाओ out_unlock;

	desc->istate &= ~(IRQS_REPLAY | IRQS_WAITING);

	/*
	 * If its disabled or no action available
	 * keep it masked and get out of here
	 */
	अगर (unlikely(!desc->action || irqd_irq_disabled(&desc->irq_data))) अणु
		desc->istate |= IRQS_PENDING;
		जाओ out_unlock;
	पूर्ण

	kstat_incr_irqs_this_cpu(desc);
	handle_irq_event(desc);

	cond_unmask_irq(desc);

out_unlock:
	raw_spin_unlock(&desc->lock);
पूर्ण
EXPORT_SYMBOL_GPL(handle_level_irq);

अटल व्योम cond_unmask_eoi_irq(काष्ठा irq_desc *desc, काष्ठा irq_chip *chip)
अणु
	अगर (!(desc->istate & IRQS_ONESHOT)) अणु
		chip->irq_eoi(&desc->irq_data);
		वापस;
	पूर्ण
	/*
	 * We need to unmask in the following हालs:
	 * - Oneshot irq which did not wake the thपढ़ो (caused by a
	 *   spurious पूर्णांकerrupt or a primary handler handling it
	 *   completely).
	 */
	अगर (!irqd_irq_disabled(&desc->irq_data) &&
	    irqd_irq_masked(&desc->irq_data) && !desc->thपढ़ोs_oneshot) अणु
		chip->irq_eoi(&desc->irq_data);
		unmask_irq(desc);
	पूर्ण अन्यथा अगर (!(chip->flags & IRQCHIP_EOI_THREADED)) अणु
		chip->irq_eoi(&desc->irq_data);
	पूर्ण
पूर्ण

/**
 *	handle_fasteoi_irq - irq handler क्रम transparent controllers
 *	@desc:	the पूर्णांकerrupt description काष्ठाure क्रम this irq
 *
 *	Only a single callback will be issued to the chip: an ->eoi()
 *	call when the पूर्णांकerrupt has been serviced. This enables support
 *	क्रम modern क्रमms of पूर्णांकerrupt handlers, which handle the flow
 *	details in hardware, transparently.
 */
व्योम handle_fasteoi_irq(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = desc->irq_data.chip;

	raw_spin_lock(&desc->lock);

	अगर (!irq_may_run(desc))
		जाओ out;

	desc->istate &= ~(IRQS_REPLAY | IRQS_WAITING);

	/*
	 * If its disabled or no action available
	 * then mask it and get out of here:
	 */
	अगर (unlikely(!desc->action || irqd_irq_disabled(&desc->irq_data))) अणु
		desc->istate |= IRQS_PENDING;
		mask_irq(desc);
		जाओ out;
	पूर्ण

	kstat_incr_irqs_this_cpu(desc);
	अगर (desc->istate & IRQS_ONESHOT)
		mask_irq(desc);

	handle_irq_event(desc);

	cond_unmask_eoi_irq(desc, chip);

	raw_spin_unlock(&desc->lock);
	वापस;
out:
	अगर (!(chip->flags & IRQCHIP_EOI_IF_HANDLED))
		chip->irq_eoi(&desc->irq_data);
	raw_spin_unlock(&desc->lock);
पूर्ण
EXPORT_SYMBOL_GPL(handle_fasteoi_irq);

/**
 *	handle_fasteoi_nmi - irq handler क्रम NMI पूर्णांकerrupt lines
 *	@desc:	the पूर्णांकerrupt description काष्ठाure क्रम this irq
 *
 *	A simple NMI-safe handler, considering the restrictions
 *	from request_nmi.
 *
 *	Only a single callback will be issued to the chip: an ->eoi()
 *	call when the पूर्णांकerrupt has been serviced. This enables support
 *	क्रम modern क्रमms of पूर्णांकerrupt handlers, which handle the flow
 *	details in hardware, transparently.
 */
व्योम handle_fasteoi_nmi(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा irqaction *action = desc->action;
	अचिन्हित पूर्णांक irq = irq_desc_get_irq(desc);
	irqवापस_t res;

	__kstat_incr_irqs_this_cpu(desc);

	trace_irq_handler_entry(irq, action);
	/*
	 * NMIs cannot be shared, there is only one action.
	 */
	res = action->handler(irq, action->dev_id);
	trace_irq_handler_निकास(irq, action, res);

	अगर (chip->irq_eoi)
		chip->irq_eoi(&desc->irq_data);
पूर्ण
EXPORT_SYMBOL_GPL(handle_fasteoi_nmi);

/**
 *	handle_edge_irq - edge type IRQ handler
 *	@desc:	the पूर्णांकerrupt description काष्ठाure क्रम this irq
 *
 *	Interrupt occurs on the falling and/or rising edge of a hardware
 *	संकेत. The occurrence is latched पूर्णांकo the irq controller hardware
 *	and must be acked in order to be reenabled. After the ack another
 *	पूर्णांकerrupt can happen on the same source even beक्रमe the first one
 *	is handled by the associated event handler. If this happens it
 *	might be necessary to disable (mask) the पूर्णांकerrupt depending on the
 *	controller hardware. This requires to reenable the पूर्णांकerrupt inside
 *	of the loop which handles the पूर्णांकerrupts which have arrived जबतक
 *	the handler was running. If all pending पूर्णांकerrupts are handled, the
 *	loop is left.
 */
व्योम handle_edge_irq(काष्ठा irq_desc *desc)
अणु
	raw_spin_lock(&desc->lock);

	desc->istate &= ~(IRQS_REPLAY | IRQS_WAITING);

	अगर (!irq_may_run(desc)) अणु
		desc->istate |= IRQS_PENDING;
		mask_ack_irq(desc);
		जाओ out_unlock;
	पूर्ण

	/*
	 * If its disabled or no action available then mask it and get
	 * out of here.
	 */
	अगर (irqd_irq_disabled(&desc->irq_data) || !desc->action) अणु
		desc->istate |= IRQS_PENDING;
		mask_ack_irq(desc);
		जाओ out_unlock;
	पूर्ण

	kstat_incr_irqs_this_cpu(desc);

	/* Start handling the irq */
	desc->irq_data.chip->irq_ack(&desc->irq_data);

	करो अणु
		अगर (unlikely(!desc->action)) अणु
			mask_irq(desc);
			जाओ out_unlock;
		पूर्ण

		/*
		 * When another irq arrived जबतक we were handling
		 * one, we could have masked the irq.
		 * Reenable it, अगर it was not disabled in meanसमय.
		 */
		अगर (unlikely(desc->istate & IRQS_PENDING)) अणु
			अगर (!irqd_irq_disabled(&desc->irq_data) &&
			    irqd_irq_masked(&desc->irq_data))
				unmask_irq(desc);
		पूर्ण

		handle_irq_event(desc);

	पूर्ण जबतक ((desc->istate & IRQS_PENDING) &&
		 !irqd_irq_disabled(&desc->irq_data));

out_unlock:
	raw_spin_unlock(&desc->lock);
पूर्ण
EXPORT_SYMBOL(handle_edge_irq);

#अगर_घोषित CONFIG_IRQ_EDGE_EOI_HANDLER
/**
 *	handle_edge_eoi_irq - edge eoi type IRQ handler
 *	@desc:	the पूर्णांकerrupt description काष्ठाure क्रम this irq
 *
 * Similar as the above handle_edge_irq, but using eoi and w/o the
 * mask/unmask logic.
 */
व्योम handle_edge_eoi_irq(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);

	raw_spin_lock(&desc->lock);

	desc->istate &= ~(IRQS_REPLAY | IRQS_WAITING);

	अगर (!irq_may_run(desc)) अणु
		desc->istate |= IRQS_PENDING;
		जाओ out_eoi;
	पूर्ण

	/*
	 * If its disabled or no action available then mask it and get
	 * out of here.
	 */
	अगर (irqd_irq_disabled(&desc->irq_data) || !desc->action) अणु
		desc->istate |= IRQS_PENDING;
		जाओ out_eoi;
	पूर्ण

	kstat_incr_irqs_this_cpu(desc);

	करो अणु
		अगर (unlikely(!desc->action))
			जाओ out_eoi;

		handle_irq_event(desc);

	पूर्ण जबतक ((desc->istate & IRQS_PENDING) &&
		 !irqd_irq_disabled(&desc->irq_data));

out_eoi:
	chip->irq_eoi(&desc->irq_data);
	raw_spin_unlock(&desc->lock);
पूर्ण
#पूर्ण_अगर

/**
 *	handle_percpu_irq - Per CPU local irq handler
 *	@desc:	the पूर्णांकerrupt description काष्ठाure क्रम this irq
 *
 *	Per CPU पूर्णांकerrupts on SMP machines without locking requirements
 */
व्योम handle_percpu_irq(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);

	/*
	 * PER CPU पूर्णांकerrupts are not serialized. Do not touch
	 * desc->tot_count.
	 */
	__kstat_incr_irqs_this_cpu(desc);

	अगर (chip->irq_ack)
		chip->irq_ack(&desc->irq_data);

	handle_irq_event_percpu(desc);

	अगर (chip->irq_eoi)
		chip->irq_eoi(&desc->irq_data);
पूर्ण

/**
 * handle_percpu_devid_irq - Per CPU local irq handler with per cpu dev ids
 * @desc:	the पूर्णांकerrupt description काष्ठाure क्रम this irq
 *
 * Per CPU पूर्णांकerrupts on SMP machines without locking requirements. Same as
 * handle_percpu_irq() above but with the following extras:
 *
 * action->percpu_dev_id is a poपूर्णांकer to percpu variables which
 * contain the real device id क्रम the cpu on which this handler is
 * called
 */
व्योम handle_percpu_devid_irq(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा irqaction *action = desc->action;
	अचिन्हित पूर्णांक irq = irq_desc_get_irq(desc);
	irqवापस_t res;

	/*
	 * PER CPU पूर्णांकerrupts are not serialized. Do not touch
	 * desc->tot_count.
	 */
	__kstat_incr_irqs_this_cpu(desc);

	अगर (chip->irq_ack)
		chip->irq_ack(&desc->irq_data);

	अगर (likely(action)) अणु
		trace_irq_handler_entry(irq, action);
		res = action->handler(irq, raw_cpu_ptr(action->percpu_dev_id));
		trace_irq_handler_निकास(irq, action, res);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक cpu = smp_processor_id();
		bool enabled = cpumask_test_cpu(cpu, desc->percpu_enabled);

		अगर (enabled)
			irq_percpu_disable(desc, cpu);

		pr_err_once("Spurious%s percpu IRQ%u on CPU%u\n",
			    enabled ? " and unmasked" : "", irq, cpu);
	पूर्ण

	अगर (chip->irq_eoi)
		chip->irq_eoi(&desc->irq_data);
पूर्ण

/**
 * handle_percpu_devid_fasteoi_nmi - Per CPU local NMI handler with per cpu
 *				     dev ids
 * @desc:	the पूर्णांकerrupt description काष्ठाure क्रम this irq
 *
 * Similar to handle_fasteoi_nmi, but handling the dev_id cookie
 * as a percpu poपूर्णांकer.
 */
व्योम handle_percpu_devid_fasteoi_nmi(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा irqaction *action = desc->action;
	अचिन्हित पूर्णांक irq = irq_desc_get_irq(desc);
	irqवापस_t res;

	__kstat_incr_irqs_this_cpu(desc);

	trace_irq_handler_entry(irq, action);
	res = action->handler(irq, raw_cpu_ptr(action->percpu_dev_id));
	trace_irq_handler_निकास(irq, action, res);

	अगर (chip->irq_eoi)
		chip->irq_eoi(&desc->irq_data);
पूर्ण

अटल व्योम
__irq_करो_set_handler(काष्ठा irq_desc *desc, irq_flow_handler_t handle,
		     पूर्णांक is_chained, स्थिर अक्षर *name)
अणु
	अगर (!handle) अणु
		handle = handle_bad_irq;
	पूर्ण अन्यथा अणु
		काष्ठा irq_data *irq_data = &desc->irq_data;
#अगर_घोषित CONFIG_IRQ_DOMAIN_HIERARCHY
		/*
		 * With hierarchical करोमुख्यs we might run पूर्णांकo a
		 * situation where the outermost chip is not yet set
		 * up, but the inner chips are there.  Instead of
		 * bailing we install the handler, but obviously we
		 * cannot enable/startup the पूर्णांकerrupt at this poपूर्णांक.
		 */
		जबतक (irq_data) अणु
			अगर (irq_data->chip != &no_irq_chip)
				अवरोध;
			/*
			 * Bail out अगर the outer chip is not set up
			 * and the पूर्णांकerrupt supposed to be started
			 * right away.
			 */
			अगर (WARN_ON(is_chained))
				वापस;
			/* Try the parent */
			irq_data = irq_data->parent_data;
		पूर्ण
#पूर्ण_अगर
		अगर (WARN_ON(!irq_data || irq_data->chip == &no_irq_chip))
			वापस;
	पूर्ण

	/* Uninstall? */
	अगर (handle == handle_bad_irq) अणु
		अगर (desc->irq_data.chip != &no_irq_chip)
			mask_ack_irq(desc);
		irq_state_set_disabled(desc);
		अगर (is_chained)
			desc->action = शून्य;
		desc->depth = 1;
	पूर्ण
	desc->handle_irq = handle;
	desc->name = name;

	अगर (handle != handle_bad_irq && is_chained) अणु
		अचिन्हित पूर्णांक type = irqd_get_trigger_type(&desc->irq_data);

		/*
		 * We're about to start this पूर्णांकerrupt immediately,
		 * hence the need to set the trigger configuration.
		 * But the .set_type callback may have overridden the
		 * flow handler, ignoring that we're dealing with a
		 * chained पूर्णांकerrupt. Reset it immediately because we
		 * करो know better.
		 */
		अगर (type != IRQ_TYPE_NONE) अणु
			__irq_set_trigger(desc, type);
			desc->handle_irq = handle;
		पूर्ण

		irq_settings_set_noprobe(desc);
		irq_settings_set_norequest(desc);
		irq_settings_set_nothपढ़ो(desc);
		desc->action = &chained_action;
		irq_activate_and_startup(desc, IRQ_RESEND);
	पूर्ण
पूर्ण

व्योम
__irq_set_handler(अचिन्हित पूर्णांक irq, irq_flow_handler_t handle, पूर्णांक is_chained,
		  स्थिर अक्षर *name)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा irq_desc *desc = irq_get_desc_buslock(irq, &flags, 0);

	अगर (!desc)
		वापस;

	__irq_करो_set_handler(desc, handle, is_chained, name);
	irq_put_desc_busunlock(desc, flags);
पूर्ण
EXPORT_SYMBOL_GPL(__irq_set_handler);

व्योम
irq_set_chained_handler_and_data(अचिन्हित पूर्णांक irq, irq_flow_handler_t handle,
				 व्योम *data)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा irq_desc *desc = irq_get_desc_buslock(irq, &flags, 0);

	अगर (!desc)
		वापस;

	desc->irq_common_data.handler_data = data;
	__irq_करो_set_handler(desc, handle, 1, शून्य);

	irq_put_desc_busunlock(desc, flags);
पूर्ण
EXPORT_SYMBOL_GPL(irq_set_chained_handler_and_data);

व्योम
irq_set_chip_and_handler_name(अचिन्हित पूर्णांक irq, काष्ठा irq_chip *chip,
			      irq_flow_handler_t handle, स्थिर अक्षर *name)
अणु
	irq_set_chip(irq, chip);
	__irq_set_handler(irq, handle, 0, name);
पूर्ण
EXPORT_SYMBOL_GPL(irq_set_chip_and_handler_name);

व्योम irq_modअगरy_status(अचिन्हित पूर्णांक irq, अचिन्हित दीर्घ clr, अचिन्हित दीर्घ set)
अणु
	अचिन्हित दीर्घ flags, trigger, पंचांगp;
	काष्ठा irq_desc *desc = irq_get_desc_lock(irq, &flags, 0);

	अगर (!desc)
		वापस;

	/*
	 * Warn when a driver sets the no स्वतःenable flag on an alपढ़ोy
	 * active पूर्णांकerrupt.
	 */
	WARN_ON_ONCE(!desc->depth && (set & _IRQ_NOAUTOEN));

	irq_settings_clr_and_set(desc, clr, set);

	trigger = irqd_get_trigger_type(&desc->irq_data);

	irqd_clear(&desc->irq_data, IRQD_NO_BALANCING | IRQD_PER_CPU |
		   IRQD_TRIGGER_MASK | IRQD_LEVEL | IRQD_MOVE_PCNTXT);
	अगर (irq_settings_has_no_balance_set(desc))
		irqd_set(&desc->irq_data, IRQD_NO_BALANCING);
	अगर (irq_settings_is_per_cpu(desc))
		irqd_set(&desc->irq_data, IRQD_PER_CPU);
	अगर (irq_settings_can_move_pcntxt(desc))
		irqd_set(&desc->irq_data, IRQD_MOVE_PCNTXT);
	अगर (irq_settings_is_level(desc))
		irqd_set(&desc->irq_data, IRQD_LEVEL);

	पंचांगp = irq_settings_get_trigger_mask(desc);
	अगर (पंचांगp != IRQ_TYPE_NONE)
		trigger = पंचांगp;

	irqd_set(&desc->irq_data, trigger);

	irq_put_desc_unlock(desc, flags);
पूर्ण
EXPORT_SYMBOL_GPL(irq_modअगरy_status);

/**
 *	irq_cpu_online - Invoke all irq_cpu_online functions.
 *
 *	Iterate through all irqs and invoke the chip.irq_cpu_online()
 *	क्रम each.
 */
व्योम irq_cpu_online(व्योम)
अणु
	काष्ठा irq_desc *desc;
	काष्ठा irq_chip *chip;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक irq;

	क्रम_each_active_irq(irq) अणु
		desc = irq_to_desc(irq);
		अगर (!desc)
			जारी;

		raw_spin_lock_irqsave(&desc->lock, flags);

		chip = irq_data_get_irq_chip(&desc->irq_data);
		अगर (chip && chip->irq_cpu_online &&
		    (!(chip->flags & IRQCHIP_ONOFFLINE_ENABLED) ||
		     !irqd_irq_disabled(&desc->irq_data)))
			chip->irq_cpu_online(&desc->irq_data);

		raw_spin_unlock_irqrestore(&desc->lock, flags);
	पूर्ण
पूर्ण

/**
 *	irq_cpu_offline - Invoke all irq_cpu_offline functions.
 *
 *	Iterate through all irqs and invoke the chip.irq_cpu_offline()
 *	क्रम each.
 */
व्योम irq_cpu_offline(व्योम)
अणु
	काष्ठा irq_desc *desc;
	काष्ठा irq_chip *chip;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक irq;

	क्रम_each_active_irq(irq) अणु
		desc = irq_to_desc(irq);
		अगर (!desc)
			जारी;

		raw_spin_lock_irqsave(&desc->lock, flags);

		chip = irq_data_get_irq_chip(&desc->irq_data);
		अगर (chip && chip->irq_cpu_offline &&
		    (!(chip->flags & IRQCHIP_ONOFFLINE_ENABLED) ||
		     !irqd_irq_disabled(&desc->irq_data)))
			chip->irq_cpu_offline(&desc->irq_data);

		raw_spin_unlock_irqrestore(&desc->lock, flags);
	पूर्ण
पूर्ण

#अगर_घोषित	CONFIG_IRQ_DOMAIN_HIERARCHY

#अगर_घोषित CONFIG_IRQ_FASTEOI_HIERARCHY_HANDLERS
/**
 *	handle_fasteoi_ack_irq - irq handler क्रम edge hierarchy
 *	stacked on transparent controllers
 *
 *	@desc:	the पूर्णांकerrupt description काष्ठाure क्रम this irq
 *
 *	Like handle_fasteoi_irq(), but क्रम use with hierarchy where
 *	the irq_chip also needs to have its ->irq_ack() function
 *	called.
 */
व्योम handle_fasteoi_ack_irq(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = desc->irq_data.chip;

	raw_spin_lock(&desc->lock);

	अगर (!irq_may_run(desc))
		जाओ out;

	desc->istate &= ~(IRQS_REPLAY | IRQS_WAITING);

	/*
	 * If its disabled or no action available
	 * then mask it and get out of here:
	 */
	अगर (unlikely(!desc->action || irqd_irq_disabled(&desc->irq_data))) अणु
		desc->istate |= IRQS_PENDING;
		mask_irq(desc);
		जाओ out;
	पूर्ण

	kstat_incr_irqs_this_cpu(desc);
	अगर (desc->istate & IRQS_ONESHOT)
		mask_irq(desc);

	/* Start handling the irq */
	desc->irq_data.chip->irq_ack(&desc->irq_data);

	handle_irq_event(desc);

	cond_unmask_eoi_irq(desc, chip);

	raw_spin_unlock(&desc->lock);
	वापस;
out:
	अगर (!(chip->flags & IRQCHIP_EOI_IF_HANDLED))
		chip->irq_eoi(&desc->irq_data);
	raw_spin_unlock(&desc->lock);
पूर्ण
EXPORT_SYMBOL_GPL(handle_fasteoi_ack_irq);

/**
 *	handle_fasteoi_mask_irq - irq handler क्रम level hierarchy
 *	stacked on transparent controllers
 *
 *	@desc:	the पूर्णांकerrupt description काष्ठाure क्रम this irq
 *
 *	Like handle_fasteoi_irq(), but क्रम use with hierarchy where
 *	the irq_chip also needs to have its ->irq_mask_ack() function
 *	called.
 */
व्योम handle_fasteoi_mask_irq(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = desc->irq_data.chip;

	raw_spin_lock(&desc->lock);
	mask_ack_irq(desc);

	अगर (!irq_may_run(desc))
		जाओ out;

	desc->istate &= ~(IRQS_REPLAY | IRQS_WAITING);

	/*
	 * If its disabled or no action available
	 * then mask it and get out of here:
	 */
	अगर (unlikely(!desc->action || irqd_irq_disabled(&desc->irq_data))) अणु
		desc->istate |= IRQS_PENDING;
		mask_irq(desc);
		जाओ out;
	पूर्ण

	kstat_incr_irqs_this_cpu(desc);
	अगर (desc->istate & IRQS_ONESHOT)
		mask_irq(desc);

	handle_irq_event(desc);

	cond_unmask_eoi_irq(desc, chip);

	raw_spin_unlock(&desc->lock);
	वापस;
out:
	अगर (!(chip->flags & IRQCHIP_EOI_IF_HANDLED))
		chip->irq_eoi(&desc->irq_data);
	raw_spin_unlock(&desc->lock);
पूर्ण
EXPORT_SYMBOL_GPL(handle_fasteoi_mask_irq);

#पूर्ण_अगर /* CONFIG_IRQ_FASTEOI_HIERARCHY_HANDLERS */

/**
 * irq_chip_set_parent_state - set the state of a parent पूर्णांकerrupt.
 *
 * @data: Poपूर्णांकer to पूर्णांकerrupt specअगरic data
 * @which: State to be restored (one of IRQCHIP_STATE_*)
 * @val: Value corresponding to @which
 *
 * Conditional success, अगर the underlying irqchip करोes not implement it.
 */
पूर्णांक irq_chip_set_parent_state(काष्ठा irq_data *data,
			      क्रमागत irqchip_irq_state which,
			      bool val)
अणु
	data = data->parent_data;

	अगर (!data || !data->chip->irq_set_irqchip_state)
		वापस 0;

	वापस data->chip->irq_set_irqchip_state(data, which, val);
पूर्ण
EXPORT_SYMBOL_GPL(irq_chip_set_parent_state);

/**
 * irq_chip_get_parent_state - get the state of a parent पूर्णांकerrupt.
 *
 * @data: Poपूर्णांकer to पूर्णांकerrupt specअगरic data
 * @which: one of IRQCHIP_STATE_* the caller wants to know
 * @state: a poपूर्णांकer to a boolean where the state is to be stored
 *
 * Conditional success, अगर the underlying irqchip करोes not implement it.
 */
पूर्णांक irq_chip_get_parent_state(काष्ठा irq_data *data,
			      क्रमागत irqchip_irq_state which,
			      bool *state)
अणु
	data = data->parent_data;

	अगर (!data || !data->chip->irq_get_irqchip_state)
		वापस 0;

	वापस data->chip->irq_get_irqchip_state(data, which, state);
पूर्ण
EXPORT_SYMBOL_GPL(irq_chip_get_parent_state);

/**
 * irq_chip_enable_parent - Enable the parent पूर्णांकerrupt (शेषs to unmask अगर
 * शून्य)
 * @data:	Poपूर्णांकer to पूर्णांकerrupt specअगरic data
 */
व्योम irq_chip_enable_parent(काष्ठा irq_data *data)
अणु
	data = data->parent_data;
	अगर (data->chip->irq_enable)
		data->chip->irq_enable(data);
	अन्यथा
		data->chip->irq_unmask(data);
पूर्ण
EXPORT_SYMBOL_GPL(irq_chip_enable_parent);

/**
 * irq_chip_disable_parent - Disable the parent पूर्णांकerrupt (शेषs to mask अगर
 * शून्य)
 * @data:	Poपूर्णांकer to पूर्णांकerrupt specअगरic data
 */
व्योम irq_chip_disable_parent(काष्ठा irq_data *data)
अणु
	data = data->parent_data;
	अगर (data->chip->irq_disable)
		data->chip->irq_disable(data);
	अन्यथा
		data->chip->irq_mask(data);
पूर्ण
EXPORT_SYMBOL_GPL(irq_chip_disable_parent);

/**
 * irq_chip_ack_parent - Acknowledge the parent पूर्णांकerrupt
 * @data:	Poपूर्णांकer to पूर्णांकerrupt specअगरic data
 */
व्योम irq_chip_ack_parent(काष्ठा irq_data *data)
अणु
	data = data->parent_data;
	data->chip->irq_ack(data);
पूर्ण
EXPORT_SYMBOL_GPL(irq_chip_ack_parent);

/**
 * irq_chip_mask_parent - Mask the parent पूर्णांकerrupt
 * @data:	Poपूर्णांकer to पूर्णांकerrupt specअगरic data
 */
व्योम irq_chip_mask_parent(काष्ठा irq_data *data)
अणु
	data = data->parent_data;
	data->chip->irq_mask(data);
पूर्ण
EXPORT_SYMBOL_GPL(irq_chip_mask_parent);

/**
 * irq_chip_mask_ack_parent - Mask and acknowledge the parent पूर्णांकerrupt
 * @data:	Poपूर्णांकer to पूर्णांकerrupt specअगरic data
 */
व्योम irq_chip_mask_ack_parent(काष्ठा irq_data *data)
अणु
	data = data->parent_data;
	data->chip->irq_mask_ack(data);
पूर्ण
EXPORT_SYMBOL_GPL(irq_chip_mask_ack_parent);

/**
 * irq_chip_unmask_parent - Unmask the parent पूर्णांकerrupt
 * @data:	Poपूर्णांकer to पूर्णांकerrupt specअगरic data
 */
व्योम irq_chip_unmask_parent(काष्ठा irq_data *data)
अणु
	data = data->parent_data;
	data->chip->irq_unmask(data);
पूर्ण
EXPORT_SYMBOL_GPL(irq_chip_unmask_parent);

/**
 * irq_chip_eoi_parent - Invoke EOI on the parent पूर्णांकerrupt
 * @data:	Poपूर्णांकer to पूर्णांकerrupt specअगरic data
 */
व्योम irq_chip_eoi_parent(काष्ठा irq_data *data)
अणु
	data = data->parent_data;
	data->chip->irq_eoi(data);
पूर्ण
EXPORT_SYMBOL_GPL(irq_chip_eoi_parent);

/**
 * irq_chip_set_affinity_parent - Set affinity on the parent पूर्णांकerrupt
 * @data:	Poपूर्णांकer to पूर्णांकerrupt specअगरic data
 * @dest:	The affinity mask to set
 * @क्रमce:	Flag to enक्रमce setting (disable online checks)
 *
 * Conditional, as the underlying parent chip might not implement it.
 */
पूर्णांक irq_chip_set_affinity_parent(काष्ठा irq_data *data,
				 स्थिर काष्ठा cpumask *dest, bool क्रमce)
अणु
	data = data->parent_data;
	अगर (data->chip->irq_set_affinity)
		वापस data->chip->irq_set_affinity(data, dest, क्रमce);

	वापस -ENOSYS;
पूर्ण
EXPORT_SYMBOL_GPL(irq_chip_set_affinity_parent);

/**
 * irq_chip_set_type_parent - Set IRQ type on the parent पूर्णांकerrupt
 * @data:	Poपूर्णांकer to पूर्णांकerrupt specअगरic data
 * @type:	IRQ_TYPE_अणुLEVEL,EDGEपूर्ण_* value - see include/linux/irq.h
 *
 * Conditional, as the underlying parent chip might not implement it.
 */
पूर्णांक irq_chip_set_type_parent(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	data = data->parent_data;

	अगर (data->chip->irq_set_type)
		वापस data->chip->irq_set_type(data, type);

	वापस -ENOSYS;
पूर्ण
EXPORT_SYMBOL_GPL(irq_chip_set_type_parent);

/**
 * irq_chip_retrigger_hierarchy - Retrigger an पूर्णांकerrupt in hardware
 * @data:	Poपूर्णांकer to पूर्णांकerrupt specअगरic data
 *
 * Iterate through the करोमुख्य hierarchy of the पूर्णांकerrupt and check
 * whether a hw retrigger function exists. If yes, invoke it.
 */
पूर्णांक irq_chip_retrigger_hierarchy(काष्ठा irq_data *data)
अणु
	क्रम (data = data->parent_data; data; data = data->parent_data)
		अगर (data->chip && data->chip->irq_retrigger)
			वापस data->chip->irq_retrigger(data);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(irq_chip_retrigger_hierarchy);

/**
 * irq_chip_set_vcpu_affinity_parent - Set vcpu affinity on the parent पूर्णांकerrupt
 * @data:	Poपूर्णांकer to पूर्णांकerrupt specअगरic data
 * @vcpu_info:	The vcpu affinity inक्रमmation
 */
पूर्णांक irq_chip_set_vcpu_affinity_parent(काष्ठा irq_data *data, व्योम *vcpu_info)
अणु
	data = data->parent_data;
	अगर (data->chip->irq_set_vcpu_affinity)
		वापस data->chip->irq_set_vcpu_affinity(data, vcpu_info);

	वापस -ENOSYS;
पूर्ण
EXPORT_SYMBOL_GPL(irq_chip_set_vcpu_affinity_parent);
/**
 * irq_chip_set_wake_parent - Set/reset wake-up on the parent पूर्णांकerrupt
 * @data:	Poपूर्णांकer to पूर्णांकerrupt specअगरic data
 * @on:		Whether to set or reset the wake-up capability of this irq
 *
 * Conditional, as the underlying parent chip might not implement it.
 */
पूर्णांक irq_chip_set_wake_parent(काष्ठा irq_data *data, अचिन्हित पूर्णांक on)
अणु
	data = data->parent_data;

	अगर (data->chip->flags & IRQCHIP_SKIP_SET_WAKE)
		वापस 0;

	अगर (data->chip->irq_set_wake)
		वापस data->chip->irq_set_wake(data, on);

	वापस -ENOSYS;
पूर्ण
EXPORT_SYMBOL_GPL(irq_chip_set_wake_parent);

/**
 * irq_chip_request_resources_parent - Request resources on the parent पूर्णांकerrupt
 * @data:	Poपूर्णांकer to पूर्णांकerrupt specअगरic data
 */
पूर्णांक irq_chip_request_resources_parent(काष्ठा irq_data *data)
अणु
	data = data->parent_data;

	अगर (data->chip->irq_request_resources)
		वापस data->chip->irq_request_resources(data);

	वापस -ENOSYS;
पूर्ण
EXPORT_SYMBOL_GPL(irq_chip_request_resources_parent);

/**
 * irq_chip_release_resources_parent - Release resources on the parent पूर्णांकerrupt
 * @data:	Poपूर्णांकer to पूर्णांकerrupt specअगरic data
 */
व्योम irq_chip_release_resources_parent(काष्ठा irq_data *data)
अणु
	data = data->parent_data;
	अगर (data->chip->irq_release_resources)
		data->chip->irq_release_resources(data);
पूर्ण
EXPORT_SYMBOL_GPL(irq_chip_release_resources_parent);
#पूर्ण_अगर

/**
 * irq_chip_compose_msi_msg - Compose msi message क्रम a irq chip
 * @data:	Poपूर्णांकer to पूर्णांकerrupt specअगरic data
 * @msg:	Poपूर्णांकer to the MSI message
 *
 * For hierarchical करोमुख्यs we find the first chip in the hierarchy
 * which implements the irq_compose_msi_msg callback. For non
 * hierarchical we use the top level chip.
 */
पूर्णांक irq_chip_compose_msi_msg(काष्ठा irq_data *data, काष्ठा msi_msg *msg)
अणु
	काष्ठा irq_data *pos;

	क्रम (pos = शून्य; !pos && data; data = irqd_get_parent_data(data)) अणु
		अगर (data->chip && data->chip->irq_compose_msi_msg)
			pos = data;
	पूर्ण

	अगर (!pos)
		वापस -ENOSYS;

	pos->chip->irq_compose_msi_msg(pos, msg);
	वापस 0;
पूर्ण

/**
 * irq_chip_pm_get - Enable घातer क्रम an IRQ chip
 * @data:	Poपूर्णांकer to पूर्णांकerrupt specअगरic data
 *
 * Enable the घातer to the IRQ chip referenced by the पूर्णांकerrupt data
 * काष्ठाure.
 */
पूर्णांक irq_chip_pm_get(काष्ठा irq_data *data)
अणु
	पूर्णांक retval;

	अगर (IS_ENABLED(CONFIG_PM) && data->chip->parent_device) अणु
		retval = pm_runसमय_get_sync(data->chip->parent_device);
		अगर (retval < 0) अणु
			pm_runसमय_put_noidle(data->chip->parent_device);
			वापस retval;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * irq_chip_pm_put - Disable घातer क्रम an IRQ chip
 * @data:	Poपूर्णांकer to पूर्णांकerrupt specअगरic data
 *
 * Disable the घातer to the IRQ chip referenced by the पूर्णांकerrupt data
 * काष्ठाure, beदीर्घs. Note that घातer will only be disabled, once this
 * function has been called क्रम all IRQs that have called irq_chip_pm_get().
 */
पूर्णांक irq_chip_pm_put(काष्ठा irq_data *data)
अणु
	पूर्णांक retval = 0;

	अगर (IS_ENABLED(CONFIG_PM) && data->chip->parent_device)
		retval = pm_runसमय_put(data->chip->parent_device);

	वापस (retval < 0) ? retval : 0;
पूर्ण
