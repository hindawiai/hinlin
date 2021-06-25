<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017 Marvell
 *
 * Antoine Tenart <antoine.tenart@मुक्त-electrons.com>
 */

#समावेश <linux/arm-smccc.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/phy.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

/* Relative to priv->base */
#घोषणा MVEBU_COMPHY_SERDES_CFG0(n)		(0x0 + (n) * 0x1000)
#घोषणा     MVEBU_COMPHY_SERDES_CFG0_PU_PLL	BIT(1)
#घोषणा     MVEBU_COMPHY_SERDES_CFG0_GEN_RX(n)	((n) << 3)
#घोषणा     MVEBU_COMPHY_SERDES_CFG0_GEN_TX(n)	((n) << 7)
#घोषणा     MVEBU_COMPHY_SERDES_CFG0_PU_RX	BIT(11)
#घोषणा     MVEBU_COMPHY_SERDES_CFG0_PU_TX	BIT(12)
#घोषणा     MVEBU_COMPHY_SERDES_CFG0_HALF_BUS	BIT(14)
#घोषणा     MVEBU_COMPHY_SERDES_CFG0_RXAUI_MODE	BIT(15)
#घोषणा MVEBU_COMPHY_SERDES_CFG1(n)		(0x4 + (n) * 0x1000)
#घोषणा     MVEBU_COMPHY_SERDES_CFG1_RESET	BIT(3)
#घोषणा     MVEBU_COMPHY_SERDES_CFG1_RX_INIT	BIT(4)
#घोषणा     MVEBU_COMPHY_SERDES_CFG1_CORE_RESET	BIT(5)
#घोषणा     MVEBU_COMPHY_SERDES_CFG1_RF_RESET	BIT(6)
#घोषणा MVEBU_COMPHY_SERDES_CFG2(n)		(0x8 + (n) * 0x1000)
#घोषणा     MVEBU_COMPHY_SERDES_CFG2_DFE_EN	BIT(4)
#घोषणा MVEBU_COMPHY_SERDES_STATUS0(n)		(0x18 + (n) * 0x1000)
#घोषणा     MVEBU_COMPHY_SERDES_STATUS0_TX_PLL_RDY	BIT(2)
#घोषणा     MVEBU_COMPHY_SERDES_STATUS0_RX_PLL_RDY	BIT(3)
#घोषणा     MVEBU_COMPHY_SERDES_STATUS0_RX_INIT		BIT(4)
#घोषणा MVEBU_COMPHY_PWRPLL_CTRL(n)		(0x804 + (n) * 0x1000)
#घोषणा     MVEBU_COMPHY_PWRPLL_CTRL_RFREQ(n)	((n) << 0)
#घोषणा     MVEBU_COMPHY_PWRPLL_PHY_MODE(n)	((n) << 5)
#घोषणा MVEBU_COMPHY_IMP_CAL(n)			(0x80c + (n) * 0x1000)
#घोषणा     MVEBU_COMPHY_IMP_CAL_TX_EXT(n)	((n) << 10)
#घोषणा     MVEBU_COMPHY_IMP_CAL_TX_EXT_EN	BIT(15)
#घोषणा MVEBU_COMPHY_DFE_RES(n)			(0x81c + (n) * 0x1000)
#घोषणा     MVEBU_COMPHY_DFE_RES_FORCE_GEN_TBL	BIT(15)
#घोषणा MVEBU_COMPHY_COEF(n)			(0x828 + (n) * 0x1000)
#घोषणा     MVEBU_COMPHY_COEF_DFE_EN		BIT(14)
#घोषणा     MVEBU_COMPHY_COEF_DFE_CTRL		BIT(15)
#घोषणा MVEBU_COMPHY_GEN1_S0(n)			(0x834 + (n) * 0x1000)
#घोषणा     MVEBU_COMPHY_GEN1_S0_TX_AMP(n)	((n) << 1)
#घोषणा     MVEBU_COMPHY_GEN1_S0_TX_EMPH(n)	((n) << 7)
#घोषणा MVEBU_COMPHY_GEN1_S1(n)			(0x838 + (n) * 0x1000)
#घोषणा     MVEBU_COMPHY_GEN1_S1_RX_MUL_PI(n)	((n) << 0)
#घोषणा     MVEBU_COMPHY_GEN1_S1_RX_MUL_PF(n)	((n) << 3)
#घोषणा     MVEBU_COMPHY_GEN1_S1_RX_MUL_FI(n)	((n) << 6)
#घोषणा     MVEBU_COMPHY_GEN1_S1_RX_MUL_FF(n)	((n) << 8)
#घोषणा     MVEBU_COMPHY_GEN1_S1_RX_DFE_EN	BIT(10)
#घोषणा     MVEBU_COMPHY_GEN1_S1_RX_DIV(n)	((n) << 11)
#घोषणा MVEBU_COMPHY_GEN1_S2(n)			(0x8f4 + (n) * 0x1000)
#घोषणा     MVEBU_COMPHY_GEN1_S2_TX_EMPH(n)	((n) << 0)
#घोषणा     MVEBU_COMPHY_GEN1_S2_TX_EMPH_EN	BIT(4)
#घोषणा MVEBU_COMPHY_LOOPBACK(n)		(0x88c + (n) * 0x1000)
#घोषणा     MVEBU_COMPHY_LOOPBACK_DBUS_WIDTH(n)	((n) << 1)
#घोषणा MVEBU_COMPHY_VDD_CAL0(n)		(0x908 + (n) * 0x1000)
#घोषणा     MVEBU_COMPHY_VDD_CAL0_CONT_MODE	BIT(15)
#घोषणा MVEBU_COMPHY_EXT_SELV(n)		(0x914 + (n) * 0x1000)
#घोषणा     MVEBU_COMPHY_EXT_SELV_RX_SAMPL(n)	((n) << 5)
#घोषणा MVEBU_COMPHY_MISC_CTRL0(n)		(0x93c + (n) * 0x1000)
#घोषणा     MVEBU_COMPHY_MISC_CTRL0_ICP_FORCE	BIT(5)
#घोषणा     MVEBU_COMPHY_MISC_CTRL0_REFCLK_SEL	BIT(10)
#घोषणा MVEBU_COMPHY_RX_CTRL1(n)		(0x940 + (n) * 0x1000)
#घोषणा     MVEBU_COMPHY_RX_CTRL1_RXCLK2X_SEL	BIT(11)
#घोषणा     MVEBU_COMPHY_RX_CTRL1_CLK8T_EN	BIT(12)
#घोषणा MVEBU_COMPHY_SPEED_DIV(n)		(0x954 + (n) * 0x1000)
#घोषणा     MVEBU_COMPHY_SPEED_DIV_TX_FORCE	BIT(7)
#घोषणा MVEBU_SP_CALIB(n)			(0x96c + (n) * 0x1000)
#घोषणा     MVEBU_SP_CALIB_SAMPLER(n)		((n) << 8)
#घोषणा     MVEBU_SP_CALIB_SAMPLER_EN		BIT(12)
#घोषणा MVEBU_COMPHY_TX_SLEW_RATE(n)		(0x974 + (n) * 0x1000)
#घोषणा     MVEBU_COMPHY_TX_SLEW_RATE_EMPH(n)	((n) << 5)
#घोषणा     MVEBU_COMPHY_TX_SLEW_RATE_SLC(n)	((n) << 10)
#घोषणा MVEBU_COMPHY_DTL_CTRL(n)		(0x984 + (n) * 0x1000)
#घोषणा     MVEBU_COMPHY_DTL_CTRL_DTL_FLOOP_EN	BIT(2)
#घोषणा MVEBU_COMPHY_FRAME_DETECT0(n)		(0xa14 + (n) * 0x1000)
#घोषणा     MVEBU_COMPHY_FRAME_DETECT0_PATN(n)	((n) << 7)
#घोषणा MVEBU_COMPHY_FRAME_DETECT3(n)		(0xa20 + (n) * 0x1000)
#घोषणा     MVEBU_COMPHY_FRAME_DETECT3_LOST_TIMEOUT_EN	BIT(12)
#घोषणा MVEBU_COMPHY_DME(n)			(0xa28 + (n) * 0x1000)
#घोषणा     MVEBU_COMPHY_DME_ETH_MODE		BIT(7)
#घोषणा MVEBU_COMPHY_TRAINING0(n)		(0xa68 + (n) * 0x1000)
#घोषणा     MVEBU_COMPHY_TRAINING0_P2P_HOLD	BIT(15)
#घोषणा MVEBU_COMPHY_TRAINING5(n)		(0xaa4 + (n) * 0x1000)
#घोषणा	    MVEBU_COMPHY_TRAINING5_RX_TIMER(n)	((n) << 0)
#घोषणा MVEBU_COMPHY_TX_TRAIN_PRESET(n)		(0xb1c + (n) * 0x1000)
#घोषणा     MVEBU_COMPHY_TX_TRAIN_PRESET_16B_AUTO_EN	BIT(8)
#घोषणा     MVEBU_COMPHY_TX_TRAIN_PRESET_PRBS11		BIT(9)
#घोषणा MVEBU_COMPHY_GEN1_S3(n)			(0xc40 + (n) * 0x1000)
#घोषणा     MVEBU_COMPHY_GEN1_S3_FBCK_SEL	BIT(9)
#घोषणा MVEBU_COMPHY_GEN1_S4(n)			(0xc44 + (n) * 0x1000)
#घोषणा	    MVEBU_COMPHY_GEN1_S4_DFE_RES(n)	((n) << 8)
#घोषणा MVEBU_COMPHY_TX_PRESET(n)		(0xc68 + (n) * 0x1000)
#घोषणा     MVEBU_COMPHY_TX_PRESET_INDEX(n)	((n) << 0)
#घोषणा MVEBU_COMPHY_GEN1_S5(n)			(0xd38 + (n) * 0x1000)
#घोषणा     MVEBU_COMPHY_GEN1_S5_ICP(n)		((n) << 0)

