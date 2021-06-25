<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 2018 Jernej Skrabec <jernej.skrabec@siol.net>
 */

#समावेश <linux/delay.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश "sun8i_dw_hdmi.h"

/*
 * Address can be actually any value. Here is set to same value as
 * it is set in BSP driver.
 */
#घोषणा I2C_ADDR	0x69

अटल स्थिर काष्ठा dw_hdmi_mpll_config sun50i_h6_mpll_cfg[] = अणु
	अणु
		30666000, अणु
			अणु 0x00b3, 0x0000 पूर्ण,
			अणु 0x2153, 0x0000 पूर्ण,
			अणु 0x40f3, 0x0000 पूर्ण,
		पूर्ण,
	पूर्ण,  अणु
		36800000, अणु
			अणु 0x00b3, 0x0000 पूर्ण,
			अणु 0x2153, 0x0000 पूर्ण,
			अणु 0x40a2, 0x0001 पूर्ण,
		पूर्ण,
	पूर्ण,  अणु
		46000000, अणु
			अणु 0x00b3, 0x0000 पूर्ण,
			अणु 0x2142, 0x0001 पूर्ण,
			अणु 0x40a2, 0x0001 पूर्ण,
		पूर्ण,
	पूर्ण,  अणु
		61333000, अणु
			अणु 0x0072, 0x0001 पूर्ण,
			अणु 0x2142, 0x0001 पूर्ण,
			अणु 0x40a2, 0x0001 पूर्ण,
		पूर्ण,
	पूर्ण,  अणु
		73600000, अणु
			अणु 0x0072, 0x0001 पूर्ण,
			अणु 0x2142, 0x0001 पूर्ण,
			अणु 0x4061, 0x0002 पूर्ण,
		पूर्ण,
	पूर्ण,  अणु
		92000000, अणु
			अणु 0x0072, 0x0001 पूर्ण,
			अणु 0x2145, 0x0002 पूर्ण,
			अणु 0x4061, 0x0002 पूर्ण,
		पूर्ण,
	पूर्ण,  अणु
		122666000, अणु
			अणु 0x0051, 0x0002 पूर्ण,
			अणु 0x2145, 0x0002 पूर्ण,
			अणु 0x4061, 0x0002 पूर्ण,
		पूर्ण,
	पूर्ण,  अणु
		147200000, अणु
			अणु 0x0051, 0x0002 पूर्ण,
			अणु 0x2145, 0x0002 पूर्ण,
			अणु 0x4064, 0x0003 पूर्ण,
		पूर्ण,
	पूर्ण,  अणु
		184000000, अणु
			अणु 0x0051, 0x0002 पूर्ण,
			अणु 0x214c, 0x0003 पूर्ण,
			अणु 0x4064, 0x0003 पूर्ण,
		पूर्ण,
	पूर्ण,  अणु
		226666000, अणु
			अणु 0x0040, 0x0003 पूर्ण,
			अणु 0x214c, 0x0003 पूर्ण,
			अणु 0x4064, 0x0003 पूर्ण,
		पूर्ण,
	पूर्ण,  अणु
		272000000, अणु
			अणु 0x0040, 0x0003 पूर्ण,
			अणु 0x214c, 0x0003 पूर्ण,
			अणु 0x5a64, 0x0003 पूर्ण,
		पूर्ण,
	पूर्ण,  अणु
		340000000, अणु
			अणु 0x0040, 0x0003 पूर्ण,
			अणु 0x3b4c, 0x0003 पूर्ण,
			अणु 0x5a64, 0x0003 पूर्ण,
		पूर्ण,
	पूर्ण,  अणु
		594000000, अणु
			अणु 0x1a40, 0x0003 पूर्ण,
			अणु 0x3b4c, 0x0003 पूर्ण,
			अणु 0x5a64, 0x0003 पूर्ण,
		पूर्ण,
	पूर्ण, अणु
		~0UL, अणु
			अणु 0x0000, 0x0000 पूर्ण,
			अणु 0x0000, 0x0000 पूर्ण,
			अणु 0x0000, 0x0000 पूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा dw_hdmi_curr_ctrl sun50i_h6_cur_ctr[] = अणु
	/* pixelclk    bpp8    bpp10   bpp12 */
	अणु 27000000,  अणु 0x0012, 0x0000, 0x0000 पूर्ण, पूर्ण,
	अणु 74250000,  अणु 0x0013, 0x001a, 0x001b पूर्ण, पूर्ण,
	अणु 148500000, अणु 0x0019, 0x0033, 0x0034 पूर्ण, पूर्ण,
	अणु 297000000, अणु 0x0019, 0x001b, 0x001b पूर्ण, पूर्ण,
	अणु 594000000, अणु 0x0010, 0x001b, 0x001b पूर्ण, पूर्ण,
	अणु ~0UL,      अणु 0x0000, 0x0000, 0x0000 पूर्ण, पूर्ण
पूर्ण;

