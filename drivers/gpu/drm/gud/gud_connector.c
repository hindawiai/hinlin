<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright 2020 Noralf Trथचnnes
 */

#समावेश <linux/backlight.h>
#समावेश <linux/workqueue.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_state_helper.h>
#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_modeset_helper_vtables.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>
#समावेश <drm/gud.h>

#समावेश "gud_internal.h"

काष्ठा gud_connector अणु
	काष्ठा drm_connector connector;
	काष्ठा drm_encoder encoder;
	काष्ठा backlight_device *backlight;
	काष्ठा work_काष्ठा backlight_work;

	/* Supported properties */
	u16 *properties;
	अचिन्हित पूर्णांक num_properties;

	/* Initial gadget tv state अगर applicable, applied on state reset */
	काष्ठा drm_tv_connector_state initial_tv_state;

	/*
	 * Initial gadget backlight brightness अगर applicable, applied on state reset.
	 * The value -ENODEV is used to संकेत no backlight.
	 */
	पूर्णांक initial_brightness;
पूर्ण;

अटल अंतरभूत काष्ठा gud_connector *to_gud_connector(काष्ठा drm_connector *connector)
अणु
	वापस container_of(connector, काष्ठा gud_connector, connector);
पूर्ण

अटल व्योम gud_conn_err(काष्ठा drm_connector *connector, स्थिर अक्षर *msg, पूर्णांक ret)
अणु
	dev_err(connector->dev->dev, "%s: %s (ret=%d)\n", connector->name, msg, ret);
पूर्ण

/*
 * Use a worker to aव्योम taking kms locks inside the backlight lock.
 * Other display drivers use backlight within their kms locks.
 * This aव्योमs inconsistent locking rules, which would upset lockdep.
 */
अटल व्योम gud_connector_backlight_update_status_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gud_connector *gconn = container_of(work, काष्ठा gud_connector, backlight_work);
	काष्ठा drm_connector *connector = &gconn->connector;
	काष्ठा drm_connector_state *connector_state;
	काष्ठा drm_device *drm = connector->dev;
	काष्ठा drm_modeset_acquire_ctx ctx;
	काष्ठा drm_atomic_state *state;
	पूर्णांक idx, ret;

	अगर (!drm_dev_enter(drm, &idx))
		वापस;

	state = drm_atomic_state_alloc(drm);
	अगर (!state) अणु
		ret = -ENOMEM;
		जाओ निकास;
	पूर्ण

	drm_modeset_acquire_init(&ctx, 0);
	state->acquire_ctx = &ctx;
retry:
	connector_state = drm_atomic_get_connector_state(state, connector);
	अगर (IS_ERR(connector_state)) अणु
		ret = PTR_ERR(connector_state);
		जाओ out;
	पूर्ण

	/* Reuse tv.brightness to aव्योम having to subclass */
	connector_state->tv.brightness = gconn->backlight->props.brightness;

	ret = drm_atomic_commit(state);
out:
	अगर (ret == -EDEADLK) अणु
		drm_atomic_state_clear(state);
		drm_modeset_backoff(&ctx);
		जाओ retry;
	पूर्ण

	drm_atomic_state_put(state);

	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);
निकास:
	drm_dev_निकास(idx);

	अगर (ret)
		dev_err(drm->dev, "Failed to update backlight, err=%d\n", ret);
पूर्ण

अटल पूर्णांक gud_connector_backlight_update_status(काष्ठा backlight_device *bd)
अणु
	काष्ठा drm_connector *connector = bl_get_data(bd);
	काष्ठा gud_connector *gconn = to_gud_connector(connector);

	/* The USB समयout is 5 seconds so use प्रणाली_दीर्घ_wq क्रम worst हाल scenario */
	queue_work(प्रणाली_दीर्घ_wq, &gconn->backlight_work);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops gud_connector_backlight_ops = अणु
	.update_status	= gud_connector_backlight_update_status,
पूर्ण;

