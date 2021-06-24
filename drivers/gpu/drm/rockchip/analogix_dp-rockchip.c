<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Rockchip SoC DP (Display Port) पूर्णांकerface driver.
 *
 * Copyright (C) Fuzhou Rockchip Electronics Co., Ltd.
 * Author: Andy Yan <andy.yan@rock-chips.com>
 *         Yakir Yang <ykk@rock-chips.com>
 *         Jeff Chen <jeff.chen@rock-chips.com>
 */

#समावेश <linux/component.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/clk.h>

#समावेश <video/of_videomode.h>
#समावेश <video/videomode.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/bridge/analogix_dp.h>
#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "rockchip_drm_drv.h"
#समावेश "rockchip_drm_vop.h"

#घोषणा RK3288_GRF_SOC_CON6		0x25c
#घोषणा RK3288_EDP_LCDC_SEL		BIT(5)
#घोषणा RK3399_GRF_SOC_CON20		0x6250
#घोषणा RK3399_EDP_LCDC_SEL		BIT(5)

#घोषणा HIWORD_UPDATE(val, mask)	(val | (mask) << 16)

#घोषणा PSR_WAIT_LINE_FLAG_TIMEOUT_MS	100

#घोषणा to_dp(nm)	container_of(nm, काष्ठा rockchip_dp_device, nm)

/**
 * काष्ठा rockchip_dp_chip_data - splite the grf setting of kind of chips
 * @lcdsel_grf_reg: grf रेजिस्टर offset of lcdc select
 * @lcdsel_big: reg value of selecting vop big क्रम eDP
 * @lcdsel_lit: reg value of selecting vop little क्रम eDP
 * @chip_type: specअगरic chip type
 */
काष्ठा rockchip_dp_chip_data अणु
	u32	lcdsel_grf_reg;
	u32	lcdsel_big;
	u32	lcdsel_lit;
	u32	chip_type;
पूर्ण;

काष्ठा rockchip_dp_device अणु
	काष्ठा drm_device        *drm_dev;
	काष्ठा device            *dev;
	काष्ठा drm_encoder       encoder;
	काष्ठा drm_display_mode  mode;

	काष्ठा clk               *pclk;
	काष्ठा clk               *grfclk;
	काष्ठा regmap            *grf;
	काष्ठा reset_control     *rst;

	स्थिर काष्ठा rockchip_dp_chip_data *data;

	काष्ठा analogix_dp_device *adp;
	काष्ठा analogix_dp_plat_data plat_data;
पूर्ण;

अटल पूर्णांक rockchip_dp_pre_init(काष्ठा rockchip_dp_device *dp)
अणु
	reset_control_निश्चित(dp->rst);
	usleep_range(10, 20);
	reset_control_deनिश्चित(dp->rst);

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_dp_घातeron_start(काष्ठा analogix_dp_plat_data *plat_data)
अणु
	काष्ठा rockchip_dp_device *dp = to_dp(plat_data);
	पूर्णांक ret;

	ret = clk_prepare_enable(dp->pclk);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dp->dev, "failed to enable pclk %d\n", ret);
		वापस ret;
	पूर्ण

	ret = rockchip_dp_pre_init(dp);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dp->dev, "failed to dp pre init %d\n", ret);
		clk_disable_unprepare(dp->pclk);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rockchip_dp_घातerकरोwn(काष्ठा analogix_dp_plat_data *plat_data)
