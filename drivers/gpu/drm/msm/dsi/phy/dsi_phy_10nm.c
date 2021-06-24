<शैली गुरु>
/*
 * SPDX-License-Identअगरier: GPL-2.0
 * Copyright (c) 2018, The Linux Foundation
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/iopoll.h>

#समावेश "dsi_phy.h"
#समावेश "dsi.xml.h"

/*
 * DSI PLL 10nm - घड़ी diagram (eg: DSI0):
 *
 *           dsi0_pll_out_भाग_clk  dsi0_pll_bit_clk
 *                              |                |
 *                              |                |
 *                 +---------+  |  +----------+  |  +----+
 *  dsi0vco_clk ---| out_भाग |--o--| भागl_3_0 |--o--| /8 |-- dsi0_phy_pll_out_byteclk
 *                 +---------+  |  +----------+  |  +----+
 *                              |                |
 *                              |                |         dsi0_pll_by_2_bit_clk
 *                              |                |          |
 *                              |                |  +----+  |  |\  dsi0_pclk_mux
 *                              |                |--| /2 |--o--| \   |
 *                              |                |  +----+     |  \  |  +---------+
 *                              |                --------------|  |--o--| भाग_7_4 |-- dsi0_phy_pll_out_dsiclk
 *                              |------------------------------|  /     +---------+
 *                              |          +-----+             | /
 *                              -----------| /4? |--o----------|/
 *                                         +-----+  |           |
 *                                                  |           |dsiclk_sel
 *                                                  |
 *                                                  dsi0_pll_post_out_भाग_clk
 */

#घोषणा VCO_REF_CLK_RATE		19200000
#घोषणा FRAC_BITS 18

/* v3.0.0 10nm implementation that requires the old timings settings */
#घोषणा DSI_PHY_10NM_QUIRK_OLD_TIMINGS	BIT(0)

काष्ठा dsi_pll_config अणु
	bool enable_ssc;
	bool ssc_center;
	u32 ssc_freq;
	u32 ssc_offset;
	u32 ssc_adj_per;

	/* out */
	u32 pll_prop_gain_rate;
	u32 decimal_भाग_start;
	u32 frac_भाग_start;
	u32 pll_घड़ी_inverters;
	u32 ssc_stepsize;
	u32 ssc_भाग_per;
पूर्ण;

काष्ठा pll_10nm_cached_state अणु
	अचिन्हित दीर्घ vco_rate;
	u8 bit_clk_भाग;
	u8 pix_clk_भाग;
	u8 pll_out_भाग;
	u8 pll_mux;
पूर्ण;

काष्ठा dsi_pll_10nm अणु
	काष्ठा clk_hw clk_hw;

	काष्ठा msm_dsi_phy *phy;

	u64 vco_current_rate;

	/* protects REG_DSI_10nm_PHY_CMN_CLK_CFG0 रेजिस्टर */
	spinlock_t postभाग_lock;

	काष्ठा pll_10nm_cached_state cached_state;

	काष्ठा dsi_pll_10nm *slave;
पूर्ण;

#घोषणा to_pll_10nm(x)	container_of(x, काष्ठा dsi_pll_10nm, clk_hw)

/*
 * Global list of निजी DSI PLL काष्ठा poपूर्णांकers. We need this क्रम Dual DSI
 * mode, where the master PLL's clk_ops needs access the slave's निजी data
 */
अटल काष्ठा dsi_pll_10nm *pll_10nm_list[DSI_MAX];

अटल व्योम dsi_pll_setup_config(काष्ठा dsi_pll_config *config)
अणु
	config->ssc_freq = 31500;
	config->ssc_offset = 5000;
	config->ssc_adj_per = 2;

	config->enable_ssc = false;
	config->ssc_center = false;
पूर्ण

अटल व्योम dsi_pll_calc_dec_frac(काष्ठा dsi_pll_10nm *pll, काष्ठा dsi_pll_config *config)
अणु
	u64 fref = VCO_REF_CLK_RATE;
	u64 pll_freq;
	u64 भागider;
	u64 dec, dec_multiple;
	u32 frac;
	u64 multiplier;

	pll_freq = pll->vco_current_rate;

	भागider = fref * 2;

	multiplier = 1 << FRAC_BITS;
	dec_multiple = भाग_u64(pll_freq * multiplier, भागider);
	dec = भाग_u64_rem(dec_multiple, multiplier, &frac);

	अगर (pll_freq <= 1900000000UL)
		config->pll_prop_gain_rate = 8;
	अन्यथा अगर (pll_freq <= 3000000000UL)
		config->pll_prop_gain_rate = 10;
	अन्यथा
		config->pll_prop_gain_rate = 12;
	अगर (pll_freq < 1100000000UL)
		config->pll_घड़ी_inverters = 8;
	अन्यथा
		config->pll_घड़ी_inverters = 0;

	config->decimal_भाग_start = dec;
	config->frac_भाग_start = frac;
पूर्ण

#घोषणा SSC_CENTER		BIT(0)
#घोषणा SSC_EN			BIT(1)

