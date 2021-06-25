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

#अगर_अघोषित __DRM_BRIDGE_H__
#घोषणा __DRM_BRIDGE_H__

#समावेश <linux/प्रकार.स>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_mode_object.h>
#समावेश <drm/drm_modes.h>

काष्ठा drm_bridge;
काष्ठा drm_bridge_timings;
काष्ठा drm_connector;
काष्ठा drm_display_info;
काष्ठा drm_panel;
काष्ठा edid;
काष्ठा i2c_adapter;

/**
 * क्रमागत drm_bridge_attach_flags - Flags क्रम &drm_bridge_funcs.attach
 */
क्रमागत drm_bridge_attach_flags अणु
	/**
	 * @DRM_BRIDGE_ATTACH_NO_CONNECTOR: When this flag is set the bridge
	 * shall not create a drm_connector.
	 */
	DRM_BRIDGE_ATTACH_NO_CONNECTOR = BIT(0),
पूर्ण;

/**
 * काष्ठा drm_bridge_funcs - drm_bridge control functions
 */
काष्ठा drm_bridge_funcs अणु
	/**
	 * @attach:
	 *
	 * This callback is invoked whenever our bridge is being attached to a
	 * &drm_encoder. The flags argument tunes the behaviour of the attach
	 * operation (see DRM_BRIDGE_ATTACH_*).
	 *
	 * The @attach callback is optional.
	 *
	 * RETURNS:
	 *
	 * Zero on success, error code on failure.
	 */
	पूर्णांक (*attach)(काष्ठा drm_bridge *bridge,
		      क्रमागत drm_bridge_attach_flags flags);

	/**
	 * @detach:
	 *
	 * This callback is invoked whenever our bridge is being detached from a
	 * &drm_encoder.
	 *
	 * The @detach callback is optional.
	 */
	व्योम (*detach)(काष्ठा drm_bridge *bridge);

	/**
	 * @mode_valid:
	 *
	 * This callback is used to check अगर a specअगरic mode is valid in this
	 * bridge. This should be implemented अगर the bridge has some sort of
	 * restriction in the modes it can display. For example, a given bridge
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
	 * The @mode_valid callback is optional.
	 *
	 * NOTE:
	 *
	 * Since this function is both called from the check phase of an atomic
	 * commit, and the mode validation in the probe paths it is not allowed
	 * to look at anything अन्यथा but the passed-in mode, and validate it
	 * against configuration-invariant hardward स्थिरraपूर्णांकs. Any further
	 * limits which depend upon the configuration can only be checked in
	 * @mode_fixup.
	 *
	 * RETURNS:
	 *
	 * drm_mode_status Enum
	 */
	क्रमागत drm_mode_status (*mode_valid)(काष्ठा drm_bridge *bridge,
					   स्थिर काष्ठा drm_display_info *info,
					   स्थिर काष्ठा drm_display_mode *mode);

	/**
	 * @mode_fixup:
	 *
	 * This callback is used to validate and adjust a mode. The parameter
	 * mode is the display mode that should be fed to the next element in
	 * the display chain, either the final &drm_connector or the next
	 * &drm_bridge. The parameter adjusted_mode is the input mode the bridge
	 * requires. It can be modअगरied by this callback and करोes not need to
	 * match mode. See also &drm_crtc_state.adjusted_mode क्रम more details.
	 *
	 * This is the only hook that allows a bridge to reject a modeset. If
	 * this function passes all other callbacks must succeed क्रम this
	 * configuration.
	 *
	 * The mode_fixup callback is optional. &drm_bridge_funcs.mode_fixup()
	 * is not called when &drm_bridge_funcs.atomic_check() is implemented,
	 * so only one of them should be provided.
	 *
	 * NOTE:
	 *
	 * This function is called in the check phase of atomic modesets, which
	 * can be पातed क्रम any reason (including on userspace's request to
	 * just check whether a configuration would be possible). Drivers MUST
	 * NOT touch any persistent state (hardware or software) or data
	 * काष्ठाures except the passed in @state parameter.
	 *
	 * Also beware that userspace can request its own custom modes, neither
	 * core nor helpers filter modes to the list of probe modes reported by
	 * the GETCONNECTOR IOCTL and stored in &drm_connector.modes. To ensure
	 * that modes are filtered consistently put any bridge स्थिरraपूर्णांकs and
	 * limits checks पूर्णांकo @mode_valid.
	 *
	 * RETURNS:
	 *
	 * True अगर an acceptable configuration is possible, false अगर the modeset
	 * operation should be rejected.
	 */
	bool (*mode_fixup)(काष्ठा drm_bridge *bridge,
			   स्थिर काष्ठा drm_display_mode *mode,
			   काष्ठा drm_display_mode *adjusted_mode);
	/**
	 * @disable:
	 *
	 * This callback should disable the bridge. It is called right beक्रमe
	 * the preceding element in the display pipe is disabled. If the
	 * preceding element is a bridge this means it's called beक्रमe that
	 * bridge's @disable vfunc. If the preceding element is a &drm_encoder
	 * it's called right beक्रमe the &drm_encoder_helper_funcs.disable,
	 * &drm_encoder_helper_funcs.prepare or &drm_encoder_helper_funcs.dpms
	 * hook.
	 *
	 * The bridge can assume that the display pipe (i.e. घड़ीs and timing
	 * संकेतs) feeding it is still running when this callback is called.
	 *
	 * The @disable callback is optional.
	 */
	व्योम (*disable)(काष्ठा drm_bridge *bridge);

	/**
	 * @post_disable:
	 *
	 * This callback should disable the bridge. It is called right after the
	 * preceding element in the display pipe is disabled. If the preceding
	 * element is a bridge this means it's called after that bridge's
	 * @post_disable function. If the preceding element is a &drm_encoder
	 * it's called right after the encoder's
	 * &drm_encoder_helper_funcs.disable, &drm_encoder_helper_funcs.prepare
	 * or &drm_encoder_helper_funcs.dpms hook.
	 *
	 * The bridge must assume that the display pipe (i.e. घड़ीs and timing
	 * singals) feeding it is no दीर्घer running when this callback is
	 * called.
	 *
	 * The @post_disable callback is optional.
	 */
	व्योम (*post_disable)(काष्ठा drm_bridge *bridge);

	/**
	 * @mode_set:
	 *
	 * This callback should set the given mode on the bridge. It is called
	 * after the @mode_set callback क्रम the preceding element in the display
	 * pipeline has been called alपढ़ोy. If the bridge is the first element
	 * then this would be &drm_encoder_helper_funcs.mode_set. The display
	 * pipe (i.e.  घड़ीs and timing संकेतs) is off when this function is
	 * called.
	 *
	 * The adjusted_mode parameter is the mode output by the CRTC क्रम the
	 * first bridge in the chain. It can be dअगरferent from the mode
	 * parameter that contains the desired mode क्रम the connector at the end
	 * of the bridges chain, क्रम instance when the first bridge in the chain
	 * perक्रमms scaling. The adjusted mode is mostly useful क्रम the first
	 * bridge in the chain and is likely irrelevant क्रम the other bridges.
	 *
	 * For atomic drivers the adjusted_mode is the mode stored in
	 * &drm_crtc_state.adjusted_mode.
	 *
	 * NOTE:
	 *
	 * If a need arises to store and access modes adjusted क्रम other
	 * locations than the connection between the CRTC and the first bridge,
	 * the DRM framework will have to be extended with DRM bridge states.
	 */
	व्योम (*mode_set)(काष्ठा drm_bridge *bridge,
			 स्थिर काष्ठा drm_display_mode *mode,
			 स्थिर काष्ठा drm_display_mode *adjusted_mode);
	/**
	 * @pre_enable:
	 *
	 * This callback should enable the bridge. It is called right beक्रमe
	 * the preceding element in the display pipe is enabled. If the
	 * preceding element is a bridge this means it's called beक्रमe that
	 * bridge's @pre_enable function. If the preceding element is a
	 * &drm_encoder it's called right before the encoder's
	 * &drm_encoder_helper_funcs.enable, &drm_encoder_helper_funcs.commit or
	 * &drm_encoder_helper_funcs.dpms hook.
	 *
	 * The display pipe (i.e. घड़ीs and timing संकेतs) feeding this bridge
	 * will not yet be running when this callback is called. The bridge must
	 * not enable the display link feeding the next bridge in the chain (अगर
	 * there is one) when this callback is called.
	 *
	 * The @pre_enable callback is optional.
	 */
	व्योम (*pre_enable)(काष्ठा drm_bridge *bridge);

	/**
	 * @enable:
	 *
	 * This callback should enable the bridge. It is called right after
	 * the preceding element in the display pipe is enabled. If the
	 * preceding element is a bridge this means it's called after that
	 * bridge's @enable function. If the preceding element is a
	 * &drm_encoder it's called right after the encoder's
	 * &drm_encoder_helper_funcs.enable, &drm_encoder_helper_funcs.commit or
	 * &drm_encoder_helper_funcs.dpms hook.
	 *
	 * The bridge can assume that the display pipe (i.e. घड़ीs and timing
	 * संकेतs) feeding it is running when this callback is called. This
	 * callback must enable the display link feeding the next bridge in the
	 * chain अगर there is one.
	 *
	 * The @enable callback is optional.
	 */
	व्योम (*enable)(काष्ठा drm_bridge *bridge);

	/**
	 * @atomic_pre_enable:
	 *
	 * This callback should enable the bridge. It is called right beक्रमe
	 * the preceding element in the display pipe is enabled. If the
	 * preceding element is a bridge this means it's called beक्रमe that
	 * bridge's @atomic_pre_enable or @pre_enable function. If the preceding
	 * element is a &drm_encoder it's called right before the encoder's
	 * &drm_encoder_helper_funcs.atomic_enable hook.
	 *
	 * The display pipe (i.e. घड़ीs and timing संकेतs) feeding this bridge
	 * will not yet be running when this callback is called. The bridge must
	 * not enable the display link feeding the next bridge in the chain (अगर
	 * there is one) when this callback is called.
	 *
	 * Note that this function will only be invoked in the context of an
	 * atomic commit. It will not be invoked from
	 * &drm_bridge_chain_pre_enable. It would be prudent to also provide an
	 * implementation of @pre_enable अगर you are expecting driver calls पूर्णांकo
	 * &drm_bridge_chain_pre_enable.
	 *
	 * The @atomic_pre_enable callback is optional.
	 */
	व्योम (*atomic_pre_enable)(काष्ठा drm_bridge *bridge,
				  काष्ठा drm_bridge_state *old_bridge_state);

	/**
	 * @atomic_enable:
	 *
	 * This callback should enable the bridge. It is called right after
	 * the preceding element in the display pipe is enabled. If the
	 * preceding element is a bridge this means it's called after that
	 * bridge's @atomic_enable or @enable function. If the preceding element
	 * is a &drm_encoder it's called right after the encoder's
	 * &drm_encoder_helper_funcs.atomic_enable hook.
	 *
	 * The bridge can assume that the display pipe (i.e. घड़ीs and timing
	 * संकेतs) feeding it is running when this callback is called. This
	 * callback must enable the display link feeding the next bridge in the
	 * chain अगर there is one.
	 *
	 * Note that this function will only be invoked in the context of an
	 * atomic commit. It will not be invoked from &drm_bridge_chain_enable.
	 * It would be prudent to also provide an implementation of @enable अगर
	 * you are expecting driver calls पूर्णांकo &drm_bridge_chain_enable.
	 *
	 * The @atomic_enable callback is optional.
	 */
	व्योम (*atomic_enable)(काष्ठा drm_bridge *bridge,
			      काष्ठा drm_bridge_state *old_bridge_state);
	/**
	 * @atomic_disable:
	 *
	 * This callback should disable the bridge. It is called right beक्रमe
	 * the preceding element in the display pipe is disabled. If the
	 * preceding element is a bridge this means it's called beक्रमe that
	 * bridge's @atomic_disable or @disable vfunc. If the preceding element
	 * is a &drm_encoder it's called right beक्रमe the
	 * &drm_encoder_helper_funcs.atomic_disable hook.
	 *
	 * The bridge can assume that the display pipe (i.e. घड़ीs and timing
	 * संकेतs) feeding it is still running when this callback is called.
	 *
	 * Note that this function will only be invoked in the context of an
	 * atomic commit. It will not be invoked from
	 * &drm_bridge_chain_disable. It would be prudent to also provide an
	 * implementation of @disable अगर you are expecting driver calls पूर्णांकo
	 * &drm_bridge_chain_disable.
	 *
	 * The @atomic_disable callback is optional.
	 */
	व्योम (*atomic_disable)(काष्ठा drm_bridge *bridge,
			       काष्ठा drm_bridge_state *old_bridge_state);

	/**
	 * @atomic_post_disable:
	 *
	 * This callback should disable the bridge. It is called right after the
	 * preceding element in the display pipe is disabled. If the preceding
	 * element is a bridge this means it's called after that bridge's
	 * @atomic_post_disable or @post_disable function. If the preceding
	 * element is a &drm_encoder it's called right after the encoder's
	 * &drm_encoder_helper_funcs.atomic_disable hook.
	 *
	 * The bridge must assume that the display pipe (i.e. घड़ीs and timing
	 * संकेतs) feeding it is no दीर्घer running when this callback is
	 * called.
	 *
	 * Note that this function will only be invoked in the context of an
	 * atomic commit. It will not be invoked from
	 * &drm_bridge_chain_post_disable.
	 * It would be prudent to also provide an implementation of
	 * @post_disable अगर you are expecting driver calls पूर्णांकo
	 * &drm_bridge_chain_post_disable.
	 *
	 * The @atomic_post_disable callback is optional.
	 */
	व्योम (*atomic_post_disable)(काष्ठा drm_bridge *bridge,
				    काष्ठा drm_bridge_state *old_bridge_state);

	/**
	 * @atomic_duplicate_state:
	 *
	 * Duplicate the current bridge state object (which is guaranteed to be
	 * non-शून्य).
	 *
	 * The atomic_duplicate_state hook is mandatory अगर the bridge
	 * implements any of the atomic hooks, and should be left unasचिन्हित
	 * otherwise. For bridges that करोn't subclass &drm_bridge_state, the
	 * drm_atomic_helper_bridge_duplicate_state() helper function shall be
	 * used to implement this hook.
	 *
	 * RETURNS:
	 * A valid drm_bridge_state object or शून्य अगर the allocation fails.
	 */
	काष्ठा drm_bridge_state *(*atomic_duplicate_state)(काष्ठा drm_bridge *bridge);

	/**
	 * @atomic_destroy_state:
	 *
	 * Destroy a bridge state object previously allocated by
	 * &drm_bridge_funcs.atomic_duplicate_state().
	 *
	 * The atomic_destroy_state hook is mandatory अगर the bridge implements
	 * any of the atomic hooks, and should be left unasचिन्हित otherwise.
	 * For bridges that करोn't subclass &drm_bridge_state, the
	 * drm_atomic_helper_bridge_destroy_state() helper function shall be
	 * used to implement this hook.
	 */
	व्योम (*atomic_destroy_state)(काष्ठा drm_bridge *bridge,
				     काष्ठा drm_bridge_state *state);

	/**
	 * @atomic_get_output_bus_fmts:
	 *
	 * Return the supported bus क्रमmats on the output end of a bridge.
	 * The वापसed array must be allocated with kदो_स्मृति() and will be
	 * मुक्तd by the caller. If the allocation fails, शून्य should be
	 * वापसed. num_output_fmts must be set to the वापसed array size.
	 * Formats listed in the वापसed array should be listed in decreasing
	 * preference order (the core will try all क्रमmats until it finds one
	 * that works).
	 *
	 * This method is only called on the last element of the bridge chain
	 * as part of the bus क्रमmat negotiation process that happens in
	 * &drm_atomic_bridge_chain_select_bus_fmts().
	 * This method is optional. When not implemented, the core will
	 * fall back to &drm_connector.display_info.bus_क्रमmats[0] अगर
	 * &drm_connector.display_info.num_bus_क्रमmats > 0,
	 * or to MEDIA_BUS_FMT_FIXED otherwise.
	 */
	u32 *(*atomic_get_output_bus_fmts)(काष्ठा drm_bridge *bridge,
					   काष्ठा drm_bridge_state *bridge_state,
					   काष्ठा drm_crtc_state *crtc_state,
					   काष्ठा drm_connector_state *conn_state,
					   अचिन्हित पूर्णांक *num_output_fmts);

	/**
	 * @atomic_get_input_bus_fmts:
	 *
	 * Return the supported bus क्रमmats on the input end of a bridge क्रम
	 * a specअगरic output bus क्रमmat.
	 *
	 * The वापसed array must be allocated with kदो_स्मृति() and will be
	 * मुक्तd by the caller. If the allocation fails, शून्य should be
	 * वापसed. num_output_fmts must be set to the वापसed array size.
	 * Formats listed in the वापसed array should be listed in decreasing
	 * preference order (the core will try all क्रमmats until it finds one
	 * that works). When the क्रमmat is not supported शून्य should be
	 * वापसed and num_output_fmts should be set to 0.
	 *
	 * This method is called on all elements of the bridge chain as part of
	 * the bus क्रमmat negotiation process that happens in
	 * drm_atomic_bridge_chain_select_bus_fmts().
	 * This method is optional. When not implemented, the core will bypass
	 * bus क्रमmat negotiation on this element of the bridge without
	 * failing, and the previous element in the chain will be passed
	 * MEDIA_BUS_FMT_FIXED as its output bus क्रमmat.
	 *
	 * Bridge drivers that need to support being linked to bridges that are
	 * not supporting bus क्रमmat negotiation should handle the
	 * output_fmt == MEDIA_BUS_FMT_FIXED हाल appropriately, by selecting a
	 * sensible शेष value or extracting this inक्रमmation from somewhere
	 * अन्यथा (FW property, &drm_display_mode, &drm_display_info, ...)
	 *
	 * Note: Even अगर input क्रमmat selection on the first bridge has no
	 * impact on the negotiation process (bus क्रमmat negotiation stops once
	 * we reach the first element of the chain), drivers are expected to
	 * वापस accurate input क्रमmats as the input क्रमmat may be used to
	 * configure the CRTC output appropriately.
	 */
	u32 *(*atomic_get_input_bus_fmts)(काष्ठा drm_bridge *bridge,
					  काष्ठा drm_bridge_state *bridge_state,
					  काष्ठा drm_crtc_state *crtc_state,
					  काष्ठा drm_connector_state *conn_state,
					  u32 output_fmt,
					  अचिन्हित पूर्णांक *num_input_fmts);

	/**
	 * @atomic_check:
	 *
	 * This method is responsible क्रम checking bridge state correctness.
	 * It can also check the state of the surrounding components in chain
	 * to make sure the whole pipeline can work properly.
	 *
	 * &drm_bridge_funcs.atomic_check() hooks are called in reverse
	 * order (from the last to the first bridge).
	 *
	 * This method is optional. &drm_bridge_funcs.mode_fixup() is not
	 * called when &drm_bridge_funcs.atomic_check() is implemented, so only
	 * one of them should be provided.
	 *
	 * If drivers need to tweak &drm_bridge_state.input_bus_cfg.flags or
	 * &drm_bridge_state.output_bus_cfg.flags it should happen in
	 * this function. By शेष the &drm_bridge_state.output_bus_cfg.flags
	 * field is set to the next bridge
	 * &drm_bridge_state.input_bus_cfg.flags value or
	 * &drm_connector.display_info.bus_flags अगर the bridge is the last
	 * element in the chain.
	 *
	 * RETURNS:
	 * zero अगर the check passed, a negative error code otherwise.
	 */
	पूर्णांक (*atomic_check)(काष्ठा drm_bridge *bridge,
			    काष्ठा drm_bridge_state *bridge_state,
			    काष्ठा drm_crtc_state *crtc_state,
			    काष्ठा drm_connector_state *conn_state);

	/**
	 * @atomic_reset:
	 *
	 * Reset the bridge to a predefined state (or retrieve its current
	 * state) and वापस a &drm_bridge_state object matching this state.
	 * This function is called at attach समय.
	 *
	 * The atomic_reset hook is mandatory अगर the bridge implements any of
	 * the atomic hooks, and should be left unasचिन्हित otherwise. For
	 * bridges that करोn't subclass &drm_bridge_state, the
	 * drm_atomic_helper_bridge_reset() helper function shall be used to
	 * implement this hook.
	 *
	 * Note that the atomic_reset() semantics is not exactly matching the
	 * reset() semantics found on other components (connector, plane, ...).
	 *
	 * 1. The reset operation happens when the bridge is attached, not when
	 *    drm_mode_config_reset() is called
	 * 2. It's meant to be used exclusively on bridges that have been
	 *    converted to the ATOMIC API
	 *
	 * RETURNS:
	 * A valid drm_bridge_state object in हाल of success, an ERR_PTR()
	 * giving the reason of the failure otherwise.
	 */
	काष्ठा drm_bridge_state *(*atomic_reset)(काष्ठा drm_bridge *bridge);

	/**
	 * @detect:
	 *
	 * Check अगर anything is attached to the bridge output.
	 *
	 * This callback is optional, अगर not implemented the bridge will be
	 * considered as always having a component attached to its output.
	 * Bridges that implement this callback shall set the
	 * DRM_BRIDGE_OP_DETECT flag in their &drm_bridge->ops.
	 *
	 * RETURNS:
	 *
	 * drm_connector_status indicating the bridge output status.
	 */
	क्रमागत drm_connector_status (*detect)(काष्ठा drm_bridge *bridge);

	/**
	 * @get_modes:
	 *
	 * Fill all modes currently valid क्रम the sink पूर्णांकo the &drm_connector
	 * with drm_mode_probed_add().
	 *
	 * The @get_modes callback is mostly पूर्णांकended to support non-probeable
	 * displays such as many fixed panels. Bridges that support पढ़ोing
	 * EDID shall leave @get_modes unimplemented and implement the
	 * &drm_bridge_funcs->get_edid callback instead.
	 *
	 * This callback is optional. Bridges that implement it shall set the
	 * DRM_BRIDGE_OP_MODES flag in their &drm_bridge->ops.
	 *
	 * The connector parameter shall be used क्रम the sole purpose of
	 * filling modes, and shall not be stored पूर्णांकernally by bridge drivers
	 * क्रम future usage.
	 *
	 * RETURNS:
	 *
	 * The number of modes added by calling drm_mode_probed_add().
	 */
	पूर्णांक (*get_modes)(काष्ठा drm_bridge *bridge,
			 काष्ठा drm_connector *connector);

	/**
	 * @get_edid:
	 *
	 * Read and parse the EDID data of the connected display.
	 *
	 * The @get_edid callback is the preferred way of reporting mode
	 * inक्रमmation क्रम a display connected to the bridge output. Bridges
	 * that support पढ़ोing EDID shall implement this callback and leave
	 * the @get_modes callback unimplemented.
	 *
	 * The caller of this operation shall first verअगरy the output
	 * connection status and refrain from पढ़ोing EDID from a disconnected
	 * output.
	 *
	 * This callback is optional. Bridges that implement it shall set the
	 * DRM_BRIDGE_OP_EDID flag in their &drm_bridge->ops.
	 *
	 * The connector parameter shall be used क्रम the sole purpose of EDID
	 * retrieval and parsing, and shall not be stored पूर्णांकernally by bridge
	 * drivers क्रम future usage.
	 *
	 * RETURNS:
	 *
	 * An edid काष्ठाure newly allocated with kदो_स्मृति() (or similar) on
	 * success, or शून्य otherwise. The caller is responsible क्रम मुक्तing
	 * the वापसed edid काष्ठाure with kमुक्त().
	 */
	काष्ठा edid *(*get_edid)(काष्ठा drm_bridge *bridge,
				 काष्ठा drm_connector *connector);

	/**
	 * @hpd_notअगरy:
	 *
	 * Notअगरy the bridge of hot plug detection.
	 *
	 * This callback is optional, it may be implemented by bridges that
	 * need to be notअगरied of display connection or disconnection क्रम
	 * पूर्णांकernal reasons. One use हाल is to reset the पूर्णांकernal state of CEC
	 * controllers क्रम HDMI bridges.
	 */
	व्योम (*hpd_notअगरy)(काष्ठा drm_bridge *bridge,
			   क्रमागत drm_connector_status status);

	/**
	 * @hpd_enable:
	 *
	 * Enable hot plug detection. From now on the bridge shall call
	 * drm_bridge_hpd_notअगरy() each समय a change is detected in the output
	 * connection status, until hot plug detection माला_लो disabled with
	 * @hpd_disable.
	 *
	 * This callback is optional and shall only be implemented by bridges
	 * that support hot-plug notअगरication without polling. Bridges that
	 * implement it shall also implement the @hpd_disable callback and set
	 * the DRM_BRIDGE_OP_HPD flag in their &drm_bridge->ops.
	 */
	व्योम (*hpd_enable)(काष्ठा drm_bridge *bridge);

	/**
	 * @hpd_disable:
	 *
	 * Disable hot plug detection. Once this function वापसs the bridge
	 * shall not call drm_bridge_hpd_notअगरy() when a change in the output
	 * connection status occurs.
	 *
	 * This callback is optional and shall only be implemented by bridges
	 * that support hot-plug notअगरication without polling. Bridges that
	 * implement it shall also implement the @hpd_enable callback and set
	 * the DRM_BRIDGE_OP_HPD flag in their &drm_bridge->ops.
	 */
	व्योम (*hpd_disable)(काष्ठा drm_bridge *bridge);
