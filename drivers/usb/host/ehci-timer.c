<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2012 by Alan Stern
 */

/* This file is part of ehci-hcd.c */

/*-------------------------------------------------------------------------*/

/* Set a bit in the USBCMD रेजिस्टर */
अटल व्योम ehci_set_command_bit(काष्ठा ehci_hcd *ehci, u32 bit)
अणु
	ehci->command |= bit;
	ehci_ग_लिखोl(ehci, ehci->command, &ehci->regs->command);

	/* unblock posted ग_लिखो */
	ehci_पढ़ोl(ehci, &ehci->regs->command);
पूर्ण

/* Clear a bit in the USBCMD रेजिस्टर */
अटल व्योम ehci_clear_command_bit(काष्ठा ehci_hcd *ehci, u32 bit)
अणु
	ehci->command &= ~bit;
	ehci_ग_लिखोl(ehci, ehci->command, &ehci->regs->command);

	/* unblock posted ग_लिखो */
	ehci_पढ़ोl(ehci, &ehci->regs->command);
पूर्ण

/*-------------------------------------------------------------------------*/

/*
 * EHCI समयr support...  Now using hrसमयrs.
 *
 * Lots of dअगरferent events are triggered from ehci->hrसमयr.  Whenever
 * the समयr routine runs, it checks each possible event; events that are
 * currently enabled and whose expiration समय has passed get handled.
 * The set of enabled events is stored as a collection of bitflags in
 * ehci->enabled_hrसमयr_events, and they are numbered in order of
 * increasing delay values (ranging between 1 ms and 100 ms).
 *
 * Rather than implementing a sorted list or tree of all pending events,
 * we keep track only of the lowest-numbered pending event, in
 * ehci->next_hrसमयr_event.  Whenever ehci->hrसमयr माला_लो restarted, its
 * expiration समय is set to the समयout value क्रम this event.
 *
 * As a result, events might not get handled right away; the actual delay
 * could be anywhere up to twice the requested delay.  This करोesn't
 * matter, because none of the events are especially समय-critical.  The
 * ones that matter most all have a delay of 1 ms, so they will be
 * handled after 2 ms at most, which is okay.  In addition to this, we
 * allow क्रम an expiration range of 1 ms.
 */

/*
 * Delay lengths क्रम the hrसमयr event types.
 * Keep this list sorted by delay length, in the same order as
 * the event types indexed by क्रमागत ehci_hrसमयr_event in ehci.h.
 */
अटल अचिन्हित event_delays_ns[] = अणु
	1 * NSEC_PER_MSEC,	/* EHCI_HRTIMER_POLL_ASS */
	1 * NSEC_PER_MSEC,	/* EHCI_HRTIMER_POLL_PSS */
	1 * NSEC_PER_MSEC,	/* EHCI_HRTIMER_POLL_DEAD */
	1125 * NSEC_PER_USEC,	/* EHCI_HRTIMER_UNLINK_INTR */
	2 * NSEC_PER_MSEC,	/* EHCI_HRTIMER_FREE_ITDS */
	2 * NSEC_PER_MSEC,	/* EHCI_HRTIMER_ACTIVE_UNLINK */
	5 * NSEC_PER_MSEC,	/* EHCI_HRTIMER_START_UNLINK_INTR */
	6 * NSEC_PER_MSEC,	/* EHCI_HRTIMER_ASYNC_UNLINKS */
	10 * NSEC_PER_MSEC,	/* EHCI_HRTIMER_IAA_WATCHDOG */
	10 * NSEC_PER_MSEC,	/* EHCI_HRTIMER_DISABLE_PERIODIC */
	15 * NSEC_PER_MSEC,	/* EHCI_HRTIMER_DISABLE_ASYNC */
	100 * NSEC_PER_MSEC,	/* EHCI_HRTIMER_IO_WATCHDOG */
पूर्ण;

/* Enable a pending hrसमयr event */
अटल व्योम ehci_enable_event(काष्ठा ehci_hcd *ehci, अचिन्हित event,
		bool resched)
