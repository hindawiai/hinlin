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

#अगर_अघोषित __DRM_PLANE_H__
#घोषणा __DRM_PLANE_H__

#समावेश <linux/list.h>
#समावेश <linux/प्रकार.स>
#समावेश <drm/drm_mode_object.h>
#समावेश <drm/drm_color_mgmt.h>
#समावेश <drm/drm_rect.h>
#समावेश <drm/drm_modeset_lock.h>
#समावेश <drm/drm_util.h>

काष्ठा drm_crtc;
काष्ठा drm_prपूर्णांकer;
काष्ठा drm_modeset_acquire_ctx;

क्रमागत drm_scaling_filter अणु
	DRM_SCALING_FILTER_DEFAULT,
	DRM_SCALING_FILTER_NEAREST_NEIGHBOR,
पूर्ण;

/**
 * काष्ठा drm_plane_state - mutable plane state
 *
 * Please not that the destination coordinates @crtc_x, @crtc_y, @crtc_h and
 * @crtc_w and the source coordinates @src_x, @src_y, @src_h and @src_w are the
 * raw coordinates provided by userspace. Drivers should use
 * drm_atomic_helper_check_plane_state() and only use the derived rectangles in
 * @src and @dst to program the hardware.
 */
काष्ठा drm_plane_state अणु
	/** @plane: backpoपूर्णांकer to the plane */
	काष्ठा drm_plane *plane;

	/**
	 * @crtc:
	 *
	 * Currently bound CRTC, शून्य अगर disabled. Do not this ग_लिखो directly,
	 * use drm_atomic_set_crtc_क्रम_plane()
	 */
	काष्ठा drm_crtc *crtc;

	/**
	 * @fb:
	 *
	 * Currently bound framebuffer. Do not ग_लिखो this directly, use
	 * drm_atomic_set_fb_क्रम_plane()
	 */
	काष्ठा drm_framebuffer *fb;

	/**
	 * @fence:
	 *
	 * Optional fence to रुको क्रम beक्रमe scanning out @fb. The core atomic
	 * code will set this when userspace is using explicit fencing. Do not
	 * ग_लिखो this field directly क्रम a driver's implicit fence, use
	 * drm_atomic_set_fence_क्रम_plane() to ensure that an explicit fence is
	 * preserved.
	 *
	 * Drivers should store any implicit fence in this from their
	 * &drm_plane_helper_funcs.prepare_fb callback. See drm_gem_plane_helper_prepare_fb()
	 * and drm_gem_simple_display_pipe_prepare_fb() क्रम suitable helpers.
	 */
	काष्ठा dma_fence *fence;

	/**
	 * @crtc_x:
	 *
	 * Left position of visible portion of plane on crtc, चिन्हित dest
	 * location allows it to be partially off screen.
	 */

	पूर्णांक32_t crtc_x;
	/**
	 * @crtc_y:
	 *
	 * Upper position of visible portion of plane on crtc, चिन्हित dest
	 * location allows it to be partially off screen.
	 */
	पूर्णांक32_t crtc_y;

	/** @crtc_w: width of visible portion of plane on crtc */
	/** @crtc_h: height of visible portion of plane on crtc */
	uपूर्णांक32_t crtc_w, crtc_h;

	/**
	 * @src_x: left position of visible portion of plane within plane (in
	 * 16.16 fixed poपूर्णांक).
	 */
	uपूर्णांक32_t src_x;
	/**
	 * @src_y: upper position of visible portion of plane within plane (in
	 * 16.16 fixed poपूर्णांक).
	 */
	uपूर्णांक32_t src_y;
	/** @src_w: width of visible portion of plane (in 16.16) */
	/** @src_h: height of visible portion of plane (in 16.16) */
	uपूर्णांक32_t src_h, src_w;

	/**
	 * @alpha:
	 * Opacity of the plane with 0 as completely transparent and 0xffff as
	 * completely opaque. See drm_plane_create_alpha_property() क्रम more
	 * details.
	 */
	u16 alpha;

	/**
	 * @pixel_blend_mode:
	 * The alpha blending equation selection, describing how the pixels from
	 * the current plane are composited with the background. Value can be
	 * one of DRM_MODE_BLEND_*
	 */
	uपूर्णांक16_t pixel_blend_mode;

	/**
	 * @rotation:
	 * Rotation of the plane. See drm_plane_create_rotation_property() क्रम
	 * more details.
	 */
	अचिन्हित पूर्णांक rotation;

	/**
	 * @zpos:
	 * Priority of the given plane on crtc (optional).
	 *
	 * User-space may set mutable zpos properties so that multiple active
	 * planes on the same CRTC have identical zpos values. This is a
	 * user-space bug, but drivers can solve the conflict by comparing the
	 * plane object IDs; the plane with a higher ID is stacked on top of a
	 * plane with a lower ID.
	 *
	 * See drm_plane_create_zpos_property() and
	 * drm_plane_create_zpos_immutable_property() क्रम more details.
	 */
	अचिन्हित पूर्णांक zpos;

	/**
	 * @normalized_zpos:
	 * Normalized value of zpos: unique, range from 0 to N-1 where N is the
	 * number of active planes क्रम given crtc. Note that the driver must set
	 * &drm_mode_config.normalize_zpos or call drm_atomic_normalize_zpos() to
	 * update this beक्रमe it can be trusted.
	 */
	अचिन्हित पूर्णांक normalized_zpos;

	/**
	 * @color_encoding:
	 *
	 * Color encoding क्रम non RGB क्रमmats
	 */
	क्रमागत drm_color_encoding color_encoding;

	/**
	 * @color_range:
	 *
	 * Color range क्रम non RGB क्रमmats
	 */
	क्रमागत drm_color_range color_range;

	/**
	 * @fb_damage_clips:
	 *
	 * Blob representing damage (area in plane framebuffer that changed
	 * since last plane update) as an array of &drm_mode_rect in framebuffer
	 * coodinates of the attached framebuffer. Note that unlike plane src,
	 * damage clips are not in 16.16 fixed poपूर्णांक.
	 */
	काष्ठा drm_property_blob *fb_damage_clips;

	/**
	 * @src:
	 *
	 * source coordinates of the plane (in 16.16).
	 *
	 * When using drm_atomic_helper_check_plane_state(),
	 * the coordinates are clipped, but the driver may choose
	 * to use unclipped coordinates instead when the hardware
	 * perक्रमms the clipping स्वतःmatically.
	 */
	/**
	 * @dst:
	 *
	 * clipped destination coordinates of the plane.
	 *
	 * When using drm_atomic_helper_check_plane_state(),
	 * the coordinates are clipped, but the driver may choose
	 * to use unclipped coordinates instead when the hardware
	 * perक्रमms the clipping स्वतःmatically.
	 */
	काष्ठा drm_rect src, dst;

	/**
	 * @visible:
	 *
	 * Visibility of the plane. This can be false even अगर fb!=शून्य and
	 * crtc!=शून्य, due to clipping.
	 */
	bool visible;

	/**
	 * @scaling_filter:
	 *
	 * Scaling filter to be applied
	 */
	क्रमागत drm_scaling_filter scaling_filter;

	/**
	 * @commit: Tracks the pending commit to prevent use-after-मुक्त conditions,
	 * and क्रम async plane updates.
	 *
	 * May be शून्य.
	 */
	काष्ठा drm_crtc_commit *commit;

	/** @state: backpoपूर्णांकer to global drm_atomic_state */
	काष्ठा drm_atomic_state *state;
