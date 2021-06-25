<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2007 Wolfgang Gअक्रमegger <wg@gअक्रमegger.com>
 * Copyright (C) 2008 Markus Plessing <plessing@ems-wuensche.com>
 * Copyright (C) 2008 Sebastian Haas <haas@ems-wuensche.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/पन.स>

#समावेश "sja1000.h"

#घोषणा DRV_NAME  "ems_pci"

MODULE_AUTHOR("Sebastian Haas <haas@ems-wuenche.com>");
MODULE_DESCRIPTION("Socket-CAN driver for EMS CPC-PCI/PCIe/104P CAN cards");
MODULE_LICENSE("GPL v2");

#घोषणा EMS_PCI_V1_MAX_CHAN 2
#घोषणा EMS_PCI_V2_MAX_CHAN 4
#घोषणा EMS_PCI_MAX_CHAN    EMS_PCI_V2_MAX_CHAN

काष्ठा ems_pci_card अणु
	पूर्णांक version;
	पूर्णांक channels;

	काष्ठा pci_dev *pci_dev;
	काष्ठा net_device *net_dev[EMS_PCI_MAX_CHAN];

	व्योम __iomem *conf_addr;
	व्योम __iomem *base_addr;
पूर्ण;

#घोषणा EMS_PCI_CAN_CLOCK (16000000 / 2)

/*
 * Register definitions and descriptions are from LinCAN 0.3.3.
 *
 * PSB4610 PITA-2 bridge control रेजिस्टरs
 */
#घोषणा PITA2_ICR           0x00	/* Interrupt Control Register */
#घोषणा PITA2_ICR_INT0      0x00000002	/* [RC] INT0 Active/Clear */
#घोषणा PITA2_ICR_INT0_EN   0x00020000	/* [RW] Enable INT0 */

#घोषणा PITA2_MISC          0x1c	/* Miscellaneous Register */
#घोषणा PITA2_MISC_CONFIG   0x04000000	/* Multiplexed parallel पूर्णांकerface */

/*
 * Register definitions क्रम the PLX 9030
 */
#घोषणा PLX_ICSR            0x4c   /* Interrupt Control/Status रेजिस्टर */
#घोषणा PLX_ICSR_LINTI1_ENA 0x0001 /* LINTi1 Enable */
#घोषणा PLX_ICSR_PCIINT_ENA 0x0040 /* PCI Interrupt Enable */
#घोषणा PLX_ICSR_LINTI1_CLR 0x0400 /* Local Edge Triggerable Interrupt Clear */
#घोषणा PLX_ICSR_ENA_CLR    (PLX_ICSR_LINTI1_ENA | PLX_ICSR_PCIINT_ENA | \
			     PLX_ICSR_LINTI1_CLR)

/*
 * The board configuration is probably following:
 * RX1 is connected to ground.
 * TX1 is not connected.
 * CLKO is not connected.
 * Setting the OCR रेजिस्टर to 0xDA is a good idea.
 * This means normal output mode, push-pull and the correct polarity.
 */
#घोषणा EMS_PCI_OCR         (OCR_TX0_PUSHPULL | OCR_TX1_PUSHPULL)

/*
 * In the CDR रेजिस्टर, you should set CBP to 1.
 * You will probably also want to set the घड़ी भागider value to 7
 * (meaning direct oscillator output) because the second SJA1000 chip
 * is driven by the first one CLKOUT output.
 */
#घोषणा EMS_PCI_CDR             (CDR_CBP | CDR_CLKOUT_MASK)

#घोषणा EMS_PCI_V1_BASE_BAR     1
#घोषणा EMS_PCI_V1_CONF_SIZE    4096 /* size of PITA control area */
#घोषणा EMS_PCI_V2_BASE_BAR     2
#घोषणा EMS_PCI_V2_CONF_SIZE    128 /* size of PLX control area */
#घोषणा EMS_PCI_CAN_BASE_OFFSET 0x400 /* offset where the controllers starts */
#घोषणा EMS_PCI_CAN_CTRL_SIZE   0x200 /* memory size क्रम each controller */

#घोषणा EMS_PCI_BASE_SIZE  4096 /* size of controller area */

अटल स्थिर काष्ठा pci_device_id ems_pci_tbl[] = अणु
	/* CPC-PCI v1 */
	अणुPCI_VENDOR_ID_SIEMENS, 0x2104, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
	/* CPC-PCI v2 */
	अणुPCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9030, PCI_VENDOR_ID_PLX, 0x4000पूर्ण,
	/* CPC-104P v2 */
	अणुPCI_VENDOR_ID_PLX, PCI_DEVICE_ID_PLX_9030, PCI_VENDOR_ID_PLX, 0x4002पूर्ण,
	अणु0,पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, ems_pci_tbl);

/*
 * Helper to पढ़ो पूर्णांकernal रेजिस्टरs from card logic (not CAN)
 */
