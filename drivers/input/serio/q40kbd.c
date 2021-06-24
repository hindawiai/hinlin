<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 2000-2001 Vojtech Pavlik
 *
 *  Based on the work of:
 *	Riअक्षरd Zidlicky <Riअक्षरd.Zidlicky@stud.inक्रमmatik.uni-erlangen.de>
 */

/*
 * Q40 PS/2 keyboard controller driver क्रम Linux/m68k
 */

/*
 */

#समावेश <linux/module.h>
#समावेश <linux/serपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/err.h>
#समावेश <linux/bitops.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/q40_master.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/q40पूर्णांकs.h>

#घोषणा DRV_NAME	"q40kbd"

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION("Q40 PS/2 keyboard controller driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);

काष्ठा q40kbd अणु
	काष्ठा serio *port;
	spinlock_t lock;
पूर्ण;

अटल irqवापस_t q40kbd_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा q40kbd *q40kbd = dev_id;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&q40kbd->lock, flags);

	अगर (Q40_IRQ_KEYB_MASK & master_inb(INTERRUPT_REG))
		serio_पूर्णांकerrupt(q40kbd->port, master_inb(KEYCODE_REG), 0);

	master_outb(-1, KEYBOARD_UNLOCK_REG);

	spin_unlock_irqrestore(&q40kbd->lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * q40kbd_flush() flushes all data that may be in the keyboard buffers
 */

अटल व्योम q40kbd_flush(काष्ठा q40kbd *q40kbd)
अणु
	पूर्णांक maxपढ़ो = 100;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&q40kbd->lock, flags);

	जबतक (maxपढ़ो-- && (Q40_IRQ_KEYB_MASK & master_inb(INTERRUPT_REG)))
		master_inb(KEYCODE_REG);

	spin_unlock_irqrestore(&q40kbd->lock, flags);
पूर्ण

अटल व्योम q40kbd_stop(व्योम)
अणु
	master_outb(0, KEY_IRQ_ENABLE_REG);
	master_outb(-1, KEYBOARD_UNLOCK_REG);
पूर्ण

/*
 * q40kbd_खोलो() is called when a port is खोलो by the higher layer.
 * It allocates the पूर्णांकerrupt and enables in in the chip.
 */

अटल पूर्णांक q40kbd_खोलो(काष्ठा serio *port)
अणु
	काष्ठा q40kbd *q40kbd = port->port_data;

	q40kbd_flush(q40kbd);

	/* off we go */
	master_outb(-1, KEYBOARD_UNLOCK_REG);
	master_outb(1, KEY_IRQ_ENABLE_REG);

	वापस 0;
पूर्ण

अटल व्योम q40kbd_बंद(काष्ठा serio *port)
अणु
	काष्ठा q40kbd *q40kbd = port->port_data;

	q40kbd_stop();
	q40kbd_flush(q40kbd);
पूर्ण

अटल पूर्णांक q40kbd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा q40kbd *q40kbd;
	काष्ठा serio *port;
	पूर्णांक error;

	q40kbd = kzalloc(माप(काष्ठा q40kbd), GFP_KERNEL);
	port = kzalloc(माप(काष्ठा serio), GFP_KERNEL);
	अगर (!q40kbd || !port) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	q40kbd->port = port;
	spin_lock_init(&q40kbd->lock);

	port->id.type = SERIO_8042;
	port->खोलो = q40kbd_खोलो;
	port->बंद = q40kbd_बंद;
	port->port_data = q40kbd;
	port->dev.parent = &pdev->dev;
	strlcpy(port->name, "Q40 Kbd Port", माप(port->name));
	strlcpy(port->phys, "Q40", माप(port->phys));

	q40kbd_stop();

	error = request_irq(Q40_IRQ_KEYBOARD, q40kbd_पूर्णांकerrupt, 0,
			    DRV_NAME, q40kbd);
	अगर (error) अणु
		dev_err(&pdev->dev, "Can't get irq %d.\n", Q40_IRQ_KEYBOARD);
		जाओ err_मुक्त_mem;
	पूर्ण

	serio_रेजिस्टर_port(q40kbd->port);

	platक्रमm_set_drvdata(pdev, q40kbd);
	prपूर्णांकk(KERN_INFO "serio: Q40 kbd registered\n");

	वापस 0;

err_मुक्त_mem:
	kमुक्त(port);
	kमुक्त(q40kbd);
	वापस error;
पूर्ण

अटल पूर्णांक q40kbd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा q40kbd *q40kbd = platक्रमm_get_drvdata(pdev);

	/*
	 * q40kbd_बंद() will be called as part of unरेजिस्टरing
	 * and will ensure that IRQ is turned off, so it is safe
	 * to unरेजिस्टर port first and मुक्त IRQ later.
	 */
	serio_unरेजिस्टर_port(q40kbd->port);
	मुक्त_irq(Q40_IRQ_KEYBOARD, q40kbd);
	kमुक्त(q40kbd);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver q40kbd_driver = अणु
	.driver		= अणु
		.name	= "q40kbd",
	पूर्ण,
	.हटाओ		= q40kbd_हटाओ,
पूर्ण;

module_platक्रमm_driver_probe(q40kbd_driver, q40kbd_probe);
