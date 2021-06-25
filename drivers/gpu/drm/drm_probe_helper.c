<शैली गुरु>
/*
 * Copyright (c) 2006-2008 Intel Corporation
 * Copyright (c) 2007 Dave Airlie <airlied@linux.ie>
 *
 * DRM core CRTC related functions
 *
 * Permission to use, copy, modअगरy, distribute, and sell this software and its
 * करोcumentation क्रम any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting करोcumentation, and
 * that the name of the copyright holders not be used in advertising or
 * खुलाity pertaining to distribution of the software without specअगरic,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software क्रम any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INसूचीECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 *
 * Authors:
 *      Keith Packard
 *	Eric Anholt <eric@anholt.net>
 *      Dave Airlie <airlied@linux.ie>
 *      Jesse Barnes <jesse.barnes@पूर्णांकel.com>
 */

#समावेश <linux/export.h>
#समावेश <linux/moduleparam.h>

#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_client.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_modeset_helper_vtables.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_sysfs.h>

#समावेश "drm_crtc_helper_internal.h"

/**
 * DOC: output probing helper overview
 *
 * This library provides some helper code क्रम output probing. It provides an
 * implementation of the core &drm_connector_funcs.fill_modes पूर्णांकerface with
 * drm_helper_probe_single_connector_modes().
 *
 * It also provides support क्रम polling connectors with a work item and क्रम
 * generic hotplug पूर्णांकerrupt handling where the driver करोesn't or cannot keep
 * track of a per-connector hpd पूर्णांकerrupt.
 *
 * This helper library can be used independently of the modeset helper library.
 * Drivers can also overग_लिखो dअगरferent parts e.g. use their own hotplug
 * handling code to aव्योम probing unrelated outमाला_दो.
 *
 * The probe helpers share the function table काष्ठाures with other display
 * helper libraries. See &काष्ठा drm_connector_helper_funcs क्रम the details.
 */

अटल bool drm_kms_helper_poll = true;
module_param_named(poll, drm_kms_helper_poll, bool, 0600);

अटल क्रमागत drm_mode_status
drm_mode_validate_flag(स्थिर काष्ठा drm_display_mode *mode,
		       पूर्णांक flags)
अणु
	अगर ((mode->flags & DRM_MODE_FLAG_INTERLACE) &&
	    !(flags & DRM_MODE_FLAG_INTERLACE))
		वापस MODE_NO_INTERLACE;

	अगर ((mode->flags & DRM_MODE_FLAG_DBLSCAN) &&
	    !(flags & DRM_MODE_FLAG_DBLSCAN))
		वापस MODE_NO_DBLESCAN;

	अगर ((mode->flags & DRM_MODE_FLAG_3D_MASK) &&
	    !(flags & DRM_MODE_FLAG_3D_MASK))
		वापस MODE_NO_STEREO;

	वापस MODE_OK;
पूर्ण

