<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>

#समावेश "dsi_phy.h"
#समावेश "dsi.xml.h"

/*
 * DSI PLL 28nm - घड़ी diagram (eg: DSI0):
 *
 *         dsi0analog_postभाग_clk
 *                             |         dsi0indirect_path_भाग2_clk
 *                             |          |
 *                   +------+  |  +----+  |  |\   dsi0byte_mux
 *  dsi0vco_clk --o--| DIV1 |--o--| /2 |--o--| \   |
 *                |  +------+     +----+     | m|  |  +----+
 *                |                          | u|--o--| /4 |-- dsi0pllbyte
 *                |                          | x|     +----+
 *                o--------------------------| /
 *                |                          |/
 *                |          +------+
 *                o----------| DIV3 |------------------------- dsi0pll
 *                           +------+
 */

#घोषणा POLL_MAX_READS			10
#घोषणा POLL_TIMEOUT_US		50

#घोषणा VCO_REF_CLK_RATE		19200000
#घोषणा VCO_MIN_RATE			350000000
#घोषणा VCO_MAX_RATE			750000000

/* v2.0.0 28nm LP implementation */
#घोषणा DSI_PHY_28NM_QUIRK_PHY_LP	BIT(0)

#घोषणा LPFR_LUT_SIZE			10
काष्ठा lpfr_cfg अणु
	अचिन्हित दीर्घ vco_rate;
	u32 resistance;
पूर्ण;

/* Loop filter resistance: */
अटल स्थिर काष्ठा lpfr_cfg lpfr_lut[LPFR_LUT_SIZE] = अणु
	अणु 479500000,  8 पूर्ण,
	अणु 480000000, 11 पूर्ण,
	अणु 575500000,  8 पूर्ण,
	अणु 576000000, 12 पूर्ण,
	अणु 610500000,  8 पूर्ण,
	अणु 659500000,  9 पूर्ण,
	अणु 671500000, 10 पूर्ण,
	अणु 672000000, 14 पूर्ण,
	अणु 708500000, 10 पूर्ण,
	अणु 750000000, 11 पूर्ण,
पूर्ण;

काष्ठा pll_28nm_cached_state अणु
	अचिन्हित दीर्घ vco_rate;
	u8 postभाग3;
	u8 postभाग1;
	u8 byte_mux;
पूर्ण;

काष्ठा dsi_pll_28nm अणु
	काष्ठा clk_hw clk_hw;

	काष्ठा msm_dsi_phy *phy;

	काष्ठा pll_28nm_cached_state cached_state;
पूर्ण;

#घोषणा to_pll_28nm(x)	container_of(x, काष्ठा dsi_pll_28nm, clk_hw)

अटल bool pll_28nm_poll_क्रम_पढ़ोy(काष्ठा dsi_pll_28nm *pll_28nm,
				u32 nb_tries, u32 समयout_us)
अणु
	bool pll_locked = false;
	u32 val;

	जबतक (nb_tries--) अणु
		val = dsi_phy_पढ़ो(pll_28nm->phy->pll_base + REG_DSI_28nm_PHY_PLL_STATUS);
		pll_locked = !!(val & DSI_28nm_PHY_PLL_STATUS_PLL_RDY);

		अगर (pll_locked)
			अवरोध;

		udelay(समयout_us);
	पूर्ण
	DBG("DSI PLL is %slocked", pll_locked ? "" : "*not* ");

	वापस pll_locked;
पूर्ण

अटल व्योम pll_28nm_software_reset(काष्ठा dsi_pll_28nm *pll_28nm)
अणु
	व्योम __iomem *base = pll_28nm->phy->pll_base;

	/*
	 * Add HW recommended delays after toggling the software
	 * reset bit off and back on.
	 */
	dsi_phy_ग_लिखो_udelay(base + REG_DSI_28nm_PHY_PLL_TEST_CFG,
			DSI_28nm_PHY_PLL_TEST_CFG_PLL_SW_RESET, 1);
	dsi_phy_ग_लिखो_udelay(base + REG_DSI_28nm_PHY_PLL_TEST_CFG, 0x00, 1);
पूर्ण

/*
 * Clock Callbacks
 */
