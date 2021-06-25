<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cs.c -- Kernel Card Services - core services
 *
 * The initial developer of the original code is David A. Hinds
 * <dahinds@users.sourceक्रमge.net>.  Portions created by David A. Hinds
 * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.
 *
 * (C) 1999		David A. Hinds
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/major.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समयr.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/device.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <यंत्र/irq.h>

#समावेश <pcmcia/ss.h>
#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/cisreg.h>
#समावेश <pcmcia/ds.h>
#समावेश "cs_internal.h"


/* Module parameters */

MODULE_AUTHOR("David Hinds <dahinds@users.sourceforge.net>");
MODULE_DESCRIPTION("Linux Kernel Card Services");
MODULE_LICENSE("GPL");

#घोषणा INT_MODULE_PARM(n, v) अटल पूर्णांक n = v; module_param(n, पूर्णांक, 0444)

INT_MODULE_PARM(setup_delay,	10);		/* centiseconds */
INT_MODULE_PARM(resume_delay,	20);		/* centiseconds */
INT_MODULE_PARM(shutकरोwn_delay,	3);		/* centiseconds */
INT_MODULE_PARM(vcc_settle,	40);		/* centiseconds */
INT_MODULE_PARM(reset_समय,	10);		/* usecs */
INT_MODULE_PARM(unreset_delay,	10);		/* centiseconds */
INT_MODULE_PARM(unreset_check,	10);		/* centiseconds */
INT_MODULE_PARM(unreset_limit,	30);		/* unreset_check's */

/* Access speed क्रम attribute memory winकरोws */
INT_MODULE_PARM(cis_speed,	300);		/* ns */


socket_state_t dead_socket = अणु
	.csc_mask	= SS_DETECT,
पूर्ण;
EXPORT_SYMBOL(dead_socket);


/* List of all sockets, रक्षित by a rwsem */
LIST_HEAD(pcmcia_socket_list);
EXPORT_SYMBOL(pcmcia_socket_list);

DECLARE_RWSEM(pcmcia_socket_list_rwsem);
EXPORT_SYMBOL(pcmcia_socket_list_rwsem);


काष्ठा pcmcia_socket *pcmcia_get_socket(काष्ठा pcmcia_socket *skt)
अणु
	काष्ठा device *dev = get_device(&skt->dev);
	अगर (!dev)
		वापस शून्य;
	वापस dev_get_drvdata(dev);
पूर्ण
EXPORT_SYMBOL(pcmcia_get_socket);


व्योम pcmcia_put_socket(काष्ठा pcmcia_socket *skt)
अणु
	put_device(&skt->dev);
पूर्ण
EXPORT_SYMBOL(pcmcia_put_socket);


अटल व्योम pcmcia_release_socket(काष्ठा device *dev)
अणु
	काष्ठा pcmcia_socket *socket = dev_get_drvdata(dev);

	complete(&socket->socket_released);
पूर्ण

अटल पूर्णांक pccardd(व्योम *__skt);

/**
 * pcmcia_रेजिस्टर_socket - add a new pcmcia socket device
 * @socket: the &socket to रेजिस्टर
 */
पूर्णांक pcmcia_रेजिस्टर_socket(काष्ठा pcmcia_socket *socket)
अणु
	काष्ठा task_काष्ठा *tsk;
	पूर्णांक ret;

	अगर (!socket || !socket->ops || !socket->dev.parent || !socket->resource_ops)
		वापस -EINVAL;

	dev_dbg(&socket->dev, "pcmcia_register_socket(0x%p)\n", socket->ops);

	/* try to obtain a socket number [yes, it माला_लो ugly अगर we
	 * रेजिस्टर more than 2^माप(अचिन्हित पूर्णांक) pcmcia
	 * sockets... but the socket number is deprecated
	 * anyways, so I करोn't care] */
	करोwn_ग_लिखो(&pcmcia_socket_list_rwsem);
	अगर (list_empty(&pcmcia_socket_list))
		socket->sock = 0;
	अन्यथा अणु
		अचिन्हित पूर्णांक found, i = 1;
		काष्ठा pcmcia_socket *पंचांगp;
		करो अणु
			found = 1;
			list_क्रम_each_entry(पंचांगp, &pcmcia_socket_list, socket_list) अणु
				अगर (पंचांगp->sock == i)
					found = 0;
			पूर्ण
			i++;
		पूर्ण जबतक (!found);
		socket->sock = i - 1;
	पूर्ण
	list_add_tail(&socket->socket_list, &pcmcia_socket_list);
	up_ग_लिखो(&pcmcia_socket_list_rwsem);