अटल पूर्णांक
drm_mode_validate_pipeline(काष्ठा drm_display_mode *mode,
			   काष्ठा drm_connector *connector,
			   काष्ठा drm_modeset_acquire_ctx *ctx,
			   क्रमागत drm_mode_status *status)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_encoder *encoder;
	पूर्णांक ret;

	/* Step 1: Validate against connector */
	ret = drm_connector_mode_valid(connector, mode, ctx, status);
	अगर (ret || *status != MODE_OK)
		वापस ret;

	/* Step 2: Validate against encoders and crtcs */
	drm_connector_क्रम_each_possible_encoder(connector, encoder) अणु
		काष्ठा drm_bridge *bridge;
		काष्ठा drm_crtc *crtc;

		*status = drm_encoder_mode_valid(encoder, mode);
		अगर (*status != MODE_OK) अणु
			/* No poपूर्णांक in continuing क्रम crtc check as this encoder
			 * will not accept the mode anyway. If all encoders
			 * reject the mode then, at निकास, ret will not be
			 * MODE_OK. */
			जारी;
		पूर्ण

		bridge = drm_bridge_chain_get_first_bridge(encoder);
		*status = drm_bridge_chain_mode_valid(bridge,
						      &connector->display_info,
						      mode);
		अगर (*status != MODE_OK) अणु
			/* There is also no poपूर्णांक in continuing क्रम crtc check
			 * here. */
			जारी;
		पूर्ण

		drm_क्रम_each_crtc(crtc, dev) अणु
			अगर (!drm_encoder_crtc_ok(encoder, crtc))
				जारी;

			*status = drm_crtc_mode_valid(crtc, mode);
			अगर (*status == MODE_OK) अणु
				/* If we get to this poपूर्णांक there is at least
				 * one combination of encoder+crtc that works
				 * क्रम this mode. Lets वापस now. */
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक drm_helper_probe_add_cmdline_mode(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_cmdline_mode *cmdline_mode;
	काष्ठा drm_display_mode *mode;

	cmdline_mode = &connector->cmdline_mode;
	अगर (!cmdline_mode->specअगरied)
		वापस 0;

	/* Only add a GTF mode अगर we find no matching probed modes */
	list_क्रम_each_entry(mode, &connector->probed_modes, head) अणु
		अगर (mode->hdisplay != cmdline_mode->xres ||
		    mode->vdisplay != cmdline_mode->yres)
			जारी;

		अगर (cmdline_mode->refresh_specअगरied) अणु
			/* The probed mode's vrefresh is set until later */
			अगर (drm_mode_vrefresh(mode) != cmdline_mode->refresh)
				जारी;
		पूर्ण

		/* Mark the matching mode as being preferred by the user */
		mode->type |= DRM_MODE_TYPE_USERDEF;
		वापस 0;
	पूर्ण

	mode = drm_mode_create_from_cmdline_mode(connector->dev,
						 cmdline_mode);
	अगर (mode == शून्य)
		वापस 0;

	drm_mode_probed_add(connector, mode);
	वापस 1;
पूर्ण

क्रमागत drm_mode_status drm_crtc_mode_valid(काष्ठा drm_crtc *crtc,
					 स्थिर काष्ठा drm_display_mode *mode)
अणु
	स्थिर काष्ठा drm_crtc_helper_funcs *crtc_funcs = crtc->helper_निजी;

	अगर (!crtc_funcs || !crtc_funcs->mode_valid)
		वापस MODE_OK;

	वापस crtc_funcs->mode_valid(crtc, mode);
पूर्ण

क्रमागत drm_mode_status drm_encoder_mode_valid(काष्ठा drm_encoder *encoder,
					    स्थिर काष्ठा drm_display_mode *mode)
अणु
	स्थिर काष्ठा drm_encoder_helper_funcs *encoder_funcs =
		encoder->helper_निजी;

	अगर (!encoder_funcs || !encoder_funcs->mode_valid)
		वापस MODE_OK;

	वापस encoder_funcs->mode_valid(encoder, mode);
पूर्ण

पूर्णांक
drm_connector_mode_valid(काष्ठा drm_connector *connector,
			 काष्ठा drm_display_mode *mode,
			 काष्ठा drm_modeset_acquire_ctx *ctx,
			 क्रमागत drm_mode_status *status)
अणु
	स्थिर काष्ठा drm_connector_helper_funcs *connector_funcs =
		connector->helper_निजी;
	पूर्णांक ret = 0;

	अगर (!connector_funcs)
		*status = MODE_OK;
	अन्यथा अगर (connector_funcs->mode_valid_ctx)
		ret = connector_funcs->mode_valid_ctx(connector, mode, ctx,
						      status);
	अन्यथा अगर (connector_funcs->mode_valid)
		*status = connector_funcs->mode_valid(connector, mode);
	अन्यथा
		*status = MODE_OK;

	वापस ret;
पूर्ण

#घोषणा DRM_OUTPUT_POLL_PERIOD (10*HZ)
/**
 * drm_kms_helper_poll_enable - re-enable output polling.
 * @dev: drm_device
 *
 * This function re-enables the output polling work, after it has been
 * temporarily disabled using drm_kms_helper_poll_disable(), क्रम example over
 * suspend/resume.
 *
 * Drivers can call this helper from their device resume implementation. It is
 * not an error to call this even when output polling isn't enabled.
 *
 * Note that calls to enable and disable polling must be strictly ordered, which
 * is स्वतःmatically the हाल when they're only call from suspend/resume
 * callbacks.
 */
व्योम drm_kms_helper_poll_enable(काष्ठा drm_device *dev)
अणु
	bool poll = false;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;
	अचिन्हित दीर्घ delay = DRM_OUTPUT_POLL_PERIOD;

	अगर (!dev->mode_config.poll_enabled || !drm_kms_helper_poll)
		वापस;

	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
		अगर (connector->polled & (DRM_CONNECTOR_POLL_CONNECT |
					 DRM_CONNECTOR_POLL_DISCONNECT))
			poll = true;
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	अगर (dev->mode_config.delayed_event) अणु
		/*
		 * FIXME:
		 *
		 * Use लघु (1s) delay to handle the initial delayed event.
		 * This delay should not be needed, but Optimus/nouveau will
		 * fail in a mysterious way अगर the delayed event is handled as
		 * soon as possible like it is करोne in
		 * drm_helper_probe_single_connector_modes() in हाल the poll
		 * was enabled beक्रमe.
		 */
		poll = true;
		delay = HZ;
	पूर्ण

	अगर (poll)
		schedule_delayed_work(&dev->mode_config.output_poll_work, delay);
पूर्ण
EXPORT_SYMBOL(drm_kms_helper_poll_enable);

अटल क्रमागत drm_connector_status
drm_helper_probe_detect_ctx(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	स्थिर काष्ठा drm_connector_helper_funcs *funcs = connector->helper_निजी;
	काष्ठा drm_modeset_acquire_ctx ctx;
	पूर्णांक ret;

	drm_modeset_acquire_init(&ctx, 0);

retry:
	ret = drm_modeset_lock(&connector->dev->mode_config.connection_mutex, &ctx);
	अगर (!ret) अणु
		अगर (funcs->detect_ctx)
			ret = funcs->detect_ctx(connector, &ctx, क्रमce);
		अन्यथा अगर (connector->funcs->detect)
			ret = connector->funcs->detect(connector, क्रमce);
		अन्यथा
			ret = connector_status_connected;
	पूर्ण

	अगर (ret == -EDEADLK) अणु
		drm_modeset_backoff(&ctx);
		जाओ retry;
	पूर्ण

	अगर (WARN_ON(ret < 0))
		ret = connector_status_unknown;

	अगर (ret != connector->status)
		connector->epoch_counter += 1;

	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);

	वापस ret;
पूर्ण

/**
 * drm_helper_probe_detect - probe connector status
 * @connector: connector to probe
 * @ctx: acquire_ctx, or शून्य to let this function handle locking.
 * @क्रमce: Whether deकाष्ठाive probe operations should be perक्रमmed.
 *
 * This function calls the detect callbacks of the connector.
 * This function वापसs &drm_connector_status, or
 * अगर @ctx is set, it might also वापस -EDEADLK.
 */
पूर्णांक
drm_helper_probe_detect(काष्ठा drm_connector *connector,
			काष्ठा drm_modeset_acquire_ctx *ctx,
			bool क्रमce)
अणु
	स्थिर काष्ठा drm_connector_helper_funcs *funcs = connector->helper_निजी;
	काष्ठा drm_device *dev = connector->dev;
	पूर्णांक ret;

	अगर (!ctx)
		वापस drm_helper_probe_detect_ctx(connector, क्रमce);

	ret = drm_modeset_lock(&dev->mode_config.connection_mutex, ctx);
	अगर (ret)
		वापस ret;

	अगर (funcs->detect_ctx)
		ret = funcs->detect_ctx(connector, ctx, क्रमce);
	अन्यथा अगर (connector->funcs->detect)
		ret = connector->funcs->detect(connector, क्रमce);
	अन्यथा
		ret = connector_status_connected;

	अगर (ret != connector->status)
		connector->epoch_counter += 1;

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_helper_probe_detect);

