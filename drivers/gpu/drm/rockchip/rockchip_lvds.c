<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Fuzhou Rockchip Electronics Co.Ltd
 * Author:
 *      Mark Yao <mark.yao@rock-chips.com>
 *      Sandy Huang <hjc@rock-chips.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/pinctrl/devinfo.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "rockchip_drm_drv.h"
#समावेश "rockchip_drm_vop.h"
#समावेश "rockchip_lvds.h"

#घोषणा DISPLAY_OUTPUT_RGB		0
#घोषणा DISPLAY_OUTPUT_LVDS		1
#घोषणा DISPLAY_OUTPUT_DUAL_LVDS	2

काष्ठा rockchip_lvds;

#घोषणा connector_to_lvds(c) \
		container_of(c, काष्ठा rockchip_lvds, connector)

#घोषणा encoder_to_lvds(c) \
		container_of(c, काष्ठा rockchip_lvds, encoder)

/**
 * काष्ठा rockchip_lvds_soc_data - rockchip lvds Soc निजी data
 * @probe: LVDS platक्रमm probe function
 * @helper_funcs: LVDS connector helper functions
 */
काष्ठा rockchip_lvds_soc_data अणु
	पूर्णांक (*probe)(काष्ठा platक्रमm_device *pdev, काष्ठा rockchip_lvds *lvds);
	स्थिर काष्ठा drm_encoder_helper_funcs *helper_funcs;
पूर्ण;

काष्ठा rockchip_lvds अणु
	काष्ठा device *dev;
	व्योम __iomem *regs;
	काष्ठा regmap *grf;
	काष्ठा clk *pclk;
	काष्ठा phy *dphy;
	स्थिर काष्ठा rockchip_lvds_soc_data *soc_data;
	पूर्णांक output; /* rgb lvds or dual lvds output */
	पूर्णांक क्रमmat; /* vesa or jeida क्रमmat */
	काष्ठा drm_device *drm_dev;
	काष्ठा drm_panel *panel;
	काष्ठा drm_bridge *bridge;
	काष्ठा drm_connector connector;
	काष्ठा drm_encoder encoder;
	काष्ठा dev_pin_info *pins;
पूर्ण;

अटल अंतरभूत व्योम rk3288_ग_लिखोl(काष्ठा rockchip_lvds *lvds, u32 offset,
				 u32 val)
अणु
	ग_लिखोl_relaxed(val, lvds->regs + offset);
	अगर (lvds->output == DISPLAY_OUTPUT_LVDS)
		वापस;
	ग_लिखोl_relaxed(val, lvds->regs + offset + RK3288_LVDS_CH1_OFFSET);
पूर्ण

अटल अंतरभूत पूर्णांक rockchip_lvds_name_to_क्रमmat(स्थिर अक्षर *s)
अणु
	अगर (म_भेदन(s, "jeida-18", 8) == 0)
		वापस LVDS_JEIDA_18;
	अन्यथा अगर (म_भेदन(s, "jeida-24", 8) == 0)
		वापस LVDS_JEIDA_24;
	अन्यथा अगर (म_भेदन(s, "vesa-24", 7) == 0)
		वापस LVDS_VESA_24;

	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक rockchip_lvds_name_to_output(स्थिर अक्षर *s)
अणु
	अगर (म_भेदन(s, "rgb", 3) == 0)
		वापस DISPLAY_OUTPUT_RGB;
	अन्यथा अगर (म_भेदन(s, "lvds", 4) == 0)
		वापस DISPLAY_OUTPUT_LVDS;
	अन्यथा अगर (म_भेदन(s, "duallvds", 8) == 0)
		वापस DISPLAY_OUTPUT_DUAL_LVDS;

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs rockchip_lvds_connector_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = drm_connector_cleanup,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक rockchip_lvds_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा rockchip_lvds *lvds = connector_to_lvds(connector);
	काष्ठा drm_panel *panel = lvds->panel;

	वापस drm_panel_get_modes(panel, connector);
पूर्ण

अटल स्थिर
काष्ठा drm_connector_helper_funcs rockchip_lvds_connector_helper_funcs = अणु
	.get_modes = rockchip_lvds_connector_get_modes,
पूर्ण;

