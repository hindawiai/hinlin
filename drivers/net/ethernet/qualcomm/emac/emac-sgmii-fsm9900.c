<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2015-2016, The Linux Foundation. All rights reserved.
 */

/* Qualcomm Technologies, Inc. FSM9900 EMAC SGMII Controller driver.
 */

#समावेश <linux/iopoll.h>
#समावेश "emac.h"

/* EMAC_QSERDES रेजिस्टर offsets */
#घोषणा EMAC_QSERDES_COM_SYS_CLK_CTRL		0x0000
#घोषणा EMAC_QSERDES_COM_PLL_CNTRL		0x0014
#घोषणा EMAC_QSERDES_COM_PLL_IP_SETI		0x0018
#घोषणा EMAC_QSERDES_COM_PLL_CP_SETI		0x0024
#घोषणा EMAC_QSERDES_COM_PLL_IP_SETP		0x0028
#घोषणा EMAC_QSERDES_COM_PLL_CP_SETP		0x002c
#घोषणा EMAC_QSERDES_COM_SYSCLK_EN_SEL		0x0038
#घोषणा EMAC_QSERDES_COM_RESETSM_CNTRL		0x0040
#घोषणा EMAC_QSERDES_COM_PLLLOCK_CMP1		0x0044
#घोषणा EMAC_QSERDES_COM_PLLLOCK_CMP2		0x0048
#घोषणा EMAC_QSERDES_COM_PLLLOCK_CMP3		0x004c
#घोषणा EMAC_QSERDES_COM_PLLLOCK_CMP_EN		0x0050
#घोषणा EMAC_QSERDES_COM_DEC_START1		0x0064
#घोषणा EMAC_QSERDES_COM_DIV_FRAC_START1	0x0098
#घोषणा EMAC_QSERDES_COM_DIV_FRAC_START2	0x009c
#घोषणा EMAC_QSERDES_COM_DIV_FRAC_START3	0x00a0
#घोषणा EMAC_QSERDES_COM_DEC_START2		0x00a4
#घोषणा EMAC_QSERDES_COM_PLL_CRCTRL		0x00ac
#घोषणा EMAC_QSERDES_COM_RESET_SM		0x00bc
#घोषणा EMAC_QSERDES_TX_BIST_MODE_LANENO	0x0100
#घोषणा EMAC_QSERDES_TX_TX_EMP_POST1_LVL	0x0108
#घोषणा EMAC_QSERDES_TX_TX_DRV_LVL		0x010c
#घोषणा EMAC_QSERDES_TX_LANE_MODE		0x0150
#घोषणा EMAC_QSERDES_TX_TRAN_DRVR_EMP_EN	0x0170
#घोषणा EMAC_QSERDES_RX_CDR_CONTROL		0x0200
#घोषणा EMAC_QSERDES_RX_CDR_CONTROL2		0x0210
#घोषणा EMAC_QSERDES_RX_RX_EQ_GAIN12		0x0230

/* EMAC_SGMII रेजिस्टर offsets */
#घोषणा EMAC_SGMII_PHY_SERDES_START		0x0000
#घोषणा EMAC_SGMII_PHY_CMN_PWR_CTRL		0x0004
#घोषणा EMAC_SGMII_PHY_RX_PWR_CTRL		0x0008
#घोषणा EMAC_SGMII_PHY_TX_PWR_CTRL		0x000C
#घोषणा EMAC_SGMII_PHY_LANE_CTRL1		0x0018
#घोषणा EMAC_SGMII_PHY_CDR_CTRL0		0x0058
#घोषणा EMAC_SGMII_PHY_POW_DWN_CTRL0		0x0080
#घोषणा EMAC_SGMII_PHY_INTERRUPT_MASK		0x00b4

#घोषणा PLL_IPSETI(x)				((x) & 0x3f)

#घोषणा PLL_CPSETI(x)				((x) & 0xff)

#घोषणा PLL_IPSETP(x)				((x) & 0x3f)

#घोषणा PLL_CPSETP(x)				((x) & 0x1f)

#घोषणा PLL_RCTRL(x)				(((x) & 0xf) << 4)
#घोषणा PLL_CCTRL(x)				((x) & 0xf)

#घोषणा LANE_MODE(x)				((x) & 0x1f)

#घोषणा SYSCLK_CM				BIT(4)
#घोषणा SYSCLK_AC_COUPLE			BIT(3)

#घोषणा OCP_EN					BIT(5)
#घोषणा PLL_DIV_FFEN				BIT(2)
#घोषणा PLL_DIV_ORD				BIT(1)

#घोषणा SYSCLK_SEL_CMOS				BIT(3)

#घोषणा FRQ_TUNE_MODE				BIT(4)

#घोषणा PLLLOCK_CMP_EN				BIT(0)

#घोषणा DEC_START1_MUX				BIT(7)
#घोषणा DEC_START1(x)				((x) & 0x7f)

