<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2011 Marvell International Ltd. All rights reserved.
 * Copyright (C) 2018 Lubomir Rपूर्णांकel <lkundrak@v3.sk>
 */

#समावेश <dt-bindings/phy/phy.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>

/* phy regs */
#घोषणा UTMI_REVISION		0x0
#घोषणा UTMI_CTRL		0x4
#घोषणा UTMI_PLL		0x8
#घोषणा UTMI_TX			0xc
#घोषणा UTMI_RX			0x10
#घोषणा UTMI_IVREF		0x14
#घोषणा UTMI_T0			0x18
#घोषणा UTMI_T1			0x1c
#घोषणा UTMI_T2			0x20
#घोषणा UTMI_T3			0x24
#घोषणा UTMI_T4			0x28
#घोषणा UTMI_T5			0x2c
#घोषणा UTMI_RESERVE		0x30
#घोषणा UTMI_USB_INT		0x34
#घोषणा UTMI_DBG_CTL		0x38
#घोषणा UTMI_OTG_ADDON		0x3c

/* For UTMICTRL Register */
#घोषणा UTMI_CTRL_USB_CLK_EN                    (1 << 31)
/* pxa168 */
#घोषणा UTMI_CTRL_SUSPEND_SET1                  (1 << 30)
#घोषणा UTMI_CTRL_SUSPEND_SET2                  (1 << 29)
#घोषणा UTMI_CTRL_RXBUF_PDWN                    (1 << 24)
#घोषणा UTMI_CTRL_TXBUF_PDWN                    (1 << 11)

#घोषणा UTMI_CTRL_INPKT_DELAY_SHIFT             30
#घोषणा UTMI_CTRL_INPKT_DELAY_SOF_SHIFT		28
#घोषणा UTMI_CTRL_PU_REF_SHIFT			20
#घोषणा UTMI_CTRL_ARC_PULLDN_SHIFT              12
#घोषणा UTMI_CTRL_PLL_PWR_UP_SHIFT              1
#घोषणा UTMI_CTRL_PWR_UP_SHIFT                  0

/* For UTMI_PLL Register */
#घोषणा UTMI_PLL_PLLCALI12_SHIFT		29
#घोषणा UTMI_PLL_PLLCALI12_MASK			(0x3 << 29)

#घोषणा UTMI_PLL_PLLVDD18_SHIFT			27
#घोषणा UTMI_PLL_PLLVDD18_MASK			(0x3 << 27)

#घोषणा UTMI_PLL_PLLVDD12_SHIFT			25
#घोषणा UTMI_PLL_PLLVDD12_MASK			(0x3 << 25)

#घोषणा UTMI_PLL_CLK_BLK_EN_SHIFT               24
#घोषणा CLK_BLK_EN                              (0x1 << 24)
#घोषणा PLL_READY                               (0x1 << 23)
#घोषणा KVCO_EXT                                (0x1 << 22)
#घोषणा VCOCAL_START                            (0x1 << 21)

#घोषणा UTMI_PLL_KVCO_SHIFT			15
#घोषणा UTMI_PLL_KVCO_MASK                      (0x7 << 15)

#घोषणा UTMI_PLL_ICP_SHIFT			12
#घोषणा UTMI_PLL_ICP_MASK                       (0x7 << 12)

#घोषणा UTMI_PLL_FBDIV_SHIFT                    4
#घोषणा UTMI_PLL_FBDIV_MASK                     (0xFF << 4)

#घोषणा UTMI_PLL_REFDIV_SHIFT                   0
#घोषणा UTMI_PLL_REFDIV_MASK                    (0xF << 0)

/* For UTMI_TX Register */
#घोषणा UTMI_TX_REG_EXT_FS_RCAL_SHIFT		27
#घोषणा UTMI_TX_REG_EXT_FS_RCAL_MASK		(0xf << 27)

#घोषणा UTMI_TX_REG_EXT_FS_RCAL_EN_SHIFT	26
#घोषणा UTMI_TX_REG_EXT_FS_RCAL_EN_MASK		(0x1 << 26)