पूर्ण;

/**
 * काष्ठा drm_bridge_timings - timing inक्रमmation क्रम the bridge
 */
काष्ठा drm_bridge_timings अणु
	/**
	 * @input_bus_flags:
	 *
	 * Tells what additional settings क्रम the pixel data on the bus
	 * this bridge requires (like pixel संकेत polarity). See also
	 * &drm_display_info->bus_flags.
	 */
	u32 input_bus_flags;
	/**
	 * @setup_समय_ps:
	 *
	 * Defines the समय in picoseconds the input data lines must be
	 * stable beक्रमe the घड़ी edge.
	 */
	u32 setup_समय_ps;
	/**
	 * @hold_समय_ps:
	 *
	 * Defines the समय in picoseconds taken क्रम the bridge to sample the
	 * input संकेत after the घड़ी edge.
	 */
	u32 hold_समय_ps;
	/**
	 * @dual_link:
	 *
	 * True अगर the bus operates in dual-link mode. The exact meaning is
	 * dependent on the bus type. For LVDS buses, this indicates that even-
	 * and odd-numbered pixels are received on separate links.
	 */
	bool dual_link;
पूर्ण;

/**
 * क्रमागत drm_bridge_ops - Biपंचांगask of operations supported by the bridge
 */
क्रमागत drm_bridge_ops अणु
	/**
	 * @DRM_BRIDGE_OP_DETECT: The bridge can detect displays connected to
	 * its output. Bridges that set this flag shall implement the
	 * &drm_bridge_funcs->detect callback.
	 */
	DRM_BRIDGE_OP_DETECT = BIT(0),
	/**
	 * @DRM_BRIDGE_OP_EDID: The bridge can retrieve the EDID of the display
	 * connected to its output. Bridges that set this flag shall implement
	 * the &drm_bridge_funcs->get_edid callback.
	 */
	DRM_BRIDGE_OP_EDID = BIT(1),
	/**
	 * @DRM_BRIDGE_OP_HPD: The bridge can detect hot-plug and hot-unplug
	 * without requiring polling. Bridges that set this flag shall
	 * implement the &drm_bridge_funcs->hpd_enable and
	 * &drm_bridge_funcs->hpd_disable callbacks अगर they support enabling
	 * and disabling hot-plug detection dynamically.
	 */
	DRM_BRIDGE_OP_HPD = BIT(2),
	/**
	 * @DRM_BRIDGE_OP_MODES: The bridge can retrieve the modes supported
	 * by the display at its output. This करोes not include पढ़ोing EDID
	 * which is separately covered by @DRM_BRIDGE_OP_EDID. Bridges that set
	 * this flag shall implement the &drm_bridge_funcs->get_modes callback.
	 */
	DRM_BRIDGE_OP_MODES = BIT(3),
