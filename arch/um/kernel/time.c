<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015 Anton Ivanov (aivanov@अणुbrocade.com,kot-begemot.co.ukपूर्ण)
 * Copyright (C) 2015 Thomas Meyer (thomas@m3y3r.de)
 * Copyright (C) 2012-2014 Cisco Systems
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 * Copyright (C) 2019 Intel Corporation
 */

#समावेश <linux/घड़ीchips.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/param.h>
#समावेश <kern_util.h>
#समावेश <os.h>
#समावेश <linux/समय-पूर्णांकernal.h>
#समावेश <linux/um_समयtravel.h>
#समावेश <shared/init.h>

#अगर_घोषित CONFIG_UML_TIME_TRAVEL_SUPPORT
क्रमागत समय_प्रकारravel_mode समय_प्रकारravel_mode;
EXPORT_SYMBOL_GPL(समय_प्रकारravel_mode);

अटल bool समय_प्रकारravel_start_set;
अटल अचिन्हित दीर्घ दीर्घ समय_प्रकारravel_start;
अटल अचिन्हित दीर्घ दीर्घ समय_प्रकारravel_समय;
अटल LIST_HEAD(समय_प्रकारravel_events);
अटल LIST_HEAD(समय_प्रकारravel_irqs);
अटल अचिन्हित दीर्घ दीर्घ समय_प्रकारravel_समयr_पूर्णांकerval;
अटल अचिन्हित दीर्घ दीर्घ समय_प्रकारravel_next_event;
अटल काष्ठा समय_प्रकारravel_event समय_प्रकारravel_समयr_event;
अटल पूर्णांक समय_प्रकारravel_ext_fd = -1;
अटल अचिन्हित पूर्णांक समय_प्रकारravel_ext_रुकोing;
अटल bool समय_प्रकारravel_ext_prev_request_valid;
अटल अचिन्हित दीर्घ दीर्घ समय_प्रकारravel_ext_prev_request;
अटल bool समय_प्रकारravel_ext_मुक्त_until_valid;
अटल अचिन्हित दीर्घ दीर्घ समय_प्रकारravel_ext_मुक्त_until;

अटल व्योम समय_प्रकारravel_set_समय(अचिन्हित दीर्घ दीर्घ ns)
अणु
	अगर (unlikely(ns < समय_प्रकारravel_समय))
		panic("time-travel: time goes backwards %lld -> %lld\n",
		      समय_प्रकारravel_समय, ns);
	अन्यथा अगर (unlikely(ns >= S64_MAX))
		panic("The system was going to sleep forever, aborting");

	समय_प्रकारravel_समय = ns;
पूर्ण

क्रमागत समय_प्रकारravel_message_handling अणु
	TTMH_IDLE,
	TTMH_POLL,
	TTMH_READ,
पूर्ण;

अटल व्योम समय_प्रकारravel_handle_message(काष्ठा um_समयtravel_msg *msg,
				       क्रमागत समय_प्रकारravel_message_handling mode)
अणु
	काष्ठा um_समयtravel_msg resp = अणु
		.op = UM_TIMETRAVEL_ACK,
	पूर्ण;
	पूर्णांक ret;

	/*
	 * Poll outside the locked section (अगर we're not called to only पढ़ो
	 * the response) so we can get पूर्णांकerrupts क्रम e.g. virtio जबतक we're
	 * here, but then we need to lock to not get पूर्णांकerrupted between the
	 * पढ़ो of the message and ग_लिखो of the ACK.
	 */
	अगर (mode != TTMH_READ) अणु
		bool disabled = irqs_disabled();

		BUG_ON(mode == TTMH_IDLE && !disabled);

		अगर (disabled)
			local_irq_enable();
		जबतक (os_poll(1, &समय_प्रकारravel_ext_fd) != 0) अणु
			/* nothing */
		पूर्ण
		अगर (disabled)
			local_irq_disable();
	पूर्ण

	ret = os_पढ़ो_file(समय_प्रकारravel_ext_fd, msg, माप(*msg));

	अगर (ret == 0)
		panic("time-travel external link is broken\n");
	अगर (ret != माप(*msg))
		panic("invalid time-travel message - %d bytes\n", ret);

	चयन (msg->op) अणु
	शेष:
		WARN_ONCE(1, "time-travel: unexpected message %lld\n",
			  (अचिन्हित दीर्घ दीर्घ)msg->op);
		अवरोध;
	हाल UM_TIMETRAVEL_ACK:
		वापस;
	हाल UM_TIMETRAVEL_RUN:
		समय_प्रकारravel_set_समय(msg->समय);
		अवरोध;
	हाल UM_TIMETRAVEL_FREE_UNTIL:
		समय_प्रकारravel_ext_मुक्त_until_valid = true;
		समय_प्रकारravel_ext_मुक्त_until = msg->समय;
		अवरोध;
	पूर्ण

	resp.seq = msg->seq;
	os_ग_लिखो_file(समय_प्रकारravel_ext_fd, &resp, माप(resp));
