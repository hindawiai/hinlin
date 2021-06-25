<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * phy-zynqmp.c - PHY driver क्रम Xilinx ZynqMP GT.
 *
 * Copyright (C) 2018-2020 Xilinx Inc.
 *
 * Author: Anurag Kumar Vulisha <anuragku@xilinx.com>
 * Author: Subbaraya Sundeep <sundeep.lkml@gmail.com>
 * Author: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *
 * This driver is tested क्रम USB, SATA and Display Port currently.
 * Other controllers PCIe and SGMII should also work but that is
 * experimental as of now.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <dt-bindings/phy/phy.h>

/*
 * Lane Registers
 */

/* TX De-emphasis parameters */
#घोषणा L0_TX_ANA_TM_18			0x0048
#घोषणा L0_TX_ANA_TM_118		0x01d8
#घोषणा L0_TX_ANA_TM_118_FORCE_17_0	BIT(0)

/* DN Resistor calibration code parameters */
#घोषणा L0_TXPMA_ST_3			0x0b0c
#घोषणा L0_DN_CALIB_CODE		0x3f

/* PMA control parameters */
#घोषणा L0_TXPMD_TM_45			0x0cb4
#घोषणा L0_TXPMD_TM_48			0x0cc0
#घोषणा L0_TXPMD_TM_45_OVER_DP_MAIN	BIT(0)
#घोषणा L0_TXPMD_TM_45_ENABLE_DP_MAIN	BIT(1)
#घोषणा L0_TXPMD_TM_45_OVER_DP_POST1	BIT(2)
#घोषणा L0_TXPMD_TM_45_ENABLE_DP_POST1	BIT(3)
#घोषणा L0_TXPMD_TM_45_OVER_DP_POST2	BIT(4)
#घोषणा L0_TXPMD_TM_45_ENABLE_DP_POST2	BIT(5)

/* PCS control parameters */
#घोषणा L0_TM_DIG_6			0x106c
#घोषणा L0_TM_DIS_DESCRAMBLE_DECODER	0x0f
#घोषणा L0_TX_DIG_61			0x00f4
#घोषणा L0_TM_DISABLE_SCRAMBLE_ENCODER	0x0f

/* PLL Test Mode रेजिस्टर parameters */
#घोषणा L0_TM_PLL_DIG_37		0x2094
#घोषणा L0_TM_COARSE_CODE_LIMIT		0x10

/* PLL SSC step size offsets */
#घोषणा L0_PLL_SS_STEPS_0_LSB		0x2368
#घोषणा L0_PLL_SS_STEPS_1_MSB		0x236c
#घोषणा L0_PLL_SS_STEP_SIZE_0_LSB	0x2370
#घोषणा L0_PLL_SS_STEP_SIZE_1		0x2374
#घोषणा L0_PLL_SS_STEP_SIZE_2		0x2378
#घोषणा L0_PLL_SS_STEP_SIZE_3_MSB	0x237c
#घोषणा L0_PLL_STATUS_READ_1		0x23e4

/* SSC step size parameters */
#घोषणा STEP_SIZE_0_MASK		0xff
#घोषणा STEP_SIZE_1_MASK		0xff
#घोषणा STEP_SIZE_2_MASK		0xff
#घोषणा STEP_SIZE_3_MASK		0x3
#घोषणा STEP_SIZE_SHIFT			8
#घोषणा FORCE_STEP_SIZE			0x10
#घोषणा FORCE_STEPS			0x20
#घोषणा STEPS_0_MASK			0xff
#घोषणा STEPS_1_MASK			0x07

/* Reference घड़ी selection parameters */
#घोषणा L0_Ln_REF_CLK_SEL(n)		(0x2860 + (n) * 4)
#घोषणा L0_REF_CLK_SEL_MASK		0x8f

/* Calibration digital logic parameters */
#घोषणा L3_TM_CALIB_DIG19		0xec4c
#घोषणा L3_CALIB_DONE_STATUS		0xef14
#घोषणा L3_TM_CALIB_DIG18		0xec48
#घोषणा L3_TM_CALIB_DIG19_NSW		0x07
#घोषणा L3_TM_CALIB_DIG18_NSW		0xe0
#घोषणा L3_TM_OVERRIDE_NSW_CODE         0x20
#घोषणा L3_CALIB_DONE			0x02
#घोषणा L3_NSW_SHIFT			5
#घोषणा L3_NSW_PIPE_SHIFT		4
#घोषणा L3_NSW_CALIB_SHIFT		3

#घोषणा PHY_REG_OFFSET			0x4000

/*
 * Global Registers
 */

/* Refclk selection parameters */
#घोषणा PLL_REF_SEL(n)			(0x10000 + (n) * 4)
#घोषणा PLL_FREQ_MASK			0x1f
#घोषणा PLL_STATUS_LOCKED		0x10

/* Inter Connect Matrix parameters */
#घोषणा ICM_CFG0			0x10010
#घोषणा ICM_CFG1			0x10014
#घोषणा ICM_CFG0_L0_MASK		0x07
#घोषणा ICM_CFG0_L1_MASK		0x70
#घोषणा ICM_CFG1_L2_MASK		0x07
#घोषणा ICM_CFG2_L3_MASK		0x70
#घोषणा ICM_CFG_SHIFT			4

/* Inter Connect Matrix allowed protocols */
#घोषणा ICM_PROTOCOL_PD			0x0
#घोषणा ICM_PROTOCOL_PCIE		0x1
#घोषणा ICM_PROTOCOL_SATA		0x2
#घोषणा ICM_PROTOCOL_USB		0x3
#घोषणा ICM_PROTOCOL_DP			0x4
#घोषणा ICM_PROTOCOL_SGMII		0x5