अटल पूर्णांक dsi_pll_28nm_clk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा dsi_pll_28nm *pll_28nm = to_pll_28nm(hw);
	काष्ठा device *dev = &pll_28nm->phy->pdev->dev;
	व्योम __iomem *base = pll_28nm->phy->pll_base;
	अचिन्हित दीर्घ भाग_fbx1000, gen_vco_clk;
	u32 refclk_cfg, frac_n_mode, frac_n_value;
	u32 sdm_cfg0, sdm_cfg1, sdm_cfg2, sdm_cfg3;
	u32 cal_cfg10, cal_cfg11;
	u32 rem;
	पूर्णांक i;

	VERB("rate=%lu, parent's=%lu", rate, parent_rate);

	/* Force postभाग2 to be भाग-4 */
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_PLL_POSTDIV2_CFG, 3);

	/* Configure the Loop filter resistance */
	क्रम (i = 0; i < LPFR_LUT_SIZE; i++)
		अगर (rate <= lpfr_lut[i].vco_rate)
			अवरोध;
	अगर (i == LPFR_LUT_SIZE) अणु
		DRM_DEV_ERROR(dev, "unable to get loop filter resistance. vco=%lu\n",
				rate);
		वापस -EINVAL;
	पूर्ण
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_PLL_LPFR_CFG, lpfr_lut[i].resistance);

	/* Loop filter capacitance values : c1 and c2 */
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_PLL_LPFC1_CFG, 0x70);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_PLL_LPFC2_CFG, 0x15);

	rem = rate % VCO_REF_CLK_RATE;
	अगर (rem) अणु
		refclk_cfg = DSI_28nm_PHY_PLL_REFCLK_CFG_DBLR;
		frac_n_mode = 1;
		भाग_fbx1000 = rate / (VCO_REF_CLK_RATE / 500);
		gen_vco_clk = भाग_fbx1000 * (VCO_REF_CLK_RATE / 500);
	पूर्ण अन्यथा अणु
		refclk_cfg = 0x0;
		frac_n_mode = 0;
		भाग_fbx1000 = rate / (VCO_REF_CLK_RATE / 1000);
		gen_vco_clk = भाग_fbx1000 * (VCO_REF_CLK_RATE / 1000);
	पूर्ण

	DBG("refclk_cfg = %d", refclk_cfg);

	rem = भाग_fbx1000 % 1000;
	frac_n_value = (rem << 16) / 1000;

	DBG("div_fb = %lu", भाग_fbx1000);
	DBG("frac_n_value = %d", frac_n_value);

	DBG("Generated VCO Clock: %lu", gen_vco_clk);
	rem = 0;
	sdm_cfg1 = dsi_phy_पढ़ो(base + REG_DSI_28nm_PHY_PLL_SDM_CFG1);
	sdm_cfg1 &= ~DSI_28nm_PHY_PLL_SDM_CFG1_DC_OFFSET__MASK;
	अगर (frac_n_mode) अणु
		sdm_cfg0 = 0x0;
		sdm_cfg0 |= DSI_28nm_PHY_PLL_SDM_CFG0_BYP_DIV(0);
		sdm_cfg1 |= DSI_28nm_PHY_PLL_SDM_CFG1_DC_OFFSET(
				(u32)(((भाग_fbx1000 / 1000) & 0x3f) - 1));
		sdm_cfg3 = frac_n_value >> 8;
		sdm_cfg2 = frac_n_value & 0xff;
	पूर्ण अन्यथा अणु
		sdm_cfg0 = DSI_28nm_PHY_PLL_SDM_CFG0_BYP;
		sdm_cfg0 |= DSI_28nm_PHY_PLL_SDM_CFG0_BYP_DIV(
				(u32)(((भाग_fbx1000 / 1000) & 0x3f) - 1));
		sdm_cfg1 |= DSI_28nm_PHY_PLL_SDM_CFG1_DC_OFFSET(0);
		sdm_cfg2 = 0;
		sdm_cfg3 = 0;
	पूर्ण

	DBG("sdm_cfg0=%d", sdm_cfg0);
	DBG("sdm_cfg1=%d", sdm_cfg1);
	DBG("sdm_cfg2=%d", sdm_cfg2);
	DBG("sdm_cfg3=%d", sdm_cfg3);

	cal_cfg11 = (u32)(gen_vco_clk / (256 * 1000000));
	cal_cfg10 = (u32)((gen_vco_clk % (256 * 1000000)) / 1000000);
	DBG("cal_cfg10=%d, cal_cfg11=%d", cal_cfg10, cal_cfg11);

	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_PLL_CHGPUMP_CFG, 0x02);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_PLL_CAL_CFG3,    0x2b);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_PLL_CAL_CFG4,    0x06);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_PLL_LKDET_CFG2,  0x0d);

	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_PLL_SDM_CFG1, sdm_cfg1);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_PLL_SDM_CFG2,
		DSI_28nm_PHY_PLL_SDM_CFG2_FREQ_SEED_7_0(sdm_cfg2));
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_PLL_SDM_CFG3,
		DSI_28nm_PHY_PLL_SDM_CFG3_FREQ_SEED_15_8(sdm_cfg3));
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_PLL_SDM_CFG4, 0x00);

	/* Add hardware recommended delay क्रम correct PLL configuration */
	अगर (pll_28nm->phy->cfg->quirks & DSI_PHY_28NM_QUIRK_PHY_LP)
		udelay(1000);
	अन्यथा
		udelay(1);

	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_PLL_REFCLK_CFG, refclk_cfg);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_PLL_PWRGEN_CFG, 0x00);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_PLL_VCOLPF_CFG, 0x31);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_PLL_SDM_CFG0,   sdm_cfg0);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_PLL_CAL_CFG0,   0x12);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_PLL_CAL_CFG6,   0x30);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_PLL_CAL_CFG7,   0x00);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_PLL_CAL_CFG8,   0x60);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_PLL_CAL_CFG9,   0x00);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_PLL_CAL_CFG10,  cal_cfg10 & 0xff);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_PLL_CAL_CFG11,  cal_cfg11 & 0xff);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_PLL_EFUSE_CFG,  0x20);

	वापस 0;