#घोषणा UTMI_TX_TXVDD12_SHIFT                   22
#घोषणा UTMI_TX_TXVDD12_MASK                    (0x3 << 22)

#घोषणा UTMI_TX_CK60_PHSEL_SHIFT                17
#घोषणा UTMI_TX_CK60_PHSEL_MASK                 (0xf << 17)

#घोषणा UTMI_TX_IMPCAL_VTH_SHIFT                14
#घोषणा UTMI_TX_IMPCAL_VTH_MASK                 (0x7 << 14)

#घोषणा REG_RCAL_START                          (0x1 << 12)

#घोषणा UTMI_TX_LOW_VDD_EN_SHIFT                11

#घोषणा UTMI_TX_AMP_SHIFT			0
#घोषणा UTMI_TX_AMP_MASK			(0x7 << 0)

/* For UTMI_RX Register */
#घोषणा UTMI_REG_SQ_LENGTH_SHIFT                15
#घोषणा UTMI_REG_SQ_LENGTH_MASK                 (0x3 << 15)

#घोषणा UTMI_RX_SQ_THRESH_SHIFT                 4
#घोषणा UTMI_RX_SQ_THRESH_MASK                  (0xf << 4)

#घोषणा UTMI_OTG_ADDON_OTG_ON			(1 << 0)

क्रमागत pxa_usb_phy_version अणु
	PXA_USB_PHY_MMP2,
	PXA_USB_PHY_PXA910,
	PXA_USB_PHY_PXA168,
पूर्ण;

काष्ठा pxa_usb_phy अणु
	काष्ठा phy *phy;
	व्योम __iomem *base;
	क्रमागत pxa_usb_phy_version version;
पूर्ण;

/*****************************************************************************
 * The रेजिस्टरs पढ़ो/ग_लिखो routines
 *****************************************************************************/

अटल अचिन्हित पूर्णांक u2o_get(व्योम __iomem *base, अचिन्हित पूर्णांक offset)
अणु
	वापस पढ़ोl_relaxed(base + offset);
पूर्ण

अटल व्योम u2o_set(व्योम __iomem *base, अचिन्हित पूर्णांक offset,
		अचिन्हित पूर्णांक value)
अणु
	u32 reg;

	reg = पढ़ोl_relaxed(base + offset);
	reg |= value;
	ग_लिखोl_relaxed(reg, base + offset);
	पढ़ोl_relaxed(base + offset);
पूर्ण

अटल व्योम u2o_clear(व्योम __iomem *base, अचिन्हित पूर्णांक offset,
		अचिन्हित पूर्णांक value)
अणु
	u32 reg;

	reg = पढ़ोl_relaxed(base + offset);
	reg &= ~value;
	ग_लिखोl_relaxed(reg, base + offset);
	पढ़ोl_relaxed(base + offset);
पूर्ण

अटल व्योम u2o_ग_लिखो(व्योम __iomem *base, अचिन्हित पूर्णांक offset,
		अचिन्हित पूर्णांक value)
अणु
	ग_लिखोl_relaxed(value, base + offset);
	पढ़ोl_relaxed(base + offset);
पूर्ण