/* Test Mode common reset control  parameters */
#घोषणा TM_CMN_RST			0x10018
#घोषणा TM_CMN_RST_EN			0x1
#घोषणा TM_CMN_RST_SET			0x2
#घोषणा TM_CMN_RST_MASK			0x3

/* Bus width parameters */
#घोषणा TX_PROT_BUS_WIDTH		0x10040
#घोषणा RX_PROT_BUS_WIDTH		0x10044
#घोषणा PROT_BUS_WIDTH_10		0x0
#घोषणा PROT_BUS_WIDTH_20		0x1
#घोषणा PROT_BUS_WIDTH_40		0x2
#घोषणा PROT_BUS_WIDTH_SHIFT		2

/* Number of GT lanes */
#घोषणा NUM_LANES			4

/* SIOU SATA control रेजिस्टर */
#घोषणा SATA_CONTROL_OFFSET		0x0100

/* Total number of controllers */
#घोषणा CONTROLLERS_PER_LANE		5

/* Protocol Type parameters */
#घोषणा XPSGTR_TYPE_USB0		0  /* USB controller 0 */
#घोषणा XPSGTR_TYPE_USB1		1  /* USB controller 1 */
#घोषणा XPSGTR_TYPE_SATA_0		2  /* SATA controller lane 0 */
#घोषणा XPSGTR_TYPE_SATA_1		3  /* SATA controller lane 1 */
#घोषणा XPSGTR_TYPE_PCIE_0		4  /* PCIe controller lane 0 */
#घोषणा XPSGTR_TYPE_PCIE_1		5  /* PCIe controller lane 1 */
#घोषणा XPSGTR_TYPE_PCIE_2		6  /* PCIe controller lane 2 */
#घोषणा XPSGTR_TYPE_PCIE_3		7  /* PCIe controller lane 3 */
#घोषणा XPSGTR_TYPE_DP_0		8  /* Display Port controller lane 0 */
#घोषणा XPSGTR_TYPE_DP_1		9  /* Display Port controller lane 1 */
#घोषणा XPSGTR_TYPE_SGMII0		10 /* Ethernet SGMII controller 0 */
#घोषणा XPSGTR_TYPE_SGMII1		11 /* Ethernet SGMII controller 1 */
#घोषणा XPSGTR_TYPE_SGMII2		12 /* Ethernet SGMII controller 2 */
#घोषणा XPSGTR_TYPE_SGMII3		13 /* Ethernet SGMII controller 3 */

/* Timeout values */
#घोषणा TIMEOUT_US			1000

काष्ठा xpsgtr_dev;

/**
 * काष्ठा xpsgtr_ssc - काष्ठाure to hold SSC settings क्रम a lane
 * @refclk_rate: PLL reference घड़ी frequency
 * @pll_ref_clk: value to be written to रेजिस्टर क्रम corresponding ref clk rate
 * @steps: number of steps of SSC (Spपढ़ो Spectrum Clock)
 * @step_size: step size of each step
 */
काष्ठा xpsgtr_ssc अणु
	u32 refclk_rate;
	u8  pll_ref_clk;
	u32 steps;
	u32 step_size;
पूर्ण;

/**
 * काष्ठा xpsgtr_phy - representation of a lane
 * @phy: poपूर्णांकer to the kernel PHY device
 * @type: controller which uses this lane
 * @lane: lane number
 * @protocol: protocol in which the lane operates
 * @skip_phy_init: skip phy_init() अगर true
 * @dev: poपूर्णांकer to the xpsgtr_dev instance
 * @refclk: reference घड़ी index
 */
काष्ठा xpsgtr_phy अणु
	काष्ठा phy *phy;
	u8 type;
	u8 lane;
	u8 protocol;
	bool skip_phy_init;
	काष्ठा xpsgtr_dev *dev;
	अचिन्हित पूर्णांक refclk;
पूर्ण;

/**
 * काष्ठा xpsgtr_dev - representation of a ZynMP GT device
 * @dev: poपूर्णांकer to device
 * @serdes: serdes base address
 * @siou: siou base address
 * @gtr_mutex: mutex क्रम locking
 * @phys: PHY lanes
 * @refclk_sscs: spपढ़ो spectrum settings क्रम the reference घड़ीs
 * @clk: reference घड़ीs
 * @tx_term_fix: fix क्रम GT issue
 * @saved_icm_cfg0: stored value of ICM CFG0 रेजिस्टर
 * @saved_icm_cfg1: stored value of ICM CFG1 रेजिस्टर
 */
काष्ठा xpsgtr_dev अणु
	काष्ठा device *dev;
	व्योम __iomem *serdes;
	व्योम __iomem *siou;
	काष्ठा mutex gtr_mutex; /* mutex क्रम locking */
	काष्ठा xpsgtr_phy phys[NUM_LANES];
	स्थिर काष्ठा xpsgtr_ssc *refclk_sscs[NUM_LANES];
	काष्ठा clk *clk[NUM_LANES];
	bool tx_term_fix;
	अचिन्हित पूर्णांक saved_icm_cfg0;
	अचिन्हित पूर्णांक saved_icm_cfg1;
पूर्ण;

/*
 * Configuration Data
 */

