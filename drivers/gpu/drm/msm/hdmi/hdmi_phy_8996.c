<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>

#समावेश "hdmi.h"

#घोषणा HDMI_VCO_MAX_FREQ			12000000000UL
#घोषणा HDMI_VCO_MIN_FREQ			8000000000UL

#घोषणा HDMI_PCLK_MAX_FREQ			600000000
#घोषणा HDMI_PCLK_MIN_FREQ			25000000

#घोषणा HDMI_HIGH_FREQ_BIT_CLK_THRESHOLD	3400000000UL
#घोषणा HDMI_DIG_FREQ_BIT_CLK_THRESHOLD		1500000000UL
#घोषणा HDMI_MID_FREQ_BIT_CLK_THRESHOLD		750000000UL
#घोषणा HDMI_CORECLK_DIV			5
#घोषणा HDMI_DEFAULT_REF_CLOCK			19200000
#घोषणा HDMI_PLL_CMP_CNT			1024

#घोषणा HDMI_PLL_POLL_MAX_READS			100
#घोषणा HDMI_PLL_POLL_TIMEOUT_US		150

#घोषणा HDMI_NUM_TX_CHANNEL			4

काष्ठा hdmi_pll_8996 अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा clk_hw clk_hw;

	/* pll mmio base */
	व्योम __iomem *mmio_qserdes_com;
	/* tx channel base */
	व्योम __iomem *mmio_qserdes_tx[HDMI_NUM_TX_CHANNEL];
पूर्ण;

#घोषणा hw_clk_to_pll(x) container_of(x, काष्ठा hdmi_pll_8996, clk_hw)

काष्ठा hdmi_8996_phy_pll_reg_cfg अणु
	u32 tx_lx_lane_mode[HDMI_NUM_TX_CHANNEL];
	u32 tx_lx_tx_band[HDMI_NUM_TX_CHANNEL];
	u32 com_svs_mode_clk_sel;
	u32 com_hsclk_sel;
	u32 com_pll_cctrl_mode0;
	u32 com_pll_rctrl_mode0;
	u32 com_cp_ctrl_mode0;
	u32 com_dec_start_mode0;
	u32 com_भाग_frac_start1_mode0;
	u32 com_भाग_frac_start2_mode0;
	u32 com_भाग_frac_start3_mode0;
	u32 com_पूर्णांकegloop_gain0_mode0;
	u32 com_पूर्णांकegloop_gain1_mode0;
	u32 com_lock_cmp_en;
	u32 com_lock_cmp1_mode0;
	u32 com_lock_cmp2_mode0;
	u32 com_lock_cmp3_mode0;
	u32 com_core_clk_en;
	u32 com_coreclk_भाग;
	u32 com_vco_tune_ctrl;

	u32 tx_lx_tx_drv_lvl[HDMI_NUM_TX_CHANNEL];
	u32 tx_lx_tx_emp_post1_lvl[HDMI_NUM_TX_CHANNEL];
	u32 tx_lx_vmode_ctrl1[HDMI_NUM_TX_CHANNEL];
	u32 tx_lx_vmode_ctrl2[HDMI_NUM_TX_CHANNEL];
	u32 tx_lx_res_code_lane_tx[HDMI_NUM_TX_CHANNEL];
	u32 tx_lx_hp_pd_enables[HDMI_NUM_TX_CHANNEL];

	u32 phy_mode;
पूर्ण;

काष्ठा hdmi_8996_post_भागider अणु
	u64 vco_freq;
	पूर्णांक hsclk_भागsel;
	पूर्णांक vco_ratio;
	पूर्णांक tx_band_sel;
	पूर्णांक half_rate_mode;
पूर्ण;

अटल अंतरभूत काष्ठा hdmi_phy *pll_get_phy(काष्ठा hdmi_pll_8996 *pll)
अणु
	वापस platक्रमm_get_drvdata(pll->pdev);
पूर्ण

अटल अंतरभूत व्योम hdmi_pll_ग_लिखो(काष्ठा hdmi_pll_8996 *pll, पूर्णांक offset,
				  u32 data)
अणु
	msm_ग_लिखोl(data, pll->mmio_qserdes_com + offset);
पूर्ण

अटल अंतरभूत u32 hdmi_pll_पढ़ो(काष्ठा hdmi_pll_8996 *pll, पूर्णांक offset)
अणु
	वापस msm_पढ़ोl(pll->mmio_qserdes_com + offset);
पूर्ण

