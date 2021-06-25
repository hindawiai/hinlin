<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 * Copyright (C) 2015 Amlogic, Inc. All rights reserved.
 * Copyright (C) 2014 Endless Mobile
 *
 * Written by:
 *     Jasper St. Pierre <jstpierre@mecheye.net>
 */

#समावेश <linux/export.h>
#समावेश <linux/of_graph.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "meson_registers.h"
#समावेश "meson_vclk.h"
#समावेश "meson_venc_cvbs.h"

/* HHI VDAC Registers */
#घोषणा HHI_VDAC_CNTL0		0x2F4 /* 0xbd offset in data sheet */
#घोषणा HHI_VDAC_CNTL0_G12A	0x2EC /* 0xbd offset in data sheet */
#घोषणा HHI_VDAC_CNTL1		0x2F8 /* 0xbe offset in data sheet */
#घोषणा HHI_VDAC_CNTL1_G12A	0x2F0 /* 0xbe offset in data sheet */

काष्ठा meson_venc_cvbs अणु
	काष्ठा drm_encoder	encoder;
	काष्ठा drm_connector	connector;
	काष्ठा meson_drm	*priv;
पूर्ण;
#घोषणा encoder_to_meson_venc_cvbs(x) \
	container_of(x, काष्ठा meson_venc_cvbs, encoder)

#घोषणा connector_to_meson_venc_cvbs(x) \
	container_of(x, काष्ठा meson_venc_cvbs, connector)

/* Supported Modes */

काष्ठा meson_cvbs_mode meson_cvbs_modes[MESON_CVBS_MODES_COUNT] = अणु
	अणु /* PAL */
		.enci = &meson_cvbs_enci_pal,
		.mode = अणु
			DRM_MODE("720x576i", DRM_MODE_TYPE_DRIVER, 13500,
				 720, 732, 795, 864, 0, 576, 580, 586, 625, 0,
				 DRM_MODE_FLAG_INTERLACE),
			.picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3,
		पूर्ण,
	पूर्ण,
	अणु /* NTSC */
		.enci = &meson_cvbs_enci_ntsc,
		.mode = अणु
			DRM_MODE("720x480i", DRM_MODE_TYPE_DRIVER, 13500,
				720, 739, 801, 858, 0, 480, 488, 494, 525, 0,
				DRM_MODE_FLAG_INTERLACE),
			.picture_aspect_ratio = HDMI_PICTURE_ASPECT_4_3,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा meson_cvbs_mode *
meson_cvbs_get_mode(स्थिर काष्ठा drm_display_mode *req_mode)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MESON_CVBS_MODES_COUNT; ++i) अणु
		काष्ठा meson_cvbs_mode *meson_mode = &meson_cvbs_modes[i];

		अगर (drm_mode_match(req_mode, &meson_mode->mode,
				   DRM_MODE_MATCH_TIMINGS |
				   DRM_MODE_MATCH_CLOCK |
				   DRM_MODE_MATCH_FLAGS |
				   DRM_MODE_MATCH_3D_FLAGS))
			वापस meson_mode;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Connector */

अटल व्योम meson_cvbs_connector_destroy(काष्ठा drm_connector *connector)
अणु
	drm_connector_cleanup(connector);
पूर्ण

अटल क्रमागत drm_connector_status
meson_cvbs_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	/* FIXME: Add load-detect or jack-detect अगर possible */
	वापस connector_status_connected;
पूर्ण

अटल पूर्णांक meson_cvbs_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_display_mode *mode;
	पूर्णांक i;

	क्रम (i = 0; i < MESON_CVBS_MODES_COUNT; ++i) अणु
		काष्ठा meson_cvbs_mode *meson_mode = &meson_cvbs_modes[i];

		mode = drm_mode_duplicate(dev, &meson_mode->mode);
		अगर (!mode) अणु
			DRM_ERROR("Failed to create a new display mode\n");
			वापस 0;
		पूर्ण

		drm_mode_probed_add(connector, mode);
	पूर्ण

	वापस i;
पूर्ण

अटल पूर्णांक meson_cvbs_connector_mode_valid(काष्ठा drm_connector *connector,
					   काष्ठा drm_display_mode *mode)
अणु
	/* Validate the modes added in get_modes */
	वापस MODE_OK;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs meson_cvbs_connector_funcs = अणु
	.detect			= meson_cvbs_connector_detect,
	.fill_modes		= drm_helper_probe_single_connector_modes,
	.destroy		= meson_cvbs_connector_destroy,
	.reset			= drm_atomic_helper_connector_reset,
	.atomic_duplicate_state	= drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state	= drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल स्थिर
काष्ठा drm_connector_helper_funcs meson_cvbs_connector_helper_funcs = अणु
	.get_modes	= meson_cvbs_connector_get_modes,
	.mode_valid	= meson_cvbs_connector_mode_valid,
पूर्ण;

/* Encoder */

अटल व्योम meson_venc_cvbs_encoder_destroy(काष्ठा drm_encoder *encoder)
अणु
	drm_encoder_cleanup(encoder);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs meson_venc_cvbs_encoder_funcs = अणु
	.destroy        = meson_venc_cvbs_encoder_destroy,
पूर्ण;

अटल पूर्णांक meson_venc_cvbs_encoder_atomic_check(काष्ठा drm_encoder *encoder,
					काष्ठा drm_crtc_state *crtc_state,
					काष्ठा drm_connector_state *conn_state)