अटल पूर्णांक gud_connector_backlight_रेजिस्टर(काष्ठा gud_connector *gconn)
अणु
	काष्ठा drm_connector *connector = &gconn->connector;
	काष्ठा backlight_device *bd;
	स्थिर अक्षर *name;
	स्थिर काष्ठा backlight_properties props = अणु
		.type = BACKLIGHT_RAW,
		.scale = BACKLIGHT_SCALE_NON_LINEAR,
		.max_brightness = 100,
		.brightness = gconn->initial_brightness,
	पूर्ण;

	name = kaप्र_लिखो(GFP_KERNEL, "card%d-%s-backlight",
			 connector->dev->primary->index, connector->name);
	अगर (!name)
		वापस -ENOMEM;

	bd = backlight_device_रेजिस्टर(name, connector->kdev, connector,
				       &gud_connector_backlight_ops, &props);
	kमुक्त(name);
	अगर (IS_ERR(bd))
		वापस PTR_ERR(bd);

	gconn->backlight = bd;

	वापस 0;
पूर्ण

अटल पूर्णांक gud_connector_detect(काष्ठा drm_connector *connector,
				काष्ठा drm_modeset_acquire_ctx *ctx, bool क्रमce)
अणु
	काष्ठा gud_device *gdrm = to_gud_device(connector->dev);
	पूर्णांक idx, ret;
	u8 status;

	अगर (!drm_dev_enter(connector->dev, &idx))
		वापस connector_status_disconnected;

	अगर (क्रमce) अणु
		ret = gud_usb_set(gdrm, GUD_REQ_SET_CONNECTOR_FORCE_DETECT,
				  connector->index, शून्य, 0);
		अगर (ret) अणु
			ret = connector_status_unknown;
			जाओ निकास;
		पूर्ण
	पूर्ण

	ret = gud_usb_get_u8(gdrm, GUD_REQ_GET_CONNECTOR_STATUS, connector->index, &status);
	अगर (ret) अणु
		ret = connector_status_unknown;
		जाओ निकास;
	पूर्ण

	चयन (status & GUD_CONNECTOR_STATUS_CONNECTED_MASK) अणु
	हाल GUD_CONNECTOR_STATUS_DISCONNECTED:
		ret = connector_status_disconnected;
		अवरोध;
	हाल GUD_CONNECTOR_STATUS_CONNECTED:
		ret = connector_status_connected;
		अवरोध;
	शेष:
		ret = connector_status_unknown;
		अवरोध;
	पूर्ण

	अगर (status & GUD_CONNECTOR_STATUS_CHANGED)
		connector->epoch_counter += 1;
निकास:
	drm_dev_निकास(idx);

	वापस ret;
पूर्ण

काष्ठा gud_connector_get_edid_ctx अणु
	व्योम *buf;
	माप_प्रकार len;
	bool edid_override;
पूर्ण;

अटल पूर्णांक gud_connector_get_edid_block(व्योम *data, u8 *buf, अचिन्हित पूर्णांक block, माप_प्रकार len)
अणु
	काष्ठा gud_connector_get_edid_ctx *ctx = data;
	माप_प्रकार start = block * EDID_LENGTH;

	ctx->edid_override = false;

	अगर (start + len > ctx->len)
		वापस -1;

	स_नकल(buf, ctx->buf + start, len);

	वापस 0;
पूर्ण

