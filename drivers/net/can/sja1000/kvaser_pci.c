<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008 Per Dalen <per.dalen@cnw.se>
 *
 * Parts of this software are based on (derived) the following:
 *
 * - Kvaser linux driver, version 4.72 BETA
 *   Copyright (C) 2002-2007 KVASER AB
 *
 * - Lincan driver, version 0.3.3, OCERA project
 *   Copyright (C) 2004 Pavel Pisa
 *   Copyright (C) 2001 Arnaud Westenberg
 *
 * - Socketcan SJA1000 drivers
 *   Copyright (C) 2007 Wolfgang Gअक्रमegger <wg@gअक्रमegger.com>
 *   Copyright (c) 2002-2007 Volkswagen Group Electronic Research
 *   Copyright (c) 2003 Matthias Brukner, Trajet Gmbh, Rebenring 33,
 *   38106 Braunschweig, GERMANY
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/पन.स>

#समावेश "sja1000.h"

#घोषणा DRV_NAME  "kvaser_pci"

MODULE_AUTHOR("Per Dalen <per.dalen@cnw.se>");
MODULE_DESCRIPTION("Socket-CAN driver for KVASER PCAN PCI cards");
MODULE_LICENSE("GPL v2");

#घोषणा MAX_NO_OF_CHANNELS        4 /* max no of channels on a single card */

काष्ठा kvaser_pci अणु
	पूर्णांक channel;
	काष्ठा pci_dev *pci_dev;
	काष्ठा net_device *slave_dev[MAX_NO_OF_CHANNELS-1];
	व्योम __iomem *conf_addr;
	व्योम __iomem *res_addr;
	पूर्णांक no_channels;
	u8 xilinx_ver;
पूर्ण;

#घोषणा KVASER_PCI_CAN_CLOCK      (16000000 / 2)

/*
 * The board configuration is probably following:
 * RX1 is connected to ground.
 * TX1 is not connected.
 * CLKO is not connected.
 * Setting the OCR रेजिस्टर to 0xDA is a good idea.
 * This means  normal output mode , push-pull and the correct polarity.
 */
#घोषणा KVASER_PCI_OCR            (OCR_TX0_PUSHPULL | OCR_TX1_PUSHPULL)

/*
 * In the CDR रेजिस्टर, you should set CBP to 1.
 * You will probably also want to set the घड़ी भागider value to 0
 * (meaning भागide-by-2), the Pelican bit, and the घड़ी-off bit
 * (you will have no need क्रम CLKOUT anyway).
 */
#घोषणा KVASER_PCI_CDR            (CDR_CBP | CDR_CLKOUT_MASK)

/*
 * These रेजिस्टर values are valid क्रम revision 14 of the Xilinx logic.
 */
#घोषणा XILINX_VERINT             7   /* Lower nibble simulate पूर्णांकerrupts,
					 high nibble version number. */

#घोषणा XILINX_PRESUMED_VERSION   14

/*
 * Important S5920 रेजिस्टरs
 */
#घोषणा S5920_INTCSR              0x38
#घोषणा S5920_PTCR                0x60
#घोषणा INTCSR_ADDON_INTENABLE_M  0x2000


#घोषणा KVASER_PCI_PORT_BYTES     0x20

#घोषणा PCI_CONFIG_PORT_SIZE      0x80      /* size of the config io-memory */
#घोषणा PCI_PORT_SIZE             0x80      /* size of a channel io-memory */
#घोषणा PCI_PORT_XILINX_SIZE      0x08      /* size of a xilinx io-memory */

#घोषणा KVASER_PCI_VENDOR_ID1     0x10e8    /* the PCI device and venकरोr IDs */
#घोषणा KVASER_PCI_DEVICE_ID1     0x8406

#घोषणा KVASER_PCI_VENDOR_ID2     0x1a07    /* the PCI device and venकरोr IDs */
#घोषणा KVASER_PCI_DEVICE_ID2     0x0008

अटल स्थिर काष्ठा pci_device_id kvaser_pci_tbl[] = अणु
	अणुKVASER_PCI_VENDOR_ID1, KVASER_PCI_DEVICE_ID1, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
	अणुKVASER_PCI_VENDOR_ID2, KVASER_PCI_DEVICE_ID2, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
	अणु 0,पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, kvaser_pci_tbl);

अटल u8 kvaser_pci_पढ़ो_reg(स्थिर काष्ठा sja1000_priv *priv, पूर्णांक port)
अणु
	वापस ioपढ़ो8(priv->reg_base + port);
पूर्ण

अटल व्योम kvaser_pci_ग_लिखो_reg(स्थिर काष्ठा sja1000_priv *priv,
				 पूर्णांक port, u8 val)