अटल अंतरभूत व्योम hdmi_tx_chan_ग_लिखो(काष्ठा hdmi_pll_8996 *pll, पूर्णांक channel,
				      पूर्णांक offset, पूर्णांक data)
अणु
	 msm_ग_लिखोl(data, pll->mmio_qserdes_tx[channel] + offset);
पूर्ण

अटल अंतरभूत u32 pll_get_cpctrl(u64 frac_start, अचिन्हित दीर्घ ref_clk,
				 bool gen_ssc)
अणु
	अगर ((frac_start != 0) || gen_ssc)
		वापस (11000000 / (ref_clk / 20));

	वापस 0x23;
पूर्ण

अटल अंतरभूत u32 pll_get_rctrl(u64 frac_start, bool gen_ssc)
अणु
	अगर ((frac_start != 0) || gen_ssc)
		वापस 0x16;

	वापस 0x10;
पूर्ण

अटल अंतरभूत u32 pll_get_cctrl(u64 frac_start, bool gen_ssc)
अणु
	अगर ((frac_start != 0) || gen_ssc)
		वापस 0x28;

	वापस 0x1;
पूर्ण

अटल अंतरभूत u32 pll_get_पूर्णांकegloop_gain(u64 frac_start, u64 bclk, u32 ref_clk,
					 bool gen_ssc)
अणु
	पूर्णांक digclk_भागsel = bclk >= HDMI_DIG_FREQ_BIT_CLK_THRESHOLD ? 1 : 2;
	u64 base;

	अगर ((frac_start != 0) || gen_ssc)
		base = (64 * ref_clk) / HDMI_DEFAULT_REF_CLOCK;
	अन्यथा
		base = (1022 * ref_clk) / 100;

	base <<= digclk_भागsel;

	वापस (base <= 2046 ? base : 2046);
पूर्ण

अटल अंतरभूत u32 pll_get_pll_cmp(u64 fdata, अचिन्हित दीर्घ ref_clk)
अणु
	u64 भागidend = HDMI_PLL_CMP_CNT * fdata;
	u32 भागisor = ref_clk * 10;
	u32 rem;

	rem = करो_भाग(भागidend, भागisor);
	अगर (rem > (भागisor >> 1))
		भागidend++;

	वापस भागidend - 1;
पूर्ण

अटल अंतरभूत u64 pll_cmp_to_fdata(u32 pll_cmp, अचिन्हित दीर्घ ref_clk)
अणु
	u64 fdata = ((u64)pll_cmp) * ref_clk * 10;

	करो_भाग(fdata, HDMI_PLL_CMP_CNT);

	वापस fdata;
पूर्ण

अटल पूर्णांक pll_get_post_भाग(काष्ठा hdmi_8996_post_भागider *pd, u64 bclk)
अणु
	पूर्णांक ratio[] = अणु 2, 3, 4, 5, 6, 9, 10, 12, 14, 15, 20, 21, 25, 28, 35 पूर्ण;
	पूर्णांक hs_भागsel[] = अणु 0, 4, 8, 12, 1, 5, 2, 9, 3, 13, 10, 7, 14, 11, 15 पूर्ण;
	पूर्णांक tx_band_sel[] = अणु 0, 1, 2, 3 पूर्ण;
	u64 vco_freq[60];
	u64 vco, vco_optimal;
	पूर्णांक half_rate_mode = 0;
	पूर्णांक vco_optimal_index, vco_freq_index;
	पूर्णांक i, j;

retry:
	vco_optimal = HDMI_VCO_MAX_FREQ;
	vco_optimal_index = -1;
	vco_freq_index = 0;
	क्रम (i = 0; i < 15; i++) अणु
		क्रम (j = 0; j < 4; j++) अणु
			u32 ratio_mult = ratio[i] << tx_band_sel[j];

			vco = bclk >> half_rate_mode;
			vco *= ratio_mult;
			vco_freq[vco_freq_index++] = vco;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 60; i++) अणु
		u64 vco_पंचांगp = vco_freq[i];

		अगर ((vco_पंचांगp >= HDMI_VCO_MIN_FREQ) &&
		    (vco_पंचांगp <= vco_optimal)) अणु
			vco_optimal = vco_पंचांगp;
			vco_optimal_index = i;
		पूर्ण
	पूर्ण

	अगर (vco_optimal_index == -1) अणु
		अगर (!half_rate_mode) अणु
			half_rate_mode = 1;
			जाओ retry;
		पूर्ण
	पूर्ण अन्यथा अणु
		pd->vco_freq = vco_optimal;
		pd->tx_band_sel = tx_band_sel[vco_optimal_index % 4];
		pd->vco_ratio = ratio[vco_optimal_index / 4];
		pd->hsclk_भागsel = hs_भागsel[vco_optimal_index / 4];

		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक pll_calculate(अचिन्हित दीर्घ pix_clk, अचिन्हित दीर्घ ref_clk,
			 काष्ठा hdmi_8996_phy_pll_reg_cfg *cfg)