अटल स्थिर काष्ठा dw_hdmi_phy_config sun50i_h6_phy_config[] = अणु
	/*pixelclk   symbol   term   vlev*/
	अणु 27000000,  0x8009, 0x0007, 0x02b0 पूर्ण,
	अणु 74250000,  0x8009, 0x0006, 0x022d पूर्ण,
	अणु 148500000, 0x8029, 0x0006, 0x0270 पूर्ण,
	अणु 297000000, 0x8039, 0x0005, 0x01ab पूर्ण,
	अणु 594000000, 0x8029, 0x0000, 0x008a पूर्ण,
	अणु ~0UL,	     0x0000, 0x0000, 0x0000पूर्ण
पूर्ण;

अटल पूर्णांक sun8i_hdmi_phy_config_a83t(काष्ठा dw_hdmi *hdmi,
				      काष्ठा sun8i_hdmi_phy *phy,
				      अचिन्हित पूर्णांक clk_rate)
अणु
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_REXT_CTRL_REG,
			   SUN8I_HDMI_PHY_REXT_CTRL_REXT_EN,
			   SUN8I_HDMI_PHY_REXT_CTRL_REXT_EN);

	/* घातer करोwn */
	dw_hdmi_phy_gen2_txpwron(hdmi, 0);
	dw_hdmi_phy_gen2_pddq(hdmi, 1);

	dw_hdmi_phy_reset(hdmi);

	dw_hdmi_phy_gen2_pddq(hdmi, 0);

	dw_hdmi_phy_i2c_set_addr(hdmi, I2C_ADDR);

	/*
	 * Values are taken from BSP HDMI driver. Although AW didn't
	 * release any करोcumentation, explanation of this values can
	 * be found in i.MX 6Dual/6Quad Reference Manual.
	 */
	अगर (clk_rate <= 27000000) अणु
		dw_hdmi_phy_i2c_ग_लिखो(hdmi, 0x01e0, 0x06);
		dw_hdmi_phy_i2c_ग_लिखो(hdmi, 0x0000, 0x15);
		dw_hdmi_phy_i2c_ग_लिखो(hdmi, 0x08da, 0x10);
		dw_hdmi_phy_i2c_ग_लिखो(hdmi, 0x0007, 0x19);
		dw_hdmi_phy_i2c_ग_लिखो(hdmi, 0x0318, 0x0e);
		dw_hdmi_phy_i2c_ग_लिखो(hdmi, 0x8009, 0x09);
	पूर्ण अन्यथा अगर (clk_rate <= 74250000) अणु
		dw_hdmi_phy_i2c_ग_लिखो(hdmi, 0x0540, 0x06);
		dw_hdmi_phy_i2c_ग_लिखो(hdmi, 0x0005, 0x15);
		dw_hdmi_phy_i2c_ग_लिखो(hdmi, 0x0000, 0x10);
		dw_hdmi_phy_i2c_ग_लिखो(hdmi, 0x0007, 0x19);
		dw_hdmi_phy_i2c_ग_लिखो(hdmi, 0x02b5, 0x0e);
		dw_hdmi_phy_i2c_ग_लिखो(hdmi, 0x8009, 0x09);
	पूर्ण अन्यथा अगर (clk_rate <= 148500000) अणु
		dw_hdmi_phy_i2c_ग_लिखो(hdmi, 0x04a0, 0x06);
		dw_hdmi_phy_i2c_ग_लिखो(hdmi, 0x000a, 0x15);
		dw_hdmi_phy_i2c_ग_लिखो(hdmi, 0x0000, 0x10);
		dw_hdmi_phy_i2c_ग_लिखो(hdmi, 0x0002, 0x19);
		dw_hdmi_phy_i2c_ग_लिखो(hdmi, 0x0021, 0x0e);
		dw_hdmi_phy_i2c_ग_लिखो(hdmi, 0x8029, 0x09);
	पूर्ण अन्यथा अणु
		dw_hdmi_phy_i2c_ग_लिखो(hdmi, 0x0000, 0x06);
		dw_hdmi_phy_i2c_ग_लिखो(hdmi, 0x000f, 0x15);
		dw_hdmi_phy_i2c_ग_लिखो(hdmi, 0x0000, 0x10);
		dw_hdmi_phy_i2c_ग_लिखो(hdmi, 0x0002, 0x19);
		dw_hdmi_phy_i2c_ग_लिखो(hdmi, 0x0000, 0x0e);
		dw_hdmi_phy_i2c_ग_लिखो(hdmi, 0x802b, 0x09);
	पूर्ण

	dw_hdmi_phy_i2c_ग_लिखो(hdmi, 0x0000, 0x1e);
	dw_hdmi_phy_i2c_ग_लिखो(hdmi, 0x0000, 0x13);
	dw_hdmi_phy_i2c_ग_लिखो(hdmi, 0x0000, 0x17);

	dw_hdmi_phy_gen2_txpwron(hdmi, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक sun8i_hdmi_phy_config_h3(काष्ठा dw_hdmi *hdmi,
				    काष्ठा sun8i_hdmi_phy *phy,
				    अचिन्हित पूर्णांक clk_rate)
अणु
	u32 pll_cfg1_init;
	u32 pll_cfg2_init;
	u32 ana_cfg1_end;
	u32 ana_cfg2_init;
	u32 ana_cfg3_init;
	u32 b_offset = 0;
	u32 val;

	/* bandwidth / frequency independent settings */

	pll_cfg1_init = SUN8I_HDMI_PHY_PLL_CFG1_LDO2_EN |
			SUN8I_HDMI_PHY_PLL_CFG1_LDO1_EN |
			SUN8I_HDMI_PHY_PLL_CFG1_LDO_VSET(7) |
			SUN8I_HDMI_PHY_PLL_CFG1_UNKNOWN(1) |
			SUN8I_HDMI_PHY_PLL_CFG1_PLLDBEN |
			SUN8I_HDMI_PHY_PLL_CFG1_CS |
			SUN8I_HDMI_PHY_PLL_CFG1_CP_S(2) |
			SUN8I_HDMI_PHY_PLL_CFG1_CNT_INT(63) |
			SUN8I_HDMI_PHY_PLL_CFG1_BWS;

	pll_cfg2_init = SUN8I_HDMI_PHY_PLL_CFG2_SV_H |
			SUN8I_HDMI_PHY_PLL_CFG2_VCOGAIN_EN |
			SUN8I_HDMI_PHY_PLL_CFG2_SDIV2;

	ana_cfg1_end = SUN8I_HDMI_PHY_ANA_CFG1_REG_SVBH(1) |
		       SUN8I_HDMI_PHY_ANA_CFG1_AMP_OPT |
		       SUN8I_HDMI_PHY_ANA_CFG1_EMP_OPT |
		       SUN8I_HDMI_PHY_ANA_CFG1_AMPCK_OPT |
		       SUN8I_HDMI_PHY_ANA_CFG1_EMPCK_OPT |
		       SUN8I_HDMI_PHY_ANA_CFG1_ENRCAL |
		       SUN8I_HDMI_PHY_ANA_CFG1_ENCALOG |
		       SUN8I_HDMI_PHY_ANA_CFG1_REG_SCKTMDS |
		       SUN8I_HDMI_PHY_ANA_CFG1_TMDSCLK_EN |
		       SUN8I_HDMI_PHY_ANA_CFG1_TXEN_MASK |
		       SUN8I_HDMI_PHY_ANA_CFG1_TXEN_ALL |
		       SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDSCLK |
		       SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDS2 |
		       SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDS1 |
		       SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDS0 |
		       SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDS2 |
		       SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDS1 |
		       SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDS0 |
		       SUN8I_HDMI_PHY_ANA_CFG1_CKEN |
		       SUN8I_HDMI_PHY_ANA_CFG1_LDOEN |
		       SUN8I_HDMI_PHY_ANA_CFG1_ENVBS |
		       SUN8I_HDMI_PHY_ANA_CFG1_ENBI;

	ana_cfg2_init = SUN8I_HDMI_PHY_ANA_CFG2_M_EN |
			SUN8I_HDMI_PHY_ANA_CFG2_REG_DENCK |
			SUN8I_HDMI_PHY_ANA_CFG2_REG_DEN |
			SUN8I_HDMI_PHY_ANA_CFG2_REG_CKSS(1) |
			SUN8I_HDMI_PHY_ANA_CFG2_REG_CSMPS(1);

	ana_cfg3_init = SUN8I_HDMI_PHY_ANA_CFG3_REG_WIRE(0x3e0) |
			SUN8I_HDMI_PHY_ANA_CFG3_SDAEN |
			SUN8I_HDMI_PHY_ANA_CFG3_SCLEN;

	/* bandwidth / frequency dependent settings */
	अगर (clk_rate <= 27000000) अणु
		pll_cfg1_init |= SUN8I_HDMI_PHY_PLL_CFG1_HV_IS_33 |
				 SUN8I_HDMI_PHY_PLL_CFG1_CNT_INT(32);
		pll_cfg2_init |= SUN8I_HDMI_PHY_PLL_CFG2_VCO_S(4) |
				 SUN8I_HDMI_PHY_PLL_CFG2_S(4);
		ana_cfg1_end |= SUN8I_HDMI_PHY_ANA_CFG1_REG_CALSW;
		ana_cfg2_init |= SUN8I_HDMI_PHY_ANA_CFG2_REG_SLV(4) |
				 SUN8I_HDMI_PHY_ANA_CFG2_REG_RESDI(phy->rcal);
		ana_cfg3_init |= SUN8I_HDMI_PHY_ANA_CFG3_REG_AMPCK(3) |
				 SUN8I_HDMI_PHY_ANA_CFG3_REG_AMP(5);
	पूर्ण अन्यथा अगर (clk_rate <= 74250000) अणु
		pll_cfg1_init |= SUN8I_HDMI_PHY_PLL_CFG1_HV_IS_33 |
				 SUN8I_HDMI_PHY_PLL_CFG1_CNT_INT(32);
		pll_cfg2_init |= SUN8I_HDMI_PHY_PLL_CFG2_VCO_S(4) |
				 SUN8I_HDMI_PHY_PLL_CFG2_S(5);
		ana_cfg1_end |= SUN8I_HDMI_PHY_ANA_CFG1_REG_CALSW;
		ana_cfg2_init |= SUN8I_HDMI_PHY_ANA_CFG2_REG_SLV(4) |
				 SUN8I_HDMI_PHY_ANA_CFG2_REG_RESDI(phy->rcal);
		ana_cfg3_init |= SUN8I_HDMI_PHY_ANA_CFG3_REG_AMPCK(5) |
				 SUN8I_HDMI_PHY_ANA_CFG3_REG_AMP(7);
	पूर्ण अन्यथा अगर (clk_rate <= 148500000) अणु
		pll_cfg1_init |= SUN8I_HDMI_PHY_PLL_CFG1_HV_IS_33 |
				 SUN8I_HDMI_PHY_PLL_CFG1_CNT_INT(32);
		pll_cfg2_init |= SUN8I_HDMI_PHY_PLL_CFG2_VCO_S(4) |
				 SUN8I_HDMI_PHY_PLL_CFG2_S(6);
		ana_cfg2_init |= SUN8I_HDMI_PHY_ANA_CFG2_REG_BIGSWCK |
				 SUN8I_HDMI_PHY_ANA_CFG2_REG_BIGSW |
				 SUN8I_HDMI_PHY_ANA_CFG2_REG_SLV(2);
		ana_cfg3_init |= SUN8I_HDMI_PHY_ANA_CFG3_REG_AMPCK(7) |
				 SUN8I_HDMI_PHY_ANA_CFG3_REG_AMP(9);
	पूर्ण अन्यथा अणु
		b_offset = 2;
		pll_cfg1_init |= SUN8I_HDMI_PHY_PLL_CFG1_CNT_INT(63);
		pll_cfg2_init |= SUN8I_HDMI_PHY_PLL_CFG2_VCO_S(6) |
				 SUN8I_HDMI_PHY_PLL_CFG2_S(7);
		ana_cfg2_init |= SUN8I_HDMI_PHY_ANA_CFG2_REG_BIGSWCK |
				 SUN8I_HDMI_PHY_ANA_CFG2_REG_BIGSW |
				 SUN8I_HDMI_PHY_ANA_CFG2_REG_SLV(4);
		ana_cfg3_init |= SUN8I_HDMI_PHY_ANA_CFG3_REG_AMPCK(9) |
				 SUN8I_HDMI_PHY_ANA_CFG3_REG_AMP(13) |
				 SUN8I_HDMI_PHY_ANA_CFG3_REG_EMP(3);
	पूर्ण

	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_ANA_CFG1_REG,
			   SUN8I_HDMI_PHY_ANA_CFG1_TXEN_MASK, 0);

	/*
	 * NOTE: We have to be careful not to overग_लिखो PHY parent
	 * घड़ी selection bit and घड़ी भागider.
	 */
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_PLL_CFG1_REG,
			   (u32)~SUN8I_HDMI_PHY_PLL_CFG1_CKIN_SEL_MSK,
			   pll_cfg1_init);
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_PLL_CFG2_REG,
			   (u32)~SUN8I_HDMI_PHY_PLL_CFG2_PREDIV_MSK,
			   pll_cfg2_init);
	usleep_range(10000, 15000);
	regmap_ग_लिखो(phy->regs, SUN8I_HDMI_PHY_PLL_CFG3_REG,
		     SUN8I_HDMI_PHY_PLL_CFG3_SOUT_DIV2);
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_PLL_CFG1_REG,
			   SUN8I_HDMI_PHY_PLL_CFG1_PLLEN,
			   SUN8I_HDMI_PHY_PLL_CFG1_PLLEN);
	msleep(100);

	/* get B value */
	regmap_पढ़ो(phy->regs, SUN8I_HDMI_PHY_ANA_STS_REG, &val);
	val = (val & SUN8I_HDMI_PHY_ANA_STS_B_OUT_MSK) >>
		SUN8I_HDMI_PHY_ANA_STS_B_OUT_SHIFT;
	val = min(val + b_offset, (u32)0x3f);

	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_PLL_CFG1_REG,
			   SUN8I_HDMI_PHY_PLL_CFG1_REG_OD1 |
			   SUN8I_HDMI_PHY_PLL_CFG1_REG_OD,
			   SUN8I_HDMI_PHY_PLL_CFG1_REG_OD1 |
			   SUN8I_HDMI_PHY_PLL_CFG1_REG_OD);
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_PLL_CFG1_REG,
			   SUN8I_HDMI_PHY_PLL_CFG1_B_IN_MSK,
			   val << SUN8I_HDMI_PHY_PLL_CFG1_B_IN_SHIFT);
	msleep(100);
	regmap_ग_लिखो(phy->regs, SUN8I_HDMI_PHY_ANA_CFG1_REG, ana_cfg1_end);
	regmap_ग_लिखो(phy->regs, SUN8I_HDMI_PHY_ANA_CFG2_REG, ana_cfg2_init);
	regmap_ग_लिखो(phy->regs, SUN8I_HDMI_PHY_ANA_CFG3_REG, ana_cfg3_init);

	वापस 0;
