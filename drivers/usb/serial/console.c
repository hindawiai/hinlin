<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * USB Serial Console driver
 *
 * Copyright (C) 2001 - 2002 Greg Kroah-Harपंचांगan (greg@kroah.com)
 *
 * Thanks to Randy Dunlap क्रम the original version of this code.
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/console.h>
#समावेश <linux/serial.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>

काष्ठा usbcons_info अणु
	पूर्णांक			magic;
	पूर्णांक			अवरोध_flag;
	काष्ठा usb_serial_port	*port;
पूर्ण;

अटल काष्ठा usbcons_info usbcons_info;
अटल काष्ठा console usbcons;

/*
 * ------------------------------------------------------------
 * USB Serial console driver
 *
 * Much of the code here is copied from drivers/अक्षर/serial.c
 * and implements a phony serial console in the same way that
 * serial.c करोes so that in हाल some software queries it,
 * it will get the same results.
 *
 * Things that are dअगरferent from the way the serial port code
 * करोes things, is that we call the lower level usb-serial
 * driver code to initialize the device, and we set the initial
 * console speeds based on the command line arguments.
 * ------------------------------------------------------------
 */

अटल स्थिर काष्ठा tty_operations usb_console_fake_tty_ops = अणु
पूर्ण;

/*
 * The parsing of the command line works exactly like the
 * serial.c code, except that the specअगरier is "ttyUSB" instead
 * of "ttyS".
 */
अटल पूर्णांक usb_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा usbcons_info *info = &usbcons_info;
	पूर्णांक baud = 9600;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक करोflow = 0;
	पूर्णांक cflag = CREAD | HUPCL | CLOCAL;
	अक्षर *s;
	काष्ठा usb_serial *serial;
	काष्ठा usb_serial_port *port;
	पूर्णांक retval;
	काष्ठा tty_काष्ठा *tty = शून्य;
	काष्ठा ktermios dummy;

	अगर (options) अणु
		baud = simple_म_से_अदीर्घ(options, शून्य, 10);
		s = options;
		जबतक (*s >= '0' && *s <= '9')
			s++;
		अगर (*s)
			parity = *s++;
		अगर (*s)
			bits   = *s++ - '0';
		अगर (*s)
			करोflow = (*s++ == 'r');
	पूर्ण

	/* Sane शेष */
	अगर (baud == 0)
		baud = 9600;

	चयन (bits) अणु
	हाल 7:
		cflag |= CS7;
		अवरोध;
	शेष:
	हाल 8:
		cflag |= CS8;
		अवरोध;
	पूर्ण
	चयन (parity) अणु
	हाल 'o': case 'O':
		cflag |= PARODD;
		अवरोध;
	हाल 'e': case 'E':
		cflag |= PARENB;
		अवरोध;
	पूर्ण

	अगर (करोflow)
		cflag |= CRTSCTS;

	/*
	 * no need to check the index here: अगर the index is wrong, console
	 * code won't call us
	 */
	port = usb_serial_port_get_by_minor(co->index);
	अगर (port == शून्य) अणु
		/* no device is connected yet, sorry :( */
		pr_err("No USB device connected to ttyUSB%i\n", co->index);
		वापस -ENODEV;
	पूर्ण
	serial = port->serial;

	retval = usb_स्वतःpm_get_पूर्णांकerface(serial->पूर्णांकerface);
	अगर (retval)
		जाओ error_get_पूर्णांकerface;

	tty_port_tty_set(&port->port, शून्य);

	info->port = port;

	++port->port.count;
	अगर (!tty_port_initialized(&port->port)) अणु
		अगर (serial->type->set_termios) अणु
			/*
			 * allocate a fake tty so the driver can initialize
			 * the termios काष्ठाure, then later call set_termios to
			 * configure according to command line arguments
			 */
			tty = kzalloc(माप(*tty), GFP_KERNEL);
			अगर (!tty) अणु
				retval = -ENOMEM;
				जाओ reset_खोलो_count;
			पूर्ण
			kref_init(&tty->kref);
			tty->driver = usb_serial_tty_driver;
			tty->index = co->index;
			init_ldsem(&tty->ldisc_sem);
			spin_lock_init(&tty->files_lock);
			INIT_LIST_HEAD(&tty->tty_files);
			kref_get(&tty->driver->kref);
			__module_get(tty->driver->owner);
			tty->ops = &usb_console_fake_tty_ops;
			tty_init_termios(tty);
			tty_port_tty_set(&port->port, tty);
		पूर्ण

		/* only call the device specअगरic खोलो अगर this
		 * is the first समय the port is खोलोed */
		retval = serial->type->खोलो(शून्य, port);
		अगर (retval) अणु
			dev_err(&port->dev, "could not open USB console port\n");
			जाओ fail;
		पूर्ण

		अगर (serial->type->set_termios) अणु
			tty->termios.c_cflag = cflag;
			tty_termios_encode_baud_rate(&tty->termios, baud, baud);
			स_रखो(&dummy, 0, माप(काष्ठा ktermios));
			serial->type->set_termios(tty, port, &dummy);

			tty_port_tty_set(&port->port, शून्य);
			tty_save_termios(tty);
			tty_kref_put(tty);
		पूर्ण
		tty_port_set_initialized(&port->port, 1);
	पूर्ण
	/* Now that any required fake tty operations are completed restore
	 * the tty port count */
	--port->port.count;
	/* The console is special in terms of closing the device so
	 * indicate this port is now acting as a प्रणाली console. */
	port->port.console = 1;

	mutex_unlock(&serial->disc_mutex);
	वापस retval;

 fail:
	tty_port_tty_set(&port->port, शून्य);
	tty_kref_put(tty);
 reset_खोलो_count:
	port->port.count = 0;
	info->port = शून्य;
	usb_स्वतःpm_put_पूर्णांकerface(serial->पूर्णांकerface);
 error_get_पूर्णांकerface:
	usb_serial_put(serial);
	mutex_unlock(&serial->disc_mutex);
	वापस retval;
