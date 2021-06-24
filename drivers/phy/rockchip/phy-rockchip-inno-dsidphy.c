<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018 Rockchip Electronics Co. Ltd.
 *
 * Author: Wyon Bi <bivvy.bi@rock-chips.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/clk.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>
#समावेश <linux/समय64.h>

#समावेश <linux/phy/phy.h>
#समावेश <linux/phy/phy-mipi-dphy.h>

#घोषणा UPDATE(x, h, l)	(((x) << (l)) & GENMASK((h), (l)))

/*
 * The offset address[7:0] is distributed two parts, one from the bit7 to bit5
 * is the first address, the other from the bit4 to bit0 is the second address.
 * when you configure the रेजिस्टरs, you must set both of them. The Clock Lane
 * and Data Lane use the same रेजिस्टरs with the same second address, but the
 * first address is dअगरferent.
 */
#घोषणा FIRST_ADDRESS(x)		(((x) & 0x7) << 5)
#घोषणा SECOND_ADDRESS(x)		(((x) & 0x1f) << 0)
#घोषणा PHY_REG(first, second)		(FIRST_ADDRESS(first) | \
					 SECOND_ADDRESS(second))

/* Analog Register Part: reg00 */
#घोषणा BANDGAP_POWER_MASK			BIT(7)
#घोषणा BANDGAP_POWER_DOWN			BIT(7)
#घोषणा BANDGAP_POWER_ON			0
#घोषणा LANE_EN_MASK				GENMASK(6, 2)
#घोषणा LANE_EN_CK				BIT(6)
#घोषणा LANE_EN_3				BIT(5)
#घोषणा LANE_EN_2				BIT(4)
#घोषणा LANE_EN_1				BIT(3)
#घोषणा LANE_EN_0				BIT(2)
#घोषणा POWER_WORK_MASK				GENMASK(1, 0)
#घोषणा POWER_WORK_ENABLE			UPDATE(1, 1, 0)
#घोषणा POWER_WORK_DISABLE			UPDATE(2, 1, 0)
/* Analog Register Part: reg01 */
#घोषणा REG_SYNCRST_MASK			BIT(2)
#घोषणा REG_SYNCRST_RESET			BIT(2)
#घोषणा REG_SYNCRST_NORMAL			0
#घोषणा REG_LDOPD_MASK				BIT(1)
#घोषणा REG_LDOPD_POWER_DOWN			BIT(1)
#घोषणा REG_LDOPD_POWER_ON			0
#घोषणा REG_PLLPD_MASK				BIT(0)
#घोषणा REG_PLLPD_POWER_DOWN			BIT(0)
#घोषणा REG_PLLPD_POWER_ON			0
/* Analog Register Part: reg03 */
#घोषणा REG_FBDIV_HI_MASK			BIT(5)
#घोषणा REG_FBDIV_HI(x)				UPDATE((x >> 8), 5, 5)
#घोषणा REG_PREDIV_MASK				GENMASK(4, 0)
#घोषणा REG_PREDIV(x)				UPDATE(x, 4, 0)
/* Analog Register Part: reg04 */
#घोषणा REG_FBDIV_LO_MASK			GENMASK(7, 0)
#घोषणा REG_FBDIV_LO(x)				UPDATE(x, 7, 0)
/* Analog Register Part: reg05 */
#घोषणा SAMPLE_CLOCK_PHASE_MASK			GENMASK(6, 4)
#घोषणा SAMPLE_CLOCK_PHASE(x)			UPDATE(x, 6, 4)
#घोषणा CLOCK_LANE_SKEW_PHASE_MASK		GENMASK(2, 0)
#घोषणा CLOCK_LANE_SKEW_PHASE(x)		UPDATE(x, 2, 0)
/* Analog Register Part: reg06 */
#घोषणा DATA_LANE_3_SKEW_PHASE_MASK		GENMASK(6, 4)
#घोषणा DATA_LANE_3_SKEW_PHASE(x)		UPDATE(x, 6, 4)
#घोषणा DATA_LANE_2_SKEW_PHASE_MASK		GENMASK(2, 0)
#घोषणा DATA_LANE_2_SKEW_PHASE(x)		UPDATE(x, 2, 0)
/* Analog Register Part: reg07 */
#घोषणा DATA_LANE_1_SKEW_PHASE_MASK		GENMASK(6, 4)
#घोषणा DATA_LANE_1_SKEW_PHASE(x)		UPDATE(x, 6, 4)
#घोषणा DATA_LANE_0_SKEW_PHASE_MASK		GENMASK(2, 0)
#घोषणा DATA_LANE_0_SKEW_PHASE(x)		UPDATE(x, 2, 0)
/* Analog Register Part: reg08 */
#घोषणा SAMPLE_CLOCK_सूचीECTION_MASK		BIT(4)
#घोषणा SAMPLE_CLOCK_सूचीECTION_REVERSE		BIT(4)
#घोषणा SAMPLE_CLOCK_सूचीECTION_FORWARD		0
/* Digital Register Part: reg00 */
#घोषणा REG_DIG_RSTN_MASK			BIT(0)
#घोषणा REG_DIG_RSTN_NORMAL			BIT(0)
#घोषणा REG_DIG_RSTN_RESET			0
/* Digital Register Part: reg01 */
#घोषणा INVERT_TXCLKESC_MASK			BIT(1)
#घोषणा INVERT_TXCLKESC_ENABLE			BIT(1)
#घोषणा INVERT_TXCLKESC_DISABLE			0
#घोषणा INVERT_TXBYTECLKHS_MASK			BIT(0)
#घोषणा INVERT_TXBYTECLKHS_ENABLE		BIT(0)
#घोषणा INVERT_TXBYTECLKHS_DISABLE		0
/* Clock/Data0/Data1/Data2/Data3 Lane Register Part: reg05 */
#घोषणा T_LPX_CNT_MASK				GENMASK(5, 0)
#घोषणा T_LPX_CNT(x)				UPDATE(x, 5, 0)
/* Clock/Data0/Data1/Data2/Data3 Lane Register Part: reg06 */
#घोषणा T_HS_PREPARE_CNT_MASK			GENMASK(6, 0)
#घोषणा T_HS_PREPARE_CNT(x)			UPDATE(x, 6, 0)
/* Clock/Data0/Data1/Data2/Data3 Lane Register Part: reg07 */
#घोषणा T_HS_ZERO_CNT_MASK			GENMASK(5, 0)
#घोषणा T_HS_ZERO_CNT(x)			UPDATE(x, 5, 0)
/* Clock/Data0/Data1/Data2/Data3 Lane Register Part: reg08 */
#घोषणा T_HS_TRAIL_CNT_MASK			GENMASK(6, 0)
#घोषणा T_HS_TRAIL_CNT(x)			UPDATE(x, 6, 0)
/* Clock/Data0/Data1/Data2/Data3 Lane Register Part: reg09 */
#घोषणा T_HS_EXIT_CNT_MASK			GENMASK(4, 0)
#घोषणा T_HS_EXIT_CNT(x)			UPDATE(x, 4, 0)
/* Clock/Data0/Data1/Data2/Data3 Lane Register Part: reg0a */
#घोषणा T_CLK_POST_CNT_MASK			GENMASK(3, 0)
#घोषणा T_CLK_POST_CNT(x)			UPDATE(x, 3, 0)
/* Clock/Data0/Data1/Data2/Data3 Lane Register Part: reg0c */
#घोषणा LPDT_TX_PPI_SYNC_MASK			BIT(2)
#घोषणा LPDT_TX_PPI_SYNC_ENABLE			BIT(2)
#घोषणा LPDT_TX_PPI_SYNC_DISABLE		0
#घोषणा T_WAKEUP_CNT_HI_MASK			GENMASK(1, 0)
#घोषणा T_WAKEUP_CNT_HI(x)			UPDATE(x, 1, 0)
/* Clock/Data0/Data1/Data2/Data3 Lane Register Part: reg0d */
#घोषणा T_WAKEUP_CNT_LO_MASK			GENMASK(7, 0)
#घोषणा T_WAKEUP_CNT_LO(x)			UPDATE(x, 7, 0)
/* Clock/Data0/Data1/Data2/Data3 Lane Register Part: reg0e */
#घोषणा T_CLK_PRE_CNT_MASK			GENMASK(3, 0)
#घोषणा T_CLK_PRE_CNT(x)			UPDATE(x, 3, 0)
/* Clock/Data0/Data1/Data2/Data3 Lane Register Part: reg10 */
#घोषणा T_TA_GO_CNT_MASK			GENMASK(5, 0)
#घोषणा T_TA_GO_CNT(x)				UPDATE(x, 5, 0)
/* Clock/Data0/Data1/Data2/Data3 Lane Register Part: reg11 */
#घोषणा T_TA_SURE_CNT_MASK			GENMASK(5, 0)
#घोषणा T_TA_SURE_CNT(x)			UPDATE(x, 5, 0)
/* Clock/Data0/Data1/Data2/Data3 Lane Register Part: reg12 */
#घोषणा T_TA_WAIT_CNT_MASK			GENMASK(5, 0)
#घोषणा T_TA_WAIT_CNT(x)			UPDATE(x, 5, 0)
/* LVDS Register Part: reg00 */
#घोषणा LVDS_DIGITAL_INTERNAL_RESET_MASK	BIT(2)
#घोषणा LVDS_DIGITAL_INTERNAL_RESET_DISABLE	BIT(2)
#घोषणा LVDS_DIGITAL_INTERNAL_RESET_ENABLE	0
/* LVDS Register Part: reg01 */
#घोषणा LVDS_DIGITAL_INTERNAL_ENABLE_MASK	BIT(7)
#घोषणा LVDS_DIGITAL_INTERNAL_ENABLE		BIT(7)
#घोषणा LVDS_DIGITAL_INTERNAL_DISABLE		0
/* LVDS Register Part: reg03 */
#घोषणा MODE_ENABLE_MASK			GENMASK(2, 0)
#घोषणा TTL_MODE_ENABLE				BIT(2)
#घोषणा LVDS_MODE_ENABLE			BIT(1)
#घोषणा MIPI_MODE_ENABLE			BIT(0)
/* LVDS Register Part: reg0b */
#घोषणा LVDS_LANE_EN_MASK			GENMASK(7, 3)
#घोषणा LVDS_DATA_LANE0_EN			BIT(7)
#घोषणा LVDS_DATA_LANE1_EN			BIT(6)
#घोषणा LVDS_DATA_LANE2_EN			BIT(5)
#घोषणा LVDS_DATA_LANE3_EN			BIT(4)
#घोषणा LVDS_CLK_LANE_EN			BIT(3)
#घोषणा LVDS_PLL_POWER_MASK			BIT(2)
#घोषणा LVDS_PLL_POWER_OFF			BIT(2)
#घोषणा LVDS_PLL_POWER_ON			0
#घोषणा LVDS_BANDGAP_POWER_MASK			BIT(0)
#घोषणा LVDS_BANDGAP_POWER_DOWN			BIT(0)
#घोषणा LVDS_BANDGAP_POWER_ON			0

