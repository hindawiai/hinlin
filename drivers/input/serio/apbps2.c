<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2013 Aeroflex Gaisler
 *
 * This driver supports the APBPS2 PS/2 core available in the GRLIB
 * VHDL IP core library.
 *
 * Full करोcumentation of the APBPS2 core can be found here:
 * http://www.gaisler.com/products/grlib/grip.pdf
 *
 * See "Documentation/devicetree/bindings/input/ps2keyb-mouse-apbps2.txt" क्रम
 * inक्रमmation on खोलो firmware properties.
 *
 * Contributors: Daniel Hellstrom <daniel@gaisler.com>
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_device.h>
#समावेश <linux/module.h>
#समावेश <linux/serपन.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>

काष्ठा apbps2_regs अणु
	u32 __iomem data;	/* 0x00 */
	u32 __iomem status;	/* 0x04 */
	u32 __iomem ctrl;	/* 0x08 */
	u32 __iomem reload;	/* 0x0c */
पूर्ण;

#घोषणा APBPS2_STATUS_DR	(1<<0)
#घोषणा APBPS2_STATUS_PE	(1<<1)
#घोषणा APBPS2_STATUS_FE	(1<<2)
#घोषणा APBPS2_STATUS_KI	(1<<3)
#घोषणा APBPS2_STATUS_RF	(1<<4)
#घोषणा APBPS2_STATUS_TF	(1<<5)
#घोषणा APBPS2_STATUS_TCNT	(0x1f<<22)
#घोषणा APBPS2_STATUS_RCNT	(0x1f<<27)

#घोषणा APBPS2_CTRL_RE		(1<<0)
#घोषणा APBPS2_CTRL_TE		(1<<1)
#घोषणा APBPS2_CTRL_RI		(1<<2)
#घोषणा APBPS2_CTRL_TI		(1<<3)

काष्ठा apbps2_priv अणु
	काष्ठा serio		*io;
	काष्ठा apbps2_regs	__iomem *regs;
पूर्ण;

अटल पूर्णांक apbps2_idx;

अटल irqवापस_t apbps2_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा apbps2_priv *priv = dev_id;
	अचिन्हित दीर्घ status, data, rxflags;
	irqवापस_t ret = IRQ_NONE;

	जबतक ((status = ioपढ़ो32be(&priv->regs->status)) & APBPS2_STATUS_DR) अणु
		data = ioपढ़ो32be(&priv->regs->data);
		rxflags = (status & APBPS2_STATUS_PE) ? SERIO_PARITY : 0;
		rxflags |= (status & APBPS2_STATUS_FE) ? SERIO_FRAME : 0;

		/* clear error bits? */
		अगर (rxflags)
			ioग_लिखो32be(0, &priv->regs->status);

		serio_पूर्णांकerrupt(priv->io, data, rxflags);

		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक apbps2_ग_लिखो(काष्ठा serio *io, अचिन्हित अक्षर val)
अणु
	काष्ठा apbps2_priv *priv = io->port_data;
	अचिन्हित पूर्णांक tleft = 10000; /* समयout in 100ms */

	/* delay until PS/2 controller has room क्रम more अक्षरs */
	जबतक ((ioपढ़ो32be(&priv->regs->status) & APBPS2_STATUS_TF) && tleft--)
		udelay(10);

	अगर ((ioपढ़ो32be(&priv->regs->status) & APBPS2_STATUS_TF) == 0) अणु
		ioग_लिखो32be(val, &priv->regs->data);

		ioग_लिखो32be(APBPS2_CTRL_RE | APBPS2_CTRL_RI | APBPS2_CTRL_TE,
				&priv->regs->ctrl);
		वापस 0;
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक apbps2_खोलो(काष्ठा serio *io)
अणु
	काष्ठा apbps2_priv *priv = io->port_data;
	पूर्णांक limit;

	/* clear error flags */
	ioग_लिखो32be(0, &priv->regs->status);

	/* Clear old data अगर available (unlikely) */
	limit = 1024;
	जबतक ((ioपढ़ो32be(&priv->regs->status) & APBPS2_STATUS_DR) && --limit)
		ioपढ़ो32be(&priv->regs->data);

	/* Enable reciever and it's पूर्णांकerrupt */
	ioग_लिखो32be(APBPS2_CTRL_RE | APBPS2_CTRL_RI, &priv->regs->ctrl);

	वापस 0;