पूर्ण

अटल पूर्णांक sun8i_hdmi_phy_config(काष्ठा dw_hdmi *hdmi, व्योम *data,
				 स्थिर काष्ठा drm_display_info *display,
				 स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा sun8i_hdmi_phy *phy = (काष्ठा sun8i_hdmi_phy *)data;
	u32 val = 0;

	अगर (mode->flags & DRM_MODE_FLAG_NHSYNC)
		val |= SUN8I_HDMI_PHY_DBG_CTRL_POL_NHSYNC;

	अगर (mode->flags & DRM_MODE_FLAG_NVSYNC)
		val |= SUN8I_HDMI_PHY_DBG_CTRL_POL_NVSYNC;

	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_DBG_CTRL_REG,
			   SUN8I_HDMI_PHY_DBG_CTRL_POL_MASK, val);

	अगर (phy->variant->has_phy_clk)
		clk_set_rate(phy->clk_phy, mode->crtc_घड़ी * 1000);

	वापस phy->variant->phy_config(hdmi, phy, mode->crtc_घड़ी * 1000);
पूर्ण;

अटल व्योम sun8i_hdmi_phy_disable_a83t(काष्ठा dw_hdmi *hdmi,
					काष्ठा sun8i_hdmi_phy *phy)
अणु
	dw_hdmi_phy_gen2_txpwron(hdmi, 0);
	dw_hdmi_phy_gen2_pddq(hdmi, 1);

	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_REXT_CTRL_REG,
			   SUN8I_HDMI_PHY_REXT_CTRL_REXT_EN, 0);
