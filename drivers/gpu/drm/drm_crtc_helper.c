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
#समावेश <linux/kernel.h>
#समावेश <linux/moduleparam.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_atomic_uapi.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_vblank.h>

#समावेश "drm_crtc_helper_internal.h"

/**
 * DOC: overview
 *
 * The CRTC modeset helper library provides a शेष set_config implementation
 * in drm_crtc_helper_set_config(). Plus a few other convenience functions using
 * the same callbacks which drivers can use to e.g. restore the modeset
 * configuration on resume with drm_helper_resume_क्रमce_mode().
 *
 * Note that this helper library करोesn't track the current घातer state of CRTCs
 * and encoders. It can call callbacks like &drm_encoder_helper_funcs.dpms even
 * though the hardware is alपढ़ोy in the desired state. This deficiency has been
 * fixed in the atomic helpers.
 *
 * The driver callbacks are mostly compatible with the atomic modeset helpers,
 * except क्रम the handling of the primary plane: Atomic helpers require that the
 * primary plane is implemented as a real standalone plane and not directly tied
 * to the CRTC state. For easier transition this library provides functions to
 * implement the old semantics required by the CRTC helpers using the new plane
 * and atomic helper callbacks.
 *
 * Drivers are strongly urged to convert to the atomic helpers (by way of first
 * converting to the plane helpers). New drivers must not use these functions
 * but need to implement the atomic पूर्णांकerface instead, potentially using the
 * atomic helpers क्रम that.
 *
 * These legacy modeset helpers use the same function table काष्ठाures as
 * all other modesetting helpers. See the करोcumentation क्रम काष्ठा
 * &drm_crtc_helper_funcs, &काष्ठा drm_encoder_helper_funcs and काष्ठा
 * &drm_connector_helper_funcs.
 */

/**
 * drm_helper_encoder_in_use - check अगर a given encoder is in use
 * @encoder: encoder to check
 *
 * Checks whether @encoder is with the current mode setting output configuration
 * in use by any connector. This करोesn't mean that it is actually enabled since
 * the DPMS state is tracked separately.
 *
 * Returns:
 * True अगर @encoder is used, false otherwise.
 */
bool drm_helper_encoder_in_use(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;
	काष्ठा drm_device *dev = encoder->dev;

	WARN_ON(drm_drv_uses_atomic_modeset(dev));

	/*
	 * We can expect this mutex to be locked अगर we are not panicking.
	 * Locking is currently fubar in the panic handler.
	 */
	अगर (!oops_in_progress) अणु
		WARN_ON(!mutex_is_locked(&dev->mode_config.mutex));
		WARN_ON(!drm_modeset_is_locked(&dev->mode_config.connection_mutex));
	पूर्ण


	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
		अगर (connector->encoder == encoder) अणु
			drm_connector_list_iter_end(&conn_iter);
			वापस true;
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);
	वापस false;
पूर्ण
EXPORT_SYMBOL(drm_helper_encoder_in_use);

/**
 * drm_helper_crtc_in_use - check अगर a given CRTC is in a mode_config
 * @crtc: CRTC to check
 *
 * Checks whether @crtc is with the current mode setting output configuration
 * in use by any connector. This करोesn't mean that it is actually enabled since
 * the DPMS state is tracked separately.
 *
 * Returns:
 * True अगर @crtc is used, false otherwise.
 */