पूर्ण

अटल u64 समय_प्रकारravel_ext_req(u32 op, u64 समय)
अणु
	अटल पूर्णांक seq;
	पूर्णांक mseq = ++seq;
	काष्ठा um_समयtravel_msg msg = अणु
		.op = op,
		.समय = समय,
		.seq = mseq,
	पूर्ण;
	अचिन्हित दीर्घ flags;

	/*
	 * We need to save पूर्णांकerrupts here and only restore when we
	 * got the ACK - otherwise we can get पूर्णांकerrupted and send
	 * another request जबतक we're still रुकोing क्रम an ACK, but
	 * the peer करोesn't know we got पूर्णांकerrupted and will send
	 * the ACKs in the same order as the message, but we'd need
	 * to see them in the opposite order ...
	 *
	 * This wouldn't matter *too* much, but some ACKs carry the
	 * current समय (क्रम UM_TIMETRAVEL_GET) and getting another
	 * ACK without a समय would confuse us a lot!
	 *
	 * The sequence number assignment that happens here lets us
	 * debug such message handling issues more easily.
	 */
	local_irq_save(flags);
	os_ग_लिखो_file(समय_प्रकारravel_ext_fd, &msg, माप(msg));

	जबतक (msg.op != UM_TIMETRAVEL_ACK)
		समय_प्रकारravel_handle_message(&msg, TTMH_READ);

	अगर (msg.seq != mseq)
		panic("time-travel: ACK message has different seqno! op=%d, seq=%d != %d time=%lld\n",
		      msg.op, msg.seq, mseq, msg.समय);

	अगर (op == UM_TIMETRAVEL_GET)
		समय_प्रकारravel_set_समय(msg.समय);
	local_irq_restore(flags);

	वापस msg.समय;
पूर्ण

व्योम __समय_प्रकारravel_रुको_पढ़ोable(पूर्णांक fd)
अणु
	पूर्णांक fds[2] = अणु fd, समय_प्रकारravel_ext_fd पूर्ण;
	पूर्णांक ret;

	अगर (समय_प्रकारravel_mode != TT_MODE_EXTERNAL)
		वापस;

	जबतक ((ret = os_poll(2, fds))) अणु
		काष्ठा um_समयtravel_msg msg;

		अगर (ret == 1)
			समय_प्रकारravel_handle_message(&msg, TTMH_READ);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(__समय_प्रकारravel_रुको_पढ़ोable);

अटल व्योम समय_प्रकारravel_ext_update_request(अचिन्हित दीर्घ दीर्घ समय)
अणु
	अगर (समय_प्रकारravel_mode != TT_MODE_EXTERNAL)
		वापस;

	/* asked क्रम exactly this समय previously */
	अगर (समय_प्रकारravel_ext_prev_request_valid &&
	    समय == समय_प्रकारravel_ext_prev_request)
		वापस;

	/*
	 * अगर we're running and are allowed to run past the request
	 * then we करोn't need to update it either
	 */
	अगर (!समय_प्रकारravel_ext_रुकोing && समय_प्रकारravel_ext_मुक्त_until_valid &&
	    समय < समय_प्रकारravel_ext_मुक्त_until)
		वापस;

	समय_प्रकारravel_ext_prev_request = समय;
	समय_प्रकारravel_ext_prev_request_valid = true;
	समय_प्रकारravel_ext_req(UM_TIMETRAVEL_REQUEST, समय);
पूर्ण

व्योम __समय_प्रकारravel_propagate_समय(व्योम)
अणु
	अटल अचिन्हित दीर्घ दीर्घ last_propagated;

	अगर (last_propagated == समय_प्रकारravel_समय)
		वापस;

	समय_प्रकारravel_ext_req(UM_TIMETRAVEL_UPDATE, समय_प्रकारravel_समय);
	last_propagated = समय_प्रकारravel_समय;
पूर्ण
EXPORT_SYMBOL_GPL(__समय_प्रकारravel_propagate_समय);

