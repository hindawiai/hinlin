<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 1992, 1998-2004 Linus Torvalds, Ingo Molnar
 *
 * This file contains spurious पूर्णांकerrupt handling.
 */

#समावेश <linux/jअगरfies.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/समयr.h>

#समावेश "internals.h"

अटल पूर्णांक irqfixup __पढ़ो_mostly;

#घोषणा POLL_SPURIOUS_IRQ_INTERVAL (HZ/10)
अटल व्योम poll_spurious_irqs(काष्ठा समयr_list *unused);
अटल DEFINE_TIMER(poll_spurious_irq_समयr, poll_spurious_irqs);
अटल पूर्णांक irq_poll_cpu;
अटल atomic_t irq_poll_active;

/*
 * We रुको here क्रम a poller to finish.
 *
 * If the poll runs on this CPU, then we yell loudly and वापस
 * false. That will leave the पूर्णांकerrupt line disabled in the worst
 * हाल, but it should never happen.
 *
 * We रुको until the poller is करोne and then recheck disabled and
 * action (about to be disabled). Only अगर it's still active, we वापस
 * true and let the handler run.
 */
bool irq_रुको_क्रम_poll(काष्ठा irq_desc *desc)
	__must_hold(&desc->lock)
अणु
	अगर (WARN_ONCE(irq_poll_cpu == smp_processor_id(),
		      "irq poll in progress on cpu %d for irq %d\n",
		      smp_processor_id(), desc->irq_data.irq))
		वापस false;

#अगर_घोषित CONFIG_SMP
	करो अणु
		raw_spin_unlock(&desc->lock);
		जबतक (irqd_irq_inprogress(&desc->irq_data))
			cpu_relax();
		raw_spin_lock(&desc->lock);
	पूर्ण जबतक (irqd_irq_inprogress(&desc->irq_data));
	/* Might have been disabled in meanसमय */
	वापस !irqd_irq_disabled(&desc->irq_data) && desc->action;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण


/*
 * Recovery handler क्रम misrouted पूर्णांकerrupts.
 */
अटल पूर्णांक try_one_irq(काष्ठा irq_desc *desc, bool क्रमce)
अणु
	irqवापस_t ret = IRQ_NONE;
	काष्ठा irqaction *action;

	raw_spin_lock(&desc->lock);

	/*
	 * PER_CPU, nested thपढ़ो पूर्णांकerrupts and पूर्णांकerrupts explicitly
	 * marked polled are excluded from polling.
	 */
	अगर (irq_settings_is_per_cpu(desc) ||
	    irq_settings_is_nested_thपढ़ो(desc) ||
	    irq_settings_is_polled(desc))
		जाओ out;

	/*
	 * Do not poll disabled पूर्णांकerrupts unless the spurious
	 * disabled poller asks explicitly.
	 */
	अगर (irqd_irq_disabled(&desc->irq_data) && !क्रमce)
		जाओ out;

	/*
	 * All handlers must agree on IRQF_SHARED, so we test just the
	 * first.
	 */
	action = desc->action;
	अगर (!action || !(action->flags & IRQF_SHARED) ||
	    (action->flags & __IRQF_TIMER))
		जाओ out;

	/* Alपढ़ोy running on another processor */
	अगर (irqd_irq_inprogress(&desc->irq_data)) अणु
		/*
		 * Alपढ़ोy running: If it is shared get the other
		 * CPU to go looking क्रम our mystery पूर्णांकerrupt too
		 */
		desc->istate |= IRQS_PENDING;
		जाओ out;
	पूर्ण

	/* Mark it poll in progress */
	desc->istate |= IRQS_POLL_INPROGRESS;
	करो अणु
		अगर (handle_irq_event(desc) == IRQ_HANDLED)
			ret = IRQ_HANDLED;
		/* Make sure that there is still a valid action */
		action = desc->action;
	पूर्ण जबतक ((desc->istate & IRQS_PENDING) && action);
	desc->istate &= ~IRQS_POLL_INPROGRESS;
out:
	raw_spin_unlock(&desc->lock);
	वापस ret == IRQ_HANDLED;
पूर्ण

