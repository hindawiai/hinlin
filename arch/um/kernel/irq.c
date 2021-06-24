<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017 - Cambridge Greys Ltd
 * Copyright (C) 2011 - 2014 Cisco Systems Inc
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 * Derived (i.e. mostly copied) from arch/i386/kernel/irq.c:
 *	Copyright (C) 1992, 1998 Linus Torvalds, Ingo Molnar
 */

#समावेश <linux/cpumask.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <as-layout.h>
#समावेश <kern_util.h>
#समावेश <os.h>
#समावेश <irq_user.h>
#समावेश <irq_kern.h>
#समावेश <linux/समय-पूर्णांकernal.h>


बाह्य व्योम मुक्त_irqs(व्योम);

/* When epoll triggers we करो not know why it did so
 * we can also have dअगरferent IRQs क्रम पढ़ो and ग_लिखो.
 * This is why we keep a small irq_reg array क्रम each fd -
 * one entry per IRQ type
 */
काष्ठा irq_reg अणु
	व्योम *id;
	पूर्णांक irq;
	/* it's cheaper to store this than to query it */
	पूर्णांक events;
	bool active;
	bool pending;
	bool wakeup;
#अगर_घोषित CONFIG_UML_TIME_TRAVEL_SUPPORT
	bool pending_on_resume;
	व्योम (*समयtravel_handler)(पूर्णांक, पूर्णांक, व्योम *,
				   काष्ठा समय_प्रकारravel_event *);
	काष्ठा समय_प्रकारravel_event event;
#पूर्ण_अगर
पूर्ण;

काष्ठा irq_entry अणु
	काष्ठा list_head list;
	पूर्णांक fd;
	काष्ठा irq_reg reg[NUM_IRQ_TYPES];
	bool suspended;
	bool sigio_workaround;
पूर्ण;

अटल DEFINE_SPINLOCK(irq_lock);
अटल LIST_HEAD(active_fds);
अटल DECLARE_BITMAP(irqs_allocated, NR_IRQS);
अटल bool irqs_suspended;

अटल व्योम irq_io_loop(काष्ठा irq_reg *irq, काष्ठा uml_pt_regs *regs)
अणु
/*
 * irq->active guards against reentry
 * irq->pending accumulates pending requests
 * अगर pending is उठाओd the irq_handler is re-run
 * until pending is cleared
 */
	अगर (irq->active) अणु
		irq->active = false;

		करो अणु
			irq->pending = false;
			करो_IRQ(irq->irq, regs);
		पूर्ण जबतक (irq->pending);

		irq->active = true;
	पूर्ण अन्यथा अणु
		irq->pending = true;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_UML_TIME_TRAVEL_SUPPORT
अटल व्योम irq_event_handler(काष्ठा समय_प्रकारravel_event *ev)
अणु
	काष्ठा irq_reg *reg = container_of(ev, काष्ठा irq_reg, event);

	/* करो nothing अगर suspended - just to cause a wakeup */
	अगर (irqs_suspended)
		वापस;

	generic_handle_irq(reg->irq);
पूर्ण

अटल bool irq_करो_समयtravel_handler(काष्ठा irq_entry *entry,
				      क्रमागत um_irq_type t)
अणु
	काष्ठा irq_reg *reg = &entry->reg[t];

	अगर (!reg->समयtravel_handler)
		वापस false;

	/* prevent nesting - we'll get it again later when we SIGIO ourselves */
	अगर (reg->pending_on_resume)
		वापस true;

	reg->समयtravel_handler(reg->irq, entry->fd, reg->id, &reg->event);

	अगर (!reg->event.pending)
		वापस false;

	अगर (irqs_suspended)
		reg->pending_on_resume = true;
	वापस true;
पूर्ण
#अन्यथा
अटल bool irq_करो_समयtravel_handler(काष्ठा irq_entry *entry,
				      क्रमागत um_irq_type t)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल व्योम sigio_reg_handler(पूर्णांक idx, काष्ठा irq_entry *entry, क्रमागत um_irq_type t,
			      काष्ठा uml_pt_regs *regs)
अणु
	काष्ठा irq_reg *reg = &entry->reg[t];

	अगर (!reg->events)
		वापस;

	अगर (os_epoll_triggered(idx, reg->events) <= 0)
		वापस;

	अगर (irq_करो_समयtravel_handler(entry, t))
		वापस;

	अगर (irqs_suspended)
		वापस;

	irq_io_loop(reg, regs);