अटल पूर्णांक
rockchip_lvds_encoder_atomic_check(काष्ठा drm_encoder *encoder,
				   काष्ठा drm_crtc_state *crtc_state,
				   काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा rockchip_crtc_state *s = to_rockchip_crtc_state(crtc_state);

	s->output_mode = ROCKCHIP_OUT_MODE_P888;
	s->output_type = DRM_MODE_CONNECTOR_LVDS;

	वापस 0;
पूर्ण

अटल पूर्णांक rk3288_lvds_घातeron(काष्ठा rockchip_lvds *lvds)
अणु
	पूर्णांक ret;
	u32 val;

	ret = clk_enable(lvds->pclk);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(lvds->dev, "failed to enable lvds pclk %d\n", ret);
		वापस ret;
	पूर्ण
	ret = pm_runसमय_get_sync(lvds->dev);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(lvds->dev, "failed to get pm runtime: %d\n", ret);
		clk_disable(lvds->pclk);
		वापस ret;
	पूर्ण
	val = RK3288_LVDS_CH0_REG0_LANE4_EN | RK3288_LVDS_CH0_REG0_LANE3_EN |
		RK3288_LVDS_CH0_REG0_LANE2_EN | RK3288_LVDS_CH0_REG0_LANE1_EN |
		RK3288_LVDS_CH0_REG0_LANE0_EN;
	अगर (lvds->output == DISPLAY_OUTPUT_RGB) अणु
		val |= RK3288_LVDS_CH0_REG0_TTL_EN |
			RK3288_LVDS_CH0_REG0_LANECK_EN;
		rk3288_ग_लिखोl(lvds, RK3288_LVDS_CH0_REG0, val);
		rk3288_ग_लिखोl(lvds, RK3288_LVDS_CH0_REG2,
			      RK3288_LVDS_PLL_FBDIV_REG2(0x46));
		rk3288_ग_लिखोl(lvds, RK3288_LVDS_CH0_REG4,
			      RK3288_LVDS_CH0_REG4_LANECK_TTL_MODE |
			      RK3288_LVDS_CH0_REG4_LANE4_TTL_MODE |
			      RK3288_LVDS_CH0_REG4_LANE3_TTL_MODE |
			      RK3288_LVDS_CH0_REG4_LANE2_TTL_MODE |
			      RK3288_LVDS_CH0_REG4_LANE1_TTL_MODE |
			      RK3288_LVDS_CH0_REG4_LANE0_TTL_MODE);
		rk3288_ग_लिखोl(lvds, RK3288_LVDS_CH0_REG5,
			      RK3288_LVDS_CH0_REG5_LANECK_TTL_DATA |
			      RK3288_LVDS_CH0_REG5_LANE4_TTL_DATA |
			      RK3288_LVDS_CH0_REG5_LANE3_TTL_DATA |
			      RK3288_LVDS_CH0_REG5_LANE2_TTL_DATA |
			      RK3288_LVDS_CH0_REG5_LANE1_TTL_DATA |
			      RK3288_LVDS_CH0_REG5_LANE0_TTL_DATA);
	पूर्ण अन्यथा अणु
		val |= RK3288_LVDS_CH0_REG0_LVDS_EN |
			    RK3288_LVDS_CH0_REG0_LANECK_EN;
		rk3288_ग_लिखोl(lvds, RK3288_LVDS_CH0_REG0, val);
		rk3288_ग_लिखोl(lvds, RK3288_LVDS_CH0_REG1,
			      RK3288_LVDS_CH0_REG1_LANECK_BIAS |
			      RK3288_LVDS_CH0_REG1_LANE4_BIAS |
			      RK3288_LVDS_CH0_REG1_LANE3_BIAS |
			      RK3288_LVDS_CH0_REG1_LANE2_BIAS |
			      RK3288_LVDS_CH0_REG1_LANE1_BIAS |
			      RK3288_LVDS_CH0_REG1_LANE0_BIAS);
		rk3288_ग_लिखोl(lvds, RK3288_LVDS_CH0_REG2,
			      RK3288_LVDS_CH0_REG2_RESERVE_ON |
			      RK3288_LVDS_CH0_REG2_LANECK_LVDS_MODE |
			      RK3288_LVDS_CH0_REG2_LANE4_LVDS_MODE |
			      RK3288_LVDS_CH0_REG2_LANE3_LVDS_MODE |
			      RK3288_LVDS_CH0_REG2_LANE2_LVDS_MODE |
			      RK3288_LVDS_CH0_REG2_LANE1_LVDS_MODE |
			      RK3288_LVDS_CH0_REG2_LANE0_LVDS_MODE |
			      RK3288_LVDS_PLL_FBDIV_REG2(0x46));
		rk3288_ग_लिखोl(lvds, RK3288_LVDS_CH0_REG4, 0x00);
		rk3288_ग_लिखोl(lvds, RK3288_LVDS_CH0_REG5, 0x00);
	पूर्ण
	rk3288_ग_लिखोl(lvds, RK3288_LVDS_CH0_REG3,
		      RK3288_LVDS_PLL_FBDIV_REG3(0x46));
	rk3288_ग_लिखोl(lvds, RK3288_LVDS_CH0_REGD,
		      RK3288_LVDS_PLL_PREDIV_REGD(0x0a));
	rk3288_ग_लिखोl(lvds, RK3288_LVDS_CH0_REG20,
		      RK3288_LVDS_CH0_REG20_LSB);

	rk3288_ग_लिखोl(lvds, RK3288_LVDS_CFG_REGC,
		      RK3288_LVDS_CFG_REGC_PLL_ENABLE);
	rk3288_ग_लिखोl(lvds, RK3288_LVDS_CFG_REG21,
		      RK3288_LVDS_CFG_REG21_TX_ENABLE);

	वापस 0;
पूर्ण

अटल व्योम rk3288_lvds_घातeroff(काष्ठा rockchip_lvds *lvds)
अणु
	पूर्णांक ret;
	u32 val;

	rk3288_ग_लिखोl(lvds, RK3288_LVDS_CFG_REG21,
		      RK3288_LVDS_CFG_REG21_TX_ENABLE);
	rk3288_ग_लिखोl(lvds, RK3288_LVDS_CFG_REGC,
		      RK3288_LVDS_CFG_REGC_PLL_ENABLE);
	val = LVDS_DUAL | LVDS_TTL_EN | LVDS_CH0_EN | LVDS_CH1_EN | LVDS_PWRDN;
	val |= val << 16;
	ret = regmap_ग_लिखो(lvds->grf, RK3288_LVDS_GRF_SOC_CON7, val);
	अगर (ret != 0)
		DRM_DEV_ERROR(lvds->dev, "Could not write to GRF: %d\n", ret);

	pm_runसमय_put(lvds->dev);
	clk_disable(lvds->pclk);
पूर्ण

अटल पूर्णांक rk3288_lvds_grf_config(काष्ठा drm_encoder *encoder,
				  काष्ठा drm_display_mode *mode)
अणु
	काष्ठा rockchip_lvds *lvds = encoder_to_lvds(encoder);
	u8 pin_hsync = (mode->flags & DRM_MODE_FLAG_PHSYNC) ? 1 : 0;
	u8 pin_dclk = (mode->flags & DRM_MODE_FLAG_PCSYNC) ? 1 : 0;
	u32 val;
	पूर्णांक ret;

	/* iomux to LCD data/sync mode */
	अगर (lvds->output == DISPLAY_OUTPUT_RGB)
		अगर (lvds->pins && !IS_ERR(lvds->pins->शेष_state))
			pinctrl_select_state(lvds->pins->p,
					     lvds->pins->शेष_state);
	val = lvds->क्रमmat | LVDS_CH0_EN;
	अगर (lvds->output == DISPLAY_OUTPUT_RGB)
		val |= LVDS_TTL_EN | LVDS_CH1_EN;
	अन्यथा अगर (lvds->output == DISPLAY_OUTPUT_DUAL_LVDS)
		val |= LVDS_DUAL | LVDS_CH1_EN;

	अगर ((mode->htotal - mode->hsync_start) & 0x01)
		val |= LVDS_START_PHASE_RST_1;

	val |= (pin_dclk << 8) | (pin_hsync << 9);
	val |= (0xffff << 16);
	ret = regmap_ग_लिखो(lvds->grf, RK3288_LVDS_GRF_SOC_CON7, val);
	अगर (ret)
		DRM_DEV_ERROR(lvds->dev, "Could not write to GRF: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक rk3288_lvds_set_vop_source(काष्ठा rockchip_lvds *lvds,
				      काष्ठा drm_encoder *encoder)
अणु
	u32 val;
	पूर्णांक ret;

	ret = drm_of_encoder_active_endpoपूर्णांक_id(lvds->dev->of_node, encoder);
	अगर (ret < 0)
		वापस ret;

	val = RK3288_LVDS_SOC_CON6_SEL_VOP_LIT << 16;
	अगर (ret)
		val |= RK3288_LVDS_SOC_CON6_SEL_VOP_LIT;

	ret = regmap_ग_लिखो(lvds->grf, RK3288_LVDS_GRF_SOC_CON6, val);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम rk3288_lvds_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा rockchip_lvds *lvds = encoder_to_lvds(encoder);
	काष्ठा drm_display_mode *mode = &encoder->crtc->state->adjusted_mode;
	पूर्णांक ret;

	drm_panel_prepare(lvds->panel);

	ret = rk3288_lvds_घातeron(lvds);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(lvds->dev, "failed to power on LVDS: %d\n", ret);
		drm_panel_unprepare(lvds->panel);
		वापस;
	पूर्ण

	ret = rk3288_lvds_grf_config(encoder, mode);
	अगर (ret) अणु
		DRM_DEV_ERROR(lvds->dev, "failed to configure LVDS: %d\n", ret);
		drm_panel_unprepare(lvds->panel);
		वापस;
	पूर्ण

	ret = rk3288_lvds_set_vop_source(lvds, encoder);
	अगर (ret) अणु
		DRM_DEV_ERROR(lvds->dev, "failed to set VOP source: %d\n", ret);
		drm_panel_unprepare(lvds->panel);
		वापस;
	पूर्ण

	drm_panel_enable(lvds->panel);
पूर्ण

अटल व्योम rk3288_lvds_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा rockchip_lvds *lvds = encoder_to_lvds(encoder);

	drm_panel_disable(lvds->panel);
	rk3288_lvds_घातeroff(lvds);
	drm_panel_unprepare(lvds->panel);
पूर्ण

अटल पूर्णांक px30_lvds_घातeron(काष्ठा rockchip_lvds *lvds)
अणु
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(lvds->dev);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(lvds->dev, "failed to get pm runtime: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Enable LVDS mode */
	वापस regmap_update_bits(lvds->grf, PX30_LVDS_GRF_PD_VO_CON1,
				  PX30_LVDS_MODE_EN(1) | PX30_LVDS_P2S_EN(1),
				  PX30_LVDS_MODE_EN(1) | PX30_LVDS_P2S_EN(1));
पूर्ण

अटल व्योम px30_lvds_घातeroff(काष्ठा rockchip_lvds *lvds)
अणु
	regmap_update_bits(lvds->grf, PX30_LVDS_GRF_PD_VO_CON1,
			   PX30_LVDS_MODE_EN(1) | PX30_LVDS_P2S_EN(1),
			   PX30_LVDS_MODE_EN(0) | PX30_LVDS_P2S_EN(0));

	pm_runसमय_put(lvds->dev);
पूर्ण

अटल पूर्णांक px30_lvds_grf_config(काष्ठा drm_encoder *encoder,
				काष्ठा drm_display_mode *mode)
अणु
	काष्ठा rockchip_lvds *lvds = encoder_to_lvds(encoder);

	अगर (lvds->output != DISPLAY_OUTPUT_LVDS) अणु
		DRM_DEV_ERROR(lvds->dev, "Unsupported display output %d\n",
			      lvds->output);
		वापस -EINVAL;
	पूर्ण

	/* Set क्रमmat */
	वापस regmap_update_bits(lvds->grf, PX30_LVDS_GRF_PD_VO_CON1,
				  PX30_LVDS_FORMAT(lvds->क्रमmat),
				  PX30_LVDS_FORMAT(lvds->क्रमmat));
पूर्ण

अटल पूर्णांक px30_lvds_set_vop_source(काष्ठा rockchip_lvds *lvds,
				    काष्ठा drm_encoder *encoder)
अणु
	पूर्णांक vop;

	vop = drm_of_encoder_active_endpoपूर्णांक_id(lvds->dev->of_node, encoder);
	अगर (vop < 0)
		वापस vop;

	वापस regmap_update_bits(lvds->grf, PX30_LVDS_GRF_PD_VO_CON1,
				  PX30_LVDS_VOP_SEL(1),
				  PX30_LVDS_VOP_SEL(vop));
पूर्ण

अटल व्योम px30_lvds_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा rockchip_lvds *lvds = encoder_to_lvds(encoder);
	काष्ठा drm_display_mode *mode = &encoder->crtc->state->adjusted_mode;
	पूर्णांक ret;

	drm_panel_prepare(lvds->panel);

	ret = px30_lvds_घातeron(lvds);
	अगर (ret) अणु
		DRM_DEV_ERROR(lvds->dev, "failed to power on LVDS: %d\n", ret);
		drm_panel_unprepare(lvds->panel);
		वापस;
	पूर्ण

	ret = px30_lvds_grf_config(encoder, mode);
	अगर (ret) अणु
		DRM_DEV_ERROR(lvds->dev, "failed to configure LVDS: %d\n", ret);
		drm_panel_unprepare(lvds->panel);
		वापस;
	पूर्ण

	ret = px30_lvds_set_vop_source(lvds, encoder);
	अगर (ret) अणु
		DRM_DEV_ERROR(lvds->dev, "failed to set VOP source: %d\n", ret);
		drm_panel_unprepare(lvds->panel);
		वापस;
	पूर्ण

	drm_panel_enable(lvds->panel);
पूर्ण

अटल व्योम px30_lvds_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा rockchip_lvds *lvds = encoder_to_lvds(encoder);

	drm_panel_disable(lvds->panel);
	px30_lvds_घातeroff(lvds);
	drm_panel_unprepare(lvds->panel);
पूर्ण

अटल स्थिर
काष्ठा drm_encoder_helper_funcs rk3288_lvds_encoder_helper_funcs = अणु
	.enable = rk3288_lvds_encoder_enable,
	.disable = rk3288_lvds_encoder_disable,
	.atomic_check = rockchip_lvds_encoder_atomic_check,
पूर्ण;

अटल स्थिर
काष्ठा drm_encoder_helper_funcs px30_lvds_encoder_helper_funcs = अणु
	.enable = px30_lvds_encoder_enable,
	.disable = px30_lvds_encoder_disable,
	.atomic_check = rockchip_lvds_encoder_atomic_check,
पूर्ण;

अटल पूर्णांक rk3288_lvds_probe(काष्ठा platक्रमm_device *pdev,
			     काष्ठा rockchip_lvds *lvds)
अणु
	काष्ठा resource *res;
	पूर्णांक ret;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	lvds->regs = devm_ioremap_resource(lvds->dev, res);
	अगर (IS_ERR(lvds->regs))
		वापस PTR_ERR(lvds->regs);

	lvds->pclk = devm_clk_get(lvds->dev, "pclk_lvds");
	अगर (IS_ERR(lvds->pclk)) अणु
		DRM_DEV_ERROR(lvds->dev, "could not get pclk_lvds\n");
		वापस PTR_ERR(lvds->pclk);
	पूर्ण

	lvds->pins = devm_kzalloc(lvds->dev, माप(*lvds->pins),
				  GFP_KERNEL);
	अगर (!lvds->pins)
		वापस -ENOMEM;

	lvds->pins->p = devm_pinctrl_get(lvds->dev);
	अगर (IS_ERR(lvds->pins->p)) अणु
		DRM_DEV_ERROR(lvds->dev, "no pinctrl handle\n");
		devm_kमुक्त(lvds->dev, lvds->pins);
		lvds->pins = शून्य;
	पूर्ण अन्यथा अणु
		lvds->pins->शेष_state =
			pinctrl_lookup_state(lvds->pins->p, "lcdc");
		अगर (IS_ERR(lvds->pins->शेष_state)) अणु
			DRM_DEV_ERROR(lvds->dev, "no default pinctrl state\n");
			devm_kमुक्त(lvds->dev, lvds->pins);
			lvds->pins = शून्य;
		पूर्ण
	पूर्ण

	ret = clk_prepare(lvds->pclk);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(lvds->dev, "failed to prepare pclk_lvds\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक px30_lvds_probe(काष्ठा platक्रमm_device *pdev,
			   काष्ठा rockchip_lvds *lvds)
अणु
	पूर्णांक ret;

	/* MSB */
	ret =  regmap_update_bits(lvds->grf, PX30_LVDS_GRF_PD_VO_CON1,
				  PX30_LVDS_MSBSEL(1),
				  PX30_LVDS_MSBSEL(1));
	अगर (ret)
		वापस ret;

	/* PHY */
	lvds->dphy = devm_phy_get(&pdev->dev, "dphy");
	अगर (IS_ERR(lvds->dphy))
		वापस PTR_ERR(lvds->dphy);

	phy_init(lvds->dphy);
	अगर (ret)
		वापस ret;

	phy_set_mode(lvds->dphy, PHY_MODE_LVDS);
	अगर (ret)
		वापस ret;

	वापस phy_घातer_on(lvds->dphy);
पूर्ण

अटल स्थिर काष्ठा rockchip_lvds_soc_data rk3288_lvds_data = अणु
	.probe = rk3288_lvds_probe,
	.helper_funcs = &rk3288_lvds_encoder_helper_funcs,
पूर्ण;

अटल स्थिर काष्ठा rockchip_lvds_soc_data px30_lvds_data = अणु
	.probe = px30_lvds_probe,
	.helper_funcs = &px30_lvds_encoder_helper_funcs,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rockchip_lvds_dt_ids[] = अणु
	अणु
		.compatible = "rockchip,rk3288-lvds",
		.data = &rk3288_lvds_data
	पूर्ण,
	अणु
		.compatible = "rockchip,px30-lvds",
		.data = &px30_lvds_data
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rockchip_lvds_dt_ids);

अटल पूर्णांक rockchip_lvds_bind(काष्ठा device *dev, काष्ठा device *master,
			      व्योम *data)
अणु
	काष्ठा rockchip_lvds *lvds = dev_get_drvdata(dev);
	काष्ठा drm_device *drm_dev = data;
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_connector *connector;
	काष्ठा device_node *remote = शून्य;
	काष्ठा device_node  *port, *endpoपूर्णांक;
	पूर्णांक ret = 0, child_count = 0;
	स्थिर अक्षर *name;
	u32 endpoपूर्णांक_id = 0;

	lvds->drm_dev = drm_dev;
	port = of_graph_get_port_by_id(dev->of_node, 1);
	अगर (!port) अणु
		DRM_DEV_ERROR(dev,
			      "can't found port point, please init lvds panel port!\n");
		वापस -EINVAL;
	पूर्ण
	क्रम_each_child_of_node(port, endpoपूर्णांक) अणु
		child_count++;
		of_property_पढ़ो_u32(endpoपूर्णांक, "reg", &endpoपूर्णांक_id);
		ret = drm_of_find_panel_or_bridge(dev->of_node, 1, endpoपूर्णांक_id,
						  &lvds->panel, &lvds->bridge);
		अगर (!ret) अणु
			of_node_put(endpoपूर्णांक);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!child_count) अणु
		DRM_DEV_ERROR(dev, "lvds port does not have any children\n");
		ret = -EINVAL;
		जाओ err_put_port;
	पूर्ण अन्यथा अगर (ret) अणु
		DRM_DEV_ERROR(dev, "failed to find panel and bridge node\n");
		ret = -EPROBE_DEFER;
		जाओ err_put_port;
	पूर्ण
	अगर (lvds->panel)
		remote = lvds->panel->dev->of_node;
	अन्यथा
		remote = lvds->bridge->of_node;
	अगर (of_property_पढ़ो_string(dev->of_node, "rockchip,output", &name))
		/* शेष set it as output rgb */
		lvds->output = DISPLAY_OUTPUT_RGB;
	अन्यथा
		lvds->output = rockchip_lvds_name_to_output(name);

	अगर (lvds->output < 0) अणु
		DRM_DEV_ERROR(dev, "invalid output type [%s]\n", name);
		ret = lvds->output;
		जाओ err_put_remote;
	पूर्ण

	अगर (of_property_पढ़ो_string(remote, "data-mapping", &name))
		/* शेष set it as क्रमmat vesa 18 */
		lvds->क्रमmat = LVDS_VESA_18;
	अन्यथा
		lvds->क्रमmat = rockchip_lvds_name_to_क्रमmat(name);

	अगर (lvds->क्रमmat < 0) अणु
		DRM_DEV_ERROR(dev, "invalid data-mapping format [%s]\n", name);
		ret = lvds->क्रमmat;
		जाओ err_put_remote;
	पूर्ण

	encoder = &lvds->encoder;
	encoder->possible_crtcs = drm_of_find_possible_crtcs(drm_dev,
							     dev->of_node);

	ret = drm_simple_encoder_init(drm_dev, encoder, DRM_MODE_ENCODER_LVDS);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(drm_dev->dev,
			      "failed to initialize encoder: %d\n", ret);
		जाओ err_put_remote;
	पूर्ण

	drm_encoder_helper_add(encoder, lvds->soc_data->helper_funcs);

	अगर (lvds->panel) अणु
		connector = &lvds->connector;
		connector->dpms = DRM_MODE_DPMS_OFF;
		ret = drm_connector_init(drm_dev, connector,
					 &rockchip_lvds_connector_funcs,
					 DRM_MODE_CONNECTOR_LVDS);
		अगर (ret < 0) अणु
			DRM_DEV_ERROR(drm_dev->dev,
				      "failed to initialize connector: %d\n", ret);
			जाओ err_मुक्त_encoder;
		पूर्ण

		drm_connector_helper_add(connector,
					 &rockchip_lvds_connector_helper_funcs);

		ret = drm_connector_attach_encoder(connector, encoder);
		अगर (ret < 0) अणु
			DRM_DEV_ERROR(drm_dev->dev,
				      "failed to attach encoder: %d\n", ret);
			जाओ err_मुक्त_connector;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = drm_bridge_attach(encoder, lvds->bridge, शून्य, 0);
		अगर (ret) अणु
			DRM_DEV_ERROR(drm_dev->dev,
				      "failed to attach bridge: %d\n", ret);
			जाओ err_मुक्त_encoder;
		पूर्ण
	पूर्ण

	pm_runसमय_enable(dev);
	of_node_put(remote);
	of_node_put(port);

	वापस 0;