पूर्ण;

/**
 * काष्ठा drm_bridge - central DRM bridge control काष्ठाure
 */
काष्ठा drm_bridge अणु
	/** @base: inherit from &drm_निजी_object */
	काष्ठा drm_निजी_obj base;
	/** @dev: DRM device this bridge beदीर्घs to */
	काष्ठा drm_device *dev;
	/** @encoder: encoder to which this bridge is connected */
	काष्ठा drm_encoder *encoder;
	/** @chain_node: used to क्रमm a bridge chain */
	काष्ठा list_head chain_node;
#अगर_घोषित CONFIG_OF
	/** @of_node: device node poपूर्णांकer to the bridge */
	काष्ठा device_node *of_node;
#पूर्ण_अगर
	/** @list: to keep track of all added bridges */
	काष्ठा list_head list;
	/**
	 * @timings:
	 *
	 * the timing specअगरication क्रम the bridge, अगर any (may be शून्य)
	 */
	स्थिर काष्ठा drm_bridge_timings *timings;
	/** @funcs: control functions */
	स्थिर काष्ठा drm_bridge_funcs *funcs;
	/** @driver_निजी: poपूर्णांकer to the bridge driver's पूर्णांकernal context */
	व्योम *driver_निजी;
	/** @ops: biपंचांगask of operations supported by the bridge */
	क्रमागत drm_bridge_ops ops;
	/**
	 * @type: Type of the connection at the bridge output
	 * (DRM_MODE_CONNECTOR_*). For bridges at the end of this chain this
	 * identअगरies the type of connected display.
	 */
	पूर्णांक type;
	/**
	 * @पूर्णांकerlace_allowed: Indicate that the bridge can handle पूर्णांकerlaced
	 * modes.
	 */
	bool पूर्णांकerlace_allowed;
	/**
	 * @ddc: Associated I2C adapter क्रम DDC access, अगर any.
	 */
	काष्ठा i2c_adapter *ddc;
	/** निजी: */
	/**
	 * @hpd_mutex: Protects the @hpd_cb and @hpd_data fields.
	 */
	काष्ठा mutex hpd_mutex;
	/**
	 * @hpd_cb: Hot plug detection callback, रेजिस्टरed with
	 * drm_bridge_hpd_enable().
	 */
	व्योम (*hpd_cb)(व्योम *data, क्रमागत drm_connector_status status);
	/**
	 * @hpd_data: Private data passed to the Hot plug detection callback
	 * @hpd_cb.
	 */
	व्योम *hpd_data;
