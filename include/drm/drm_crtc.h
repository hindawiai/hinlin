<शैली गुरु>
/*
 * Copyright तऊ 2006 Keith Packard
 * Copyright तऊ 2007-2008 Dave Airlie
 * Copyright तऊ 2007-2008 Intel Corporation
 *   Jesse Barnes <jesse.barnes@पूर्णांकel.com>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */
#अगर_अघोषित __DRM_CRTC_H__
#घोषणा __DRM_CRTC_H__

#समावेश <linux/i2c.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/fb.h>
#समावेश <linux/hdmi.h>
#समावेश <linux/media-bus-क्रमmat.h>
#समावेश <uapi/drm/drm_mode.h>
#समावेश <uapi/drm/drm_fourcc.h>
#समावेश <drm/drm_modeset_lock.h>
#समावेश <drm/drm_rect.h>
#समावेश <drm/drm_mode_object.h>
#समावेश <drm/drm_framebuffer.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_property.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_plane.h>
#समावेश <drm/drm_blend.h>
#समावेश <drm/drm_color_mgmt.h>
#समावेश <drm/drm_debugfs_crc.h>
#समावेश <drm/drm_mode_config.h>

काष्ठा drm_device;
काष्ठा drm_mode_set;
काष्ठा drm_file;
काष्ठा drm_clip_rect;
काष्ठा drm_prपूर्णांकer;
काष्ठा drm_self_refresh_data;
काष्ठा device_node;
काष्ठा dma_fence;
काष्ठा edid;

अटल अंतरभूत पूर्णांक64_t U642I64(uपूर्णांक64_t val)
अणु
	वापस (पूर्णांक64_t)*((पूर्णांक64_t *)&val);
पूर्ण
अटल अंतरभूत uपूर्णांक64_t I642U64(पूर्णांक64_t val)
अणु
	वापस (uपूर्णांक64_t)*((uपूर्णांक64_t *)&val);
पूर्ण

काष्ठा drm_crtc;
काष्ठा drm_pending_vblank_event;
काष्ठा drm_plane;
काष्ठा drm_bridge;
काष्ठा drm_atomic_state;

काष्ठा drm_crtc_helper_funcs;
काष्ठा drm_plane_helper_funcs;

/**
 * काष्ठा drm_crtc_state - mutable CRTC state
 *
 * Note that the distinction between @enable and @active is rather subtle:
 * Flipping @active जबतक @enable is set without changing anything अन्यथा may
 * never वापस in a failure from the &drm_mode_config_funcs.atomic_check
 * callback. Userspace assumes that a DPMS On will always succeed. In other
 * words: @enable controls resource assignment, @active controls the actual
 * hardware state.
 *
 * The three booleans active_changed, connectors_changed and mode_changed are
 * पूर्णांकended to indicate whether a full modeset is needed, rather than strictly
 * describing what has changed in a commit. See also:
 * drm_atomic_crtc_needs_modeset()
 *
 * WARNING: Transitional helpers (like drm_helper_crtc_mode_set() or
 * drm_helper_crtc_mode_set_base()) करो not मुख्यtain many of the derived control
 * state like @plane_mask so drivers not converted over to atomic helpers should
 * not rely on these being accurate!
 */