अणु
	काष्ठा hdmi_8996_post_भागider pd;
	u64 bclk;
	u64 पंचांगds_clk;
	u64 dec_start;
	u64 frac_start;
	u64 fdata;
	u32 pll_भागisor;
	u32 rem;
	u32 cpctrl;
	u32 rctrl;
	u32 cctrl;
	u32 पूर्णांकegloop_gain;
	u32 pll_cmp;
	पूर्णांक i, ret;

	/* bit clk = 10 * pix_clk */
	bclk = ((u64)pix_clk) * 10;

	अगर (bclk > HDMI_HIGH_FREQ_BIT_CLK_THRESHOLD)
		पंचांगds_clk = pix_clk >> 2;
	अन्यथा
		पंचांगds_clk = pix_clk;

	ret = pll_get_post_भाग(&pd, bclk);
	अगर (ret)
		वापस ret;

	dec_start = pd.vco_freq;
	pll_भागisor = 4 * ref_clk;
	करो_भाग(dec_start, pll_भागisor);

	frac_start = pd.vco_freq * (1 << 20);

	rem = करो_भाग(frac_start, pll_भागisor);
	frac_start -= dec_start * (1 << 20);
	अगर (rem > (pll_भागisor >> 1))
		frac_start++;

	cpctrl = pll_get_cpctrl(frac_start, ref_clk, false);
	rctrl = pll_get_rctrl(frac_start, false);
	cctrl = pll_get_cctrl(frac_start, false);
	पूर्णांकegloop_gain = pll_get_पूर्णांकegloop_gain(frac_start, bclk,
						ref_clk, false);

	fdata = pd.vco_freq;
	करो_भाग(fdata, pd.vco_ratio);

	pll_cmp = pll_get_pll_cmp(fdata, ref_clk);

	DBG("VCO freq: %llu", pd.vco_freq);
	DBG("fdata: %llu", fdata);
	DBG("pix_clk: %lu", pix_clk);
	DBG("tmds clk: %llu", पंचांगds_clk);
	DBG("HSCLK_SEL: %d", pd.hsclk_भागsel);
	DBG("DEC_START: %llu", dec_start);
	DBG("DIV_FRAC_START: %llu", frac_start);
	DBG("PLL_CPCTRL: %u", cpctrl);
	DBG("PLL_RCTRL: %u", rctrl);
	DBG("PLL_CCTRL: %u", cctrl);
	DBG("INTEGLOOP_GAIN: %u", पूर्णांकegloop_gain);
	DBG("TX_BAND: %d", pd.tx_band_sel);
	DBG("PLL_CMP: %u", pll_cmp);

	/* Convert these values to रेजिस्टर specअगरic values */
	अगर (bclk > HDMI_DIG_FREQ_BIT_CLK_THRESHOLD)
		cfg->com_svs_mode_clk_sel = 1;
	अन्यथा
		cfg->com_svs_mode_clk_sel = 2;

	cfg->com_hsclk_sel = (0x20 | pd.hsclk_भागsel);
	cfg->com_pll_cctrl_mode0 = cctrl;
	cfg->com_pll_rctrl_mode0 = rctrl;
	cfg->com_cp_ctrl_mode0 = cpctrl;
	cfg->com_dec_start_mode0 = dec_start;
	cfg->com_भाग_frac_start1_mode0 = (frac_start & 0xff);
	cfg->com_भाग_frac_start2_mode0 = ((frac_start & 0xff00) >> 8);
	cfg->com_भाग_frac_start3_mode0 = ((frac_start & 0xf0000) >> 16);
	cfg->com_पूर्णांकegloop_gain0_mode0 = (पूर्णांकegloop_gain & 0xff);
	cfg->com_पूर्णांकegloop_gain1_mode0 = ((पूर्णांकegloop_gain & 0xf00) >> 8);
	cfg->com_lock_cmp1_mode0 = (pll_cmp & 0xff);
	cfg->com_lock_cmp2_mode0 = ((pll_cmp & 0xff00) >> 8);
	cfg->com_lock_cmp3_mode0 = ((pll_cmp & 0x30000) >> 16);
	cfg->com_lock_cmp_en = 0x0;
	cfg->com_core_clk_en = 0x2c;
	cfg->com_coreclk_भाग = HDMI_CORECLK_DIV;
	cfg->phy_mode = (bclk > HDMI_HIGH_FREQ_BIT_CLK_THRESHOLD) ? 0x10 : 0x0;
	cfg->com_vco_tune_ctrl = 0x0;

	cfg->tx_lx_lane_mode[0] =
		cfg->tx_lx_lane_mode[2] = 0x43;

	cfg->tx_lx_hp_pd_enables[0] =
		cfg->tx_lx_hp_pd_enables[1] =
		cfg->tx_lx_hp_pd_enables[2] = 0x0c;
	cfg->tx_lx_hp_pd_enables[3] = 0x3;

	क्रम (i = 0; i < HDMI_NUM_TX_CHANNEL; i++)
		cfg->tx_lx_tx_band[i] = pd.tx_band_sel + 4;

	अगर (bclk > HDMI_HIGH_FREQ_BIT_CLK_THRESHOLD) अणु
		cfg->tx_lx_tx_drv_lvl[0] =
			cfg->tx_lx_tx_drv_lvl[1] =
			cfg->tx_lx_tx_drv_lvl[2] = 0x25;
		cfg->tx_lx_tx_drv_lvl[3] = 0x22;

		cfg->tx_lx_tx_emp_post1_lvl[0] =
			cfg->tx_lx_tx_emp_post1_lvl[1] =
			cfg->tx_lx_tx_emp_post1_lvl[2] = 0x23;
		cfg->tx_lx_tx_emp_post1_lvl[3] = 0x27;

		cfg->tx_lx_vmode_ctrl1[0] =
			cfg->tx_lx_vmode_ctrl1[1] =
			cfg->tx_lx_vmode_ctrl1[2] =
			cfg->tx_lx_vmode_ctrl1[3] = 0x00;

		cfg->tx_lx_vmode_ctrl2[0] =
			cfg->tx_lx_vmode_ctrl2[1] =
			cfg->tx_lx_vmode_ctrl2[2] = 0x0D;

		cfg->tx_lx_vmode_ctrl2[3] = 0x00;
	पूर्ण अन्यथा अगर (bclk > HDMI_MID_FREQ_BIT_CLK_THRESHOLD) अणु
		क्रम (i = 0; i < HDMI_NUM_TX_CHANNEL; i++) अणु
			cfg->tx_lx_tx_drv_lvl[i] = 0x25;
			cfg->tx_lx_tx_emp_post1_lvl[i] = 0x23;
			cfg->tx_lx_vmode_ctrl1[i] = 0x00;
		पूर्ण

		cfg->tx_lx_vmode_ctrl2[0] =
			cfg->tx_lx_vmode_ctrl2[1] =
			cfg->tx_lx_vmode_ctrl2[2] = 0x0D;
		cfg->tx_lx_vmode_ctrl2[3] = 0x00;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < HDMI_NUM_TX_CHANNEL; i++) अणु
			cfg->tx_lx_tx_drv_lvl[i] = 0x20;
			cfg->tx_lx_tx_emp_post1_lvl[i] = 0x20;
			cfg->tx_lx_vmode_ctrl1[i] = 0x00;
			cfg->tx_lx_vmode_ctrl2[i] = 0x0E;
		पूर्ण
	पूर्ण

	DBG("com_svs_mode_clk_sel = 0x%x", cfg->com_svs_mode_clk_sel);
	DBG("com_hsclk_sel = 0x%x", cfg->com_hsclk_sel);
	DBG("com_lock_cmp_en = 0x%x", cfg->com_lock_cmp_en);
	DBG("com_pll_cctrl_mode0 = 0x%x", cfg->com_pll_cctrl_mode0);
	DBG("com_pll_rctrl_mode0 = 0x%x", cfg->com_pll_rctrl_mode0);
	DBG("com_cp_ctrl_mode0 = 0x%x", cfg->com_cp_ctrl_mode0);
	DBG("com_dec_start_mode0 = 0x%x", cfg->com_dec_start_mode0);
	DBG("com_div_frac_start1_mode0 = 0x%x", cfg->com_भाग_frac_start1_mode0);
	DBG("com_div_frac_start2_mode0 = 0x%x", cfg->com_भाग_frac_start2_mode0);
	DBG("com_div_frac_start3_mode0 = 0x%x", cfg->com_भाग_frac_start3_mode0);
	DBG("com_integloop_gain0_mode0 = 0x%x", cfg->com_पूर्णांकegloop_gain0_mode0);
	DBG("com_integloop_gain1_mode0 = 0x%x", cfg->com_पूर्णांकegloop_gain1_mode0);
	DBG("com_lock_cmp1_mode0 = 0x%x", cfg->com_lock_cmp1_mode0);
	DBG("com_lock_cmp2_mode0 = 0x%x", cfg->com_lock_cmp2_mode0);
	DBG("com_lock_cmp3_mode0 = 0x%x", cfg->com_lock_cmp3_mode0);
	DBG("com_core_clk_en = 0x%x", cfg->com_core_clk_en);
	DBG("com_coreclk_div = 0x%x", cfg->com_coreclk_भाग);
	DBG("phy_mode = 0x%x", cfg->phy_mode);

	DBG("tx_l0_lane_mode = 0x%x", cfg->tx_lx_lane_mode[0]);
	DBG("tx_l2_lane_mode = 0x%x", cfg->tx_lx_lane_mode[2]);

	क्रम (i = 0; i < HDMI_NUM_TX_CHANNEL; i++) अणु
		DBG("tx_l%d_tx_band = 0x%x", i, cfg->tx_lx_tx_band[i]);
		DBG("tx_l%d_tx_drv_lvl = 0x%x", i, cfg->tx_lx_tx_drv_lvl[i]);
		DBG("tx_l%d_tx_emp_post1_lvl = 0x%x", i,
		    cfg->tx_lx_tx_emp_post1_lvl[i]);
		DBG("tx_l%d_vmode_ctrl1 = 0x%x", i, cfg->tx_lx_vmode_ctrl1[i]);
		DBG("tx_l%d_vmode_ctrl2 = 0x%x", i, cfg->tx_lx_vmode_ctrl2[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hdmi_8996_pll_set_clk_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				      अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा hdmi_pll_8996 *pll = hw_clk_to_pll(hw);
	काष्ठा hdmi_phy *phy = pll_get_phy(pll);
	काष्ठा hdmi_8996_phy_pll_reg_cfg cfg;
	पूर्णांक i, ret;

	स_रखो(&cfg, 0x00, माप(cfg));

	ret = pll_calculate(rate, parent_rate, &cfg);
	अगर (ret) अणु
		DRM_ERROR("PLL calculation failed\n");
		वापस ret;
	पूर्ण

	/* Initially shut करोwn PHY */
	DBG("Disabling PHY");
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8996_PHY_PD_CTL, 0x0);
	udelay(500);

	/* Power up sequence */
	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_BG_CTRL, 0x04);

	hdmi_phy_ग_लिखो(phy, REG_HDMI_8996_PHY_PD_CTL, 0x1);
	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_RESETSM_CNTRL, 0x20);
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8996_PHY_TX0_TX1_LANE_CTL, 0x0F);
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8996_PHY_TX2_TX3_LANE_CTL, 0x0F);

	क्रम (i = 0; i < HDMI_NUM_TX_CHANNEL; i++) अणु
		hdmi_tx_chan_ग_लिखो(pll, i,
				   REG_HDMI_PHY_QSERDES_TX_LX_CLKBUF_ENABLE,
				   0x03);
		hdmi_tx_chan_ग_लिखो(pll, i,
				   REG_HDMI_PHY_QSERDES_TX_LX_TX_BAND,
				   cfg.tx_lx_tx_band[i]);
		hdmi_tx_chan_ग_लिखो(pll, i,
				   REG_HDMI_PHY_QSERDES_TX_LX_RESET_TSYNC_EN,
				   0x03);
	पूर्ण

	hdmi_tx_chan_ग_लिखो(pll, 0, REG_HDMI_PHY_QSERDES_TX_LX_LANE_MODE,
			   cfg.tx_lx_lane_mode[0]);
	hdmi_tx_chan_ग_लिखो(pll, 2, REG_HDMI_PHY_QSERDES_TX_LX_LANE_MODE,
			   cfg.tx_lx_lane_mode[2]);

	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_SYSCLK_BUF_ENABLE, 0x1E);
	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_BIAS_EN_CLKBUFLR_EN, 0x07);
	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_SYSCLK_EN_SEL, 0x37);
	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_SYS_CLK_CTRL, 0x02);
	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_CLK_ENABLE1, 0x0E);

	/* Bypass VCO calibration */
	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_SVS_MODE_CLK_SEL,
		       cfg.com_svs_mode_clk_sel);

	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_BG_TRIM, 0x0F);
	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_PLL_IVCO, 0x0F);
	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_VCO_TUNE_CTRL,
		       cfg.com_vco_tune_ctrl);

	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_BG_CTRL, 0x06);

	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_CLK_SELECT, 0x30);
	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_HSCLK_SEL,
		       cfg.com_hsclk_sel);
	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_LOCK_CMP_EN,
		       cfg.com_lock_cmp_en);

	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_PLL_CCTRL_MODE0,
		       cfg.com_pll_cctrl_mode0);
	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_PLL_RCTRL_MODE0,
		       cfg.com_pll_rctrl_mode0);
	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_CP_CTRL_MODE0,
		       cfg.com_cp_ctrl_mode0);
	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_DEC_START_MODE0,
		       cfg.com_dec_start_mode0);
	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_DIV_FRAC_START1_MODE0,
		       cfg.com_भाग_frac_start1_mode0);
	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_DIV_FRAC_START2_MODE0,
		       cfg.com_भाग_frac_start2_mode0);
	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_DIV_FRAC_START3_MODE0,
		       cfg.com_भाग_frac_start3_mode0);

	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_INTEGLOOP_GAIN0_MODE0,
		       cfg.com_पूर्णांकegloop_gain0_mode0);
	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_INTEGLOOP_GAIN1_MODE0,
		       cfg.com_पूर्णांकegloop_gain1_mode0);

	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_LOCK_CMP1_MODE0,
		       cfg.com_lock_cmp1_mode0);
	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_LOCK_CMP2_MODE0,
		       cfg.com_lock_cmp2_mode0);
	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_LOCK_CMP3_MODE0,
		       cfg.com_lock_cmp3_mode0);

	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_VCO_TUNE_MAP, 0x00);
	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_CORE_CLK_EN,
		       cfg.com_core_clk_en);
	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_CORECLK_DIV,
		       cfg.com_coreclk_भाग);
	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_CMN_CONFIG, 0x02);

	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_RESCODE_DIV_NUM, 0x15);

	/* TX lanes setup (TX 0/1/2/3) */
	क्रम (i = 0; i < HDMI_NUM_TX_CHANNEL; i++) अणु
		hdmi_tx_chan_ग_लिखो(pll, i,
				   REG_HDMI_PHY_QSERDES_TX_LX_TX_DRV_LVL,
				   cfg.tx_lx_tx_drv_lvl[i]);
		hdmi_tx_chan_ग_लिखो(pll, i,
				   REG_HDMI_PHY_QSERDES_TX_LX_TX_EMP_POST1_LVL,
				   cfg.tx_lx_tx_emp_post1_lvl[i]);
		hdmi_tx_chan_ग_लिखो(pll, i,
				   REG_HDMI_PHY_QSERDES_TX_LX_VMODE_CTRL1,
				   cfg.tx_lx_vmode_ctrl1[i]);
		hdmi_tx_chan_ग_लिखो(pll, i,
				   REG_HDMI_PHY_QSERDES_TX_LX_VMODE_CTRL2,
				   cfg.tx_lx_vmode_ctrl2[i]);
		hdmi_tx_chan_ग_लिखो(pll, i,
				   REG_HDMI_PHY_QSERDES_TX_LX_TX_DRV_LVL_OFFSET,
				   0x00);
		hdmi_tx_chan_ग_लिखो(pll, i,
			REG_HDMI_PHY_QSERDES_TX_LX_RES_CODE_LANE_OFFSET,
			0x00);
		hdmi_tx_chan_ग_लिखो(pll, i,
			REG_HDMI_PHY_QSERDES_TX_LX_TRAN_DRVR_EMP_EN,
			0x03);
		hdmi_tx_chan_ग_लिखो(pll, i,
			REG_HDMI_PHY_QSERDES_TX_LX_PARRATE_REC_DETECT_IDLE_EN,
			0x40);
		hdmi_tx_chan_ग_लिखो(pll, i,
				   REG_HDMI_PHY_QSERDES_TX_LX_HP_PD_ENABLES,
				   cfg.tx_lx_hp_pd_enables[i]);
	पूर्ण

	hdmi_phy_ग_लिखो(phy, REG_HDMI_8996_PHY_MODE, cfg.phy_mode);
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8996_PHY_PD_CTL, 0x1F);

	/*
	 * Ensure that vco configuration माला_लो flushed to hardware beक्रमe
	 * enabling the PLL
	 */
	wmb();

	वापस 0;