अटल व्योम dsi_pll_calc_ssc(काष्ठा dsi_pll_10nm *pll, काष्ठा dsi_pll_config *config)
अणु
	u32 ssc_per;
	u32 ssc_mod;
	u64 ssc_step_size;
	u64 frac;

	अगर (!config->enable_ssc) अणु
		DBG("SSC not enabled\n");
		वापस;
	पूर्ण

	ssc_per = DIV_ROUND_CLOSEST(VCO_REF_CLK_RATE, config->ssc_freq) / 2 - 1;
	ssc_mod = (ssc_per + 1) % (config->ssc_adj_per + 1);
	ssc_per -= ssc_mod;

	frac = config->frac_भाग_start;
	ssc_step_size = config->decimal_भाग_start;
	ssc_step_size *= (1 << FRAC_BITS);
	ssc_step_size += frac;
	ssc_step_size *= config->ssc_offset;
	ssc_step_size *= (config->ssc_adj_per + 1);
	ssc_step_size = भाग_u64(ssc_step_size, (ssc_per + 1));
	ssc_step_size = DIV_ROUND_CLOSEST_ULL(ssc_step_size, 1000000);

	config->ssc_भाग_per = ssc_per;
	config->ssc_stepsize = ssc_step_size;

	pr_debug("SCC: Dec:%d, frac:%llu, frac_bits:%d\n",
		 config->decimal_भाग_start, frac, FRAC_BITS);
	pr_debug("SSC: div_per:0x%X, stepsize:0x%X, adjper:0x%X\n",
		 ssc_per, (u32)ssc_step_size, config->ssc_adj_per);
पूर्ण

अटल व्योम dsi_pll_ssc_commit(काष्ठा dsi_pll_10nm *pll, काष्ठा dsi_pll_config *config)
अणु
	व्योम __iomem *base = pll->phy->pll_base;

	अगर (config->enable_ssc) अणु
		pr_debug("SSC is enabled\n");

		dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_SSC_STEPSIZE_LOW_1,
			  config->ssc_stepsize & 0xff);
		dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_SSC_STEPSIZE_HIGH_1,
			  config->ssc_stepsize >> 8);
		dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_SSC_DIV_PER_LOW_1,
			  config->ssc_भाग_per & 0xff);
		dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_SSC_DIV_PER_HIGH_1,
			  config->ssc_भाग_per >> 8);
		dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_SSC_DIV_ADJPER_LOW_1,
			  config->ssc_adj_per & 0xff);
		dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_SSC_DIV_ADJPER_HIGH_1,
			  config->ssc_adj_per >> 8);
		dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_SSC_CONTROL,
			  SSC_EN | (config->ssc_center ? SSC_CENTER : 0));
	पूर्ण
पूर्ण

अटल व्योम dsi_pll_config_hzindep_reg(काष्ठा dsi_pll_10nm *pll)
अणु
	व्योम __iomem *base = pll->phy->pll_base;

	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_ANALOG_CONTROLS_ONE, 0x80);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_ANALOG_CONTROLS_TWO, 0x03);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_ANALOG_CONTROLS_THREE, 0x00);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_DSM_DIVIDER, 0x00);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_FEEDBACK_DIVIDER, 0x4e);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_CALIBRATION_SETTINGS, 0x40);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_BAND_SEL_CAL_SETTINGS_THREE,
		  0xba);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_FREQ_DETECT_SETTINGS_ONE, 0x0c);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_OUTDIV, 0x00);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_CORE_OVERRIDE, 0x00);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_PLL_DIGITAL_TIMERS_TWO, 0x08);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_PLL_PROP_GAIN_RATE_1, 0x08);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_PLL_BAND_SET_RATE_1, 0xc0);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_PLL_INT_GAIN_IFILT_BAND_1, 0xfa);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_PLL_FL_INT_GAIN_PFILT_BAND_1,
		  0x4c);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_PLL_LOCK_OVERRIDE, 0x80);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_PFILT, 0x29);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_IFILT, 0x3f);
पूर्ण

अटल व्योम dsi_pll_commit(काष्ठा dsi_pll_10nm *pll, काष्ठा dsi_pll_config *config)
अणु
	व्योम __iomem *base = pll->phy->pll_base;

	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_CORE_INPUT_OVERRIDE, 0x12);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_DECIMAL_DIV_START_1,
		  config->decimal_भाग_start);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_FRAC_DIV_START_LOW_1,
		  config->frac_भाग_start & 0xff);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_FRAC_DIV_START_MID_1,
		  (config->frac_भाग_start & 0xff00) >> 8);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_FRAC_DIV_START_HIGH_1,
		  (config->frac_भाग_start & 0x30000) >> 16);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_PLL_LOCKDET_RATE_1, 64);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_PLL_LOCK_DELAY, 0x06);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_CMODE, 0x10);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_PLL_CLOCK_INVERTERS,
		  config->pll_घड़ी_inverters);
पूर्ण

अटल पूर्णांक dsi_pll_10nm_vco_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा dsi_pll_10nm *pll_10nm = to_pll_10nm(hw);
	काष्ठा dsi_pll_config config;

	DBG("DSI PLL%d rate=%lu, parent's=%lu", pll_10nm->phy->id, rate,
	    parent_rate);

	pll_10nm->vco_current_rate = rate;

	dsi_pll_setup_config(&config);

	dsi_pll_calc_dec_frac(pll_10nm, &config);

	dsi_pll_calc_ssc(pll_10nm, &config);

	dsi_pll_commit(pll_10nm, &config);

	dsi_pll_config_hzindep_reg(pll_10nm);

	dsi_pll_ssc_commit(pll_10nm, &config);

	/* flush, ensure all रेजिस्टर ग_लिखोs are करोne*/
	wmb();

	वापस 0;