#घोषणा DSI_PHY_RSTZ		0xa0
#घोषणा PHY_ENABLECLK		BIT(2)
#घोषणा DSI_PHY_STATUS		0xb0
#घोषणा PHY_LOCK		BIT(0)

काष्ठा inno_dsidphy अणु
	काष्ठा device *dev;
	काष्ठा clk *ref_clk;
	काष्ठा clk *pclk_phy;
	काष्ठा clk *pclk_host;
	व्योम __iomem *phy_base;
	व्योम __iomem *host_base;
	काष्ठा reset_control *rst;
	क्रमागत phy_mode mode;
	काष्ठा phy_configure_opts_mipi_dphy dphy_cfg;

	काष्ठा clk *pll_clk;
	काष्ठा अणु
		काष्ठा clk_hw hw;
		u8 preभाग;
		u16 fbभाग;
		अचिन्हित दीर्घ rate;
	पूर्ण pll;
पूर्ण;

क्रमागत अणु
	REGISTER_PART_ANALOG,
	REGISTER_PART_DIGITAL,
	REGISTER_PART_CLOCK_LANE,
	REGISTER_PART_DATA0_LANE,
	REGISTER_PART_DATA1_LANE,
	REGISTER_PART_DATA2_LANE,
	REGISTER_PART_DATA3_LANE,
	REGISTER_PART_LVDS,
