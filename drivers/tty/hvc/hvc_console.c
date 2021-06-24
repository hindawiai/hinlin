<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2001 Anton Blanअक्षरd <anton@au.ibm.com>, IBM
 * Copyright (C) 2001 Paul Mackerras <paulus@au.ibm.com>, IBM
 * Copyright (C) 2004 Benjamin Herrenschmidt <benh@kernel.crashing.org>, IBM Corp.
 * Copyright (C) 2004 IBM Corporation
 *
 * Additional Author(s):
 *  Ryan S. Arnold <rsa@us.ibm.com>
 */

#समावेश <linux/console.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/init.h>
#समावेश <linux/kbd_kern.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/list.h>
#समावेश <linux/major.h>
#समावेश <linux/atomic.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/slab.h>
#समावेश <linux/serial_core.h>

#समावेश <linux/uaccess.h>

#समावेश "hvc_console.h"

#घोषणा HVC_MAJOR	229
#घोषणा HVC_MINOR	0

/*
 * Wait this दीर्घ per iteration जबतक trying to push buffered data to the
 * hypervisor beक्रमe allowing the tty to complete a बंद operation.
 */
#घोषणा HVC_CLOSE_WAIT (HZ/100) /* 1/10 of a second */

/*
 * These sizes are most efficient क्रम vio, because they are the
 * native transfer size. We could make them selectable in the
 * future to better deal with backends that want other buffer sizes.
 */
#घोषणा N_OUTBUF	16
#घोषणा N_INBUF		16

#घोषणा __ALIGNED__ __attribute__((__aligned__(माप(दीर्घ))))

अटल काष्ठा tty_driver *hvc_driver;
अटल काष्ठा task_काष्ठा *hvc_task;

/* Picks up late kicks after list walk but beक्रमe schedule() */
अटल पूर्णांक hvc_kicked;

/* hvc_init is triggered from hvc_alloc, i.e. only when actually used */
अटल atomic_t hvc_needs_init __पढ़ो_mostly = ATOMIC_INIT(-1);

अटल पूर्णांक hvc_init(व्योम);

#अगर_घोषित CONFIG_MAGIC_SYSRQ
अटल पूर्णांक sysrq_pressed;
#पूर्ण_अगर

/* dynamic list of hvc_काष्ठा instances */
अटल LIST_HEAD(hvc_काष्ठाs);

/*
 * Protect the list of hvc_काष्ठा instances from inserts and removals during
 * list traversal.
 */
अटल DEFINE_MUTEX(hvc_काष्ठाs_mutex);

/*
 * This value is used to assign a tty->index value to a hvc_काष्ठा based
 * upon order of exposure via hvc_probe(), when we can not match it to
 * a console candidate रेजिस्टरed with hvc_instantiate().
 */
अटल पूर्णांक last_hvc = -1;

/*
 * Do not call this function with either the hvc_काष्ठाs_mutex or the hvc_काष्ठा
 * lock held.  If successful, this function increments the kref reference
 * count against the target hvc_काष्ठा so it should be released when finished.
 */
अटल काष्ठा hvc_काष्ठा *hvc_get_by_index(पूर्णांक index)
अणु
	काष्ठा hvc_काष्ठा *hp;
	अचिन्हित दीर्घ flags;

	mutex_lock(&hvc_काष्ठाs_mutex);

	list_क्रम_each_entry(hp, &hvc_काष्ठाs, next) अणु
		spin_lock_irqsave(&hp->lock, flags);
		अगर (hp->index == index) अणु
			tty_port_get(&hp->port);
			spin_unlock_irqrestore(&hp->lock, flags);
			mutex_unlock(&hvc_काष्ठाs_mutex);
			वापस hp;
		पूर्ण
		spin_unlock_irqrestore(&hp->lock, flags);
	पूर्ण
	hp = शून्य;
	mutex_unlock(&hvc_काष्ठाs_mutex);

	वापस hp;
पूर्ण

अटल पूर्णांक __hvc_flush(स्थिर काष्ठा hv_ops *ops, uपूर्णांक32_t vtermno, bool रुको)
अणु
	अगर (रुको)
		might_sleep();

	अगर (ops->flush)
		वापस ops->flush(vtermno, रुको);
	वापस 0;
पूर्ण

अटल पूर्णांक hvc_console_flush(स्थिर काष्ठा hv_ops *ops, uपूर्णांक32_t vtermno)
अणु
	वापस __hvc_flush(ops, vtermno, false);
पूर्ण

/*
 * Wait क्रम the console to flush beक्रमe writing more to it. This sleeps.
 */