अटल u8 ems_pci_v1_पढ़ोb(काष्ठा ems_pci_card *card, अचिन्हित पूर्णांक port)
अणु
	वापस पढ़ोb(card->base_addr + (port * 4));
पूर्ण

अटल u8 ems_pci_v1_पढ़ो_reg(स्थिर काष्ठा sja1000_priv *priv, पूर्णांक port)
अणु
	वापस पढ़ोb(priv->reg_base + (port * 4));
पूर्ण

अटल व्योम ems_pci_v1_ग_लिखो_reg(स्थिर काष्ठा sja1000_priv *priv,
				 पूर्णांक port, u8 val)
अणु
	ग_लिखोb(val, priv->reg_base + (port * 4));
पूर्ण

अटल व्योम ems_pci_v1_post_irq(स्थिर काष्ठा sja1000_priv *priv)
अणु
	काष्ठा ems_pci_card *card = (काष्ठा ems_pci_card *)priv->priv;

	/* reset पूर्णांक flag of pita */
	ग_लिखोl(PITA2_ICR_INT0_EN | PITA2_ICR_INT0,
	       card->conf_addr + PITA2_ICR);
पूर्ण

अटल u8 ems_pci_v2_पढ़ो_reg(स्थिर काष्ठा sja1000_priv *priv, पूर्णांक port)
अणु
	वापस पढ़ोb(priv->reg_base + port);
पूर्ण

अटल व्योम ems_pci_v2_ग_लिखो_reg(स्थिर काष्ठा sja1000_priv *priv,
				 पूर्णांक port, u8 val)
अणु
	ग_लिखोb(val, priv->reg_base + port);
पूर्ण

अटल व्योम ems_pci_v2_post_irq(स्थिर काष्ठा sja1000_priv *priv)
अणु
	काष्ठा ems_pci_card *card = (काष्ठा ems_pci_card *)priv->priv;

	ग_लिखोl(PLX_ICSR_ENA_CLR, card->conf_addr + PLX_ICSR);
पूर्ण

/*
 * Check अगर a CAN controller is present at the specअगरied location
 * by trying to set 'em पूर्णांकo the PeliCAN mode
 */