/* वापसs true अगर we must करो a रुको to the simसमय device */
अटल bool समय_प्रकारravel_ext_request(अचिन्हित दीर्घ दीर्घ समय)
अणु
	/*
	 * If we received an बाह्यal sync poपूर्णांक ("free until") then we
	 * करोn't have to request/रुको क्रम anything until then, unless
	 * we're alपढ़ोy रुकोing.
	 */
	अगर (!समय_प्रकारravel_ext_रुकोing && समय_प्रकारravel_ext_मुक्त_until_valid &&
	    समय < समय_प्रकारravel_ext_मुक्त_until)
		वापस false;

	समय_प्रकारravel_ext_update_request(समय);
	वापस true;
पूर्ण

अटल व्योम समय_प्रकारravel_ext_रुको(bool idle)
अणु
	काष्ठा um_समयtravel_msg msg = अणु
		.op = UM_TIMETRAVEL_ACK,
	पूर्ण;

	समय_प्रकारravel_ext_prev_request_valid = false;
	समय_प्रकारravel_ext_मुक्त_until_valid = false;
	समय_प्रकारravel_ext_रुकोing++;

	समय_प्रकारravel_ext_req(UM_TIMETRAVEL_WAIT, -1);

	/*
	 * Here we are deep in the idle loop, so we have to अवरोध out of the
	 * kernel असलtraction in a sense and implement this in terms of the
	 * UML प्रणाली रुकोing on the VQ पूर्णांकerrupt जबतक sleeping, when we get
	 * the संकेत it'll call समय_प्रकारravel_ext_vq_notअगरy_करोne() completing the
	 * call.
	 */
	जबतक (msg.op != UM_TIMETRAVEL_RUN)
		समय_प्रकारravel_handle_message(&msg, idle ? TTMH_IDLE : TTMH_POLL);

	समय_प्रकारravel_ext_रुकोing--;

	/* we might request more stuff जबतक polling - reset when we run */
	समय_प्रकारravel_ext_prev_request_valid = false;
पूर्ण

अटल व्योम समय_प्रकारravel_ext_get_समय(व्योम)
अणु
	समय_प्रकारravel_ext_req(UM_TIMETRAVEL_GET, -1);
पूर्ण

अटल व्योम __समय_प्रकारravel_update_समय(अचिन्हित दीर्घ दीर्घ ns, bool idle)
अणु
	अगर (समय_प्रकारravel_mode == TT_MODE_EXTERNAL && समय_प्रकारravel_ext_request(ns))
		समय_प्रकारravel_ext_रुको(idle);
	अन्यथा
		समय_प्रकारravel_set_समय(ns);
पूर्ण

अटल काष्ठा समय_प्रकारravel_event *समय_प्रकारravel_first_event(व्योम)
अणु
	वापस list_first_entry_or_null(&समय_प्रकारravel_events,
					काष्ठा समय_प्रकारravel_event,
					list);
पूर्ण

अटल व्योम __समय_प्रकारravel_add_event(काष्ठा समय_प्रकारravel_event *e,
				    अचिन्हित दीर्घ दीर्घ समय)
अणु
	काष्ठा समय_प्रकारravel_event *पंचांगp;
	bool inserted = false;
	अचिन्हित दीर्घ flags;

	अगर (e->pending)
		वापस;

	e->pending = true;
	e->समय = समय;

	local_irq_save(flags);
	list_क्रम_each_entry(पंचांगp, &समय_प्रकारravel_events, list) अणु
		/*
		 * Add the new entry beक्रमe one with higher समय,
		 * or अगर they're equal and both on stack, because
		 * in that हाल we need to unwind the stack in the
		 * right order, and the later event (समयr sleep
		 * or such) must be dequeued first.
		 */
		अगर ((पंचांगp->समय > e->समय) ||
		    (पंचांगp->समय == e->समय && पंचांगp->onstack && e->onstack)) अणु
			list_add_tail(&e->list, &पंचांगp->list);
			inserted = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!inserted)
		list_add_tail(&e->list, &समय_प्रकारravel_events);

	पंचांगp = समय_प्रकारravel_first_event();
	समय_प्रकारravel_ext_update_request(पंचांगp->समय);
	समय_प्रकारravel_next_event = पंचांगp->समय;
	local_irq_restore(flags);
पूर्ण

अटल व्योम समय_प्रकारravel_add_event(काष्ठा समय_प्रकारravel_event *e,
				  अचिन्हित दीर्घ दीर्घ समय)
अणु
	अगर (WARN_ON(!e->fn))
		वापस;

	__समय_प्रकारravel_add_event(e, समय);
पूर्ण

