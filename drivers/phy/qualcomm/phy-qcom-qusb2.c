<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2017, 2019, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>

#समावेश <dt-bindings/phy/phy-qcom-qusb2.h>

#घोषणा QUSB2PHY_PLL			0x0
#घोषणा QUSB2PHY_PLL_TEST		0x04
#घोषणा CLK_REF_SEL			BIT(7)

#घोषणा QUSB2PHY_PLL_TUNE		0x08
#घोषणा QUSB2PHY_PLL_USER_CTL1		0x0c
#घोषणा QUSB2PHY_PLL_USER_CTL2		0x10
#घोषणा QUSB2PHY_PLL_AUTOPGM_CTL1	0x1c
#घोषणा QUSB2PHY_PLL_PWR_CTRL		0x18

/* QUSB2PHY_PLL_STATUS रेजिस्टर bits */
#घोषणा PLL_LOCKED			BIT(5)

/* QUSB2PHY_PLL_COMMON_STATUS_ONE रेजिस्टर bits */
#घोषणा CORE_READY_STATUS		BIT(0)

/* QUSB2PHY_PORT_POWERDOWN रेजिस्टर bits */
#घोषणा CLAMP_N_EN			BIT(5)
#घोषणा FREEZIO_N			BIT(1)
#घोषणा POWER_DOWN			BIT(0)

/* QUSB2PHY_PWR_CTRL1 रेजिस्टर bits */
#घोषणा PWR_CTRL1_VREF_SUPPLY_TRIM	BIT(5)
#घोषणा PWR_CTRL1_CLAMP_N_EN		BIT(1)

#घोषणा QUSB2PHY_REFCLK_ENABLE		BIT(0)

#घोषणा PHY_CLK_SCHEME_SEL		BIT(0)

/* QUSB2PHY_INTR_CTRL रेजिस्टर bits */
#घोषणा DMSE_INTR_HIGH_SEL			BIT(4)
#घोषणा DPSE_INTR_HIGH_SEL			BIT(3)
#घोषणा CHG_DET_INTR_EN				BIT(2)
#घोषणा DMSE_INTR_EN				BIT(1)
#घोषणा DPSE_INTR_EN				BIT(0)

/* QUSB2PHY_PLL_CORE_INPUT_OVERRIDE रेजिस्टर bits */
#घोषणा CORE_PLL_EN_FROM_RESET			BIT(4)
#घोषणा CORE_RESET				BIT(5)
#घोषणा CORE_RESET_MUX				BIT(6)

/* QUSB2PHY_IMP_CTRL1 रेजिस्टर bits */
#घोषणा IMP_RES_OFFSET_MASK			GENMASK(5, 0)
#घोषणा IMP_RES_OFFSET_SHIFT			0x0

/* QUSB2PHY_PLL_BIAS_CONTROL_2 रेजिस्टर bits */
#घोषणा BIAS_CTRL2_RES_OFFSET_MASK		GENMASK(5, 0)
#घोषणा BIAS_CTRL2_RES_OFFSET_SHIFT		0x0

/* QUSB2PHY_CHG_CONTROL_2 रेजिस्टर bits */
#घोषणा CHG_CTRL2_OFFSET_MASK			GENMASK(5, 4)
#घोषणा CHG_CTRL2_OFFSET_SHIFT			0x4

/* QUSB2PHY_PORT_TUNE1 रेजिस्टर bits */
#घोषणा HSTX_TRIM_MASK				GENMASK(7, 4)
#घोषणा HSTX_TRIM_SHIFT				0x4
#घोषणा PREEMPH_WIDTH_HALF_BIT			BIT(2)
#घोषणा PREEMPHASIS_EN_MASK			GENMASK(1, 0)
#घोषणा PREEMPHASIS_EN_SHIFT			0x0

/* QUSB2PHY_PORT_TUNE2 रेजिस्टर bits */
#घोषणा HSDISC_TRIM_MASK			GENMASK(1, 0)
#घोषणा HSDISC_TRIM_SHIFT			0x0

#घोषणा QUSB2PHY_PLL_ANALOG_CONTROLS_TWO	0x04
#घोषणा QUSB2PHY_PLL_CLOCK_INVERTERS		0x18c
#घोषणा QUSB2PHY_PLL_CMODE			0x2c
#घोषणा QUSB2PHY_PLL_LOCK_DELAY			0x184
#घोषणा QUSB2PHY_PLL_DIGITAL_TIMERS_TWO		0xb4
#घोषणा QUSB2PHY_PLL_BIAS_CONTROL_1		0x194
#घोषणा QUSB2PHY_PLL_BIAS_CONTROL_2		0x198
#घोषणा QUSB2PHY_PWR_CTRL2			0x214
#घोषणा QUSB2PHY_IMP_CTRL1			0x220
#घोषणा QUSB2PHY_IMP_CTRL2			0x224
#घोषणा QUSB2PHY_CHG_CTRL2			0x23c

काष्ठा qusb2_phy_init_tbl अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक val;
	/*
	 * रेजिस्टर part of layout ?
	 * अगर yes, then offset gives index in the reg-layout
	 */
	पूर्णांक in_layout;
पूर्ण;

#घोषणा QUSB2_PHY_INIT_CFG(o, v) \
	अणु			\
		.offset = o,	\
		.val = v,	\
	पूर्ण

#घोषणा QUSB2_PHY_INIT_CFG_L(o, v) \
	अणु			\
		.offset = o,	\
		.val = v,	\
		.in_layout = 1,	\
	पूर्ण

/* set of रेजिस्टरs with offsets dअगरferent per-PHY */
क्रमागत qusb2phy_reg_layout अणु
	QUSB2PHY_PLL_CORE_INPUT_OVERRIDE,
	QUSB2PHY_PLL_STATUS,
	QUSB2PHY_PORT_TUNE1,
	QUSB2PHY_PORT_TUNE2,
	QUSB2PHY_PORT_TUNE3,
	QUSB2PHY_PORT_TUNE4,
	QUSB2PHY_PORT_TUNE5,
	QUSB2PHY_PORT_TEST1,
	QUSB2PHY_PORT_TEST2,
	QUSB2PHY_PORT_POWERDOWN,
	QUSB2PHY_INTR_CTRL,