पूर्ण;

अटल अंतरभूत काष्ठा drm_rect
drm_plane_state_src(स्थिर काष्ठा drm_plane_state *state)
अणु
	काष्ठा drm_rect src = अणु
		.x1 = state->src_x,
		.y1 = state->src_y,
		.x2 = state->src_x + state->src_w,
		.y2 = state->src_y + state->src_h,
	पूर्ण;
	वापस src;
पूर्ण

अटल अंतरभूत काष्ठा drm_rect
drm_plane_state_dest(स्थिर काष्ठा drm_plane_state *state)
अणु
	काष्ठा drm_rect dest = अणु
		.x1 = state->crtc_x,
		.y1 = state->crtc_y,
		.x2 = state->crtc_x + state->crtc_w,
		.y2 = state->crtc_y + state->crtc_h,
	पूर्ण;
	वापस dest;
पूर्ण

/**
 * काष्ठा drm_plane_funcs - driver plane control functions
 */
काष्ठा drm_plane_funcs अणु
	/**
	 * @update_plane:
	 *
	 * This is the legacy entry poपूर्णांक to enable and configure the plane क्रम
	 * the given CRTC and framebuffer. It is never called to disable the
	 * plane, i.e. the passed-in crtc and fb paramters are never शून्य.
	 *
	 * The source rectangle in frame buffer memory coordinates is given by
	 * the src_x, src_y, src_w and src_h parameters (as 16.16 fixed poपूर्णांक
	 * values). Devices that करोn't support subpixel plane coordinates can
	 * ignore the fractional part.
	 *
	 * The destination rectangle in CRTC coordinates is given by the
	 * crtc_x, crtc_y, crtc_w and crtc_h parameters (as पूर्णांकeger values).
	 * Devices scale the source rectangle to the destination rectangle. If
	 * scaling is not supported, and the source rectangle size करोesn't match
	 * the destination rectangle size, the driver must वापस a
	 * -<errorname>EINVAL</errorname> error.
	 *
	 * Drivers implementing atomic modeset should use
	 * drm_atomic_helper_update_plane() to implement this hook.
	 *
	 * RETURNS:
	 *
	 * 0 on success or a negative error code on failure.
	 */
	पूर्णांक (*update_plane)(काष्ठा drm_plane *plane,
			    काष्ठा drm_crtc *crtc, काष्ठा drm_framebuffer *fb,
			    पूर्णांक crtc_x, पूर्णांक crtc_y,
			    अचिन्हित पूर्णांक crtc_w, अचिन्हित पूर्णांक crtc_h,
			    uपूर्णांक32_t src_x, uपूर्णांक32_t src_y,
			    uपूर्णांक32_t src_w, uपूर्णांक32_t src_h,
			    काष्ठा drm_modeset_acquire_ctx *ctx);

	/**
	 * @disable_plane:
	 *
	 * This is the legacy entry poपूर्णांक to disable the plane. The DRM core
	 * calls this method in response to a DRM_IOCTL_MODE_SETPLANE IOCTL call
	 * with the frame buffer ID set to 0.  Disabled planes must not be
	 * processed by the CRTC.
	 *
	 * Drivers implementing atomic modeset should use
	 * drm_atomic_helper_disable_plane() to implement this hook.
	 *
	 * RETURNS:
	 *
	 * 0 on success or a negative error code on failure.
	 */
	पूर्णांक (*disable_plane)(काष्ठा drm_plane *plane,
			     काष्ठा drm_modeset_acquire_ctx *ctx);

	/**
	 * @destroy:
	 *
	 * Clean up plane resources. This is only called at driver unload समय
	 * through drm_mode_config_cleanup() since a plane cannot be hotplugged
	 * in DRM.
	 */
	व्योम (*destroy)(काष्ठा drm_plane *plane);

	/**
	 * @reset:
	 *
	 * Reset plane hardware and software state to off. This function isn't
	 * called by the core directly, only through drm_mode_config_reset().
	 * It's not a helper hook only क्रम historical reasons.
	 *
	 * Atomic drivers can use drm_atomic_helper_plane_reset() to reset
	 * atomic state using this hook.
	 */
	व्योम (*reset)(काष्ठा drm_plane *plane);

	/**
	 * @set_property:
	 *
	 * This is the legacy entry poपूर्णांक to update a property attached to the
	 * plane.
	 *
	 * This callback is optional अगर the driver करोes not support any legacy
	 * driver-निजी properties. For atomic drivers it is not used because
	 * property handling is करोne entirely in the DRM core.
	 *
	 * RETURNS:
	 *
	 * 0 on success or a negative error code on failure.
	 */
	पूर्णांक (*set_property)(काष्ठा drm_plane *plane,
			    काष्ठा drm_property *property, uपूर्णांक64_t val);

	/**
	 * @atomic_duplicate_state:
	 *
	 * Duplicate the current atomic state क्रम this plane and वापस it.
	 * The core and helpers guarantee that any atomic state duplicated with
	 * this hook and still owned by the caller (i.e. not transferred to the
	 * driver by calling &drm_mode_config_funcs.atomic_commit) will be
	 * cleaned up by calling the @atomic_destroy_state hook in this
	 * काष्ठाure.
	 *
	 * This callback is mandatory क्रम atomic drivers.
	 *
	 * Atomic drivers which करोn't subclass &काष्ठा drm_plane_state should use
	 * drm_atomic_helper_plane_duplicate_state(). Drivers that subclass the
	 * state काष्ठाure to extend it with driver-निजी state should use
	 * __drm_atomic_helper_plane_duplicate_state() to make sure shared state is
	 * duplicated in a consistent fashion across drivers.
	 *
	 * It is an error to call this hook beक्रमe &drm_plane.state has been
	 * initialized correctly.
	 *
	 * NOTE:
	 *
	 * If the duplicate state references refcounted resources this hook must
	 * acquire a reference क्रम each of them. The driver must release these
	 * references again in @atomic_destroy_state.
	 *
	 * RETURNS:
	 *
	 * Duplicated atomic state or शून्य when the allocation failed.
	 */
	काष्ठा drm_plane_state *(*atomic_duplicate_state)(काष्ठा drm_plane *plane);

	/**
	 * @atomic_destroy_state:
	 *
	 * Destroy a state duplicated with @atomic_duplicate_state and release
	 * or unreference all resources it references
	 *
	 * This callback is mandatory क्रम atomic drivers.
	 */
	व्योम (*atomic_destroy_state)(काष्ठा drm_plane *plane,
				     काष्ठा drm_plane_state *state);

	/**
	 * @atomic_set_property:
	 *
	 * Decode a driver-निजी property value and store the decoded value
	 * पूर्णांकo the passed-in state काष्ठाure. Since the atomic core decodes all
	 * standardized properties (even क्रम extensions beyond the core set of
	 * properties which might not be implemented by all drivers) this
	 * requires drivers to subclass the state काष्ठाure.
	 *
	 * Such driver-निजी properties should really only be implemented क्रम
	 * truly hardware/venकरोr specअगरic state. Instead it is preferred to
	 * standardize atomic extension and decode the properties used to expose
	 * such an extension in the core.
	 *
	 * Do not call this function directly, use
	 * drm_atomic_plane_set_property() instead.
	 *
	 * This callback is optional अगर the driver करोes not support any
	 * driver-निजी atomic properties.
	 *
	 * NOTE:
	 *
	 * This function is called in the state assembly phase of atomic
	 * modesets, which can be पातed क्रम any reason (including on
	 * userspace's request to just check whether a configuration would be
	 * possible). Drivers MUST NOT touch any persistent state (hardware or
	 * software) or data काष्ठाures except the passed in @state parameter.
	 *
	 * Also since userspace controls in which order properties are set this
	 * function must not करो any input validation (since the state update is
	 * incomplete and hence likely inconsistent). Instead any such input
	 * validation must be करोne in the various atomic_check callbacks.
	 *
	 * RETURNS:
	 *
	 * 0 अगर the property has been found, -EINVAL अगर the property isn't
	 * implemented by the driver (which shouldn't ever happen, the core only
	 * asks क्रम properties attached to this plane). No other validation is
	 * allowed by the driver. The core alपढ़ोy checks that the property
	 * value is within the range (पूर्णांकeger, valid क्रमागत value, ...) the driver
	 * set when रेजिस्टरing the property.
	 */
	पूर्णांक (*atomic_set_property)(काष्ठा drm_plane *plane,
				   काष्ठा drm_plane_state *state,
				   काष्ठा drm_property *property,
				   uपूर्णांक64_t val);

	/**
	 * @atomic_get_property:
	 *
	 * Reads out the decoded driver-निजी property. This is used to
	 * implement the GETPLANE IOCTL.
	 *
	 * Do not call this function directly, use
	 * drm_atomic_plane_get_property() instead.
	 *
	 * This callback is optional अगर the driver करोes not support any
	 * driver-निजी atomic properties.
	 *
	 * RETURNS:
	 *
	 * 0 on success, -EINVAL अगर the property isn't implemented by the
	 * driver (which should never happen, the core only asks क्रम
	 * properties attached to this plane).
	 */
	पूर्णांक (*atomic_get_property)(काष्ठा drm_plane *plane,
				   स्थिर काष्ठा drm_plane_state *state,
				   काष्ठा drm_property *property,
				   uपूर्णांक64_t *val);
	/**
	 * @late_रेजिस्टर:
	 *
	 * This optional hook can be used to रेजिस्टर additional userspace
	 * पूर्णांकerfaces attached to the plane like debugfs पूर्णांकerfaces.
	 * It is called late in the driver load sequence from drm_dev_रेजिस्टर().
	 * Everything added from this callback should be unरेजिस्टरed in
	 * the early_unरेजिस्टर callback.
	 *
	 * Returns:
	 *
	 * 0 on success, or a negative error code on failure.
	 */
	पूर्णांक (*late_रेजिस्टर)(काष्ठा drm_plane *plane);

	/**
	 * @early_unरेजिस्टर:
	 *
	 * This optional hook should be used to unरेजिस्टर the additional
	 * userspace पूर्णांकerfaces attached to the plane from
	 * @late_रेजिस्टर. It is called from drm_dev_unरेजिस्टर(),
	 * early in the driver unload sequence to disable userspace access
	 * beक्रमe data काष्ठाures are tornकरोwn.
	 */
	व्योम (*early_unरेजिस्टर)(काष्ठा drm_plane *plane);

	/**
	 * @atomic_prपूर्णांक_state:
	 *
	 * If driver subclasses &काष्ठा drm_plane_state, it should implement
	 * this optional hook क्रम prपूर्णांकing additional driver specअगरic state.
	 *
	 * Do not call this directly, use drm_atomic_plane_prपूर्णांक_state()
	 * instead.
	 */
	व्योम (*atomic_prपूर्णांक_state)(काष्ठा drm_prपूर्णांकer *p,
				   स्थिर काष्ठा drm_plane_state *state);

	/**
	 * @क्रमmat_mod_supported:
	 *
	 * This optional hook is used क्रम the DRM to determine अगर the given
	 * क्रमmat/modअगरier combination is valid क्रम the plane. This allows the
	 * DRM to generate the correct क्रमmat biपंचांगask (which क्रमmats apply to
	 * which modअगरier), and to valdiate modअगरiers at atomic_check समय.
	 *
	 * If not present, then any modअगरier in the plane's modअगरier
	 * list is allowed with any of the plane's क्रमmats.
	 *
	 * Returns:
	 *
	 * True अगर the given modअगरier is valid क्रम that क्रमmat on the plane.
	 * False otherwise.
	 */
	bool (*क्रमmat_mod_supported)(काष्ठा drm_plane *plane, uपूर्णांक32_t क्रमmat,
				     uपूर्णांक64_t modअगरier);