व्योम समय_प्रकारravel_add_event_rel(काष्ठा समय_प्रकारravel_event *e,
			       अचिन्हित दीर्घ दीर्घ delay_ns)
अणु
	समय_प्रकारravel_add_event(e, समय_प्रकारravel_समय + delay_ns);
पूर्ण

व्योम समय_प्रकारravel_periodic_समयr(काष्ठा समय_प्रकारravel_event *e)
अणु
	समय_प्रकारravel_add_event(&समय_प्रकारravel_समयr_event,
			      समय_प्रकारravel_समय + समय_प्रकारravel_समयr_पूर्णांकerval);
	deliver_alarm();
पूर्ण

व्योम deliver_समय_प्रकारravel_irqs(व्योम)
अणु
	काष्ठा समय_प्रकारravel_event *e;
	अचिन्हित दीर्घ flags;

	/*
	 * Don't करो anything क्रम most हालs. Note that because here we have
	 * to disable IRQs (and re-enable later) we'll actually recurse at
	 * the end of the function, so this is strictly necessary.
	 */
	अगर (likely(list_empty(&समय_प्रकारravel_irqs)))
		वापस;

	local_irq_save(flags);
	irq_enter();
	जबतक ((e = list_first_entry_or_null(&समय_प्रकारravel_irqs,
					     काष्ठा समय_प्रकारravel_event,
					     list))) अणु
		WARN(e->समय != समय_प्रकारravel_समय,
		     "time moved from %lld to %lld before IRQ delivery\n",
		     समय_प्रकारravel_समय, e->समय);
		list_del(&e->list);
		e->pending = false;
		e->fn(e);
	पूर्ण
	irq_निकास();
	local_irq_restore(flags);
पूर्ण

अटल व्योम समय_प्रकारravel_deliver_event(काष्ठा समय_प्रकारravel_event *e)
अणु
	अगर (e == &समय_प्रकारravel_समयr_event) अणु
		/*
		 * deliver_alarm() करोes the irq_enter/irq_निकास
		 * by itself, so must handle it specially here
		 */
		e->fn(e);
	पूर्ण अन्यथा अगर (irqs_disabled()) अणु
		list_add_tail(&e->list, &समय_प्रकारravel_irqs);
		/*
		 * set pending again, it was set to false when the
		 * event was deleted from the original list, but
		 * now it's still pending until we deliver the IRQ.
		 */
		e->pending = true;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ flags;

		local_irq_save(flags);
		irq_enter();
		e->fn(e);
		irq_निकास();
		local_irq_restore(flags);
	पूर्ण
पूर्ण

bool समय_प्रकारravel_del_event(काष्ठा समय_प्रकारravel_event *e)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!e->pending)
		वापस false;
	local_irq_save(flags);
	list_del(&e->list);
	e->pending = false;
	local_irq_restore(flags);
	वापस true;
पूर्ण

अटल व्योम समय_प्रकारravel_update_समय(अचिन्हित दीर्घ दीर्घ next, bool idle)
अणु
	काष्ठा समय_प्रकारravel_event ne = अणु
		.onstack = true,
	पूर्ण;
	काष्ठा समय_प्रकारravel_event *e;
	bool finished = idle;

	/* add it without a handler - we deal with that specअगरically below */
	__समय_प्रकारravel_add_event(&ne, next);

	करो अणु
		e = समय_प्रकारravel_first_event();

		BUG_ON(!e);
		__समय_प्रकारravel_update_समय(e->समय, idle);

		/* new events may have been inserted जबतक we were रुकोing */
		अगर (e == समय_प्रकारravel_first_event()) अणु
			BUG_ON(!समय_प्रकारravel_del_event(e));
			BUG_ON(समय_प्रकारravel_समय != e->समय);

			अगर (e == &ne) अणु
				finished = true;
			पूर्ण अन्यथा अणु
				अगर (e->onstack)
					panic("On-stack event dequeued outside of the stack! time=%lld, event time=%lld, event=%pS\n",
					      समय_प्रकारravel_समय, e->समय, e);
				समय_प्रकारravel_deliver_event(e);
			पूर्ण
		पूर्ण

		e = समय_प्रकारravel_first_event();
		अगर (e)
			समय_प्रकारravel_ext_update_request(e->समय);
	पूर्ण जबतक (ne.pending && !finished);

	समय_प्रकारravel_del_event(&ne);
पूर्ण

व्योम समय_प्रकारravel_ndelay(अचिन्हित दीर्घ nsec)
अणु
	समय_प्रकारravel_update_समय(समय_प्रकारravel_समय + nsec, false);
