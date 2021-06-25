<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/*
 * SerDes PHY driver क्रम Microsemi Ocelot
 *
 * Copyright (c) 2018 Microsemi
 *
 */

#समावेश <linux/err.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <soc/mscc/ocelot_hsपन.स>
#समावेश <dt-bindings/phy/phy-ocelot-serdes.h>

काष्ठा serdes_ctrl अणु
	काष्ठा regmap		*regs;
	काष्ठा device		*dev;
	काष्ठा phy		*phys[SERDES_MAX];
पूर्ण;

काष्ठा serdes_macro अणु
	u8			idx;
	/* Not used when in QSGMII or PCIe mode */
	पूर्णांक			port;
	काष्ठा serdes_ctrl	*ctrl;
पूर्ण;

#घोषणा MCB_S6G_CFG_TIMEOUT     50

अटल पूर्णांक __serdes_ग_लिखो_mcb_s6g(काष्ठा regmap *regmap, u8 macro, u32 op)
अणु
	अचिन्हित पूर्णांक regval = 0;

	regmap_ग_लिखो(regmap, HSIO_MCB_S6G_ADDR_CFG, op |
		     HSIO_MCB_S6G_ADDR_CFG_SERDES6G_ADDR(BIT(macro)));

	वापस regmap_पढ़ो_poll_समयout(regmap, HSIO_MCB_S6G_ADDR_CFG, regval,
					(regval & op) != op, 100,
					MCB_S6G_CFG_TIMEOUT * 1000);
पूर्ण

अटल पूर्णांक serdes_commit_mcb_s6g(काष्ठा regmap *regmap, u8 macro)
अणु
	वापस __serdes_ग_लिखो_mcb_s6g(regmap, macro,
		HSIO_MCB_S6G_ADDR_CFG_SERDES6G_WR_ONE_SHOT);
पूर्ण

अटल पूर्णांक serdes_update_mcb_s6g(काष्ठा regmap *regmap, u8 macro)
अणु
	वापस __serdes_ग_लिखो_mcb_s6g(regmap, macro,
		HSIO_MCB_S6G_ADDR_CFG_SERDES6G_RD_ONE_SHOT);
पूर्ण

