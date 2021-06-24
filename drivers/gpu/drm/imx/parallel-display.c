<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * i.MX drm driver - parallel display implementation
 *
 * Copyright (C) 2012 Sascha Hauer, Pengutronix
 */

#समावेश <linux/component.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/videodev2.h>

#समावेश <video/of_display_timing.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "imx-drm.h"

काष्ठा imx_parallel_display_encoder अणु
	काष्ठा drm_connector connector;
	काष्ठा drm_encoder encoder;
	काष्ठा drm_bridge bridge;
	काष्ठा imx_parallel_display *pd;
पूर्ण;

काष्ठा imx_parallel_display अणु
	काष्ठा device *dev;
	व्योम *edid;
	u32 bus_क्रमmat;
	u32 bus_flags;
	काष्ठा drm_display_mode mode;
	काष्ठा drm_panel *panel;
	काष्ठा drm_bridge *next_bridge;
पूर्ण;

अटल अंतरभूत काष्ठा imx_parallel_display *con_to_imxpd(काष्ठा drm_connector *c)
अणु
	वापस container_of(c, काष्ठा imx_parallel_display_encoder, connector)->pd;
पूर्ण

अटल अंतरभूत काष्ठा imx_parallel_display *bridge_to_imxpd(काष्ठा drm_bridge *b)
अणु
	वापस container_of(b, काष्ठा imx_parallel_display_encoder, bridge)->pd;
पूर्ण

अटल पूर्णांक imx_pd_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा imx_parallel_display *imxpd = con_to_imxpd(connector);
	काष्ठा device_node *np = imxpd->dev->of_node;
	पूर्णांक num_modes;

	num_modes = drm_panel_get_modes(imxpd->panel, connector);
	अगर (num_modes > 0)
		वापस num_modes;

	अगर (imxpd->edid) अणु
		drm_connector_update_edid_property(connector, imxpd->edid);
		num_modes = drm_add_edid_modes(connector, imxpd->edid);
	पूर्ण

	अगर (np) अणु
		काष्ठा drm_display_mode *mode = drm_mode_create(connector->dev);
		पूर्णांक ret;

		अगर (!mode)
			वापस -EINVAL;

		ret = of_get_drm_display_mode(np, &imxpd->mode,
					      &imxpd->bus_flags,
					      OF_USE_NATIVE_MODE);
		अगर (ret)
			वापस ret;

		drm_mode_copy(mode, &imxpd->mode);
		mode->type |= DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
		drm_mode_probed_add(connector, mode);
		num_modes++;
	पूर्ण

	वापस num_modes;
पूर्ण

अटल व्योम imx_pd_bridge_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा imx_parallel_display *imxpd = bridge_to_imxpd(bridge);

	drm_panel_prepare(imxpd->panel);
	drm_panel_enable(imxpd->panel);
पूर्ण

अटल व्योम imx_pd_bridge_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा imx_parallel_display *imxpd = bridge_to_imxpd(bridge);

	drm_panel_disable(imxpd->panel);
	drm_panel_unprepare(imxpd->panel);
पूर्ण

अटल स्थिर u32 imx_pd_bus_fmts[] = अणु
	MEDIA_BUS_FMT_RGB888_1X24,
	MEDIA_BUS_FMT_BGR888_1X24,
	MEDIA_BUS_FMT_GBR888_1X24,
	MEDIA_BUS_FMT_RGB666_1X18,
	MEDIA_BUS_FMT_RGB666_1X24_CPADHI,
	MEDIA_BUS_FMT_RGB565_1X16,
पूर्ण;

अटल u32 *
imx_pd_bridge_atomic_get_output_bus_fmts(काष्ठा drm_bridge *bridge,
					 काष्ठा drm_bridge_state *bridge_state,
					 काष्ठा drm_crtc_state *crtc_state,
					 काष्ठा drm_connector_state *conn_state,
					 अचिन्हित पूर्णांक *num_output_fmts)
अणु
	काष्ठा drm_display_info *di = &conn_state->connector->display_info;
	काष्ठा imx_parallel_display *imxpd = bridge_to_imxpd(bridge);
	u32 *output_fmts;

	अगर (!imxpd->bus_क्रमmat && !di->num_bus_क्रमmats) अणु
		*num_output_fmts = ARRAY_SIZE(imx_pd_bus_fmts);
		वापस kmemdup(imx_pd_bus_fmts, माप(imx_pd_bus_fmts),
			       GFP_KERNEL);
	पूर्ण

	*num_output_fmts = 1;
	output_fmts = kदो_स्मृति(माप(*output_fmts), GFP_KERNEL);
	अगर (!output_fmts)
		वापस शून्य;

	अगर (!imxpd->bus_क्रमmat && di->num_bus_क्रमmats)
		output_fmts[0] = di->bus_क्रमmats[0];
	अन्यथा
		output_fmts[0] = imxpd->bus_क्रमmat;

	वापस output_fmts;