/**
 * drm_helper_probe_single_connector_modes - get complete set of display modes
 * @connector: connector to probe
 * @maxX: max width क्रम modes
 * @maxY: max height क्रम modes
 *
 * Based on the helper callbacks implemented by @connector in काष्ठा
 * &drm_connector_helper_funcs try to detect all valid modes.  Modes will first
 * be added to the connector's probed_modes list, then culled (based on validity
 * and the @maxX, @maxY parameters) and put पूर्णांकo the normal modes list.
 *
 * Intended to be used as a generic implementation of the
 * &drm_connector_funcs.fill_modes() vfunc क्रम drivers that use the CRTC helpers
 * क्रम output mode filtering and detection.
 *
 * The basic procedure is as follows
 *
 * 1. All modes currently on the connector's modes list are marked as stale
 *
 * 2. New modes are added to the connector's probed_modes list with
 *    drm_mode_probed_add(). New modes start their lअगरe with status as OK.
 *    Modes are added from a single source using the following priority order.
 *
 *    - &drm_connector_helper_funcs.get_modes vfunc
 *    - अगर the connector status is connector_status_connected, standard
 *      VESA DMT modes up to 1024x768 are स्वतःmatically added
 *      (drm_add_modes_noedid())
 *
 *    Finally modes specअगरied via the kernel command line (video=...) are
 *    added in addition to what the earlier probes produced
 *    (drm_helper_probe_add_cmdline_mode()). These modes are generated
 *    using the VESA GTF/CVT क्रमmulas.
 *
 * 3. Modes are moved from the probed_modes list to the modes list. Potential
 *    duplicates are merged together (see drm_connector_list_update()).
 *    After this step the probed_modes list will be empty again.
 *
 * 4. Any non-stale mode on the modes list then undergoes validation
 *
 *    - drm_mode_validate_basic() perक्रमms basic sanity checks
 *    - drm_mode_validate_size() filters out modes larger than @maxX and @maxY
 *      (अगर specअगरied)
 *    - drm_mode_validate_flag() checks the modes against basic connector
 *      capabilities (पूर्णांकerlace_allowed,द्विगुनscan_allowed,stereo_allowed)
 *    - the optional &drm_connector_helper_funcs.mode_valid or
 *      &drm_connector_helper_funcs.mode_valid_ctx helpers can perक्रमm driver
 *      and/or sink specअगरic checks
 *    - the optional &drm_crtc_helper_funcs.mode_valid,
 *      &drm_bridge_funcs.mode_valid and &drm_encoder_helper_funcs.mode_valid
 *      helpers can perक्रमm driver and/or source specअगरic checks which are also
 *      enक्रमced by the modeset/atomic helpers
 *
 * 5. Any mode whose status is not OK is pruned from the connector's modes list,
 *    accompanied by a debug message indicating the reason क्रम the mode's
 *    rejection (see drm_mode_prune_invalid()).
 *
 * Returns:
 * The number of modes found on @connector.
 */