पूर्ण

अटल व्योम sun8i_hdmi_phy_disable_h3(काष्ठा dw_hdmi *hdmi,
				      काष्ठा sun8i_hdmi_phy *phy)
अणु
	regmap_ग_लिखो(phy->regs, SUN8I_HDMI_PHY_ANA_CFG1_REG,
		     SUN8I_HDMI_PHY_ANA_CFG1_LDOEN |
		     SUN8I_HDMI_PHY_ANA_CFG1_ENVBS |
		     SUN8I_HDMI_PHY_ANA_CFG1_ENBI);
	regmap_ग_लिखो(phy->regs, SUN8I_HDMI_PHY_PLL_CFG1_REG, 0);
पूर्ण

अटल व्योम sun8i_hdmi_phy_disable(काष्ठा dw_hdmi *hdmi, व्योम *data)
अणु
	काष्ठा sun8i_hdmi_phy *phy = (काष्ठा sun8i_hdmi_phy *)data;

	phy->variant->phy_disable(hdmi, phy);
पूर्ण

अटल स्थिर काष्ठा dw_hdmi_phy_ops sun8i_hdmi_phy_ops = अणु
	.init = &sun8i_hdmi_phy_config,
	.disable = &sun8i_hdmi_phy_disable,
	.पढ़ो_hpd = &dw_hdmi_phy_पढ़ो_hpd,
	.update_hpd = &dw_hdmi_phy_update_hpd,
	.setup_hpd = &dw_hdmi_phy_setup_hpd,
