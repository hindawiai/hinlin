<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>

/* USB QSCRATCH Hardware रेजिस्टरs */
#घोषणा QSCRATCH_GENERAL_CFG		(0x08)
#घोषणा HSUSB_PHY_CTRL_REG		(0x10)

/* PHY_CTRL_REG */
#घोषणा HSUSB_CTRL_DMSEHV_CLAMP		BIT(24)
#घोषणा HSUSB_CTRL_USB2_SUSPEND		BIT(23)
#घोषणा HSUSB_CTRL_UTMI_CLK_EN		BIT(21)
#घोषणा HSUSB_CTRL_UTMI_OTG_VBUS_VALID	BIT(20)
#घोषणा HSUSB_CTRL_USE_CLKCORE		BIT(18)
#घोषणा HSUSB_CTRL_DPSEHV_CLAMP		BIT(17)
#घोषणा HSUSB_CTRL_COMMONONN		BIT(11)
#घोषणा HSUSB_CTRL_ID_HV_CLAMP		BIT(9)
#घोषणा HSUSB_CTRL_OTGSESSVLD_CLAMP	BIT(8)
#घोषणा HSUSB_CTRL_CLAMP_EN		BIT(7)
#घोषणा HSUSB_CTRL_RETENABLEN		BIT(1)
#घोषणा HSUSB_CTRL_POR			BIT(0)

/* QSCRATCH_GENERAL_CFG */
#घोषणा HSUSB_GCFG_XHCI_REV		BIT(2)

/* USB QSCRATCH Hardware रेजिस्टरs */
#घोषणा SSUSB_PHY_CTRL_REG		(0x00)
#घोषणा SSUSB_PHY_PARAM_CTRL_1		(0x04)
#घोषणा SSUSB_PHY_PARAM_CTRL_2		(0x08)
#घोषणा CR_PROTOCOL_DATA_IN_REG		(0x0c)
#घोषणा CR_PROTOCOL_DATA_OUT_REG	(0x10)
#घोषणा CR_PROTOCOL_CAP_ADDR_REG	(0x14)
#घोषणा CR_PROTOCOL_CAP_DATA_REG	(0x18)
#घोषणा CR_PROTOCOL_READ_REG		(0x1c)
#घोषणा CR_PROTOCOL_WRITE_REG		(0x20)

/* PHY_CTRL_REG */
#घोषणा SSUSB_CTRL_REF_USE_PAD		BIT(28)
#घोषणा SSUSB_CTRL_TEST_POWERDOWN	BIT(27)
#घोषणा SSUSB_CTRL_LANE0_PWR_PRESENT	BIT(24)
#घोषणा SSUSB_CTRL_SS_PHY_EN		BIT(8)
#घोषणा SSUSB_CTRL_SS_PHY_RESET		BIT(7)

/* SSPHY control रेजिस्टरs - Does this need 0x30? */
#घोषणा SSPHY_CTRL_RX_OVRD_IN_HI(lane)	(0x1006 + 0x100 * (lane))
#घोषणा SSPHY_CTRL_TX_OVRD_DRV_LO(lane)	(0x1002 + 0x100 * (lane))

/* SSPHY SoC version specअगरic values */
#घोषणा SSPHY_RX_EQ_VALUE		4 /* Override value क्रम rx_eq */
/* Override value क्रम transmit preemphasis */
#घोषणा SSPHY_TX_DEEMPH_3_5DB		23
/* Override value क्रम mpll */
#घोषणा SSPHY_MPLL_VALUE		0

/* QSCRATCH PHY_PARAM_CTRL1 fields */
#घोषणा PHY_PARAM_CTRL1_TX_FULL_SWING_MASK	GENMASK(26, 19)
#घोषणा PHY_PARAM_CTRL1_TX_DEEMPH_6DB_MASK	GENMASK(19, 13)
#घोषणा PHY_PARAM_CTRL1_TX_DEEMPH_3_5DB_MASK	GENMASK(13, 7)
#घोषणा PHY_PARAM_CTRL1_LOS_BIAS_MASK		GENMASK(7, 2)