पूर्ण;

/**
 * क्रमागत drm_plane_type - uapi plane type क्रमागतeration
 *
 * For historical reasons not all planes are made the same. This क्रमागतeration is
 * used to tell the dअगरferent types of planes apart to implement the dअगरferent
 * uapi semantics क्रम them. For userspace which is universal plane aware and
 * which is using that atomic IOCTL there's no dअगरference between these planes
 * (beyong what the driver and hardware can support of course).
 *
 * For compatibility with legacy userspace, only overlay planes are made
 * available to userspace by शेष. Userspace clients may set the
 * &DRM_CLIENT_CAP_UNIVERSAL_PLANES client capability bit to indicate that they
 * wish to receive a universal plane list containing all plane types. See also
 * drm_क्रम_each_legacy_plane().
 *
 * In addition to setting each plane's type, drivers need to setup the
 * &drm_crtc.primary and optionally &drm_crtc.cursor poपूर्णांकers क्रम legacy
 * IOCTLs. See drm_crtc_init_with_planes().
 *
 * WARNING: The values of this क्रमागत is UABI since they're exposed in the "type"
 * property.
 */
क्रमागत drm_plane_type अणु
	/**
	 * @DRM_PLANE_TYPE_OVERLAY:
	 *
	 * Overlay planes represent all non-primary, non-cursor planes. Some
	 * drivers refer to these types of planes as "sprites" पूर्णांकernally.
	 */
	DRM_PLANE_TYPE_OVERLAY,

	/**
	 * @DRM_PLANE_TYPE_PRIMARY:
	 *
	 * A primary plane attached to a CRTC is the most likely to be able to
	 * light up the CRTC when no scaling/cropping is used and the plane
	 * covers the whole CRTC.
	 */
	DRM_PLANE_TYPE_PRIMARY,

	/**
	 * @DRM_PLANE_TYPE_CURSOR:
	 *
	 * A cursor plane attached to a CRTC is more likely to be able to be
	 * enabled when no scaling/cropping is used and the framebuffer has the
	 * size indicated by &drm_mode_config.cursor_width and
	 * &drm_mode_config.cursor_height. Additionally, अगर the driver करोesn't
	 * support modअगरiers, the framebuffer should have a linear layout.
	 */
	DRM_PLANE_TYPE_CURSOR,
