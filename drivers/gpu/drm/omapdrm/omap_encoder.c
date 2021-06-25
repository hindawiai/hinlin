<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Rob Clark <rob@ti.com>
 */

#समावेश <linux/list.h>

#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_modeset_helper_vtables.h>
#समावेश <drm/drm_edid.h>

#समावेश "omap_drv.h"

/*
 * encoder funcs
 */

#घोषणा to_omap_encoder(x) container_of(x, काष्ठा omap_encoder, base)

/* The encoder and connector both map to same dssdev.. the encoder
 * handles the 'active' parts, ie. anything the modअगरies the state
 * of the hw, and the connector handles the 'read-only' parts, like
 * detecting connection and पढ़ोing edid.
 */
काष्ठा omap_encoder अणु
	काष्ठा drm_encoder base;
	काष्ठा omap_dss_device *output;
पूर्ण;

अटल व्योम omap_encoder_destroy(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा omap_encoder *omap_encoder = to_omap_encoder(encoder);

	drm_encoder_cleanup(encoder);
	kमुक्त(omap_encoder);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs omap_encoder_funcs = अणु
	.destroy = omap_encoder_destroy,
पूर्ण;

अटल व्योम omap_encoder_update_videomode_flags(काष्ठा videomode *vm,
						u32 bus_flags)
अणु
	अगर (!(vm->flags & (DISPLAY_FLAGS_DE_LOW |
			   DISPLAY_FLAGS_DE_HIGH))) अणु
		अगर (bus_flags & DRM_BUS_FLAG_DE_LOW)
			vm->flags |= DISPLAY_FLAGS_DE_LOW;
		अन्यथा अगर (bus_flags & DRM_BUS_FLAG_DE_HIGH)
			vm->flags |= DISPLAY_FLAGS_DE_HIGH;
	पूर्ण

	अगर (!(vm->flags & (DISPLAY_FLAGS_PIXDATA_POSEDGE |
			   DISPLAY_FLAGS_PIXDATA_NEGEDGE))) अणु
		अगर (bus_flags & DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE)
			vm->flags |= DISPLAY_FLAGS_PIXDATA_POSEDGE;
		अन्यथा अगर (bus_flags & DRM_BUS_FLAG_PIXDATA_DRIVE_NEGEDGE)
			vm->flags |= DISPLAY_FLAGS_PIXDATA_NEGEDGE;
	पूर्ण

	अगर (!(vm->flags & (DISPLAY_FLAGS_SYNC_POSEDGE |
			   DISPLAY_FLAGS_SYNC_NEGEDGE))) अणु
		अगर (bus_flags & DRM_BUS_FLAG_SYNC_DRIVE_POSEDGE)
			vm->flags |= DISPLAY_FLAGS_SYNC_POSEDGE;
		अन्यथा अगर (bus_flags & DRM_BUS_FLAG_SYNC_DRIVE_NEGEDGE)
			vm->flags |= DISPLAY_FLAGS_SYNC_NEGEDGE;
	पूर्ण
पूर्ण

अटल व्योम omap_encoder_mode_set(काष्ठा drm_encoder *encoder,
				  काष्ठा drm_display_mode *mode,
				  काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा omap_encoder *omap_encoder = to_omap_encoder(encoder);
	काष्ठा omap_dss_device *output = omap_encoder->output;
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_connector *connector;
	काष्ठा drm_bridge *bridge;
	काष्ठा videomode vm = अणु 0 पूर्ण;
	u32 bus_flags;

	list_क्रम_each_entry(connector, &dev->mode_config.connector_list, head) अणु
		अगर (connector->encoder == encoder)
			अवरोध;
	पूर्ण

	drm_display_mode_to_videomode(adjusted_mode, &vm);

	/*
	 * HACK: This fixes the vm flags.
	 * काष्ठा drm_display_mode करोes not contain the VSYNC/HSYNC/DE flags and
	 * they get lost when converting back and क्रमth between काष्ठा
	 * drm_display_mode and काष्ठा videomode. The hack below goes and
	 * fetches the missing flags.
	 *
	 * A better solution is to use DRM's bus-flags through the whole driver.
	 */
	क्रम (bridge = output->bridge; bridge;
	     bridge = drm_bridge_get_next_bridge(bridge)) अणु
		अगर (!bridge->timings)
			जारी;

		bus_flags = bridge->timings->input_bus_flags;
		omap_encoder_update_videomode_flags(&vm, bus_flags);
	पूर्ण

	bus_flags = connector->display_info.bus_flags;
	omap_encoder_update_videomode_flags(&vm, bus_flags);

	/* Set timings क्रम all devices in the display pipeline. */
	dss_mgr_set_timings(output, &vm);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs omap_encoder_helper_funcs = अणु
	.mode_set = omap_encoder_mode_set,
पूर्ण;

/* initialize encoder */
काष्ठा drm_encoder *omap_encoder_init(काष्ठा drm_device *dev,
				      काष्ठा omap_dss_device *output)
अणु
	काष्ठा drm_encoder *encoder = शून्य;
	काष्ठा omap_encoder *omap_encoder;

	omap_encoder = kzalloc(माप(*omap_encoder), GFP_KERNEL);
	अगर (!omap_encoder)
		जाओ fail;

	omap_encoder->output = output;

	encoder = &omap_encoder->base;

	drm_encoder_init(dev, encoder, &omap_encoder_funcs,
			 DRM_MODE_ENCODER_TMDS, शून्य);
	drm_encoder_helper_add(encoder, &omap_encoder_helper_funcs);

	वापस encoder;

fail:
	अगर (encoder)
		omap_encoder_destroy(encoder);

	वापस शून्य;
पूर्ण
