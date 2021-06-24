<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Texas Instruments
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <video/display_timing.h>
#समावेश <video/of_display_timing.h>
#समावेश <video/videomode.h>

#समावेश <drm/drm_atomic_state_helper.h>
#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_modeset_helper_vtables.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "tilcdc_drv.h"
#समावेश "tilcdc_panel.h"

काष्ठा panel_module अणु
	काष्ठा tilcdc_module base;
	काष्ठा tilcdc_panel_info *info;
	काष्ठा display_timings *timings;
	काष्ठा backlight_device *backlight;
	काष्ठा gpio_desc *enable_gpio;
पूर्ण;
#घोषणा to_panel_module(x) container_of(x, काष्ठा panel_module, base)


/*
 * Encoder:
 */

काष्ठा panel_encoder अणु
	काष्ठा drm_encoder base;
	काष्ठा panel_module *mod;
पूर्ण;
#घोषणा to_panel_encoder(x) container_of(x, काष्ठा panel_encoder, base)

अटल व्योम panel_encoder_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	काष्ठा panel_encoder *panel_encoder = to_panel_encoder(encoder);
	काष्ठा backlight_device *backlight = panel_encoder->mod->backlight;
	काष्ठा gpio_desc *gpio = panel_encoder->mod->enable_gpio;

	अगर (backlight) अणु
		backlight->props.घातer = mode == DRM_MODE_DPMS_ON ?
					 FB_BLANK_UNBLANK : FB_BLANK_POWERDOWN;
		backlight_update_status(backlight);
	पूर्ण

	अगर (gpio)
		gpiod_set_value_cansleep(gpio,
					 mode == DRM_MODE_DPMS_ON ? 1 : 0);
पूर्ण

अटल व्योम panel_encoder_prepare(काष्ठा drm_encoder *encoder)
अणु
	panel_encoder_dpms(encoder, DRM_MODE_DPMS_OFF);
पूर्ण

अटल व्योम panel_encoder_commit(काष्ठा drm_encoder *encoder)
अणु
	panel_encoder_dpms(encoder, DRM_MODE_DPMS_ON);
पूर्ण

अटल व्योम panel_encoder_mode_set(काष्ठा drm_encoder *encoder,
		काष्ठा drm_display_mode *mode,
		काष्ठा drm_display_mode *adjusted_mode)
अणु
	/* nothing needed */
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs panel_encoder_helper_funcs = अणु
		.dpms           = panel_encoder_dpms,
		.prepare        = panel_encoder_prepare,
		.commit         = panel_encoder_commit,
		.mode_set       = panel_encoder_mode_set,
पूर्ण;

अटल काष्ठा drm_encoder *panel_encoder_create(काष्ठा drm_device *dev,
		काष्ठा panel_module *mod)
अणु
	काष्ठा panel_encoder *panel_encoder;
	काष्ठा drm_encoder *encoder;
	पूर्णांक ret;

	panel_encoder = devm_kzalloc(dev->dev, माप(*panel_encoder),
				     GFP_KERNEL);
	अगर (!panel_encoder)
		वापस शून्य;

	panel_encoder->mod = mod;

	encoder = &panel_encoder->base;
	encoder->possible_crtcs = 1;

	ret = drm_simple_encoder_init(dev, encoder, DRM_MODE_ENCODER_LVDS);
	अगर (ret < 0)
		जाओ fail;

	drm_encoder_helper_add(encoder, &panel_encoder_helper_funcs);

	वापस encoder;

fail:
	drm_encoder_cleanup(encoder);
	वापस शून्य;
पूर्ण

/*
 * Connector:
 */

काष्ठा panel_connector अणु
	काष्ठा drm_connector base;

	काष्ठा drm_encoder *encoder;  /* our connected encoder */
	काष्ठा panel_module *mod;
पूर्ण;
#घोषणा to_panel_connector(x) container_of(x, काष्ठा panel_connector, base)


अटल व्योम panel_connector_destroy(काष्ठा drm_connector *connector)
अणु
	drm_connector_unरेजिस्टर(connector);
	drm_connector_cleanup(connector);
पूर्ण