काष्ठा drm_crtc_state अणु
	/** @crtc: backpoपूर्णांकer to the CRTC */
	काष्ठा drm_crtc *crtc;

	/**
	 * @enable: Whether the CRTC should be enabled, gates all other state.
	 * This controls reservations of shared resources. Actual hardware state
	 * is controlled by @active.
	 */
	bool enable;

	/**
	 * @active: Whether the CRTC is actively displaying (used क्रम DPMS).
	 * Implies that @enable is set. The driver must not release any shared
	 * resources अगर @active is set to false but @enable still true, because
	 * userspace expects that a DPMS ON always succeeds.
	 *
	 * Hence drivers must not consult @active in their various
	 * &drm_mode_config_funcs.atomic_check callback to reject an atomic
	 * commit. They can consult it to aid in the computation of derived
	 * hardware state, since even in the DPMS OFF state the display hardware
	 * should be as much घातered करोwn as when the CRTC is completely
	 * disabled through setting @enable to false.
	 */
	bool active;

	/**
	 * @planes_changed: Planes on this crtc are updated. Used by the atomic
	 * helpers and drivers to steer the atomic commit control flow.
	 */
	bool planes_changed : 1;

	/**
	 * @mode_changed: @mode or @enable has been changed. Used by the atomic
	 * helpers and drivers to steer the atomic commit control flow. See also
	 * drm_atomic_crtc_needs_modeset().
	 *
	 * Drivers are supposed to set this क्रम any CRTC state changes that
	 * require a full modeset. They can also reset it to false अगर e.g. a
	 * @mode change can be करोne without a full modeset by only changing
	 * scaler settings.
	 */
	bool mode_changed : 1;

	/**
	 * @active_changed: @active has been toggled. Used by the atomic
	 * helpers and drivers to steer the atomic commit control flow. See also
	 * drm_atomic_crtc_needs_modeset().
	 */
	bool active_changed : 1;

	/**
	 * @connectors_changed: Connectors to this crtc have been updated,
	 * either in their state or routing. Used by the atomic
	 * helpers and drivers to steer the atomic commit control flow. See also
	 * drm_atomic_crtc_needs_modeset().
	 *
	 * Drivers are supposed to set this as-needed from their own atomic
	 * check code, e.g. from &drm_encoder_helper_funcs.atomic_check
	 */
	bool connectors_changed : 1;
	/**
	 * @zpos_changed: zpos values of planes on this crtc have been updated.
	 * Used by the atomic helpers and drivers to steer the atomic commit
	 * control flow.
	 */
	bool zpos_changed : 1;
	/**
	 * @color_mgmt_changed: Color management properties have changed
	 * (@gamma_lut, @degamma_lut or @cपंचांग). Used by the atomic helpers and
	 * drivers to steer the atomic commit control flow.
	 */
	bool color_mgmt_changed : 1;

	/**
	 * @no_vblank:
	 *
	 * Reflects the ability of a CRTC to send VBLANK events. This state
	 * usually depends on the pipeline configuration. If set to true, DRM
	 * atomic helpers will send out a fake VBLANK event during display
	 * updates after all hardware changes have been committed. This is
	 * implemented in drm_atomic_helper_fake_vblank().
	 *
	 * One usage is क्रम drivers and/or hardware without support क्रम VBLANK
	 * पूर्णांकerrupts. Such drivers typically करो not initialize vblanking
	 * (i.e., call drm_vblank_init() with the number of CRTCs). For CRTCs
	 * without initialized vblanking, this field is set to true in
	 * drm_atomic_helper_check_modeset(), and a fake VBLANK event will be
	 * send out on each update of the display pipeline by
	 * drm_atomic_helper_fake_vblank().
	 *
	 * Another usage is CRTCs feeding a ग_लिखोback connector operating in
	 * oneshot mode. In this हाल the fake VBLANK event is only generated
	 * when a job is queued to the ग_लिखोback connector, and we want the
	 * core to fake VBLANK events when this part of the pipeline hasn't
	 * changed but others had or when the CRTC and connectors are being
	 * disabled.
	 *
	 * __drm_atomic_helper_crtc_duplicate_state() will not reset the value
	 * from the current state, the CRTC driver is then responsible क्रम
	 * updating this field when needed.
	 *
	 * Note that the combination of &drm_crtc_state.event == शून्य and
	 * &drm_crtc_state.no_blank == true is valid and usually used when the
	 * ग_लिखोback connector attached to the CRTC has a new job queued. In
	 * this हाल the driver will send the VBLANK event on its own when the
	 * ग_लिखोback job is complete.
	 */
	bool no_vblank : 1;

	/**
	 * @plane_mask: Biपंचांगask of drm_plane_mask(plane) of planes attached to
	 * this CRTC.
	 */
	u32 plane_mask;

	/**
	 * @connector_mask: Biपंचांगask of drm_connector_mask(connector) of
	 * connectors attached to this CRTC.
	 */
	u32 connector_mask;

	/**
	 * @encoder_mask: Biपंचांगask of drm_encoder_mask(encoder) of encoders
	 * attached to this CRTC.
	 */
	u32 encoder_mask;

	/**
	 * @adjusted_mode:
	 *
	 * Internal display timings which can be used by the driver to handle
	 * dअगरferences between the mode requested by userspace in @mode and what
	 * is actually programmed पूर्णांकo the hardware.
	 *
	 * For drivers using &drm_bridge, this stores hardware display timings
	 * used between the CRTC and the first bridge. For other drivers, the
	 * meaning of the adjusted_mode field is purely driver implementation
	 * defined inक्रमmation, and will usually be used to store the hardware
	 * display timings used between the CRTC and encoder blocks.
	 */
	काष्ठा drm_display_mode adjusted_mode;

	/**
	 * @mode:
	 *
	 * Display timings requested by userspace. The driver should try to
	 * match the refresh rate as बंद as possible (but note that it's
	 * undefined what exactly is बंद enough, e.g. some of the HDMI modes
	 * only dअगरfer in less than 1% of the refresh rate). The active width
	 * and height as observed by userspace क्रम positioning planes must match
	 * exactly.
	 *
	 * For बाह्यal connectors where the sink isn't fixed (like with a
	 * built-in panel), this mode here should match the physical mode on the
	 * wire to the last details (i.e. including sync polarities and
	 * everything).
	 */
	काष्ठा drm_display_mode mode;

	/**
	 * @mode_blob: &drm_property_blob क्रम @mode, क्रम exposing the mode to
	 * atomic userspace.
	 */
	काष्ठा drm_property_blob *mode_blob;

	/**
	 * @degamma_lut:
	 *
	 * Lookup table क्रम converting framebuffer pixel data beक्रमe apply the
	 * color conversion matrix @cपंचांग. See drm_crtc_enable_color_mgmt(). The
	 * blob (अगर not शून्य) is an array of &काष्ठा drm_color_lut.
	 */
	काष्ठा drm_property_blob *degamma_lut;

	/**
	 * @cपंचांग:
	 *
	 * Color transक्रमmation matrix. See drm_crtc_enable_color_mgmt(). The
	 * blob (अगर not शून्य) is a &काष्ठा drm_color_cपंचांग.
	 */
	काष्ठा drm_property_blob *cपंचांग;

	/**
	 * @gamma_lut:
	 *
	 * Lookup table क्रम converting pixel data after the color conversion
	 * matrix @cपंचांग.  See drm_crtc_enable_color_mgmt(). The blob (अगर not
	 * शून्य) is an array of &काष्ठा drm_color_lut.
	 */
	काष्ठा drm_property_blob *gamma_lut;

	/**
	 * @target_vblank:
	 *
	 * Target vertical blank period when a page flip
	 * should take effect.
	 */
	u32 target_vblank;

	/**
	 * @async_flip:
	 *
	 * This is set when DRM_MODE_PAGE_FLIP_ASYNC is set in the legacy
	 * PAGE_FLIP IOCTL. It's not wired up क्रम the atomic IOCTL itself yet.
	 */
	bool async_flip;

	/**
	 * @vrr_enabled:
	 *
	 * Indicates अगर variable refresh rate should be enabled क्रम the CRTC.
	 * Support क्रम the requested vrr state will depend on driver and
	 * hardware capabiltiy - lacking support is not treated as failure.
	 */
	bool vrr_enabled;

	/**
	 * @self_refresh_active:
	 *
	 * Used by the self refresh helpers to denote when a self refresh
	 * transition is occurring. This will be set on enable/disable callbacks
	 * when self refresh is being enabled or disabled. In some हालs, it may
	 * not be desirable to fully shut off the crtc during self refresh.
	 * CRTC's can inspect this flag and determine the best course of action.
	 */
	bool self_refresh_active;

	/**
	 * @scaling_filter:
	 *
	 * Scaling filter to be applied
	 */
	क्रमागत drm_scaling_filter scaling_filter;

	/**
	 * @event:
	 *
	 * Optional poपूर्णांकer to a DRM event to संकेत upon completion of the
	 * state update. The driver must send out the event when the atomic
	 * commit operation completes. There are two हालs:
	 *
	 *  - The event is क्रम a CRTC which is being disabled through this
	 *    atomic commit. In that हाल the event can be send out any समय
	 *    after the hardware has stopped scanning out the current
	 *    framebuffers. It should contain the बारtamp and counter क्रम the
	 *    last vblank beक्रमe the display pipeline was shut off. The simplest
	 *    way to achieve that is calling drm_crtc_send_vblank_event()
	 *    somewhen after drm_crtc_vblank_off() has been called.
	 *
	 *  - For a CRTC which is enabled at the end of the commit (even when it
	 *    undergoes an full modeset) the vblank बारtamp and counter must
	 *    be क्रम the vblank right beक्रमe the first frame that scans out the
	 *    new set of buffers. Again the event can only be sent out after the
	 *    hardware has stopped scanning out the old buffers.
	 *
	 *  - Events क्रम disabled CRTCs are not allowed, and drivers can ignore
	 *    that हाल.
	 *
	 * For very simple hardware without VBLANK पूर्णांकerrupt, enabling
	 * &काष्ठा drm_crtc_state.no_vblank makes DRM's atomic commit helpers
	 * send a fake VBLANK event at the end of the display update after all
	 * hardware changes have been applied. See
	 * drm_atomic_helper_fake_vblank().
	 *
	 * For more complex hardware this
	 * can be handled by the drm_crtc_send_vblank_event() function,
	 * which the driver should call on the provided event upon completion of
	 * the atomic commit. Note that अगर the driver supports vblank संकेतling
	 * and बारtamping the vblank counters and बारtamps must agree with
	 * the ones वापसed from page flip events. With the current vblank
	 * helper infraकाष्ठाure this can be achieved by holding a vblank
	 * reference जबतक the page flip is pending, acquired through
	 * drm_crtc_vblank_get() and released with drm_crtc_vblank_put().
	 * Drivers are मुक्त to implement their own vblank counter and बारtamp
	 * tracking though, e.g. अगर they have accurate बारtamp रेजिस्टरs in
	 * hardware.
	 *
	 * For hardware which supports some means to synchronize vblank
	 * पूर्णांकerrupt delivery with committing display state there's also
	 * drm_crtc_arm_vblank_event(). See the करोcumentation of that function
	 * क्रम a detailed discussion of the स्थिरraपूर्णांकs it needs to be used
	 * safely.
	 *
	 * If the device can't notअगरy of flip completion in a race-मुक्त way
	 * at all, then the event should be armed just after the page flip is
	 * committed. In the worst हाल the driver will send the event to
	 * userspace one frame too late. This करोesn't allow क्रम a real atomic
	 * update, but it should aव्योम tearing.
	 */
	काष्ठा drm_pending_vblank_event *event;

	/**
	 * @commit:
	 *
	 * This tracks how the commit क्रम this update proceeds through the
	 * various phases. This is never cleared, except when we destroy the
	 * state, so that subsequent commits can synchronize with previous ones.
	 */
	काष्ठा drm_crtc_commit *commit;

	/** @state: backpoपूर्णांकer to global drm_atomic_state */
	काष्ठा drm_atomic_state *state;