/* lookup table to hold all settings needed क्रम a ref घड़ी frequency */
अटल स्थिर काष्ठा xpsgtr_ssc ssc_lookup[] = अणु
	अणु  19200000, 0x05,  608, 264020 पूर्ण,
	अणु  20000000, 0x06,  634, 243454 पूर्ण,
	अणु  24000000, 0x07,  760, 168973 पूर्ण,
	अणु  26000000, 0x08,  824, 143860 पूर्ण,
	अणु  27000000, 0x09,  856,  86551 पूर्ण,
	अणु  38400000, 0x0a, 1218,  65896 पूर्ण,
	अणु  40000000, 0x0b,  634, 243454 पूर्ण,
	अणु  52000000, 0x0c,  824, 143860 पूर्ण,
	अणु 100000000, 0x0d, 1058,  87533 पूर्ण,
	अणु 108000000, 0x0e,  856,  86551 पूर्ण,
	अणु 125000000, 0x0f,  992, 119497 पूर्ण,
	अणु 135000000, 0x10, 1070,  55393 पूर्ण,
	अणु 150000000, 0x11,  792, 187091 पूर्ण
पूर्ण;

/*
 * I/O Accessors
 */

अटल अंतरभूत u32 xpsgtr_पढ़ो(काष्ठा xpsgtr_dev *gtr_dev, u32 reg)
अणु
	वापस पढ़ोl(gtr_dev->serdes + reg);
पूर्ण

अटल अंतरभूत व्योम xpsgtr_ग_लिखो(काष्ठा xpsgtr_dev *gtr_dev, u32 reg, u32 value)
अणु
	ग_लिखोl(value, gtr_dev->serdes + reg);
पूर्ण

अटल अंतरभूत व्योम xpsgtr_clr_set(काष्ठा xpsgtr_dev *gtr_dev, u32 reg,
				  u32 clr, u32 set)
अणु
	u32 value = xpsgtr_पढ़ो(gtr_dev, reg);

	value &= ~clr;
	value |= set;
	xpsgtr_ग_लिखो(gtr_dev, reg, value);
पूर्ण

अटल अंतरभूत u32 xpsgtr_पढ़ो_phy(काष्ठा xpsgtr_phy *gtr_phy, u32 reg)
अणु
	व्योम __iomem *addr = gtr_phy->dev->serdes
			   + gtr_phy->lane * PHY_REG_OFFSET + reg;

	वापस पढ़ोl(addr);
पूर्ण

अटल अंतरभूत व्योम xpsgtr_ग_लिखो_phy(काष्ठा xpsgtr_phy *gtr_phy,
				    u32 reg, u32 value)
अणु
	व्योम __iomem *addr = gtr_phy->dev->serdes
			   + gtr_phy->lane * PHY_REG_OFFSET + reg;

	ग_लिखोl(value, addr);
पूर्ण

अटल अंतरभूत व्योम xpsgtr_clr_set_phy(काष्ठा xpsgtr_phy *gtr_phy,
				      u32 reg, u32 clr, u32 set)
अणु
	व्योम __iomem *addr = gtr_phy->dev->serdes
			   + gtr_phy->lane * PHY_REG_OFFSET + reg;

	ग_लिखोl((पढ़ोl(addr) & ~clr) | set, addr);
पूर्ण

/*
 * Hardware Configuration
 */

/* Wait क्रम the PLL to lock (with a समयout). */
अटल पूर्णांक xpsgtr_रुको_pll_lock(काष्ठा phy *phy)
अणु
	काष्ठा xpsgtr_phy *gtr_phy = phy_get_drvdata(phy);
	काष्ठा xpsgtr_dev *gtr_dev = gtr_phy->dev;
	अचिन्हित पूर्णांक समयout = TIMEOUT_US;
	पूर्णांक ret;

	dev_dbg(gtr_dev->dev, "Waiting for PLL lock\n");

	जबतक (1) अणु
		u32 reg = xpsgtr_पढ़ो_phy(gtr_phy, L0_PLL_STATUS_READ_1);

		अगर ((reg & PLL_STATUS_LOCKED) == PLL_STATUS_LOCKED) अणु
			ret = 0;
			अवरोध;
		पूर्ण

		अगर (--समयout == 0) अणु
			ret = -ETIMEDOUT;
			अवरोध;
		पूर्ण

		udelay(1);
	पूर्ण

	अगर (ret == -ETIMEDOUT)
		dev_err(gtr_dev->dev,
			"lane %u (type %u, protocol %u): PLL lock timeout\n",
			gtr_phy->lane, gtr_phy->type, gtr_phy->protocol);

	वापस ret;
पूर्ण

/* Configure PLL and spपढ़ो-sprectrum घड़ी. */
अटल व्योम xpsgtr_configure_pll(काष्ठा xpsgtr_phy *gtr_phy)
अणु
	स्थिर काष्ठा xpsgtr_ssc *ssc;
	u32 step_size;

	ssc = gtr_phy->dev->refclk_sscs[gtr_phy->refclk];
	step_size = ssc->step_size;

	xpsgtr_clr_set(gtr_phy->dev, PLL_REF_SEL(gtr_phy->lane),
		       PLL_FREQ_MASK, ssc->pll_ref_clk);

	/* Enable lane घड़ी sharing, अगर required */
	अगर (gtr_phy->refclk != gtr_phy->lane) अणु
		/* Lane3 Ref Clock Selection Register */
		xpsgtr_clr_set(gtr_phy->dev, L0_Ln_REF_CLK_SEL(gtr_phy->lane),
			       L0_REF_CLK_SEL_MASK, 1 << gtr_phy->refclk);
	पूर्ण

	/* SSC step size [7:0] */
	xpsgtr_clr_set_phy(gtr_phy, L0_PLL_SS_STEP_SIZE_0_LSB,
			   STEP_SIZE_0_MASK, step_size & STEP_SIZE_0_MASK);

	/* SSC step size [15:8] */
	step_size >>= STEP_SIZE_SHIFT;
	xpsgtr_clr_set_phy(gtr_phy, L0_PLL_SS_STEP_SIZE_1,
			   STEP_SIZE_1_MASK, step_size & STEP_SIZE_1_MASK);

	/* SSC step size [23:16] */
	step_size >>= STEP_SIZE_SHIFT;
	xpsgtr_clr_set_phy(gtr_phy, L0_PLL_SS_STEP_SIZE_2,
			   STEP_SIZE_2_MASK, step_size & STEP_SIZE_2_MASK);

	/* SSC steps [7:0] */
	xpsgtr_clr_set_phy(gtr_phy, L0_PLL_SS_STEPS_0_LSB,
			   STEPS_0_MASK, ssc->steps & STEPS_0_MASK);

	/* SSC steps [10:8] */
	xpsgtr_clr_set_phy(gtr_phy, L0_PLL_SS_STEPS_1_MSB,
			   STEPS_1_MASK,
			   (ssc->steps >> STEP_SIZE_SHIFT) & STEPS_1_MASK);

	/* SSC step size [24:25] */
	step_size >>= STEP_SIZE_SHIFT;
	xpsgtr_clr_set_phy(gtr_phy, L0_PLL_SS_STEP_SIZE_3_MSB,
			   STEP_SIZE_3_MASK, (step_size & STEP_SIZE_3_MASK) |
			   FORCE_STEP_SIZE | FORCE_STEPS);
