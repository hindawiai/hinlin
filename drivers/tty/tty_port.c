<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Tty port functions
 */

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/serial.h>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/रुको.h>
#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/serdev.h>
#समावेश "tty.h"

अटल पूर्णांक tty_port_शेष_receive_buf(काष्ठा tty_port *port,
					स्थिर अचिन्हित अक्षर *p,
					स्थिर अचिन्हित अक्षर *f, माप_प्रकार count)
अणु
	पूर्णांक ret;
	काष्ठा tty_काष्ठा *tty;
	काष्ठा tty_ldisc *disc;

	tty = READ_ONCE(port->itty);
	अगर (!tty)
		वापस 0;

	disc = tty_ldisc_ref(tty);
	अगर (!disc)
		वापस 0;

	ret = tty_ldisc_receive_buf(disc, p, (अक्षर *)f, count);

	tty_ldisc_deref(disc);

	वापस ret;
पूर्ण

अटल व्योम tty_port_शेष_wakeup(काष्ठा tty_port *port)
अणु
	काष्ठा tty_काष्ठा *tty = tty_port_tty_get(port);

	अगर (tty) अणु
		tty_wakeup(tty);
		tty_kref_put(tty);
	पूर्ण
पूर्ण

स्थिर काष्ठा tty_port_client_operations tty_port_शेष_client_ops = अणु
	.receive_buf = tty_port_शेष_receive_buf,
	.ग_लिखो_wakeup = tty_port_शेष_wakeup,
पूर्ण;
EXPORT_SYMBOL_GPL(tty_port_शेष_client_ops);

व्योम tty_port_init(काष्ठा tty_port *port)
अणु
	स_रखो(port, 0, माप(*port));
	tty_buffer_init(port);
	init_रुकोqueue_head(&port->खोलो_रुको);
	init_रुकोqueue_head(&port->delta_msr_रुको);
	mutex_init(&port->mutex);
	mutex_init(&port->buf_mutex);
	spin_lock_init(&port->lock);
	port->बंद_delay = (50 * HZ) / 100;
	port->closing_रुको = (3000 * HZ) / 100;
	port->client_ops = &tty_port_शेष_client_ops;
	kref_init(&port->kref);
पूर्ण
EXPORT_SYMBOL(tty_port_init);

/**
 * tty_port_link_device - link tty and tty_port
 * @port: tty_port of the device
 * @driver: tty_driver क्रम this device
 * @index: index of the tty
 *
 * Provide the tty layer with a link from a tty (specअगरied by @index) to a
 * tty_port (@port). Use this only अगर neither tty_port_रेजिस्टर_device nor
 * tty_port_install is used in the driver. If used, this has to be called beक्रमe
 * tty_रेजिस्टर_driver.
 */
व्योम tty_port_link_device(काष्ठा tty_port *port,
		काष्ठा tty_driver *driver, अचिन्हित index)
अणु
	अगर (WARN_ON(index >= driver->num))
		वापस;
	driver->ports[index] = port;
पूर्ण
EXPORT_SYMBOL_GPL(tty_port_link_device);

/**
 * tty_port_रेजिस्टर_device - रेजिस्टर tty device
 * @port: tty_port of the device
 * @driver: tty_driver क्रम this device
 * @index: index of the tty
 * @device: parent अगर exists, otherwise शून्य
 *
 * It is the same as tty_रेजिस्टर_device except the provided @port is linked to
 * a concrete tty specअगरied by @index. Use this or tty_port_install (or both).
 * Call tty_port_link_device as a last resort.
 */
काष्ठा device *tty_port_रेजिस्टर_device(काष्ठा tty_port *port,
		काष्ठा tty_driver *driver, अचिन्हित index,
		काष्ठा device *device)