पूर्ण;

अटल स्थिर काष्ठा qusb2_phy_init_tbl ipq6018_init_tbl[] = अणु
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PLL, 0x14),
	QUSB2_PHY_INIT_CFG_L(QUSB2PHY_PORT_TUNE1, 0xF8),
	QUSB2_PHY_INIT_CFG_L(QUSB2PHY_PORT_TUNE2, 0xB3),
	QUSB2_PHY_INIT_CFG_L(QUSB2PHY_PORT_TUNE3, 0x83),
	QUSB2_PHY_INIT_CFG_L(QUSB2PHY_PORT_TUNE4, 0xC0),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PLL_TUNE, 0x30),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PLL_USER_CTL1, 0x79),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PLL_USER_CTL2, 0x21),
	QUSB2_PHY_INIT_CFG_L(QUSB2PHY_PORT_TUNE5, 0x00),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PLL_PWR_CTRL, 0x00),
	QUSB2_PHY_INIT_CFG_L(QUSB2PHY_PORT_TEST2, 0x14),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PLL_TEST, 0x80),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PLL_AUTOPGM_CTL1, 0x9F),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ipq6018_regs_layout[] = अणु
	[QUSB2PHY_PLL_STATUS]              = 0x38,
	[QUSB2PHY_PORT_TUNE1]              = 0x80,
	[QUSB2PHY_PORT_TUNE2]              = 0x84,
	[QUSB2PHY_PORT_TUNE3]              = 0x88,
	[QUSB2PHY_PORT_TUNE4]              = 0x8C,
	[QUSB2PHY_PORT_TUNE5]              = 0x90,
	[QUSB2PHY_PORT_TEST1]              = 0x98,
	[QUSB2PHY_PORT_TEST2]              = 0x9C,
	[QUSB2PHY_PORT_POWERDOWN]          = 0xB4,
	[QUSB2PHY_INTR_CTRL]               = 0xBC,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक msm8996_regs_layout[] = अणु
	[QUSB2PHY_PLL_STATUS]		= 0x38,
	[QUSB2PHY_PORT_TUNE1]		= 0x80,
	[QUSB2PHY_PORT_TUNE2]		= 0x84,
	[QUSB2PHY_PORT_TUNE3]		= 0x88,
	[QUSB2PHY_PORT_TUNE4]		= 0x8c,
	[QUSB2PHY_PORT_TUNE5]		= 0x90,
	[QUSB2PHY_PORT_TEST1]		= 0xb8,
	[QUSB2PHY_PORT_TEST2]		= 0x9c,
	[QUSB2PHY_PORT_POWERDOWN]	= 0xb4,
	[QUSB2PHY_INTR_CTRL]		= 0xbc,
पूर्ण;

अटल स्थिर काष्ठा qusb2_phy_init_tbl msm8996_init_tbl[] = अणु
	QUSB2_PHY_INIT_CFG_L(QUSB2PHY_PORT_TUNE1, 0xf8),
	QUSB2_PHY_INIT_CFG_L(QUSB2PHY_PORT_TUNE2, 0xb3),
	QUSB2_PHY_INIT_CFG_L(QUSB2PHY_PORT_TUNE3, 0x83),
	QUSB2_PHY_INIT_CFG_L(QUSB2PHY_PORT_TUNE4, 0xc0),

	QUSB2_PHY_INIT_CFG(QUSB2PHY_PLL_TUNE, 0x30),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PLL_USER_CTL1, 0x79),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PLL_USER_CTL2, 0x21),

	QUSB2_PHY_INIT_CFG_L(QUSB2PHY_PORT_TEST2, 0x14),

	QUSB2_PHY_INIT_CFG(QUSB2PHY_PLL_AUTOPGM_CTL1, 0x9f),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PLL_PWR_CTRL, 0x00),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक msm8998_regs_layout[] = अणु
	[QUSB2PHY_PLL_CORE_INPUT_OVERRIDE] = 0xa8,
	[QUSB2PHY_PLL_STATUS]              = 0x1a0,
	[QUSB2PHY_PORT_TUNE1]              = 0x23c,
	[QUSB2PHY_PORT_TUNE2]              = 0x240,
	[QUSB2PHY_PORT_TUNE3]              = 0x244,
	[QUSB2PHY_PORT_TUNE4]              = 0x248,
	[QUSB2PHY_PORT_TEST1]              = 0x24c,
	[QUSB2PHY_PORT_TEST2]              = 0x250,
	[QUSB2PHY_PORT_POWERDOWN]          = 0x210,
	[QUSB2PHY_INTR_CTRL]               = 0x22c,
पूर्ण;

अटल स्थिर काष्ठा qusb2_phy_init_tbl msm8998_init_tbl[] = अणु
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PLL_ANALOG_CONTROLS_TWO, 0x13),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PLL_CLOCK_INVERTERS, 0x7c),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PLL_CMODE, 0x80),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PLL_LOCK_DELAY, 0x0a),

	QUSB2_PHY_INIT_CFG_L(QUSB2PHY_PORT_TUNE1, 0xa5),
	QUSB2_PHY_INIT_CFG_L(QUSB2PHY_PORT_TUNE2, 0x09),

	QUSB2_PHY_INIT_CFG(QUSB2PHY_PLL_DIGITAL_TIMERS_TWO, 0x19),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक qusb2_v2_regs_layout[] = अणु
	[QUSB2PHY_PLL_CORE_INPUT_OVERRIDE] = 0xa8,
	[QUSB2PHY_PLL_STATUS]		= 0x1a0,
	[QUSB2PHY_PORT_TUNE1]		= 0x240,
	[QUSB2PHY_PORT_TUNE2]		= 0x244,
	[QUSB2PHY_PORT_TUNE3]		= 0x248,
	[QUSB2PHY_PORT_TUNE4]		= 0x24c,
	[QUSB2PHY_PORT_TUNE5]		= 0x250,
	[QUSB2PHY_PORT_TEST1]		= 0x254,
	[QUSB2PHY_PORT_TEST2]		= 0x258,
	[QUSB2PHY_PORT_POWERDOWN]	= 0x210,
	[QUSB2PHY_INTR_CTRL]		= 0x230,
