<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

#समावेश <linux/export.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_of.h>

#समावेश "tidss_crtc.h"
#समावेश "tidss_drv.h"
#समावेश "tidss_encoder.h"

अटल पूर्णांक tidss_encoder_atomic_check(काष्ठा drm_encoder *encoder,
				      काष्ठा drm_crtc_state *crtc_state,
				      काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_device *ddev = encoder->dev;
	काष्ठा tidss_crtc_state *tcrtc_state = to_tidss_crtc_state(crtc_state);
	काष्ठा drm_display_info *di = &conn_state->connector->display_info;
	काष्ठा drm_bridge *bridge;
	bool bus_flags_set = false;

	dev_dbg(ddev->dev, "%s\n", __func__);

	/*
	 * Take the bus_flags from the first bridge that defines
	 * bridge timings, or from the connector's display_info अगर no
	 * bridge defines the timings.
	 */
	drm_क्रम_each_bridge_in_chain(encoder, bridge) अणु
		अगर (!bridge->timings)
			जारी;

		tcrtc_state->bus_flags = bridge->timings->input_bus_flags;
		bus_flags_set = true;
		अवरोध;
	पूर्ण

	अगर (!di->bus_क्रमmats || di->num_bus_क्रमmats == 0)  अणु
		dev_err(ddev->dev, "%s: No bus_formats in connected display\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	// XXX any cleaner way to set bus क्रमmat and flags?
	tcrtc_state->bus_क्रमmat = di->bus_क्रमmats[0];
	अगर (!bus_flags_set)
		tcrtc_state->bus_flags = di->bus_flags;

	वापस 0;
पूर्ण

अटल व्योम tidss_encoder_destroy(काष्ठा drm_encoder *encoder)
अणु
	drm_encoder_cleanup(encoder);
	kमुक्त(encoder);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs encoder_helper_funcs = अणु
	.atomic_check = tidss_encoder_atomic_check,
पूर्ण;

अटल स्थिर काष्ठा drm_encoder_funcs encoder_funcs = अणु
	.destroy = tidss_encoder_destroy,
पूर्ण;

काष्ठा drm_encoder *tidss_encoder_create(काष्ठा tidss_device *tidss,
					 u32 encoder_type, u32 possible_crtcs)
अणु
	काष्ठा drm_encoder *enc;
	पूर्णांक ret;

	enc = kzalloc(माप(*enc), GFP_KERNEL);
	अगर (!enc)
		वापस ERR_PTR(-ENOMEM);

	enc->possible_crtcs = possible_crtcs;

	ret = drm_encoder_init(&tidss->ddev, enc, &encoder_funcs,
			       encoder_type, शून्य);
	अगर (ret < 0) अणु
		kमुक्त(enc);
		वापस ERR_PTR(ret);
	पूर्ण

	drm_encoder_helper_add(enc, &encoder_helper_funcs);

	dev_dbg(tidss->dev, "Encoder create done\n");

	वापस enc;
पूर्ण