अटल पूर्णांक misrouted_irq(पूर्णांक irq)
अणु
	काष्ठा irq_desc *desc;
	पूर्णांक i, ok = 0;

	अगर (atomic_inc_वापस(&irq_poll_active) != 1)
		जाओ out;

	irq_poll_cpu = smp_processor_id();

	क्रम_each_irq_desc(i, desc) अणु
		अगर (!i)
			 जारी;

		अगर (i == irq)	/* Alपढ़ोy tried */
			जारी;

		अगर (try_one_irq(desc, false))
			ok = 1;
	पूर्ण
out:
	atomic_dec(&irq_poll_active);
	/* So the caller can adjust the irq error counts */
	वापस ok;
पूर्ण

अटल व्योम poll_spurious_irqs(काष्ठा समयr_list *unused)
अणु
	काष्ठा irq_desc *desc;
	पूर्णांक i;

	अगर (atomic_inc_वापस(&irq_poll_active) != 1)
		जाओ out;
	irq_poll_cpu = smp_processor_id();

	क्रम_each_irq_desc(i, desc) अणु
		अचिन्हित पूर्णांक state;

		अगर (!i)
			 जारी;

		/* Racy but it करोesn't matter */
		state = desc->istate;
		barrier();
		अगर (!(state & IRQS_SPURIOUS_DISABLED))
			जारी;

		local_irq_disable();
		try_one_irq(desc, true);
		local_irq_enable();
	पूर्ण
out:
	atomic_dec(&irq_poll_active);
	mod_समयr(&poll_spurious_irq_समयr,
		  jअगरfies + POLL_SPURIOUS_IRQ_INTERVAL);
पूर्ण

अटल अंतरभूत पूर्णांक bad_action_ret(irqवापस_t action_ret)
अणु
	अचिन्हित पूर्णांक r = action_ret;

	अगर (likely(r <= (IRQ_HANDLED | IRQ_WAKE_THREAD)))
		वापस 0;
	वापस 1;
पूर्ण

/*
 * If 99,900 of the previous 100,000 पूर्णांकerrupts have not been handled
 * then assume that the IRQ is stuck in some manner. Drop a diagnostic
 * and try to turn the IRQ off.
 *
 * (The other 100-of-100,000 पूर्णांकerrupts may have been a correctly
 *  functioning device sharing an IRQ with the failing one)
 */
अटल व्योम __report_bad_irq(काष्ठा irq_desc *desc, irqवापस_t action_ret)
अणु
	अचिन्हित पूर्णांक irq = irq_desc_get_irq(desc);
	काष्ठा irqaction *action;
	अचिन्हित दीर्घ flags;

	अगर (bad_action_ret(action_ret)) अणु
		prपूर्णांकk(KERN_ERR "irq event %d: bogus return value %x\n",
				irq, action_ret);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "irq %d: nobody cared (try booting with "
				"the \"irqpoll\" option)\n", irq);
	पूर्ण
	dump_stack();
	prपूर्णांकk(KERN_ERR "handlers:\n");

	/*
	 * We need to take desc->lock here. note_पूर्णांकerrupt() is called
	 * w/o desc->lock held, but IRQ_PROGRESS set. We might race
	 * with something अन्यथा removing an action. It's ok to take
	 * desc->lock here. See synchronize_irq().
	 */
	raw_spin_lock_irqsave(&desc->lock, flags);
	क्रम_each_action_of_desc(desc, action) अणु
		prपूर्णांकk(KERN_ERR "[<%p>] %ps", action->handler, action->handler);
		अगर (action->thपढ़ो_fn)
			prपूर्णांकk(KERN_CONT " threaded [<%p>] %ps",
					action->thपढ़ो_fn, action->thपढ़ो_fn);
		prपूर्णांकk(KERN_CONT "\n");
	पूर्ण
	raw_spin_unlock_irqrestore(&desc->lock, flags);
पूर्ण

अटल व्योम report_bad_irq(काष्ठा irq_desc *desc, irqवापस_t action_ret)
अणु
	अटल पूर्णांक count = 100;

	अगर (count > 0) अणु
		count--;
		__report_bad_irq(desc, action_ret);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक
try_misrouted_irq(अचिन्हित पूर्णांक irq, काष्ठा irq_desc *desc,
		  irqवापस_t action_ret)