अटल पूर्णांक gud_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा gud_device *gdrm = to_gud_device(connector->dev);
	काष्ठा gud_display_mode_req *reqmodes = शून्य;
	काष्ठा gud_connector_get_edid_ctx edid_ctx;
	अचिन्हित पूर्णांक i, num_modes = 0;
	काष्ठा edid *edid = शून्य;
	पूर्णांक idx, ret;

	अगर (!drm_dev_enter(connector->dev, &idx))
		वापस 0;

	edid_ctx.edid_override = true;
	edid_ctx.buf = kदो_स्मृति(GUD_CONNECTOR_MAX_EDID_LEN, GFP_KERNEL);
	अगर (!edid_ctx.buf)
		जाओ out;

	ret = gud_usb_get(gdrm, GUD_REQ_GET_CONNECTOR_EDID, connector->index,
			  edid_ctx.buf, GUD_CONNECTOR_MAX_EDID_LEN);
	अगर (ret > 0 && ret % EDID_LENGTH) अणु
		gud_conn_err(connector, "Invalid EDID size", ret);
	पूर्ण अन्यथा अगर (ret > 0) अणु
		edid_ctx.len = ret;
		edid = drm_करो_get_edid(connector, gud_connector_get_edid_block, &edid_ctx);
	पूर्ण

	kमुक्त(edid_ctx.buf);
	drm_connector_update_edid_property(connector, edid);

	अगर (edid && edid_ctx.edid_override)
		जाओ out;

	reqmodes = kदो_स्मृति_array(GUD_CONNECTOR_MAX_NUM_MODES, माप(*reqmodes), GFP_KERNEL);
	अगर (!reqmodes)
		जाओ out;

	ret = gud_usb_get(gdrm, GUD_REQ_GET_CONNECTOR_MODES, connector->index,
			  reqmodes, GUD_CONNECTOR_MAX_NUM_MODES * माप(*reqmodes));
	अगर (ret <= 0)
		जाओ out;
	अगर (ret % माप(*reqmodes)) अणु
		gud_conn_err(connector, "Invalid display mode array size", ret);
		जाओ out;
	पूर्ण

	num_modes = ret / माप(*reqmodes);

	क्रम (i = 0; i < num_modes; i++) अणु
		काष्ठा drm_display_mode *mode;

		mode = drm_mode_create(connector->dev);
		अगर (!mode) अणु
			num_modes = i;
			जाओ out;
		पूर्ण

		gud_to_display_mode(mode, &reqmodes[i]);
		drm_mode_probed_add(connector, mode);
	पूर्ण
out:
	अगर (!num_modes)
		num_modes = drm_add_edid_modes(connector, edid);

	kमुक्त(reqmodes);
	kमुक्त(edid);
	drm_dev_निकास(idx);

	वापस num_modes;
पूर्ण

