<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2015-2016, The Linux Foundation. All rights reserved.
 */

/* Qualcomm Technologies, Inc. QDF2432 EMAC SGMII Controller driver.
 */

#समावेश <linux/iopoll.h>
#समावेश "emac.h"

/* EMAC_SGMII रेजिस्टर offsets */
#घोषणा EMAC_SGMII_PHY_TX_PWR_CTRL		0x000C
#घोषणा EMAC_SGMII_PHY_LANE_CTRL1		0x0018
#घोषणा EMAC_SGMII_PHY_CDR_CTRL0		0x0058
#घोषणा EMAC_SGMII_PHY_POW_DWN_CTRL0		0x0080
#घोषणा EMAC_SGMII_PHY_RESET_CTRL		0x00a8
#घोषणा EMAC_SGMII_PHY_INTERRUPT_MASK		0x00b4

/* SGMII digital lane रेजिस्टरs */
#घोषणा EMAC_SGMII_LN_DRVR_CTRL0		0x000C
#घोषणा EMAC_SGMII_LN_DRVR_TAP_EN		0x0018
#घोषणा EMAC_SGMII_LN_TX_MARGINING		0x001C
#घोषणा EMAC_SGMII_LN_TX_PRE			0x0020
#घोषणा EMAC_SGMII_LN_TX_POST			0x0024
#घोषणा EMAC_SGMII_LN_TX_BAND_MODE		0x0060
#घोषणा EMAC_SGMII_LN_LANE_MODE			0x0064
#घोषणा EMAC_SGMII_LN_PARALLEL_RATE		0x0078
#घोषणा EMAC_SGMII_LN_CML_CTRL_MODE0		0x00B8
#घोषणा EMAC_SGMII_LN_MIXER_CTRL_MODE0		0x00D0
#घोषणा EMAC_SGMII_LN_VGA_INITVAL		0x0134
#घोषणा EMAC_SGMII_LN_UCDR_FO_GAIN_MODE0	0x017C
#घोषणा EMAC_SGMII_LN_UCDR_SO_GAIN_MODE0	0x0188
#घोषणा EMAC_SGMII_LN_UCDR_SO_CONFIG		0x0194
#घोषणा EMAC_SGMII_LN_RX_BAND			0x019C
#घोषणा EMAC_SGMII_LN_RX_RCVR_PATH1_MODE0	0x01B8
#घोषणा EMAC_SGMII_LN_RSM_CONFIG		0x01F0
#घोषणा EMAC_SGMII_LN_SIGDET_ENABLES		0x0224
#घोषणा EMAC_SGMII_LN_SIGDET_CNTRL		0x0228
#घोषणा EMAC_SGMII_LN_SIGDET_DEGLITCH_CNTRL	0x022C
#घोषणा EMAC_SGMII_LN_RX_EN_SIGNAL		0x02A0
#घोषणा EMAC_SGMII_LN_RX_MISC_CNTRL0		0x02AC
#घोषणा EMAC_SGMII_LN_DRVR_LOGIC_CLKDIV		0x02BC

/* SGMII digital lane रेजिस्टर values */
#घोषणा UCDR_STEP_BY_TWO_MODE0			BIT(7)
#घोषणा UCDR_xO_GAIN_MODE(x)			((x) & 0x7f)
#घोषणा UCDR_ENABLE				BIT(6)
#घोषणा UCDR_SO_SATURATION(x)			((x) & 0x3f)

#घोषणा SIGDET_LP_BYP_PS4			BIT(7)
#घोषणा SIGDET_EN_PS0_TO_PS2			BIT(6)

#घोषणा TXVAL_VALID_INIT			BIT(4)
#घोषणा KR_PCIGEN3_MODE				BIT(0)

#घोषणा MAIN_EN					BIT(0)

#घोषणा TX_MARGINING_MUX			BIT(6)
#घोषणा TX_MARGINING(x)				((x) & 0x3f)

#घोषणा TX_PRE_MUX				BIT(6)

#घोषणा TX_POST_MUX				BIT(6)

#घोषणा CML_GEAR_MODE(x)			(((x) & 7) << 3)
#घोषणा CML2CMOS_IBOOST_MODE(x)			((x) & 7)