अणु
	काष्ठा rockchip_dp_device *dp = to_dp(plat_data);

	clk_disable_unprepare(dp->pclk);

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_dp_get_modes(काष्ठा analogix_dp_plat_data *plat_data,
				 काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_display_info *di = &connector->display_info;
	/* VOP couldn't output YUV video क्रमmat क्रम eDP rightly */
	u32 mask = DRM_COLOR_FORMAT_YCRCB444 | DRM_COLOR_FORMAT_YCRCB422;

	अगर ((di->color_क्रमmats & mask)) अणु
		DRM_DEBUG_KMS("Swapping display color format from YUV to RGB\n");
		di->color_क्रमmats &= ~mask;
		di->color_क्रमmats |= DRM_COLOR_FORMAT_RGB444;
		di->bpc = 8;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool
rockchip_dp_drm_encoder_mode_fixup(काष्ठा drm_encoder *encoder,
				   स्थिर काष्ठा drm_display_mode *mode,
				   काष्ठा drm_display_mode *adjusted_mode)
अणु
	/* करो nothing */
	वापस true;
पूर्ण

अटल व्योम rockchip_dp_drm_encoder_mode_set(काष्ठा drm_encoder *encoder,
					     काष्ठा drm_display_mode *mode,
					     काष्ठा drm_display_mode *adjusted)
अणु
	/* करो nothing */
पूर्ण

अटल
काष्ठा drm_crtc *rockchip_dp_drm_get_new_crtc(काष्ठा drm_encoder *encoder,
					      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_state *conn_state;

	connector = drm_atomic_get_new_connector_क्रम_encoder(state, encoder);
	अगर (!connector)
		वापस शून्य;

	conn_state = drm_atomic_get_new_connector_state(state, connector);
	अगर (!conn_state)
		वापस शून्य;

	वापस conn_state->crtc;
पूर्ण

अटल व्योम rockchip_dp_drm_encoder_enable(काष्ठा drm_encoder *encoder,
					   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा rockchip_dp_device *dp = to_dp(encoder);
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *old_crtc_state;
	पूर्णांक ret;
	u32 val;

	crtc = rockchip_dp_drm_get_new_crtc(encoder, state);
	अगर (!crtc)
		वापस;

	old_crtc_state = drm_atomic_get_old_crtc_state(state, crtc);
	/* Coming back from self refresh, nothing to करो */
	अगर (old_crtc_state && old_crtc_state->self_refresh_active)
		वापस;

	ret = drm_of_encoder_active_endpoपूर्णांक_id(dp->dev->of_node, encoder);
	अगर (ret < 0)
		वापस;

	अगर (ret)
		val = dp->data->lcdsel_lit;
	अन्यथा
		val = dp->data->lcdsel_big;

	DRM_DEV_DEBUG(dp->dev, "vop %s output to dp\n", (ret) ? "LIT" : "BIG");

	ret = clk_prepare_enable(dp->grfclk);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dp->dev, "failed to enable grfclk %d\n", ret);
		वापस;
	पूर्ण

	ret = regmap_ग_लिखो(dp->grf, dp->data->lcdsel_grf_reg, val);
	अगर (ret != 0)
		DRM_DEV_ERROR(dp->dev, "Could not write to GRF: %d\n", ret);

	clk_disable_unprepare(dp->grfclk);
पूर्ण

अटल व्योम rockchip_dp_drm_encoder_disable(काष्ठा drm_encoder *encoder,
					    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा rockchip_dp_device *dp = to_dp(encoder);
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *new_crtc_state = शून्य;
	पूर्णांक ret;

	crtc = rockchip_dp_drm_get_new_crtc(encoder, state);
	/* No crtc means we're करोing a full shutकरोwn */
	अगर (!crtc)
		वापस;

	new_crtc_state = drm_atomic_get_new_crtc_state(state, crtc);
	/* If we're not entering self-refresh, no need to रुको क्रम vact */
	अगर (!new_crtc_state || !new_crtc_state->self_refresh_active)
		वापस;

	ret = rockchip_drm_रुको_vact_end(crtc, PSR_WAIT_LINE_FLAG_TIMEOUT_MS);
	अगर (ret)
		DRM_DEV_ERROR(dp->dev, "line flag irq timed out\n");
पूर्ण

अटल पूर्णांक
rockchip_dp_drm_encoder_atomic_check(काष्ठा drm_encoder *encoder,
				      काष्ठा drm_crtc_state *crtc_state,
				      काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा rockchip_crtc_state *s = to_rockchip_crtc_state(crtc_state);
	काष्ठा drm_display_info *di = &conn_state->connector->display_info;

	/*
	 * The hardware IC deचिन्हित that VOP must output the RGB10 video
	 * क्रमmat to eDP controller, and अगर eDP panel only support RGB8,
	 * then eDP controller should cut करोwn the video data, not via VOP
	 * controller, that's why we need to hardcode the VOP output mode
	 * to RGA10 here.
	 */

	s->output_mode = ROCKCHIP_OUT_MODE_AAAA;
	s->output_type = DRM_MODE_CONNECTOR_eDP;
	s->output_bpc = di->bpc;

	वापस 0;
पूर्ण

अटल काष्ठा drm_encoder_helper_funcs rockchip_dp_encoder_helper_funcs = अणु
	.mode_fixup = rockchip_dp_drm_encoder_mode_fixup,
	.mode_set = rockchip_dp_drm_encoder_mode_set,
	.atomic_enable = rockchip_dp_drm_encoder_enable,
	.atomic_disable = rockchip_dp_drm_encoder_disable,
	.atomic_check = rockchip_dp_drm_encoder_atomic_check,
पूर्ण;

अटल पूर्णांक rockchip_dp_of_probe(काष्ठा rockchip_dp_device *dp)
अणु
	काष्ठा device *dev = dp->dev;
	काष्ठा device_node *np = dev->of_node;

	dp->grf = syscon_regmap_lookup_by_phandle(np, "rockchip,grf");
	अगर (IS_ERR(dp->grf)) अणु
		DRM_DEV_ERROR(dev, "failed to get rockchip,grf property\n");
		वापस PTR_ERR(dp->grf);
	पूर्ण

	dp->grfclk = devm_clk_get(dev, "grf");
	अगर (PTR_ERR(dp->grfclk) == -ENOENT) अणु
		dp->grfclk = शून्य;
	पूर्ण अन्यथा अगर (PTR_ERR(dp->grfclk) == -EPROBE_DEFER) अणु
		वापस -EPROBE_DEFER;
	पूर्ण अन्यथा अगर (IS_ERR(dp->grfclk)) अणु
		DRM_DEV_ERROR(dev, "failed to get grf clock\n");
		वापस PTR_ERR(dp->grfclk);
	पूर्ण

	dp->pclk = devm_clk_get(dev, "pclk");
	अगर (IS_ERR(dp->pclk)) अणु
		DRM_DEV_ERROR(dev, "failed to get pclk property\n");
		वापस PTR_ERR(dp->pclk);
	पूर्ण

	dp->rst = devm_reset_control_get(dev, "dp");
	अगर (IS_ERR(dp->rst)) अणु
		DRM_DEV_ERROR(dev, "failed to get dp reset control\n");
		वापस PTR_ERR(dp->rst);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_dp_drm_create_encoder(काष्ठा rockchip_dp_device *dp)
अणु
	काष्ठा drm_encoder *encoder = &dp->encoder;
	काष्ठा drm_device *drm_dev = dp->drm_dev;
	काष्ठा device *dev = dp->dev;
	पूर्णांक ret;

	encoder->possible_crtcs = drm_of_find_possible_crtcs(drm_dev,
							     dev->of_node);
	DRM_DEBUG_KMS("possible_crtcs = 0x%x\n", encoder->possible_crtcs);

	ret = drm_simple_encoder_init(drm_dev, encoder,
				      DRM_MODE_ENCODER_TMDS);
	अगर (ret) अणु
		DRM_ERROR("failed to initialize encoder with drm\n");
		वापस ret;
	पूर्ण

	drm_encoder_helper_add(encoder, &rockchip_dp_encoder_helper_funcs);

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_dp_bind(काष्ठा device *dev, काष्ठा device *master,
			    व्योम *data)
अणु
	काष्ठा rockchip_dp_device *dp = dev_get_drvdata(dev);
	काष्ठा drm_device *drm_dev = data;
	पूर्णांक ret;

	dp->drm_dev = drm_dev;

	ret = rockchip_dp_drm_create_encoder(dp);
	अगर (ret) अणु
		DRM_ERROR("failed to create drm encoder\n");
		वापस ret;
	पूर्ण

	dp->plat_data.encoder = &dp->encoder;

	ret = analogix_dp_bind(dp->adp, drm_dev);
	अगर (ret)
		जाओ err_cleanup_encoder;

	वापस 0;
err_cleanup_encoder:
	dp->encoder.funcs->destroy(&dp->encoder);
	वापस ret;
पूर्ण

अटल व्योम rockchip_dp_unbind(काष्ठा device *dev, काष्ठा device *master,
			       व्योम *data)
अणु
	काष्ठा rockchip_dp_device *dp = dev_get_drvdata(dev);

	analogix_dp_unbind(dp->adp);
	dp->encoder.funcs->destroy(&dp->encoder);
पूर्ण

अटल स्थिर काष्ठा component_ops rockchip_dp_component_ops = अणु
	.bind = rockchip_dp_bind,
	.unbind = rockchip_dp_unbind,
पूर्ण;

अटल पूर्णांक rockchip_dp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा rockchip_dp_chip_data *dp_data;
	काष्ठा drm_panel *panel = शून्य;
	काष्ठा rockchip_dp_device *dp;
	पूर्णांक ret;

	dp_data = of_device_get_match_data(dev);
	अगर (!dp_data)
		वापस -ENODEV;

	ret = drm_of_find_panel_or_bridge(dev->of_node, 1, 0, &panel, शून्य);
	अगर (ret < 0)
		वापस ret;

	dp = devm_kzalloc(dev, माप(*dp), GFP_KERNEL);
	अगर (!dp)
		वापस -ENOMEM;

	dp->dev = dev;
	dp->adp = ERR_PTR(-ENODEV);
	dp->data = dp_data;
	dp->plat_data.panel = panel;
	dp->plat_data.dev_type = dp->data->chip_type;
	dp->plat_data.घातer_on_start = rockchip_dp_घातeron_start;
	dp->plat_data.घातer_off = rockchip_dp_घातerकरोwn;
	dp->plat_data.get_modes = rockchip_dp_get_modes;

	ret = rockchip_dp_of_probe(dp);
	अगर (ret < 0)
		वापस ret;

	platक्रमm_set_drvdata(pdev, dp);

	dp->adp = analogix_dp_probe(dev, &dp->plat_data);
	अगर (IS_ERR(dp->adp))
		वापस PTR_ERR(dp->adp);

	वापस component_add(dev, &rockchip_dp_component_ops);
पूर्ण

अटल पूर्णांक rockchip_dp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rockchip_dp_device *dp = platक्रमm_get_drvdata(pdev);

	component_del(&pdev->dev, &rockchip_dp_component_ops);
	analogix_dp_हटाओ(dp->adp);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक rockchip_dp_suspend(काष्ठा device *dev)
अणु
	काष्ठा rockchip_dp_device *dp = dev_get_drvdata(dev);

	अगर (IS_ERR(dp->adp))
		वापस 0;

	वापस analogix_dp_suspend(dp->adp);
पूर्ण

अटल पूर्णांक rockchip_dp_resume(काष्ठा device *dev)
अणु
	काष्ठा rockchip_dp_device *dp = dev_get_drvdata(dev);

	अगर (IS_ERR(dp->adp))
		वापस 0;

	वापस analogix_dp_resume(dp->adp);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops rockchip_dp_pm_ops = अणु
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend_late = rockchip_dp_suspend,
	.resume_early = rockchip_dp_resume,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा rockchip_dp_chip_data rk3399_edp = अणु
	.lcdsel_grf_reg = RK3399_GRF_SOC_CON20,
	.lcdsel_big = HIWORD_UPDATE(0, RK3399_EDP_LCDC_SEL),
	.lcdsel_lit = HIWORD_UPDATE(RK3399_EDP_LCDC_SEL, RK3399_EDP_LCDC_SEL),
	.chip_type = RK3399_EDP,
पूर्ण;

अटल स्थिर काष्ठा rockchip_dp_chip_data rk3288_dp = अणु
	.lcdsel_grf_reg = RK3288_GRF_SOC_CON6,
	.lcdsel_big = HIWORD_UPDATE(0, RK3288_EDP_LCDC_SEL),
	.lcdsel_lit = HIWORD_UPDATE(RK3288_EDP_LCDC_SEL, RK3288_EDP_LCDC_SEL),
	.chip_type = RK3288_DP,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rockchip_dp_dt_ids[] = अणु
	अणु.compatible = "rockchip,rk3288-dp", .data = &rk3288_dp पूर्ण,
	अणु.compatible = "rockchip,rk3399-edp", .data = &rk3399_edp पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rockchip_dp_dt_ids);

काष्ठा platक्रमm_driver rockchip_dp_driver = अणु
	.probe = rockchip_dp_probe,
	.हटाओ = rockchip_dp_हटाओ,
	.driver = अणु
		   .name = "rockchip-dp",
		   .pm = &rockchip_dp_pm_ops,
		   .of_match_table = of_match_ptr(rockchip_dp_dt_ids),
	पूर्ण,
पूर्ण;