पूर्ण

व्योम sigio_handler(पूर्णांक sig, काष्ठा siginfo *unused_si, काष्ठा uml_pt_regs *regs)
अणु
	काष्ठा irq_entry *irq_entry;
	पूर्णांक n, i;

	अगर (irqs_suspended && !um_irq_समयtravel_handler_used())
		वापस;

	जबतक (1) अणु
		/* This is now lockless - epoll keeps back-referencesto the irqs
		 * which have trigger it so there is no need to walk the irq
		 * list and lock it every समय. We aव्योम locking by turning off
		 * IO क्रम a specअगरic fd by executing os_del_epoll_fd(fd) beक्रमe
		 * we करो any changes to the actual data काष्ठाures
		 */
		n = os_रुकोing_क्रम_events_epoll();

		अगर (n <= 0) अणु
			अगर (n == -EINTR)
				जारी;
			अन्यथा
				अवरोध;
		पूर्ण

		क्रम (i = 0; i < n ; i++) अणु
			क्रमागत um_irq_type t;

			irq_entry = os_epoll_get_data_poपूर्णांकer(i);

			क्रम (t = 0; t < NUM_IRQ_TYPES; t++)
				sigio_reg_handler(i, irq_entry, t, regs);
		पूर्ण
	पूर्ण

	अगर (!irqs_suspended)
		मुक्त_irqs();
पूर्ण

अटल काष्ठा irq_entry *get_irq_entry_by_fd(पूर्णांक fd)
अणु
	काष्ठा irq_entry *walk;

	lockdep_निश्चित_held(&irq_lock);

	list_क्रम_each_entry(walk, &active_fds, list) अणु
		अगर (walk->fd == fd)
			वापस walk;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम मुक्त_irq_entry(काष्ठा irq_entry *to_मुक्त, bool हटाओ)
अणु
	अगर (!to_मुक्त)
		वापस;

	अगर (हटाओ)
		os_del_epoll_fd(to_मुक्त->fd);
	list_del(&to_मुक्त->list);
	kमुक्त(to_मुक्त);
पूर्ण

अटल bool update_irq_entry(काष्ठा irq_entry *entry)
अणु
	क्रमागत um_irq_type i;
	पूर्णांक events = 0;

	क्रम (i = 0; i < NUM_IRQ_TYPES; i++)
		events |= entry->reg[i].events;

	अगर (events) अणु
		/* will modअगरy (instead of add) अगर needed */
		os_add_epoll_fd(events, entry->fd, entry);
		वापस true;
	पूर्ण

	os_del_epoll_fd(entry->fd);
	वापस false;
पूर्ण

अटल व्योम update_or_मुक्त_irq_entry(काष्ठा irq_entry *entry)
अणु
	अगर (!update_irq_entry(entry))
		मुक्त_irq_entry(entry, false);
पूर्ण

अटल पूर्णांक activate_fd(पूर्णांक irq, पूर्णांक fd, क्रमागत um_irq_type type, व्योम *dev_id,
		       व्योम (*समयtravel_handler)(पूर्णांक, पूर्णांक, व्योम *,
						  काष्ठा समय_प्रकारravel_event *))
अणु
	काष्ठा irq_entry *irq_entry;
	पूर्णांक err, events = os_event_mask(type);
	अचिन्हित दीर्घ flags;

	err = os_set_fd_async(fd);
	अगर (err < 0)
		जाओ out;

	spin_lock_irqsave(&irq_lock, flags);
	irq_entry = get_irq_entry_by_fd(fd);
	अगर (irq_entry) अणु
		/* cannot रेजिस्टर the same FD twice with the same type */
		अगर (WARN_ON(irq_entry->reg[type].events)) अणु
			err = -EALREADY;
			जाओ out_unlock;
		पूर्ण

		/* temporarily disable to aव्योम IRQ-side locking */
		os_del_epoll_fd(fd);
	पूर्ण अन्यथा अणु
		irq_entry = kzalloc(माप(*irq_entry), GFP_ATOMIC);
		अगर (!irq_entry) अणु
			err = -ENOMEM;
			जाओ out_unlock;
		पूर्ण
		irq_entry->fd = fd;
		list_add_tail(&irq_entry->list, &active_fds);
		maybe_sigio_broken(fd);
	पूर्ण

	irq_entry->reg[type].id = dev_id;
	irq_entry->reg[type].irq = irq;
	irq_entry->reg[type].active = true;
	irq_entry->reg[type].events = events;