पूर्ण;

अटल अंतरभूत काष्ठा inno_dsidphy *hw_to_inno(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा inno_dsidphy, pll.hw);
पूर्ण

अटल व्योम phy_update_bits(काष्ठा inno_dsidphy *inno,
			    u8 first, u8 second, u8 mask, u8 val)
अणु
	u32 reg = PHY_REG(first, second) << 2;
	अचिन्हित पूर्णांक पंचांगp, orig;

	orig = पढ़ोl(inno->phy_base + reg);
	पंचांगp = orig & ~mask;
	पंचांगp |= val & mask;
	ग_लिखोl(पंचांगp, inno->phy_base + reg);
पूर्ण

अटल अचिन्हित दीर्घ inno_dsidphy_pll_calc_rate(काष्ठा inno_dsidphy *inno,
						अचिन्हित दीर्घ rate)
अणु
	अचिन्हित दीर्घ prate = clk_get_rate(inno->ref_clk);
	अचिन्हित दीर्घ best_freq = 0;
	अचिन्हित दीर्घ fref, fout;
	u8 min_preभाग, max_preभाग;
	u8 _preभाग, best_preभाग = 1;
	u16 _fbभाग, best_fbभाग = 1;
	u32 min_delta = अच_पूर्णांक_उच्च;

	/*
	 * The PLL output frequency can be calculated using a simple क्रमmula:
	 * PLL_Output_Frequency = (FREF / PREDIV * FBDIV) / 2
	 * PLL_Output_Frequency: it is equal to DDR-Clock-Frequency * 2
	 */
	fref = prate / 2;
	अगर (rate > 1000000000UL)
		fout = 1000000000UL;
	अन्यथा
		fout = rate;

	/* 5Mhz < Fref / preभाग < 40MHz */
	min_preभाग = DIV_ROUND_UP(fref, 40000000);
	max_preभाग = fref / 5000000;

	क्रम (_preभाग = min_preभाग; _preभाग <= max_preभाग; _preभाग++) अणु
		u64 पंचांगp;
		u32 delta;

		पंचांगp = (u64)fout * _preभाग;
		करो_भाग(पंचांगp, fref);
		_fbभाग = पंचांगp;

		/*
		 * The possible settings of feedback भागider are
		 * 12, 13, 14, 16, ~ 511
		 */
		अगर (_fbभाग == 15)
			जारी;

		अगर (_fbभाग < 12 || _fbभाग > 511)
			जारी;

		पंचांगp = (u64)_fbभाग * fref;
		करो_भाग(पंचांगp, _preभाग);

		delta = असल(fout - पंचांगp);
		अगर (!delta) अणु
			best_preभाग = _preभाग;
			best_fbभाग = _fbभाग;
			best_freq = पंचांगp;
			अवरोध;
		पूर्ण अन्यथा अगर (delta < min_delta) अणु
			best_preभाग = _preभाग;
			best_fbभाग = _fbभाग;
			best_freq = पंचांगp;
			min_delta = delta;
		पूर्ण
	पूर्ण

	अगर (best_freq) अणु
		inno->pll.preभाग = best_preभाग;
		inno->pll.fbभाग = best_fbभाग;
		inno->pll.rate = best_freq;
	पूर्ण

	वापस best_freq;
