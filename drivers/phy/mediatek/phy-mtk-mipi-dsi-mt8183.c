<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2019 MediaTek Inc.
 * Author: jitao.shi <jitao.shi@mediatek.com>
 */

#समावेश "phy-mtk-mipi-dsi.h"

#घोषणा MIPITX_LANE_CON		0x000c
#घोषणा RG_DSI_CPHY_T1DRV_EN		BIT(0)
#घोषणा RG_DSI_ANA_CK_SEL		BIT(1)
#घोषणा RG_DSI_PHY_CK_SEL		BIT(2)
#घोषणा RG_DSI_CPHY_EN			BIT(3)
#घोषणा RG_DSI_PHYCK_INV_EN		BIT(4)
#घोषणा RG_DSI_PWR04_EN			BIT(5)
#घोषणा RG_DSI_BG_LPF_EN		BIT(6)
#घोषणा RG_DSI_BG_CORE_EN		BIT(7)
#घोषणा RG_DSI_PAD_TIEL_SEL		BIT(8)

#घोषणा MIPITX_VOLTAGE_SEL	0x0010
#घोषणा RG_DSI_HSTX_LDO_REF_SEL		(0xf << 6)

#घोषणा MIPITX_PLL_PWR		0x0028
#घोषणा MIPITX_PLL_CON0		0x002c
#घोषणा MIPITX_PLL_CON1		0x0030
#घोषणा MIPITX_PLL_CON2		0x0034
#घोषणा MIPITX_PLL_CON3		0x0038
#घोषणा MIPITX_PLL_CON4		0x003c
#घोषणा RG_DSI_PLL_IBIAS		(3 << 10)

#घोषणा MIPITX_D2P_RTCODE	0x0100
#घोषणा MIPITX_D2_SW_CTL_EN	0x0144
#घोषणा MIPITX_D0_SW_CTL_EN	0x0244
#घोषणा MIPITX_CK_CKMODE_EN	0x0328
#घोषणा DSI_CK_CKMODE_EN		BIT(0)
#घोषणा MIPITX_CK_SW_CTL_EN	0x0344
#घोषणा MIPITX_D1_SW_CTL_EN	0x0444
#घोषणा MIPITX_D3_SW_CTL_EN	0x0544
#घोषणा DSI_SW_CTL_EN			BIT(0)
#घोषणा AD_DSI_PLL_SDM_PWR_ON		BIT(0)
#घोषणा AD_DSI_PLL_SDM_ISO_EN		BIT(1)

#घोषणा RG_DSI_PLL_EN			BIT(4)
#घोषणा RG_DSI_PLL_POSDIV		(0x7 << 8)

अटल पूर्णांक mtk_mipi_tx_pll_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा mtk_mipi_tx *mipi_tx = mtk_mipi_tx_from_clk_hw(hw);
	अचिन्हित पूर्णांक txभाग, txभाग0;
	u64 pcw;

	dev_dbg(mipi_tx->dev, "enable: %u bps\n", mipi_tx->data_rate);

	अगर (mipi_tx->data_rate >= 2000000000) अणु
		txभाग = 1;
		txभाग0 = 0;
	पूर्ण अन्यथा अगर (mipi_tx->data_rate >= 1000000000) अणु
		txभाग = 2;
		txभाग0 = 1;
	पूर्ण अन्यथा अगर (mipi_tx->data_rate >= 500000000) अणु
		txभाग = 4;
		txभाग0 = 2;
	पूर्ण अन्यथा अगर (mipi_tx->data_rate > 250000000) अणु
		txभाग = 8;
		txभाग0 = 3;
	पूर्ण अन्यथा अगर (mipi_tx->data_rate >= 125000000) अणु
		txभाग = 16;
		txभाग0 = 4;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	mtk_mipi_tx_clear_bits(mipi_tx, MIPITX_PLL_CON4, RG_DSI_PLL_IBIAS);

	mtk_mipi_tx_set_bits(mipi_tx, MIPITX_PLL_PWR, AD_DSI_PLL_SDM_PWR_ON);
	mtk_mipi_tx_clear_bits(mipi_tx, MIPITX_PLL_CON1, RG_DSI_PLL_EN);
	udelay(1);
	mtk_mipi_tx_clear_bits(mipi_tx, MIPITX_PLL_PWR, AD_DSI_PLL_SDM_ISO_EN);
	pcw = भाग_u64(((u64)mipi_tx->data_rate * txभाग) << 24, 26000000);
	ग_लिखोl(pcw, mipi_tx->regs + MIPITX_PLL_CON0);
	mtk_mipi_tx_update_bits(mipi_tx, MIPITX_PLL_CON1, RG_DSI_PLL_POSDIV,
				txभाग0 << 8);
	mtk_mipi_tx_set_bits(mipi_tx, MIPITX_PLL_CON1, RG_DSI_PLL_EN);

	वापस 0;
पूर्ण

अटल व्योम mtk_mipi_tx_pll_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा mtk_mipi_tx *mipi_tx = mtk_mipi_tx_from_clk_hw(hw);

	mtk_mipi_tx_clear_bits(mipi_tx, MIPITX_PLL_CON1, RG_DSI_PLL_EN);

	mtk_mipi_tx_set_bits(mipi_tx, MIPITX_PLL_PWR, AD_DSI_PLL_SDM_ISO_EN);
	mtk_mipi_tx_clear_bits(mipi_tx, MIPITX_PLL_PWR, AD_DSI_PLL_SDM_PWR_ON);