#अगर_अघोषित CONFIG_CARDBUS
	/*
	 * If we करो not support Cardbus, ensure that
	 * the Cardbus socket capability is disabled.
	 */
	socket->features &= ~SS_CAP_CARDBUS;
#पूर्ण_अगर

	/* set proper values in socket->dev */
	dev_set_drvdata(&socket->dev, socket);
	socket->dev.class = &pcmcia_socket_class;
	dev_set_name(&socket->dev, "pcmcia_socket%u", socket->sock);

	/* base address = 0, map = 0 */
	socket->cis_mem.flags = 0;
	socket->cis_mem.speed = cis_speed;

	INIT_LIST_HEAD(&socket->cis_cache);

	init_completion(&socket->socket_released);
	init_completion(&socket->thपढ़ो_करोne);
	mutex_init(&socket->skt_mutex);
	mutex_init(&socket->ops_mutex);
	spin_lock_init(&socket->thपढ़ो_lock);

	अगर (socket->resource_ops->init) अणु
		mutex_lock(&socket->ops_mutex);
		ret = socket->resource_ops->init(socket);
		mutex_unlock(&socket->ops_mutex);
		अगर (ret)
			जाओ err;
	पूर्ण

	tsk = kthपढ़ो_run(pccardd, socket, "pccardd");
	अगर (IS_ERR(tsk)) अणु
		ret = PTR_ERR(tsk);
		जाओ err;
	पूर्ण

	रुको_क्रम_completion(&socket->thपढ़ो_करोne);
	अगर (!socket->thपढ़ो) अणु
		dev_warn(&socket->dev,
			 "PCMCIA: warning: socket thread did not start\n");
		वापस -EIO;
	पूर्ण

	pcmcia_parse_events(socket, SS_DETECT);

	/*
	 * Let's try to get the PCMCIA module क्रम 16-bit PCMCIA support.
	 * If it fails, it करोesn't matter -- we still have 32-bit CardBus
	 * support to offer, so this is not a failure mode.
	 */
	request_module_noरुको("pcmcia");

	वापस 0;

 err:
	करोwn_ग_लिखो(&pcmcia_socket_list_rwsem);
	list_del(&socket->socket_list);
	up_ग_लिखो(&pcmcia_socket_list_rwsem);
	वापस ret;
पूर्ण /* pcmcia_रेजिस्टर_socket */
EXPORT_SYMBOL(pcmcia_रेजिस्टर_socket);


/**
 * pcmcia_unरेजिस्टर_socket - हटाओ a pcmcia socket device
 * @socket: the &socket to unरेजिस्टर
 */
व्योम pcmcia_unरेजिस्टर_socket(काष्ठा pcmcia_socket *socket)
अणु
	अगर (!socket)
		वापस;

	dev_dbg(&socket->dev, "pcmcia_unregister_socket(0x%p)\n", socket->ops);

	अगर (socket->thपढ़ो)
		kthपढ़ो_stop(socket->thपढ़ो);

	/* हटाओ from our own list */
	करोwn_ग_लिखो(&pcmcia_socket_list_rwsem);
	list_del(&socket->socket_list);
	up_ग_लिखो(&pcmcia_socket_list_rwsem);

	/* रुको क्रम sysfs to drop all references */
	अगर (socket->resource_ops->निकास) अणु
		mutex_lock(&socket->ops_mutex);
		socket->resource_ops->निकास(socket);
		mutex_unlock(&socket->ops_mutex);
	पूर्ण
	रुको_क्रम_completion(&socket->socket_released);
पूर्ण /* pcmcia_unरेजिस्टर_socket */
EXPORT_SYMBOL(pcmcia_unरेजिस्टर_socket);