पूर्ण

अटल व्योम inno_dsidphy_mipi_mode_enable(काष्ठा inno_dsidphy *inno)
अणु
	काष्ठा phy_configure_opts_mipi_dphy *cfg = &inno->dphy_cfg;
	स्थिर काष्ठा अणु
		अचिन्हित दीर्घ rate;
		u8 hs_prepare;
		u8 clk_lane_hs_zero;
		u8 data_lane_hs_zero;
		u8 hs_trail;
	पूर्ण timings[] = अणु
		अणु 110000000, 0x20, 0x16, 0x02, 0x22पूर्ण,
		अणु 150000000, 0x06, 0x16, 0x03, 0x45पूर्ण,
		अणु 200000000, 0x18, 0x17, 0x04, 0x0bपूर्ण,
		अणु 250000000, 0x05, 0x17, 0x05, 0x16पूर्ण,
		अणु 300000000, 0x51, 0x18, 0x06, 0x2cपूर्ण,
		अणु 400000000, 0x64, 0x19, 0x07, 0x33पूर्ण,
		अणु 500000000, 0x20, 0x1b, 0x07, 0x4eपूर्ण,
		अणु 600000000, 0x6a, 0x1d, 0x08, 0x3aपूर्ण,
		अणु 700000000, 0x3e, 0x1e, 0x08, 0x6aपूर्ण,
		अणु 800000000, 0x21, 0x1f, 0x09, 0x29पूर्ण,
		अणु1000000000, 0x09, 0x20, 0x09, 0x27पूर्ण,
	पूर्ण;
	u32 t_txbyteclkhs, t_txclkesc;
	u32 txbyteclkhs, txclkesc, esc_clk_भाग;
	u32 hs_निकास, clk_post, clk_pre, wakeup, lpx, ta_go, ta_sure, ta_रुको;
	u32 hs_prepare, hs_trail, hs_zero, clk_lane_hs_zero, data_lane_hs_zero;
	अचिन्हित पूर्णांक i;

	inno_dsidphy_pll_calc_rate(inno, cfg->hs_clk_rate);

	/* Select MIPI mode */
	phy_update_bits(inno, REGISTER_PART_LVDS, 0x03,
			MODE_ENABLE_MASK, MIPI_MODE_ENABLE);
	/* Configure PLL */
	phy_update_bits(inno, REGISTER_PART_ANALOG, 0x03,
			REG_PREDIV_MASK, REG_PREDIV(inno->pll.preभाग));
	phy_update_bits(inno, REGISTER_PART_ANALOG, 0x03,
			REG_FBDIV_HI_MASK, REG_FBDIV_HI(inno->pll.fbभाग));
	phy_update_bits(inno, REGISTER_PART_ANALOG, 0x04,
			REG_FBDIV_LO_MASK, REG_FBDIV_LO(inno->pll.fbभाग));
	/* Enable PLL and LDO */
	phy_update_bits(inno, REGISTER_PART_ANALOG, 0x01,
			REG_LDOPD_MASK | REG_PLLPD_MASK,
			REG_LDOPD_POWER_ON | REG_PLLPD_POWER_ON);
	/* Reset analog */
	phy_update_bits(inno, REGISTER_PART_ANALOG, 0x01,
			REG_SYNCRST_MASK, REG_SYNCRST_RESET);
	udelay(1);
	phy_update_bits(inno, REGISTER_PART_ANALOG, 0x01,
			REG_SYNCRST_MASK, REG_SYNCRST_NORMAL);
	/* Reset digital */
	phy_update_bits(inno, REGISTER_PART_DIGITAL, 0x00,
			REG_DIG_RSTN_MASK, REG_DIG_RSTN_RESET);
	udelay(1);
	phy_update_bits(inno, REGISTER_PART_DIGITAL, 0x00,
			REG_DIG_RSTN_MASK, REG_DIG_RSTN_NORMAL);

	txbyteclkhs = inno->pll.rate / 8;
	t_txbyteclkhs = भाग_u64(PSEC_PER_SEC, txbyteclkhs);

	esc_clk_भाग = DIV_ROUND_UP(txbyteclkhs, 20000000);
	txclkesc = txbyteclkhs / esc_clk_भाग;
	t_txclkesc = भाग_u64(PSEC_PER_SEC, txclkesc);

	/*
	 * The value of counter क्रम HS Ths-निकास
	 * Ths-निकास = Tpin_txbyteclkhs * value
	 */
	hs_निकास = DIV_ROUND_UP(cfg->hs_निकास, t_txbyteclkhs);
	/*
	 * The value of counter क्रम HS Tclk-post
	 * Tclk-post = Tpin_txbyteclkhs * value
	 */
	clk_post = DIV_ROUND_UP(cfg->clk_post, t_txbyteclkhs);
	/*
	 * The value of counter क्रम HS Tclk-pre
	 * Tclk-pre = Tpin_txbyteclkhs * value
	 */
	clk_pre = DIV_ROUND_UP(cfg->clk_pre, t_txbyteclkhs);

	/*
	 * The value of counter क्रम HS Tlpx Time
	 * Tlpx = Tpin_txbyteclkhs * (2 + value)
	 */
	lpx = DIV_ROUND_UP(cfg->lpx, t_txbyteclkhs);
	अगर (lpx >= 2)
		lpx -= 2;

	/*
	 * The value of counter क्रम HS Tta-go
	 * Tta-go क्रम turnaround
	 * Tta-go = Ttxclkesc * value
	 */
	ta_go = DIV_ROUND_UP(cfg->ta_go, t_txclkesc);
	/*
	 * The value of counter क्रम HS Tta-sure
	 * Tta-sure क्रम turnaround
	 * Tta-sure = Ttxclkesc * value
	 */
	ta_sure = DIV_ROUND_UP(cfg->ta_sure, t_txclkesc);
	/*
	 * The value of counter क्रम HS Tta-रुको
	 * Tta-रुको क्रम turnaround
	 * Tta-रुको = Ttxclkesc * value
	 */
	ta_रुको = DIV_ROUND_UP(cfg->ta_get, t_txclkesc);

	क्रम (i = 0; i < ARRAY_SIZE(timings); i++)
		अगर (inno->pll.rate <= timings[i].rate)
			अवरोध;

	अगर (i == ARRAY_SIZE(timings))
		--i;

	hs_prepare = timings[i].hs_prepare;
	hs_trail = timings[i].hs_trail;
	clk_lane_hs_zero = timings[i].clk_lane_hs_zero;
	data_lane_hs_zero = timings[i].data_lane_hs_zero;
	wakeup = 0x3ff;

	क्रम (i = REGISTER_PART_CLOCK_LANE; i <= REGISTER_PART_DATA3_LANE; i++) अणु
		अगर (i == REGISTER_PART_CLOCK_LANE)
			hs_zero = clk_lane_hs_zero;
		अन्यथा
			hs_zero = data_lane_hs_zero;

		phy_update_bits(inno, i, 0x05, T_LPX_CNT_MASK,
				T_LPX_CNT(lpx));
		phy_update_bits(inno, i, 0x06, T_HS_PREPARE_CNT_MASK,
				T_HS_PREPARE_CNT(hs_prepare));
		phy_update_bits(inno, i, 0x07, T_HS_ZERO_CNT_MASK,
				T_HS_ZERO_CNT(hs_zero));
		phy_update_bits(inno, i, 0x08, T_HS_TRAIL_CNT_MASK,
				T_HS_TRAIL_CNT(hs_trail));
		phy_update_bits(inno, i, 0x09, T_HS_EXIT_CNT_MASK,
				T_HS_EXIT_CNT(hs_निकास));
		phy_update_bits(inno, i, 0x0a, T_CLK_POST_CNT_MASK,
				T_CLK_POST_CNT(clk_post));
		phy_update_bits(inno, i, 0x0e, T_CLK_PRE_CNT_MASK,
				T_CLK_PRE_CNT(clk_pre));
		phy_update_bits(inno, i, 0x0c, T_WAKEUP_CNT_HI_MASK,
				T_WAKEUP_CNT_HI(wakeup >> 8));
		phy_update_bits(inno, i, 0x0d, T_WAKEUP_CNT_LO_MASK,
				T_WAKEUP_CNT_LO(wakeup));
		phy_update_bits(inno, i, 0x10, T_TA_GO_CNT_MASK,
				T_TA_GO_CNT(ta_go));
		phy_update_bits(inno, i, 0x11, T_TA_SURE_CNT_MASK,
				T_TA_SURE_CNT(ta_sure));
		phy_update_bits(inno, i, 0x12, T_TA_WAIT_CNT_MASK,
				T_TA_WAIT_CNT(ta_रुको));
	पूर्ण

	/* Enable all lanes on analog part */
	phy_update_bits(inno, REGISTER_PART_ANALOG, 0x00,
			LANE_EN_MASK, LANE_EN_CK | LANE_EN_3 | LANE_EN_2 |
			LANE_EN_1 | LANE_EN_0);