अटल पूर्णांक serdes_init_s6g(काष्ठा regmap *regmap, u8 serdes, पूर्णांक mode)
अणु
	u32 pll_fsm_ctrl_data;
	u32 ob_ena1v_mode;
	u32 des_bw_ana;
	u32 ob_ena_cas;
	u32 अगर_mode;
	u32 ob_lev;
	u32 qrate;
	पूर्णांक ret;

	अगर (mode == PHY_INTERFACE_MODE_QSGMII) अणु
		pll_fsm_ctrl_data = 120;
		ob_ena1v_mode = 0;
		ob_ena_cas = 0;
		des_bw_ana = 5;
		ob_lev = 24;
		अगर_mode = 3;
		qrate = 0;
	पूर्ण अन्यथा अणु
		pll_fsm_ctrl_data = 60;
		ob_ena1v_mode = 1;
		ob_ena_cas = 2;
		des_bw_ana = 3;
		ob_lev = 48;
		अगर_mode = 1;
		qrate = 1;
	पूर्ण

	ret = serdes_update_mcb_s6g(regmap, serdes);
	अगर (ret)
		वापस ret;

	/* Test pattern */

	regmap_update_bits(regmap, HSIO_S6G_COMMON_CFG,
			   HSIO_S6G_COMMON_CFG_SYS_RST, 0);

	regmap_update_bits(regmap, HSIO_S6G_PLL_CFG,
			   HSIO_S6G_PLL_CFG_PLL_FSM_ENA, 0);

	regmap_update_bits(regmap, HSIO_S6G_IB_CFG,
			   HSIO_S6G_IB_CFG_IB_SIG_DET_ENA |
			   HSIO_S6G_IB_CFG_IB_REG_ENA |
			   HSIO_S6G_IB_CFG_IB_SAM_ENA |
			   HSIO_S6G_IB_CFG_IB_EQZ_ENA |
			   HSIO_S6G_IB_CFG_IB_CONCUR |
			   HSIO_S6G_IB_CFG_IB_CAL_ENA,
			   HSIO_S6G_IB_CFG_IB_SIG_DET_ENA |
			   HSIO_S6G_IB_CFG_IB_REG_ENA |
			   HSIO_S6G_IB_CFG_IB_SAM_ENA |
			   HSIO_S6G_IB_CFG_IB_EQZ_ENA |
			   HSIO_S6G_IB_CFG_IB_CONCUR);

	regmap_update_bits(regmap, HSIO_S6G_IB_CFG1,
			   HSIO_S6G_IB_CFG1_IB_FRC_OFFSET |
			   HSIO_S6G_IB_CFG1_IB_FRC_LP |
			   HSIO_S6G_IB_CFG1_IB_FRC_MID |
			   HSIO_S6G_IB_CFG1_IB_FRC_HP |
			   HSIO_S6G_IB_CFG1_IB_FILT_OFFSET |
			   HSIO_S6G_IB_CFG1_IB_FILT_LP |
			   HSIO_S6G_IB_CFG1_IB_FILT_MID |
			   HSIO_S6G_IB_CFG1_IB_FILT_HP,
			   HSIO_S6G_IB_CFG1_IB_FILT_OFFSET |
			   HSIO_S6G_IB_CFG1_IB_FILT_HP |
			   HSIO_S6G_IB_CFG1_IB_FILT_LP |
			   HSIO_S6G_IB_CFG1_IB_FILT_MID);

	regmap_update_bits(regmap, HSIO_S6G_IB_CFG2,
			   HSIO_S6G_IB_CFG2_IB_UREG_M,
			   HSIO_S6G_IB_CFG2_IB_UREG(4));

	regmap_update_bits(regmap, HSIO_S6G_IB_CFG3,
			   HSIO_S6G_IB_CFG3_IB_INI_OFFSET_M |
			   HSIO_S6G_IB_CFG3_IB_INI_LP_M |
			   HSIO_S6G_IB_CFG3_IB_INI_MID_M |
			   HSIO_S6G_IB_CFG3_IB_INI_HP_M,
			   HSIO_S6G_IB_CFG3_IB_INI_OFFSET(31) |
			   HSIO_S6G_IB_CFG3_IB_INI_LP(1) |
			   HSIO_S6G_IB_CFG3_IB_INI_MID(31) |
			   HSIO_S6G_IB_CFG3_IB_INI_HP(0));

	regmap_update_bits(regmap, HSIO_S6G_MISC_CFG,
			   HSIO_S6G_MISC_CFG_LANE_RST,
			   HSIO_S6G_MISC_CFG_LANE_RST);

	ret = serdes_commit_mcb_s6g(regmap, serdes);
	अगर (ret)
		वापस ret;

	/* OB + DES + IB + SER CFG */
	regmap_update_bits(regmap, HSIO_S6G_OB_CFG,
			   HSIO_S6G_OB_CFG_OB_IDLE |
			   HSIO_S6G_OB_CFG_OB_ENA1V_MODE |
			   HSIO_S6G_OB_CFG_OB_POST0_M |
			   HSIO_S6G_OB_CFG_OB_PREC_M,
			   (ob_ena1v_mode ? HSIO_S6G_OB_CFG_OB_ENA1V_MODE : 0) |
			   HSIO_S6G_OB_CFG_OB_POST0(0) |
			   HSIO_S6G_OB_CFG_OB_PREC(0));

	regmap_update_bits(regmap, HSIO_S6G_OB_CFG1,
			   HSIO_S6G_OB_CFG1_OB_ENA_CAS_M |
			   HSIO_S6G_OB_CFG1_OB_LEV_M,
			   HSIO_S6G_OB_CFG1_OB_LEV(ob_lev) |
			   HSIO_S6G_OB_CFG1_OB_ENA_CAS(ob_ena_cas));

	regmap_update_bits(regmap, HSIO_S6G_DES_CFG,
			   HSIO_S6G_DES_CFG_DES_PHS_CTRL_M |
			   HSIO_S6G_DES_CFG_DES_CPMD_SEL_M |
			   HSIO_S6G_DES_CFG_DES_BW_ANA_M,
			   HSIO_S6G_DES_CFG_DES_PHS_CTRL(2) |
			   HSIO_S6G_DES_CFG_DES_CPMD_SEL(0) |
			   HSIO_S6G_DES_CFG_DES_BW_ANA(des_bw_ana));

	regmap_update_bits(regmap, HSIO_S6G_IB_CFG,
			   HSIO_S6G_IB_CFG_IB_SIG_DET_CLK_SEL_M |
			   HSIO_S6G_IB_CFG_IB_REG_PAT_SEL_OFFSET_M,
			   HSIO_S6G_IB_CFG_IB_REG_PAT_SEL_OFFSET(0) |
			   HSIO_S6G_IB_CFG_IB_SIG_DET_CLK_SEL(0));

	regmap_update_bits(regmap, HSIO_S6G_IB_CFG1,
			   HSIO_S6G_IB_CFG1_IB_TSDET_M,
			   HSIO_S6G_IB_CFG1_IB_TSDET(16));

	regmap_update_bits(regmap, HSIO_S6G_SER_CFG,
			   HSIO_S6G_SER_CFG_SER_ALISEL_M |
			   HSIO_S6G_SER_CFG_SER_ENALI,
			   HSIO_S6G_SER_CFG_SER_ALISEL(0));

	regmap_update_bits(regmap, HSIO_S6G_PLL_CFG,
			   HSIO_S6G_PLL_CFG_PLL_DIV4 |
			   HSIO_S6G_PLL_CFG_PLL_ENA_ROT |
			   HSIO_S6G_PLL_CFG_PLL_FSM_CTRL_DATA_M |
			   HSIO_S6G_PLL_CFG_PLL_ROT_सूची |
			   HSIO_S6G_PLL_CFG_PLL_ROT_FRQ,
			   HSIO_S6G_PLL_CFG_PLL_FSM_CTRL_DATA
			   (pll_fsm_ctrl_data));

	regmap_update_bits(regmap, HSIO_S6G_COMMON_CFG,
			   HSIO_S6G_COMMON_CFG_SYS_RST |
			   HSIO_S6G_COMMON_CFG_ENA_LANE |
			   HSIO_S6G_COMMON_CFG_PWD_RX |
			   HSIO_S6G_COMMON_CFG_PWD_TX |
			   HSIO_S6G_COMMON_CFG_HRATE |
			   HSIO_S6G_COMMON_CFG_QRATE |
			   HSIO_S6G_COMMON_CFG_ENA_ELOOP |
			   HSIO_S6G_COMMON_CFG_ENA_FLOOP |
			   HSIO_S6G_COMMON_CFG_IF_MODE_M,
			   HSIO_S6G_COMMON_CFG_SYS_RST |
			   HSIO_S6G_COMMON_CFG_ENA_LANE |
			   (qrate ? HSIO_S6G_COMMON_CFG_QRATE : 0) |
			   HSIO_S6G_COMMON_CFG_IF_MODE(अगर_mode));

	regmap_update_bits(regmap, HSIO_S6G_MISC_CFG,
			   HSIO_S6G_MISC_CFG_LANE_RST |
			   HSIO_S6G_MISC_CFG_DES_100FX_CPMD_ENA |
			   HSIO_S6G_MISC_CFG_RX_LPI_MODE_ENA |
			   HSIO_S6G_MISC_CFG_TX_LPI_MODE_ENA,
			   HSIO_S6G_MISC_CFG_LANE_RST |
			   HSIO_S6G_MISC_CFG_RX_LPI_MODE_ENA);


	ret = serdes_commit_mcb_s6g(regmap, serdes);
	अगर (ret)
		वापस ret;

	regmap_update_bits(regmap, HSIO_S6G_PLL_CFG,
			   HSIO_S6G_PLL_CFG_PLL_FSM_ENA,
			   HSIO_S6G_PLL_CFG_PLL_FSM_ENA);

	ret = serdes_commit_mcb_s6g(regmap, serdes);
	अगर (ret)
		वापस ret;

	/* Wait क्रम PLL bringup */
	msleep(20);

	regmap_update_bits(regmap, HSIO_S6G_IB_CFG,
			   HSIO_S6G_IB_CFG_IB_CAL_ENA,
			   HSIO_S6G_IB_CFG_IB_CAL_ENA);

	regmap_update_bits(regmap, HSIO_S6G_MISC_CFG,
			   HSIO_S6G_MISC_CFG_LANE_RST, 0);

	ret = serdes_commit_mcb_s6g(regmap, serdes);
	अगर (ret)
		वापस ret;

	/* Wait क्रम calibration */
	msleep(60);

	regmap_update_bits(regmap, HSIO_S6G_IB_CFG,
			   HSIO_S6G_IB_CFG_IB_REG_PAT_SEL_OFFSET_M |
			   HSIO_S6G_IB_CFG_IB_SIG_DET_CLK_SEL_M,
			   HSIO_S6G_IB_CFG_IB_REG_PAT_SEL_OFFSET(0) |
			   HSIO_S6G_IB_CFG_IB_SIG_DET_CLK_SEL(7));

	regmap_update_bits(regmap, HSIO_S6G_IB_CFG1,
			   HSIO_S6G_IB_CFG1_IB_TSDET_M,
			   HSIO_S6G_IB_CFG1_IB_TSDET(3));

	/* IB CFG */

	वापस 0;