#घोषणा PHY_PARAM_CTRL1_MASK				\
		(PHY_PARAM_CTRL1_TX_FULL_SWING_MASK |	\
		 PHY_PARAM_CTRL1_TX_DEEMPH_6DB_MASK |	\
		 PHY_PARAM_CTRL1_TX_DEEMPH_3_5DB_MASK |	\
		 PHY_PARAM_CTRL1_LOS_BIAS_MASK)

#घोषणा PHY_PARAM_CTRL1_TX_FULL_SWING(x)	\
		(((x) << 20) & PHY_PARAM_CTRL1_TX_FULL_SWING_MASK)
#घोषणा PHY_PARAM_CTRL1_TX_DEEMPH_6DB(x)	\
		(((x) << 14) & PHY_PARAM_CTRL1_TX_DEEMPH_6DB_MASK)
#घोषणा PHY_PARAM_CTRL1_TX_DEEMPH_3_5DB(x)	\
		(((x) <<  8) & PHY_PARAM_CTRL1_TX_DEEMPH_3_5DB_MASK)
#घोषणा PHY_PARAM_CTRL1_LOS_BIAS(x)	\
		(((x) <<  3) & PHY_PARAM_CTRL1_LOS_BIAS_MASK)

/* RX OVRD IN HI bits */
#घोषणा RX_OVRD_IN_HI_RX_RESET_OVRD		BIT(13)
#घोषणा RX_OVRD_IN_HI_RX_RX_RESET		BIT(12)
#घोषणा RX_OVRD_IN_HI_RX_EQ_OVRD		BIT(11)
#घोषणा RX_OVRD_IN_HI_RX_EQ_MASK		GENMASK(10, 7)
#घोषणा RX_OVRD_IN_HI_RX_EQ(x)			((x) << 8)
#घोषणा RX_OVRD_IN_HI_RX_EQ_EN_OVRD		BIT(7)
#घोषणा RX_OVRD_IN_HI_RX_EQ_EN			BIT(6)
#घोषणा RX_OVRD_IN_HI_RX_LOS_FILTER_OVRD	BIT(5)
#घोषणा RX_OVRD_IN_HI_RX_LOS_FILTER_MASK	GENMASK(4, 2)
#घोषणा RX_OVRD_IN_HI_RX_RATE_OVRD		BIT(2)
#घोषणा RX_OVRD_IN_HI_RX_RATE_MASK		GENMASK(2, 0)

/* TX OVRD DRV LO रेजिस्टर bits */
#घोषणा TX_OVRD_DRV_LO_AMPLITUDE_MASK		GENMASK(6, 0)
#घोषणा TX_OVRD_DRV_LO_PREEMPH_MASK		GENMASK(13, 6)
#घोषणा TX_OVRD_DRV_LO_PREEMPH(x)		((x) << 7)
#घोषणा TX_OVRD_DRV_LO_EN			BIT(14)

/* MPLL bits */
#घोषणा SSPHY_MPLL_MASK				GENMASK(8, 5)
#घोषणा SSPHY_MPLL(x)				((x) << 5)

/* SS CAP रेजिस्टर bits */
#घोषणा SS_CR_CAP_ADDR_REG			BIT(0)
#घोषणा SS_CR_CAP_DATA_REG			BIT(0)
#घोषणा SS_CR_READ_REG				BIT(0)
#घोषणा SS_CR_WRITE_REG				BIT(0)

काष्ठा usb_phy अणु
	व्योम __iomem		*base;
	काष्ठा device		*dev;
	काष्ठा clk		*xo_clk;
	काष्ठा clk		*ref_clk;
	u32			rx_eq;
	u32			tx_deamp_3_5db;
	u32			mpll;
पूर्ण;

काष्ठा phy_drvdata अणु
	काष्ठा phy_ops	ops;
	u32		clk_rate;
पूर्ण;