पूर्ण

अटल bool imx_pd_क्रमmat_supported(u32 output_fmt)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(imx_pd_bus_fmts); i++) अणु
		अगर (imx_pd_bus_fmts[i] == output_fmt)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल u32 *
imx_pd_bridge_atomic_get_input_bus_fmts(काष्ठा drm_bridge *bridge,
					काष्ठा drm_bridge_state *bridge_state,
					काष्ठा drm_crtc_state *crtc_state,
					काष्ठा drm_connector_state *conn_state,
					u32 output_fmt,
					अचिन्हित पूर्णांक *num_input_fmts)
अणु
	काष्ठा imx_parallel_display *imxpd = bridge_to_imxpd(bridge);
	u32 *input_fmts;

	/*
	 * If the next bridge करोes not support bus क्रमmat negotiation, let's
	 * use the अटल bus क्रमmat definition (imxpd->bus_क्रमmat) अगर it's
	 * specअगरied, RGB888 when it's not.
	 */
	अगर (output_fmt == MEDIA_BUS_FMT_FIXED)
		output_fmt = imxpd->bus_क्रमmat ? : MEDIA_BUS_FMT_RGB888_1X24;

	/* Now make sure the requested output क्रमmat is supported. */
	अगर ((imxpd->bus_क्रमmat && imxpd->bus_क्रमmat != output_fmt) ||
	    !imx_pd_क्रमmat_supported(output_fmt)) अणु
		*num_input_fmts = 0;
		वापस शून्य;
	पूर्ण

	*num_input_fmts = 1;
	input_fmts = kदो_स्मृति(माप(*input_fmts), GFP_KERNEL);
	अगर (!input_fmts)
		वापस शून्य;

	input_fmts[0] = output_fmt;
	वापस input_fmts;
पूर्ण

