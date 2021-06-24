<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Linaro, Ltd.
 * Rob Herring <robh@kernel.org>
 *
 * Based on venकरोr driver:
 * Copyright (C) 2013 Marvell Inc.
 * Author: Chao Xie <xiechao.mail@gmail.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/phy/phy.h>

/* USB PXA1928 PHY mapping */
#घोषणा PHY_28NM_PLL_REG0			0x0
#घोषणा PHY_28NM_PLL_REG1			0x4
#घोषणा PHY_28NM_CAL_REG			0x8
#घोषणा PHY_28NM_TX_REG0			0x0c
#घोषणा PHY_28NM_TX_REG1			0x10
#घोषणा PHY_28NM_RX_REG0			0x14
#घोषणा PHY_28NM_RX_REG1			0x18
#घोषणा PHY_28NM_DIG_REG0			0x1c
#घोषणा PHY_28NM_DIG_REG1			0x20
#घोषणा PHY_28NM_TEST_REG0			0x24
#घोषणा PHY_28NM_TEST_REG1			0x28
#घोषणा PHY_28NM_MOC_REG			0x2c
#घोषणा PHY_28NM_PHY_RESERVE			0x30
#घोषणा PHY_28NM_OTG_REG			0x34
#घोषणा PHY_28NM_CHRG_DET			0x38
#घोषणा PHY_28NM_CTRL_REG0			0xc4
#घोषणा PHY_28NM_CTRL_REG1			0xc8
#घोषणा PHY_28NM_CTRL_REG2			0xd4
#घोषणा PHY_28NM_CTRL_REG3			0xdc

/* PHY_28NM_PLL_REG0 */
#घोषणा PHY_28NM_PLL_READY			BIT(31)

#घोषणा PHY_28NM_PLL_SELLPFR_SHIFT		28
#घोषणा PHY_28NM_PLL_SELLPFR_MASK		(0x3 << 28)

#घोषणा PHY_28NM_PLL_FBDIV_SHIFT		16
#घोषणा PHY_28NM_PLL_FBDIV_MASK			(0x1ff << 16)

#घोषणा PHY_28NM_PLL_ICP_SHIFT			8
#घोषणा PHY_28NM_PLL_ICP_MASK			(0x7 << 8)

#घोषणा PHY_28NM_PLL_REFDIV_SHIFT		0
#घोषणा PHY_28NM_PLL_REFDIV_MASK		0x7f

/* PHY_28NM_PLL_REG1 */
#घोषणा PHY_28NM_PLL_PU_BY_REG			BIT(1)

#घोषणा PHY_28NM_PLL_PU_PLL			BIT(0)

/* PHY_28NM_CAL_REG */
#घोषणा PHY_28NM_PLL_PLLCAL_DONE		BIT(31)

#घोषणा PHY_28NM_PLL_IMPCAL_DONE		BIT(23)

#घोषणा PHY_28NM_PLL_KVCO_SHIFT			16
#घोषणा PHY_28NM_PLL_KVCO_MASK			(0x7 << 16)

#घोषणा PHY_28NM_PLL_CAL12_SHIFT		20
#घोषणा PHY_28NM_PLL_CAL12_MASK			(0x3 << 20)

#घोषणा PHY_28NM_IMPCAL_VTH_SHIFT		8
#घोषणा PHY_28NM_IMPCAL_VTH_MASK		(0x7 << 8)

#घोषणा PHY_28NM_PLLCAL_START_SHIFT		22
#घोषणा PHY_28NM_IMPCAL_START_SHIFT		13

/* PHY_28NM_TX_REG0 */
#घोषणा PHY_28NM_TX_PU_BY_REG			BIT(25)

#घोषणा PHY_28NM_TX_PU_ANA			BIT(24)

#घोषणा PHY_28NM_TX_AMP_SHIFT			20
#घोषणा PHY_28NM_TX_AMP_MASK			(0x7 << 20)

/* PHY_28NM_RX_REG0 */
#घोषणा PHY_28NM_RX_SQ_THRESH_SHIFT		0
#घोषणा PHY_28NM_RX_SQ_THRESH_MASK		(0xf << 0)