पूर्ण;

अटल व्योम sun8i_hdmi_phy_unlock(काष्ठा sun8i_hdmi_phy *phy)
अणु
	/* enable पढ़ो access to HDMI controller */
	regmap_ग_लिखो(phy->regs, SUN8I_HDMI_PHY_READ_EN_REG,
		     SUN8I_HDMI_PHY_READ_EN_MAGIC);

	/* unscramble रेजिस्टर offsets */
	regmap_ग_लिखो(phy->regs, SUN8I_HDMI_PHY_UNSCRAMBLE_REG,
		     SUN8I_HDMI_PHY_UNSCRAMBLE_MAGIC);
पूर्ण

अटल व्योम sun50i_hdmi_phy_init_h6(काष्ठा sun8i_hdmi_phy *phy)
अणु
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_REXT_CTRL_REG,
			   SUN8I_HDMI_PHY_REXT_CTRL_REXT_EN,
			   SUN8I_HDMI_PHY_REXT_CTRL_REXT_EN);

	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_REXT_CTRL_REG,
			   0xffff0000, 0x80c00000);
पूर्ण

अटल व्योम sun8i_hdmi_phy_init_a83t(काष्ठा sun8i_hdmi_phy *phy)
अणु
	sun8i_hdmi_phy_unlock(phy);

	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_DBG_CTRL_REG,
			   SUN8I_HDMI_PHY_DBG_CTRL_PX_LOCK,
			   SUN8I_HDMI_PHY_DBG_CTRL_PX_LOCK);

	/*
	 * Set PHY I2C address. It must match to the address set by
	 * dw_hdmi_phy_set_slave_addr().
	 */
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_DBG_CTRL_REG,
			   SUN8I_HDMI_PHY_DBG_CTRL_ADDR_MASK,
			   SUN8I_HDMI_PHY_DBG_CTRL_ADDR(I2C_ADDR));
