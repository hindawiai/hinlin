<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (C) 2018 Jernej Skrabec <jernej.skrabec@siol.net>
 */

#अगर_अघोषित _SUN8I_DW_HDMI_H_
#घोषणा _SUN8I_DW_HDMI_H_

#समावेश <drm/bridge/dw_hdmi.h>
#समावेश <drm/drm_encoder.h>
#समावेश <linux/clk.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>

#घोषणा SUN8I_HDMI_PHY_DBG_CTRL_REG	0x0000
#घोषणा SUN8I_HDMI_PHY_DBG_CTRL_PX_LOCK		BIT(0)
#घोषणा SUN8I_HDMI_PHY_DBG_CTRL_POL_MASK	GENMASK(15, 8)
#घोषणा SUN8I_HDMI_PHY_DBG_CTRL_POL_NHSYNC	BIT(8)
#घोषणा SUN8I_HDMI_PHY_DBG_CTRL_POL_NVSYNC	BIT(9)
#घोषणा SUN8I_HDMI_PHY_DBG_CTRL_ADDR_MASK	GENMASK(23, 16)
#घोषणा SUN8I_HDMI_PHY_DBG_CTRL_ADDR(addr)	(addr << 16)

#घोषणा SUN8I_HDMI_PHY_REXT_CTRL_REG	0x0004
#घोषणा SUN8I_HDMI_PHY_REXT_CTRL_REXT_EN	BIT(31)

#घोषणा SUN8I_HDMI_PHY_READ_EN_REG	0x0010
#घोषणा SUN8I_HDMI_PHY_READ_EN_MAGIC		0x54524545

#घोषणा SUN8I_HDMI_PHY_UNSCRAMBLE_REG	0x0014
#घोषणा SUN8I_HDMI_PHY_UNSCRAMBLE_MAGIC		0x42494E47

#घोषणा SUN8I_HDMI_PHY_ANA_CFG1_REG	0x0020
#घोषणा SUN8I_HDMI_PHY_ANA_CFG1_REG_SWI		BIT(31)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG1_REG_PWEND	BIT(30)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG1_REG_PWENC	BIT(29)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG1_REG_CALSW	BIT(28)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG1_REG_SVRCAL(x)	((x) << 26)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG1_REG_SVBH(x)	((x) << 24)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG1_AMP_OPT		BIT(23)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG1_EMP_OPT		BIT(22)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG1_AMPCK_OPT	BIT(21)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG1_EMPCK_OPT	BIT(20)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG1_ENRCAL		BIT(19)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG1_ENCALOG		BIT(18)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG1_REG_SCKTMDS	BIT(17)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG1_TMDSCLK_EN	BIT(16)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG1_TXEN_MASK	GENMASK(15, 12)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG1_TXEN_ALL	(0xf << 12)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDSCLK	BIT(11)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDS2	BIT(10)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDS1	BIT(9)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDS0	BIT(8)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDSCLK	BIT(7)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDS2	BIT(6)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDS1	BIT(5)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDS0	BIT(4)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG1_CKEN		BIT(3)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG1_LDOEN		BIT(2)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG1_ENVBS		BIT(1)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG1_ENBI		BIT(0)

#घोषणा SUN8I_HDMI_PHY_ANA_CFG2_REG	0x0024
#घोषणा SUN8I_HDMI_PHY_ANA_CFG2_M_EN		BIT(31)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG2_PLLDBEN		BIT(30)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG2_SEN		BIT(29)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG2_REG_HPDPD	BIT(28)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG2_REG_HPDEN	BIT(27)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG2_REG_PLRCK	BIT(26)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG2_REG_PLR(x)	((x) << 23)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG2_REG_DENCK	BIT(22)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG2_REG_DEN		BIT(21)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG2_REG_CD(x)	((x) << 19)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG2_REG_CKSS(x)	((x) << 17)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG2_REG_BIGSWCK	BIT(16)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG2_REG_BIGSW	BIT(15)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG2_REG_CSMPS(x)	((x) << 13)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG2_REG_SLV(x)	((x) << 10)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG2_REG_BOOSTCK(x)	((x) << 8)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG2_REG_BOOST(x)	((x) << 6)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG2_REG_RESDI(x)	((x) << 0)