पूर्ण

अटल पूर्णांक dsi_pll_28nm_clk_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा dsi_pll_28nm *pll_28nm = to_pll_28nm(hw);

	वापस pll_28nm_poll_क्रम_पढ़ोy(pll_28nm, POLL_MAX_READS,
					POLL_TIMEOUT_US);
पूर्ण

अटल अचिन्हित दीर्घ dsi_pll_28nm_clk_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा dsi_pll_28nm *pll_28nm = to_pll_28nm(hw);
	व्योम __iomem *base = pll_28nm->phy->pll_base;
	u32 sdm0, द्विगुनr, sdm_byp_भाग;
	u32 sdm_dc_off, sdm_freq_seed, sdm2, sdm3;
	u32 ref_clk = VCO_REF_CLK_RATE;
	अचिन्हित दीर्घ vco_rate;

	VERB("parent_rate=%lu", parent_rate);

	/* Check to see अगर the ref clk द्विगुनr is enabled */
	द्विगुनr = dsi_phy_पढ़ो(base + REG_DSI_28nm_PHY_PLL_REFCLK_CFG) &
			DSI_28nm_PHY_PLL_REFCLK_CFG_DBLR;
	ref_clk += (द्विगुनr * VCO_REF_CLK_RATE);

	/* see अगर it is पूर्णांकeger mode or sdm mode */
	sdm0 = dsi_phy_पढ़ो(base + REG_DSI_28nm_PHY_PLL_SDM_CFG0);
	अगर (sdm0 & DSI_28nm_PHY_PLL_SDM_CFG0_BYP) अणु
		/* पूर्णांकeger mode */
		sdm_byp_भाग = FIELD(
				dsi_phy_पढ़ो(base + REG_DSI_28nm_PHY_PLL_SDM_CFG0),
				DSI_28nm_PHY_PLL_SDM_CFG0_BYP_DIV) + 1;
		vco_rate = ref_clk * sdm_byp_भाग;
	पूर्ण अन्यथा अणु
		/* sdm mode */
		sdm_dc_off = FIELD(
				dsi_phy_पढ़ो(base + REG_DSI_28nm_PHY_PLL_SDM_CFG1),
				DSI_28nm_PHY_PLL_SDM_CFG1_DC_OFFSET);
		DBG("sdm_dc_off = %d", sdm_dc_off);
		sdm2 = FIELD(dsi_phy_पढ़ो(base + REG_DSI_28nm_PHY_PLL_SDM_CFG2),
				DSI_28nm_PHY_PLL_SDM_CFG2_FREQ_SEED_7_0);
		sdm3 = FIELD(dsi_phy_पढ़ो(base + REG_DSI_28nm_PHY_PLL_SDM_CFG3),
				DSI_28nm_PHY_PLL_SDM_CFG3_FREQ_SEED_15_8);
		sdm_freq_seed = (sdm3 << 8) | sdm2;
		DBG("sdm_freq_seed = %d", sdm_freq_seed);

		vco_rate = (ref_clk * (sdm_dc_off + 1)) +
			mult_frac(ref_clk, sdm_freq_seed, BIT(16));
		DBG("vco rate = %lu", vco_rate);
	पूर्ण

	DBG("returning vco rate = %lu", vco_rate);

	वापस vco_rate;
पूर्ण

