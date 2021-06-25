<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018, Nuvoton Corporation.
 * Copyright (c) 2018, Intel Corporation.
 */

#घोषणा pr_fmt(fmt) "nuvoton-kcs-bmc: " fmt

#समावेश <linux/atomic.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश "kcs_bmc.h"

#घोषणा DEVICE_NAME	"npcm-kcs-bmc"
#घोषणा KCS_CHANNEL_MAX	3

#घोषणा KCS1ST		0x0C
#घोषणा KCS2ST		0x1E
#घोषणा KCS3ST		0x30

#घोषणा KCS1DO		0x0E
#घोषणा KCS2DO		0x20
#घोषणा KCS3DO		0x32

#घोषणा KCS1DI		0x10
#घोषणा KCS2DI		0x22
#घोषणा KCS3DI		0x34

#घोषणा KCS1CTL		0x18
#घोषणा KCS2CTL		0x2A
#घोषणा KCS3CTL		0x3C
#घोषणा    KCS_CTL_IBFIE	BIT(0)

#घोषणा KCS1IE		0x1C
#घोषणा KCS2IE		0x2E
#घोषणा KCS3IE		0x40
#घोषणा    KCS_IE_IRQE          BIT(0)
#घोषणा    KCS_IE_HIRQE         BIT(3)

/*
 * 7.2.4 Core KCS Registers
 * Registers in this module are 8 bits. An 8-bit रेजिस्टर must be accessed
 * by an 8-bit पढ़ो or ग_लिखो.
 *
 * sts: KCS Channel n Status Register (KCSnST).
 * करोb: KCS Channel n Data Out Buffer Register (KCSnDO).
 * dib: KCS Channel n Data In Buffer Register (KCSnDI).
 * ctl: KCS Channel n Control Register (KCSnCTL).
 * ie : KCS Channel n  Interrupt Enable Register (KCSnIE).
 */
काष्ठा npcm7xx_kcs_reg अणु
	u32 sts;
	u32 करोb;
	u32 dib;
	u32 ctl;
	u32 ie;
पूर्ण;

काष्ठा npcm7xx_kcs_bmc अणु
	काष्ठा regmap *map;

	स्थिर काष्ठा npcm7xx_kcs_reg *reg;
पूर्ण;

अटल स्थिर काष्ठा npcm7xx_kcs_reg npcm7xx_kcs_reg_tbl[KCS_CHANNEL_MAX] = अणु
	अणु .sts = KCS1ST, .करोb = KCS1DO, .dib = KCS1DI, .ctl = KCS1CTL, .ie = KCS1IE पूर्ण,
	अणु .sts = KCS2ST, .करोb = KCS2DO, .dib = KCS2DI, .ctl = KCS2CTL, .ie = KCS2IE पूर्ण,
	अणु .sts = KCS3ST, .करोb = KCS3DO, .dib = KCS3DI, .ctl = KCS3CTL, .ie = KCS3IE पूर्ण,
पूर्ण;

अटल u8 npcm7xx_kcs_inb(काष्ठा kcs_bmc *kcs_bmc, u32 reg)
अणु
	काष्ठा npcm7xx_kcs_bmc *priv = kcs_bmc_priv(kcs_bmc);
	u32 val = 0;
	पूर्णांक rc;

	rc = regmap_पढ़ो(priv->map, reg, &val);
	WARN(rc != 0, "regmap_read() failed: %d\n", rc);

	वापस rc == 0 ? (u8)val : 0;
पूर्ण

अटल व्योम npcm7xx_kcs_outb(काष्ठा kcs_bmc *kcs_bmc, u32 reg, u8 data)
अणु
	काष्ठा npcm7xx_kcs_bmc *priv = kcs_bmc_priv(kcs_bmc);
	पूर्णांक rc;

	rc = regmap_ग_लिखो(priv->map, reg, data);
	WARN(rc != 0, "regmap_write() failed: %d\n", rc);
पूर्ण