काष्ठा pcmcia_socket *pcmcia_get_socket_by_nr(अचिन्हित पूर्णांक nr)
अणु
	काष्ठा pcmcia_socket *s;

	करोwn_पढ़ो(&pcmcia_socket_list_rwsem);
	list_क्रम_each_entry(s, &pcmcia_socket_list, socket_list)
		अगर (s->sock == nr) अणु
			up_पढ़ो(&pcmcia_socket_list_rwsem);
			वापस s;
		पूर्ण
	up_पढ़ो(&pcmcia_socket_list_rwsem);

	वापस शून्य;

पूर्ण
EXPORT_SYMBOL(pcmcia_get_socket_by_nr);

अटल पूर्णांक socket_reset(काष्ठा pcmcia_socket *skt)
अणु
	पूर्णांक status, i;

	dev_dbg(&skt->dev, "reset\n");

	skt->socket.flags |= SS_OUTPUT_ENA | SS_RESET;
	skt->ops->set_socket(skt, &skt->socket);
	udelay((दीर्घ)reset_समय);

	skt->socket.flags &= ~SS_RESET;
	skt->ops->set_socket(skt, &skt->socket);

	msleep(unreset_delay * 10);
	क्रम (i = 0; i < unreset_limit; i++) अणु
		skt->ops->get_status(skt, &status);

		अगर (!(status & SS_DETECT))
			वापस -ENODEV;

		अगर (status & SS_READY)
			वापस 0;

		msleep(unreset_check * 10);
	पूर्ण

	dev_err(&skt->dev, "time out after reset\n");
	वापस -ETIMEDOUT;
पूर्ण

/*
 * socket_setup() and socket_shutकरोwn() are called by the मुख्य event handler
 * when card insertion and removal events are received.
 * socket_setup() turns on socket घातer and resets the socket, in two stages.
 * socket_shutकरोwn() unconfigures a socket and turns off socket घातer.
 */
अटल व्योम socket_shutकरोwn(काष्ठा pcmcia_socket *s)
अणु
	पूर्णांक status;

	dev_dbg(&s->dev, "shutdown\n");

	अगर (s->callback)
		s->callback->हटाओ(s);

	mutex_lock(&s->ops_mutex);
	s->state &= SOCKET_INUSE | SOCKET_PRESENT;
	msleep(shutकरोwn_delay * 10);
	s->state &= SOCKET_INUSE;

	/* Blank out the socket state */
	s->socket = dead_socket;
	s->ops->init(s);
	s->ops->set_socket(s, &s->socket);
	s->lock_count = 0;
	kमुक्त(s->fake_cis);
	s->fake_cis = शून्य;
	s->functions = 0;

	/* From here on we can be sure that only we (that is, the
	 * pccardd thपढ़ो) accesses this socket, and all (16-bit)
	 * PCMCIA पूर्णांकeractions are gone. Thereक्रमe, release
	 * ops_mutex so that we करोn't get a sysfs-related lockdep
	 * warning.
	 */
	mutex_unlock(&s->ops_mutex);

#अगर_घोषित CONFIG_CARDBUS
	cb_मुक्त(s);
#पूर्ण_अगर

	/* give socket some समय to घातer करोwn */
	msleep(100);

	s->ops->get_status(s, &status);
	अगर (status & SS_POWERON) अणु
		dev_err(&s->dev,
			"*** DANGER *** unable to remove socket power\n");
	पूर्ण

	s->state &= ~SOCKET_INUSE;
पूर्ण

