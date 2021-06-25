<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Fपूर्णांकek F81601 PCIE to 2 CAN controller driver
 *
 * Copyright (C) 2019 Peter Hong <peter_hong@fपूर्णांकek.com.tw>
 * Copyright (C) 2019 Linux Foundation
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

#घोषणा F81601_PCI_MAX_CHAN		2

#घोषणा F81601_DECODE_REG		0x209
#घोषणा F81601_IO_MODE			BIT(7)
#घोषणा F81601_MEM_MODE			BIT(6)
#घोषणा F81601_CFG_MODE			BIT(5)
#घोषणा F81601_CAN2_INTERNAL_CLK	BIT(3)
#घोषणा F81601_CAN1_INTERNAL_CLK	BIT(2)
#घोषणा F81601_CAN2_EN			BIT(1)
#घोषणा F81601_CAN1_EN			BIT(0)

#घोषणा F81601_TRAP_REG			0x20a
#घोषणा F81601_CAN2_HAS_EN		BIT(4)

काष्ठा f81601_pci_card अणु
	व्योम __iomem *addr;
	spinlock_t lock;	/* use this spin lock only क्रम ग_लिखो access */
	काष्ठा pci_dev *dev;
	काष्ठा net_device *net_dev[F81601_PCI_MAX_CHAN];
पूर्ण;

अटल स्थिर काष्ठा pci_device_id f81601_pci_tbl[] = अणु
	अणु PCI_DEVICE(0x1c29, 0x1703) पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, f81601_pci_tbl);

अटल bool पूर्णांकernal_clk = true;
module_param(पूर्णांकernal_clk, bool, 0444);
MODULE_PARM_DESC(पूर्णांकernal_clk, "Use internal clock, default true (24MHz)");

अटल अचिन्हित पूर्णांक बाह्यal_clk;
module_param(बाह्यal_clk, uपूर्णांक, 0444);
MODULE_PARM_DESC(बाह्यal_clk, "External clock when internal_clk disabled");

अटल u8 f81601_pci_पढ़ो_reg(स्थिर काष्ठा sja1000_priv *priv, पूर्णांक port)
अणु
	वापस पढ़ोb(priv->reg_base + port);
पूर्ण

अटल व्योम f81601_pci_ग_लिखो_reg(स्थिर काष्ठा sja1000_priv *priv, पूर्णांक port,
				 u8 val)
अणु
	काष्ठा f81601_pci_card *card = priv->priv;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&card->lock, flags);
	ग_लिखोb(val, priv->reg_base + port);
	पढ़ोb(priv->reg_base);
	spin_unlock_irqrestore(&card->lock, flags);
पूर्ण

अटल व्योम f81601_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा f81601_pci_card *card = pci_get_drvdata(pdev);
	काष्ठा net_device *dev;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(card->net_dev); i++) अणु
		dev = card->net_dev[i];
		अगर (!dev)
			जारी;

		dev_info(&pdev->dev, "%s: Removing %s\n", __func__, dev->name);

		unरेजिस्टर_sja1000dev(dev);
		मुक्त_sja1000dev(dev);
	पूर्ण
पूर्ण

/* Probe F81601 based device क्रम the SJA1000 chips and रेजिस्टर each
 * available CAN channel to SJA1000 Socket-CAN subप्रणाली.
 */