bool drm_helper_crtc_in_use(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_device *dev = crtc->dev;

	WARN_ON(drm_drv_uses_atomic_modeset(dev));

	/*
	 * We can expect this mutex to be locked अगर we are not panicking.
	 * Locking is currently fubar in the panic handler.
	 */
	अगर (!oops_in_progress)
		WARN_ON(!mutex_is_locked(&dev->mode_config.mutex));

	drm_क्रम_each_encoder(encoder, dev)
		अगर (encoder->crtc == crtc && drm_helper_encoder_in_use(encoder))
			वापस true;
	वापस false;
पूर्ण
EXPORT_SYMBOL(drm_helper_crtc_in_use);

अटल व्योम
drm_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	स्थिर काष्ठा drm_encoder_helper_funcs *encoder_funcs = encoder->helper_निजी;

	अगर (!encoder_funcs)
		वापस;

	अगर (encoder_funcs->disable)
		(*encoder_funcs->disable)(encoder);
	अन्यथा अगर (encoder_funcs->dpms)
		(*encoder_funcs->dpms)(encoder, DRM_MODE_DPMS_OFF);
पूर्ण

अटल व्योम __drm_helper_disable_unused_functions(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_crtc *crtc;

	drm_warn_on_modeset_not_all_locked(dev);

	drm_क्रम_each_encoder(encoder, dev) अणु
		अगर (!drm_helper_encoder_in_use(encoder)) अणु
			drm_encoder_disable(encoder);
			/* disconnect encoder from any connector */
			encoder->crtc = शून्य;
		पूर्ण
	पूर्ण

	drm_क्रम_each_crtc(crtc, dev) अणु
		स्थिर काष्ठा drm_crtc_helper_funcs *crtc_funcs = crtc->helper_निजी;

		crtc->enabled = drm_helper_crtc_in_use(crtc);
		अगर (!crtc->enabled) अणु
			अगर (crtc_funcs->disable)
				(*crtc_funcs->disable)(crtc);
			अन्यथा
				(*crtc_funcs->dpms)(crtc, DRM_MODE_DPMS_OFF);
			crtc->primary->fb = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * drm_helper_disable_unused_functions - disable unused objects
 * @dev: DRM device
 *
 * This function walks through the entire mode setting configuration of @dev. It
 * will हटाओ any CRTC links of unused encoders and encoder links of
 * disconnected connectors. Then it will disable all unused encoders and CRTCs
 * either by calling their disable callback अगर available or by calling their
 * dpms callback with DRM_MODE_DPMS_OFF.
 *
 * NOTE:
 *
 * This function is part of the legacy modeset helper library and will cause
 * major confusion with atomic drivers. This is because atomic helpers guarantee
 * to never call ->disable() hooks on a disabled function, or ->enable() hooks
 * on an enabled functions. drm_helper_disable_unused_functions() on the other
 * hand throws such guarantees पूर्णांकo the wind and calls disable hooks
 * unconditionally on unused functions.
 */
व्योम drm_helper_disable_unused_functions(काष्ठा drm_device *dev)
अणु
	WARN_ON(drm_drv_uses_atomic_modeset(dev));

	drm_modeset_lock_all(dev);
	__drm_helper_disable_unused_functions(dev);
	drm_modeset_unlock_all(dev);
पूर्ण
EXPORT_SYMBOL(drm_helper_disable_unused_functions);

/*
 * Check the CRTC we're going to map each output to vs. its current
 * CRTC.  If they करोn't match, we have to disable the output and the CRTC
 * since the driver will have to re-route things.
 */
अटल व्योम
drm_crtc_prepare_encoders(काष्ठा drm_device *dev)
अणु
	स्थिर काष्ठा drm_encoder_helper_funcs *encoder_funcs;
	काष्ठा drm_encoder *encoder;

	drm_क्रम_each_encoder(encoder, dev) अणु
		encoder_funcs = encoder->helper_निजी;
		अगर (!encoder_funcs)
			जारी;

		/* Disable unused encoders */
		अगर (encoder->crtc == शून्य)
			drm_encoder_disable(encoder);
	पूर्ण
पूर्ण

/**
 * drm_crtc_helper_set_mode - पूर्णांकernal helper to set a mode
 * @crtc: CRTC to program
 * @mode: mode to use
 * @x: horizontal offset पूर्णांकo the surface
 * @y: vertical offset पूर्णांकo the surface
 * @old_fb: old framebuffer, क्रम cleanup
 *
 * Try to set @mode on @crtc.  Give @crtc and its associated connectors a chance
 * to fixup or reject the mode prior to trying to set it. This is an पूर्णांकernal
 * helper that drivers could e.g. use to update properties that require the
 * entire output pipe to be disabled and re-enabled in a new configuration. For
 * example क्रम changing whether audio is enabled on a hdmi link or क्रम changing
 * panel fitter or dither attributes. It is also called by the
 * drm_crtc_helper_set_config() helper function to drive the mode setting
 * sequence.
 *
 * Returns:
 * True अगर the mode was set successfully, false otherwise.
 */
bool drm_crtc_helper_set_mode(काष्ठा drm_crtc *crtc,
			      काष्ठा drm_display_mode *mode,
			      पूर्णांक x, पूर्णांक y,
			      काष्ठा drm_framebuffer *old_fb)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_display_mode *adjusted_mode, saved_mode, saved_hwmode;
	स्थिर काष्ठा drm_crtc_helper_funcs *crtc_funcs = crtc->helper_निजी;
	स्थिर काष्ठा drm_encoder_helper_funcs *encoder_funcs;
	पूर्णांक saved_x, saved_y;
	bool saved_enabled;
	काष्ठा drm_encoder *encoder;
	bool ret = true;

	WARN_ON(drm_drv_uses_atomic_modeset(dev));

	drm_warn_on_modeset_not_all_locked(dev);

	saved_enabled = crtc->enabled;
	crtc->enabled = drm_helper_crtc_in_use(crtc);
	अगर (!crtc->enabled)
		वापस true;

	adjusted_mode = drm_mode_duplicate(dev, mode);
	अगर (!adjusted_mode) अणु
		crtc->enabled = saved_enabled;
		वापस false;
	पूर्ण

	saved_mode = crtc->mode;
	saved_hwmode = crtc->hwmode;
	saved_x = crtc->x;
	saved_y = crtc->y;

	/* Update crtc values up front so the driver can rely on them क्रम mode
	 * setting.
	 */
	crtc->mode = *mode;
	crtc->x = x;
	crtc->y = y;

	/* Pass our mode to the connectors and the CRTC to give them a chance to
	 * adjust it according to limitations or connector properties, and also
	 * a chance to reject the mode entirely.
	 */
	drm_क्रम_each_encoder(encoder, dev) अणु

		अगर (encoder->crtc != crtc)
			जारी;

		encoder_funcs = encoder->helper_निजी;
		अगर (!encoder_funcs)
			जारी;

		encoder_funcs = encoder->helper_निजी;
		अगर (encoder_funcs->mode_fixup) अणु
			अगर (!(ret = encoder_funcs->mode_fixup(encoder, mode,
							      adjusted_mode))) अणु
				DRM_DEBUG_KMS("Encoder fixup failed\n");
				जाओ करोne;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (crtc_funcs->mode_fixup) अणु
		अगर (!(ret = crtc_funcs->mode_fixup(crtc, mode,
						adjusted_mode))) अणु
			DRM_DEBUG_KMS("CRTC fixup failed\n");
			जाओ करोne;
		पूर्ण
	पूर्ण
	DRM_DEBUG_KMS("[CRTC:%d:%s]\n", crtc->base.id, crtc->name);

	crtc->hwmode = *adjusted_mode;

	/* Prepare the encoders and CRTCs beक्रमe setting the mode. */
	drm_क्रम_each_encoder(encoder, dev) अणु

		अगर (encoder->crtc != crtc)
			जारी;

		encoder_funcs = encoder->helper_निजी;
		अगर (!encoder_funcs)
			जारी;

		/* Disable the encoders as the first thing we करो. */
		अगर (encoder_funcs->prepare)
			encoder_funcs->prepare(encoder);
	पूर्ण

	drm_crtc_prepare_encoders(dev);

	crtc_funcs->prepare(crtc);

	/* Set up the DPLL and any encoders state that needs to adjust or depend
	 * on the DPLL.
	 */
	ret = !crtc_funcs->mode_set(crtc, mode, adjusted_mode, x, y, old_fb);
	अगर (!ret)
	    जाओ करोne;

	drm_क्रम_each_encoder(encoder, dev) अणु

		अगर (encoder->crtc != crtc)
			जारी;

		encoder_funcs = encoder->helper_निजी;
		अगर (!encoder_funcs)
			जारी;

		DRM_DEBUG_KMS("[ENCODER:%d:%s] set [MODE:%s]\n",
			encoder->base.id, encoder->name, mode->name);
		अगर (encoder_funcs->mode_set)
			encoder_funcs->mode_set(encoder, mode, adjusted_mode);
	पूर्ण

	/* Now enable the घड़ीs, plane, pipe, and connectors that we set up. */
	crtc_funcs->commit(crtc);

	drm_क्रम_each_encoder(encoder, dev) अणु

		अगर (encoder->crtc != crtc)
			जारी;

		encoder_funcs = encoder->helper_निजी;
		अगर (!encoder_funcs)
			जारी;

		अगर (encoder_funcs->commit)
			encoder_funcs->commit(encoder);
	पूर्ण

	/* Calculate and store various स्थिरants which
	 * are later needed by vblank and swap-completion
	 * बारtamping. They are derived from true hwmode.
	 */
	drm_calc_बारtamping_स्थिरants(crtc, &crtc->hwmode);

	/* FIXME: add subpixel order */
करोne:
	drm_mode_destroy(dev, adjusted_mode);
	अगर (!ret) अणु
		crtc->enabled = saved_enabled;
		crtc->mode = saved_mode;
		crtc->hwmode = saved_hwmode;
		crtc->x = saved_x;
		crtc->y = saved_y;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_crtc_helper_set_mode);

अटल व्योम
drm_crtc_helper_disable(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_connector *connector;
	काष्ठा drm_encoder *encoder;

	/* Decouple all encoders and their attached connectors from this crtc */
	drm_क्रम_each_encoder(encoder, dev) अणु
		काष्ठा drm_connector_list_iter conn_iter;

		अगर (encoder->crtc != crtc)
			जारी;

		drm_connector_list_iter_begin(dev, &conn_iter);
		drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
			अगर (connector->encoder != encoder)
				जारी;

			connector->encoder = शून्य;

			/*
			 * drm_helper_disable_unused_functions() ought to be
			 * करोing this, but since we've decoupled the encoder
			 * from the connector above, the required connection
			 * between them is henceक्रमth no दीर्घer available.
			 */
			connector->dpms = DRM_MODE_DPMS_OFF;

			/* we keep a reference जबतक the encoder is bound */
			drm_connector_put(connector);
		पूर्ण
		drm_connector_list_iter_end(&conn_iter);
	पूर्ण

	__drm_helper_disable_unused_functions(dev);
पूर्ण

/*
 * For connectors that support multiple encoders, either the
 * .atomic_best_encoder() or .best_encoder() operation must be implemented.
 */
काष्ठा drm_encoder *
drm_connector_get_single_encoder(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_encoder *encoder;

	WARN_ON(hweight32(connector->possible_encoders) > 1);
	drm_connector_क्रम_each_possible_encoder(connector, encoder)
		वापस encoder;

	वापस शून्य;
पूर्ण

/**
 * drm_crtc_helper_set_config - set a new config from userspace
 * @set: mode set configuration
 * @ctx: lock acquire context, not used here
 *
 * The drm_crtc_helper_set_config() helper function implements the of
 * &drm_crtc_funcs.set_config callback क्रम drivers using the legacy CRTC
 * helpers.
 *
 * It first tries to locate the best encoder क्रम each connector by calling the
 * connector @drm_connector_helper_funcs.best_encoder helper operation.
 *
 * After locating the appropriate encoders, the helper function will call the
 * mode_fixup encoder and CRTC helper operations to adjust the requested mode,
 * or reject it completely in which हाल an error will be वापसed to the
 * application. If the new configuration after mode adjusपंचांगent is identical to
 * the current configuration the helper function will वापस without perक्रमming
 * any other operation.
 *
 * If the adjusted mode is identical to the current mode but changes to the
 * frame buffer need to be applied, the drm_crtc_helper_set_config() function
 * will call the CRTC &drm_crtc_helper_funcs.mode_set_base helper operation.
 *
 * If the adjusted mode dअगरfers from the current mode, or अगर the
 * ->mode_set_base() helper operation is not provided, the helper function
 * perक्रमms a full mode set sequence by calling the ->prepare(), ->mode_set()
 * and ->commit() CRTC and encoder helper operations, in that order.
 * Alternatively it can also use the dpms and disable helper operations. For
 * details see &काष्ठा drm_crtc_helper_funcs and काष्ठा
 * &drm_encoder_helper_funcs.
 *
 * This function is deprecated.  New drivers must implement atomic modeset
 * support, क्रम which this function is unsuitable. Instead drivers should use
 * drm_atomic_helper_set_config().
 *
 * Returns:
 * Returns 0 on success, negative त्रुटि_सं numbers on failure.
 */
पूर्णांक drm_crtc_helper_set_config(काष्ठा drm_mode_set *set,
			       काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा drm_device *dev;
	काष्ठा drm_crtc **save_encoder_crtcs, *new_crtc;
	काष्ठा drm_encoder **save_connector_encoders, *new_encoder, *encoder;
	bool mode_changed = false; /* अगर true करो a full mode set */
	bool fb_changed = false; /* अगर true and !mode_changed just करो a flip */
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;
	पूर्णांक count = 0, ro, fail = 0;
	स्थिर काष्ठा drm_crtc_helper_funcs *crtc_funcs;
	काष्ठा drm_mode_set save_set;
	पूर्णांक ret;
	पूर्णांक i;

	DRM_DEBUG_KMS("\n");

	BUG_ON(!set);
	BUG_ON(!set->crtc);
	BUG_ON(!set->crtc->helper_निजी);

	/* Enक्रमce sane पूर्णांकerface api - has been abused by the fb helper. */
	BUG_ON(!set->mode && set->fb);
	BUG_ON(set->fb && set->num_connectors == 0);

	crtc_funcs = set->crtc->helper_निजी;

	dev = set->crtc->dev;
	WARN_ON(drm_drv_uses_atomic_modeset(dev));

	अगर (!set->mode)
		set->fb = शून्य;

	अगर (set->fb) अणु
		DRM_DEBUG_KMS("[CRTC:%d:%s] [FB:%d] #connectors=%d (x y) (%i %i)\n",
			      set->crtc->base.id, set->crtc->name,
			      set->fb->base.id,
			      (पूर्णांक)set->num_connectors, set->x, set->y);
	पूर्ण अन्यथा अणु
		DRM_DEBUG_KMS("[CRTC:%d:%s] [NOFB]\n",
			      set->crtc->base.id, set->crtc->name);
		drm_crtc_helper_disable(set->crtc);
		वापस 0;
	पूर्ण

	drm_warn_on_modeset_not_all_locked(dev);

	/*
	 * Allocate space क्रम the backup of all (non-poपूर्णांकer) encoder and
	 * connector data.
	 */
	save_encoder_crtcs = kसुस्मृति(dev->mode_config.num_encoder,
				माप(काष्ठा drm_crtc *), GFP_KERNEL);
	अगर (!save_encoder_crtcs)
		वापस -ENOMEM;

	save_connector_encoders = kसुस्मृति(dev->mode_config.num_connector,
				माप(काष्ठा drm_encoder *), GFP_KERNEL);
	अगर (!save_connector_encoders) अणु
		kमुक्त(save_encoder_crtcs);
		वापस -ENOMEM;
	पूर्ण

	/*
	 * Copy data. Note that driver निजी data is not affected.
	 * Should anything bad happen only the expected state is
	 * restored, not the drivers personal bookkeeping.
	 */
	count = 0;
	drm_क्रम_each_encoder(encoder, dev) अणु
		save_encoder_crtcs[count++] = encoder->crtc;
	पूर्ण

	count = 0;
	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter)
		save_connector_encoders[count++] = connector->encoder;
	drm_connector_list_iter_end(&conn_iter);

	save_set.crtc = set->crtc;
	save_set.mode = &set->crtc->mode;
	save_set.x = set->crtc->x;
	save_set.y = set->crtc->y;
	save_set.fb = set->crtc->primary->fb;

	/* We should be able to check here अगर the fb has the same properties
	 * and then just flip_or_move it */
	अगर (set->crtc->primary->fb != set->fb) अणु
		/* If we have no fb then treat it as a full mode set */
		अगर (set->crtc->primary->fb == शून्य) अणु
			DRM_DEBUG_KMS("crtc has no fb, full mode set\n");
			mode_changed = true;
		पूर्ण अन्यथा अगर (set->fb->क्रमmat != set->crtc->primary->fb->क्रमmat) अणु
			mode_changed = true;
		पूर्ण अन्यथा
			fb_changed = true;
	पूर्ण

	अगर (set->x != set->crtc->x || set->y != set->crtc->y)
		fb_changed = true;

	अगर (!drm_mode_equal(set->mode, &set->crtc->mode)) अणु
		DRM_DEBUG_KMS("modes are different, full mode set\n");
		drm_mode_debug_prपूर्णांकmodeline(&set->crtc->mode);
		drm_mode_debug_prपूर्णांकmodeline(set->mode);
		mode_changed = true;
	पूर्ण

	/* take a reference on all unbound connectors in set, reuse the
	 * alपढ़ोy taken reference क्रम bound connectors
	 */
	क्रम (ro = 0; ro < set->num_connectors; ro++) अणु
		अगर (set->connectors[ro]->encoder)
			जारी;
		drm_connector_get(set->connectors[ro]);
	पूर्ण

	/* a) traverse passed in connector list and get encoders क्रम them */
	count = 0;
	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
		स्थिर काष्ठा drm_connector_helper_funcs *connector_funcs =
			connector->helper_निजी;
		new_encoder = connector->encoder;
		क्रम (ro = 0; ro < set->num_connectors; ro++) अणु
			अगर (set->connectors[ro] == connector) अणु
				अगर (connector_funcs->best_encoder)
					new_encoder = connector_funcs->best_encoder(connector);
				अन्यथा
					new_encoder = drm_connector_get_single_encoder(connector);

				/* अगर we can't get an encoder क्रम a connector
				   we are setting now - then fail */
				अगर (new_encoder == शून्य)
					/* करोn't अवरोध so fail path works correct */
					fail = 1;

				अगर (connector->dpms != DRM_MODE_DPMS_ON) अणु
					DRM_DEBUG_KMS("connector dpms not on, full mode switch\n");
					mode_changed = true;
				पूर्ण

				अवरोध;
			पूर्ण
		पूर्ण

		अगर (new_encoder != connector->encoder) अणु
			DRM_DEBUG_KMS("encoder changed, full mode switch\n");
			mode_changed = true;
			/* If the encoder is reused क्रम another connector, then
			 * the appropriate crtc will be set later.
			 */
			अगर (connector->encoder)
				connector->encoder->crtc = शून्य;
			connector->encoder = new_encoder;
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	अगर (fail) अणु
		ret = -EINVAL;
		जाओ fail;
	पूर्ण

	count = 0;
	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
		अगर (!connector->encoder)
			जारी;

		अगर (connector->encoder->crtc == set->crtc)
			new_crtc = शून्य;
		अन्यथा
			new_crtc = connector->encoder->crtc;

		क्रम (ro = 0; ro < set->num_connectors; ro++) अणु
			अगर (set->connectors[ro] == connector)
				new_crtc = set->crtc;
		पूर्ण

		/* Make sure the new CRTC will work with the encoder */
		अगर (new_crtc &&
		    !drm_encoder_crtc_ok(connector->encoder, new_crtc)) अणु
			ret = -EINVAL;
			drm_connector_list_iter_end(&conn_iter);
			जाओ fail;
		पूर्ण
		अगर (new_crtc != connector->encoder->crtc) अणु
			DRM_DEBUG_KMS("crtc changed, full mode switch\n");
			mode_changed = true;
			connector->encoder->crtc = new_crtc;
		पूर्ण
		अगर (new_crtc) अणु
			DRM_DEBUG_KMS("[CONNECTOR:%d:%s] to [CRTC:%d:%s]\n",
				      connector->base.id, connector->name,
				      new_crtc->base.id, new_crtc->name);
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("[CONNECTOR:%d:%s] to [NOCRTC]\n",
				      connector->base.id, connector->name);
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	/* mode_set_base is not a required function */
	अगर (fb_changed && !crtc_funcs->mode_set_base)
		mode_changed = true;

	अगर (mode_changed) अणु
		अगर (drm_helper_crtc_in_use(set->crtc)) अणु
			DRM_DEBUG_KMS("attempting to set mode from"
					" userspace\n");
			drm_mode_debug_prपूर्णांकmodeline(set->mode);
			set->crtc->primary->fb = set->fb;
			अगर (!drm_crtc_helper_set_mode(set->crtc, set->mode,
						      set->x, set->y,
						      save_set.fb)) अणु
				DRM_ERROR("failed to set mode on [CRTC:%d:%s]\n",
					  set->crtc->base.id, set->crtc->name);
				set->crtc->primary->fb = save_set.fb;
				ret = -EINVAL;
				जाओ fail;
			पूर्ण
			DRM_DEBUG_KMS("Setting connector DPMS state to on\n");
			क्रम (i = 0; i < set->num_connectors; i++) अणु
				DRM_DEBUG_KMS("\t[CONNECTOR:%d:%s] set DPMS on\n", set->connectors[i]->base.id,
					      set->connectors[i]->name);
				set->connectors[i]->funcs->dpms(set->connectors[i], DRM_MODE_DPMS_ON);
			पूर्ण
		पूर्ण
		__drm_helper_disable_unused_functions(dev);
	पूर्ण अन्यथा अगर (fb_changed) अणु
		set->crtc->x = set->x;
		set->crtc->y = set->y;
		set->crtc->primary->fb = set->fb;
		ret = crtc_funcs->mode_set_base(set->crtc,
						set->x, set->y, save_set.fb);
		अगर (ret != 0) अणु
			set->crtc->x = save_set.x;
			set->crtc->y = save_set.y;
			set->crtc->primary->fb = save_set.fb;
			जाओ fail;
		पूर्ण
	पूर्ण

	kमुक्त(save_connector_encoders);
	kमुक्त(save_encoder_crtcs);
	वापस 0;

fail:
	/* Restore all previous data. */
	count = 0;
	drm_क्रम_each_encoder(encoder, dev) अणु
		encoder->crtc = save_encoder_crtcs[count++];
	पूर्ण

	count = 0;
	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter)
		connector->encoder = save_connector_encoders[count++];
	drm_connector_list_iter_end(&conn_iter);

	/* after fail drop reference on all unbound connectors in set, let
	 * bound connectors keep their reference
	 */
	क्रम (ro = 0; ro < set->num_connectors; ro++) अणु
		अगर (set->connectors[ro]->encoder)
			जारी;
		drm_connector_put(set->connectors[ro]);
	पूर्ण

	/* Try to restore the config */
	अगर (mode_changed &&
	    !drm_crtc_helper_set_mode(save_set.crtc, save_set.mode, save_set.x,
				      save_set.y, save_set.fb))
		DRM_ERROR("failed to restore config after modeset failure\n");

	kमुक्त(save_connector_encoders);
	kमुक्त(save_encoder_crtcs);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_crtc_helper_set_config);

अटल पूर्णांक drm_helper_choose_encoder_dpms(काष्ठा drm_encoder *encoder)
अणु
	पूर्णांक dpms = DRM_MODE_DPMS_OFF;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;
	काष्ठा drm_device *dev = encoder->dev;

	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter)
		अगर (connector->encoder == encoder)
			अगर (connector->dpms < dpms)
				dpms = connector->dpms;
	drm_connector_list_iter_end(&conn_iter);

	वापस dpms;