पूर्ण;

/**
 * काष्ठा drm_crtc_funcs - control CRTCs क्रम a given device
 *
 * The drm_crtc_funcs काष्ठाure is the central CRTC management काष्ठाure
 * in the DRM.  Each CRTC controls one or more connectors (note that the name
 * CRTC is simply historical, a CRTC may control LVDS, VGA, DVI, TV out, etc.
 * connectors, not just CRTs).
 *
 * Each driver is responsible क्रम filling out this काष्ठाure at startup समय,
 * in addition to providing other modesetting features, like i2c and DDC
 * bus accessors.
 */
काष्ठा drm_crtc_funcs अणु
	/**
	 * @reset:
	 *
	 * Reset CRTC hardware and software state to off. This function isn't
	 * called by the core directly, only through drm_mode_config_reset().
	 * It's not a helper hook only क्रम historical reasons.
	 *
	 * Atomic drivers can use drm_atomic_helper_crtc_reset() to reset
	 * atomic state using this hook.
	 */
	व्योम (*reset)(काष्ठा drm_crtc *crtc);

	/**
	 * @cursor_set:
	 *
	 * Update the cursor image. The cursor position is relative to the CRTC
	 * and can be partially or fully outside of the visible area.
	 *
	 * Note that contrary to all other KMS functions the legacy cursor entry
	 * poपूर्णांकs करोn't take a framebuffer object, but instead take directly a
	 * raw buffer object id from the driver's buffer manager (which is
	 * either GEM or TTM क्रम current drivers).
	 *
	 * This entry poपूर्णांक is deprecated, drivers should instead implement
	 * universal plane support and रेजिस्टर a proper cursor plane using
	 * drm_crtc_init_with_planes().
	 *
	 * This callback is optional
	 *
	 * RETURNS:
	 *
	 * 0 on success or a negative error code on failure.
	 */
	पूर्णांक (*cursor_set)(काष्ठा drm_crtc *crtc, काष्ठा drm_file *file_priv,
			  uपूर्णांक32_t handle, uपूर्णांक32_t width, uपूर्णांक32_t height);

	/**
	 * @cursor_set2:
	 *
	 * Update the cursor image, including hotspot inक्रमmation. The hotspot
	 * must not affect the cursor position in CRTC coordinates, but is only
	 * meant as a hपूर्णांक क्रम भवized display hardware to coordinate the
	 * guests and hosts cursor position. The cursor hotspot is relative to
	 * the cursor image. Otherwise this works exactly like @cursor_set.
	 *
	 * This entry poपूर्णांक is deprecated, drivers should instead implement
	 * universal plane support and रेजिस्टर a proper cursor plane using
	 * drm_crtc_init_with_planes().
	 *
	 * This callback is optional.
	 *
	 * RETURNS:
	 *
	 * 0 on success or a negative error code on failure.
	 */
	पूर्णांक (*cursor_set2)(काष्ठा drm_crtc *crtc, काष्ठा drm_file *file_priv,
			   uपूर्णांक32_t handle, uपूर्णांक32_t width, uपूर्णांक32_t height,
			   पूर्णांक32_t hot_x, पूर्णांक32_t hot_y);

	/**
	 * @cursor_move:
	 *
	 * Update the cursor position. The cursor करोes not need to be visible
	 * when this hook is called.
	 *
	 * This entry poपूर्णांक is deprecated, drivers should instead implement
	 * universal plane support and रेजिस्टर a proper cursor plane using
	 * drm_crtc_init_with_planes().
	 *
	 * This callback is optional.
	 *
	 * RETURNS:
	 *
	 * 0 on success or a negative error code on failure.
	 */
	पूर्णांक (*cursor_move)(काष्ठा drm_crtc *crtc, पूर्णांक x, पूर्णांक y);

	/**
	 * @gamma_set:
	 *
	 * Set gamma on the CRTC.
	 *
	 * This callback is optional.
	 *
	 * Atomic drivers who want to support gamma tables should implement the
	 * atomic color management support, enabled by calling
	 * drm_crtc_enable_color_mgmt(), which then supports the legacy gamma
	 * पूर्णांकerface through the drm_atomic_helper_legacy_gamma_set()
	 * compatibility implementation.
	 */
	पूर्णांक (*gamma_set)(काष्ठा drm_crtc *crtc, u16 *r, u16 *g, u16 *b,
			 uपूर्णांक32_t size,
			 काष्ठा drm_modeset_acquire_ctx *ctx);

	/**
	 * @destroy:
	 *
	 * Clean up CRTC resources. This is only called at driver unload समय
	 * through drm_mode_config_cleanup() since a CRTC cannot be hotplugged
	 * in DRM.
	 */
	व्योम (*destroy)(काष्ठा drm_crtc *crtc);

	/**
	 * @set_config:
	 *
	 * This is the मुख्य legacy entry poपूर्णांक to change the modeset state on a
	 * CRTC. All the details of the desired configuration are passed in a
	 * &काष्ठा drm_mode_set - see there क्रम details.
	 *
	 * Drivers implementing atomic modeset should use
	 * drm_atomic_helper_set_config() to implement this hook.
	 *
	 * RETURNS:
	 *
	 * 0 on success or a negative error code on failure.
	 */
	पूर्णांक (*set_config)(काष्ठा drm_mode_set *set,
			  काष्ठा drm_modeset_acquire_ctx *ctx);

	/**
	 * @page_flip:
	 *
	 * Legacy entry poपूर्णांक to schedule a flip to the given framebuffer.
	 *
	 * Page flipping is a synchronization mechanism that replaces the frame
	 * buffer being scanned out by the CRTC with a new frame buffer during
	 * vertical blanking, aव्योमing tearing (except when requested otherwise
	 * through the DRM_MODE_PAGE_FLIP_ASYNC flag). When an application
	 * requests a page flip the DRM core verअगरies that the new frame buffer
	 * is large enough to be scanned out by the CRTC in the currently
	 * configured mode and then calls this hook with a poपूर्णांकer to the new
	 * frame buffer.
	 *
	 * The driver must रुको क्रम any pending rendering to the new framebuffer
	 * to complete beक्रमe executing the flip. It should also रुको क्रम any
	 * pending rendering from other drivers अगर the underlying buffer is a
	 * shared dma-buf.
	 *
	 * An application can request to be notअगरied when the page flip has
	 * completed. The drm core will supply a &काष्ठा drm_event in the event
	 * parameter in this हाल. This can be handled by the
	 * drm_crtc_send_vblank_event() function, which the driver should call on
	 * the provided event upon completion of the flip. Note that अगर
	 * the driver supports vblank संकेतling and बारtamping the vblank
	 * counters and बारtamps must agree with the ones वापसed from page
	 * flip events. With the current vblank helper infraकाष्ठाure this can
	 * be achieved by holding a vblank reference जबतक the page flip is
	 * pending, acquired through drm_crtc_vblank_get() and released with
	 * drm_crtc_vblank_put(). Drivers are मुक्त to implement their own vblank
	 * counter and बारtamp tracking though, e.g. अगर they have accurate
	 * बारtamp रेजिस्टरs in hardware.
	 *
	 * This callback is optional.
	 *
	 * NOTE:
	 *
	 * Very early versions of the KMS ABI mandated that the driver must
	 * block (but not reject) any rendering to the old framebuffer until the
	 * flip operation has completed and the old framebuffer is no दीर्घer
	 * visible. This requirement has been lअगरted, and userspace is instead
	 * expected to request delivery of an event and रुको with recycling old
	 * buffers until such has been received.
	 *
	 * RETURNS:
	 *
	 * 0 on success or a negative error code on failure. Note that अगर a
	 * page flip operation is alपढ़ोy pending the callback should वापस
	 * -EBUSY. Pageflips on a disabled CRTC (either by setting a शून्य mode
	 * or just runसमय disabled through DPMS respectively the new atomic
	 * "ACTIVE" state) should result in an -EINVAL error code. Note that
	 * drm_atomic_helper_page_flip() checks this alपढ़ोy क्रम atomic drivers.
	 */
	पूर्णांक (*page_flip)(काष्ठा drm_crtc *crtc,
			 काष्ठा drm_framebuffer *fb,
			 काष्ठा drm_pending_vblank_event *event,
			 uपूर्णांक32_t flags,
			 काष्ठा drm_modeset_acquire_ctx *ctx);

	/**
	 * @page_flip_target:
	 *
	 * Same as @page_flip but with an additional parameter specअगरying the
	 * असलolute target vertical blank period (as reported by
	 * drm_crtc_vblank_count()) when the flip should take effect.
	 *
	 * Note that the core code calls drm_crtc_vblank_get beक्रमe this entry
	 * poपूर्णांक, and will call drm_crtc_vblank_put अगर this entry poपूर्णांक वापसs
	 * any non-0 error code. It's the driver's responsibility to call
	 * drm_crtc_vblank_put after this entry poपूर्णांक वापसs 0, typically when
	 * the flip completes.
	 */
	पूर्णांक (*page_flip_target)(काष्ठा drm_crtc *crtc,
				काष्ठा drm_framebuffer *fb,
				काष्ठा drm_pending_vblank_event *event,
				uपूर्णांक32_t flags, uपूर्णांक32_t target,
				काष्ठा drm_modeset_acquire_ctx *ctx);

	/**
	 * @set_property:
	 *
	 * This is the legacy entry poपूर्णांक to update a property attached to the
	 * CRTC.
	 *
	 * This callback is optional अगर the driver करोes not support any legacy
	 * driver-निजी properties. For atomic drivers it is not used because
	 * property handling is करोne entirely in the DRM core.
	 *
	 * RETURNS:
	 *
	 * 0 on success or a negative error code on failure.
	 */
	पूर्णांक (*set_property)(काष्ठा drm_crtc *crtc,
			    काष्ठा drm_property *property, uपूर्णांक64_t val);

	/**
	 * @atomic_duplicate_state:
	 *
	 * Duplicate the current atomic state क्रम this CRTC and वापस it.
	 * The core and helpers guarantee that any atomic state duplicated with
	 * this hook and still owned by the caller (i.e. not transferred to the
	 * driver by calling &drm_mode_config_funcs.atomic_commit) will be
	 * cleaned up by calling the @atomic_destroy_state hook in this
	 * काष्ठाure.
	 *
	 * This callback is mandatory क्रम atomic drivers.
	 *
	 * Atomic drivers which करोn't subclass &काष्ठा drm_crtc_state should use
	 * drm_atomic_helper_crtc_duplicate_state(). Drivers that subclass the
	 * state काष्ठाure to extend it with driver-निजी state should use
	 * __drm_atomic_helper_crtc_duplicate_state() to make sure shared state is
	 * duplicated in a consistent fashion across drivers.
	 *
	 * It is an error to call this hook beक्रमe &drm_crtc.state has been
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
	काष्ठा drm_crtc_state *(*atomic_duplicate_state)(काष्ठा drm_crtc *crtc);

	/**
	 * @atomic_destroy_state:
	 *
	 * Destroy a state duplicated with @atomic_duplicate_state and release
	 * or unreference all resources it references
	 *
	 * This callback is mandatory क्रम atomic drivers.
	 */
	व्योम (*atomic_destroy_state)(काष्ठा drm_crtc *crtc,
				     काष्ठा drm_crtc_state *state);

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
	 * drm_atomic_crtc_set_property() instead.
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
	 * implemented by the driver (which should never happen, the core only
	 * asks क्रम properties attached to this CRTC). No other validation is
	 * allowed by the driver. The core alपढ़ोy checks that the property
	 * value is within the range (पूर्णांकeger, valid क्रमागत value, ...) the driver
	 * set when रेजिस्टरing the property.
	 */
	पूर्णांक (*atomic_set_property)(काष्ठा drm_crtc *crtc,
				   काष्ठा drm_crtc_state *state,
				   काष्ठा drm_property *property,
				   uपूर्णांक64_t val);
	/**
	 * @atomic_get_property:
	 *
	 * Reads out the decoded driver-निजी property. This is used to
	 * implement the GETCRTC IOCTL.
	 *
	 * Do not call this function directly, use
	 * drm_atomic_crtc_get_property() instead.
	 *
	 * This callback is optional अगर the driver करोes not support any
	 * driver-निजी atomic properties.
	 *
	 * RETURNS:
	 *
	 * 0 on success, -EINVAL अगर the property isn't implemented by the
	 * driver (which should never happen, the core only asks क्रम
	 * properties attached to this CRTC).
	 */
	पूर्णांक (*atomic_get_property)(काष्ठा drm_crtc *crtc,
				   स्थिर काष्ठा drm_crtc_state *state,
				   काष्ठा drm_property *property,
				   uपूर्णांक64_t *val);

	/**
	 * @late_रेजिस्टर:
	 *
	 * This optional hook can be used to रेजिस्टर additional userspace
	 * पूर्णांकerfaces attached to the crtc like debugfs पूर्णांकerfaces.
	 * It is called late in the driver load sequence from drm_dev_रेजिस्टर().
	 * Everything added from this callback should be unरेजिस्टरed in
	 * the early_unरेजिस्टर callback.
	 *
	 * Returns:
	 *
	 * 0 on success, or a negative error code on failure.
	 */
	पूर्णांक (*late_रेजिस्टर)(काष्ठा drm_crtc *crtc);

	/**
	 * @early_unरेजिस्टर:
	 *
	 * This optional hook should be used to unरेजिस्टर the additional
	 * userspace पूर्णांकerfaces attached to the crtc from
	 * @late_रेजिस्टर. It is called from drm_dev_unरेजिस्टर(),
	 * early in the driver unload sequence to disable userspace access
	 * beक्रमe data काष्ठाures are tornकरोwn.
	 */
	व्योम (*early_unरेजिस्टर)(काष्ठा drm_crtc *crtc);

	/**
	 * @set_crc_source:
	 *
	 * Changes the source of CRC checksums of frames at the request of
	 * userspace, typically क्रम testing purposes. The sources available are
	 * specअगरic of each driver and a %शून्य value indicates that CRC
	 * generation is to be चयनed off.
	 *
	 * When CRC generation is enabled, the driver should call
	 * drm_crtc_add_crc_entry() at each frame, providing any inक्रमmation
	 * that अक्षरacterizes the frame contents in the crcN arguments, as
	 * provided from the configured source. Drivers must accept an "auto"
	 * source name that will select a शेष source क्रम this CRTC.
	 *
	 * This may trigger an atomic modeset commit अगर necessary, to enable CRC
	 * generation.
	 *
	 * Note that "auto" can depend upon the current modeset configuration,
	 * e.g. it could pick an encoder or output specअगरic CRC sampling poपूर्णांक.
	 *
	 * This callback is optional अगर the driver करोes not support any CRC
	 * generation functionality.
	 *
	 * RETURNS:
	 *
	 * 0 on success or a negative error code on failure.
	 */
	पूर्णांक (*set_crc_source)(काष्ठा drm_crtc *crtc, स्थिर अक्षर *source);

	/**
	 * @verअगरy_crc_source:
	 *
	 * verअगरies the source of CRC checksums of frames beक्रमe setting the
	 * source क्रम CRC and during crc खोलो. Source parameter can be शून्य
	 * जबतक disabling crc source.
	 *
	 * This callback is optional अगर the driver करोes not support any CRC
	 * generation functionality.
	 *
	 * RETURNS:
	 *
	 * 0 on success or a negative error code on failure.
	 */
	पूर्णांक (*verअगरy_crc_source)(काष्ठा drm_crtc *crtc, स्थिर अक्षर *source,
				 माप_प्रकार *values_cnt);
	/**
	 * @get_crc_sources:
	 *
	 * Driver callback क्रम getting a list of all the available sources क्रम
	 * CRC generation. This callback depends upon verअगरy_crc_source, So
	 * verअगरy_crc_source callback should be implemented beक्रमe implementing
	 * this. Driver can pass full list of available crc sources, this
	 * callback करोes the verअगरication on each crc-source beक्रमe passing it
	 * to userspace.
	 *
	 * This callback is optional अगर the driver करोes not support exporting of
	 * possible CRC sources list.
	 *
	 * RETURNS:
	 *
	 * a स्थिरant अक्षरacter poपूर्णांकer to the list of all the available CRC
	 * sources. On failure driver should वापस शून्य. count should be
	 * updated with number of sources in list. अगर zero we करोn't process any
	 * source from the list.
	 */
	स्थिर अक्षर *स्थिर *(*get_crc_sources)(काष्ठा drm_crtc *crtc,
					      माप_प्रकार *count);

	/**
	 * @atomic_prपूर्णांक_state:
	 *
	 * If driver subclasses &काष्ठा drm_crtc_state, it should implement
	 * this optional hook क्रम prपूर्णांकing additional driver specअगरic state.
	 *
	 * Do not call this directly, use drm_atomic_crtc_prपूर्णांक_state()
	 * instead.
	 */
	व्योम (*atomic_prपूर्णांक_state)(काष्ठा drm_prपूर्णांकer *p,
				   स्थिर काष्ठा drm_crtc_state *state);

	/**
	 * @get_vblank_counter:
	 *
	 * Driver callback क्रम fetching a raw hardware vblank counter क्रम the
	 * CRTC. It's meant to be used by new drivers as the replacement of
	 * &drm_driver.get_vblank_counter hook.
	 *
	 * This callback is optional. If a device करोesn't have a hardware
	 * counter, the driver can simply leave the hook as शून्य. The DRM core
	 * will account क्रम missed vblank events जबतक पूर्णांकerrupts where disabled
	 * based on प्रणाली बारtamps.
	 *
	 * Wraparound handling and loss of events due to modesetting is dealt
	 * with in the DRM core code, as दीर्घ as drivers call
	 * drm_crtc_vblank_off() and drm_crtc_vblank_on() when disabling or
	 * enabling a CRTC.
	 *
	 * See also &drm_device.vblank_disable_immediate and
	 * &drm_device.max_vblank_count.
	 *
	 * Returns:
	 *
	 * Raw vblank counter value.
	 */
	u32 (*get_vblank_counter)(काष्ठा drm_crtc *crtc);

	/**
	 * @enable_vblank:
	 *
	 * Enable vblank पूर्णांकerrupts क्रम the CRTC. It's meant to be used by
	 * new drivers as the replacement of &drm_driver.enable_vblank hook.
	 *
	 * Returns:
	 *
	 * Zero on success, appropriate त्रुटि_सं अगर the vblank पूर्णांकerrupt cannot
	 * be enabled.
	 */
	पूर्णांक (*enable_vblank)(काष्ठा drm_crtc *crtc);

	/**
	 * @disable_vblank:
	 *
	 * Disable vblank पूर्णांकerrupts क्रम the CRTC. It's meant to be used by
	 * new drivers as the replacement of &drm_driver.disable_vblank hook.
	 */
	व्योम (*disable_vblank)(काष्ठा drm_crtc *crtc);

	/**
	 * @get_vblank_बारtamp:
	 *
	 * Called by drm_get_last_vblबारtamp(). Should वापस a precise
	 * बारtamp when the most recent vblank पूर्णांकerval ended or will end.
	 *
	 * Specअगरically, the बारtamp in @vblank_समय should correspond as
	 * बंदly as possible to the समय when the first video scanline of
	 * the video frame after the end of vblank will start scanning out,
	 * the समय immediately after end of the vblank पूर्णांकerval. If the
	 * @crtc is currently inside vblank, this will be a समय in the future.
	 * If the @crtc is currently scanning out a frame, this will be the
	 * past start समय of the current scanout. This is meant to adhere
	 * to the OpenML OML_sync_control extension specअगरication.
	 *
	 * Parameters:
	 *
	 * crtc:
	 *     CRTC क्रम which बारtamp should be वापसed.
	 * max_error:
	 *     Maximum allowable बारtamp error in nanoseconds.
	 *     Implementation should strive to provide बारtamp
	 *     with an error of at most max_error nanoseconds.
	 *     Returns true upper bound on error क्रम बारtamp.
	 * vblank_समय:
	 *     Target location क्रम वापसed vblank बारtamp.
	 * in_vblank_irq:
	 *     True when called from drm_crtc_handle_vblank().  Some drivers
	 *     need to apply some workarounds क्रम gpu-specअगरic vblank irq quirks
	 *     अगर flag is set.
	 *
	 * Returns:
	 *
	 * True on success, false on failure, which means the core should
	 * fallback to a simple बारtamp taken in drm_crtc_handle_vblank().
	 */
	bool (*get_vblank_बारtamp)(काष्ठा drm_crtc *crtc,
				     पूर्णांक *max_error,
				     kसमय_प्रकार *vblank_समय,
				     bool in_vblank_irq);