अटल पूर्णांक socket_setup(काष्ठा pcmcia_socket *skt, पूर्णांक initial_delay)
अणु
	पूर्णांक status, i;

	dev_dbg(&skt->dev, "setup\n");

	skt->ops->get_status(skt, &status);
	अगर (!(status & SS_DETECT))
		वापस -ENODEV;

	msleep(initial_delay * 10);

	क्रम (i = 0; i < 100; i++) अणु
		skt->ops->get_status(skt, &status);
		अगर (!(status & SS_DETECT))
			वापस -ENODEV;

		अगर (!(status & SS_PENDING))
			अवरोध;

		msleep(100);
	पूर्ण

	अगर (status & SS_PENDING) अणु
		dev_err(&skt->dev, "voltage interrogation timed out\n");
		वापस -ETIMEDOUT;
	पूर्ण

	अगर (status & SS_CARDBUS) अणु
		अगर (!(skt->features & SS_CAP_CARDBUS)) अणु
			dev_err(&skt->dev, "cardbus cards are not supported\n");
			वापस -EINVAL;
		पूर्ण
		skt->state |= SOCKET_CARDBUS;
	पूर्ण अन्यथा
		skt->state &= ~SOCKET_CARDBUS;

	/*
	 * Decode the card voltage requirements, and apply घातer to the card.
	 */
	अगर (status & SS_3VCARD)
		skt->socket.Vcc = skt->socket.Vpp = 33;
	अन्यथा अगर (!(status & SS_XVCARD))
		skt->socket.Vcc = skt->socket.Vpp = 50;
	अन्यथा अणु
		dev_err(&skt->dev, "unsupported voltage key\n");
		वापस -EIO;
	पूर्ण

	अगर (skt->घातer_hook)
		skt->घातer_hook(skt, HOOK_POWER_PRE);

	skt->socket.flags = 0;
	skt->ops->set_socket(skt, &skt->socket);

	/*
	 * Wait "vcc_settle" क्रम the supply to stabilise.
	 */
	msleep(vcc_settle * 10);

	skt->ops->get_status(skt, &status);
	अगर (!(status & SS_POWERON)) अणु
		dev_err(&skt->dev, "unable to apply power\n");
		वापस -EIO;
	पूर्ण

	status = socket_reset(skt);

	अगर (skt->घातer_hook)
		skt->घातer_hook(skt, HOOK_POWER_POST);

	वापस status;
पूर्ण

/*
 * Handle card insertion.  Setup the socket, reset the card,
 * and then tell the rest of PCMCIA that a card is present.
 */
अटल पूर्णांक socket_insert(काष्ठा pcmcia_socket *skt)
अणु
	पूर्णांक ret;

	dev_dbg(&skt->dev, "insert\n");

	mutex_lock(&skt->ops_mutex);
	अगर (skt->state & SOCKET_INUSE) अणु
		mutex_unlock(&skt->ops_mutex);
		वापस -EINVAL;
	पूर्ण
	skt->state |= SOCKET_INUSE;

	ret = socket_setup(skt, setup_delay);
	अगर (ret == 0) अणु
		skt->state |= SOCKET_PRESENT;

		dev_notice(&skt->dev, "pccard: %s card inserted into slot %d\n",
			   (skt->state & SOCKET_CARDBUS) ? "CardBus" : "PCMCIA",
			   skt->sock);

#अगर_घोषित CONFIG_CARDBUS
		अगर (skt->state & SOCKET_CARDBUS) अणु
			cb_alloc(skt);
			skt->state |= SOCKET_CARDBUS_CONFIG;
		पूर्ण
#पूर्ण_अगर
		dev_dbg(&skt->dev, "insert done\n");
		mutex_unlock(&skt->ops_mutex);

		अगर (!(skt->state & SOCKET_CARDBUS) && (skt->callback))
			skt->callback->add(skt);
	पूर्ण अन्यथा अणु
		mutex_unlock(&skt->ops_mutex);
		socket_shutकरोwn(skt);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक socket_suspend(काष्ठा pcmcia_socket *skt)
