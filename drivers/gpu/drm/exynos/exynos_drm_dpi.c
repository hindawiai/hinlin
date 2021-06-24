<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Exynos DRM Parallel output support.
 *
 * Copyright (c) 2014 Samsung Electronics Co., Ltd
 *
 * Contacts: Andrzej Hajda <a.hajda@samsung.com>
*/

#समावेश <linux/of_graph.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश <video/of_videomode.h>
#समावेश <video/videomode.h>

#समावेश "exynos_drm_crtc.h"

काष्ठा exynos_dpi अणु
	काष्ठा drm_encoder encoder;
	काष्ठा device *dev;
	काष्ठा device_node *panel_node;

	काष्ठा drm_panel *panel;
	काष्ठा drm_connector connector;

	काष्ठा videomode *vm;
पूर्ण;

#घोषणा connector_to_dpi(c) container_of(c, काष्ठा exynos_dpi, connector)

अटल अंतरभूत काष्ठा exynos_dpi *encoder_to_dpi(काष्ठा drm_encoder *e)
अणु
	वापस container_of(e, काष्ठा exynos_dpi, encoder);
पूर्ण

अटल क्रमागत drm_connector_status
exynos_dpi_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	वापस connector_status_connected;
पूर्ण

अटल व्योम exynos_dpi_connector_destroy(काष्ठा drm_connector *connector)
अणु
	drm_connector_unरेजिस्टर(connector);
	drm_connector_cleanup(connector);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs exynos_dpi_connector_funcs = अणु
	.detect = exynos_dpi_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = exynos_dpi_connector_destroy,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक exynos_dpi_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा exynos_dpi *ctx = connector_to_dpi(connector);

	/* fimd timings माला_लो precedence over panel modes */
	अगर (ctx->vm) अणु
		काष्ठा drm_display_mode *mode;

		mode = drm_mode_create(connector->dev);
		अगर (!mode) अणु
			DRM_DEV_ERROR(ctx->dev,
				      "failed to create a new display mode\n");
			वापस 0;
		पूर्ण
		drm_display_mode_from_videomode(ctx->vm, mode);
		mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
		drm_mode_probed_add(connector, mode);
		वापस 1;
	पूर्ण

	अगर (ctx->panel)
		वापस drm_panel_get_modes(ctx->panel, connector);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs exynos_dpi_connector_helper_funcs = अणु
	.get_modes = exynos_dpi_get_modes,
पूर्ण;

अटल पूर्णांक exynos_dpi_create_connector(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा exynos_dpi *ctx = encoder_to_dpi(encoder);
	काष्ठा drm_connector *connector = &ctx->connector;
	पूर्णांक ret;

	connector->polled = DRM_CONNECTOR_POLL_HPD;

	ret = drm_connector_init(encoder->dev, connector,
				 &exynos_dpi_connector_funcs,
				 DRM_MODE_CONNECTOR_VGA);
	अगर (ret) अणु
		DRM_DEV_ERROR(ctx->dev,
			      "failed to initialize connector with drm\n");
		वापस ret;
	पूर्ण

	drm_connector_helper_add(connector, &exynos_dpi_connector_helper_funcs);
	drm_connector_attach_encoder(connector, encoder);

	वापस 0;
पूर्ण

अटल व्योम exynos_dpi_mode_set(काष्ठा drm_encoder *encoder,
				काष्ठा drm_display_mode *mode,
				काष्ठा drm_display_mode *adjusted_mode)
अणु
पूर्ण

अटल व्योम exynos_dpi_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा exynos_dpi *ctx = encoder_to_dpi(encoder);

	अगर (ctx->panel) अणु
		drm_panel_prepare(ctx->panel);
		drm_panel_enable(ctx->panel);
	पूर्ण
पूर्ण

अटल व्योम exynos_dpi_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा exynos_dpi *ctx = encoder_to_dpi(encoder);

	अगर (ctx->panel) अणु
		drm_panel_disable(ctx->panel);
		drm_panel_unprepare(ctx->panel);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs exynos_dpi_encoder_helper_funcs = अणु
	.mode_set = exynos_dpi_mode_set,
	.enable = exynos_dpi_enable,
	.disable = exynos_dpi_disable,
पूर्ण;

क्रमागत अणु
	FIMD_PORT_IN0,
	FIMD_PORT_IN1,
	FIMD_PORT_IN2,
	FIMD_PORT_RGB,
	FIMD_PORT_WRB,
पूर्ण;

अटल पूर्णांक exynos_dpi_parse_dt(काष्ठा exynos_dpi *ctx)
अणु
	काष्ठा device *dev = ctx->dev;
	काष्ठा device_node *dn = dev->of_node;
	काष्ठा device_node *np;

	ctx->panel_node = of_graph_get_remote_node(dn, FIMD_PORT_RGB, 0);

	np = of_get_child_by_name(dn, "display-timings");
	अगर (np) अणु
		काष्ठा videomode *vm;
		पूर्णांक ret;

		of_node_put(np);

		vm = devm_kzalloc(dev, माप(*ctx->vm), GFP_KERNEL);
		अगर (!vm)
			वापस -ENOMEM;

		ret = of_get_videomode(dn, vm, 0);
		अगर (ret < 0) अणु
			devm_kमुक्त(dev, vm);
			वापस ret;
		पूर्ण

		ctx->vm = vm;

		वापस 0;
	पूर्ण

	अगर (!ctx->panel_node)
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक exynos_dpi_bind(काष्ठा drm_device *dev, काष्ठा drm_encoder *encoder)
अणु
	पूर्णांक ret;

	drm_simple_encoder_init(dev, encoder, DRM_MODE_ENCODER_TMDS);

	drm_encoder_helper_add(encoder, &exynos_dpi_encoder_helper_funcs);

	ret = exynos_drm_set_possible_crtcs(encoder, EXYNOS_DISPLAY_TYPE_LCD);
	अगर (ret < 0)
		वापस ret;

	ret = exynos_dpi_create_connector(encoder);
	अगर (ret) अणु
		DRM_DEV_ERROR(encoder_to_dpi(encoder)->dev,
			      "failed to create connector ret = %d\n", ret);
		drm_encoder_cleanup(encoder);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा drm_encoder *exynos_dpi_probe(काष्ठा device *dev)
अणु
	काष्ठा exynos_dpi *ctx;
	पूर्णांक ret;

	ctx = devm_kzalloc(dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस ERR_PTR(-ENOMEM);

	ctx->dev = dev;

	ret = exynos_dpi_parse_dt(ctx);
	अगर (ret < 0) अणु
		devm_kमुक्त(dev, ctx);
		वापस शून्य;
	पूर्ण

	अगर (ctx->panel_node) अणु
		ctx->panel = of_drm_find_panel(ctx->panel_node);
		अगर (IS_ERR(ctx->panel))
			वापस ERR_CAST(ctx->panel);
	पूर्ण

	वापस &ctx->encoder;
पूर्ण

पूर्णांक exynos_dpi_हटाओ(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा exynos_dpi *ctx = encoder_to_dpi(encoder);

	exynos_dpi_disable(&ctx->encoder);

	वापस 0;
पूर्ण