/* PHY_28NM_RX_REG1 */
#घोषणा PHY_28NM_RX_SQCAL_DONE			BIT(31)

/* PHY_28NM_DIG_REG0 */
#घोषणा PHY_28NM_DIG_BITSTAFFING_ERR		BIT(31)
#घोषणा PHY_28NM_DIG_SYNC_ERR			BIT(30)

#घोषणा PHY_28NM_DIG_SQ_FILT_SHIFT		16
#घोषणा PHY_28NM_DIG_SQ_FILT_MASK		(0x7 << 16)

#घोषणा PHY_28NM_DIG_SQ_BLK_SHIFT		12
#घोषणा PHY_28NM_DIG_SQ_BLK_MASK		(0x7 << 12)

#घोषणा PHY_28NM_DIG_SYNC_NUM_SHIFT		0
#घोषणा PHY_28NM_DIG_SYNC_NUM_MASK		(0x3 << 0)

#घोषणा PHY_28NM_PLL_LOCK_BYPASS		BIT(7)

/* PHY_28NM_OTG_REG */
#घोषणा PHY_28NM_OTG_CONTROL_BY_PIN		BIT(5)
#घोषणा PHY_28NM_OTG_PU_OTG			BIT(4)

#घोषणा PHY_28NM_CHGDTC_ENABLE_SWITCH_DM_SHIFT_28 13
#घोषणा PHY_28NM_CHGDTC_ENABLE_SWITCH_DP_SHIFT_28 12
#घोषणा PHY_28NM_CHGDTC_VSRC_CHARGE_SHIFT_28	10
#घोषणा PHY_28NM_CHGDTC_VDAT_CHARGE_SHIFT_28	8
#घोषणा PHY_28NM_CHGDTC_CDP_DM_AUTO_SWITCH_SHIFT_28 7
#घोषणा PHY_28NM_CHGDTC_DP_DM_SWAP_SHIFT_28	6
#घोषणा PHY_28NM_CHGDTC_PU_CHRG_DTC_SHIFT_28	5
#घोषणा PHY_28NM_CHGDTC_PD_EN_SHIFT_28		4
#घोषणा PHY_28NM_CHGDTC_DCP_EN_SHIFT_28		3
#घोषणा PHY_28NM_CHGDTC_CDP_EN_SHIFT_28		2
#घोषणा PHY_28NM_CHGDTC_TESTMON_CHRGDTC_SHIFT_28 0

#घोषणा PHY_28NM_CTRL1_CHRG_DTC_OUT_SHIFT_28	4
#घोषणा PHY_28NM_CTRL1_VBUSDTC_OUT_SHIFT_28	2

#घोषणा PHY_28NM_CTRL3_OVERWRITE		BIT(0)
#घोषणा PHY_28NM_CTRL3_VBUS_VALID		BIT(4)
#घोषणा PHY_28NM_CTRL3_AVALID			BIT(5)
#घोषणा PHY_28NM_CTRL3_BVALID			BIT(6)

काष्ठा mv_usb2_phy अणु
	काष्ठा phy		*phy;
	काष्ठा platक्रमm_device	*pdev;
	व्योम __iomem		*base;
	काष्ठा clk		*clk;
पूर्ण;

अटल पूर्णांक रुको_क्रम_reg(व्योम __iomem *reg, u32 mask, u32 ms)
अणु
	u32 val;

	वापस पढ़ोl_poll_समयout(reg, val, ((val & mask) == mask),
				   1000, 1000 * ms);
पूर्ण