अटल पूर्णांक panel_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा panel_connector *panel_connector = to_panel_connector(connector);
	काष्ठा display_timings *timings = panel_connector->mod->timings;
	पूर्णांक i;

	क्रम (i = 0; i < timings->num_timings; i++) अणु
		काष्ठा drm_display_mode *mode;
		काष्ठा videomode vm;

		अगर (videomode_from_timings(timings, &vm, i))
			अवरोध;

		mode = drm_mode_create(dev);
		अगर (!mode)
			अवरोध;

		drm_display_mode_from_videomode(&vm, mode);

		mode->type = DRM_MODE_TYPE_DRIVER;

		अगर (timings->native_mode == i)
			mode->type |= DRM_MODE_TYPE_PREFERRED;

		drm_mode_set_name(mode);
		drm_mode_probed_add(connector, mode);
	पूर्ण

	वापस i;
पूर्ण

अटल काष्ठा drm_encoder *panel_connector_best_encoder(
		काष्ठा drm_connector *connector)
अणु
	काष्ठा panel_connector *panel_connector = to_panel_connector(connector);
	वापस panel_connector->encoder;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs panel_connector_funcs = अणु
	.destroy            = panel_connector_destroy,
	.fill_modes         = drm_helper_probe_single_connector_modes,
	.reset              = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_helper_funcs panel_connector_helper_funcs = अणु
	.get_modes          = panel_connector_get_modes,
	.best_encoder       = panel_connector_best_encoder,
पूर्ण;

अटल काष्ठा drm_connector *panel_connector_create(काष्ठा drm_device *dev,
		काष्ठा panel_module *mod, काष्ठा drm_encoder *encoder)
अणु
	काष्ठा panel_connector *panel_connector;
	काष्ठा drm_connector *connector;
	पूर्णांक ret;

	panel_connector = devm_kzalloc(dev->dev, माप(*panel_connector),
				       GFP_KERNEL);
	अगर (!panel_connector)
		वापस शून्य;

	panel_connector->encoder = encoder;
	panel_connector->mod = mod;

	connector = &panel_connector->base;

	drm_connector_init(dev, connector, &panel_connector_funcs,
			DRM_MODE_CONNECTOR_LVDS);
	drm_connector_helper_add(connector, &panel_connector_helper_funcs);

	connector->पूर्णांकerlace_allowed = 0;
	connector->द्विगुनscan_allowed = 0;

	ret = drm_connector_attach_encoder(connector, encoder);
	अगर (ret)
		जाओ fail;

	वापस connector;

fail:
	panel_connector_destroy(connector);
	वापस शून्य;
पूर्ण

/*
 * Module:
 */

अटल पूर्णांक panel_modeset_init(काष्ठा tilcdc_module *mod, काष्ठा drm_device *dev)
अणु
	काष्ठा panel_module *panel_mod = to_panel_module(mod);
	काष्ठा tilcdc_drm_निजी *priv = dev->dev_निजी;
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_connector *connector;

	encoder = panel_encoder_create(dev, panel_mod);
	अगर (!encoder)
		वापस -ENOMEM;

	connector = panel_connector_create(dev, panel_mod, encoder);
	अगर (!connector)
		वापस -ENOMEM;

	priv->encoders[priv->num_encoders++] = encoder;
	priv->connectors[priv->num_connectors++] = connector;

	tilcdc_crtc_set_panel_info(priv->crtc,
				   to_panel_encoder(encoder)->mod->info);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा tilcdc_module_ops panel_module_ops = अणु
		.modeset_init = panel_modeset_init,
पूर्ण;

/*
 * Device:
 */

/* maybe move this somewhere common अगर it is needed by other outमाला_दो? */
अटल काष्ठा tilcdc_panel_info *of_get_panel_info(काष्ठा device_node *np)
अणु
	काष्ठा device_node *info_np;
	काष्ठा tilcdc_panel_info *info;
	पूर्णांक ret = 0;

	अगर (!np) अणु
		pr_err("%s: no devicenode given\n", __func__);
		वापस शून्य;
	पूर्ण

	info_np = of_get_child_by_name(np, "panel-info");
	अगर (!info_np) अणु
		pr_err("%s: could not find panel-info node\n", __func__);
		वापस शून्य;
	पूर्ण

	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (!info)
		जाओ put_node;

	ret |= of_property_पढ़ो_u32(info_np, "ac-bias", &info->ac_bias);
	ret |= of_property_पढ़ो_u32(info_np, "ac-bias-intrpt", &info->ac_bias_पूर्णांकrpt);
	ret |= of_property_पढ़ो_u32(info_np, "dma-burst-sz", &info->dma_burst_sz);
	ret |= of_property_पढ़ो_u32(info_np, "bpp", &info->bpp);
	ret |= of_property_पढ़ो_u32(info_np, "fdd", &info->fdd);
	ret |= of_property_पढ़ो_u32(info_np, "sync-edge", &info->sync_edge);
	ret |= of_property_पढ़ो_u32(info_np, "sync-ctrl", &info->sync_ctrl);
	ret |= of_property_पढ़ो_u32(info_np, "raster-order", &info->raster_order);
	ret |= of_property_पढ़ो_u32(info_np, "fifo-th", &info->fअगरo_th);

	/* optional: */
	info->tft_alt_mode      = of_property_पढ़ो_bool(info_np, "tft-alt-mode");
	info->invert_pxl_clk    = of_property_पढ़ो_bool(info_np, "invert-pxl-clk");

	अगर (ret) अणु
		pr_err("%s: error reading panel-info properties\n", __func__);
		kमुक्त(info);
		info = शून्य;
	पूर्ण

