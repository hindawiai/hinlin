<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * USB Serial Converter Generic functions
 *
 * Copyright (C) 2010 - 2013 Johan Hovold (jhovold@gmail.com)
 * Copyright (C) 1999 - 2002 Greg Kroah-Harपंचांगan (greg@kroah.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/serial.h>

#अगर_घोषित CONFIG_USB_SERIAL_GENERIC

अटल __u16 venकरोr  = 0x05f9;
अटल __u16 product = 0xffff;

module_param(venकरोr, uलघु, 0);
MODULE_PARM_DESC(venकरोr, "User specified USB idVendor");

module_param(product, uलघु, 0);
MODULE_PARM_DESC(product, "User specified USB idProduct");

अटल काष्ठा usb_device_id generic_device_ids[2]; /* Initially all zeroes. */

अटल पूर्णांक usb_serial_generic_probe(काष्ठा usb_serial *serial,
					स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा device *dev = &serial->पूर्णांकerface->dev;

	dev_info(dev, "The \"generic\" usb-serial driver is only for testing and one-off prototypes.\n");
	dev_info(dev, "Tell linux-usb@vger.kernel.org to add your device to a proper driver.\n");

	वापस 0;
पूर्ण

अटल पूर्णांक usb_serial_generic_calc_num_ports(काष्ठा usb_serial *serial,
					काष्ठा usb_serial_endpoपूर्णांकs *epds)
अणु
	काष्ठा device *dev = &serial->पूर्णांकerface->dev;
	पूर्णांक num_ports;

	num_ports = max(epds->num_bulk_in, epds->num_bulk_out);

	अगर (num_ports == 0) अणु
		dev_err(dev, "device has no bulk endpoints\n");
		वापस -ENODEV;
	पूर्ण

	वापस num_ports;
पूर्ण

अटल काष्ठा usb_serial_driver usb_serial_generic_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"generic",
	पूर्ण,
	.id_table =		generic_device_ids,
	.probe =		usb_serial_generic_probe,
	.calc_num_ports =	usb_serial_generic_calc_num_ports,
	.throttle =		usb_serial_generic_throttle,
	.unthrottle =		usb_serial_generic_unthrottle,
	.resume =		usb_serial_generic_resume,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&usb_serial_generic_device, शून्य
पूर्ण;

#पूर्ण_अगर

पूर्णांक usb_serial_generic_रेजिस्टर(व्योम)
अणु
	पूर्णांक retval = 0;

#अगर_घोषित CONFIG_USB_SERIAL_GENERIC
	generic_device_ids[0].idVenकरोr = venकरोr;
	generic_device_ids[0].idProduct = product;
	generic_device_ids[0].match_flags =
		USB_DEVICE_ID_MATCH_VENDOR | USB_DEVICE_ID_MATCH_PRODUCT;

	retval = usb_serial_रेजिस्टर_drivers(serial_drivers,
			"usbserial_generic", generic_device_ids);
#पूर्ण_अगर
	वापस retval;
पूर्ण

व्योम usb_serial_generic_deरेजिस्टर(व्योम)
अणु
#अगर_घोषित CONFIG_USB_SERIAL_GENERIC
	usb_serial_deरेजिस्टर_drivers(serial_drivers);
#पूर्ण_अगर
पूर्ण

पूर्णांक usb_serial_generic_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	पूर्णांक result = 0;

	clear_bit(USB_SERIAL_THROTTLED, &port->flags);

	अगर (port->bulk_in_size)
		result = usb_serial_generic_submit_पढ़ो_urbs(port, GFP_KERNEL);

	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(usb_serial_generic_खोलो);

व्योम usb_serial_generic_बंद(काष्ठा usb_serial_port *port)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	अगर (port->bulk_out_size) अणु
		क्रम (i = 0; i < ARRAY_SIZE(port->ग_लिखो_urbs); ++i)
			usb_समाप्त_urb(port->ग_लिखो_urbs[i]);

		spin_lock_irqsave(&port->lock, flags);
		kfअगरo_reset_out(&port->ग_लिखो_fअगरo);
		spin_unlock_irqrestore(&port->lock, flags);
	पूर्ण
	अगर (port->bulk_in_size) अणु
		क्रम (i = 0; i < ARRAY_SIZE(port->पढ़ो_urbs); ++i)
			usb_समाप्त_urb(port->पढ़ो_urbs[i]);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(usb_serial_generic_बंद);

पूर्णांक usb_serial_generic_prepare_ग_लिखो_buffer(काष्ठा usb_serial_port *port,
						व्योम *dest, माप_प्रकार size)
अणु
	वापस kfअगरo_out_locked(&port->ग_लिखो_fअगरo, dest, size, &port->lock);
पूर्ण

/**
 * usb_serial_generic_ग_लिखो_start - start writing buffered data
 * @port: usb-serial port
 * @mem_flags: flags to use क्रम memory allocations
 *
 * Serialised using USB_SERIAL_WRITE_BUSY flag.
 *
 * Return: Zero on success or अगर busy, otherwise a negative त्रुटि_सं value.
 */
पूर्णांक usb_serial_generic_ग_लिखो_start(काष्ठा usb_serial_port *port,
							gfp_t mem_flags)
अणु
	काष्ठा urb *urb;
	पूर्णांक count, result;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	अगर (test_and_set_bit_lock(USB_SERIAL_WRITE_BUSY, &port->flags))
		वापस 0;
retry:
	spin_lock_irqsave(&port->lock, flags);
	अगर (!port->ग_लिखो_urbs_मुक्त || !kfअगरo_len(&port->ग_लिखो_fअगरo)) अणु
		clear_bit_unlock(USB_SERIAL_WRITE_BUSY, &port->flags);
		spin_unlock_irqrestore(&port->lock, flags);
		वापस 0;
	पूर्ण
	i = (पूर्णांक)find_first_bit(&port->ग_लिखो_urbs_मुक्त,
						ARRAY_SIZE(port->ग_लिखो_urbs));
	spin_unlock_irqrestore(&port->lock, flags);

	urb = port->ग_लिखो_urbs[i];
	count = port->serial->type->prepare_ग_लिखो_buffer(port,
						urb->transfer_buffer,
						port->bulk_out_size);
	urb->transfer_buffer_length = count;
	usb_serial_debug_data(&port->dev, __func__, count, urb->transfer_buffer);
	spin_lock_irqsave(&port->lock, flags);
	port->tx_bytes += count;
	spin_unlock_irqrestore(&port->lock, flags);

	clear_bit(i, &port->ग_लिखो_urbs_मुक्त);
	result = usb_submit_urb(urb, mem_flags);
	अगर (result) अणु
		dev_err_console(port, "%s - error submitting urb: %d\n",
						__func__, result);
		set_bit(i, &port->ग_लिखो_urbs_मुक्त);
		spin_lock_irqsave(&port->lock, flags);
		port->tx_bytes -= count;
		spin_unlock_irqrestore(&port->lock, flags);

		clear_bit_unlock(USB_SERIAL_WRITE_BUSY, &port->flags);
		वापस result;
	पूर्ण

	जाओ retry;	/* try sending off another urb */
पूर्ण
EXPORT_SYMBOL_GPL(usb_serial_generic_ग_लिखो_start);

/**
 * usb_serial_generic_ग_लिखो - generic ग_लिखो function
 * @tty: tty क्रम the port
 * @port: usb-serial port
 * @buf: data to ग_लिखो
 * @count: number of bytes to ग_लिखो
 *
 * Return: The number of अक्षरacters buffered, which may be anything from
 * zero to @count, or a negative त्रुटि_सं value.
 */
पूर्णांक usb_serial_generic_ग_लिखो(काष्ठा tty_काष्ठा *tty,
	काष्ठा usb_serial_port *port, स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	पूर्णांक result;

	अगर (!port->bulk_out_size)
		वापस -ENODEV;

	अगर (!count)
		वापस 0;

	count = kfअगरo_in_locked(&port->ग_लिखो_fअगरo, buf, count, &port->lock);
	result = usb_serial_generic_ग_लिखो_start(port, GFP_ATOMIC);
	अगर (result)
		वापस result;

	वापस count;
पूर्ण
EXPORT_SYMBOL_GPL(usb_serial_generic_ग_लिखो);

पूर्णांक usb_serial_generic_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक room;

	अगर (!port->bulk_out_size)
		वापस 0;

	spin_lock_irqsave(&port->lock, flags);
	room = kfअगरo_avail(&port->ग_लिखो_fअगरo);
	spin_unlock_irqrestore(&port->lock, flags);

	dev_dbg(&port->dev, "%s - returns %d\n", __func__, room);
	वापस room;
पूर्ण

पूर्णांक usb_serial_generic_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक अक्षरs;

	अगर (!port->bulk_out_size)
		वापस 0;

	spin_lock_irqsave(&port->lock, flags);
	अक्षरs = kfअगरo_len(&port->ग_लिखो_fअगरo) + port->tx_bytes;
	spin_unlock_irqrestore(&port->lock, flags);

	dev_dbg(&port->dev, "%s - returns %d\n", __func__, अक्षरs);
	वापस अक्षरs;
पूर्ण
EXPORT_SYMBOL_GPL(usb_serial_generic_अक्षरs_in_buffer);

व्योम usb_serial_generic_रुको_until_sent(काष्ठा tty_काष्ठा *tty, दीर्घ समयout)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	अचिन्हित पूर्णांक bps;
	अचिन्हित दीर्घ period;
	अचिन्हित दीर्घ expire;

	bps = tty_get_baud_rate(tty);
	अगर (!bps)
		bps = 9600;	/* B0 */
	/*
	 * Use a poll-period of roughly the समय it takes to send one
	 * अक्षरacter or at least one jअगरfy.
	 */
	period = max_t(अचिन्हित दीर्घ, (10 * HZ / bps), 1);
	अगर (समयout)
		period = min_t(अचिन्हित दीर्घ, period, समयout);

	dev_dbg(&port->dev, "%s - timeout = %u ms, period = %u ms\n",
					__func__, jअगरfies_to_msecs(समयout),
					jअगरfies_to_msecs(period));
	expire = jअगरfies + समयout;
	जबतक (!port->serial->type->tx_empty(port)) अणु
		schedule_समयout_पूर्णांकerruptible(period);
		अगर (संकेत_pending(current))
			अवरोध;
		अगर (समयout && समय_after(jअगरfies, expire))
			अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(usb_serial_generic_रुको_until_sent);

अटल पूर्णांक usb_serial_generic_submit_पढ़ो_urb(काष्ठा usb_serial_port *port,
						पूर्णांक index, gfp_t mem_flags)
अणु
	पूर्णांक res;

	अगर (!test_and_clear_bit(index, &port->पढ़ो_urbs_मुक्त))
		वापस 0;

	dev_dbg(&port->dev, "%s - urb %d\n", __func__, index);

	res = usb_submit_urb(port->पढ़ो_urbs[index], mem_flags);
	अगर (res) अणु
		अगर (res != -EPERM && res != -ENODEV) अणु
			dev_err(&port->dev,
					"%s - usb_submit_urb failed: %d\n",
					__func__, res);
		पूर्ण
		set_bit(index, &port->पढ़ो_urbs_मुक्त);
		वापस res;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक usb_serial_generic_submit_पढ़ो_urbs(काष्ठा usb_serial_port *port,
					gfp_t mem_flags)
अणु
	पूर्णांक res;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(port->पढ़ो_urbs); ++i) अणु
		res = usb_serial_generic_submit_पढ़ो_urb(port, i, mem_flags);
		अगर (res)
			जाओ err;
	पूर्ण

	वापस 0;
err:
	क्रम (; i >= 0; --i)
		usb_समाप्त_urb(port->पढ़ो_urbs[i]);

	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(usb_serial_generic_submit_पढ़ो_urbs);

व्योम usb_serial_generic_process_पढ़ो_urb(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	अक्षर *ch = urb->transfer_buffer;
	पूर्णांक i;

	अगर (!urb->actual_length)
		वापस;
	/*
	 * The per अक्षरacter mucking around with sysrq path it too slow क्रम
	 * stuff like 3G modems, so लघुcircuit it in the 99.9999999% of
	 * हालs where the USB serial is not a console anyway.
	 */
	अगर (port->sysrq) अणु
		क्रम (i = 0; i < urb->actual_length; i++, ch++) अणु
			अगर (!usb_serial_handle_sysrq_अक्षर(port, *ch))
				tty_insert_flip_अक्षर(&port->port, *ch, TTY_NORMAL);
		पूर्ण
	पूर्ण अन्यथा अणु
		tty_insert_flip_string(&port->port, ch, urb->actual_length);
	पूर्ण
	tty_flip_buffer_push(&port->port);
पूर्ण
EXPORT_SYMBOL_GPL(usb_serial_generic_process_पढ़ो_urb);

व्योम usb_serial_generic_पढ़ो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;
	अचिन्हित अक्षर *data = urb->transfer_buffer;
	bool stopped = false;
	पूर्णांक status = urb->status;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(port->पढ़ो_urbs); ++i) अणु
		अगर (urb == port->पढ़ो_urbs[i])
			अवरोध;
	पूर्ण

	dev_dbg(&port->dev, "%s - urb %d, len %d\n", __func__, i,
							urb->actual_length);
	चयन (status) अणु
	हाल 0:
		usb_serial_debug_data(&port->dev, __func__, urb->actual_length,
							data);
		port->serial->type->process_पढ़ो_urb(urb);
		अवरोध;
	हाल -ENOENT:
	हाल -ECONNRESET:
	हाल -ESHUTDOWN:
		dev_dbg(&port->dev, "%s - urb stopped: %d\n",
							__func__, status);
		stopped = true;
		अवरोध;
	हाल -EPIPE:
		dev_err(&port->dev, "%s - urb stopped: %d\n",
							__func__, status);
		stopped = true;
		अवरोध;
	शेष:
		dev_dbg(&port->dev, "%s - nonzero urb status: %d\n",
							__func__, status);
		अवरोध;
	पूर्ण

	/*
	 * Make sure URB processing is करोne beक्रमe marking as मुक्त to aव्योम
	 * racing with unthrottle() on another CPU. Matches the barriers
	 * implied by the test_and_clear_bit() in
	 * usb_serial_generic_submit_पढ़ो_urb().
	 */
	smp_mb__beक्रमe_atomic();
	set_bit(i, &port->पढ़ो_urbs_मुक्त);
	/*
	 * Make sure URB is marked as मुक्त beक्रमe checking the throttled flag
	 * to aव्योम racing with unthrottle() on another CPU. Matches the
	 * smp_mb__after_atomic() in unthrottle().
	 */
	smp_mb__after_atomic();

	अगर (stopped)
		वापस;

	अगर (test_bit(USB_SERIAL_THROTTLED, &port->flags))
		वापस;

	usb_serial_generic_submit_पढ़ो_urb(port, i, GFP_ATOMIC);
पूर्ण
EXPORT_SYMBOL_GPL(usb_serial_generic_पढ़ो_bulk_callback);

व्योम usb_serial_generic_ग_लिखो_bulk_callback(काष्ठा urb *urb)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा usb_serial_port *port = urb->context;
	पूर्णांक status = urb->status;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(port->ग_लिखो_urbs); ++i) अणु
		अगर (port->ग_लिखो_urbs[i] == urb)
			अवरोध;
	पूर्ण
	spin_lock_irqsave(&port->lock, flags);
	port->tx_bytes -= urb->transfer_buffer_length;
	set_bit(i, &port->ग_लिखो_urbs_मुक्त);
	spin_unlock_irqrestore(&port->lock, flags);

	चयन (status) अणु
	हाल 0:
		अवरोध;
	हाल -ENOENT:
	हाल -ECONNRESET:
	हाल -ESHUTDOWN:
		dev_dbg(&port->dev, "%s - urb stopped: %d\n",
							__func__, status);
		वापस;
	हाल -EPIPE:
		dev_err_console(port, "%s - urb stopped: %d\n",
							__func__, status);
		वापस;
	शेष:
		dev_err_console(port, "%s - nonzero urb status: %d\n",
							__func__, status);
		अवरोध;
	पूर्ण

	usb_serial_generic_ग_लिखो_start(port, GFP_ATOMIC);
	usb_serial_port_softपूर्णांक(port);
पूर्ण
EXPORT_SYMBOL_GPL(usb_serial_generic_ग_लिखो_bulk_callback);

व्योम usb_serial_generic_throttle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;

	set_bit(USB_SERIAL_THROTTLED, &port->flags);
पूर्ण
EXPORT_SYMBOL_GPL(usb_serial_generic_throttle);

व्योम usb_serial_generic_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;

	clear_bit(USB_SERIAL_THROTTLED, &port->flags);

	/*
	 * Matches the smp_mb__after_atomic() in
	 * usb_serial_generic_पढ़ो_bulk_callback().
	 */
	smp_mb__after_atomic();

	usb_serial_generic_submit_पढ़ो_urbs(port, GFP_KERNEL);
पूर्ण
EXPORT_SYMBOL_GPL(usb_serial_generic_unthrottle);

अटल bool usb_serial_generic_msr_changed(काष्ठा tty_काष्ठा *tty,
				अचिन्हित दीर्घ arg, काष्ठा async_icount *cprev)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा async_icount cnow;
	अचिन्हित दीर्घ flags;
	bool ret;

	/*
	 * Use tty-port initialised flag to detect all hangups including the
	 * one generated at USB-device disconnect.
	 */
	अगर (!tty_port_initialized(&port->port))
		वापस true;

	spin_lock_irqsave(&port->lock, flags);
	cnow = port->icount;				/* atomic copy*/
	spin_unlock_irqrestore(&port->lock, flags);

	ret =	((arg & TIOCM_RNG) && (cnow.rng != cprev->rng)) ||
		((arg & TIOCM_DSR) && (cnow.dsr != cprev->dsr)) ||
		((arg & TIOCM_CD)  && (cnow.dcd != cprev->dcd)) ||
		((arg & TIOCM_CTS) && (cnow.cts != cprev->cts));

	*cprev = cnow;

	वापस ret;
पूर्ण

पूर्णांक usb_serial_generic_tiocmiरुको(काष्ठा tty_काष्ठा *tty, अचिन्हित दीर्घ arg)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा async_icount cnow;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&port->lock, flags);
	cnow = port->icount;				/* atomic copy */
	spin_unlock_irqrestore(&port->lock, flags);

	ret = रुको_event_पूर्णांकerruptible(port->port.delta_msr_रुको,
			usb_serial_generic_msr_changed(tty, arg, &cnow));
	अगर (!ret && !tty_port_initialized(&port->port))
		ret = -EIO;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_serial_generic_tiocmiरुको);