पूर्ण;


/**
 * काष्ठा drm_plane - central DRM plane control काष्ठाure
 *
 * Planes represent the scanout hardware of a display block. They receive their
 * input data from a &drm_framebuffer and feed it to a &drm_crtc. Planes control
 * the color conversion, see `Plane Composition Properties`_ क्रम more details,
 * and are also involved in the color conversion of input pixels, see `Color
 * Management Properties`_ क्रम details on that.
 */
काष्ठा drm_plane अणु
	/** @dev: DRM device this plane beदीर्घs to */
	काष्ठा drm_device *dev;

	/**
	 * @head:
	 *
	 * List of all planes on @dev, linked from &drm_mode_config.plane_list.
	 * Invariant over the lअगरeसमय of @dev and thereक्रमe करोes not need
	 * locking.
	 */
	काष्ठा list_head head;

	/** @name: human पढ़ोable name, can be overwritten by the driver */
	अक्षर *name;

	/**
	 * @mutex:
	 *
	 * Protects modeset plane state, together with the &drm_crtc.mutex of
	 * CRTC this plane is linked to (when active, getting activated or
	 * getting disabled).
	 *
	 * For atomic drivers specअगरically this protects @state.
	 */
	काष्ठा drm_modeset_lock mutex;

	/** @base: base mode object */
	काष्ठा drm_mode_object base;

	/**
	 * @possible_crtcs: pipes this plane can be bound to स्थिरructed from
	 * drm_crtc_mask()
	 */
	uपूर्णांक32_t possible_crtcs;
	/** @क्रमmat_types: array of क्रमmats supported by this plane */
	uपूर्णांक32_t *क्रमmat_types;
	/** @क्रमmat_count: Size of the array poपूर्णांकed at by @क्रमmat_types. */
	अचिन्हित पूर्णांक क्रमmat_count;
	/**
	 * @क्रमmat_शेष: driver hasn't supplied supported क्रमmats क्रम the
	 * plane. Used by the drm_plane_init compatibility wrapper only.
	 */
	bool क्रमmat_शेष;

	/** @modअगरiers: array of modअगरiers supported by this plane */
	uपूर्णांक64_t *modअगरiers;
	/** @modअगरier_count: Size of the array poपूर्णांकed at by @modअगरier_count. */
	अचिन्हित पूर्णांक modअगरier_count;

	/**
	 * @crtc:
	 *
	 * Currently bound CRTC, only meaningful क्रम non-atomic drivers. For
	 * atomic drivers this is क्रमced to be शून्य, atomic drivers should
	 * instead check &drm_plane_state.crtc.
	 */
	काष्ठा drm_crtc *crtc;

	/**
	 * @fb:
	 *
	 * Currently bound framebuffer, only meaningful क्रम non-atomic drivers.
	 * For atomic drivers this is क्रमced to be शून्य, atomic drivers should
	 * instead check &drm_plane_state.fb.
	 */
	काष्ठा drm_framebuffer *fb;

	/**
	 * @old_fb:
	 *
	 * Temporary tracking of the old fb जबतक a modeset is ongoing. Only
	 * used by non-atomic drivers, क्रमced to be शून्य क्रम atomic drivers.
	 */
	काष्ठा drm_framebuffer *old_fb;

	/** @funcs: plane control functions */
	स्थिर काष्ठा drm_plane_funcs *funcs;

	/** @properties: property tracking क्रम this plane */
	काष्ठा drm_object_properties properties;

	/** @type: Type of plane, see &क्रमागत drm_plane_type क्रम details. */
	क्रमागत drm_plane_type type;

	/**
	 * @index: Position inside the mode_config.list, can be used as an array
	 * index. It is invariant over the lअगरeसमय of the plane.
	 */
	अचिन्हित index;

	/** @helper_निजी: mid-layer निजी data */
	स्थिर काष्ठा drm_plane_helper_funcs *helper_निजी;

	/**
	 * @state:
	 *
	 * Current atomic state क्रम this plane.
	 *
	 * This is रक्षित by @mutex. Note that nonblocking atomic commits
	 * access the current plane state without taking locks. Either by going
	 * through the &काष्ठा drm_atomic_state poपूर्णांकers, see
	 * क्रम_each_oldnew_plane_in_state(), क्रम_each_old_plane_in_state() and
	 * क्रम_each_new_plane_in_state(). Or through careful ordering of atomic
	 * commit operations as implemented in the atomic helpers, see
	 * &काष्ठा drm_crtc_commit.
	 */
	काष्ठा drm_plane_state *state;

	/**
	 * @alpha_property:
	 * Optional alpha property क्रम this plane. See
	 * drm_plane_create_alpha_property().
	 */
	काष्ठा drm_property *alpha_property;
	/**
	 * @zpos_property:
	 * Optional zpos property क्रम this plane. See
	 * drm_plane_create_zpos_property().
	 */
	काष्ठा drm_property *zpos_property;
	/**
	 * @rotation_property:
	 * Optional rotation property क्रम this plane. See
	 * drm_plane_create_rotation_property().
	 */
	काष्ठा drm_property *rotation_property;
	/**
	 * @blend_mode_property:
	 * Optional "pixel blend mode" क्रमागत property क्रम this plane.
	 * Blend mode property represents the alpha blending equation selection,
	 * describing how the pixels from the current plane are composited with
	 * the background.
	 */
	काष्ठा drm_property *blend_mode_property;

	/**
	 * @color_encoding_property:
	 *
	 * Optional "COLOR_ENCODING" क्रमागत property क्रम specअगरying
	 * color encoding क्रम non RGB क्रमmats.
	 * See drm_plane_create_color_properties().
	 */
	काष्ठा drm_property *color_encoding_property;
	/**
	 * @color_range_property:
	 *
	 * Optional "COLOR_RANGE" क्रमागत property क्रम specअगरying
	 * color range क्रम non RGB क्रमmats.
	 * See drm_plane_create_color_properties().
	 */
	काष्ठा drm_property *color_range_property;

	/**
	 * @scaling_filter_property: property to apply a particular filter जबतक
	 * scaling.
	 */
	काष्ठा drm_property *scaling_filter_property;