अणु
	वापस tty_port_रेजिस्टर_device_attr(port, driver, index, device, शून्य, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(tty_port_रेजिस्टर_device);

/**
 * tty_port_रेजिस्टर_device_attr - रेजिस्टर tty device
 * @port: tty_port of the device
 * @driver: tty_driver क्रम this device
 * @index: index of the tty
 * @device: parent अगर exists, otherwise शून्य
 * @drvdata: Driver data to be set to device.
 * @attr_grp: Attribute group to be set on device.
 *
 * It is the same as tty_रेजिस्टर_device_attr except the provided @port is
 * linked to a concrete tty specअगरied by @index. Use this or tty_port_install
 * (or both). Call tty_port_link_device as a last resort.
 */
काष्ठा device *tty_port_रेजिस्टर_device_attr(काष्ठा tty_port *port,
		काष्ठा tty_driver *driver, अचिन्हित index,
		काष्ठा device *device, व्योम *drvdata,
		स्थिर काष्ठा attribute_group **attr_grp)
अणु
	tty_port_link_device(port, driver, index);
	वापस tty_रेजिस्टर_device_attr(driver, index, device, drvdata,
			attr_grp);
पूर्ण
EXPORT_SYMBOL_GPL(tty_port_रेजिस्टर_device_attr);

/**
 * tty_port_रेजिस्टर_device_attr_serdev - रेजिस्टर tty or serdev device
 * @port: tty_port of the device
 * @driver: tty_driver क्रम this device
 * @index: index of the tty
 * @device: parent अगर exists, otherwise शून्य
 * @drvdata: driver data क्रम the device
 * @attr_grp: attribute group क्रम the device
 *
 * Register a serdev or tty device depending on अगर the parent device has any
 * defined serdev clients or not.
 */
काष्ठा device *tty_port_रेजिस्टर_device_attr_serdev(काष्ठा tty_port *port,
		काष्ठा tty_driver *driver, अचिन्हित index,
		काष्ठा device *device, व्योम *drvdata,
		स्थिर काष्ठा attribute_group **attr_grp)
अणु
	काष्ठा device *dev;

	tty_port_link_device(port, driver, index);

	dev = serdev_tty_port_रेजिस्टर(port, device, driver, index);
	अगर (PTR_ERR(dev) != -ENODEV) अणु
		/* Skip creating cdev अगर we रेजिस्टरed a serdev device */
		वापस dev;
	पूर्ण

	वापस tty_रेजिस्टर_device_attr(driver, index, device, drvdata,
			attr_grp);
पूर्ण
EXPORT_SYMBOL_GPL(tty_port_रेजिस्टर_device_attr_serdev);

/**
 * tty_port_रेजिस्टर_device_serdev - रेजिस्टर tty or serdev device
 * @port: tty_port of the device
 * @driver: tty_driver क्रम this device
 * @index: index of the tty
 * @device: parent अगर exists, otherwise शून्य
 *
 * Register a serdev or tty device depending on अगर the parent device has any
 * defined serdev clients or not.
 */
काष्ठा device *tty_port_रेजिस्टर_device_serdev(काष्ठा tty_port *port,
		काष्ठा tty_driver *driver, अचिन्हित index,
		काष्ठा device *device)
अणु
	वापस tty_port_रेजिस्टर_device_attr_serdev(port, driver, index,
			device, शून्य, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(tty_port_रेजिस्टर_device_serdev);

/**
 * tty_port_unरेजिस्टर_device - deरेजिस्टर a tty or serdev device
 * @port: tty_port of the device
 * @driver: tty_driver क्रम this device
 * @index: index of the tty
 *
 * If a tty or serdev device is रेजिस्टरed with a call to
 * tty_port_रेजिस्टर_device_serdev() then this function must be called when
 * the device is gone.
 */
व्योम tty_port_unरेजिस्टर_device(काष्ठा tty_port *port,
		काष्ठा tty_driver *driver, अचिन्हित index)
अणु
	पूर्णांक ret;

	ret = serdev_tty_port_unरेजिस्टर(port);
	अगर (ret == 0)
		वापस;

	tty_unरेजिस्टर_device(driver, index);
पूर्ण
EXPORT_SYMBOL_GPL(tty_port_unरेजिस्टर_device);

पूर्णांक tty_port_alloc_xmit_buf(काष्ठा tty_port *port)
अणु
	/* We may sleep in get_zeroed_page() */
	mutex_lock(&port->buf_mutex);
	अगर (port->xmit_buf == शून्य)
		port->xmit_buf = (अचिन्हित अक्षर *)get_zeroed_page(GFP_KERNEL);
	mutex_unlock(&port->buf_mutex);
	अगर (port->xmit_buf == शून्य)
		वापस -ENOMEM;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(tty_port_alloc_xmit_buf);

व्योम tty_port_मुक्त_xmit_buf(काष्ठा tty_port *port)
अणु
	mutex_lock(&port->buf_mutex);
	अगर (port->xmit_buf != शून्य) अणु
		मुक्त_page((अचिन्हित दीर्घ)port->xmit_buf);
		port->xmit_buf = शून्य;
	पूर्ण
	mutex_unlock(&port->buf_mutex);
पूर्ण
EXPORT_SYMBOL(tty_port_मुक्त_xmit_buf);

/**
 * tty_port_destroy -- destroy inited port
 * @port: tty port to be destroyed
 *
 * When a port was initialized using tty_port_init, one has to destroy the
 * port by this function. Either indirectly by using tty_port refcounting
 * (tty_port_put) or directly अगर refcounting is not used.
 */
व्योम tty_port_destroy(काष्ठा tty_port *port)
अणु
	tty_buffer_cancel_work(port);
	tty_buffer_मुक्त_all(port);
पूर्ण
EXPORT_SYMBOL(tty_port_destroy);

अटल व्योम tty_port_deकाष्ठाor(काष्ठा kref *kref)
अणु
	काष्ठा tty_port *port = container_of(kref, काष्ठा tty_port, kref);

	/* check अगर last port ref was dropped beक्रमe tty release */
	अगर (WARN_ON(port->itty))
		वापस;
	अगर (port->xmit_buf)
		मुक्त_page((अचिन्हित दीर्घ)port->xmit_buf);
	tty_port_destroy(port);
	अगर (port->ops && port->ops->deकाष्ठा)
		port->ops->deकाष्ठा(port);
	अन्यथा
		kमुक्त(port);
पूर्ण

व्योम tty_port_put(काष्ठा tty_port *port)
अणु
	अगर (port)
		kref_put(&port->kref, tty_port_deकाष्ठाor);
पूर्ण
EXPORT_SYMBOL(tty_port_put);

/**
 *	tty_port_tty_get	-	get a tty reference
 *	@port: tty port
 *
 *	Return a refcount रक्षित tty instance or शून्य अगर the port is not
 *	associated with a tty (eg due to बंद or hangup)
 */
काष्ठा tty_काष्ठा *tty_port_tty_get(काष्ठा tty_port *port)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा tty_काष्ठा *tty;

	spin_lock_irqsave(&port->lock, flags);
	tty = tty_kref_get(port->tty);
	spin_unlock_irqrestore(&port->lock, flags);
	वापस tty;
पूर्ण
EXPORT_SYMBOL(tty_port_tty_get);

/**
 *	tty_port_tty_set	-	set the tty of a port
 *	@port: tty port
 *	@tty: the tty
 *
 *	Associate the port and tty pair. Manages any पूर्णांकernal refcounts.
 *	Pass शून्य to deassociate a port
 */
व्योम tty_port_tty_set(काष्ठा tty_port *port, काष्ठा tty_काष्ठा *tty)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);
	tty_kref_put(port->tty);
	port->tty = tty_kref_get(tty);
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण
EXPORT_SYMBOL(tty_port_tty_set);

अटल व्योम tty_port_shutकरोwn(काष्ठा tty_port *port, काष्ठा tty_काष्ठा *tty)
अणु
	mutex_lock(&port->mutex);
	अगर (port->console)
		जाओ out;

	अगर (tty_port_initialized(port)) अणु
		tty_port_set_initialized(port, 0);
		/*
		 * Drop DTR/RTS अगर HUPCL is set. This causes any attached
		 * modem to hang up the line.
		 */
		अगर (tty && C_HUPCL(tty))
			tty_port_lower_dtr_rts(port);

		अगर (port->ops->shutकरोwn)
			port->ops->shutकरोwn(port);
	पूर्ण
out:
	mutex_unlock(&port->mutex);
पूर्ण

/**
 *	tty_port_hangup		-	hangup helper
 *	@port: tty port
 *
 *	Perक्रमm port level tty hangup flag and count changes. Drop the tty
 *	reference.
 *
 *	Caller holds tty lock.
 */
व्योम tty_port_hangup(काष्ठा tty_port *port)
अणु
	काष्ठा tty_काष्ठा *tty;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);
	port->count = 0;
	tty = port->tty;
	अगर (tty)
		set_bit(TTY_IO_ERROR, &tty->flags);
	port->tty = शून्य;
	spin_unlock_irqrestore(&port->lock, flags);
	tty_port_set_active(port, 0);
	tty_port_shutकरोwn(port, tty);
	tty_kref_put(tty);
	wake_up_पूर्णांकerruptible(&port->खोलो_रुको);
	wake_up_पूर्णांकerruptible(&port->delta_msr_रुको);