अणु
	kसमय_प्रकार		*समयout = &ehci->hr_समयouts[event];

	अगर (resched)
		*समयout = kसमय_add(kसमय_get(), event_delays_ns[event]);
	ehci->enabled_hrसमयr_events |= (1 << event);

	/* Track only the lowest-numbered pending event */
	अगर (event < ehci->next_hrसमयr_event) अणु
		ehci->next_hrसमयr_event = event;
		hrसमयr_start_range_ns(&ehci->hrसमयr, *समयout,
				NSEC_PER_MSEC, HRTIMER_MODE_ABS);
	पूर्ण
पूर्ण


/* Poll the STS_ASS status bit; see when it agrees with CMD_ASE */
अटल व्योम ehci_poll_ASS(काष्ठा ehci_hcd *ehci)
अणु
	अचिन्हित	actual, want;

	/* Don't enable anything if the controller isn't running (e.g., died) */
	अगर (ehci->rh_state != EHCI_RH_RUNNING)
		वापस;

	want = (ehci->command & CMD_ASE) ? STS_ASS : 0;
	actual = ehci_पढ़ोl(ehci, &ehci->regs->status) & STS_ASS;

	अगर (want != actual) अणु

		/* Poll again later, but give up after about 2-4 ms */
		अगर (ehci->ASS_poll_count++ < 2) अणु
			ehci_enable_event(ehci, EHCI_HRTIMER_POLL_ASS, true);
			वापस;
		पूर्ण
		ehci_dbg(ehci, "Waited too long for the async schedule status (%x/%x), giving up\n",
				want, actual);
	पूर्ण
	ehci->ASS_poll_count = 0;

	/* The status is up-to-date; restart or stop the schedule as needed */
	अगर (want == 0) अणु	/* Stopped */
		अगर (ehci->async_count > 0)
			ehci_set_command_bit(ehci, CMD_ASE);

	पूर्ण अन्यथा अणु		/* Running */
		अगर (ehci->async_count == 0) अणु

			/* Turn off the schedule after a जबतक */
			ehci_enable_event(ehci, EHCI_HRTIMER_DISABLE_ASYNC,
					true);
		पूर्ण
	पूर्ण
पूर्ण

/* Turn off the async schedule after a brief delay */
अटल व्योम ehci_disable_ASE(काष्ठा ehci_hcd *ehci)
अणु
	ehci_clear_command_bit(ehci, CMD_ASE);
पूर्ण


/* Poll the STS_PSS status bit; see when it agrees with CMD_PSE */
अटल व्योम ehci_poll_PSS(काष्ठा ehci_hcd *ehci)
अणु
	अचिन्हित	actual, want;

	/* Don't do anything if the controller isn't running (e.g., died) */
	अगर (ehci->rh_state != EHCI_RH_RUNNING)
		वापस;

	want = (ehci->command & CMD_PSE) ? STS_PSS : 0;
	actual = ehci_पढ़ोl(ehci, &ehci->regs->status) & STS_PSS;

	अगर (want != actual) अणु

		/* Poll again later, but give up after about 2-4 ms */
		अगर (ehci->PSS_poll_count++ < 2) अणु
			ehci_enable_event(ehci, EHCI_HRTIMER_POLL_PSS, true);
			वापस;
		पूर्ण
		ehci_dbg(ehci, "Waited too long for the periodic schedule status (%x/%x), giving up\n",
				want, actual);
	पूर्ण
	ehci->PSS_poll_count = 0;

	/* The status is up-to-date; restart or stop the schedule as needed */
	अगर (want == 0) अणु	/* Stopped */
		अगर (ehci->periodic_count > 0)
			ehci_set_command_bit(ehci, CMD_PSE);

	पूर्ण अन्यथा अणु		/* Running */
		अगर (ehci->periodic_count == 0) अणु

			/* Turn off the schedule after a जबतक */
			ehci_enable_event(ehci, EHCI_HRTIMER_DISABLE_PERIODIC,
					true);
		पूर्ण
	पूर्ण
पूर्ण