पूर्ण;

#घोषणा obj_to_plane(x) container_of(x, काष्ठा drm_plane, base)

__म_लिखो(9, 10)
पूर्णांक drm_universal_plane_init(काष्ठा drm_device *dev,
			     काष्ठा drm_plane *plane,
			     uपूर्णांक32_t possible_crtcs,
			     स्थिर काष्ठा drm_plane_funcs *funcs,
			     स्थिर uपूर्णांक32_t *क्रमmats,
			     अचिन्हित पूर्णांक क्रमmat_count,
			     स्थिर uपूर्णांक64_t *क्रमmat_modअगरiers,
			     क्रमागत drm_plane_type type,
			     स्थिर अक्षर *name, ...);
पूर्णांक drm_plane_init(काष्ठा drm_device *dev,
		   काष्ठा drm_plane *plane,
		   uपूर्णांक32_t possible_crtcs,
		   स्थिर काष्ठा drm_plane_funcs *funcs,
		   स्थिर uपूर्णांक32_t *क्रमmats, अचिन्हित पूर्णांक क्रमmat_count,
		   bool is_primary);
व्योम drm_plane_cleanup(काष्ठा drm_plane *plane);

__म_लिखो(10, 11)
व्योम *__drmm_universal_plane_alloc(काष्ठा drm_device *dev,
				   माप_प्रकार size, माप_प्रकार offset,
				   uपूर्णांक32_t possible_crtcs,
				   स्थिर काष्ठा drm_plane_funcs *funcs,
				   स्थिर uपूर्णांक32_t *क्रमmats,
				   अचिन्हित पूर्णांक क्रमmat_count,
				   स्थिर uपूर्णांक64_t *क्रमmat_modअगरiers,
				   क्रमागत drm_plane_type plane_type,
				   स्थिर अक्षर *name, ...);