अटल पूर्णांक hvc_flush(काष्ठा hvc_काष्ठा *hp)
अणु
	वापस __hvc_flush(hp->ops, hp->vtermno, true);
पूर्ण

/*
 * Initial console vtermnos क्रम console API usage prior to full console
 * initialization.  Any vty adapter outside this range will not have usable
 * console पूर्णांकerfaces but can still be used as a tty device.  This has to be
 * अटल because kदो_स्मृति will not work during early console init.
 */
अटल स्थिर काष्ठा hv_ops *cons_ops[MAX_NR_HVC_CONSOLES];
अटल uपूर्णांक32_t vtermnos[MAX_NR_HVC_CONSOLES] =
	अणु[0 ... MAX_NR_HVC_CONSOLES - 1] = -1पूर्ण;

/*
 * Console APIs, NOT TTY.  These APIs are available immediately when
 * hvc_console_setup() finds adapters.
 */

अटल व्योम hvc_console_prपूर्णांक(काष्ठा console *co, स्थिर अक्षर *b,
			      अचिन्हित count)
अणु
	अक्षर c[N_OUTBUF] __ALIGNED__;
	अचिन्हित i = 0, n = 0;
	पूर्णांक r, करोnecr = 0, index = co->index;

	/* Console access attempt outside of acceptable console range. */
	अगर (index >= MAX_NR_HVC_CONSOLES)
		वापस;

	/* This console adapter was हटाओd so it is not usable. */
	अगर (vtermnos[index] == -1)
		वापस;

	जबतक (count > 0 || i > 0) अणु
		अगर (count > 0 && i < माप(c)) अणु
			अगर (b[n] == '\n' && !करोnecr) अणु
				c[i++] = '\r';
				करोnecr = 1;
			पूर्ण अन्यथा अणु
				c[i++] = b[n++];
				करोnecr = 0;
				--count;
			पूर्ण
		पूर्ण अन्यथा अणु
			r = cons_ops[index]->put_अक्षरs(vtermnos[index], c, i);
			अगर (r <= 0) अणु
				/* throw away अक्षरacters on error
				 * but spin in हाल of -EAGAIN */
				अगर (r != -EAGAIN) अणु
					i = 0;
				पूर्ण अन्यथा अणु
					hvc_console_flush(cons_ops[index],
						      vtermnos[index]);
				पूर्ण
			पूर्ण अन्यथा अगर (r > 0) अणु
				i -= r;
				अगर (i > 0)
					स_हटाओ(c, c+r, i);
			पूर्ण
		पूर्ण
	पूर्ण
	hvc_console_flush(cons_ops[index], vtermnos[index]);
पूर्ण

अटल काष्ठा tty_driver *hvc_console_device(काष्ठा console *c, पूर्णांक *index)
अणु
	अगर (vtermnos[c->index] == -1)
		वापस शून्य;

	*index = c->index;
	वापस hvc_driver;
पूर्ण

अटल पूर्णांक hvc_console_setup(काष्ठा console *co, अक्षर *options)
अणु	
	अगर (co->index < 0 || co->index >= MAX_NR_HVC_CONSOLES)
		वापस -ENODEV;

	अगर (vtermnos[co->index] == -1)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल काष्ठा console hvc_console = अणु
	.name		= "hvc",
	.ग_लिखो		= hvc_console_prपूर्णांक,
	.device		= hvc_console_device,
	.setup		= hvc_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
पूर्ण;

/*
 * Early console initialization.  Precedes driver initialization.
 *
 * (1) we are first, and the user specअगरied another driver
 * -- index will reमुख्य -1
 * (2) we are first and the user specअगरied no driver
 * -- index will be set to 0, then we will fail setup.
 * (3)  we are first and the user specअगरied our driver
 * -- index will be set to user specअगरied driver, and we will fail
 * (4) we are after driver, and this initcall will रेजिस्टर us
 * -- अगर the user didn't specअगरy a driver then the console will match
 *
 * Note that क्रम हालs 2 and 3, we will match later when the io driver
 * calls hvc_instantiate() and call रेजिस्टर again.
 */
अटल पूर्णांक __init hvc_console_init(व्योम)
अणु
	रेजिस्टर_console(&hvc_console);
	वापस 0;
पूर्ण
console_initcall(hvc_console_init);

/* callback when the kboject ref count reaches zero. */
अटल व्योम hvc_port_deकाष्ठा(काष्ठा tty_port *port)
अणु
	काष्ठा hvc_काष्ठा *hp = container_of(port, काष्ठा hvc_काष्ठा, port);
	अचिन्हित दीर्घ flags;

	mutex_lock(&hvc_काष्ठाs_mutex);

	spin_lock_irqsave(&hp->lock, flags);
	list_del(&(hp->next));
	spin_unlock_irqrestore(&hp->lock, flags);

	mutex_unlock(&hvc_काष्ठाs_mutex);

	kमुक्त(hp);