/**
 * Write रेजिस्टर and पढ़ो back masked value to confirm it is written
 *
 * @base - QCOM DWC3 PHY base भव address.
 * @offset - रेजिस्टर offset.
 * @mask - रेजिस्टर biपंचांगask specअगरying what should be updated
 * @val - value to ग_लिखो.
 */
अटल अंतरभूत व्योम usb_phy_ग_लिखो_पढ़ोback(काष्ठा usb_phy *phy_dwc3,
					  u32 offset,
					  स्थिर u32 mask, u32 val)
अणु
	u32 ग_लिखो_val, पंचांगp = पढ़ोl(phy_dwc3->base + offset);

	पंचांगp &= ~mask;		/* retain other bits */
	ग_लिखो_val = पंचांगp | val;

	ग_लिखोl(ग_लिखो_val, phy_dwc3->base + offset);

	/* Read back to see अगर val was written */
	पंचांगp = पढ़ोl(phy_dwc3->base + offset);
	पंचांगp &= mask;		/* clear other bits */

	अगर (पंचांगp != val)
		dev_err(phy_dwc3->dev, "write: %x to QSCRATCH: %x FAILED\n", val, offset);
पूर्ण

अटल पूर्णांक रुको_क्रम_latch(व्योम __iomem *addr)
अणु
	u32 retry = 10;

	जबतक (true) अणु
		अगर (!पढ़ोl(addr))
			अवरोध;

		अगर (--retry == 0)
			वापस -ETIMEDOUT;

		usleep_range(10, 20);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * Write SSPHY रेजिस्टर
 *
 * @base - QCOM DWC3 PHY base भव address.
 * @addr - SSPHY address to ग_लिखो.
 * @val - value to ग_लिखो.
 */
अटल पूर्णांक usb_ss_ग_लिखो_phycreg(काष्ठा usb_phy *phy_dwc3,
				u32 addr, u32 val)
अणु
	पूर्णांक ret;

	ग_लिखोl(addr, phy_dwc3->base + CR_PROTOCOL_DATA_IN_REG);
	ग_लिखोl(SS_CR_CAP_ADDR_REG,
	       phy_dwc3->base + CR_PROTOCOL_CAP_ADDR_REG);

	ret = रुको_क्रम_latch(phy_dwc3->base + CR_PROTOCOL_CAP_ADDR_REG);
	अगर (ret)
		जाओ err_रुको;

	ग_लिखोl(val, phy_dwc3->base + CR_PROTOCOL_DATA_IN_REG);
	ग_लिखोl(SS_CR_CAP_DATA_REG,
	       phy_dwc3->base + CR_PROTOCOL_CAP_DATA_REG);

	ret = रुको_क्रम_latch(phy_dwc3->base + CR_PROTOCOL_CAP_DATA_REG);
	अगर (ret)
		जाओ err_रुको;

	ग_लिखोl(SS_CR_WRITE_REG, phy_dwc3->base + CR_PROTOCOL_WRITE_REG);

	ret = रुको_क्रम_latch(phy_dwc3->base + CR_PROTOCOL_WRITE_REG);

err_रुको:
	अगर (ret)
		dev_err(phy_dwc3->dev, "timeout waiting for latch\n");
	वापस ret;
पूर्ण

/**
 * Read SSPHY रेजिस्टर.
 *
 * @base - QCOM DWC3 PHY base भव address.
 * @addr - SSPHY address to पढ़ो.
 */
अटल पूर्णांक usb_ss_पढ़ो_phycreg(काष्ठा usb_phy *phy_dwc3,
			       u32 addr, u32 *val)