पूर्ण

अटल व्योम apbps2_बंद(काष्ठा serio *io)
अणु
	काष्ठा apbps2_priv *priv = io->port_data;

	/* stop पूर्णांकerrupts at PS/2 HW level */
	ioग_लिखो32be(0, &priv->regs->ctrl);
पूर्ण

/* Initialize one APBPS2 PS/2 core */
अटल पूर्णांक apbps2_of_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा apbps2_priv *priv;
	पूर्णांक irq, err;
	u32 freq_hz;
	काष्ठा resource *res;

	priv = devm_kzalloc(&ofdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv) अणु
		dev_err(&ofdev->dev, "memory allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	/* Find Device Address */
	res = platक्रमm_get_resource(ofdev, IORESOURCE_MEM, 0);
	priv->regs = devm_ioremap_resource(&ofdev->dev, res);
	अगर (IS_ERR(priv->regs))
		वापस PTR_ERR(priv->regs);

	/* Reset hardware, disable पूर्णांकerrupt */
	ioग_लिखो32be(0, &priv->regs->ctrl);

	/* IRQ */
	irq = irq_of_parse_and_map(ofdev->dev.of_node, 0);
	err = devm_request_irq(&ofdev->dev, irq, apbps2_isr,
				IRQF_SHARED, "apbps2", priv);
	अगर (err) अणु
		dev_err(&ofdev->dev, "request IRQ%d failed\n", irq);
		वापस err;
	पूर्ण

	/* Get core frequency */
	अगर (of_property_पढ़ो_u32(ofdev->dev.of_node, "freq", &freq_hz)) अणु
		dev_err(&ofdev->dev, "unable to get core frequency\n");
		वापस -EINVAL;
	पूर्ण

	/* Set reload रेजिस्टर to core freq in kHz/10 */
	ioग_लिखो32be(freq_hz / 10000, &priv->regs->reload);

	priv->io = kzalloc(माप(काष्ठा serio), GFP_KERNEL);
	अगर (!priv->io)
		वापस -ENOMEM;

	priv->io->id.type = SERIO_8042;
	priv->io->खोलो = apbps2_खोलो;
	priv->io->बंद = apbps2_बंद;
	priv->io->ग_लिखो = apbps2_ग_लिखो;
	priv->io->port_data = priv;
	strlcpy(priv->io->name, "APBPS2 PS/2", माप(priv->io->name));
	snम_लिखो(priv->io->phys, माप(priv->io->phys),
		 "apbps2_%d", apbps2_idx++);

	dev_info(&ofdev->dev, "irq = %d, base = 0x%p\n", irq, priv->regs);

	serio_रेजिस्टर_port(priv->io);

	platक्रमm_set_drvdata(ofdev, priv);

	वापस 0;
पूर्ण

अटल पूर्णांक apbps2_of_हटाओ(काष्ठा platक्रमm_device *of_dev)
अणु
	काष्ठा apbps2_priv *priv = platक्रमm_get_drvdata(of_dev);

	serio_unरेजिस्टर_port(priv->io);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id apbps2_of_match[] = अणु
	अणु .name = "GAISLER_APBPS2", पूर्ण,
	अणु .name = "01_060", पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, apbps2_of_match);

अटल काष्ठा platक्रमm_driver apbps2_of_driver = अणु
	.driver = अणु
		.name = "grlib-apbps2",
		.of_match_table = apbps2_of_match,
	पूर्ण,
	.probe = apbps2_of_probe,
	.हटाओ = apbps2_of_हटाओ,
पूर्ण;

module_platक्रमm_driver(apbps2_of_driver);

MODULE_AUTHOR("Aeroflex Gaisler AB.");
MODULE_DESCRIPTION("GRLIB APBPS2 PS/2 serial I/O");
MODULE_LICENSE("GPL");