पूर्ण

/* Configure the lane protocol. */
अटल व्योम xpsgtr_lane_set_protocol(काष्ठा xpsgtr_phy *gtr_phy)
अणु
	काष्ठा xpsgtr_dev *gtr_dev = gtr_phy->dev;
	u8 protocol = gtr_phy->protocol;

	चयन (gtr_phy->lane) अणु
	हाल 0:
		xpsgtr_clr_set(gtr_dev, ICM_CFG0, ICM_CFG0_L0_MASK, protocol);
		अवरोध;
	हाल 1:
		xpsgtr_clr_set(gtr_dev, ICM_CFG0, ICM_CFG0_L1_MASK,
			       protocol << ICM_CFG_SHIFT);
		अवरोध;
	हाल 2:
		xpsgtr_clr_set(gtr_dev, ICM_CFG1, ICM_CFG0_L0_MASK, protocol);
		अवरोध;
	हाल 3:
		xpsgtr_clr_set(gtr_dev, ICM_CFG1, ICM_CFG0_L1_MASK,
			       protocol << ICM_CFG_SHIFT);
		अवरोध;
	शेष:
		/* We alपढ़ोy checked 0 <= lane <= 3 */
		अवरोध;
	पूर्ण
पूर्ण

/* Bypass (de)scrambler and 8b/10b decoder and encoder. */
अटल व्योम xpsgtr_bypass_scrambler_8b10b(काष्ठा xpsgtr_phy *gtr_phy)
अणु
	xpsgtr_ग_लिखो_phy(gtr_phy, L0_TM_DIG_6, L0_TM_DIS_DESCRAMBLE_DECODER);
	xpsgtr_ग_लिखो_phy(gtr_phy, L0_TX_DIG_61, L0_TM_DISABLE_SCRAMBLE_ENCODER);
पूर्ण

/* DP-specअगरic initialization. */
अटल व्योम xpsgtr_phy_init_dp(काष्ठा xpsgtr_phy *gtr_phy)
अणु
	xpsgtr_ग_लिखो_phy(gtr_phy, L0_TXPMD_TM_45,
			 L0_TXPMD_TM_45_OVER_DP_MAIN |
			 L0_TXPMD_TM_45_ENABLE_DP_MAIN |
			 L0_TXPMD_TM_45_OVER_DP_POST1 |
			 L0_TXPMD_TM_45_OVER_DP_POST2 |
			 L0_TXPMD_TM_45_ENABLE_DP_POST2);
	xpsgtr_ग_लिखो_phy(gtr_phy, L0_TX_ANA_TM_118,
			 L0_TX_ANA_TM_118_FORCE_17_0);
पूर्ण

/* SATA-specअगरic initialization. */
अटल व्योम xpsgtr_phy_init_sata(काष्ठा xpsgtr_phy *gtr_phy)
अणु
	काष्ठा xpsgtr_dev *gtr_dev = gtr_phy->dev;

	xpsgtr_bypass_scrambler_8b10b(gtr_phy);

	ग_लिखोl(gtr_phy->lane, gtr_dev->siou + SATA_CONTROL_OFFSET);
पूर्ण

/* SGMII-specअगरic initialization. */
अटल व्योम xpsgtr_phy_init_sgmii(काष्ठा xpsgtr_phy *gtr_phy)
अणु
	काष्ठा xpsgtr_dev *gtr_dev = gtr_phy->dev;

	/* Set SGMII protocol TX and RX bus width to 10 bits. */
	xpsgtr_ग_लिखो(gtr_dev, TX_PROT_BUS_WIDTH,
		     PROT_BUS_WIDTH_10 << (gtr_phy->lane * PROT_BUS_WIDTH_SHIFT));
	xpsgtr_ग_लिखो(gtr_dev, RX_PROT_BUS_WIDTH,
		     PROT_BUS_WIDTH_10 << (gtr_phy->lane * PROT_BUS_WIDTH_SHIFT));

	xpsgtr_bypass_scrambler_8b10b(gtr_phy);
पूर्ण

/* Configure TX de-emphasis and margining क्रम DP. */
अटल व्योम xpsgtr_phy_configure_dp(काष्ठा xpsgtr_phy *gtr_phy, अचिन्हित पूर्णांक pre,
				    अचिन्हित पूर्णांक voltage)
