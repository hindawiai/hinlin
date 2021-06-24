<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 1992, 1998-2006 Linus Torvalds, Ingo Molnar
 * Copyright (C) 2005-2006, Thomas Gleixner, Russell King
 *
 * This file contains the core पूर्णांकerrupt handling code. Detailed
 * inक्रमmation is available in Documentation/core-api/genericirq.rst
 *
 */

#समावेश <linux/irq.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel_स्थिति.स>

#समावेश <trace/events/irq.h>

#समावेश "internals.h"

#अगर_घोषित CONFIG_GENERIC_IRQ_MULTI_HANDLER
व्योम (*handle_arch_irq)(काष्ठा pt_regs *) __ro_after_init;
#पूर्ण_अगर

/**
 * handle_bad_irq - handle spurious and unhandled irqs
 * @desc:      description of the पूर्णांकerrupt
 *
 * Handles spurious and unhandled IRQ's. It also prपूर्णांकs a debugmessage.
 */
व्योम handle_bad_irq(काष्ठा irq_desc *desc)
अणु
	अचिन्हित पूर्णांक irq = irq_desc_get_irq(desc);

	prपूर्णांक_irq_desc(irq, desc);
	kstat_incr_irqs_this_cpu(desc);
	ack_bad_irq(irq);
पूर्ण
EXPORT_SYMBOL_GPL(handle_bad_irq);

/*
 * Special, empty irq handler:
 */
irqवापस_t no_action(पूर्णांक cpl, व्योम *dev_id)
अणु
	वापस IRQ_NONE;
पूर्ण
EXPORT_SYMBOL_GPL(no_action);

अटल व्योम warn_no_thपढ़ो(अचिन्हित पूर्णांक irq, काष्ठा irqaction *action)
अणु
	अगर (test_and_set_bit(IRQTF_WARNED, &action->thपढ़ो_flags))
		वापस;

	prपूर्णांकk(KERN_WARNING "IRQ %d device %s returned IRQ_WAKE_THREAD "
	       "but no thread function available.", irq, action->name);
पूर्ण

व्योम __irq_wake_thपढ़ो(काष्ठा irq_desc *desc, काष्ठा irqaction *action)
अणु
	/*
	 * In हाल the thपढ़ो crashed and was समाप्तed we just pretend that
	 * we handled the पूर्णांकerrupt. The hardirq handler has disabled the
	 * device पूर्णांकerrupt, so no irq storm is lurking.
	 */
	अगर (action->thपढ़ो->flags & PF_EXITING)
		वापस;

	/*
	 * Wake up the handler thपढ़ो क्रम this action. If the
	 * RUNTHREAD bit is alपढ़ोy set, nothing to करो.
	 */
	अगर (test_and_set_bit(IRQTF_RUNTHREAD, &action->thपढ़ो_flags))
		वापस;

	/*
	 * It's safe to OR the mask lockless here. We have only two
	 * places which ग_लिखो to thपढ़ोs_oneshot: This code and the
	 * irq thपढ़ो.
	 *
	 * This code is the hard irq context and can never run on two
	 * cpus in parallel. If it ever करोes we have more serious
	 * problems than this biपंचांगask.
	 *
	 * The irq thपढ़ोs of this irq which clear their "running" bit
	 * in thपढ़ोs_oneshot are serialized via desc->lock against
	 * each other and they are serialized against this code by
	 * IRQS_INPROGRESS.
	 *
	 * Hard irq handler:
	 *
	 *	spin_lock(desc->lock);
	 *	desc->state |= IRQS_INPROGRESS;
	 *	spin_unlock(desc->lock);
	 *	set_bit(IRQTF_RUNTHREAD, &action->thपढ़ो_flags);
	 *	desc->thपढ़ोs_oneshot |= mask;
	 *	spin_lock(desc->lock);
	 *	desc->state &= ~IRQS_INPROGRESS;
	 *	spin_unlock(desc->lock);
	 *
	 * irq thपढ़ो:
	 *
	 * again:
	 *	spin_lock(desc->lock);
	 *	अगर (desc->state & IRQS_INPROGRESS) अणु
	 *		spin_unlock(desc->lock);
	 *		जबतक(desc->state & IRQS_INPROGRESS)
	 *			cpu_relax();
	 *		जाओ again;
	 *	पूर्ण
	 *	अगर (!test_bit(IRQTF_RUNTHREAD, &action->thपढ़ो_flags))
	 *		desc->thपढ़ोs_oneshot &= ~mask;
	 *	spin_unlock(desc->lock);
	 *
	 * So either the thपढ़ो रुकोs क्रम us to clear IRQS_INPROGRESS
	 * or we are रुकोing in the flow handler क्रम desc->lock to be
	 * released beक्रमe we reach this poपूर्णांक. The thपढ़ो also checks
	 * IRQTF_RUNTHREAD under desc->lock. If set it leaves
	 * thपढ़ोs_oneshot untouched and runs the thपढ़ो another समय.
	 */
	desc->thपढ़ोs_oneshot |= action->thपढ़ो_mask;

	/*
	 * We increment the thपढ़ोs_active counter in हाल we wake up
	 * the irq thपढ़ो. The irq thपढ़ो decrements the counter when
	 * it वापसs from the handler or in the निकास path and wakes
	 * up रुकोers which are stuck in synchronize_irq() when the
	 * active count becomes zero. synchronize_irq() is serialized
	 * against this code (hard irq handler) via IRQS_INPROGRESS
	 * like the finalize_oneshot() code. See comment above.
	 */
	atomic_inc(&desc->thपढ़ोs_active);

	wake_up_process(action->thपढ़ो);