पूर्ण;

अटल स्थिर काष्ठा qusb2_phy_init_tbl qusb2_v2_init_tbl[] = अणु
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PLL_ANALOG_CONTROLS_TWO, 0x03),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PLL_CLOCK_INVERTERS, 0x7c),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PLL_CMODE, 0x80),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PLL_LOCK_DELAY, 0x0a),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PLL_DIGITAL_TIMERS_TWO, 0x19),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PLL_BIAS_CONTROL_1, 0x40),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PLL_BIAS_CONTROL_2, 0x20),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_PWR_CTRL2, 0x21),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_IMP_CTRL1, 0x0),
	QUSB2_PHY_INIT_CFG(QUSB2PHY_IMP_CTRL2, 0x58),

	QUSB2_PHY_INIT_CFG_L(QUSB2PHY_PORT_TUNE1, 0x30),
	QUSB2_PHY_INIT_CFG_L(QUSB2PHY_PORT_TUNE2, 0x29),
	QUSB2_PHY_INIT_CFG_L(QUSB2PHY_PORT_TUNE3, 0xca),
	QUSB2_PHY_INIT_CFG_L(QUSB2PHY_PORT_TUNE4, 0x04),
	QUSB2_PHY_INIT_CFG_L(QUSB2PHY_PORT_TUNE5, 0x03),

	QUSB2_PHY_INIT_CFG(QUSB2PHY_CHG_CTRL2, 0x0),
पूर्ण;

काष्ठा qusb2_phy_cfg अणु
	स्थिर काष्ठा qusb2_phy_init_tbl *tbl;
	/* number of entries in the table */
	अचिन्हित पूर्णांक tbl_num;
	/* offset to PHY_CLK_SCHEME रेजिस्टर in TCSR map */
	अचिन्हित पूर्णांक clk_scheme_offset;

	/* array of रेजिस्टरs with dअगरferent offsets */
	स्थिर अचिन्हित पूर्णांक *regs;
	अचिन्हित पूर्णांक mask_core_पढ़ोy;
	अचिन्हित पूर्णांक disable_ctrl;
	अचिन्हित पूर्णांक स्वतःresume_en;

	/* true अगर PHY has PLL_TEST रेजिस्टर to select clk_scheme */
	bool has_pll_test;

	/* true अगर TUNE1 रेजिस्टर must be updated by fused value, अन्यथा TUNE2 */
	bool update_tune1_with_efuse;

	/* true अगर PHY has PLL_CORE_INPUT_OVERRIDE रेजिस्टर to reset PLL */
	bool has_pll_override;

	/* true अगर PHY शेष clk scheme is single-ended */
	bool se_clk_scheme_शेष;
पूर्ण;

अटल स्थिर काष्ठा qusb2_phy_cfg msm8996_phy_cfg = अणु
	.tbl		= msm8996_init_tbl,
	.tbl_num	= ARRAY_SIZE(msm8996_init_tbl),
	.regs		= msm8996_regs_layout,

	.has_pll_test	= true,
	.se_clk_scheme_शेष = true,
	.disable_ctrl	= (CLAMP_N_EN | FREEZIO_N | POWER_DOWN),
	.mask_core_पढ़ोy = PLL_LOCKED,
	.स्वतःresume_en	 = BIT(3),
पूर्ण;

अटल स्थिर काष्ठा qusb2_phy_cfg msm8998_phy_cfg = अणु
	.tbl            = msm8998_init_tbl,
	.tbl_num        = ARRAY_SIZE(msm8998_init_tbl),
	.regs           = msm8998_regs_layout,

	.disable_ctrl   = POWER_DOWN,
	.mask_core_पढ़ोy = CORE_READY_STATUS,
	.has_pll_override = true,
	.se_clk_scheme_शेष = true,
	.स्वतःresume_en   = BIT(0),
	.update_tune1_with_efuse = true,
पूर्ण;

अटल स्थिर काष्ठा qusb2_phy_cfg ipq6018_phy_cfg = अणु
	.tbl            = ipq6018_init_tbl,
	.tbl_num        = ARRAY_SIZE(ipq6018_init_tbl),
	.regs           = ipq6018_regs_layout,

	.disable_ctrl   = POWER_DOWN,
	.mask_core_पढ़ोy = PLL_LOCKED,
	/* स्वतःresume not used */
	.स्वतःresume_en   = BIT(0),
पूर्ण;

अटल स्थिर काष्ठा qusb2_phy_cfg qusb2_v2_phy_cfg = अणु
	.tbl		= qusb2_v2_init_tbl,
	.tbl_num	= ARRAY_SIZE(qusb2_v2_init_tbl),
	.regs		= qusb2_v2_regs_layout,

	.disable_ctrl	= (PWR_CTRL1_VREF_SUPPLY_TRIM | PWR_CTRL1_CLAMP_N_EN |
			   POWER_DOWN),
	.mask_core_पढ़ोy = CORE_READY_STATUS,
	.has_pll_override = true,
	.se_clk_scheme_शेष = true,
	.स्वतःresume_en	  = BIT(0),
	.update_tune1_with_efuse = true,
पूर्ण;

