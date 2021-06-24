<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008 Sebastian Haas (initial अक्षरdev implementation)
 * Copyright (C) 2010 Markus Plessing <plessing@ems-wuensche.com>
 * Rework क्रम मुख्यline by Oliver Hartkopp <socketcan@hartkopp.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ds.h>
#समावेश <linux/can.h>
#समावेश <linux/can/dev.h>
#समावेश "sja1000.h"

#घोषणा DRV_NAME "ems_pcmcia"

MODULE_AUTHOR("Markus Plessing <plessing@ems-wuensche.com>");
MODULE_DESCRIPTION("Socket-CAN driver for EMS CPC-CARD cards");
MODULE_LICENSE("GPL v2");

#घोषणा EMS_PCMCIA_MAX_CHAN 2

काष्ठा ems_pcmcia_card अणु
	पूर्णांक channels;
	काष्ठा pcmcia_device *pcmcia_dev;
	काष्ठा net_device *net_dev[EMS_PCMCIA_MAX_CHAN];
	व्योम __iomem *base_addr;
पूर्ण;

#घोषणा EMS_PCMCIA_CAN_CLOCK (16000000 / 2)

/*
 * The board configuration is probably following:
 * RX1 is connected to ground.
 * TX1 is not connected.
 * CLKO is not connected.
 * Setting the OCR रेजिस्टर to 0xDA is a good idea.
 * This means  normal output mode , push-pull and the correct polarity.
 */
#घोषणा EMS_PCMCIA_OCR (OCR_TX0_PUSHPULL | OCR_TX1_PUSHPULL)

/*
 * In the CDR रेजिस्टर, you should set CBP to 1.
 * You will probably also want to set the घड़ी भागider value to 7
 * (meaning direct oscillator output) because the second SJA1000 chip
 * is driven by the first one CLKOUT output.
 */
#घोषणा EMS_PCMCIA_CDR (CDR_CBP | CDR_CLKOUT_MASK)
#घोषणा EMS_PCMCIA_MEM_SIZE 4096 /* Size of the remapped io-memory */
#घोषणा EMS_PCMCIA_CAN_BASE_OFFSET 0x100 /* Offset where controllers starts */
#घोषणा EMS_PCMCIA_CAN_CTRL_SIZE 0x80 /* Memory size क्रम each controller */

#घोषणा EMS_CMD_RESET 0x00 /* Perक्रमm a reset of the card */
#घोषणा EMS_CMD_MAP   0x03 /* Map CAN controllers पूर्णांकo card' memory */
#घोषणा EMS_CMD_UMAP  0x02 /* Unmap CAN controllers from card' memory */

अटल काष्ठा pcmcia_device_id ems_pcmcia_tbl[] = अणु
	PCMCIA_DEVICE_PROD_ID123("EMS_T_W", "CPC-Card", "V2.0", 0xeab1ea23,
				 0xa338573f, 0xe4575800),
	PCMCIA_DEVICE_शून्य,
पूर्ण;

MODULE_DEVICE_TABLE(pcmcia, ems_pcmcia_tbl);

अटल u8 ems_pcmcia_पढ़ो_reg(स्थिर काष्ठा sja1000_priv *priv, पूर्णांक port)
अणु
	वापस पढ़ोb(priv->reg_base + port);
पूर्ण

अटल व्योम ems_pcmcia_ग_लिखो_reg(स्थिर काष्ठा sja1000_priv *priv, पूर्णांक port,
				 u8 val)
अणु
	ग_लिखोb(val, priv->reg_base + port);
पूर्ण

अटल irqवापस_t ems_pcmcia_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ems_pcmcia_card *card = dev_id;
	काष्ठा net_device *dev;
	irqवापस_t retval = IRQ_NONE;
	पूर्णांक i, again;

	/* Card not present */
	अगर (पढ़ोw(card->base_addr) != 0xAA55)
		वापस IRQ_HANDLED;

	करो अणु
		again = 0;

		/* Check पूर्णांकerrupt क्रम each channel */
		क्रम (i = 0; i < card->channels; i++) अणु
			dev = card->net_dev[i];
			अगर (!dev)
				जारी;

			अगर (sja1000_पूर्णांकerrupt(irq, dev) == IRQ_HANDLED)
				again = 1;
		पूर्ण
		/* At least one channel handled the पूर्णांकerrupt */
		अगर (again)
			retval = IRQ_HANDLED;

	पूर्ण जबतक (again);

	वापस retval;