अणु
	अगर ((skt->state & SOCKET_SUSPEND) && !(skt->state & SOCKET_IN_RESUME))
		वापस -EBUSY;

	mutex_lock(&skt->ops_mutex);
	/* store state on first suspend, but not after spurious wakeups */
	अगर (!(skt->state & SOCKET_IN_RESUME))
		skt->suspended_state = skt->state;

	skt->socket = dead_socket;
	skt->ops->set_socket(skt, &skt->socket);
	अगर (skt->ops->suspend)
		skt->ops->suspend(skt);
	skt->state |= SOCKET_SUSPEND;
	skt->state &= ~SOCKET_IN_RESUME;
	mutex_unlock(&skt->ops_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक socket_early_resume(काष्ठा pcmcia_socket *skt)
अणु
	mutex_lock(&skt->ops_mutex);
	skt->socket = dead_socket;
	skt->ops->init(skt);
	skt->ops->set_socket(skt, &skt->socket);
	अगर (skt->state & SOCKET_PRESENT)
		skt->resume_status = socket_setup(skt, resume_delay);
	skt->state |= SOCKET_IN_RESUME;
	mutex_unlock(&skt->ops_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक socket_late_resume(काष्ठा pcmcia_socket *skt)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&skt->ops_mutex);
	skt->state &= ~(SOCKET_SUSPEND | SOCKET_IN_RESUME);
	mutex_unlock(&skt->ops_mutex);

	अगर (!(skt->state & SOCKET_PRESENT)) अणु
		ret = socket_insert(skt);
		अगर (ret == -ENODEV)
			ret = 0;
		वापस ret;
	पूर्ण

	अगर (skt->resume_status) अणु
		socket_shutकरोwn(skt);
		वापस 0;
	पूर्ण

	अगर (skt->suspended_state != skt->state) अणु
		dev_dbg(&skt->dev,
			"suspend state 0x%x != resume state 0x%x\n",
			skt->suspended_state, skt->state);

		socket_shutकरोwn(skt);
		वापस socket_insert(skt);
	पूर्ण

	अगर (!(skt->state & SOCKET_CARDBUS) && (skt->callback))
		ret = skt->callback->early_resume(skt);
	वापस ret;
पूर्ण

/*
 * Finalize the resume. In हाल of a cardbus socket, we have
 * to rebind the devices as we can't be certain that it has been
 * replaced, or not.
 */
अटल पूर्णांक socket_complete_resume(काष्ठा pcmcia_socket *skt)
अणु
	पूर्णांक ret = 0;
#अगर_घोषित CONFIG_CARDBUS
	अगर (skt->state & SOCKET_CARDBUS) अणु
		/* We can't be sure the CardBus card is the same
		 * as the one previously inserted. Thereक्रमe, हटाओ
		 * and re-add... */
		cb_मुक्त(skt);
		ret = cb_alloc(skt);
		अगर (ret)
			cb_मुक्त(skt);
	पूर्ण
#पूर्ण_अगर
	वापस ret;
पूर्ण

/*
 * Resume a socket.  If a card is present, verअगरy its CIS against
 * our cached copy.  If they are dअगरferent, the card has been
 * replaced, and we need to tell the drivers.
 */
अटल पूर्णांक socket_resume(काष्ठा pcmcia_socket *skt)
अणु
	पूर्णांक err;
	अगर (!(skt->state & SOCKET_SUSPEND))
		वापस -EBUSY;

	socket_early_resume(skt);
	err = socket_late_resume(skt);
	अगर (!err)
		err = socket_complete_resume(skt);
	वापस err;
पूर्ण

अटल व्योम socket_हटाओ(काष्ठा pcmcia_socket *skt)
अणु
	dev_notice(&skt->dev, "pccard: card ejected from slot %d\n", skt->sock);
	socket_shutकरोwn(skt);
पूर्ण

/*
 * Process a socket card detect status change.
 *
 * If we करोn't have a card alपढ़ोy present, delay the detect event क्रम
 * about 20ms (to be on the safe side) beक्रमe पढ़ोing the socket status.
 *
 * Some i82365-based प्रणालीs send multiple SS_DETECT events during card
 * insertion, and the "card present" status bit seems to bounce.  This
 * will probably be true with GPIO-based card detection प्रणालीs after
 * the product has aged.
 */
अटल व्योम socket_detect_change(काष्ठा pcmcia_socket *skt)
अणु
	अगर (!(skt->state & SOCKET_SUSPEND)) अणु
		पूर्णांक status;

		अगर (!(skt->state & SOCKET_PRESENT))
			msleep(20);

		skt->ops->get_status(skt, &status);
		अगर ((skt->state & SOCKET_PRESENT) &&
		     !(status & SS_DETECT))
			socket_हटाओ(skt);
		अगर (!(skt->state & SOCKET_PRESENT) &&
		    (status & SS_DETECT))
			socket_insert(skt);
	पूर्ण
पूर्ण

अटल पूर्णांक pccardd(व्योम *__skt)
अणु
	काष्ठा pcmcia_socket *skt = __skt;
	पूर्णांक ret;

	skt->thपढ़ो = current;
	skt->socket = dead_socket;
	skt->ops->init(skt);
	skt->ops->set_socket(skt, &skt->socket);

	/* रेजिस्टर with the device core */
	ret = device_रेजिस्टर(&skt->dev);
	अगर (ret) अणु
		dev_warn(&skt->dev, "PCMCIA: unable to register socket\n");
		skt->thपढ़ो = शून्य;
		complete(&skt->thपढ़ो_करोne);
		वापस 0;
	पूर्ण
	ret = pccard_sysfs_add_socket(&skt->dev);
	अगर (ret)
		dev_warn(&skt->dev, "err %d adding socket attributes\n", ret);

	complete(&skt->thपढ़ो_करोne);

	/* रुको क्रम userspace to catch up */
	msleep(250);

	set_मुक्तzable();
	क्रम (;;) अणु
		अचिन्हित दीर्घ flags;
		अचिन्हित पूर्णांक events;
		अचिन्हित पूर्णांक sysfs_events;

		spin_lock_irqsave(&skt->thपढ़ो_lock, flags);
		events = skt->thपढ़ो_events;
		skt->thपढ़ो_events = 0;
		sysfs_events = skt->sysfs_events;
		skt->sysfs_events = 0;
		spin_unlock_irqrestore(&skt->thपढ़ो_lock, flags);

		mutex_lock(&skt->skt_mutex);
		अगर (events & SS_DETECT)
			socket_detect_change(skt);

		अगर (sysfs_events) अणु
			अगर (sysfs_events & PCMCIA_UEVENT_EJECT)
				socket_हटाओ(skt);
			अगर (sysfs_events & PCMCIA_UEVENT_INSERT)
				socket_insert(skt);
			अगर ((sysfs_events & PCMCIA_UEVENT_SUSPEND) &&
				!(skt->state & SOCKET_CARDBUS)) अणु
				अगर (skt->callback)
					ret = skt->callback->suspend(skt);
				अन्यथा
					ret = 0;
				अगर (!ret) अणु
					socket_suspend(skt);
					msleep(100);
				पूर्ण
			पूर्ण
			अगर ((sysfs_events & PCMCIA_UEVENT_RESUME) &&
				!(skt->state & SOCKET_CARDBUS)) अणु
				ret = socket_resume(skt);
				अगर (!ret && skt->callback)
					skt->callback->resume(skt);
			पूर्ण
			अगर ((sysfs_events & PCMCIA_UEVENT_REQUERY) &&
				!(skt->state & SOCKET_CARDBUS)) अणु
				अगर (!ret && skt->callback)
					skt->callback->requery(skt);
			पूर्ण
		पूर्ण
		mutex_unlock(&skt->skt_mutex);

		अगर (events || sysfs_events)
			जारी;

		अगर (kthपढ़ो_should_stop())
			अवरोध;

		set_current_state(TASK_INTERRUPTIBLE);

		schedule();

		/* make sure we are running */
		__set_current_state(TASK_RUNNING);

		try_to_मुक्तze();
	पूर्ण

	/* shut करोwn socket, अगर a device is still present */
	अगर (skt->state & SOCKET_PRESENT) अणु
		mutex_lock(&skt->skt_mutex);
		socket_हटाओ(skt);
		mutex_unlock(&skt->skt_mutex);
	पूर्ण

	/* हटाओ from the device core */
	pccard_sysfs_हटाओ_socket(&skt->dev);
	device_unरेजिस्टर(&skt->dev);

	वापस 0;
पूर्ण

/*
 * Yenta (at least) probes पूर्णांकerrupts beक्रमe रेजिस्टरing the socket and
 * starting the handler thपढ़ो.
 */
व्योम pcmcia_parse_events(काष्ठा pcmcia_socket *s, u_पूर्णांक events)
अणु
	अचिन्हित दीर्घ flags;
	dev_dbg(&s->dev, "parse_events: events %08x\n", events);
	अगर (s->thपढ़ो) अणु
		spin_lock_irqsave(&s->thपढ़ो_lock, flags);
		s->thपढ़ो_events |= events;
		spin_unlock_irqrestore(&s->thपढ़ो_lock, flags);

		wake_up_process(s->thपढ़ो);
	पूर्ण
पूर्ण /* pcmcia_parse_events */
EXPORT_SYMBOL(pcmcia_parse_events);

/**
 * pcmcia_parse_uevents() - tell pccardd to issue manual commands
 * @s:		the PCMCIA socket we wan't to command
 * @events:	events to pass to pccardd
 *
 * userspace-issued insert, eject, suspend and resume commands must be
 * handled by pccardd to aव्योम any sysfs-related deadlocks. Valid events
 * are PCMCIA_UEVENT_EJECT (क्रम eject), PCMCIA_UEVENT__INSERT (क्रम insert),
 * PCMCIA_UEVENT_RESUME (क्रम resume), PCMCIA_UEVENT_SUSPEND (क्रम suspend)
 * and PCMCIA_UEVENT_REQUERY (क्रम re-querying the PCMCIA card).
 */
व्योम pcmcia_parse_uevents(काष्ठा pcmcia_socket *s, u_पूर्णांक events)
अणु
	अचिन्हित दीर्घ flags;
	dev_dbg(&s->dev, "parse_uevents: events %08x\n", events);
	अगर (s->thपढ़ो) अणु
		spin_lock_irqsave(&s->thपढ़ो_lock, flags);
		s->sysfs_events |= events;
		spin_unlock_irqrestore(&s->thपढ़ो_lock, flags);

		wake_up_process(s->thपढ़ो);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(pcmcia_parse_uevents);


/* रेजिस्टर pcmcia_callback */
पूर्णांक pccard_रेजिस्टर_pcmcia(काष्ठा pcmcia_socket *s, काष्ठा pcmcia_callback *c)
अणु
	पूर्णांक ret = 0;

	/* s->skt_mutex also protects s->callback */
	mutex_lock(&s->skt_mutex);

	अगर (c) अणु
		/* registration */
		अगर (s->callback) अणु
			ret = -EBUSY;
			जाओ err;
		पूर्ण

		s->callback = c;

		अगर ((s->state & (SOCKET_PRESENT|SOCKET_CARDBUS)) == SOCKET_PRESENT)
			s->callback->add(s);
	पूर्ण अन्यथा
		s->callback = शून्य;
 err:
	mutex_unlock(&s->skt_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(pccard_रेजिस्टर_pcmcia);


/* I'm not sure which "reset" function this is supposed to use,
 * but क्रम now, it uses the low-level पूर्णांकerface's reset, not the
 * CIS रेजिस्टर.
 */

पूर्णांक pcmcia_reset_card(काष्ठा pcmcia_socket *skt)
अणु
	पूर्णांक ret;

	dev_dbg(&skt->dev, "resetting socket\n");

	mutex_lock(&skt->skt_mutex);
	करो अणु
		अगर (!(skt->state & SOCKET_PRESENT)) अणु
			dev_dbg(&skt->dev, "can't reset, not present\n");
			ret = -ENODEV;
			अवरोध;
		पूर्ण
		अगर (skt->state & SOCKET_SUSPEND) अणु
			dev_dbg(&skt->dev, "can't reset, suspended\n");
			ret = -EBUSY;
			अवरोध;
		पूर्ण
		अगर (skt->state & SOCKET_CARDBUS) अणु
			dev_dbg(&skt->dev, "can't reset, is cardbus\n");
			ret = -EPERM;
			अवरोध;
		पूर्ण

		अगर (skt->callback)
			skt->callback->suspend(skt);
		mutex_lock(&skt->ops_mutex);
		ret = socket_reset(skt);
		mutex_unlock(&skt->ops_mutex);
		अगर ((ret == 0) && (skt->callback))
			skt->callback->resume(skt);

		ret = 0;
	पूर्ण जबतक (0);
	mutex_unlock(&skt->skt_mutex);

	वापस ret;
पूर्ण /* reset_card */
EXPORT_SYMBOL(pcmcia_reset_card);


अटल पूर्णांक pcmcia_socket_uevent(काष्ठा device *dev,
				काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा pcmcia_socket *s = container_of(dev, काष्ठा pcmcia_socket, dev);

	अगर (add_uevent_var(env, "SOCKET_NO=%u", s->sock))
		वापस -ENOMEM;

	वापस 0;
पूर्ण


अटल काष्ठा completion pcmcia_unload;

अटल व्योम pcmcia_release_socket_class(काष्ठा class *data)
अणु
	complete(&pcmcia_unload);
पूर्ण


#अगर_घोषित CONFIG_PM

अटल पूर्णांक __pcmcia_pm_op(काष्ठा device *dev,
			  पूर्णांक (*callback) (काष्ठा pcmcia_socket *skt))
अणु
	काष्ठा pcmcia_socket *s = container_of(dev, काष्ठा pcmcia_socket, dev);
	पूर्णांक ret;

	mutex_lock(&s->skt_mutex);
	ret = callback(s);
	mutex_unlock(&s->skt_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक pcmcia_socket_dev_suspend_noirq(काष्ठा device *dev)
अणु
	वापस __pcmcia_pm_op(dev, socket_suspend);
पूर्ण

अटल पूर्णांक pcmcia_socket_dev_resume_noirq(काष्ठा device *dev)
अणु
	वापस __pcmcia_pm_op(dev, socket_early_resume);
पूर्ण

अटल पूर्णांक __used pcmcia_socket_dev_resume(काष्ठा device *dev)
अणु
	वापस __pcmcia_pm_op(dev, socket_late_resume);
पूर्ण

अटल व्योम __used pcmcia_socket_dev_complete(काष्ठा device *dev)
अणु
	WARN(__pcmcia_pm_op(dev, socket_complete_resume),
		"failed to complete resume");
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops pcmcia_socket_pm_ops = अणु
	/* dev_resume may be called with IRQs enabled */
	SET_SYSTEM_SLEEP_PM_OPS(शून्य,
				pcmcia_socket_dev_resume)

	/* late suspend must be called with IRQs disabled */
	.suspend_noirq = pcmcia_socket_dev_suspend_noirq,
	.मुक्तze_noirq = pcmcia_socket_dev_suspend_noirq,
	.घातeroff_noirq = pcmcia_socket_dev_suspend_noirq,

	/* early resume must be called with IRQs disabled */
	.resume_noirq = pcmcia_socket_dev_resume_noirq,
	.thaw_noirq = pcmcia_socket_dev_resume_noirq,
	.restore_noirq = pcmcia_socket_dev_resume_noirq,
	.complete = pcmcia_socket_dev_complete,
पूर्ण;

#घोषणा PCMCIA_SOCKET_CLASS_PM_OPS (&pcmcia_socket_pm_ops)

#अन्यथा /* CONFIG_PM */

#घोषणा PCMCIA_SOCKET_CLASS_PM_OPS शून्य

#पूर्ण_अगर /* CONFIG_PM */

काष्ठा class pcmcia_socket_class = अणु
	.name = "pcmcia_socket",
	.dev_uevent = pcmcia_socket_uevent,
	.dev_release = pcmcia_release_socket,
	.class_release = pcmcia_release_socket_class,
	.pm = PCMCIA_SOCKET_CLASS_PM_OPS,
पूर्ण;
EXPORT_SYMBOL(pcmcia_socket_class);


अटल पूर्णांक __init init_pcmcia_cs(व्योम)
अणु
	init_completion(&pcmcia_unload);
	वापस class_रेजिस्टर(&pcmcia_socket_class);
पूर्ण

अटल व्योम __निकास निकास_pcmcia_cs(व्योम)
अणु
	class_unरेजिस्टर(&pcmcia_socket_class);
	रुको_क्रम_completion(&pcmcia_unload);
पूर्ण

subsys_initcall(init_pcmcia_cs);
module_निकास(निकास_pcmcia_cs);

