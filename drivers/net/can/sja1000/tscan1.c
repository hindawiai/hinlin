<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * tscan1.c: driver क्रम Technologic Systems TS-CAN1 PC104 boards
 *
 * Copyright 2010 Andre B. Oliveira
 */

/*
 * References:
 * - Getting started with TS-CAN1, Technologic Systems, Jun 2009
 *	http://www.embeddedarm.com/करोcumentation/ts-can1-manual.pdf
 */

#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/isa.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश "sja1000.h"

MODULE_DESCRIPTION("Driver for Technologic Systems TS-CAN1 PC104 boards");
MODULE_AUTHOR("Andre B. Oliveira <anbadeol@gmail.com>");
MODULE_LICENSE("GPL");

/* Maximum number of boards (one in each JP1:JP2 setting of IO address) */
#घोषणा TSCAN1_MAXDEV 4

/* PLD रेजिस्टरs address offsets */
#घोषणा TSCAN1_ID1	0
#घोषणा TSCAN1_ID2	1
#घोषणा TSCAN1_VERSION	2
#घोषणा TSCAN1_LED	3
#घोषणा TSCAN1_PAGE	4
#घोषणा TSCAN1_MODE	5
#घोषणा TSCAN1_JUMPERS	6

/* PLD board identअगरier रेजिस्टरs magic values */
#घोषणा TSCAN1_ID1_VALUE 0xf6
#घोषणा TSCAN1_ID2_VALUE 0xb9

/* PLD mode रेजिस्टर SJA1000 IO enable bit */
#घोषणा TSCAN1_MODE_ENABLE 0x40

/* PLD jumpers रेजिस्टर bits */
#घोषणा TSCAN1_JP4 0x10
#घोषणा TSCAN1_JP5 0x20

/* PLD IO base addresses start */
#घोषणा TSCAN1_PLD_ADDRESS 0x150

/* PLD रेजिस्टर space size */
#घोषणा TSCAN1_PLD_SIZE 8

/* SJA1000 रेजिस्टर space size */
#घोषणा TSCAN1_SJA1000_SIZE 32

/* SJA1000 crystal frequency (16MHz) */
#घोषणा TSCAN1_SJA1000_XTAL 16000000

/* SJA1000 IO base addresses */
अटल स्थिर अचिन्हित लघु tscan1_sja1000_addresses[] = अणु
	0x100, 0x120, 0x180, 0x1a0, 0x200, 0x240, 0x280, 0x320
पूर्ण;

/* Read SJA1000 रेजिस्टर */
अटल u8 tscan1_पढ़ो(स्थिर काष्ठा sja1000_priv *priv, पूर्णांक reg)
अणु
	वापस inb((अचिन्हित दीर्घ)priv->reg_base + reg);
पूर्ण

/* Write SJA1000 रेजिस्टर */
अटल व्योम tscan1_ग_लिखो(स्थिर काष्ठा sja1000_priv *priv, पूर्णांक reg, u8 val)
अणु
	outb(val, (अचिन्हित दीर्घ)priv->reg_base + reg);
पूर्ण