put_node:
	of_node_put(info_np);
	वापस info;
पूर्ण

अटल पूर्णांक panel_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा backlight_device *backlight;
	काष्ठा panel_module *panel_mod;
	काष्ठा tilcdc_module *mod;
	काष्ठा pinctrl *pinctrl;
	पूर्णांक ret;

	/* bail out early अगर no DT data: */
	अगर (!node) अणु
		dev_err(&pdev->dev, "device-tree data is missing\n");
		वापस -ENXIO;
	पूर्ण

	panel_mod = devm_kzalloc(&pdev->dev, माप(*panel_mod), GFP_KERNEL);
	अगर (!panel_mod)
		वापस -ENOMEM;

	backlight = devm_of_find_backlight(&pdev->dev);
	अगर (IS_ERR(backlight))
		वापस PTR_ERR(backlight);
	panel_mod->backlight = backlight;

	panel_mod->enable_gpio = devm_gpiod_get_optional(&pdev->dev, "enable",
							 GPIOD_OUT_LOW);
	अगर (IS_ERR(panel_mod->enable_gpio)) अणु
		ret = PTR_ERR(panel_mod->enable_gpio);
		dev_err(&pdev->dev, "failed to request enable GPIO\n");
		जाओ fail_backlight;
	पूर्ण

	अगर (panel_mod->enable_gpio)
		dev_info(&pdev->dev, "found enable GPIO\n");

	mod = &panel_mod->base;
	pdev->dev.platक्रमm_data = mod;

	tilcdc_module_init(mod, "panel", &panel_module_ops);

	pinctrl = devm_pinctrl_get_select_शेष(&pdev->dev);
	अगर (IS_ERR(pinctrl))
		dev_warn(&pdev->dev, "pins are not configured\n");

	panel_mod->timings = of_get_display_timings(node);
	अगर (!panel_mod->timings) अणु
		dev_err(&pdev->dev, "could not get panel timings\n");
		ret = -EINVAL;
		जाओ fail_मुक्त;
	पूर्ण

	panel_mod->info = of_get_panel_info(node);
	अगर (!panel_mod->info) अणु
		dev_err(&pdev->dev, "could not get panel info\n");
		ret = -EINVAL;
		जाओ fail_timings;
	पूर्ण

	वापस 0;

fail_timings:
	display_timings_release(panel_mod->timings);

fail_मुक्त:
	tilcdc_module_cleanup(mod);

fail_backlight:
	अगर (panel_mod->backlight)
		put_device(&panel_mod->backlight->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक panel_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tilcdc_module *mod = dev_get_platdata(&pdev->dev);
	काष्ठा panel_module *panel_mod = to_panel_module(mod);
	काष्ठा backlight_device *backlight = panel_mod->backlight;

	अगर (backlight)
		put_device(&backlight->dev);

	display_timings_release(panel_mod->timings);

	tilcdc_module_cleanup(mod);
	kमुक्त(panel_mod->info);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id panel_of_match[] = अणु
		अणु .compatible = "ti,tilcdc,panel", पूर्ण,
		अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver panel_driver = अणु
	.probe = panel_probe,
	.हटाओ = panel_हटाओ,
	.driver = अणु
		.name = "tilcdc-panel",
		.of_match_table = panel_of_match,
	पूर्ण,
पूर्ण;

पूर्णांक __init tilcdc_panel_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&panel_driver);
पूर्ण

व्योम __निकास tilcdc_panel_fini(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&panel_driver);
पूर्ण