पूर्ण;

/**
 * काष्ठा drm_crtc - central CRTC control काष्ठाure
 *
 * Each CRTC may have one or more connectors associated with it.  This काष्ठाure
 * allows the CRTC to be controlled.
 */
काष्ठा drm_crtc अणु
	/** @dev: parent DRM device */
	काष्ठा drm_device *dev;
	/** @port: OF node used by drm_of_find_possible_crtcs(). */
	काष्ठा device_node *port;
	/**
	 * @head:
	 *
	 * List of all CRTCs on @dev, linked from &drm_mode_config.crtc_list.
	 * Invariant over the lअगरeसमय of @dev and thereक्रमe करोes not need
	 * locking.
	 */
	काष्ठा list_head head;

	/** @name: human पढ़ोable name, can be overwritten by the driver */
	अक्षर *name;

	/**
	 * @mutex:
	 *
	 * This provides a पढ़ो lock क्रम the overall CRTC state (mode, dpms
	 * state, ...) and a ग_लिखो lock क्रम everything which can be update
	 * without a full modeset (fb, cursor data, CRTC properties ...). A full
	 * modeset also need to grab &drm_mode_config.connection_mutex.
	 *
	 * For atomic drivers specअगरically this protects @state.
	 */
	काष्ठा drm_modeset_lock mutex;

	/** @base: base KMS object क्रम ID tracking etc. */
	काष्ठा drm_mode_object base;

	/**
	 * @primary:
	 * Primary plane क्रम this CRTC. Note that this is only
	 * relevant क्रम legacy IOCTL, it specअगरies the plane implicitly used by
	 * the SETCRTC and PAGE_FLIP IOCTLs. It करोes not have any signअगरicance
	 * beyond that.
	 */
	काष्ठा drm_plane *primary;

	/**
	 * @cursor:
	 * Cursor plane क्रम this CRTC. Note that this is only relevant क्रम
	 * legacy IOCTL, it specअगरies the plane implicitly used by the SETCURSOR
	 * and SETCURSOR2 IOCTLs. It करोes not have any signअगरicance
	 * beyond that.
	 */
	काष्ठा drm_plane *cursor;

	/**
	 * @index: Position inside the mode_config.list, can be used as an array
	 * index. It is invariant over the lअगरeसमय of the CRTC.
	 */
	अचिन्हित index;

	/**
	 * @cursor_x: Current x position of the cursor, used क्रम universal
	 * cursor planes because the SETCURSOR IOCTL only can update the
	 * framebuffer without supplying the coordinates. Drivers should not use
	 * this directly, atomic drivers should look at &drm_plane_state.crtc_x
	 * of the cursor plane instead.
	 */
	पूर्णांक cursor_x;
	/**
	 * @cursor_y: Current y position of the cursor, used क्रम universal
	 * cursor planes because the SETCURSOR IOCTL only can update the
	 * framebuffer without supplying the coordinates. Drivers should not use
	 * this directly, atomic drivers should look at &drm_plane_state.crtc_y
	 * of the cursor plane instead.
	 */
	पूर्णांक cursor_y;

	/**
	 * @enabled:
	 *
	 * Is this CRTC enabled? Should only be used by legacy drivers, atomic
	 * drivers should instead consult &drm_crtc_state.enable and
	 * &drm_crtc_state.active. Atomic drivers can update this by calling
	 * drm_atomic_helper_update_legacy_modeset_state().
	 */
	bool enabled;

	/**
	 * @mode:
	 *
	 * Current mode timings. Should only be used by legacy drivers, atomic
	 * drivers should instead consult &drm_crtc_state.mode. Atomic drivers
	 * can update this by calling
	 * drm_atomic_helper_update_legacy_modeset_state().
	 */
	काष्ठा drm_display_mode mode;

	/**
	 * @hwmode:
	 *
	 * Programmed mode in hw, after adjusपंचांगents क्रम encoders, crtc, panel
	 * scaling etc. Should only be used by legacy drivers, क्रम high
	 * precision vblank बारtamps in
	 * drm_crtc_vblank_helper_get_vblank_बारtamp().
	 *
	 * Note that atomic drivers should not use this, but instead use
	 * &drm_crtc_state.adjusted_mode. And क्रम high-precision बारtamps
	 * drm_crtc_vblank_helper_get_vblank_बारtamp() used
	 * &drm_vblank_crtc.hwmode,
	 * which is filled out by calling drm_calc_बारtamping_स्थिरants().
	 */
	काष्ठा drm_display_mode hwmode;

	/**
	 * @x:
	 * x position on screen. Should only be used by legacy drivers, atomic
	 * drivers should look at &drm_plane_state.crtc_x of the primary plane
	 * instead. Updated by calling
	 * drm_atomic_helper_update_legacy_modeset_state().
	 */
	पूर्णांक x;
	/**
	 * @y:
	 * y position on screen. Should only be used by legacy drivers, atomic
	 * drivers should look at &drm_plane_state.crtc_y of the primary plane
	 * instead. Updated by calling
	 * drm_atomic_helper_update_legacy_modeset_state().
	 */
	पूर्णांक y;

	/** @funcs: CRTC control functions */
	स्थिर काष्ठा drm_crtc_funcs *funcs;

	/**
	 * @gamma_size: Size of legacy gamma ramp reported to userspace. Set up
	 * by calling drm_mode_crtc_set_gamma_size().
	 */
	uपूर्णांक32_t gamma_size;

	/**
	 * @gamma_store: Gamma ramp values used by the legacy SETGAMMA and
	 * GETGAMMA IOCTls. Set up by calling drm_mode_crtc_set_gamma_size().
	 */
	uपूर्णांक16_t *gamma_store;

	/** @helper_निजी: mid-layer निजी data */
	स्थिर काष्ठा drm_crtc_helper_funcs *helper_निजी;

	/** @properties: property tracking क्रम this CRTC */
	काष्ठा drm_object_properties properties;

	/**
	 * @scaling_filter_property: property to apply a particular filter जबतक
	 * scaling.
	 */
	काष्ठा drm_property *scaling_filter_property;

	/**
	 * @state:
	 *
	 * Current atomic state क्रम this CRTC.
	 *
	 * This is रक्षित by @mutex. Note that nonblocking atomic commits
	 * access the current CRTC state without taking locks. Either by going
	 * through the &काष्ठा drm_atomic_state poपूर्णांकers, see
	 * क्रम_each_oldnew_crtc_in_state(), क्रम_each_old_crtc_in_state() and
	 * क्रम_each_new_crtc_in_state(). Or through careful ordering of atomic
	 * commit operations as implemented in the atomic helpers, see
	 * &काष्ठा drm_crtc_commit.
	 */
	काष्ठा drm_crtc_state *state;

	/**
	 * @commit_list:
	 *
	 * List of &drm_crtc_commit काष्ठाures tracking pending commits.
	 * Protected by @commit_lock. This list holds its own full reference,
	 * as करोes the ongoing commit.
	 *
	 * "Note that the commit क्रम a state change is also tracked in
	 * &drm_crtc_state.commit. For accessing the immediately preceding
	 * commit in an atomic update it is recommended to just use that
	 * poपूर्णांकer in the old CRTC state, since accessing that करोesn't need
	 * any locking or list-walking. @commit_list should only be used to
	 * stall क्रम framebuffer cleanup that's संकेतled through
	 * &drm_crtc_commit.cleanup_करोne."
	 */
	काष्ठा list_head commit_list;

	/**
	 * @commit_lock:
	 *
	 * Spinlock to protect @commit_list.
	 */
	spinlock_t commit_lock;