अटल पूर्णांक _dsi_pll_28nm_vco_prepare_hpm(काष्ठा dsi_pll_28nm *pll_28nm)
अणु
	काष्ठा device *dev = &pll_28nm->phy->pdev->dev;
	व्योम __iomem *base = pll_28nm->phy->pll_base;
	u32 max_पढ़ोs = 5, समयout_us = 100;
	bool locked;
	u32 val;
	पूर्णांक i;

	DBG("id=%d", pll_28nm->phy->id);

	pll_28nm_software_reset(pll_28nm);

	/*
	 * PLL घातer up sequence.
	 * Add necessary delays recommended by hardware.
	 */
	val = DSI_28nm_PHY_PLL_GLB_CFG_PLL_PWRDN_B;
	dsi_phy_ग_लिखो_udelay(base + REG_DSI_28nm_PHY_PLL_GLB_CFG, val, 1);

	val |= DSI_28nm_PHY_PLL_GLB_CFG_PLL_PWRGEN_PWRDN_B;
	dsi_phy_ग_लिखो_udelay(base + REG_DSI_28nm_PHY_PLL_GLB_CFG, val, 200);

	val |= DSI_28nm_PHY_PLL_GLB_CFG_PLL_LDO_PWRDN_B;
	dsi_phy_ग_लिखो_udelay(base + REG_DSI_28nm_PHY_PLL_GLB_CFG, val, 500);

	val |= DSI_28nm_PHY_PLL_GLB_CFG_PLL_ENABLE;
	dsi_phy_ग_लिखो_udelay(base + REG_DSI_28nm_PHY_PLL_GLB_CFG, val, 600);

	क्रम (i = 0; i < 2; i++) अणु
		/* DSI Uniphy lock detect setting */
		dsi_phy_ग_लिखो_udelay(base + REG_DSI_28nm_PHY_PLL_LKDET_CFG2,
				0x0c, 100);
		dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_PLL_LKDET_CFG2, 0x0d);

		/* poll क्रम PLL पढ़ोy status */
		locked = pll_28nm_poll_क्रम_पढ़ोy(pll_28nm,
						max_पढ़ोs, समयout_us);
		अगर (locked)
			अवरोध;

		pll_28nm_software_reset(pll_28nm);

		/*
		 * PLL घातer up sequence.
		 * Add necessary delays recommended by hardware.
		 */
		val = DSI_28nm_PHY_PLL_GLB_CFG_PLL_PWRDN_B;
		dsi_phy_ग_लिखो_udelay(base + REG_DSI_28nm_PHY_PLL_GLB_CFG, val, 1);

		val |= DSI_28nm_PHY_PLL_GLB_CFG_PLL_PWRGEN_PWRDN_B;
		dsi_phy_ग_लिखो_udelay(base + REG_DSI_28nm_PHY_PLL_GLB_CFG, val, 200);

		val |= DSI_28nm_PHY_PLL_GLB_CFG_PLL_LDO_PWRDN_B;
		dsi_phy_ग_लिखो_udelay(base + REG_DSI_28nm_PHY_PLL_GLB_CFG, val, 250);

		val &= ~DSI_28nm_PHY_PLL_GLB_CFG_PLL_LDO_PWRDN_B;
		dsi_phy_ग_लिखो_udelay(base + REG_DSI_28nm_PHY_PLL_GLB_CFG, val, 200);

		val |= DSI_28nm_PHY_PLL_GLB_CFG_PLL_LDO_PWRDN_B;
		dsi_phy_ग_लिखो_udelay(base + REG_DSI_28nm_PHY_PLL_GLB_CFG, val, 500);

		val |= DSI_28nm_PHY_PLL_GLB_CFG_PLL_ENABLE;
		dsi_phy_ग_लिखो_udelay(base + REG_DSI_28nm_PHY_PLL_GLB_CFG, val, 600);
	पूर्ण

	अगर (unlikely(!locked))
		DRM_DEV_ERROR(dev, "DSI PLL lock failed\n");
	अन्यथा
		DBG("DSI PLL Lock success");

	वापस locked ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक dsi_pll_28nm_vco_prepare_hpm(काष्ठा clk_hw *hw)
अणु
	काष्ठा dsi_pll_28nm *pll_28nm = to_pll_28nm(hw);
	पूर्णांक i, ret;

	अगर (unlikely(pll_28nm->phy->pll_on))
		वापस 0;

	क्रम (i = 0; i < 3; i++) अणु
		ret = _dsi_pll_28nm_vco_prepare_hpm(pll_28nm);
		अगर (!ret) अणु
			pll_28nm->phy->pll_on = true;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dsi_pll_28nm_vco_prepare_lp(काष्ठा clk_hw *hw)
अणु
	काष्ठा dsi_pll_28nm *pll_28nm = to_pll_28nm(hw);
	काष्ठा device *dev = &pll_28nm->phy->pdev->dev;
	व्योम __iomem *base = pll_28nm->phy->pll_base;
	bool locked;
	u32 max_पढ़ोs = 10, समयout_us = 50;
	u32 val;

	DBG("id=%d", pll_28nm->phy->id);

	अगर (unlikely(pll_28nm->phy->pll_on))
		वापस 0;

	pll_28nm_software_reset(pll_28nm);

	/*
	 * PLL घातer up sequence.
	 * Add necessary delays recommended by hardware.
	 */
	dsi_phy_ग_लिखो_ndelay(base + REG_DSI_28nm_PHY_PLL_CAL_CFG1, 0x34, 500);

	val = DSI_28nm_PHY_PLL_GLB_CFG_PLL_PWRDN_B;
	dsi_phy_ग_लिखो_ndelay(base + REG_DSI_28nm_PHY_PLL_GLB_CFG, val, 500);

	val |= DSI_28nm_PHY_PLL_GLB_CFG_PLL_PWRGEN_PWRDN_B;
	dsi_phy_ग_लिखो_ndelay(base + REG_DSI_28nm_PHY_PLL_GLB_CFG, val, 500);

	val |= DSI_28nm_PHY_PLL_GLB_CFG_PLL_LDO_PWRDN_B |
		DSI_28nm_PHY_PLL_GLB_CFG_PLL_ENABLE;
	dsi_phy_ग_लिखो_ndelay(base + REG_DSI_28nm_PHY_PLL_GLB_CFG, val, 500);

	/* DSI PLL toggle lock detect setting */
	dsi_phy_ग_लिखो_ndelay(base + REG_DSI_28nm_PHY_PLL_LKDET_CFG2, 0x04, 500);
	dsi_phy_ग_लिखो_udelay(base + REG_DSI_28nm_PHY_PLL_LKDET_CFG2, 0x05, 512);

	locked = pll_28nm_poll_क्रम_पढ़ोy(pll_28nm, max_पढ़ोs, समयout_us);

	अगर (unlikely(!locked)) अणु
		DRM_DEV_ERROR(dev, "DSI PLL lock failed\n");
		वापस -EINVAL;
	पूर्ण

	DBG("DSI PLL lock success");
	pll_28nm->phy->pll_on = true;

	वापस 0;