पूर्ण

अटल पूर्णांक hdmi_8996_phy_पढ़ोy_status(काष्ठा hdmi_phy *phy)
अणु
	u32 nb_tries = HDMI_PLL_POLL_MAX_READS;
	अचिन्हित दीर्घ समयout = HDMI_PLL_POLL_TIMEOUT_US;
	u32 status;
	पूर्णांक phy_पढ़ोy = 0;

	DBG("Waiting for PHY ready");

	जबतक (nb_tries--) अणु
		status = hdmi_phy_पढ़ो(phy, REG_HDMI_8996_PHY_STATUS);
		phy_पढ़ोy = status & BIT(0);

		अगर (phy_पढ़ोy)
			अवरोध;

		udelay(समयout);
	पूर्ण

	DBG("PHY is %sready", phy_पढ़ोy ? "" : "*not* ");

	वापस phy_पढ़ोy;
पूर्ण

अटल पूर्णांक hdmi_8996_pll_lock_status(काष्ठा hdmi_pll_8996 *pll)
अणु
	u32 status;
	पूर्णांक nb_tries = HDMI_PLL_POLL_MAX_READS;
	अचिन्हित दीर्घ समयout = HDMI_PLL_POLL_TIMEOUT_US;
	पूर्णांक pll_locked = 0;

	DBG("Waiting for PLL lock");

	जबतक (nb_tries--) अणु
		status = hdmi_pll_पढ़ो(pll,
				       REG_HDMI_PHY_QSERDES_COM_C_READY_STATUS);
		pll_locked = status & BIT(0);

		अगर (pll_locked)
			अवरोध;

		udelay(समयout);
	पूर्ण

	DBG("HDMI PLL is %slocked", pll_locked ? "" : "*not* ");

	वापस pll_locked;