/* Turn off the periodic schedule after a brief delay */
अटल व्योम ehci_disable_PSE(काष्ठा ehci_hcd *ehci)
अणु
	ehci_clear_command_bit(ehci, CMD_PSE);
पूर्ण


/* Poll the STS_HALT status bit; see when a dead controller stops */
अटल व्योम ehci_handle_controller_death(काष्ठा ehci_hcd *ehci)
अणु
	अगर (!(ehci_पढ़ोl(ehci, &ehci->regs->status) & STS_HALT)) अणु

		/* Give up after a few milliseconds */
		अगर (ehci->died_poll_count++ < 5) अणु
			/* Try again later */
			ehci_enable_event(ehci, EHCI_HRTIMER_POLL_DEAD, true);
			वापस;
		पूर्ण
		ehci_warn(ehci, "Waited too long for the controller to stop, giving up\n");
	पूर्ण

	/* Clean up the mess */
	ehci->rh_state = EHCI_RH_HALTED;
	ehci_ग_लिखोl(ehci, 0, &ehci->regs->configured_flag);
	ehci_ग_लिखोl(ehci, 0, &ehci->regs->पूर्णांकr_enable);
	ehci_work(ehci);
	end_unlink_async(ehci);

	/* Not in process context, so करोn't try to reset the controller */
पूर्ण

/* start to unlink पूर्णांकerrupt QHs  */
अटल व्योम ehci_handle_start_पूर्णांकr_unlinks(काष्ठा ehci_hcd *ehci)
अणु
	bool		stopped = (ehci->rh_state < EHCI_RH_RUNNING);

	/*
	 * Process all the QHs on the पूर्णांकr_unlink list that were added
	 * beक्रमe the current unlink cycle began.  The list is in
	 * temporal order, so stop when we reach the first entry in the
	 * current cycle.  But अगर the root hub isn't running then
	 * process all the QHs on the list.
	 */
	जबतक (!list_empty(&ehci->पूर्णांकr_unlink_रुको)) अणु
		काष्ठा ehci_qh	*qh;

		qh = list_first_entry(&ehci->पूर्णांकr_unlink_रुको,
				काष्ठा ehci_qh, unlink_node);
		अगर (!stopped && (qh->unlink_cycle ==
				ehci->पूर्णांकr_unlink_रुको_cycle))
			अवरोध;
		list_del_init(&qh->unlink_node);
		qh->unlink_reason |= QH_UNLINK_QUEUE_EMPTY;
		start_unlink_पूर्णांकr(ehci, qh);
	पूर्ण

	/* Handle reमुख्यing entries later */
	अगर (!list_empty(&ehci->पूर्णांकr_unlink_रुको)) अणु
		ehci_enable_event(ehci, EHCI_HRTIMER_START_UNLINK_INTR, true);
		++ehci->पूर्णांकr_unlink_रुको_cycle;
	पूर्ण
पूर्ण

/* Handle unlinked पूर्णांकerrupt QHs once they are gone from the hardware */
अटल व्योम ehci_handle_पूर्णांकr_unlinks(काष्ठा ehci_hcd *ehci)
अणु
	bool		stopped = (ehci->rh_state < EHCI_RH_RUNNING);

	/*
	 * Process all the QHs on the पूर्णांकr_unlink list that were added
	 * beक्रमe the current unlink cycle began.  The list is in
	 * temporal order, so stop when we reach the first entry in the
	 * current cycle.  But अगर the root hub isn't running then
	 * process all the QHs on the list.
	 */
	ehci->पूर्णांकr_unlinking = true;
	जबतक (!list_empty(&ehci->पूर्णांकr_unlink)) अणु
		काष्ठा ehci_qh	*qh;

		qh = list_first_entry(&ehci->पूर्णांकr_unlink, काष्ठा ehci_qh,
				unlink_node);
		अगर (!stopped && qh->unlink_cycle == ehci->पूर्णांकr_unlink_cycle)
			अवरोध;
		list_del_init(&qh->unlink_node);
		end_unlink_पूर्णांकr(ehci, qh);
	पूर्ण

	/* Handle reमुख्यing entries later */
	अगर (!list_empty(&ehci->पूर्णांकr_unlink)) अणु
		ehci_enable_event(ehci, EHCI_HRTIMER_UNLINK_INTR, true);
		++ehci->पूर्णांकr_unlink_cycle;
	पूर्ण
	ehci->पूर्णांकr_unlinking = false;