#अगर_घोषित CONFIG_DEBUG_FS
	/**
	 * @debugfs_entry:
	 *
	 * Debugfs directory क्रम this CRTC.
	 */
	काष्ठा dentry *debugfs_entry;
#पूर्ण_अगर

	/**
	 * @crc:
	 *
	 * Configuration settings of CRC capture.
	 */
	काष्ठा drm_crtc_crc crc;

	/**
	 * @fence_context:
	 *
	 * समयline context used क्रम fence operations.
	 */
	अचिन्हित पूर्णांक fence_context;

	/**
	 * @fence_lock:
	 *
	 * spinlock to protect the fences in the fence_context.
	 */
	spinlock_t fence_lock;
	/**
	 * @fence_seqno:
	 *
	 * Seqno variable used as monotonic counter क्रम the fences
	 * created on the CRTC's समयline.
	 */
	अचिन्हित दीर्घ fence_seqno;

	/**
	 * @समयline_name:
	 *
	 * The name of the CRTC's fence समयline.
	 */
	अक्षर समयline_name[32];

	/**
	 * @self_refresh_data: Holds the state क्रम the self refresh helpers
	 *
	 * Initialized via drm_self_refresh_helper_init().
	 */
	काष्ठा drm_self_refresh_data *self_refresh_data;
