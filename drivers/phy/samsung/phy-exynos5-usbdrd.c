<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Samsung Exynos5 SoC series USB DRD PHY driver
 *
 * Phy provider क्रम USB 3.0 DRD controller on Exynos5 SoC series
 *
 * Copyright (C) 2014 Samsung Electronics Co., Ltd.
 * Author: Vivek Gautam <gautam.vivek@samsung.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/soc/samsung/exynos-regs-pmu.h>

/* Exynos USB PHY रेजिस्टरs */
#घोषणा EXYNOS5_FSEL_9MHZ6		0x0
#घोषणा EXYNOS5_FSEL_10MHZ		0x1
#घोषणा EXYNOS5_FSEL_12MHZ		0x2
#घोषणा EXYNOS5_FSEL_19MHZ2		0x3
#घोषणा EXYNOS5_FSEL_20MHZ		0x4
#घोषणा EXYNOS5_FSEL_24MHZ		0x5
#घोषणा EXYNOS5_FSEL_50MHZ		0x7

/* Exynos5: USB 3.0 DRD PHY रेजिस्टरs */
#घोषणा EXYNOS5_DRD_LINKSYSTEM			0x04

#घोषणा LINKSYSTEM_FLADJ_MASK			(0x3f << 1)
#घोषणा LINKSYSTEM_FLADJ(_x)			((_x) << 1)
#घोषणा LINKSYSTEM_XHCI_VERSION_CONTROL		BIT(27)

#घोषणा EXYNOS5_DRD_PHYUTMI			0x08

#घोषणा PHYUTMI_OTGDISABLE			BIT(6)
#घोषणा PHYUTMI_FORCESUSPEND			BIT(1)
#घोषणा PHYUTMI_FORCESLEEP			BIT(0)

#घोषणा EXYNOS5_DRD_PHYPIPE			0x0c

#घोषणा EXYNOS5_DRD_PHYCLKRST			0x10

#घोषणा PHYCLKRST_EN_UTMISUSPEND		BIT(31)

#घोषणा PHYCLKRST_SSC_REFCLKSEL_MASK		(0xff << 23)
#घोषणा PHYCLKRST_SSC_REFCLKSEL(_x)		((_x) << 23)

#घोषणा PHYCLKRST_SSC_RANGE_MASK		(0x03 << 21)
#घोषणा PHYCLKRST_SSC_RANGE(_x)			((_x) << 21)

#घोषणा PHYCLKRST_SSC_EN			BIT(20)
#घोषणा PHYCLKRST_REF_SSP_EN			BIT(19)
#घोषणा PHYCLKRST_REF_CLKDIV2			BIT(18)

#घोषणा PHYCLKRST_MPLL_MULTIPLIER_MASK		(0x7f << 11)
#घोषणा PHYCLKRST_MPLL_MULTIPLIER_100MHZ_REF	(0x19 << 11)
#घोषणा PHYCLKRST_MPLL_MULTIPLIER_50M_REF	(0x32 << 11)
#घोषणा PHYCLKRST_MPLL_MULTIPLIER_24MHZ_REF	(0x68 << 11)
#घोषणा PHYCLKRST_MPLL_MULTIPLIER_20MHZ_REF	(0x7d << 11)
#घोषणा PHYCLKRST_MPLL_MULTIPLIER_19200KHZ_REF	(0x02 << 11)

#घोषणा PHYCLKRST_FSEL_UTMI_MASK		(0x7 << 5)
#घोषणा PHYCLKRST_FSEL_PIPE_MASK		(0x7 << 8)
#घोषणा PHYCLKRST_FSEL(_x)			((_x) << 5)
#घोषणा PHYCLKRST_FSEL_PAD_100MHZ		(0x27 << 5)
#घोषणा PHYCLKRST_FSEL_PAD_24MHZ		(0x2a << 5)
#घोषणा PHYCLKRST_FSEL_PAD_20MHZ		(0x31 << 5)
#घोषणा PHYCLKRST_FSEL_PAD_19_2MHZ		(0x38 << 5)

#घोषणा PHYCLKRST_RETENABLEN			BIT(4)

#घोषणा PHYCLKRST_REFCLKSEL_MASK		(0x03 << 2)
#घोषणा PHYCLKRST_REFCLKSEL_PAD_REFCLK		(0x2 << 2)
#घोषणा PHYCLKRST_REFCLKSEL_EXT_REFCLK		(0x3 << 2)

#घोषणा PHYCLKRST_PORTRESET			BIT(1)
#घोषणा PHYCLKRST_COMMONONN			BIT(0)

#घोषणा EXYNOS5_DRD_PHYREG0			0x14
#घोषणा PHYREG0_SSC_REF_CLK_SEL			BIT(21)
#घोषणा PHYREG0_SSC_RANGE			BIT(20)
#घोषणा PHYREG0_CR_WRITE			BIT(19)
#घोषणा PHYREG0_CR_READ				BIT(18)
#घोषणा PHYREG0_CR_DATA_IN(_x)			((_x) << 2)
#घोषणा PHYREG0_CR_CAP_DATA			BIT(1)
#घोषणा PHYREG0_CR_CAP_ADDR			BIT(0)

#घोषणा EXYNOS5_DRD_PHYREG1			0x18
#घोषणा PHYREG1_CR_DATA_OUT(_x)			((_x) << 1)
#घोषणा PHYREG1_CR_ACK				BIT(0)

#घोषणा EXYNOS5_DRD_PHYPARAM0			0x1c