पूर्ण

अटल व्योम inno_dsidphy_lvds_mode_enable(काष्ठा inno_dsidphy *inno)
अणु
	u8 preभाग = 2;
	u16 fbभाग = 28;

	/* Sample घड़ी reverse direction */
	phy_update_bits(inno, REGISTER_PART_ANALOG, 0x08,
			SAMPLE_CLOCK_सूचीECTION_MASK,
			SAMPLE_CLOCK_सूचीECTION_REVERSE);

	/* Select LVDS mode */
	phy_update_bits(inno, REGISTER_PART_LVDS, 0x03,
			MODE_ENABLE_MASK, LVDS_MODE_ENABLE);
	/* Configure PLL */
	phy_update_bits(inno, REGISTER_PART_ANALOG, 0x03,
			REG_PREDIV_MASK, REG_PREDIV(preभाग));
	phy_update_bits(inno, REGISTER_PART_ANALOG, 0x03,
			REG_FBDIV_HI_MASK, REG_FBDIV_HI(fbभाग));
	phy_update_bits(inno, REGISTER_PART_ANALOG, 0x04,
			REG_FBDIV_LO_MASK, REG_FBDIV_LO(fbभाग));
	phy_update_bits(inno, REGISTER_PART_LVDS, 0x08, 0xff, 0xfc);
	/* Enable PLL and Bandgap */
	phy_update_bits(inno, REGISTER_PART_LVDS, 0x0b,
			LVDS_PLL_POWER_MASK | LVDS_BANDGAP_POWER_MASK,
			LVDS_PLL_POWER_ON | LVDS_BANDGAP_POWER_ON);

	msleep(20);

	/* Reset LVDS digital logic */
	phy_update_bits(inno, REGISTER_PART_LVDS, 0x00,
			LVDS_DIGITAL_INTERNAL_RESET_MASK,
			LVDS_DIGITAL_INTERNAL_RESET_ENABLE);
	udelay(1);
	phy_update_bits(inno, REGISTER_PART_LVDS, 0x00,
			LVDS_DIGITAL_INTERNAL_RESET_MASK,
			LVDS_DIGITAL_INTERNAL_RESET_DISABLE);
	/* Enable LVDS digital logic */
	phy_update_bits(inno, REGISTER_PART_LVDS, 0x01,
			LVDS_DIGITAL_INTERNAL_ENABLE_MASK,
			LVDS_DIGITAL_INTERNAL_ENABLE);
	/* Enable LVDS analog driver */
	phy_update_bits(inno, REGISTER_PART_LVDS, 0x0b,
			LVDS_LANE_EN_MASK, LVDS_CLK_LANE_EN |
			LVDS_DATA_LANE0_EN | LVDS_DATA_LANE1_EN |
			LVDS_DATA_LANE2_EN | LVDS_DATA_LANE3_EN);