पूर्ण

अटल पूर्णांक dsi_pll_10nm_lock_status(काष्ठा dsi_pll_10nm *pll)
अणु
	काष्ठा device *dev = &pll->phy->pdev->dev;
	पूर्णांक rc;
	u32 status = 0;
	u32 स्थिर delay_us = 100;
	u32 स्थिर समयout_us = 5000;

	rc = पढ़ोl_poll_समयout_atomic(pll->phy->pll_base +
				       REG_DSI_10nm_PHY_PLL_COMMON_STATUS_ONE,
				       status,
				       ((status & BIT(0)) > 0),
				       delay_us,
				       समयout_us);
	अगर (rc)
		DRM_DEV_ERROR(dev, "DSI PLL(%d) lock failed, status=0x%08x\n",
			      pll->phy->id, status);

	वापस rc;
पूर्ण

अटल व्योम dsi_pll_disable_pll_bias(काष्ठा dsi_pll_10nm *pll)
अणु
	u32 data = dsi_phy_पढ़ो(pll->phy->base + REG_DSI_10nm_PHY_CMN_CTRL_0);

	dsi_phy_ग_लिखो(pll->phy->pll_base + REG_DSI_10nm_PHY_PLL_SYSTEM_MUXES, 0);
	dsi_phy_ग_लिखो(pll->phy->base + REG_DSI_10nm_PHY_CMN_CTRL_0,
		  data & ~BIT(5));
	ndelay(250);
पूर्ण

अटल व्योम dsi_pll_enable_pll_bias(काष्ठा dsi_pll_10nm *pll)
अणु
	u32 data = dsi_phy_पढ़ो(pll->phy->base + REG_DSI_10nm_PHY_CMN_CTRL_0);

	dsi_phy_ग_लिखो(pll->phy->base + REG_DSI_10nm_PHY_CMN_CTRL_0,
		  data | BIT(5));
	dsi_phy_ग_लिखो(pll->phy->pll_base + REG_DSI_10nm_PHY_PLL_SYSTEM_MUXES, 0xc0);
	ndelay(250);
पूर्ण

अटल व्योम dsi_pll_disable_global_clk(काष्ठा dsi_pll_10nm *pll)
अणु
	u32 data;

	data = dsi_phy_पढ़ो(pll->phy->base + REG_DSI_10nm_PHY_CMN_CLK_CFG1);
	dsi_phy_ग_लिखो(pll->phy->base + REG_DSI_10nm_PHY_CMN_CLK_CFG1,
		  data & ~BIT(5));
पूर्ण

अटल व्योम dsi_pll_enable_global_clk(काष्ठा dsi_pll_10nm *pll)
अणु
	u32 data;

	data = dsi_phy_पढ़ो(pll->phy->base + REG_DSI_10nm_PHY_CMN_CLK_CFG1);
	dsi_phy_ग_लिखो(pll->phy->base + REG_DSI_10nm_PHY_CMN_CLK_CFG1,
		  data | BIT(5));
पूर्ण

अटल पूर्णांक dsi_pll_10nm_vco_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा dsi_pll_10nm *pll_10nm = to_pll_10nm(hw);
	काष्ठा device *dev = &pll_10nm->phy->pdev->dev;
	पूर्णांक rc;

	dsi_pll_enable_pll_bias(pll_10nm);
	अगर (pll_10nm->slave)
		dsi_pll_enable_pll_bias(pll_10nm->slave);

	rc = dsi_pll_10nm_vco_set_rate(hw,pll_10nm->vco_current_rate, 0);
	अगर (rc) अणु
		DRM_DEV_ERROR(dev, "vco_set_rate failed, rc=%d\n", rc);
		वापस rc;
	पूर्ण

	/* Start PLL */
	dsi_phy_ग_लिखो(pll_10nm->phy->base + REG_DSI_10nm_PHY_CMN_PLL_CNTRL,
		  0x01);

	/*
	 * ensure all PLL configurations are written prior to checking
	 * क्रम PLL lock.
	 */
	wmb();

	/* Check क्रम PLL lock */
	rc = dsi_pll_10nm_lock_status(pll_10nm);
	अगर (rc) अणु
		DRM_DEV_ERROR(dev, "PLL(%d) lock failed\n", pll_10nm->phy->id);
		जाओ error;
	पूर्ण

	pll_10nm->phy->pll_on = true;

	dsi_pll_enable_global_clk(pll_10nm);
	अगर (pll_10nm->slave)
		dsi_pll_enable_global_clk(pll_10nm->slave);

	dsi_phy_ग_लिखो(pll_10nm->phy->base + REG_DSI_10nm_PHY_CMN_RBUF_CTRL,
		  0x01);
	अगर (pll_10nm->slave)
		dsi_phy_ग_लिखो(pll_10nm->slave->phy->base +
			  REG_DSI_10nm_PHY_CMN_RBUF_CTRL, 0x01);

error:
	वापस rc;
पूर्ण

अटल व्योम dsi_pll_disable_sub(काष्ठा dsi_pll_10nm *pll)
अणु
	dsi_phy_ग_लिखो(pll->phy->base + REG_DSI_10nm_PHY_CMN_RBUF_CTRL, 0);
	dsi_pll_disable_pll_bias(pll);
पूर्ण