अणु
	ioग_लिखो8(val, priv->reg_base + port);
पूर्ण

अटल व्योम kvaser_pci_disable_irq(काष्ठा net_device *dev)
अणु
	काष्ठा sja1000_priv *priv = netdev_priv(dev);
	काष्ठा kvaser_pci *board = priv->priv;
	u32 पूर्णांकcsr;

	/* Disable पूर्णांकerrupts from card */
	पूर्णांकcsr = ioपढ़ो32(board->conf_addr + S5920_INTCSR);
	पूर्णांकcsr &= ~INTCSR_ADDON_INTENABLE_M;
	ioग_लिखो32(पूर्णांकcsr, board->conf_addr + S5920_INTCSR);
पूर्ण

अटल व्योम kvaser_pci_enable_irq(काष्ठा net_device *dev)
अणु
	काष्ठा sja1000_priv *priv = netdev_priv(dev);
	काष्ठा kvaser_pci *board = priv->priv;
	u32 पंचांगp_en_io;

	/* Enable पूर्णांकerrupts from card */
	पंचांगp_en_io = ioपढ़ो32(board->conf_addr + S5920_INTCSR);
	पंचांगp_en_io |= INTCSR_ADDON_INTENABLE_M;
	ioग_लिखो32(पंचांगp_en_io, board->conf_addr + S5920_INTCSR);
पूर्ण

अटल पूर्णांक number_of_sja1000_chip(व्योम __iomem *base_addr)
अणु
	u8 status;
	पूर्णांक i;

	क्रम (i = 0; i < MAX_NO_OF_CHANNELS; i++) अणु
		/* reset chip */
		ioग_लिखो8(MOD_RM, base_addr +
			 (i * KVASER_PCI_PORT_BYTES) + SJA1000_MOD);
		status = ioपढ़ो8(base_addr +
				 (i * KVASER_PCI_PORT_BYTES) + SJA1000_MOD);
		/* check reset bit */
		अगर (!(status & MOD_RM))
			अवरोध;
	पूर्ण

	वापस i;
पूर्ण

अटल व्योम kvaser_pci_del_chan(काष्ठा net_device *dev)
अणु
	काष्ठा sja1000_priv *priv;
	काष्ठा kvaser_pci *board;
	पूर्णांक i;

	अगर (!dev)
		वापस;
	priv = netdev_priv(dev);
	board = priv->priv;
	अगर (!board)
		वापस;

	dev_info(&board->pci_dev->dev, "Removing device %s\n",
		 dev->name);

	/* Disable PCI पूर्णांकerrupts */
	kvaser_pci_disable_irq(dev);

	क्रम (i = 0; i < board->no_channels - 1; i++) अणु
		अगर (board->slave_dev[i]) अणु
			dev_info(&board->pci_dev->dev, "Removing device %s\n",
				 board->slave_dev[i]->name);
			unरेजिस्टर_sja1000dev(board->slave_dev[i]);
			मुक्त_sja1000dev(board->slave_dev[i]);
		पूर्ण
	पूर्ण
	unरेजिस्टर_sja1000dev(dev);

	pci_iounmap(board->pci_dev, priv->reg_base);
	pci_iounmap(board->pci_dev, board->conf_addr);
	pci_iounmap(board->pci_dev, board->res_addr);

	मुक्त_sja1000dev(dev);
पूर्ण

अटल पूर्णांक kvaser_pci_add_chan(काष्ठा pci_dev *pdev, पूर्णांक channel,
			       काष्ठा net_device **master_dev,
			       व्योम __iomem *conf_addr,
			       व्योम __iomem *res_addr,
			       व्योम __iomem *base_addr)
