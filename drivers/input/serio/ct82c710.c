<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 1999-2001 Vojtech Pavlik
 */

/*
 *  82C710 C&T mouse port chip driver क्रम Linux
 */

/*
 */

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/serपन.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/पन.स>

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION("82C710 C&T mouse port chip driver");
MODULE_LICENSE("GPL");

/*
 * ct82c710 पूर्णांकerface
 */

#घोषणा CT82C710_DEV_IDLE     0x01		/* Device Idle */
#घोषणा CT82C710_RX_FULL      0x02		/* Device Char received */
#घोषणा CT82C710_TX_IDLE      0x04		/* Device XMIT Idle */
#घोषणा CT82C710_RESET        0x08		/* Device Reset */
#घोषणा CT82C710_INTS_ON      0x10		/* Device Interrupt On */
#घोषणा CT82C710_ERROR_FLAG   0x20		/* Device Error */
#घोषणा CT82C710_CLEAR        0x40		/* Device Clear */
#घोषणा CT82C710_ENABLE       0x80		/* Device Enable */

#घोषणा CT82C710_IRQ          12

#घोषणा CT82C710_DATA         ct82c710_iores.start
#घोषणा CT82C710_STATUS       (ct82c710_iores.start + 1)

अटल काष्ठा serio *ct82c710_port;
अटल काष्ठा platक्रमm_device *ct82c710_device;
अटल काष्ठा resource ct82c710_iores;

/*
 * Interrupt handler क्रम the 82C710 mouse port. A अक्षरacter
 * is रुकोing in the 82C710.
 */

अटल irqवापस_t ct82c710_पूर्णांकerrupt(पूर्णांक cpl, व्योम *dev_id)
अणु
	वापस serio_पूर्णांकerrupt(ct82c710_port, inb(CT82C710_DATA), 0);
पूर्ण

/*
 * Wait क्रम device to send output अक्षर and flush any input अक्षर.
 */

अटल पूर्णांक ct82c170_रुको(व्योम)
अणु
	पूर्णांक समयout = 60000;

	जबतक ((inb(CT82C710_STATUS) & (CT82C710_RX_FULL | CT82C710_TX_IDLE | CT82C710_DEV_IDLE))
		       != (CT82C710_DEV_IDLE | CT82C710_TX_IDLE) && समयout) अणु

		अगर (inb_p(CT82C710_STATUS) & CT82C710_RX_FULL) inb_p(CT82C710_DATA);

		udelay(1);
		समयout--;
	पूर्ण

	वापस !समयout;
पूर्ण

अटल व्योम ct82c710_बंद(काष्ठा serio *serio)
अणु
	अगर (ct82c170_रुको())
		prपूर्णांकk(KERN_WARNING "ct82c710.c: Device busy in close()\n");

	outb_p(inb_p(CT82C710_STATUS) & ~(CT82C710_ENABLE | CT82C710_INTS_ON), CT82C710_STATUS);

	अगर (ct82c170_रुको())
		prपूर्णांकk(KERN_WARNING "ct82c710.c: Device busy in close()\n");

	मुक्त_irq(CT82C710_IRQ, शून्य);
पूर्ण

अटल पूर्णांक ct82c710_खोलो(काष्ठा serio *serio)
अणु
	अचिन्हित अक्षर status;
	पूर्णांक err;

	err = request_irq(CT82C710_IRQ, ct82c710_पूर्णांकerrupt, 0, "ct82c710", शून्य);
	अगर (err)
		वापस err;

	status = inb_p(CT82C710_STATUS);

	status |= (CT82C710_ENABLE | CT82C710_RESET);
	outb_p(status, CT82C710_STATUS);

	status &= ~(CT82C710_RESET);
	outb_p(status, CT82C710_STATUS);

	status |= CT82C710_INTS_ON;
	outb_p(status, CT82C710_STATUS);	/* Enable पूर्णांकerrupts */

	जबतक (ct82c170_रुको()) अणु
		prपूर्णांकk(KERN_ERR "ct82c710: Device busy in open()\n");
		status &= ~(CT82C710_ENABLE | CT82C710_INTS_ON);
		outb_p(status, CT82C710_STATUS);
		मुक्त_irq(CT82C710_IRQ, शून्य);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Write to the 82C710 mouse device.
 */