#घोषणा PHYPARAM0_REF_USE_PAD			BIT(31)
#घोषणा PHYPARAM0_REF_LOSLEVEL_MASK		(0x1f << 26)
#घोषणा PHYPARAM0_REF_LOSLEVEL			(0x9 << 26)

#घोषणा EXYNOS5_DRD_PHYPARAM1			0x20

#घोषणा PHYPARAM1_PCS_TXDEEMPH_MASK		(0x1f << 0)
#घोषणा PHYPARAM1_PCS_TXDEEMPH			(0x1c)

#घोषणा EXYNOS5_DRD_PHYTERM			0x24

#घोषणा EXYNOS5_DRD_PHYTEST			0x28

#घोषणा PHYTEST_POWERDOWN_SSP			BIT(3)
#घोषणा PHYTEST_POWERDOWN_HSP			BIT(2)

#घोषणा EXYNOS5_DRD_PHYADP			0x2c

#घोषणा EXYNOS5_DRD_PHYUTMICLKSEL		0x30

#घोषणा PHYUTMICLKSEL_UTMI_CLKSEL		BIT(2)

#घोषणा EXYNOS5_DRD_PHYRESUME			0x34
#घोषणा EXYNOS5_DRD_LINKPORT			0x44

/* USB 3.0 DRD PHY SS Function Control Reg; accessed by CR_PORT */
#घोषणा EXYNOS5_DRD_PHYSS_LOSLEVEL_OVRD_IN		(0x15)
#घोषणा LOSLEVEL_OVRD_IN_LOS_BIAS_5420			(0x5 << 13)
#घोषणा LOSLEVEL_OVRD_IN_LOS_BIAS_DEFAULT		(0x0 << 13)
#घोषणा LOSLEVEL_OVRD_IN_EN				(0x1 << 10)
#घोषणा LOSLEVEL_OVRD_IN_LOS_LEVEL_DEFAULT		(0x9 << 0)

#घोषणा EXYNOS5_DRD_PHYSS_TX_VBOOSTLEVEL_OVRD_IN	(0x12)
#घोषणा TX_VBOOSTLEVEL_OVRD_IN_VBOOST_5420		(0x5 << 13)
#घोषणा TX_VBOOSTLEVEL_OVRD_IN_VBOOST_DEFAULT		(0x4 << 13)

#घोषणा EXYNOS5_DRD_PHYSS_LANE0_TX_DEBUG		(0x1010)
#घोषणा LANE0_TX_DEBUG_RXDET_MEAS_TIME_19M2_20M		(0x4 << 4)
#घोषणा LANE0_TX_DEBUG_RXDET_MEAS_TIME_24M		(0x8 << 4)
#घोषणा LANE0_TX_DEBUG_RXDET_MEAS_TIME_25M_26M		(0x8 << 4)
#घोषणा LANE0_TX_DEBUG_RXDET_MEAS_TIME_48M_50M_52M	(0x20 << 4)
#घोषणा LANE0_TX_DEBUG_RXDET_MEAS_TIME_62M5		(0x20 << 4)
#घोषणा LANE0_TX_DEBUG_RXDET_MEAS_TIME_96M_100M		(0x40 << 4)

#घोषणा KHZ	1000
#घोषणा MHZ	(KHZ * KHZ)

क्रमागत exynos5_usbdrd_phy_id अणु
	EXYNOS5_DRDPHY_UTMI,
	EXYNOS5_DRDPHY_PIPE3,
	EXYNOS5_DRDPHYS_NUM,
पूर्ण;

काष्ठा phy_usb_instance;
काष्ठा exynos5_usbdrd_phy;

काष्ठा exynos5_usbdrd_phy_config अणु
	u32 id;
	व्योम (*phy_isol)(काष्ठा phy_usb_instance *inst, u32 on);
	व्योम (*phy_init)(काष्ठा exynos5_usbdrd_phy *phy_drd);
	अचिन्हित पूर्णांक (*set_refclk)(काष्ठा phy_usb_instance *inst);
पूर्ण;

काष्ठा exynos5_usbdrd_phy_drvdata अणु
	स्थिर काष्ठा exynos5_usbdrd_phy_config *phy_cfg;
	u32 pmu_offset_usbdrd0_phy;
	u32 pmu_offset_usbdrd1_phy;
	bool has_common_clk_gate;
पूर्ण;

/**
 * काष्ठा exynos5_usbdrd_phy - driver data क्रम USB 3.0 PHY
 * @dev: poपूर्णांकer to device instance of this platक्रमm device
 * @reg_phy: usb phy controller रेजिस्टर memory base
 * @clk: phy घड़ी क्रम रेजिस्टर access
 * @pipeclk: घड़ी क्रम pipe3 phy
 * @uपंचांगiclk: घड़ी क्रम uपंचांगi+ phy
 * @itpclk: घड़ी क्रम ITP generation
 * @drv_data: poपूर्णांकer to SoC level driver data काष्ठाure
 * @phys: array क्रम 'EXYNOS5_DRDPHYS_NUM' number of PHY
 *	    instances each with its 'phy' and 'phy_cfg'.
 * @extrefclk: frequency select settings when using 'separate
 *	       reference घड़ीs' क्रम SS and HS operations
 * @ref_clk: reference घड़ी to PHY block from which PHY's
 *	     operational घड़ीs are derived
 * @vbus: VBUS regulator क्रम phy
 * @vbus_boost: Boost regulator क्रम VBUS present on few Exynos boards
 */
