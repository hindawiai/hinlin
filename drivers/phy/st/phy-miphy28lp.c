<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 STMicroelectronics
 *
 * STMicroelectronics PHY driver MiPHY28lp (क्रम SoC STiH407).
 *
 * Author: Alexandre Torgue <alexandre.torgue@st.com>
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_address.h>
#समावेश <linux/clk.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/delay.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>

#समावेश <dt-bindings/phy/phy.h>

/* MiPHY रेजिस्टरs */
#घोषणा MIPHY_CONF_RESET		0x00
#घोषणा RST_APPLI_SW		BIT(0)
#घोषणा RST_CONF_SW		BIT(1)
#घोषणा RST_MACRO_SW		BIT(2)

#घोषणा MIPHY_RESET			0x01
#घोषणा RST_PLL_SW		BIT(0)
#घोषणा RST_COMP_SW		BIT(2)

#घोषणा MIPHY_STATUS_1			0x02
#घोषणा PHY_RDY			BIT(0)
#घोषणा HFC_RDY			BIT(1)
#घोषणा HFC_PLL			BIT(2)

#घोषणा MIPHY_CONTROL			0x04
#घोषणा TERM_EN_SW		BIT(2)
#घोषणा DIS_LINK_RST		BIT(3)
#घोषणा AUTO_RST_RX		BIT(4)
#घोषणा PX_RX_POL		BIT(5)

#घोषणा MIPHY_BOUNDARY_SEL		0x0a
#घोषणा TX_SEL			BIT(6)
#घोषणा SSC_SEL			BIT(4)
#घोषणा GENSEL_SEL		BIT(0)

#घोषणा MIPHY_BOUNDARY_1		0x0b
#घोषणा MIPHY_BOUNDARY_2		0x0c
#घोषणा SSC_EN_SW		BIT(2)

#घोषणा MIPHY_PLL_CLKREF_FREQ		0x0d
#घोषणा MIPHY_SPEED			0x0e
#घोषणा TX_SPDSEL_80DEC		0
#घोषणा TX_SPDSEL_40DEC		1
#घोषणा TX_SPDSEL_20DEC		2
#घोषणा RX_SPDSEL_80DEC		0
#घोषणा RX_SPDSEL_40DEC		(1 << 2)
#घोषणा RX_SPDSEL_20DEC		(2 << 2)

#घोषणा MIPHY_CONF			0x0f
#घोषणा MIPHY_CTRL_TEST_SEL		0x20
#घोषणा MIPHY_CTRL_TEST_1		0x21
#घोषणा MIPHY_CTRL_TEST_2		0x22
#घोषणा MIPHY_CTRL_TEST_3		0x23
#घोषणा MIPHY_CTRL_TEST_4		0x24
#घोषणा MIPHY_FEEDBACK_TEST		0x25
#घोषणा MIPHY_DEBUG_BUS			0x26
#घोषणा MIPHY_DEBUG_STATUS_MSB		0x27
#घोषणा MIPHY_DEBUG_STATUS_LSB		0x28
#घोषणा MIPHY_PWR_RAIL_1		0x29
#घोषणा MIPHY_PWR_RAIL_2		0x2a
#घोषणा MIPHY_SYNCHAR_CONTROL		0x30

#घोषणा MIPHY_COMP_FSM_1		0x3a
#घोषणा COMP_START		BIT(6)

#घोषणा MIPHY_COMP_FSM_6		0x3f
#घोषणा COMP_DONE		BIT(7)

#घोषणा MIPHY_COMP_POSTP		0x42
#घोषणा MIPHY_TX_CTRL_1			0x49
#घोषणा TX_REG_STEP_0V		0
#घोषणा TX_REG_STEP_P_25MV	1
#घोषणा TX_REG_STEP_P_50MV	2
#घोषणा TX_REG_STEP_N_25MV	7
#घोषणा TX_REG_STEP_N_50MV	6
#घोषणा TX_REG_STEP_N_75MV	5

#घोषणा MIPHY_TX_CTRL_2			0x4a
#घोषणा TX_SLEW_SW_40_PS	0
#घोषणा TX_SLEW_SW_80_PS	1
#घोषणा TX_SLEW_SW_120_PS	2

#घोषणा MIPHY_TX_CTRL_3			0x4b
#घोषणा MIPHY_TX_CAL_MAN		0x4e
#घोषणा TX_SLEW_CAL_MAN_EN	BIT(0)

#घोषणा MIPHY_TST_BIAS_BOOST_2		0x62
#घोषणा MIPHY_BIAS_BOOST_1		0x63
#घोषणा MIPHY_BIAS_BOOST_2		0x64
#घोषणा MIPHY_RX_DESBUFF_FDB_2		0x67
#घोषणा MIPHY_RX_DESBUFF_FDB_3		0x68
#घोषणा MIPHY_SIGDET_COMPENS1		0x69
#घोषणा MIPHY_SIGDET_COMPENS2		0x6a
#घोषणा MIPHY_JITTER_PERIOD		0x6b
#घोषणा MIPHY_JITTER_AMPLITUDE_1	0x6c
#घोषणा MIPHY_JITTER_AMPLITUDE_2	0x6d
#घोषणा MIPHY_JITTER_AMPLITUDE_3	0x6e
#घोषणा MIPHY_RX_K_GAIN			0x78
#घोषणा MIPHY_RX_BUFFER_CTRL		0x7a
#घोषणा VGA_GAIN		BIT(0)
#घोषणा EQ_DC_GAIN		BIT(2)
#घोषणा EQ_BOOST_GAIN		BIT(3)

#घोषणा MIPHY_RX_VGA_GAIN		0x7b
#घोषणा MIPHY_RX_EQU_GAIN_1		0x7f
#घोषणा MIPHY_RX_EQU_GAIN_2		0x80
#घोषणा MIPHY_RX_EQU_GAIN_3		0x81
#घोषणा MIPHY_RX_CAL_CTRL_1		0x97
#घोषणा MIPHY_RX_CAL_CTRL_2		0x98

#घोषणा MIPHY_RX_CAL_OFFSET_CTRL	0x99
#घोषणा CAL_OFFSET_VGA_64	(0x03 << 0)
#घोषणा CAL_OFFSET_THRESHOLD_64	(0x03 << 2)
#घोषणा VGA_OFFSET_POLARITY	BIT(4)
#घोषणा OFFSET_COMPENSATION_EN	BIT(6)

#घोषणा MIPHY_RX_CAL_VGA_STEP		0x9a
#घोषणा MIPHY_RX_CAL_EYE_MIN		0x9d
#घोषणा MIPHY_RX_CAL_OPT_LENGTH		0x9f
#घोषणा MIPHY_RX_LOCK_CTRL_1		0xc1
#घोषणा MIPHY_RX_LOCK_SETTINGS_OPT	0xc2
#घोषणा MIPHY_RX_LOCK_STEP		0xc4

#घोषणा MIPHY_RX_SIGDET_SLEEP_OA	0xc9
#घोषणा MIPHY_RX_SIGDET_SLEEP_SEL	0xca
#घोषणा MIPHY_RX_SIGDET_WAIT_SEL	0xcb
#घोषणा MIPHY_RX_SIGDET_DATA_SEL	0xcc
#घोषणा EN_ULTRA_LOW_POWER	BIT(0)
#घोषणा EN_FIRST_HALF		BIT(1)
#घोषणा EN_SECOND_HALF		BIT(2)
#घोषणा EN_DIGIT_SIGNAL_CHECK	BIT(3)