पूर्ण
EXPORT_SYMBOL(tty_port_hangup);

/**
 * tty_port_tty_hangup - helper to hang up a tty
 *
 * @port: tty port
 * @check_clocal: hang only ttys with CLOCAL unset?
 */
व्योम tty_port_tty_hangup(काष्ठा tty_port *port, bool check_clocal)
अणु
	काष्ठा tty_काष्ठा *tty = tty_port_tty_get(port);

	अगर (tty && (!check_clocal || !C_CLOCAL(tty)))
		tty_hangup(tty);
	tty_kref_put(tty);
पूर्ण
EXPORT_SYMBOL_GPL(tty_port_tty_hangup);

/**
 * tty_port_tty_wakeup - helper to wake up a tty
 *
 * @port: tty port
 */
व्योम tty_port_tty_wakeup(काष्ठा tty_port *port)
अणु
	port->client_ops->ग_लिखो_wakeup(port);
पूर्ण
EXPORT_SYMBOL_GPL(tty_port_tty_wakeup);

/**
 *	tty_port_carrier_उठाओd	-	carrier उठाओd check
 *	@port: tty port
 *
 *	Wrapper क्रम the carrier detect logic. For the moment this is used
 *	to hide some पूर्णांकernal details. This will eventually become entirely
 *	पूर्णांकernal to the tty port.
 */