पूर्ण

अटल व्योम hvc_check_console(पूर्णांक index)
अणु
	/* Alपढ़ोy enabled, bail out */
	अगर (hvc_console.flags & CON_ENABLED)
		वापस;

 	/* If this index is what the user requested, then रेजिस्टर
	 * now (setup won't fail at this point).  It's ok to just
	 * call रेजिस्टर again अगर previously .setup failed.
	 */
	अगर (index == hvc_console.index)
		रेजिस्टर_console(&hvc_console);
पूर्ण

/*
 * hvc_instantiate() is an early console discovery method which locates
 * consoles * prior to the vio subप्रणाली discovering them.  Hotplugged
 * vty adapters करो NOT get an hvc_instantiate() callback since they
 * appear after early console init.
 */
पूर्णांक hvc_instantiate(uपूर्णांक32_t vtermno, पूर्णांक index, स्थिर काष्ठा hv_ops *ops)
अणु
	काष्ठा hvc_काष्ठा *hp;

	अगर (index < 0 || index >= MAX_NR_HVC_CONSOLES)
		वापस -1;

	अगर (vtermnos[index] != -1)
		वापस -1;

	/* make sure no no tty has been रेजिस्टरed in this index */
	hp = hvc_get_by_index(index);
	अगर (hp) अणु
		tty_port_put(&hp->port);
		वापस -1;
	पूर्ण

	vtermnos[index] = vtermno;
	cons_ops[index] = ops;

	/* check अगर we need to re-रेजिस्टर the kernel console */
	hvc_check_console(index);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hvc_instantiate);

/* Wake the sleeping khvcd */
व्योम hvc_kick(व्योम)
अणु
	hvc_kicked = 1;
	wake_up_process(hvc_task);
पूर्ण
EXPORT_SYMBOL_GPL(hvc_kick);

अटल व्योम hvc_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	hvc_kick();
पूर्ण

अटल पूर्णांक hvc_install(काष्ठा tty_driver *driver, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा hvc_काष्ठा *hp;
	पूर्णांक rc;

	/* Auto increments kref reference अगर found. */
	hp = hvc_get_by_index(tty->index);
	अगर (!hp)
		वापस -ENODEV;

	tty->driver_data = hp;

	rc = tty_port_install(&hp->port, driver, tty);
	अगर (rc)
		tty_port_put(&hp->port);
	वापस rc;
पूर्ण

/*
 * The TTY पूर्णांकerface won't be used until after the vio layer has exposed the vty
 * adapter to the kernel.
 */
अटल पूर्णांक hvc_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file * filp)
अणु
	काष्ठा hvc_काष्ठा *hp = tty->driver_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	spin_lock_irqsave(&hp->port.lock, flags);
	/* Check and then increment क्रम fast path खोलो. */
	अगर (hp->port.count++ > 0) अणु
		spin_unlock_irqrestore(&hp->port.lock, flags);
		hvc_kick();
		वापस 0;
	पूर्ण /* अन्यथा count == 0 */
	spin_unlock_irqrestore(&hp->port.lock, flags);

	tty_port_tty_set(&hp->port, tty);

	अगर (hp->ops->notअगरier_add)
		rc = hp->ops->notअगरier_add(hp, hp->data);

	/*
	 * If the notअगरier fails we वापस an error.  The tty layer
	 * will call hvc_बंद() after a failed खोलो but we करोn't want to clean
	 * up there so we'll clean up here and clear out the previously set
	 * tty fields and वापस the kref reference.
	 */
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "hvc_open: request_irq failed with rc %d.\n", rc);
	पूर्ण अन्यथा अणु
		/* We are पढ़ोy... उठाओ DTR/RTS */
		अगर (C_BAUD(tty))
			अगर (hp->ops->dtr_rts)
				hp->ops->dtr_rts(hp, 1);
		tty_port_set_initialized(&hp->port, true);
	पूर्ण

	/* Force wakeup of the polling thपढ़ो */
	hvc_kick();

	वापस rc;
पूर्ण