/* Relative to priv->regmap */
#घोषणा MVEBU_COMPHY_CONF1(n)			(0x1000 + (n) * 0x28)
#घोषणा     MVEBU_COMPHY_CONF1_PWRUP		BIT(1)
#घोषणा     MVEBU_COMPHY_CONF1_USB_PCIE		BIT(2)	/* 0: Ethernet/SATA */
#घोषणा MVEBU_COMPHY_CONF6(n)			(0x1014 + (n) * 0x28)
#घोषणा     MVEBU_COMPHY_CONF6_40B		BIT(18)
#घोषणा MVEBU_COMPHY_SELECTOR			0x1140
#घोषणा     MVEBU_COMPHY_SELECTOR_PHY(n)	((n) * 0x4)
#घोषणा MVEBU_COMPHY_PIPE_SELECTOR		0x1144
#घोषणा     MVEBU_COMPHY_PIPE_SELECTOR_PIPE(n)	((n) * 0x4)
#घोषणा MVEBU_COMPHY_SD1_CTRL1			0x1148
#घोषणा     MVEBU_COMPHY_SD1_CTRL1_RXAUI1_EN	BIT(26)
#घोषणा     MVEBU_COMPHY_SD1_CTRL1_RXAUI0_EN	BIT(27)

#घोषणा MVEBU_COMPHY_LANES	6
#घोषणा MVEBU_COMPHY_PORTS	3

#घोषणा COMPHY_SIP_POWER_ON	0x82000001
#घोषणा COMPHY_SIP_POWER_OFF	0x82000002

/*
 * A lane is described by the following bitfields:
 * [ 1- 0]: COMPHY polarity invertion
 * [ 2- 7]: COMPHY speed
 * [ 5-11]: COMPHY port index
 * [12-16]: COMPHY mode
 * [17]: Clock source
 * [18-20]: PCIe width (x1, x2, x4)
 */
#घोषणा COMPHY_FW_POL_OFFSET	0
#घोषणा COMPHY_FW_POL_MASK	GENMASK(1, 0)
#घोषणा COMPHY_FW_SPEED_OFFSET	2
#घोषणा COMPHY_FW_SPEED_MASK	GENMASK(7, 2)
#घोषणा COMPHY_FW_SPEED_MAX	COMPHY_FW_SPEED_MASK
#घोषणा COMPHY_FW_SPEED_1250	0
#घोषणा COMPHY_FW_SPEED_3125	2
#घोषणा COMPHY_FW_SPEED_5000	3
#घोषणा COMPHY_FW_SPEED_103125	6
#घोषणा COMPHY_FW_PORT_OFFSET	8
#घोषणा COMPHY_FW_PORT_MASK	GENMASK(11, 8)
#घोषणा COMPHY_FW_MODE_OFFSET	12
#घोषणा COMPHY_FW_MODE_MASK	GENMASK(16, 12)
#घोषणा COMPHY_FW_WIDTH_OFFSET	18
#घोषणा COMPHY_FW_WIDTH_MASK	GENMASK(20, 18)

#घोषणा COMPHY_FW_PARAM_FULL(mode, port, speed, pol, width)		\
	((((pol) << COMPHY_FW_POL_OFFSET) & COMPHY_FW_POL_MASK) |	\
	 (((mode) << COMPHY_FW_MODE_OFFSET) & COMPHY_FW_MODE_MASK) |	\
	 (((port) << COMPHY_FW_PORT_OFFSET) & COMPHY_FW_PORT_MASK) |	\
	 (((speed) << COMPHY_FW_SPEED_OFFSET) & COMPHY_FW_SPEED_MASK) |	\
	 (((width) << COMPHY_FW_WIDTH_OFFSET) & COMPHY_FW_WIDTH_MASK))

#घोषणा COMPHY_FW_PARAM(mode, port)					\
	COMPHY_FW_PARAM_FULL(mode, port, COMPHY_FW_SPEED_MAX, 0, 0)

#घोषणा COMPHY_FW_PARAM_ETH(mode, port, speed)				\
	COMPHY_FW_PARAM_FULL(mode, port, speed, 0, 0)

#घोषणा COMPHY_FW_PARAM_PCIE(mode, port, width)				\
	COMPHY_FW_PARAM_FULL(mode, port, COMPHY_FW_SPEED_5000, 0, width)

#घोषणा COMPHY_FW_MODE_SATA		0x1
#घोषणा COMPHY_FW_MODE_SGMII		0x2 /* SGMII 1G */
#घोषणा COMPHY_FW_MODE_HS_SGMII		0x3 /* SGMII 2.5G */
#घोषणा COMPHY_FW_MODE_USB3H		0x4
#घोषणा COMPHY_FW_MODE_USB3D		0x5
#घोषणा COMPHY_FW_MODE_PCIE		0x6
#घोषणा COMPHY_FW_MODE_RXAUI		0x7
#घोषणा COMPHY_FW_MODE_XFI		0x8 /* SFI: 0x9 (is treated like XFI) */

काष्ठा mvebu_comphy_conf अणु
	क्रमागत phy_mode mode;
	पूर्णांक submode;
	अचिन्हित lane;
	अचिन्हित port;
	u32 mux;
	u32 fw_mode;
पूर्ण;

#घोषणा ETH_CONF(_lane, _port, _submode, _mux, _fw)	\
	अणु						\
		.lane = _lane,				\
		.port = _port,				\
		.mode = PHY_MODE_ETHERNET,		\
		.submode = _submode,			\
		.mux = _mux,				\
		.fw_mode = _fw,				\
	पूर्ण