अटल पूर्णांक mv_usb2_phy_28nm_init(काष्ठा phy *phy)
अणु
	काष्ठा mv_usb2_phy *mv_phy = phy_get_drvdata(phy);
	काष्ठा platक्रमm_device *pdev = mv_phy->pdev;
	व्योम __iomem *base = mv_phy->base;
	u32 reg;
	पूर्णांक ret;

	clk_prepare_enable(mv_phy->clk);

	/* PHY_28NM_PLL_REG0 */
	reg = पढ़ोl(base + PHY_28NM_PLL_REG0) &
		~(PHY_28NM_PLL_SELLPFR_MASK | PHY_28NM_PLL_FBDIV_MASK
		| PHY_28NM_PLL_ICP_MASK	| PHY_28NM_PLL_REFDIV_MASK);
	ग_लिखोl(reg | (0x1 << PHY_28NM_PLL_SELLPFR_SHIFT
		| 0xf0 << PHY_28NM_PLL_FBDIV_SHIFT
		| 0x3 << PHY_28NM_PLL_ICP_SHIFT
		| 0xd << PHY_28NM_PLL_REFDIV_SHIFT),
		base + PHY_28NM_PLL_REG0);

	/* PHY_28NM_PLL_REG1 */
	reg = पढ़ोl(base + PHY_28NM_PLL_REG1);
	ग_लिखोl(reg | PHY_28NM_PLL_PU_PLL | PHY_28NM_PLL_PU_BY_REG,
		base + PHY_28NM_PLL_REG1);

	/* PHY_28NM_TX_REG0 */
	reg = पढ़ोl(base + PHY_28NM_TX_REG0) & ~PHY_28NM_TX_AMP_MASK;
	ग_लिखोl(reg | PHY_28NM_TX_PU_BY_REG | 0x3 << PHY_28NM_TX_AMP_SHIFT |
		PHY_28NM_TX_PU_ANA,
		base + PHY_28NM_TX_REG0);

	/* PHY_28NM_RX_REG0 */
	reg = पढ़ोl(base + PHY_28NM_RX_REG0) & ~PHY_28NM_RX_SQ_THRESH_MASK;
	ग_लिखोl(reg | 0xa << PHY_28NM_RX_SQ_THRESH_SHIFT,
		base + PHY_28NM_RX_REG0);

	/* PHY_28NM_DIG_REG0 */
	reg = पढ़ोl(base + PHY_28NM_DIG_REG0) &
		~(PHY_28NM_DIG_BITSTAFFING_ERR | PHY_28NM_DIG_SYNC_ERR |
		PHY_28NM_DIG_SQ_FILT_MASK | PHY_28NM_DIG_SQ_BLK_MASK |
		PHY_28NM_DIG_SYNC_NUM_MASK);
	ग_लिखोl(reg | (0x1 << PHY_28NM_DIG_SYNC_NUM_SHIFT |
		PHY_28NM_PLL_LOCK_BYPASS),
		base + PHY_28NM_DIG_REG0);

	/* PHY_28NM_OTG_REG */
	reg = पढ़ोl(base + PHY_28NM_OTG_REG) | PHY_28NM_OTG_PU_OTG;
	ग_लिखोl(reg & ~PHY_28NM_OTG_CONTROL_BY_PIN, base + PHY_28NM_OTG_REG);

	/*
	 *  Calibration Timing
	 *		   ____________________________
	 *  CAL START   ___|
	 *			   ____________________
	 *  CAL_DONE    ___________|
	 *		   | 400us |
	 */

	/* Make sure PHY Calibration is पढ़ोy */
	ret = रुको_क्रम_reg(base + PHY_28NM_CAL_REG,
			   PHY_28NM_PLL_PLLCAL_DONE | PHY_28NM_PLL_IMPCAL_DONE,
			   100);
	अगर (ret) अणु
		dev_warn(&pdev->dev, "USB PHY PLL calibrate not done after 100mS.");
		जाओ err_clk;
	पूर्ण
	ret = रुको_क्रम_reg(base + PHY_28NM_RX_REG1,
			   PHY_28NM_RX_SQCAL_DONE, 100);
	अगर (ret) अणु
		dev_warn(&pdev->dev, "USB PHY RX SQ calibrate not done after 100mS.");
		जाओ err_clk;
	पूर्ण
	/* Make sure PHY PLL is पढ़ोy */
	ret = रुको_क्रम_reg(base + PHY_28NM_PLL_REG0, PHY_28NM_PLL_READY, 100);
	अगर (ret) अणु
		dev_warn(&pdev->dev, "PLL_READY not set after 100mS.");
		जाओ err_clk;
	पूर्ण

	वापस 0;