अटल पूर्णांक ct82c710_ग_लिखो(काष्ठा serio *port, अचिन्हित अक्षर c)
अणु
	अगर (ct82c170_रुको()) वापस -1;
	outb_p(c, CT82C710_DATA);
	वापस 0;
पूर्ण

/*
 * See अगर we can find a 82C710 device. Read mouse address.
 */

अटल पूर्णांक __init ct82c710_detect(व्योम)
अणु
	outb_p(0x55, 0x2fa);				/* Any value except 9, ff or 36 */
	outb_p(0xaa, 0x3fa);				/* Inverse of 55 */
	outb_p(0x36, 0x3fa);				/* Address the chip */
	outb_p(0xe4, 0x3fa);				/* 390/4; 390 = config address */
	outb_p(0x1b, 0x2fa);				/* Inverse of e4 */
	outb_p(0x0f, 0x390);				/* Write index */
	अगर (inb_p(0x391) != 0xe4)			/* Config address found? */
		वापस -ENODEV;				/* No: no 82C710 here */

	outb_p(0x0d, 0x390);				/* Write index */
	ct82c710_iores.start = inb_p(0x391) << 2;	/* Get mouse I/O address */
	ct82c710_iores.end = ct82c710_iores.start + 1;
	ct82c710_iores.flags = IORESOURCE_IO;
	outb_p(0x0f, 0x390);
	outb_p(0x0f, 0x391);				/* Close config mode */

	वापस 0;
पूर्ण

अटल पूर्णांक ct82c710_probe(काष्ठा platक्रमm_device *dev)
अणु
	ct82c710_port = kzalloc(माप(काष्ठा serio), GFP_KERNEL);
	अगर (!ct82c710_port)
		वापस -ENOMEM;

	ct82c710_port->id.type = SERIO_8042;
	ct82c710_port->dev.parent = &dev->dev;
	ct82c710_port->खोलो = ct82c710_खोलो;
	ct82c710_port->बंद = ct82c710_बंद;
	ct82c710_port->ग_लिखो = ct82c710_ग_लिखो;
	strlcpy(ct82c710_port->name, "C&T 82c710 mouse port",
		माप(ct82c710_port->name));
	snम_लिखो(ct82c710_port->phys, माप(ct82c710_port->phys),
		 "isa%16llx/serio0", (अचिन्हित दीर्घ दीर्घ)CT82C710_DATA);

	serio_रेजिस्टर_port(ct82c710_port);

	prपूर्णांकk(KERN_INFO "serio: C&T 82c710 mouse port at %#llx irq %d\n",
		(अचिन्हित दीर्घ दीर्घ)CT82C710_DATA, CT82C710_IRQ);

	वापस 0;
पूर्ण

अटल पूर्णांक ct82c710_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	serio_unरेजिस्टर_port(ct82c710_port);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ct82c710_driver = अणु
	.driver		= अणु
		.name	= "ct82c710",
	पूर्ण,
	.probe		= ct82c710_probe,
	.हटाओ		= ct82c710_हटाओ,
पूर्ण;


अटल पूर्णांक __init ct82c710_init(व्योम)
अणु
	पूर्णांक error;

	error = ct82c710_detect();
	अगर (error)
		वापस error;

	error = platक्रमm_driver_रेजिस्टर(&ct82c710_driver);
	अगर (error)
		वापस error;

	ct82c710_device = platक्रमm_device_alloc("ct82c710", -1);
	अगर (!ct82c710_device) अणु
		error = -ENOMEM;
		जाओ err_unरेजिस्टर_driver;
	पूर्ण

	error = platक्रमm_device_add_resources(ct82c710_device, &ct82c710_iores, 1);
	अगर (error)
		जाओ err_मुक्त_device;

	error = platक्रमm_device_add(ct82c710_device);
	अगर (error)
		जाओ err_मुक्त_device;

	वापस 0;

 err_मुक्त_device:
	platक्रमm_device_put(ct82c710_device);
 err_unरेजिस्टर_driver:
	platक्रमm_driver_unरेजिस्टर(&ct82c710_driver);
	वापस error;
पूर्ण

अटल व्योम __निकास ct82c710_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(ct82c710_device);
	platक्रमm_driver_unरेजिस्टर(&ct82c710_driver);
पूर्ण

module_init(ct82c710_init);
module_निकास(ct82c710_निकास);
