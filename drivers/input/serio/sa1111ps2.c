<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/input/serio/sa1111ps2.c
 *
 *  Copyright (C) 2002 Russell King
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश <यंत्र/पन.स>

#समावेश <यंत्र/hardware/sa1111.h>

#घोषणा PS2CR		0x0000
#घोषणा PS2STAT		0x0004
#घोषणा PS2DATA		0x0008
#घोषणा PS2CLKDIV	0x000c
#घोषणा PS2PRECNT	0x0010

#घोषणा PS2CR_ENA	0x08
#घोषणा PS2CR_FKD	0x02
#घोषणा PS2CR_FKC	0x01

#घोषणा PS2STAT_STP	0x0100
#घोषणा PS2STAT_TXE	0x0080
#घोषणा PS2STAT_TXB	0x0040
#घोषणा PS2STAT_RXF	0x0020
#घोषणा PS2STAT_RXB	0x0010
#घोषणा PS2STAT_ENA	0x0008
#घोषणा PS2STAT_RXP	0x0004
#घोषणा PS2STAT_KBD	0x0002
#घोषणा PS2STAT_KBC	0x0001

काष्ठा ps2अगर अणु
	काष्ठा serio		*io;
	काष्ठा sa1111_dev	*dev;
	व्योम __iomem		*base;
	पूर्णांक			rx_irq;
	पूर्णांक			tx_irq;
	अचिन्हित पूर्णांक		खोलो;
	spinlock_t		lock;
	अचिन्हित पूर्णांक		head;
	अचिन्हित पूर्णांक		tail;
	अचिन्हित अक्षर		buf[4];
पूर्ण;

/*
 * Read all bytes रुकोing in the PS2 port.  There should be
 * at the most one, but we loop क्रम safety.  If there was a
 * framing error, we have to manually clear the status.
 */
अटल irqवापस_t ps2_rxपूर्णांक(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ps2अगर *ps2अगर = dev_id;
	अचिन्हित पूर्णांक scancode, flag, status;

	status = पढ़ोl_relaxed(ps2अगर->base + PS2STAT);
	जबतक (status & PS2STAT_RXF) अणु
		अगर (status & PS2STAT_STP)
			ग_लिखोl_relaxed(PS2STAT_STP, ps2अगर->base + PS2STAT);

		flag = (status & PS2STAT_STP ? SERIO_FRAME : 0) |
		       (status & PS2STAT_RXP ? 0 : SERIO_PARITY);

		scancode = पढ़ोl_relaxed(ps2अगर->base + PS2DATA) & 0xff;

		अगर (hweight8(scancode) & 1)
			flag ^= SERIO_PARITY;

		serio_पूर्णांकerrupt(ps2अगर->io, scancode, flag);

		status = पढ़ोl_relaxed(ps2अगर->base + PS2STAT);
        पूर्ण

        वापस IRQ_HANDLED;
पूर्ण

/*
 * Completion of ps2 ग_लिखो
 */
अटल irqवापस_t ps2_txपूर्णांक(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ps2अगर *ps2अगर = dev_id;
	अचिन्हित पूर्णांक status;

	spin_lock(&ps2अगर->lock);
	status = पढ़ोl_relaxed(ps2अगर->base + PS2STAT);
	अगर (ps2अगर->head == ps2अगर->tail) अणु
		disable_irq_nosync(irq);
		/* करोne */
	पूर्ण अन्यथा अगर (status & PS2STAT_TXE) अणु
		ग_लिखोl_relaxed(ps2अगर->buf[ps2अगर->tail], ps2अगर->base + PS2DATA);
		ps2अगर->tail = (ps2अगर->tail + 1) & (माप(ps2अगर->buf) - 1);
	पूर्ण
	spin_unlock(&ps2अगर->lock);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Write a byte to the PS2 port.  We have to रुको क्रम the
 * port to indicate that the transmitter is empty.
 */
अटल पूर्णांक ps2_ग_लिखो(काष्ठा serio *io, अचिन्हित अक्षर val)
अणु
	काष्ठा ps2अगर *ps2अगर = io->port_data;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक head;

	spin_lock_irqsave(&ps2अगर->lock, flags);

	/*
	 * If the TX रेजिस्टर is empty, we can go straight out.
	 */
	अगर (पढ़ोl_relaxed(ps2अगर->base + PS2STAT) & PS2STAT_TXE) अणु
		ग_लिखोl_relaxed(val, ps2अगर->base + PS2DATA);
	पूर्ण अन्यथा अणु
		अगर (ps2अगर->head == ps2अगर->tail)
			enable_irq(ps2अगर->tx_irq);
		head = (ps2अगर->head + 1) & (माप(ps2अगर->buf) - 1);
		अगर (head != ps2अगर->tail) अणु
			ps2अगर->buf[ps2अगर->head] = val;
			ps2अगर->head = head;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&ps2अगर->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक ps2_खोलो(काष्ठा serio *io)
अणु
	काष्ठा ps2अगर *ps2अगर = io->port_data;
	पूर्णांक ret;

	ret = sa1111_enable_device(ps2अगर->dev);
	अगर (ret)
		वापस ret;

	ret = request_irq(ps2अगर->rx_irq, ps2_rxपूर्णांक, 0,
			  SA1111_DRIVER_NAME(ps2अगर->dev), ps2अगर);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "sa1111ps2: could not allocate IRQ%d: %d\n",
			ps2अगर->rx_irq, ret);
		sa1111_disable_device(ps2अगर->dev);
		वापस ret;
	पूर्ण

	ret = request_irq(ps2अगर->tx_irq, ps2_txपूर्णांक, 0,
			  SA1111_DRIVER_NAME(ps2अगर->dev), ps2अगर);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "sa1111ps2: could not allocate IRQ%d: %d\n",
			ps2अगर->tx_irq, ret);
		मुक्त_irq(ps2अगर->rx_irq, ps2अगर);
		sa1111_disable_device(ps2अगर->dev);
		वापस ret;
	पूर्ण

	ps2अगर->खोलो = 1;

	enable_irq_wake(ps2अगर->rx_irq);

	ग_लिखोl_relaxed(PS2CR_ENA, ps2अगर->base + PS2CR);
	वापस 0;