अटल व्योम npcm7xx_kcs_enable_channel(काष्ठा kcs_bmc *kcs_bmc, bool enable)
अणु
	काष्ठा npcm7xx_kcs_bmc *priv = kcs_bmc_priv(kcs_bmc);

	regmap_update_bits(priv->map, priv->reg->ctl, KCS_CTL_IBFIE,
			   enable ? KCS_CTL_IBFIE : 0);

	regmap_update_bits(priv->map, priv->reg->ie, KCS_IE_IRQE | KCS_IE_HIRQE,
			   enable ? KCS_IE_IRQE | KCS_IE_HIRQE : 0);
पूर्ण

अटल irqवापस_t npcm7xx_kcs_irq(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा kcs_bmc *kcs_bmc = arg;

	अगर (!kcs_bmc_handle_event(kcs_bmc))
		वापस IRQ_HANDLED;

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक npcm7xx_kcs_config_irq(काष्ठा kcs_bmc *kcs_bmc,
				  काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक irq;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	वापस devm_request_irq(dev, irq, npcm7xx_kcs_irq, IRQF_SHARED,
				dev_name(dev), kcs_bmc);
पूर्ण

अटल पूर्णांक npcm7xx_kcs_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा npcm7xx_kcs_bmc *priv;
	काष्ठा kcs_bmc *kcs_bmc;
	u32 chan;
	पूर्णांक rc;

	rc = of_property_पढ़ो_u32(dev->of_node, "kcs_chan", &chan);
	अगर (rc != 0 || chan == 0 || chan > KCS_CHANNEL_MAX) अणु
		dev_err(dev, "no valid 'kcs_chan' configured\n");
		वापस -ENODEV;
	पूर्ण

	kcs_bmc = kcs_bmc_alloc(dev, माप(*priv), chan);
	अगर (!kcs_bmc)
		वापस -ENOMEM;

	priv = kcs_bmc_priv(kcs_bmc);
	priv->map = syscon_node_to_regmap(dev->parent->of_node);
	अगर (IS_ERR(priv->map)) अणु
		dev_err(dev, "Couldn't get regmap\n");
		वापस -ENODEV;
	पूर्ण
	priv->reg = &npcm7xx_kcs_reg_tbl[chan - 1];

	kcs_bmc->ioreg.idr = priv->reg->dib;
	kcs_bmc->ioreg.odr = priv->reg->करोb;
	kcs_bmc->ioreg.str = priv->reg->sts;
	kcs_bmc->io_inputb = npcm7xx_kcs_inb;
	kcs_bmc->io_outputb = npcm7xx_kcs_outb;

	dev_set_drvdata(dev, kcs_bmc);

	npcm7xx_kcs_enable_channel(kcs_bmc, true);
	rc = npcm7xx_kcs_config_irq(kcs_bmc, pdev);
	अगर (rc)
		वापस rc;

	rc = misc_रेजिस्टर(&kcs_bmc->miscdev);
	अगर (rc) अणु
		dev_err(dev, "Unable to register device\n");
		वापस rc;
	पूर्ण

	pr_info("channel=%u idr=0x%x odr=0x%x str=0x%x\n",
		chan,
		kcs_bmc->ioreg.idr, kcs_bmc->ioreg.odr, kcs_bmc->ioreg.str);

	वापस 0;
पूर्ण

अटल पूर्णांक npcm7xx_kcs_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा kcs_bmc *kcs_bmc = dev_get_drvdata(&pdev->dev);

	misc_deरेजिस्टर(&kcs_bmc->miscdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id npcm_kcs_bmc_match[] = अणु
	अणु .compatible = "nuvoton,npcm750-kcs-bmc" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, npcm_kcs_bmc_match);

अटल काष्ठा platक्रमm_driver npcm_kcs_bmc_driver = अणु
	.driver = अणु
		.name		= DEVICE_NAME,
		.of_match_table	= npcm_kcs_bmc_match,
	पूर्ण,
	.probe	= npcm7xx_kcs_probe,
	.हटाओ	= npcm7xx_kcs_हटाओ,
पूर्ण;
module_platक्रमm_driver(npcm_kcs_bmc_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Avi Fishman <avifishman70@gmail.com>");
MODULE_AUTHOR("Haiyue Wang <haiyue.wang@linux.intel.com>");
MODULE_DESCRIPTION("NPCM7xx device interface to the KCS BMC device");