#घोषणा GEN_CONF(_lane, _port, _mode, _fw)		\
	अणु						\
		.lane = _lane,				\
		.port = _port,				\
		.mode = _mode,				\
		.submode = PHY_INTERFACE_MODE_NA,	\
		.mux = -1,				\
		.fw_mode = _fw,				\
	पूर्ण

अटल स्थिर काष्ठा mvebu_comphy_conf mvebu_comphy_cp110_modes[] = अणु
	/* lane 0 */
	GEN_CONF(0, 0, PHY_MODE_PCIE, COMPHY_FW_MODE_PCIE),
	ETH_CONF(0, 1, PHY_INTERFACE_MODE_SGMII, 0x1, COMPHY_FW_MODE_SGMII),
	ETH_CONF(0, 1, PHY_INTERFACE_MODE_2500BASEX, 0x1, COMPHY_FW_MODE_HS_SGMII),
	GEN_CONF(0, 1, PHY_MODE_SATA, COMPHY_FW_MODE_SATA),
	/* lane 1 */
	GEN_CONF(1, 0, PHY_MODE_USB_HOST_SS, COMPHY_FW_MODE_USB3H),
	GEN_CONF(1, 0, PHY_MODE_USB_DEVICE_SS, COMPHY_FW_MODE_USB3D),
	GEN_CONF(1, 0, PHY_MODE_SATA, COMPHY_FW_MODE_SATA),
	GEN_CONF(1, 0, PHY_MODE_PCIE, COMPHY_FW_MODE_PCIE),
	ETH_CONF(1, 2, PHY_INTERFACE_MODE_SGMII, 0x1, COMPHY_FW_MODE_SGMII),
	ETH_CONF(1, 2, PHY_INTERFACE_MODE_2500BASEX, 0x1, COMPHY_FW_MODE_HS_SGMII),
	/* lane 2 */
	ETH_CONF(2, 0, PHY_INTERFACE_MODE_SGMII, 0x1, COMPHY_FW_MODE_SGMII),
	ETH_CONF(2, 0, PHY_INTERFACE_MODE_2500BASEX, 0x1, COMPHY_FW_MODE_HS_SGMII),
	ETH_CONF(2, 0, PHY_INTERFACE_MODE_RXAUI, 0x1, COMPHY_FW_MODE_RXAUI),
	ETH_CONF(2, 0, PHY_INTERFACE_MODE_10GBASER, 0x1, COMPHY_FW_MODE_XFI),
	GEN_CONF(2, 0, PHY_MODE_USB_HOST_SS, COMPHY_FW_MODE_USB3H),
	GEN_CONF(2, 0, PHY_MODE_SATA, COMPHY_FW_MODE_SATA),
	GEN_CONF(2, 0, PHY_MODE_PCIE, COMPHY_FW_MODE_PCIE),
	/* lane 3 */
	GEN_CONF(3, 0, PHY_MODE_PCIE, COMPHY_FW_MODE_PCIE),
	ETH_CONF(3, 1, PHY_INTERFACE_MODE_SGMII, 0x2, COMPHY_FW_MODE_SGMII),
	ETH_CONF(3, 1, PHY_INTERFACE_MODE_2500BASEX, 0x2, COMPHY_FW_MODE_HS_SGMII),
	ETH_CONF(3, 1, PHY_INTERFACE_MODE_RXAUI, 0x1, COMPHY_FW_MODE_RXAUI),
	GEN_CONF(3, 1, PHY_MODE_USB_HOST_SS, COMPHY_FW_MODE_USB3H),
	GEN_CONF(3, 1, PHY_MODE_SATA, COMPHY_FW_MODE_SATA),
	/* lane 4 */
	ETH_CONF(4, 0, PHY_INTERFACE_MODE_SGMII, 0x2, COMPHY_FW_MODE_SGMII),
	ETH_CONF(4, 0, PHY_INTERFACE_MODE_2500BASEX, 0x2, COMPHY_FW_MODE_HS_SGMII),
	ETH_CONF(4, 0, PHY_INTERFACE_MODE_10GBASER, 0x2, COMPHY_FW_MODE_XFI),
	ETH_CONF(4, 0, PHY_INTERFACE_MODE_RXAUI, 0x2, COMPHY_FW_MODE_RXAUI),
	GEN_CONF(4, 0, PHY_MODE_USB_DEVICE_SS, COMPHY_FW_MODE_USB3D),
	GEN_CONF(4, 1, PHY_MODE_USB_HOST_SS, COMPHY_FW_MODE_USB3H),
	GEN_CONF(4, 1, PHY_MODE_PCIE, COMPHY_FW_MODE_PCIE),
	ETH_CONF(4, 1, PHY_INTERFACE_MODE_SGMII, 0x1, COMPHY_FW_MODE_SGMII),
	ETH_CONF(4, 1, PHY_INTERFACE_MODE_2500BASEX, -1, COMPHY_FW_MODE_HS_SGMII),
	ETH_CONF(4, 1, PHY_INTERFACE_MODE_10GBASER, -1, COMPHY_FW_MODE_XFI),
	/* lane 5 */
	ETH_CONF(5, 1, PHY_INTERFACE_MODE_RXAUI, 0x2, COMPHY_FW_MODE_RXAUI),
	GEN_CONF(5, 1, PHY_MODE_SATA, COMPHY_FW_MODE_SATA),
	ETH_CONF(5, 2, PHY_INTERFACE_MODE_SGMII, 0x1, COMPHY_FW_MODE_SGMII),
	ETH_CONF(5, 2, PHY_INTERFACE_MODE_2500BASEX, 0x1, COMPHY_FW_MODE_HS_SGMII),
	GEN_CONF(5, 2, PHY_MODE_PCIE, COMPHY_FW_MODE_PCIE),
पूर्ण;

काष्ठा mvebu_comphy_priv अणु
	व्योम __iomem *base;
	काष्ठा regmap *regmap;
	काष्ठा device *dev;
	काष्ठा clk *mg_करोमुख्य_clk;
	काष्ठा clk *mg_core_clk;
	काष्ठा clk *axi_clk;
	अचिन्हित दीर्घ cp_phys;
पूर्ण;

काष्ठा mvebu_comphy_lane अणु
	काष्ठा mvebu_comphy_priv *priv;
	अचिन्हित id;
	क्रमागत phy_mode mode;
	पूर्णांक submode;
	पूर्णांक port;
पूर्ण;

अटल पूर्णांक mvebu_comphy_smc(अचिन्हित दीर्घ function, अचिन्हित दीर्घ phys,
			    अचिन्हित दीर्घ lane, अचिन्हित दीर्घ mode)
अणु
	काष्ठा arm_smccc_res res;
	s32 ret;

	arm_smccc_smc(function, phys, lane, mode, 0, 0, 0, 0, &res);
	ret = res.a0;

	चयन (ret) अणु
	हाल SMCCC_RET_SUCCESS:
		वापस 0;
	हाल SMCCC_RET_NOT_SUPPORTED:
		वापस -EOPNOTSUPP;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mvebu_comphy_get_mode(bool fw_mode, पूर्णांक lane, पूर्णांक port,
				 क्रमागत phy_mode mode, पूर्णांक submode)
