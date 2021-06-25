<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2009 Rafael J. Wysocki <rjw@sisk.pl>, Novell Inc.
 *
 * This file contains घातer management functions related to पूर्णांकerrupts.
 */

#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/suspend.h>
#समावेश <linux/syscore_ops.h>

#समावेश "internals.h"

bool irq_pm_check_wakeup(काष्ठा irq_desc *desc)
अणु
	अगर (irqd_is_wakeup_armed(&desc->irq_data)) अणु
		irqd_clear(&desc->irq_data, IRQD_WAKEUP_ARMED);
		desc->istate |= IRQS_SUSPENDED | IRQS_PENDING;
		desc->depth++;
		irq_disable(desc);
		pm_प्रणाली_irq_wakeup(irq_desc_get_irq(desc));
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * Called from __setup_irq() with desc->lock held after @action has
 * been installed in the action chain.
 */
व्योम irq_pm_install_action(काष्ठा irq_desc *desc, काष्ठा irqaction *action)
अणु
	desc->nr_actions++;

	अगर (action->flags & IRQF_FORCE_RESUME)
		desc->क्रमce_resume_depth++;

	WARN_ON_ONCE(desc->क्रमce_resume_depth &&
		     desc->क्रमce_resume_depth != desc->nr_actions);

	अगर (action->flags & IRQF_NO_SUSPEND)
		desc->no_suspend_depth++;
	अन्यथा अगर (action->flags & IRQF_COND_SUSPEND)
		desc->cond_suspend_depth++;

	WARN_ON_ONCE(desc->no_suspend_depth &&
		     (desc->no_suspend_depth +
			desc->cond_suspend_depth) != desc->nr_actions);
पूर्ण

/*
 * Called from __मुक्त_irq() with desc->lock held after @action has
 * been हटाओd from the action chain.
 */
व्योम irq_pm_हटाओ_action(काष्ठा irq_desc *desc, काष्ठा irqaction *action)
अणु
	desc->nr_actions--;

	अगर (action->flags & IRQF_FORCE_RESUME)
		desc->क्रमce_resume_depth--;

	अगर (action->flags & IRQF_NO_SUSPEND)
		desc->no_suspend_depth--;
	अन्यथा अगर (action->flags & IRQF_COND_SUSPEND)
		desc->cond_suspend_depth--;
पूर्ण

अटल bool suspend_device_irq(काष्ठा irq_desc *desc)
अणु
	अचिन्हित दीर्घ chipflags = irq_desc_get_chip(desc)->flags;
	काष्ठा irq_data *irqd = &desc->irq_data;

	अगर (!desc->action || irq_desc_is_chained(desc) ||
	    desc->no_suspend_depth)
		वापस false;

	अगर (irqd_is_wakeup_set(irqd)) अणु
		irqd_set(irqd, IRQD_WAKEUP_ARMED);

		अगर ((chipflags & IRQCHIP_ENABLE_WAKEUP_ON_SUSPEND) &&
		     irqd_irq_disabled(irqd)) अणु
			/*
			 * Interrupt marked क्रम wakeup is in disabled state.
			 * Enable पूर्णांकerrupt here to unmask/enable in irqchip
			 * to be able to resume with such पूर्णांकerrupts.
			 */
			__enable_irq(desc);
			irqd_set(irqd, IRQD_IRQ_ENABLED_ON_SUSPEND);
		पूर्ण
		/*
		 * We वापस true here to क्रमce the caller to issue
		 * synchronize_irq(). We need to make sure that the
		 * IRQD_WAKEUP_ARMED is visible beक्रमe we वापस from
		 * suspend_device_irqs().
		 */
		वापस true;
	पूर्ण

	desc->istate |= IRQS_SUSPENDED;
	__disable_irq(desc);

	/*
	 * Hardware which has no wakeup source configuration facility
	 * requires that the non wakeup पूर्णांकerrupts are masked at the
	 * chip level. The chip implementation indicates that with
	 * IRQCHIP_MASK_ON_SUSPEND.
	 */
	अगर (chipflags & IRQCHIP_MASK_ON_SUSPEND)
		mask_irq(desc);
	वापस true;
पूर्ण

/**
 * suspend_device_irqs - disable all currently enabled पूर्णांकerrupt lines
 *
 * During प्रणाली-wide suspend or hibernation device drivers need to be
 * prevented from receiving पूर्णांकerrupts and this function is provided
 * क्रम this purpose.
 *
 * So we disable all पूर्णांकerrupts and mark them IRQS_SUSPENDED except
 * क्रम those which are unused, those which are marked as not
 * suspendable via an पूर्णांकerrupt request with the flag IRQF_NO_SUSPEND
 * set and those which are marked as active wakeup sources.
 *
 * The active wakeup sources are handled by the flow handler entry
 * code which checks क्रम the IRQD_WAKEUP_ARMED flag, suspends the
 * पूर्णांकerrupt and notअगरies the pm core about the wakeup.
 */
