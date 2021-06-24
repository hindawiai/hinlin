<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2014 Marvell Technology Group Ltd.
 *
 * Antoine Tenart <antoine.tenart@मुक्त-electrons.com>
 * Jisheng Zhang <jszhang@marvell.com>
 */

#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>

#घोषणा USB_PHY_PLL		0x04
#घोषणा USB_PHY_PLL_CONTROL	0x08
#घोषणा USB_PHY_TX_CTRL0	0x10
#घोषणा USB_PHY_TX_CTRL1	0x14
#घोषणा USB_PHY_TX_CTRL2	0x18
#घोषणा USB_PHY_RX_CTRL		0x20
#घोषणा USB_PHY_ANALOG		0x34

/* USB_PHY_PLL */
#घोषणा CLK_REF_DIV(x)		((x) << 4)
#घोषणा FEEDBACK_CLK_DIV(x)	((x) << 8)

/* USB_PHY_PLL_CONTROL */
#घोषणा CLK_STABLE		BIT(0)
#घोषणा PLL_CTRL_PIN		BIT(1)
#घोषणा PLL_CTRL_REG		BIT(2)
#घोषणा PLL_ON			BIT(3)
#घोषणा PHASE_OFF_TOL_125	(0x0 << 5)
#घोषणा PHASE_OFF_TOL_250	BIT(5)
#घोषणा KVC0_CALIB		(0x0 << 9)
#घोषणा KVC0_REG_CTRL		BIT(9)
#घोषणा KVC0_HIGH		(0x0 << 10)
#घोषणा KVC0_LOW		(0x3 << 10)
#घोषणा CLK_BLK_EN		BIT(13)

/* USB_PHY_TX_CTRL0 */
#घोषणा EXT_HS_RCAL_EN		BIT(3)
#घोषणा EXT_FS_RCAL_EN		BIT(4)
#घोषणा IMPCAL_VTH_DIV(x)	((x) << 5)
#घोषणा EXT_RS_RCAL_DIV(x)	((x) << 8)
#घोषणा EXT_FS_RCAL_DIV(x)	((x) << 12)

/* USB_PHY_TX_CTRL1 */
#घोषणा TX_VDD15_14		(0x0 << 4)
#घोषणा TX_VDD15_15		BIT(4)
#घोषणा TX_VDD15_16		(0x2 << 4)
#घोषणा TX_VDD15_17		(0x3 << 4)
#घोषणा TX_VDD12_VDD		(0x0 << 6)
#घोषणा TX_VDD12_11		BIT(6)
#घोषणा TX_VDD12_12		(0x2 << 6)
#घोषणा TX_VDD12_13		(0x3 << 6)
#घोषणा LOW_VDD_EN		BIT(8)
#घोषणा TX_OUT_AMP(x)		((x) << 9)

/* USB_PHY_TX_CTRL2 */
#घोषणा TX_CHAN_CTRL_REG(x)	((x) << 0)
#घोषणा DRV_SLEWRATE(x)		((x) << 4)
#घोषणा IMP_CAL_FS_HS_DLY_0	(0x0 << 6)
#घोषणा IMP_CAL_FS_HS_DLY_1	BIT(6)
#घोषणा IMP_CAL_FS_HS_DLY_2	(0x2 << 6)
#घोषणा IMP_CAL_FS_HS_DLY_3	(0x3 << 6)
#घोषणा FS_DRV_EN_MASK(x)	((x) << 8)
#घोषणा HS_DRV_EN_MASK(x)	((x) << 12)

/* USB_PHY_RX_CTRL */
#घोषणा PHASE_FREEZE_DLY_2_CL	(0x0 << 0)
#घोषणा PHASE_FREEZE_DLY_4_CL	BIT(0)
#घोषणा ACK_LENGTH_8_CL		(0x0 << 2)
#घोषणा ACK_LENGTH_12_CL	BIT(2)
#घोषणा ACK_LENGTH_16_CL	(0x2 << 2)
#घोषणा ACK_LENGTH_20_CL	(0x3 << 2)
#घोषणा SQ_LENGTH_3		(0x0 << 4)
#घोषणा SQ_LENGTH_6		BIT(4)
#घोषणा SQ_LENGTH_9		(0x2 << 4)
#घोषणा SQ_LENGTH_12		(0x3 << 4)
#घोषणा DISCON_THRESHOLD_260	(0x0 << 6)
#घोषणा DISCON_THRESHOLD_270	BIT(6)
#घोषणा DISCON_THRESHOLD_280	(0x2 << 6)
#घोषणा DISCON_THRESHOLD_290	(0x3 << 6)
#घोषणा SQ_THRESHOLD(x)		((x) << 8)
#घोषणा LPF_COEF(x)		((x) << 12)
#घोषणा INTPL_CUR_10		(0x0 << 14)
#घोषणा INTPL_CUR_20		BIT(14)
#घोषणा INTPL_CUR_30		(0x2 << 14)
#घोषणा INTPL_CUR_40		(0x3 << 14)