पूर्ण

#घोषणा MCB_S1G_CFG_TIMEOUT     50

अटल पूर्णांक __serdes_ग_लिखो_mcb_s1g(काष्ठा regmap *regmap, u8 macro, u32 op)
अणु
	अचिन्हित पूर्णांक regval;

	regmap_ग_लिखो(regmap, HSIO_MCB_S1G_ADDR_CFG, op |
		     HSIO_MCB_S1G_ADDR_CFG_SERDES1G_ADDR(BIT(macro)));

	वापस regmap_पढ़ो_poll_समयout(regmap, HSIO_MCB_S1G_ADDR_CFG, regval,
					(regval & op) != op, 100,
					MCB_S1G_CFG_TIMEOUT * 1000);
पूर्ण

अटल पूर्णांक serdes_commit_mcb_s1g(काष्ठा regmap *regmap, u8 macro)
अणु
	वापस __serdes_ग_लिखो_mcb_s1g(regmap, macro,
		HSIO_MCB_S1G_ADDR_CFG_SERDES1G_WR_ONE_SHOT);
पूर्ण

अटल पूर्णांक serdes_update_mcb_s1g(काष्ठा regmap *regmap, u8 macro)
अणु
	वापस __serdes_ग_लिखो_mcb_s1g(regmap, macro,
		HSIO_MCB_S1G_ADDR_CFG_SERDES1G_RD_ONE_SHOT);