पूर्णांक drm_helper_probe_single_connector_modes(काष्ठा drm_connector *connector,
					    uपूर्णांक32_t maxX, uपूर्णांक32_t maxY)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_display_mode *mode;
	स्थिर काष्ठा drm_connector_helper_funcs *connector_funcs =
		connector->helper_निजी;
	पूर्णांक count = 0, ret;
	पूर्णांक mode_flags = 0;
	bool verbose_prune = true;
	क्रमागत drm_connector_status old_status;
	काष्ठा drm_modeset_acquire_ctx ctx;

	WARN_ON(!mutex_is_locked(&dev->mode_config.mutex));

	drm_modeset_acquire_init(&ctx, 0);

	DRM_DEBUG_KMS("[CONNECTOR:%d:%s]\n", connector->base.id,
			connector->name);

retry:
	ret = drm_modeset_lock(&dev->mode_config.connection_mutex, &ctx);
	अगर (ret == -EDEADLK) अणु
		drm_modeset_backoff(&ctx);
		जाओ retry;
	पूर्ण अन्यथा
		WARN_ON(ret < 0);

	/* set all old modes to the stale state */
	list_क्रम_each_entry(mode, &connector->modes, head)
		mode->status = MODE_STALE;

	old_status = connector->status;

	अगर (connector->क्रमce) अणु
		अगर (connector->क्रमce == DRM_FORCE_ON ||
		    connector->क्रमce == DRM_FORCE_ON_DIGITAL)
			connector->status = connector_status_connected;
		अन्यथा
			connector->status = connector_status_disconnected;
		अगर (connector->funcs->क्रमce)
			connector->funcs->क्रमce(connector);
	पूर्ण अन्यथा अणु
		ret = drm_helper_probe_detect(connector, &ctx, true);

		अगर (ret == -EDEADLK) अणु
			drm_modeset_backoff(&ctx);
			जाओ retry;
		पूर्ण अन्यथा अगर (WARN(ret < 0, "Invalid return value %i for connector detection\n", ret))
			ret = connector_status_unknown;

		connector->status = ret;
	पूर्ण

	/*
	 * Normally either the driver's hpd code or the poll loop should
	 * pick up any changes and fire the hotplug event. But अगर
	 * userspace sneaks in a probe, we might miss a change. Hence
	 * check here, and अगर anything changed start the hotplug code.
	 */
	अगर (old_status != connector->status) अणु
		DRM_DEBUG_KMS("[CONNECTOR:%d:%s] status updated from %s to %s\n",
			      connector->base.id,
			      connector->name,
			      drm_get_connector_status_name(old_status),
			      drm_get_connector_status_name(connector->status));

		/*
		 * The hotplug event code might call पूर्णांकo the fb
		 * helpers, and so expects that we करो not hold any
		 * locks. Fire up the poll काष्ठा instead, it will
		 * disable itself again.
		 */
		dev->mode_config.delayed_event = true;
		अगर (dev->mode_config.poll_enabled)
			schedule_delayed_work(&dev->mode_config.output_poll_work,
					      0);
	पूर्ण

	/* Re-enable polling in हाल the global poll config changed. */
	अगर (drm_kms_helper_poll != dev->mode_config.poll_running)
		drm_kms_helper_poll_enable(dev);

	dev->mode_config.poll_running = drm_kms_helper_poll;

	अगर (connector->status == connector_status_disconnected) अणु
		DRM_DEBUG_KMS("[CONNECTOR:%d:%s] disconnected\n",
			connector->base.id, connector->name);
		drm_connector_update_edid_property(connector, शून्य);
		verbose_prune = false;
		जाओ prune;
	पूर्ण

	count = (*connector_funcs->get_modes)(connector);

	/*
	 * Fallback क्रम when DDC probe failed in drm_get_edid() and thus skipped
	 * override/firmware EDID.
	 */
	अगर (count == 0 && connector->status == connector_status_connected)
		count = drm_add_override_edid_modes(connector);

	अगर (count == 0 && (connector->status == connector_status_connected ||
			   connector->status == connector_status_unknown))
		count = drm_add_modes_noedid(connector, 1024, 768);
	count += drm_helper_probe_add_cmdline_mode(connector);
	अगर (count == 0)
		जाओ prune;

	drm_connector_list_update(connector);

	अगर (connector->पूर्णांकerlace_allowed)
		mode_flags |= DRM_MODE_FLAG_INTERLACE;
	अगर (connector->द्विगुनscan_allowed)
		mode_flags |= DRM_MODE_FLAG_DBLSCAN;
	अगर (connector->stereo_allowed)
		mode_flags |= DRM_MODE_FLAG_3D_MASK;

	list_क्रम_each_entry(mode, &connector->modes, head) अणु
		अगर (mode->status != MODE_OK)
			जारी;

		mode->status = drm_mode_validate_driver(dev, mode);
		अगर (mode->status != MODE_OK)
			जारी;

		mode->status = drm_mode_validate_size(mode, maxX, maxY);
		अगर (mode->status != MODE_OK)
			जारी;

		mode->status = drm_mode_validate_flag(mode, mode_flags);
		अगर (mode->status != MODE_OK)
			जारी;

		ret = drm_mode_validate_pipeline(mode, connector, &ctx,
						 &mode->status);
		अगर (ret) अणु
			drm_dbg_kms(dev,
				    "drm_mode_validate_pipeline failed: %d\n",
				    ret);

			अगर (drm_WARN_ON_ONCE(dev, ret != -EDEADLK)) अणु
				mode->status = MODE_ERROR;
			पूर्ण अन्यथा अणु
				drm_modeset_backoff(&ctx);
				जाओ retry;
			पूर्ण
		पूर्ण

		अगर (mode->status != MODE_OK)
			जारी;
		mode->status = drm_mode_validate_ycbcr420(mode, connector);
	पूर्ण

