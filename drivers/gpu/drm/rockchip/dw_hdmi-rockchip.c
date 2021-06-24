<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2014, Fuzhou Rockchip Electronics Co., Ltd
 */

#समावेश <linux/clk.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/regmap.h>

#समावेश <drm/bridge/dw_hdmi.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "rockchip_drm_drv.h"
#समावेश "rockchip_drm_vop.h"

#घोषणा RK3228_GRF_SOC_CON2		0x0408
#घोषणा RK3228_HDMI_SDAIN_MSK		BIT(14)
#घोषणा RK3228_HDMI_SCLIN_MSK		BIT(13)
#घोषणा RK3228_GRF_SOC_CON6		0x0418
#घोषणा RK3228_HDMI_HPD_VSEL		BIT(6)
#घोषणा RK3228_HDMI_SDA_VSEL		BIT(5)
#घोषणा RK3228_HDMI_SCL_VSEL		BIT(4)

#घोषणा RK3288_GRF_SOC_CON6		0x025C
#घोषणा RK3288_HDMI_LCDC_SEL		BIT(4)
#घोषणा RK3328_GRF_SOC_CON2		0x0408

#घोषणा RK3328_HDMI_SDAIN_MSK		BIT(11)
#घोषणा RK3328_HDMI_SCLIN_MSK		BIT(10)
#घोषणा RK3328_HDMI_HPD_IOE		BIT(2)
#घोषणा RK3328_GRF_SOC_CON3		0x040c
/* need to be unset अगर hdmi or i2c should control voltage */
#घोषणा RK3328_HDMI_SDA5V_GRF		BIT(15)
#घोषणा RK3328_HDMI_SCL5V_GRF		BIT(14)
#घोषणा RK3328_HDMI_HPD5V_GRF		BIT(13)
#घोषणा RK3328_HDMI_CEC5V_GRF		BIT(12)
#घोषणा RK3328_GRF_SOC_CON4		0x0410
#घोषणा RK3328_HDMI_HPD_SARADC		BIT(13)
#घोषणा RK3328_HDMI_CEC_5V		BIT(11)
#घोषणा RK3328_HDMI_SDA_5V		BIT(10)
#घोषणा RK3328_HDMI_SCL_5V		BIT(9)
#घोषणा RK3328_HDMI_HPD_5V		BIT(8)

#घोषणा RK3399_GRF_SOC_CON20		0x6250
#घोषणा RK3399_HDMI_LCDC_SEL		BIT(6)

#घोषणा HIWORD_UPDATE(val, mask)	(val | (mask) << 16)

/**
 * काष्ठा rockchip_hdmi_chip_data - splite the grf setting of kind of chips
 * @lcdsel_grf_reg: grf रेजिस्टर offset of lcdc select
 * @lcdsel_big: reg value of selecting vop big क्रम HDMI
 * @lcdsel_lit: reg value of selecting vop little क्रम HDMI
 */
काष्ठा rockchip_hdmi_chip_data अणु
	पूर्णांक	lcdsel_grf_reg;
	u32	lcdsel_big;
	u32	lcdsel_lit;
पूर्ण;

काष्ठा rockchip_hdmi अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा drm_encoder encoder;
	स्थिर काष्ठा rockchip_hdmi_chip_data *chip_data;
	काष्ठा clk *vpll_clk;
	काष्ठा clk *grf_clk;
	काष्ठा dw_hdmi *hdmi;
	काष्ठा phy *phy;
पूर्ण;

#घोषणा to_rockchip_hdmi(x)	container_of(x, काष्ठा rockchip_hdmi, x)

