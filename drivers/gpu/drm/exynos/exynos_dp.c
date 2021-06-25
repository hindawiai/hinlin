<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Samsung SoC DP (Display Port) पूर्णांकerface driver.
 *
 * Copyright (C) 2012 Samsung Electronics Co., Ltd.
 * Author: Jingoo Han <jg1.han@samsung.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <video/of_display_timing.h>
#समावेश <video/of_videomode.h>
#समावेश <video/videomode.h>

#समावेश <drm/bridge/analogix_dp.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>
#समावेश <drm/exynos_drm.h>

#समावेश "exynos_drm_crtc.h"

#घोषणा to_dp(nm)	container_of(nm, काष्ठा exynos_dp_device, nm)

काष्ठा exynos_dp_device अणु
	काष्ठा drm_encoder         encoder;
	काष्ठा drm_connector       *connector;
	काष्ठा drm_bridge          *ptn_bridge;
	काष्ठा drm_device          *drm_dev;
	काष्ठा device              *dev;

	काष्ठा videomode           vm;
	काष्ठा analogix_dp_device *adp;
	काष्ठा analogix_dp_plat_data plat_data;
पूर्ण;

अटल पूर्णांक exynos_dp_crtc_घड़ी_enable(काष्ठा analogix_dp_plat_data *plat_data,
				bool enable)
अणु
	काष्ठा exynos_dp_device *dp = to_dp(plat_data);
	काष्ठा drm_encoder *encoder = &dp->encoder;

	अगर (!encoder->crtc)
		वापस -EPERM;

	exynos_drm_pipe_clk_enable(to_exynos_crtc(encoder->crtc), enable);

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_dp_घातeron(काष्ठा analogix_dp_plat_data *plat_data)
अणु
	वापस exynos_dp_crtc_घड़ी_enable(plat_data, true);
पूर्ण

अटल पूर्णांक exynos_dp_घातeroff(काष्ठा analogix_dp_plat_data *plat_data)
अणु
	वापस exynos_dp_crtc_घड़ी_enable(plat_data, false);
पूर्ण

अटल पूर्णांक exynos_dp_get_modes(काष्ठा analogix_dp_plat_data *plat_data,
			       काष्ठा drm_connector *connector)
अणु
	काष्ठा exynos_dp_device *dp = to_dp(plat_data);
	काष्ठा drm_display_mode *mode;
	पूर्णांक num_modes = 0;

	अगर (dp->plat_data.panel)
		वापस num_modes;

	mode = drm_mode_create(connector->dev);
	अगर (!mode) अणु
		DRM_DEV_ERROR(dp->dev,
			      "failed to create a new display mode.\n");
		वापस num_modes;
	पूर्ण

	drm_display_mode_from_videomode(&dp->vm, mode);
	connector->display_info.width_mm = mode->width_mm;
	connector->display_info.height_mm = mode->height_mm;

	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	drm_mode_set_name(mode);
	drm_mode_probed_add(connector, mode);

	वापस num_modes + 1;
पूर्ण

अटल पूर्णांक exynos_dp_bridge_attach(काष्ठा analogix_dp_plat_data *plat_data,
				   काष्ठा drm_bridge *bridge,
				   काष्ठा drm_connector *connector)
अणु
	काष्ठा exynos_dp_device *dp = to_dp(plat_data);
	पूर्णांक ret;

	dp->connector = connector;

	/* Pre-empt DP connector creation अगर there's a bridge */
	अगर (dp->ptn_bridge) अणु
		ret = drm_bridge_attach(&dp->encoder, dp->ptn_bridge, bridge,
					0);
		अगर (ret) अणु
			DRM_DEV_ERROR(dp->dev,
				      "Failed to attach bridge to drm\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम exynos_dp_mode_set(काष्ठा drm_encoder *encoder,
			       काष्ठा drm_display_mode *mode,
			       काष्ठा drm_display_mode *adjusted_mode)
अणु
पूर्ण

अटल व्योम exynos_dp_nop(काष्ठा drm_encoder *encoder)
अणु
	/* करो nothing */
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs exynos_dp_encoder_helper_funcs = अणु
	.mode_set = exynos_dp_mode_set,
	.enable = exynos_dp_nop,
	.disable = exynos_dp_nop,
पूर्ण;