पूर्ण

irqवापस_t __handle_irq_event_percpu(काष्ठा irq_desc *desc, अचिन्हित पूर्णांक *flags)
अणु
	irqवापस_t retval = IRQ_NONE;
	अचिन्हित पूर्णांक irq = desc->irq_data.irq;
	काष्ठा irqaction *action;

	record_irq_समय(desc);

	क्रम_each_action_of_desc(desc, action) अणु
		irqवापस_t res;

		/*
		 * If this IRQ would be thपढ़ोed under क्रमce_irqthपढ़ोs, mark it so.
		 */
		अगर (irq_settings_can_thपढ़ो(desc) &&
		    !(action->flags & (IRQF_NO_THREAD | IRQF_PERCPU | IRQF_ONESHOT)))
			lockdep_hardirq_thपढ़ोed();

		trace_irq_handler_entry(irq, action);
		res = action->handler(irq, action->dev_id);
		trace_irq_handler_निकास(irq, action, res);

		अगर (WARN_ONCE(!irqs_disabled(),"irq %u handler %pS enabled interrupts\n",
			      irq, action->handler))
			local_irq_disable();

		चयन (res) अणु
		हाल IRQ_WAKE_THREAD:
			/*
			 * Catch drivers which वापस WAKE_THREAD but
			 * did not set up a thपढ़ो function
			 */
			अगर (unlikely(!action->thपढ़ो_fn)) अणु
				warn_no_thपढ़ो(irq, action);
				अवरोध;
			पूर्ण

			__irq_wake_thपढ़ो(desc, action);

			fallthrough;	/* to add to अक्रमomness */
		हाल IRQ_HANDLED:
			*flags |= action->flags;
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण

		retval |= res;
	पूर्ण

	वापस retval;
पूर्ण

irqवापस_t handle_irq_event_percpu(काष्ठा irq_desc *desc)
अणु
	irqवापस_t retval;
	अचिन्हित पूर्णांक flags = 0;

	retval = __handle_irq_event_percpu(desc, &flags);

	add_पूर्णांकerrupt_अक्रमomness(desc->irq_data.irq, flags);

	अगर (!noirqdebug)
		note_पूर्णांकerrupt(desc, retval);
	वापस retval;
पूर्ण

irqवापस_t handle_irq_event(काष्ठा irq_desc *desc)
अणु
	irqवापस_t ret;

	desc->istate &= ~IRQS_PENDING;
	irqd_set(&desc->irq_data, IRQD_IRQ_INPROGRESS);
	raw_spin_unlock(&desc->lock);

	ret = handle_irq_event_percpu(desc);

	raw_spin_lock(&desc->lock);
	irqd_clear(&desc->irq_data, IRQD_IRQ_INPROGRESS);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_GENERIC_IRQ_MULTI_HANDLER
पूर्णांक __init set_handle_irq(व्योम (*handle_irq)(काष्ठा pt_regs *))
अणु
	अगर (handle_arch_irq)
		वापस -EBUSY;

	handle_arch_irq = handle_irq;
	वापस 0;
पूर्ण
#पूर्ण_अगर