अणु
	पूर्णांक i, n = ARRAY_SIZE(mvebu_comphy_cp110_modes);
	/* Ignore PCIe submode: it represents the width */
	bool ignore_submode = (mode == PHY_MODE_PCIE);
	स्थिर काष्ठा mvebu_comphy_conf *conf;

	/* Unused PHY mux value is 0x0 */
	अगर (mode == PHY_MODE_INVALID)
		वापस 0;

	क्रम (i = 0; i < n; i++) अणु
		conf = &mvebu_comphy_cp110_modes[i];
		अगर (conf->lane == lane &&
		    conf->port == port &&
		    conf->mode == mode &&
		    (conf->submode == submode || ignore_submode))
			अवरोध;
	पूर्ण

	अगर (i == n)
		वापस -EINVAL;

	अगर (fw_mode)
		वापस conf->fw_mode;
	अन्यथा
		वापस conf->mux;
पूर्ण

अटल अंतरभूत पूर्णांक mvebu_comphy_get_mux(पूर्णांक lane, पूर्णांक port,
				       क्रमागत phy_mode mode, पूर्णांक submode)
अणु
	वापस mvebu_comphy_get_mode(false, lane, port, mode, submode);
पूर्ण

अटल अंतरभूत पूर्णांक mvebu_comphy_get_fw_mode(पूर्णांक lane, पूर्णांक port,
					   क्रमागत phy_mode mode, पूर्णांक submode)
अणु
	वापस mvebu_comphy_get_mode(true, lane, port, mode, submode);
पूर्ण

अटल पूर्णांक mvebu_comphy_ethernet_init_reset(काष्ठा mvebu_comphy_lane *lane)
अणु
	काष्ठा mvebu_comphy_priv *priv = lane->priv;
	u32 val;

	regmap_पढ़ो(priv->regmap, MVEBU_COMPHY_CONF1(lane->id), &val);
	val &= ~MVEBU_COMPHY_CONF1_USB_PCIE;
	val |= MVEBU_COMPHY_CONF1_PWRUP;
	regmap_ग_लिखो(priv->regmap, MVEBU_COMPHY_CONF1(lane->id), val);

	/* Select baud rates and PLLs */
	val = पढ़ोl(priv->base + MVEBU_COMPHY_SERDES_CFG0(lane->id));
	val &= ~(MVEBU_COMPHY_SERDES_CFG0_PU_PLL |
		 MVEBU_COMPHY_SERDES_CFG0_PU_RX |
		 MVEBU_COMPHY_SERDES_CFG0_PU_TX |
		 MVEBU_COMPHY_SERDES_CFG0_HALF_BUS |
		 MVEBU_COMPHY_SERDES_CFG0_GEN_RX(0xf) |
		 MVEBU_COMPHY_SERDES_CFG0_GEN_TX(0xf) |
		 MVEBU_COMPHY_SERDES_CFG0_RXAUI_MODE);

	चयन (lane->submode) अणु
	हाल PHY_INTERFACE_MODE_10GBASER:
		val |= MVEBU_COMPHY_SERDES_CFG0_GEN_RX(0xe) |
		       MVEBU_COMPHY_SERDES_CFG0_GEN_TX(0xe);
		अवरोध;
	हाल PHY_INTERFACE_MODE_RXAUI:
		val |= MVEBU_COMPHY_SERDES_CFG0_GEN_RX(0xb) |
		       MVEBU_COMPHY_SERDES_CFG0_GEN_TX(0xb) |
		       MVEBU_COMPHY_SERDES_CFG0_RXAUI_MODE;
		अवरोध;
	हाल PHY_INTERFACE_MODE_2500BASEX:
		val |= MVEBU_COMPHY_SERDES_CFG0_GEN_RX(0x8) |
		       MVEBU_COMPHY_SERDES_CFG0_GEN_TX(0x8) |
		       MVEBU_COMPHY_SERDES_CFG0_HALF_BUS;
		अवरोध;
	हाल PHY_INTERFACE_MODE_SGMII:
		val |= MVEBU_COMPHY_SERDES_CFG0_GEN_RX(0x6) |
		       MVEBU_COMPHY_SERDES_CFG0_GEN_TX(0x6) |
		       MVEBU_COMPHY_SERDES_CFG0_HALF_BUS;
		अवरोध;
	शेष:
		dev_err(priv->dev,
			"unsupported comphy submode (%d) on lane %d\n",
			lane->submode,
			lane->id);
		वापस -ENOTSUPP;
	पूर्ण

	ग_लिखोl(val, priv->base + MVEBU_COMPHY_SERDES_CFG0(lane->id));

	अगर (lane->submode == PHY_INTERFACE_MODE_RXAUI) अणु
		regmap_पढ़ो(priv->regmap, MVEBU_COMPHY_SD1_CTRL1, &val);

		चयन (lane->id) अणु
		हाल 2:
		हाल 3:
			val |= MVEBU_COMPHY_SD1_CTRL1_RXAUI0_EN;
			अवरोध;
		हाल 4:
		हाल 5:
			val |= MVEBU_COMPHY_SD1_CTRL1_RXAUI1_EN;
			अवरोध;
		शेष:
			dev_err(priv->dev,
				"RXAUI is not supported on comphy lane %d\n",
				lane->id);
			वापस -EINVAL;
		पूर्ण

		regmap_ग_लिखो(priv->regmap, MVEBU_COMPHY_SD1_CTRL1, val);
	पूर्ण

	/* reset */
	val = पढ़ोl(priv->base + MVEBU_COMPHY_SERDES_CFG1(lane->id));
	val &= ~(MVEBU_COMPHY_SERDES_CFG1_RESET |
		 MVEBU_COMPHY_SERDES_CFG1_CORE_RESET |
		 MVEBU_COMPHY_SERDES_CFG1_RF_RESET);
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_SERDES_CFG1(lane->id));

	/* de-निश्चित reset */
	val = पढ़ोl(priv->base + MVEBU_COMPHY_SERDES_CFG1(lane->id));
	val |= MVEBU_COMPHY_SERDES_CFG1_RESET |
	       MVEBU_COMPHY_SERDES_CFG1_CORE_RESET;
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_SERDES_CFG1(lane->id));

	/* रुको until घड़ीs are पढ़ोy */
	mdelay(1);

	/* exlicitly disable 40B, the bits isn't clear on reset */
	regmap_पढ़ो(priv->regmap, MVEBU_COMPHY_CONF6(lane->id), &val);
	val &= ~MVEBU_COMPHY_CONF6_40B;
	regmap_ग_लिखो(priv->regmap, MVEBU_COMPHY_CONF6(lane->id), val);

	/* refclk selection */
	val = पढ़ोl(priv->base + MVEBU_COMPHY_MISC_CTRL0(lane->id));
	val &= ~MVEBU_COMPHY_MISC_CTRL0_REFCLK_SEL;
	अगर (lane->submode == PHY_INTERFACE_MODE_10GBASER)
		val |= MVEBU_COMPHY_MISC_CTRL0_ICP_FORCE;
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_MISC_CTRL0(lane->id));

	/* घातer and pll selection */
	val = पढ़ोl(priv->base + MVEBU_COMPHY_PWRPLL_CTRL(lane->id));
	val &= ~(MVEBU_COMPHY_PWRPLL_CTRL_RFREQ(0x1f) |
		 MVEBU_COMPHY_PWRPLL_PHY_MODE(0x7));
	val |= MVEBU_COMPHY_PWRPLL_CTRL_RFREQ(0x1) |
	       MVEBU_COMPHY_PWRPLL_PHY_MODE(0x4);
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_PWRPLL_CTRL(lane->id));

	val = पढ़ोl(priv->base + MVEBU_COMPHY_LOOPBACK(lane->id));
	val &= ~MVEBU_COMPHY_LOOPBACK_DBUS_WIDTH(0x7);
	val |= MVEBU_COMPHY_LOOPBACK_DBUS_WIDTH(0x1);
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_LOOPBACK(lane->id));

	वापस 0;
पूर्ण