पूर्ण;

अटल अंतरभूत काष्ठा drm_bridge *
drm_priv_to_bridge(काष्ठा drm_निजी_obj *priv)
अणु
	वापस container_of(priv, काष्ठा drm_bridge, base);
पूर्ण

व्योम drm_bridge_add(काष्ठा drm_bridge *bridge);
व्योम drm_bridge_हटाओ(काष्ठा drm_bridge *bridge);
काष्ठा drm_bridge *of_drm_find_bridge(काष्ठा device_node *np);
पूर्णांक drm_bridge_attach(काष्ठा drm_encoder *encoder, काष्ठा drm_bridge *bridge,
		      काष्ठा drm_bridge *previous,
		      क्रमागत drm_bridge_attach_flags flags);

/**
 * drm_bridge_get_next_bridge() - Get the next bridge in the chain
 * @bridge: bridge object
 *
 * RETURNS:
 * the next bridge in the chain after @bridge, or शून्य अगर @bridge is the last.
 */
अटल अंतरभूत काष्ठा drm_bridge *
drm_bridge_get_next_bridge(काष्ठा drm_bridge *bridge)
अणु
	अगर (list_is_last(&bridge->chain_node, &bridge->encoder->bridge_chain))
		वापस शून्य;

	वापस list_next_entry(bridge, chain_node);