#घोषणा DIV_FRAC_START_MUX			BIT(7)
#घोषणा DIV_FRAC_START(x)			((x) & 0x7f)

#घोषणा DIV_FRAC_START3_MUX			BIT(4)
#घोषणा DIV_FRAC_START3(x)			((x) & 0xf)

#घोषणा DEC_START2_MUX				BIT(1)
#घोषणा DEC_START2				BIT(0)

#घोषणा READY					BIT(5)

#घोषणा TX_EMP_POST1_LVL_MUX			BIT(5)
#घोषणा TX_EMP_POST1_LVL(x)			((x) & 0x1f)

#घोषणा TX_DRV_LVL_MUX				BIT(4)
#घोषणा TX_DRV_LVL(x)				((x) & 0xf)

#घोषणा EMP_EN_MUX				BIT(1)
#घोषणा EMP_EN					BIT(0)

#घोषणा SECONDORDERENABLE			BIT(6)
#घोषणा FIRSTORDER_THRESH(x)			(((x) & 0x7) << 3)
#घोषणा SECONDORDERGAIN(x)			((x) & 0x7)

#घोषणा RX_EQ_GAIN2(x)				(((x) & 0xf) << 4)
#घोषणा RX_EQ_GAIN1(x)				((x) & 0xf)

#घोषणा SERDES_START				BIT(0)

#घोषणा BIAS_EN					BIT(6)
#घोषणा PLL_EN					BIT(5)
#घोषणा SYSCLK_EN				BIT(4)
#घोषणा CLKBUF_L_EN				BIT(3)
#घोषणा PLL_TXCLK_EN				BIT(1)
#घोषणा PLL_RXCLK_EN				BIT(0)

#घोषणा L0_RX_SIGDET_EN				BIT(7)
#घोषणा L0_RX_TERM_MODE(x)			(((x) & 3) << 4)
#घोषणा L0_RX_I_EN				BIT(1)

#घोषणा L0_TX_EN				BIT(5)
#घोषणा L0_CLKBUF_EN				BIT(4)
#घोषणा L0_TRAN_BIAS_EN				BIT(1)

#घोषणा L0_RX_EQUALIZE_ENABLE			BIT(6)
#घोषणा L0_RESET_TSYNC_EN			BIT(4)
#घोषणा L0_DRV_LVL(x)				((x) & 0xf)

#घोषणा PWRDN_B					BIT(0)
#घोषणा CDR_MAX_CNT(x)				((x) & 0xff)

#घोषणा PLLLOCK_CMP(x)				((x) & 0xff)

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