पूर्ण

अटल व्योम dsi_pll_28nm_vco_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा dsi_pll_28nm *pll_28nm = to_pll_28nm(hw);

	DBG("id=%d", pll_28nm->phy->id);

	अगर (unlikely(!pll_28nm->phy->pll_on))
		वापस;

	dsi_phy_ग_लिखो(pll_28nm->phy->pll_base + REG_DSI_28nm_PHY_PLL_GLB_CFG, 0x00);

	pll_28nm->phy->pll_on = false;
पूर्ण

अटल दीर्घ dsi_pll_28nm_clk_round_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ rate, अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा dsi_pll_28nm *pll_28nm = to_pll_28nm(hw);

	अगर      (rate < pll_28nm->phy->cfg->min_pll_rate)
		वापस  pll_28nm->phy->cfg->min_pll_rate;
	अन्यथा अगर (rate > pll_28nm->phy->cfg->max_pll_rate)
		वापस  pll_28nm->phy->cfg->max_pll_rate;
	अन्यथा
		वापस rate;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_ops_dsi_pll_28nm_vco_hpm = अणु
	.round_rate = dsi_pll_28nm_clk_round_rate,
	.set_rate = dsi_pll_28nm_clk_set_rate,
	.recalc_rate = dsi_pll_28nm_clk_recalc_rate,
	.prepare = dsi_pll_28nm_vco_prepare_hpm,
	.unprepare = dsi_pll_28nm_vco_unprepare,
	.is_enabled = dsi_pll_28nm_clk_is_enabled,
पूर्ण;

अटल स्थिर काष्ठा clk_ops clk_ops_dsi_pll_28nm_vco_lp = अणु
	.round_rate = dsi_pll_28nm_clk_round_rate,
	.set_rate = dsi_pll_28nm_clk_set_rate,
	.recalc_rate = dsi_pll_28nm_clk_recalc_rate,
	.prepare = dsi_pll_28nm_vco_prepare_lp,
	.unprepare = dsi_pll_28nm_vco_unprepare,
	.is_enabled = dsi_pll_28nm_clk_is_enabled,
पूर्ण;

/*
 * PLL Callbacks
 */

अटल व्योम dsi_28nm_pll_save_state(काष्ठा msm_dsi_phy *phy)
अणु
	काष्ठा dsi_pll_28nm *pll_28nm = to_pll_28nm(phy->vco_hw);
	काष्ठा pll_28nm_cached_state *cached_state = &pll_28nm->cached_state;
	व्योम __iomem *base = pll_28nm->phy->pll_base;

	cached_state->postभाग3 =
			dsi_phy_पढ़ो(base + REG_DSI_28nm_PHY_PLL_POSTDIV3_CFG);
	cached_state->postभाग1 =
			dsi_phy_पढ़ो(base + REG_DSI_28nm_PHY_PLL_POSTDIV1_CFG);
	cached_state->byte_mux = dsi_phy_पढ़ो(base + REG_DSI_28nm_PHY_PLL_VREG_CFG);
	अगर (dsi_pll_28nm_clk_is_enabled(phy->vco_hw))
		cached_state->vco_rate = clk_hw_get_rate(phy->vco_hw);
	अन्यथा
		cached_state->vco_rate = 0;
पूर्ण

अटल पूर्णांक dsi_28nm_pll_restore_state(काष्ठा msm_dsi_phy *phy)
अणु
	काष्ठा dsi_pll_28nm *pll_28nm = to_pll_28nm(phy->vco_hw);
	काष्ठा pll_28nm_cached_state *cached_state = &pll_28nm->cached_state;
	व्योम __iomem *base = pll_28nm->phy->pll_base;
	पूर्णांक ret;

	ret = dsi_pll_28nm_clk_set_rate(phy->vco_hw,
					cached_state->vco_rate, 0);
	अगर (ret) अणु
		DRM_DEV_ERROR(&pll_28nm->phy->pdev->dev,
			"restore vco rate failed. ret=%d\n", ret);
		वापस ret;
	पूर्ण

	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_PLL_POSTDIV3_CFG,
			cached_state->postभाग3);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_PLL_POSTDIV1_CFG,
			cached_state->postभाग1);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_PLL_VREG_CFG,
			cached_state->byte_mux);

	वापस 0;
पूर्ण

