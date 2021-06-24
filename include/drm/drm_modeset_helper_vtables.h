<शैली गुरु>
/*
 * Copyright तऊ 2006 Keith Packard
 * Copyright तऊ 2007-2008 Dave Airlie
 * Copyright तऊ 2007-2008 Intel Corporation
 *   Jesse Barnes <jesse.barnes@पूर्णांकel.com>
 * Copyright तऊ 2011-2013 Intel Corporation
 * Copyright तऊ 2015 Intel Corporation
 *   Daniel Vetter <daniel.vetter@ffwll.ch>
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

#अगर_अघोषित __DRM_MODESET_HELPER_VTABLES_H__
#घोषणा __DRM_MODESET_HELPER_VTABLES_H__

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_encoder.h>

/**
 * DOC: overview
 *
 * The DRM mode setting helper functions are common code क्रम drivers to use अगर
 * they wish.  Drivers are not क्रमced to use this code in their
 * implementations but it would be useful अगर the code they करो use at least
 * provides a consistent पूर्णांकerface and operation to userspace. Thereक्रमe it is
 * highly recommended to use the provided helpers as much as possible.
 *
 * Because there is only one poपूर्णांकer per modeset object to hold a vfunc table
 * क्रम helper libraries they are by necessity shared among the dअगरferent
 * helpers.
 *
 * To make this clear all the helper vtables are pulled together in this location here.
 */

क्रमागत mode_set_atomic;
काष्ठा drm_ग_लिखोback_connector;
काष्ठा drm_ग_लिखोback_job;

/**
 * काष्ठा drm_crtc_helper_funcs - helper operations क्रम CRTCs
 *
 * These hooks are used by the legacy CRTC helpers, the transitional plane
 * helpers and the new atomic modesetting helpers.
 */