व्योम suspend_device_irqs(व्योम)
अणु
	काष्ठा irq_desc *desc;
	पूर्णांक irq;

	क्रम_each_irq_desc(irq, desc) अणु
		अचिन्हित दीर्घ flags;
		bool sync;

		अगर (irq_settings_is_nested_thपढ़ो(desc))
			जारी;
		raw_spin_lock_irqsave(&desc->lock, flags);
		sync = suspend_device_irq(desc);
		raw_spin_unlock_irqrestore(&desc->lock, flags);

		अगर (sync)
			synchronize_irq(irq);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(suspend_device_irqs);

अटल व्योम resume_irq(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_data *irqd = &desc->irq_data;

	irqd_clear(irqd, IRQD_WAKEUP_ARMED);

	अगर (irqd_is_enabled_on_suspend(irqd)) अणु
		/*
		 * Interrupt marked क्रम wakeup was enabled during suspend
		 * entry. Disable such पूर्णांकerrupts to restore them back to
		 * original state.
		 */
		__disable_irq(desc);
		irqd_clear(irqd, IRQD_IRQ_ENABLED_ON_SUSPEND);
	पूर्ण

	अगर (desc->istate & IRQS_SUSPENDED)
		जाओ resume;

	/* Force resume the पूर्णांकerrupt? */
	अगर (!desc->क्रमce_resume_depth)
		वापस;

	/* Pretend that it got disabled ! */
	desc->depth++;
	irq_state_set_disabled(desc);
	irq_state_set_masked(desc);
resume:
	desc->istate &= ~IRQS_SUSPENDED;
	__enable_irq(desc);
पूर्ण

अटल व्योम resume_irqs(bool want_early)
अणु
	काष्ठा irq_desc *desc;
	पूर्णांक irq;

	क्रम_each_irq_desc(irq, desc) अणु
		अचिन्हित दीर्घ flags;
		bool is_early = desc->action &&
			desc->action->flags & IRQF_EARLY_RESUME;

		अगर (!is_early && want_early)
			जारी;
		अगर (irq_settings_is_nested_thपढ़ो(desc))
			जारी;

		raw_spin_lock_irqsave(&desc->lock, flags);
		resume_irq(desc);
		raw_spin_unlock_irqrestore(&desc->lock, flags);
	पूर्ण
पूर्ण

/**
 * rearm_wake_irq - rearm a wakeup पूर्णांकerrupt line after संकेतing wakeup
 * @irq: Interrupt to rearm
 */
व्योम rearm_wake_irq(अचिन्हित पूर्णांक irq)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा irq_desc *desc = irq_get_desc_buslock(irq, &flags, IRQ_GET_DESC_CHECK_GLOBAL);

	अगर (!desc)
		वापस;

	अगर (!(desc->istate & IRQS_SUSPENDED) ||
	    !irqd_is_wakeup_set(&desc->irq_data))
		जाओ unlock;

	desc->istate &= ~IRQS_SUSPENDED;
	irqd_set(&desc->irq_data, IRQD_WAKEUP_ARMED);
	__enable_irq(desc);

unlock:
	irq_put_desc_busunlock(desc, flags);
पूर्ण

/**
 * irq_pm_syscore_ops - enable पूर्णांकerrupt lines early
 *
 * Enable all पूर्णांकerrupt lines with %IRQF_EARLY_RESUME set.
 */
अटल व्योम irq_pm_syscore_resume(व्योम)
अणु
	resume_irqs(true);
पूर्ण

अटल काष्ठा syscore_ops irq_pm_syscore_ops = अणु
	.resume		= irq_pm_syscore_resume,
पूर्ण;

अटल पूर्णांक __init irq_pm_init_ops(व्योम)
अणु
	रेजिस्टर_syscore_ops(&irq_pm_syscore_ops);
	वापस 0;
पूर्ण

device_initcall(irq_pm_init_ops);

/**
 * resume_device_irqs - enable पूर्णांकerrupt lines disabled by suspend_device_irqs()
 *
 * Enable all non-%IRQF_EARLY_RESUME पूर्णांकerrupt lines previously
 * disabled by suspend_device_irqs() that have the IRQS_SUSPENDED flag
 * set as well as those with %IRQF_FORCE_RESUME.
 */
व्योम resume_device_irqs(व्योम)
अणु
	resume_irqs(false);
पूर्ण
EXPORT_SYMBOL_GPL(resume_device_irqs);