prune:
	drm_mode_prune_invalid(dev, &connector->modes, verbose_prune);

	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);

	अगर (list_empty(&connector->modes))
		वापस 0;

	drm_mode_sort(&connector->modes);

	DRM_DEBUG_KMS("[CONNECTOR:%d:%s] probed modes :\n", connector->base.id,
			connector->name);
	list_क्रम_each_entry(mode, &connector->modes, head) अणु
		drm_mode_set_crtcinfo(mode, CRTC_INTERLACE_HALVE_V);
		drm_mode_debug_prपूर्णांकmodeline(mode);
	पूर्ण

	वापस count;
पूर्ण
EXPORT_SYMBOL(drm_helper_probe_single_connector_modes);

/**
 * drm_kms_helper_hotplug_event - fire off KMS hotplug events
 * @dev: drm_device whose connector state changed
 *
 * This function fires off the uevent क्रम userspace and also calls the
 * output_poll_changed function, which is most commonly used to inक्रमm the fbdev
 * emulation code and allow it to update the fbcon output configuration.
 *
 * Drivers should call this from their hotplug handling code when a change is
 * detected. Note that this function करोes not करो any output detection of its
 * own, like drm_helper_hpd_irq_event() करोes - this is assumed to be करोne by the
 * driver alपढ़ोy.
 *
 * This function must be called from process context with no mode
 * setting locks held.
 */
