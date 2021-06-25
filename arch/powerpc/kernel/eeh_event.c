<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (c) 2005 Linas Vepstas <linas@linas.org>
 */

#समावेश <linux/delay.h>
#समावेश <linux/list.h>
#समावेश <linux/sched.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <यंत्र/eeh_event.h>
#समावेश <यंत्र/ppc-pci.h>

/** Overview:
 *  EEH error states may be detected within exception handlers;
 *  however, the recovery processing needs to occur asynchronously
 *  in a normal kernel context and not an पूर्णांकerrupt context.
 *  This pair of routines creates an event and queues it onto a
 *  work-queue, where a worker thपढ़ो can drive recovery.
 */

अटल DEFINE_SPINLOCK(eeh_eventlist_lock);
अटल DECLARE_COMPLETION(eeh_eventlist_event);
अटल LIST_HEAD(eeh_eventlist);

/**
 * eeh_event_handler - Dispatch EEH events.
 * @dummy - unused
 *
 * The detection of a frozen slot can occur inside an पूर्णांकerrupt,
 * where it can be hard to करो anything about it.  The goal of this
 * routine is to pull these detection events out of the context
 * of the पूर्णांकerrupt handler, and re-dispatch them क्रम processing
 * at a later समय in a normal context.
 */
अटल पूर्णांक eeh_event_handler(व्योम * dummy)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा eeh_event *event;

	जबतक (!kthपढ़ो_should_stop()) अणु
		अगर (रुको_क्रम_completion_पूर्णांकerruptible(&eeh_eventlist_event))
			अवरोध;

		/* Fetch EEH event from the queue */
		spin_lock_irqsave(&eeh_eventlist_lock, flags);
		event = शून्य;
		अगर (!list_empty(&eeh_eventlist)) अणु
			event = list_entry(eeh_eventlist.next,
					   काष्ठा eeh_event, list);
			list_del(&event->list);
		पूर्ण
		spin_unlock_irqrestore(&eeh_eventlist_lock, flags);
		अगर (!event)
			जारी;

		/* We might have event without binding PE */
		अगर (event->pe)
			eeh_handle_normal_event(event->pe);
		अन्यथा
			eeh_handle_special_event();

		kमुक्त(event);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * eeh_event_init - Start kernel thपढ़ो to handle EEH events
 *
 * This routine is called to start the kernel thपढ़ो क्रम processing
 * EEH event.
 */
पूर्णांक eeh_event_init(व्योम)
अणु
	काष्ठा task_काष्ठा *t;
	पूर्णांक ret = 0;

	t = kthपढ़ो_run(eeh_event_handler, शून्य, "eehd");
	अगर (IS_ERR(t)) अणु
		ret = PTR_ERR(t);
		pr_err("%s: Failed to start EEH daemon (%d)\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * eeh_send_failure_event - Generate a PCI error event
 * @pe: EEH PE
 *
 * This routine can be called within an पूर्णांकerrupt context;
 * the actual event will be delivered in a normal context
 * (from a workqueue).
 */
पूर्णांक __eeh_send_failure_event(काष्ठा eeh_pe *pe)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा eeh_event *event;

	event = kzalloc(माप(*event), GFP_ATOMIC);
	अगर (!event) अणु
		pr_err("EEH: out of memory, event not handled\n");
		वापस -ENOMEM;
	पूर्ण
	event->pe = pe;

	/*
	 * Mark the PE as recovering beक्रमe inserting it in the queue.
	 * This prevents the PE from being मुक्त()ed by a hotplug driver
	 * जबतक the PE is sitting in the event queue.
	 */
	अगर (pe) अणु
#अगर_घोषित CONFIG_STACKTRACE
		/*
		 * Save the current stack trace so we can dump it from the
		 * event handler thपढ़ो.
		 */
		pe->trace_entries = stack_trace_save(pe->stack_trace,
					 ARRAY_SIZE(pe->stack_trace), 0);
#पूर्ण_अगर /* CONFIG_STACKTRACE */

		eeh_pe_state_mark(pe, EEH_PE_RECOVERING);
	पूर्ण

	/* We may or may not be called in an पूर्णांकerrupt context */
	spin_lock_irqsave(&eeh_eventlist_lock, flags);
	list_add(&event->list, &eeh_eventlist);
	spin_unlock_irqrestore(&eeh_eventlist_lock, flags);

	/* For EEH deamon to knick in */
	complete(&eeh_eventlist_event);

	वापस 0;
पूर्ण

पूर्णांक eeh_send_failure_event(काष्ठा eeh_pe *pe)
अणु
	/*
	 * If we've manually supressed recovery events via debugfs
	 * then just drop it on the न्यूनमान.
	 */
	अगर (eeh_debugfs_no_recover) अणु
		pr_err("EEH: Event dropped due to no_recover setting\n");
		वापस 0;
	पूर्ण

	वापस __eeh_send_failure_event(pe);
पूर्ण

/**
 * eeh_हटाओ_event - Remove EEH event from the queue
 * @pe: Event binding to the PE
 * @क्रमce: Event will be हटाओd unconditionally
 *
 * On PowerNV platक्रमm, we might have subsequent coming events
 * is part of the क्रमmer one. For that हाल, those subsequent
 * coming events are totally duplicated and unnecessary, thus
 * they should be हटाओd.
 */
व्योम eeh_हटाओ_event(काष्ठा eeh_pe *pe, bool क्रमce)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा eeh_event *event, *पंचांगp;

	/*
	 * If we have शून्य PE passed in, we have dead IOC
	 * or we're sure we can report all existing errors
	 * by the caller.
	 *
	 * With "force", the event with associated PE that
	 * have been isolated, the event won't be हटाओd
	 * to aव्योम event lost.
	 */
	spin_lock_irqsave(&eeh_eventlist_lock, flags);
	list_क्रम_each_entry_safe(event, पंचांगp, &eeh_eventlist, list) अणु
		अगर (!क्रमce && event->pe &&
		    (event->pe->state & EEH_PE_ISOLATED))
			जारी;

		अगर (!pe) अणु
			list_del(&event->list);
			kमुक्त(event);
		पूर्ण अन्यथा अगर (pe->type & EEH_PE_PHB) अणु
			अगर (event->pe && event->pe->phb == pe->phb) अणु
				list_del(&event->list);
				kमुक्त(event);
			पूर्ण
		पूर्ण अन्यथा अगर (event->pe == pe) अणु
			list_del(&event->list);
			kमुक्त(event);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&eeh_eventlist_lock, flags);
पूर्ण