काष्ठा exynos5_usbdrd_phy अणु
	काष्ठा device *dev;
	व्योम __iomem *reg_phy;
	काष्ठा clk *clk;
	काष्ठा clk *pipeclk;
	काष्ठा clk *uपंचांगiclk;
	काष्ठा clk *itpclk;
	स्थिर काष्ठा exynos5_usbdrd_phy_drvdata *drv_data;
	काष्ठा phy_usb_instance अणु
		काष्ठा phy *phy;
		u32 index;
		काष्ठा regmap *reg_pmu;
		u32 pmu_offset;
		स्थिर काष्ठा exynos5_usbdrd_phy_config *phy_cfg;
	पूर्ण phys[EXYNOS5_DRDPHYS_NUM];
	u32 extrefclk;
	काष्ठा clk *ref_clk;
	काष्ठा regulator *vbus;
	काष्ठा regulator *vbus_boost;
पूर्ण;

अटल अंतरभूत
काष्ठा exynos5_usbdrd_phy *to_usbdrd_phy(काष्ठा phy_usb_instance *inst)
अणु
	वापस container_of((inst), काष्ठा exynos5_usbdrd_phy,
			    phys[(inst)->index]);
पूर्ण

/*
 * exynos5_rate_to_clk() converts the supplied घड़ी rate to the value that
 * can be written to the phy रेजिस्टर.
 */
अटल अचिन्हित पूर्णांक exynos5_rate_to_clk(अचिन्हित दीर्घ rate, u32 *reg)
अणु
	/* EXYNOS5_FSEL_MASK */

	चयन (rate) अणु
	हाल 9600 * KHZ:
		*reg = EXYNOS5_FSEL_9MHZ6;
		अवरोध;
	हाल 10 * MHZ:
		*reg = EXYNOS5_FSEL_10MHZ;
		अवरोध;
	हाल 12 * MHZ:
		*reg = EXYNOS5_FSEL_12MHZ;
		अवरोध;
	हाल 19200 * KHZ:
		*reg = EXYNOS5_FSEL_19MHZ2;
		अवरोध;
	हाल 20 * MHZ:
		*reg = EXYNOS5_FSEL_20MHZ;
		अवरोध;
	हाल 24 * MHZ:
		*reg = EXYNOS5_FSEL_24MHZ;
		अवरोध;
	हाल 50 * MHZ:
		*reg = EXYNOS5_FSEL_50MHZ;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम exynos5_usbdrd_phy_isol(काष्ठा phy_usb_instance *inst,
						अचिन्हित पूर्णांक on)
अणु
	अचिन्हित पूर्णांक val;

	अगर (!inst->reg_pmu)
		वापस;

	val = on ? 0 : EXYNOS4_PHY_ENABLE;

	regmap_update_bits(inst->reg_pmu, inst->pmu_offset,
			   EXYNOS4_PHY_ENABLE, val);
पूर्ण

/*
 * Sets the pipe3 phy's clk as EXTREFCLK (XXTI) which is पूर्णांकernal घड़ी
 * from घड़ी core. Further sets multiplier values and spपढ़ो spectrum
 * घड़ी settings क्रम SuperSpeed operations.
 */
अटल अचिन्हित पूर्णांक
exynos5_usbdrd_pipe3_set_refclk(काष्ठा phy_usb_instance *inst)
अणु
	u32 reg;
	काष्ठा exynos5_usbdrd_phy *phy_drd = to_usbdrd_phy(inst);

	/* restore any previous reference घड़ी settings */
	reg = पढ़ोl(phy_drd->reg_phy + EXYNOS5_DRD_PHYCLKRST);

	/* Use EXTREFCLK as ref घड़ी */
	reg &= ~PHYCLKRST_REFCLKSEL_MASK;
	reg |=	PHYCLKRST_REFCLKSEL_EXT_REFCLK;

	/* FSEL settings corresponding to reference घड़ी */
	reg &= ~PHYCLKRST_FSEL_PIPE_MASK |
		PHYCLKRST_MPLL_MULTIPLIER_MASK |
		PHYCLKRST_SSC_REFCLKSEL_MASK;
	चयन (phy_drd->extrefclk) अणु
	हाल EXYNOS5_FSEL_50MHZ:
		reg |= (PHYCLKRST_MPLL_MULTIPLIER_50M_REF |
			PHYCLKRST_SSC_REFCLKSEL(0x00));
		अवरोध;
	हाल EXYNOS5_FSEL_24MHZ:
		reg |= (PHYCLKRST_MPLL_MULTIPLIER_24MHZ_REF |
			PHYCLKRST_SSC_REFCLKSEL(0x88));
		अवरोध;
	हाल EXYNOS5_FSEL_20MHZ:
		reg |= (PHYCLKRST_MPLL_MULTIPLIER_20MHZ_REF |
			PHYCLKRST_SSC_REFCLKSEL(0x00));
		अवरोध;
	हाल EXYNOS5_FSEL_19MHZ2:
		reg |= (PHYCLKRST_MPLL_MULTIPLIER_19200KHZ_REF |
			PHYCLKRST_SSC_REFCLKSEL(0x88));
		अवरोध;
	शेष:
		dev_dbg(phy_drd->dev, "unsupported ref clk\n");
		अवरोध;
	पूर्ण

	वापस reg;
पूर्ण

/*
 * Sets the uपंचांगi phy's clk as EXTREFCLK (XXTI) which is पूर्णांकernal घड़ी
 * from घड़ी core. Further sets the FSEL values क्रम HighSpeed operations.
 */