अटल व्योम dsi_pll_10nm_vco_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा dsi_pll_10nm *pll_10nm = to_pll_10nm(hw);

	/*
	 * To aव्योम any stray glitches जबतक abruptly घातering करोwn the PLL
	 * make sure to gate the घड़ी using the घड़ी enable bit beक्रमe
	 * घातering करोwn the PLL
	 */
	dsi_pll_disable_global_clk(pll_10nm);
	dsi_phy_ग_लिखो(pll_10nm->phy->base + REG_DSI_10nm_PHY_CMN_PLL_CNTRL, 0);
	dsi_pll_disable_sub(pll_10nm);
	अगर (pll_10nm->slave) अणु
		dsi_pll_disable_global_clk(pll_10nm->slave);
		dsi_pll_disable_sub(pll_10nm->slave);
	पूर्ण
	/* flush, ensure all रेजिस्टर ग_लिखोs are करोne */
	wmb();
	pll_10nm->phy->pll_on = false;
पूर्ण

अटल अचिन्हित दीर्घ dsi_pll_10nm_vco_recalc_rate(काष्ठा clk_hw *hw,
						  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा dsi_pll_10nm *pll_10nm = to_pll_10nm(hw);
	व्योम __iomem *base = pll_10nm->phy->pll_base;
	u64 ref_clk = VCO_REF_CLK_RATE;
	u64 vco_rate = 0x0;
	u64 multiplier;
	u32 frac;
	u32 dec;
	u64 pll_freq, पंचांगp64;

	dec = dsi_phy_पढ़ो(base + REG_DSI_10nm_PHY_PLL_DECIMAL_DIV_START_1);
	dec &= 0xff;

	frac = dsi_phy_पढ़ो(base + REG_DSI_10nm_PHY_PLL_FRAC_DIV_START_LOW_1);
	frac |= ((dsi_phy_पढ़ो(base + REG_DSI_10nm_PHY_PLL_FRAC_DIV_START_MID_1) &
		  0xff) << 8);
	frac |= ((dsi_phy_पढ़ो(base + REG_DSI_10nm_PHY_PLL_FRAC_DIV_START_HIGH_1) &
		  0x3) << 16);

	/*
	 * TODO:
	 *	1. Assumes prescaler is disabled
	 */
	multiplier = 1 << FRAC_BITS;
	pll_freq = dec * (ref_clk * 2);
	पंचांगp64 = (ref_clk * 2 * frac);
	pll_freq += भाग_u64(पंचांगp64, multiplier);

	vco_rate = pll_freq;
	pll_10nm->vco_current_rate = vco_rate;

	DBG("DSI PLL%d returning vco rate = %lu, dec = %x, frac = %x",
	    pll_10nm->phy->id, (अचिन्हित दीर्घ)vco_rate, dec, frac);

	वापस (अचिन्हित दीर्घ)vco_rate;
पूर्ण

अटल दीर्घ dsi_pll_10nm_clk_round_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ rate, अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा dsi_pll_10nm *pll_10nm = to_pll_10nm(hw);

	अगर      (rate < pll_10nm->phy->cfg->min_pll_rate)
		वापस  pll_10nm->phy->cfg->min_pll_rate;
	अन्यथा अगर (rate > pll_10nm->phy->cfg->max_pll_rate)
		वापस  pll_10nm->phy->cfg->max_pll_rate;
	अन्यथा
		वापस rate;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_ops_dsi_pll_10nm_vco = अणु
	.round_rate = dsi_pll_10nm_clk_round_rate,
	.set_rate = dsi_pll_10nm_vco_set_rate,
	.recalc_rate = dsi_pll_10nm_vco_recalc_rate,
	.prepare = dsi_pll_10nm_vco_prepare,
	.unprepare = dsi_pll_10nm_vco_unprepare,
पूर्ण;

/*
 * PLL Callbacks
 */

अटल व्योम dsi_10nm_pll_save_state(काष्ठा msm_dsi_phy *phy)
अणु
	काष्ठा dsi_pll_10nm *pll_10nm = to_pll_10nm(phy->vco_hw);
	काष्ठा pll_10nm_cached_state *cached = &pll_10nm->cached_state;
	व्योम __iomem *phy_base = pll_10nm->phy->base;
	u32 cmn_clk_cfg0, cmn_clk_cfg1;

	cached->pll_out_भाग = dsi_phy_पढ़ो(pll_10nm->phy->pll_base +
				       REG_DSI_10nm_PHY_PLL_PLL_OUTDIV_RATE);
	cached->pll_out_भाग &= 0x3;

	cmn_clk_cfg0 = dsi_phy_पढ़ो(phy_base + REG_DSI_10nm_PHY_CMN_CLK_CFG0);
	cached->bit_clk_भाग = cmn_clk_cfg0 & 0xf;
	cached->pix_clk_भाग = (cmn_clk_cfg0 & 0xf0) >> 4;

	cmn_clk_cfg1 = dsi_phy_पढ़ो(phy_base + REG_DSI_10nm_PHY_CMN_CLK_CFG1);
	cached->pll_mux = cmn_clk_cfg1 & 0x3;

	DBG("DSI PLL%d outdiv %x bit_clk_div %x pix_clk_div %x pll_mux %x",
	    pll_10nm->phy->id, cached->pll_out_भाग, cached->bit_clk_भाग,
	    cached->pix_clk_भाग, cached->pll_mux);
पूर्ण

अटल पूर्णांक dsi_10nm_pll_restore_state(काष्ठा msm_dsi_phy *phy)
अणु
	काष्ठा dsi_pll_10nm *pll_10nm = to_pll_10nm(phy->vco_hw);
	काष्ठा pll_10nm_cached_state *cached = &pll_10nm->cached_state;
	व्योम __iomem *phy_base = pll_10nm->phy->base;
	u32 val;
	पूर्णांक ret;

	val = dsi_phy_पढ़ो(pll_10nm->phy->pll_base + REG_DSI_10nm_PHY_PLL_PLL_OUTDIV_RATE);
	val &= ~0x3;
	val |= cached->pll_out_भाग;
	dsi_phy_ग_लिखो(pll_10nm->phy->pll_base + REG_DSI_10nm_PHY_PLL_PLL_OUTDIV_RATE, val);

	dsi_phy_ग_लिखो(phy_base + REG_DSI_10nm_PHY_CMN_CLK_CFG0,
		  cached->bit_clk_भाग | (cached->pix_clk_भाग << 4));

	val = dsi_phy_पढ़ो(phy_base + REG_DSI_10nm_PHY_CMN_CLK_CFG1);
	val &= ~0x3;
	val |= cached->pll_mux;
	dsi_phy_ग_लिखो(phy_base + REG_DSI_10nm_PHY_CMN_CLK_CFG1, val);

	ret = dsi_pll_10nm_vco_set_rate(phy->vco_hw,
			pll_10nm->vco_current_rate,
			VCO_REF_CLK_RATE);
	अगर (ret) अणु
		DRM_DEV_ERROR(&pll_10nm->phy->pdev->dev,
			"restore vco rate failed. ret=%d\n", ret);
		वापस ret;
	पूर्ण

	DBG("DSI PLL%d", pll_10nm->phy->id);

	वापस 0;
पूर्ण

अटल पूर्णांक dsi_10nm_set_useहाल(काष्ठा msm_dsi_phy *phy)
अणु
	काष्ठा dsi_pll_10nm *pll_10nm = to_pll_10nm(phy->vco_hw);
	व्योम __iomem *base = phy->base;
	u32 data = 0x0;	/* पूर्णांकernal PLL */

	DBG("DSI PLL%d", pll_10nm->phy->id);

	चयन (phy->useहाल) अणु
	हाल MSM_DSI_PHY_STANDALONE:
		अवरोध;
	हाल MSM_DSI_PHY_MASTER:
		pll_10nm->slave = pll_10nm_list[(pll_10nm->phy->id + 1) % DSI_MAX];
		अवरोध;
	हाल MSM_DSI_PHY_SLAVE:
		data = 0x1; /* बाह्यal PLL */
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* set PLL src */
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_CMN_CLK_CFG1, (data << 2));

	वापस 0;