#अगर_घोषित CONFIG_UML_TIME_TRAVEL_SUPPORT
	अगर (um_irq_समयtravel_handler_used()) अणु
		irq_entry->reg[type].समयtravel_handler = समयtravel_handler;
		irq_entry->reg[type].event.fn = irq_event_handler;
	पूर्ण
#पूर्ण_अगर

	WARN_ON(!update_irq_entry(irq_entry));
	spin_unlock_irqrestore(&irq_lock, flags);

	वापस 0;
out_unlock:
	spin_unlock_irqrestore(&irq_lock, flags);
out:
	वापस err;
पूर्ण

/*
 * Remove the entry or entries क्रम a specअगरic FD, अगर you
 * करोn't want to हटाओ all the possible entries then use
 * um_मुक्त_irq() or deactivate_fd() instead.
 */
व्योम मुक्त_irq_by_fd(पूर्णांक fd)
अणु
	काष्ठा irq_entry *to_मुक्त;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&irq_lock, flags);
	to_मुक्त = get_irq_entry_by_fd(fd);
	मुक्त_irq_entry(to_मुक्त, true);
	spin_unlock_irqrestore(&irq_lock, flags);
पूर्ण
EXPORT_SYMBOL(मुक्त_irq_by_fd);

अटल व्योम मुक्त_irq_by_irq_and_dev(अचिन्हित पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा irq_entry *entry;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&irq_lock, flags);
	list_क्रम_each_entry(entry, &active_fds, list) अणु
		क्रमागत um_irq_type i;

		क्रम (i = 0; i < NUM_IRQ_TYPES; i++) अणु
			काष्ठा irq_reg *reg = &entry->reg[i];

			अगर (!reg->events)
				जारी;
			अगर (reg->irq != irq)
				जारी;
			अगर (reg->id != dev)
				जारी;

			os_del_epoll_fd(entry->fd);
			reg->events = 0;
			update_or_मुक्त_irq_entry(entry);
			जाओ out;
		पूर्ण
	पूर्ण
out:
	spin_unlock_irqrestore(&irq_lock, flags);
पूर्ण

व्योम deactivate_fd(पूर्णांक fd, पूर्णांक irqnum)
अणु
	काष्ठा irq_entry *entry;
	अचिन्हित दीर्घ flags;
	क्रमागत um_irq_type i;

	os_del_epoll_fd(fd);

	spin_lock_irqsave(&irq_lock, flags);
	entry = get_irq_entry_by_fd(fd);
	अगर (!entry)
		जाओ out;

	क्रम (i = 0; i < NUM_IRQ_TYPES; i++) अणु
		अगर (!entry->reg[i].events)
			जारी;
		अगर (entry->reg[i].irq == irqnum)
			entry->reg[i].events = 0;
	पूर्ण

	update_or_मुक्त_irq_entry(entry);
out:
	spin_unlock_irqrestore(&irq_lock, flags);

	ignore_sigio_fd(fd);
पूर्ण
EXPORT_SYMBOL(deactivate_fd);

/*
 * Called just beक्रमe shutकरोwn in order to provide a clean exec
 * environment in हाल the प्रणाली is rebooting.  No locking because
 * that would cause a poपूर्णांकless shutकरोwn hang अगर something hadn't
 * released the lock.
 */
पूर्णांक deactivate_all_fds(व्योम)
अणु
	काष्ठा irq_entry *entry;

	/* Stop IO. The IRQ loop has no lock so this is our
	 * only way of making sure we are safe to dispose
	 * of all IRQ handlers
	 */
	os_set_ioignore();

	/* we can no दीर्घer call kमुक्त() here so just deactivate */
	list_क्रम_each_entry(entry, &active_fds, list)
		os_del_epoll_fd(entry->fd);
	os_बंद_epoll_fd();
	वापस 0;
पूर्ण

/*
 * करो_IRQ handles all normal device IRQs (the special
 * SMP cross-CPU पूर्णांकerrupts have their own specअगरic
 * handlers).
 */