पूर्ण

अटल पूर्णांक inno_dsidphy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा inno_dsidphy *inno = phy_get_drvdata(phy);

	clk_prepare_enable(inno->pclk_phy);
	clk_prepare_enable(inno->ref_clk);
	pm_runसमय_get_sync(inno->dev);

	/* Bandgap घातer on */
	phy_update_bits(inno, REGISTER_PART_ANALOG, 0x00,
			BANDGAP_POWER_MASK, BANDGAP_POWER_ON);
	/* Enable घातer work */
	phy_update_bits(inno, REGISTER_PART_ANALOG, 0x00,
			POWER_WORK_MASK, POWER_WORK_ENABLE);

	चयन (inno->mode) अणु
	हाल PHY_MODE_MIPI_DPHY:
		inno_dsidphy_mipi_mode_enable(inno);
		अवरोध;
	हाल PHY_MODE_LVDS:
		inno_dsidphy_lvds_mode_enable(inno);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक inno_dsidphy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा inno_dsidphy *inno = phy_get_drvdata(phy);

	phy_update_bits(inno, REGISTER_PART_ANALOG, 0x00, LANE_EN_MASK, 0);
	phy_update_bits(inno, REGISTER_PART_ANALOG, 0x01,
			REG_LDOPD_MASK | REG_PLLPD_MASK,
			REG_LDOPD_POWER_DOWN | REG_PLLPD_POWER_DOWN);
	phy_update_bits(inno, REGISTER_PART_ANALOG, 0x00,
			POWER_WORK_MASK, POWER_WORK_DISABLE);
	phy_update_bits(inno, REGISTER_PART_ANALOG, 0x00,
			BANDGAP_POWER_MASK, BANDGAP_POWER_DOWN);

	phy_update_bits(inno, REGISTER_PART_LVDS, 0x0b, LVDS_LANE_EN_MASK, 0);
	phy_update_bits(inno, REGISTER_PART_LVDS, 0x01,
			LVDS_DIGITAL_INTERNAL_ENABLE_MASK,
			LVDS_DIGITAL_INTERNAL_DISABLE);
	phy_update_bits(inno, REGISTER_PART_LVDS, 0x0b,
			LVDS_PLL_POWER_MASK | LVDS_BANDGAP_POWER_MASK,
			LVDS_PLL_POWER_OFF | LVDS_BANDGAP_POWER_DOWN);

	pm_runसमय_put(inno->dev);
	clk_disable_unprepare(inno->ref_clk);
	clk_disable_unprepare(inno->pclk_phy);

	वापस 0;