/* Probe क्रम a TS-CAN1 board with JP2:JP1 jumper setting ID */
अटल पूर्णांक tscan1_probe(काष्ठा device *dev, अचिन्हित id)
अणु
	काष्ठा net_device *netdev;
	काष्ठा sja1000_priv *priv;
	अचिन्हित दीर्घ pld_base, sja1000_base;
	पूर्णांक irq, i;

	pld_base = TSCAN1_PLD_ADDRESS + id * TSCAN1_PLD_SIZE;
	अगर (!request_region(pld_base, TSCAN1_PLD_SIZE, dev_name(dev)))
		वापस -EBUSY;

	अगर (inb(pld_base + TSCAN1_ID1) != TSCAN1_ID1_VALUE ||
	    inb(pld_base + TSCAN1_ID2) != TSCAN1_ID2_VALUE) अणु
		release_region(pld_base, TSCAN1_PLD_SIZE);
		वापस -ENODEV;
	पूर्ण

	चयन (inb(pld_base + TSCAN1_JUMPERS) & (TSCAN1_JP4 | TSCAN1_JP5)) अणु
	हाल TSCAN1_JP4:
		irq = 6;
		अवरोध;
	हाल TSCAN1_JP5:
		irq = 7;
		अवरोध;
	हाल TSCAN1_JP4 | TSCAN1_JP5:
		irq = 5;
		अवरोध;
	शेष:
		dev_err(dev, "invalid JP4:JP5 setting (no IRQ)\n");
		release_region(pld_base, TSCAN1_PLD_SIZE);
		वापस -EINVAL;
	पूर्ण

	netdev = alloc_sja1000dev(0);
	अगर (!netdev) अणु
		release_region(pld_base, TSCAN1_PLD_SIZE);
		वापस -ENOMEM;
	पूर्ण

	dev_set_drvdata(dev, netdev);
	SET_NETDEV_DEV(netdev, dev);

	netdev->base_addr = pld_base;
	netdev->irq = irq;

	priv = netdev_priv(netdev);
	priv->पढ़ो_reg = tscan1_पढ़ो;
	priv->ग_लिखो_reg = tscan1_ग_लिखो;
	priv->can.घड़ी.freq = TSCAN1_SJA1000_XTAL / 2;
	priv->cdr = CDR_CBP | CDR_CLK_OFF;
	priv->ocr = OCR_TX0_PUSHPULL;

	/* Select the first SJA1000 IO address that is मुक्त and that works */
	क्रम (i = 0; i < ARRAY_SIZE(tscan1_sja1000_addresses); i++) अणु
		sja1000_base = tscan1_sja1000_addresses[i];
		अगर (!request_region(sja1000_base, TSCAN1_SJA1000_SIZE,
								dev_name(dev)))
			जारी;

		/* Set SJA1000 IO base address and enable it */
		outb(TSCAN1_MODE_ENABLE | i, pld_base + TSCAN1_MODE);

		priv->reg_base = (व्योम __iomem *)sja1000_base;
		अगर (!रेजिस्टर_sja1000dev(netdev)) अणु
			/* SJA1000 probe succeeded; turn LED off and वापस */
			outb(0, pld_base + TSCAN1_LED);
			netdev_info(netdev, "TS-CAN1 at 0x%lx 0x%lx irq %d\n",
						pld_base, sja1000_base, irq);
			वापस 0;
		पूर्ण

		/* SJA1000 probe failed; release and try next address */
		outb(0, pld_base + TSCAN1_MODE);
		release_region(sja1000_base, TSCAN1_SJA1000_SIZE);
	पूर्ण

	dev_err(dev, "failed to assign SJA1000 IO address\n");
	dev_set_drvdata(dev, शून्य);
	मुक्त_sja1000dev(netdev);
	release_region(pld_base, TSCAN1_PLD_SIZE);
	वापस -ENXIO;
पूर्ण

अटल व्योम tscan1_हटाओ(काष्ठा device *dev, अचिन्हित id /*unused*/)
अणु
	काष्ठा net_device *netdev;
	काष्ठा sja1000_priv *priv;
	अचिन्हित दीर्घ pld_base, sja1000_base;

	netdev = dev_get_drvdata(dev);
	unरेजिस्टर_sja1000dev(netdev);
	dev_set_drvdata(dev, शून्य);

	priv = netdev_priv(netdev);
	pld_base = netdev->base_addr;
	sja1000_base = (अचिन्हित दीर्घ)priv->reg_base;

	outb(0, pld_base + TSCAN1_MODE);	/* disable SJA1000 IO space */

	release_region(sja1000_base, TSCAN1_SJA1000_SIZE);
	release_region(pld_base, TSCAN1_PLD_SIZE);

	मुक्त_sja1000dev(netdev);
पूर्ण

अटल काष्ठा isa_driver tscan1_isa_driver = अणु
	.probe = tscan1_probe,
	.हटाओ = tscan1_हटाओ,
	.driver = अणु
		.name = "tscan1",
	पूर्ण,
पूर्ण;

module_isa_driver(tscan1_isa_driver, TSCAN1_MAXDEV);