पूर्ण


/* Start another मुक्त-iTDs/siTDs cycle */
अटल व्योम start_मुक्त_itds(काष्ठा ehci_hcd *ehci)
अणु
	अगर (!(ehci->enabled_hrसमयr_events & BIT(EHCI_HRTIMER_FREE_ITDS))) अणु
		ehci->last_itd_to_मुक्त = list_entry(
				ehci->cached_itd_list.prev,
				काष्ठा ehci_itd, itd_list);
		ehci->last_sitd_to_मुक्त = list_entry(
				ehci->cached_sitd_list.prev,
				काष्ठा ehci_sitd, sitd_list);
		ehci_enable_event(ehci, EHCI_HRTIMER_FREE_ITDS, true);
	पूर्ण
पूर्ण

/* Wait क्रम controller to stop using old iTDs and siTDs */
अटल व्योम end_मुक्त_itds(काष्ठा ehci_hcd *ehci)
अणु
	काष्ठा ehci_itd		*itd, *n;
	काष्ठा ehci_sitd	*sitd, *sn;

	अगर (ehci->rh_state < EHCI_RH_RUNNING) अणु
		ehci->last_itd_to_मुक्त = शून्य;
		ehci->last_sitd_to_मुक्त = शून्य;
	पूर्ण

	list_क्रम_each_entry_safe(itd, n, &ehci->cached_itd_list, itd_list) अणु
		list_del(&itd->itd_list);
		dma_pool_मुक्त(ehci->itd_pool, itd, itd->itd_dma);
		अगर (itd == ehci->last_itd_to_मुक्त)
			अवरोध;
	पूर्ण
	list_क्रम_each_entry_safe(sitd, sn, &ehci->cached_sitd_list, sitd_list) अणु
		list_del(&sitd->sitd_list);
		dma_pool_मुक्त(ehci->sitd_pool, sitd, sitd->sitd_dma);
		अगर (sitd == ehci->last_sitd_to_मुक्त)
			अवरोध;
	पूर्ण

	अगर (!list_empty(&ehci->cached_itd_list) ||
			!list_empty(&ehci->cached_sitd_list))
		start_मुक्त_itds(ehci);
पूर्ण


/* Handle lost (or very late) IAA पूर्णांकerrupts */
अटल व्योम ehci_iaa_watchकरोg(काष्ठा ehci_hcd *ehci)
अणु
	u32 cmd, status;

	/*
	 * Lost IAA irqs wedge things badly; seen first with a vt8235.
	 * So we need this watchकरोg, but must protect it against both
	 * (a) SMP races against real IAA firing and retriggering, and
	 * (b) clean HC shutकरोwn, when IAA watchकरोg was pending.
	 */
	अगर (!ehci->iaa_in_progress || ehci->rh_state != EHCI_RH_RUNNING)
		वापस;

	/* If we get here, IAA is *REALLY* late.  It's barely
	 * conceivable that the प्रणाली is so busy that CMD_IAAD
	 * is still legitimately set, so let's be sure it's
	 * clear beक्रमe we पढ़ो STS_IAA.  (The HC should clear
	 * CMD_IAAD when it sets STS_IAA.)
	 */
	cmd = ehci_पढ़ोl(ehci, &ehci->regs->command);

	/*
	 * If IAA is set here it either legitimately triggered
	 * after the watchकरोg समयr expired (_way_ late, so we'll
	 * still count it as lost) ... or a silicon erratum:
	 * - VIA seems to set IAA without triggering the IRQ;
	 * - IAAD potentially cleared without setting IAA.
	 */
	status = ehci_पढ़ोl(ehci, &ehci->regs->status);
	अगर ((status & STS_IAA) || !(cmd & CMD_IAAD)) अणु
		INCR(ehci->stats.lost_iaa);
		ehci_ग_लिखोl(ehci, STS_IAA, &ehci->regs->status);
	पूर्ण

	ehci_dbg(ehci, "IAA watchdog: status %x cmd %x\n", status, cmd);
	end_iaa_cycle(ehci);