पूर्ण

/**
 * drm_bridge_get_prev_bridge() - Get the previous bridge in the chain
 * @bridge: bridge object
 *
 * RETURNS:
 * the previous bridge in the chain, or शून्य अगर @bridge is the first.
 */
अटल अंतरभूत काष्ठा drm_bridge *
drm_bridge_get_prev_bridge(काष्ठा drm_bridge *bridge)
अणु
	अगर (list_is_first(&bridge->chain_node, &bridge->encoder->bridge_chain))
		वापस शून्य;

	वापस list_prev_entry(bridge, chain_node);
पूर्ण

/**
 * drm_bridge_chain_get_first_bridge() - Get the first bridge in the chain
 * @encoder: encoder object
 *
 * RETURNS:
 * the first bridge in the chain, or शून्य अगर @encoder has no bridge attached
 * to it.
 */
अटल अंतरभूत काष्ठा drm_bridge *
drm_bridge_chain_get_first_bridge(काष्ठा drm_encoder *encoder)
अणु
	वापस list_first_entry_or_null(&encoder->bridge_chain,
					काष्ठा drm_bridge, chain_node);
पूर्ण

/**
 * drm_क्रम_each_bridge_in_chain() - Iterate over all bridges present in a chain
 * @encoder: the encoder to iterate bridges on
 * @bridge: a bridge poपूर्णांकer updated to poपूर्णांक to the current bridge at each
 *	    iteration
 *
 * Iterate over all bridges present in the bridge chain attached to @encoder.
 */