पूर्ण

अटल दीर्घ mtk_mipi_tx_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				       अचिन्हित दीर्घ *prate)
अणु
	वापस clamp_val(rate, 50000000, 1600000000);
पूर्ण

अटल स्थिर काष्ठा clk_ops mtk_mipi_tx_pll_ops = अणु
	.enable = mtk_mipi_tx_pll_enable,
	.disable = mtk_mipi_tx_pll_disable,
	.round_rate = mtk_mipi_tx_pll_round_rate,
	.set_rate = mtk_mipi_tx_pll_set_rate,
	.recalc_rate = mtk_mipi_tx_pll_recalc_rate,
पूर्ण;

अटल व्योम mtk_mipi_tx_config_calibration_data(काष्ठा mtk_mipi_tx *mipi_tx)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < 5; i++) अणु
		अगर ((mipi_tx->rt_code[i] & 0x1f) == 0)
			mipi_tx->rt_code[i] |= 0x10;

		अगर ((mipi_tx->rt_code[i] >> 5 & 0x1f) == 0)
			mipi_tx->rt_code[i] |= 0x10 << 5;

		क्रम (j = 0; j < 10; j++)
			mtk_mipi_tx_update_bits(mipi_tx,
				MIPITX_D2P_RTCODE * (i + 1) + j * 4,
				1, mipi_tx->rt_code[i] >> j & 1);
	पूर्ण
पूर्ण

अटल व्योम mtk_mipi_tx_घातer_on_संकेत(काष्ठा phy *phy)
अणु
	काष्ठा mtk_mipi_tx *mipi_tx = phy_get_drvdata(phy);

	/* BG_LPF_EN / BG_CORE_EN */
	ग_लिखोl(RG_DSI_PAD_TIEL_SEL | RG_DSI_BG_CORE_EN,
	       mipi_tx->regs + MIPITX_LANE_CON);
	usleep_range(30, 100);
	ग_लिखोl(RG_DSI_BG_CORE_EN | RG_DSI_BG_LPF_EN,
	       mipi_tx->regs + MIPITX_LANE_CON);

	/* Switch OFF each Lane */
	mtk_mipi_tx_clear_bits(mipi_tx, MIPITX_D0_SW_CTL_EN, DSI_SW_CTL_EN);
	mtk_mipi_tx_clear_bits(mipi_tx, MIPITX_D1_SW_CTL_EN, DSI_SW_CTL_EN);
	mtk_mipi_tx_clear_bits(mipi_tx, MIPITX_D2_SW_CTL_EN, DSI_SW_CTL_EN);
	mtk_mipi_tx_clear_bits(mipi_tx, MIPITX_D3_SW_CTL_EN, DSI_SW_CTL_EN);
	mtk_mipi_tx_clear_bits(mipi_tx, MIPITX_CK_SW_CTL_EN, DSI_SW_CTL_EN);

	mtk_mipi_tx_update_bits(mipi_tx, MIPITX_VOLTAGE_SEL,
				RG_DSI_HSTX_LDO_REF_SEL,
				(mipi_tx->mipitx_drive - 3000) / 200 << 6);

	mtk_mipi_tx_config_calibration_data(mipi_tx);

	mtk_mipi_tx_set_bits(mipi_tx, MIPITX_CK_CKMODE_EN, DSI_CK_CKMODE_EN);
पूर्ण

अटल व्योम mtk_mipi_tx_घातer_off_संकेत(काष्ठा phy *phy)
अणु
	काष्ठा mtk_mipi_tx *mipi_tx = phy_get_drvdata(phy);

	/* Switch ON each Lane */
	mtk_mipi_tx_set_bits(mipi_tx, MIPITX_D0_SW_CTL_EN, DSI_SW_CTL_EN);
	mtk_mipi_tx_set_bits(mipi_tx, MIPITX_D1_SW_CTL_EN, DSI_SW_CTL_EN);
	mtk_mipi_tx_set_bits(mipi_tx, MIPITX_D2_SW_CTL_EN, DSI_SW_CTL_EN);
	mtk_mipi_tx_set_bits(mipi_tx, MIPITX_D3_SW_CTL_EN, DSI_SW_CTL_EN);
	mtk_mipi_tx_set_bits(mipi_tx, MIPITX_CK_SW_CTL_EN, DSI_SW_CTL_EN);

	ग_लिखोl(RG_DSI_PAD_TIEL_SEL | RG_DSI_BG_CORE_EN,
	       mipi_tx->regs + MIPITX_LANE_CON);
	ग_लिखोl(RG_DSI_PAD_TIEL_SEL, mipi_tx->regs + MIPITX_LANE_CON);
पूर्ण

स्थिर काष्ठा mtk_mipitx_data mt8183_mipitx_data = अणु
	.mipi_tx_clk_ops = &mtk_mipi_tx_pll_ops,
	.mipi_tx_enable_संकेत = mtk_mipi_tx_घातer_on_संकेत,
	.mipi_tx_disable_संकेत = mtk_mipi_tx_घातer_off_संकेत,
पूर्ण;