अटल पूर्णांक pll_28nm_रेजिस्टर(काष्ठा dsi_pll_28nm *pll_28nm, काष्ठा clk_hw **provided_घड़ीs)
अणु
	अक्षर clk_name[32], parent1[32], parent2[32], vco_name[32];
	काष्ठा clk_init_data vco_init = अणु
		.parent_names = (स्थिर अक्षर *[])अणु "xo" पूर्ण,
		.num_parents = 1,
		.name = vco_name,
		.flags = CLK_IGNORE_UNUSED,
	पूर्ण;
	काष्ठा device *dev = &pll_28nm->phy->pdev->dev;
	काष्ठा clk_hw *hw;
	पूर्णांक ret;

	DBG("%d", pll_28nm->phy->id);

	अगर (pll_28nm->phy->cfg->quirks & DSI_PHY_28NM_QUIRK_PHY_LP)
		vco_init.ops = &clk_ops_dsi_pll_28nm_vco_lp;
	अन्यथा
		vco_init.ops = &clk_ops_dsi_pll_28nm_vco_hpm;

	snम_लिखो(vco_name, 32, "dsi%dvco_clk", pll_28nm->phy->id);
	pll_28nm->clk_hw.init = &vco_init;
	ret = devm_clk_hw_रेजिस्टर(dev, &pll_28nm->clk_hw);
	अगर (ret)
		वापस ret;

	snम_लिखो(clk_name, 32, "dsi%danalog_postdiv_clk", pll_28nm->phy->id);
	snम_लिखो(parent1, 32, "dsi%dvco_clk", pll_28nm->phy->id);
	hw = devm_clk_hw_रेजिस्टर_भागider(dev, clk_name,
			parent1, CLK_SET_RATE_PARENT,
			pll_28nm->phy->pll_base +
			REG_DSI_28nm_PHY_PLL_POSTDIV1_CFG,
			0, 4, 0, शून्य);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);

	snम_लिखो(clk_name, 32, "dsi%dindirect_path_div2_clk", pll_28nm->phy->id);
	snम_लिखो(parent1, 32, "dsi%danalog_postdiv_clk", pll_28nm->phy->id);
	hw = devm_clk_hw_रेजिस्टर_fixed_factor(dev, clk_name,
			parent1, CLK_SET_RATE_PARENT,
			1, 2);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);

	snम_लिखो(clk_name, 32, "dsi%dpll", pll_28nm->phy->id);
	snम_लिखो(parent1, 32, "dsi%dvco_clk", pll_28nm->phy->id);
	hw = devm_clk_hw_रेजिस्टर_भागider(dev, clk_name,
				parent1, 0, pll_28nm->phy->pll_base +
				REG_DSI_28nm_PHY_PLL_POSTDIV3_CFG,
				0, 8, 0, शून्य);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);
	provided_घड़ीs[DSI_PIXEL_PLL_CLK] = hw;

	snम_लिखो(clk_name, 32, "dsi%dbyte_mux", pll_28nm->phy->id);
	snम_लिखो(parent1, 32, "dsi%dvco_clk", pll_28nm->phy->id);
	snम_लिखो(parent2, 32, "dsi%dindirect_path_div2_clk", pll_28nm->phy->id);
	hw = devm_clk_hw_रेजिस्टर_mux(dev, clk_name,
			((स्थिर अक्षर *[])अणु
				parent1, parent2
			पूर्ण), 2, CLK_SET_RATE_PARENT, pll_28nm->phy->pll_base +
			REG_DSI_28nm_PHY_PLL_VREG_CFG, 1, 1, 0, शून्य);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);

	snम_लिखो(clk_name, 32, "dsi%dpllbyte", pll_28nm->phy->id);
	snम_लिखो(parent1, 32, "dsi%dbyte_mux", pll_28nm->phy->id);
	hw = devm_clk_hw_रेजिस्टर_fixed_factor(dev, clk_name,
				parent1, CLK_SET_RATE_PARENT, 1, 4);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);
	provided_घड़ीs[DSI_BYTE_PLL_CLK] = hw;

	वापस 0;
पूर्ण

अटल पूर्णांक dsi_pll_28nm_init(काष्ठा msm_dsi_phy *phy)
अणु
	काष्ठा platक्रमm_device *pdev = phy->pdev;
	काष्ठा dsi_pll_28nm *pll_28nm;
	पूर्णांक ret;

	अगर (!pdev)
		वापस -ENODEV;

	pll_28nm = devm_kzalloc(&pdev->dev, माप(*pll_28nm), GFP_KERNEL);
	अगर (!pll_28nm)
		वापस -ENOMEM;

	pll_28nm->phy = phy;

	ret = pll_28nm_रेजिस्टर(pll_28nm, phy->provided_घड़ीs->hws);
	अगर (ret) अणु
		DRM_DEV_ERROR(&pdev->dev, "failed to register PLL: %d\n", ret);
		वापस ret;
	पूर्ण

	phy->vco_hw = &pll_28nm->clk_hw;

	वापस 0;
पूर्ण

अटल व्योम dsi_28nm_dphy_set_timing(काष्ठा msm_dsi_phy *phy,
		काष्ठा msm_dsi_dphy_timing *timing)