पूर्ण
EXPORT_SYMBOL(समय_प्रकारravel_ndelay);

व्योम समय_प्रकारravel_add_irq_event(काष्ठा समय_प्रकारravel_event *e)
अणु
	BUG_ON(समय_प्रकारravel_mode != TT_MODE_EXTERNAL);

	समय_प्रकारravel_ext_get_समय();
	/*
	 * We could model पूर्णांकerrupt latency here, क्रम now just
	 * करोn't have any latency at all and request the exact
	 * same समय (again) to run the पूर्णांकerrupt...
	 */
	समय_प्रकारravel_add_event(e, समय_प्रकारravel_समय);
पूर्ण
EXPORT_SYMBOL_GPL(समय_प्रकारravel_add_irq_event);

अटल व्योम समय_प्रकारravel_oneshot_समयr(काष्ठा समय_प्रकारravel_event *e)
अणु
	deliver_alarm();
पूर्ण

व्योम समय_प्रकारravel_sleep(व्योम)
अणु
	/*
	 * Wait "forever" (using S64_MAX because there are some potential
	 * wrapping issues, especially with the current TT_MODE_EXTERNAL
	 * controller application.
	 */
	अचिन्हित दीर्घ दीर्घ next = S64_MAX;

	अगर (समय_प्रकारravel_mode == TT_MODE_BASIC)
		os_समयr_disable();

	समय_प्रकारravel_update_समय(next, true);

	अगर (समय_प्रकारravel_mode == TT_MODE_BASIC &&
	    समय_प्रकारravel_समयr_event.pending) अणु
		अगर (समय_प्रकारravel_समयr_event.fn == समय_प्रकारravel_periodic_समयr) अणु
			/*
			 * This is somewhat wrong - we should get the first
			 * one sooner like the os_समयr_one_shot() below...
			 */
			os_समयr_set_पूर्णांकerval(समय_प्रकारravel_समयr_पूर्णांकerval);
		पूर्ण अन्यथा अणु
			os_समयr_one_shot(समय_प्रकारravel_समयr_event.समय - next);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम समय_प्रकारravel_handle_real_alarm(व्योम)
अणु
	समय_प्रकारravel_set_समय(समय_प्रकारravel_next_event);

	समय_प्रकारravel_del_event(&समय_प्रकारravel_समयr_event);

	अगर (समय_प्रकारravel_समयr_event.fn == समय_प्रकारravel_periodic_समयr)
		समय_प्रकारravel_add_event(&समय_प्रकारravel_समयr_event,
				      समय_प्रकारravel_समय +
				      समय_प्रकारravel_समयr_पूर्णांकerval);
पूर्ण

अटल व्योम समय_प्रकारravel_set_पूर्णांकerval(अचिन्हित दीर्घ दीर्घ पूर्णांकerval)
अणु
	समय_प्रकारravel_समयr_पूर्णांकerval = पूर्णांकerval;
पूर्ण

अटल पूर्णांक समय_प्रकारravel_connect_बाह्यal(स्थिर अक्षर *socket)
अणु
	स्थिर अक्षर *sep;
	अचिन्हित दीर्घ दीर्घ id = (अचिन्हित दीर्घ दीर्घ)-1;
	पूर्णांक rc;

	अगर ((sep = म_अक्षर(socket, ':'))) अणु
		अक्षर buf[25] = अणुपूर्ण;
		अगर (sep - socket > माप(buf) - 1)
			जाओ invalid_number;

		स_नकल(buf, socket, sep - socket);
		अगर (kम_से_अदीर्घl(buf, 0, &id)) अणु
invalid_number:
			panic("time-travel: invalid external ID in string '%s'\n",
			      socket);
			वापस -EINVAL;
		पूर्ण

		socket = sep + 1;
	पूर्ण

	rc = os_connect_socket(socket);
	अगर (rc < 0) अणु
		panic("time-travel: failed to connect to external socket %s\n",
		      socket);
		वापस rc;
	पूर्ण

	समय_प्रकारravel_ext_fd = rc;

	समय_प्रकारravel_ext_req(UM_TIMETRAVEL_START, id);

	वापस 1;
पूर्ण