अटल पूर्णांक gud_connector_atomic_check(काष्ठा drm_connector *connector,
				      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_connector_state *new_state;
	काष्ठा drm_crtc_state *new_crtc_state;
	काष्ठा drm_connector_state *old_state;

	new_state = drm_atomic_get_new_connector_state(state, connector);
	अगर (!new_state->crtc)
		वापस 0;

	old_state = drm_atomic_get_old_connector_state(state, connector);
	new_crtc_state = drm_atomic_get_new_crtc_state(state, new_state->crtc);

	अगर (old_state->tv.margins.left != new_state->tv.margins.left ||
	    old_state->tv.margins.right != new_state->tv.margins.right ||
	    old_state->tv.margins.top != new_state->tv.margins.top ||
	    old_state->tv.margins.bottom != new_state->tv.margins.bottom ||
	    old_state->tv.mode != new_state->tv.mode ||
	    old_state->tv.brightness != new_state->tv.brightness ||
	    old_state->tv.contrast != new_state->tv.contrast ||
	    old_state->tv.flicker_reduction != new_state->tv.flicker_reduction ||
	    old_state->tv.overscan != new_state->tv.overscan ||
	    old_state->tv.saturation != new_state->tv.saturation ||
	    old_state->tv.hue != new_state->tv.hue)
		new_crtc_state->connectors_changed = true;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs gud_connector_helper_funcs = अणु
	.detect_ctx = gud_connector_detect,
	.get_modes = gud_connector_get_modes,
	.atomic_check = gud_connector_atomic_check,
पूर्ण;

अटल पूर्णांक gud_connector_late_रेजिस्टर(काष्ठा drm_connector *connector)
अणु
	काष्ठा gud_connector *gconn = to_gud_connector(connector);

	अगर (gconn->initial_brightness < 0)
		वापस 0;

	वापस gud_connector_backlight_रेजिस्टर(gconn);
पूर्ण

अटल व्योम gud_connector_early_unरेजिस्टर(काष्ठा drm_connector *connector)
अणु
	काष्ठा gud_connector *gconn = to_gud_connector(connector);

	backlight_device_unरेजिस्टर(gconn->backlight);
	cancel_work_sync(&gconn->backlight_work);
पूर्ण

अटल व्योम gud_connector_destroy(काष्ठा drm_connector *connector)
अणु
	काष्ठा gud_connector *gconn = to_gud_connector(connector);

	drm_connector_cleanup(connector);
	kमुक्त(gconn->properties);
	kमुक्त(gconn);
पूर्ण

अटल व्योम gud_connector_reset(काष्ठा drm_connector *connector)
अणु
	काष्ठा gud_connector *gconn = to_gud_connector(connector);

	drm_atomic_helper_connector_reset(connector);
	connector->state->tv = gconn->initial_tv_state;
	/* Set margins from command line */
	drm_atomic_helper_connector_tv_reset(connector);
	अगर (gconn->initial_brightness >= 0)
		connector->state->tv.brightness = gconn->initial_brightness;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs gud_connector_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.late_रेजिस्टर = gud_connector_late_रेजिस्टर,
	.early_unरेजिस्टर = gud_connector_early_unरेजिस्टर,
	.destroy = gud_connector_destroy,
	.reset = gud_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

/*
 * The tv.mode property is shared among the connectors and its क्रमागत names are
 * driver specअगरic. This means that अगर more than one connector uses tv.mode,
 * the क्रमागत names has to be the same.
 */
अटल पूर्णांक gud_connector_add_tv_mode(काष्ठा gud_device *gdrm, काष्ठा drm_connector *connector)
अणु
	माप_प्रकार buf_len = GUD_CONNECTOR_TV_MODE_MAX_NUM * GUD_CONNECTOR_TV_MODE_NAME_LEN;
	स्थिर अक्षर *modes[GUD_CONNECTOR_TV_MODE_MAX_NUM];
	अचिन्हित पूर्णांक i, num_modes;
	अक्षर *buf;
	पूर्णांक ret;

	buf = kदो_स्मृति(buf_len, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = gud_usb_get(gdrm, GUD_REQ_GET_CONNECTOR_TV_MODE_VALUES,
			  connector->index, buf, buf_len);
	अगर (ret < 0)
		जाओ मुक्त;
	अगर (!ret || ret % GUD_CONNECTOR_TV_MODE_NAME_LEN) अणु
		ret = -EIO;
		जाओ मुक्त;
	पूर्ण

	num_modes = ret / GUD_CONNECTOR_TV_MODE_NAME_LEN;
	क्रम (i = 0; i < num_modes; i++)
		modes[i] = &buf[i * GUD_CONNECTOR_TV_MODE_NAME_LEN];

	ret = drm_mode_create_tv_properties(connector->dev, num_modes, modes);
मुक्त:
	kमुक्त(buf);
	अगर (ret < 0)
		gud_conn_err(connector, "Failed to add TV modes", ret);

	वापस ret;
पूर्ण

अटल काष्ठा drm_property *
gud_connector_property_lookup(काष्ठा drm_connector *connector, u16 prop)
अणु
	काष्ठा drm_mode_config *config = &connector->dev->mode_config;

	चयन (prop) अणु
	हाल GUD_PROPERTY_TV_LEFT_MARGIN:
		वापस config->tv_left_margin_property;
	हाल GUD_PROPERTY_TV_RIGHT_MARGIN:
		वापस config->tv_right_margin_property;
	हाल GUD_PROPERTY_TV_TOP_MARGIN:
		वापस config->tv_top_margin_property;
	हाल GUD_PROPERTY_TV_BOTTOM_MARGIN:
		वापस config->tv_bottom_margin_property;
	हाल GUD_PROPERTY_TV_MODE:
		वापस config->tv_mode_property;
	हाल GUD_PROPERTY_TV_BRIGHTNESS:
		वापस config->tv_brightness_property;
	हाल GUD_PROPERTY_TV_CONTRAST:
		वापस config->tv_contrast_property;
	हाल GUD_PROPERTY_TV_FLICKER_REDUCTION:
		वापस config->tv_flicker_reduction_property;
	हाल GUD_PROPERTY_TV_OVERSCAN:
		वापस config->tv_overscan_property;
	हाल GUD_PROPERTY_TV_SATURATION:
		वापस config->tv_saturation_property;
	हाल GUD_PROPERTY_TV_HUE:
		वापस config->tv_hue_property;
	शेष:
		वापस ERR_PTR(-EINVAL);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक *gud_connector_tv_state_val(u16 prop, काष्ठा drm_tv_connector_state *state)
अणु
	चयन (prop) अणु
	हाल GUD_PROPERTY_TV_LEFT_MARGIN:
		वापस &state->margins.left;
	हाल GUD_PROPERTY_TV_RIGHT_MARGIN:
		वापस &state->margins.right;
	हाल GUD_PROPERTY_TV_TOP_MARGIN:
		वापस &state->margins.top;
	हाल GUD_PROPERTY_TV_BOTTOM_MARGIN:
		वापस &state->margins.bottom;
	हाल GUD_PROPERTY_TV_MODE:
		वापस &state->mode;
	हाल GUD_PROPERTY_TV_BRIGHTNESS:
		वापस &state->brightness;
	हाल GUD_PROPERTY_TV_CONTRAST:
		वापस &state->contrast;
	हाल GUD_PROPERTY_TV_FLICKER_REDUCTION:
		वापस &state->flicker_reduction;
	हाल GUD_PROPERTY_TV_OVERSCAN:
		वापस &state->overscan;
	हाल GUD_PROPERTY_TV_SATURATION:
		वापस &state->saturation;
	हाल GUD_PROPERTY_TV_HUE:
		वापस &state->hue;
	शेष:
		वापस ERR_PTR(-EINVAL);
	पूर्ण
पूर्ण

अटल पूर्णांक gud_connector_add_properties(काष्ठा gud_device *gdrm, काष्ठा gud_connector *gconn)
अणु
	काष्ठा drm_connector *connector = &gconn->connector;
	काष्ठा drm_device *drm = &gdrm->drm;
	काष्ठा gud_property_req *properties;
	अचिन्हित पूर्णांक i, num_properties;
	पूर्णांक ret;

	properties = kसुस्मृति(GUD_CONNECTOR_PROPERTIES_MAX_NUM, माप(*properties), GFP_KERNEL);
	अगर (!properties)
		वापस -ENOMEM;

	ret = gud_usb_get(gdrm, GUD_REQ_GET_CONNECTOR_PROPERTIES, connector->index,
			  properties, GUD_CONNECTOR_PROPERTIES_MAX_NUM * माप(*properties));
	अगर (ret <= 0)
		जाओ out;
	अगर (ret % माप(*properties)) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	num_properties = ret / माप(*properties);
	ret = 0;

	gconn->properties = kसुस्मृति(num_properties, माप(*gconn->properties), GFP_KERNEL);
	अगर (!gconn->properties) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < num_properties; i++) अणु
		u16 prop = le16_to_cpu(properties[i].prop);
		u64 val = le64_to_cpu(properties[i].val);
		काष्ठा drm_property *property;
		अचिन्हित पूर्णांक *state_val;

		drm_dbg(drm, "property: %u = %llu(0x%llx)\n", prop, val, val);

		चयन (prop) अणु
		हाल GUD_PROPERTY_TV_LEFT_MARGIN:
			fallthrough;
		हाल GUD_PROPERTY_TV_RIGHT_MARGIN:
			fallthrough;
		हाल GUD_PROPERTY_TV_TOP_MARGIN:
			fallthrough;
		हाल GUD_PROPERTY_TV_BOTTOM_MARGIN:
			ret = drm_mode_create_tv_margin_properties(drm);
			अगर (ret)
				जाओ out;
			अवरोध;
		हाल GUD_PROPERTY_TV_MODE:
			ret = gud_connector_add_tv_mode(gdrm, connector);
			अगर (ret)
				जाओ out;
			अवरोध;
		हाल GUD_PROPERTY_TV_BRIGHTNESS:
			fallthrough;
		हाल GUD_PROPERTY_TV_CONTRAST:
			fallthrough;
		हाल GUD_PROPERTY_TV_FLICKER_REDUCTION:
			fallthrough;
		हाल GUD_PROPERTY_TV_OVERSCAN:
			fallthrough;
		हाल GUD_PROPERTY_TV_SATURATION:
			fallthrough;
		हाल GUD_PROPERTY_TV_HUE:
			/* This is a no-op अगर alपढ़ोy added. */
			ret = drm_mode_create_tv_properties(drm, 0, शून्य);
			अगर (ret)
				जाओ out;
			अवरोध;
		हाल GUD_PROPERTY_BACKLIGHT_BRIGHTNESS:
			अगर (val > 100) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			gconn->initial_brightness = val;
			अवरोध;
		शेष:
			/* New ones might show up in future devices, skip those we करोn't know. */
			drm_dbg(drm, "Ignoring unknown property: %u\n", prop);
			जारी;
		पूर्ण

		gconn->properties[gconn->num_properties++] = prop;

		अगर (prop == GUD_PROPERTY_BACKLIGHT_BRIGHTNESS)
			जारी; /* not a DRM property */

		property = gud_connector_property_lookup(connector, prop);
		अगर (WARN_ON(IS_ERR(property)))
			जारी;

		state_val = gud_connector_tv_state_val(prop, &gconn->initial_tv_state);
		अगर (WARN_ON(IS_ERR(state_val)))
			जारी;

		*state_val = val;
		drm_object_attach_property(&connector->base, property, 0);
	पूर्ण
out:
	kमुक्त(properties);

	वापस ret;
पूर्ण

पूर्णांक gud_connector_fill_properties(काष्ठा drm_connector_state *connector_state,
				  काष्ठा gud_property_req *properties)
अणु
	काष्ठा gud_connector *gconn = to_gud_connector(connector_state->connector);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < gconn->num_properties; i++) अणु
		u16 prop = gconn->properties[i];
		u64 val;

		अगर (prop == GUD_PROPERTY_BACKLIGHT_BRIGHTNESS) अणु
			val = connector_state->tv.brightness;
		पूर्ण अन्यथा अणु
			अचिन्हित पूर्णांक *state_val;

			state_val = gud_connector_tv_state_val(prop, &connector_state->tv);
			अगर (WARN_ON_ONCE(IS_ERR(state_val)))
				वापस PTR_ERR(state_val);

			val = *state_val;
		पूर्ण

		properties[i].prop = cpu_to_le16(prop);
		properties[i].val = cpu_to_le64(val);
	पूर्ण

	वापस gconn->num_properties;