#घोषणा MIPHY_RX_POWER_CTRL_1		0xcd
#घोषणा MIPHY_RX_POWER_CTRL_2		0xce
#घोषणा MIPHY_PLL_CALSET_CTRL		0xd3
#घोषणा MIPHY_PLL_CALSET_1		0xd4
#घोषणा MIPHY_PLL_CALSET_2		0xd5
#घोषणा MIPHY_PLL_CALSET_3		0xd6
#घोषणा MIPHY_PLL_CALSET_4		0xd7
#घोषणा MIPHY_PLL_SBR_1			0xe3
#घोषणा SET_NEW_CHANGE		BIT(1)

#घोषणा MIPHY_PLL_SBR_2			0xe4
#घोषणा MIPHY_PLL_SBR_3			0xe5
#घोषणा MIPHY_PLL_SBR_4			0xe6
#घोषणा MIPHY_PLL_COMMON_MISC_2		0xe9
#घोषणा START_ACT_FILT		BIT(6)

#घोषणा MIPHY_PLL_SPAREIN		0xeb

/*
 * On STiH407 the glue logic can be dअगरferent among MiPHY devices; क्रम example:
 * MiPHY0: OSC_FORCE_EXT means:
 *  0: 30MHz crystal clk - 1: 100MHz ext clk routed through MiPHY1
 * MiPHY1: OSC_FORCE_EXT means:
 *  1: 30MHz crystal clk - 0: 100MHz ext clk routed through MiPHY1
 * Some devices have not the possibility to check अगर the osc is पढ़ोy.
 */
#घोषणा MIPHY_OSC_FORCE_EXT	BIT(3)
#घोषणा MIPHY_OSC_RDY		BIT(5)

#घोषणा MIPHY_CTRL_MASK		0x0f
#घोषणा MIPHY_CTRL_DEFAULT	0
#घोषणा MIPHY_CTRL_SYNC_D_EN	BIT(2)

/* SATA / PCIe defines */
#घोषणा SATA_CTRL_MASK		0x07
#घोषणा PCIE_CTRL_MASK		0xff
#घोषणा SATA_CTRL_SELECT_SATA	1
#घोषणा SATA_CTRL_SELECT_PCIE	0
#घोषणा SYSCFG_PCIE_PCIE_VAL	0x80
#घोषणा SATA_SPDMODE		1

#घोषणा MIPHY_SATA_BANK_NB	3
#घोषणा MIPHY_PCIE_BANK_NB	2

क्रमागत अणु
	SYSCFG_CTRL,
	SYSCFG_STATUS,
	SYSCFG_PCI,
	SYSCFG_SATA,
	SYSCFG_REG_MAX,
पूर्ण;

काष्ठा miphy28lp_phy अणु
	काष्ठा phy *phy;
	काष्ठा miphy28lp_dev *phydev;
	व्योम __iomem *base;
	व्योम __iomem *pipebase;

	bool osc_क्रमce_ext;
	bool osc_rdy;
	bool px_rx_pol_inv;
	bool ssc;
	bool tx_impedance;

	काष्ठा reset_control *miphy_rst;

	u32 sata_gen;

	/* Sysconfig रेजिस्टरs offsets needed to configure the device */
	u32 syscfg_reg[SYSCFG_REG_MAX];
	u8 type;
पूर्ण;

काष्ठा miphy28lp_dev अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा mutex miphy_mutex;
	काष्ठा miphy28lp_phy **phys;
	पूर्णांक nphys;
पूर्ण;

काष्ठा miphy_initval अणु
	u16 reg;
	u16 val;
पूर्ण;

क्रमागत miphy_sata_gen अणु SATA_GEN1, SATA_GEN2, SATA_GEN3 पूर्ण;

अटल अक्षर *PHY_TYPE_name[] = अणु "sata-up", "pcie-up", "", "usb3-up" पूर्ण;

काष्ठा pll_ratio अणु
	पूर्णांक clk_ref;
	पूर्णांक calset_1;
	पूर्णांक calset_2;
	पूर्णांक calset_3;
	पूर्णांक calset_4;
	पूर्णांक cal_ctrl;
पूर्ण;

अटल काष्ठा pll_ratio sata_pll_ratio = अणु
	.clk_ref = 0x1e,
	.calset_1 = 0xc8,
	.calset_2 = 0x00,
	.calset_3 = 0x00,
	.calset_4 = 0x00,
	.cal_ctrl = 0x00,
पूर्ण;

अटल काष्ठा pll_ratio pcie_pll_ratio = अणु
	.clk_ref = 0x1e,
	.calset_1 = 0xa6,
	.calset_2 = 0xaa,
	.calset_3 = 0xaa,
	.calset_4 = 0x00,
	.cal_ctrl = 0x00,
पूर्ण;

अटल काष्ठा pll_ratio usb3_pll_ratio = अणु
	.clk_ref = 0x1e,
	.calset_1 = 0xa6,
	.calset_2 = 0xaa,
	.calset_3 = 0xaa,
	.calset_4 = 0x04,
	.cal_ctrl = 0x00,
पूर्ण;

काष्ठा miphy28lp_pll_gen अणु
	पूर्णांक bank;
	पूर्णांक speed;
	पूर्णांक bias_boost_1;
	पूर्णांक bias_boost_2;
	पूर्णांक tx_ctrl_1;
	पूर्णांक tx_ctrl_2;
	पूर्णांक tx_ctrl_3;
	पूर्णांक rx_k_gain;
	पूर्णांक rx_vga_gain;
	पूर्णांक rx_equ_gain_1;
	पूर्णांक rx_equ_gain_2;
	पूर्णांक rx_equ_gain_3;
	पूर्णांक rx_buff_ctrl;
पूर्ण;

अटल काष्ठा miphy28lp_pll_gen sata_pll_gen[] = अणु
	अणु
		.bank		= 0x00,
		.speed		= TX_SPDSEL_80DEC | RX_SPDSEL_80DEC,
		.bias_boost_1	= 0x00,
		.bias_boost_2	= 0xae,
		.tx_ctrl_2	= 0x53,
		.tx_ctrl_3	= 0x00,
		.rx_buff_ctrl	= EQ_BOOST_GAIN | EQ_DC_GAIN | VGA_GAIN,
		.rx_vga_gain	= 0x00,
		.rx_equ_gain_1	= 0x7d,
		.rx_equ_gain_2	= 0x56,
		.rx_equ_gain_3	= 0x00,
	पूर्ण,
	अणु
		.bank		= 0x01,
		.speed		= TX_SPDSEL_40DEC | RX_SPDSEL_40DEC,
		.bias_boost_1	= 0x00,
		.bias_boost_2	= 0xae,
		.tx_ctrl_2	= 0x72,
		.tx_ctrl_3	= 0x20,
		.rx_buff_ctrl	= EQ_BOOST_GAIN | EQ_DC_GAIN | VGA_GAIN,
		.rx_vga_gain	= 0x00,
		.rx_equ_gain_1	= 0x7d,
		.rx_equ_gain_2	= 0x56,
		.rx_equ_gain_3	= 0x00,
	पूर्ण,
	अणु
		.bank		= 0x02,
		.speed		= TX_SPDSEL_20DEC | RX_SPDSEL_20DEC,
		.bias_boost_1	= 0x00,
		.bias_boost_2	= 0xae,
		.tx_ctrl_2	= 0xc0,
		.tx_ctrl_3	= 0x20,
		.rx_buff_ctrl	= EQ_BOOST_GAIN | EQ_DC_GAIN | VGA_GAIN,
		.rx_vga_gain	= 0x00,
		.rx_equ_gain_1	= 0x7d,
		.rx_equ_gain_2	= 0x56,
		.rx_equ_gain_3	= 0x00,
	पूर्ण,