पूर्ण

अटल पूर्णांक hdmi_8996_pll_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा hdmi_pll_8996 *pll = hw_clk_to_pll(hw);
	काष्ठा hdmi_phy *phy = pll_get_phy(pll);
	पूर्णांक i, ret = 0;

	hdmi_phy_ग_लिखो(phy, REG_HDMI_8996_PHY_CFG, 0x1);
	udelay(100);

	hdmi_phy_ग_लिखो(phy, REG_HDMI_8996_PHY_CFG, 0x19);
	udelay(100);

	ret = hdmi_8996_pll_lock_status(pll);
	अगर (!ret)
		वापस ret;

	क्रम (i = 0; i < HDMI_NUM_TX_CHANNEL; i++)
		hdmi_tx_chan_ग_लिखो(pll, i,
			REG_HDMI_PHY_QSERDES_TX_LX_HIGHZ_TRANSCEIVEREN_BIAS_DRVR_EN,
			0x6F);

	/* Disable SSC */
	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_SSC_PER1, 0x0);
	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_SSC_PER2, 0x0);
	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_SSC_STEP_SIZE1, 0x0);
	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_SSC_STEP_SIZE2, 0x0);
	hdmi_pll_ग_लिखो(pll, REG_HDMI_PHY_QSERDES_COM_SSC_EN_CENTER, 0x2);

	ret = hdmi_8996_phy_पढ़ोy_status(phy);
	अगर (!ret)
		वापस ret;

	/* Restart the retiming buffer */
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8996_PHY_CFG, 0x18);
	udelay(1);
	hdmi_phy_ग_लिखो(phy, REG_HDMI_8996_PHY_CFG, 0x19);

	वापस 0;
