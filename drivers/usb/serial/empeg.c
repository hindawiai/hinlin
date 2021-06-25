<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * USB Empeg empeg-car player driver
 *
 *	Copyright (C) 2000, 2001
 *	    Gary Brubaker (xavyer@ix.netcom.com)
 *
 *	Copyright (C) 1999 - 2001
 *	    Greg Kroah-Harपंचांगan (greg@kroah.com)
 *
 * See Documentation/usb/usb-serial.rst क्रम more inक्रमmation on using this
 * driver
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>

#घोषणा DRIVER_AUTHOR "Greg Kroah-Hartman <greg@kroah.com>, Gary Brubaker <xavyer@ix.netcom.com>"
#घोषणा DRIVER_DESC "USB Empeg Mark I/II Driver"

#घोषणा EMPEG_VENDOR_ID			0x084f
#घोषणा EMPEG_PRODUCT_ID		0x0001

/* function prototypes क्रम an empeg-car player */
अटल पूर्णांक  empeg_startup(काष्ठा usb_serial *serial);
अटल व्योम empeg_init_termios(काष्ठा tty_काष्ठा *tty);

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE(EMPEG_VENDOR_ID, EMPEG_PRODUCT_ID) पूर्ण,
	अणु पूर्ण					/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, id_table);

अटल काष्ठा usb_serial_driver empeg_device = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"empeg",
	पूर्ण,
	.id_table =		id_table,
	.num_ports =		1,
	.bulk_out_size =	256,
	.throttle =		usb_serial_generic_throttle,
	.unthrottle =		usb_serial_generic_unthrottle,
	.attach =		empeg_startup,
	.init_termios =		empeg_init_termios,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&empeg_device, शून्य
पूर्ण;

अटल पूर्णांक empeg_startup(काष्ठा usb_serial *serial)
अणु
	पूर्णांक r;

	अगर (serial->dev->actconfig->desc.bConfigurationValue != 1) अणु
		dev_err(&serial->dev->dev, "active config #%d != 1 ??\n",
			serial->dev->actconfig->desc.bConfigurationValue);
		वापस -ENODEV;
	पूर्ण

	r = usb_reset_configuration(serial->dev);

	/* जारी on with initialization */
	वापस r;
पूर्ण

अटल व्योम empeg_init_termios(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा ktermios *termios = &tty->termios;

	/*
	 * The empeg-car player wants these particular tty settings.
	 * You could, क्रम example, change the baud rate, however the
	 * player only supports 115200 (currently), so there is really
	 * no poपूर्णांक in support क्रम changes to the tty settings.
	 * (at least क्रम now)
	 *
	 * The शेष requirements क्रम this device are:
	 */
	termios->c_अगरlag
		&= ~(IGNBRK	/* disable ignore अवरोध */
		| BRKINT	/* disable अवरोध causes पूर्णांकerrupt */
		| PARMRK	/* disable mark parity errors */
		| ISTRIP	/* disable clear high bit of input अक्षरacters */
		| INLCR		/* disable translate NL to CR */
		| IGNCR		/* disable ignore CR */
		| ICRNL		/* disable translate CR to NL */
		| IXON);	/* disable enable XON/XOFF flow control */

	termios->c_oflag
		&= ~OPOST;	/* disable postprocess output अक्षरacters */

	termios->c_lflag
		&= ~(ECHO	/* disable echo input अक्षरacters */
		| ECHONL	/* disable echo new line */
		| ICANON	/* disable erase, समाप्त, werase, and rprnt special अक्षरacters */
		| ISIG		/* disable पूर्णांकerrupt, quit, and suspend special अक्षरacters */
		| IEXTEN);	/* disable non-POSIX special अक्षरacters */

	termios->c_cflag
		&= ~(CSIZE	/* no size */
		| PARENB	/* disable parity bit */
		| CBAUD);	/* clear current baud rate */

	termios->c_cflag
		|= CS8;		/* अक्षरacter size 8 bits */

	tty_encode_baud_rate(tty, 115200, 115200);
पूर्ण

module_usb_serial_driver(serial_drivers, id_table);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL v2");
