<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SGI O2 MACE PS2 controller driver क्रम linux
 *
 * Copyright (C) 2002 Vivien Chappelier
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/serपन.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/err.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/ip32/mace.h>
#समावेश <यंत्र/ip32/ip32_पूर्णांकs.h>

MODULE_AUTHOR("Vivien Chappelier <vivien.chappelier@linux-mips.org");
MODULE_DESCRIPTION("SGI O2 MACE PS2 controller driver");
MODULE_LICENSE("GPL");

#घोषणा MACE_PS2_TIMEOUT 10000 /* in 50us unit */

#घोषणा PS2_STATUS_CLOCK_SIGNAL  BIT(0) /* बाह्यal घड़ी संकेत */
#घोषणा PS2_STATUS_CLOCK_INHIBIT BIT(1) /* clken output संकेत */
#घोषणा PS2_STATUS_TX_INPROGRESS BIT(2) /* transmission in progress */
#घोषणा PS2_STATUS_TX_EMPTY      BIT(3) /* empty transmit buffer */
#घोषणा PS2_STATUS_RX_FULL       BIT(4) /* full receive buffer */
#घोषणा PS2_STATUS_RX_INPROGRESS BIT(5) /* reception in progress */
#घोषणा PS2_STATUS_ERROR_PARITY  BIT(6) /* parity error */
#घोषणा PS2_STATUS_ERROR_FRAMING BIT(7) /* framing error */

#घोषणा PS2_CONTROL_TX_CLOCK_DISABLE BIT(0) /* inhibit घड़ी संकेत after TX */
#घोषणा PS2_CONTROL_TX_ENABLE        BIT(1) /* transmit enable */
#घोषणा PS2_CONTROL_TX_INT_ENABLE    BIT(2) /* enable transmit पूर्णांकerrupt */
#घोषणा PS2_CONTROL_RX_INT_ENABLE    BIT(3) /* enable receive पूर्णांकerrupt */
#घोषणा PS2_CONTROL_RX_CLOCK_ENABLE  BIT(4) /* छोड़ो reception अगर set to 0 */
#घोषणा PS2_CONTROL_RESET            BIT(5) /* reset */

काष्ठा maceps2_data अणु
	काष्ठा mace_ps2port *port;
	पूर्णांक irq;
पूर्ण;

अटल काष्ठा maceps2_data port_data[2];
अटल काष्ठा serio *maceps2_port[2];
अटल काष्ठा platक्रमm_device *maceps2_device;

अटल पूर्णांक maceps2_ग_लिखो(काष्ठा serio *dev, अचिन्हित अक्षर val)
अणु
	काष्ठा mace_ps2port *port = ((काष्ठा maceps2_data *)dev->port_data)->port;
	अचिन्हित पूर्णांक समयout = MACE_PS2_TIMEOUT;

	करो अणु
		अगर (port->status & PS2_STATUS_TX_EMPTY) अणु
			port->tx = val;
			वापस 0;
		पूर्ण
		udelay(50);
	पूर्ण जबतक (समयout--);

	वापस -1;
पूर्ण

अटल irqवापस_t maceps2_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा serio *dev = dev_id;
	काष्ठा mace_ps2port *port = ((काष्ठा maceps2_data *)dev->port_data)->port;
	अचिन्हित दीर्घ byte;

	अगर (port->status & PS2_STATUS_RX_FULL) अणु
		byte = port->rx;
		serio_पूर्णांकerrupt(dev, byte & 0xff, 0);
        पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक maceps2_खोलो(काष्ठा serio *dev)
अणु
	काष्ठा maceps2_data *data = (काष्ठा maceps2_data *)dev->port_data;

	अगर (request_irq(data->irq, maceps2_पूर्णांकerrupt, 0, "PS2 port", dev)) अणु
		prपूर्णांकk(KERN_ERR "Could not allocate PS/2 IRQ\n");
		वापस -EBUSY;
	पूर्ण

	/* Reset port */
	data->port->control = PS2_CONTROL_TX_CLOCK_DISABLE | PS2_CONTROL_RESET;
	udelay(100);

        /* Enable पूर्णांकerrupts */
	data->port->control = PS2_CONTROL_RX_CLOCK_ENABLE |
			      PS2_CONTROL_TX_ENABLE |
			      PS2_CONTROL_RX_INT_ENABLE;

	वापस 0;