पूर्ण

अटल व्योम ps2_बंद(काष्ठा serio *io)
अणु
	काष्ठा ps2अगर *ps2अगर = io->port_data;

	ग_लिखोl_relaxed(0, ps2अगर->base + PS2CR);

	disable_irq_wake(ps2अगर->rx_irq);

	ps2अगर->खोलो = 0;

	मुक्त_irq(ps2अगर->tx_irq, ps2अगर);
	मुक्त_irq(ps2अगर->rx_irq, ps2अगर);

	sa1111_disable_device(ps2अगर->dev);
पूर्ण

/*
 * Clear the input buffer.
 */
अटल व्योम ps2_clear_input(काष्ठा ps2अगर *ps2अगर)
अणु
	पूर्णांक maxपढ़ो = 100;

	जबतक (maxपढ़ो--) अणु
		अगर ((पढ़ोl_relaxed(ps2अगर->base + PS2DATA) & 0xff) == 0xff)
			अवरोध;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक ps2_test_one(काष्ठा ps2अगर *ps2अगर,
					   अचिन्हित पूर्णांक mask)
अणु
	अचिन्हित पूर्णांक val;

	ग_लिखोl_relaxed(PS2CR_ENA | mask, ps2अगर->base + PS2CR);

	udelay(10);

	val = पढ़ोl_relaxed(ps2अगर->base + PS2STAT);
	वापस val & (PS2STAT_KBC | PS2STAT_KBD);
पूर्ण

/*
 * Test the keyboard पूर्णांकerface.  We basically check to make sure that
 * we can drive each line to the keyboard independently of each other.
 */
अटल पूर्णांक ps2_test(काष्ठा ps2अगर *ps2अगर)
अणु
	अचिन्हित पूर्णांक stat;
	पूर्णांक ret = 0;

	stat = ps2_test_one(ps2अगर, PS2CR_FKC);
	अगर (stat != PS2STAT_KBD) अणु
		prपूर्णांकk("PS/2 interface test failed[1]: %02x\n", stat);
		ret = -ENODEV;
	पूर्ण

	stat = ps2_test_one(ps2अगर, 0);
	अगर (stat != (PS2STAT_KBC | PS2STAT_KBD)) अणु
		prपूर्णांकk("PS/2 interface test failed[2]: %02x\n", stat);
		ret = -ENODEV;
	पूर्ण

	stat = ps2_test_one(ps2अगर, PS2CR_FKD);
	अगर (stat != PS2STAT_KBC) अणु
		prपूर्णांकk("PS/2 interface test failed[3]: %02x\n", stat);
		ret = -ENODEV;
	पूर्ण

	ग_लिखोl_relaxed(0, ps2अगर->base + PS2CR);

	वापस ret;
पूर्ण

/*
 * Add one device to this driver.
 */