#घोषणा SUN8I_HDMI_PHY_ANA_CFG3_REG	0x0028
#घोषणा SUN8I_HDMI_PHY_ANA_CFG3_REG_SLOWCK(x)	((x) << 30)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG3_REG_SLOW(x)	((x) << 28)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG3_REG_WIRE(x)	((x) << 18)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG3_REG_AMPCK(x)	((x) << 14)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG3_REG_EMPCK(x)	((x) << 11)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG3_REG_AMP(x)	((x) << 7)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG3_REG_EMP(x)	((x) << 4)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG3_SDAPD		BIT(3)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG3_SDAEN		BIT(2)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG3_SCLPD		BIT(1)
#घोषणा SUN8I_HDMI_PHY_ANA_CFG3_SCLEN		BIT(0)

#घोषणा SUN8I_HDMI_PHY_PLL_CFG1_REG	0x002c
#घोषणा SUN8I_HDMI_PHY_PLL_CFG1_REG_OD1		BIT(31)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG1_REG_OD		BIT(30)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG1_LDO2_EN		BIT(29)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG1_LDO1_EN		BIT(28)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG1_HV_IS_33	BIT(27)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG1_CKIN_SEL_MSK	BIT(26)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG1_CKIN_SEL_SHIFT	26
#घोषणा SUN8I_HDMI_PHY_PLL_CFG1_PLLEN		BIT(25)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG1_LDO_VSET(x)	((x) << 22)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG1_UNKNOWN(x)	((x) << 20)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG1_PLLDBEN		BIT(19)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG1_CS		BIT(18)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG1_CP_S(x)		((x) << 13)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG1_CNT_INT(x)	((x) << 7)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG1_BWS		BIT(6)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG1_B_IN_MSK	GENMASK(5, 0)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG1_B_IN_SHIFT	0

#घोषणा SUN8I_HDMI_PHY_PLL_CFG2_REG	0x0030
#घोषणा SUN8I_HDMI_PHY_PLL_CFG2_SV_H		BIT(31)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG2_PDCLKSEL(x)	((x) << 29)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG2_CLKSTEP(x)	((x) << 27)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG2_PSET(x)		((x) << 24)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG2_PCLK_SEL	BIT(23)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG2_AUTOSYNC_DIS	BIT(22)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG2_VREG2_OUT_EN	BIT(21)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG2_VREG1_OUT_EN	BIT(20)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG2_VCOGAIN_EN	BIT(19)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG2_VCOGAIN(x)	((x) << 16)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG2_VCO_S(x)	((x) << 12)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG2_VCO_RST_IN	BIT(11)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG2_SINT_FRAC	BIT(10)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG2_SDIV2		BIT(9)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG2_S(x)		((x) << 6)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG2_S6P25_7P5	BIT(5)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG2_S5_7		BIT(4)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG2_PREDIV_MSK	GENMASK(3, 0)
#घोषणा SUN8I_HDMI_PHY_PLL_CFG2_PREDIV_SHIFT	0
#घोषणा SUN8I_HDMI_PHY_PLL_CFG2_PREDIV(x)	(((x) - 1) << 0)

#घोषणा SUN8I_HDMI_PHY_PLL_CFG3_REG	0x0034
#घोषणा SUN8I_HDMI_PHY_PLL_CFG3_SOUT_DIV2	BIT(0)

#घोषणा SUN8I_HDMI_PHY_ANA_STS_REG	0x0038
#घोषणा SUN8I_HDMI_PHY_ANA_STS_B_OUT_SHIFT	11
#घोषणा SUN8I_HDMI_PHY_ANA_STS_B_OUT_MSK	GENMASK(16, 11)
#घोषणा SUN8I_HDMI_PHY_ANA_STS_RCALEND2D	BIT(7)
#घोषणा SUN8I_HDMI_PHY_ANA_STS_RCAL_MASK	GENMASK(5, 0)