अणु
	अगर (meson_cvbs_get_mode(&crtc_state->mode))
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल व्योम meson_venc_cvbs_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा meson_venc_cvbs *meson_venc_cvbs =
					encoder_to_meson_venc_cvbs(encoder);
	काष्ठा meson_drm *priv = meson_venc_cvbs->priv;

	/* Disable CVBS VDAC */
	अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A)) अणु
		regmap_ग_लिखो(priv->hhi, HHI_VDAC_CNTL0_G12A, 0);
		regmap_ग_लिखो(priv->hhi, HHI_VDAC_CNTL1_G12A, 0);
	पूर्ण अन्यथा अणु
		regmap_ग_लिखो(priv->hhi, HHI_VDAC_CNTL0, 0);
		regmap_ग_लिखो(priv->hhi, HHI_VDAC_CNTL1, 8);
	पूर्ण
पूर्ण

अटल व्योम meson_venc_cvbs_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा meson_venc_cvbs *meson_venc_cvbs =
					encoder_to_meson_venc_cvbs(encoder);
	काष्ठा meson_drm *priv = meson_venc_cvbs->priv;

	/* VDAC0 source is not from ATV */
	ग_लिखोl_bits_relaxed(VENC_VDAC_SEL_ATV_DMD, 0,
			    priv->io_base + _REG(VENC_VDAC_DACSEL0));

	अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXBB)) अणु
		regmap_ग_लिखो(priv->hhi, HHI_VDAC_CNTL0, 1);
		regmap_ग_लिखो(priv->hhi, HHI_VDAC_CNTL1, 0);
	पूर्ण अन्यथा अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXM) ||
		 meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXL)) अणु
		regmap_ग_लिखो(priv->hhi, HHI_VDAC_CNTL0, 0xf0001);
		regmap_ग_लिखो(priv->hhi, HHI_VDAC_CNTL1, 0);
	पूर्ण अन्यथा अगर (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A)) अणु
		regmap_ग_लिखो(priv->hhi, HHI_VDAC_CNTL0_G12A, 0x906001);
		regmap_ग_लिखो(priv->hhi, HHI_VDAC_CNTL1_G12A, 0);
	पूर्ण
पूर्ण

अटल व्योम meson_venc_cvbs_encoder_mode_set(काष्ठा drm_encoder *encoder,
				   काष्ठा drm_display_mode *mode,
				   काष्ठा drm_display_mode *adjusted_mode)
अणु
	स्थिर काष्ठा meson_cvbs_mode *meson_mode = meson_cvbs_get_mode(mode);
	काष्ठा meson_venc_cvbs *meson_venc_cvbs =
					encoder_to_meson_venc_cvbs(encoder);
	काष्ठा meson_drm *priv = meson_venc_cvbs->priv;

	अगर (meson_mode) अणु
		meson_venci_cvbs_mode_set(priv, meson_mode->enci);

		/* Setup 27MHz vclk2 क्रम ENCI and VDAC */
		meson_vclk_setup(priv, MESON_VCLK_TARGET_CVBS,
				 MESON_VCLK_CVBS, MESON_VCLK_CVBS,
				 MESON_VCLK_CVBS, MESON_VCLK_CVBS,
				 true);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs
				meson_venc_cvbs_encoder_helper_funcs = अणु
	.atomic_check	= meson_venc_cvbs_encoder_atomic_check,
	.disable	= meson_venc_cvbs_encoder_disable,
	.enable		= meson_venc_cvbs_encoder_enable,
	.mode_set	= meson_venc_cvbs_encoder_mode_set,
पूर्ण;

अटल bool meson_venc_cvbs_connector_is_available(काष्ठा meson_drm *priv)
अणु
	काष्ठा device_node *remote;

	remote = of_graph_get_remote_node(priv->dev->of_node, 0, 0);
	अगर (!remote)
		वापस false;

	of_node_put(remote);
	वापस true;
पूर्ण

पूर्णांक meson_venc_cvbs_create(काष्ठा meson_drm *priv)
अणु
	काष्ठा drm_device *drm = priv->drm;
	काष्ठा meson_venc_cvbs *meson_venc_cvbs;
	काष्ठा drm_connector *connector;
	काष्ठा drm_encoder *encoder;
	पूर्णांक ret;

	अगर (!meson_venc_cvbs_connector_is_available(priv)) अणु
		dev_info(drm->dev, "CVBS Output connector not available\n");
		वापस 0;
	पूर्ण

	meson_venc_cvbs = devm_kzalloc(priv->dev, माप(*meson_venc_cvbs),
				       GFP_KERNEL);
	अगर (!meson_venc_cvbs)
		वापस -ENOMEM;

	meson_venc_cvbs->priv = priv;
	encoder = &meson_venc_cvbs->encoder;
	connector = &meson_venc_cvbs->connector;

	/* Connector */

	drm_connector_helper_add(connector,
				 &meson_cvbs_connector_helper_funcs);

	ret = drm_connector_init(drm, connector, &meson_cvbs_connector_funcs,
				 DRM_MODE_CONNECTOR_Composite);
	अगर (ret) अणु
		dev_err(priv->dev, "Failed to init CVBS connector\n");
		वापस ret;
	पूर्ण

	connector->पूर्णांकerlace_allowed = 1;

	/* Encoder */

	drm_encoder_helper_add(encoder, &meson_venc_cvbs_encoder_helper_funcs);

	ret = drm_encoder_init(drm, encoder, &meson_venc_cvbs_encoder_funcs,
			       DRM_MODE_ENCODER_TVDAC, "meson_venc_cvbs");
	अगर (ret) अणु
		dev_err(priv->dev, "Failed to init CVBS encoder\n");
		वापस ret;
	पूर्ण

	encoder->possible_crtcs = BIT(0);

	drm_connector_attach_encoder(connector, encoder);

	वापस 0;
पूर्ण