अणु
	काष्ठा irqaction *action;

	अगर (!irqfixup)
		वापस 0;

	/* We didn't actually handle the IRQ - see अगर it was misrouted? */
	अगर (action_ret == IRQ_NONE)
		वापस 1;

	/*
	 * But क्रम 'irqfixup == 2' we also करो it क्रम handled पूर्णांकerrupts अगर
	 * they are marked as IRQF_IRQPOLL (or क्रम irq zero, which is the
	 * traditional PC समयr पूर्णांकerrupt.. Legacy)
	 */
	अगर (irqfixup < 2)
		वापस 0;

	अगर (!irq)
		वापस 1;

	/*
	 * Since we करोn't get the descriptor lock, "action" can
	 * change under us.  We करोn't really care, but we don't
	 * want to follow a शून्य poपूर्णांकer. So tell the compiler to
	 * just load it once by using a barrier.
	 */
	action = desc->action;
	barrier();
	वापस action && (action->flags & IRQF_IRQPOLL);
पूर्ण

#घोषणा SPURIOUS_DEFERRED	0x80000000

व्योम note_पूर्णांकerrupt(काष्ठा irq_desc *desc, irqवापस_t action_ret)
अणु
	अचिन्हित पूर्णांक irq;

	अगर (desc->istate & IRQS_POLL_INPROGRESS ||
	    irq_settings_is_polled(desc))
		वापस;

	अगर (bad_action_ret(action_ret)) अणु
		report_bad_irq(desc, action_ret);
		वापस;
	पूर्ण

	/*
	 * We cannot call note_पूर्णांकerrupt from the thपढ़ोed handler
	 * because we need to look at the compound of all handlers
	 * (primary and thपढ़ोed). Aside of that in the thपढ़ोed
	 * shared हाल we have no serialization against an incoming
	 * hardware पूर्णांकerrupt जबतक we are dealing with a thपढ़ोed
	 * result.
	 *
	 * So in हाल a thपढ़ो is woken, we just note the fact and
	 * defer the analysis to the next hardware पूर्णांकerrupt.
	 *
	 * The thपढ़ोed handlers store whether they successfully
	 * handled an पूर्णांकerrupt and we check whether that number
	 * changed versus the last invocation.
	 *
	 * We could handle all पूर्णांकerrupts with the delayed by one
	 * mechanism, but क्रम the non क्रमced thपढ़ोed हाल we'd just
	 * add poपूर्णांकless overhead to the straight hardirq पूर्णांकerrupts
	 * क्रम the sake of a few lines less code.
	 */
	अगर (action_ret & IRQ_WAKE_THREAD) अणु
		/*
		 * There is a thपढ़ो woken. Check whether one of the
		 * shared primary handlers वापसed IRQ_HANDLED. If
		 * not we defer the spurious detection to the next
		 * पूर्णांकerrupt.
		 */
		अगर (action_ret == IRQ_WAKE_THREAD) अणु
			पूर्णांक handled;
			/*
			 * We use bit 31 of thपढ़ो_handled_last to
			 * denote the deferred spurious detection
			 * active. No locking necessary as
			 * thपढ़ो_handled_last is only accessed here
			 * and we have the guarantee that hard
			 * पूर्णांकerrupts are not reentrant.
			 */
			अगर (!(desc->thपढ़ोs_handled_last & SPURIOUS_DEFERRED)) अणु
				desc->thपढ़ोs_handled_last |= SPURIOUS_DEFERRED;
				वापस;
			पूर्ण
			/*
			 * Check whether one of the thपढ़ोed handlers
			 * वापसed IRQ_HANDLED since the last
			 * पूर्णांकerrupt happened.
			 *
			 * For simplicity we just set bit 31, as it is
			 * set in thपढ़ोs_handled_last as well. So we
			 * aव्योम extra masking. And we really करो not
			 * care about the high bits of the handled
			 * count. We just care about the count being
			 * dअगरferent than the one we saw beक्रमe.
			 */
			handled = atomic_पढ़ो(&desc->thपढ़ोs_handled);
			handled |= SPURIOUS_DEFERRED;
			अगर (handled != desc->thपढ़ोs_handled_last) अणु
				action_ret = IRQ_HANDLED;
				/*
				 * Note: We keep the SPURIOUS_DEFERRED
				 * bit set. We are handling the
				 * previous invocation right now.
				 * Keep it क्रम the current one, so the
				 * next hardware पूर्णांकerrupt will
				 * account क्रम it.
				 */
				desc->thपढ़ोs_handled_last = handled;
			पूर्ण अन्यथा अणु
				/*
				 * None of the thपढ़ोed handlers felt
				 * responsible क्रम the last पूर्णांकerrupt
				 *
				 * We keep the SPURIOUS_DEFERRED bit
				 * set in thपढ़ोs_handled_last as we
				 * need to account क्रम the current
				 * पूर्णांकerrupt as well.
				 */
				action_ret = IRQ_NONE;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * One of the primary handlers वापसed
			 * IRQ_HANDLED. So we करोn't care about the
			 * thपढ़ोed handlers on the same line. Clear
			 * the deferred detection bit.
			 *
			 * In theory we could/should check whether the
			 * deferred bit is set and take the result of
			 * the previous run पूर्णांकo account here as
			 * well. But it's really not worth the
			 * trouble. If every other पूर्णांकerrupt is
			 * handled we never trigger the spurious
			 * detector. And अगर this is just the one out
			 * of 100k unhandled ones which is handled
			 * then we merily delay the spurious detection
			 * by one hard पूर्णांकerrupt. Not a real problem.
			 */
			desc->thपढ़ोs_handled_last &= ~SPURIOUS_DEFERRED;
		पूर्ण
	पूर्ण

	अगर (unlikely(action_ret == IRQ_NONE)) अणु
		/*
		 * If we are seeing only the odd spurious IRQ caused by
		 * bus asynchronicity then करोn't eventually trigger an error,
		 * otherwise the counter becomes a करोomsday समयr क्रम otherwise
		 * working प्रणालीs
		 */
		अगर (समय_after(jअगरfies, desc->last_unhandled + HZ/10))
			desc->irqs_unhandled = 1;
		अन्यथा
			desc->irqs_unhandled++;
		desc->last_unhandled = jअगरfies;
	पूर्ण

	irq = irq_desc_get_irq(desc);
	अगर (unlikely(try_misrouted_irq(irq, desc, action_ret))) अणु
		पूर्णांक ok = misrouted_irq(irq);
		अगर (action_ret == IRQ_NONE)
			desc->irqs_unhandled -= ok;
	पूर्ण

	अगर (likely(!desc->irqs_unhandled))
		वापस;

	/* Now getting पूर्णांकo unhandled irq detection */
	desc->irq_count++;
	अगर (likely(desc->irq_count < 100000))
		वापस;

	desc->irq_count = 0;
	अगर (unlikely(desc->irqs_unhandled > 99900)) अणु
		/*
		 * The पूर्णांकerrupt is stuck
		 */
		__report_bad_irq(desc, action_ret);
		/*
		 * Now समाप्त the IRQ
		 */
		prपूर्णांकk(KERN_EMERG "Disabling IRQ #%d\n", irq);
		desc->istate |= IRQS_SPURIOUS_DISABLED;
		desc->depth++;
		irq_disable(desc);

		mod_समयr(&poll_spurious_irq_समयr,
			  jअगरfies + POLL_SPURIOUS_IRQ_INTERVAL);
	पूर्ण
	desc->irqs_unhandled = 0;