अटल पूर्णांक mvebu_comphy_init_plls(काष्ठा mvebu_comphy_lane *lane)
अणु
	काष्ठा mvebu_comphy_priv *priv = lane->priv;
	u32 val;

	/* SERDES बाह्यal config */
	val = पढ़ोl(priv->base + MVEBU_COMPHY_SERDES_CFG0(lane->id));
	val |= MVEBU_COMPHY_SERDES_CFG0_PU_PLL |
	       MVEBU_COMPHY_SERDES_CFG0_PU_RX |
	       MVEBU_COMPHY_SERDES_CFG0_PU_TX;
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_SERDES_CFG0(lane->id));

	/* check rx/tx pll */
	पढ़ोl_poll_समयout(priv->base + MVEBU_COMPHY_SERDES_STATUS0(lane->id),
			   val,
			   val & (MVEBU_COMPHY_SERDES_STATUS0_RX_PLL_RDY |
				  MVEBU_COMPHY_SERDES_STATUS0_TX_PLL_RDY),
			   1000, 150000);
	अगर (!(val & (MVEBU_COMPHY_SERDES_STATUS0_RX_PLL_RDY |
		     MVEBU_COMPHY_SERDES_STATUS0_TX_PLL_RDY)))
		वापस -ETIMEDOUT;

	/* rx init */
	val = पढ़ोl(priv->base + MVEBU_COMPHY_SERDES_CFG1(lane->id));
	val |= MVEBU_COMPHY_SERDES_CFG1_RX_INIT;
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_SERDES_CFG1(lane->id));

	/* check rx */
	पढ़ोl_poll_समयout(priv->base + MVEBU_COMPHY_SERDES_STATUS0(lane->id),
			   val, val & MVEBU_COMPHY_SERDES_STATUS0_RX_INIT,
			   1000, 10000);
	अगर (!(val & MVEBU_COMPHY_SERDES_STATUS0_RX_INIT))
		वापस -ETIMEDOUT;

	val = पढ़ोl(priv->base + MVEBU_COMPHY_SERDES_CFG1(lane->id));
	val &= ~MVEBU_COMPHY_SERDES_CFG1_RX_INIT;
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_SERDES_CFG1(lane->id));

	वापस 0;
पूर्ण

अटल पूर्णांक mvebu_comphy_set_mode_sgmii(काष्ठा phy *phy)
अणु
	काष्ठा mvebu_comphy_lane *lane = phy_get_drvdata(phy);
	काष्ठा mvebu_comphy_priv *priv = lane->priv;
	u32 val;
	पूर्णांक err;

	err = mvebu_comphy_ethernet_init_reset(lane);
	अगर (err)
		वापस err;

	val = पढ़ोl(priv->base + MVEBU_COMPHY_RX_CTRL1(lane->id));
	val &= ~MVEBU_COMPHY_RX_CTRL1_CLK8T_EN;
	val |= MVEBU_COMPHY_RX_CTRL1_RXCLK2X_SEL;
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_RX_CTRL1(lane->id));

	val = पढ़ोl(priv->base + MVEBU_COMPHY_DTL_CTRL(lane->id));
	val &= ~MVEBU_COMPHY_DTL_CTRL_DTL_FLOOP_EN;
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_DTL_CTRL(lane->id));

	regmap_पढ़ो(priv->regmap, MVEBU_COMPHY_CONF1(lane->id), &val);
	val &= ~MVEBU_COMPHY_CONF1_USB_PCIE;
	val |= MVEBU_COMPHY_CONF1_PWRUP;
	regmap_ग_लिखो(priv->regmap, MVEBU_COMPHY_CONF1(lane->id), val);

	val = पढ़ोl(priv->base + MVEBU_COMPHY_GEN1_S0(lane->id));
	val &= ~MVEBU_COMPHY_GEN1_S0_TX_EMPH(0xf);
	val |= MVEBU_COMPHY_GEN1_S0_TX_EMPH(0x1);
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_GEN1_S0(lane->id));

	वापस mvebu_comphy_init_plls(lane);
पूर्ण

अटल पूर्णांक mvebu_comphy_set_mode_rxaui(काष्ठा phy *phy)
अणु
	काष्ठा mvebu_comphy_lane *lane = phy_get_drvdata(phy);
	काष्ठा mvebu_comphy_priv *priv = lane->priv;
	u32 val;
	पूर्णांक err;

	err = mvebu_comphy_ethernet_init_reset(lane);
	अगर (err)
		वापस err;

	val = पढ़ोl(priv->base + MVEBU_COMPHY_RX_CTRL1(lane->id));
	val |= MVEBU_COMPHY_RX_CTRL1_RXCLK2X_SEL |
	       MVEBU_COMPHY_RX_CTRL1_CLK8T_EN;
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_RX_CTRL1(lane->id));

	val = पढ़ोl(priv->base + MVEBU_COMPHY_DTL_CTRL(lane->id));
	val |= MVEBU_COMPHY_DTL_CTRL_DTL_FLOOP_EN;
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_DTL_CTRL(lane->id));

	val = पढ़ोl(priv->base + MVEBU_COMPHY_SERDES_CFG2(lane->id));
	val |= MVEBU_COMPHY_SERDES_CFG2_DFE_EN;
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_SERDES_CFG2(lane->id));

	val = पढ़ोl(priv->base + MVEBU_COMPHY_DFE_RES(lane->id));
	val |= MVEBU_COMPHY_DFE_RES_FORCE_GEN_TBL;
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_DFE_RES(lane->id));

	val = पढ़ोl(priv->base + MVEBU_COMPHY_GEN1_S0(lane->id));
	val &= ~MVEBU_COMPHY_GEN1_S0_TX_EMPH(0xf);
	val |= MVEBU_COMPHY_GEN1_S0_TX_EMPH(0xd);
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_GEN1_S0(lane->id));

	val = पढ़ोl(priv->base + MVEBU_COMPHY_GEN1_S1(lane->id));
	val &= ~(MVEBU_COMPHY_GEN1_S1_RX_MUL_PI(0x7) |
		 MVEBU_COMPHY_GEN1_S1_RX_MUL_PF(0x7));
	val |= MVEBU_COMPHY_GEN1_S1_RX_MUL_PI(0x1) |
	       MVEBU_COMPHY_GEN1_S1_RX_MUL_PF(0x1) |
	       MVEBU_COMPHY_GEN1_S1_RX_DFE_EN;
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_GEN1_S1(lane->id));

	val = पढ़ोl(priv->base + MVEBU_COMPHY_COEF(lane->id));
	val &= ~(MVEBU_COMPHY_COEF_DFE_EN | MVEBU_COMPHY_COEF_DFE_CTRL);
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_COEF(lane->id));

	val = पढ़ोl(priv->base + MVEBU_COMPHY_GEN1_S4(lane->id));
	val &= ~MVEBU_COMPHY_GEN1_S4_DFE_RES(0x3);
	val |= MVEBU_COMPHY_GEN1_S4_DFE_RES(0x1);
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_GEN1_S4(lane->id));

	वापस mvebu_comphy_init_plls(lane);
पूर्ण