अटल अचिन्हित पूर्णांक
exynos5_usbdrd_uपंचांगi_set_refclk(काष्ठा phy_usb_instance *inst)
अणु
	u32 reg;
	काष्ठा exynos5_usbdrd_phy *phy_drd = to_usbdrd_phy(inst);

	/* restore any previous reference घड़ी settings */
	reg = पढ़ोl(phy_drd->reg_phy + EXYNOS5_DRD_PHYCLKRST);

	reg &= ~PHYCLKRST_REFCLKSEL_MASK;
	reg |=	PHYCLKRST_REFCLKSEL_EXT_REFCLK;

	reg &= ~PHYCLKRST_FSEL_UTMI_MASK |
		PHYCLKRST_MPLL_MULTIPLIER_MASK |
		PHYCLKRST_SSC_REFCLKSEL_MASK;
	reg |= PHYCLKRST_FSEL(phy_drd->extrefclk);

	वापस reg;
पूर्ण

अटल व्योम exynos5_usbdrd_pipe3_init(काष्ठा exynos5_usbdrd_phy *phy_drd)
अणु
	u32 reg;

	reg = पढ़ोl(phy_drd->reg_phy + EXYNOS5_DRD_PHYPARAM1);
	/* Set Tx De-Emphasis level */
	reg &= ~PHYPARAM1_PCS_TXDEEMPH_MASK;
	reg |=	PHYPARAM1_PCS_TXDEEMPH;
	ग_लिखोl(reg, phy_drd->reg_phy + EXYNOS5_DRD_PHYPARAM1);

	reg = पढ़ोl(phy_drd->reg_phy + EXYNOS5_DRD_PHYTEST);
	reg &= ~PHYTEST_POWERDOWN_SSP;
	ग_लिखोl(reg, phy_drd->reg_phy + EXYNOS5_DRD_PHYTEST);
पूर्ण

अटल व्योम exynos5_usbdrd_uपंचांगi_init(काष्ठा exynos5_usbdrd_phy *phy_drd)
अणु
	u32 reg;

	reg = पढ़ोl(phy_drd->reg_phy + EXYNOS5_DRD_PHYPARAM0);
	/* Set Loss-of-Signal Detector sensitivity */
	reg &= ~PHYPARAM0_REF_LOSLEVEL_MASK;
	reg |=	PHYPARAM0_REF_LOSLEVEL;
	ग_लिखोl(reg, phy_drd->reg_phy + EXYNOS5_DRD_PHYPARAM0);

	reg = पढ़ोl(phy_drd->reg_phy + EXYNOS5_DRD_PHYPARAM1);
	/* Set Tx De-Emphasis level */
	reg &= ~PHYPARAM1_PCS_TXDEEMPH_MASK;
	reg |=	PHYPARAM1_PCS_TXDEEMPH;
	ग_लिखोl(reg, phy_drd->reg_phy + EXYNOS5_DRD_PHYPARAM1);

	/* UTMI Power Control */
	ग_लिखोl(PHYUTMI_OTGDISABLE, phy_drd->reg_phy + EXYNOS5_DRD_PHYUTMI);

	reg = पढ़ोl(phy_drd->reg_phy + EXYNOS5_DRD_PHYTEST);
	reg &= ~PHYTEST_POWERDOWN_HSP;
	ग_लिखोl(reg, phy_drd->reg_phy + EXYNOS5_DRD_PHYTEST);
पूर्ण