अटल स्थिर काष्ठा dw_hdmi_mpll_config rockchip_mpll_cfg[] = अणु
	अणु
		27000000, अणु
			अणु 0x00b3, 0x0000पूर्ण,
			अणु 0x2153, 0x0000पूर्ण,
			अणु 0x40f3, 0x0000पूर्ण
		पूर्ण,
	पूर्ण, अणु
		36000000, अणु
			अणु 0x00b3, 0x0000पूर्ण,
			अणु 0x2153, 0x0000पूर्ण,
			अणु 0x40f3, 0x0000पूर्ण
		पूर्ण,
	पूर्ण, अणु
		40000000, अणु
			अणु 0x00b3, 0x0000पूर्ण,
			अणु 0x2153, 0x0000पूर्ण,
			अणु 0x40f3, 0x0000पूर्ण
		पूर्ण,
	पूर्ण, अणु
		54000000, अणु
			अणु 0x0072, 0x0001पूर्ण,
			अणु 0x2142, 0x0001पूर्ण,
			अणु 0x40a2, 0x0001पूर्ण,
		पूर्ण,
	पूर्ण, अणु
		65000000, अणु
			अणु 0x0072, 0x0001पूर्ण,
			अणु 0x2142, 0x0001पूर्ण,
			अणु 0x40a2, 0x0001पूर्ण,
		पूर्ण,
	पूर्ण, अणु
		66000000, अणु
			अणु 0x013e, 0x0003पूर्ण,
			अणु 0x217e, 0x0002पूर्ण,
			अणु 0x4061, 0x0002पूर्ण
		पूर्ण,
	पूर्ण, अणु
		74250000, अणु
			अणु 0x0072, 0x0001पूर्ण,
			अणु 0x2145, 0x0002पूर्ण,
			अणु 0x4061, 0x0002पूर्ण
		पूर्ण,
	पूर्ण, अणु
		83500000, अणु
			अणु 0x0072, 0x0001पूर्ण,
		पूर्ण,
	पूर्ण, अणु
		108000000, अणु
			अणु 0x0051, 0x0002पूर्ण,
			अणु 0x2145, 0x0002पूर्ण,
			अणु 0x4061, 0x0002पूर्ण
		पूर्ण,
	पूर्ण, अणु
		106500000, अणु
			अणु 0x0051, 0x0002पूर्ण,
			अणु 0x2145, 0x0002पूर्ण,
			अणु 0x4061, 0x0002पूर्ण
		पूर्ण,
	पूर्ण, अणु
		146250000, अणु
			अणु 0x0051, 0x0002पूर्ण,
			अणु 0x2145, 0x0002पूर्ण,
			अणु 0x4061, 0x0002पूर्ण
		पूर्ण,
	पूर्ण, अणु
		148500000, अणु
			अणु 0x0051, 0x0003पूर्ण,
			अणु 0x214c, 0x0003पूर्ण,
			अणु 0x4064, 0x0003पूर्ण
		पूर्ण,
	पूर्ण, अणु
		~0UL, अणु
			अणु 0x00a0, 0x000a पूर्ण,
			अणु 0x2001, 0x000f पूर्ण,
			अणु 0x4002, 0x000f पूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा dw_hdmi_curr_ctrl rockchip_cur_ctr[] = अणु
	/*      pixelclk    bpp8    bpp10   bpp12 */
	अणु
		40000000,  अणु 0x0018, 0x0018, 0x0018 पूर्ण,
	पूर्ण, अणु
		65000000,  अणु 0x0028, 0x0028, 0x0028 पूर्ण,
	पूर्ण, अणु
		66000000,  अणु 0x0038, 0x0038, 0x0038 पूर्ण,
	पूर्ण, अणु
		74250000,  अणु 0x0028, 0x0038, 0x0038 पूर्ण,
	पूर्ण, अणु
		83500000,  अणु 0x0028, 0x0038, 0x0038 पूर्ण,
	पूर्ण, अणु
		146250000, अणु 0x0038, 0x0038, 0x0038 पूर्ण,
	पूर्ण, अणु
		148500000, अणु 0x0000, 0x0038, 0x0038 पूर्ण,
	पूर्ण, अणु
		~0UL,      अणु 0x0000, 0x0000, 0x0000पूर्ण,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा dw_hdmi_phy_config rockchip_phy_config[] = अणु
	/*pixelclk   symbol   term   vlev*/
	अणु 74250000,  0x8009, 0x0004, 0x0272पूर्ण,
	अणु 148500000, 0x802b, 0x0004, 0x028dपूर्ण,
	अणु 297000000, 0x8039, 0x0005, 0x028dपूर्ण,
	अणु ~0UL,	     0x0000, 0x0000, 0x0000पूर्ण