अटल व्योम समय_प्रकारravel_set_start(व्योम)
अणु
	अगर (समय_प्रकारravel_start_set)
		वापस;

	चयन (समय_प्रकारravel_mode) अणु
	हाल TT_MODE_EXTERNAL:
		समय_प्रकारravel_start = समय_प्रकारravel_ext_req(UM_TIMETRAVEL_GET_TOD, -1);
		/* controller gave us the *current* समय, so adjust by that */
		समय_प्रकारravel_ext_get_समय();
		समय_प्रकारravel_start -= समय_प्रकारravel_समय;
		अवरोध;
	हाल TT_MODE_INFCPU:
	हाल TT_MODE_BASIC:
		अगर (!समय_प्रकारravel_start_set)
			समय_प्रकारravel_start = os_persistent_घड़ी_emulation();
		अवरोध;
	हाल TT_MODE_OFF:
		/* we just पढ़ो the host घड़ी with os_persistent_घड़ी_emulation() */
		अवरोध;
	पूर्ण

	समय_प्रकारravel_start_set = true;
पूर्ण
#अन्यथा /* CONFIG_UML_TIME_TRAVEL_SUPPORT */
#घोषणा समय_प्रकारravel_start_set 0
#घोषणा समय_प्रकारravel_start 0
#घोषणा समय_प्रकारravel_समय 0
#घोषणा समय_प्रकारravel_ext_रुकोing 0

अटल अंतरभूत व्योम समय_प्रकारravel_update_समय(अचिन्हित दीर्घ दीर्घ ns, bool retearly)
अणु
पूर्ण

अटल अंतरभूत व्योम समय_प्रकारravel_handle_real_alarm(व्योम)
अणु
पूर्ण

अटल व्योम समय_प्रकारravel_set_पूर्णांकerval(अचिन्हित दीर्घ दीर्घ पूर्णांकerval)
अणु
पूर्ण

अटल अंतरभूत व्योम समय_प्रकारravel_set_start(व्योम)
अणु
पूर्ण

/* fail link अगर this actually माला_लो used */
बाह्य u64 समय_प्रकारravel_ext_req(u32 op, u64 समय);

/* these are empty macros so the काष्ठा/fn need not exist */
#घोषणा समय_प्रकारravel_add_event(e, समय) करो अणु पूर्ण जबतक (0)
/* बाह्यally not usable - redefine here so we can */
#अघोषित समय_प्रकारravel_del_event
#घोषणा समय_प्रकारravel_del_event(e) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

व्योम समयr_handler(पूर्णांक sig, काष्ठा siginfo *unused_si, काष्ठा uml_pt_regs *regs)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * In basic समय-travel mode we still get real पूर्णांकerrupts
	 * (संकेतs) but since we करोn't पढ़ो समय from the OS, we
	 * must update the simulated समय here to the expiry when
	 * we get a संकेत.
	 * This is not the हाल in inf-cpu mode, since there we
	 * never get any real संकेतs from the OS.
	 */
	अगर (समय_प्रकारravel_mode == TT_MODE_BASIC)
		समय_प्रकारravel_handle_real_alarm();

	local_irq_save(flags);
	करो_IRQ(TIMER_IRQ, regs);
	local_irq_restore(flags);
पूर्ण

अटल पूर्णांक iसमयr_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	अगर (समय_प्रकारravel_mode != TT_MODE_OFF)
		समय_प्रकारravel_del_event(&समय_प्रकारravel_समयr_event);

	अगर (समय_प्रकारravel_mode != TT_MODE_INFCPU &&
	    समय_प्रकारravel_mode != TT_MODE_EXTERNAL)
		os_समयr_disable();

	वापस 0;
पूर्ण

अटल पूर्णांक iसमयr_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	अचिन्हित दीर्घ दीर्घ पूर्णांकerval = NSEC_PER_SEC / HZ;

	अगर (समय_प्रकारravel_mode != TT_MODE_OFF) अणु
		समय_प्रकारravel_del_event(&समय_प्रकारravel_समयr_event);
		समय_प्रकारravel_set_event_fn(&समय_प्रकारravel_समयr_event,
					 समय_प्रकारravel_periodic_समयr);
		समय_प्रकारravel_set_पूर्णांकerval(पूर्णांकerval);
		समय_प्रकारravel_add_event(&समय_प्रकारravel_समयr_event,
				      समय_प्रकारravel_समय + पूर्णांकerval);
	पूर्ण

	अगर (समय_प्रकारravel_mode != TT_MODE_INFCPU &&
	    समय_प्रकारravel_mode != TT_MODE_EXTERNAL)
		os_समयr_set_पूर्णांकerval(पूर्णांकerval);

	वापस 0;
पूर्ण

अटल पूर्णांक iसमयr_next_event(अचिन्हित दीर्घ delta,
			     काष्ठा घड़ी_event_device *evt)