#घोषणा SUN8I_HDMI_PHY_CEC_REG		0x003c

काष्ठा sun8i_hdmi_phy;

काष्ठा sun8i_hdmi_phy_variant अणु
	bool has_phy_clk;
	bool has_second_pll;
	अचिन्हित पूर्णांक is_custom_phy : 1;
	स्थिर काष्ठा dw_hdmi_curr_ctrl *cur_ctr;
	स्थिर काष्ठा dw_hdmi_mpll_config *mpll_cfg;
	स्थिर काष्ठा dw_hdmi_phy_config *phy_cfg;
	व्योम (*phy_init)(काष्ठा sun8i_hdmi_phy *phy);
	व्योम (*phy_disable)(काष्ठा dw_hdmi *hdmi,
			    काष्ठा sun8i_hdmi_phy *phy);
	पूर्णांक  (*phy_config)(काष्ठा dw_hdmi *hdmi,
			   काष्ठा sun8i_hdmi_phy *phy,
			   अचिन्हित पूर्णांक clk_rate);
पूर्ण;

काष्ठा sun8i_hdmi_phy अणु
	काष्ठा clk			*clk_bus;
	काष्ठा clk			*clk_mod;
	काष्ठा clk			*clk_phy;
	काष्ठा clk			*clk_pll0;
	काष्ठा clk			*clk_pll1;
	अचिन्हित पूर्णांक			rcal;
	काष्ठा regmap			*regs;
	काष्ठा reset_control		*rst_phy;
	काष्ठा sun8i_hdmi_phy_variant	*variant;
पूर्ण;

काष्ठा sun8i_dw_hdmi_quirks अणु
	क्रमागत drm_mode_status (*mode_valid)(काष्ठा dw_hdmi *hdmi, व्योम *data,
					   स्थिर काष्ठा drm_display_info *info,
					   स्थिर काष्ठा drm_display_mode *mode);
	अचिन्हित पूर्णांक use_drm_infoframe : 1;
पूर्ण;

काष्ठा sun8i_dw_hdmi अणु
	काष्ठा clk			*clk_पंचांगds;
	काष्ठा device			*dev;
	काष्ठा dw_hdmi			*hdmi;
	काष्ठा drm_encoder		encoder;
	काष्ठा sun8i_hdmi_phy		*phy;
	काष्ठा dw_hdmi_plat_data	plat_data;
	काष्ठा regulator		*regulator;
	स्थिर काष्ठा sun8i_dw_hdmi_quirks *quirks;
	काष्ठा reset_control		*rst_ctrl;
	काष्ठा gpio_desc		*ddc_en;
पूर्ण;

बाह्य काष्ठा platक्रमm_driver sun8i_hdmi_phy_driver;

अटल अंतरभूत काष्ठा sun8i_dw_hdmi *
encoder_to_sun8i_dw_hdmi(काष्ठा drm_encoder *encoder)
अणु
	वापस container_of(encoder, काष्ठा sun8i_dw_hdmi, encoder);
पूर्ण

पूर्णांक sun8i_hdmi_phy_get(काष्ठा sun8i_dw_hdmi *hdmi, काष्ठा device_node *node);

व्योम sun8i_hdmi_phy_init(काष्ठा sun8i_hdmi_phy *phy);
व्योम sun8i_hdmi_phy_set_ops(काष्ठा sun8i_hdmi_phy *phy,
			    काष्ठा dw_hdmi_plat_data *plat_data);

पूर्णांक sun8i_phy_clk_create(काष्ठा sun8i_hdmi_phy *phy, काष्ठा device *dev,
			 bool second_parent);

#पूर्ण_अगर /* _SUN8I_DW_HDMI_H_ */