पूर्णांक usb_serial_generic_get_icount(काष्ठा tty_काष्ठा *tty,
					काष्ठा serial_icounter_काष्ठा *icount)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा async_icount cnow;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);
	cnow = port->icount;				/* atomic copy */
	spin_unlock_irqrestore(&port->lock, flags);

	icount->cts = cnow.cts;
	icount->dsr = cnow.dsr;
	icount->rng = cnow.rng;
	icount->dcd = cnow.dcd;
	icount->tx = cnow.tx;
	icount->rx = cnow.rx;
	icount->frame = cnow.frame;
	icount->parity = cnow.parity;
	icount->overrun = cnow.overrun;
	icount->brk = cnow.brk;
	icount->buf_overrun = cnow.buf_overrun;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usb_serial_generic_get_icount);

#अगर defined(CONFIG_USB_SERIAL_CONSOLE) && defined(CONFIG_MAGIC_SYSRQ)
पूर्णांक usb_serial_handle_sysrq_अक्षर(काष्ठा usb_serial_port *port, अचिन्हित पूर्णांक ch)
अणु
	अगर (port->sysrq) अणु
		अगर (ch && समय_beक्रमe(jअगरfies, port->sysrq)) अणु
			handle_sysrq(ch);
			port->sysrq = 0;
			वापस 1;
		पूर्ण
		port->sysrq = 0;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usb_serial_handle_sysrq_अक्षर);