अटल व्योम hvc_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file * filp)
अणु
	काष्ठा hvc_काष्ठा *hp = tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (tty_hung_up_p(filp))
		वापस;

	spin_lock_irqsave(&hp->port.lock, flags);

	अगर (--hp->port.count == 0) अणु
		spin_unlock_irqrestore(&hp->port.lock, flags);
		/* We are करोne with the tty poपूर्णांकer now. */
		tty_port_tty_set(&hp->port, शून्य);

		अगर (!tty_port_initialized(&hp->port))
			वापस;

		अगर (C_HUPCL(tty))
			अगर (hp->ops->dtr_rts)
				hp->ops->dtr_rts(hp, 0);

		अगर (hp->ops->notअगरier_del)
			hp->ops->notअगरier_del(hp, hp->data);

		/* cancel pending tty resize work */
		cancel_work_sync(&hp->tty_resize);

		/*
		 * Chain calls अक्षरs_in_buffer() and वापसs immediately अगर
		 * there is no buffered data otherwise sleeps on a रुको queue
		 * waking periodically to check अक्षरs_in_buffer().
		 */
		tty_रुको_until_sent(tty, HVC_CLOSE_WAIT);
		tty_port_set_initialized(&hp->port, false);
	पूर्ण अन्यथा अणु
		अगर (hp->port.count < 0)
			prपूर्णांकk(KERN_ERR "hvc_close %X: oops, count is %d\n",
				hp->vtermno, hp->port.count);
		spin_unlock_irqrestore(&hp->port.lock, flags);
	पूर्ण
पूर्ण

अटल व्योम hvc_cleanup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा hvc_काष्ठा *hp = tty->driver_data;

	tty_port_put(&hp->port);
पूर्ण

अटल व्योम hvc_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा hvc_काष्ठा *hp = tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (!hp)
		वापस;

	/* cancel pending tty resize work */
	cancel_work_sync(&hp->tty_resize);

	spin_lock_irqsave(&hp->port.lock, flags);

	/*
	 * The N_TTY line discipline has problems such that in a बंद vs
	 * खोलो->hangup हाल this can be called after the final बंद so prevent
	 * that from happening क्रम now.
	 */
	अगर (hp->port.count <= 0) अणु
		spin_unlock_irqrestore(&hp->port.lock, flags);
		वापस;
	पूर्ण

	hp->port.count = 0;
	spin_unlock_irqrestore(&hp->port.lock, flags);
	tty_port_tty_set(&hp->port, शून्य);

	hp->n_outbuf = 0;

	अगर (hp->ops->notअगरier_hangup)
		hp->ops->notअगरier_hangup(hp, hp->data);
पूर्ण

/*
 * Push buffered अक्षरacters whether they were just recently buffered or रुकोing
 * on a blocked hypervisor.  Call this function with hp->lock held.
 */
अटल पूर्णांक hvc_push(काष्ठा hvc_काष्ठा *hp)
अणु
	पूर्णांक n;

	n = hp->ops->put_अक्षरs(hp->vtermno, hp->outbuf, hp->n_outbuf);
	अगर (n <= 0) अणु
		अगर (n == 0 || n == -EAGAIN) अणु
			hp->करो_wakeup = 1;
			वापस 0;
		पूर्ण
		/* throw away output on error; this happens when
		   there is no session connected to the vterm. */
		hp->n_outbuf = 0;
	पूर्ण अन्यथा
		hp->n_outbuf -= n;
	अगर (hp->n_outbuf > 0)
		स_हटाओ(hp->outbuf, hp->outbuf + n, hp->n_outbuf);
	अन्यथा
		hp->करो_wakeup = 1;

	वापस n;
पूर्ण