अचिन्हित पूर्णांक करो_IRQ(पूर्णांक irq, काष्ठा uml_pt_regs *regs)
अणु
	काष्ठा pt_regs *old_regs = set_irq_regs((काष्ठा pt_regs *)regs);
	irq_enter();
	generic_handle_irq(irq);
	irq_निकास();
	set_irq_regs(old_regs);
	वापस 1;
पूर्ण

व्योम um_मुक्त_irq(पूर्णांक irq, व्योम *dev)
अणु
	अगर (WARN(irq < 0 || irq > NR_IRQS, "freeing invalid irq %d", irq))
		वापस;

	मुक्त_irq_by_irq_and_dev(irq, dev);
	मुक्त_irq(irq, dev);
	clear_bit(irq, irqs_allocated);
पूर्ण
EXPORT_SYMBOL(um_मुक्त_irq);

अटल पूर्णांक
_um_request_irq(पूर्णांक irq, पूर्णांक fd, क्रमागत um_irq_type type,
		irq_handler_t handler, अचिन्हित दीर्घ irqflags,
		स्थिर अक्षर *devname, व्योम *dev_id,
		व्योम (*समयtravel_handler)(पूर्णांक, पूर्णांक, व्योम *,
					   काष्ठा समय_प्रकारravel_event *))
अणु
	पूर्णांक err;

	अगर (irq == UM_IRQ_ALLOC) अणु
		पूर्णांक i;

		क्रम (i = UM_FIRST_DYN_IRQ; i < NR_IRQS; i++) अणु
			अगर (!test_and_set_bit(i, irqs_allocated)) अणु
				irq = i;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (irq < 0)
		वापस -ENOSPC;

	अगर (fd != -1) अणु
		err = activate_fd(irq, fd, type, dev_id, समयtravel_handler);
		अगर (err)
			जाओ error;
	पूर्ण

	err = request_irq(irq, handler, irqflags, devname, dev_id);
	अगर (err < 0)
		जाओ error;

	वापस irq;
error:
	clear_bit(irq, irqs_allocated);
	वापस err;
पूर्ण

पूर्णांक um_request_irq(पूर्णांक irq, पूर्णांक fd, क्रमागत um_irq_type type,
		   irq_handler_t handler, अचिन्हित दीर्घ irqflags,
		   स्थिर अक्षर *devname, व्योम *dev_id)
अणु
	वापस _um_request_irq(irq, fd, type, handler, irqflags,
			       devname, dev_id, शून्य);
पूर्ण
EXPORT_SYMBOL(um_request_irq);

#अगर_घोषित CONFIG_UML_TIME_TRAVEL_SUPPORT
पूर्णांक um_request_irq_tt(पूर्णांक irq, पूर्णांक fd, क्रमागत um_irq_type type,
		      irq_handler_t handler, अचिन्हित दीर्घ irqflags,
		      स्थिर अक्षर *devname, व्योम *dev_id,
		      व्योम (*समयtravel_handler)(पूर्णांक, पूर्णांक, व्योम *,
						 काष्ठा समय_प्रकारravel_event *))
अणु
	वापस _um_request_irq(irq, fd, type, handler, irqflags,
			       devname, dev_id, समयtravel_handler);
पूर्ण
EXPORT_SYMBOL(um_request_irq_tt);
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
व्योम um_irqs_suspend(व्योम)
अणु
	काष्ठा irq_entry *entry;
	अचिन्हित दीर्घ flags;

	irqs_suspended = true;

	spin_lock_irqsave(&irq_lock, flags);
	list_क्रम_each_entry(entry, &active_fds, list) अणु
		क्रमागत um_irq_type t;
		bool clear = true;

		क्रम (t = 0; t < NUM_IRQ_TYPES; t++) अणु
			अगर (!entry->reg[t].events)
				जारी;

			/*
			 * For the SIGIO_WRITE_IRQ, which is used to handle the
			 * SIGIO workaround thपढ़ो, we need special handling:
			 * enable wake क्रम it itself, but below we tell it about
			 * any FDs that should be suspended.
			 */
			अगर (entry->reg[t].wakeup ||
			    entry->reg[t].irq == SIGIO_WRITE_IRQ
#अगर_घोषित CONFIG_UML_TIME_TRAVEL_SUPPORT
			    || entry->reg[t].समयtravel_handler
#पूर्ण_अगर
			    ) अणु
				clear = false;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (clear) अणु
			entry->suspended = true;
			os_clear_fd_async(entry->fd);
			entry->sigio_workaround =
				!__ignore_sigio_fd(entry->fd);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&irq_lock, flags);