पूर्ण;

अटल पूर्णांक rockchip_hdmi_parse_dt(काष्ठा rockchip_hdmi *hdmi)
अणु
	काष्ठा device_node *np = hdmi->dev->of_node;

	hdmi->regmap = syscon_regmap_lookup_by_phandle(np, "rockchip,grf");
	अगर (IS_ERR(hdmi->regmap)) अणु
		DRM_DEV_ERROR(hdmi->dev, "Unable to get rockchip,grf\n");
		वापस PTR_ERR(hdmi->regmap);
	पूर्ण

	hdmi->vpll_clk = devm_clk_get(hdmi->dev, "vpll");
	अगर (PTR_ERR(hdmi->vpll_clk) == -ENOENT) अणु
		hdmi->vpll_clk = शून्य;
	पूर्ण अन्यथा अगर (PTR_ERR(hdmi->vpll_clk) == -EPROBE_DEFER) अणु
		वापस -EPROBE_DEFER;
	पूर्ण अन्यथा अगर (IS_ERR(hdmi->vpll_clk)) अणु
		DRM_DEV_ERROR(hdmi->dev, "failed to get vpll clock\n");
		वापस PTR_ERR(hdmi->vpll_clk);
	पूर्ण

	hdmi->grf_clk = devm_clk_get(hdmi->dev, "grf");
	अगर (PTR_ERR(hdmi->grf_clk) == -ENOENT) अणु
		hdmi->grf_clk = शून्य;
	पूर्ण अन्यथा अगर (PTR_ERR(hdmi->grf_clk) == -EPROBE_DEFER) अणु
		वापस -EPROBE_DEFER;
	पूर्ण अन्यथा अगर (IS_ERR(hdmi->grf_clk)) अणु
		DRM_DEV_ERROR(hdmi->dev, "failed to get grf clock\n");
		वापस PTR_ERR(hdmi->grf_clk);
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत drm_mode_status
dw_hdmi_rockchip_mode_valid(काष्ठा dw_hdmi *hdmi, व्योम *data,
			    स्थिर काष्ठा drm_display_info *info,
			    स्थिर काष्ठा drm_display_mode *mode)
अणु
	स्थिर काष्ठा dw_hdmi_mpll_config *mpll_cfg = rockchip_mpll_cfg;
	पूर्णांक pclk = mode->घड़ी * 1000;
	bool valid = false;
	पूर्णांक i;

	क्रम (i = 0; mpll_cfg[i].mpixelघड़ी != (~0UL); i++) अणु
		अगर (pclk == mpll_cfg[i].mpixelघड़ी) अणु
			valid = true;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस (valid) ? MODE_OK : MODE_BAD;
पूर्ण

अटल व्योम dw_hdmi_rockchip_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
पूर्ण

अटल bool
dw_hdmi_rockchip_encoder_mode_fixup(काष्ठा drm_encoder *encoder,
				    स्थिर काष्ठा drm_display_mode *mode,
				    काष्ठा drm_display_mode *adj_mode)
अणु
	वापस true;
पूर्ण

अटल व्योम dw_hdmi_rockchip_encoder_mode_set(काष्ठा drm_encoder *encoder,
					      काष्ठा drm_display_mode *mode,
					      काष्ठा drm_display_mode *adj_mode)
अणु
	काष्ठा rockchip_hdmi *hdmi = to_rockchip_hdmi(encoder);

	clk_set_rate(hdmi->vpll_clk, adj_mode->घड़ी * 1000);
पूर्ण