काष्ठा drm_crtc_helper_funcs अणु
	/**
	 * @dpms:
	 *
	 * Callback to control घातer levels on the CRTC.  If the mode passed in
	 * is unsupported, the provider must use the next lowest घातer level.
	 * This is used by the legacy CRTC helpers to implement DPMS
	 * functionality in drm_helper_connector_dpms().
	 *
	 * This callback is also used to disable a CRTC by calling it with
	 * DRM_MODE_DPMS_OFF अगर the @disable hook isn't used.
	 *
	 * This callback is used by the legacy CRTC helpers.  Atomic helpers
	 * also support using this hook क्रम enabling and disabling a CRTC to
	 * facilitate transitions to atomic, but it is deprecated. Instead
	 * @atomic_enable and @atomic_disable should be used.
	 */
	व्योम (*dpms)(काष्ठा drm_crtc *crtc, पूर्णांक mode);

	/**
	 * @prepare:
	 *
	 * This callback should prepare the CRTC क्रम a subsequent modeset, which
	 * in practice means the driver should disable the CRTC अगर it is
	 * running. Most drivers ended up implementing this by calling their
	 * @dpms hook with DRM_MODE_DPMS_OFF.
	 *
	 * This callback is used by the legacy CRTC helpers.  Atomic helpers
	 * also support using this hook क्रम disabling a CRTC to facilitate
	 * transitions to atomic, but it is deprecated. Instead @atomic_disable
	 * should be used.
	 */
	व्योम (*prepare)(काष्ठा drm_crtc *crtc);

	/**
	 * @commit:
	 *
	 * This callback should commit the new mode on the CRTC after a modeset,
	 * which in practice means the driver should enable the CRTC.  Most
	 * drivers ended up implementing this by calling their @dpms hook with
	 * DRM_MODE_DPMS_ON.
	 *
	 * This callback is used by the legacy CRTC helpers.  Atomic helpers
	 * also support using this hook क्रम enabling a CRTC to facilitate
	 * transitions to atomic, but it is deprecated. Instead @atomic_enable
	 * should be used.
	 */
	व्योम (*commit)(काष्ठा drm_crtc *crtc);

	/**
	 * @mode_valid:
	 *
	 * This callback is used to check अगर a specअगरic mode is valid in this
	 * crtc. This should be implemented अगर the crtc has some sort of
	 * restriction in the modes it can display. For example, a given crtc
	 * may be responsible to set a घड़ी value. If the घड़ी can not
	 * produce all the values क्रम the available modes then this callback
	 * can be used to restrict the number of modes to only the ones that
	 * can be displayed.
	 *
	 * This hook is used by the probe helpers to filter the mode list in
	 * drm_helper_probe_single_connector_modes(), and it is used by the
	 * atomic helpers to validate modes supplied by userspace in
	 * drm_atomic_helper_check_modeset().
	 *
	 * This function is optional.
	 *
	 * NOTE:
	 *
	 * Since this function is both called from the check phase of an atomic
	 * commit, and the mode validation in the probe paths it is not allowed
	 * to look at anything अन्यथा but the passed-in mode, and validate it
	 * against configuration-invariant hardward स्थिरraपूर्णांकs. Any further
	 * limits which depend upon the configuration can only be checked in
	 * @mode_fixup or @atomic_check.
	 *
	 * RETURNS:
	 *
	 * drm_mode_status Enum
	 */
	क्रमागत drm_mode_status (*mode_valid)(काष्ठा drm_crtc *crtc,
					   स्थिर काष्ठा drm_display_mode *mode);

	/**
	 * @mode_fixup:
	 *
	 * This callback is used to validate a mode. The parameter mode is the
	 * display mode that userspace requested, adjusted_mode is the mode the
	 * encoders need to be fed with. Note that this is the inverse semantics
	 * of the meaning क्रम the &drm_encoder and &drm_bridge_funcs.mode_fixup
	 * vfunc. If the CRTC cannot support the requested conversion from mode
	 * to adjusted_mode it should reject the modeset. See also
	 * &drm_crtc_state.adjusted_mode क्रम more details.
	 *
	 * This function is used by both legacy CRTC helpers and atomic helpers.
	 * With atomic helpers it is optional.
	 *
	 * NOTE:
	 *
	 * This function is called in the check phase of atomic modesets, which
	 * can be पातed क्रम any reason (including on userspace's request to
	 * just check whether a configuration would be possible). Atomic drivers
	 * MUST NOT touch any persistent state (hardware or software) or data
	 * काष्ठाures except the passed in adjusted_mode parameter.
	 *
	 * This is in contrast to the legacy CRTC helpers where this was
	 * allowed.
	 *
	 * Atomic drivers which need to inspect and adjust more state should
	 * instead use the @atomic_check callback, but note that they're not
	 * perfectly equivalent: @mode_valid is called from
	 * drm_atomic_helper_check_modeset(), but @atomic_check is called from
	 * drm_atomic_helper_check_planes(), because originally it was meant क्रम
	 * plane update checks only.
	 *
	 * Also beware that userspace can request its own custom modes, neither
	 * core nor helpers filter modes to the list of probe modes reported by
	 * the GETCONNECTOR IOCTL and stored in &drm_connector.modes. To ensure
	 * that modes are filtered consistently put any CRTC स्थिरraपूर्णांकs and
	 * limits checks पूर्णांकo @mode_valid.
	 *
	 * RETURNS:
	 *
	 * True अगर an acceptable configuration is possible, false अगर the modeset
	 * operation should be rejected.
	 */
	bool (*mode_fixup)(काष्ठा drm_crtc *crtc,
			   स्थिर काष्ठा drm_display_mode *mode,
			   काष्ठा drm_display_mode *adjusted_mode);

	/**
	 * @mode_set:
	 *
	 * This callback is used by the legacy CRTC helpers to set a new mode,
	 * position and framebuffer. Since it ties the primary plane to every
	 * mode change it is incompatible with universal plane support. And
	 * since it can't update other planes it's incompatible with atomic
	 * modeset support.
	 *
	 * This callback is only used by CRTC helpers and deprecated.
	 *
	 * RETURNS:
	 *
	 * 0 on success or a negative error code on failure.
	 */
	पूर्णांक (*mode_set)(काष्ठा drm_crtc *crtc, काष्ठा drm_display_mode *mode,
			काष्ठा drm_display_mode *adjusted_mode, पूर्णांक x, पूर्णांक y,
			काष्ठा drm_framebuffer *old_fb);

	/**
	 * @mode_set_nofb:
	 *
	 * This callback is used to update the display mode of a CRTC without
	 * changing anything of the primary plane configuration. This fits the
	 * requirement of atomic and hence is used by the atomic helpers. It is
	 * also used by the transitional plane helpers to implement a
	 * @mode_set hook in drm_helper_crtc_mode_set().
	 *
	 * Note that the display pipe is completely off when this function is
	 * called. Atomic drivers which need hardware to be running beक्रमe they
	 * program the new display mode (e.g. because they implement runसमय PM)
	 * should not use this hook. This is because the helper library calls
	 * this hook only once per mode change and not every समय the display
	 * pipeline is suspended using either DPMS or the new "ACTIVE" property.
	 * Which means रेजिस्टर values set in this callback might get reset when
	 * the CRTC is suspended, but not restored.  Such drivers should instead
	 * move all their CRTC setup पूर्णांकo the @atomic_enable callback.
	 *
	 * This callback is optional.
	 */
	व्योम (*mode_set_nofb)(काष्ठा drm_crtc *crtc);

	/**
	 * @mode_set_base:
	 *
	 * This callback is used by the legacy CRTC helpers to set a new
	 * framebuffer and scanout position. It is optional and used as an
	 * optimized fast-path instead of a full mode set operation with all the
	 * resulting flickering. If it is not present
	 * drm_crtc_helper_set_config() will fall back to a full modeset, using
	 * the @mode_set callback. Since it can't update other planes it's
	 * incompatible with atomic modeset support.
	 *
	 * This callback is only used by the CRTC helpers and deprecated.
	 *
	 * RETURNS:
	 *
	 * 0 on success or a negative error code on failure.
	 */
	पूर्णांक (*mode_set_base)(काष्ठा drm_crtc *crtc, पूर्णांक x, पूर्णांक y,
			     काष्ठा drm_framebuffer *old_fb);

	/**
	 * @mode_set_base_atomic:
	 *
	 * This callback is used by the fbdev helpers to set a new framebuffer
	 * and scanout without sleeping, i.e. from an atomic calling context. It
	 * is only used to implement kgdb support.
	 *
	 * This callback is optional and only needed क्रम kgdb support in the fbdev
	 * helpers.
	 *
	 * RETURNS:
	 *
	 * 0 on success or a negative error code on failure.
	 */
	पूर्णांक (*mode_set_base_atomic)(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_framebuffer *fb, पूर्णांक x, पूर्णांक y,
				    क्रमागत mode_set_atomic);

	/**
	 * @disable:
	 *
	 * This callback should be used to disable the CRTC. With the atomic
	 * drivers it is called after all encoders connected to this CRTC have
	 * been shut off alपढ़ोy using their own
	 * &drm_encoder_helper_funcs.disable hook. If that sequence is too
	 * simple drivers can just add their own hooks and call it from this
	 * CRTC callback here by looping over all encoders connected to it using
	 * क्रम_each_encoder_on_crtc().
	 *
	 * This hook is used both by legacy CRTC helpers and atomic helpers.
	 * Atomic drivers करोn't need to implement it if there's no need to
	 * disable anything at the CRTC level. To ensure that runसमय PM
	 * handling (using either DPMS or the new "ACTIVE" property) works
	 * @disable must be the inverse of @atomic_enable क्रम atomic drivers.
	 * Atomic drivers should consider to use @atomic_disable instead of
	 * this one.
	 *
	 * NOTE:
	 *
	 * With legacy CRTC helpers there's a big semantic dअगरference between
	 * @disable and other hooks (like @prepare or @dpms) used to shut करोwn a
	 * CRTC: @disable is only called when also logically disabling the
	 * display pipeline and needs to release any resources acquired in
	 * @mode_set (like shared PLLs, or again release pinned framebuffers).
	 *
	 * Thereक्रमe @disable must be the inverse of @mode_set plus @commit क्रम
	 * drivers still using legacy CRTC helpers, which is dअगरferent from the
	 * rules under atomic.
	 */
	व्योम (*disable)(काष्ठा drm_crtc *crtc);

	/**
	 * @atomic_check:
	 *
	 * Drivers should check plane-update related CRTC स्थिरraपूर्णांकs in this
	 * hook. They can also check mode related limitations but need to be
	 * aware of the calling order, since this hook is used by
	 * drm_atomic_helper_check_planes() whereas the preparations needed to
	 * check output routing and the display mode is करोne in
	 * drm_atomic_helper_check_modeset(). Thereक्रमe drivers that want to
	 * check output routing and display mode स्थिरraपूर्णांकs in this callback
	 * must ensure that drm_atomic_helper_check_modeset() has been called
	 * beक्रमehand. This is calling order used by the शेष helper
	 * implementation in drm_atomic_helper_check().
	 *
	 * When using drm_atomic_helper_check_planes() this hook is called
	 * after the &drm_plane_helper_funcs.atomic_check hook क्रम planes, which
	 * allows drivers to assign shared resources requested by planes in this
	 * callback here. For more complicated dependencies the driver can call
	 * the provided check helpers multiple बार until the computed state
	 * has a final configuration and everything has been checked.
	 *
	 * This function is also allowed to inspect any other object's state and
	 * can add more state objects to the atomic commit अगर needed. Care must
	 * be taken though to ensure that state check and compute functions क्रम
	 * these added states are all called, and derived state in other objects
	 * all updated. Again the recommendation is to just call check helpers
	 * until a maximal configuration is reached.
	 *
	 * This callback is used by the atomic modeset helpers and by the
	 * transitional plane helpers, but it is optional.
	 *
	 * NOTE:
	 *
	 * This function is called in the check phase of an atomic update. The
	 * driver is not allowed to change anything outside of the मुक्त-standing
	 * state object passed-in.
	 *
	 * Also beware that userspace can request its own custom modes, neither
	 * core nor helpers filter modes to the list of probe modes reported by
	 * the GETCONNECTOR IOCTL and stored in &drm_connector.modes. To ensure
	 * that modes are filtered consistently put any CRTC स्थिरraपूर्णांकs and
	 * limits checks पूर्णांकo @mode_valid.
	 *
	 * RETURNS:
	 *
	 * 0 on success, -EINVAL अगर the state or the transition can't be
	 * supported, -ENOMEM on memory allocation failure and -EDEADLK अगर an
	 * attempt to obtain another state object ran पूर्णांकo a &drm_modeset_lock
	 * deadlock.
	 */
	पूर्णांक (*atomic_check)(काष्ठा drm_crtc *crtc,
			    काष्ठा drm_atomic_state *state);

	/**
	 * @atomic_begin:
	 *
	 * Drivers should prepare क्रम an atomic update of multiple planes on
	 * a CRTC in this hook. Depending upon hardware this might be vblank
	 * evasion, blocking updates by setting bits or करोing preparatory work
	 * क्रम e.g. manual update display.
	 *
	 * This hook is called beक्रमe any plane commit functions are called.
	 *
	 * Note that the घातer state of the display pipe when this function is
	 * called depends upon the exact helpers and calling sequence the driver
	 * has picked. See drm_atomic_helper_commit_planes() क्रम a discussion of
	 * the tradeoffs and variants of plane commit helpers.
	 *
	 * This callback is used by the atomic modeset helpers and by the
	 * transitional plane helpers, but it is optional.
	 */
	व्योम (*atomic_begin)(काष्ठा drm_crtc *crtc,
			     काष्ठा drm_atomic_state *state);
	/**
	 * @atomic_flush:
	 *
	 * Drivers should finalize an atomic update of multiple planes on
	 * a CRTC in this hook. Depending upon hardware this might include
	 * checking that vblank evasion was successful, unblocking updates by
	 * setting bits or setting the GO bit to flush out all updates.
	 *
	 * Simple hardware or hardware with special requirements can commit and
	 * flush out all updates क्रम all planes from this hook and क्रमgo all the
	 * other commit hooks क्रम plane updates.
	 *
	 * This hook is called after any plane commit functions are called.
	 *
	 * Note that the घातer state of the display pipe when this function is
	 * called depends upon the exact helpers and calling sequence the driver
	 * has picked. See drm_atomic_helper_commit_planes() क्रम a discussion of
	 * the tradeoffs and variants of plane commit helpers.
	 *
	 * This callback is used by the atomic modeset helpers and by the
	 * transitional plane helpers, but it is optional.
	 */
	व्योम (*atomic_flush)(काष्ठा drm_crtc *crtc,
			     काष्ठा drm_atomic_state *state);

	/**
	 * @atomic_enable:
	 *
	 * This callback should be used to enable the CRTC. With the atomic
	 * drivers it is called beक्रमe all encoders connected to this CRTC are
	 * enabled through the encoder's own &drm_encoder_helper_funcs.enable
	 * hook.  If that sequence is too simple drivers can just add their own
	 * hooks and call it from this CRTC callback here by looping over all
	 * encoders connected to it using क्रम_each_encoder_on_crtc().
	 *
	 * This hook is used only by atomic helpers, क्रम symmetry with
	 * @atomic_disable. Atomic drivers करोn't need to implement it if there's
	 * no need to enable anything at the CRTC level. To ensure that runसमय
	 * PM handling (using either DPMS or the new "ACTIVE" property) works
	 * @atomic_enable must be the inverse of @atomic_disable क्रम atomic
	 * drivers.
	 *
	 * This function is optional.
	 */
	व्योम (*atomic_enable)(काष्ठा drm_crtc *crtc,
			      काष्ठा drm_atomic_state *state);

	/**
	 * @atomic_disable:
	 *
	 * This callback should be used to disable the CRTC. With the atomic
	 * drivers it is called after all encoders connected to this CRTC have
	 * been shut off alपढ़ोy using their own
	 * &drm_encoder_helper_funcs.disable hook. If that sequence is too
	 * simple drivers can just add their own hooks and call it from this
	 * CRTC callback here by looping over all encoders connected to it using
	 * क्रम_each_encoder_on_crtc().
	 *
	 * This hook is used only by atomic helpers. Atomic drivers करोn't
	 * need to implement it अगर there's no need to disable anything at the
	 * CRTC level.
	 *
	 * This function is optional.
	 */
	व्योम (*atomic_disable)(काष्ठा drm_crtc *crtc,
			       काष्ठा drm_atomic_state *state);

	/**
	 * @get_scanout_position:
	 *
	 * Called by vblank बारtamping code.
	 *
	 * Returns the current display scanout position from a CRTC and an
	 * optional accurate kसमय_get() बारtamp of when the position was
	 * measured. Note that this is a helper callback which is only used
	 * अगर a driver uses drm_crtc_vblank_helper_get_vblank_बारtamp()
	 * क्रम the @drm_crtc_funcs.get_vblank_बारtamp callback.
	 *
	 * Parameters:
	 *
	 * crtc:
	 *     The CRTC.
	 * in_vblank_irq:
	 *     True when called from drm_crtc_handle_vblank(). Some drivers
	 *     need to apply some workarounds क्रम gpu-specअगरic vblank irq
	 *     quirks अगर the flag is set.
	 * vpos:
	 *     Target location क्रम current vertical scanout position.
	 * hpos:
	 *     Target location क्रम current horizontal scanout position.
	 * sसमय:
	 *     Target location क्रम बारtamp taken immediately beक्रमe
	 *     scanout position query. Can be शून्य to skip बारtamp.
	 * eसमय:
	 *     Target location क्रम बारtamp taken immediately after
	 *     scanout position query. Can be शून्य to skip बारtamp.
	 * mode:
	 *     Current display timings.
	 *
	 * Returns vpos as a positive number जबतक in active scanout area.
	 * Returns vpos as a negative number inside vblank, counting the number
	 * of scanlines to go until end of vblank, e.g., -1 means "one scanline
	 * until start of active scanout / end of vblank."
	 *
	 * Returns:
	 *
	 * True on success, false अगर a reliable scanout position counter could
	 * not be पढ़ो out.
	 */
	bool (*get_scanout_position)(काष्ठा drm_crtc *crtc,
				     bool in_vblank_irq, पूर्णांक *vpos, पूर्णांक *hpos,
				     kसमय_प्रकार *sसमय, kसमय_प्रकार *eसमय,
				     स्थिर काष्ठा drm_display_mode *mode);