अटल स्थिर काष्ठा qusb2_phy_cfg sdm660_phy_cfg = अणु
	.tbl		= msm8996_init_tbl,
	.tbl_num	= ARRAY_SIZE(msm8996_init_tbl),
	.regs		= msm8996_regs_layout,

	.has_pll_test	= true,
	.se_clk_scheme_शेष = false,
	.disable_ctrl	= (CLAMP_N_EN | FREEZIO_N | POWER_DOWN),
	.mask_core_पढ़ोy = PLL_LOCKED,
	.स्वतःresume_en	 = BIT(3),
पूर्ण;

अटल स्थिर अक्षर * स्थिर qusb2_phy_vreg_names[] = अणु
	"vdda-pll", "vdda-phy-dpdm",
पूर्ण;

#घोषणा QUSB2_NUM_VREGS		ARRAY_SIZE(qusb2_phy_vreg_names)

/* काष्ठा override_param - काष्ठाure holding qusb2 v2 phy overriding param
 * set override true अगर the  device tree property exists and पढ़ो and assign
 * to value
 */
काष्ठा override_param अणु
	bool override;
	u8 value;
पूर्ण;

/*काष्ठा override_params - काष्ठाure holding qusb2 v2 phy overriding params
 * @imp_res_offset: rescode offset to be updated in IMP_CTRL1 रेजिस्टर
 * @hstx_trim: HSTX_TRIM to be updated in TUNE1 रेजिस्टर
 * @preemphasis: Amplitude Pre-Emphasis to be updated in TUNE1 रेजिस्टर
 * @preemphasis_width: half/full-width Pre-Emphasis updated via TUNE1
 * @bias_ctrl: bias ctrl to be updated in BIAS_CONTROL_2 रेजिस्टर
 * @अक्षरge_ctrl: अक्षरge ctrl to be updated in CHG_CTRL2 रेजिस्टर
 * @hsdisc_trim: disconnect threshold to be updated in TUNE2 रेजिस्टर
 */
काष्ठा override_params अणु
	काष्ठा override_param imp_res_offset;
	काष्ठा override_param hstx_trim;
	काष्ठा override_param preemphasis;
	काष्ठा override_param preemphasis_width;
	काष्ठा override_param bias_ctrl;
	काष्ठा override_param अक्षरge_ctrl;
	काष्ठा override_param hsdisc_trim;
पूर्ण;

/**
 * काष्ठा qusb2_phy - काष्ठाure holding qusb2 phy attributes
 *
 * @phy: generic phy
 * @base: iomapped memory space क्रम qubs2 phy
 *
 * @cfg_ahb_clk: AHB2PHY पूर्णांकerface घड़ी
 * @ref_clk: phy reference घड़ी
 * @अगरace_clk: phy पूर्णांकerface घड़ी
 * @phy_reset: phy reset control
 * @vregs: regulator supplies bulk data
 *
 * @tcsr: TCSR syscon रेजिस्टर map
 * @cell: nvmem cell containing phy tuning value
 *
 * @overrides: poपूर्णांकer to काष्ठाure क्रम all overriding tuning params
 *
 * @cfg: phy config data
 * @has_se_clk_scheme: indicate अगर PHY has single-ended ref घड़ी scheme
 * @phy_initialized: indicate अगर PHY has been initialized
 * @mode: current PHY mode
 */
काष्ठा qusb2_phy अणु
	काष्ठा phy *phy;
	व्योम __iomem *base;

	काष्ठा clk *cfg_ahb_clk;
	काष्ठा clk *ref_clk;
	काष्ठा clk *अगरace_clk;
	काष्ठा reset_control *phy_reset;
	काष्ठा regulator_bulk_data vregs[QUSB2_NUM_VREGS];

	काष्ठा regmap *tcsr;
	काष्ठा nvmem_cell *cell;

	काष्ठा override_params overrides;

	स्थिर काष्ठा qusb2_phy_cfg *cfg;
	bool has_se_clk_scheme;
	bool phy_initialized;
	क्रमागत phy_mode mode;
पूर्ण;

अटल अंतरभूत व्योम qusb2_ग_लिखो_mask(व्योम __iomem *base, u32 offset,
				    u32 val, u32 mask)
अणु
	u32 reg;

	reg = पढ़ोl(base + offset);
	reg &= ~mask;
	reg |= val & mask;
	ग_लिखोl(reg, base + offset);

	/* Ensure above ग_लिखो is completed */
	पढ़ोl(base + offset);
पूर्ण

अटल अंतरभूत व्योम qusb2_setbits(व्योम __iomem *base, u32 offset, u32 val)
अणु
	u32 reg;

	reg = पढ़ोl(base + offset);
	reg |= val;
	ग_लिखोl(reg, base + offset);

	/* Ensure above ग_लिखो is completed */
	पढ़ोl(base + offset);
पूर्ण

अटल अंतरभूत व्योम qusb2_clrbits(व्योम __iomem *base, u32 offset, u32 val)
अणु
	u32 reg;

	reg = पढ़ोl(base + offset);
	reg &= ~val;
	ग_लिखोl(reg, base + offset);

	/* Ensure above ग_लिखो is completed */
	पढ़ोl(base + offset);
पूर्ण

अटल अंतरभूत
व्योम qcom_qusb2_phy_configure(व्योम __iomem *base,
			      स्थिर अचिन्हित पूर्णांक *regs,
			      स्थिर काष्ठा qusb2_phy_init_tbl tbl[], पूर्णांक num)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num; i++) अणु
		अगर (tbl[i].in_layout)
			ग_लिखोl(tbl[i].val, base + regs[tbl[i].offset]);
		अन्यथा
			ग_लिखोl(tbl[i].val, base + tbl[i].offset);
	पूर्ण
पूर्ण

/*
 * Update board specअगरic PHY tuning override values अगर specअगरied from
 * device tree.
 */