अणु
	अटल स्थिर u8 voltage_swing[4][4] = अणु
		अणु 0x2a, 0x27, 0x24, 0x20 पूर्ण,
		अणु 0x27, 0x23, 0x20, 0xff पूर्ण,
		अणु 0x24, 0x20, 0xff, 0xff पूर्ण,
		अणु 0xff, 0xff, 0xff, 0xff पूर्ण
	पूर्ण;
	अटल स्थिर u8 pre_emphasis[4][4] = अणु
		अणु 0x02, 0x02, 0x02, 0x02 पूर्ण,
		अणु 0x01, 0x01, 0x01, 0xff पूर्ण,
		अणु 0x00, 0x00, 0xff, 0xff पूर्ण,
		अणु 0xff, 0xff, 0xff, 0xff पूर्ण
	पूर्ण;

	xpsgtr_ग_लिखो_phy(gtr_phy, L0_TXPMD_TM_48, voltage_swing[pre][voltage]);
	xpsgtr_ग_लिखो_phy(gtr_phy, L0_TX_ANA_TM_18, pre_emphasis[pre][voltage]);
पूर्ण

/*
 * PHY Operations
 */

अटल bool xpsgtr_phy_init_required(काष्ठा xpsgtr_phy *gtr_phy)
अणु
	/*
	 * As USB may save the snapshot of the states during hibernation, करोing
	 * phy_init() will put the USB controller पूर्णांकo reset, resulting in the
	 * losing of the saved snapshot. So try to aव्योम phy_init() क्रम USB
	 * except when gtr_phy->skip_phy_init is false (this happens when FPD is
	 * shutकरोwn during suspend or when gt lane is changed from current one)
	 */
	अगर (gtr_phy->protocol == ICM_PROTOCOL_USB && gtr_phy->skip_phy_init)
		वापस false;
	अन्यथा
		वापस true;
पूर्ण

/*
 * There is a functional issue in the GT. The TX termination resistance can be
 * out of spec due to a issue in the calibration logic. This is the workaround
 * to fix it, required क्रम XCZU9EG silicon.
 */
अटल पूर्णांक xpsgtr_phy_tx_term_fix(काष्ठा xpsgtr_phy *gtr_phy)
अणु
	काष्ठा xpsgtr_dev *gtr_dev = gtr_phy->dev;
	u32 समयout = TIMEOUT_US;
	u32 nsw;

	/* Enabling Test Mode control क्रम CMN Rest */
	xpsgtr_clr_set(gtr_dev, TM_CMN_RST, TM_CMN_RST_MASK, TM_CMN_RST_SET);

	/* Set Test Mode reset */
	xpsgtr_clr_set(gtr_dev, TM_CMN_RST, TM_CMN_RST_MASK, TM_CMN_RST_EN);

	xpsgtr_ग_लिखो(gtr_dev, L3_TM_CALIB_DIG18, 0x00);
	xpsgtr_ग_लिखो(gtr_dev, L3_TM_CALIB_DIG19, L3_TM_OVERRIDE_NSW_CODE);

	/*
	 * As a part of work around sequence क्रम PMOS calibration fix,
	 * we need to configure any lane ICM_CFG to valid protocol. This
	 * will deनिश्चित the CMN_Resetn संकेत.
	 */
	xpsgtr_lane_set_protocol(gtr_phy);

	/* Clear Test Mode reset */
	xpsgtr_clr_set(gtr_dev, TM_CMN_RST, TM_CMN_RST_MASK, TM_CMN_RST_SET);

	dev_dbg(gtr_dev->dev, "calibrating...\n");

	करो अणु
		u32 reg = xpsgtr_पढ़ो(gtr_dev, L3_CALIB_DONE_STATUS);

		अगर ((reg & L3_CALIB_DONE) == L3_CALIB_DONE)
			अवरोध;

		अगर (!--समयout) अणु
			dev_err(gtr_dev->dev, "calibration time out\n");
			वापस -ETIMEDOUT;
		पूर्ण

		udelay(1);
	पूर्ण जबतक (समयout > 0);

	dev_dbg(gtr_dev->dev, "calibration done\n");

	/* Reading NMOS Register Code */
	nsw = xpsgtr_पढ़ो(gtr_dev, L0_TXPMA_ST_3) & L0_DN_CALIB_CODE;

	/* Set Test Mode reset */
	xpsgtr_clr_set(gtr_dev, TM_CMN_RST, TM_CMN_RST_MASK, TM_CMN_RST_EN);

	/* Writing NMOS रेजिस्टर values back [5:3] */
	xpsgtr_ग_लिखो(gtr_dev, L3_TM_CALIB_DIG19, nsw >> L3_NSW_CALIB_SHIFT);

	/* Writing NMOS रेजिस्टर value [2:0] */
	xpsgtr_ग_लिखो(gtr_dev, L3_TM_CALIB_DIG18,
		     ((nsw & L3_TM_CALIB_DIG19_NSW) << L3_NSW_SHIFT) |
		     (1 << L3_NSW_PIPE_SHIFT));

	/* Clear Test Mode reset */
	xpsgtr_clr_set(gtr_dev, TM_CMN_RST, TM_CMN_RST_MASK, TM_CMN_RST_SET);

	वापस 0;
पूर्ण