अटल पूर्णांक exynos_dp_dt_parse_panel(काष्ठा exynos_dp_device *dp)
अणु
	पूर्णांक ret;

	ret = of_get_videomode(dp->dev->of_node, &dp->vm, OF_USE_NATIVE_MODE);
	अगर (ret) अणु
		DRM_DEV_ERROR(dp->dev,
			      "failed: of_get_videomode() : %d\n", ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक exynos_dp_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा exynos_dp_device *dp = dev_get_drvdata(dev);
	काष्ठा drm_encoder *encoder = &dp->encoder;
	काष्ठा drm_device *drm_dev = data;
	पूर्णांक ret;

	dp->drm_dev = drm_dev;

	अगर (!dp->plat_data.panel && !dp->ptn_bridge) अणु
		ret = exynos_dp_dt_parse_panel(dp);
		अगर (ret)
			वापस ret;
	पूर्ण

	drm_simple_encoder_init(drm_dev, encoder, DRM_MODE_ENCODER_TMDS);

	drm_encoder_helper_add(encoder, &exynos_dp_encoder_helper_funcs);

	ret = exynos_drm_set_possible_crtcs(encoder, EXYNOS_DISPLAY_TYPE_LCD);
	अगर (ret < 0)
		वापस ret;

	dp->plat_data.encoder = encoder;

	ret = analogix_dp_bind(dp->adp, dp->drm_dev);
	अगर (ret)
		dp->encoder.funcs->destroy(&dp->encoder);

	वापस ret;
पूर्ण

अटल व्योम exynos_dp_unbind(काष्ठा device *dev, काष्ठा device *master,
			     व्योम *data)
अणु
	काष्ठा exynos_dp_device *dp = dev_get_drvdata(dev);

	analogix_dp_unbind(dp->adp);
	dp->encoder.funcs->destroy(&dp->encoder);
पूर्ण

अटल स्थिर काष्ठा component_ops exynos_dp_ops = अणु
	.bind	= exynos_dp_bind,
	.unbind	= exynos_dp_unbind,
पूर्ण;

अटल पूर्णांक exynos_dp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np;
	काष्ठा exynos_dp_device *dp;
	काष्ठा drm_panel *panel;
	काष्ठा drm_bridge *bridge;
	पूर्णांक ret;

	dp = devm_kzalloc(&pdev->dev, माप(काष्ठा exynos_dp_device),
			  GFP_KERNEL);
	अगर (!dp)
		वापस -ENOMEM;

	dp->dev = dev;
	/*
	 * We just use the drvdata until driver run पूर्णांकo component
	 * add function, and then we would set drvdata to null, so
	 * that analogix dp driver would take अक्षरge of the drvdata.
	 */
	platक्रमm_set_drvdata(pdev, dp);

	/* This is क्रम the backward compatibility. */
	np = of_parse_phandle(dev->of_node, "panel", 0);
	अगर (np) अणु
		dp->plat_data.panel = of_drm_find_panel(np);

		of_node_put(np);
		अगर (IS_ERR(dp->plat_data.panel))
			वापस PTR_ERR(dp->plat_data.panel);

		जाओ out;
	पूर्ण

	ret = drm_of_find_panel_or_bridge(dev->of_node, 0, 0, &panel, &bridge);
	अगर (ret)
		वापस ret;

	/* The remote port can be either a panel or a bridge */
	dp->plat_data.panel = panel;
	dp->plat_data.dev_type = EXYNOS_DP;
	dp->plat_data.घातer_on_start = exynos_dp_घातeron;
	dp->plat_data.घातer_off = exynos_dp_घातeroff;
	dp->plat_data.attach = exynos_dp_bridge_attach;
	dp->plat_data.get_modes = exynos_dp_get_modes;
	dp->plat_data.skip_connector = !!bridge;

	dp->ptn_bridge = bridge;

out:
	dp->adp = analogix_dp_probe(dev, &dp->plat_data);
	अगर (IS_ERR(dp->adp))
		वापस PTR_ERR(dp->adp);

	वापस component_add(&pdev->dev, &exynos_dp_ops);
पूर्ण

अटल पूर्णांक exynos_dp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा exynos_dp_device *dp = platक्रमm_get_drvdata(pdev);

	component_del(&pdev->dev, &exynos_dp_ops);
	analogix_dp_हटाओ(dp->adp);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक exynos_dp_suspend(काष्ठा device *dev)
अणु
	काष्ठा exynos_dp_device *dp = dev_get_drvdata(dev);

	वापस analogix_dp_suspend(dp->adp);
पूर्ण

अटल पूर्णांक exynos_dp_resume(काष्ठा device *dev)
अणु
	काष्ठा exynos_dp_device *dp = dev_get_drvdata(dev);

	वापस analogix_dp_resume(dp->adp);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops exynos_dp_pm_ops = अणु
	SET_RUNTIME_PM_OPS(exynos_dp_suspend, exynos_dp_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id exynos_dp_match[] = अणु
	अणु .compatible = "samsung,exynos5-dp" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, exynos_dp_match);

काष्ठा platक्रमm_driver dp_driver = अणु
	.probe		= exynos_dp_probe,
	.हटाओ		= exynos_dp_हटाओ,
	.driver		= अणु
		.name	= "exynos-dp",
		.owner	= THIS_MODULE,
		.pm	= &exynos_dp_pm_ops,
		.of_match_table = exynos_dp_match,
	पूर्ण,
पूर्ण;

MODULE_AUTHOR("Jingoo Han <jg1.han@samsung.com>");
MODULE_DESCRIPTION("Samsung Specific Analogix-DP Driver Extension");
MODULE_LICENSE("GPL v2");