अटल पूर्णांक mvebu_comphy_set_mode_10gbaser(काष्ठा phy *phy)
अणु
	काष्ठा mvebu_comphy_lane *lane = phy_get_drvdata(phy);
	काष्ठा mvebu_comphy_priv *priv = lane->priv;
	u32 val;
	पूर्णांक err;

	err = mvebu_comphy_ethernet_init_reset(lane);
	अगर (err)
		वापस err;

	val = पढ़ोl(priv->base + MVEBU_COMPHY_RX_CTRL1(lane->id));
	val |= MVEBU_COMPHY_RX_CTRL1_RXCLK2X_SEL |
	       MVEBU_COMPHY_RX_CTRL1_CLK8T_EN;
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_RX_CTRL1(lane->id));

	val = पढ़ोl(priv->base + MVEBU_COMPHY_DTL_CTRL(lane->id));
	val |= MVEBU_COMPHY_DTL_CTRL_DTL_FLOOP_EN;
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_DTL_CTRL(lane->id));

	/* Speed भागider */
	val = पढ़ोl(priv->base + MVEBU_COMPHY_SPEED_DIV(lane->id));
	val |= MVEBU_COMPHY_SPEED_DIV_TX_FORCE;
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_SPEED_DIV(lane->id));

	val = पढ़ोl(priv->base + MVEBU_COMPHY_SERDES_CFG2(lane->id));
	val |= MVEBU_COMPHY_SERDES_CFG2_DFE_EN;
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_SERDES_CFG2(lane->id));

	/* DFE resolution */
	val = पढ़ोl(priv->base + MVEBU_COMPHY_DFE_RES(lane->id));
	val |= MVEBU_COMPHY_DFE_RES_FORCE_GEN_TBL;
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_DFE_RES(lane->id));

	val = पढ़ोl(priv->base + MVEBU_COMPHY_GEN1_S0(lane->id));
	val &= ~(MVEBU_COMPHY_GEN1_S0_TX_AMP(0x1f) |
		 MVEBU_COMPHY_GEN1_S0_TX_EMPH(0xf));
	val |= MVEBU_COMPHY_GEN1_S0_TX_AMP(0x1c) |
	       MVEBU_COMPHY_GEN1_S0_TX_EMPH(0xe);
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_GEN1_S0(lane->id));

	val = पढ़ोl(priv->base + MVEBU_COMPHY_GEN1_S2(lane->id));
	val &= ~MVEBU_COMPHY_GEN1_S2_TX_EMPH(0xf);
	val |= MVEBU_COMPHY_GEN1_S2_TX_EMPH_EN;
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_GEN1_S2(lane->id));

	val = पढ़ोl(priv->base + MVEBU_COMPHY_TX_SLEW_RATE(lane->id));
	val |= MVEBU_COMPHY_TX_SLEW_RATE_EMPH(0x3) |
	       MVEBU_COMPHY_TX_SLEW_RATE_SLC(0x3f);
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_TX_SLEW_RATE(lane->id));

	/* Impedance calibration */
	val = पढ़ोl(priv->base + MVEBU_COMPHY_IMP_CAL(lane->id));
	val &= ~MVEBU_COMPHY_IMP_CAL_TX_EXT(0x1f);
	val |= MVEBU_COMPHY_IMP_CAL_TX_EXT(0xe) |
	       MVEBU_COMPHY_IMP_CAL_TX_EXT_EN;
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_IMP_CAL(lane->id));

	val = पढ़ोl(priv->base + MVEBU_COMPHY_GEN1_S5(lane->id));
	val &= ~MVEBU_COMPHY_GEN1_S5_ICP(0xf);
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_GEN1_S5(lane->id));

	val = पढ़ोl(priv->base + MVEBU_COMPHY_GEN1_S1(lane->id));
	val &= ~(MVEBU_COMPHY_GEN1_S1_RX_MUL_PI(0x7) |
		 MVEBU_COMPHY_GEN1_S1_RX_MUL_PF(0x7) |
		 MVEBU_COMPHY_GEN1_S1_RX_MUL_FI(0x3) |
		 MVEBU_COMPHY_GEN1_S1_RX_MUL_FF(0x3));
	val |= MVEBU_COMPHY_GEN1_S1_RX_DFE_EN |
	       MVEBU_COMPHY_GEN1_S1_RX_MUL_PI(0x2) |
	       MVEBU_COMPHY_GEN1_S1_RX_MUL_PF(0x2) |
	       MVEBU_COMPHY_GEN1_S1_RX_MUL_FF(0x1) |
	       MVEBU_COMPHY_GEN1_S1_RX_DIV(0x3);
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_GEN1_S1(lane->id));

	val = पढ़ोl(priv->base + MVEBU_COMPHY_COEF(lane->id));
	val &= ~(MVEBU_COMPHY_COEF_DFE_EN | MVEBU_COMPHY_COEF_DFE_CTRL);
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_COEF(lane->id));

	val = पढ़ोl(priv->base + MVEBU_COMPHY_GEN1_S4(lane->id));
	val &= ~MVEBU_COMPHY_GEN1_S4_DFE_RES(0x3);
	val |= MVEBU_COMPHY_GEN1_S4_DFE_RES(0x1);
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_GEN1_S4(lane->id));

	val = पढ़ोl(priv->base + MVEBU_COMPHY_GEN1_S3(lane->id));
	val |= MVEBU_COMPHY_GEN1_S3_FBCK_SEL;
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_GEN1_S3(lane->id));

	/* rx training समयr */
	val = पढ़ोl(priv->base + MVEBU_COMPHY_TRAINING5(lane->id));
	val &= ~MVEBU_COMPHY_TRAINING5_RX_TIMER(0x3ff);
	val |= MVEBU_COMPHY_TRAINING5_RX_TIMER(0x13);
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_TRAINING5(lane->id));

	/* tx train peak to peak hold */
	val = पढ़ोl(priv->base + MVEBU_COMPHY_TRAINING0(lane->id));
	val |= MVEBU_COMPHY_TRAINING0_P2P_HOLD;
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_TRAINING0(lane->id));

	val = पढ़ोl(priv->base + MVEBU_COMPHY_TX_PRESET(lane->id));
	val &= ~MVEBU_COMPHY_TX_PRESET_INDEX(0xf);
	val |= MVEBU_COMPHY_TX_PRESET_INDEX(0x2);	/* preset coeff */
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_TX_PRESET(lane->id));

	val = पढ़ोl(priv->base + MVEBU_COMPHY_FRAME_DETECT3(lane->id));
	val &= ~MVEBU_COMPHY_FRAME_DETECT3_LOST_TIMEOUT_EN;
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_FRAME_DETECT3(lane->id));

	val = पढ़ोl(priv->base + MVEBU_COMPHY_TX_TRAIN_PRESET(lane->id));
	val |= MVEBU_COMPHY_TX_TRAIN_PRESET_16B_AUTO_EN |
	       MVEBU_COMPHY_TX_TRAIN_PRESET_PRBS11;
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_TX_TRAIN_PRESET(lane->id));

	val = पढ़ोl(priv->base + MVEBU_COMPHY_FRAME_DETECT0(lane->id));
	val &= ~MVEBU_COMPHY_FRAME_DETECT0_PATN(0x1ff);
	val |= MVEBU_COMPHY_FRAME_DETECT0_PATN(0x88);
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_FRAME_DETECT0(lane->id));

	val = पढ़ोl(priv->base + MVEBU_COMPHY_DME(lane->id));
	val |= MVEBU_COMPHY_DME_ETH_MODE;
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_DME(lane->id));

	val = पढ़ोl(priv->base + MVEBU_COMPHY_VDD_CAL0(lane->id));
	val |= MVEBU_COMPHY_VDD_CAL0_CONT_MODE;
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_VDD_CAL0(lane->id));

	val = पढ़ोl(priv->base + MVEBU_SP_CALIB(lane->id));
	val &= ~MVEBU_SP_CALIB_SAMPLER(0x3);
	val |= MVEBU_SP_CALIB_SAMPLER(0x3) |
	       MVEBU_SP_CALIB_SAMPLER_EN;
	ग_लिखोl(val, priv->base + MVEBU_SP_CALIB(lane->id));
	val &= ~MVEBU_SP_CALIB_SAMPLER_EN;
	ग_लिखोl(val, priv->base + MVEBU_SP_CALIB(lane->id));

	/* External rx regulator */
	val = पढ़ोl(priv->base + MVEBU_COMPHY_EXT_SELV(lane->id));
	val &= ~MVEBU_COMPHY_EXT_SELV_RX_SAMPL(0x1f);
	val |= MVEBU_COMPHY_EXT_SELV_RX_SAMPL(0x1a);
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_EXT_SELV(lane->id));

	वापस mvebu_comphy_init_plls(lane);