अटल अंतरभूत पूर्णांक ems_pci_check_chan(स्थिर काष्ठा sja1000_priv *priv)
अणु
	अचिन्हित अक्षर res;

	/* Make sure SJA1000 is in reset mode */
	priv->ग_लिखो_reg(priv, SJA1000_MOD, 1);

	priv->ग_लिखो_reg(priv, SJA1000_CDR, CDR_PELICAN);

	/* पढ़ो reset-values */
	res = priv->पढ़ो_reg(priv, SJA1000_CDR);

	अगर (res == CDR_PELICAN)
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम ems_pci_del_card(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ems_pci_card *card = pci_get_drvdata(pdev);
	काष्ठा net_device *dev;
	पूर्णांक i = 0;

	क्रम (i = 0; i < card->channels; i++) अणु
		dev = card->net_dev[i];

		अगर (!dev)
			जारी;

		dev_info(&pdev->dev, "Removing %s.\n", dev->name);
		unरेजिस्टर_sja1000dev(dev);
		मुक्त_sja1000dev(dev);
	पूर्ण

	अगर (card->base_addr != शून्य)
		pci_iounmap(card->pci_dev, card->base_addr);

	अगर (card->conf_addr != शून्य)
		pci_iounmap(card->pci_dev, card->conf_addr);

	kमुक्त(card);

	pci_disable_device(pdev);
पूर्ण

अटल व्योम ems_pci_card_reset(काष्ठा ems_pci_card *card)
अणु
	/* Request board reset */
	ग_लिखोb(0, card->base_addr);
पूर्ण

/*
 * Probe PCI device क्रम EMS CAN signature and रेजिस्टर each available
 * CAN channel to SJA1000 Socket-CAN subप्रणाली.
 */
अटल पूर्णांक ems_pci_add_card(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा sja1000_priv *priv;
	काष्ठा net_device *dev;
	काष्ठा ems_pci_card *card;
	पूर्णांक max_chan, conf_size, base_bar;
	पूर्णांक err, i;

	/* Enabling PCI device */
	अगर (pci_enable_device(pdev) < 0) अणु
		dev_err(&pdev->dev, "Enabling PCI device failed\n");
		वापस -ENODEV;
	पूर्ण

	/* Allocating card काष्ठाures to hold addresses, ... */
	card = kzalloc(माप(काष्ठा ems_pci_card), GFP_KERNEL);
	अगर (card == शून्य) अणु
		pci_disable_device(pdev);
		वापस -ENOMEM;
	पूर्ण

	pci_set_drvdata(pdev, card);

	card->pci_dev = pdev;

	card->channels = 0;

	अगर (pdev->venकरोr == PCI_VENDOR_ID_PLX) अणु
		card->version = 2; /* CPC-PCI v2 */
		max_chan = EMS_PCI_V2_MAX_CHAN;
		base_bar = EMS_PCI_V2_BASE_BAR;
		conf_size = EMS_PCI_V2_CONF_SIZE;
	पूर्ण अन्यथा अणु
		card->version = 1; /* CPC-PCI v1 */
		max_chan = EMS_PCI_V1_MAX_CHAN;
		base_bar = EMS_PCI_V1_BASE_BAR;
		conf_size = EMS_PCI_V1_CONF_SIZE;
	पूर्ण

	/* Remap configuration space and controller memory area */
	card->conf_addr = pci_iomap(pdev, 0, conf_size);
	अगर (card->conf_addr == शून्य) अणु
		err = -ENOMEM;
		जाओ failure_cleanup;
	पूर्ण

	card->base_addr = pci_iomap(pdev, base_bar, EMS_PCI_BASE_SIZE);
	अगर (card->base_addr == शून्य) अणु
		err = -ENOMEM;
		जाओ failure_cleanup;
	पूर्ण

	अगर (card->version == 1) अणु
		/* Configure PITA-2 parallel पूर्णांकerface (enable MUX) */
		ग_लिखोl(PITA2_MISC_CONFIG, card->conf_addr + PITA2_MISC);

		/* Check क्रम unique EMS CAN signature */
		अगर (ems_pci_v1_पढ़ोb(card, 0) != 0x55 ||
		    ems_pci_v1_पढ़ोb(card, 1) != 0xAA ||
		    ems_pci_v1_पढ़ोb(card, 2) != 0x01 ||
		    ems_pci_v1_पढ़ोb(card, 3) != 0xCB ||
		    ems_pci_v1_पढ़ोb(card, 4) != 0x11) अणु
			dev_err(&pdev->dev,
				"Not EMS Dr. Thomas Wuensche interface\n");
			err = -ENODEV;
			जाओ failure_cleanup;
		पूर्ण
	पूर्ण

	ems_pci_card_reset(card);

	/* Detect available channels */
	क्रम (i = 0; i < max_chan; i++) अणु
		dev = alloc_sja1000dev(0);
		अगर (dev == शून्य) अणु
			err = -ENOMEM;
			जाओ failure_cleanup;
		पूर्ण

		card->net_dev[i] = dev;
		priv = netdev_priv(dev);
		priv->priv = card;
		priv->irq_flags = IRQF_SHARED;

		dev->irq = pdev->irq;
		priv->reg_base = card->base_addr + EMS_PCI_CAN_BASE_OFFSET
					+ (i * EMS_PCI_CAN_CTRL_SIZE);
		अगर (card->version == 1) अणु
			priv->पढ़ो_reg  = ems_pci_v1_पढ़ो_reg;
			priv->ग_लिखो_reg = ems_pci_v1_ग_लिखो_reg;
			priv->post_irq  = ems_pci_v1_post_irq;
		पूर्ण अन्यथा अणु
			priv->पढ़ो_reg  = ems_pci_v2_पढ़ो_reg;
			priv->ग_लिखो_reg = ems_pci_v2_ग_लिखो_reg;
			priv->post_irq  = ems_pci_v2_post_irq;
		पूर्ण

		/* Check अगर channel is present */
		अगर (ems_pci_check_chan(priv)) अणु
			priv->can.घड़ी.freq = EMS_PCI_CAN_CLOCK;
			priv->ocr = EMS_PCI_OCR;
			priv->cdr = EMS_PCI_CDR;

			SET_NETDEV_DEV(dev, &pdev->dev);
			dev->dev_id = i;

			अगर (card->version == 1)
				/* reset पूर्णांक flag of pita */
				ग_लिखोl(PITA2_ICR_INT0_EN | PITA2_ICR_INT0,
				       card->conf_addr + PITA2_ICR);
			अन्यथा
				/* enable IRQ in PLX 9030 */
				ग_लिखोl(PLX_ICSR_ENA_CLR,
				       card->conf_addr + PLX_ICSR);

			/* Register SJA1000 device */
			err = रेजिस्टर_sja1000dev(dev);
			अगर (err) अणु
				dev_err(&pdev->dev, "Registering device failed "
							"(err=%d)\n", err);
				मुक्त_sja1000dev(dev);
				जाओ failure_cleanup;
			पूर्ण

			card->channels++;

			dev_info(&pdev->dev, "Channel #%d at 0x%p, irq %d\n",
					i + 1, priv->reg_base, dev->irq);
		पूर्ण अन्यथा अणु
			मुक्त_sja1000dev(dev);
		पूर्ण
	पूर्ण

	वापस 0;

failure_cleanup:
	dev_err(&pdev->dev, "Error: %d. Cleaning Up.\n", err);

	ems_pci_del_card(pdev);

	वापस err;
पूर्ण

अटल काष्ठा pci_driver ems_pci_driver = अणु
	.name = DRV_NAME,
	.id_table = ems_pci_tbl,
	.probe = ems_pci_add_card,
	.हटाओ = ems_pci_del_card,
पूर्ण;

module_pci_driver(ems_pci_driver);