पूर्ण;

/**
 * drm_crtc_helper_add - sets the helper vtable क्रम a crtc
 * @crtc: DRM CRTC
 * @funcs: helper vtable to set क्रम @crtc
 */
अटल अंतरभूत व्योम drm_crtc_helper_add(काष्ठा drm_crtc *crtc,
				       स्थिर काष्ठा drm_crtc_helper_funcs *funcs)
अणु
	crtc->helper_निजी = funcs;
पूर्ण

/**
 * काष्ठा drm_encoder_helper_funcs - helper operations क्रम encoders
 *
 * These hooks are used by the legacy CRTC helpers, the transitional plane
 * helpers and the new atomic modesetting helpers.
 */
काष्ठा drm_encoder_helper_funcs अणु
	/**
	 * @dpms:
	 *
	 * Callback to control घातer levels on the encoder.  If the mode passed in
	 * is unsupported, the provider must use the next lowest घातer level.
	 * This is used by the legacy encoder helpers to implement DPMS
	 * functionality in drm_helper_connector_dpms().
	 *
	 * This callback is also used to disable an encoder by calling it with
	 * DRM_MODE_DPMS_OFF अगर the @disable hook isn't used.
	 *
	 * This callback is used by the legacy CRTC helpers.  Atomic helpers
	 * also support using this hook क्रम enabling and disabling an encoder to
	 * facilitate transitions to atomic, but it is deprecated. Instead
	 * @enable and @disable should be used.
	 */
	व्योम (*dpms)(काष्ठा drm_encoder *encoder, पूर्णांक mode);

	/**
	 * @mode_valid:
	 *
	 * This callback is used to check अगर a specअगरic mode is valid in this
	 * encoder. This should be implemented अगर the encoder has some sort
	 * of restriction in the modes it can display. For example, a given
	 * encoder may be responsible to set a घड़ी value. If the घड़ी can
	 * not produce all the values क्रम the available modes then this callback
	 * can be used to restrict the number of modes to only the ones that
	 * can be displayed.
	 *
	 * This hook is used by the probe helpers to filter the mode list in
	 * drm_helper_probe_single_connector_modes(), and it is used by the
	 * atomic helpers to validate modes supplied by userspace in
	 * drm_atomic_helper_check_modeset().
	 *
	 * This function is optional.
	 *
	 * NOTE:
	 *
	 * Since this function is both called from the check phase of an atomic
	 * commit, and the mode validation in the probe paths it is not allowed
	 * to look at anything अन्यथा but the passed-in mode, and validate it
	 * against configuration-invariant hardward स्थिरraपूर्णांकs. Any further
	 * limits which depend upon the configuration can only be checked in
	 * @mode_fixup or @atomic_check.
	 *
	 * RETURNS:
	 *
	 * drm_mode_status Enum
	 */
	क्रमागत drm_mode_status (*mode_valid)(काष्ठा drm_encoder *crtc,
					   स्थिर काष्ठा drm_display_mode *mode);

	/**
	 * @mode_fixup:
	 *
	 * This callback is used to validate and adjust a mode. The parameter
	 * mode is the display mode that should be fed to the next element in
	 * the display chain, either the final &drm_connector or a &drm_bridge.
	 * The parameter adjusted_mode is the input mode the encoder requires. It
	 * can be modअगरied by this callback and करोes not need to match mode. See
	 * also &drm_crtc_state.adjusted_mode क्रम more details.
	 *
	 * This function is used by both legacy CRTC helpers and atomic helpers.
	 * This hook is optional.
	 *
	 * NOTE:
	 *
	 * This function is called in the check phase of atomic modesets, which
	 * can be पातed क्रम any reason (including on userspace's request to
	 * just check whether a configuration would be possible). Atomic drivers
	 * MUST NOT touch any persistent state (hardware or software) or data
	 * काष्ठाures except the passed in adjusted_mode parameter.
	 *
	 * This is in contrast to the legacy CRTC helpers where this was
	 * allowed.
	 *
	 * Atomic drivers which need to inspect and adjust more state should
	 * instead use the @atomic_check callback. If @atomic_check is used,
	 * this hook isn't called since @atomic_check allows a strict superset
	 * of the functionality of @mode_fixup.
	 *
	 * Also beware that userspace can request its own custom modes, neither
	 * core nor helpers filter modes to the list of probe modes reported by
	 * the GETCONNECTOR IOCTL and stored in &drm_connector.modes. To ensure
	 * that modes are filtered consistently put any encoder स्थिरraपूर्णांकs and
	 * limits checks पूर्णांकo @mode_valid.
	 *
	 * RETURNS:
	 *
	 * True अगर an acceptable configuration is possible, false अगर the modeset
	 * operation should be rejected.
	 */
	bool (*mode_fixup)(काष्ठा drm_encoder *encoder,
			   स्थिर काष्ठा drm_display_mode *mode,
			   काष्ठा drm_display_mode *adjusted_mode);

	/**
	 * @prepare:
	 *
	 * This callback should prepare the encoder क्रम a subsequent modeset,
	 * which in practice means the driver should disable the encoder अगर it
	 * is running. Most drivers ended up implementing this by calling their
	 * @dpms hook with DRM_MODE_DPMS_OFF.
	 *
	 * This callback is used by the legacy CRTC helpers.  Atomic helpers
	 * also support using this hook क्रम disabling an encoder to facilitate
	 * transitions to atomic, but it is deprecated. Instead @disable should
	 * be used.
	 */
	व्योम (*prepare)(काष्ठा drm_encoder *encoder);

	/**
	 * @commit:
	 *
	 * This callback should commit the new mode on the encoder after a modeset,
	 * which in practice means the driver should enable the encoder.  Most
	 * drivers ended up implementing this by calling their @dpms hook with
	 * DRM_MODE_DPMS_ON.
	 *
	 * This callback is used by the legacy CRTC helpers.  Atomic helpers
	 * also support using this hook क्रम enabling an encoder to facilitate
	 * transitions to atomic, but it is deprecated. Instead @enable should
	 * be used.
	 */
	व्योम (*commit)(काष्ठा drm_encoder *encoder);

	/**
	 * @mode_set:
	 *
	 * This callback is used to update the display mode of an encoder.
	 *
	 * Note that the display pipe is completely off when this function is
	 * called. Drivers which need hardware to be running beक्रमe they program
	 * the new display mode (because they implement runसमय PM) should not
	 * use this hook, because the helper library calls it only once and not
	 * every समय the display pipeline is suspend using either DPMS or the
	 * new "ACTIVE" property. Such drivers should instead move all their
	 * encoder setup पूर्णांकo the @enable callback.
	 *
	 * This callback is used both by the legacy CRTC helpers and the atomic
	 * modeset helpers. It is optional in the atomic helpers.
	 *
	 * NOTE:
	 *
	 * If the driver uses the atomic modeset helpers and needs to inspect
	 * the connector state or connector display info during mode setting,
	 * @atomic_mode_set can be used instead.
	 */
	व्योम (*mode_set)(काष्ठा drm_encoder *encoder,
			 काष्ठा drm_display_mode *mode,
			 काष्ठा drm_display_mode *adjusted_mode);

	/**
	 * @atomic_mode_set:
	 *
	 * This callback is used to update the display mode of an encoder.
	 *
	 * Note that the display pipe is completely off when this function is
	 * called. Drivers which need hardware to be running beक्रमe they program
	 * the new display mode (because they implement runसमय PM) should not
	 * use this hook, because the helper library calls it only once and not
	 * every समय the display pipeline is suspended using either DPMS or the
	 * new "ACTIVE" property. Such drivers should instead move all their
	 * encoder setup पूर्णांकo the @enable callback.
	 *
	 * This callback is used by the atomic modeset helpers in place of the
	 * @mode_set callback, अगर set by the driver. It is optional and should
	 * be used instead of @mode_set अगर the driver needs to inspect the
	 * connector state or display info, since there is no direct way to
	 * go from the encoder to the current connector.
	 */
	व्योम (*atomic_mode_set)(काष्ठा drm_encoder *encoder,
				काष्ठा drm_crtc_state *crtc_state,
				काष्ठा drm_connector_state *conn_state);

	/**
	 * @detect:
	 *
	 * This callback can be used by drivers who want to करो detection on the
	 * encoder object instead of in connector functions.
	 *
	 * It is not used by any helper and thereक्रमe has purely driver-specअगरic
	 * semantics. New drivers shouldn't use this and instead just implement
	 * their own निजी callbacks.
	 *
	 * FIXME:
	 *
	 * This should just be converted पूर्णांकo a pile of driver vfuncs.
	 * Currently radeon, amdgpu and nouveau are using it.
	 */
	क्रमागत drm_connector_status (*detect)(काष्ठा drm_encoder *encoder,
					    काष्ठा drm_connector *connector);

	/**
	 * @atomic_disable:
	 *
	 * This callback should be used to disable the encoder. With the atomic
	 * drivers it is called beक्रमe this encoder's CRTC has been shut off
	 * using their own &drm_crtc_helper_funcs.atomic_disable hook. If that
	 * sequence is too simple drivers can just add their own driver निजी
	 * encoder hooks and call them from CRTC's callback by looping over all
	 * encoders connected to it using क्रम_each_encoder_on_crtc().
	 *
	 * This callback is a variant of @disable that provides the atomic state
	 * to the driver. If @atomic_disable is implemented, @disable is not
	 * called by the helpers.
	 *
	 * This hook is only used by atomic helpers. Atomic drivers करोn't need
	 * to implement it अगर there's no need to disable anything at the encoder
	 * level. To ensure that runसमय PM handling (using either DPMS or the
	 * new "ACTIVE" property) works @atomic_disable must be the inverse of
	 * @atomic_enable.
	 */
	व्योम (*atomic_disable)(काष्ठा drm_encoder *encoder,
			       काष्ठा drm_atomic_state *state);

	/**
	 * @atomic_enable:
	 *
	 * This callback should be used to enable the encoder. It is called
	 * after this encoder's CRTC has been enabled using their own
	 * &drm_crtc_helper_funcs.atomic_enable hook. If that sequence is
	 * too simple drivers can just add their own driver निजी encoder
	 * hooks and call them from CRTC's callback by looping over all encoders
	 * connected to it using क्रम_each_encoder_on_crtc().
	 *
	 * This callback is a variant of @enable that provides the atomic state
	 * to the driver. If @atomic_enable is implemented, @enable is not
	 * called by the helpers.
	 *
	 * This hook is only used by atomic helpers, it is the opposite of
	 * @atomic_disable. Atomic drivers करोn't need to implement it if there's
	 * no need to enable anything at the encoder level. To ensure that
	 * runसमय PM handling works @atomic_enable must be the inverse of
	 * @atomic_disable.
	 */
	व्योम (*atomic_enable)(काष्ठा drm_encoder *encoder,
			      काष्ठा drm_atomic_state *state);

	/**
	 * @disable:
	 *
	 * This callback should be used to disable the encoder. With the atomic
	 * drivers it is called beक्रमe this encoder's CRTC has been shut off
	 * using their own &drm_crtc_helper_funcs.disable hook.  If that
	 * sequence is too simple drivers can just add their own driver निजी
	 * encoder hooks and call them from CRTC's callback by looping over all
	 * encoders connected to it using क्रम_each_encoder_on_crtc().
	 *
	 * This hook is used both by legacy CRTC helpers and atomic helpers.
	 * Atomic drivers करोn't need to implement it if there's no need to
	 * disable anything at the encoder level. To ensure that runसमय PM
	 * handling (using either DPMS or the new "ACTIVE" property) works
	 * @disable must be the inverse of @enable क्रम atomic drivers.
	 *
	 * For atomic drivers also consider @atomic_disable and save yourself
	 * from having to पढ़ो the NOTE below!
	 *
	 * NOTE:
	 *
	 * With legacy CRTC helpers there's a big semantic dअगरference between
	 * @disable and other hooks (like @prepare or @dpms) used to shut करोwn a
	 * encoder: @disable is only called when also logically disabling the
	 * display pipeline and needs to release any resources acquired in
	 * @mode_set (like shared PLLs, or again release pinned framebuffers).
	 *
	 * Thereक्रमe @disable must be the inverse of @mode_set plus @commit क्रम
	 * drivers still using legacy CRTC helpers, which is dअगरferent from the
	 * rules under atomic.
	 */
	व्योम (*disable)(काष्ठा drm_encoder *encoder);

	/**
	 * @enable:
	 *
	 * This callback should be used to enable the encoder. With the atomic
	 * drivers it is called after this encoder's CRTC has been enabled using
	 * their own &drm_crtc_helper_funcs.enable hook.  If that sequence is
	 * too simple drivers can just add their own driver निजी encoder
	 * hooks and call them from CRTC's callback by looping over all encoders
	 * connected to it using क्रम_each_encoder_on_crtc().
	 *
	 * This hook is only used by atomic helpers, it is the opposite of
	 * @disable. Atomic drivers करोn't need to implement it if there's no
	 * need to enable anything at the encoder level. To ensure that
	 * runसमय PM handling (using either DPMS or the new "ACTIVE" property)
	 * works @enable must be the inverse of @disable क्रम atomic drivers.
	 */
	व्योम (*enable)(काष्ठा drm_encoder *encoder);

	/**
	 * @atomic_check:
	 *
	 * This callback is used to validate encoder state क्रम atomic drivers.
	 * Since the encoder is the object connecting the CRTC and connector it
	 * माला_लो passed both states, to be able to validate पूर्णांकeractions and
	 * update the CRTC to match what the encoder needs क्रम the requested
	 * connector.
	 *
	 * Since this provides a strict superset of the functionality of
	 * @mode_fixup (the requested and adjusted modes are both available
	 * through the passed in &काष्ठा drm_crtc_state) @mode_fixup is not
	 * called when @atomic_check is implemented.
	 *
	 * This function is used by the atomic helpers, but it is optional.
	 *
	 * NOTE:
	 *
	 * This function is called in the check phase of an atomic update. The
	 * driver is not allowed to change anything outside of the मुक्त-standing
	 * state objects passed-in or assembled in the overall &drm_atomic_state
	 * update tracking काष्ठाure.
	 *
	 * Also beware that userspace can request its own custom modes, neither
	 * core nor helpers filter modes to the list of probe modes reported by
	 * the GETCONNECTOR IOCTL and stored in &drm_connector.modes. To ensure
	 * that modes are filtered consistently put any encoder स्थिरraपूर्णांकs and
	 * limits checks पूर्णांकo @mode_valid.
	 *
	 * RETURNS:
	 *
	 * 0 on success, -EINVAL अगर the state or the transition can't be
	 * supported, -ENOMEM on memory allocation failure and -EDEADLK अगर an
	 * attempt to obtain another state object ran पूर्णांकo a &drm_modeset_lock
	 * deadlock.
	 */
	पूर्णांक (*atomic_check)(काष्ठा drm_encoder *encoder,
			    काष्ठा drm_crtc_state *crtc_state,
			    काष्ठा drm_connector_state *conn_state);