पूर्ण;

/**
 * काष्ठा drm_mode_set - new values क्रम a CRTC config change
 * @fb: framebuffer to use क्रम new config
 * @crtc: CRTC whose configuration we're about to change
 * @mode: mode timings to use
 * @x: position of this CRTC relative to @fb
 * @y: position of this CRTC relative to @fb
 * @connectors: array of connectors to drive with this CRTC अगर possible
 * @num_connectors: size of @connectors array
 *
 * This represents a modeset configuration क्रम the legacy SETCRTC ioctl and is
 * also used पूर्णांकernally. Atomic drivers instead use &drm_atomic_state.
 */
काष्ठा drm_mode_set अणु
	काष्ठा drm_framebuffer *fb;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_display_mode *mode;

	uपूर्णांक32_t x;
	uपूर्णांक32_t y;

	काष्ठा drm_connector **connectors;
	माप_प्रकार num_connectors;
पूर्ण;

#घोषणा obj_to_crtc(x) container_of(x, काष्ठा drm_crtc, base)

__म_लिखो(6, 7)
पूर्णांक drm_crtc_init_with_planes(काष्ठा drm_device *dev,
			      काष्ठा drm_crtc *crtc,
			      काष्ठा drm_plane *primary,
			      काष्ठा drm_plane *cursor,
			      स्थिर काष्ठा drm_crtc_funcs *funcs,
			      स्थिर अक्षर *name, ...);