अटल पूर्णांक xpsgtr_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा xpsgtr_phy *gtr_phy = phy_get_drvdata(phy);
	काष्ठा xpsgtr_dev *gtr_dev = gtr_phy->dev;
	पूर्णांक ret = 0;

	mutex_lock(&gtr_dev->gtr_mutex);

	/* Skip initialization अगर not required. */
	अगर (!xpsgtr_phy_init_required(gtr_phy))
		जाओ out;

	अगर (gtr_dev->tx_term_fix) अणु
		ret = xpsgtr_phy_tx_term_fix(gtr_phy);
		अगर (ret < 0)
			जाओ out;

		gtr_dev->tx_term_fix = false;
	पूर्ण

	/* Enable coarse code saturation limiting logic. */
	xpsgtr_ग_लिखो_phy(gtr_phy, L0_TM_PLL_DIG_37, L0_TM_COARSE_CODE_LIMIT);

	/*
	 * Configure the PLL, the lane protocol, and perक्रमm protocol-specअगरic
	 * initialization.
	 */
	xpsgtr_configure_pll(gtr_phy);
	xpsgtr_lane_set_protocol(gtr_phy);

	चयन (gtr_phy->protocol) अणु
	हाल ICM_PROTOCOL_DP:
		xpsgtr_phy_init_dp(gtr_phy);
		अवरोध;

	हाल ICM_PROTOCOL_SATA:
		xpsgtr_phy_init_sata(gtr_phy);
		अवरोध;

	हाल ICM_PROTOCOL_SGMII:
		xpsgtr_phy_init_sgmii(gtr_phy);
		अवरोध;
	पूर्ण