पूर्ण

/* Helper which handles bridge ordering around encoder dpms */
अटल व्योम drm_helper_encoder_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	स्थिर काष्ठा drm_encoder_helper_funcs *encoder_funcs;

	encoder_funcs = encoder->helper_निजी;
	अगर (!encoder_funcs)
		वापस;

	अगर (encoder_funcs->dpms)
		encoder_funcs->dpms(encoder, mode);
पूर्ण

अटल पूर्णांक drm_helper_choose_crtc_dpms(काष्ठा drm_crtc *crtc)
अणु
	पूर्णांक dpms = DRM_MODE_DPMS_OFF;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;
	काष्ठा drm_device *dev = crtc->dev;

	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter)
		अगर (connector->encoder && connector->encoder->crtc == crtc)
			अगर (connector->dpms < dpms)
				dpms = connector->dpms;
	drm_connector_list_iter_end(&conn_iter);

	वापस dpms;
पूर्ण

/**
 * drm_helper_connector_dpms() - connector dpms helper implementation
 * @connector: affected connector
 * @mode: DPMS mode
 *
 * The drm_helper_connector_dpms() helper function implements the
 * &drm_connector_funcs.dpms callback क्रम drivers using the legacy CRTC
 * helpers.
 *
 * This is the मुख्य helper function provided by the CRTC helper framework क्रम
 * implementing the DPMS connector attribute. It computes the new desired DPMS
 * state क्रम all encoders and CRTCs in the output mesh and calls the
 * &drm_crtc_helper_funcs.dpms and &drm_encoder_helper_funcs.dpms callbacks
 * provided by the driver.
 *
 * This function is deprecated.  New drivers must implement atomic modeset
 * support, where DPMS is handled in the DRM core.
 *
 * Returns:
 * Always वापसs 0.
 */