पूर्ण

/*
 * Check अगर a CAN controller is present at the specअगरied location
 * by trying to set 'em पूर्णांकo the PeliCAN mode
 */
अटल अंतरभूत पूर्णांक ems_pcmcia_check_chan(काष्ठा sja1000_priv *priv)
अणु
	/* Make sure SJA1000 is in reset mode */
	ems_pcmcia_ग_लिखो_reg(priv, SJA1000_MOD, 1);
	ems_pcmcia_ग_लिखो_reg(priv, SJA1000_CDR, CDR_PELICAN);

	/* पढ़ो reset-values */
	अगर (ems_pcmcia_पढ़ो_reg(priv, SJA1000_CDR) == CDR_PELICAN)
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम ems_pcmcia_del_card(काष्ठा pcmcia_device *pdev)
अणु
	काष्ठा ems_pcmcia_card *card = pdev->priv;
	काष्ठा net_device *dev;
	पूर्णांक i;

	मुक्त_irq(pdev->irq, card);

	क्रम (i = 0; i < card->channels; i++) अणु
		dev = card->net_dev[i];
		अगर (!dev)
			जारी;

		prपूर्णांकk(KERN_INFO "%s: removing %s on channel #%d\n",
		       DRV_NAME, dev->name, i);
		unरेजिस्टर_sja1000dev(dev);
		मुक्त_sja1000dev(dev);
	पूर्ण

	ग_लिखोb(EMS_CMD_UMAP, card->base_addr);
	iounmap(card->base_addr);
	kमुक्त(card);

	pdev->priv = शून्य;
पूर्ण

/*
 * Probe PCI device क्रम EMS CAN signature and रेजिस्टर each available
 * CAN channel to SJA1000 Socket-CAN subप्रणाली.
 */
अटल पूर्णांक ems_pcmcia_add_card(काष्ठा pcmcia_device *pdev, अचिन्हित दीर्घ base)
अणु
	काष्ठा sja1000_priv *priv;
	काष्ठा net_device *dev;
	काष्ठा ems_pcmcia_card *card;
	पूर्णांक err, i;

	/* Allocating card काष्ठाures to hold addresses, ... */
	card = kzalloc(माप(काष्ठा ems_pcmcia_card), GFP_KERNEL);
	अगर (!card)
		वापस -ENOMEM;

	pdev->priv = card;
	card->channels = 0;

	card->base_addr = ioremap(base, EMS_PCMCIA_MEM_SIZE);
	अगर (!card->base_addr) अणु
		err = -ENOMEM;
		जाओ failure_cleanup;
	पूर्ण

	/* Check क्रम unique EMS CAN signature */
	अगर (पढ़ोw(card->base_addr) != 0xAA55) अणु
		err = -ENODEV;
		जाओ failure_cleanup;
	पूर्ण

	/* Request board reset */
	ग_लिखोb(EMS_CMD_RESET, card->base_addr);

	/* Make sure CAN controllers are mapped पूर्णांकo card's memory space */
	ग_लिखोb(EMS_CMD_MAP, card->base_addr);

	/* Detect available channels */
	क्रम (i = 0; i < EMS_PCMCIA_MAX_CHAN; i++) अणु
		dev = alloc_sja1000dev(0);
		अगर (!dev) अणु
			err = -ENOMEM;
			जाओ failure_cleanup;
		पूर्ण

		card->net_dev[i] = dev;
		priv = netdev_priv(dev);
		priv->priv = card;
		SET_NETDEV_DEV(dev, &pdev->dev);
		dev->dev_id = i;

		priv->irq_flags = IRQF_SHARED;
		dev->irq = pdev->irq;
		priv->reg_base = card->base_addr + EMS_PCMCIA_CAN_BASE_OFFSET +
			(i * EMS_PCMCIA_CAN_CTRL_SIZE);

		/* Check अगर channel is present */
		अगर (ems_pcmcia_check_chan(priv)) अणु
			priv->पढ़ो_reg  = ems_pcmcia_पढ़ो_reg;
			priv->ग_लिखो_reg = ems_pcmcia_ग_लिखो_reg;
			priv->can.घड़ी.freq = EMS_PCMCIA_CAN_CLOCK;
			priv->ocr = EMS_PCMCIA_OCR;
			priv->cdr = EMS_PCMCIA_CDR;
			priv->flags |= SJA1000_CUSTOM_IRQ_HANDLER;

			/* Register SJA1000 device */
			err = रेजिस्टर_sja1000dev(dev);
			अगर (err) अणु
				मुक्त_sja1000dev(dev);
				जाओ failure_cleanup;
			पूर्ण

			card->channels++;

			prपूर्णांकk(KERN_INFO "%s: registered %s on channel "
			       "#%d at 0x%p, irq %d\n", DRV_NAME, dev->name,
			       i, priv->reg_base, dev->irq);
		पूर्ण अन्यथा
			मुक्त_sja1000dev(dev);
	पूर्ण

	err = request_irq(dev->irq, &ems_pcmcia_पूर्णांकerrupt, IRQF_SHARED,
			  DRV_NAME, card);
	अगर (!err)
		वापस 0;