अटल पूर्णांक f81601_pci_probe(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा sja1000_priv *priv;
	काष्ठा net_device *dev;
	काष्ठा f81601_pci_card *card;
	पूर्णांक err, i, count;
	u8 पंचांगp;

	अगर (pcim_enable_device(pdev) < 0) अणु
		dev_err(&pdev->dev, "Failed to enable PCI device\n");
		वापस -ENODEV;
	पूर्ण

	dev_info(&pdev->dev, "Detected card at slot #%i\n",
		 PCI_SLOT(pdev->devfn));

	card = devm_kzalloc(&pdev->dev, माप(*card), GFP_KERNEL);
	अगर (!card)
		वापस -ENOMEM;

	card->dev = pdev;
	spin_lock_init(&card->lock);

	pci_set_drvdata(pdev, card);

	पंचांगp = F81601_IO_MODE | F81601_MEM_MODE | F81601_CFG_MODE |
		F81601_CAN2_EN | F81601_CAN1_EN;

	अगर (पूर्णांकernal_clk) अणु
		पंचांगp |= F81601_CAN2_INTERNAL_CLK | F81601_CAN1_INTERNAL_CLK;

		dev_info(&pdev->dev,
			 "F81601 running with internal clock: 24Mhz\n");
	पूर्ण अन्यथा अणु
		dev_info(&pdev->dev,
			 "F81601 running with external clock: %dMhz\n",
			 बाह्यal_clk / 1000000);
	पूर्ण

	pci_ग_लिखो_config_byte(pdev, F81601_DECODE_REG, पंचांगp);

	card->addr = pcim_iomap(pdev, 0, pci_resource_len(pdev, 0));

	अगर (!card->addr) अणु
		err = -ENOMEM;
		dev_err(&pdev->dev, "%s: Failed to remap BAR\n", __func__);
		जाओ failure_cleanup;
	पूर्ण

	/* पढ़ो CAN2_HW_EN strap pin to detect how many CANBUS करो we have */
	count = ARRAY_SIZE(card->net_dev);
	pci_पढ़ो_config_byte(pdev, F81601_TRAP_REG, &पंचांगp);
	अगर (!(पंचांगp & F81601_CAN2_HAS_EN))
		count = 1;

	क्रम (i = 0; i < count; i++) अणु
		dev = alloc_sja1000dev(0);
		अगर (!dev) अणु
			err = -ENOMEM;
			जाओ failure_cleanup;
		पूर्ण

		priv = netdev_priv(dev);
		priv->priv = card;
		priv->irq_flags = IRQF_SHARED;
		priv->reg_base = card->addr + 0x80 * i;
		priv->पढ़ो_reg = f81601_pci_पढ़ो_reg;
		priv->ग_लिखो_reg = f81601_pci_ग_लिखो_reg;

		अगर (पूर्णांकernal_clk)
			priv->can.घड़ी.freq = 24000000 / 2;
		अन्यथा
			priv->can.घड़ी.freq = बाह्यal_clk / 2;

		priv->ocr = OCR_TX0_PUSHPULL | OCR_TX1_PUSHPULL;
		priv->cdr = CDR_CBP;

		SET_NETDEV_DEV(dev, &pdev->dev);
		dev->dev_id = i;
		dev->irq = pdev->irq;

		/* Register SJA1000 device */
		err = रेजिस्टर_sja1000dev(dev);
		अगर (err) अणु
			dev_err(&pdev->dev,
				"%s: Registering device failed: %x\n", __func__,
				err);
			मुक्त_sja1000dev(dev);
			जाओ failure_cleanup;
		पूर्ण

		card->net_dev[i] = dev;
		dev_info(&pdev->dev, "Channel #%d, %s at 0x%p, irq %d\n", i,
			 dev->name, priv->reg_base, dev->irq);
	पूर्ण

	वापस 0;

 failure_cleanup:
	dev_err(&pdev->dev, "%s: failed: %d. Cleaning Up.\n", __func__, err);
	f81601_pci_हटाओ(pdev);

	वापस err;
पूर्ण

अटल काष्ठा pci_driver f81601_pci_driver = अणु
	.name =	"f81601",
	.id_table = f81601_pci_tbl,
	.probe = f81601_pci_probe,
	.हटाओ = f81601_pci_हटाओ,
पूर्ण;

MODULE_DESCRIPTION("Fintek F81601 PCIE to 2 CANBUS adaptor driver");
MODULE_AUTHOR("Peter Hong <peter_hong@fintek.com.tw>");
MODULE_LICENSE("GPL v2");

module_pci_driver(f81601_pci_driver);