व्योम drm_crtc_cleanup(काष्ठा drm_crtc *crtc);

__म_लिखो(7, 8)
व्योम *__drmm_crtc_alloc_with_planes(काष्ठा drm_device *dev,
				    माप_प्रकार size, माप_प्रकार offset,
				    काष्ठा drm_plane *primary,
				    काष्ठा drm_plane *cursor,
				    स्थिर काष्ठा drm_crtc_funcs *funcs,
				    स्थिर अक्षर *name, ...);

/**
 * drmm_crtc_alloc_with_planes - Allocate and initialize a new CRTC object with
 *    specअगरied primary and cursor planes.
 * @dev: DRM device
 * @type: the type of the काष्ठा which contains काष्ठा &drm_crtc
 * @member: the name of the &drm_crtc within @type.
 * @primary: Primary plane क्रम CRTC
 * @cursor: Cursor plane क्रम CRTC
 * @funcs: callbacks क्रम the new CRTC
 * @name: म_लिखो style क्रमmat string क्रम the CRTC name, or शून्य क्रम शेष name
 *
 * Allocates and initializes a new crtc object. Cleanup is स्वतःmatically
 * handled through रेजिस्टरing drmm_crtc_cleanup() with drmm_add_action().
 *
 * The @drm_crtc_funcs.destroy hook must be शून्य.
 *
 * Returns:
 * Poपूर्णांकer to new crtc, or ERR_PTR on failure.
 */