पूर्णांक drm_helper_connector_dpms(काष्ठा drm_connector *connector, पूर्णांक mode)
अणु
	काष्ठा drm_encoder *encoder = connector->encoder;
	काष्ठा drm_crtc *crtc = encoder ? encoder->crtc : शून्य;
	पूर्णांक old_dpms, encoder_dpms = DRM_MODE_DPMS_OFF;

	WARN_ON(drm_drv_uses_atomic_modeset(connector->dev));

	अगर (mode == connector->dpms)
		वापस 0;

	old_dpms = connector->dpms;
	connector->dpms = mode;

	अगर (encoder)
		encoder_dpms = drm_helper_choose_encoder_dpms(encoder);

	/* from off to on, करो crtc then encoder */
	अगर (mode < old_dpms) अणु
		अगर (crtc) अणु
			स्थिर काष्ठा drm_crtc_helper_funcs *crtc_funcs = crtc->helper_निजी;

			अगर (crtc_funcs->dpms)
				(*crtc_funcs->dpms) (crtc,
						     drm_helper_choose_crtc_dpms(crtc));
		पूर्ण
		अगर (encoder)
			drm_helper_encoder_dpms(encoder, encoder_dpms);
	पूर्ण

	/* from on to off, करो encoder then crtc */
	अगर (mode > old_dpms) अणु
		अगर (encoder)
			drm_helper_encoder_dpms(encoder, encoder_dpms);
		अगर (crtc) अणु
			स्थिर काष्ठा drm_crtc_helper_funcs *crtc_funcs = crtc->helper_निजी;

			अगर (crtc_funcs->dpms)
				(*crtc_funcs->dpms) (crtc,
						     drm_helper_choose_crtc_dpms(crtc));
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_helper_connector_dpms);