पूर्ण

अटल पूर्णांक mvebu_comphy_घातer_on_legacy(काष्ठा phy *phy)
अणु
	काष्ठा mvebu_comphy_lane *lane = phy_get_drvdata(phy);
	काष्ठा mvebu_comphy_priv *priv = lane->priv;
	पूर्णांक ret, mux;
	u32 val;

	mux = mvebu_comphy_get_mux(lane->id, lane->port,
				   lane->mode, lane->submode);
	अगर (mux < 0)
		वापस -ENOTSUPP;

	regmap_पढ़ो(priv->regmap, MVEBU_COMPHY_PIPE_SELECTOR, &val);
	val &= ~(0xf << MVEBU_COMPHY_PIPE_SELECTOR_PIPE(lane->id));
	regmap_ग_लिखो(priv->regmap, MVEBU_COMPHY_PIPE_SELECTOR, val);

	regmap_पढ़ो(priv->regmap, MVEBU_COMPHY_SELECTOR, &val);
	val &= ~(0xf << MVEBU_COMPHY_SELECTOR_PHY(lane->id));
	val |= mux << MVEBU_COMPHY_SELECTOR_PHY(lane->id);
	regmap_ग_लिखो(priv->regmap, MVEBU_COMPHY_SELECTOR, val);

	चयन (lane->submode) अणु
	हाल PHY_INTERFACE_MODE_SGMII:
	हाल PHY_INTERFACE_MODE_2500BASEX:
		ret = mvebu_comphy_set_mode_sgmii(phy);
		अवरोध;
	हाल PHY_INTERFACE_MODE_RXAUI:
		ret = mvebu_comphy_set_mode_rxaui(phy);
		अवरोध;
	हाल PHY_INTERFACE_MODE_10GBASER:
		ret = mvebu_comphy_set_mode_10gbaser(phy);
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	/* digital reset */
	val = पढ़ोl(priv->base + MVEBU_COMPHY_SERDES_CFG1(lane->id));
	val |= MVEBU_COMPHY_SERDES_CFG1_RF_RESET;
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_SERDES_CFG1(lane->id));

	वापस ret;
पूर्ण

अटल पूर्णांक mvebu_comphy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा mvebu_comphy_lane *lane = phy_get_drvdata(phy);
	काष्ठा mvebu_comphy_priv *priv = lane->priv;
	पूर्णांक fw_mode, fw_speed;
	u32 fw_param = 0;
	पूर्णांक ret;

	fw_mode = mvebu_comphy_get_fw_mode(lane->id, lane->port,
					   lane->mode, lane->submode);
	अगर (fw_mode < 0)
		जाओ try_legacy;

	/* Try SMC flow first */
	चयन (lane->mode) अणु
	हाल PHY_MODE_ETHERNET:
		चयन (lane->submode) अणु
		हाल PHY_INTERFACE_MODE_RXAUI:
			dev_dbg(priv->dev, "set lane %d to RXAUI mode\n",
				lane->id);
			fw_speed = 0;
			अवरोध;
		हाल PHY_INTERFACE_MODE_SGMII:
			dev_dbg(priv->dev, "set lane %d to 1000BASE-X mode\n",
				lane->id);
			fw_speed = COMPHY_FW_SPEED_1250;
			अवरोध;
		हाल PHY_INTERFACE_MODE_2500BASEX:
			dev_dbg(priv->dev, "set lane %d to 2500BASE-X mode\n",
				lane->id);
			fw_speed = COMPHY_FW_SPEED_3125;
			अवरोध;
		हाल PHY_INTERFACE_MODE_10GBASER:
			dev_dbg(priv->dev, "set lane %d to 10GBASE-R mode\n",
				lane->id);
			fw_speed = COMPHY_FW_SPEED_103125;
			अवरोध;
		शेष:
			dev_err(priv->dev, "unsupported Ethernet mode (%d)\n",
				lane->submode);
			वापस -ENOTSUPP;
		पूर्ण
		fw_param = COMPHY_FW_PARAM_ETH(fw_mode, lane->port, fw_speed);
		अवरोध;
	हाल PHY_MODE_USB_HOST_SS:
	हाल PHY_MODE_USB_DEVICE_SS:
		dev_dbg(priv->dev, "set lane %d to USB3 mode\n", lane->id);
		fw_param = COMPHY_FW_PARAM(fw_mode, lane->port);
		अवरोध;
	हाल PHY_MODE_SATA:
		dev_dbg(priv->dev, "set lane %d to SATA mode\n", lane->id);
		fw_param = COMPHY_FW_PARAM(fw_mode, lane->port);
		अवरोध;
	हाल PHY_MODE_PCIE:
		dev_dbg(priv->dev, "set lane %d to PCIe mode (x%d)\n", lane->id,
			lane->submode);
		fw_param = COMPHY_FW_PARAM_PCIE(fw_mode, lane->port,
						lane->submode);
		अवरोध;
	शेष:
		dev_err(priv->dev, "unsupported PHY mode (%d)\n", lane->mode);
		वापस -ENOTSUPP;
	पूर्ण

	ret = mvebu_comphy_smc(COMPHY_SIP_POWER_ON, priv->cp_phys, lane->id,
			       fw_param);
	अगर (!ret)
		वापस ret;

	अगर (ret == -EOPNOTSUPP)
		dev_err(priv->dev,
			"unsupported SMC call, try updating your firmware\n");

	dev_warn(priv->dev,
		 "Firmware could not configure PHY %d with mode %d (ret: %d), trying legacy method\n",
		 lane->id, lane->mode, ret);

try_legacy:
	/* Fallback to Linux's implementation */
	वापस mvebu_comphy_घातer_on_legacy(phy);
पूर्ण

अटल पूर्णांक mvebu_comphy_set_mode(काष्ठा phy *phy,
				 क्रमागत phy_mode mode, पूर्णांक submode)
अणु
	काष्ठा mvebu_comphy_lane *lane = phy_get_drvdata(phy);

	अगर (submode == PHY_INTERFACE_MODE_1000BASEX)
		submode = PHY_INTERFACE_MODE_SGMII;

	अगर (mvebu_comphy_get_fw_mode(lane->id, lane->port, mode, submode) < 0)
		वापस -EINVAL;

	lane->mode = mode;
	lane->submode = submode;

	/* PCIe submode represents the width */
	अगर (mode == PHY_MODE_PCIE && !lane->submode)
		lane->submode = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक mvebu_comphy_घातer_off_legacy(काष्ठा phy *phy)
अणु
	काष्ठा mvebu_comphy_lane *lane = phy_get_drvdata(phy);
	काष्ठा mvebu_comphy_priv *priv = lane->priv;
	u32 val;

	val = पढ़ोl(priv->base + MVEBU_COMPHY_SERDES_CFG1(lane->id));
	val &= ~(MVEBU_COMPHY_SERDES_CFG1_RESET |
		 MVEBU_COMPHY_SERDES_CFG1_CORE_RESET |
		 MVEBU_COMPHY_SERDES_CFG1_RF_RESET);
	ग_लिखोl(val, priv->base + MVEBU_COMPHY_SERDES_CFG1(lane->id));

	regmap_पढ़ो(priv->regmap, MVEBU_COMPHY_SELECTOR, &val);
	val &= ~(0xf << MVEBU_COMPHY_SELECTOR_PHY(lane->id));
	regmap_ग_लिखो(priv->regmap, MVEBU_COMPHY_SELECTOR, val);

	regmap_पढ़ो(priv->regmap, MVEBU_COMPHY_PIPE_SELECTOR, &val);
	val &= ~(0xf << MVEBU_COMPHY_PIPE_SELECTOR_PIPE(lane->id));
	regmap_ग_लिखो(priv->regmap, MVEBU_COMPHY_PIPE_SELECTOR, val);

	वापस 0;