अटल व्योम qusb2_phy_override_phy_params(काष्ठा qusb2_phy *qphy)
अणु
	स्थिर काष्ठा qusb2_phy_cfg *cfg = qphy->cfg;
	काष्ठा override_params *or = &qphy->overrides;

	अगर (or->imp_res_offset.override)
		qusb2_ग_लिखो_mask(qphy->base, QUSB2PHY_IMP_CTRL1,
		or->imp_res_offset.value << IMP_RES_OFFSET_SHIFT,
			     IMP_RES_OFFSET_MASK);

	अगर (or->bias_ctrl.override)
		qusb2_ग_लिखो_mask(qphy->base, QUSB2PHY_PLL_BIAS_CONTROL_2,
		or->bias_ctrl.value << BIAS_CTRL2_RES_OFFSET_SHIFT,
			   BIAS_CTRL2_RES_OFFSET_MASK);

	अगर (or->अक्षरge_ctrl.override)
		qusb2_ग_लिखो_mask(qphy->base, QUSB2PHY_CHG_CTRL2,
		or->अक्षरge_ctrl.value << CHG_CTRL2_OFFSET_SHIFT,
			     CHG_CTRL2_OFFSET_MASK);

	अगर (or->hstx_trim.override)
		qusb2_ग_लिखो_mask(qphy->base, cfg->regs[QUSB2PHY_PORT_TUNE1],
		or->hstx_trim.value << HSTX_TRIM_SHIFT,
				 HSTX_TRIM_MASK);

	अगर (or->preemphasis.override)
		qusb2_ग_लिखो_mask(qphy->base, cfg->regs[QUSB2PHY_PORT_TUNE1],
		or->preemphasis.value << PREEMPHASIS_EN_SHIFT,
				PREEMPHASIS_EN_MASK);

	अगर (or->preemphasis_width.override) अणु
		अगर (or->preemphasis_width.value ==
		    QUSB2_V2_PREEMPHASIS_WIDTH_HALF_BIT)
			qusb2_setbits(qphy->base,
				      cfg->regs[QUSB2PHY_PORT_TUNE1],
				      PREEMPH_WIDTH_HALF_BIT);
		अन्यथा
			qusb2_clrbits(qphy->base,
				      cfg->regs[QUSB2PHY_PORT_TUNE1],
				      PREEMPH_WIDTH_HALF_BIT);
	पूर्ण

	अगर (or->hsdisc_trim.override)
		qusb2_ग_लिखो_mask(qphy->base, cfg->regs[QUSB2PHY_PORT_TUNE2],
		or->hsdisc_trim.value << HSDISC_TRIM_SHIFT,
				 HSDISC_TRIM_MASK);
पूर्ण

/*
 * Fetches HS Tx tuning value from nvmem and sets the
 * QUSB2PHY_PORT_TUNE1/2 रेजिस्टर.
 * For error हाल, skip setting the value and use the शेष value.
 */
अटल व्योम qusb2_phy_set_tune2_param(काष्ठा qusb2_phy *qphy)
अणु
	काष्ठा device *dev = &qphy->phy->dev;
	स्थिर काष्ठा qusb2_phy_cfg *cfg = qphy->cfg;
	u8 *val;

	/* efuse रेजिस्टर is optional */
	अगर (!qphy->cell)
		वापस;

	/*
	 * Read efuse रेजिस्टर having TUNE2/1 parameter's high nibble.
	 * If efuse रेजिस्टर shows value as 0x0 (indicating value is not
	 * fused), or अगर we fail to find a valid efuse रेजिस्टर setting,
	 * then use शेष value क्रम high nibble that we have alपढ़ोy
	 * set जबतक configuring the phy.
	 */
	val = nvmem_cell_पढ़ो(qphy->cell, शून्य);
	अगर (IS_ERR(val) || !val[0]) अणु
		dev_dbg(dev, "failed to read a valid hs-tx trim value\n");
		वापस;
	पूर्ण

	/* Fused TUNE1/2 value is the higher nibble only */
	अगर (cfg->update_tune1_with_efuse)
		qusb2_ग_लिखो_mask(qphy->base, cfg->regs[QUSB2PHY_PORT_TUNE1],
				 val[0] << HSTX_TRIM_SHIFT,
				 HSTX_TRIM_MASK);
	अन्यथा
		qusb2_ग_लिखो_mask(qphy->base, cfg->regs[QUSB2PHY_PORT_TUNE2],
				 val[0] << HSTX_TRIM_SHIFT,
				 HSTX_TRIM_MASK);
पूर्ण

अटल पूर्णांक qusb2_phy_set_mode(काष्ठा phy *phy,
			      क्रमागत phy_mode mode, पूर्णांक submode)