पूर्ण;

/**
 * drm_encoder_helper_add - sets the helper vtable क्रम an encoder
 * @encoder: DRM encoder
 * @funcs: helper vtable to set क्रम @encoder
 */
अटल अंतरभूत व्योम drm_encoder_helper_add(काष्ठा drm_encoder *encoder,
					  स्थिर काष्ठा drm_encoder_helper_funcs *funcs)
अणु
	encoder->helper_निजी = funcs;
पूर्ण

/**
 * काष्ठा drm_connector_helper_funcs - helper operations क्रम connectors
 *
 * These functions are used by the atomic and legacy modeset helpers and by the
 * probe helpers.
 */
काष्ठा drm_connector_helper_funcs अणु
	/**
	 * @get_modes:
	 *
	 * This function should fill in all modes currently valid क्रम the sink
	 * पूर्णांकo the &drm_connector.probed_modes list. It should also update the
	 * EDID property by calling drm_connector_update_edid_property().
	 *
	 * The usual way to implement this is to cache the EDID retrieved in the
	 * probe callback somewhere in the driver-निजी connector काष्ठाure.
	 * In this function drivers then parse the modes in the EDID and add
	 * them by calling drm_add_edid_modes(). But connectors that drive a
	 * fixed panel can also manually add specअगरic modes using
	 * drm_mode_probed_add(). Drivers which manually add modes should also
	 * make sure that the &drm_connector.display_info,
	 * &drm_connector.width_mm and &drm_connector.height_mm fields are
	 * filled in.
	 *
	 * Note that the caller function will स्वतःmatically add standard VESA
	 * DMT modes up to 1024x768 अगर the .get_modes() helper operation वापसs
	 * no mode and अगर the connector status is connector_status_connected or
	 * connector_status_unknown. There is no need to call
	 * drm_add_modes_noedid() manually in that हाल.
	 *
	 * Virtual drivers that just want some standard VESA mode with a given
	 * resolution can call drm_add_modes_noedid(), and mark the preferred
	 * one using drm_set_preferred_mode().
	 *
	 * This function is only called after the @detect hook has indicated
	 * that a sink is connected and when the EDID isn't overridden through
	 * sysfs or the kernel commandline.
	 *
	 * This callback is used by the probe helpers in e.g.
	 * drm_helper_probe_single_connector_modes().
	 *
	 * To aव्योम races with concurrent connector state updates, the helper
	 * libraries always call this with the &drm_mode_config.connection_mutex
	 * held. Because of this it's safe to inspect &drm_connector->state.
	 *
	 * RETURNS:
	 *
	 * The number of modes added by calling drm_mode_probed_add().
	 */
	पूर्णांक (*get_modes)(काष्ठा drm_connector *connector);

	/**
	 * @detect_ctx:
	 *
	 * Check to see अगर anything is attached to the connector. The parameter
	 * क्रमce is set to false whilst polling, true when checking the
	 * connector due to a user request. क्रमce can be used by the driver to
	 * aव्योम expensive, deकाष्ठाive operations during स्वतःmated probing.
	 *
	 * This callback is optional, अगर not implemented the connector will be
	 * considered as always being attached.
	 *
	 * This is the atomic version of &drm_connector_funcs.detect.
	 *
	 * To aव्योम races against concurrent connector state updates, the
	 * helper libraries always call this with ctx set to a valid context,
	 * and &drm_mode_config.connection_mutex will always be locked with
	 * the ctx parameter set to this ctx. This allows taking additional
	 * locks as required.
	 *
	 * RETURNS:
	 *
	 * &drm_connector_status indicating the connector's status,
	 * or the error code वापसed by drm_modeset_lock(), -EDEADLK.
	 */
	पूर्णांक (*detect_ctx)(काष्ठा drm_connector *connector,
			  काष्ठा drm_modeset_acquire_ctx *ctx,
			  bool क्रमce);

	/**
	 * @mode_valid:
	 *
	 * Callback to validate a mode क्रम a connector, irrespective of the
	 * specअगरic display configuration.
	 *
	 * This callback is used by the probe helpers to filter the mode list
	 * (which is usually derived from the EDID data block from the sink).
	 * See e.g. drm_helper_probe_single_connector_modes().
	 *
	 * This function is optional.
	 *
	 * NOTE:
	 *
	 * This only filters the mode list supplied to userspace in the
	 * GETCONNECTOR IOCTL. Compared to &drm_encoder_helper_funcs.mode_valid,
	 * &drm_crtc_helper_funcs.mode_valid and &drm_bridge_funcs.mode_valid,
	 * which are also called by the atomic helpers from
	 * drm_atomic_helper_check_modeset(). This allows userspace to क्रमce and
	 * ignore sink स्थिरraपूर्णांक (like the pixel घड़ी limits in the screen's
	 * EDID), which is useful क्रम e.g. testing, or working around a broken
	 * EDID. Any source hardware स्थिरraपूर्णांक (which always need to be
	 * enक्रमced) thereक्रमe should be checked in one of the above callbacks,
	 * and not this one here.
	 *
	 * To aव्योम races with concurrent connector state updates, the helper
	 * libraries always call this with the &drm_mode_config.connection_mutex
	 * held. Because of this it's safe to inspect &drm_connector->state.
         *
	 * RETURNS:
	 *
	 * Either &drm_mode_status.MODE_OK or one of the failure reasons in &क्रमागत
	 * drm_mode_status.
	 */
	क्रमागत drm_mode_status (*mode_valid)(काष्ठा drm_connector *connector,
					   काष्ठा drm_display_mode *mode);

	/**
	 * @mode_valid_ctx:
	 *
	 * Callback to validate a mode क्रम a connector, irrespective of the
	 * specअगरic display configuration.
	 *
	 * This callback is used by the probe helpers to filter the mode list
	 * (which is usually derived from the EDID data block from the sink).
	 * See e.g. drm_helper_probe_single_connector_modes().
	 *
	 * This function is optional, and is the atomic version of
	 * &drm_connector_helper_funcs.mode_valid.
	 *
	 * To allow क्रम accessing the atomic state of modesetting objects, the
	 * helper libraries always call this with ctx set to a valid context,
	 * and &drm_mode_config.connection_mutex will always be locked with
	 * the ctx parameter set to @ctx. This allows क्रम taking additional
	 * locks as required.
	 *
	 * Even though additional locks may be acquired, this callback is
	 * still expected not to take any स्थिरraपूर्णांकs पूर्णांकo account which would
	 * be influenced by the currently set display state - such स्थिरraपूर्णांकs
	 * should be handled in the driver's atomic check. For example, अगर a
	 * connector shares display bandwidth with other connectors then it
	 * would be ok to validate the minimum bandwidth requirement of a mode
	 * against the maximum possible bandwidth of the connector. But it
	 * wouldn't be ok to take the current bandwidth usage of other
	 * connectors पूर्णांकo account, as this would change depending on the
	 * display state.
	 *
	 * Returns:
	 * 0 अगर &drm_connector_helper_funcs.mode_valid_ctx succeeded and wrote
	 * the &क्रमागत drm_mode_status value to @status, or a negative error
	 * code otherwise.
	 *
	 */
	पूर्णांक (*mode_valid_ctx)(काष्ठा drm_connector *connector,
			      काष्ठा drm_display_mode *mode,
			      काष्ठा drm_modeset_acquire_ctx *ctx,
			      क्रमागत drm_mode_status *status);

	/**
	 * @best_encoder:
	 *
	 * This function should select the best encoder क्रम the given connector.
	 *
	 * This function is used by both the atomic helpers (in the
	 * drm_atomic_helper_check_modeset() function) and in the legacy CRTC
	 * helpers.
	 *
	 * NOTE:
	 *
	 * In atomic drivers this function is called in the check phase of an
	 * atomic update. The driver is not allowed to change or inspect
	 * anything outside of arguments passed-in. Atomic drivers which need to
	 * inspect dynamic configuration state should instead use
	 * @atomic_best_encoder.
	 *
	 * You can leave this function to शून्य अगर the connector is only
	 * attached to a single encoder. In this हाल, the core will call
	 * drm_connector_get_single_encoder() क्रम you.
	 *
	 * RETURNS:
	 *
	 * Encoder that should be used क्रम the given connector and connector
	 * state, or शून्य अगर no suitable encoder exists. Note that the helpers
	 * will ensure that encoders aren't used twice, drivers should not check
	 * क्रम this.
	 */
	काष्ठा drm_encoder *(*best_encoder)(काष्ठा drm_connector *connector);

	/**
	 * @atomic_best_encoder:
	 *
	 * This is the atomic version of @best_encoder क्रम atomic drivers which
	 * need to select the best encoder depending upon the desired
	 * configuration and can't select it अटलally.
	 *
	 * This function is used by drm_atomic_helper_check_modeset().
	 * If it is not implemented, the core will fallback to @best_encoder
	 * (or drm_connector_get_single_encoder() अगर @best_encoder is शून्य).
	 *
	 * NOTE:
	 *
	 * This function is called in the check phase of an atomic update. The
	 * driver is not allowed to change anything outside of the
	 * &drm_atomic_state update tracking काष्ठाure passed in.
	 *
	 * RETURNS:
	 *
	 * Encoder that should be used क्रम the given connector and connector
	 * state, or शून्य अगर no suitable encoder exists. Note that the helpers
	 * will ensure that encoders aren't used twice, drivers should not check
	 * क्रम this.
	 */
	काष्ठा drm_encoder *(*atomic_best_encoder)(काष्ठा drm_connector *connector,
						   काष्ठा drm_atomic_state *state);

	/**
	 * @atomic_check:
	 *
	 * This hook is used to validate connector state. This function is
	 * called from &drm_atomic_helper_check_modeset, and is called when
	 * a connector property is set, or a modeset on the crtc is क्रमced.
	 *
	 * Because &drm_atomic_helper_check_modeset may be called multiple बार,
	 * this function should handle being called multiple बार as well.
	 *
	 * This function is also allowed to inspect any other object's state and
	 * can add more state objects to the atomic commit अगर needed. Care must
	 * be taken though to ensure that state check and compute functions क्रम
	 * these added states are all called, and derived state in other objects
	 * all updated. Again the recommendation is to just call check helpers
	 * until a maximal configuration is reached.
	 *
	 * NOTE:
	 *
	 * This function is called in the check phase of an atomic update. The
	 * driver is not allowed to change anything outside of the मुक्त-standing
	 * state objects passed-in or assembled in the overall &drm_atomic_state
	 * update tracking काष्ठाure.
	 *
	 * RETURNS:
	 *
	 * 0 on success, -EINVAL अगर the state or the transition can't be
	 * supported, -ENOMEM on memory allocation failure and -EDEADLK अगर an
	 * attempt to obtain another state object ran पूर्णांकo a &drm_modeset_lock
	 * deadlock.
	 */
	पूर्णांक (*atomic_check)(काष्ठा drm_connector *connector,
			    काष्ठा drm_atomic_state *state);

	/**
	 * @atomic_commit:
	 *
	 * This hook is to be used by drivers implementing ग_लिखोback connectors
	 * that need a poपूर्णांक when to commit the ग_लिखोback job to the hardware.
	 * The ग_लिखोback_job to commit is available in the new connector state,
	 * in &drm_connector_state.ग_लिखोback_job.
	 *
	 * This hook is optional.
	 *
	 * This callback is used by the atomic modeset helpers.
	 */
	व्योम (*atomic_commit)(काष्ठा drm_connector *connector,
			      काष्ठा drm_atomic_state *state);

	/**
	 * @prepare_ग_लिखोback_job:
	 *
	 * As ग_लिखोback jobs contain a framebuffer, drivers may need to
	 * prepare and clean them up the same way they can prepare and
	 * clean up framebuffers क्रम planes. This optional connector operation
	 * is used to support the preparation of ग_लिखोback jobs. The job
	 * prepare operation is called from drm_atomic_helper_prepare_planes()
	 * क्रम काष्ठा &drm_ग_लिखोback_connector connectors only.
	 *
	 * This operation is optional.
	 *
	 * This callback is used by the atomic modeset helpers.
	 */
	पूर्णांक (*prepare_ग_लिखोback_job)(काष्ठा drm_ग_लिखोback_connector *connector,
				     काष्ठा drm_ग_लिखोback_job *job);
	/**
	 * @cleanup_ग_लिखोback_job:
	 *
	 * This optional connector operation is used to support the
	 * cleanup of ग_लिखोback jobs. The job cleanup operation is called
	 * from the existing drm_ग_लिखोback_cleanup_job() function, invoked
	 * both when destroying the job as part of an पातed commit, or when
	 * the job completes.
	 *
	 * This operation is optional.
	 *
	 * This callback is used by the atomic modeset helpers.
	 */
	व्योम (*cleanup_ग_लिखोback_job)(काष्ठा drm_ग_लिखोback_connector *connector,
				      काष्ठा drm_ग_लिखोback_job *job);