अटल पूर्णांक pxa_usb_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा pxa_usb_phy *pxa_usb_phy = phy_get_drvdata(phy);
	व्योम __iomem *base = pxa_usb_phy->base;
	पूर्णांक loops;

	dev_info(&phy->dev, "initializing Marvell PXA USB PHY");

	/* Initialize the USB PHY घातer */
	अगर (pxa_usb_phy->version == PXA_USB_PHY_PXA910) अणु
		u2o_set(base, UTMI_CTRL, (1<<UTMI_CTRL_INPKT_DELAY_SOF_SHIFT)
			| (1<<UTMI_CTRL_PU_REF_SHIFT));
	पूर्ण

	u2o_set(base, UTMI_CTRL, 1<<UTMI_CTRL_PLL_PWR_UP_SHIFT);
	u2o_set(base, UTMI_CTRL, 1<<UTMI_CTRL_PWR_UP_SHIFT);

	/* UTMI_PLL settings */
	u2o_clear(base, UTMI_PLL, UTMI_PLL_PLLVDD18_MASK
		| UTMI_PLL_PLLVDD12_MASK | UTMI_PLL_PLLCALI12_MASK
		| UTMI_PLL_FBDIV_MASK | UTMI_PLL_REFDIV_MASK
		| UTMI_PLL_ICP_MASK | UTMI_PLL_KVCO_MASK);

	u2o_set(base, UTMI_PLL, 0xee<<UTMI_PLL_FBDIV_SHIFT
		| 0xb<<UTMI_PLL_REFDIV_SHIFT | 3<<UTMI_PLL_PLLVDD18_SHIFT
		| 3<<UTMI_PLL_PLLVDD12_SHIFT | 3<<UTMI_PLL_PLLCALI12_SHIFT
		| 1<<UTMI_PLL_ICP_SHIFT | 3<<UTMI_PLL_KVCO_SHIFT);

	/* UTMI_TX */
	u2o_clear(base, UTMI_TX, UTMI_TX_REG_EXT_FS_RCAL_EN_MASK
		| UTMI_TX_TXVDD12_MASK | UTMI_TX_CK60_PHSEL_MASK
		| UTMI_TX_IMPCAL_VTH_MASK | UTMI_TX_REG_EXT_FS_RCAL_MASK
		| UTMI_TX_AMP_MASK);
	u2o_set(base, UTMI_TX, 3<<UTMI_TX_TXVDD12_SHIFT
		| 4<<UTMI_TX_CK60_PHSEL_SHIFT | 4<<UTMI_TX_IMPCAL_VTH_SHIFT
		| 8<<UTMI_TX_REG_EXT_FS_RCAL_SHIFT | 3<<UTMI_TX_AMP_SHIFT);

	/* UTMI_RX */
	u2o_clear(base, UTMI_RX, UTMI_RX_SQ_THRESH_MASK
		| UTMI_REG_SQ_LENGTH_MASK);
	u2o_set(base, UTMI_RX, 7<<UTMI_RX_SQ_THRESH_SHIFT
		| 2<<UTMI_REG_SQ_LENGTH_SHIFT);

	/* UTMI_IVREF */
	अगर (pxa_usb_phy->version == PXA_USB_PHY_PXA168) अणु
		/*
		 * fixing Microsoft Altair board पूर्णांकerface with NEC hub issue -
		 * Set UTMI_IVREF from 0x4a3 to 0x4bf
		 */
		u2o_ग_लिखो(base, UTMI_IVREF, 0x4bf);
	पूर्ण

	/* toggle VCOCAL_START bit of UTMI_PLL */
	udelay(200);
	u2o_set(base, UTMI_PLL, VCOCAL_START);
	udelay(40);
	u2o_clear(base, UTMI_PLL, VCOCAL_START);

	/* toggle REG_RCAL_START bit of UTMI_TX */
	udelay(400);
	u2o_set(base, UTMI_TX, REG_RCAL_START);
	udelay(40);
	u2o_clear(base, UTMI_TX, REG_RCAL_START);
	udelay(400);

	/* Make sure PHY PLL is पढ़ोy */
	loops = 0;
	जबतक ((u2o_get(base, UTMI_PLL) & PLL_READY) == 0) अणु
		mdelay(1);
		loops++;
		अगर (loops > 100) अणु
			dev_warn(&phy->dev, "calibrate timeout, UTMI_PLL %x\n",
						u2o_get(base, UTMI_PLL));
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (pxa_usb_phy->version == PXA_USB_PHY_PXA168) अणु
		u2o_set(base, UTMI_RESERVE, 1 << 5);
		/* Turn on UTMI PHY OTG extension */
		u2o_ग_लिखो(base, UTMI_OTG_ADDON, 1);
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक pxa_usb_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा pxa_usb_phy *pxa_usb_phy = phy_get_drvdata(phy);
	व्योम __iomem *base = pxa_usb_phy->base;

	dev_info(&phy->dev, "deinitializing Marvell PXA USB PHY");

	अगर (pxa_usb_phy->version == PXA_USB_PHY_PXA168)
		u2o_clear(base, UTMI_OTG_ADDON, UTMI_OTG_ADDON_OTG_ON);

	u2o_clear(base, UTMI_CTRL, UTMI_CTRL_RXBUF_PDWN);
	u2o_clear(base, UTMI_CTRL, UTMI_CTRL_TXBUF_PDWN);
	u2o_clear(base, UTMI_CTRL, UTMI_CTRL_USB_CLK_EN);
	u2o_clear(base, UTMI_CTRL, 1<<UTMI_CTRL_PWR_UP_SHIFT);
	u2o_clear(base, UTMI_CTRL, 1<<UTMI_CTRL_PLL_PWR_UP_SHIFT);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops pxa_usb_phy_ops = अणु
	.init	= pxa_usb_phy_init,
	.निकास	= pxa_usb_phy_निकास,
	.owner	= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id pxa_usb_phy_of_match[] = अणु
	अणु
		.compatible = "marvell,mmp2-usb-phy",
		.data = (व्योम *)PXA_USB_PHY_MMP2,
	पूर्ण, अणु
		.compatible = "marvell,pxa910-usb-phy",
		.data = (व्योम *)PXA_USB_PHY_PXA910,
	पूर्ण, अणु
		.compatible = "marvell,pxa168-usb-phy",
		.data = (व्योम *)PXA_USB_PHY_PXA168,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pxa_usb_phy_of_match);