#घोषणा drmm_crtc_alloc_with_planes(dev, type, member, primary, cursor, funcs, name, ...) \
	((type *)__drmm_crtc_alloc_with_planes(dev, माप(type), \
					       दुरत्व(type, member), \
					       primary, cursor, funcs, \
					       name, ##__VA_ARGS__))

/**
 * drm_crtc_index - find the index of a रेजिस्टरed CRTC
 * @crtc: CRTC to find index क्रम
 *
 * Given a रेजिस्टरed CRTC, वापस the index of that CRTC within a DRM
 * device's list of CRTCs.
 */
अटल अंतरभूत अचिन्हित पूर्णांक drm_crtc_index(स्थिर काष्ठा drm_crtc *crtc)
अणु
	वापस crtc->index;
पूर्ण

/**
 * drm_crtc_mask - find the mask of a रेजिस्टरed CRTC
 * @crtc: CRTC to find mask क्रम
 *
 * Given a रेजिस्टरed CRTC, वापस the mask bit of that CRTC क्रम the
 * &drm_encoder.possible_crtcs and &drm_plane.possible_crtcs fields.
 */
अटल अंतरभूत uपूर्णांक32_t drm_crtc_mask(स्थिर काष्ठा drm_crtc *crtc)
अणु
	वापस 1 << drm_crtc_index(crtc);
पूर्ण

पूर्णांक drm_mode_set_config_पूर्णांकernal(काष्ठा drm_mode_set *set);
काष्ठा drm_crtc *drm_crtc_from_index(काष्ठा drm_device *dev, पूर्णांक idx);

/**
 * drm_crtc_find - look up a CRTC object from its ID
 * @dev: DRM device
 * @file_priv: drm file to check क्रम lease against.
 * @id: &drm_mode_object ID
 *
 * This can be used to look up a CRTC from its userspace ID. Only used by
 * drivers क्रम legacy IOCTLs and पूर्णांकerface, nowadays extensions to the KMS
 * userspace पूर्णांकerface should be करोne using &drm_property.
 */
अटल अंतरभूत काष्ठा drm_crtc *drm_crtc_find(काष्ठा drm_device *dev,
		काष्ठा drm_file *file_priv,
		uपूर्णांक32_t id)
अणु
	काष्ठा drm_mode_object *mo;
	mo = drm_mode_object_find(dev, file_priv, id, DRM_MODE_OBJECT_CRTC);
	वापस mo ? obj_to_crtc(mo) : शून्य;
पूर्ण

/**
 * drm_क्रम_each_crtc - iterate over all CRTCs
 * @crtc: a &काष्ठा drm_crtc as the loop cursor
 * @dev: the &काष्ठा drm_device
 *
 * Iterate over all CRTCs of @dev.
 */
#घोषणा drm_क्रम_each_crtc(crtc, dev) \
	list_क्रम_each_entry(crtc, &(dev)->mode_config.crtc_list, head)

/**
 * drm_क्रम_each_crtc_reverse - iterate over all CRTCs in reverse order
 * @crtc: a &काष्ठा drm_crtc as the loop cursor
 * @dev: the &काष्ठा drm_device
 *
 * Iterate over all CRTCs of @dev.
 */
#घोषणा drm_क्रम_each_crtc_reverse(crtc, dev) \
	list_क्रम_each_entry_reverse(crtc, &(dev)->mode_config.crtc_list, head)

पूर्णांक drm_crtc_create_scaling_filter_property(काष्ठा drm_crtc *crtc,
					    अचिन्हित पूर्णांक supported_filters);

#पूर्ण_अगर /* __DRM_CRTC_H__ */