#घोषणा drm_क्रम_each_bridge_in_chain(encoder, bridge)			\
	list_क्रम_each_entry(bridge, &(encoder)->bridge_chain, chain_node)

bool drm_bridge_chain_mode_fixup(काष्ठा drm_bridge *bridge,
				 स्थिर काष्ठा drm_display_mode *mode,
				 काष्ठा drm_display_mode *adjusted_mode);
क्रमागत drm_mode_status
drm_bridge_chain_mode_valid(काष्ठा drm_bridge *bridge,
			    स्थिर काष्ठा drm_display_info *info,
			    स्थिर काष्ठा drm_display_mode *mode);
व्योम drm_bridge_chain_disable(काष्ठा drm_bridge *bridge);
व्योम drm_bridge_chain_post_disable(काष्ठा drm_bridge *bridge);
व्योम drm_bridge_chain_mode_set(काष्ठा drm_bridge *bridge,
			       स्थिर काष्ठा drm_display_mode *mode,
			       स्थिर काष्ठा drm_display_mode *adjusted_mode);
व्योम drm_bridge_chain_pre_enable(काष्ठा drm_bridge *bridge);
व्योम drm_bridge_chain_enable(काष्ठा drm_bridge *bridge);

पूर्णांक drm_atomic_bridge_chain_check(काष्ठा drm_bridge *bridge,
				  काष्ठा drm_crtc_state *crtc_state,
				  काष्ठा drm_connector_state *conn_state);