पूर्ण

अटल पूर्णांक inno_dsidphy_set_mode(काष्ठा phy *phy, क्रमागत phy_mode mode,
				   पूर्णांक submode)
अणु
	काष्ठा inno_dsidphy *inno = phy_get_drvdata(phy);

	चयन (mode) अणु
	हाल PHY_MODE_MIPI_DPHY:
	हाल PHY_MODE_LVDS:
		inno->mode = mode;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक inno_dsidphy_configure(काष्ठा phy *phy,
				  जोड़ phy_configure_opts *opts)
अणु
	काष्ठा inno_dsidphy *inno = phy_get_drvdata(phy);
	पूर्णांक ret;

	अगर (inno->mode != PHY_MODE_MIPI_DPHY)
		वापस -EINVAL;

	ret = phy_mipi_dphy_config_validate(&opts->mipi_dphy);
	अगर (ret)
		वापस ret;

	स_नकल(&inno->dphy_cfg, &opts->mipi_dphy, माप(inno->dphy_cfg));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops inno_dsidphy_ops = अणु
	.configure = inno_dsidphy_configure,
	.set_mode = inno_dsidphy_set_mode,
	.घातer_on = inno_dsidphy_घातer_on,
	.घातer_off = inno_dsidphy_घातer_off,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक inno_dsidphy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा inno_dsidphy *inno;
	काष्ठा phy_provider *phy_provider;
	काष्ठा phy *phy;
	पूर्णांक ret;

	inno = devm_kzalloc(dev, माप(*inno), GFP_KERNEL);
	अगर (!inno)
		वापस -ENOMEM;

	inno->dev = dev;
	platक्रमm_set_drvdata(pdev, inno);

	inno->phy_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(inno->phy_base))
		वापस PTR_ERR(inno->phy_base);

	inno->ref_clk = devm_clk_get(dev, "ref");
	अगर (IS_ERR(inno->ref_clk)) अणु
		ret = PTR_ERR(inno->ref_clk);
		dev_err(dev, "failed to get ref clock: %d\n", ret);
		वापस ret;
	पूर्ण

	inno->pclk_phy = devm_clk_get(dev, "pclk");
	अगर (IS_ERR(inno->pclk_phy)) अणु
		ret = PTR_ERR(inno->pclk_phy);
		dev_err(dev, "failed to get phy pclk: %d\n", ret);
		वापस ret;
	पूर्ण

	inno->rst = devm_reset_control_get(dev, "apb");
	अगर (IS_ERR(inno->rst)) अणु
		ret = PTR_ERR(inno->rst);
		dev_err(dev, "failed to get system reset control: %d\n", ret);
		वापस ret;
	पूर्ण

	phy = devm_phy_create(dev, शून्य, &inno_dsidphy_ops);
	अगर (IS_ERR(phy)) अणु
		ret = PTR_ERR(phy);
		dev_err(dev, "failed to create phy: %d\n", ret);
		वापस ret;
	पूर्ण

	phy_set_drvdata(phy, inno);

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	अगर (IS_ERR(phy_provider)) अणु
		ret = PTR_ERR(phy_provider);
		dev_err(dev, "failed to register phy provider: %d\n", ret);
		वापस ret;
	पूर्ण

	pm_runसमय_enable(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक inno_dsidphy_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा inno_dsidphy *inno = platक्रमm_get_drvdata(pdev);

	pm_runसमय_disable(inno->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id inno_dsidphy_of_match[] = अणु
	अणु .compatible = "rockchip,px30-dsi-dphy", पूर्ण,
	अणु .compatible = "rockchip,rk3128-dsi-dphy", पूर्ण,
	अणु .compatible = "rockchip,rk3368-dsi-dphy", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, inno_dsidphy_of_match);

अटल काष्ठा platक्रमm_driver inno_dsidphy_driver = अणु
	.driver = अणु
		.name = "inno-dsidphy",
		.of_match_table	= of_match_ptr(inno_dsidphy_of_match),
	पूर्ण,
	.probe = inno_dsidphy_probe,
	.हटाओ = inno_dsidphy_हटाओ,
पूर्ण;
module_platक्रमm_driver(inno_dsidphy_driver);

MODULE_AUTHOR("Wyon Bi <bivvy.bi@rock-chips.com>");
MODULE_DESCRIPTION("Innosilicon MIPI/LVDS/TTL Video Combo PHY driver");
MODULE_LICENSE("GPL v2");