पूर्ण;

अटल काष्ठा miphy28lp_pll_gen pcie_pll_gen[] = अणु
	अणु
		.bank		= 0x00,
		.speed		= TX_SPDSEL_40DEC | RX_SPDSEL_40DEC,
		.bias_boost_1	= 0x00,
		.bias_boost_2	= 0xa5,
		.tx_ctrl_1	= TX_REG_STEP_N_25MV,
		.tx_ctrl_2	= 0x71,
		.tx_ctrl_3	= 0x60,
		.rx_k_gain	= 0x98,
		.rx_buff_ctrl	= EQ_BOOST_GAIN | EQ_DC_GAIN | VGA_GAIN,
		.rx_vga_gain	= 0x00,
		.rx_equ_gain_1	= 0x79,
		.rx_equ_gain_2	= 0x56,
	पूर्ण,
	अणु
		.bank		= 0x01,
		.speed		= TX_SPDSEL_20DEC | RX_SPDSEL_20DEC,
		.bias_boost_1	= 0x00,
		.bias_boost_2	= 0xa5,
		.tx_ctrl_1	= TX_REG_STEP_N_25MV,
		.tx_ctrl_2	= 0x70,
		.tx_ctrl_3	= 0x60,
		.rx_k_gain	= 0xcc,
		.rx_buff_ctrl	= EQ_BOOST_GAIN | EQ_DC_GAIN | VGA_GAIN,
		.rx_vga_gain	= 0x00,
		.rx_equ_gain_1	= 0x78,
		.rx_equ_gain_2	= 0x07,
	पूर्ण,
पूर्ण;

अटल अंतरभूत व्योम miphy28lp_set_reset(काष्ठा miphy28lp_phy *miphy_phy)
अणु
	व्योम __iomem *base = miphy_phy->base;
	u8 val;

	/* Putting Macro in reset */
	ग_लिखोb_relaxed(RST_APPLI_SW, base + MIPHY_CONF_RESET);

	val = RST_APPLI_SW | RST_CONF_SW;
	ग_लिखोb_relaxed(val, base + MIPHY_CONF_RESET);

	ग_लिखोb_relaxed(RST_APPLI_SW, base + MIPHY_CONF_RESET);

	/* Bringing the MIPHY-CPU रेजिस्टरs out of reset */
	अगर (miphy_phy->type == PHY_TYPE_PCIE) अणु
		val = AUTO_RST_RX | TERM_EN_SW;
		ग_लिखोb_relaxed(val, base + MIPHY_CONTROL);
	पूर्ण अन्यथा अणु
		val = AUTO_RST_RX | TERM_EN_SW | DIS_LINK_RST;
		ग_लिखोb_relaxed(val, base + MIPHY_CONTROL);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम miphy28lp_pll_calibration(काष्ठा miphy28lp_phy *miphy_phy,
		काष्ठा pll_ratio *pll_ratio)
अणु
	व्योम __iomem *base = miphy_phy->base;
	u8 val;

	/* Applying PLL Settings */
	ग_लिखोb_relaxed(0x1d, base + MIPHY_PLL_SPAREIN);
	ग_लिखोb_relaxed(pll_ratio->clk_ref, base + MIPHY_PLL_CLKREF_FREQ);

	/* PLL Ratio */
	ग_लिखोb_relaxed(pll_ratio->calset_1, base + MIPHY_PLL_CALSET_1);
	ग_लिखोb_relaxed(pll_ratio->calset_2, base + MIPHY_PLL_CALSET_2);
	ग_लिखोb_relaxed(pll_ratio->calset_3, base + MIPHY_PLL_CALSET_3);
	ग_लिखोb_relaxed(pll_ratio->calset_4, base + MIPHY_PLL_CALSET_4);
	ग_लिखोb_relaxed(pll_ratio->cal_ctrl, base + MIPHY_PLL_CALSET_CTRL);

	ग_लिखोb_relaxed(TX_SEL, base + MIPHY_BOUNDARY_SEL);

	val = (0x68 << 1) | TX_SLEW_CAL_MAN_EN;
	ग_लिखोb_relaxed(val, base + MIPHY_TX_CAL_MAN);

	val = VGA_OFFSET_POLARITY | CAL_OFFSET_THRESHOLD_64 | CAL_OFFSET_VGA_64;

	अगर (miphy_phy->type != PHY_TYPE_SATA)
		val |= OFFSET_COMPENSATION_EN;

	ग_लिखोb_relaxed(val, base + MIPHY_RX_CAL_OFFSET_CTRL);

	अगर (miphy_phy->type == PHY_TYPE_USB3) अणु
		ग_लिखोb_relaxed(0x00, base + MIPHY_CONF);
		ग_लिखोb_relaxed(0x70, base + MIPHY_RX_LOCK_STEP);
		ग_लिखोb_relaxed(EN_FIRST_HALF, base + MIPHY_RX_SIGDET_SLEEP_OA);
		ग_लिखोb_relaxed(EN_FIRST_HALF, base + MIPHY_RX_SIGDET_SLEEP_SEL);
		ग_लिखोb_relaxed(EN_FIRST_HALF, base + MIPHY_RX_SIGDET_WAIT_SEL);

		val = EN_DIGIT_SIGNAL_CHECK | EN_FIRST_HALF;
		ग_लिखोb_relaxed(val, base + MIPHY_RX_SIGDET_DATA_SEL);
	पूर्ण

पूर्ण

अटल अंतरभूत व्योम miphy28lp_sata_config_gen(काष्ठा miphy28lp_phy *miphy_phy)
अणु
	व्योम __iomem *base = miphy_phy->base;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(sata_pll_gen); i++) अणु
		काष्ठा miphy28lp_pll_gen *gen = &sata_pll_gen[i];

		/* Banked settings */
		ग_लिखोb_relaxed(gen->bank, base + MIPHY_CONF);
		ग_लिखोb_relaxed(gen->speed, base + MIPHY_SPEED);
		ग_लिखोb_relaxed(gen->bias_boost_1, base + MIPHY_BIAS_BOOST_1);
		ग_लिखोb_relaxed(gen->bias_boost_2, base + MIPHY_BIAS_BOOST_2);

		/* TX buffer Settings */
		ग_लिखोb_relaxed(gen->tx_ctrl_2, base + MIPHY_TX_CTRL_2);
		ग_लिखोb_relaxed(gen->tx_ctrl_3, base + MIPHY_TX_CTRL_3);

		/* RX Buffer Settings */
		ग_लिखोb_relaxed(gen->rx_buff_ctrl, base + MIPHY_RX_BUFFER_CTRL);
		ग_लिखोb_relaxed(gen->rx_vga_gain, base + MIPHY_RX_VGA_GAIN);
		ग_लिखोb_relaxed(gen->rx_equ_gain_1, base + MIPHY_RX_EQU_GAIN_1);
		ग_लिखोb_relaxed(gen->rx_equ_gain_2, base + MIPHY_RX_EQU_GAIN_2);
		ग_लिखोb_relaxed(gen->rx_equ_gain_3, base + MIPHY_RX_EQU_GAIN_3);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम miphy28lp_pcie_config_gen(काष्ठा miphy28lp_phy *miphy_phy)