अटल पूर्णांक imx_pd_bridge_atomic_check(काष्ठा drm_bridge *bridge,
				      काष्ठा drm_bridge_state *bridge_state,
				      काष्ठा drm_crtc_state *crtc_state,
				      काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा imx_crtc_state *imx_crtc_state = to_imx_crtc_state(crtc_state);
	काष्ठा drm_display_info *di = &conn_state->connector->display_info;
	काष्ठा imx_parallel_display *imxpd = bridge_to_imxpd(bridge);
	काष्ठा drm_bridge_state *next_bridge_state = शून्य;
	काष्ठा drm_bridge *next_bridge;
	u32 bus_flags, bus_fmt;

	next_bridge = drm_bridge_get_next_bridge(bridge);
	अगर (next_bridge)
		next_bridge_state = drm_atomic_get_new_bridge_state(crtc_state->state,
								    next_bridge);

	अगर (next_bridge_state)
		bus_flags = next_bridge_state->input_bus_cfg.flags;
	अन्यथा अगर (di->num_bus_क्रमmats)
		bus_flags = di->bus_flags;
	अन्यथा
		bus_flags = imxpd->bus_flags;

	bus_fmt = bridge_state->input_bus_cfg.क्रमmat;
	अगर (!imx_pd_क्रमmat_supported(bus_fmt))
		वापस -EINVAL;

	अगर (bus_flags &
	    ~(DRM_BUS_FLAG_DE_LOW | DRM_BUS_FLAG_DE_HIGH |
	      DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE |
	      DRM_BUS_FLAG_PIXDATA_DRIVE_NEGEDGE)) अणु
		dev_warn(imxpd->dev, "invalid bus_flags (%x)\n", bus_flags);
		वापस -EINVAL;
	पूर्ण

	bridge_state->output_bus_cfg.flags = bus_flags;
	bridge_state->input_bus_cfg.flags = bus_flags;
	imx_crtc_state->bus_flags = bus_flags;
	imx_crtc_state->bus_क्रमmat = bridge_state->input_bus_cfg.क्रमmat;
	imx_crtc_state->di_hsync_pin = 2;
	imx_crtc_state->di_vsync_pin = 3;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs imx_pd_connector_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = imx_drm_connector_destroy,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_helper_funcs imx_pd_connector_helper_funcs = अणु
	.get_modes = imx_pd_connector_get_modes,
पूर्ण;

अटल स्थिर काष्ठा drm_bridge_funcs imx_pd_bridge_funcs = अणु
	.enable = imx_pd_bridge_enable,
	.disable = imx_pd_bridge_disable,
	.atomic_reset = drm_atomic_helper_bridge_reset,
	.atomic_duplicate_state = drm_atomic_helper_bridge_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_bridge_destroy_state,
	.atomic_check = imx_pd_bridge_atomic_check,
	.atomic_get_input_bus_fmts = imx_pd_bridge_atomic_get_input_bus_fmts,
	.atomic_get_output_bus_fmts = imx_pd_bridge_atomic_get_output_bus_fmts,
पूर्ण;

अटल पूर्णांक imx_pd_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा drm_device *drm = data;
	काष्ठा imx_parallel_display *imxpd = dev_get_drvdata(dev);
	काष्ठा imx_parallel_display_encoder *imxpd_encoder;
	काष्ठा drm_connector *connector;
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_bridge *bridge;
	पूर्णांक ret;

	imxpd_encoder = drmm_simple_encoder_alloc(drm, काष्ठा imx_parallel_display_encoder,
						  encoder, DRM_MODE_ENCODER_NONE);
	अगर (IS_ERR(imxpd_encoder))
		वापस PTR_ERR(imxpd_encoder);

	imxpd_encoder->pd = imxpd;
	connector = &imxpd_encoder->connector;
	encoder = &imxpd_encoder->encoder;
	bridge = &imxpd_encoder->bridge;

	ret = imx_drm_encoder_parse_of(drm, encoder, imxpd->dev->of_node);
	अगर (ret)
		वापस ret;

	/* set the connector's dpms to OFF so that
	 * drm_helper_connector_dpms() won't वापस
	 * immediately since the current state is ON
	 * at this poपूर्णांक.
	 */
	connector->dpms = DRM_MODE_DPMS_OFF;

	bridge->funcs = &imx_pd_bridge_funcs;
	drm_bridge_attach(encoder, bridge, शून्य, 0);

	अगर (imxpd->next_bridge) अणु
		ret = drm_bridge_attach(encoder, imxpd->next_bridge, bridge, 0);
		अगर (ret < 0) अणु
			dev_err(imxpd->dev, "failed to attach bridge: %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		drm_connector_helper_add(connector,
					 &imx_pd_connector_helper_funcs);
		drm_connector_init(drm, connector, &imx_pd_connector_funcs,
				   DRM_MODE_CONNECTOR_DPI);

		drm_connector_attach_encoder(connector, encoder);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा component_ops imx_pd_ops = अणु
	.bind	= imx_pd_bind,
पूर्ण;

अटल पूर्णांक imx_pd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	स्थिर u8 *edidp;
	काष्ठा imx_parallel_display *imxpd;
	पूर्णांक edid_len;
	पूर्णांक ret;
	u32 bus_क्रमmat = 0;
	स्थिर अक्षर *fmt;

	imxpd = devm_kzalloc(dev, माप(*imxpd), GFP_KERNEL);
	अगर (!imxpd)
		वापस -ENOMEM;

	/* port@1 is the output port */
	ret = drm_of_find_panel_or_bridge(np, 1, 0, &imxpd->panel,
					  &imxpd->next_bridge);
	अगर (ret && ret != -ENODEV)
		वापस ret;

	edidp = of_get_property(np, "edid", &edid_len);
	अगर (edidp)
		imxpd->edid = devm_kmemdup(dev, edidp, edid_len, GFP_KERNEL);

	ret = of_property_पढ़ो_string(np, "interface-pix-fmt", &fmt);
	अगर (!ret) अणु
		अगर (!म_भेद(fmt, "rgb24"))
			bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24;
		अन्यथा अगर (!म_भेद(fmt, "rgb565"))
			bus_क्रमmat = MEDIA_BUS_FMT_RGB565_1X16;
		अन्यथा अगर (!म_भेद(fmt, "bgr666"))
			bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X18;
		अन्यथा अगर (!म_भेद(fmt, "lvds666"))
			bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X24_CPADHI;
	पूर्ण
	imxpd->bus_क्रमmat = bus_क्रमmat;

	imxpd->dev = dev;

	platक्रमm_set_drvdata(pdev, imxpd);

	वापस component_add(dev, &imx_pd_ops);
पूर्ण

अटल पूर्णांक imx_pd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &imx_pd_ops);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id imx_pd_dt_ids[] = अणु
	अणु .compatible = "fsl,imx-parallel-display", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_pd_dt_ids);

अटल काष्ठा platक्रमm_driver imx_pd_driver = अणु
	.probe		= imx_pd_probe,
	.हटाओ		= imx_pd_हटाओ,
	.driver		= अणु
		.of_match_table = imx_pd_dt_ids,
		.name	= "imx-parallel-display",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(imx_pd_driver);

MODULE_DESCRIPTION("i.MX parallel display driver");
MODULE_AUTHOR("Sascha Hauer, Pengutronix");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:imx-parallel-display");