पूर्ण

अटल दीर्घ hdmi_8996_pll_round_rate(काष्ठा clk_hw *hw,
				     अचिन्हित दीर्घ rate,
				     अचिन्हित दीर्घ *parent_rate)
अणु
	अगर (rate < HDMI_PCLK_MIN_FREQ)
		वापस HDMI_PCLK_MIN_FREQ;
	अन्यथा अगर (rate > HDMI_PCLK_MAX_FREQ)
		वापस HDMI_PCLK_MAX_FREQ;
	अन्यथा
		वापस rate;
पूर्ण

अटल अचिन्हित दीर्घ hdmi_8996_pll_recalc_rate(काष्ठा clk_hw *hw,
					       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा hdmi_pll_8996 *pll = hw_clk_to_pll(hw);
	u64 fdata;
	u32 cmp1, cmp2, cmp3, pll_cmp;

	cmp1 = hdmi_pll_पढ़ो(pll, REG_HDMI_PHY_QSERDES_COM_LOCK_CMP1_MODE0);
	cmp2 = hdmi_pll_पढ़ो(pll, REG_HDMI_PHY_QSERDES_COM_LOCK_CMP2_MODE0);
	cmp3 = hdmi_pll_पढ़ो(pll, REG_HDMI_PHY_QSERDES_COM_LOCK_CMP3_MODE0);

	pll_cmp = cmp1 | (cmp2 << 8) | (cmp3 << 16);

	fdata = pll_cmp_to_fdata(pll_cmp + 1, parent_rate);

	करो_भाग(fdata, 10);

	वापस fdata;
पूर्ण

अटल व्योम hdmi_8996_pll_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा hdmi_pll_8996 *pll = hw_clk_to_pll(hw);
	काष्ठा hdmi_phy *phy = pll_get_phy(pll);

	hdmi_phy_ग_लिखो(phy, REG_HDMI_8996_PHY_CFG, 0x6);
	usleep_range(100, 150);
पूर्ण

अटल पूर्णांक hdmi_8996_pll_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा hdmi_pll_8996 *pll = hw_clk_to_pll(hw);
	u32 status;
	पूर्णांक pll_locked;

	status = hdmi_pll_पढ़ो(pll, REG_HDMI_PHY_QSERDES_COM_C_READY_STATUS);
	pll_locked = status & BIT(0);

	वापस pll_locked;
पूर्ण

अटल काष्ठा clk_ops hdmi_8996_pll_ops = अणु
	.set_rate = hdmi_8996_pll_set_clk_rate,
	.round_rate = hdmi_8996_pll_round_rate,
	.recalc_rate = hdmi_8996_pll_recalc_rate,
	.prepare = hdmi_8996_pll_prepare,
	.unprepare = hdmi_8996_pll_unprepare,
	.is_enabled = hdmi_8996_pll_is_enabled,
पूर्ण;

अटल स्थिर अक्षर * स्थिर hdmi_pll_parents[] = अणु
	"xo",
पूर्ण;

अटल काष्ठा clk_init_data pll_init = अणु
	.name = "hdmipll",
	.ops = &hdmi_8996_pll_ops,
	.parent_names = hdmi_pll_parents,
	.num_parents = ARRAY_SIZE(hdmi_pll_parents),
	.flags = CLK_IGNORE_UNUSED,
पूर्ण;

पूर्णांक msm_hdmi_pll_8996_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा hdmi_pll_8996 *pll;
	काष्ठा clk *clk;
	पूर्णांक i;

	pll = devm_kzalloc(dev, माप(*pll), GFP_KERNEL);
	अगर (!pll)
		वापस -ENOMEM;

	pll->pdev = pdev;

	pll->mmio_qserdes_com = msm_ioremap(pdev, "hdmi_pll", "HDMI_PLL");
	अगर (IS_ERR(pll->mmio_qserdes_com)) अणु
		DRM_DEV_ERROR(dev, "failed to map pll base\n");
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < HDMI_NUM_TX_CHANNEL; i++) अणु
		अक्षर name[32], label[32];

		snम_लिखो(name, माप(name), "hdmi_tx_l%d", i);
		snम_लिखो(label, माप(label), "HDMI_TX_L%d", i);

		pll->mmio_qserdes_tx[i] = msm_ioremap(pdev, name, label);
		अगर (IS_ERR(pll->mmio_qserdes_tx[i])) अणु
			DRM_DEV_ERROR(dev, "failed to map pll base\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	pll->clk_hw.init = &pll_init;

	clk = devm_clk_रेजिस्टर(dev, &pll->clk_hw);
	अगर (IS_ERR(clk)) अणु
		DRM_DEV_ERROR(dev, "failed to register pll clock\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर hdmi_phy_8996_reg_names[] = अणु
	"vddio",
	"vcca",
पूर्ण;

अटल स्थिर अक्षर * स्थिर hdmi_phy_8996_clk_names[] = अणु
	"iface", "ref",
पूर्ण;

स्थिर काष्ठा hdmi_phy_cfg msm_hdmi_phy_8996_cfg = अणु
	.type = MSM_HDMI_PHY_8996,
	.reg_names = hdmi_phy_8996_reg_names,
	.num_regs = ARRAY_SIZE(hdmi_phy_8996_reg_names),
	.clk_names = hdmi_phy_8996_clk_names,
	.num_clks = ARRAY_SIZE(hdmi_phy_8996_clk_names),
पूर्ण;