failure_cleanup:
	ems_pcmcia_del_card(pdev);
	वापस err;
पूर्ण

/*
 * Setup PCMCIA socket and probe क्रम EMS CPC-CARD
 */
अटल पूर्णांक ems_pcmcia_probe(काष्ठा pcmcia_device *dev)
अणु
	पूर्णांक csval;

	/* General socket configuration */
	dev->config_flags |= CONF_ENABLE_IRQ;
	dev->config_index = 1;
	dev->config_regs = PRESENT_OPTION;

	/* The io काष्ठाure describes IO port mapping */
	dev->resource[0]->end = 16;
	dev->resource[0]->flags |= IO_DATA_PATH_WIDTH_8;
	dev->resource[1]->end = 16;
	dev->resource[1]->flags |= IO_DATA_PATH_WIDTH_16;
	dev->io_lines = 5;

	/* Allocate a memory winकरोw */
	dev->resource[2]->flags =
		(WIN_DATA_WIDTH_8 | WIN_MEMORY_TYPE_CM | WIN_ENABLE);
	dev->resource[2]->start = dev->resource[2]->end = 0;

	csval = pcmcia_request_winकरोw(dev, dev->resource[2], 0);
	अगर (csval) अणु
		dev_err(&dev->dev, "pcmcia_request_window failed (err=%d)\n",
			csval);
		वापस 0;
	पूर्ण

	csval = pcmcia_map_mem_page(dev, dev->resource[2], dev->config_base);
	अगर (csval) अणु
		dev_err(&dev->dev, "pcmcia_map_mem_page failed (err=%d)\n",
			csval);
		वापस 0;
	पूर्ण

	csval = pcmcia_enable_device(dev);
	अगर (csval) अणु
		dev_err(&dev->dev, "pcmcia_enable_device failed (err=%d)\n",
			csval);
		वापस 0;
	पूर्ण

	ems_pcmcia_add_card(dev, dev->resource[2]->start);
	वापस 0;
पूर्ण

/*
 * Release claimed resources
 */
अटल व्योम ems_pcmcia_हटाओ(काष्ठा pcmcia_device *dev)
अणु
	ems_pcmcia_del_card(dev);
	pcmcia_disable_device(dev);
पूर्ण

अटल काष्ठा pcmcia_driver ems_pcmcia_driver = अणु
	.name = DRV_NAME,
	.probe = ems_pcmcia_probe,
	.हटाओ = ems_pcmcia_हटाओ,
	.id_table = ems_pcmcia_tbl,
पूर्ण;
module_pcmcia_driver(ems_pcmcia_driver);