अणु
	व्योम __iomem *base = miphy_phy->base;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pcie_pll_gen); i++) अणु
		काष्ठा miphy28lp_pll_gen *gen = &pcie_pll_gen[i];

		/* Banked settings */
		ग_लिखोb_relaxed(gen->bank, base + MIPHY_CONF);
		ग_लिखोb_relaxed(gen->speed, base + MIPHY_SPEED);
		ग_लिखोb_relaxed(gen->bias_boost_1, base + MIPHY_BIAS_BOOST_1);
		ग_लिखोb_relaxed(gen->bias_boost_2, base + MIPHY_BIAS_BOOST_2);

		/* TX buffer Settings */
		ग_लिखोb_relaxed(gen->tx_ctrl_1, base + MIPHY_TX_CTRL_1);
		ग_लिखोb_relaxed(gen->tx_ctrl_2, base + MIPHY_TX_CTRL_2);
		ग_लिखोb_relaxed(gen->tx_ctrl_3, base + MIPHY_TX_CTRL_3);

		ग_लिखोb_relaxed(gen->rx_k_gain, base + MIPHY_RX_K_GAIN);

		/* RX Buffer Settings */
		ग_लिखोb_relaxed(gen->rx_buff_ctrl, base + MIPHY_RX_BUFFER_CTRL);
		ग_लिखोb_relaxed(gen->rx_vga_gain, base + MIPHY_RX_VGA_GAIN);
		ग_लिखोb_relaxed(gen->rx_equ_gain_1, base + MIPHY_RX_EQU_GAIN_1);
		ग_लिखोb_relaxed(gen->rx_equ_gain_2, base + MIPHY_RX_EQU_GAIN_2);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक miphy28lp_रुको_compensation(काष्ठा miphy28lp_phy *miphy_phy)
अणु
	अचिन्हित दीर्घ finish = jअगरfies + 5 * HZ;
	u8 val;

	/* Waiting क्रम Compensation to complete */
	करो अणु
		val = पढ़ोb_relaxed(miphy_phy->base + MIPHY_COMP_FSM_6);

		अगर (समय_after_eq(jअगरfies, finish))
			वापस -EBUSY;
		cpu_relax();
	पूर्ण जबतक (!(val & COMP_DONE));

	वापस 0;
पूर्ण


अटल अंतरभूत पूर्णांक miphy28lp_compensation(काष्ठा miphy28lp_phy *miphy_phy,
		काष्ठा pll_ratio *pll_ratio)
अणु
	व्योम __iomem *base = miphy_phy->base;

	/* Poll क्रम HFC पढ़ोy after reset release */
	/* Compensation measurement */
	ग_लिखोb_relaxed(RST_PLL_SW | RST_COMP_SW, base + MIPHY_RESET);

	ग_लिखोb_relaxed(0x00, base + MIPHY_PLL_COMMON_MISC_2);
	ग_लिखोb_relaxed(pll_ratio->clk_ref, base + MIPHY_PLL_CLKREF_FREQ);
	ग_लिखोb_relaxed(COMP_START, base + MIPHY_COMP_FSM_1);

	अगर (miphy_phy->type == PHY_TYPE_PCIE)
		ग_लिखोb_relaxed(RST_PLL_SW, base + MIPHY_RESET);

	ग_लिखोb_relaxed(0x00, base + MIPHY_RESET);
	ग_लिखोb_relaxed(START_ACT_FILT, base + MIPHY_PLL_COMMON_MISC_2);
	ग_लिखोb_relaxed(SET_NEW_CHANGE, base + MIPHY_PLL_SBR_1);

	/* TX compensation offset to re-center TX impedance */
	ग_लिखोb_relaxed(0x00, base + MIPHY_COMP_POSTP);

	अगर (miphy_phy->type == PHY_TYPE_PCIE)
		वापस miphy28lp_रुको_compensation(miphy_phy);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम miphy28_usb3_miphy_reset(काष्ठा miphy28lp_phy *miphy_phy)
अणु
	व्योम __iomem *base = miphy_phy->base;
	u8 val;

	/* MIPHY Reset */
	ग_लिखोb_relaxed(RST_APPLI_SW, base + MIPHY_CONF_RESET);
	ग_लिखोb_relaxed(0x00, base + MIPHY_CONF_RESET);
	ग_लिखोb_relaxed(RST_COMP_SW, base + MIPHY_RESET);

	val = RST_COMP_SW | RST_PLL_SW;
	ग_लिखोb_relaxed(val, base + MIPHY_RESET);

	ग_लिखोb_relaxed(0x00, base + MIPHY_PLL_COMMON_MISC_2);
	ग_लिखोb_relaxed(0x1e, base + MIPHY_PLL_CLKREF_FREQ);
	ग_लिखोb_relaxed(COMP_START, base + MIPHY_COMP_FSM_1);
	ग_लिखोb_relaxed(RST_PLL_SW, base + MIPHY_RESET);
	ग_लिखोb_relaxed(0x00, base + MIPHY_RESET);
	ग_लिखोb_relaxed(START_ACT_FILT, base + MIPHY_PLL_COMMON_MISC_2);
	ग_लिखोb_relaxed(0x00, base + MIPHY_CONF);
	ग_लिखोb_relaxed(0x00, base + MIPHY_BOUNDARY_1);
	ग_लिखोb_relaxed(0x00, base + MIPHY_TST_BIAS_BOOST_2);
	ग_लिखोb_relaxed(0x00, base + MIPHY_CONF);
	ग_लिखोb_relaxed(SET_NEW_CHANGE, base + MIPHY_PLL_SBR_1);
	ग_लिखोb_relaxed(0xa5, base + MIPHY_DEBUG_BUS);
	ग_लिखोb_relaxed(0x00, base + MIPHY_CONF);
पूर्ण

अटल व्योम miphy_sata_tune_ssc(काष्ठा miphy28lp_phy *miphy_phy)
अणु
	व्योम __iomem *base = miphy_phy->base;
	u8 val;

	/* Compensate Tx impedance to aव्योम out of range values */
	/*
	 * Enable the SSC on PLL क्रम all banks
	 * SSC Modulation @ 31 KHz and 4000 ppm modulation amp
	 */
	val = पढ़ोb_relaxed(base + MIPHY_BOUNDARY_2);
	val |= SSC_EN_SW;
	ग_लिखोb_relaxed(val, base + MIPHY_BOUNDARY_2);

	val = पढ़ोb_relaxed(base + MIPHY_BOUNDARY_SEL);
	val |= SSC_SEL;
	ग_लिखोb_relaxed(val, base + MIPHY_BOUNDARY_SEL);

	क्रम (val = 0; val < MIPHY_SATA_BANK_NB; val++) अणु
		ग_लिखोb_relaxed(val, base + MIPHY_CONF);

		/* Add value to each reference घड़ी cycle  */
		/* and define the period length of the SSC */
		ग_लिखोb_relaxed(0x3c, base + MIPHY_PLL_SBR_2);
		ग_लिखोb_relaxed(0x6c, base + MIPHY_PLL_SBR_3);
		ग_लिखोb_relaxed(0x81, base + MIPHY_PLL_SBR_4);

		/* Clear any previous request */
		ग_लिखोb_relaxed(0x00, base + MIPHY_PLL_SBR_1);

		/* requests the PLL to take in account new parameters */
		ग_लिखोb_relaxed(SET_NEW_CHANGE, base + MIPHY_PLL_SBR_1);

		/* To be sure there is no other pending requests */
		ग_लिखोb_relaxed(0x00, base + MIPHY_PLL_SBR_1);
	पूर्ण