व्योम drm_atomic_bridge_chain_disable(काष्ठा drm_bridge *bridge,
				     काष्ठा drm_atomic_state *state);
व्योम drm_atomic_bridge_chain_post_disable(काष्ठा drm_bridge *bridge,
					  काष्ठा drm_atomic_state *state);
व्योम drm_atomic_bridge_chain_pre_enable(काष्ठा drm_bridge *bridge,
					काष्ठा drm_atomic_state *state);
व्योम drm_atomic_bridge_chain_enable(काष्ठा drm_bridge *bridge,
				    काष्ठा drm_atomic_state *state);

u32 *
drm_atomic_helper_bridge_propagate_bus_fmt(काष्ठा drm_bridge *bridge,
					काष्ठा drm_bridge_state *bridge_state,
					काष्ठा drm_crtc_state *crtc_state,
					काष्ठा drm_connector_state *conn_state,
					u32 output_fmt,
					अचिन्हित पूर्णांक *num_input_fmts);

क्रमागत drm_connector_status drm_bridge_detect(काष्ठा drm_bridge *bridge);
पूर्णांक drm_bridge_get_modes(काष्ठा drm_bridge *bridge,
			 काष्ठा drm_connector *connector);
काष्ठा edid *drm_bridge_get_edid(काष्ठा drm_bridge *bridge,
				 काष्ठा drm_connector *connector);