पूर्ण

अटल पूर्णांक gud_connector_create(काष्ठा gud_device *gdrm, अचिन्हित पूर्णांक index,
				काष्ठा gud_connector_descriptor_req *desc)
अणु
	काष्ठा drm_device *drm = &gdrm->drm;
	काष्ठा gud_connector *gconn;
	काष्ठा drm_connector *connector;
	काष्ठा drm_encoder *encoder;
	पूर्णांक ret, connector_type;
	u32 flags;

	gconn = kzalloc(माप(*gconn), GFP_KERNEL);
	अगर (!gconn)
		वापस -ENOMEM;

	INIT_WORK(&gconn->backlight_work, gud_connector_backlight_update_status_work);
	gconn->initial_brightness = -ENODEV;
	flags = le32_to_cpu(desc->flags);
	connector = &gconn->connector;

	drm_dbg(drm, "Connector: index=%u type=%u flags=0x%x\n", index, desc->connector_type, flags);

	चयन (desc->connector_type) अणु
	हाल GUD_CONNECTOR_TYPE_PANEL:
		connector_type = DRM_MODE_CONNECTOR_USB;
		अवरोध;
	हाल GUD_CONNECTOR_TYPE_VGA:
		connector_type = DRM_MODE_CONNECTOR_VGA;
		अवरोध;
	हाल GUD_CONNECTOR_TYPE_DVI:
		connector_type = DRM_MODE_CONNECTOR_DVID;
		अवरोध;
	हाल GUD_CONNECTOR_TYPE_COMPOSITE:
		connector_type = DRM_MODE_CONNECTOR_Composite;
		अवरोध;
	हाल GUD_CONNECTOR_TYPE_SVIDEO:
		connector_type = DRM_MODE_CONNECTOR_SVIDEO;
		अवरोध;
	हाल GUD_CONNECTOR_TYPE_COMPONENT:
		connector_type = DRM_MODE_CONNECTOR_Component;
		अवरोध;
	हाल GUD_CONNECTOR_TYPE_DISPLAYPORT:
		connector_type = DRM_MODE_CONNECTOR_DisplayPort;
		अवरोध;
	हाल GUD_CONNECTOR_TYPE_HDMI:
		connector_type = DRM_MODE_CONNECTOR_HDMIA;
		अवरोध;
	शेष: /* future types */
		connector_type = DRM_MODE_CONNECTOR_USB;
		अवरोध;
	पूर्ण

	drm_connector_helper_add(connector, &gud_connector_helper_funcs);
	ret = drm_connector_init(drm, connector, &gud_connector_funcs, connector_type);
	अगर (ret) अणु
		kमुक्त(connector);
		वापस ret;
	पूर्ण

	अगर (WARN_ON(connector->index != index))
		वापस -EINVAL;

	अगर (flags & GUD_CONNECTOR_FLAGS_POLL_STATUS)
		connector->polled = (DRM_CONNECTOR_POLL_CONNECT | DRM_CONNECTOR_POLL_DISCONNECT);
	अगर (flags & GUD_CONNECTOR_FLAGS_INTERLACE)
		connector->पूर्णांकerlace_allowed = true;
	अगर (flags & GUD_CONNECTOR_FLAGS_DOUBLESCAN)
		connector->द्विगुनscan_allowed = true;

	ret = gud_connector_add_properties(gdrm, gconn);
	अगर (ret) अणु
		gud_conn_err(connector, "Failed to add properties", ret);
		वापस ret;
	पूर्ण

	/* The first connector is attached to the existing simple pipe encoder */
	अगर (!connector->index) अणु
		encoder = &gdrm->pipe.encoder;
	पूर्ण अन्यथा अणु
		encoder = &gconn->encoder;

		ret = drm_simple_encoder_init(drm, encoder, DRM_MODE_ENCODER_NONE);
		अगर (ret)
			वापस ret;

		encoder->possible_crtcs = 1;
	पूर्ण

	वापस drm_connector_attach_encoder(connector, encoder);
पूर्ण

पूर्णांक gud_get_connectors(काष्ठा gud_device *gdrm)
अणु
	काष्ठा gud_connector_descriptor_req *descs;
	अचिन्हित पूर्णांक i, num_connectors;
	पूर्णांक ret;

	descs = kदो_स्मृति_array(GUD_CONNECTORS_MAX_NUM, माप(*descs), GFP_KERNEL);
	अगर (!descs)
		वापस -ENOMEM;

	ret = gud_usb_get(gdrm, GUD_REQ_GET_CONNECTORS, 0,
			  descs, GUD_CONNECTORS_MAX_NUM * माप(*descs));
	अगर (ret < 0)
		जाओ मुक्त;
	अगर (!ret || ret % माप(*descs)) अणु
		ret = -EIO;
		जाओ मुक्त;
	पूर्ण

	num_connectors = ret / माप(*descs);

	क्रम (i = 0; i < num_connectors; i++) अणु
		ret = gud_connector_create(gdrm, i, &descs[i]);
		अगर (ret)
			जाओ मुक्त;
	पूर्ण
मुक्त:
	kमुक्त(descs);

	वापस ret;
पूर्ण