अटल स्थिर काष्ठा emac_reg_ग_लिखो physical_coding_sublayer_programming[] = अणु
	अणुEMAC_SGMII_PHY_CDR_CTRL0, CDR_MAX_CNT(15)पूर्ण,
	अणुEMAC_SGMII_PHY_POW_DWN_CTRL0, PWRDN_Bपूर्ण,
	अणुEMAC_SGMII_PHY_CMN_PWR_CTRL,
		BIAS_EN | SYSCLK_EN | CLKBUF_L_EN | PLL_TXCLK_EN | PLL_RXCLK_ENपूर्ण,
	अणुEMAC_SGMII_PHY_TX_PWR_CTRL, L0_TX_EN | L0_CLKBUF_EN | L0_TRAN_BIAS_ENपूर्ण,
	अणुEMAC_SGMII_PHY_RX_PWR_CTRL,
		L0_RX_SIGDET_EN | L0_RX_TERM_MODE(1) | L0_RX_I_ENपूर्ण,
	अणुEMAC_SGMII_PHY_CMN_PWR_CTRL,
		BIAS_EN | PLL_EN | SYSCLK_EN | CLKBUF_L_EN | PLL_TXCLK_EN |
		PLL_RXCLK_ENपूर्ण,
	अणुEMAC_SGMII_PHY_LANE_CTRL1,
		L0_RX_EQUALIZE_ENABLE | L0_RESET_TSYNC_EN | L0_DRV_LVL(15)पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा emac_reg_ग_लिखो sysclk_refclk_setting[] = अणु
	अणुEMAC_QSERDES_COM_SYSCLK_EN_SEL, SYSCLK_SEL_CMOSपूर्ण,
	अणुEMAC_QSERDES_COM_SYS_CLK_CTRL,	SYSCLK_CM | SYSCLK_AC_COUPLEपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा emac_reg_ग_लिखो pll_setting[] = अणु
	अणुEMAC_QSERDES_COM_PLL_IP_SETI, PLL_IPSETI(1)पूर्ण,
	अणुEMAC_QSERDES_COM_PLL_CP_SETI, PLL_CPSETI(59)पूर्ण,
	अणुEMAC_QSERDES_COM_PLL_IP_SETP, PLL_IPSETP(10)पूर्ण,
	अणुEMAC_QSERDES_COM_PLL_CP_SETP, PLL_CPSETP(9)पूर्ण,
	अणुEMAC_QSERDES_COM_PLL_CRCTRL, PLL_RCTRL(15) | PLL_CCTRL(11)पूर्ण,
	अणुEMAC_QSERDES_COM_PLL_CNTRL, OCP_EN | PLL_DIV_FFEN | PLL_DIV_ORDपूर्ण,
	अणुEMAC_QSERDES_COM_DEC_START1, DEC_START1_MUX | DEC_START1(2)पूर्ण,
	अणुEMAC_QSERDES_COM_DEC_START2, DEC_START2_MUX | DEC_START2पूर्ण,
	अणुEMAC_QSERDES_COM_DIV_FRAC_START1,
		DIV_FRAC_START_MUX | DIV_FRAC_START(85)पूर्ण,
	अणुEMAC_QSERDES_COM_DIV_FRAC_START2,
		DIV_FRAC_START_MUX | DIV_FRAC_START(42)पूर्ण,
	अणुEMAC_QSERDES_COM_DIV_FRAC_START3,
		DIV_FRAC_START3_MUX | DIV_FRAC_START3(3)पूर्ण,
	अणुEMAC_QSERDES_COM_PLLLOCK_CMP1, PLLLOCK_CMP(43)पूर्ण,
	अणुEMAC_QSERDES_COM_PLLLOCK_CMP2, PLLLOCK_CMP(104)पूर्ण,
	अणुEMAC_QSERDES_COM_PLLLOCK_CMP3, PLLLOCK_CMP(0)पूर्ण,
	अणुEMAC_QSERDES_COM_PLLLOCK_CMP_EN, PLLLOCK_CMP_ENपूर्ण,
	अणुEMAC_QSERDES_COM_RESETSM_CNTRL, FRQ_TUNE_MODEपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा emac_reg_ग_लिखो cdr_setting[] = अणु
	अणुEMAC_QSERDES_RX_CDR_CONTROL,
		SECONDORDERENABLE | FIRSTORDER_THRESH(3) | SECONDORDERGAIN(2)पूर्ण,
	अणुEMAC_QSERDES_RX_CDR_CONTROL2,
		SECONDORDERENABLE | FIRSTORDER_THRESH(3) | SECONDORDERGAIN(4)पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा emac_reg_ग_लिखो tx_rx_setting[] = अणु
	अणुEMAC_QSERDES_TX_BIST_MODE_LANENO, 0पूर्ण,
	अणुEMAC_QSERDES_TX_TX_DRV_LVL, TX_DRV_LVL_MUX | TX_DRV_LVL(15)पूर्ण,
	अणुEMAC_QSERDES_TX_TRAN_DRVR_EMP_EN, EMP_EN_MUX | EMP_ENपूर्ण,
	अणुEMAC_QSERDES_TX_TX_EMP_POST1_LVL,
		TX_EMP_POST1_LVL_MUX | TX_EMP_POST1_LVL(1)पूर्ण,
	अणुEMAC_QSERDES_RX_RX_EQ_GAIN12, RX_EQ_GAIN2(15) | RX_EQ_GAIN1(15)पूर्ण,
	अणुEMAC_QSERDES_TX_LANE_MODE, LANE_MODE(8)पूर्ण,
पूर्ण;

पूर्णांक emac_sgmii_init_fsm9900(काष्ठा emac_adapter *adpt)
अणु
	काष्ठा emac_sgmii *phy = &adpt->phy;
	अचिन्हित पूर्णांक i;

	emac_reg_ग_लिखो_all(phy->base, physical_coding_sublayer_programming,
			   ARRAY_SIZE(physical_coding_sublayer_programming));
	emac_reg_ग_लिखो_all(phy->base, sysclk_refclk_setting,
			   ARRAY_SIZE(sysclk_refclk_setting));
	emac_reg_ग_लिखो_all(phy->base, pll_setting, ARRAY_SIZE(pll_setting));
	emac_reg_ग_लिखो_all(phy->base, cdr_setting, ARRAY_SIZE(cdr_setting));
	emac_reg_ग_लिखो_all(phy->base, tx_rx_setting, ARRAY_SIZE(tx_rx_setting));

	/* Power up the Ser/Des engine */
	ग_लिखोl(SERDES_START, phy->base + EMAC_SGMII_PHY_SERDES_START);

	क्रम (i = 0; i < SERDES_START_WAIT_TIMES; i++) अणु
		अगर (पढ़ोl(phy->base + EMAC_QSERDES_COM_RESET_SM) & READY)
			अवरोध;
		usleep_range(100, 200);
	पूर्ण

	अगर (i == SERDES_START_WAIT_TIMES) अणु
		netdev_err(adpt->netdev, "error: ser/des failed to start\n");
		वापस -EIO;
	पूर्ण
	/* Mask out all the SGMII Interrupt */
	ग_लिखोl(0, phy->base + EMAC_SGMII_PHY_INTERRUPT_MASK);

	वापस 0;
पूर्ण