अणु
	पूर्णांक ret;

	ग_लिखोl(addr, phy_dwc3->base + CR_PROTOCOL_DATA_IN_REG);
	ग_लिखोl(SS_CR_CAP_ADDR_REG,
	       phy_dwc3->base + CR_PROTOCOL_CAP_ADDR_REG);

	ret = रुको_क्रम_latch(phy_dwc3->base + CR_PROTOCOL_CAP_ADDR_REG);
	अगर (ret)
		जाओ err_रुको;

	/*
	 * Due to hardware bug, first पढ़ो of SSPHY रेजिस्टर might be
	 * incorrect. Hence as workaround, SW should perक्रमm SSPHY रेजिस्टर
	 * पढ़ो twice, but use only second पढ़ो and ignore first पढ़ो.
	 */
	ग_लिखोl(SS_CR_READ_REG, phy_dwc3->base + CR_PROTOCOL_READ_REG);

	ret = रुको_क्रम_latch(phy_dwc3->base + CR_PROTOCOL_READ_REG);
	अगर (ret)
		जाओ err_रुको;

	/* throwaway पढ़ो */
	पढ़ोl(phy_dwc3->base + CR_PROTOCOL_DATA_OUT_REG);

	ग_लिखोl(SS_CR_READ_REG, phy_dwc3->base + CR_PROTOCOL_READ_REG);

	ret = रुको_क्रम_latch(phy_dwc3->base + CR_PROTOCOL_READ_REG);
	अगर (ret)
		जाओ err_रुको;

	*val = पढ़ोl(phy_dwc3->base + CR_PROTOCOL_DATA_OUT_REG);

err_रुको:
	वापस ret;
पूर्ण