अटल व्योम dw_hdmi_rockchip_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा rockchip_hdmi *hdmi = to_rockchip_hdmi(encoder);
	u32 val;
	पूर्णांक ret;

	अगर (hdmi->chip_data->lcdsel_grf_reg < 0)
		वापस;

	ret = drm_of_encoder_active_endpoपूर्णांक_id(hdmi->dev->of_node, encoder);
	अगर (ret)
		val = hdmi->chip_data->lcdsel_lit;
	अन्यथा
		val = hdmi->chip_data->lcdsel_big;

	ret = clk_prepare_enable(hdmi->grf_clk);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(hdmi->dev, "failed to enable grfclk %d\n", ret);
		वापस;
	पूर्ण

	ret = regmap_ग_लिखो(hdmi->regmap, hdmi->chip_data->lcdsel_grf_reg, val);
	अगर (ret != 0)
		DRM_DEV_ERROR(hdmi->dev, "Could not write to GRF: %d\n", ret);

	clk_disable_unprepare(hdmi->grf_clk);
	DRM_DEV_DEBUG(hdmi->dev, "vop %s output to hdmi\n",
		      ret ? "LIT" : "BIG");
पूर्ण

अटल पूर्णांक
dw_hdmi_rockchip_encoder_atomic_check(काष्ठा drm_encoder *encoder,
				      काष्ठा drm_crtc_state *crtc_state,
				      काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा rockchip_crtc_state *s = to_rockchip_crtc_state(crtc_state);

	s->output_mode = ROCKCHIP_OUT_MODE_AAAA;
	s->output_type = DRM_MODE_CONNECTOR_HDMIA;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs dw_hdmi_rockchip_encoder_helper_funcs = अणु
	.mode_fixup = dw_hdmi_rockchip_encoder_mode_fixup,
	.mode_set   = dw_hdmi_rockchip_encoder_mode_set,
	.enable     = dw_hdmi_rockchip_encoder_enable,
	.disable    = dw_hdmi_rockchip_encoder_disable,
	.atomic_check = dw_hdmi_rockchip_encoder_atomic_check,
पूर्ण;

अटल पूर्णांक dw_hdmi_rockchip_genphy_init(काष्ठा dw_hdmi *dw_hdmi, व्योम *data,
					स्थिर काष्ठा drm_display_info *display,
					स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा rockchip_hdmi *hdmi = (काष्ठा rockchip_hdmi *)data;

	वापस phy_घातer_on(hdmi->phy);
पूर्ण

अटल व्योम dw_hdmi_rockchip_genphy_disable(काष्ठा dw_hdmi *dw_hdmi, व्योम *data)
अणु
	काष्ठा rockchip_hdmi *hdmi = (काष्ठा rockchip_hdmi *)data;

	phy_घातer_off(hdmi->phy);
पूर्ण

अटल व्योम dw_hdmi_rk3228_setup_hpd(काष्ठा dw_hdmi *dw_hdmi, व्योम *data)
अणु
	काष्ठा rockchip_hdmi *hdmi = (काष्ठा rockchip_hdmi *)data;

	dw_hdmi_phy_setup_hpd(dw_hdmi, data);

	regmap_ग_लिखो(hdmi->regmap,
		RK3228_GRF_SOC_CON6,
		HIWORD_UPDATE(RK3228_HDMI_HPD_VSEL | RK3228_HDMI_SDA_VSEL |
			      RK3228_HDMI_SCL_VSEL,
			      RK3228_HDMI_HPD_VSEL | RK3228_HDMI_SDA_VSEL |
			      RK3228_HDMI_SCL_VSEL));

	regmap_ग_लिखो(hdmi->regmap,
		RK3228_GRF_SOC_CON2,
		HIWORD_UPDATE(RK3228_HDMI_SDAIN_MSK | RK3228_HDMI_SCLIN_MSK,
			      RK3228_HDMI_SDAIN_MSK | RK3228_HDMI_SCLIN_MSK));
पूर्ण

अटल क्रमागत drm_connector_status
dw_hdmi_rk3328_पढ़ो_hpd(काष्ठा dw_hdmi *dw_hdmi, व्योम *data)
अणु
	काष्ठा rockchip_hdmi *hdmi = (काष्ठा rockchip_hdmi *)data;
	क्रमागत drm_connector_status status;

	status = dw_hdmi_phy_पढ़ो_hpd(dw_hdmi, data);

	अगर (status == connector_status_connected)
		regmap_ग_लिखो(hdmi->regmap,
			RK3328_GRF_SOC_CON4,
			HIWORD_UPDATE(RK3328_HDMI_SDA_5V | RK3328_HDMI_SCL_5V,
				      RK3328_HDMI_SDA_5V | RK3328_HDMI_SCL_5V));
	अन्यथा
		regmap_ग_लिखो(hdmi->regmap,
			RK3328_GRF_SOC_CON4,
			HIWORD_UPDATE(0, RK3328_HDMI_SDA_5V |
					 RK3328_HDMI_SCL_5V));
	वापस status;
पूर्ण

अटल व्योम dw_hdmi_rk3328_setup_hpd(काष्ठा dw_hdmi *dw_hdmi, व्योम *data)
अणु
	काष्ठा rockchip_hdmi *hdmi = (काष्ठा rockchip_hdmi *)data;

	dw_hdmi_phy_setup_hpd(dw_hdmi, data);

	/* Enable and map pins to 3V grf-controlled io-voltage */
	regmap_ग_लिखो(hdmi->regmap,
		RK3328_GRF_SOC_CON4,
		HIWORD_UPDATE(0, RK3328_HDMI_HPD_SARADC | RK3328_HDMI_CEC_5V |
				 RK3328_HDMI_SDA_5V | RK3328_HDMI_SCL_5V |
				 RK3328_HDMI_HPD_5V));
	regmap_ग_लिखो(hdmi->regmap,
		RK3328_GRF_SOC_CON3,
		HIWORD_UPDATE(0, RK3328_HDMI_SDA5V_GRF | RK3328_HDMI_SCL5V_GRF |
				 RK3328_HDMI_HPD5V_GRF |
				 RK3328_HDMI_CEC5V_GRF));
	regmap_ग_लिखो(hdmi->regmap,
		RK3328_GRF_SOC_CON2,
		HIWORD_UPDATE(RK3328_HDMI_SDAIN_MSK | RK3328_HDMI_SCLIN_MSK,
			      RK3328_HDMI_SDAIN_MSK | RK3328_HDMI_SCLIN_MSK |
			      RK3328_HDMI_HPD_IOE));
पूर्ण

अटल स्थिर काष्ठा dw_hdmi_phy_ops rk3228_hdmi_phy_ops = अणु
	.init		= dw_hdmi_rockchip_genphy_init,
	.disable	= dw_hdmi_rockchip_genphy_disable,
	.पढ़ो_hpd	= dw_hdmi_phy_पढ़ो_hpd,
	.update_hpd	= dw_hdmi_phy_update_hpd,
	.setup_hpd	= dw_hdmi_rk3228_setup_hpd,
पूर्ण;

अटल काष्ठा rockchip_hdmi_chip_data rk3228_chip_data = अणु
	.lcdsel_grf_reg = -1,
पूर्ण;

अटल स्थिर काष्ठा dw_hdmi_plat_data rk3228_hdmi_drv_data = अणु
	.mode_valid = dw_hdmi_rockchip_mode_valid,
	.mpll_cfg = rockchip_mpll_cfg,
	.cur_ctr = rockchip_cur_ctr,
	.phy_config = rockchip_phy_config,
	.phy_data = &rk3228_chip_data,
	.phy_ops = &rk3228_hdmi_phy_ops,
	.phy_name = "inno_dw_hdmi_phy2",
	.phy_क्रमce_venकरोr = true,
पूर्ण;

अटल काष्ठा rockchip_hdmi_chip_data rk3288_chip_data = अणु
	.lcdsel_grf_reg = RK3288_GRF_SOC_CON6,
	.lcdsel_big = HIWORD_UPDATE(0, RK3288_HDMI_LCDC_SEL),
	.lcdsel_lit = HIWORD_UPDATE(RK3288_HDMI_LCDC_SEL, RK3288_HDMI_LCDC_SEL),
पूर्ण;

अटल स्थिर काष्ठा dw_hdmi_plat_data rk3288_hdmi_drv_data = अणु
	.mode_valid = dw_hdmi_rockchip_mode_valid,
	.mpll_cfg   = rockchip_mpll_cfg,
	.cur_ctr    = rockchip_cur_ctr,
	.phy_config = rockchip_phy_config,
	.phy_data = &rk3288_chip_data,
पूर्ण;

अटल स्थिर काष्ठा dw_hdmi_phy_ops rk3328_hdmi_phy_ops = अणु
	.init		= dw_hdmi_rockchip_genphy_init,
	.disable	= dw_hdmi_rockchip_genphy_disable,
	.पढ़ो_hpd	= dw_hdmi_rk3328_पढ़ो_hpd,
	.update_hpd	= dw_hdmi_phy_update_hpd,
	.setup_hpd	= dw_hdmi_rk3328_setup_hpd,
पूर्ण;

अटल काष्ठा rockchip_hdmi_chip_data rk3328_chip_data = अणु
	.lcdsel_grf_reg = -1,
पूर्ण;

अटल स्थिर काष्ठा dw_hdmi_plat_data rk3328_hdmi_drv_data = अणु
	.mode_valid = dw_hdmi_rockchip_mode_valid,
	.mpll_cfg = rockchip_mpll_cfg,
	.cur_ctr = rockchip_cur_ctr,
	.phy_config = rockchip_phy_config,
	.phy_data = &rk3328_chip_data,
	.phy_ops = &rk3328_hdmi_phy_ops,
	.phy_name = "inno_dw_hdmi_phy2",
	.phy_क्रमce_venकरोr = true,
	.use_drm_infoframe = true,
पूर्ण;

अटल काष्ठा rockchip_hdmi_chip_data rk3399_chip_data = अणु
	.lcdsel_grf_reg = RK3399_GRF_SOC_CON20,
	.lcdsel_big = HIWORD_UPDATE(0, RK3399_HDMI_LCDC_SEL),
	.lcdsel_lit = HIWORD_UPDATE(RK3399_HDMI_LCDC_SEL, RK3399_HDMI_LCDC_SEL),
पूर्ण;

अटल स्थिर काष्ठा dw_hdmi_plat_data rk3399_hdmi_drv_data = अणु
	.mode_valid = dw_hdmi_rockchip_mode_valid,
	.mpll_cfg   = rockchip_mpll_cfg,
	.cur_ctr    = rockchip_cur_ctr,
	.phy_config = rockchip_phy_config,
	.phy_data = &rk3399_chip_data,
	.use_drm_infoframe = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id dw_hdmi_rockchip_dt_ids[] = अणु
	अणु .compatible = "rockchip,rk3228-dw-hdmi",
	  .data = &rk3228_hdmi_drv_data
	पूर्ण,
	अणु .compatible = "rockchip,rk3288-dw-hdmi",
	  .data = &rk3288_hdmi_drv_data
	पूर्ण,
	अणु .compatible = "rockchip,rk3328-dw-hdmi",
	  .data = &rk3328_hdmi_drv_data
	पूर्ण,
	अणु .compatible = "rockchip,rk3399-dw-hdmi",
	  .data = &rk3399_hdmi_drv_data
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, dw_hdmi_rockchip_dt_ids);

अटल पूर्णांक dw_hdmi_rockchip_bind(काष्ठा device *dev, काष्ठा device *master,
				 व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा dw_hdmi_plat_data *plat_data;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा drm_device *drm = data;
	काष्ठा drm_encoder *encoder;
	काष्ठा rockchip_hdmi *hdmi;
	पूर्णांक ret;

	अगर (!pdev->dev.of_node)
		वापस -ENODEV;

	hdmi = devm_kzalloc(&pdev->dev, माप(*hdmi), GFP_KERNEL);
	अगर (!hdmi)
		वापस -ENOMEM;

	match = of_match_node(dw_hdmi_rockchip_dt_ids, pdev->dev.of_node);
	plat_data = devm_kmemdup(&pdev->dev, match->data,
					     माप(*plat_data), GFP_KERNEL);
	अगर (!plat_data)
		वापस -ENOMEM;

	hdmi->dev = &pdev->dev;
	hdmi->chip_data = plat_data->phy_data;
	plat_data->phy_data = hdmi;
	encoder = &hdmi->encoder;

	encoder->possible_crtcs = drm_of_find_possible_crtcs(drm, dev->of_node);
	/*
	 * If we failed to find the CRTC(s) which this encoder is
	 * supposed to be connected to, it's because the CRTC has
	 * not been रेजिस्टरed yet.  Defer probing, and hope that
	 * the required CRTC is added later.
	 */
	अगर (encoder->possible_crtcs == 0)
		वापस -EPROBE_DEFER;

	ret = rockchip_hdmi_parse_dt(hdmi);
	अगर (ret) अणु
		DRM_DEV_ERROR(hdmi->dev, "Unable to parse OF data\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(hdmi->vpll_clk);
	अगर (ret) अणु
		DRM_DEV_ERROR(hdmi->dev, "Failed to enable HDMI vpll: %d\n",
			      ret);
		वापस ret;
	पूर्ण

	hdmi->phy = devm_phy_optional_get(dev, "hdmi");
	अगर (IS_ERR(hdmi->phy)) अणु
		ret = PTR_ERR(hdmi->phy);
		अगर (ret != -EPROBE_DEFER)
			DRM_DEV_ERROR(hdmi->dev, "failed to get phy\n");
		वापस ret;
	पूर्ण

	drm_encoder_helper_add(encoder, &dw_hdmi_rockchip_encoder_helper_funcs);
	drm_simple_encoder_init(drm, encoder, DRM_MODE_ENCODER_TMDS);

	platक्रमm_set_drvdata(pdev, hdmi);

	hdmi->hdmi = dw_hdmi_bind(pdev, encoder, plat_data);

	/*
	 * If dw_hdmi_bind() fails we'll never call dw_hdmi_unbind(),
	 * which would have called the encoder cleanup.  Do it manually.
	 */
	अगर (IS_ERR(hdmi->hdmi)) अणु
		ret = PTR_ERR(hdmi->hdmi);
		drm_encoder_cleanup(encoder);
		clk_disable_unprepare(hdmi->vpll_clk);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम dw_hdmi_rockchip_unbind(काष्ठा device *dev, काष्ठा device *master,
				    व्योम *data)
अणु
	काष्ठा rockchip_hdmi *hdmi = dev_get_drvdata(dev);

	dw_hdmi_unbind(hdmi->hdmi);
	clk_disable_unprepare(hdmi->vpll_clk);
पूर्ण

अटल स्थिर काष्ठा component_ops dw_hdmi_rockchip_ops = अणु
	.bind	= dw_hdmi_rockchip_bind,
	.unbind	= dw_hdmi_rockchip_unbind,
पूर्ण;

अटल पूर्णांक dw_hdmi_rockchip_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &dw_hdmi_rockchip_ops);
पूर्ण

अटल पूर्णांक dw_hdmi_rockchip_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &dw_hdmi_rockchip_ops);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused dw_hdmi_rockchip_resume(काष्ठा device *dev)
अणु
	काष्ठा rockchip_hdmi *hdmi = dev_get_drvdata(dev);

	dw_hdmi_resume(hdmi->hdmi);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops dw_hdmi_rockchip_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(शून्य, dw_hdmi_rockchip_resume)
पूर्ण;

काष्ठा platक्रमm_driver dw_hdmi_rockchip_pltfm_driver = अणु
	.probe  = dw_hdmi_rockchip_probe,
	.हटाओ = dw_hdmi_rockchip_हटाओ,
	.driver = अणु
		.name = "dwhdmi-rockchip",
		.pm = &dw_hdmi_rockchip_pm,
		.of_match_table = dw_hdmi_rockchip_dt_ids,
	पूर्ण,
पूर्ण;