अटल पूर्णांक pxa_usb_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा pxa_usb_phy *pxa_usb_phy;
	काष्ठा phy_provider *provider;
	स्थिर काष्ठा of_device_id *of_id;

	pxa_usb_phy = devm_kzalloc(dev, माप(काष्ठा pxa_usb_phy), GFP_KERNEL);
	अगर (!pxa_usb_phy)
		वापस -ENOMEM;

	of_id = of_match_node(pxa_usb_phy_of_match, dev->of_node);
	अगर (of_id)
		pxa_usb_phy->version = (क्रमागत pxa_usb_phy_version)of_id->data;
	अन्यथा
		pxa_usb_phy->version = PXA_USB_PHY_MMP2;

	pxa_usb_phy->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pxa_usb_phy->base)) अणु
		dev_err(dev, "failed to remap PHY regs\n");
		वापस PTR_ERR(pxa_usb_phy->base);
	पूर्ण

	pxa_usb_phy->phy = devm_phy_create(dev, शून्य, &pxa_usb_phy_ops);
	अगर (IS_ERR(pxa_usb_phy->phy)) अणु
		dev_err(dev, "failed to create PHY\n");
		वापस PTR_ERR(pxa_usb_phy->phy);
	पूर्ण

	phy_set_drvdata(pxa_usb_phy->phy, pxa_usb_phy);
	provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	अगर (IS_ERR(provider)) अणु
		dev_err(dev, "failed to register PHY provider\n");
		वापस PTR_ERR(provider);
	पूर्ण

	अगर (!dev->of_node) अणु
		phy_create_lookup(pxa_usb_phy->phy, "usb", "mv-udc");
		phy_create_lookup(pxa_usb_phy->phy, "usb", "pxa-u2oehci");
		phy_create_lookup(pxa_usb_phy->phy, "usb", "mv-otg");
	पूर्ण

	dev_info(dev, "Marvell PXA USB PHY");
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pxa_usb_phy_driver = अणु
	.probe		= pxa_usb_phy_probe,
	.driver		= अणु
		.name	= "pxa-usb-phy",
		.of_match_table = pxa_usb_phy_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(pxa_usb_phy_driver);

MODULE_AUTHOR("Lubomir Rintel <lkundrak@v3.sk>");
MODULE_DESCRIPTION("Marvell PXA USB PHY Driver");
MODULE_LICENSE("GPL v2");