err_मुक्त_connector:
	drm_connector_cleanup(connector);
err_मुक्त_encoder:
	drm_encoder_cleanup(encoder);
err_put_remote:
	of_node_put(remote);
err_put_port:
	of_node_put(port);

	वापस ret;
पूर्ण

अटल व्योम rockchip_lvds_unbind(काष्ठा device *dev, काष्ठा device *master,
				व्योम *data)
अणु
	काष्ठा rockchip_lvds *lvds = dev_get_drvdata(dev);
	स्थिर काष्ठा drm_encoder_helper_funcs *encoder_funcs;

	encoder_funcs = lvds->soc_data->helper_funcs;
	encoder_funcs->disable(&lvds->encoder);
	pm_runसमय_disable(dev);
	drm_connector_cleanup(&lvds->connector);
	drm_encoder_cleanup(&lvds->encoder);
पूर्ण

अटल स्थिर काष्ठा component_ops rockchip_lvds_component_ops = अणु
	.bind = rockchip_lvds_bind,
	.unbind = rockchip_lvds_unbind,
पूर्ण;

अटल पूर्णांक rockchip_lvds_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rockchip_lvds *lvds;
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक ret;

	अगर (!dev->of_node)
		वापस -ENODEV;

	lvds = devm_kzalloc(&pdev->dev, माप(*lvds), GFP_KERNEL);
	अगर (!lvds)
		वापस -ENOMEM;

	lvds->dev = dev;
	match = of_match_node(rockchip_lvds_dt_ids, dev->of_node);
	अगर (!match)
		वापस -ENODEV;
	lvds->soc_data = match->data;

	lvds->grf = syscon_regmap_lookup_by_phandle(dev->of_node,
						    "rockchip,grf");
	अगर (IS_ERR(lvds->grf)) अणु
		DRM_DEV_ERROR(dev, "missing rockchip,grf property\n");
		वापस PTR_ERR(lvds->grf);
	पूर्ण

	ret = lvds->soc_data->probe(pdev, lvds);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "Platform initialization failed\n");
		वापस ret;
	पूर्ण

	dev_set_drvdata(dev, lvds);

	ret = component_add(&pdev->dev, &rockchip_lvds_component_ops);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dev, "failed to add component\n");
		clk_unprepare(lvds->pclk);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rockchip_lvds_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rockchip_lvds *lvds = platक्रमm_get_drvdata(pdev);

	component_del(&pdev->dev, &rockchip_lvds_component_ops);
	clk_unprepare(lvds->pclk);

	वापस 0;
पूर्ण

काष्ठा platक्रमm_driver rockchip_lvds_driver = अणु
	.probe = rockchip_lvds_probe,
	.हटाओ = rockchip_lvds_हटाओ,
	.driver = अणु
		   .name = "rockchip-lvds",
		   .of_match_table = of_match_ptr(rockchip_lvds_dt_ids),
	पूर्ण,
पूर्ण;