पूर्ण

अटल व्योम miphy_pcie_tune_ssc(काष्ठा miphy28lp_phy *miphy_phy)
अणु
	व्योम __iomem *base = miphy_phy->base;
	u8 val;

	/* Compensate Tx impedance to aव्योम out of range values */
	/*
	 * Enable the SSC on PLL क्रम all banks
	 * SSC Modulation @ 31 KHz and 4000 ppm modulation amp
	 */
	val = पढ़ोb_relaxed(base + MIPHY_BOUNDARY_2);
	val |= SSC_EN_SW;
	ग_लिखोb_relaxed(val, base + MIPHY_BOUNDARY_2);

	val = पढ़ोb_relaxed(base + MIPHY_BOUNDARY_SEL);
	val |= SSC_SEL;
	ग_लिखोb_relaxed(val, base + MIPHY_BOUNDARY_SEL);

	क्रम (val = 0; val < MIPHY_PCIE_BANK_NB; val++) अणु
		ग_लिखोb_relaxed(val, base + MIPHY_CONF);

		/* Validate Step component */
		ग_लिखोb_relaxed(0x69, base + MIPHY_PLL_SBR_3);
		ग_लिखोb_relaxed(0x21, base + MIPHY_PLL_SBR_4);

		/* Validate Period component */
		ग_लिखोb_relaxed(0x3c, base + MIPHY_PLL_SBR_2);
		ग_लिखोb_relaxed(0x21, base + MIPHY_PLL_SBR_4);

		/* Clear any previous request */
		ग_लिखोb_relaxed(0x00, base + MIPHY_PLL_SBR_1);

		/* requests the PLL to take in account new parameters */
		ग_लिखोb_relaxed(SET_NEW_CHANGE, base + MIPHY_PLL_SBR_1);

		/* To be sure there is no other pending requests */
		ग_लिखोb_relaxed(0x00, base + MIPHY_PLL_SBR_1);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम miphy_tune_tx_impedance(काष्ठा miphy28lp_phy *miphy_phy)
अणु
	/* Compensate Tx impedance to aव्योम out of range values */
	ग_लिखोb_relaxed(0x02, miphy_phy->base + MIPHY_COMP_POSTP);
पूर्ण

अटल अंतरभूत पूर्णांक miphy28lp_configure_sata(काष्ठा miphy28lp_phy *miphy_phy)
अणु
	व्योम __iomem *base = miphy_phy->base;
	पूर्णांक err;
	u8 val;

	/* Putting Macro in reset */
	miphy28lp_set_reset(miphy_phy);

	/* PLL calibration */
	miphy28lp_pll_calibration(miphy_phy, &sata_pll_ratio);

	/* Banked settings Gen1/Gen2/Gen3 */
	miphy28lp_sata_config_gen(miphy_phy);

	/* Power control */
	/* Input bridge enable, manual input bridge control */
	ग_लिखोb_relaxed(0x21, base + MIPHY_RX_POWER_CTRL_1);

	/* Macro out of reset */
	ग_लिखोb_relaxed(0x00, base + MIPHY_CONF_RESET);

	/* Poll क्रम HFC पढ़ोy after reset release */
	/* Compensation measurement */
	err = miphy28lp_compensation(miphy_phy, &sata_pll_ratio);
	अगर (err)
		वापस err;

	अगर (miphy_phy->px_rx_pol_inv) अणु
		/* Invert Rx polarity */
		val = पढ़ोb_relaxed(miphy_phy->base + MIPHY_CONTROL);
		val |= PX_RX_POL;
		ग_लिखोb_relaxed(val, miphy_phy->base + MIPHY_CONTROL);
	पूर्ण

	अगर (miphy_phy->ssc)
		miphy_sata_tune_ssc(miphy_phy);

	अगर (miphy_phy->tx_impedance)
		miphy_tune_tx_impedance(miphy_phy);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक miphy28lp_configure_pcie(काष्ठा miphy28lp_phy *miphy_phy)
अणु
	व्योम __iomem *base = miphy_phy->base;
	पूर्णांक err;

	/* Putting Macro in reset */
	miphy28lp_set_reset(miphy_phy);

	/* PLL calibration */
	miphy28lp_pll_calibration(miphy_phy, &pcie_pll_ratio);

	/* Banked settings Gen1/Gen2 */
	miphy28lp_pcie_config_gen(miphy_phy);

	/* Power control */
	/* Input bridge enable, manual input bridge control */
	ग_लिखोb_relaxed(0x21, base + MIPHY_RX_POWER_CTRL_1);

	/* Macro out of reset */
	ग_लिखोb_relaxed(0x00, base + MIPHY_CONF_RESET);

	/* Poll क्रम HFC पढ़ोy after reset release */
	/* Compensation measurement */
	err = miphy28lp_compensation(miphy_phy, &pcie_pll_ratio);
	अगर (err)
		वापस err;

	अगर (miphy_phy->ssc)
		miphy_pcie_tune_ssc(miphy_phy);

	अगर (miphy_phy->tx_impedance)
		miphy_tune_tx_impedance(miphy_phy);

	वापस 0;
पूर्ण