पूर्ण

/*
 * The post भागiders and mux घड़ीs are created using the standard भागider and
 * mux API. Unlike the 14nm PHY, the slave PLL करोesn't need its भागiders/mux
 * state to follow the master PLL's divider/mux state. Therefore, we don't
 * require special घड़ी ops that also configure the slave PLL रेजिस्टरs
 */
अटल पूर्णांक pll_10nm_रेजिस्टर(काष्ठा dsi_pll_10nm *pll_10nm, काष्ठा clk_hw **provided_घड़ीs)
अणु
	अक्षर clk_name[32], parent[32], vco_name[32];
	अक्षर parent2[32], parent3[32], parent4[32];
	काष्ठा clk_init_data vco_init = अणु
		.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
		.num_parents = 1,
		.name = vco_name,
		.flags = CLK_IGNORE_UNUSED,
		.ops = &clk_ops_dsi_pll_10nm_vco,
	पूर्ण;
	काष्ठा device *dev = &pll_10nm->phy->pdev->dev;
	काष्ठा clk_hw *hw;
	पूर्णांक ret;

	DBG("DSI%d", pll_10nm->phy->id);

	snम_लिखो(vco_name, 32, "dsi%dvco_clk", pll_10nm->phy->id);
	pll_10nm->clk_hw.init = &vco_init;

	ret = devm_clk_hw_रेजिस्टर(dev, &pll_10nm->clk_hw);
	अगर (ret)
		वापस ret;

	snम_लिखो(clk_name, 32, "dsi%d_pll_out_div_clk", pll_10nm->phy->id);
	snम_लिखो(parent, 32, "dsi%dvco_clk", pll_10nm->phy->id);

	hw = devm_clk_hw_रेजिस्टर_भागider(dev, clk_name,
				     parent, CLK_SET_RATE_PARENT,
				     pll_10nm->phy->pll_base +
				     REG_DSI_10nm_PHY_PLL_PLL_OUTDIV_RATE,
				     0, 2, CLK_DIVIDER_POWER_OF_TWO, शून्य);
	अगर (IS_ERR(hw)) अणु
		ret = PTR_ERR(hw);
		जाओ fail;
	पूर्ण

	snम_लिखो(clk_name, 32, "dsi%d_pll_bit_clk", pll_10nm->phy->id);
	snम_लिखो(parent, 32, "dsi%d_pll_out_div_clk", pll_10nm->phy->id);

	/* BIT CLK: DIV_CTRL_3_0 */
	hw = devm_clk_hw_रेजिस्टर_भागider(dev, clk_name, parent,
				     CLK_SET_RATE_PARENT,
				     pll_10nm->phy->base +
				     REG_DSI_10nm_PHY_CMN_CLK_CFG0,
				     0, 4, CLK_DIVIDER_ONE_BASED,
				     &pll_10nm->postभाग_lock);
	अगर (IS_ERR(hw)) अणु
		ret = PTR_ERR(hw);
		जाओ fail;
	पूर्ण

	snम_लिखो(clk_name, 32, "dsi%d_phy_pll_out_byteclk", pll_10nm->phy->id);
	snम_लिखो(parent, 32, "dsi%d_pll_bit_clk", pll_10nm->phy->id);

	/* DSI Byte घड़ी = VCO_CLK / OUT_DIV / BIT_DIV / 8 */
	hw = devm_clk_hw_रेजिस्टर_fixed_factor(dev, clk_name, parent,
					  CLK_SET_RATE_PARENT, 1, 8);
	अगर (IS_ERR(hw)) अणु
		ret = PTR_ERR(hw);
		जाओ fail;
	पूर्ण

	provided_घड़ीs[DSI_BYTE_PLL_CLK] = hw;

	snम_लिखो(clk_name, 32, "dsi%d_pll_by_2_bit_clk", pll_10nm->phy->id);
	snम_लिखो(parent, 32, "dsi%d_pll_bit_clk", pll_10nm->phy->id);

	hw = devm_clk_hw_रेजिस्टर_fixed_factor(dev, clk_name, parent,
					  0, 1, 2);
	अगर (IS_ERR(hw)) अणु
		ret = PTR_ERR(hw);
		जाओ fail;
	पूर्ण

	snम_लिखो(clk_name, 32, "dsi%d_pll_post_out_div_clk", pll_10nm->phy->id);
	snम_लिखो(parent, 32, "dsi%d_pll_out_div_clk", pll_10nm->phy->id);

	hw = devm_clk_hw_रेजिस्टर_fixed_factor(dev, clk_name, parent,
					  0, 1, 4);
	अगर (IS_ERR(hw)) अणु
		ret = PTR_ERR(hw);
		जाओ fail;
	पूर्ण

	snम_लिखो(clk_name, 32, "dsi%d_pclk_mux", pll_10nm->phy->id);
	snम_लिखो(parent, 32, "dsi%d_pll_bit_clk", pll_10nm->phy->id);
	snम_लिखो(parent2, 32, "dsi%d_pll_by_2_bit_clk", pll_10nm->phy->id);
	snम_लिखो(parent3, 32, "dsi%d_pll_out_div_clk", pll_10nm->phy->id);
	snम_लिखो(parent4, 32, "dsi%d_pll_post_out_div_clk", pll_10nm->phy->id);

	hw = devm_clk_hw_रेजिस्टर_mux(dev, clk_name,
				 ((स्थिर अक्षर *[])अणु
				 parent, parent2, parent3, parent4
				 पूर्ण), 4, 0, pll_10nm->phy->base +
				 REG_DSI_10nm_PHY_CMN_CLK_CFG1,
				 0, 2, 0, शून्य);
	अगर (IS_ERR(hw)) अणु
		ret = PTR_ERR(hw);
		जाओ fail;
	पूर्ण

	snम_लिखो(clk_name, 32, "dsi%d_phy_pll_out_dsiclk", pll_10nm->phy->id);
	snम_लिखो(parent, 32, "dsi%d_pclk_mux", pll_10nm->phy->id);

	/* PIX CLK DIV : DIV_CTRL_7_4*/
	hw = devm_clk_hw_रेजिस्टर_भागider(dev, clk_name, parent,
				     0, pll_10nm->phy->base +
					REG_DSI_10nm_PHY_CMN_CLK_CFG0,
				     4, 4, CLK_DIVIDER_ONE_BASED,
				     &pll_10nm->postभाग_lock);
	अगर (IS_ERR(hw)) अणु
		ret = PTR_ERR(hw);
		जाओ fail;
	पूर्ण

	provided_घड़ीs[DSI_PIXEL_PLL_CLK] = hw;

	वापस 0;

