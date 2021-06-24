<शैली गुरु>
/*
 * Copyright (c) 2016 Intel Corporation
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
 */

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_modeset_helper.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>

/**
 * DOC: aux kms helpers
 *
 * This helper library contains various one-off functions which करोn't really fit
 * anywhere अन्यथा in the DRM modeset helper library.
 */

/**
 * drm_helper_move_panel_connectors_to_head() - move panels to the front in the
 * 						connector list
 * @dev: drm device to operate on
 *
 * Some userspace presumes that the first connected connector is the मुख्य
 * display, where it's supposed to display e.g. the login screen. For
 * laptops, this should be the मुख्य panel. Use this function to sort all
 * (eDP/LVDS/DSI) panels to the front of the connector list, instead of
 * painstakingly trying to initialize them in the right order.
 */
व्योम drm_helper_move_panel_connectors_to_head(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_connector *connector, *पंचांगp;
	काष्ठा list_head panel_list;

	INIT_LIST_HEAD(&panel_list);

	spin_lock_irq(&dev->mode_config.connector_list_lock);
	list_क्रम_each_entry_safe(connector, पंचांगp,
				 &dev->mode_config.connector_list, head) अणु
		अगर (connector->connector_type == DRM_MODE_CONNECTOR_LVDS ||
		    connector->connector_type == DRM_MODE_CONNECTOR_eDP ||
		    connector->connector_type == DRM_MODE_CONNECTOR_DSI)
			list_move_tail(&connector->head, &panel_list);
	पूर्ण

	list_splice(&panel_list, &dev->mode_config.connector_list);
	spin_unlock_irq(&dev->mode_config.connector_list_lock);
पूर्ण
EXPORT_SYMBOL(drm_helper_move_panel_connectors_to_head);

/**
 * drm_helper_mode_fill_fb_काष्ठा - fill out framebuffer metadata
 * @dev: DRM device
 * @fb: drm_framebuffer object to fill out
 * @mode_cmd: metadata from the userspace fb creation request
 *
 * This helper can be used in a drivers fb_create callback to pre-fill the fb's
 * metadata fields.
 */
व्योम drm_helper_mode_fill_fb_काष्ठा(काष्ठा drm_device *dev,
				    काष्ठा drm_framebuffer *fb,
				    स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	पूर्णांक i;

	fb->dev = dev;
	fb->क्रमmat = drm_get_क्रमmat_info(dev, mode_cmd);
	fb->width = mode_cmd->width;
	fb->height = mode_cmd->height;
	क्रम (i = 0; i < 4; i++) अणु
		fb->pitches[i] = mode_cmd->pitches[i];
		fb->offsets[i] = mode_cmd->offsets[i];
	पूर्ण
	fb->modअगरier = mode_cmd->modअगरier[0];
	fb->flags = mode_cmd->flags;
पूर्ण
EXPORT_SYMBOL(drm_helper_mode_fill_fb_काष्ठा);

/*
 * This is the minimal list of क्रमmats that seem to be safe क्रम modeset use
 * with all current DRM drivers.  Most hardware can actually support more
 * क्रमmats than this and drivers may specअगरy a more accurate list when
 * creating the primary plane.  However drivers that still call
 * drm_plane_init() will use this minimal क्रमmat list as the शेष.
 */
अटल स्थिर uपूर्णांक32_t safe_modeset_क्रमmats[] = अणु
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_ARGB8888,
पूर्ण;

अटल काष्ठा drm_plane *create_primary_plane(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_plane *primary;
	पूर्णांक ret;

	primary = kzalloc(माप(*primary), GFP_KERNEL);
	अगर (primary == शून्य) अणु
		DRM_DEBUG_KMS("Failed to allocate primary plane\n");
		वापस शून्य;
	पूर्ण

	/*
	 * Remove the क्रमmat_शेष field from drm_plane when dropping
	 * this helper.
	 */
	primary->क्रमmat_शेष = true;

	/* possible_crtc's will be filled in later by crtc_init */
	ret = drm_universal_plane_init(dev, primary, 0,
				       &drm_primary_helper_funcs,
				       safe_modeset_क्रमmats,
				       ARRAY_SIZE(safe_modeset_क्रमmats),
				       शून्य,
				       DRM_PLANE_TYPE_PRIMARY, शून्य);
	अगर (ret) अणु
		kमुक्त(primary);
		primary = शून्य;
	पूर्ण

	वापस primary;
पूर्ण

/**
 * drm_crtc_init - Legacy CRTC initialization function
 * @dev: DRM device
 * @crtc: CRTC object to init
 * @funcs: callbacks क्रम the new CRTC
 *
 * Initialize a CRTC object with a शेष helper-provided primary plane and no
 * cursor plane.
 *
 * Note that we make some assumptions about hardware limitations that may not be
 * true क्रम all hardware:
 *
 * 1. Primary plane cannot be repositioned.
 * 2. Primary plane cannot be scaled.
 * 3. Primary plane must cover the entire CRTC.
 * 4. Subpixel positioning is not supported.
 * 5. The primary plane must always be on अगर the CRTC is enabled.
 *
 * This is purely a backwards compatibility helper क्रम old drivers. Drivers
 * should instead implement their own primary plane. Atomic drivers must करो so.
 * Drivers with the above hardware restriction can look पूर्णांकo using &काष्ठा
 * drm_simple_display_pipe, which encapsulates the above limitations पूर्णांकo a nice
 * पूर्णांकerface.
 *
 * Returns:
 * Zero on success, error code on failure.
 */
पूर्णांक drm_crtc_init(काष्ठा drm_device *dev, काष्ठा drm_crtc *crtc,
		  स्थिर काष्ठा drm_crtc_funcs *funcs)
अणु
	काष्ठा drm_plane *primary;

	primary = create_primary_plane(dev);
	वापस drm_crtc_init_with_planes(dev, crtc, primary, शून्य, funcs,
					 शून्य);
पूर्ण
EXPORT_SYMBOL(drm_crtc_init);

/**
 * drm_mode_config_helper_suspend - Modeset suspend helper
 * @dev: DRM device
 *
 * This helper function takes care of suspending the modeset side. It disables
 * output polling अगर initialized, suspends fbdev अगर used and finally calls
 * drm_atomic_helper_suspend().
 * If suspending fails, fbdev and polling is re-enabled.
 *
 * Returns:
 * Zero on success, negative error code on error.
 *
 * See also:
 * drm_kms_helper_poll_disable() and drm_fb_helper_set_suspend_unlocked().
 */
पूर्णांक drm_mode_config_helper_suspend(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_atomic_state *state;

	अगर (!dev)
		वापस 0;

	drm_kms_helper_poll_disable(dev);
	drm_fb_helper_set_suspend_unlocked(dev->fb_helper, 1);
	state = drm_atomic_helper_suspend(dev);
	अगर (IS_ERR(state)) अणु
		drm_fb_helper_set_suspend_unlocked(dev->fb_helper, 0);
		drm_kms_helper_poll_enable(dev);
		वापस PTR_ERR(state);
	पूर्ण

	dev->mode_config.suspend_state = state;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_mode_config_helper_suspend);

/**
 * drm_mode_config_helper_resume - Modeset resume helper
 * @dev: DRM device
 *
 * This helper function takes care of resuming the modeset side. It calls
 * drm_atomic_helper_resume(), resumes fbdev अगर used and enables output polling
 * अगर initiaized.
 *
 * Returns:
 * Zero on success, negative error code on error.
 *
 * See also:
 * drm_fb_helper_set_suspend_unlocked() and drm_kms_helper_poll_enable().
 */
पूर्णांक drm_mode_config_helper_resume(काष्ठा drm_device *dev)
अणु
	पूर्णांक ret;

	अगर (!dev)
		वापस 0;

	अगर (WARN_ON(!dev->mode_config.suspend_state))
		वापस -EINVAL;

	ret = drm_atomic_helper_resume(dev, dev->mode_config.suspend_state);
	अगर (ret)
		DRM_ERROR("Failed to resume (%d)\n", ret);
	dev->mode_config.suspend_state = शून्य;

	drm_fb_helper_set_suspend_unlocked(dev->fb_helper, 0);
	drm_kms_helper_poll_enable(dev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_mode_config_helper_resume);