पूर्णांक usb_serial_handle_अवरोध(काष्ठा usb_serial_port *port)
अणु
	अगर (!port->port.console)
		वापस 0;

	अगर (!port->sysrq) अणु
		port->sysrq = jअगरfies + HZ*5;
		वापस 1;
	पूर्ण
	port->sysrq = 0;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usb_serial_handle_अवरोध);
#पूर्ण_अगर

/**
 * usb_serial_handle_dcd_change - handle a change of carrier detect state
 * @port: usb-serial port
 * @tty: tty क्रम the port
 * @status: new carrier detect status, nonzero अगर active
 */
व्योम usb_serial_handle_dcd_change(काष्ठा usb_serial_port *port,
				काष्ठा tty_काष्ठा *tty, अचिन्हित पूर्णांक status)
अणु
	dev_dbg(&port->dev, "%s - status %d\n", __func__, status);

	अगर (tty) अणु
		काष्ठा tty_ldisc *ld = tty_ldisc_ref(tty);

		अगर (ld) अणु
			अगर (ld->ops->dcd_change)
				ld->ops->dcd_change(tty, status);
			tty_ldisc_deref(ld);
		पूर्ण
	पूर्ण

	अगर (status)
		wake_up_पूर्णांकerruptible(&port->port.खोलो_रुको);
	अन्यथा अगर (tty && !C_CLOCAL(tty))
		tty_hangup(tty);
पूर्ण
EXPORT_SYMBOL_GPL(usb_serial_handle_dcd_change);

पूर्णांक usb_serial_generic_resume(काष्ठा usb_serial *serial)
अणु
	काष्ठा usb_serial_port *port;
	पूर्णांक i, c = 0, r;

	क्रम (i = 0; i < serial->num_ports; i++) अणु
		port = serial->port[i];
		अगर (!tty_port_initialized(&port->port))
			जारी;

		अगर (port->bulk_in_size) अणु
			r = usb_serial_generic_submit_पढ़ो_urbs(port,
								GFP_NOIO);
			अगर (r < 0)
				c++;
		पूर्ण

		अगर (port->bulk_out_size) अणु
			r = usb_serial_generic_ग_लिखो_start(port, GFP_NOIO);
			अगर (r < 0)
				c++;
		पूर्ण
	पूर्ण

	वापस c ? -EIO : 0;
पूर्ण
EXPORT_SYMBOL_GPL(usb_serial_generic_resume);