fail:

	वापस ret;
पूर्ण

अटल पूर्णांक dsi_pll_10nm_init(काष्ठा msm_dsi_phy *phy)
अणु
	काष्ठा platक्रमm_device *pdev = phy->pdev;
	काष्ठा dsi_pll_10nm *pll_10nm;
	पूर्णांक ret;

	pll_10nm = devm_kzalloc(&pdev->dev, माप(*pll_10nm), GFP_KERNEL);
	अगर (!pll_10nm)
		वापस -ENOMEM;

	DBG("DSI PLL%d", phy->id);

	pll_10nm_list[phy->id] = pll_10nm;

	spin_lock_init(&pll_10nm->postभाग_lock);

	pll_10nm->phy = phy;

	ret = pll_10nm_रेजिस्टर(pll_10nm, phy->provided_घड़ीs->hws);
	अगर (ret) अणु
		DRM_DEV_ERROR(&pdev->dev, "failed to register PLL: %d\n", ret);
		वापस ret;
	पूर्ण

	phy->vco_hw = &pll_10nm->clk_hw;

	/* TODO: Remove this when we have proper display hanकरोver support */
	msm_dsi_phy_pll_save_state(phy);

	वापस 0;
पूर्ण

अटल पूर्णांक dsi_phy_hw_v3_0_is_pll_on(काष्ठा msm_dsi_phy *phy)
अणु
	व्योम __iomem *base = phy->base;
	u32 data = 0;

	data = dsi_phy_पढ़ो(base + REG_DSI_10nm_PHY_CMN_PLL_CNTRL);
	mb(); /* make sure पढ़ो happened */

	वापस (data & BIT(0));