पूर्ण

अटल पूर्णांक serdes_init_s1g(काष्ठा regmap *regmap, u8 serdes)
अणु
	पूर्णांक ret;

	ret = serdes_update_mcb_s1g(regmap, serdes);
	अगर (ret)
		वापस ret;

	regmap_update_bits(regmap, HSIO_S1G_COMMON_CFG,
			   HSIO_S1G_COMMON_CFG_SYS_RST |
			   HSIO_S1G_COMMON_CFG_ENA_LANE |
			   HSIO_S1G_COMMON_CFG_ENA_ELOOP |
			   HSIO_S1G_COMMON_CFG_ENA_FLOOP,
			   HSIO_S1G_COMMON_CFG_ENA_LANE);

	regmap_update_bits(regmap, HSIO_S1G_PLL_CFG,
			   HSIO_S1G_PLL_CFG_PLL_FSM_ENA |
			   HSIO_S1G_PLL_CFG_PLL_FSM_CTRL_DATA_M,
			   HSIO_S1G_PLL_CFG_PLL_FSM_CTRL_DATA(200) |
			   HSIO_S1G_PLL_CFG_PLL_FSM_ENA);

	regmap_update_bits(regmap, HSIO_S1G_MISC_CFG,
			   HSIO_S1G_MISC_CFG_DES_100FX_CPMD_ENA |
			   HSIO_S1G_MISC_CFG_LANE_RST,
			   HSIO_S1G_MISC_CFG_LANE_RST);

	ret = serdes_commit_mcb_s1g(regmap, serdes);
	अगर (ret)
		वापस ret;

	regmap_update_bits(regmap, HSIO_S1G_COMMON_CFG,
			   HSIO_S1G_COMMON_CFG_SYS_RST,
			   HSIO_S1G_COMMON_CFG_SYS_RST);

	regmap_update_bits(regmap, HSIO_S1G_MISC_CFG,
			   HSIO_S1G_MISC_CFG_LANE_RST, 0);

	ret = serdes_commit_mcb_s1g(regmap, serdes);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

काष्ठा serdes_mux अणु
	u8			idx;
	u8			port;
	क्रमागत phy_mode		mode;
	पूर्णांक			submode;
	u32			mask;
	u32			mux;
पूर्ण;

#घोषणा SERDES_MUX(_idx, _port, _mode, _submode, _mask, _mux) अणु \
	.idx = _idx,						\
	.port = _port,						\
	.mode = _mode,						\
	.submode = _submode,					\
	.mask = _mask,						\
	.mux = _mux,						\
पूर्ण

#घोषणा SERDES_MUX_SGMII(i, p, m, c) \
	SERDES_MUX(i, p, PHY_MODE_ETHERNET, PHY_INTERFACE_MODE_SGMII, m, c)