पूर्ण

अटल व्योम usb_console_ग_लिखो(काष्ठा console *co,
					स्थिर अक्षर *buf, अचिन्हित count)
अणु
	अटल काष्ठा usbcons_info *info = &usbcons_info;
	काष्ठा usb_serial_port *port = info->port;
	काष्ठा usb_serial *serial;
	पूर्णांक retval = -ENODEV;

	अगर (!port || port->serial->dev->state == USB_STATE_NOTATTACHED)
		वापस;
	serial = port->serial;

	अगर (count == 0)
		वापस;

	dev_dbg(&port->dev, "%s - %d byte(s)\n", __func__, count);

	अगर (!port->port.console) अणु
		dev_dbg(&port->dev, "%s - port not opened\n", __func__);
		वापस;
	पूर्ण

	जबतक (count) अणु
		अचिन्हित पूर्णांक i;
		अचिन्हित पूर्णांक lf;
		/* search क्रम LF so we can insert CR अगर necessary */
		क्रम (i = 0, lf = 0 ; i < count ; i++) अणु
			अगर (*(buf + i) == 10) अणु
				lf = 1;
				i++;
				अवरोध;
			पूर्ण
		पूर्ण
		/* pass on to the driver specअगरic version of this function अगर
		   it is available */
		retval = serial->type->ग_लिखो(शून्य, port, buf, i);
		dev_dbg(&port->dev, "%s - write: %d\n", __func__, retval);
		अगर (lf) अणु
			/* append CR after LF */
			अचिन्हित अक्षर cr = 13;
			retval = serial->type->ग_लिखो(शून्य, port, &cr, 1);
			dev_dbg(&port->dev, "%s - write cr: %d\n",
							__func__, retval);
		पूर्ण
		buf += i;
		count -= i;
	पूर्ण
पूर्ण

अटल काष्ठा tty_driver *usb_console_device(काष्ठा console *co, पूर्णांक *index)
अणु
	काष्ठा tty_driver **p = (काष्ठा tty_driver **)co->data;

	अगर (!*p)
		वापस शून्य;

	*index = co->index;
	वापस *p;
पूर्ण

अटल काष्ठा console usbcons = अणु
	.name =		"ttyUSB",
	.ग_लिखो =	usb_console_ग_लिखो,
	.device =	usb_console_device,
	.setup =	usb_console_setup,
	.flags =	CON_PRINTBUFFER,
	.index =	-1,
	.data = 	&usb_serial_tty_driver,
पूर्ण;

व्योम usb_serial_console_disconnect(काष्ठा usb_serial *serial)
अणु
	अगर (serial->port[0] && serial->port[0] == usbcons_info.port) अणु
		usb_serial_console_निकास();
		usb_serial_put(serial);
	पूर्ण
पूर्ण

व्योम usb_serial_console_init(पूर्णांक minor)
अणु
	अगर (minor == 0) अणु
		/*
		 * Call रेजिस्टर_console() अगर this is the first device plugged
		 * in.  If we call it earlier, then the callback to
		 * console_setup() will fail, as there is not a device seen by
		 * the USB subप्रणाली yet.
		 */
		/*
		 * Register console.
		 * NOTES:
		 * console_setup() is called (back) immediately (from
		 * रेजिस्टर_console). console_ग_लिखो() is called immediately
		 * from रेजिस्टर_console अगरf CON_PRINTBUFFER is set in flags.
		 */
		pr_debug("registering the USB serial console.\n");
		रेजिस्टर_console(&usbcons);
	पूर्ण
पूर्ण

व्योम usb_serial_console_निकास(व्योम)
अणु
	अगर (usbcons_info.port) अणु
		unरेजिस्टर_console(&usbcons);
		usbcons_info.port->port.console = 0;
		usbcons_info.port = शून्य;
	पूर्ण
पूर्ण

