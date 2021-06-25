<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Hisilicon Hibmc SoC drm driver
 *
 * Based on the bochs drm driver.
 *
 * Copyright (c) 2016 Huawei Limited.
 *
 * Author:
 *	Rongrong Zou <zourongrong@huawei.com>
 *	Rongrong Zou <zourongrong@gmail.com>
 *	Jianhua Li <lijianhua@huawei.com>
 */

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "hibmc_drm_drv.h"
#समावेश "hibmc_drm_regs.h"

अटल पूर्णांक hibmc_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	पूर्णांक count;
	व्योम *edid;
	काष्ठा hibmc_connector *hibmc_connector = to_hibmc_connector(connector);

	edid = drm_get_edid(connector, &hibmc_connector->adapter);
	अगर (edid) अणु
		drm_connector_update_edid_property(connector, edid);
		count = drm_add_edid_modes(connector, edid);
		अगर (count)
			जाओ out;
	पूर्ण

	count = drm_add_modes_noedid(connector,
				     connector->dev->mode_config.max_width,
				     connector->dev->mode_config.max_height);
	drm_set_preferred_mode(connector, 1024, 768);

out:
	kमुक्त(edid);
	वापस count;
पूर्ण

अटल व्योम hibmc_connector_destroy(काष्ठा drm_connector *connector)
अणु
	काष्ठा hibmc_connector *hibmc_connector = to_hibmc_connector(connector);

	i2c_del_adapter(&hibmc_connector->adapter);
	drm_connector_cleanup(connector);
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs
	hibmc_connector_helper_funcs = अणु
	.get_modes = hibmc_connector_get_modes,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs hibmc_connector_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = hibmc_connector_destroy,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल व्योम hibmc_encoder_mode_set(काष्ठा drm_encoder *encoder,
				   काष्ठा drm_display_mode *mode,
				   काष्ठा drm_display_mode *adj_mode)
अणु
	u32 reg;
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा hibmc_drm_निजी *priv = to_hibmc_drm_निजी(dev);

	reg = पढ़ोl(priv->mmio + HIBMC_DISPLAY_CONTROL_HISILE);
	reg |= HIBMC_DISPLAY_CONTROL_FPVDDEN(1);
	reg |= HIBMC_DISPLAY_CONTROL_PANELDATE(1);
	reg |= HIBMC_DISPLAY_CONTROL_FPEN(1);
	reg |= HIBMC_DISPLAY_CONTROL_VBIASEN(1);
	ग_लिखोl(reg, priv->mmio + HIBMC_DISPLAY_CONTROL_HISILE);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs hibmc_encoder_helper_funcs = अणु
	.mode_set = hibmc_encoder_mode_set,
पूर्ण;

पूर्णांक hibmc_vdac_init(काष्ठा hibmc_drm_निजी *priv)
अणु
	काष्ठा drm_device *dev = &priv->dev;
	काष्ठा hibmc_connector *hibmc_connector = &priv->connector;
	काष्ठा drm_encoder *encoder = &priv->encoder;
	काष्ठा drm_crtc *crtc = &priv->crtc;
	काष्ठा drm_connector *connector = &hibmc_connector->base;
	पूर्णांक ret;

	ret = hibmc_ddc_create(dev, hibmc_connector);
	अगर (ret) अणु
		drm_err(dev, "failed to create ddc: %d\n", ret);
		वापस ret;
	पूर्ण

	encoder->possible_crtcs = drm_crtc_mask(crtc);
	ret = drm_simple_encoder_init(dev, encoder, DRM_MODE_ENCODER_DAC);
	अगर (ret) अणु
		drm_err(dev, "failed to init encoder: %d\n", ret);
		वापस ret;
	पूर्ण

	drm_encoder_helper_add(encoder, &hibmc_encoder_helper_funcs);

	ret = drm_connector_init_with_ddc(dev, connector,
					  &hibmc_connector_funcs,
					  DRM_MODE_CONNECTOR_VGA,
					  &hibmc_connector->adapter);
	अगर (ret) अणु
		drm_err(dev, "failed to init connector: %d\n", ret);
		वापस ret;
	पूर्ण

	drm_connector_helper_add(connector, &hibmc_connector_helper_funcs);

	drm_connector_attach_encoder(connector, encoder);

	वापस 0;
पूर्ण