#घोषणा SERDES_MUX_QSGMII(i, p, m, c) \
	SERDES_MUX(i, p, PHY_MODE_ETHERNET, PHY_INTERFACE_MODE_QSGMII, m, c)

अटल स्थिर काष्ठा serdes_mux ocelot_serdes_muxes[] = अणु
	SERDES_MUX_SGMII(SERDES1G(0), 0, 0, 0),
	SERDES_MUX_SGMII(SERDES1G(1), 1, HSIO_HW_CFG_DEV1G_5_MODE, 0),
	SERDES_MUX_SGMII(SERDES1G(1), 5, HSIO_HW_CFG_QSGMII_ENA |
			 HSIO_HW_CFG_DEV1G_5_MODE, HSIO_HW_CFG_DEV1G_5_MODE),
	SERDES_MUX_SGMII(SERDES1G(2), 2, HSIO_HW_CFG_DEV1G_4_MODE, 0),
	SERDES_MUX_SGMII(SERDES1G(2), 4, HSIO_HW_CFG_QSGMII_ENA |
			 HSIO_HW_CFG_DEV1G_4_MODE, HSIO_HW_CFG_DEV1G_4_MODE),
	SERDES_MUX_SGMII(SERDES1G(3), 3, HSIO_HW_CFG_DEV1G_6_MODE, 0),
	SERDES_MUX_SGMII(SERDES1G(3), 6, HSIO_HW_CFG_QSGMII_ENA |
			 HSIO_HW_CFG_DEV1G_6_MODE, HSIO_HW_CFG_DEV1G_6_MODE),
	SERDES_MUX_SGMII(SERDES1G(4), 4, HSIO_HW_CFG_QSGMII_ENA |
			 HSIO_HW_CFG_DEV1G_4_MODE | HSIO_HW_CFG_DEV1G_9_MODE,
			 0),
	SERDES_MUX_SGMII(SERDES1G(4), 9, HSIO_HW_CFG_DEV1G_4_MODE |
			 HSIO_HW_CFG_DEV1G_9_MODE, HSIO_HW_CFG_DEV1G_4_MODE |
			 HSIO_HW_CFG_DEV1G_9_MODE),
	SERDES_MUX_SGMII(SERDES1G(5), 5, HSIO_HW_CFG_QSGMII_ENA |
			 HSIO_HW_CFG_DEV1G_5_MODE | HSIO_HW_CFG_DEV2G5_10_MODE,
			 0),
	SERDES_MUX_SGMII(SERDES1G(5), 10, HSIO_HW_CFG_PCIE_ENA |
			 HSIO_HW_CFG_DEV1G_5_MODE | HSIO_HW_CFG_DEV2G5_10_MODE,
			 HSIO_HW_CFG_DEV1G_5_MODE | HSIO_HW_CFG_DEV2G5_10_MODE),
	SERDES_MUX_QSGMII(SERDES6G(0), 4, HSIO_HW_CFG_QSGMII_ENA,
			  HSIO_HW_CFG_QSGMII_ENA),
	SERDES_MUX_QSGMII(SERDES6G(0), 5, HSIO_HW_CFG_QSGMII_ENA,
			  HSIO_HW_CFG_QSGMII_ENA),
	SERDES_MUX_QSGMII(SERDES6G(0), 6, HSIO_HW_CFG_QSGMII_ENA,
			  HSIO_HW_CFG_QSGMII_ENA),
	SERDES_MUX_SGMII(SERDES6G(0), 7, HSIO_HW_CFG_QSGMII_ENA, 0),
	SERDES_MUX_QSGMII(SERDES6G(0), 7, HSIO_HW_CFG_QSGMII_ENA,
			  HSIO_HW_CFG_QSGMII_ENA),
	SERDES_MUX_SGMII(SERDES6G(1), 8, 0, 0),
	SERDES_MUX_SGMII(SERDES6G(2), 10, HSIO_HW_CFG_PCIE_ENA |
			 HSIO_HW_CFG_DEV2G5_10_MODE, 0),
	SERDES_MUX(SERDES6G(2), 10, PHY_MODE_PCIE, 0, HSIO_HW_CFG_PCIE_ENA,
		   HSIO_HW_CFG_PCIE_ENA),
पूर्ण;