अणु
	व्योम __iomem *base = phy->base;

	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_TIMING_CTRL_0,
		DSI_28nm_PHY_TIMING_CTRL_0_CLK_ZERO(timing->clk_zero));
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_TIMING_CTRL_1,
		DSI_28nm_PHY_TIMING_CTRL_1_CLK_TRAIL(timing->clk_trail));
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_TIMING_CTRL_2,
		DSI_28nm_PHY_TIMING_CTRL_2_CLK_PREPARE(timing->clk_prepare));
	अगर (timing->clk_zero & BIT(8))
		dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_TIMING_CTRL_3,
			DSI_28nm_PHY_TIMING_CTRL_3_CLK_ZERO_8);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_TIMING_CTRL_4,
		DSI_28nm_PHY_TIMING_CTRL_4_HS_EXIT(timing->hs_निकास));
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_TIMING_CTRL_5,
		DSI_28nm_PHY_TIMING_CTRL_5_HS_ZERO(timing->hs_zero));
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_TIMING_CTRL_6,
		DSI_28nm_PHY_TIMING_CTRL_6_HS_PREPARE(timing->hs_prepare));
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_TIMING_CTRL_7,
		DSI_28nm_PHY_TIMING_CTRL_7_HS_TRAIL(timing->hs_trail));
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_TIMING_CTRL_8,
		DSI_28nm_PHY_TIMING_CTRL_8_HS_RQST(timing->hs_rqst));
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_TIMING_CTRL_9,
		DSI_28nm_PHY_TIMING_CTRL_9_TA_GO(timing->ta_go) |
		DSI_28nm_PHY_TIMING_CTRL_9_TA_SURE(timing->ta_sure));
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_TIMING_CTRL_10,
		DSI_28nm_PHY_TIMING_CTRL_10_TA_GET(timing->ta_get));
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_TIMING_CTRL_11,
		DSI_28nm_PHY_TIMING_CTRL_11_TRIG3_CMD(0));
पूर्ण

अटल व्योम dsi_28nm_phy_regulator_enable_dcdc(काष्ठा msm_dsi_phy *phy)
अणु
	व्योम __iomem *base = phy->reg_base;

	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_REGULATOR_CTRL_0, 0x0);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_REGULATOR_CAL_PWR_CFG, 1);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_REGULATOR_CTRL_5, 0);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_REGULATOR_CTRL_3, 0);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_REGULATOR_CTRL_2, 0x3);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_REGULATOR_CTRL_1, 0x9);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_REGULATOR_CTRL_0, 0x7);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_REGULATOR_CTRL_4, 0x20);
	dsi_phy_ग_लिखो(phy->base + REG_DSI_28nm_PHY_LDO_CNTRL, 0x00);
पूर्ण

अटल व्योम dsi_28nm_phy_regulator_enable_lकरो(काष्ठा msm_dsi_phy *phy)
अणु
	व्योम __iomem *base = phy->reg_base;

	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_REGULATOR_CTRL_0, 0x0);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_REGULATOR_CAL_PWR_CFG, 0);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_REGULATOR_CTRL_5, 0x7);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_REGULATOR_CTRL_3, 0);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_REGULATOR_CTRL_2, 0x1);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_REGULATOR_CTRL_1, 0x1);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_REGULATOR_CTRL_4, 0x20);

	अगर (phy->cfg->quirks & DSI_PHY_28NM_QUIRK_PHY_LP)
		dsi_phy_ग_लिखो(phy->base + REG_DSI_28nm_PHY_LDO_CNTRL, 0x05);
	अन्यथा
		dsi_phy_ग_लिखो(phy->base + REG_DSI_28nm_PHY_LDO_CNTRL, 0x0d);
पूर्ण

अटल व्योम dsi_28nm_phy_regulator_ctrl(काष्ठा msm_dsi_phy *phy, bool enable)
अणु
	अगर (!enable) अणु
		dsi_phy_ग_लिखो(phy->reg_base +
			      REG_DSI_28nm_PHY_REGULATOR_CAL_PWR_CFG, 0);
		वापस;
	पूर्ण

	अगर (phy->regulator_lकरो_mode)
		dsi_28nm_phy_regulator_enable_lकरो(phy);
	अन्यथा
		dsi_28nm_phy_regulator_enable_dcdc(phy);
पूर्ण

अटल पूर्णांक dsi_28nm_phy_enable(काष्ठा msm_dsi_phy *phy,
				काष्ठा msm_dsi_phy_clk_request *clk_req)