पूर्ण

अटल व्योम dsi_phy_hw_v3_0_config_lpcdrx(काष्ठा msm_dsi_phy *phy, bool enable)
अणु
	व्योम __iomem *lane_base = phy->lane_base;
	पूर्णांक phy_lane_0 = 0;	/* TODO: Support all lane swap configs */

	/*
	 * LPRX and CDRX need to enabled only क्रम physical data lane
	 * corresponding to the logical data lane 0
	 */
	अगर (enable)
		dsi_phy_ग_लिखो(lane_base +
			      REG_DSI_10nm_PHY_LN_LPRX_CTRL(phy_lane_0), 0x3);
	अन्यथा
		dsi_phy_ग_लिखो(lane_base +
			      REG_DSI_10nm_PHY_LN_LPRX_CTRL(phy_lane_0), 0);
पूर्ण

अटल व्योम dsi_phy_hw_v3_0_lane_settings(काष्ठा msm_dsi_phy *phy)
अणु
	पूर्णांक i;
	u8 tx_dctrl[] = अणु 0x00, 0x00, 0x00, 0x04, 0x01 पूर्ण;
	व्योम __iomem *lane_base = phy->lane_base;

	अगर (phy->cfg->quirks & DSI_PHY_10NM_QUIRK_OLD_TIMINGS)
		tx_dctrl[3] = 0x02;

	/* Strength ctrl settings */
	क्रम (i = 0; i < 5; i++) अणु
		dsi_phy_ग_लिखो(lane_base + REG_DSI_10nm_PHY_LN_LPTX_STR_CTRL(i),
			      0x55);
		/*
		 * Disable LPRX and CDRX क्रम all lanes. And later on, it will
		 * be only enabled क्रम the physical data lane corresponding
		 * to the logical data lane 0
		 */
		dsi_phy_ग_लिखो(lane_base + REG_DSI_10nm_PHY_LN_LPRX_CTRL(i), 0);
		dsi_phy_ग_लिखो(lane_base + REG_DSI_10nm_PHY_LN_PIN_SWAP(i), 0x0);
		dsi_phy_ग_लिखो(lane_base + REG_DSI_10nm_PHY_LN_HSTX_STR_CTRL(i),
			      0x88);
	पूर्ण

	dsi_phy_hw_v3_0_config_lpcdrx(phy, true);

	/* other settings */
	क्रम (i = 0; i < 5; i++) अणु
		dsi_phy_ग_लिखो(lane_base + REG_DSI_10nm_PHY_LN_CFG0(i), 0x0);
		dsi_phy_ग_लिखो(lane_base + REG_DSI_10nm_PHY_LN_CFG1(i), 0x0);
		dsi_phy_ग_लिखो(lane_base + REG_DSI_10nm_PHY_LN_CFG2(i), 0x0);
		dsi_phy_ग_लिखो(lane_base + REG_DSI_10nm_PHY_LN_CFG3(i),
			      i == 4 ? 0x80 : 0x0);
		dsi_phy_ग_लिखो(lane_base +
			      REG_DSI_10nm_PHY_LN_OFFSET_TOP_CTRL(i), 0x0);
		dsi_phy_ग_लिखो(lane_base +
			      REG_DSI_10nm_PHY_LN_OFFSET_BOT_CTRL(i), 0x0);
		dsi_phy_ग_लिखो(lane_base + REG_DSI_10nm_PHY_LN_TX_DCTRL(i),
			      tx_dctrl[i]);
	पूर्ण

	अगर (!(phy->cfg->quirks & DSI_PHY_10NM_QUIRK_OLD_TIMINGS)) अणु
		/* Toggle BIT 0 to release मुक्तze I/0 */
		dsi_phy_ग_लिखो(lane_base + REG_DSI_10nm_PHY_LN_TX_DCTRL(3), 0x05);
		dsi_phy_ग_लिखो(lane_base + REG_DSI_10nm_PHY_LN_TX_DCTRL(3), 0x04);
	पूर्ण
पूर्ण

अटल पूर्णांक dsi_10nm_phy_enable(काष्ठा msm_dsi_phy *phy,
			       काष्ठा msm_dsi_phy_clk_request *clk_req)