पूर्ण

व्योम um_irqs_resume(व्योम)
अणु
	काष्ठा irq_entry *entry;
	अचिन्हित दीर्घ flags;


	local_irq_save(flags);
#अगर_घोषित CONFIG_UML_TIME_TRAVEL_SUPPORT
	/*
	 * We करोn't need to lock anything here since we're in resume
	 * and nothing अन्यथा is running, but have disabled IRQs so we
	 * करोn't try anything अन्यथा with the पूर्णांकerrupt list from there.
	 */
	list_क्रम_each_entry(entry, &active_fds, list) अणु
		क्रमागत um_irq_type t;

		क्रम (t = 0; t < NUM_IRQ_TYPES; t++) अणु
			काष्ठा irq_reg *reg = &entry->reg[t];

			अगर (reg->pending_on_resume) अणु
				irq_enter();
				generic_handle_irq(reg->irq);
				irq_निकास();
				reg->pending_on_resume = false;
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	spin_lock(&irq_lock);
	list_क्रम_each_entry(entry, &active_fds, list) अणु
		अगर (entry->suspended) अणु
			पूर्णांक err = os_set_fd_async(entry->fd);

			WARN(err < 0, "os_set_fd_async returned %d\n", err);
			entry->suspended = false;

			अगर (entry->sigio_workaround) अणु
				err = __add_sigio_fd(entry->fd);
				WARN(err < 0, "add_sigio_returned %d\n", err);
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&irq_lock, flags);

	irqs_suspended = false;
	send_sigio_to_self();
पूर्ण

अटल पूर्णांक normal_irq_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक on)
अणु
	काष्ठा irq_entry *entry;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&irq_lock, flags);
	list_क्रम_each_entry(entry, &active_fds, list) अणु
		क्रमागत um_irq_type t;

		क्रम (t = 0; t < NUM_IRQ_TYPES; t++) अणु
			अगर (!entry->reg[t].events)
				जारी;

			अगर (entry->reg[t].irq != d->irq)
				जारी;
			entry->reg[t].wakeup = on;
			जाओ unlock;
		पूर्ण
	पूर्ण
unlock:
	spin_unlock_irqrestore(&irq_lock, flags);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा normal_irq_set_wake शून्य
#पूर्ण_अगर

/*
 * irq_chip must define at least enable/disable and ack when
 * the edge handler is used.
 */
अटल व्योम dummy(काष्ठा irq_data *d)
अणु
पूर्ण

/* This is used क्रम everything other than the समयr. */
अटल काष्ठा irq_chip normal_irq_type = अणु
	.name = "SIGIO",
	.irq_disable = dummy,
	.irq_enable = dummy,
	.irq_ack = dummy,
	.irq_mask = dummy,
	.irq_unmask = dummy,
	.irq_set_wake = normal_irq_set_wake,
पूर्ण;

अटल काष्ठा irq_chip alarm_irq_type = अणु
	.name = "SIGALRM",
	.irq_disable = dummy,
	.irq_enable = dummy,
	.irq_ack = dummy,
	.irq_mask = dummy,
	.irq_unmask = dummy,
पूर्ण;

व्योम __init init_IRQ(व्योम)
अणु
	पूर्णांक i;

	irq_set_chip_and_handler(TIMER_IRQ, &alarm_irq_type, handle_edge_irq);

	क्रम (i = 1; i < NR_IRQS; i++)
		irq_set_chip_and_handler(i, &normal_irq_type, handle_edge_irq);
	/* Initialize EPOLL Loop */
	os_setup_epoll();
पूर्ण

