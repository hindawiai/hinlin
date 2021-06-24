<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/input/serio/pcips2.c
 *
 *  Copyright (C) 2003 Russell King, All Rights Reserved.
 *
 *  I'm not sure अगर this is a generic PS/2 PCI पूर्णांकerface or specअगरic to
 *  the Mobility Electronics करोcking station.
 */
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/input.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/serपन.स>
#समावेश <linux/delay.h>
#समावेश <यंत्र/पन.स>

#घोषणा PS2_CTRL		(0)
#घोषणा PS2_STATUS		(1)
#घोषणा PS2_DATA		(2)

#घोषणा PS2_CTRL_CLK		(1<<0)
#घोषणा PS2_CTRL_DAT		(1<<1)
#घोषणा PS2_CTRL_TXIRQ		(1<<2)
#घोषणा PS2_CTRL_ENABLE		(1<<3)
#घोषणा PS2_CTRL_RXIRQ		(1<<4)

#घोषणा PS2_STAT_CLK		(1<<0)
#घोषणा PS2_STAT_DAT		(1<<1)
#घोषणा PS2_STAT_PARITY		(1<<2)
#घोषणा PS2_STAT_RXFULL		(1<<5)
#घोषणा PS2_STAT_TXBUSY		(1<<6)
#घोषणा PS2_STAT_TXEMPTY	(1<<7)

काष्ठा pcips2_data अणु
	काष्ठा serio	*io;
	अचिन्हित पूर्णांक	base;
	काष्ठा pci_dev	*dev;
पूर्ण;

अटल पूर्णांक pcips2_ग_लिखो(काष्ठा serio *io, अचिन्हित अक्षर val)
अणु
	काष्ठा pcips2_data *ps2अगर = io->port_data;
	अचिन्हित पूर्णांक stat;

	करो अणु
		stat = inb(ps2अगर->base + PS2_STATUS);
		cpu_relax();
	पूर्ण जबतक (!(stat & PS2_STAT_TXEMPTY));

	outb(val, ps2अगर->base + PS2_DATA);

	वापस 0;
पूर्ण

अटल irqवापस_t pcips2_पूर्णांकerrupt(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा pcips2_data *ps2अगर = devid;
	अचिन्हित अक्षर status, scancode;
	पूर्णांक handled = 0;

	करो अणु
		अचिन्हित पूर्णांक flag;

		status = inb(ps2अगर->base + PS2_STATUS);
		अगर (!(status & PS2_STAT_RXFULL))
			अवरोध;
		handled = 1;
		scancode = inb(ps2अगर->base + PS2_DATA);
		अगर (status == 0xff && scancode == 0xff)
			अवरोध;

		flag = (status & PS2_STAT_PARITY) ? 0 : SERIO_PARITY;

		अगर (hweight8(scancode) & 1)
			flag ^= SERIO_PARITY;

		serio_पूर्णांकerrupt(ps2अगर->io, scancode, flag);
	पूर्ण जबतक (1);
	वापस IRQ_RETVAL(handled);
पूर्ण

अटल व्योम pcips2_flush_input(काष्ठा pcips2_data *ps2अगर)
अणु
	अचिन्हित अक्षर status, scancode;

	करो अणु
		status = inb(ps2अगर->base + PS2_STATUS);
		अगर (!(status & PS2_STAT_RXFULL))
			अवरोध;
		scancode = inb(ps2अगर->base + PS2_DATA);
		अगर (status == 0xff && scancode == 0xff)
			अवरोध;
	पूर्ण जबतक (1);
पूर्ण

अटल पूर्णांक pcips2_खोलो(काष्ठा serio *io)
अणु
	काष्ठा pcips2_data *ps2अगर = io->port_data;
	पूर्णांक ret, val = 0;

	outb(PS2_CTRL_ENABLE, ps2अगर->base);
	pcips2_flush_input(ps2अगर);

	ret = request_irq(ps2अगर->dev->irq, pcips2_पूर्णांकerrupt, IRQF_SHARED,
			  "pcips2", ps2अगर);
	अगर (ret == 0)
		val = PS2_CTRL_ENABLE | PS2_CTRL_RXIRQ;

	outb(val, ps2अगर->base);

	वापस ret;
पूर्ण

अटल व्योम pcips2_बंद(काष्ठा serio *io)
अणु
	काष्ठा pcips2_data *ps2अगर = io->port_data;

	outb(0, ps2अगर->base);

	मुक्त_irq(ps2अगर->dev->irq, ps2अगर);
पूर्ण

अटल पूर्णांक pcips2_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा pcips2_data *ps2अगर;
	काष्ठा serio *serio;
	पूर्णांक ret;

	ret = pci_enable_device(dev);
	अगर (ret)
		जाओ out;

	ret = pci_request_regions(dev, "pcips2");
	अगर (ret)
		जाओ disable;

	ps2अगर = kzalloc(माप(काष्ठा pcips2_data), GFP_KERNEL);
	serio = kzalloc(माप(काष्ठा serio), GFP_KERNEL);
	अगर (!ps2अगर || !serio) अणु
		ret = -ENOMEM;
		जाओ release;
	पूर्ण


	serio->id.type		= SERIO_8042;
	serio->ग_लिखो		= pcips2_ग_लिखो;
	serio->खोलो		= pcips2_खोलो;
	serio->बंद		= pcips2_बंद;
	strlcpy(serio->name, pci_name(dev), माप(serio->name));
	strlcpy(serio->phys, dev_name(&dev->dev), माप(serio->phys));
	serio->port_data	= ps2अगर;
	serio->dev.parent	= &dev->dev;
	ps2अगर->io		= serio;
	ps2अगर->dev		= dev;
	ps2अगर->base		= pci_resource_start(dev, 0);

	pci_set_drvdata(dev, ps2अगर);

	serio_रेजिस्टर_port(ps2अगर->io);
	वापस 0;

 release:
	kमुक्त(ps2अगर);
	kमुक्त(serio);
	pci_release_regions(dev);
 disable:
	pci_disable_device(dev);
 out:
	वापस ret;
पूर्ण

अटल व्योम pcips2_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा pcips2_data *ps2अगर = pci_get_drvdata(dev);

	serio_unरेजिस्टर_port(ps2अगर->io);
	kमुक्त(ps2अगर);
	pci_release_regions(dev);
	pci_disable_device(dev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id pcips2_ids[] = अणु
	अणु
		.venकरोr		= 0x14f2,	/* MOBILITY */
		.device		= 0x0123,	/* Keyboard */
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.class		= PCI_CLASS_INPUT_KEYBOARD << 8,
		.class_mask	= 0xffff00,
	पूर्ण,
	अणु
		.venकरोr		= 0x14f2,	/* MOBILITY */
		.device		= 0x0124,	/* Mouse */
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
		.class		= PCI_CLASS_INPUT_MOUSE << 8,
		.class_mask	= 0xffff00,
	पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, pcips2_ids);

अटल काष्ठा pci_driver pcips2_driver = अणु
	.name			= "pcips2",
	.id_table		= pcips2_ids,
	.probe			= pcips2_probe,
	.हटाओ			= pcips2_हटाओ,
पूर्ण;

module_pci_driver(pcips2_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Russell King <rmk@arm.linux.org.uk>");
MODULE_DESCRIPTION("PCI PS/2 keyboard/mouse driver");