अणु
	पूर्णांक ret;
	u32 status;
	u32 स्थिर delay_us = 5;
	u32 स्थिर समयout_us = 1000;
	काष्ठा msm_dsi_dphy_timing *timing = &phy->timing;
	व्योम __iomem *base = phy->base;
	u32 data;

	DBG("");

	अगर (msm_dsi_dphy_timing_calc_v3(timing, clk_req)) अणु
		DRM_DEV_ERROR(&phy->pdev->dev,
			"%s: D-PHY timing calculation failed\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (dsi_phy_hw_v3_0_is_pll_on(phy))
		pr_warn("PLL turned on before configuring PHY\n");

	/* रुको क्रम REFGEN READY */
	ret = पढ़ोl_poll_समयout_atomic(base + REG_DSI_10nm_PHY_CMN_PHY_STATUS,
					status, (status & BIT(0)),
					delay_us, समयout_us);
	अगर (ret) अणु
		pr_err("Ref gen not ready. Aborting\n");
		वापस -EINVAL;
	पूर्ण

	/* de-निश्चित digital and pll घातer करोwn */
	data = BIT(6) | BIT(5);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_CMN_CTRL_0, data);

	/* Assert PLL core reset */
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_CMN_PLL_CNTRL, 0x00);

	/* turn off resync FIFO */
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_CMN_RBUF_CTRL, 0x00);

	/* Select MS1 byte-clk */
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_CMN_GLBL_CTRL, 0x10);

	/* Enable LDO */
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_CMN_VREG_CTRL, 0x59);

	/* Configure PHY lane swap (TODO: we need to calculate this) */
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_CMN_LANE_CFG0, 0x21);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_CMN_LANE_CFG1, 0x84);

	/* DSI PHY timings */
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_CMN_TIMING_CTRL_0,
		      timing->hs_halfbyte_en);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_CMN_TIMING_CTRL_1,
		      timing->clk_zero);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_CMN_TIMING_CTRL_2,
		      timing->clk_prepare);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_CMN_TIMING_CTRL_3,
		      timing->clk_trail);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_CMN_TIMING_CTRL_4,
		      timing->hs_निकास);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_CMN_TIMING_CTRL_5,
		      timing->hs_zero);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_CMN_TIMING_CTRL_6,
		      timing->hs_prepare);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_CMN_TIMING_CTRL_7,
		      timing->hs_trail);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_CMN_TIMING_CTRL_8,
		      timing->hs_rqst);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_CMN_TIMING_CTRL_9,
		      timing->ta_go | (timing->ta_sure << 3));
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_CMN_TIMING_CTRL_10,
		      timing->ta_get);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_CMN_TIMING_CTRL_11,
		      0x00);

	/* Remove घातer करोwn from all blocks */
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_CMN_CTRL_0, 0x7f);

	/* घातer up lanes */
	data = dsi_phy_पढ़ो(base + REG_DSI_10nm_PHY_CMN_CTRL_0);

	/* TODO: only घातer up lanes that are used */
	data |= 0x1F;
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_CMN_CTRL_0, data);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_CMN_LANE_CTRL0, 0x1F);

	/* Select full-rate mode */
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_CMN_CTRL_2, 0x40);

	ret = dsi_10nm_set_useहाल(phy);
	अगर (ret) अणु
		DRM_DEV_ERROR(&phy->pdev->dev, "%s: set pll usecase failed, %d\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	/* DSI lane settings */
	dsi_phy_hw_v3_0_lane_settings(phy);

	DBG("DSI%d PHY enabled", phy->id);

	वापस 0;
पूर्ण

अटल व्योम dsi_10nm_phy_disable(काष्ठा msm_dsi_phy *phy)
अणु
	व्योम __iomem *base = phy->base;
	u32 data;

	DBG("");

	अगर (dsi_phy_hw_v3_0_is_pll_on(phy))
		pr_warn("Turning OFF PHY while PLL is on\n");

	dsi_phy_hw_v3_0_config_lpcdrx(phy, false);
	data = dsi_phy_पढ़ो(base + REG_DSI_10nm_PHY_CMN_CTRL_0);

	/* disable all lanes */
	data &= ~0x1F;
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_CMN_CTRL_0, data);
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_CMN_LANE_CTRL0, 0);

	/* Turn off all PHY blocks */
	dsi_phy_ग_लिखो(base + REG_DSI_10nm_PHY_CMN_CTRL_0, 0x00);
	/* make sure phy is turned off */
	wmb();

	DBG("DSI%d PHY disabled", phy->id);
पूर्ण

स्थिर काष्ठा msm_dsi_phy_cfg dsi_phy_10nm_cfgs = अणु
	.has_phy_lane = true,
	.reg_cfg = अणु
		.num = 1,
		.regs = अणु
			अणु"vdds", 36000, 32पूर्ण,
		पूर्ण,
	पूर्ण,
	.ops = अणु
		.enable = dsi_10nm_phy_enable,
		.disable = dsi_10nm_phy_disable,
		.pll_init = dsi_pll_10nm_init,
		.save_pll_state = dsi_10nm_pll_save_state,
		.restore_pll_state = dsi_10nm_pll_restore_state,
	पूर्ण,
	.min_pll_rate = 1000000000UL,
	.max_pll_rate = 3500000000UL,
	.io_start = अणु 0xae94400, 0xae96400 पूर्ण,
	.num_dsi_phy = 2,
पूर्ण;

स्थिर काष्ठा msm_dsi_phy_cfg dsi_phy_10nm_8998_cfgs = अणु
	.has_phy_lane = true,
	.reg_cfg = अणु
		.num = 1,
		.regs = अणु
			अणु"vdds", 36000, 32पूर्ण,
		पूर्ण,
	पूर्ण,
	.ops = अणु
		.enable = dsi_10nm_phy_enable,
		.disable = dsi_10nm_phy_disable,
		.pll_init = dsi_pll_10nm_init,
		.save_pll_state = dsi_10nm_pll_save_state,
		.restore_pll_state = dsi_10nm_pll_restore_state,
	पूर्ण,
	.min_pll_rate = 1000000000UL,
	.max_pll_rate = 3500000000UL,
	.io_start = अणु 0xc994400, 0xc996400 पूर्ण,
	.num_dsi_phy = 2,
	.quirks = DSI_PHY_10NM_QUIRK_OLD_TIMINGS,
पूर्ण;