व्योम drm_bridge_hpd_enable(काष्ठा drm_bridge *bridge,
			   व्योम (*cb)(व्योम *data,
				      क्रमागत drm_connector_status status),
			   व्योम *data);
व्योम drm_bridge_hpd_disable(काष्ठा drm_bridge *bridge);
व्योम drm_bridge_hpd_notअगरy(काष्ठा drm_bridge *bridge,
			   क्रमागत drm_connector_status status);

#अगर_घोषित CONFIG_DRM_PANEL_BRIDGE
काष्ठा drm_bridge *drm_panel_bridge_add(काष्ठा drm_panel *panel);
काष्ठा drm_bridge *drm_panel_bridge_add_typed(काष्ठा drm_panel *panel,
					      u32 connector_type);
व्योम drm_panel_bridge_हटाओ(काष्ठा drm_bridge *bridge);
काष्ठा drm_bridge *devm_drm_panel_bridge_add(काष्ठा device *dev,
					     काष्ठा drm_panel *panel);
काष्ठा drm_bridge *devm_drm_panel_bridge_add_typed(काष्ठा device *dev,
						   काष्ठा drm_panel *panel,
						   u32 connector_type);
काष्ठा drm_connector *drm_panel_bridge_connector(काष्ठा drm_bridge *bridge);
#पूर्ण_अगर

#पूर्ण_अगर