पूर्ण

अटल व्योम sun8i_hdmi_phy_init_h3(काष्ठा sun8i_hdmi_phy *phy)
अणु
	अचिन्हित पूर्णांक val;

	sun8i_hdmi_phy_unlock(phy);

	regmap_ग_लिखो(phy->regs, SUN8I_HDMI_PHY_ANA_CFG1_REG, 0);
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_ANA_CFG1_REG,
			   SUN8I_HDMI_PHY_ANA_CFG1_ENBI,
			   SUN8I_HDMI_PHY_ANA_CFG1_ENBI);
	udelay(5);
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_ANA_CFG1_REG,
			   SUN8I_HDMI_PHY_ANA_CFG1_TMDSCLK_EN,
			   SUN8I_HDMI_PHY_ANA_CFG1_TMDSCLK_EN);
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_ANA_CFG1_REG,
			   SUN8I_HDMI_PHY_ANA_CFG1_ENVBS,
			   SUN8I_HDMI_PHY_ANA_CFG1_ENVBS);
	usleep_range(10, 20);
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_ANA_CFG1_REG,
			   SUN8I_HDMI_PHY_ANA_CFG1_LDOEN,
			   SUN8I_HDMI_PHY_ANA_CFG1_LDOEN);
	udelay(5);
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_ANA_CFG1_REG,
			   SUN8I_HDMI_PHY_ANA_CFG1_CKEN,
			   SUN8I_HDMI_PHY_ANA_CFG1_CKEN);
	usleep_range(40, 100);
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_ANA_CFG1_REG,
			   SUN8I_HDMI_PHY_ANA_CFG1_ENRCAL,
			   SUN8I_HDMI_PHY_ANA_CFG1_ENRCAL);
	usleep_range(100, 200);
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_ANA_CFG1_REG,
			   SUN8I_HDMI_PHY_ANA_CFG1_ENCALOG,
			   SUN8I_HDMI_PHY_ANA_CFG1_ENCALOG);
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_ANA_CFG1_REG,
			   SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDS0 |
			   SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDS1 |
			   SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDS2,
			   SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDS0 |
			   SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDS1 |
			   SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDS2);

	/* रुको क्रम calibration to finish */
	regmap_पढ़ो_poll_समयout(phy->regs, SUN8I_HDMI_PHY_ANA_STS_REG, val,
				 (val & SUN8I_HDMI_PHY_ANA_STS_RCALEND2D),
				 100, 2000);

	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_ANA_CFG1_REG,
			   SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDSCLK,
			   SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDSCLK);
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_ANA_CFG1_REG,
			   SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDS0 |
			   SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDS1 |
			   SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDS2 |
			   SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDSCLK,
			   SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDS0 |
			   SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDS1 |
			   SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDS2 |
			   SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDSCLK);

	/* enable DDC communication */
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_ANA_CFG3_REG,
			   SUN8I_HDMI_PHY_ANA_CFG3_SCLEN |
			   SUN8I_HDMI_PHY_ANA_CFG3_SDAEN,
			   SUN8I_HDMI_PHY_ANA_CFG3_SCLEN |
			   SUN8I_HDMI_PHY_ANA_CFG3_SDAEN);

	/* reset PHY PLL घड़ी parent */
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_PLL_CFG1_REG,
			   SUN8I_HDMI_PHY_PLL_CFG1_CKIN_SEL_MSK, 0);

	/* set HW control of CEC pins */
	regmap_ग_लिखो(phy->regs, SUN8I_HDMI_PHY_CEC_REG, 0);

	/* पढ़ो calibration data */
	regmap_पढ़ो(phy->regs, SUN8I_HDMI_PHY_ANA_STS_REG, &val);
	phy->rcal = (val & SUN8I_HDMI_PHY_ANA_STS_RCAL_MASK) >> 2;
पूर्ण

व्योम sun8i_hdmi_phy_init(काष्ठा sun8i_hdmi_phy *phy)
अणु
	phy->variant->phy_init(phy);
पूर्ण

व्योम sun8i_hdmi_phy_set_ops(काष्ठा sun8i_hdmi_phy *phy,
			    काष्ठा dw_hdmi_plat_data *plat_data)
