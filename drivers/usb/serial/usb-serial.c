<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * USB Serial Converter driver
 *
 * Copyright (C) 2009 - 2013 Johan Hovold (jhovold@gmail.com)
 * Copyright (C) 1999 - 2012 Greg Kroah-Harपंचांगan (greg@kroah.com)
 * Copyright (C) 2000 Peter Berger (pberger@brimson.com)
 * Copyright (C) 2000 Al Borchers (borchers@steinerpoपूर्णांक.com)
 *
 * This driver was originally based on the ACM driver by Armin Fuerst (which was
 * based on a driver by Brad Keryan)
 *
 * See Documentation/usb/usb-serial.rst क्रम more inक्रमmation on using this
 * driver
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/serial.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/idr.h>

#घोषणा DRIVER_AUTHOR "Greg Kroah-Hartman <gregkh@linuxfoundation.org>"
#घोषणा DRIVER_DESC "USB Serial Driver core"

#घोषणा USB_SERIAL_TTY_MAJOR	188
#घोषणा USB_SERIAL_TTY_MINORS	512	/* should be enough क्रम a जबतक */

/* There is no MODULE_DEVICE_TABLE क्रम usbserial.c.  Instead
   the MODULE_DEVICE_TABLE declarations in each serial driver
   cause the "hotplug" program to pull in whatever module is necessary
   via modprobe, and modprobe will load usbserial because the serial
   drivers depend on it.
*/

अटल DEFINE_IDR(serial_minors);
अटल DEFINE_MUTEX(table_lock);
अटल LIST_HEAD(usb_serial_driver_list);

/*
 * Look up the serial port काष्ठाure.  If it is found and it hasn't been
 * disconnected, वापस with the parent usb_serial काष्ठाure's disc_mutex held
 * and its refcount incremented.  Otherwise वापस शून्य.
 */
काष्ठा usb_serial_port *usb_serial_port_get_by_minor(अचिन्हित minor)
अणु
	काष्ठा usb_serial *serial;
	काष्ठा usb_serial_port *port;

	mutex_lock(&table_lock);
	port = idr_find(&serial_minors, minor);
	अगर (!port)
		जाओ निकास;

	serial = port->serial;
	mutex_lock(&serial->disc_mutex);
	अगर (serial->disconnected) अणु
		mutex_unlock(&serial->disc_mutex);
		port = शून्य;
	पूर्ण अन्यथा अणु
		kref_get(&serial->kref);
	पूर्ण
निकास:
	mutex_unlock(&table_lock);
	वापस port;
पूर्ण

अटल पूर्णांक allocate_minors(काष्ठा usb_serial *serial, पूर्णांक num_ports)
अणु
	काष्ठा usb_serial_port *port;
	अचिन्हित पूर्णांक i, j;
	पूर्णांक minor;

	dev_dbg(&serial->पूर्णांकerface->dev, "%s %d\n", __func__, num_ports);

	mutex_lock(&table_lock);
	क्रम (i = 0; i < num_ports; ++i) अणु
		port = serial->port[i];
		minor = idr_alloc(&serial_minors, port, 0,
					USB_SERIAL_TTY_MINORS, GFP_KERNEL);
		अगर (minor < 0)
			जाओ error;
		port->minor = minor;
		port->port_number = i;
	पूर्ण
	serial->minors_reserved = 1;
	mutex_unlock(&table_lock);
	वापस 0;
error:
	/* unwind the alपढ़ोy allocated minors */
	क्रम (j = 0; j < i; ++j)
		idr_हटाओ(&serial_minors, serial->port[j]->minor);
	mutex_unlock(&table_lock);
	वापस minor;
पूर्ण

अटल व्योम release_minors(काष्ठा usb_serial *serial)
अणु
	पूर्णांक i;

	mutex_lock(&table_lock);
	क्रम (i = 0; i < serial->num_ports; ++i)
		idr_हटाओ(&serial_minors, serial->port[i]->minor);
	mutex_unlock(&table_lock);
	serial->minors_reserved = 0;
पूर्ण

पूर्णांक usb_serial_claim_पूर्णांकerface(काष्ठा usb_serial *serial, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_driver *driver = serial->type->usb_driver;
	पूर्णांक ret;

	अगर (serial->sibling)
		वापस -EBUSY;

	ret = usb_driver_claim_पूर्णांकerface(driver, पूर्णांकf, serial);
	अगर (ret) अणु
		dev_err(&serial->पूर्णांकerface->dev,
				"failed to claim sibling interface: %d\n", ret);
		वापस ret;
	पूर्ण

	serial->sibling = पूर्णांकf;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usb_serial_claim_पूर्णांकerface);