अटल अंतरभूत व्योम miphy28lp_configure_usb3(काष्ठा miphy28lp_phy *miphy_phy)
अणु
	व्योम __iomem *base = miphy_phy->base;
	u8 val;

	/* Putting Macro in reset */
	miphy28lp_set_reset(miphy_phy);

	/* PLL calibration */
	miphy28lp_pll_calibration(miphy_phy, &usb3_pll_ratio);

	/* Writing The Speed Rate */
	ग_लिखोb_relaxed(0x00, base + MIPHY_CONF);

	val = RX_SPDSEL_20DEC | TX_SPDSEL_20DEC;
	ग_लिखोb_relaxed(val, base + MIPHY_SPEED);

	/* RX Channel compensation and calibration */
	ग_लिखोb_relaxed(0x1c, base + MIPHY_RX_LOCK_SETTINGS_OPT);
	ग_लिखोb_relaxed(0x51, base + MIPHY_RX_CAL_CTRL_1);
	ग_लिखोb_relaxed(0x70, base + MIPHY_RX_CAL_CTRL_2);

	val = OFFSET_COMPENSATION_EN | VGA_OFFSET_POLARITY |
	      CAL_OFFSET_THRESHOLD_64 | CAL_OFFSET_VGA_64;
	ग_लिखोb_relaxed(val, base + MIPHY_RX_CAL_OFFSET_CTRL);
	ग_लिखोb_relaxed(0x22, base + MIPHY_RX_CAL_VGA_STEP);
	ग_लिखोb_relaxed(0x0e, base + MIPHY_RX_CAL_OPT_LENGTH);

	val = EQ_DC_GAIN | VGA_GAIN;
	ग_लिखोb_relaxed(val, base + MIPHY_RX_BUFFER_CTRL);
	ग_लिखोb_relaxed(0x78, base + MIPHY_RX_EQU_GAIN_1);
	ग_लिखोb_relaxed(0x1b, base + MIPHY_SYNCHAR_CONTROL);

	/* TX compensation offset to re-center TX impedance */
	ग_लिखोb_relaxed(0x02, base + MIPHY_COMP_POSTP);

	/* Enable GENSEL_SEL and SSC */
	/* TX_SEL=0 swing preemp क्रमced by pipe registres */
	val = SSC_SEL | GENSEL_SEL;
	ग_लिखोb_relaxed(val, base + MIPHY_BOUNDARY_SEL);

	/* MIPHY Bias boost */
	ग_लिखोb_relaxed(0x00, base + MIPHY_BIAS_BOOST_1);
	ग_लिखोb_relaxed(0xa7, base + MIPHY_BIAS_BOOST_2);

	/* SSC modulation */
	ग_लिखोb_relaxed(SSC_EN_SW, base + MIPHY_BOUNDARY_2);

	/* MIPHY TX control */
	ग_लिखोb_relaxed(0x00, base + MIPHY_CONF);

	/* Validate Step component */
	ग_लिखोb_relaxed(0x5a, base + MIPHY_PLL_SBR_3);
	ग_लिखोb_relaxed(0xa0, base + MIPHY_PLL_SBR_4);

	/* Validate Period component */
	ग_लिखोb_relaxed(0x3c, base + MIPHY_PLL_SBR_2);
	ग_लिखोb_relaxed(0xa1, base + MIPHY_PLL_SBR_4);

	/* Clear any previous request */
	ग_लिखोb_relaxed(0x00, base + MIPHY_PLL_SBR_1);

	/* requests the PLL to take in account new parameters */
	ग_लिखोb_relaxed(0x02, base + MIPHY_PLL_SBR_1);

	/* To be sure there is no other pending requests */
	ग_लिखोb_relaxed(0x00, base + MIPHY_PLL_SBR_1);

	/* Rx PI controller settings */
	ग_लिखोb_relaxed(0xca, base + MIPHY_RX_K_GAIN);

	/* MIPHY RX input bridge control */
	/* INPUT_BRIDGE_EN_SW=1, manual input bridge control[0]=1 */
	ग_लिखोb_relaxed(0x21, base + MIPHY_RX_POWER_CTRL_1);
	ग_लिखोb_relaxed(0x29, base + MIPHY_RX_POWER_CTRL_1);
	ग_लिखोb_relaxed(0x1a, base + MIPHY_RX_POWER_CTRL_2);

	/* MIPHY Reset क्रम usb3 */
	miphy28_usb3_miphy_reset(miphy_phy);
पूर्ण

अटल अंतरभूत पूर्णांक miphy_is_पढ़ोy(काष्ठा miphy28lp_phy *miphy_phy)
अणु
	अचिन्हित दीर्घ finish = jअगरfies + 5 * HZ;
	u8 mask = HFC_PLL | HFC_RDY;
	u8 val;

	/*
	 * For PCIe and USB3 check only that PLL and HFC are पढ़ोy
	 * For SATA check also that phy is पढ़ोy!
	 */
	अगर (miphy_phy->type == PHY_TYPE_SATA)
		mask |= PHY_RDY;

	करो अणु
		val = पढ़ोb_relaxed(miphy_phy->base + MIPHY_STATUS_1);
		अगर ((val & mask) != mask)
			cpu_relax();
		अन्यथा
			वापस 0;
	पूर्ण जबतक (!समय_after_eq(jअगरfies, finish));

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक miphy_osc_is_पढ़ोy(काष्ठा miphy28lp_phy *miphy_phy)
अणु
	काष्ठा miphy28lp_dev *miphy_dev = miphy_phy->phydev;
	अचिन्हित दीर्घ finish = jअगरfies + 5 * HZ;
	u32 val;

	अगर (!miphy_phy->osc_rdy)
		वापस 0;

	अगर (!miphy_phy->syscfg_reg[SYSCFG_STATUS])
		वापस -EINVAL;

	करो अणु
		regmap_पढ़ो(miphy_dev->regmap,
				miphy_phy->syscfg_reg[SYSCFG_STATUS], &val);

		अगर ((val & MIPHY_OSC_RDY) != MIPHY_OSC_RDY)
			cpu_relax();
		अन्यथा
			वापस 0;
	पूर्ण जबतक (!समय_after_eq(jअगरfies, finish));

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक miphy28lp_get_resource_byname(काष्ठा device_node *child,
					  अक्षर *rname, काष्ठा resource *res)
अणु
	पूर्णांक index;

	index = of_property_match_string(child, "reg-names", rname);
	अगर (index < 0)
		वापस -ENODEV;

	वापस of_address_to_resource(child, index, res);
पूर्ण

अटल पूर्णांक miphy28lp_get_one_addr(काष्ठा device *dev,
				  काष्ठा device_node *child, अक्षर *rname,
				  व्योम __iomem **base)
अणु
	काष्ठा resource res;
	पूर्णांक ret;

	ret = miphy28lp_get_resource_byname(child, rname, &res);
	अगर (!ret) अणु
		*base = devm_ioremap(dev, res.start, resource_size(&res));
		अगर (!*base) अणु
			dev_err(dev, "failed to ioremap %s address region\n"
					, rname);
			वापस -ENOENT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* MiPHY reset and sysconf setup */
अटल पूर्णांक miphy28lp_setup(काष्ठा miphy28lp_phy *miphy_phy, u32 miphy_val)
अणु
	पूर्णांक err;
	काष्ठा miphy28lp_dev *miphy_dev = miphy_phy->phydev;

	अगर (!miphy_phy->syscfg_reg[SYSCFG_CTRL])
		वापस -EINVAL;

	err = reset_control_निश्चित(miphy_phy->miphy_rst);
	अगर (err) अणु
		dev_err(miphy_dev->dev, "unable to bring out of miphy reset\n");
		वापस err;
	पूर्ण

	अगर (miphy_phy->osc_क्रमce_ext)
		miphy_val |= MIPHY_OSC_FORCE_EXT;

	regmap_update_bits(miphy_dev->regmap,
			   miphy_phy->syscfg_reg[SYSCFG_CTRL],
			   MIPHY_CTRL_MASK, miphy_val);

	err = reset_control_deनिश्चित(miphy_phy->miphy_rst);
	अगर (err) अणु
		dev_err(miphy_dev->dev, "unable to bring out of miphy reset\n");
		वापस err;
	पूर्ण

	वापस miphy_osc_is_पढ़ोy(miphy_phy);
पूर्ण