out:
	mutex_unlock(&gtr_dev->gtr_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक xpsgtr_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा xpsgtr_phy *gtr_phy = phy_get_drvdata(phy);

	gtr_phy->skip_phy_init = false;

	वापस 0;
पूर्ण

अटल पूर्णांक xpsgtr_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा xpsgtr_phy *gtr_phy = phy_get_drvdata(phy);
	पूर्णांक ret = 0;

	/*
	 * Wait क्रम the PLL to lock. For DP, only रुको on DP0 to aव्योम
	 * cumulating रुकोs क्रम both lanes. The user is expected to initialize
	 * lane 0 last.
	 */
	अगर (gtr_phy->protocol != ICM_PROTOCOL_DP ||
	    gtr_phy->type == XPSGTR_TYPE_DP_0)
		ret = xpsgtr_रुको_pll_lock(phy);

	वापस ret;
पूर्ण

अटल पूर्णांक xpsgtr_phy_configure(काष्ठा phy *phy, जोड़ phy_configure_opts *opts)
अणु
	काष्ठा xpsgtr_phy *gtr_phy = phy_get_drvdata(phy);

	अगर (gtr_phy->protocol != ICM_PROTOCOL_DP)
		वापस 0;

	xpsgtr_phy_configure_dp(gtr_phy, opts->dp.pre[0], opts->dp.voltage[0]);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops xpsgtr_phyops = अणु
	.init		= xpsgtr_phy_init,
	.निकास		= xpsgtr_phy_निकास,
	.घातer_on	= xpsgtr_phy_घातer_on,
	.configure	= xpsgtr_phy_configure,
	.owner		= THIS_MODULE,
पूर्ण;

/*
 * OF Xlate Support
 */

/* Set the lane type and protocol based on the PHY type and instance number. */
अटल पूर्णांक xpsgtr_set_lane_type(काष्ठा xpsgtr_phy *gtr_phy, u8 phy_type,
				अचिन्हित पूर्णांक phy_instance)
अणु
	अचिन्हित पूर्णांक num_phy_types;
	स्थिर पूर्णांक *phy_types;

	चयन (phy_type) अणु
	हाल PHY_TYPE_SATA: अणु
		अटल स्थिर पूर्णांक types[] = अणु
			XPSGTR_TYPE_SATA_0,
			XPSGTR_TYPE_SATA_1,
		पूर्ण;

		phy_types = types;
		num_phy_types = ARRAY_SIZE(types);
		gtr_phy->protocol = ICM_PROTOCOL_SATA;
		अवरोध;
	पूर्ण
	हाल PHY_TYPE_USB3: अणु
		अटल स्थिर पूर्णांक types[] = अणु
			XPSGTR_TYPE_USB0,
			XPSGTR_TYPE_USB1,
		पूर्ण;

		phy_types = types;
		num_phy_types = ARRAY_SIZE(types);
		gtr_phy->protocol = ICM_PROTOCOL_USB;
		अवरोध;
	पूर्ण
	हाल PHY_TYPE_DP: अणु
		अटल स्थिर पूर्णांक types[] = अणु
			XPSGTR_TYPE_DP_0,
			XPSGTR_TYPE_DP_1,
		पूर्ण;

		phy_types = types;
		num_phy_types = ARRAY_SIZE(types);
		gtr_phy->protocol = ICM_PROTOCOL_DP;
		अवरोध;
	पूर्ण
	हाल PHY_TYPE_PCIE: अणु
		अटल स्थिर पूर्णांक types[] = अणु
			XPSGTR_TYPE_PCIE_0,
			XPSGTR_TYPE_PCIE_1,
			XPSGTR_TYPE_PCIE_2,
			XPSGTR_TYPE_PCIE_3,
		पूर्ण;

		phy_types = types;
		num_phy_types = ARRAY_SIZE(types);
		gtr_phy->protocol = ICM_PROTOCOL_PCIE;
		अवरोध;
	पूर्ण
	हाल PHY_TYPE_SGMII: अणु
		अटल स्थिर पूर्णांक types[] = अणु
			XPSGTR_TYPE_SGMII0,
			XPSGTR_TYPE_SGMII1,
			XPSGTR_TYPE_SGMII2,
			XPSGTR_TYPE_SGMII3,
		पूर्ण;

		phy_types = types;
		num_phy_types = ARRAY_SIZE(types);
		gtr_phy->protocol = ICM_PROTOCOL_SGMII;
		अवरोध;
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (phy_instance >= num_phy_types)
		वापस -EINVAL;

	gtr_phy->type = phy_types[phy_instance];
	वापस 0;
पूर्ण

/*
 * Valid combinations of controllers and lanes (Interconnect Matrix).
 */
अटल स्थिर अचिन्हित पूर्णांक icm_matrix[NUM_LANES][CONTROLLERS_PER_LANE] = अणु
	अणु XPSGTR_TYPE_PCIE_0, XPSGTR_TYPE_SATA_0, XPSGTR_TYPE_USB0,
		XPSGTR_TYPE_DP_1, XPSGTR_TYPE_SGMII0 पूर्ण,
	अणु XPSGTR_TYPE_PCIE_1, XPSGTR_TYPE_SATA_1, XPSGTR_TYPE_USB0,
		XPSGTR_TYPE_DP_0, XPSGTR_TYPE_SGMII1 पूर्ण,
	अणु XPSGTR_TYPE_PCIE_2, XPSGTR_TYPE_SATA_0, XPSGTR_TYPE_USB0,
		XPSGTR_TYPE_DP_1, XPSGTR_TYPE_SGMII2 पूर्ण,
	अणु XPSGTR_TYPE_PCIE_3, XPSGTR_TYPE_SATA_1, XPSGTR_TYPE_USB1,
		XPSGTR_TYPE_DP_0, XPSGTR_TYPE_SGMII3 पूर्ण
पूर्ण;

/* Translate OF phandle and args to PHY instance. */
अटल काष्ठा phy *xpsgtr_xlate(काष्ठा device *dev,
				काष्ठा of_phandle_args *args)
अणु
	काष्ठा xpsgtr_dev *gtr_dev = dev_get_drvdata(dev);
	काष्ठा xpsgtr_phy *gtr_phy;
	अचिन्हित पूर्णांक phy_instance;
	अचिन्हित पूर्णांक phy_lane;
	अचिन्हित पूर्णांक phy_type;
	अचिन्हित पूर्णांक refclk;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (args->args_count != 4) अणु
		dev_err(dev, "Invalid number of cells in 'phy' property\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/*
	 * Get the PHY parameters from the OF arguments and derive the lane
	 * type.
	 */
	phy_lane = args->args[0];
	अगर (phy_lane >= ARRAY_SIZE(gtr_dev->phys)) अणु
		dev_err(dev, "Invalid lane number %u\n", phy_lane);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	gtr_phy = &gtr_dev->phys[phy_lane];
	phy_type = args->args[1];
	phy_instance = args->args[2];

	ret = xpsgtr_set_lane_type(gtr_phy, phy_type, phy_instance);
	अगर (ret < 0) अणु
		dev_err(gtr_dev->dev, "Invalid PHY type and/or instance\n");
		वापस ERR_PTR(ret);
	पूर्ण

	refclk = args->args[3];
	अगर (refclk >= ARRAY_SIZE(gtr_dev->refclk_sscs) ||
	    !gtr_dev->refclk_sscs[refclk]) अणु
		dev_err(dev, "Invalid reference clock number %u\n", refclk);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	gtr_phy->refclk = refclk;

	/*
	 * Ensure that the Interconnect Matrix is obeyed, i.e a given lane type
	 * is allowed to operate on the lane.
	 */
	क्रम (i = 0; i < CONTROLLERS_PER_LANE; i++) अणु
		अगर (icm_matrix[phy_lane][i] == gtr_phy->type)
			वापस gtr_phy->phy;
	पूर्ण

	वापस ERR_PTR(-EINVAL);
पूर्ण

/*
 * Power Management
 */

अटल पूर्णांक __maybe_unused xpsgtr_suspend(काष्ठा device *dev)
अणु
	काष्ठा xpsgtr_dev *gtr_dev = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक i;

	/* Save the snapshot ICM_CFG रेजिस्टरs. */
	gtr_dev->saved_icm_cfg0 = xpsgtr_पढ़ो(gtr_dev, ICM_CFG0);
	gtr_dev->saved_icm_cfg1 = xpsgtr_पढ़ो(gtr_dev, ICM_CFG1);

	क्रम (i = 0; i < ARRAY_SIZE(gtr_dev->clk); i++)
		clk_disable_unprepare(gtr_dev->clk[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused xpsgtr_resume(काष्ठा device *dev)
अणु
	काष्ठा xpsgtr_dev *gtr_dev = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक icm_cfg0, icm_cfg1;
	अचिन्हित पूर्णांक i;
	bool skip_phy_init;
	पूर्णांक err;

	क्रम (i = 0; i < ARRAY_SIZE(gtr_dev->clk); i++) अणु
		err = clk_prepare_enable(gtr_dev->clk[i]);
		अगर (err)
			जाओ err_clk_put;
	पूर्ण

	icm_cfg0 = xpsgtr_पढ़ो(gtr_dev, ICM_CFG0);
	icm_cfg1 = xpsgtr_पढ़ो(gtr_dev, ICM_CFG1);

	/* Return अगर no GT lanes got configured beक्रमe suspend. */
	अगर (!gtr_dev->saved_icm_cfg0 && !gtr_dev->saved_icm_cfg1)
		वापस 0;

	/* Check अगर the ICM configurations changed after suspend. */
	अगर (icm_cfg0 == gtr_dev->saved_icm_cfg0 &&
	    icm_cfg1 == gtr_dev->saved_icm_cfg1)
		skip_phy_init = true;
	अन्यथा
		skip_phy_init = false;

	/* Update the skip_phy_init क्रम all gtr_phy instances. */
	क्रम (i = 0; i < ARRAY_SIZE(gtr_dev->phys); i++)
		gtr_dev->phys[i].skip_phy_init = skip_phy_init;

	वापस 0;

err_clk_put:
	जबतक (i--)
		clk_disable_unprepare(gtr_dev->clk[i]);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops xpsgtr_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(xpsgtr_suspend, xpsgtr_resume)
पूर्ण;

/*
 * Probe & Platक्रमm Driver
 */

अटल पूर्णांक xpsgtr_get_ref_घड़ीs(काष्ठा xpsgtr_dev *gtr_dev)
अणु
	अचिन्हित पूर्णांक refclk;
	पूर्णांक ret;

	क्रम (refclk = 0; refclk < ARRAY_SIZE(gtr_dev->refclk_sscs); ++refclk) अणु
		अचिन्हित दीर्घ rate;
		अचिन्हित पूर्णांक i;
		काष्ठा clk *clk;
		अक्षर name[8];

		snम_लिखो(name, माप(name), "ref%u", refclk);
		clk = devm_clk_get_optional(gtr_dev->dev, name);
		अगर (IS_ERR(clk)) अणु
			ret = dev_err_probe(gtr_dev->dev, PTR_ERR(clk),
					    "Failed to get reference clock %u\n",
					    refclk);
			जाओ err_clk_put;
		पूर्ण

		अगर (!clk)
			जारी;

		ret = clk_prepare_enable(clk);
		अगर (ret)
			जाओ err_clk_put;

		gtr_dev->clk[refclk] = clk;

		/*
		 * Get the spपढ़ो spectrum (SSC) settings क्रम the reference
		 * घड़ी rate.
		 */
		rate = clk_get_rate(clk);

		क्रम (i = 0 ; i < ARRAY_SIZE(ssc_lookup); i++) अणु
			अगर (rate == ssc_lookup[i].refclk_rate) अणु
				gtr_dev->refclk_sscs[refclk] = &ssc_lookup[i];
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (i == ARRAY_SIZE(ssc_lookup)) अणु
			dev_err(gtr_dev->dev,
				"Invalid rate %lu for reference clock %u\n",
				rate, refclk);
			ret = -EINVAL;
			जाओ err_clk_put;
		पूर्ण
	पूर्ण

	वापस 0;

err_clk_put:
	जबतक (refclk--)
		clk_disable_unprepare(gtr_dev->clk[refclk]);

	वापस ret;
पूर्ण

अटल पूर्णांक xpsgtr_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा xpsgtr_dev *gtr_dev;
	काष्ठा phy_provider *provider;
	अचिन्हित पूर्णांक port;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	gtr_dev = devm_kzalloc(&pdev->dev, माप(*gtr_dev), GFP_KERNEL);
	अगर (!gtr_dev)
		वापस -ENOMEM;

	gtr_dev->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, gtr_dev);

	mutex_init(&gtr_dev->gtr_mutex);

	अगर (of_device_is_compatible(np, "xlnx,zynqmp-psgtr"))
		gtr_dev->tx_term_fix =
			of_property_पढ़ो_bool(np, "xlnx,tx-termination-fix");

	/* Acquire resources. */
	gtr_dev->serdes = devm_platक्रमm_ioremap_resource_byname(pdev, "serdes");
	अगर (IS_ERR(gtr_dev->serdes))
		वापस PTR_ERR(gtr_dev->serdes);

	gtr_dev->siou = devm_platक्रमm_ioremap_resource_byname(pdev, "siou");
	अगर (IS_ERR(gtr_dev->siou))
		वापस PTR_ERR(gtr_dev->siou);

	ret = xpsgtr_get_ref_घड़ीs(gtr_dev);
	अगर (ret)
		वापस ret;

	/* Create PHYs. */
	क्रम (port = 0; port < ARRAY_SIZE(gtr_dev->phys); ++port) अणु
		काष्ठा xpsgtr_phy *gtr_phy = &gtr_dev->phys[port];
		काष्ठा phy *phy;

		gtr_phy->lane = port;
		gtr_phy->dev = gtr_dev;

		phy = devm_phy_create(&pdev->dev, np, &xpsgtr_phyops);
		अगर (IS_ERR(phy)) अणु
			dev_err(&pdev->dev, "failed to create PHY\n");
			ret = PTR_ERR(phy);
			जाओ err_clk_put;
		पूर्ण

		gtr_phy->phy = phy;
		phy_set_drvdata(phy, gtr_phy);
	पूर्ण

	/* Register the PHY provider. */
	provider = devm_of_phy_provider_रेजिस्टर(&pdev->dev, xpsgtr_xlate);
	अगर (IS_ERR(provider)) अणु
		dev_err(&pdev->dev, "registering provider failed\n");
		ret = PTR_ERR(provider);
		जाओ err_clk_put;
	पूर्ण
	वापस 0;

err_clk_put:
	क्रम (i = 0; i < ARRAY_SIZE(gtr_dev->clk); i++)
		clk_disable_unprepare(gtr_dev->clk[i]);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id xpsgtr_of_match[] = अणु
	अणु .compatible = "xlnx,zynqmp-psgtr", पूर्ण,
	अणु .compatible = "xlnx,zynqmp-psgtr-v1.1", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xpsgtr_of_match);

अटल काष्ठा platक्रमm_driver xpsgtr_driver = अणु
	.probe = xpsgtr_probe,
	.driver = अणु
		.name = "xilinx-psgtr",
		.of_match_table	= xpsgtr_of_match,
		.pm =  &xpsgtr_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(xpsgtr_driver);

MODULE_AUTHOR("Xilinx Inc.");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Xilinx ZynqMP High speed Gigabit Transceiver");