अटल पूर्णांक hvc_ग_लिखो(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा hvc_काष्ठा *hp = tty->driver_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक rsize, written = 0;

	/* This ग_लिखो was probably executed during a tty बंद. */
	अगर (!hp)
		वापस -EPIPE;

	/* FIXME what's this (unरक्षित) check क्रम? */
	अगर (hp->port.count <= 0)
		वापस -EIO;

	जबतक (count > 0) अणु
		पूर्णांक ret = 0;

		spin_lock_irqsave(&hp->lock, flags);

		rsize = hp->outbuf_size - hp->n_outbuf;

		अगर (rsize) अणु
			अगर (rsize > count)
				rsize = count;
			स_नकल(hp->outbuf + hp->n_outbuf, buf, rsize);
			count -= rsize;
			buf += rsize;
			hp->n_outbuf += rsize;
			written += rsize;
		पूर्ण

		अगर (hp->n_outbuf > 0)
			ret = hvc_push(hp);

		spin_unlock_irqrestore(&hp->lock, flags);

		अगर (!ret)
			अवरोध;

		अगर (count) अणु
			अगर (hp->n_outbuf > 0)
				hvc_flush(hp);
			cond_resched();
		पूर्ण
	पूर्ण

	/*
	 * Racy, but harmless, kick thपढ़ो अगर there is still pending data.
	 */
	अगर (hp->n_outbuf)
		hvc_kick();

	वापस written;
पूर्ण

/**
 * hvc_set_winsz() - Resize the hvc tty terminal winकरोw.
 * @work:	work काष्ठाure.
 *
 * The routine shall not be called within an atomic context because it
 * might sleep.
 *
 * Locking:	hp->lock
 */
अटल व्योम hvc_set_winsz(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hvc_काष्ठा *hp;
	अचिन्हित दीर्घ hvc_flags;
	काष्ठा tty_काष्ठा *tty;
	काष्ठा winsize ws;

	hp = container_of(work, काष्ठा hvc_काष्ठा, tty_resize);

	tty = tty_port_tty_get(&hp->port);
	अगर (!tty)
		वापस;

	spin_lock_irqsave(&hp->lock, hvc_flags);
	ws = hp->ws;
	spin_unlock_irqrestore(&hp->lock, hvc_flags);

	tty_करो_resize(tty, &ws);
	tty_kref_put(tty);
पूर्ण

/*
 * This is actually a contract between the driver and the tty layer outlining
 * how much ग_लिखो room the driver can guarantee will be sent OR BUFFERED.  This
 * driver MUST honor the वापस value.
 */
अटल पूर्णांक hvc_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा hvc_काष्ठा *hp = tty->driver_data;

	अगर (!hp)
		वापस 0;

	वापस hp->outbuf_size - hp->n_outbuf;
पूर्ण

अटल पूर्णांक hvc_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा hvc_काष्ठा *hp = tty->driver_data;

	अगर (!hp)
		वापस 0;
	वापस hp->n_outbuf;
पूर्ण

/*
 * समयout will vary between the MIN and MAX values defined here.  By शेष
 * and during console activity we will use a शेष MIN_TIMEOUT of 10.  When
 * the console is idle, we increase the समयout value on each pass through
 * msleep until we reach the max.  This may be noticeable as a brief (average
 * one second) delay on the console beक्रमe the console responds to input when
 * there has been no input क्रम some समय.
 */
#घोषणा MIN_TIMEOUT		(10)
#घोषणा MAX_TIMEOUT		(2000)
अटल u32 समयout = MIN_TIMEOUT;

/*
 * Maximum number of bytes to get from the console driver अगर hvc_poll is
 * called from driver (and can't sleep). Any more than this and we अवरोध
 * and start polling with khvcd. This value was derived from from an OpenBMC
 * console with the OPAL driver that results in about 0.25ms पूर्णांकerrupts off
 * latency.
 */
#घोषणा HVC_ATOMIC_READ_MAX	128

#घोषणा HVC_POLL_READ	0x00000001
#घोषणा HVC_POLL_WRITE	0x00000002

अटल पूर्णांक __hvc_poll(काष्ठा hvc_काष्ठा *hp, bool may_sleep)
अणु
	काष्ठा tty_काष्ठा *tty;
	पूर्णांक i, n, count, poll_mask = 0;
	अक्षर buf[N_INBUF] __ALIGNED__;
	अचिन्हित दीर्घ flags;
	पूर्णांक पढ़ो_total = 0;
	पूर्णांक written_total = 0;

	spin_lock_irqsave(&hp->lock, flags);

	/* Push pending ग_लिखोs */
	अगर (hp->n_outbuf > 0)
		written_total = hvc_push(hp);

	/* Reschedule us अगर still some ग_लिखो pending */
	अगर (hp->n_outbuf > 0) अणु
		poll_mask |= HVC_POLL_WRITE;
		/* If hvc_push() was not able to ग_लिखो, sleep a few msecs */
		समयout = (written_total) ? 0 : MIN_TIMEOUT;
	पूर्ण

	अगर (may_sleep) अणु
		spin_unlock_irqrestore(&hp->lock, flags);
		cond_resched();
		spin_lock_irqsave(&hp->lock, flags);
	पूर्ण

	/* No tty attached, just skip */
	tty = tty_port_tty_get(&hp->port);
	अगर (tty == शून्य)
		जाओ bail;

	/* Now check अगर we can get data (are we throttled ?) */
	अगर (tty_throttled(tty))
		जाओ out;

	/* If we aren't notifier driven and aren't throttled, we always
	 * request a reschedule
	 */
	अगर (!hp->irq_requested)
		poll_mask |= HVC_POLL_READ;

 पढ़ो_again:
	/* Read data अगर any */
	count = tty_buffer_request_room(&hp->port, N_INBUF);

	/* If flip is full, just reschedule a later पढ़ो */
	अगर (count == 0) अणु
		poll_mask |= HVC_POLL_READ;
		जाओ out;
	पूर्ण

	n = hp->ops->get_अक्षरs(hp->vtermno, buf, count);
	अगर (n <= 0) अणु
		/* Hangup the tty when disconnected from host */
		अगर (n == -EPIPE) अणु
			spin_unlock_irqrestore(&hp->lock, flags);
			tty_hangup(tty);
			spin_lock_irqsave(&hp->lock, flags);
		पूर्ण अन्यथा अगर ( n == -EAGAIN ) अणु
			/*
			 * Some back-ends can only ensure a certain min
			 * num of bytes पढ़ो, which may be > 'count'.
			 * Let the tty clear the flip buff to make room.
			 */
			poll_mask |= HVC_POLL_READ;
		पूर्ण
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < n; ++i) अणु
#अगर_घोषित CONFIG_MAGIC_SYSRQ
		अगर (hp->index == hvc_console.index) अणु
			/* Handle the SysRq Hack */
			/* XXX should support a sequence */
			अगर (buf[i] == '\x0f') अणु	/* ^O */
				/* अगर ^O is pressed again, reset
				 * sysrq_pressed and flip ^O अक्षर */
				sysrq_pressed = !sysrq_pressed;
				अगर (sysrq_pressed)
					जारी;
			पूर्ण अन्यथा अगर (sysrq_pressed) अणु
				handle_sysrq(buf[i]);
				sysrq_pressed = 0;
				जारी;
			पूर्ण
		पूर्ण
#पूर्ण_अगर /* CONFIG_MAGIC_SYSRQ */
		tty_insert_flip_अक्षर(&hp->port, buf[i], 0);
	पूर्ण
	पढ़ो_total += n;

	अगर (may_sleep) अणु
		/* Keep going until the flip is full */
		spin_unlock_irqrestore(&hp->lock, flags);
		cond_resched();
		spin_lock_irqsave(&hp->lock, flags);
		जाओ पढ़ो_again;
	पूर्ण अन्यथा अगर (पढ़ो_total < HVC_ATOMIC_READ_MAX) अणु
		/* Break and defer अगर it's a large पढ़ो in atomic */
		जाओ पढ़ो_again;
	पूर्ण

	/*
	 * Latency अवरोध, schedule another poll immediately.
	 */
	poll_mask |= HVC_POLL_READ;

 out:
	/* Wakeup ग_लिखो queue अगर necessary */
	अगर (hp->करो_wakeup) अणु
		hp->करो_wakeup = 0;
		tty_wakeup(tty);
	पूर्ण
 bail:
	spin_unlock_irqrestore(&hp->lock, flags);

	अगर (पढ़ो_total) अणु
		/* Activity is occurring, so reset the polling backoff value to
		   a minimum क्रम perक्रमmance. */
		समयout = MIN_TIMEOUT;

		tty_flip_buffer_push(&hp->port);
	पूर्ण
	tty_kref_put(tty);

	वापस poll_mask;
पूर्ण

पूर्णांक hvc_poll(काष्ठा hvc_काष्ठा *hp)
अणु
	वापस __hvc_poll(hp, false);
पूर्ण
EXPORT_SYMBOL_GPL(hvc_poll);

/**
 * __hvc_resize() - Update terminal winकरोw size inक्रमmation.
 * @hp:		HVC console poपूर्णांकer
 * @ws:		Terminal winकरोw size काष्ठाure
 *
 * Stores the specअगरied winकरोw size inक्रमmation in the hvc काष्ठाure of @hp.
 * The function schedule the tty resize update.
 *
 * Locking:	Locking मुक्त; the function MUST be called holding hp->lock
 */
व्योम __hvc_resize(काष्ठा hvc_काष्ठा *hp, काष्ठा winsize ws)
अणु
	hp->ws = ws;
	schedule_work(&hp->tty_resize);
पूर्ण
EXPORT_SYMBOL_GPL(__hvc_resize);

/*
 * This kthपढ़ो is either polling or पूर्णांकerrupt driven.  This is determined by
 * calling hvc_poll() who determines whether a console adapter support
 * पूर्णांकerrupts.
 */
अटल पूर्णांक khvcd(व्योम *unused)
अणु
	पूर्णांक poll_mask;
	काष्ठा hvc_काष्ठा *hp;

	set_मुक्तzable();
	करो अणु
		poll_mask = 0;
		hvc_kicked = 0;
		try_to_मुक्तze();
		wmb();
		अगर (!cpus_are_in_xmon()) अणु
			mutex_lock(&hvc_काष्ठाs_mutex);
			list_क्रम_each_entry(hp, &hvc_काष्ठाs, next) अणु
				poll_mask |= __hvc_poll(hp, true);
				cond_resched();
			पूर्ण
			mutex_unlock(&hvc_काष्ठाs_mutex);
		पूर्ण अन्यथा
			poll_mask |= HVC_POLL_READ;
		अगर (hvc_kicked)
			जारी;
		set_current_state(TASK_INTERRUPTIBLE);
		अगर (!hvc_kicked) अणु
			अगर (poll_mask == 0)
				schedule();
			अन्यथा अणु
				अचिन्हित दीर्घ j_समयout;

				अगर (समयout < MAX_TIMEOUT)
					समयout += (समयout >> 6) + 1;

				/*
				 * We करोn't use msleep_पूर्णांकerruptible otherwise
				 * "kick" will fail to wake us up
				 */
				j_समयout = msecs_to_jअगरfies(समयout) + 1;
				schedule_समयout_पूर्णांकerruptible(j_समयout);
			पूर्ण
		पूर्ण
		__set_current_state(TASK_RUNNING);
	पूर्ण जबतक (!kthपढ़ो_should_stop());

	वापस 0;
पूर्ण

अटल पूर्णांक hvc_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा hvc_काष्ठा *hp = tty->driver_data;

	अगर (!hp || !hp->ops->tiocmget)
		वापस -EINVAL;
	वापस hp->ops->tiocmget(hp);
पूर्ण

अटल पूर्णांक hvc_tiocmset(काष्ठा tty_काष्ठा *tty,
			अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा hvc_काष्ठा *hp = tty->driver_data;

	अगर (!hp || !hp->ops->tiocmset)
		वापस -EINVAL;
	वापस hp->ops->tiocmset(hp, set, clear);
पूर्ण

#अगर_घोषित CONFIG_CONSOLE_POLL
अटल पूर्णांक hvc_poll_init(काष्ठा tty_driver *driver, पूर्णांक line, अक्षर *options)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक hvc_poll_get_अक्षर(काष्ठा tty_driver *driver, पूर्णांक line)
अणु
	काष्ठा tty_काष्ठा *tty = driver->ttys[0];
	काष्ठा hvc_काष्ठा *hp = tty->driver_data;
	पूर्णांक n;
	अक्षर ch;

	n = hp->ops->get_अक्षरs(hp->vtermno, &ch, 1);

	अगर (n <= 0)
		वापस NO_POLL_CHAR;

	वापस ch;
पूर्ण

अटल व्योम hvc_poll_put_अक्षर(काष्ठा tty_driver *driver, पूर्णांक line, अक्षर ch)
अणु
	काष्ठा tty_काष्ठा *tty = driver->ttys[0];
	काष्ठा hvc_काष्ठा *hp = tty->driver_data;
	पूर्णांक n;

	करो अणु
		n = hp->ops->put_अक्षरs(hp->vtermno, &ch, 1);
	पूर्ण जबतक (n <= 0);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा tty_operations hvc_ops = अणु
	.install = hvc_install,
	.खोलो = hvc_खोलो,
	.बंद = hvc_बंद,
	.cleanup = hvc_cleanup,
	.ग_लिखो = hvc_ग_लिखो,
	.hangup = hvc_hangup,
	.unthrottle = hvc_unthrottle,
	.ग_लिखो_room = hvc_ग_लिखो_room,
	.अक्षरs_in_buffer = hvc_अक्षरs_in_buffer,
	.tiocmget = hvc_tiocmget,
	.tiocmset = hvc_tiocmset,
#अगर_घोषित CONFIG_CONSOLE_POLL
	.poll_init = hvc_poll_init,
	.poll_get_अक्षर = hvc_poll_get_अक्षर,
	.poll_put_अक्षर = hvc_poll_put_अक्षर,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा tty_port_operations hvc_port_ops = अणु
	.deकाष्ठा = hvc_port_deकाष्ठा,
पूर्ण;

काष्ठा hvc_काष्ठा *hvc_alloc(uपूर्णांक32_t vtermno, पूर्णांक data,
			     स्थिर काष्ठा hv_ops *ops,
			     पूर्णांक outbuf_size)
अणु
	काष्ठा hvc_काष्ठा *hp;
	पूर्णांक i;

	/* We रुको until a driver actually comes aदीर्घ */
	अगर (atomic_inc_not_zero(&hvc_needs_init)) अणु
		पूर्णांक err = hvc_init();
		अगर (err)
			वापस ERR_PTR(err);
	पूर्ण

	hp = kzalloc(ALIGN(माप(*hp), माप(दीर्घ)) + outbuf_size,
			GFP_KERNEL);
	अगर (!hp)
		वापस ERR_PTR(-ENOMEM);

	hp->vtermno = vtermno;
	hp->data = data;
	hp->ops = ops;
	hp->outbuf_size = outbuf_size;
	hp->outbuf = &((अक्षर *)hp)[ALIGN(माप(*hp), माप(दीर्घ))];

	tty_port_init(&hp->port);
	hp->port.ops = &hvc_port_ops;

	INIT_WORK(&hp->tty_resize, hvc_set_winsz);
	spin_lock_init(&hp->lock);
	mutex_lock(&hvc_काष्ठाs_mutex);

	/*
	 * find index to use:
	 * see अगर this vterm id matches one रेजिस्टरed क्रम console.
	 */
	क्रम (i=0; i < MAX_NR_HVC_CONSOLES; i++)
		अगर (vtermnos[i] == hp->vtermno &&
		    cons_ops[i] == hp->ops)
			अवरोध;

	अगर (i >= MAX_NR_HVC_CONSOLES) अणु

		/* find 'empty' slot क्रम console */
		क्रम (i = 0; i < MAX_NR_HVC_CONSOLES && vtermnos[i] != -1; i++) अणु
		पूर्ण

		/* no matching slot, just use a counter */
		अगर (i == MAX_NR_HVC_CONSOLES)
			i = ++last_hvc + MAX_NR_HVC_CONSOLES;
	पूर्ण

	hp->index = i;
	अगर (i < MAX_NR_HVC_CONSOLES) अणु
		cons_ops[i] = ops;
		vtermnos[i] = vtermno;
	पूर्ण

	list_add_tail(&(hp->next), &hvc_काष्ठाs);
	mutex_unlock(&hvc_काष्ठाs_mutex);

	/* check अगर we need to re-रेजिस्टर the kernel console */
	hvc_check_console(i);

	वापस hp;
पूर्ण
EXPORT_SYMBOL_GPL(hvc_alloc);

पूर्णांक hvc_हटाओ(काष्ठा hvc_काष्ठा *hp)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा tty_काष्ठा *tty;

	tty = tty_port_tty_get(&hp->port);

	console_lock();
	spin_lock_irqsave(&hp->lock, flags);
	अगर (hp->index < MAX_NR_HVC_CONSOLES) अणु
		vtermnos[hp->index] = -1;
		cons_ops[hp->index] = शून्य;
	पूर्ण

	/* Don't whack hp->irq because tty_hangup() will need to मुक्त the irq. */

	spin_unlock_irqrestore(&hp->lock, flags);
	console_unlock();

	/*
	 * We 'put' the instance that was grabbed when the kref instance
	 * was initialized using kref_init().  Let the last holder of this
	 * kref cause it to be हटाओd, which will probably be the tty_vhangup
	 * below.
	 */
	tty_port_put(&hp->port);

	/*
	 * This function call will स्वतः chain call hvc_hangup.
	 */
	अगर (tty) अणु
		tty_vhangup(tty);
		tty_kref_put(tty);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hvc_हटाओ);

/* Driver initialization: called as soon as someone uses hvc_alloc(). */
अटल पूर्णांक hvc_init(व्योम)
अणु
	काष्ठा tty_driver *drv;
	पूर्णांक err;

	/* We need more than hvc_count adapters due to hotplug additions. */
	drv = alloc_tty_driver(HVC_ALLOC_TTY_ADAPTERS);
	अगर (!drv) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	drv->driver_name = "hvc";
	drv->name = "hvc";
	drv->major = HVC_MAJOR;
	drv->minor_start = HVC_MINOR;
	drv->type = TTY_DRIVER_TYPE_SYSTEM;
	drv->init_termios = tty_std_termios;
	drv->flags = TTY_DRIVER_REAL_RAW | TTY_DRIVER_RESET_TERMIOS;
	tty_set_operations(drv, &hvc_ops);

	/* Always start the kthपढ़ो because there can be hotplug vty adapters
	 * added later. */
	hvc_task = kthपढ़ो_run(khvcd, शून्य, "khvcd");
	अगर (IS_ERR(hvc_task)) अणु
		prपूर्णांकk(KERN_ERR "Couldn't create kthread for console.\n");
		err = PTR_ERR(hvc_task);
		जाओ put_tty;
	पूर्ण

	err = tty_रेजिस्टर_driver(drv);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "Couldn't register hvc console driver\n");
		जाओ stop_thपढ़ो;
	पूर्ण

	/*
	 * Make sure tty is fully रेजिस्टरed beक्रमe allowing it to be
	 * found by hvc_console_device.
	 */
	smp_mb();
	hvc_driver = drv;
	वापस 0;

stop_thपढ़ो:
	kthपढ़ो_stop(hvc_task);
	hvc_task = शून्य;
put_tty:
	put_tty_driver(drv);
out:
	वापस err;
पूर्ण