अटल पूर्णांक exynos5_usbdrd_phy_init(काष्ठा phy *phy)
अणु
	पूर्णांक ret;
	u32 reg;
	काष्ठा phy_usb_instance *inst = phy_get_drvdata(phy);
	काष्ठा exynos5_usbdrd_phy *phy_drd = to_usbdrd_phy(inst);

	ret = clk_prepare_enable(phy_drd->clk);
	अगर (ret)
		वापस ret;

	/* Reset USB 3.0 PHY */
	ग_लिखोl(0x0, phy_drd->reg_phy + EXYNOS5_DRD_PHYREG0);
	ग_लिखोl(0x0, phy_drd->reg_phy + EXYNOS5_DRD_PHYRESUME);

	/*
	 * Setting the Frame length Adj value[6:1] to शेष 0x20
	 * See xHCI 1.0 spec, 5.2.4
	 */
	reg =	LINKSYSTEM_XHCI_VERSION_CONTROL |
		LINKSYSTEM_FLADJ(0x20);
	ग_लिखोl(reg, phy_drd->reg_phy + EXYNOS5_DRD_LINKSYSTEM);

	reg = पढ़ोl(phy_drd->reg_phy + EXYNOS5_DRD_PHYPARAM0);
	/* Select PHY CLK source */
	reg &= ~PHYPARAM0_REF_USE_PAD;
	ग_लिखोl(reg, phy_drd->reg_phy + EXYNOS5_DRD_PHYPARAM0);

	/* This bit must be set क्रम both HS and SS operations */
	reg = पढ़ोl(phy_drd->reg_phy + EXYNOS5_DRD_PHYUTMICLKSEL);
	reg |= PHYUTMICLKSEL_UTMI_CLKSEL;
	ग_लिखोl(reg, phy_drd->reg_phy + EXYNOS5_DRD_PHYUTMICLKSEL);

	/* UTMI or PIPE3 specअगरic init */
	inst->phy_cfg->phy_init(phy_drd);

	/* reference घड़ी settings */
	reg = inst->phy_cfg->set_refclk(inst);

		/* Digital घातer supply in normal operating mode */
	reg |=	PHYCLKRST_RETENABLEN |
		/* Enable ref घड़ी क्रम SS function */
		PHYCLKRST_REF_SSP_EN |
		/* Enable spपढ़ो spectrum */
		PHYCLKRST_SSC_EN |
		/* Power करोwn HS Bias and PLL blocks in suspend mode */
		PHYCLKRST_COMMONONN |
		/* Reset the port */
		PHYCLKRST_PORTRESET;

	ग_लिखोl(reg, phy_drd->reg_phy + EXYNOS5_DRD_PHYCLKRST);

	udelay(10);

	reg &= ~PHYCLKRST_PORTRESET;
	ग_लिखोl(reg, phy_drd->reg_phy + EXYNOS5_DRD_PHYCLKRST);

	clk_disable_unprepare(phy_drd->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक exynos5_usbdrd_phy_निकास(काष्ठा phy *phy)
अणु
	पूर्णांक ret;
	u32 reg;
	काष्ठा phy_usb_instance *inst = phy_get_drvdata(phy);
	काष्ठा exynos5_usbdrd_phy *phy_drd = to_usbdrd_phy(inst);

	ret = clk_prepare_enable(phy_drd->clk);
	अगर (ret)
		वापस ret;

	reg =	PHYUTMI_OTGDISABLE |
		PHYUTMI_FORCESUSPEND |
		PHYUTMI_FORCESLEEP;
	ग_लिखोl(reg, phy_drd->reg_phy + EXYNOS5_DRD_PHYUTMI);

	/* Resetting the PHYCLKRST enable bits to reduce leakage current */
	reg = पढ़ोl(phy_drd->reg_phy + EXYNOS5_DRD_PHYCLKRST);
	reg &= ~(PHYCLKRST_REF_SSP_EN |
		 PHYCLKRST_SSC_EN |
		 PHYCLKRST_COMMONONN);
	ग_लिखोl(reg, phy_drd->reg_phy + EXYNOS5_DRD_PHYCLKRST);

	/* Control PHYTEST to हटाओ leakage current */
	reg = पढ़ोl(phy_drd->reg_phy + EXYNOS5_DRD_PHYTEST);
	reg |=	PHYTEST_POWERDOWN_SSP |
		PHYTEST_POWERDOWN_HSP;
	ग_लिखोl(reg, phy_drd->reg_phy + EXYNOS5_DRD_PHYTEST);

	clk_disable_unprepare(phy_drd->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक exynos5_usbdrd_phy_घातer_on(काष्ठा phy *phy)
अणु
	पूर्णांक ret;
	काष्ठा phy_usb_instance *inst = phy_get_drvdata(phy);
	काष्ठा exynos5_usbdrd_phy *phy_drd = to_usbdrd_phy(inst);

	dev_dbg(phy_drd->dev, "Request to power_on usbdrd_phy phy\n");

	clk_prepare_enable(phy_drd->ref_clk);
	अगर (!phy_drd->drv_data->has_common_clk_gate) अणु
		clk_prepare_enable(phy_drd->pipeclk);
		clk_prepare_enable(phy_drd->uपंचांगiclk);
		clk_prepare_enable(phy_drd->itpclk);
	पूर्ण

	/* Enable VBUS supply */
	अगर (phy_drd->vbus_boost) अणु
		ret = regulator_enable(phy_drd->vbus_boost);
		अगर (ret) अणु
			dev_err(phy_drd->dev,
				"Failed to enable VBUS boost supply\n");
			जाओ fail_vbus;
		पूर्ण
	पूर्ण

	अगर (phy_drd->vbus) अणु
		ret = regulator_enable(phy_drd->vbus);
		अगर (ret) अणु
			dev_err(phy_drd->dev, "Failed to enable VBUS supply\n");
			जाओ fail_vbus_boost;
		पूर्ण
	पूर्ण

	/* Power-on PHY*/
	inst->phy_cfg->phy_isol(inst, 0);

	वापस 0;

fail_vbus_boost:
	अगर (phy_drd->vbus_boost)
		regulator_disable(phy_drd->vbus_boost);

fail_vbus:
	clk_disable_unprepare(phy_drd->ref_clk);
	अगर (!phy_drd->drv_data->has_common_clk_gate) अणु
		clk_disable_unprepare(phy_drd->itpclk);
		clk_disable_unprepare(phy_drd->uपंचांगiclk);
		clk_disable_unprepare(phy_drd->pipeclk);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक exynos5_usbdrd_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा phy_usb_instance *inst = phy_get_drvdata(phy);
	काष्ठा exynos5_usbdrd_phy *phy_drd = to_usbdrd_phy(inst);

	dev_dbg(phy_drd->dev, "Request to power_off usbdrd_phy phy\n");

	/* Power-off the PHY */
	inst->phy_cfg->phy_isol(inst, 1);

	/* Disable VBUS supply */
	अगर (phy_drd->vbus)
		regulator_disable(phy_drd->vbus);
	अगर (phy_drd->vbus_boost)
		regulator_disable(phy_drd->vbus_boost);

	clk_disable_unprepare(phy_drd->ref_clk);
	अगर (!phy_drd->drv_data->has_common_clk_gate) अणु
		clk_disable_unprepare(phy_drd->itpclk);
		clk_disable_unprepare(phy_drd->pipeclk);
		clk_disable_unprepare(phy_drd->uपंचांगiclk);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक crport_handshake(काष्ठा exynos5_usbdrd_phy *phy_drd,
			    u32 val, u32 cmd)
अणु
	अचिन्हित पूर्णांक result;
	पूर्णांक err;

	ग_लिखोl(val | cmd, phy_drd->reg_phy + EXYNOS5_DRD_PHYREG0);

	err = पढ़ोl_poll_समयout(phy_drd->reg_phy + EXYNOS5_DRD_PHYREG1,
				 result, (result & PHYREG1_CR_ACK), 1, 100);
	अगर (err == -ETIMEDOUT) अणु
		dev_err(phy_drd->dev, "CRPORT handshake timeout1 (0x%08x)\n", val);
		वापस err;
	पूर्ण

	ग_लिखोl(val, phy_drd->reg_phy + EXYNOS5_DRD_PHYREG0);

	err = पढ़ोl_poll_समयout(phy_drd->reg_phy + EXYNOS5_DRD_PHYREG1,
				 result, !(result & PHYREG1_CR_ACK), 1, 100);
	अगर (err == -ETIMEDOUT) अणु
		dev_err(phy_drd->dev, "CRPORT handshake timeout2 (0x%08x)\n", val);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक crport_ctrl_ग_लिखो(काष्ठा exynos5_usbdrd_phy *phy_drd,
			     u32 addr, u32 data)
अणु
	पूर्णांक ret;

	/* Write Address */
	ग_लिखोl(PHYREG0_CR_DATA_IN(addr),
	       phy_drd->reg_phy + EXYNOS5_DRD_PHYREG0);
	ret = crport_handshake(phy_drd, PHYREG0_CR_DATA_IN(addr),
			       PHYREG0_CR_CAP_ADDR);
	अगर (ret)
		वापस ret;

	/* Write Data */
	ग_लिखोl(PHYREG0_CR_DATA_IN(data),
	       phy_drd->reg_phy + EXYNOS5_DRD_PHYREG0);
	ret = crport_handshake(phy_drd, PHYREG0_CR_DATA_IN(data),
			       PHYREG0_CR_CAP_DATA);
	अगर (ret)
		वापस ret;

	ret = crport_handshake(phy_drd, PHYREG0_CR_DATA_IN(data),
			       PHYREG0_CR_WRITE);

	वापस ret;
पूर्ण

/*
 * Calibrate few PHY parameters using CR_PORT रेजिस्टर to meet
 * SuperSpeed requirements on Exynos5420 and Exynos5800 प्रणालीs,
 * which have 28nm USB 3.0 DRD PHY.
 */
अटल पूर्णांक exynos5420_usbdrd_phy_calibrate(काष्ठा exynos5_usbdrd_phy *phy_drd)
अणु
	अचिन्हित पूर्णांक temp;
	पूर्णांक ret = 0;

	/*
	 * Change los_bias to (0x5) क्रम 28nm PHY from a
	 * शेष value (0x0); los_level is set as शेष
	 * (0x9) as also reflected in los_level[30:26] bits
	 * of PHYPARAM0 रेजिस्टर.
	 */
	temp = LOSLEVEL_OVRD_IN_LOS_BIAS_5420 |
		LOSLEVEL_OVRD_IN_EN |
		LOSLEVEL_OVRD_IN_LOS_LEVEL_DEFAULT;
	ret = crport_ctrl_ग_लिखो(phy_drd,
				EXYNOS5_DRD_PHYSS_LOSLEVEL_OVRD_IN,
				temp);
	अगर (ret) अणु
		dev_err(phy_drd->dev,
			"Failed setting Loss-of-Signal level for SuperSpeed\n");
		वापस ret;
	पूर्ण

	/*
	 * Set tx_vboost_lvl to (0x5) क्रम 28nm PHY Tuning,
	 * to उठाओ Tx संकेत level from its शेष value of (0x4)
	 */
	temp = TX_VBOOSTLEVEL_OVRD_IN_VBOOST_5420;
	ret = crport_ctrl_ग_लिखो(phy_drd,
				EXYNOS5_DRD_PHYSS_TX_VBOOSTLEVEL_OVRD_IN,
				temp);
	अगर (ret) अणु
		dev_err(phy_drd->dev,
			"Failed setting Tx-Vboost-Level for SuperSpeed\n");
		वापस ret;
	पूर्ण

	/*
	 * Set proper समय to रुको क्रम RxDetect measurement, क्रम
	 * desired reference घड़ी of PHY, by tuning the CR_PORT
	 * रेजिस्टर LANE0.TX_DEBUG which is पूर्णांकernal to PHY.
	 * This fixes issue with few USB 3.0 devices, which are
	 * not detected (not even generate पूर्णांकerrupts on the bus
	 * on insertion) without this change.
	 * e.g. Samsung SUM-TSB16S 3.0 USB drive.
	 */
	चयन (phy_drd->extrefclk) अणु
	हाल EXYNOS5_FSEL_50MHZ:
		temp = LANE0_TX_DEBUG_RXDET_MEAS_TIME_48M_50M_52M;
		अवरोध;
	हाल EXYNOS5_FSEL_20MHZ:
	हाल EXYNOS5_FSEL_19MHZ2:
		temp = LANE0_TX_DEBUG_RXDET_MEAS_TIME_19M2_20M;
		अवरोध;
	हाल EXYNOS5_FSEL_24MHZ:
	शेष:
		temp = LANE0_TX_DEBUG_RXDET_MEAS_TIME_24M;
		अवरोध;
	पूर्ण

	ret = crport_ctrl_ग_लिखो(phy_drd,
				EXYNOS5_DRD_PHYSS_LANE0_TX_DEBUG,
				temp);
	अगर (ret)
		dev_err(phy_drd->dev,
			"Fail to set RxDet measurement time for SuperSpeed\n");

	वापस ret;
पूर्ण

अटल काष्ठा phy *exynos5_usbdrd_phy_xlate(काष्ठा device *dev,
					काष्ठा of_phandle_args *args)
अणु
	काष्ठा exynos5_usbdrd_phy *phy_drd = dev_get_drvdata(dev);

	अगर (WARN_ON(args->args[0] >= EXYNOS5_DRDPHYS_NUM))
		वापस ERR_PTR(-ENODEV);

	वापस phy_drd->phys[args->args[0]].phy;
पूर्ण

अटल पूर्णांक exynos5_usbdrd_phy_calibrate(काष्ठा phy *phy)
अणु
	काष्ठा phy_usb_instance *inst = phy_get_drvdata(phy);
	काष्ठा exynos5_usbdrd_phy *phy_drd = to_usbdrd_phy(inst);

	अगर (inst->phy_cfg->id == EXYNOS5_DRDPHY_UTMI)
		वापस exynos5420_usbdrd_phy_calibrate(phy_drd);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops exynos5_usbdrd_phy_ops = अणु
	.init		= exynos5_usbdrd_phy_init,
	.निकास		= exynos5_usbdrd_phy_निकास,
	.घातer_on	= exynos5_usbdrd_phy_घातer_on,
	.घातer_off	= exynos5_usbdrd_phy_घातer_off,
	.calibrate	= exynos5_usbdrd_phy_calibrate,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक exynos5_usbdrd_phy_clk_handle(काष्ठा exynos5_usbdrd_phy *phy_drd)
अणु
	अचिन्हित दीर्घ ref_rate;
	पूर्णांक ret;

	phy_drd->clk = devm_clk_get(phy_drd->dev, "phy");
	अगर (IS_ERR(phy_drd->clk)) अणु
		dev_err(phy_drd->dev, "Failed to get phy clock\n");
		वापस PTR_ERR(phy_drd->clk);
	पूर्ण

	phy_drd->ref_clk = devm_clk_get(phy_drd->dev, "ref");
	अगर (IS_ERR(phy_drd->ref_clk)) अणु
		dev_err(phy_drd->dev, "Failed to get phy reference clock\n");
		वापस PTR_ERR(phy_drd->ref_clk);
	पूर्ण
	ref_rate = clk_get_rate(phy_drd->ref_clk);

	ret = exynos5_rate_to_clk(ref_rate, &phy_drd->extrefclk);
	अगर (ret) अणु
		dev_err(phy_drd->dev, "Clock rate (%ld) not supported\n",
			ref_rate);
		वापस ret;
	पूर्ण

	अगर (!phy_drd->drv_data->has_common_clk_gate) अणु
		phy_drd->pipeclk = devm_clk_get(phy_drd->dev, "phy_pipe");
		अगर (IS_ERR(phy_drd->pipeclk)) अणु
			dev_info(phy_drd->dev,
				 "PIPE3 phy operational clock not specified\n");
			phy_drd->pipeclk = शून्य;
		पूर्ण

		phy_drd->uपंचांगiclk = devm_clk_get(phy_drd->dev, "phy_utmi");
		अगर (IS_ERR(phy_drd->uपंचांगiclk)) अणु
			dev_info(phy_drd->dev,
				 "UTMI phy operational clock not specified\n");
			phy_drd->uपंचांगiclk = शून्य;
		पूर्ण

		phy_drd->itpclk = devm_clk_get(phy_drd->dev, "itp");
		अगर (IS_ERR(phy_drd->itpclk)) अणु
			dev_info(phy_drd->dev,
				 "ITP clock from main OSC not specified\n");
			phy_drd->itpclk = शून्य;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा exynos5_usbdrd_phy_config phy_cfg_exynos5[] = अणु
	अणु
		.id		= EXYNOS5_DRDPHY_UTMI,
		.phy_isol	= exynos5_usbdrd_phy_isol,
		.phy_init	= exynos5_usbdrd_uपंचांगi_init,
		.set_refclk	= exynos5_usbdrd_uपंचांगi_set_refclk,
	पूर्ण,
	अणु
		.id		= EXYNOS5_DRDPHY_PIPE3,
		.phy_isol	= exynos5_usbdrd_phy_isol,
		.phy_init	= exynos5_usbdrd_pipe3_init,
		.set_refclk	= exynos5_usbdrd_pipe3_set_refclk,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा exynos5_usbdrd_phy_drvdata exynos5420_usbdrd_phy = अणु
	.phy_cfg		= phy_cfg_exynos5,
	.pmu_offset_usbdrd0_phy	= EXYNOS5_USBDRD_PHY_CONTROL,
	.pmu_offset_usbdrd1_phy	= EXYNOS5420_USBDRD1_PHY_CONTROL,
	.has_common_clk_gate	= true,
पूर्ण;

अटल स्थिर काष्ठा exynos5_usbdrd_phy_drvdata exynos5250_usbdrd_phy = अणु
	.phy_cfg		= phy_cfg_exynos5,
	.pmu_offset_usbdrd0_phy	= EXYNOS5_USBDRD_PHY_CONTROL,
	.has_common_clk_gate	= true,
पूर्ण;

अटल स्थिर काष्ठा exynos5_usbdrd_phy_drvdata exynos5433_usbdrd_phy = अणु
	.phy_cfg		= phy_cfg_exynos5,
	.pmu_offset_usbdrd0_phy	= EXYNOS5_USBDRD_PHY_CONTROL,
	.pmu_offset_usbdrd1_phy	= EXYNOS5433_USBHOST30_PHY_CONTROL,
	.has_common_clk_gate	= false,
पूर्ण;

अटल स्थिर काष्ठा exynos5_usbdrd_phy_drvdata exynos7_usbdrd_phy = अणु
	.phy_cfg		= phy_cfg_exynos5,
	.pmu_offset_usbdrd0_phy	= EXYNOS5_USBDRD_PHY_CONTROL,
	.has_common_clk_gate	= false,
पूर्ण;

अटल स्थिर काष्ठा of_device_id exynos5_usbdrd_phy_of_match[] = अणु
	अणु
		.compatible = "samsung,exynos5250-usbdrd-phy",
		.data = &exynos5250_usbdrd_phy
	पूर्ण, अणु
		.compatible = "samsung,exynos5420-usbdrd-phy",
		.data = &exynos5420_usbdrd_phy
	पूर्ण, अणु
		.compatible = "samsung,exynos5433-usbdrd-phy",
		.data = &exynos5433_usbdrd_phy
	पूर्ण, अणु
		.compatible = "samsung,exynos7-usbdrd-phy",
		.data = &exynos7_usbdrd_phy
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, exynos5_usbdrd_phy_of_match);

अटल पूर्णांक exynos5_usbdrd_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा exynos5_usbdrd_phy *phy_drd;
	काष्ठा phy_provider *phy_provider;
	स्थिर काष्ठा exynos5_usbdrd_phy_drvdata *drv_data;
	काष्ठा regmap *reg_pmu;
	u32 pmu_offset;
	पूर्णांक i, ret;
	पूर्णांक channel;

	phy_drd = devm_kzalloc(dev, माप(*phy_drd), GFP_KERNEL);
	अगर (!phy_drd)
		वापस -ENOMEM;

	dev_set_drvdata(dev, phy_drd);
	phy_drd->dev = dev;

	phy_drd->reg_phy = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(phy_drd->reg_phy))
		वापस PTR_ERR(phy_drd->reg_phy);

	drv_data = of_device_get_match_data(dev);
	अगर (!drv_data)
		वापस -EINVAL;

	phy_drd->drv_data = drv_data;

	ret = exynos5_usbdrd_phy_clk_handle(phy_drd);
	अगर (ret) अणु
		dev_err(dev, "Failed to initialize clocks\n");
		वापस ret;
	पूर्ण

	reg_pmu = syscon_regmap_lookup_by_phandle(dev->of_node,
						   "samsung,pmu-syscon");
	अगर (IS_ERR(reg_pmu)) अणु
		dev_err(dev, "Failed to lookup PMU regmap\n");
		वापस PTR_ERR(reg_pmu);
	पूर्ण

	/*
	 * Exynos5420 SoC has multiple channels क्रम USB 3.0 PHY, with
	 * each having separate घातer control रेजिस्टरs.
	 * 'channel' facilitates to set such रेजिस्टरs.
	 */
	channel = of_alias_get_id(node, "usbdrdphy");
	अगर (channel < 0)
		dev_dbg(dev, "Not a multi-controller usbdrd phy\n");

	चयन (channel) अणु
	हाल 1:
		pmu_offset = phy_drd->drv_data->pmu_offset_usbdrd1_phy;
		अवरोध;
	हाल 0:
	शेष:
		pmu_offset = phy_drd->drv_data->pmu_offset_usbdrd0_phy;
		अवरोध;
	पूर्ण

	/* Get Vbus regulators */
	phy_drd->vbus = devm_regulator_get(dev, "vbus");
	अगर (IS_ERR(phy_drd->vbus)) अणु
		ret = PTR_ERR(phy_drd->vbus);
		अगर (ret == -EPROBE_DEFER)
			वापस ret;

		dev_warn(dev, "Failed to get VBUS supply regulator\n");
		phy_drd->vbus = शून्य;
	पूर्ण

	phy_drd->vbus_boost = devm_regulator_get(dev, "vbus-boost");
	अगर (IS_ERR(phy_drd->vbus_boost)) अणु
		ret = PTR_ERR(phy_drd->vbus_boost);
		अगर (ret == -EPROBE_DEFER)
			वापस ret;

		dev_warn(dev, "Failed to get VBUS boost supply regulator\n");
		phy_drd->vbus_boost = शून्य;
	पूर्ण

	dev_vdbg(dev, "Creating usbdrd_phy phy\n");

	क्रम (i = 0; i < EXYNOS5_DRDPHYS_NUM; i++) अणु
		काष्ठा phy *phy = devm_phy_create(dev, शून्य,
						  &exynos5_usbdrd_phy_ops);
		अगर (IS_ERR(phy)) अणु
			dev_err(dev, "Failed to create usbdrd_phy phy\n");
			वापस PTR_ERR(phy);
		पूर्ण

		phy_drd->phys[i].phy = phy;
		phy_drd->phys[i].index = i;
		phy_drd->phys[i].reg_pmu = reg_pmu;
		phy_drd->phys[i].pmu_offset = pmu_offset;
		phy_drd->phys[i].phy_cfg = &drv_data->phy_cfg[i];
		phy_set_drvdata(phy, &phy_drd->phys[i]);
	पूर्ण

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev,
						     exynos5_usbdrd_phy_xlate);
	अगर (IS_ERR(phy_provider)) अणु
		dev_err(phy_drd->dev, "Failed to register phy provider\n");
		वापस PTR_ERR(phy_provider);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver exynos5_usb3drd_phy = अणु
	.probe	= exynos5_usbdrd_phy_probe,
	.driver = अणु
		.of_match_table	= exynos5_usbdrd_phy_of_match,
		.name		= "exynos5_usb3drd_phy",
		.suppress_bind_attrs = true,
	पूर्ण
पूर्ण;

module_platक्रमm_driver(exynos5_usb3drd_phy);
MODULE_DESCRIPTION("Samsung Exynos5 SoCs USB 3.0 DRD controller PHY driver");
MODULE_AUTHOR("Vivek Gautam <gautam.vivek@samsung.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:exynos5_usb3drd_phy");