अटल पूर्णांक ps2_probe(काष्ठा sa1111_dev *dev)
अणु
	काष्ठा ps2अगर *ps2अगर;
	काष्ठा serio *serio;
	पूर्णांक ret;

	ps2अगर = kzalloc(माप(काष्ठा ps2अगर), GFP_KERNEL);
	serio = kzalloc(माप(काष्ठा serio), GFP_KERNEL);
	अगर (!ps2अगर || !serio) अणु
		ret = -ENOMEM;
		जाओ मुक्त;
	पूर्ण

	serio->id.type		= SERIO_8042;
	serio->ग_लिखो		= ps2_ग_लिखो;
	serio->खोलो		= ps2_खोलो;
	serio->बंद		= ps2_बंद;
	strlcpy(serio->name, dev_name(&dev->dev), माप(serio->name));
	strlcpy(serio->phys, dev_name(&dev->dev), माप(serio->phys));
	serio->port_data	= ps2अगर;
	serio->dev.parent	= &dev->dev;
	ps2अगर->io		= serio;
	ps2अगर->dev		= dev;
	sa1111_set_drvdata(dev, ps2अगर);

	spin_lock_init(&ps2अगर->lock);

	ps2अगर->rx_irq = sa1111_get_irq(dev, 0);
	अगर (ps2अगर->rx_irq <= 0) अणु
		ret = ps2अगर->rx_irq ? : -ENXIO;
		जाओ मुक्त;
	पूर्ण

	ps2अगर->tx_irq = sa1111_get_irq(dev, 1);
	अगर (ps2अगर->tx_irq <= 0) अणु
		ret = ps2अगर->tx_irq ? : -ENXIO;
		जाओ मुक्त;
	पूर्ण

	/*
	 * Request the physical region क्रम this PS2 port.
	 */
	अगर (!request_mem_region(dev->res.start,
				dev->res.end - dev->res.start + 1,
				SA1111_DRIVER_NAME(dev))) अणु
		ret = -EBUSY;
		जाओ मुक्त;
	पूर्ण

	/*
	 * Our parent device has alपढ़ोy mapped the region.
	 */
	ps2अगर->base = dev->mapbase;

	sa1111_enable_device(ps2अगर->dev);

	/* Incoming घड़ी is 8MHz */
	ग_लिखोl_relaxed(0, ps2अगर->base + PS2CLKDIV);
	ग_लिखोl_relaxed(127, ps2अगर->base + PS2PRECNT);

	/*
	 * Flush any pending input.
	 */
	ps2_clear_input(ps2अगर);

	/*
	 * Test the keyboard पूर्णांकerface.
	 */
	ret = ps2_test(ps2अगर);
	अगर (ret)
		जाओ out;

	/*
	 * Flush any pending input.
	 */
	ps2_clear_input(ps2अगर);

	sa1111_disable_device(ps2अगर->dev);
	serio_रेजिस्टर_port(ps2अगर->io);
	वापस 0;

 out:
	sa1111_disable_device(ps2अगर->dev);
	release_mem_region(dev->res.start, resource_size(&dev->res));
 मुक्त:
	sa1111_set_drvdata(dev, शून्य);
	kमुक्त(ps2अगर);
	kमुक्त(serio);
	वापस ret;
पूर्ण

/*
 * Remove one device from this driver.
 */
अटल व्योम ps2_हटाओ(काष्ठा sa1111_dev *dev)
अणु
	काष्ठा ps2अगर *ps2अगर = sa1111_get_drvdata(dev);

	serio_unरेजिस्टर_port(ps2अगर->io);
	release_mem_region(dev->res.start, resource_size(&dev->res));
	sa1111_set_drvdata(dev, शून्य);

	kमुक्त(ps2अगर);
पूर्ण

/*
 * Our device driver काष्ठाure
 */
अटल काष्ठा sa1111_driver ps2_driver = अणु
	.drv = अणु
		.name	= "sa1111-ps2",
		.owner	= THIS_MODULE,
	पूर्ण,
	.devid		= SA1111_DEVID_PS2,
	.probe		= ps2_probe,
	.हटाओ		= ps2_हटाओ,
पूर्ण;

अटल पूर्णांक __init ps2_init(व्योम)
अणु
	वापस sa1111_driver_रेजिस्टर(&ps2_driver);
पूर्ण

अटल व्योम __निकास ps2_निकास(व्योम)
अणु
	sa1111_driver_unरेजिस्टर(&ps2_driver);
पूर्ण

module_init(ps2_init);
module_निकास(ps2_निकास);

MODULE_AUTHOR("Russell King <rmk@arm.linux.org.uk>");
MODULE_DESCRIPTION("SA1111 PS2 controller driver");
MODULE_LICENSE("GPL");