अणु
	काष्ठा qusb2_phy *qphy = phy_get_drvdata(phy);

	qphy->mode = mode;

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused qusb2_phy_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा qusb2_phy *qphy = dev_get_drvdata(dev);
	स्थिर काष्ठा qusb2_phy_cfg *cfg = qphy->cfg;
	u32 पूर्णांकr_mask;

	dev_vdbg(dev, "Suspending QUSB2 Phy, mode:%d\n", qphy->mode);

	अगर (!qphy->phy_initialized) अणु
		dev_vdbg(dev, "PHY not initialized, bailing out\n");
		वापस 0;
	पूर्ण

	/*
	 * Enable DP/DM पूर्णांकerrupts to detect line state changes based on current
	 * speed. In other words, enable the triggers _opposite_ of what the
	 * current D+/D- levels are e.g. अगर currently D+ high, D- low
	 * (HS 'J'/Suspend), configure the mask to trigger on D+ low OR D- high
	 */
	पूर्णांकr_mask = DPSE_INTR_EN | DMSE_INTR_EN;
	चयन (qphy->mode) अणु
	हाल PHY_MODE_USB_HOST_HS:
	हाल PHY_MODE_USB_HOST_FS:
	हाल PHY_MODE_USB_DEVICE_HS:
	हाल PHY_MODE_USB_DEVICE_FS:
		पूर्णांकr_mask |= DMSE_INTR_HIGH_SEL;
		अवरोध;
	हाल PHY_MODE_USB_HOST_LS:
	हाल PHY_MODE_USB_DEVICE_LS:
		पूर्णांकr_mask |= DPSE_INTR_HIGH_SEL;
		अवरोध;
	शेष:
		/* No device connected, enable both DP/DM high पूर्णांकerrupt */
		पूर्णांकr_mask |= DMSE_INTR_HIGH_SEL;
		पूर्णांकr_mask |= DPSE_INTR_HIGH_SEL;
		अवरोध;
	पूर्ण

	ग_लिखोl(पूर्णांकr_mask, qphy->base + cfg->regs[QUSB2PHY_INTR_CTRL]);

	/* hold core PLL पूर्णांकo reset */
	अगर (cfg->has_pll_override) अणु
		qusb2_setbits(qphy->base,
			      cfg->regs[QUSB2PHY_PLL_CORE_INPUT_OVERRIDE],
			      CORE_PLL_EN_FROM_RESET | CORE_RESET |
			      CORE_RESET_MUX);
	पूर्ण

	/* enable phy स्वतः-resume only अगर device is connected on bus */
	अगर (qphy->mode != PHY_MODE_INVALID) अणु
		qusb2_setbits(qphy->base, cfg->regs[QUSB2PHY_PORT_TEST1],
			      cfg->स्वतःresume_en);
		/* Autoresume bit has to be toggled in order to enable it */
		qusb2_clrbits(qphy->base, cfg->regs[QUSB2PHY_PORT_TEST1],
			      cfg->स्वतःresume_en);
	पूर्ण

	अगर (!qphy->has_se_clk_scheme)
		clk_disable_unprepare(qphy->ref_clk);

	clk_disable_unprepare(qphy->cfg_ahb_clk);
	clk_disable_unprepare(qphy->अगरace_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused qusb2_phy_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा qusb2_phy *qphy = dev_get_drvdata(dev);
	स्थिर काष्ठा qusb2_phy_cfg *cfg = qphy->cfg;
	पूर्णांक ret;

	dev_vdbg(dev, "Resuming QUSB2 phy, mode:%d\n", qphy->mode);

	अगर (!qphy->phy_initialized) अणु
		dev_vdbg(dev, "PHY not initialized, bailing out\n");
		वापस 0;
	पूर्ण

	ret = clk_prepare_enable(qphy->अगरace_clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable iface_clk, %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(qphy->cfg_ahb_clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable cfg ahb clock, %d\n", ret);
		जाओ disable_अगरace_clk;
	पूर्ण

	अगर (!qphy->has_se_clk_scheme) अणु
		ret = clk_prepare_enable(qphy->ref_clk);
		अगर (ret) अणु
			dev_err(dev, "failed to enable ref clk, %d\n", ret);
			जाओ disable_ahb_clk;
		पूर्ण
	पूर्ण

	ग_लिखोl(0x0, qphy->base + cfg->regs[QUSB2PHY_INTR_CTRL]);

	/* bring core PLL out of reset */
	अगर (cfg->has_pll_override) अणु
		qusb2_clrbits(qphy->base,
			      cfg->regs[QUSB2PHY_PLL_CORE_INPUT_OVERRIDE],
			      CORE_RESET | CORE_RESET_MUX);
	पूर्ण

	वापस 0;

disable_ahb_clk:
	clk_disable_unprepare(qphy->cfg_ahb_clk);
disable_अगरace_clk:
	clk_disable_unprepare(qphy->अगरace_clk);

	वापस ret;
पूर्ण

अटल पूर्णांक qusb2_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा qusb2_phy *qphy = phy_get_drvdata(phy);
	स्थिर काष्ठा qusb2_phy_cfg *cfg = qphy->cfg;
	अचिन्हित पूर्णांक val = 0;
	अचिन्हित पूर्णांक clk_scheme;
	पूर्णांक ret;

	dev_vdbg(&phy->dev, "%s(): Initializing QUSB2 phy\n", __func__);

	/* turn on regulator supplies */
	ret = regulator_bulk_enable(ARRAY_SIZE(qphy->vregs), qphy->vregs);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(qphy->अगरace_clk);
	अगर (ret) अणु
		dev_err(&phy->dev, "failed to enable iface_clk, %d\n", ret);
		जाओ घातeroff_phy;
	पूर्ण

	/* enable ahb पूर्णांकerface घड़ी to program phy */
	ret = clk_prepare_enable(qphy->cfg_ahb_clk);
	अगर (ret) अणु
		dev_err(&phy->dev, "failed to enable cfg ahb clock, %d\n", ret);
		जाओ disable_अगरace_clk;
	पूर्ण

	/* Perक्रमm phy reset */
	ret = reset_control_निश्चित(qphy->phy_reset);
	अगर (ret) अणु
		dev_err(&phy->dev, "failed to assert phy_reset, %d\n", ret);
		जाओ disable_ahb_clk;
	पूर्ण

	/* 100 us delay to keep PHY in reset mode */
	usleep_range(100, 150);

	ret = reset_control_deनिश्चित(qphy->phy_reset);
	अगर (ret) अणु
		dev_err(&phy->dev, "failed to de-assert phy_reset, %d\n", ret);
		जाओ disable_ahb_clk;
	पूर्ण

	/* Disable the PHY */
	qusb2_setbits(qphy->base, cfg->regs[QUSB2PHY_PORT_POWERDOWN],
		      qphy->cfg->disable_ctrl);

	अगर (cfg->has_pll_test) अणु
		/* save reset value to override reference घड़ी scheme later */
		val = पढ़ोl(qphy->base + QUSB2PHY_PLL_TEST);
	पूर्ण

	qcom_qusb2_phy_configure(qphy->base, cfg->regs, cfg->tbl,
				 cfg->tbl_num);

	/* Override board specअगरic PHY tuning values */
	qusb2_phy_override_phy_params(qphy);

	/* Set efuse value क्रम tuning the PHY */
	qusb2_phy_set_tune2_param(qphy);

	/* Enable the PHY */
	qusb2_clrbits(qphy->base, cfg->regs[QUSB2PHY_PORT_POWERDOWN],
		      POWER_DOWN);

	/* Required to get phy pll lock successfully */
	usleep_range(150, 160);

	/*
	 * Not all the SoCs have got a पढ़ोable TCSR_PHY_CLK_SCHEME
	 * रेजिस्टर in the TCSR so, अगर there's none, use the शेष
	 * value hardcoded in the configuration.
	 */
	qphy->has_se_clk_scheme = cfg->se_clk_scheme_शेष;

	/*
	 * पढ़ो TCSR_PHY_CLK_SCHEME रेजिस्टर to check अगर single-ended
	 * घड़ी scheme is selected. If yes, then disable dअगरferential
	 * ref_clk and use single-ended घड़ी, otherwise use dअगरferential
	 * ref_clk only.
	 */
	अगर (qphy->tcsr) अणु
		ret = regmap_पढ़ो(qphy->tcsr, qphy->cfg->clk_scheme_offset,
				  &clk_scheme);
		अगर (ret) अणु
			dev_err(&phy->dev, "failed to read clk scheme reg\n");
			जाओ निश्चित_phy_reset;
		पूर्ण

		/* is it a dअगरferential घड़ी scheme ? */
		अगर (!(clk_scheme & PHY_CLK_SCHEME_SEL)) अणु
			dev_vdbg(&phy->dev, "%s(): select differential clk\n",
				 __func__);
			qphy->has_se_clk_scheme = false;
		पूर्ण अन्यथा अणु
			dev_vdbg(&phy->dev, "%s(): select single-ended clk\n",
				 __func__);
		पूर्ण
	पूर्ण

	अगर (!qphy->has_se_clk_scheme) अणु
		ret = clk_prepare_enable(qphy->ref_clk);
		अगर (ret) अणु
			dev_err(&phy->dev, "failed to enable ref clk, %d\n",
				ret);
			जाओ निश्चित_phy_reset;
		पूर्ण
	पूर्ण

	अगर (cfg->has_pll_test) अणु
		अगर (!qphy->has_se_clk_scheme)
			val &= ~CLK_REF_SEL;
		अन्यथा
			val |= CLK_REF_SEL;

		ग_लिखोl(val, qphy->base + QUSB2PHY_PLL_TEST);

		/* ensure above ग_लिखो is through */
		पढ़ोl(qphy->base + QUSB2PHY_PLL_TEST);
	पूर्ण

	/* Required to get phy pll lock successfully */
	usleep_range(100, 110);

	val = पढ़ोb(qphy->base + cfg->regs[QUSB2PHY_PLL_STATUS]);
	अगर (!(val & cfg->mask_core_पढ़ोy)) अणु
		dev_err(&phy->dev,
			"QUSB2PHY pll lock failed: status reg = %x\n", val);
		ret = -EBUSY;
		जाओ disable_ref_clk;
	पूर्ण
	qphy->phy_initialized = true;

	वापस 0;

disable_ref_clk:
	अगर (!qphy->has_se_clk_scheme)
		clk_disable_unprepare(qphy->ref_clk);
निश्चित_phy_reset:
	reset_control_निश्चित(qphy->phy_reset);
disable_ahb_clk:
	clk_disable_unprepare(qphy->cfg_ahb_clk);
disable_अगरace_clk:
	clk_disable_unprepare(qphy->अगरace_clk);
घातeroff_phy:
	regulator_bulk_disable(ARRAY_SIZE(qphy->vregs), qphy->vregs);

	वापस ret;
पूर्ण

अटल पूर्णांक qusb2_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा qusb2_phy *qphy = phy_get_drvdata(phy);

	/* Disable the PHY */
	qusb2_setbits(qphy->base, qphy->cfg->regs[QUSB2PHY_PORT_POWERDOWN],
		      qphy->cfg->disable_ctrl);

	अगर (!qphy->has_se_clk_scheme)
		clk_disable_unprepare(qphy->ref_clk);

	reset_control_निश्चित(qphy->phy_reset);

	clk_disable_unprepare(qphy->cfg_ahb_clk);
	clk_disable_unprepare(qphy->अगरace_clk);

	regulator_bulk_disable(ARRAY_SIZE(qphy->vregs), qphy->vregs);

	qphy->phy_initialized = false;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops qusb2_phy_gen_ops = अणु
	.init		= qusb2_phy_init,
	.निकास		= qusb2_phy_निकास,
	.set_mode	= qusb2_phy_set_mode,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id qusb2_phy_of_match_table[] = अणु
	अणु
		.compatible	= "qcom,ipq6018-qusb2-phy",
		.data		= &ipq6018_phy_cfg,
	पूर्ण, अणु
		.compatible	= "qcom,ipq8074-qusb2-phy",
		.data		= &msm8996_phy_cfg,
	पूर्ण, अणु
		.compatible	= "qcom,msm8996-qusb2-phy",
		.data		= &msm8996_phy_cfg,
	पूर्ण, अणु
		.compatible	= "qcom,msm8998-qusb2-phy",
		.data		= &msm8998_phy_cfg,
	पूर्ण, अणु
		.compatible	= "qcom,sdm660-qusb2-phy",
		.data		= &sdm660_phy_cfg,
	पूर्ण, अणु
		/*
		 * Deprecated. Only here to support legacy device
		 * trees that didn't include "qcom,qusb2-v2-phy"
		 */
		.compatible	= "qcom,sdm845-qusb2-phy",
		.data		= &qusb2_v2_phy_cfg,
	पूर्ण, अणु
		.compatible	= "qcom,qusb2-v2-phy",
		.data		= &qusb2_v2_phy_cfg,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, qusb2_phy_of_match_table);

अटल स्थिर काष्ठा dev_pm_ops qusb2_phy_pm_ops = अणु
	SET_RUNTIME_PM_OPS(qusb2_phy_runसमय_suspend,
			   qusb2_phy_runसमय_resume, शून्य)
पूर्ण;

अटल पूर्णांक qusb2_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा qusb2_phy *qphy;
	काष्ठा phy_provider *phy_provider;
	काष्ठा phy *generic_phy;
	पूर्णांक ret, i;
	पूर्णांक num;
	u32 value;
	काष्ठा override_params *or;

	qphy = devm_kzalloc(dev, माप(*qphy), GFP_KERNEL);
	अगर (!qphy)
		वापस -ENOMEM;
	or = &qphy->overrides;

	qphy->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(qphy->base))
		वापस PTR_ERR(qphy->base);

	qphy->cfg_ahb_clk = devm_clk_get(dev, "cfg_ahb");
	अगर (IS_ERR(qphy->cfg_ahb_clk)) अणु
		ret = PTR_ERR(qphy->cfg_ahb_clk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get cfg ahb clk, %d\n", ret);
		वापस ret;
	पूर्ण

	qphy->ref_clk = devm_clk_get(dev, "ref");
	अगर (IS_ERR(qphy->ref_clk)) अणु
		ret = PTR_ERR(qphy->ref_clk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get ref clk, %d\n", ret);
		वापस ret;
	पूर्ण

	qphy->अगरace_clk = devm_clk_get_optional(dev, "iface");
	अगर (IS_ERR(qphy->अगरace_clk))
		वापस PTR_ERR(qphy->अगरace_clk);

	qphy->phy_reset = devm_reset_control_get_by_index(&pdev->dev, 0);
	अगर (IS_ERR(qphy->phy_reset)) अणु
		dev_err(dev, "failed to get phy core reset\n");
		वापस PTR_ERR(qphy->phy_reset);
	पूर्ण

	num = ARRAY_SIZE(qphy->vregs);
	क्रम (i = 0; i < num; i++)
		qphy->vregs[i].supply = qusb2_phy_vreg_names[i];

	ret = devm_regulator_bulk_get(dev, num, qphy->vregs);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get regulator supplies: %d\n",
				ret);
		वापस ret;
	पूर्ण

	/* Get the specअगरic init parameters of QMP phy */
	qphy->cfg = of_device_get_match_data(dev);

	qphy->tcsr = syscon_regmap_lookup_by_phandle(dev->of_node,
							"qcom,tcsr-syscon");
	अगर (IS_ERR(qphy->tcsr)) अणु
		dev_dbg(dev, "failed to lookup TCSR regmap\n");
		qphy->tcsr = शून्य;
	पूर्ण

	qphy->cell = devm_nvmem_cell_get(dev, शून्य);
	अगर (IS_ERR(qphy->cell)) अणु
		अगर (PTR_ERR(qphy->cell) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		qphy->cell = शून्य;
		dev_dbg(dev, "failed to lookup tune2 hstx trim value\n");
	पूर्ण

	अगर (!of_property_पढ़ो_u32(dev->of_node, "qcom,imp-res-offset-value",
				  &value)) अणु
		or->imp_res_offset.value = (u8)value;
		or->imp_res_offset.override = true;
	पूर्ण

	अगर (!of_property_पढ़ो_u32(dev->of_node, "qcom,bias-ctrl-value",
				  &value)) अणु
		or->bias_ctrl.value = (u8)value;
		or->bias_ctrl.override = true;
	पूर्ण

	अगर (!of_property_पढ़ो_u32(dev->of_node, "qcom,charge-ctrl-value",
				  &value)) अणु
		or->अक्षरge_ctrl.value = (u8)value;
		or->अक्षरge_ctrl.override = true;
	पूर्ण

	अगर (!of_property_पढ़ो_u32(dev->of_node, "qcom,hstx-trim-value",
				  &value)) अणु
		or->hstx_trim.value = (u8)value;
		or->hstx_trim.override = true;
	पूर्ण

	अगर (!of_property_पढ़ो_u32(dev->of_node, "qcom,preemphasis-level",
				     &value)) अणु
		or->preemphasis.value = (u8)value;
		or->preemphasis.override = true;
	पूर्ण

	अगर (!of_property_पढ़ो_u32(dev->of_node, "qcom,preemphasis-width",
				     &value)) अणु
		or->preemphasis_width.value = (u8)value;
		or->preemphasis_width.override = true;
	पूर्ण

	अगर (!of_property_पढ़ो_u32(dev->of_node, "qcom,hsdisc-trim-value",
				  &value)) अणु
		or->hsdisc_trim.value = (u8)value;
		or->hsdisc_trim.override = true;
	पूर्ण

	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);
	/*
	 * Prevent runसमय pm from being ON by शेष. Users can enable
	 * it using घातer/control in sysfs.
	 */
	pm_runसमय_क्रमbid(dev);

	generic_phy = devm_phy_create(dev, शून्य, &qusb2_phy_gen_ops);
	अगर (IS_ERR(generic_phy)) अणु
		ret = PTR_ERR(generic_phy);
		dev_err(dev, "failed to create phy, %d\n", ret);
		pm_runसमय_disable(dev);
		वापस ret;
	पूर्ण
	qphy->phy = generic_phy;

	dev_set_drvdata(dev, qphy);
	phy_set_drvdata(generic_phy, qphy);

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	अगर (!IS_ERR(phy_provider))
		dev_info(dev, "Registered Qcom-QUSB2 phy\n");
	अन्यथा
		pm_runसमय_disable(dev);

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल काष्ठा platक्रमm_driver qusb2_phy_driver = अणु
	.probe		= qusb2_phy_probe,
	.driver = अणु
		.name	= "qcom-qusb2-phy",
		.pm	= &qusb2_phy_pm_ops,
		.of_match_table = qusb2_phy_of_match_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(qusb2_phy_driver);

MODULE_AUTHOR("Vivek Gautam <vivek.gautam@codeaurora.org>");
MODULE_DESCRIPTION("Qualcomm QUSB2 PHY driver");
MODULE_LICENSE("GPL v2");