/**
 * drmm_universal_plane_alloc - Allocate and initialize an universal plane object
 * @dev: DRM device
 * @type: the type of the काष्ठा which contains काष्ठा &drm_plane
 * @member: the name of the &drm_plane within @type
 * @possible_crtcs: biपंचांगask of possible CRTCs
 * @funcs: callbacks क्रम the new plane
 * @क्रमmats: array of supported क्रमmats (DRM_FORMAT\_\*)
 * @क्रमmat_count: number of elements in @क्रमmats
 * @क्रमmat_modअगरiers: array of काष्ठा drm_क्रमmat modअगरiers terminated by
 *                    DRM_FORMAT_MOD_INVALID
 * @plane_type: type of plane (overlay, primary, cursor)
 * @name: म_लिखो style क्रमmat string क्रम the plane name, or शून्य क्रम शेष name
 *
 * Allocates and initializes a plane object of type @type. Cleanup is
 * स्वतःmatically handled through रेजिस्टरing drm_plane_cleanup() with
 * drmm_add_action().
 *
 * The @drm_plane_funcs.destroy hook must be शून्य.
 *
 * Returns:
 * Poपूर्णांकer to new plane, or ERR_PTR on failure.
 */
#घोषणा drmm_universal_plane_alloc(dev, type, member, possible_crtcs, funcs, क्रमmats, \
				   क्रमmat_count, क्रमmat_modअगरiers, plane_type, name, ...) \
	((type *)__drmm_universal_plane_alloc(dev, माप(type), \
					      दुरत्व(type, member), \
					      possible_crtcs, funcs, क्रमmats, \
					      क्रमmat_count, क्रमmat_modअगरiers, \
					      plane_type, name, ##__VA_ARGS__))

/**
 * drm_plane_index - find the index of a रेजिस्टरed plane
 * @plane: plane to find index क्रम
 *
 * Given a रेजिस्टरed plane, वापस the index of that plane within a DRM
 * device's list of planes.
 */
अटल अंतरभूत अचिन्हित पूर्णांक drm_plane_index(स्थिर काष्ठा drm_plane *plane)
अणु
	वापस plane->index;
पूर्ण

/**
 * drm_plane_mask - find the mask of a रेजिस्टरed plane
 * @plane: plane to find mask क्रम
 */
अटल अंतरभूत u32 drm_plane_mask(स्थिर काष्ठा drm_plane *plane)
अणु
	वापस 1 << drm_plane_index(plane);
पूर्ण

काष्ठा drm_plane * drm_plane_from_index(काष्ठा drm_device *dev, पूर्णांक idx);
व्योम drm_plane_क्रमce_disable(काष्ठा drm_plane *plane);

पूर्णांक drm_mode_plane_set_obj_prop(काष्ठा drm_plane *plane,
				       काष्ठा drm_property *property,
				       uपूर्णांक64_t value);

/**
 * drm_plane_find - find a &drm_plane
 * @dev: DRM device
 * @file_priv: drm file to check क्रम lease against.
 * @id: plane id
 *
 * Returns the plane with @id, शून्य अगर it करोesn't exist. Simple wrapper around
 * drm_mode_object_find().
 */
अटल अंतरभूत काष्ठा drm_plane *drm_plane_find(काष्ठा drm_device *dev,
		काष्ठा drm_file *file_priv,
		uपूर्णांक32_t id)
अणु
	काष्ठा drm_mode_object *mo;
	mo = drm_mode_object_find(dev, file_priv, id, DRM_MODE_OBJECT_PLANE);
	वापस mo ? obj_to_plane(mo) : शून्य;
पूर्ण

/**
 * drm_क्रम_each_plane_mask - iterate over planes specअगरied by biपंचांगask
 * @plane: the loop cursor
 * @dev: the DRM device
 * @plane_mask: biपंचांगask of plane indices
 *
 * Iterate over all planes specअगरied by biपंचांगask.
 */
#घोषणा drm_क्रम_each_plane_mask(plane, dev, plane_mask) \
	list_क्रम_each_entry((plane), &(dev)->mode_config.plane_list, head) \
		क्रम_each_अगर ((plane_mask) & drm_plane_mask(plane))

/**
 * drm_क्रम_each_legacy_plane - iterate over all planes क्रम legacy userspace
 * @plane: the loop cursor
 * @dev: the DRM device
 *
 * Iterate over all legacy planes of @dev, excluding primary and cursor planes.
 * This is useful क्रम implementing userspace apis when userspace is not
 * universal plane aware. See also &क्रमागत drm_plane_type.
 */
#घोषणा drm_क्रम_each_legacy_plane(plane, dev) \
	list_क्रम_each_entry(plane, &(dev)->mode_config.plane_list, head) \
		क्रम_each_अगर (plane->type == DRM_PLANE_TYPE_OVERLAY)

/**
 * drm_क्रम_each_plane - iterate over all planes
 * @plane: the loop cursor
 * @dev: the DRM device
 *
 * Iterate over all planes of @dev, include primary and cursor planes.
 */
#घोषणा drm_क्रम_each_plane(plane, dev) \
	list_क्रम_each_entry(plane, &(dev)->mode_config.plane_list, head)

bool drm_any_plane_has_क्रमmat(काष्ठा drm_device *dev,
			      u32 क्रमmat, u64 modअगरier);
/**
 * drm_plane_get_damage_clips_count - Returns damage clips count.
 * @state: Plane state.
 *
 * Simple helper to get the number of &drm_mode_rect clips set by user-space
 * during plane update.
 *
 * Return: Number of clips in plane fb_damage_clips blob property.
 */
अटल अंतरभूत अचिन्हित पूर्णांक
drm_plane_get_damage_clips_count(स्थिर काष्ठा drm_plane_state *state)
अणु
	वापस (state && state->fb_damage_clips) ?
		state->fb_damage_clips->length/माप(काष्ठा drm_mode_rect) : 0;
पूर्ण

/**
 * drm_plane_get_damage_clips - Returns damage clips.
 * @state: Plane state.
 *
 * Note that this function वापसs uapi type &drm_mode_rect. Drivers might
 * instead be पूर्णांकerested in पूर्णांकernal &drm_rect which can be obtained by calling
 * drm_helper_get_plane_damage_clips().
 *
 * Return: Damage clips in plane fb_damage_clips blob property.
 */
अटल अंतरभूत काष्ठा drm_mode_rect *
drm_plane_get_damage_clips(स्थिर काष्ठा drm_plane_state *state)
अणु
	वापस (काष्ठा drm_mode_rect *)((state && state->fb_damage_clips) ?
					state->fb_damage_clips->data : शून्य);
पूर्ण

पूर्णांक drm_plane_create_scaling_filter_property(काष्ठा drm_plane *plane,
					     अचिन्हित पूर्णांक supported_filters);

#पूर्ण_अगर