अटल पूर्णांक miphy28lp_init_sata(काष्ठा miphy28lp_phy *miphy_phy)
अणु
	काष्ठा miphy28lp_dev *miphy_dev = miphy_phy->phydev;
	पूर्णांक err, sata_conf = SATA_CTRL_SELECT_SATA;

	अगर ((!miphy_phy->syscfg_reg[SYSCFG_SATA]) ||
			(!miphy_phy->syscfg_reg[SYSCFG_PCI]) ||
			(!miphy_phy->base))
		वापस -EINVAL;

	dev_info(miphy_dev->dev, "sata-up mode, addr 0x%p\n", miphy_phy->base);

	/* Configure the glue-logic */
	sata_conf |= ((miphy_phy->sata_gen - SATA_GEN1) << SATA_SPDMODE);

	regmap_update_bits(miphy_dev->regmap,
			   miphy_phy->syscfg_reg[SYSCFG_SATA],
			   SATA_CTRL_MASK, sata_conf);

	regmap_update_bits(miphy_dev->regmap, miphy_phy->syscfg_reg[SYSCFG_PCI],
			   PCIE_CTRL_MASK, SATA_CTRL_SELECT_PCIE);

	/* MiPHY path and घड़ीing init */
	err = miphy28lp_setup(miphy_phy, MIPHY_CTRL_DEFAULT);

	अगर (err) अणु
		dev_err(miphy_dev->dev, "SATA phy setup failed\n");
		वापस err;
	पूर्ण

	/* initialize miphy */
	miphy28lp_configure_sata(miphy_phy);

	वापस miphy_is_पढ़ोy(miphy_phy);
पूर्ण

अटल पूर्णांक miphy28lp_init_pcie(काष्ठा miphy28lp_phy *miphy_phy)
अणु
	काष्ठा miphy28lp_dev *miphy_dev = miphy_phy->phydev;
	पूर्णांक err;

	अगर ((!miphy_phy->syscfg_reg[SYSCFG_SATA]) ||
			(!miphy_phy->syscfg_reg[SYSCFG_PCI])
		|| (!miphy_phy->base) || (!miphy_phy->pipebase))
		वापस -EINVAL;

	dev_info(miphy_dev->dev, "pcie-up mode, addr 0x%p\n", miphy_phy->base);

	/* Configure the glue-logic */
	regmap_update_bits(miphy_dev->regmap,
			   miphy_phy->syscfg_reg[SYSCFG_SATA],
			   SATA_CTRL_MASK, SATA_CTRL_SELECT_PCIE);

	regmap_update_bits(miphy_dev->regmap, miphy_phy->syscfg_reg[SYSCFG_PCI],
			   PCIE_CTRL_MASK, SYSCFG_PCIE_PCIE_VAL);

	/* MiPHY path and घड़ीing init */
	err = miphy28lp_setup(miphy_phy, MIPHY_CTRL_DEFAULT);

	अगर (err) अणु
		dev_err(miphy_dev->dev, "PCIe phy setup failed\n");
		वापस err;
	पूर्ण

	/* initialize miphy */
	err = miphy28lp_configure_pcie(miphy_phy);
	अगर (err)
		वापस err;

	/* PIPE Wrapper Configuration */
	ग_लिखोb_relaxed(0x68, miphy_phy->pipebase + 0x104); /* Rise_0 */
	ग_लिखोb_relaxed(0x61, miphy_phy->pipebase + 0x105); /* Rise_1 */
	ग_लिखोb_relaxed(0x68, miphy_phy->pipebase + 0x108); /* Fall_0 */
	ग_लिखोb_relaxed(0x61, miphy_phy->pipebase + 0x109); /* Fall-1 */
	ग_लिखोb_relaxed(0x68, miphy_phy->pipebase + 0x10c); /* Threshold_0 */
	ग_लिखोb_relaxed(0x60, miphy_phy->pipebase + 0x10d); /* Threshold_1 */

	/* Wait क्रम phy_पढ़ोy */
	वापस miphy_is_पढ़ोy(miphy_phy);
पूर्ण

अटल पूर्णांक miphy28lp_init_usb3(काष्ठा miphy28lp_phy *miphy_phy)
अणु
	काष्ठा miphy28lp_dev *miphy_dev = miphy_phy->phydev;
	पूर्णांक err;

	अगर ((!miphy_phy->base) || (!miphy_phy->pipebase))
		वापस -EINVAL;

	dev_info(miphy_dev->dev, "usb3-up mode, addr 0x%p\n", miphy_phy->base);

	/* MiPHY path and घड़ीing init */
	err = miphy28lp_setup(miphy_phy, MIPHY_CTRL_SYNC_D_EN);
	अगर (err) अणु
		dev_err(miphy_dev->dev, "USB3 phy setup failed\n");
		वापस err;
	पूर्ण

	/* initialize miphy */
	miphy28lp_configure_usb3(miphy_phy);

	/* PIPE Wrapper Configuration */
	ग_लिखोb_relaxed(0x68, miphy_phy->pipebase + 0x23);
	ग_लिखोb_relaxed(0x61, miphy_phy->pipebase + 0x24);
	ग_लिखोb_relaxed(0x68, miphy_phy->pipebase + 0x26);
	ग_लिखोb_relaxed(0x61, miphy_phy->pipebase + 0x27);
	ग_लिखोb_relaxed(0x18, miphy_phy->pipebase + 0x29);
	ग_लिखोb_relaxed(0x61, miphy_phy->pipebase + 0x2a);

	/* pipe Wrapper usb3 TX swing de-emph margin PREEMPH[7:4], SWING[3:0] */
	ग_लिखोb_relaxed(0X67, miphy_phy->pipebase + 0x68);
	ग_लिखोb_relaxed(0x0d, miphy_phy->pipebase + 0x69);
	ग_लिखोb_relaxed(0X67, miphy_phy->pipebase + 0x6a);
	ग_लिखोb_relaxed(0X0d, miphy_phy->pipebase + 0x6b);
	ग_लिखोb_relaxed(0X67, miphy_phy->pipebase + 0x6c);
	ग_लिखोb_relaxed(0X0d, miphy_phy->pipebase + 0x6d);
	ग_लिखोb_relaxed(0X67, miphy_phy->pipebase + 0x6e);
	ग_लिखोb_relaxed(0X0d, miphy_phy->pipebase + 0x6f);

	वापस miphy_is_पढ़ोy(miphy_phy);
पूर्ण