अणु
	काष्ठा net_device *dev;
	काष्ठा sja1000_priv *priv;
	काष्ठा kvaser_pci *board;
	पूर्णांक err;

	dev = alloc_sja1000dev(माप(काष्ठा kvaser_pci));
	अगर (dev == शून्य)
		वापस -ENOMEM;

	priv = netdev_priv(dev);
	board = priv->priv;

	board->pci_dev = pdev;
	board->channel = channel;

	/* S5920 */
	board->conf_addr = conf_addr;

	/* XILINX board wide address */
	board->res_addr = res_addr;

	अगर (channel == 0) अणु
		board->xilinx_ver =
			ioपढ़ो8(board->res_addr + XILINX_VERINT) >> 4;

		/* Assert PTADR# - we're in passive mode so the other bits are
		   not important */
		ioग_लिखो32(0x80808080UL, board->conf_addr + S5920_PTCR);

		/* Enable पूर्णांकerrupts from card */
		kvaser_pci_enable_irq(dev);
	पूर्ण अन्यथा अणु
		काष्ठा sja1000_priv *master_priv = netdev_priv(*master_dev);
		काष्ठा kvaser_pci *master_board = master_priv->priv;
		master_board->slave_dev[channel - 1] = dev;
		master_board->no_channels = channel + 1;
		board->xilinx_ver = master_board->xilinx_ver;
	पूर्ण

	priv->reg_base = base_addr + channel * KVASER_PCI_PORT_BYTES;

	priv->पढ़ो_reg = kvaser_pci_पढ़ो_reg;
	priv->ग_लिखो_reg = kvaser_pci_ग_लिखो_reg;

	priv->can.घड़ी.freq = KVASER_PCI_CAN_CLOCK;

	priv->ocr = KVASER_PCI_OCR;
	priv->cdr = KVASER_PCI_CDR;

	priv->irq_flags = IRQF_SHARED;
	dev->irq = pdev->irq;

	dev_info(&pdev->dev, "reg_base=%p conf_addr=%p irq=%d\n",
		 priv->reg_base, board->conf_addr, dev->irq);

	SET_NETDEV_DEV(dev, &pdev->dev);
	dev->dev_id = channel;

	/* Register SJA1000 device */
	err = रेजिस्टर_sja1000dev(dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Registering device failed (err=%d)\n",
			err);
		जाओ failure;
	पूर्ण

	अगर (channel == 0)
		*master_dev = dev;

	वापस 0;

failure:
	kvaser_pci_del_chan(dev);
	वापस err;
पूर्ण

अटल पूर्णांक kvaser_pci_init_one(काष्ठा pci_dev *pdev,
			       स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक err;
	काष्ठा net_device *master_dev = शून्य;
	काष्ठा sja1000_priv *priv;
	काष्ठा kvaser_pci *board;
	पूर्णांक no_channels;
	व्योम __iomem *base_addr = शून्य;
	व्योम __iomem *conf_addr = शून्य;
	व्योम __iomem *res_addr = शून्य;
	पूर्णांक i;

	dev_info(&pdev->dev, "initializing device %04x:%04x\n",
		 pdev->venकरोr, pdev->device);

	err = pci_enable_device(pdev);
	अगर (err)
		जाओ failure;

	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err)
		जाओ failure_release_pci;

	/* S5920 */
	conf_addr = pci_iomap(pdev, 0, PCI_CONFIG_PORT_SIZE);
	अगर (conf_addr == शून्य) अणु
		err = -ENODEV;
		जाओ failure_release_regions;
	पूर्ण

	/* XILINX board wide address */
	res_addr = pci_iomap(pdev, 2, PCI_PORT_XILINX_SIZE);
	अगर (res_addr == शून्य) अणु
		err = -ENOMEM;
		जाओ failure_iounmap;
	पूर्ण

	base_addr = pci_iomap(pdev, 1, PCI_PORT_SIZE);
	अगर (base_addr == शून्य) अणु
		err = -ENOMEM;
		जाओ failure_iounmap;
	पूर्ण

	no_channels = number_of_sja1000_chip(base_addr);
	अगर (no_channels == 0) अणु
		err = -ENOMEM;
		जाओ failure_iounmap;
	पूर्ण

	क्रम (i = 0; i < no_channels; i++) अणु
		err = kvaser_pci_add_chan(pdev, i, &master_dev,
					  conf_addr, res_addr,
					  base_addr);
		अगर (err)
			जाओ failure_cleanup;
	पूर्ण

	priv = netdev_priv(master_dev);
	board = priv->priv;

	dev_info(&pdev->dev, "xilinx version=%d number of channels=%d\n",
		 board->xilinx_ver, board->no_channels);

	pci_set_drvdata(pdev, master_dev);
	वापस 0;

failure_cleanup:
	kvaser_pci_del_chan(master_dev);

failure_iounmap:
	अगर (conf_addr != शून्य)
		pci_iounmap(pdev, conf_addr);
	अगर (res_addr != शून्य)
		pci_iounmap(pdev, res_addr);
	अगर (base_addr != शून्य)
		pci_iounmap(pdev, base_addr);

failure_release_regions:
	pci_release_regions(pdev);

failure_release_pci:
	pci_disable_device(pdev);

failure:
	वापस err;

पूर्ण

अटल व्योम kvaser_pci_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);

	kvaser_pci_del_chan(dev);

	pci_release_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल काष्ठा pci_driver kvaser_pci_driver = अणु
	.name = DRV_NAME,
	.id_table = kvaser_pci_tbl,
	.probe = kvaser_pci_init_one,
	.हटाओ = kvaser_pci_हटाओ_one,
पूर्ण;

module_pci_driver(kvaser_pci_driver);