अटल व्योम release_sibling(काष्ठा usb_serial *serial, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_driver *driver = serial->type->usb_driver;
	काष्ठा usb_पूर्णांकerface *sibling;

	अगर (!serial->sibling)
		वापस;

	अगर (पूर्णांकf == serial->sibling)
		sibling = serial->पूर्णांकerface;
	अन्यथा
		sibling = serial->sibling;

	usb_set_पूर्णांकfdata(sibling, शून्य);
	usb_driver_release_पूर्णांकerface(driver, sibling);
पूर्ण

अटल व्योम destroy_serial(काष्ठा kref *kref)
अणु
	काष्ठा usb_serial *serial;
	काष्ठा usb_serial_port *port;
	पूर्णांक i;

	serial = to_usb_serial(kref);

	/* वापस the minor range that this device had */
	अगर (serial->minors_reserved)
		release_minors(serial);

	अगर (serial->attached && serial->type->release)
		serial->type->release(serial);

	/* Now that nothing is using the ports, they can be मुक्तd */
	क्रम (i = 0; i < serial->num_port_poपूर्णांकers; ++i) अणु
		port = serial->port[i];
		अगर (port) अणु
			port->serial = शून्य;
			put_device(&port->dev);
		पूर्ण
	पूर्ण

	usb_put_पूर्णांकf(serial->पूर्णांकerface);
	usb_put_dev(serial->dev);
	kमुक्त(serial);
पूर्ण

व्योम usb_serial_put(काष्ठा usb_serial *serial)
अणु
	kref_put(&serial->kref, destroy_serial);
पूर्ण

/*****************************************************************************
 * Driver tty पूर्णांकerface functions
 *****************************************************************************/

/**
 * serial_install - install tty
 * @driver: the driver (USB in our हाल)
 * @tty: the tty being created
 *
 * Initialise the termios काष्ठाure क्रम this tty.  We use the शेष
 * USB serial settings but permit them to be overridden by
 * serial->type->init_termios on first खोलो.
 *
 * This is the first place a new tty माला_लो used.  Hence this is where we
 * acquire references to the usb_serial काष्ठाure and the driver module,
 * where we store a poपूर्णांकer to the port, and where we करो an स्वतःresume.
 * All these actions are reversed in serial_cleanup().
 */
अटल पूर्णांक serial_install(काष्ठा tty_driver *driver, काष्ठा tty_काष्ठा *tty)
अणु
	पूर्णांक idx = tty->index;
	काष्ठा usb_serial *serial;
	काष्ठा usb_serial_port *port;
	bool init_termios;
	पूर्णांक retval = -ENODEV;

	port = usb_serial_port_get_by_minor(idx);
	अगर (!port)
		वापस retval;

	serial = port->serial;
	अगर (!try_module_get(serial->type->driver.owner))
		जाओ error_module_get;

	retval = usb_स्वतःpm_get_पूर्णांकerface(serial->पूर्णांकerface);
	अगर (retval)
		जाओ error_get_पूर्णांकerface;

	init_termios = (driver->termios[idx] == शून्य);

	retval = tty_standard_install(driver, tty);
	अगर (retval)
		जाओ error_init_termios;

	mutex_unlock(&serial->disc_mutex);

	/* allow the driver to update the initial settings */
	अगर (init_termios && serial->type->init_termios)
		serial->type->init_termios(tty);

	tty->driver_data = port;

	वापस retval;

 error_init_termios:
	usb_स्वतःpm_put_पूर्णांकerface(serial->पूर्णांकerface);
 error_get_पूर्णांकerface:
	module_put(serial->type->driver.owner);
 error_module_get:
	usb_serial_put(serial);
	mutex_unlock(&serial->disc_mutex);
	वापस retval;
पूर्ण

अटल पूर्णांक serial_port_activate(काष्ठा tty_port *tport, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port =
		container_of(tport, काष्ठा usb_serial_port, port);
	काष्ठा usb_serial *serial = port->serial;
	पूर्णांक retval;

	mutex_lock(&serial->disc_mutex);
	अगर (serial->disconnected)
		retval = -ENODEV;
	अन्यथा
		retval = port->serial->type->खोलो(tty, port);
	mutex_unlock(&serial->disc_mutex);

	अगर (retval < 0)
		retval = usb_translate_errors(retval);

	वापस retval;
पूर्ण

अटल पूर्णांक serial_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;

	dev_dbg(&port->dev, "%s\n", __func__);

	वापस tty_port_खोलो(&port->port, tty, filp);
पूर्ण

/**
 * serial_port_shutकरोwn - shut करोwn hardware
 * @tport: tty port to shut करोwn
 *
 * Shut करोwn a USB serial port. Serialized against activate by the
 * tport mutex and kept to matching खोलो/बंद pairs
 * of calls by the initialized flag.
 *
 * Not called अगर tty is console.
 */
अटल व्योम serial_port_shutकरोwn(काष्ठा tty_port *tport)
अणु
	काष्ठा usb_serial_port *port =
		container_of(tport, काष्ठा usb_serial_port, port);
	काष्ठा usb_serial_driver *drv = port->serial->type;

	अगर (drv->बंद)
		drv->बंद(port);
पूर्ण

अटल व्योम serial_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;

	dev_dbg(&port->dev, "%s\n", __func__);

	tty_port_hangup(&port->port);
पूर्ण

अटल व्योम serial_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;

	dev_dbg(&port->dev, "%s\n", __func__);

	tty_port_बंद(&port->port, tty, filp);
पूर्ण

/**
 * serial_cleanup - मुक्त resources post बंद/hangup
 * @tty: tty to clean up
 *
 * Do the resource मुक्तing and refcount dropping क्रम the port.
 * Aव्योम मुक्तing the console.
 *
 * Called asynchronously after the last tty kref is dropped.
 */
अटल व्योम serial_cleanup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा usb_serial *serial;
	काष्ठा module *owner;

	dev_dbg(&port->dev, "%s\n", __func__);

	/* The console is magical.  Do not hang up the console hardware
	 * or there will be tears.
	 */
	अगर (port->port.console)
		वापस;

	tty->driver_data = शून्य;

	serial = port->serial;
	owner = serial->type->driver.owner;

	usb_स्वतःpm_put_पूर्णांकerface(serial->पूर्णांकerface);

	usb_serial_put(serial);
	module_put(owner);
पूर्ण

अटल पूर्णांक serial_ग_लिखो(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *buf,
								पूर्णांक count)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	पूर्णांक retval = -ENODEV;

	अगर (port->serial->dev->state == USB_STATE_NOTATTACHED)
		जाओ निकास;

	dev_dbg(&port->dev, "%s - %d byte(s)\n", __func__, count);

	retval = port->serial->type->ग_लिखो(tty, port, buf, count);
	अगर (retval < 0)
		retval = usb_translate_errors(retval);
निकास:
	वापस retval;
पूर्ण

अटल पूर्णांक serial_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;

	dev_dbg(&port->dev, "%s\n", __func__);

	वापस port->serial->type->ग_लिखो_room(tty);
पूर्ण

अटल पूर्णांक serial_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा usb_serial *serial = port->serial;

	dev_dbg(&port->dev, "%s\n", __func__);

	अगर (serial->disconnected)
		वापस 0;

	वापस serial->type->अक्षरs_in_buffer(tty);
पूर्ण

अटल व्योम serial_रुको_until_sent(काष्ठा tty_काष्ठा *tty, पूर्णांक समयout)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा usb_serial *serial = port->serial;

	dev_dbg(&port->dev, "%s\n", __func__);

	अगर (!port->serial->type->रुको_until_sent)
		वापस;

	mutex_lock(&serial->disc_mutex);
	अगर (!serial->disconnected)
		port->serial->type->रुको_until_sent(tty, समयout);
	mutex_unlock(&serial->disc_mutex);
पूर्ण

अटल व्योम serial_throttle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;

	dev_dbg(&port->dev, "%s\n", __func__);

	अगर (port->serial->type->throttle)
		port->serial->type->throttle(tty);
पूर्ण

अटल व्योम serial_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;

	dev_dbg(&port->dev, "%s\n", __func__);

	अगर (port->serial->type->unthrottle)
		port->serial->type->unthrottle(tty);
पूर्ण

अटल पूर्णांक serial_get_serial(काष्ठा tty_काष्ठा *tty, काष्ठा serial_काष्ठा *ss)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा tty_port *tport = &port->port;
	अचिन्हित पूर्णांक बंद_delay, closing_रुको;

	mutex_lock(&tport->mutex);

	बंद_delay = jअगरfies_to_msecs(tport->बंद_delay) / 10;
	closing_रुको = tport->closing_रुको;
	अगर (closing_रुको != ASYNC_CLOSING_WAIT_NONE)
		closing_रुको = jअगरfies_to_msecs(closing_रुको) / 10;

	ss->line = port->minor;
	ss->बंद_delay = बंद_delay;
	ss->closing_रुको = closing_रुको;

	अगर (port->serial->type->get_serial)
		port->serial->type->get_serial(tty, ss);

	mutex_unlock(&tport->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक serial_set_serial(काष्ठा tty_काष्ठा *tty, काष्ठा serial_काष्ठा *ss)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा tty_port *tport = &port->port;
	अचिन्हित पूर्णांक बंद_delay, closing_रुको;
	पूर्णांक ret = 0;

	बंद_delay = msecs_to_jअगरfies(ss->बंद_delay * 10);
	closing_रुको = ss->closing_रुको;
	अगर (closing_रुको != ASYNC_CLOSING_WAIT_NONE)
		closing_रुको = msecs_to_jअगरfies(closing_रुको * 10);

	mutex_lock(&tport->mutex);

	अगर (!capable(CAP_SYS_ADMIN)) अणु
		अगर (बंद_delay != tport->बंद_delay ||
				closing_रुको != tport->closing_रुको) अणु
			ret = -EPERM;
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	अगर (port->serial->type->set_serial) अणु
		ret = port->serial->type->set_serial(tty, ss);
		अगर (ret)
			जाओ out_unlock;
	पूर्ण

	tport->बंद_delay = बंद_delay;
	tport->closing_रुको = closing_रुको;
out_unlock:
	mutex_unlock(&tport->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक serial_ioctl(काष्ठा tty_काष्ठा *tty,
					अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	पूर्णांक retval = -ENOIOCTLCMD;

	dev_dbg(&port->dev, "%s - cmd 0x%04x\n", __func__, cmd);

	चयन (cmd) अणु
	हाल TIOCMIWAIT:
		अगर (port->serial->type->tiocmiरुको)
			retval = port->serial->type->tiocmiरुको(tty, arg);
		अवरोध;
	शेष:
		अगर (port->serial->type->ioctl)
			retval = port->serial->type->ioctl(tty, cmd, arg);
	पूर्ण

	वापस retval;
पूर्ण

अटल व्योम serial_set_termios(काष्ठा tty_काष्ठा *tty, काष्ठा ktermios *old)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;

	dev_dbg(&port->dev, "%s\n", __func__);

	अगर (port->serial->type->set_termios)
		port->serial->type->set_termios(tty, port, old);
	अन्यथा
		tty_termios_copy_hw(&tty->termios, old);
पूर्ण

अटल पूर्णांक serial_अवरोध(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;

	dev_dbg(&port->dev, "%s\n", __func__);

	अगर (port->serial->type->अवरोध_ctl)
		port->serial->type->अवरोध_ctl(tty, अवरोध_state);

	वापस 0;
पूर्ण

अटल पूर्णांक serial_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा usb_serial *serial;
	काष्ठा usb_serial_port *port;
	पूर्णांक i;
	अक्षर पंचांगp[40];

	seq_माला_दो(m, "usbserinfo:1.0 driver:2.0\n");
	क्रम (i = 0; i < USB_SERIAL_TTY_MINORS; ++i) अणु
		port = usb_serial_port_get_by_minor(i);
		अगर (port == शून्य)
			जारी;
		serial = port->serial;

		seq_म_लिखो(m, "%d:", i);
		अगर (serial->type->driver.owner)
			seq_म_लिखो(m, " module:%s",
				module_name(serial->type->driver.owner));
		seq_म_लिखो(m, " name:\"%s\"",
				serial->type->description);
		seq_म_लिखो(m, " vendor:%04x product:%04x",
			le16_to_cpu(serial->dev->descriptor.idVenकरोr),
			le16_to_cpu(serial->dev->descriptor.idProduct));
		seq_म_लिखो(m, " num_ports:%d", serial->num_ports);
		seq_म_लिखो(m, " port:%d", port->port_number);
		usb_make_path(serial->dev, पंचांगp, माप(पंचांगp));
		seq_म_लिखो(m, " path:%s", पंचांगp);

		seq_अ_दो(m, '\n');
		usb_serial_put(serial);
		mutex_unlock(&serial->disc_mutex);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक serial_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;

	dev_dbg(&port->dev, "%s\n", __func__);

	अगर (port->serial->type->tiocmget)
		वापस port->serial->type->tiocmget(tty);
	वापस -ENOTTY;
पूर्ण

अटल पूर्णांक serial_tiocmset(काष्ठा tty_काष्ठा *tty,
			    अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;

	dev_dbg(&port->dev, "%s\n", __func__);

	अगर (port->serial->type->tiocmset)
		वापस port->serial->type->tiocmset(tty, set, clear);
	वापस -ENOTTY;
पूर्ण

अटल पूर्णांक serial_get_icount(काष्ठा tty_काष्ठा *tty,
				काष्ठा serial_icounter_काष्ठा *icount)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;

	dev_dbg(&port->dev, "%s\n", __func__);

	अगर (port->serial->type->get_icount)
		वापस port->serial->type->get_icount(tty, icount);
	वापस -ENOTTY;
पूर्ण

/*
 * We would be calling tty_wakeup here, but unक्रमtunately some line
 * disciplines have an annoying habit of calling tty->ग_लिखो from
 * the ग_लिखो wakeup callback (e.g. n_hdlc.c).
 */
व्योम usb_serial_port_softपूर्णांक(काष्ठा usb_serial_port *port)
अणु
	schedule_work(&port->work);
पूर्ण
EXPORT_SYMBOL_GPL(usb_serial_port_softपूर्णांक);

अटल व्योम usb_serial_port_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा usb_serial_port *port =
		container_of(work, काष्ठा usb_serial_port, work);

	tty_port_tty_wakeup(&port->port);
पूर्ण

अटल व्योम usb_serial_port_poison_urbs(काष्ठा usb_serial_port *port)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(port->पढ़ो_urbs); ++i)
		usb_poison_urb(port->पढ़ो_urbs[i]);
	क्रम (i = 0; i < ARRAY_SIZE(port->ग_लिखो_urbs); ++i)
		usb_poison_urb(port->ग_लिखो_urbs[i]);

	usb_poison_urb(port->पूर्णांकerrupt_in_urb);
	usb_poison_urb(port->पूर्णांकerrupt_out_urb);
पूर्ण

अटल व्योम usb_serial_port_unpoison_urbs(काष्ठा usb_serial_port *port)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(port->पढ़ो_urbs); ++i)
		usb_unpoison_urb(port->पढ़ो_urbs[i]);
	क्रम (i = 0; i < ARRAY_SIZE(port->ग_लिखो_urbs); ++i)
		usb_unpoison_urb(port->ग_लिखो_urbs[i]);

	usb_unpoison_urb(port->पूर्णांकerrupt_in_urb);
	usb_unpoison_urb(port->पूर्णांकerrupt_out_urb);
पूर्ण

अटल व्योम usb_serial_port_release(काष्ठा device *dev)
अणु
	काष्ठा usb_serial_port *port = to_usb_serial_port(dev);
	पूर्णांक i;

	dev_dbg(dev, "%s\n", __func__);

	usb_मुक्त_urb(port->पूर्णांकerrupt_in_urb);
	usb_मुक्त_urb(port->पूर्णांकerrupt_out_urb);
	क्रम (i = 0; i < ARRAY_SIZE(port->पढ़ो_urbs); ++i) अणु
		usb_मुक्त_urb(port->पढ़ो_urbs[i]);
		kमुक्त(port->bulk_in_buffers[i]);
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(port->ग_लिखो_urbs); ++i) अणु
		usb_मुक्त_urb(port->ग_लिखो_urbs[i]);
		kमुक्त(port->bulk_out_buffers[i]);
	पूर्ण
	kfअगरo_मुक्त(&port->ग_लिखो_fअगरo);
	kमुक्त(port->पूर्णांकerrupt_in_buffer);
	kमुक्त(port->पूर्णांकerrupt_out_buffer);
	tty_port_destroy(&port->port);
	kमुक्त(port);
पूर्ण

अटल काष्ठा usb_serial *create_serial(काष्ठा usb_device *dev,
					काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
					काष्ठा usb_serial_driver *driver)
अणु
	काष्ठा usb_serial *serial;

	serial = kzalloc(माप(*serial), GFP_KERNEL);
	अगर (!serial)
		वापस शून्य;
	serial->dev = usb_get_dev(dev);
	serial->type = driver;
	serial->पूर्णांकerface = usb_get_पूर्णांकf(पूर्णांकerface);
	kref_init(&serial->kref);
	mutex_init(&serial->disc_mutex);
	serial->minors_reserved = 0;

	वापस serial;
पूर्ण

अटल स्थिर काष्ठा usb_device_id *match_dynamic_id(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
					    काष्ठा usb_serial_driver *drv)
अणु
	काष्ठा usb_dynid *dynid;

	spin_lock(&drv->dynids.lock);
	list_क्रम_each_entry(dynid, &drv->dynids.list, node) अणु
		अगर (usb_match_one_id(पूर्णांकf, &dynid->id)) अणु
			spin_unlock(&drv->dynids.lock);
			वापस &dynid->id;
		पूर्ण
	पूर्ण
	spin_unlock(&drv->dynids.lock);
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा usb_device_id *get_अगरace_id(काष्ठा usb_serial_driver *drv,
						काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	स्थिर काष्ठा usb_device_id *id;

	id = usb_match_id(पूर्णांकf, drv->id_table);
	अगर (id) अणु
		dev_dbg(&पूर्णांकf->dev, "static descriptor matches\n");
		जाओ निकास;
	पूर्ण
	id = match_dynamic_id(पूर्णांकf, drv);
	अगर (id)
		dev_dbg(&पूर्णांकf->dev, "dynamic descriptor matches\n");
निकास:
	वापस id;
पूर्ण

/* Caller must hold table_lock */
अटल काष्ठा usb_serial_driver *search_serial_device(
					काष्ठा usb_पूर्णांकerface *अगरace)
अणु
	स्थिर काष्ठा usb_device_id *id = शून्य;
	काष्ठा usb_serial_driver *drv;
	काष्ठा usb_driver *driver = to_usb_driver(अगरace->dev.driver);

	/* Check अगर the usb id matches a known device */
	list_क्रम_each_entry(drv, &usb_serial_driver_list, driver_list) अणु
		अगर (drv->usb_driver == driver)
			id = get_अगरace_id(drv, अगरace);
		अगर (id)
			वापस drv;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक serial_port_carrier_उठाओd(काष्ठा tty_port *port)
अणु
	काष्ठा usb_serial_port *p = container_of(port, काष्ठा usb_serial_port, port);
	काष्ठा usb_serial_driver *drv = p->serial->type;

	अगर (drv->carrier_उठाओd)
		वापस drv->carrier_उठाओd(p);
	/* No carrier control - करोn't block */
	वापस 1;
पूर्ण

अटल व्योम serial_port_dtr_rts(काष्ठा tty_port *port, पूर्णांक on)
अणु
	काष्ठा usb_serial_port *p = container_of(port, काष्ठा usb_serial_port, port);
	काष्ठा usb_serial_driver *drv = p->serial->type;

	अगर (drv->dtr_rts)
		drv->dtr_rts(p, on);
पूर्ण

अटल sमाप_प्रकार port_number_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_serial_port *port = to_usb_serial_port(dev);

	वापस प्र_लिखो(buf, "%u\n", port->port_number);
पूर्ण
अटल DEVICE_ATTR_RO(port_number);

अटल काष्ठा attribute *usb_serial_port_attrs[] = अणु
	&dev_attr_port_number.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(usb_serial_port);

अटल स्थिर काष्ठा tty_port_operations serial_port_ops = अणु
	.carrier_उठाओd		= serial_port_carrier_उठाओd,
	.dtr_rts		= serial_port_dtr_rts,
	.activate		= serial_port_activate,
	.shutकरोwn		= serial_port_shutकरोwn,
पूर्ण;

अटल व्योम store_endpoपूर्णांक(काष्ठा usb_serial *serial,
					काष्ठा usb_serial_endpoपूर्णांकs *epds,
					काष्ठा usb_endpoपूर्णांक_descriptor *epd)
अणु
	काष्ठा device *dev = &serial->पूर्णांकerface->dev;
	u8 addr = epd->bEndpoपूर्णांकAddress;

	अगर (usb_endpoपूर्णांक_is_bulk_in(epd)) अणु
		अगर (epds->num_bulk_in == ARRAY_SIZE(epds->bulk_in))
			वापस;
		dev_dbg(dev, "found bulk in endpoint %02x\n", addr);
		epds->bulk_in[epds->num_bulk_in++] = epd;
	पूर्ण अन्यथा अगर (usb_endpoपूर्णांक_is_bulk_out(epd)) अणु
		अगर (epds->num_bulk_out == ARRAY_SIZE(epds->bulk_out))
			वापस;
		dev_dbg(dev, "found bulk out endpoint %02x\n", addr);
		epds->bulk_out[epds->num_bulk_out++] = epd;
	पूर्ण अन्यथा अगर (usb_endpoपूर्णांक_is_पूर्णांक_in(epd)) अणु
		अगर (epds->num_पूर्णांकerrupt_in == ARRAY_SIZE(epds->पूर्णांकerrupt_in))
			वापस;
		dev_dbg(dev, "found interrupt in endpoint %02x\n", addr);
		epds->पूर्णांकerrupt_in[epds->num_पूर्णांकerrupt_in++] = epd;
	पूर्ण अन्यथा अगर (usb_endpoपूर्णांक_is_पूर्णांक_out(epd)) अणु
		अगर (epds->num_पूर्णांकerrupt_out == ARRAY_SIZE(epds->पूर्णांकerrupt_out))
			वापस;
		dev_dbg(dev, "found interrupt out endpoint %02x\n", addr);
		epds->पूर्णांकerrupt_out[epds->num_पूर्णांकerrupt_out++] = epd;
	पूर्ण
पूर्ण

अटल व्योम find_endpoपूर्णांकs(काष्ठा usb_serial *serial,
					काष्ठा usb_serial_endpoपूर्णांकs *epds,
					काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc;
	काष्ठा usb_endpoपूर्णांक_descriptor *epd;
	अचिन्हित पूर्णांक i;

	अगरace_desc = पूर्णांकf->cur_altsetting;
	क्रम (i = 0; i < अगरace_desc->desc.bNumEndpoपूर्णांकs; ++i) अणु
		epd = &अगरace_desc->endpoपूर्णांक[i].desc;
		store_endpoपूर्णांक(serial, epds, epd);
	पूर्ण
पूर्ण

अटल पूर्णांक setup_port_bulk_in(काष्ठा usb_serial_port *port,
					काष्ठा usb_endpoपूर्णांक_descriptor *epd)
अणु
	काष्ठा usb_serial_driver *type = port->serial->type;
	काष्ठा usb_device *udev = port->serial->dev;
	पूर्णांक buffer_size;
	पूर्णांक i;

	buffer_size = max_t(पूर्णांक, type->bulk_in_size, usb_endpoपूर्णांक_maxp(epd));
	port->bulk_in_size = buffer_size;
	port->bulk_in_endpoपूर्णांकAddress = epd->bEndpoपूर्णांकAddress;

	क्रम (i = 0; i < ARRAY_SIZE(port->पढ़ो_urbs); ++i) अणु
		set_bit(i, &port->पढ़ो_urbs_मुक्त);
		port->पढ़ो_urbs[i] = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!port->पढ़ो_urbs[i])
			वापस -ENOMEM;
		port->bulk_in_buffers[i] = kदो_स्मृति(buffer_size, GFP_KERNEL);
		अगर (!port->bulk_in_buffers[i])
			वापस -ENOMEM;
		usb_fill_bulk_urb(port->पढ़ो_urbs[i], udev,
				usb_rcvbulkpipe(udev, epd->bEndpoपूर्णांकAddress),
				port->bulk_in_buffers[i], buffer_size,
				type->पढ़ो_bulk_callback, port);
	पूर्ण

	port->पढ़ो_urb = port->पढ़ो_urbs[0];
	port->bulk_in_buffer = port->bulk_in_buffers[0];

	वापस 0;
पूर्ण

अटल पूर्णांक setup_port_bulk_out(काष्ठा usb_serial_port *port,
					काष्ठा usb_endpoपूर्णांक_descriptor *epd)
अणु
	काष्ठा usb_serial_driver *type = port->serial->type;
	काष्ठा usb_device *udev = port->serial->dev;
	पूर्णांक buffer_size;
	पूर्णांक i;

	अगर (kfअगरo_alloc(&port->ग_लिखो_fअगरo, PAGE_SIZE, GFP_KERNEL))
		वापस -ENOMEM;
	अगर (type->bulk_out_size)
		buffer_size = type->bulk_out_size;
	अन्यथा
		buffer_size = usb_endpoपूर्णांक_maxp(epd);
	port->bulk_out_size = buffer_size;
	port->bulk_out_endpoपूर्णांकAddress = epd->bEndpoपूर्णांकAddress;

	क्रम (i = 0; i < ARRAY_SIZE(port->ग_लिखो_urbs); ++i) अणु
		set_bit(i, &port->ग_लिखो_urbs_मुक्त);
		port->ग_लिखो_urbs[i] = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!port->ग_लिखो_urbs[i])
			वापस -ENOMEM;
		port->bulk_out_buffers[i] = kदो_स्मृति(buffer_size, GFP_KERNEL);
		अगर (!port->bulk_out_buffers[i])
			वापस -ENOMEM;
		usb_fill_bulk_urb(port->ग_लिखो_urbs[i], udev,
				usb_sndbulkpipe(udev, epd->bEndpoपूर्णांकAddress),
				port->bulk_out_buffers[i], buffer_size,
				type->ग_लिखो_bulk_callback, port);
	पूर्ण

	port->ग_लिखो_urb = port->ग_लिखो_urbs[0];
	port->bulk_out_buffer = port->bulk_out_buffers[0];

	वापस 0;
पूर्ण

अटल पूर्णांक setup_port_पूर्णांकerrupt_in(काष्ठा usb_serial_port *port,
					काष्ठा usb_endpoपूर्णांक_descriptor *epd)
अणु
	काष्ठा usb_serial_driver *type = port->serial->type;
	काष्ठा usb_device *udev = port->serial->dev;
	पूर्णांक buffer_size;

	port->पूर्णांकerrupt_in_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!port->पूर्णांकerrupt_in_urb)
		वापस -ENOMEM;
	buffer_size = usb_endpoपूर्णांक_maxp(epd);
	port->पूर्णांकerrupt_in_endpoपूर्णांकAddress = epd->bEndpoपूर्णांकAddress;
	port->पूर्णांकerrupt_in_buffer = kदो_स्मृति(buffer_size, GFP_KERNEL);
	अगर (!port->पूर्णांकerrupt_in_buffer)
		वापस -ENOMEM;
	usb_fill_पूर्णांक_urb(port->पूर्णांकerrupt_in_urb, udev,
			usb_rcvपूर्णांकpipe(udev, epd->bEndpoपूर्णांकAddress),
			port->पूर्णांकerrupt_in_buffer, buffer_size,
			type->पढ़ो_पूर्णांक_callback, port,
			epd->bInterval);

	वापस 0;
पूर्ण

अटल पूर्णांक setup_port_पूर्णांकerrupt_out(काष्ठा usb_serial_port *port,
					काष्ठा usb_endpoपूर्णांक_descriptor *epd)
अणु
	काष्ठा usb_serial_driver *type = port->serial->type;
	काष्ठा usb_device *udev = port->serial->dev;
	पूर्णांक buffer_size;

	port->पूर्णांकerrupt_out_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!port->पूर्णांकerrupt_out_urb)
		वापस -ENOMEM;
	buffer_size = usb_endpoपूर्णांक_maxp(epd);
	port->पूर्णांकerrupt_out_size = buffer_size;
	port->पूर्णांकerrupt_out_endpoपूर्णांकAddress = epd->bEndpoपूर्णांकAddress;
	port->पूर्णांकerrupt_out_buffer = kदो_स्मृति(buffer_size, GFP_KERNEL);
	अगर (!port->पूर्णांकerrupt_out_buffer)
		वापस -ENOMEM;
	usb_fill_पूर्णांक_urb(port->पूर्णांकerrupt_out_urb, udev,
			usb_sndपूर्णांकpipe(udev, epd->bEndpoपूर्णांकAddress),
			port->पूर्णांकerrupt_out_buffer, buffer_size,
			type->ग_लिखो_पूर्णांक_callback, port,
			epd->bInterval);

	वापस 0;
पूर्ण

अटल पूर्णांक usb_serial_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			       स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा device *ddev = &पूर्णांकerface->dev;
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	काष्ठा usb_serial *serial = शून्य;
	काष्ठा usb_serial_port *port;
	काष्ठा usb_serial_endpoपूर्णांकs *epds;
	काष्ठा usb_serial_driver *type = शून्य;
	पूर्णांक retval;
	पूर्णांक i;
	पूर्णांक num_ports = 0;
	अचिन्हित अक्षर max_endpoपूर्णांकs;

	mutex_lock(&table_lock);
	type = search_serial_device(पूर्णांकerface);
	अगर (!type) अणु
		mutex_unlock(&table_lock);
		dev_dbg(ddev, "none matched\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!try_module_get(type->driver.owner)) अणु
		mutex_unlock(&table_lock);
		dev_err(ddev, "module get failed, exiting\n");
		वापस -EIO;
	पूर्ण
	mutex_unlock(&table_lock);

	serial = create_serial(dev, पूर्णांकerface, type);
	अगर (!serial) अणु
		retval = -ENOMEM;
		जाओ err_put_module;
	पूर्ण

	/* अगर this device type has a probe function, call it */
	अगर (type->probe) अणु
		स्थिर काष्ठा usb_device_id *id;

		id = get_अगरace_id(type, पूर्णांकerface);
		retval = type->probe(serial, id);

		अगर (retval) अणु
			dev_dbg(ddev, "sub driver rejected device\n");
			जाओ err_release_sibling;
		पूर्ण
	पूर्ण

	/* descriptor matches, let's find the endpoपूर्णांकs needed */
	epds = kzalloc(माप(*epds), GFP_KERNEL);
	अगर (!epds) अणु
		retval = -ENOMEM;
		जाओ err_release_sibling;
	पूर्ण

	find_endpoपूर्णांकs(serial, epds, पूर्णांकerface);
	अगर (serial->sibling)
		find_endpoपूर्णांकs(serial, epds, serial->sibling);

	अगर (epds->num_bulk_in < type->num_bulk_in ||
			epds->num_bulk_out < type->num_bulk_out ||
			epds->num_पूर्णांकerrupt_in < type->num_पूर्णांकerrupt_in ||
			epds->num_पूर्णांकerrupt_out < type->num_पूर्णांकerrupt_out) अणु
		dev_err(ddev, "required endpoints missing\n");
		retval = -ENODEV;
		जाओ err_मुक्त_epds;
	पूर्ण

	अगर (type->calc_num_ports) अणु
		retval = type->calc_num_ports(serial, epds);
		अगर (retval < 0)
			जाओ err_मुक्त_epds;
		num_ports = retval;
	पूर्ण

	अगर (!num_ports)
		num_ports = type->num_ports;

	अगर (num_ports > MAX_NUM_PORTS) अणु
		dev_warn(ddev, "too many ports requested: %d\n", num_ports);
		num_ports = MAX_NUM_PORTS;
	पूर्ण

	serial->num_ports = (अचिन्हित अक्षर)num_ports;
	serial->num_bulk_in = epds->num_bulk_in;
	serial->num_bulk_out = epds->num_bulk_out;
	serial->num_पूर्णांकerrupt_in = epds->num_पूर्णांकerrupt_in;
	serial->num_पूर्णांकerrupt_out = epds->num_पूर्णांकerrupt_out;

	/* found all that we need */
	dev_info(ddev, "%s converter detected\n", type->description);

	/* create our ports, we need as many as the max endpoपूर्णांकs */
	/* we करोn't use num_ports here because some devices have more
	   endpoपूर्णांक pairs than ports */
	max_endpoपूर्णांकs = max(epds->num_bulk_in, epds->num_bulk_out);
	max_endpoपूर्णांकs = max(max_endpoपूर्णांकs, epds->num_पूर्णांकerrupt_in);
	max_endpoपूर्णांकs = max(max_endpoपूर्णांकs, epds->num_पूर्णांकerrupt_out);
	max_endpoपूर्णांकs = max(max_endpoपूर्णांकs, serial->num_ports);
	serial->num_port_poपूर्णांकers = max_endpoपूर्णांकs;

	dev_dbg(ddev, "setting up %d port structure(s)\n", max_endpoपूर्णांकs);
	क्रम (i = 0; i < max_endpoपूर्णांकs; ++i) अणु
		port = kzalloc(माप(काष्ठा usb_serial_port), GFP_KERNEL);
		अगर (!port) अणु
			retval = -ENOMEM;
			जाओ err_मुक्त_epds;
		पूर्ण
		tty_port_init(&port->port);
		port->port.ops = &serial_port_ops;
		port->serial = serial;
		spin_lock_init(&port->lock);
		/* Keep this क्रम निजी driver use क्रम the moment but
		   should probably go away */
		INIT_WORK(&port->work, usb_serial_port_work);
		serial->port[i] = port;
		port->dev.parent = &पूर्णांकerface->dev;
		port->dev.driver = शून्य;
		port->dev.bus = &usb_serial_bus_type;
		port->dev.release = &usb_serial_port_release;
		port->dev.groups = usb_serial_port_groups;
		device_initialize(&port->dev);
	पूर्ण

	/* set up the endpoपूर्णांक inक्रमmation */
	क्रम (i = 0; i < epds->num_bulk_in; ++i) अणु
		retval = setup_port_bulk_in(serial->port[i], epds->bulk_in[i]);
		अगर (retval)
			जाओ err_मुक्त_epds;
	पूर्ण

	क्रम (i = 0; i < epds->num_bulk_out; ++i) अणु
		retval = setup_port_bulk_out(serial->port[i],
				epds->bulk_out[i]);
		अगर (retval)
			जाओ err_मुक्त_epds;
	पूर्ण

	अगर (serial->type->पढ़ो_पूर्णांक_callback) अणु
		क्रम (i = 0; i < epds->num_पूर्णांकerrupt_in; ++i) अणु
			retval = setup_port_पूर्णांकerrupt_in(serial->port[i],
					epds->पूर्णांकerrupt_in[i]);
			अगर (retval)
				जाओ err_मुक्त_epds;
		पूर्ण
	पूर्ण अन्यथा अगर (epds->num_पूर्णांकerrupt_in) अणु
		dev_dbg(ddev, "The device claims to support interrupt in transfers, but read_int_callback is not defined\n");
	पूर्ण

	अगर (serial->type->ग_लिखो_पूर्णांक_callback) अणु
		क्रम (i = 0; i < epds->num_पूर्णांकerrupt_out; ++i) अणु
			retval = setup_port_पूर्णांकerrupt_out(serial->port[i],
					epds->पूर्णांकerrupt_out[i]);
			अगर (retval)
				जाओ err_मुक्त_epds;
		पूर्ण
	पूर्ण अन्यथा अगर (epds->num_पूर्णांकerrupt_out) अणु
		dev_dbg(ddev, "The device claims to support interrupt out transfers, but write_int_callback is not defined\n");
	पूर्ण

	usb_set_पूर्णांकfdata(पूर्णांकerface, serial);

	/* अगर this device type has an attach function, call it */
	अगर (type->attach) अणु
		retval = type->attach(serial);
		अगर (retval < 0)
			जाओ err_मुक्त_epds;
		serial->attached = 1;
		अगर (retval > 0) अणु
			/* quietly accept this device, but करोn't bind to a
			   serial port as it's about to disappear */
			serial->num_ports = 0;
			जाओ निकास;
		पूर्ण
	पूर्ण अन्यथा अणु
		serial->attached = 1;
	पूर्ण

	retval = allocate_minors(serial, num_ports);
	अगर (retval) अणु
		dev_err(ddev, "No more free serial minor numbers\n");
		जाओ err_मुक्त_epds;
	पूर्ण

	/* रेजिस्टर all of the inभागidual ports with the driver core */
	क्रम (i = 0; i < num_ports; ++i) अणु
		port = serial->port[i];
		dev_set_name(&port->dev, "ttyUSB%d", port->minor);
		dev_dbg(ddev, "registering %s\n", dev_name(&port->dev));
		device_enable_async_suspend(&port->dev);

		retval = device_add(&port->dev);
		अगर (retval)
			dev_err(ddev, "Error registering port device, continuing\n");
	पूर्ण

	अगर (num_ports > 0)
		usb_serial_console_init(serial->port[0]->minor);
निकास:
	kमुक्त(epds);
	module_put(type->driver.owner);
	वापस 0;

err_मुक्त_epds:
	kमुक्त(epds);
err_release_sibling:
	release_sibling(serial, पूर्णांकerface);
	usb_serial_put(serial);
err_put_module:
	module_put(type->driver.owner);

	वापस retval;
पूर्ण

अटल व्योम usb_serial_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	पूर्णांक i;
	काष्ठा usb_serial *serial = usb_get_पूर्णांकfdata(पूर्णांकerface);
	काष्ठा device *dev = &पूर्णांकerface->dev;
	काष्ठा usb_serial_port *port;
	काष्ठा tty_काष्ठा *tty;

	/* sibling पूर्णांकerface is cleaning up */
	अगर (!serial)
		वापस;

	usb_serial_console_disconnect(serial);

	mutex_lock(&serial->disc_mutex);
	/* must set a flag, to संकेत subdrivers */
	serial->disconnected = 1;
	mutex_unlock(&serial->disc_mutex);

	क्रम (i = 0; i < serial->num_ports; ++i) अणु
		port = serial->port[i];
		tty = tty_port_tty_get(&port->port);
		अगर (tty) अणु
			tty_vhangup(tty);
			tty_kref_put(tty);
		पूर्ण
		usb_serial_port_poison_urbs(port);
		wake_up_पूर्णांकerruptible(&port->port.delta_msr_रुको);
		cancel_work_sync(&port->work);
		अगर (device_is_रेजिस्टरed(&port->dev))
			device_del(&port->dev);
	पूर्ण
	अगर (serial->type->disconnect)
		serial->type->disconnect(serial);

	release_sibling(serial, पूर्णांकerface);

	/* let the last holder of this object cause it to be cleaned up */
	usb_serial_put(serial);
	dev_info(dev, "device disconnected\n");
पूर्ण

पूर्णांक usb_serial_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा usb_serial *serial = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक i, r;

	/* suspend when called क्रम first sibling पूर्णांकerface */
	अगर (serial->suspend_count++)
		वापस 0;

	/*
	 * serial->type->suspend() MUST वापस 0 in प्रणाली sleep context,
	 * otherwise, the resume callback has to recover device from
	 * previous suspend failure.
	 */
	अगर (serial->type->suspend) अणु
		r = serial->type->suspend(serial, message);
		अगर (r < 0) अणु
			serial->suspend_count--;
			वापस r;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < serial->num_ports; ++i)
		usb_serial_port_poison_urbs(serial->port[i]);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(usb_serial_suspend);

अटल व्योम usb_serial_unpoison_port_urbs(काष्ठा usb_serial *serial)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < serial->num_ports; ++i)
		usb_serial_port_unpoison_urbs(serial->port[i]);
पूर्ण

पूर्णांक usb_serial_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_serial *serial = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक rv;

	/* resume when called क्रम last sibling पूर्णांकerface */
	अगर (--serial->suspend_count)
		वापस 0;

	usb_serial_unpoison_port_urbs(serial);

	अगर (serial->type->resume)
		rv = serial->type->resume(serial);
	अन्यथा
		rv = usb_serial_generic_resume(serial);

	वापस rv;
पूर्ण
EXPORT_SYMBOL(usb_serial_resume);

अटल पूर्णांक usb_serial_reset_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_serial *serial = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक rv;

	/* resume when called क्रम last sibling पूर्णांकerface */
	अगर (--serial->suspend_count)
		वापस 0;

	usb_serial_unpoison_port_urbs(serial);

	अगर (serial->type->reset_resume) अणु
		rv = serial->type->reset_resume(serial);
	पूर्ण अन्यथा अणु
		rv = -EOPNOTSUPP;
		पूर्णांकf->needs_binding = 1;
	पूर्ण

	वापस rv;
पूर्ण

अटल स्थिर काष्ठा tty_operations serial_ops = अणु
	.खोलो =			serial_खोलो,
	.बंद =		serial_बंद,
	.ग_लिखो =		serial_ग_लिखो,
	.hangup =		serial_hangup,
	.ग_लिखो_room =		serial_ग_लिखो_room,
	.ioctl =		serial_ioctl,
	.set_termios =		serial_set_termios,
	.throttle =		serial_throttle,
	.unthrottle =		serial_unthrottle,
	.अवरोध_ctl =		serial_अवरोध,
	.अक्षरs_in_buffer =	serial_अक्षरs_in_buffer,
	.रुको_until_sent =	serial_रुको_until_sent,
	.tiocmget =		serial_tiocmget,
	.tiocmset =		serial_tiocmset,
	.get_icount =		serial_get_icount,
	.set_serial =		serial_set_serial,
	.get_serial =		serial_get_serial,
	.cleanup =		serial_cleanup,
	.install =		serial_install,
	.proc_show =		serial_proc_show,
पूर्ण;


काष्ठा tty_driver *usb_serial_tty_driver;

अटल पूर्णांक __init usb_serial_init(व्योम)
अणु
	पूर्णांक result;

	usb_serial_tty_driver = alloc_tty_driver(USB_SERIAL_TTY_MINORS);
	अगर (!usb_serial_tty_driver)
		वापस -ENOMEM;

	/* Initialize our global data */
	result = bus_रेजिस्टर(&usb_serial_bus_type);
	अगर (result) अणु
		pr_err("%s - registering bus driver failed\n", __func__);
		जाओ निकास_bus;
	पूर्ण

	usb_serial_tty_driver->driver_name = "usbserial";
	usb_serial_tty_driver->name = "ttyUSB";
	usb_serial_tty_driver->major = USB_SERIAL_TTY_MAJOR;
	usb_serial_tty_driver->minor_start = 0;
	usb_serial_tty_driver->type = TTY_DRIVER_TYPE_SERIAL;
	usb_serial_tty_driver->subtype = SERIAL_TYPE_NORMAL;
	usb_serial_tty_driver->flags = TTY_DRIVER_REAL_RAW |
						TTY_DRIVER_DYNAMIC_DEV;
	usb_serial_tty_driver->init_termios = tty_std_termios;
	usb_serial_tty_driver->init_termios.c_cflag = B9600 | CS8 | CREAD
							| HUPCL | CLOCAL;
	usb_serial_tty_driver->init_termios.c_ispeed = 9600;
	usb_serial_tty_driver->init_termios.c_ospeed = 9600;
	tty_set_operations(usb_serial_tty_driver, &serial_ops);
	result = tty_रेजिस्टर_driver(usb_serial_tty_driver);
	अगर (result) अणु
		pr_err("%s - tty_register_driver failed\n", __func__);
		जाओ निकास_reg_driver;
	पूर्ण

	/* रेजिस्टर the generic driver, अगर we should */
	result = usb_serial_generic_रेजिस्टर();
	अगर (result < 0) अणु
		pr_err("%s - registering generic driver failed\n", __func__);
		जाओ निकास_generic;
	पूर्ण

	वापस result;

निकास_generic:
	tty_unरेजिस्टर_driver(usb_serial_tty_driver);

निकास_reg_driver:
	bus_unरेजिस्टर(&usb_serial_bus_type);

निकास_bus:
	pr_err("%s - returning with error %d\n", __func__, result);
	put_tty_driver(usb_serial_tty_driver);
	वापस result;
पूर्ण


अटल व्योम __निकास usb_serial_निकास(व्योम)
अणु
	usb_serial_console_निकास();

	usb_serial_generic_deरेजिस्टर();

	tty_unरेजिस्टर_driver(usb_serial_tty_driver);
	put_tty_driver(usb_serial_tty_driver);
	bus_unरेजिस्टर(&usb_serial_bus_type);
	idr_destroy(&serial_minors);
पूर्ण


module_init(usb_serial_init);
module_निकास(usb_serial_निकास);

#घोषणा set_to_generic_अगर_null(type, function)				\
	करो अणु								\
		अगर (!type->function) अणु					\
			type->function = usb_serial_generic_##function;	\
			pr_debug("%s: using generic " #function	"\n",	\
						type->driver.name);	\
		पूर्ण							\
	पूर्ण जबतक (0)

अटल व्योम usb_serial_operations_init(काष्ठा usb_serial_driver *device)
अणु
	set_to_generic_अगर_null(device, खोलो);
	set_to_generic_अगर_null(device, ग_लिखो);
	set_to_generic_अगर_null(device, बंद);
	set_to_generic_अगर_null(device, ग_लिखो_room);
	set_to_generic_अगर_null(device, अक्षरs_in_buffer);
	अगर (device->tx_empty)
		set_to_generic_अगर_null(device, रुको_until_sent);
	set_to_generic_अगर_null(device, पढ़ो_bulk_callback);
	set_to_generic_अगर_null(device, ग_लिखो_bulk_callback);
	set_to_generic_अगर_null(device, process_पढ़ो_urb);
	set_to_generic_अगर_null(device, prepare_ग_लिखो_buffer);
पूर्ण

अटल पूर्णांक usb_serial_रेजिस्टर(काष्ठा usb_serial_driver *driver)
अणु
	पूर्णांक retval;

	अगर (usb_disabled())
		वापस -ENODEV;

	अगर (!driver->description)
		driver->description = driver->driver.name;
	अगर (!driver->usb_driver) अणु
		WARN(1, "Serial driver %s has no usb_driver\n",
				driver->description);
		वापस -EINVAL;
	पूर्ण

	/* Prevent inभागidual ports from being unbound. */
	driver->driver.suppress_bind_attrs = true;

	usb_serial_operations_init(driver);

	/* Add this device to our list of devices */
	mutex_lock(&table_lock);
	list_add(&driver->driver_list, &usb_serial_driver_list);

	retval = usb_serial_bus_रेजिस्टर(driver);
	अगर (retval) अणु
		pr_err("problem %d when registering driver %s\n", retval, driver->description);
		list_del(&driver->driver_list);
	पूर्ण अन्यथा अणु
		pr_info("USB Serial support registered for %s\n", driver->description);
	पूर्ण
	mutex_unlock(&table_lock);
	वापस retval;
पूर्ण

अटल व्योम usb_serial_deरेजिस्टर(काष्ठा usb_serial_driver *device)
अणु
	pr_info("USB Serial deregistering driver %s\n", device->description);

	mutex_lock(&table_lock);
	list_del(&device->driver_list);
	mutex_unlock(&table_lock);

	usb_serial_bus_deरेजिस्टर(device);
पूर्ण

/**
 * usb_serial_रेजिस्टर_drivers - रेजिस्टर drivers क्रम a usb-serial module
 * @serial_drivers: शून्य-terminated array of poपूर्णांकers to drivers to be रेजिस्टरed
 * @name: name of the usb_driver क्रम this set of @serial_drivers
 * @id_table: list of all devices this @serial_drivers set binds to
 *
 * Registers all the drivers in the @serial_drivers array, and dynamically
 * creates a काष्ठा usb_driver with the name @name and id_table of @id_table.
 */
पूर्णांक usb_serial_रेजिस्टर_drivers(काष्ठा usb_serial_driver *स्थिर serial_drivers[],
				स्थिर अक्षर *name,
				स्थिर काष्ठा usb_device_id *id_table)
अणु
	पूर्णांक rc;
	काष्ठा usb_driver *udriver;
	काष्ठा usb_serial_driver * स्थिर *sd;

	/*
	 * udriver must be रेजिस्टरed beक्रमe any of the serial drivers,
	 * because the store_new_id() routine क्रम the serial drivers (in
	 * bus.c) probes udriver.
	 *
	 * Perक्रमmance hack: We करोn't want udriver to be probed until
	 * the serial drivers are रेजिस्टरed, because the probe would
	 * simply fail क्रम lack of a matching serial driver.
	 * So we leave udriver's id_table set to शून्य until we are all set.
	 *
	 * Suspend/resume support is implemented in the usb-serial core,
	 * so fill in the PM-related fields in udriver.
	 */
	udriver = kzalloc(माप(*udriver), GFP_KERNEL);
	अगर (!udriver)
		वापस -ENOMEM;

	udriver->name = name;
	udriver->no_dynamic_id = 1;
	udriver->supports_स्वतःsuspend = 1;
	udriver->suspend = usb_serial_suspend;
	udriver->resume = usb_serial_resume;
	udriver->probe = usb_serial_probe;
	udriver->disconnect = usb_serial_disconnect;

	/* we only set the reset_resume field अगर the serial_driver has one */
	क्रम (sd = serial_drivers; *sd; ++sd) अणु
		अगर ((*sd)->reset_resume) अणु
			udriver->reset_resume = usb_serial_reset_resume;
			अवरोध;
		पूर्ण
	पूर्ण

	rc = usb_रेजिस्टर(udriver);
	अगर (rc)
		जाओ failed_usb_रेजिस्टर;

	क्रम (sd = serial_drivers; *sd; ++sd) अणु
		(*sd)->usb_driver = udriver;
		rc = usb_serial_रेजिस्टर(*sd);
		अगर (rc)
			जाओ failed;
	पूर्ण

	/* Now set udriver's id_table and look क्रम matches */
	udriver->id_table = id_table;
	rc = driver_attach(&udriver->drvwrap.driver);
	वापस 0;

 failed:
	जबतक (sd-- > serial_drivers)
		usb_serial_deरेजिस्टर(*sd);
	usb_deरेजिस्टर(udriver);
failed_usb_रेजिस्टर:
	kमुक्त(udriver);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(usb_serial_रेजिस्टर_drivers);

/**
 * usb_serial_deरेजिस्टर_drivers - deरेजिस्टर drivers क्रम a usb-serial module
 * @serial_drivers: शून्य-terminated array of poपूर्णांकers to drivers to be deरेजिस्टरed
 *
 * Deरेजिस्टरs all the drivers in the @serial_drivers array and deरेजिस्टरs and
 * मुक्तs the काष्ठा usb_driver that was created by the call to
 * usb_serial_रेजिस्टर_drivers().
 */
व्योम usb_serial_deरेजिस्टर_drivers(काष्ठा usb_serial_driver *स्थिर serial_drivers[])
अणु
	काष्ठा usb_driver *udriver = (*serial_drivers)->usb_driver;

	क्रम (; *serial_drivers; ++serial_drivers)
		usb_serial_deरेजिस्टर(*serial_drivers);
	usb_deरेजिस्टर(udriver);
	kमुक्त(udriver);
पूर्ण
EXPORT_SYMBOL_GPL(usb_serial_deरेजिस्टर_drivers);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL v2");