/**
 * drm_helper_resume_क्रमce_mode - क्रमce-restore mode setting configuration
 * @dev: drm_device which should be restored
 *
 * Drivers which use the mode setting helpers can use this function to
 * क्रमce-restore the mode setting configuration e.g. on resume or when something
 * अन्यथा might have trampled over the hw state (like some overzealous old BIOSen
 * tended to करो).
 *
 * This helper करोesn't provide a error वापस value since restoring the old
 * config should never fail due to resource allocation issues since the driver
 * has successfully set the restored configuration alपढ़ोy. Hence this should
 * boil करोwn to the equivalent of a few dpms on calls, which also करोn't provide
 * an error code.
 *
 * Drivers where simply restoring an old configuration again might fail (e.g.
 * due to slight dअगरferences in allocating shared resources when the
 * configuration is restored in a dअगरferent order than when userspace set it up)
 * need to use their own restore logic.
 *
 * This function is deprecated. New drivers should implement atomic mode-
 * setting and use the atomic suspend/resume helpers.
 *
 * See also:
 * drm_atomic_helper_suspend(), drm_atomic_helper_resume()
 */
व्योम drm_helper_resume_क्रमce_mode(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_encoder *encoder;
	स्थिर काष्ठा drm_crtc_helper_funcs *crtc_funcs;
	पूर्णांक encoder_dpms;
	bool ret;

	WARN_ON(drm_drv_uses_atomic_modeset(dev));

	drm_modeset_lock_all(dev);
	drm_क्रम_each_crtc(crtc, dev) अणु

		अगर (!crtc->enabled)
			जारी;

		ret = drm_crtc_helper_set_mode(crtc, &crtc->mode,
					       crtc->x, crtc->y, crtc->primary->fb);

		/* Restoring the old config should never fail! */
		अगर (ret == false)
			DRM_ERROR("failed to set mode on crtc %p\n", crtc);

		/* Turn off outमाला_दो that were alपढ़ोy घातered off */
		अगर (drm_helper_choose_crtc_dpms(crtc)) अणु
			drm_क्रम_each_encoder(encoder, dev) अणु

				अगर(encoder->crtc != crtc)
					जारी;

				encoder_dpms = drm_helper_choose_encoder_dpms(
							encoder);

				drm_helper_encoder_dpms(encoder, encoder_dpms);
			पूर्ण

			crtc_funcs = crtc->helper_निजी;
			अगर (crtc_funcs->dpms)
				(*crtc_funcs->dpms) (crtc,
						     drm_helper_choose_crtc_dpms(crtc));
		पूर्ण
	पूर्ण

	/* disable the unused connectors जबतक restoring the modesetting */
	__drm_helper_disable_unused_functions(dev);
	drm_modeset_unlock_all(dev);
पूर्ण
EXPORT_SYMBOL(drm_helper_resume_क्रमce_mode);

/**
 * drm_helper_क्रमce_disable_all - Forcibly turn off all enabled CRTCs
 * @dev: DRM device whose CRTCs to turn off
 *
 * Drivers may want to call this on unload to ensure that all displays are
 * unlit and the GPU is in a consistent, low घातer state. Takes modeset locks.
 *
 * Note: This should only be used by non-atomic legacy drivers. For an atomic
 * version look at drm_atomic_helper_shutकरोwn().
 *
 * Returns:
 * Zero on success, error code on failure.
 */
पूर्णांक drm_helper_क्रमce_disable_all(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_crtc *crtc;
	पूर्णांक ret = 0;

	drm_modeset_lock_all(dev);
	drm_क्रम_each_crtc(crtc, dev)
		अगर (crtc->enabled) अणु
			काष्ठा drm_mode_set set = अणु
				.crtc = crtc,
			पूर्ण;

			ret = drm_mode_set_config_पूर्णांकernal(&set);
			अगर (ret)
				जाओ out;
		पूर्ण
out:
	drm_modeset_unlock_all(dev);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_helper_क्रमce_disable_all);