#घोषणा MIXER_LOADB_MODE(x)			(((x) & 0xf) << 2)
#घोषणा MIXER_DATARATE_MODE(x)			((x) & 3)

#घोषणा VGA_THRESH_DFE(x)			((x) & 0x3f)

#घोषणा SIGDET_LP_BYP_PS0_TO_PS2		BIT(5)
#घोषणा SIGDET_FLT_BYP				BIT(0)

#घोषणा SIGDET_LVL(x)				(((x) & 0xf) << 4)

#घोषणा SIGDET_DEGLITCH_CTRL(x)			(((x) & 0xf) << 1)

#घोषणा DRVR_LOGIC_CLK_EN			BIT(4)
#घोषणा DRVR_LOGIC_CLK_DIV(x)			((x) & 0xf)

#घोषणा PARALLEL_RATE_MODE0(x)			((x) & 0x3)

#घोषणा BAND_MODE0(x)				((x) & 0x3)

#घोषणा LANE_MODE(x)				((x) & 0x1f)

#घोषणा CDR_PD_SEL_MODE0(x)			(((x) & 0x3) << 5)
#घोषणा BYPASS_RSM_SAMP_CAL			BIT(1)
#घोषणा BYPASS_RSM_DLL_CAL			BIT(0)

#घोषणा L0_RX_EQUALIZE_ENABLE			BIT(6)

#घोषणा PWRDN_B					BIT(0)

#घोषणा CDR_MAX_CNT(x)				((x) & 0xff)

#घोषणा SERDES_START_WAIT_TIMES			100

काष्ठा emac_reg_ग_लिखो अणु
	अचिन्हित पूर्णांक offset;
	u32 val;
पूर्ण;

अटल व्योम emac_reg_ग_लिखो_all(व्योम __iomem *base,
			       स्थिर काष्ठा emac_reg_ग_लिखो *itr, माप_प्रकार size)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < size; ++itr, ++i)
		ग_लिखोl(itr->val, base + itr->offset);
पूर्ण

अटल स्थिर काष्ठा emac_reg_ग_लिखो sgmii_laned[] = अणु
	/* CDR Settings */
	अणुEMAC_SGMII_LN_UCDR_FO_GAIN_MODE0,
		UCDR_STEP_BY_TWO_MODE0 | UCDR_xO_GAIN_MODE(10)पूर्ण,
	अणुEMAC_SGMII_LN_UCDR_SO_GAIN_MODE0, UCDR_xO_GAIN_MODE(0)पूर्ण,
	अणुEMAC_SGMII_LN_UCDR_SO_CONFIG, UCDR_ENABLE | UCDR_SO_SATURATION(12)पूर्ण,

	/* TX/RX Settings */
	अणुEMAC_SGMII_LN_RX_EN_SIGNAL, SIGDET_LP_BYP_PS4 | SIGDET_EN_PS0_TO_PS2पूर्ण,

	अणुEMAC_SGMII_LN_DRVR_CTRL0, TXVAL_VALID_INIT | KR_PCIGEN3_MODEपूर्ण,
	अणुEMAC_SGMII_LN_DRVR_TAP_EN, MAIN_ENपूर्ण,
	अणुEMAC_SGMII_LN_TX_MARGINING, TX_MARGINING_MUX | TX_MARGINING(25)पूर्ण,
	अणुEMAC_SGMII_LN_TX_PRE, TX_PRE_MUXपूर्ण,
	अणुEMAC_SGMII_LN_TX_POST, TX_POST_MUXपूर्ण,

	अणुEMAC_SGMII_LN_CML_CTRL_MODE0,
		CML_GEAR_MODE(1) | CML2CMOS_IBOOST_MODE(1)पूर्ण,
	अणुEMAC_SGMII_LN_MIXER_CTRL_MODE0,
		MIXER_LOADB_MODE(12) | MIXER_DATARATE_MODE(1)पूर्ण,
	अणुEMAC_SGMII_LN_VGA_INITVAL, VGA_THRESH_DFE(31)पूर्ण,
	अणुEMAC_SGMII_LN_SIGDET_ENABLES,
		SIGDET_LP_BYP_PS0_TO_PS2 | SIGDET_FLT_BYPपूर्ण,
	अणुEMAC_SGMII_LN_SIGDET_CNTRL, SIGDET_LVL(8)पूर्ण,

	अणुEMAC_SGMII_LN_SIGDET_DEGLITCH_CNTRL, SIGDET_DEGLITCH_CTRL(4)पूर्ण,
	अणुEMAC_SGMII_LN_RX_MISC_CNTRL0, 0पूर्ण,
	अणुEMAC_SGMII_LN_DRVR_LOGIC_CLKDIV,
		DRVR_LOGIC_CLK_EN | DRVR_LOGIC_CLK_DIV(4)पूर्ण,

	अणुEMAC_SGMII_LN_PARALLEL_RATE, PARALLEL_RATE_MODE0(1)पूर्ण,
	अणुEMAC_SGMII_LN_TX_BAND_MODE, BAND_MODE0(2)पूर्ण,
	अणुEMAC_SGMII_LN_RX_BAND, BAND_MODE0(3)पूर्ण,
	अणुEMAC_SGMII_LN_LANE_MODE, LANE_MODE(26)पूर्ण,
	अणुEMAC_SGMII_LN_RX_RCVR_PATH1_MODE0, CDR_PD_SEL_MODE0(3)पूर्ण,
	अणुEMAC_SGMII_LN_RSM_CONFIG, BYPASS_RSM_SAMP_CAL | BYPASS_RSM_DLL_CALपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा emac_reg_ग_लिखो physical_coding_sublayer_programming[] = अणु
	अणुEMAC_SGMII_PHY_POW_DWN_CTRL0, PWRDN_Bपूर्ण,
	अणुEMAC_SGMII_PHY_CDR_CTRL0, CDR_MAX_CNT(15)पूर्ण,
	अणुEMAC_SGMII_PHY_TX_PWR_CTRL, 0पूर्ण,
	अणुEMAC_SGMII_PHY_LANE_CTRL1, L0_RX_EQUALIZE_ENABLEपूर्ण,