अटल पूर्णांक qcom_ipq806x_usb_hs_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा usb_phy *phy_dwc3 = phy_get_drvdata(phy);
	पूर्णांक ret;
	u32 val;

	ret = clk_prepare_enable(phy_dwc3->xo_clk);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(phy_dwc3->ref_clk);
	अगर (ret) अणु
		clk_disable_unprepare(phy_dwc3->xo_clk);
		वापस ret;
	पूर्ण

	/*
	 * HSPHY Initialization: Enable UTMI घड़ी, select 19.2MHz fsel
	 * enable clamping, and disable RETENTION (घातer-on शेष is ENABLED)
	 */
	val = HSUSB_CTRL_DPSEHV_CLAMP | HSUSB_CTRL_DMSEHV_CLAMP |
		HSUSB_CTRL_RETENABLEN  | HSUSB_CTRL_COMMONONN |
		HSUSB_CTRL_OTGSESSVLD_CLAMP | HSUSB_CTRL_ID_HV_CLAMP |
		HSUSB_CTRL_UTMI_OTG_VBUS_VALID | HSUSB_CTRL_UTMI_CLK_EN |
		HSUSB_CTRL_CLAMP_EN | 0x70;

	/* use core घड़ी अगर बाह्यal reference is not present */
	अगर (!phy_dwc3->xo_clk)
		val |= HSUSB_CTRL_USE_CLKCORE;

	ग_लिखोl(val, phy_dwc3->base + HSUSB_PHY_CTRL_REG);
	usleep_range(2000, 2200);

	/* Disable (bypass) VBUS and ID filters */
	ग_लिखोl(HSUSB_GCFG_XHCI_REV, phy_dwc3->base + QSCRATCH_GENERAL_CFG);

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_ipq806x_usb_hs_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा usb_phy *phy_dwc3 = phy_get_drvdata(phy);

	clk_disable_unprepare(phy_dwc3->ref_clk);
	clk_disable_unprepare(phy_dwc3->xo_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_ipq806x_usb_ss_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा usb_phy *phy_dwc3 = phy_get_drvdata(phy);
	पूर्णांक ret;
	u32 data;

	ret = clk_prepare_enable(phy_dwc3->xo_clk);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(phy_dwc3->ref_clk);
	अगर (ret) अणु
		clk_disable_unprepare(phy_dwc3->xo_clk);
		वापस ret;
	पूर्ण

	/* reset phy */
	data = पढ़ोl(phy_dwc3->base + SSUSB_PHY_CTRL_REG);
	ग_लिखोl(data | SSUSB_CTRL_SS_PHY_RESET,
	       phy_dwc3->base + SSUSB_PHY_CTRL_REG);
	usleep_range(2000, 2200);
	ग_लिखोl(data, phy_dwc3->base + SSUSB_PHY_CTRL_REG);

	/* clear REF_PAD अगर we करोn't have XO clk */
	अगर (!phy_dwc3->xo_clk)
		data &= ~SSUSB_CTRL_REF_USE_PAD;
	अन्यथा
		data |= SSUSB_CTRL_REF_USE_PAD;

	ग_लिखोl(data, phy_dwc3->base + SSUSB_PHY_CTRL_REG);

	/* रुको क्रम ref clk to become stable, this can take up to 30ms */
	msleep(30);

	data |= SSUSB_CTRL_SS_PHY_EN | SSUSB_CTRL_LANE0_PWR_PRESENT;
	ग_लिखोl(data, phy_dwc3->base + SSUSB_PHY_CTRL_REG);

	/*
	 * WORKAROUND: There is SSPHY suspend bug due to which USB क्रमागतerates
	 * in HS mode instead of SS mode. Workaround it by निश्चितing
	 * LANE0.TX_ALT_BLOCK.EN_ALT_BUS to enable TX to use alt bus mode
	 */
	ret = usb_ss_पढ़ो_phycreg(phy_dwc3, 0x102D, &data);
	अगर (ret)
		जाओ err_phy_trans;

	data |= (1 << 7);
	ret = usb_ss_ग_लिखो_phycreg(phy_dwc3, 0x102D, data);
	अगर (ret)
		जाओ err_phy_trans;

	ret = usb_ss_पढ़ो_phycreg(phy_dwc3, 0x1010, &data);
	अगर (ret)
		जाओ err_phy_trans;

	data &= ~0xff0;
	data |= 0x20;
	ret = usb_ss_ग_लिखो_phycreg(phy_dwc3, 0x1010, data);
	अगर (ret)
		जाओ err_phy_trans;

	/*
	 * Fix RX Equalization setting as follows
	 * LANE0.RX_OVRD_IN_HI. RX_EQ_EN set to 0
	 * LANE0.RX_OVRD_IN_HI.RX_EQ_EN_OVRD set to 1
	 * LANE0.RX_OVRD_IN_HI.RX_EQ set based on SoC version
	 * LANE0.RX_OVRD_IN_HI.RX_EQ_OVRD set to 1
	 */
	ret = usb_ss_पढ़ो_phycreg(phy_dwc3, SSPHY_CTRL_RX_OVRD_IN_HI(0), &data);
	अगर (ret)
		जाओ err_phy_trans;

	data &= ~RX_OVRD_IN_HI_RX_EQ_EN;
	data |= RX_OVRD_IN_HI_RX_EQ_EN_OVRD;
	data &= ~RX_OVRD_IN_HI_RX_EQ_MASK;
	data |= RX_OVRD_IN_HI_RX_EQ(phy_dwc3->rx_eq);
	data |= RX_OVRD_IN_HI_RX_EQ_OVRD;
	ret = usb_ss_ग_लिखो_phycreg(phy_dwc3,
				   SSPHY_CTRL_RX_OVRD_IN_HI(0), data);
	अगर (ret)
		जाओ err_phy_trans;

	/*
	 * Set EQ and TX launch amplitudes as follows
	 * LANE0.TX_OVRD_DRV_LO.PREEMPH set based on SoC version
	 * LANE0.TX_OVRD_DRV_LO.AMPLITUDE set to 110
	 * LANE0.TX_OVRD_DRV_LO.EN set to 1.
	 */
	ret = usb_ss_पढ़ो_phycreg(phy_dwc3,
				  SSPHY_CTRL_TX_OVRD_DRV_LO(0), &data);
	अगर (ret)
		जाओ err_phy_trans;

	data &= ~TX_OVRD_DRV_LO_PREEMPH_MASK;
	data |= TX_OVRD_DRV_LO_PREEMPH(phy_dwc3->tx_deamp_3_5db);
	data &= ~TX_OVRD_DRV_LO_AMPLITUDE_MASK;
	data |= 0x6E;
	data |= TX_OVRD_DRV_LO_EN;
	ret = usb_ss_ग_लिखो_phycreg(phy_dwc3,
				   SSPHY_CTRL_TX_OVRD_DRV_LO(0), data);
	अगर (ret)
		जाओ err_phy_trans;

	data = 0;
	data &= ~SSPHY_MPLL_MASK;
	data |= SSPHY_MPLL(phy_dwc3->mpll);
	usb_ss_ग_लिखो_phycreg(phy_dwc3, 0x30, data);

	/*
	 * Set the QSCRATCH PHY_PARAM_CTRL1 parameters as follows
	 * TX_FULL_SWING [26:20] amplitude to 110
	 * TX_DEEMPH_6DB [19:14] to 32
	 * TX_DEEMPH_3_5DB [13:8] set based on SoC version
	 * LOS_BIAS [7:3] to 9
	 */
	data = पढ़ोl(phy_dwc3->base + SSUSB_PHY_PARAM_CTRL_1);

	data &= ~PHY_PARAM_CTRL1_MASK;

	data |= PHY_PARAM_CTRL1_TX_FULL_SWING(0x6e) |
		PHY_PARAM_CTRL1_TX_DEEMPH_6DB(0x20) |
		PHY_PARAM_CTRL1_TX_DEEMPH_3_5DB(phy_dwc3->tx_deamp_3_5db) |
		PHY_PARAM_CTRL1_LOS_BIAS(0x9);

	usb_phy_ग_लिखो_पढ़ोback(phy_dwc3, SSUSB_PHY_PARAM_CTRL_1,
			       PHY_PARAM_CTRL1_MASK, data);

err_phy_trans:
	वापस ret;
पूर्ण

अटल पूर्णांक qcom_ipq806x_usb_ss_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा usb_phy *phy_dwc3 = phy_get_drvdata(phy);

	/* Sequence to put SSPHY in low घातer state:
	 * 1. Clear REF_PHY_EN in PHY_CTRL_REG
	 * 2. Clear REF_USE_PAD in PHY_CTRL_REG
	 * 3. Set TEST_POWERED_DOWN in PHY_CTRL_REG to enable PHY retention
	 */
	usb_phy_ग_लिखो_पढ़ोback(phy_dwc3, SSUSB_PHY_CTRL_REG,
			       SSUSB_CTRL_SS_PHY_EN, 0x0);
	usb_phy_ग_लिखो_पढ़ोback(phy_dwc3, SSUSB_PHY_CTRL_REG,
			       SSUSB_CTRL_REF_USE_PAD, 0x0);
	usb_phy_ग_लिखो_पढ़ोback(phy_dwc3, SSUSB_PHY_CTRL_REG,
			       SSUSB_CTRL_TEST_POWERDOWN, 0x0);

	clk_disable_unprepare(phy_dwc3->ref_clk);
	clk_disable_unprepare(phy_dwc3->xo_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_drvdata qcom_ipq806x_usb_hs_drvdata = अणु
	.ops = अणु
		.init		= qcom_ipq806x_usb_hs_phy_init,
		.निकास		= qcom_ipq806x_usb_hs_phy_निकास,
		.owner		= THIS_MODULE,
	पूर्ण,
	.clk_rate = 60000000,
पूर्ण;

अटल स्थिर काष्ठा phy_drvdata qcom_ipq806x_usb_ss_drvdata = अणु
	.ops = अणु
		.init		= qcom_ipq806x_usb_ss_phy_init,
		.निकास		= qcom_ipq806x_usb_ss_phy_निकास,
		.owner		= THIS_MODULE,
	पूर्ण,
	.clk_rate = 125000000,
पूर्ण;

अटल स्थिर काष्ठा of_device_id qcom_ipq806x_usb_phy_table[] = अणु
	अणु .compatible = "qcom,ipq806x-usb-phy-hs",
	  .data = &qcom_ipq806x_usb_hs_drvdata पूर्ण,
	अणु .compatible = "qcom,ipq806x-usb-phy-ss",
	  .data = &qcom_ipq806x_usb_ss_drvdata पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_ipq806x_usb_phy_table);

अटल पूर्णांक qcom_ipq806x_usb_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	resource_माप_प्रकार size;
	काष्ठा phy *generic_phy;
	काष्ठा usb_phy *phy_dwc3;
	स्थिर काष्ठा phy_drvdata *data;
	काष्ठा phy_provider *phy_provider;

	phy_dwc3 = devm_kzalloc(&pdev->dev, माप(*phy_dwc3), GFP_KERNEL);
	अगर (!phy_dwc3)
		वापस -ENOMEM;

	data = of_device_get_match_data(&pdev->dev);

	phy_dwc3->dev = &pdev->dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -EINVAL;
	size = resource_size(res);
	phy_dwc3->base = devm_ioremap(phy_dwc3->dev, res->start, size);

	अगर (!phy_dwc3->base) अणु
		dev_err(phy_dwc3->dev, "failed to map reg\n");
		वापस -ENOMEM;
	पूर्ण

	phy_dwc3->ref_clk = devm_clk_get(phy_dwc3->dev, "ref");
	अगर (IS_ERR(phy_dwc3->ref_clk)) अणु
		dev_dbg(phy_dwc3->dev, "cannot get reference clock\n");
		वापस PTR_ERR(phy_dwc3->ref_clk);
	पूर्ण

	clk_set_rate(phy_dwc3->ref_clk, data->clk_rate);

	phy_dwc3->xo_clk = devm_clk_get(phy_dwc3->dev, "xo");
	अगर (IS_ERR(phy_dwc3->xo_clk)) अणु
		dev_dbg(phy_dwc3->dev, "cannot get TCXO clock\n");
		phy_dwc3->xo_clk = शून्य;
	पूर्ण

	/* Parse device node to probe HSIO settings */
	अगर (device_property_पढ़ो_u32(&pdev->dev, "qcom,rx-eq",
				     &phy_dwc3->rx_eq))
		phy_dwc3->rx_eq = SSPHY_RX_EQ_VALUE;

	अगर (device_property_पढ़ो_u32(&pdev->dev, "qcom,tx-deamp_3_5db",
				     &phy_dwc3->tx_deamp_3_5db))
		phy_dwc3->tx_deamp_3_5db = SSPHY_TX_DEEMPH_3_5DB;

	अगर (device_property_पढ़ो_u32(&pdev->dev, "qcom,mpll", &phy_dwc3->mpll))
		phy_dwc3->mpll = SSPHY_MPLL_VALUE;

	generic_phy = devm_phy_create(phy_dwc3->dev, pdev->dev.of_node, &data->ops);

	अगर (IS_ERR(generic_phy))
		वापस PTR_ERR(generic_phy);

	phy_set_drvdata(generic_phy, phy_dwc3);
	platक्रमm_set_drvdata(pdev, phy_dwc3);

	phy_provider = devm_of_phy_provider_रेजिस्टर(phy_dwc3->dev,
						     of_phy_simple_xlate);

	अगर (IS_ERR(phy_provider))
		वापस PTR_ERR(phy_provider);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver qcom_ipq806x_usb_phy_driver = अणु
	.probe		= qcom_ipq806x_usb_phy_probe,
	.driver		= अणु
		.name	= "qcom-ipq806x-usb-phy",
		.of_match_table = qcom_ipq806x_usb_phy_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(qcom_ipq806x_usb_phy_driver);

MODULE_ALIAS("platform:phy-qcom-ipq806x-usb");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Andy Gross <agross@codeaurora.org>");
MODULE_AUTHOR("Ivan T. Ivanov <iivanov@mm-sol.com>");
MODULE_DESCRIPTION("DesignWare USB3 QCOM PHY driver");