अटल पूर्णांक serdes_set_mode(काष्ठा phy *phy, क्रमागत phy_mode mode, पूर्णांक submode)
अणु
	काष्ठा serdes_macro *macro = phy_get_drvdata(phy);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/* As of now only PHY_MODE_ETHERNET is supported */
	अगर (mode != PHY_MODE_ETHERNET)
		वापस -EOPNOTSUPP;

	क्रम (i = 0; i < ARRAY_SIZE(ocelot_serdes_muxes); i++) अणु
		अगर (macro->idx != ocelot_serdes_muxes[i].idx ||
		    mode != ocelot_serdes_muxes[i].mode ||
		    submode != ocelot_serdes_muxes[i].submode)
			जारी;

		अगर (submode != PHY_INTERFACE_MODE_QSGMII &&
		    macro->port != ocelot_serdes_muxes[i].port)
			जारी;

		ret = regmap_update_bits(macro->ctrl->regs, HSIO_HW_CFG,
					 ocelot_serdes_muxes[i].mask,
					 ocelot_serdes_muxes[i].mux);
		अगर (ret)
			वापस ret;

		अगर (macro->idx <= SERDES1G_MAX)
			वापस serdes_init_s1g(macro->ctrl->regs, macro->idx);
		अन्यथा अगर (macro->idx <= SERDES6G_MAX)
			वापस serdes_init_s6g(macro->ctrl->regs,
					       macro->idx - (SERDES1G_MAX + 1),
					       ocelot_serdes_muxes[i].submode);

		/* PCIe not supported yet */
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा phy_ops serdes_ops = अणु
	.set_mode	= serdes_set_mode,
	.owner		= THIS_MODULE,
पूर्ण;

अटल काष्ठा phy *serdes_simple_xlate(काष्ठा device *dev,
				       काष्ठा of_phandle_args *args)
अणु
	काष्ठा serdes_ctrl *ctrl = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक port, idx, i;

	अगर (args->args_count != 2)
		वापस ERR_PTR(-EINVAL);

	port = args->args[0];
	idx = args->args[1];

	क्रम (i = 0; i < SERDES_MAX; i++) अणु
		काष्ठा serdes_macro *macro = phy_get_drvdata(ctrl->phys[i]);

		अगर (idx != macro->idx)
			जारी;

		/* SERDES6G(0) is the only SerDes capable of QSGMII */
		अगर (idx != SERDES6G(0) && macro->port >= 0)
			वापस ERR_PTR(-EBUSY);

		macro->port = port;
		वापस ctrl->phys[i];
	पूर्ण

	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल पूर्णांक serdes_phy_create(काष्ठा serdes_ctrl *ctrl, u8 idx, काष्ठा phy **phy)
अणु
	काष्ठा serdes_macro *macro;

	*phy = devm_phy_create(ctrl->dev, शून्य, &serdes_ops);
	अगर (IS_ERR(*phy))
		वापस PTR_ERR(*phy);

	macro = devm_kzalloc(ctrl->dev, माप(*macro), GFP_KERNEL);
	अगर (!macro)
		वापस -ENOMEM;

	macro->idx = idx;
	macro->ctrl = ctrl;
	macro->port = -1;

	phy_set_drvdata(*phy, macro);

	वापस 0;
पूर्ण

अटल पूर्णांक serdes_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा phy_provider *provider;
	काष्ठा serdes_ctrl *ctrl;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ctrl = devm_kzalloc(&pdev->dev, माप(*ctrl), GFP_KERNEL);
	अगर (!ctrl)
		वापस -ENOMEM;

	ctrl->dev = &pdev->dev;
	ctrl->regs = syscon_node_to_regmap(pdev->dev.parent->of_node);
	अगर (IS_ERR(ctrl->regs))
		वापस PTR_ERR(ctrl->regs);

	क्रम (i = 0; i < SERDES_MAX; i++) अणु
		ret = serdes_phy_create(ctrl, i, &ctrl->phys[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	dev_set_drvdata(&pdev->dev, ctrl);

	provider = devm_of_phy_provider_रेजिस्टर(ctrl->dev,
						 serdes_simple_xlate);

	वापस PTR_ERR_OR_ZERO(provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id serdes_ids[] = अणु
	अणु .compatible = "mscc,vsc7514-serdes", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, serdes_ids);

अटल काष्ठा platक्रमm_driver mscc_ocelot_serdes = अणु
	.probe		= serdes_probe,
	.driver		= अणु
		.name	= "mscc,ocelot-serdes",
		.of_match_table = of_match_ptr(serdes_ids),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mscc_ocelot_serdes);

MODULE_AUTHOR("Quentin Schulz <quentin.schulz@bootlin.com>");
MODULE_DESCRIPTION("SerDes driver for Microsemi Ocelot");
MODULE_LICENSE("Dual MIT/GPL");