पूर्ण;

/**
 * drm_connector_helper_add - sets the helper vtable क्रम a connector
 * @connector: DRM connector
 * @funcs: helper vtable to set क्रम @connector
 */
अटल अंतरभूत व्योम drm_connector_helper_add(काष्ठा drm_connector *connector,
					    स्थिर काष्ठा drm_connector_helper_funcs *funcs)
अणु
	connector->helper_निजी = funcs;
पूर्ण

/**
 * काष्ठा drm_plane_helper_funcs - helper operations क्रम planes
 *
 * These functions are used by the atomic helpers and by the transitional plane
 * helpers.
 */
काष्ठा drm_plane_helper_funcs अणु
	/**
	 * @prepare_fb:
	 *
	 * This hook is to prepare a framebuffer क्रम scanout by e.g. pinning
	 * its backing storage or relocating it पूर्णांकo a contiguous block of
	 * VRAM. Other possible preparatory work includes flushing caches.
	 *
	 * This function must not block क्रम outstanding rendering, since it is
	 * called in the context of the atomic IOCTL even क्रम async commits to
	 * be able to वापस any errors to userspace. Instead the recommended
	 * way is to fill out the &drm_plane_state.fence of the passed-in
	 * &drm_plane_state. If the driver करोesn't support native fences then
	 * equivalent functionality should be implemented through निजी
	 * members in the plane काष्ठाure.
	 *
	 * Drivers which always have their buffers pinned should use
	 * drm_gem_plane_helper_prepare_fb() क्रम this hook.
	 *
	 * The helpers will call @cleanup_fb with matching arguments क्रम every
	 * successful call to this hook.
	 *
	 * This callback is used by the atomic modeset helpers and by the
	 * transitional plane helpers, but it is optional.
	 *
	 * RETURNS:
	 *
	 * 0 on success or one of the following negative error codes allowed by
	 * the &drm_mode_config_funcs.atomic_commit vfunc. When using helpers
	 * this callback is the only one which can fail an atomic commit,
	 * everything अन्यथा must complete successfully.
	 */
	पूर्णांक (*prepare_fb)(काष्ठा drm_plane *plane,
			  काष्ठा drm_plane_state *new_state);
	/**
	 * @cleanup_fb:
	 *
	 * This hook is called to clean up any resources allocated क्रम the given
	 * framebuffer and plane configuration in @prepare_fb.
	 *
	 * This callback is used by the atomic modeset helpers and by the
	 * transitional plane helpers, but it is optional.
	 */
	व्योम (*cleanup_fb)(काष्ठा drm_plane *plane,
			   काष्ठा drm_plane_state *old_state);

	/**
	 * @atomic_check:
	 *
	 * Drivers should check plane specअगरic स्थिरraपूर्णांकs in this hook.
	 *
	 * When using drm_atomic_helper_check_planes() plane's @atomic_check
	 * hooks are called beक्रमe the ones क्रम CRTCs, which allows drivers to
	 * request shared resources that the CRTC controls here. For more
	 * complicated dependencies the driver can call the provided check helpers
	 * multiple बार until the computed state has a final configuration and
	 * everything has been checked.
	 *
	 * This function is also allowed to inspect any other object's state and
	 * can add more state objects to the atomic commit अगर needed. Care must
	 * be taken though to ensure that state check and compute functions क्रम
	 * these added states are all called, and derived state in other objects
	 * all updated. Again the recommendation is to just call check helpers
	 * until a maximal configuration is reached.
	 *
	 * This callback is used by the atomic modeset helpers and by the
	 * transitional plane helpers, but it is optional.
	 *
	 * NOTE:
	 *
	 * This function is called in the check phase of an atomic update. The
	 * driver is not allowed to change anything outside of the
	 * &drm_atomic_state update tracking काष्ठाure.
	 *
	 * RETURNS:
	 *
	 * 0 on success, -EINVAL अगर the state or the transition can't be
	 * supported, -ENOMEM on memory allocation failure and -EDEADLK अगर an
	 * attempt to obtain another state object ran पूर्णांकo a &drm_modeset_lock
	 * deadlock.
	 */
	पूर्णांक (*atomic_check)(काष्ठा drm_plane *plane,
			    काष्ठा drm_atomic_state *state);

	/**
	 * @atomic_update:
	 *
	 * Drivers should use this function to update the plane state.  This
	 * hook is called in-between the &drm_crtc_helper_funcs.atomic_begin and
	 * drm_crtc_helper_funcs.atomic_flush callbacks.
	 *
	 * Note that the घातer state of the display pipe when this function is
	 * called depends upon the exact helpers and calling sequence the driver
	 * has picked. See drm_atomic_helper_commit_planes() क्रम a discussion of
	 * the tradeoffs and variants of plane commit helpers.
	 *
	 * This callback is used by the atomic modeset helpers and by the
	 * transitional plane helpers, but it is optional.
	 */
	व्योम (*atomic_update)(काष्ठा drm_plane *plane,
			      काष्ठा drm_atomic_state *state);
	/**
	 * @atomic_disable:
	 *
	 * Drivers should use this function to unconditionally disable a plane.
	 * This hook is called in-between the
	 * &drm_crtc_helper_funcs.atomic_begin and
	 * drm_crtc_helper_funcs.atomic_flush callbacks. It is an alternative to
	 * @atomic_update, which will be called क्रम disabling planes, too, अगर
	 * the @atomic_disable hook isn't implemented.
	 *
	 * This hook is also useful to disable planes in preparation of a modeset,
	 * by calling drm_atomic_helper_disable_planes_on_crtc() from the
	 * &drm_crtc_helper_funcs.disable hook.
	 *
	 * Note that the घातer state of the display pipe when this function is
	 * called depends upon the exact helpers and calling sequence the driver
	 * has picked. See drm_atomic_helper_commit_planes() क्रम a discussion of
	 * the tradeoffs and variants of plane commit helpers.
	 *
	 * This callback is used by the atomic modeset helpers and by the
	 * transitional plane helpers, but it is optional.
	 */
	व्योम (*atomic_disable)(काष्ठा drm_plane *plane,
			       काष्ठा drm_atomic_state *state);

	/**
	 * @atomic_async_check:
	 *
	 * Drivers should set this function poपूर्णांकer to check अगर the plane's
	 * atomic state can be updated in a async fashion. Here async means
	 * "not vblank synchronized".
	 *
	 * This hook is called by drm_atomic_async_check() to establish अगर a
	 * given update can be committed asynchronously, that is, अगर it can
	 * jump ahead of the state currently queued क्रम update.
	 *
	 * RETURNS:
	 *
	 * Return 0 on success and any error वापसed indicates that the update
	 * can not be applied in asynchronous manner.
	 */
	पूर्णांक (*atomic_async_check)(काष्ठा drm_plane *plane,
				  काष्ठा drm_atomic_state *state);

	/**
	 * @atomic_async_update:
	 *
	 * Drivers should set this function poपूर्णांकer to perक्रमm asynchronous
	 * updates of planes, that is, jump ahead of the currently queued
	 * state and update the plane. Here async means "not vblank
	 * synchronized".
	 *
	 * This hook is called by drm_atomic_helper_async_commit().
	 *
	 * An async update will happen on legacy cursor updates. An async
	 * update won't happen अगर there is an outstanding commit modअगरying
	 * the same plane.
	 *
	 * When करोing async_update drivers shouldn't replace the
	 * &drm_plane_state but update the current one with the new plane
	 * configurations in the new plane_state.
	 *
	 * Drivers should also swap the framebuffers between current plane
	 * state (&drm_plane.state) and new_state.
	 * This is required since cleanup क्रम async commits is perक्रमmed on
	 * the new state, rather than old state like क्रम traditional commits.
	 * Since we want to give up the reference on the current (old) fb
	 * instead of our bअक्रम new one, swap them in the driver during the
	 * async commit.
	 *
	 * FIXME:
	 *  - It only works क्रम single plane updates
	 *  - Async Pageflips are not supported yet
	 *  - Some hw might still scan out the old buffer until the next
	 *    vblank, however we let go of the fb references as soon as
	 *    we run this hook. For now drivers must implement their own workers
	 *    क्रम deferring अगर needed, until a common solution is created.
	 */
	व्योम (*atomic_async_update)(काष्ठा drm_plane *plane,
				    काष्ठा drm_atomic_state *state);