पूर्ण

अटल व्योम maceps2_बंद(काष्ठा serio *dev)
अणु
	काष्ठा maceps2_data *data = (काष्ठा maceps2_data *)dev->port_data;

	data->port->control = PS2_CONTROL_TX_CLOCK_DISABLE | PS2_CONTROL_RESET;
	udelay(100);
	मुक्त_irq(data->irq, dev);
पूर्ण


अटल काष्ठा serio *maceps2_allocate_port(पूर्णांक idx)
अणु
	काष्ठा serio *serio;

	serio = kzalloc(माप(काष्ठा serio), GFP_KERNEL);
	अगर (serio) अणु
		serio->id.type		= SERIO_8042;
		serio->ग_लिखो		= maceps2_ग_लिखो;
		serio->खोलो		= maceps2_खोलो;
		serio->बंद		= maceps2_बंद;
		snम_लिखो(serio->name, माप(serio->name), "MACE PS/2 port%d", idx);
		snम_लिखो(serio->phys, माप(serio->phys), "mace/serio%d", idx);
		serio->port_data	= &port_data[idx];
		serio->dev.parent	= &maceps2_device->dev;
	पूर्ण

	वापस serio;
पूर्ण

अटल पूर्णांक maceps2_probe(काष्ठा platक्रमm_device *dev)
अणु
	maceps2_port[0] = maceps2_allocate_port(0);
	maceps2_port[1] = maceps2_allocate_port(1);
	अगर (!maceps2_port[0] || !maceps2_port[1]) अणु
		kमुक्त(maceps2_port[0]);
		kमुक्त(maceps2_port[1]);
		वापस -ENOMEM;
	पूर्ण

	serio_रेजिस्टर_port(maceps2_port[0]);
	serio_रेजिस्टर_port(maceps2_port[1]);

	वापस 0;
पूर्ण

अटल पूर्णांक maceps2_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	serio_unरेजिस्टर_port(maceps2_port[0]);
	serio_unरेजिस्टर_port(maceps2_port[1]);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver maceps2_driver = अणु
	.driver		= अणु
		.name	= "maceps2",
	पूर्ण,
	.probe		= maceps2_probe,
	.हटाओ		= maceps2_हटाओ,
पूर्ण;

अटल पूर्णांक __init maceps2_init(व्योम)
अणु
	पूर्णांक error;

	error = platक्रमm_driver_रेजिस्टर(&maceps2_driver);
	अगर (error)
		वापस error;

	maceps2_device = platक्रमm_device_alloc("maceps2", -1);
	अगर (!maceps2_device) अणु
		error = -ENOMEM;
		जाओ err_unरेजिस्टर_driver;
	पूर्ण

	port_data[0].port = &mace->perअगर.ps2.keyb;
	port_data[0].irq  = MACEISA_KEYB_IRQ;
	port_data[1].port = &mace->perअगर.ps2.mouse;
	port_data[1].irq  = MACEISA_MOUSE_IRQ;

	error = platक्रमm_device_add(maceps2_device);
	अगर (error)
		जाओ err_मुक्त_device;

	वापस 0;

 err_मुक्त_device:
	platक्रमm_device_put(maceps2_device);
 err_unरेजिस्टर_driver:
	platक्रमm_driver_unरेजिस्टर(&maceps2_driver);
	वापस error;
पूर्ण

अटल व्योम __निकास maceps2_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(maceps2_device);
	platक्रमm_driver_unरेजिस्टर(&maceps2_driver);
पूर्ण

module_init(maceps2_init);
module_निकास(maceps2_निकास);