अणु
	काष्ठा sun8i_hdmi_phy_variant *variant = phy->variant;

	अगर (variant->is_custom_phy) अणु
		plat_data->phy_ops = &sun8i_hdmi_phy_ops;
		plat_data->phy_name = "sun8i_dw_hdmi_phy";
		plat_data->phy_data = phy;
	पूर्ण अन्यथा अणु
		plat_data->mpll_cfg = variant->mpll_cfg;
		plat_data->cur_ctr = variant->cur_ctr;
		plat_data->phy_config = variant->phy_cfg;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config sun8i_hdmi_phy_regmap_config = अणु
	.reg_bits	= 32,
	.val_bits	= 32,
	.reg_stride	= 4,
	.max_रेजिस्टर	= SUN8I_HDMI_PHY_CEC_REG,
	.name		= "phy"
पूर्ण;

अटल स्थिर काष्ठा sun8i_hdmi_phy_variant sun8i_a83t_hdmi_phy = अणु
	.is_custom_phy = true,
	.phy_init = &sun8i_hdmi_phy_init_a83t,
	.phy_disable = &sun8i_hdmi_phy_disable_a83t,
	.phy_config = &sun8i_hdmi_phy_config_a83t,
पूर्ण;

अटल स्थिर काष्ठा sun8i_hdmi_phy_variant sun8i_h3_hdmi_phy = अणु
	.has_phy_clk = true,
	.is_custom_phy = true,
	.phy_init = &sun8i_hdmi_phy_init_h3,
	.phy_disable = &sun8i_hdmi_phy_disable_h3,
	.phy_config = &sun8i_hdmi_phy_config_h3,
पूर्ण;

अटल स्थिर काष्ठा sun8i_hdmi_phy_variant sun8i_r40_hdmi_phy = अणु
	.has_phy_clk = true,
	.has_second_pll = true,
	.is_custom_phy = true,
	.phy_init = &sun8i_hdmi_phy_init_h3,
	.phy_disable = &sun8i_hdmi_phy_disable_h3,
	.phy_config = &sun8i_hdmi_phy_config_h3,
पूर्ण;

अटल स्थिर काष्ठा sun8i_hdmi_phy_variant sun50i_a64_hdmi_phy = अणु
	.has_phy_clk = true,
	.is_custom_phy = true,
	.phy_init = &sun8i_hdmi_phy_init_h3,
	.phy_disable = &sun8i_hdmi_phy_disable_h3,
	.phy_config = &sun8i_hdmi_phy_config_h3,
पूर्ण;

अटल स्थिर काष्ठा sun8i_hdmi_phy_variant sun50i_h6_hdmi_phy = अणु
	.cur_ctr  = sun50i_h6_cur_ctr,
	.mpll_cfg = sun50i_h6_mpll_cfg,
	.phy_cfg  = sun50i_h6_phy_config,
	.phy_init = &sun50i_hdmi_phy_init_h6,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sun8i_hdmi_phy_of_table[] = अणु
	अणु
		.compatible = "allwinner,sun8i-a83t-hdmi-phy",
		.data = &sun8i_a83t_hdmi_phy,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun8i-h3-hdmi-phy",
		.data = &sun8i_h3_hdmi_phy,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun8i-r40-hdmi-phy",
		.data = &sun8i_r40_hdmi_phy,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun50i-a64-hdmi-phy",
		.data = &sun50i_a64_hdmi_phy,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun50i-h6-hdmi-phy",
		.data = &sun50i_h6_hdmi_phy,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

