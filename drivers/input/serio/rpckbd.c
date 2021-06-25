<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 2000-2001 Vojtech Pavlik
 *  Copyright (c) 2002 Russell King
 */

/*
 * Acorn RiscPC PS/2 keyboard controller driver क्रम Linux/ARM
 */

/*
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/serपन.स>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/hardware/iomd.h>

MODULE_AUTHOR("Vojtech Pavlik, Russell King");
MODULE_DESCRIPTION("Acorn RiscPC PS/2 keyboard controller driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:kart");

काष्ठा rpckbd_data अणु
	पूर्णांक tx_irq;
	पूर्णांक rx_irq;
पूर्ण;

अटल पूर्णांक rpckbd_ग_लिखो(काष्ठा serio *port, अचिन्हित अक्षर val)
अणु
	जबतक (!(iomd_पढ़ोb(IOMD_KCTRL) & (1 << 7)))
		cpu_relax();

	iomd_ग_लिखोb(val, IOMD_KARTTX);

	वापस 0;
पूर्ण

अटल irqवापस_t rpckbd_rx(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा serio *port = dev_id;
	अचिन्हित पूर्णांक byte;
	पूर्णांक handled = IRQ_NONE;

	जबतक (iomd_पढ़ोb(IOMD_KCTRL) & (1 << 5)) अणु
		byte = iomd_पढ़ोb(IOMD_KARTRX);

		serio_पूर्णांकerrupt(port, byte, 0);
		handled = IRQ_HANDLED;
	पूर्ण
	वापस handled;
पूर्ण

अटल irqवापस_t rpckbd_tx(पूर्णांक irq, व्योम *dev_id)
अणु
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rpckbd_खोलो(काष्ठा serio *port)
अणु
	काष्ठा rpckbd_data *rpckbd = port->port_data;

	/* Reset the keyboard state machine. */
	iomd_ग_लिखोb(0, IOMD_KCTRL);
	iomd_ग_लिखोb(8, IOMD_KCTRL);
	iomd_पढ़ोb(IOMD_KARTRX);

	अगर (request_irq(rpckbd->rx_irq, rpckbd_rx, 0, "rpckbd", port) != 0) अणु
		prपूर्णांकk(KERN_ERR "rpckbd.c: Could not allocate keyboard receive IRQ\n");
		वापस -EBUSY;
	पूर्ण

	अगर (request_irq(rpckbd->tx_irq, rpckbd_tx, 0, "rpckbd", port) != 0) अणु
		prपूर्णांकk(KERN_ERR "rpckbd.c: Could not allocate keyboard transmit IRQ\n");
		मुक्त_irq(rpckbd->rx_irq, port);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rpckbd_बंद(काष्ठा serio *port)
अणु
	काष्ठा rpckbd_data *rpckbd = port->port_data;

	मुक्त_irq(rpckbd->rx_irq, port);
	मुक्त_irq(rpckbd->tx_irq, port);
पूर्ण

/*
 * Allocate and initialize serio काष्ठाure क्रम subsequent registration
 * with serio core.
 */
अटल पूर्णांक rpckbd_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा rpckbd_data *rpckbd;
	काष्ठा serio *serio;
	पूर्णांक tx_irq, rx_irq;

	rx_irq = platक्रमm_get_irq(dev, 0);
	अगर (rx_irq <= 0)
		वापस rx_irq < 0 ? rx_irq : -ENXIO;

	tx_irq = platक्रमm_get_irq(dev, 1);
	अगर (tx_irq <= 0)
		वापस tx_irq < 0 ? tx_irq : -ENXIO;

	serio = kzalloc(माप(काष्ठा serio), GFP_KERNEL);
	rpckbd = kzalloc(माप(*rpckbd), GFP_KERNEL);
	अगर (!serio || !rpckbd) अणु
		kमुक्त(rpckbd);
		kमुक्त(serio);
		वापस -ENOMEM;
	पूर्ण

	rpckbd->rx_irq = rx_irq;
	rpckbd->tx_irq = tx_irq;

	serio->id.type		= SERIO_8042;
	serio->ग_लिखो		= rpckbd_ग_लिखो;
	serio->खोलो		= rpckbd_खोलो;
	serio->बंद		= rpckbd_बंद;
	serio->dev.parent	= &dev->dev;
	serio->port_data	= rpckbd;
	strlcpy(serio->name, "RiscPC PS/2 kbd port", माप(serio->name));
	strlcpy(serio->phys, "rpckbd/serio0", माप(serio->phys));

	platक्रमm_set_drvdata(dev, serio);
	serio_रेजिस्टर_port(serio);
	वापस 0;
पूर्ण

अटल पूर्णांक rpckbd_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा serio *serio = platक्रमm_get_drvdata(dev);
	काष्ठा rpckbd_data *rpckbd = serio->port_data;

	serio_unरेजिस्टर_port(serio);
	kमुक्त(rpckbd);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver rpckbd_driver = अणु
	.probe		= rpckbd_probe,
	.हटाओ		= rpckbd_हटाओ,
	.driver		= अणु
		.name	= "kart",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(rpckbd_driver);