err_clk:
	clk_disable_unprepare(mv_phy->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक mv_usb2_phy_28nm_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा mv_usb2_phy *mv_phy = phy_get_drvdata(phy);
	व्योम __iomem *base = mv_phy->base;

	ग_लिखोl(पढ़ोl(base + PHY_28NM_CTRL_REG3) |
		(PHY_28NM_CTRL3_OVERWRITE | PHY_28NM_CTRL3_VBUS_VALID |
		PHY_28NM_CTRL3_AVALID | PHY_28NM_CTRL3_BVALID),
		base + PHY_28NM_CTRL_REG3);

	वापस 0;
पूर्ण

अटल पूर्णांक mv_usb2_phy_28nm_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा mv_usb2_phy *mv_phy = phy_get_drvdata(phy);
	व्योम __iomem *base = mv_phy->base;

	ग_लिखोl(पढ़ोl(base + PHY_28NM_CTRL_REG3) |
		~(PHY_28NM_CTRL3_OVERWRITE | PHY_28NM_CTRL3_VBUS_VALID
		| PHY_28NM_CTRL3_AVALID	| PHY_28NM_CTRL3_BVALID),
		base + PHY_28NM_CTRL_REG3);

	वापस 0;
पूर्ण

अटल पूर्णांक mv_usb2_phy_28nm_निकास(काष्ठा phy *phy)
अणु
	काष्ठा mv_usb2_phy *mv_phy = phy_get_drvdata(phy);
	व्योम __iomem *base = mv_phy->base;
	अचिन्हित पूर्णांक val;

	val = पढ़ोw(base + PHY_28NM_PLL_REG1);
	val &= ~PHY_28NM_PLL_PU_PLL;
	ग_लिखोw(val, base + PHY_28NM_PLL_REG1);

	/* घातer करोwn PHY Analog part */
	val = पढ़ोw(base + PHY_28NM_TX_REG0);
	val &= ~PHY_28NM_TX_PU_ANA;
	ग_लिखोw(val, base + PHY_28NM_TX_REG0);

	/* घातer करोwn PHY OTG part */
	val = पढ़ोw(base + PHY_28NM_OTG_REG);
	val &= ~PHY_28NM_OTG_PU_OTG;
	ग_लिखोw(val, base + PHY_28NM_OTG_REG);

	clk_disable_unprepare(mv_phy->clk);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops usb_ops = अणु
	.init		= mv_usb2_phy_28nm_init,
	.घातer_on	= mv_usb2_phy_28nm_घातer_on,
	.घातer_off	= mv_usb2_phy_28nm_घातer_off,
	.निकास		= mv_usb2_phy_28nm_निकास,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक mv_usb2_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा phy_provider *phy_provider;
	काष्ठा mv_usb2_phy *mv_phy;

	mv_phy = devm_kzalloc(&pdev->dev, माप(*mv_phy), GFP_KERNEL);
	अगर (!mv_phy)
		वापस -ENOMEM;

	mv_phy->pdev = pdev;

	mv_phy->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(mv_phy->clk)) अणु
		dev_err(&pdev->dev, "failed to get clock.\n");
		वापस PTR_ERR(mv_phy->clk);
	पूर्ण

	mv_phy->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mv_phy->base))
		वापस PTR_ERR(mv_phy->base);

	mv_phy->phy = devm_phy_create(&pdev->dev, pdev->dev.of_node, &usb_ops);
	अगर (IS_ERR(mv_phy->phy))
		वापस PTR_ERR(mv_phy->phy);

	phy_set_drvdata(mv_phy->phy, mv_phy);

	phy_provider = devm_of_phy_provider_रेजिस्टर(&pdev->dev, of_phy_simple_xlate);
	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id mv_usbphy_dt_match[] = अणु
	अणु .compatible = "marvell,pxa1928-usb-phy", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mv_usbphy_dt_match);

अटल काष्ठा platक्रमm_driver mv_usb2_phy_driver = अणु
	.probe	= mv_usb2_phy_probe,
	.driver = अणु
		.name   = "mv-usb2-phy",
		.of_match_table = of_match_ptr(mv_usbphy_dt_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(mv_usb2_phy_driver);

MODULE_AUTHOR("Rob Herring <robh@kernel.org>");
MODULE_DESCRIPTION("Marvell USB2 phy driver");
MODULE_LICENSE("GPL v2");