पूर्ण;

पूर्णांक emac_sgmii_init_qdf2432(काष्ठा emac_adapter *adpt)
अणु
	काष्ठा emac_sgmii *phy = &adpt->phy;
	व्योम __iomem *phy_regs = phy->base;
	व्योम __iomem *laned = phy->digital;
	अचिन्हित पूर्णांक i;
	u32 lnstatus;

	/* PCS lane-x init */
	emac_reg_ग_लिखो_all(phy->base, physical_coding_sublayer_programming,
			   ARRAY_SIZE(physical_coding_sublayer_programming));

	/* SGMII lane-x init */
	emac_reg_ग_लिखो_all(phy->digital, sgmii_laned, ARRAY_SIZE(sgmii_laned));

	/* Power up PCS and start reset lane state machine */

	ग_लिखोl(0, phy_regs + EMAC_SGMII_PHY_RESET_CTRL);
	ग_लिखोl(1, laned + SGMII_LN_RSM_START);

	/* Wait क्रम c_पढ़ोy निश्चितion */
	क्रम (i = 0; i < SERDES_START_WAIT_TIMES; i++) अणु
		lnstatus = पढ़ोl(phy_regs + SGMII_PHY_LN_LANE_STATUS);
		अगर (lnstatus & BIT(1))
			अवरोध;
		usleep_range(100, 200);
	पूर्ण

	अगर (i == SERDES_START_WAIT_TIMES) अणु
		netdev_err(adpt->netdev, "SGMII failed to start\n");
		वापस -EIO;
	पूर्ण

	/* Disable digital and SERDES loopback */
	ग_लिखोl(0, phy_regs + SGMII_PHY_LN_BIST_GEN0);
	ग_लिखोl(0, phy_regs + SGMII_PHY_LN_BIST_GEN2);
	ग_लिखोl(0, phy_regs + SGMII_PHY_LN_CDR_CTRL1);

	/* Mask out all the SGMII Interrupt */
	ग_लिखोl(0, phy_regs + EMAC_SGMII_PHY_INTERRUPT_MASK);

	वापस 0;
पूर्ण