अणु
	delta += 1;

	अगर (समय_प्रकारravel_mode != TT_MODE_OFF) अणु
		समय_प्रकारravel_del_event(&समय_प्रकारravel_समयr_event);
		समय_प्रकारravel_set_event_fn(&समय_प्रकारravel_समयr_event,
					 समय_प्रकारravel_oneshot_समयr);
		समय_प्रकारravel_add_event(&समय_प्रकारravel_समयr_event,
				      समय_प्रकारravel_समय + delta);
	पूर्ण

	अगर (समय_प्रकारravel_mode != TT_MODE_INFCPU &&
	    समय_प्रकारravel_mode != TT_MODE_EXTERNAL)
		वापस os_समयr_one_shot(delta);

	वापस 0;
पूर्ण

अटल पूर्णांक iसमयr_one_shot(काष्ठा घड़ी_event_device *evt)
अणु
	वापस iसमयr_next_event(0, evt);
पूर्ण

अटल काष्ठा घड़ी_event_device समयr_घड़ीevent = अणु
	.name			= "posix-timer",
	.rating			= 250,
	.cpumask		= cpu_possible_mask,
	.features		= CLOCK_EVT_FEAT_PERIODIC |
				  CLOCK_EVT_FEAT_ONESHOT,
	.set_state_shutकरोwn	= iसमयr_shutकरोwn,
	.set_state_periodic	= iसमयr_set_periodic,
	.set_state_oneshot	= iसमयr_one_shot,
	.set_next_event		= iसमयr_next_event,
	.shअगरt			= 0,
	.max_delta_ns		= 0xffffffff,
	.max_delta_ticks	= 0xffffffff,
	.min_delta_ns		= TIMER_MIN_DELTA,
	.min_delta_ticks	= TIMER_MIN_DELTA, // microsecond resolution should be enough क्रम anyone, same as 640K RAM
	.irq			= 0,
	.mult			= 1,
पूर्ण;

अटल irqवापस_t um_समयr(पूर्णांक irq, व्योम *dev)
अणु
	अगर (get_current()->mm != शून्य)
	अणु
        /* userspace - relay संकेत, results in correct userspace समयrs */
		os_alarm_process(get_current()->mm->context.id.u.pid);
	पूर्ण

	(*समयr_घड़ीevent.event_handler)(&समयr_घड़ीevent);

	वापस IRQ_HANDLED;
पूर्ण

अटल u64 समयr_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	अगर (समय_प्रकारravel_mode != TT_MODE_OFF) अणु
		/*
		 * We make पढ़ोing the समयr cost a bit so that we करोn't get
		 * stuck in loops that expect समय to move more than the
		 * exact requested sleep amount, e.g. python's socket server,
		 * see https://bugs.python.org/issue37026.
		 *
		 * However, करोn't do that when we're in पूर्णांकerrupt or such as
		 * then we might recurse पूर्णांकo our own processing, and get to
		 * even more रुकोing, and that's not good - it messes up the
		 * "what do I do next" and onstack event we use to know when
		 * to वापस from समय_प्रकारravel_update_समय().
		 */
		अगर (!irqs_disabled() && !in_पूर्णांकerrupt() && !in_softirq() &&
		    !समय_प्रकारravel_ext_रुकोing)
			समय_प्रकारravel_update_समय(समय_प्रकारravel_समय +
						TIMER_MULTIPLIER,
						false);
		वापस समय_प्रकारravel_समय / TIMER_MULTIPLIER;
	पूर्ण

	वापस os_nsecs() / TIMER_MULTIPLIER;
पूर्ण

अटल काष्ठा घड़ीsource समयr_घड़ीsource = अणु
	.name		= "timer",
	.rating		= 300,
	.पढ़ो		= समयr_पढ़ो,
	.mask		= CLOCKSOURCE_MASK(64),
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल व्योम __init um_समयr_setup(व्योम)
अणु
	पूर्णांक err;

	err = request_irq(TIMER_IRQ, um_समयr, IRQF_TIMER, "hr timer", शून्य);
	अगर (err != 0)
		prपूर्णांकk(KERN_ERR "register_timer : request_irq failed - "
		       "errno = %d\n", -err);

	err = os_समयr_create();
	अगर (err != 0) अणु
		prपूर्णांकk(KERN_ERR "creation of timer failed - errno = %d\n", -err);
		वापस;
	पूर्ण

	err = घड़ीsource_रेजिस्टर_hz(&समयr_घड़ीsource, NSEC_PER_SEC/TIMER_MULTIPLIER);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "clocksource_register_hz returned %d\n", err);
		वापस;
	पूर्ण
	घड़ीevents_रेजिस्टर_device(&समयr_घड़ीevent);