पूर्ण;

/**
 * drm_plane_helper_add - sets the helper vtable क्रम a plane
 * @plane: DRM plane
 * @funcs: helper vtable to set क्रम @plane
 */
अटल अंतरभूत व्योम drm_plane_helper_add(काष्ठा drm_plane *plane,
					स्थिर काष्ठा drm_plane_helper_funcs *funcs)
अणु
	plane->helper_निजी = funcs;
पूर्ण

/**
 * काष्ठा drm_mode_config_helper_funcs - global modeset helper operations
 *
 * These helper functions are used by the atomic helpers.
 */
काष्ठा drm_mode_config_helper_funcs अणु
	/**
	 * @atomic_commit_tail:
	 *
	 * This hook is used by the शेष atomic_commit() hook implemented in
	 * drm_atomic_helper_commit() together with the nonblocking commit
	 * helpers (see drm_atomic_helper_setup_commit() क्रम a starting poपूर्णांक)
	 * to implement blocking and nonblocking commits easily. It is not used
	 * by the atomic helpers
	 *
	 * This function is called when the new atomic state has alपढ़ोy been
	 * swapped पूर्णांकo the various state poपूर्णांकers. The passed in state
	 * thereक्रमe contains copies of the old/previous state. This hook should
	 * commit the new state पूर्णांकo hardware. Note that the helpers have
	 * alपढ़ोy रुकोed क्रम preceeding atomic commits and fences, but drivers
	 * can add more रुकोing calls at the start of their implementation, e.g.
	 * to रुको क्रम driver-पूर्णांकernal request क्रम implicit syncing, beक्रमe
	 * starting to commit the update to the hardware.
	 *
	 * After the atomic update is committed to the hardware this hook needs
	 * to call drm_atomic_helper_commit_hw_करोne(). Then रुको क्रम the upate
	 * to be executed by the hardware, क्रम example using
	 * drm_atomic_helper_रुको_क्रम_vblanks() or
	 * drm_atomic_helper_रुको_क्रम_flip_करोne(), and then clean up the old
	 * framebuffers using drm_atomic_helper_cleanup_planes().
	 *
	 * When disabling a CRTC this hook _must_ stall क्रम the commit to
	 * complete. Vblank रुकोs करोn't work on disabled CRTC, hence the core
	 * can't take care of this. And it also can't rely on the vblank event,
	 * since that can be संकेतled alपढ़ोy when the screen shows black,
	 * which can happen much earlier than the last hardware access needed to
	 * shut off the display pipeline completely.
	 *
	 * This hook is optional, the शेष implementation is
	 * drm_atomic_helper_commit_tail().
	 */
	व्योम (*atomic_commit_tail)(काष्ठा drm_atomic_state *state);

	/**
	 * @atomic_commit_setup:
	 *
	 * This hook is used by the शेष atomic_commit() hook implemented in
	 * drm_atomic_helper_commit() together with the nonblocking helpers (see
	 * drm_atomic_helper_setup_commit()) to extend the DRM commit setup. It
	 * is not used by the atomic helpers.
	 *
	 * This function is called at the end of
	 * drm_atomic_helper_setup_commit(), so once the commit has been
	 * properly setup across the generic DRM object states. It allows
	 * drivers to करो some additional commit tracking that isn't related to a
	 * CRTC, plane or connector, tracked in a &drm_निजी_obj काष्ठाure.
	 *
	 * Note that the करोcumentation of &drm_निजी_obj has more details on
	 * how one should implement this.
	 *
	 * This hook is optional.
	 */
	पूर्णांक (*atomic_commit_setup)(काष्ठा drm_atomic_state *state);
पूर्ण;

#पूर्ण_अगर