अटल पूर्णांक miphy28lp_init(काष्ठा phy *phy)
अणु
	काष्ठा miphy28lp_phy *miphy_phy = phy_get_drvdata(phy);
	काष्ठा miphy28lp_dev *miphy_dev = miphy_phy->phydev;
	पूर्णांक ret;

	mutex_lock(&miphy_dev->miphy_mutex);

	चयन (miphy_phy->type) अणु

	हाल PHY_TYPE_SATA:
		ret = miphy28lp_init_sata(miphy_phy);
		अवरोध;
	हाल PHY_TYPE_PCIE:
		ret = miphy28lp_init_pcie(miphy_phy);
		अवरोध;
	हाल PHY_TYPE_USB3:
		ret = miphy28lp_init_usb3(miphy_phy);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	mutex_unlock(&miphy_dev->miphy_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक miphy28lp_get_addr(काष्ठा miphy28lp_phy *miphy_phy)
अणु
	काष्ठा miphy28lp_dev *miphy_dev = miphy_phy->phydev;
	काष्ठा device_node *phynode = miphy_phy->phy->dev.of_node;
	पूर्णांक err;

	अगर ((miphy_phy->type != PHY_TYPE_SATA) &&
	    (miphy_phy->type != PHY_TYPE_PCIE) &&
	    (miphy_phy->type != PHY_TYPE_USB3)) अणु
		वापस -EINVAL;
	पूर्ण

	err = miphy28lp_get_one_addr(miphy_dev->dev, phynode,
			PHY_TYPE_name[miphy_phy->type - PHY_TYPE_SATA],
			&miphy_phy->base);
	अगर (err)
		वापस err;

	अगर ((miphy_phy->type == PHY_TYPE_PCIE) ||
	    (miphy_phy->type == PHY_TYPE_USB3)) अणु
		err = miphy28lp_get_one_addr(miphy_dev->dev, phynode, "pipew",
					     &miphy_phy->pipebase);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा phy *miphy28lp_xlate(काष्ठा device *dev,
				   काष्ठा of_phandle_args *args)
अणु
	काष्ठा miphy28lp_dev *miphy_dev = dev_get_drvdata(dev);
	काष्ठा miphy28lp_phy *miphy_phy = शून्य;
	काष्ठा device_node *phynode = args->np;
	पूर्णांक ret, index = 0;

	अगर (args->args_count != 1) अणु
		dev_err(dev, "Invalid number of cells in 'phy' property\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	क्रम (index = 0; index < miphy_dev->nphys; index++)
		अगर (phynode == miphy_dev->phys[index]->phy->dev.of_node) अणु
			miphy_phy = miphy_dev->phys[index];
			अवरोध;
		पूर्ण

	अगर (!miphy_phy) अणु
		dev_err(dev, "Failed to find appropriate phy\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	miphy_phy->type = args->args[0];

	ret = miphy28lp_get_addr(miphy_phy);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	वापस miphy_phy->phy;
पूर्ण

अटल स्थिर काष्ठा phy_ops miphy28lp_ops = अणु
	.init = miphy28lp_init,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक miphy28lp_probe_resets(काष्ठा device_node *node,
				  काष्ठा miphy28lp_phy *miphy_phy)
अणु
	काष्ठा miphy28lp_dev *miphy_dev = miphy_phy->phydev;
	पूर्णांक err;

	miphy_phy->miphy_rst =
		of_reset_control_get_shared(node, "miphy-sw-rst");

	अगर (IS_ERR(miphy_phy->miphy_rst)) अणु
		dev_err(miphy_dev->dev,
				"miphy soft reset control not defined\n");
		वापस PTR_ERR(miphy_phy->miphy_rst);
	पूर्ण

	err = reset_control_deनिश्चित(miphy_phy->miphy_rst);
	अगर (err) अणु
		dev_err(miphy_dev->dev, "unable to bring out of miphy reset\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक miphy28lp_of_probe(काष्ठा device_node *np,
			      काष्ठा miphy28lp_phy *miphy_phy)
अणु
	पूर्णांक i;
	u32 ctrlreg;

	miphy_phy->osc_क्रमce_ext =
		of_property_पढ़ो_bool(np, "st,osc-force-ext");

	miphy_phy->osc_rdy = of_property_पढ़ो_bool(np, "st,osc-rdy");

	miphy_phy->px_rx_pol_inv =
		of_property_पढ़ो_bool(np, "st,px_rx_pol_inv");

	miphy_phy->ssc = of_property_पढ़ो_bool(np, "st,ssc-on");

	miphy_phy->tx_impedance =
		of_property_पढ़ो_bool(np, "st,tx-impedance-comp");

	of_property_पढ़ो_u32(np, "st,sata-gen", &miphy_phy->sata_gen);
	अगर (!miphy_phy->sata_gen)
		miphy_phy->sata_gen = SATA_GEN1;

	क्रम (i = 0; i < SYSCFG_REG_MAX; i++) अणु
		अगर (!of_property_पढ़ो_u32_index(np, "st,syscfg", i, &ctrlreg))
			miphy_phy->syscfg_reg[i] = ctrlreg;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक miphy28lp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *child, *np = pdev->dev.of_node;
	काष्ठा miphy28lp_dev *miphy_dev;
	काष्ठा phy_provider *provider;
	काष्ठा phy *phy;
	पूर्णांक ret, port = 0;

	miphy_dev = devm_kzalloc(&pdev->dev, माप(*miphy_dev), GFP_KERNEL);
	अगर (!miphy_dev)
		वापस -ENOMEM;

	miphy_dev->nphys = of_get_child_count(np);
	miphy_dev->phys = devm_kसुस्मृति(&pdev->dev, miphy_dev->nphys,
				       माप(*miphy_dev->phys), GFP_KERNEL);
	अगर (!miphy_dev->phys)
		वापस -ENOMEM;

	miphy_dev->regmap = syscon_regmap_lookup_by_phandle(np, "st,syscfg");
	अगर (IS_ERR(miphy_dev->regmap)) अणु
		dev_err(miphy_dev->dev, "No syscfg phandle specified\n");
		वापस PTR_ERR(miphy_dev->regmap);
	पूर्ण

	miphy_dev->dev = &pdev->dev;

	dev_set_drvdata(&pdev->dev, miphy_dev);

	mutex_init(&miphy_dev->miphy_mutex);

	क्रम_each_child_of_node(np, child) अणु
		काष्ठा miphy28lp_phy *miphy_phy;

		miphy_phy = devm_kzalloc(&pdev->dev, माप(*miphy_phy),
					 GFP_KERNEL);
		अगर (!miphy_phy) अणु
			ret = -ENOMEM;
			जाओ put_child;
		पूर्ण

		miphy_dev->phys[port] = miphy_phy;

		phy = devm_phy_create(&pdev->dev, child, &miphy28lp_ops);
		अगर (IS_ERR(phy)) अणु
			dev_err(&pdev->dev, "failed to create PHY\n");
			ret = PTR_ERR(phy);
			जाओ put_child;
		पूर्ण

		miphy_dev->phys[port]->phy = phy;
		miphy_dev->phys[port]->phydev = miphy_dev;

		ret = miphy28lp_of_probe(child, miphy_phy);
		अगर (ret)
			जाओ put_child;

		ret = miphy28lp_probe_resets(child, miphy_dev->phys[port]);
		अगर (ret)
			जाओ put_child;

		phy_set_drvdata(phy, miphy_dev->phys[port]);
		port++;

	पूर्ण

	provider = devm_of_phy_provider_रेजिस्टर(&pdev->dev, miphy28lp_xlate);
	वापस PTR_ERR_OR_ZERO(provider);
put_child:
	of_node_put(child);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id miphy28lp_of_match[] = अणु
	अणु.compatible = "st,miphy28lp-phy", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, miphy28lp_of_match);

अटल काष्ठा platक्रमm_driver miphy28lp_driver = अणु
	.probe = miphy28lp_probe,
	.driver = अणु
		.name = "miphy28lp-phy",
		.of_match_table = miphy28lp_of_match,
	पूर्ण
पूर्ण;

module_platक्रमm_driver(miphy28lp_driver);

MODULE_AUTHOR("Alexandre Torgue <alexandre.torgue@st.com>");
MODULE_DESCRIPTION("STMicroelectronics miphy28lp driver");
MODULE_LICENSE("GPL v2");