पूर्णांक tty_port_carrier_उठाओd(काष्ठा tty_port *port)
अणु
	अगर (port->ops->carrier_उठाओd == शून्य)
		वापस 1;
	वापस port->ops->carrier_उठाओd(port);
पूर्ण
EXPORT_SYMBOL(tty_port_carrier_उठाओd);

/**
 *	tty_port_उठाओ_dtr_rts	-	Raise DTR/RTS
 *	@port: tty port
 *
 *	Wrapper क्रम the DTR/RTS उठाओ logic. For the moment this is used
 *	to hide some पूर्णांकernal details. This will eventually become entirely
 *	पूर्णांकernal to the tty port.
 */
व्योम tty_port_उठाओ_dtr_rts(काष्ठा tty_port *port)
अणु
	अगर (port->ops->dtr_rts)
		port->ops->dtr_rts(port, 1);
पूर्ण
EXPORT_SYMBOL(tty_port_उठाओ_dtr_rts);

/**
 *	tty_port_lower_dtr_rts	-	Lower DTR/RTS
 *	@port: tty port
 *
 *	Wrapper क्रम the DTR/RTS उठाओ logic. For the moment this is used
 *	to hide some पूर्णांकernal details. This will eventually become entirely
 *	पूर्णांकernal to the tty port.
 */
व्योम tty_port_lower_dtr_rts(काष्ठा tty_port *port)
अणु
	अगर (port->ops->dtr_rts)
		port->ops->dtr_rts(port, 0);
पूर्ण
EXPORT_SYMBOL(tty_port_lower_dtr_rts);

/**
 *	tty_port_block_til_पढ़ोy	-	Waiting logic क्रम tty खोलो
 *	@port: the tty port being खोलोed
 *	@tty: the tty device being bound
 *	@filp: the file poपूर्णांकer of the खोलोer or शून्य
 *
 *	Implement the core POSIX/SuS tty behaviour when खोलोing a tty device.
 *	Handles:
 *		- hangup (both beक्रमe and during)
 *		- non blocking खोलो
 *		- rts/dtr/dcd
 *		- संकेतs
 *		- port flags and counts
 *
 *	The passed tty_port must implement the carrier_उठाओd method अगर it can
 *	करो carrier detect and the dtr_rts method अगर it supports software
 *	management of these lines. Note that the dtr/rts उठाओ is करोne each
 *	iteration as a hangup may have previously dropped them जबतक we रुको.
 *
 *	Caller holds tty lock.
 *
 *      NB: May drop and reacquire tty lock when blocking, so tty and tty_port
 *      may have changed state (eg., may have been hung up).
 */