पूर्ण

व्योम पढ़ो_persistent_घड़ी64(काष्ठा बारpec64 *ts)
अणु
	दीर्घ दीर्घ nsecs;

	समय_प्रकारravel_set_start();

	अगर (समय_प्रकारravel_mode != TT_MODE_OFF)
		nsecs = समय_प्रकारravel_start + समय_प्रकारravel_समय;
	अन्यथा
		nsecs = os_persistent_घड़ी_emulation();

	set_normalized_बारpec64(ts, nsecs / NSEC_PER_SEC,
				  nsecs % NSEC_PER_SEC);
पूर्ण

व्योम __init समय_init(व्योम)
अणु
	समयr_set_संकेत_handler();
	late_समय_init = um_समयr_setup;
पूर्ण

#अगर_घोषित CONFIG_UML_TIME_TRAVEL_SUPPORT
अचिन्हित दीर्घ calibrate_delay_is_known(व्योम)
अणु
	अगर (समय_प्रकारravel_mode == TT_MODE_INFCPU ||
	    समय_प्रकारravel_mode == TT_MODE_EXTERNAL)
		वापस 1;
	वापस 0;
पूर्ण

पूर्णांक setup_समय_प्रकारravel(अक्षर *str)
अणु
	अगर (म_भेद(str, "=inf-cpu") == 0) अणु
		समय_प्रकारravel_mode = TT_MODE_INFCPU;
		समयr_घड़ीevent.name = "time-travel-timer-infcpu";
		समयr_घड़ीsource.name = "time-travel-clock";
		वापस 1;
	पूर्ण

	अगर (म_भेदन(str, "=ext:", 5) == 0) अणु
		समय_प्रकारravel_mode = TT_MODE_EXTERNAL;
		समयr_घड़ीevent.name = "time-travel-timer-external";
		समयr_घड़ीsource.name = "time-travel-clock-external";
		वापस समय_प्रकारravel_connect_बाह्यal(str + 5);
	पूर्ण

	अगर (!*str) अणु
		समय_प्रकारravel_mode = TT_MODE_BASIC;
		समयr_घड़ीevent.name = "time-travel-timer";
		समयr_घड़ीsource.name = "time-travel-clock";
		वापस 1;
	पूर्ण

	वापस -EINVAL;
पूर्ण

__setup("time-travel", setup_समय_प्रकारravel);
__uml_help(setup_समय_प्रकारravel,
"time-travel\n"
"This option just enables basic time travel mode, in which the clock/timers\n"
"inside the UML instance skip forward when there's nothing to do, rather than\n"
"waiting for real time to elapse. However, instance CPU speed is limited by\n"
"the real CPU speed, so e.g. a 10ms timer will always fire after ~10ms wall\n"
"clock (but quicker when there's nothing to do).\n"
"\n"
"time-travel=inf-cpu\n"
"This enables time travel mode with infinite processing power, in which there\n"
"are no wall clock timers, and any CPU processing happens - as seen from the\n"
"guest - instantly. This can be useful for accurate simulation regardless of\n"
"debug overhead, physical CPU speed, etc. but is somewhat dangerous as it can\n"
"easily lead to getting stuck (e.g. if anything in the system busy loops).\n"
"\n"
"time-travel=ext:[ID:]/path/to/socket\n"
"This enables time travel mode similar to =inf-cpu, except the system will\n"
"use the given socket to coordinate with a central scheduler, in order to\n"
"have more than one system simultaneously be on simulated time. The virtio\n"
"driver code in UML knows about this so you can also simulate networks and\n"
"devices using it, assuming the device has the right capabilities.\n"
"The optional ID is a 64-bit integer that's sent to the central scheduler.\n");

पूर्णांक setup_समय_प्रकारravel_start(अक्षर *str)
अणु
	पूर्णांक err;

	err = kम_से_अदीर्घl(str, 0, &समय_प्रकारravel_start);
	अगर (err)
		वापस err;

	समय_प्रकारravel_start_set = 1;
	वापस 1;
पूर्ण

__setup("time-travel-start", setup_समय_प्रकारravel_start);
__uml_help(setup_समय_प्रकारravel_start,
"time-travel-start=<seconds>\n"
"Configure the UML instance's wall clock to start at this value rather than\n"
"the host's wall clock at the time of UML boot.\n");
#पूर्ण_अगर