पूर्ण

अटल पूर्णांक mvebu_comphy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा mvebu_comphy_lane *lane = phy_get_drvdata(phy);
	काष्ठा mvebu_comphy_priv *priv = lane->priv;
	पूर्णांक ret;

	ret = mvebu_comphy_smc(COMPHY_SIP_POWER_OFF, priv->cp_phys,
			       lane->id, 0);
	अगर (!ret)
		वापस ret;

	/* Fallback to Linux's implementation */
	वापस mvebu_comphy_घातer_off_legacy(phy);
पूर्ण

अटल स्थिर काष्ठा phy_ops mvebu_comphy_ops = अणु
	.घातer_on	= mvebu_comphy_घातer_on,
	.घातer_off	= mvebu_comphy_घातer_off,
	.set_mode	= mvebu_comphy_set_mode,
	.owner		= THIS_MODULE,
पूर्ण;

अटल काष्ठा phy *mvebu_comphy_xlate(काष्ठा device *dev,
				      काष्ठा of_phandle_args *args)
अणु
	काष्ठा mvebu_comphy_lane *lane;
	काष्ठा phy *phy;

	अगर (WARN_ON(args->args[0] >= MVEBU_COMPHY_PORTS))
		वापस ERR_PTR(-EINVAL);

	phy = of_phy_simple_xlate(dev, args);
	अगर (IS_ERR(phy))
		वापस phy;

	lane = phy_get_drvdata(phy);
	lane->port = args->args[0];

	वापस phy;
पूर्ण

अटल पूर्णांक mvebu_comphy_init_clks(काष्ठा mvebu_comphy_priv *priv)
अणु
	पूर्णांक ret;

	priv->mg_करोमुख्य_clk = devm_clk_get(priv->dev, "mg_clk");
	अगर (IS_ERR(priv->mg_करोमुख्य_clk))
		वापस PTR_ERR(priv->mg_करोमुख्य_clk);

	ret = clk_prepare_enable(priv->mg_करोमुख्य_clk);
	अगर (ret < 0)
		वापस ret;

	priv->mg_core_clk = devm_clk_get(priv->dev, "mg_core_clk");
	अगर (IS_ERR(priv->mg_core_clk)) अणु
		ret = PTR_ERR(priv->mg_core_clk);
		जाओ dis_mg_करोमुख्य_clk;
	पूर्ण

	ret = clk_prepare_enable(priv->mg_core_clk);
	अगर (ret < 0)
		जाओ dis_mg_करोमुख्य_clk;

	priv->axi_clk = devm_clk_get(priv->dev, "axi_clk");
	अगर (IS_ERR(priv->axi_clk)) अणु
		ret = PTR_ERR(priv->axi_clk);
		जाओ dis_mg_core_clk;
	पूर्ण

	ret = clk_prepare_enable(priv->axi_clk);
	अगर (ret < 0)
		जाओ dis_mg_core_clk;

	वापस 0;

dis_mg_core_clk:
	clk_disable_unprepare(priv->mg_core_clk);

dis_mg_करोमुख्य_clk:
	clk_disable_unprepare(priv->mg_करोमुख्य_clk);

	priv->mg_करोमुख्य_clk = शून्य;
	priv->mg_core_clk = शून्य;
	priv->axi_clk = शून्य;

	वापस ret;
पूर्ण;

अटल व्योम mvebu_comphy_disable_unprepare_clks(काष्ठा mvebu_comphy_priv *priv)
अणु
	अगर (priv->axi_clk)
		clk_disable_unprepare(priv->axi_clk);

	अगर (priv->mg_core_clk)
		clk_disable_unprepare(priv->mg_core_clk);

	अगर (priv->mg_करोमुख्य_clk)
		clk_disable_unprepare(priv->mg_करोमुख्य_clk);
पूर्ण

अटल पूर्णांक mvebu_comphy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mvebu_comphy_priv *priv;
	काष्ठा phy_provider *provider;
	काष्ठा device_node *child;
	काष्ठा resource *res;
	पूर्णांक ret;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = &pdev->dev;
	priv->regmap =
		syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
						"marvell,system-controller");
	अगर (IS_ERR(priv->regmap))
		वापस PTR_ERR(priv->regmap);
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	/*
	 * Ignore error अगर घड़ीs have not been initialized properly क्रम DT
	 * compatibility reasons.
	 */
	ret = mvebu_comphy_init_clks(priv);
	अगर (ret) अणु
		अगर (ret == -EPROBE_DEFER)
			वापस ret;
		dev_warn(&pdev->dev, "cannot initialize clocks\n");
	पूर्ण

	/*
	 * Hack to retrieve a physical offset relative to this CP that will be
	 * given to the firmware
	 */
	priv->cp_phys = res->start;

	क्रम_each_available_child_of_node(pdev->dev.of_node, child) अणु
		काष्ठा mvebu_comphy_lane *lane;
		काष्ठा phy *phy;
		u32 val;

		ret = of_property_पढ़ो_u32(child, "reg", &val);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "missing 'reg' property (%d)\n",
				ret);
			जारी;
		पूर्ण

		अगर (val >= MVEBU_COMPHY_LANES) अणु
			dev_err(&pdev->dev, "invalid 'reg' property\n");
			जारी;
		पूर्ण

		lane = devm_kzalloc(&pdev->dev, माप(*lane), GFP_KERNEL);
		अगर (!lane) अणु
			of_node_put(child);
			ret = -ENOMEM;
			जाओ disable_clks;
		पूर्ण

		phy = devm_phy_create(&pdev->dev, child, &mvebu_comphy_ops);
		अगर (IS_ERR(phy)) अणु
			of_node_put(child);
			ret = PTR_ERR(phy);
			जाओ disable_clks;
		पूर्ण

		lane->priv = priv;
		lane->mode = PHY_MODE_INVALID;
		lane->submode = PHY_INTERFACE_MODE_NA;
		lane->id = val;
		lane->port = -1;
		phy_set_drvdata(phy, lane);

		/*
		 * All modes are supported in this driver so we could call
		 * mvebu_comphy_घातer_off(phy) here to aव्योम relying on the
		 * bootloader/firmware configuration, but क्रम compatibility
		 * reasons we cannot de-configure the COMPHY without being sure
		 * that the firmware is up-to-date and fully-featured.
		 */
	पूर्ण

	dev_set_drvdata(&pdev->dev, priv);
	provider = devm_of_phy_provider_रेजिस्टर(&pdev->dev,
						 mvebu_comphy_xlate);

	वापस PTR_ERR_OR_ZERO(provider);

disable_clks:
	mvebu_comphy_disable_unprepare_clks(priv);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id mvebu_comphy_of_match_table[] = अणु
	अणु .compatible = "marvell,comphy-cp110" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mvebu_comphy_of_match_table);

अटल काष्ठा platक्रमm_driver mvebu_comphy_driver = अणु
	.probe	= mvebu_comphy_probe,
	.driver	= अणु
		.name = "mvebu-comphy",
		.of_match_table = mvebu_comphy_of_match_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(mvebu_comphy_driver);

MODULE_AUTHOR("Antoine Tenart <antoine.tenart@free-electrons.com>");
MODULE_DESCRIPTION("Common PHY driver for mvebu SoCs");
MODULE_LICENSE("GPL v2");