पूर्णांक tty_port_block_til_पढ़ोy(काष्ठा tty_port *port,
				काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	पूर्णांक करो_clocal = 0, retval;
	अचिन्हित दीर्घ flags;
	DEFINE_WAIT(रुको);

	/* अगर non-blocking mode is set we can pass directly to खोलो unless
	   the port has just hung up or is in another error state */
	अगर (tty_io_error(tty)) अणु
		tty_port_set_active(port, 1);
		वापस 0;
	पूर्ण
	अगर (filp == शून्य || (filp->f_flags & O_NONBLOCK)) अणु
		/* Indicate we are खोलो */
		अगर (C_BAUD(tty))
			tty_port_उठाओ_dtr_rts(port);
		tty_port_set_active(port, 1);
		वापस 0;
	पूर्ण

	अगर (C_CLOCAL(tty))
		करो_clocal = 1;

	/* Block रुकोing until we can proceed. We may need to रुको क्रम the
	   carrier, but we must also रुको क्रम any बंद that is in progress
	   beक्रमe the next खोलो may complete */

	retval = 0;

	/* The port lock protects the port counts */
	spin_lock_irqsave(&port->lock, flags);
	port->count--;
	port->blocked_खोलो++;
	spin_unlock_irqrestore(&port->lock, flags);

	जबतक (1) अणु
		/* Indicate we are खोलो */
		अगर (C_BAUD(tty) && tty_port_initialized(port))
			tty_port_उठाओ_dtr_rts(port);

		prepare_to_रुको(&port->खोलो_रुको, &रुको, TASK_INTERRUPTIBLE);
		/* Check क्रम a hangup or uninitialised port.
							Return accordingly */
		अगर (tty_hung_up_p(filp) || !tty_port_initialized(port)) अणु
			अगर (port->flags & ASYNC_HUP_NOTIFY)
				retval = -EAGAIN;
			अन्यथा
				retval = -ERESTARTSYS;
			अवरोध;
		पूर्ण
		/*
		 * Probe the carrier. For devices with no carrier detect
		 * tty_port_carrier_उठाओd will always वापस true.
		 * Never ask drivers अगर CLOCAL is set, this causes troubles
		 * on some hardware.
		 */
		अगर (करो_clocal || tty_port_carrier_उठाओd(port))
			अवरोध;
		अगर (संकेत_pending(current)) अणु
			retval = -ERESTARTSYS;
			अवरोध;
		पूर्ण
		tty_unlock(tty);
		schedule();
		tty_lock(tty);
	पूर्ण
	finish_रुको(&port->खोलो_रुको, &रुको);

	/* Update counts. A parallel hangup will have set count to zero and
	   we must not mess that up further */
	spin_lock_irqsave(&port->lock, flags);
	अगर (!tty_hung_up_p(filp))
		port->count++;
	port->blocked_खोलो--;
	spin_unlock_irqrestore(&port->lock, flags);
	अगर (retval == 0)
		tty_port_set_active(port, 1);
	वापस retval;
पूर्ण
EXPORT_SYMBOL(tty_port_block_til_पढ़ोy);

अटल व्योम tty_port_drain_delay(काष्ठा tty_port *port, काष्ठा tty_काष्ठा *tty)
अणु
	अचिन्हित पूर्णांक bps = tty_get_baud_rate(tty);
	दीर्घ समयout;

	अगर (bps > 1200) अणु
		समयout = (HZ * 10 * port->drain_delay) / bps;
		समयout = max_t(दीर्घ, समयout, HZ / 10);
	पूर्ण अन्यथा अणु
		समयout = 2 * HZ;
	पूर्ण
	schedule_समयout_पूर्णांकerruptible(समयout);
पूर्ण

/* Caller holds tty lock. */
पूर्णांक tty_port_बंद_start(काष्ठा tty_port *port,
				काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	अचिन्हित दीर्घ flags;

	अगर (tty_hung_up_p(filp))
		वापस 0;

	spin_lock_irqsave(&port->lock, flags);
	अगर (tty->count == 1 && port->count != 1) अणु
		tty_warn(tty, "%s: tty->count = 1 port count = %d\n", __func__,
			 port->count);
		port->count = 1;
	पूर्ण
	अगर (--port->count < 0) अणु
		tty_warn(tty, "%s: bad port count (%d)\n", __func__,
			 port->count);
		port->count = 0;
	पूर्ण

	अगर (port->count) अणु
		spin_unlock_irqrestore(&port->lock, flags);
		वापस 0;
	पूर्ण
	spin_unlock_irqrestore(&port->lock, flags);

	tty->closing = 1;

	अगर (tty_port_initialized(port)) अणु
		/* Don't block on a stalled port, just pull the chain */
		अगर (tty->flow_stopped)
			tty_driver_flush_buffer(tty);
		अगर (port->closing_रुको != ASYNC_CLOSING_WAIT_NONE)
			tty_रुको_until_sent(tty, port->closing_रुको);
		अगर (port->drain_delay)
			tty_port_drain_delay(port, tty);
	पूर्ण
	/* Flush the ldisc buffering */
	tty_ldisc_flush(tty);

	/* Report to caller this is the last port reference */
	वापस 1;
पूर्ण
EXPORT_SYMBOL(tty_port_बंद_start);

/* Caller holds tty lock */
व्योम tty_port_बंद_end(काष्ठा tty_port *port, काष्ठा tty_काष्ठा *tty)
अणु
	अचिन्हित दीर्घ flags;

	tty_ldisc_flush(tty);
	tty->closing = 0;

	spin_lock_irqsave(&port->lock, flags);

	अगर (port->blocked_खोलो) अणु
		spin_unlock_irqrestore(&port->lock, flags);
		अगर (port->बंद_delay)
			msleep_पूर्णांकerruptible(jअगरfies_to_msecs(port->बंद_delay));
		spin_lock_irqsave(&port->lock, flags);
		wake_up_पूर्णांकerruptible(&port->खोलो_रुको);
	पूर्ण
	spin_unlock_irqrestore(&port->lock, flags);
	tty_port_set_active(port, 0);
पूर्ण
EXPORT_SYMBOL(tty_port_बंद_end);

/*
 * tty_port_बंद
 *
 * Caller holds tty lock
 */
व्योम tty_port_बंद(काष्ठा tty_port *port, काष्ठा tty_काष्ठा *tty,
							काष्ठा file *filp)
अणु
	अगर (tty_port_बंद_start(port, tty, filp) == 0)
		वापस;
	tty_port_shutकरोwn(port, tty);
	अगर (!port->console)
		set_bit(TTY_IO_ERROR, &tty->flags);
	tty_port_बंद_end(port, tty);
	tty_port_tty_set(port, शून्य);
पूर्ण
EXPORT_SYMBOL(tty_port_बंद);

/**
 * tty_port_install - generic tty->ops->install handler
 * @port: tty_port of the device
 * @driver: tty_driver क्रम this device
 * @tty: tty to be installed
 *
 * It is the same as tty_standard_install except the provided @port is linked
 * to a concrete tty specअगरied by @tty. Use this or tty_port_रेजिस्टर_device
 * (or both). Call tty_port_link_device as a last resort.
 */
पूर्णांक tty_port_install(काष्ठा tty_port *port, काष्ठा tty_driver *driver,
		काष्ठा tty_काष्ठा *tty)
अणु
	tty->port = port;
	वापस tty_standard_install(driver, tty);
पूर्ण
EXPORT_SYMBOL_GPL(tty_port_install);

/*
 * tty_port_खोलो
 *
 * Caller holds tty lock.
 *
 * NB: may drop and reacquire tty lock (in tty_port_block_til_पढ़ोy()) so
 * tty and tty_port may have changed state (eg., may be hung up now)
 */
पूर्णांक tty_port_खोलो(काष्ठा tty_port *port, काष्ठा tty_काष्ठा *tty,
							काष्ठा file *filp)
अणु
	spin_lock_irq(&port->lock);
	++port->count;
	spin_unlock_irq(&port->lock);
	tty_port_tty_set(port, tty);

	/*
	 * Do the device-specअगरic खोलो only अगर the hardware isn't
	 * alपढ़ोy initialized. Serialize खोलो and shutकरोwn using the
	 * port mutex.
	 */

	mutex_lock(&port->mutex);

	अगर (!tty_port_initialized(port)) अणु
		clear_bit(TTY_IO_ERROR, &tty->flags);
		अगर (port->ops->activate) अणु
			पूर्णांक retval = port->ops->activate(port, tty);
			अगर (retval) अणु
				mutex_unlock(&port->mutex);
				वापस retval;
			पूर्ण
		पूर्ण
		tty_port_set_initialized(port, 1);
	पूर्ण
	mutex_unlock(&port->mutex);
	वापस tty_port_block_til_पढ़ोy(port, tty, filp);
पूर्ण

EXPORT_SYMBOL(tty_port_खोलो);