पूर्ण


/* Enable the I/O watchकरोg, अगर appropriate */
अटल व्योम turn_on_io_watchकरोg(काष्ठा ehci_hcd *ehci)
अणु
	/* Not needed अगर the controller isn't running or it's alपढ़ोy enabled */
	अगर (ehci->rh_state != EHCI_RH_RUNNING ||
			(ehci->enabled_hrसमयr_events &
				BIT(EHCI_HRTIMER_IO_WATCHDOG)))
		वापस;

	/*
	 * Isochronous transfers always need the watchकरोg.
	 * For other sorts we use it only अगर the flag is set.
	 */
	अगर (ehci->isoc_count > 0 || (ehci->need_io_watchकरोg &&
			ehci->async_count + ehci->पूर्णांकr_count > 0))
		ehci_enable_event(ehci, EHCI_HRTIMER_IO_WATCHDOG, true);
पूर्ण


/*
 * Handler functions क्रम the hrसमयr event types.
 * Keep this array in the same order as the event types indexed by
 * क्रमागत ehci_hrसमयr_event in ehci.h.
 */
अटल व्योम (*event_handlers[])(काष्ठा ehci_hcd *) = अणु
	ehci_poll_ASS,			/* EHCI_HRTIMER_POLL_ASS */
	ehci_poll_PSS,			/* EHCI_HRTIMER_POLL_PSS */
	ehci_handle_controller_death,	/* EHCI_HRTIMER_POLL_DEAD */
	ehci_handle_पूर्णांकr_unlinks,	/* EHCI_HRTIMER_UNLINK_INTR */
	end_मुक्त_itds,			/* EHCI_HRTIMER_FREE_ITDS */
	end_unlink_async,		/* EHCI_HRTIMER_ACTIVE_UNLINK */
	ehci_handle_start_पूर्णांकr_unlinks,	/* EHCI_HRTIMER_START_UNLINK_INTR */
	unlink_empty_async,		/* EHCI_HRTIMER_ASYNC_UNLINKS */
	ehci_iaa_watchकरोg,		/* EHCI_HRTIMER_IAA_WATCHDOG */
	ehci_disable_PSE,		/* EHCI_HRTIMER_DISABLE_PERIODIC */
	ehci_disable_ASE,		/* EHCI_HRTIMER_DISABLE_ASYNC */
	ehci_work,			/* EHCI_HRTIMER_IO_WATCHDOG */
पूर्ण;

अटल क्रमागत hrसमयr_restart ehci_hrसमयr_func(काष्ठा hrसमयr *t)
अणु
	काष्ठा ehci_hcd	*ehci = container_of(t, काष्ठा ehci_hcd, hrसमयr);
	kसमय_प्रकार		now;
	अचिन्हित दीर्घ	events;
	अचिन्हित दीर्घ	flags;
	अचिन्हित	e;

	spin_lock_irqsave(&ehci->lock, flags);

	events = ehci->enabled_hrसमयr_events;
	ehci->enabled_hrसमयr_events = 0;
	ehci->next_hrसमयr_event = EHCI_HRTIMER_NO_EVENT;

	/*
	 * Check each pending event.  If its समय has expired, handle
	 * the event; otherwise re-enable it.
	 */
	now = kसमय_get();
	क्रम_each_set_bit(e, &events, EHCI_HRTIMER_NUM_EVENTS) अणु
		अगर (kसमय_compare(now, ehci->hr_समयouts[e]) >= 0)
			event_handlers[e](ehci);
		अन्यथा
			ehci_enable_event(ehci, e, false);
	पूर्ण

	spin_unlock_irqrestore(&ehci->lock, flags);
	वापस HRTIMER_NORESTART;
पूर्ण