/*
 * IRQ stack entry and निकास:
 *
 * Unlike i386, UML करोesn't receive IRQs on the normal kernel stack
 * and चयन over to the IRQ stack after some preparation.  We use
 * sigaltstack to receive संकेतs on a separate stack from the start.
 * These two functions make sure the rest of the kernel won't be too
 * upset by being on a dअगरferent stack.  The IRQ stack has a
 * thपढ़ो_info काष्ठाure at the bottom so that current et al जारी
 * to work.
 *
 * to_irq_stack copies the current task's thपढ़ो_info to the IRQ stack
 * thपढ़ो_info and sets the tasks's stack to poपूर्णांक to the IRQ stack.
 *
 * from_irq_stack copies the thपढ़ो_info काष्ठा back (flags may have
 * been modअगरied) and resets the task's stack poपूर्णांकer.
 *
 * Tricky bits -
 *
 * What happens when two संकेतs race each other?  UML करोesn't block
 * संकेतs with sigprocmask, SA_DEFER, or sa_mask, so a second संकेत
 * could arrive जबतक a previous one is still setting up the
 * thपढ़ो_info.
 *
 * There are three हालs -
 *     The first पूर्णांकerrupt on the stack - sets up the thपढ़ो_info and
 * handles the पूर्णांकerrupt
 *     A nested पूर्णांकerrupt पूर्णांकerrupting the copying of the thपढ़ो_info -
 * can't handle the पूर्णांकerrupt, as the stack is in an unknown state
 *     A nested पूर्णांकerrupt not पूर्णांकerrupting the copying of the
 * thपढ़ो_info - करोesn't करो any setup, just handles the पूर्णांकerrupt
 *
 * The first job is to figure out whether we पूर्णांकerrupted stack setup.
 * This is करोne by xchging the संकेत mask with thपढ़ो_info->pending.
 * If the value that comes back is zero, then there is no setup in
 * progress, and the पूर्णांकerrupt can be handled.  If the value is
 * non-zero, then there is stack setup in progress.  In order to have
 * the पूर्णांकerrupt handled, we leave our संकेत in the mask, and it will
 * be handled by the upper handler after it has set up the stack.
 *
 * Next is to figure out whether we are the outer handler or a nested
 * one.  As part of setting up the stack, thपढ़ो_info->real_thपढ़ो is
 * set to non-शून्य (and is reset to शून्य on निकास).  This is the
 * nesting indicator.  If it is non-शून्य, then the stack is alपढ़ोy
 * set up and the handler can run.
 */

अटल अचिन्हित दीर्घ pending_mask;

अचिन्हित दीर्घ to_irq_stack(अचिन्हित दीर्घ *mask_out)
अणु
	काष्ठा thपढ़ो_info *ti;
	अचिन्हित दीर्घ mask, old;
	पूर्णांक nested;

	mask = xchg(&pending_mask, *mask_out);
	अगर (mask != 0) अणु
		/*
		 * If any पूर्णांकerrupts come in at this poपूर्णांक, we want to
		 * make sure that their bits aren't lost by our
		 * putting our bit in.  So, this loop accumulates bits
		 * until xchg वापसs the same value that we put in.
		 * When that happens, there were no new पूर्णांकerrupts,
		 * and pending_mask contains a bit क्रम each पूर्णांकerrupt
		 * that came in.
		 */
		old = *mask_out;
		करो अणु
			old |= mask;
			mask = xchg(&pending_mask, old);
		पूर्ण जबतक (mask != old);
		वापस 1;
	पूर्ण

	ti = current_thपढ़ो_info();
	nested = (ti->real_thपढ़ो != शून्य);
	अगर (!nested) अणु
		काष्ठा task_काष्ठा *task;
		काष्ठा thपढ़ो_info *tti;

		task = cpu_tasks[ti->cpu].task;
		tti = task_thपढ़ो_info(task);

		*ti = *tti;
		ti->real_thपढ़ो = tti;
		task->stack = ti;
	पूर्ण

	mask = xchg(&pending_mask, 0);
	*mask_out |= mask | nested;
	वापस 0;
पूर्ण

अचिन्हित दीर्घ from_irq_stack(पूर्णांक nested)
अणु
	काष्ठा thपढ़ो_info *ti, *to;
	अचिन्हित दीर्घ mask;

	ti = current_thपढ़ो_info();

	pending_mask = 1;

	to = ti->real_thपढ़ो;
	current->stack = to;
	ti->real_thपढ़ो = शून्य;
	*to = *ti;

	mask = xchg(&pending_mask, 0);
	वापस mask & ~1;
पूर्ण