पूर्ण

bool noirqdebug __पढ़ो_mostly;

पूर्णांक noirqdebug_setup(अक्षर *str)
अणु
	noirqdebug = 1;
	prपूर्णांकk(KERN_INFO "IRQ lockup detection disabled\n");

	वापस 1;
पूर्ण

__setup("noirqdebug", noirqdebug_setup);
module_param(noirqdebug, bool, 0644);
MODULE_PARM_DESC(noirqdebug, "Disable irq lockup detection when true");

अटल पूर्णांक __init irqfixup_setup(अक्षर *str)
अणु
	irqfixup = 1;
	prपूर्णांकk(KERN_WARNING "Misrouted IRQ fixup support enabled.\n");
	prपूर्णांकk(KERN_WARNING "This may impact system performance.\n");

	वापस 1;
पूर्ण

__setup("irqfixup", irqfixup_setup);
module_param(irqfixup, पूर्णांक, 0644);

अटल पूर्णांक __init irqpoll_setup(अक्षर *str)
अणु
	irqfixup = 2;
	prपूर्णांकk(KERN_WARNING "Misrouted IRQ fixup and polling support "
				"enabled\n");
	prपूर्णांकk(KERN_WARNING "This may significantly impact system "
				"performance\n");
	वापस 1;
पूर्ण

__setup("irqpoll", irqpoll_setup);