अणु
	काष्ठा msm_dsi_dphy_timing *timing = &phy->timing;
	पूर्णांक i;
	व्योम __iomem *base = phy->base;
	u32 val;

	DBG("");

	अगर (msm_dsi_dphy_timing_calc(timing, clk_req)) अणु
		DRM_DEV_ERROR(&phy->pdev->dev,
			"%s: D-PHY timing calculation failed\n", __func__);
		वापस -EINVAL;
	पूर्ण

	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_STRENGTH_0, 0xff);

	dsi_28nm_phy_regulator_ctrl(phy, true);

	dsi_28nm_dphy_set_timing(phy, timing);

	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_CTRL_1, 0x00);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_CTRL_0, 0x5f);

	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_STRENGTH_1, 0x6);

	क्रम (i = 0; i < 4; i++) अणु
		dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_LN_CFG_0(i), 0);
		dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_LN_CFG_1(i), 0);
		dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_LN_CFG_2(i), 0);
		dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_LN_CFG_3(i), 0);
		dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_LN_CFG_4(i), 0);
		dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_LN_TEST_DATAPATH(i), 0);
		dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_LN_DEBUG_SEL(i), 0);
		dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_LN_TEST_STR_0(i), 0x1);
		dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_LN_TEST_STR_1(i), 0x97);
	पूर्ण

	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_LNCK_CFG_4, 0);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_LNCK_CFG_1, 0xc0);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_LNCK_TEST_STR0, 0x1);
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_LNCK_TEST_STR1, 0xbb);

	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_CTRL_0, 0x5f);

	val = dsi_phy_पढ़ो(base + REG_DSI_28nm_PHY_GLBL_TEST_CTRL);
	अगर (phy->id == DSI_1 && phy->useहाल == MSM_DSI_PHY_SLAVE)
		val &= ~DSI_28nm_PHY_GLBL_TEST_CTRL_BITCLK_HS_SEL;
	अन्यथा
		val |= DSI_28nm_PHY_GLBL_TEST_CTRL_BITCLK_HS_SEL;
	dsi_phy_ग_लिखो(base + REG_DSI_28nm_PHY_GLBL_TEST_CTRL, val);

	वापस 0;
पूर्ण

अटल व्योम dsi_28nm_phy_disable(काष्ठा msm_dsi_phy *phy)
अणु
	dsi_phy_ग_लिखो(phy->base + REG_DSI_28nm_PHY_CTRL_0, 0);
	dsi_28nm_phy_regulator_ctrl(phy, false);

	/*
	 * Wait क्रम the रेजिस्टरs ग_लिखोs to complete in order to
	 * ensure that the phy is completely disabled
	 */
	wmb();
पूर्ण

स्थिर काष्ठा msm_dsi_phy_cfg dsi_phy_28nm_hpm_cfgs = अणु
	.has_phy_regulator = true,
	.reg_cfg = अणु
		.num = 1,
		.regs = अणु
			अणु"vddio", 100000, 100पूर्ण,
		पूर्ण,
	पूर्ण,
	.ops = अणु
		.enable = dsi_28nm_phy_enable,
		.disable = dsi_28nm_phy_disable,
		.pll_init = dsi_pll_28nm_init,
		.save_pll_state = dsi_28nm_pll_save_state,
		.restore_pll_state = dsi_28nm_pll_restore_state,
	पूर्ण,
	.min_pll_rate = VCO_MIN_RATE,
	.max_pll_rate = VCO_MAX_RATE,
	.io_start = अणु 0xfd922b00, 0xfd923100 पूर्ण,
	.num_dsi_phy = 2,
पूर्ण;

स्थिर काष्ठा msm_dsi_phy_cfg dsi_phy_28nm_hpm_famb_cfgs = अणु
	.has_phy_regulator = true,
	.reg_cfg = अणु
		.num = 1,
		.regs = अणु
			अणु"vddio", 100000, 100पूर्ण,
		पूर्ण,
	पूर्ण,
	.ops = अणु
		.enable = dsi_28nm_phy_enable,
		.disable = dsi_28nm_phy_disable,
		.pll_init = dsi_pll_28nm_init,
		.save_pll_state = dsi_28nm_pll_save_state,
		.restore_pll_state = dsi_28nm_pll_restore_state,
	पूर्ण,
	.min_pll_rate = VCO_MIN_RATE,
	.max_pll_rate = VCO_MAX_RATE,
	.io_start = अणु 0x1a94400, 0x1a96400 पूर्ण,
	.num_dsi_phy = 2,
पूर्ण;

स्थिर काष्ठा msm_dsi_phy_cfg dsi_phy_28nm_lp_cfgs = अणु
	.has_phy_regulator = true,
	.reg_cfg = अणु
		.num = 1,
		.regs = अणु
			अणु"vddio", 100000, 100पूर्ण,	/* 1.8 V */
		पूर्ण,
	पूर्ण,
	.ops = अणु
		.enable = dsi_28nm_phy_enable,
		.disable = dsi_28nm_phy_disable,
		.pll_init = dsi_pll_28nm_init,
		.save_pll_state = dsi_28nm_pll_save_state,
		.restore_pll_state = dsi_28nm_pll_restore_state,
	पूर्ण,
	.min_pll_rate = VCO_MIN_RATE,
	.max_pll_rate = VCO_MAX_RATE,
	.io_start = अणु 0x1a98500 पूर्ण,
	.num_dsi_phy = 1,
	.quirks = DSI_PHY_28NM_QUIRK_PHY_LP,
पूर्ण;