व्योम drm_kms_helper_hotplug_event(काष्ठा drm_device *dev)
अणु
	/* send a uevent + call fbdev */
	drm_sysfs_hotplug_event(dev);
	अगर (dev->mode_config.funcs->output_poll_changed)
		dev->mode_config.funcs->output_poll_changed(dev);

	drm_client_dev_hotplug(dev);
पूर्ण
EXPORT_SYMBOL(drm_kms_helper_hotplug_event);

अटल व्योम output_poll_execute(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *delayed_work = to_delayed_work(work);
	काष्ठा drm_device *dev = container_of(delayed_work, काष्ठा drm_device, mode_config.output_poll_work);
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;
	क्रमागत drm_connector_status old_status;
	bool repoll = false, changed;
	u64 old_epoch_counter;

	अगर (!dev->mode_config.poll_enabled)
		वापस;

	/* Pick up any changes detected by the probe functions. */
	changed = dev->mode_config.delayed_event;
	dev->mode_config.delayed_event = false;

	अगर (!drm_kms_helper_poll)
		जाओ out;

	अगर (!mutex_trylock(&dev->mode_config.mutex)) अणु
		repoll = true;
		जाओ out;
	पूर्ण

	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
		/* Ignore क्रमced connectors. */
		अगर (connector->क्रमce)
			जारी;

		/* Ignore HPD capable connectors and connectors where we करोn't
		 * want any hotplug detection at all क्रम polling. */
		अगर (!connector->polled || connector->polled == DRM_CONNECTOR_POLL_HPD)
			जारी;

		old_status = connector->status;
		/* अगर we are connected and करोn't want to poll क्रम disconnect
		   skip it */
		अगर (old_status == connector_status_connected &&
		    !(connector->polled & DRM_CONNECTOR_POLL_DISCONNECT))
			जारी;

		repoll = true;

		old_epoch_counter = connector->epoch_counter;
		connector->status = drm_helper_probe_detect(connector, शून्य, false);
		अगर (old_epoch_counter != connector->epoch_counter) अणु
			स्थिर अक्षर *old, *new;

			/*
			 * The poll work sets क्रमce=false when calling detect so
			 * that drivers can aव्योम to करो disruptive tests (e.g.
			 * when load detect cycles could cause flickering on
			 * other, running displays). This bears the risk that we
			 * flip-flop between unknown here in the poll work and
			 * the real state when userspace क्रमces a full detect
			 * call after receiving a hotplug event due to this
			 * change.
			 *
			 * Hence clamp an unknown detect status to the old
			 * value.
			 */
			अगर (connector->status == connector_status_unknown) अणु
				connector->status = old_status;
				जारी;
			पूर्ण

			old = drm_get_connector_status_name(old_status);
			new = drm_get_connector_status_name(connector->status);

			DRM_DEBUG_KMS("[CONNECTOR:%d:%s] "
				      "status updated from %s to %s\n",
				      connector->base.id,
				      connector->name,
				      old, new);
			DRM_DEBUG_KMS("[CONNECTOR:%d:%s] epoch counter %llu -> %llu\n",
				      connector->base.id, connector->name,
				      old_epoch_counter, connector->epoch_counter);

			changed = true;
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	mutex_unlock(&dev->mode_config.mutex);

out:
	अगर (changed)
		drm_kms_helper_hotplug_event(dev);

	अगर (repoll)
		schedule_delayed_work(delayed_work, DRM_OUTPUT_POLL_PERIOD);
पूर्ण

/**
 * drm_kms_helper_is_poll_worker - is %current task an output poll worker?
 *
 * Determine अगर %current task is an output poll worker.  This can be used
 * to select distinct code paths क्रम output polling versus other contexts.
 *
 * One use हाल is to aव्योम a deadlock between the output poll worker and
 * the स्वतःsuspend worker wherein the latter रुकोs क्रम polling to finish
 * upon calling drm_kms_helper_poll_disable(), जबतक the क्रमmer रुकोs क्रम
 * runसमय suspend to finish upon calling pm_runसमय_get_sync() in a
 * connector ->detect hook.
 */
bool drm_kms_helper_is_poll_worker(व्योम)
अणु
	काष्ठा work_काष्ठा *work = current_work();

	वापस work && work->func == output_poll_execute;
पूर्ण
EXPORT_SYMBOL(drm_kms_helper_is_poll_worker);

/**
 * drm_kms_helper_poll_disable - disable output polling
 * @dev: drm_device
 *
 * This function disables the output polling work.
 *
 * Drivers can call this helper from their device suspend implementation. It is
 * not an error to call this even when output polling isn't enabled or alपढ़ोy
 * disabled. Polling is re-enabled by calling drm_kms_helper_poll_enable().
 *
 * Note that calls to enable and disable polling must be strictly ordered, which
 * is स्वतःmatically the हाल when they're only call from suspend/resume
 * callbacks.
 */
व्योम drm_kms_helper_poll_disable(काष्ठा drm_device *dev)
अणु
	अगर (!dev->mode_config.poll_enabled)
		वापस;
	cancel_delayed_work_sync(&dev->mode_config.output_poll_work);
पूर्ण
EXPORT_SYMBOL(drm_kms_helper_poll_disable);

/**
 * drm_kms_helper_poll_init - initialize and enable output polling
 * @dev: drm_device
 *
 * This function पूर्णांकializes and then also enables output polling support क्रम
 * @dev. Drivers which करो not have reliable hotplug support in hardware can use
 * this helper infraकाष्ठाure to regularly poll such connectors क्रम changes in
 * their connection state.
 *
 * Drivers can control which connectors are polled by setting the
 * DRM_CONNECTOR_POLL_CONNECT and DRM_CONNECTOR_POLL_DISCONNECT flags. On
 * connectors where probing live outमाला_दो can result in visual distortion drivers
 * should not set the DRM_CONNECTOR_POLL_DISCONNECT flag to aव्योम this.
 * Connectors which have no flag or only DRM_CONNECTOR_POLL_HPD set are
 * completely ignored by the polling logic.
 *
 * Note that a connector can be both polled and probed from the hotplug handler,
 * in हाल the hotplug पूर्णांकerrupt is known to be unreliable.
 */
व्योम drm_kms_helper_poll_init(काष्ठा drm_device *dev)
अणु
	INIT_DELAYED_WORK(&dev->mode_config.output_poll_work, output_poll_execute);
	dev->mode_config.poll_enabled = true;

	drm_kms_helper_poll_enable(dev);
पूर्ण
EXPORT_SYMBOL(drm_kms_helper_poll_init);

/**
 * drm_kms_helper_poll_fini - disable output polling and clean it up
 * @dev: drm_device
 */
व्योम drm_kms_helper_poll_fini(काष्ठा drm_device *dev)
अणु
	अगर (!dev->mode_config.poll_enabled)
		वापस;

	dev->mode_config.poll_enabled = false;
	cancel_delayed_work_sync(&dev->mode_config.output_poll_work);
पूर्ण
EXPORT_SYMBOL(drm_kms_helper_poll_fini);

/**
 * drm_helper_hpd_irq_event - hotplug processing
 * @dev: drm_device
 *
 * Drivers can use this helper function to run a detect cycle on all connectors
 * which have the DRM_CONNECTOR_POLL_HPD flag set in their &polled member. All
 * other connectors are ignored, which is useful to aव्योम reprobing fixed
 * panels.
 *
 * This helper function is useful क्रम drivers which can't or don't track hotplug
 * पूर्णांकerrupts क्रम each connector.
 *
 * Drivers which support hotplug पूर्णांकerrupts क्रम each connector inभागidually and
 * which have a more fine-grained detect logic should bypass this code and
 * directly call drm_kms_helper_hotplug_event() in हाल the connector state
 * changed.
 *
 * This function must be called from process context with no mode
 * setting locks held.
 *
 * Note that a connector can be both polled and probed from the hotplug handler,
 * in हाल the hotplug पूर्णांकerrupt is known to be unreliable.
 */
bool drm_helper_hpd_irq_event(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;
	क्रमागत drm_connector_status old_status;
	bool changed = false;
	u64 old_epoch_counter;

	अगर (!dev->mode_config.poll_enabled)
		वापस false;

	mutex_lock(&dev->mode_config.mutex);
	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
		/* Only handle HPD capable connectors. */
		अगर (!(connector->polled & DRM_CONNECTOR_POLL_HPD))
			जारी;

		old_status = connector->status;

		old_epoch_counter = connector->epoch_counter;

		DRM_DEBUG_KMS("[CONNECTOR:%d:%s] Old epoch counter %llu\n", connector->base.id,
			      connector->name,
			      old_epoch_counter);

		connector->status = drm_helper_probe_detect(connector, शून्य, false);
		DRM_DEBUG_KMS("[CONNECTOR:%d:%s] status updated from %s to %s\n",
			      connector->base.id,
			      connector->name,
			      drm_get_connector_status_name(old_status),
			      drm_get_connector_status_name(connector->status));

		DRM_DEBUG_KMS("[CONNECTOR:%d:%s] New epoch counter %llu\n",
			      connector->base.id,
			      connector->name,
			      connector->epoch_counter);

		/*
		 * Check अगर epoch counter had changed, meaning that we need
		 * to send a uevent.
		 */
		अगर (old_epoch_counter != connector->epoch_counter)
			changed = true;

	पूर्ण
	drm_connector_list_iter_end(&conn_iter);
	mutex_unlock(&dev->mode_config.mutex);

	अगर (changed) अणु
		drm_kms_helper_hotplug_event(dev);
		DRM_DEBUG_KMS("Sent hotplug event\n");
	पूर्ण

	वापस changed;
पूर्ण
EXPORT_SYMBOL(drm_helper_hpd_irq_event);