पूर्णांक sun8i_hdmi_phy_get(काष्ठा sun8i_dw_hdmi *hdmi, काष्ठा device_node *node)
अणु
	काष्ठा platक्रमm_device *pdev = of_find_device_by_node(node);
	काष्ठा sun8i_hdmi_phy *phy;

	अगर (!pdev)
		वापस -EPROBE_DEFER;

	phy = platक्रमm_get_drvdata(pdev);
	अगर (!phy)
		वापस -EPROBE_DEFER;

	hdmi->phy = phy;

	put_device(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक sun8i_hdmi_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा sun8i_hdmi_phy *phy;
	काष्ठा resource res;
	व्योम __iomem *regs;
	पूर्णांक ret;

	match = of_match_node(sun8i_hdmi_phy_of_table, node);
	अगर (!match) अणु
		dev_err(dev, "Incompatible HDMI PHY\n");
		वापस -EINVAL;
	पूर्ण

	phy = devm_kzalloc(dev, माप(*phy), GFP_KERNEL);
	अगर (!phy)
		वापस -ENOMEM;

	phy->variant = (काष्ठा sun8i_hdmi_phy_variant *)match->data;

	ret = of_address_to_resource(node, 0, &res);
	अगर (ret) अणु
		dev_err(dev, "phy: Couldn't get our resources\n");
		वापस ret;
	पूर्ण

	regs = devm_ioremap_resource(dev, &res);
	अगर (IS_ERR(regs)) अणु
		dev_err(dev, "Couldn't map the HDMI PHY registers\n");
		वापस PTR_ERR(regs);
	पूर्ण

	phy->regs = devm_regmap_init_mmio(dev, regs,
					  &sun8i_hdmi_phy_regmap_config);
	अगर (IS_ERR(phy->regs)) अणु
		dev_err(dev, "Couldn't create the HDMI PHY regmap\n");
		वापस PTR_ERR(phy->regs);
	पूर्ण

	phy->clk_bus = of_clk_get_by_name(node, "bus");
	अगर (IS_ERR(phy->clk_bus)) अणु
		dev_err(dev, "Could not get bus clock\n");
		वापस PTR_ERR(phy->clk_bus);
	पूर्ण

	phy->clk_mod = of_clk_get_by_name(node, "mod");
	अगर (IS_ERR(phy->clk_mod)) अणु
		dev_err(dev, "Could not get mod clock\n");
		ret = PTR_ERR(phy->clk_mod);
		जाओ err_put_clk_bus;
	पूर्ण

	अगर (phy->variant->has_phy_clk) अणु
		phy->clk_pll0 = of_clk_get_by_name(node, "pll-0");
		अगर (IS_ERR(phy->clk_pll0)) अणु
			dev_err(dev, "Could not get pll-0 clock\n");
			ret = PTR_ERR(phy->clk_pll0);
			जाओ err_put_clk_mod;
		पूर्ण

		अगर (phy->variant->has_second_pll) अणु
			phy->clk_pll1 = of_clk_get_by_name(node, "pll-1");
			अगर (IS_ERR(phy->clk_pll1)) अणु
				dev_err(dev, "Could not get pll-1 clock\n");
				ret = PTR_ERR(phy->clk_pll1);
				जाओ err_put_clk_pll0;
			पूर्ण
		पूर्ण
	पूर्ण

	phy->rst_phy = of_reset_control_get_shared(node, "phy");
	अगर (IS_ERR(phy->rst_phy)) अणु
		dev_err(dev, "Could not get phy reset control\n");
		ret = PTR_ERR(phy->rst_phy);
		जाओ err_put_clk_pll1;
	पूर्ण

	ret = reset_control_deनिश्चित(phy->rst_phy);
	अगर (ret) अणु
		dev_err(dev, "Cannot deassert phy reset control: %d\n", ret);
		जाओ err_put_rst_phy;
	पूर्ण

	ret = clk_prepare_enable(phy->clk_bus);
	अगर (ret) अणु
		dev_err(dev, "Cannot enable bus clock: %d\n", ret);
		जाओ err_deनिश्चित_rst_phy;
	पूर्ण

	ret = clk_prepare_enable(phy->clk_mod);
	अगर (ret) अणु
		dev_err(dev, "Cannot enable mod clock: %d\n", ret);
		जाओ err_disable_clk_bus;
	पूर्ण

	अगर (phy->variant->has_phy_clk) अणु
		ret = sun8i_phy_clk_create(phy, dev,
					   phy->variant->has_second_pll);
		अगर (ret) अणु
			dev_err(dev, "Couldn't create the PHY clock\n");
			जाओ err_disable_clk_mod;
		पूर्ण

		clk_prepare_enable(phy->clk_phy);
	पूर्ण

	platक्रमm_set_drvdata(pdev, phy);

	वापस 0;

err_disable_clk_mod:
	clk_disable_unprepare(phy->clk_mod);
err_disable_clk_bus:
	clk_disable_unprepare(phy->clk_bus);
err_deनिश्चित_rst_phy:
	reset_control_निश्चित(phy->rst_phy);
err_put_rst_phy:
	reset_control_put(phy->rst_phy);
err_put_clk_pll1:
	clk_put(phy->clk_pll1);
err_put_clk_pll0:
	clk_put(phy->clk_pll0);
err_put_clk_mod:
	clk_put(phy->clk_mod);
err_put_clk_bus:
	clk_put(phy->clk_bus);

	वापस ret;
पूर्ण

अटल पूर्णांक sun8i_hdmi_phy_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sun8i_hdmi_phy *phy = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(phy->clk_mod);
	clk_disable_unprepare(phy->clk_bus);
	clk_disable_unprepare(phy->clk_phy);

	reset_control_निश्चित(phy->rst_phy);

	reset_control_put(phy->rst_phy);

	clk_put(phy->clk_pll0);
	clk_put(phy->clk_pll1);
	clk_put(phy->clk_mod);
	clk_put(phy->clk_bus);
	वापस 0;
पूर्ण

काष्ठा platक्रमm_driver sun8i_hdmi_phy_driver = अणु
	.probe  = sun8i_hdmi_phy_probe,
	.हटाओ = sun8i_hdmi_phy_हटाओ,
	.driver = अणु
		.name = "sun8i-hdmi-phy",
		.of_match_table = sun8i_hdmi_phy_of_table,
	पूर्ण,
पूर्ण;