/* USB_PHY_ANALOG */
#घोषणा ANA_PWR_UP		BIT(1)
#घोषणा ANA_PWR_DOWN		BIT(2)
#घोषणा V2I_VCO_RATIO(x)	((x) << 7)
#घोषणा R_ROTATE_90		(0x0 << 10)
#घोषणा R_ROTATE_0		BIT(10)
#घोषणा MODE_TEST_EN		BIT(11)
#घोषणा ANA_TEST_DC_CTRL(x)	((x) << 12)

अटल स्थिर u32 phy_berlin_pll_भागiders[] = अणु
	/* Berlin 2 */
	CLK_REF_DIV(0x6) | FEEDBACK_CLK_DIV(0x55),
	/* Berlin 2CD/Q */
	CLK_REF_DIV(0xc) | FEEDBACK_CLK_DIV(0x54),
पूर्ण;

काष्ठा phy_berlin_usb_priv अणु
	व्योम __iomem		*base;
	काष्ठा reset_control	*rst_ctrl;
	u32			pll_भागider;
पूर्ण;

अटल पूर्णांक phy_berlin_usb_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा phy_berlin_usb_priv *priv = phy_get_drvdata(phy);

	reset_control_reset(priv->rst_ctrl);

	ग_लिखोl(priv->pll_भागider,
	       priv->base + USB_PHY_PLL);
	ग_लिखोl(CLK_STABLE | PLL_CTRL_REG | PHASE_OFF_TOL_250 | KVC0_REG_CTRL |
	       CLK_BLK_EN, priv->base + USB_PHY_PLL_CONTROL);
	ग_लिखोl(V2I_VCO_RATIO(0x5) | R_ROTATE_0 | ANA_TEST_DC_CTRL(0x5),
	       priv->base + USB_PHY_ANALOG);
	ग_लिखोl(PHASE_FREEZE_DLY_4_CL | ACK_LENGTH_16_CL | SQ_LENGTH_12 |
	       DISCON_THRESHOLD_270 | SQ_THRESHOLD(0xa) | LPF_COEF(0x2) |
	       INTPL_CUR_30, priv->base + USB_PHY_RX_CTRL);

	ग_लिखोl(TX_VDD12_13 | TX_OUT_AMP(0x3), priv->base + USB_PHY_TX_CTRL1);
	ग_लिखोl(EXT_HS_RCAL_EN | IMPCAL_VTH_DIV(0x3) | EXT_RS_RCAL_DIV(0x4),
	       priv->base + USB_PHY_TX_CTRL0);

	ग_लिखोl(EXT_HS_RCAL_EN | IMPCAL_VTH_DIV(0x3) | EXT_RS_RCAL_DIV(0x4) |
	       EXT_FS_RCAL_DIV(0x2), priv->base + USB_PHY_TX_CTRL0);

	ग_लिखोl(EXT_HS_RCAL_EN | IMPCAL_VTH_DIV(0x3) | EXT_RS_RCAL_DIV(0x4),
	       priv->base + USB_PHY_TX_CTRL0);
	ग_लिखोl(TX_CHAN_CTRL_REG(0xf) | DRV_SLEWRATE(0x3) | IMP_CAL_FS_HS_DLY_3 |
	       FS_DRV_EN_MASK(0xd), priv->base + USB_PHY_TX_CTRL2);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops phy_berlin_usb_ops = अणु
	.घातer_on	= phy_berlin_usb_घातer_on,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id phy_berlin_usb_of_match[] = अणु
	अणु
		.compatible = "marvell,berlin2-usb-phy",
		.data = &phy_berlin_pll_भागiders[0],
	पूर्ण,
	अणु
		.compatible = "marvell,berlin2cd-usb-phy",
		.data = &phy_berlin_pll_भागiders[1],
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, phy_berlin_usb_of_match);

अटल पूर्णांक phy_berlin_usb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match =
		of_match_device(phy_berlin_usb_of_match, &pdev->dev);
	काष्ठा phy_berlin_usb_priv *priv;
	काष्ठा phy *phy;
	काष्ठा phy_provider *phy_provider;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	priv->rst_ctrl = devm_reset_control_get(&pdev->dev, शून्य);
	अगर (IS_ERR(priv->rst_ctrl))
		वापस PTR_ERR(priv->rst_ctrl);

	priv->pll_भागider = *((u32 *)match->data);

	phy = devm_phy_create(&pdev->dev, शून्य, &phy_berlin_usb_ops);
	अगर (IS_ERR(phy)) अणु
		dev_err(&pdev->dev, "failed to create PHY\n");
		वापस PTR_ERR(phy);
	पूर्ण

	phy_set_drvdata(phy, priv);

	phy_provider =
		devm_of_phy_provider_रेजिस्टर(&pdev->dev, of_phy_simple_xlate);
	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल काष्ठा platक्रमm_driver phy_berlin_usb_driver = अणु
	.probe	= phy_berlin_usb_probe,
	.driver	= अणु
		.name		= "phy-berlin-usb",
		.of_match_table	= phy_berlin_usb_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(phy_berlin_usb_driver);

MODULE_AUTHOR("Antoine Tenart <antoine.tenart@free-electrons.com>");
MODULE_DESCRIPTION("Marvell Berlin PHY driver for USB");
MODULE_LICENSE("GPL");
