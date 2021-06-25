<शैली गुरु>
/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sub license,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>

#समावेश <drm/drm_atomic_state_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_encoder.h>

#समावेश "drm_crtc_internal.h"

/**
 * DOC: overview
 *
 * &काष्ठा drm_bridge represents a device that hangs on to an encoder. These are
 * handy when a regular &drm_encoder entity isn't enough to represent the entire
 * encoder chain.
 *
 * A bridge is always attached to a single &drm_encoder at a समय, but can be
 * either connected to it directly, or through a chain of bridges::
 *
 *     [ CRTC ---> ] Encoder ---> Bridge A ---> Bridge B
 *
 * Here, the output of the encoder feeds to bridge A, and that furthers feeds to
 * bridge B. Bridge chains can be arbitrarily दीर्घ, and shall be fully linear:
 * Chaining multiple bridges to the output of a bridge, or the same bridge to
 * the output of dअगरferent bridges, is not supported.
 *
 * Display drivers are responsible क्रम linking encoders with the first bridge
 * in the chains. This is करोne by acquiring the appropriate bridge with
 * of_drm_find_bridge() or drm_of_find_panel_or_bridge(), or creating it क्रम a
 * panel with drm_panel_bridge_add_typed() (or the managed version
 * devm_drm_panel_bridge_add_typed()). Once acquired, the bridge shall be
 * attached to the encoder with a call to drm_bridge_attach().
 *
 * Bridges are responsible क्रम linking themselves with the next bridge in the
 * chain, अगर any. This is करोne the same way as क्रम encoders, with the call to
 * drm_bridge_attach() occurring in the &drm_bridge_funcs.attach operation.
 *
 * Once these links are created, the bridges can participate aदीर्घ with encoder
 * functions to perक्रमm mode validation and fixup (through
 * drm_bridge_chain_mode_valid() and drm_atomic_bridge_chain_check()), mode
 * setting (through drm_bridge_chain_mode_set()), enable (through
 * drm_atomic_bridge_chain_pre_enable() and drm_atomic_bridge_chain_enable())
 * and disable (through drm_atomic_bridge_chain_disable() and
 * drm_atomic_bridge_chain_post_disable()). Those functions call the
 * corresponding operations provided in &drm_bridge_funcs in sequence क्रम all
 * bridges in the chain.
 *
 * For display drivers that use the atomic helpers
 * drm_atomic_helper_check_modeset(),
 * drm_atomic_helper_commit_modeset_enables() and
 * drm_atomic_helper_commit_modeset_disables() (either directly in hand-rolled
 * commit check and commit tail handlers, or through the higher-level
 * drm_atomic_helper_check() and drm_atomic_helper_commit_tail() or
 * drm_atomic_helper_commit_tail_rpm() helpers), this is करोne transparently and
 * requires no पूर्णांकervention from the driver. For other drivers, the relevant
 * DRM bridge chain functions shall be called manually.
 *
 * Bridges also participate in implementing the &drm_connector at the end of
 * the bridge chain. Display drivers may use the drm_bridge_connector_init()
 * helper to create the &drm_connector, or implement it manually on top of the
 * connector-related operations exposed by the bridge (see the overview
 * करोcumentation of bridge operations क्रम more details).
 *
 * &drm_bridge, like &drm_panel, aren't &drm_mode_object entities like planes,
 * CRTCs, encoders or connectors and hence are not visible to userspace. They
 * just provide additional hooks to get the desired output at the end of the
 * encoder chain.
 */

अटल DEFINE_MUTEX(bridge_lock);
अटल LIST_HEAD(bridge_list);

/**
 * drm_bridge_add - add the given bridge to the global bridge list
 *
 * @bridge: bridge control काष्ठाure
 */
व्योम drm_bridge_add(काष्ठा drm_bridge *bridge)
अणु
	mutex_init(&bridge->hpd_mutex);

	mutex_lock(&bridge_lock);
	list_add_tail(&bridge->list, &bridge_list);
	mutex_unlock(&bridge_lock);
पूर्ण
EXPORT_SYMBOL(drm_bridge_add);

/**
 * drm_bridge_हटाओ - हटाओ the given bridge from the global bridge list
 *
 * @bridge: bridge control काष्ठाure
 */
व्योम drm_bridge_हटाओ(काष्ठा drm_bridge *bridge)
अणु
	mutex_lock(&bridge_lock);
	list_del_init(&bridge->list);
	mutex_unlock(&bridge_lock);

	mutex_destroy(&bridge->hpd_mutex);
पूर्ण
EXPORT_SYMBOL(drm_bridge_हटाओ);

अटल काष्ठा drm_निजी_state *
drm_bridge_atomic_duplicate_priv_state(काष्ठा drm_निजी_obj *obj)
अणु
	काष्ठा drm_bridge *bridge = drm_priv_to_bridge(obj);
	काष्ठा drm_bridge_state *state;

	state = bridge->funcs->atomic_duplicate_state(bridge);
	वापस state ? &state->base : शून्य;
पूर्ण

अटल व्योम
drm_bridge_atomic_destroy_priv_state(काष्ठा drm_निजी_obj *obj,
				     काष्ठा drm_निजी_state *s)
अणु
	काष्ठा drm_bridge_state *state = drm_priv_to_bridge_state(s);
	काष्ठा drm_bridge *bridge = drm_priv_to_bridge(obj);

	bridge->funcs->atomic_destroy_state(bridge, state);
पूर्ण

अटल स्थिर काष्ठा drm_निजी_state_funcs drm_bridge_priv_state_funcs = अणु
	.atomic_duplicate_state = drm_bridge_atomic_duplicate_priv_state,
	.atomic_destroy_state = drm_bridge_atomic_destroy_priv_state,
पूर्ण;

/**
 * drm_bridge_attach - attach the bridge to an encoder's chain
 *
 * @encoder: DRM encoder
 * @bridge: bridge to attach
 * @previous: previous bridge in the chain (optional)
 * @flags: DRM_BRIDGE_ATTACH_* flags
 *
 * Called by a kms driver to link the bridge to an encoder's chain. The previous
 * argument specअगरies the previous bridge in the chain. If शून्य, the bridge is
 * linked directly at the encoder's output. Otherwise it is linked at the
 * previous bridge's output.
 *
 * If non-शून्य the previous bridge must be alपढ़ोy attached by a call to this
 * function.
 *
 * Note that bridges attached to encoders are स्वतः-detached during encoder
 * cleanup in drm_encoder_cleanup(), so drm_bridge_attach() should generally
 * *not* be balanced with a drm_bridge_detach() in driver code.
 *
 * RETURNS:
 * Zero on success, error code on failure
 */
पूर्णांक drm_bridge_attach(काष्ठा drm_encoder *encoder, काष्ठा drm_bridge *bridge,
		      काष्ठा drm_bridge *previous,
		      क्रमागत drm_bridge_attach_flags flags)
अणु
	पूर्णांक ret;

	अगर (!encoder || !bridge)
		वापस -EINVAL;

	अगर (previous && (!previous->dev || previous->encoder != encoder))
		वापस -EINVAL;

	अगर (bridge->dev)
		वापस -EBUSY;

	bridge->dev = encoder->dev;
	bridge->encoder = encoder;

	अगर (previous)
		list_add(&bridge->chain_node, &previous->chain_node);
	अन्यथा
		list_add(&bridge->chain_node, &encoder->bridge_chain);

	अगर (bridge->funcs->attach) अणु
		ret = bridge->funcs->attach(bridge, flags);
		अगर (ret < 0)
			जाओ err_reset_bridge;
	पूर्ण

	अगर (bridge->funcs->atomic_reset) अणु
		काष्ठा drm_bridge_state *state;

		state = bridge->funcs->atomic_reset(bridge);
		अगर (IS_ERR(state)) अणु
			ret = PTR_ERR(state);
			जाओ err_detach_bridge;
		पूर्ण

		drm_atomic_निजी_obj_init(bridge->dev, &bridge->base,
					    &state->base,
					    &drm_bridge_priv_state_funcs);
	पूर्ण

	वापस 0;

err_detach_bridge:
	अगर (bridge->funcs->detach)
		bridge->funcs->detach(bridge);

err_reset_bridge:
	bridge->dev = शून्य;
	bridge->encoder = शून्य;
	list_del(&bridge->chain_node);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_bridge_attach);

व्योम drm_bridge_detach(काष्ठा drm_bridge *bridge)
अणु
	अगर (WARN_ON(!bridge))
		वापस;

	अगर (WARN_ON(!bridge->dev))
		वापस;

	अगर (bridge->funcs->atomic_reset)
		drm_atomic_निजी_obj_fini(&bridge->base);

	अगर (bridge->funcs->detach)
		bridge->funcs->detach(bridge);

	list_del(&bridge->chain_node);
	bridge->dev = शून्य;
पूर्ण

/**
 * DOC: bridge operations
 *
 * Bridge drivers expose operations through the &drm_bridge_funcs काष्ठाure.
 * The DRM पूर्णांकernals (atomic and CRTC helpers) use the helpers defined in
 * drm_bridge.c to call bridge operations. Those operations are भागided in
 * three big categories to support dअगरferent parts of the bridge usage.
 *
 * - The encoder-related operations support control of the bridges in the
 *   chain, and are roughly counterparts to the &drm_encoder_helper_funcs
 *   operations. They are used by the legacy CRTC and the atomic modeset
 *   helpers to perक्रमm mode validation, fixup and setting, and enable and
 *   disable the bridge स्वतःmatically.
 *
 *   The enable and disable operations are split in
 *   &drm_bridge_funcs.pre_enable, &drm_bridge_funcs.enable,
 *   &drm_bridge_funcs.disable and &drm_bridge_funcs.post_disable to provide
 *   finer-grained control.
 *
 *   Bridge drivers may implement the legacy version of those operations, or
 *   the atomic version (prefixed with atomic\_), in which हाल they shall also
 *   implement the atomic state bookkeeping operations
 *   (&drm_bridge_funcs.atomic_duplicate_state,
 *   &drm_bridge_funcs.atomic_destroy_state and &drm_bridge_funcs.reset).
 *   Mixing atomic and non-atomic versions of the operations is not supported.
 *
 * - The bus क्रमmat negotiation operations
 *   &drm_bridge_funcs.atomic_get_output_bus_fmts and
 *   &drm_bridge_funcs.atomic_get_input_bus_fmts allow bridge drivers to
 *   negotiate the क्रमmats transmitted between bridges in the chain when
 *   multiple क्रमmats are supported. Negotiation क्रम क्रमmats is perक्रमmed
 *   transparently क्रम display drivers by the atomic modeset helpers. Only
 *   atomic versions of those operations exist, bridge drivers that need to
 *   implement them shall thus also implement the atomic version of the
 *   encoder-related operations. This feature is not supported by the legacy
 *   CRTC helpers.
 *
 * - The connector-related operations support implementing a &drm_connector
 *   based on a chain of bridges. DRM bridges traditionally create a
 *   &drm_connector क्रम bridges meant to be used at the end of the chain. This
 *   माला_दो additional burden on bridge drivers, especially क्रम bridges that may
 *   be used in the middle of a chain or at the end of it. Furthermore, it
 *   requires all operations of the &drm_connector to be handled by a single
 *   bridge, which करोesn't always match the hardware architecture.
 *
 *   To simplअगरy bridge drivers and make the connector implementation more
 *   flexible, a new model allows bridges to unconditionally skip creation of
 *   &drm_connector and instead expose &drm_bridge_funcs operations to support
 *   an बाह्यally-implemented &drm_connector. Those operations are
 *   &drm_bridge_funcs.detect, &drm_bridge_funcs.get_modes,
 *   &drm_bridge_funcs.get_edid, &drm_bridge_funcs.hpd_notअगरy,
 *   &drm_bridge_funcs.hpd_enable and &drm_bridge_funcs.hpd_disable. When
 *   implemented, display drivers shall create a &drm_connector instance क्रम
 *   each chain of bridges, and implement those connector instances based on
 *   the bridge connector operations.
 *
 *   Bridge drivers shall implement the connector-related operations क्रम all
 *   the features that the bridge hardware support. For instance, अगर a bridge
 *   supports पढ़ोing EDID, the &drm_bridge_funcs.get_edid shall be
 *   implemented. This however करोesn't mean that the DDC lines are wired to the
 *   bridge on a particular platक्रमm, as they could also be connected to an I2C
 *   controller of the SoC. Support क्रम the connector-related operations on the
 *   running platक्रमm is reported through the &drm_bridge.ops flags. Bridge
 *   drivers shall detect which operations they can support on the platक्रमm
 *   (usually this inक्रमmation is provided by ACPI or DT), and set the
 *   &drm_bridge.ops flags क्रम all supported operations. A flag shall only be
 *   set अगर the corresponding &drm_bridge_funcs operation is implemented, but
 *   an implemented operation करोesn't necessarily imply that the corresponding
 *   flag will be set. Display drivers shall use the &drm_bridge.ops flags to
 *   decide which bridge to delegate a connector operation to. This mechanism
 *   allows providing a single अटल स्थिर &drm_bridge_funcs instance in
 *   bridge drivers, improving security by storing function poपूर्णांकers in
 *   पढ़ो-only memory.
 *
 *   In order to ease transition, bridge drivers may support both the old and
 *   new models by making connector creation optional and implementing the
 *   connected-related bridge operations. Connector creation is then controlled
 *   by the flags argument to the drm_bridge_attach() function. Display drivers
 *   that support the new model and create connectors themselves shall set the
 *   %DRM_BRIDGE_ATTACH_NO_CONNECTOR flag, and bridge drivers shall then skip
 *   connector creation. For पूर्णांकermediate bridges in the chain, the flag shall
 *   be passed to the drm_bridge_attach() call क्रम the करोwnstream bridge.
 *   Bridge drivers that implement the new model only shall वापस an error
 *   from their &drm_bridge_funcs.attach handler when the
 *   %DRM_BRIDGE_ATTACH_NO_CONNECTOR flag is not set. New display drivers
 *   should use the new model, and convert the bridge drivers they use अगर
 *   needed, in order to gradually transition to the new model.
 */

/**
 * drm_bridge_chain_mode_fixup - fixup proposed mode क्रम all bridges in the
 *				 encoder chain
 * @bridge: bridge control काष्ठाure
 * @mode: desired mode to be set क्रम the bridge
 * @adjusted_mode: updated mode that works क्रम this bridge
 *
 * Calls &drm_bridge_funcs.mode_fixup क्रम all the bridges in the
 * encoder chain, starting from the first bridge to the last.
 *
 * Note: the bridge passed should be the one बंदst to the encoder
 *
 * RETURNS:
 * true on success, false on failure
 */
bool drm_bridge_chain_mode_fixup(काष्ठा drm_bridge *bridge,
				 स्थिर काष्ठा drm_display_mode *mode,
				 काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा drm_encoder *encoder;

	अगर (!bridge)
		वापस true;

	encoder = bridge->encoder;
	list_क्रम_each_entry_from(bridge, &encoder->bridge_chain, chain_node) अणु
		अगर (!bridge->funcs->mode_fixup)
			जारी;

		अगर (!bridge->funcs->mode_fixup(bridge, mode, adjusted_mode))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL(drm_bridge_chain_mode_fixup);

/**
 * drm_bridge_chain_mode_valid - validate the mode against all bridges in the
 *				 encoder chain.
 * @bridge: bridge control काष्ठाure
 * @info: display info against which the mode shall be validated
 * @mode: desired mode to be validated
 *
 * Calls &drm_bridge_funcs.mode_valid क्रम all the bridges in the encoder
 * chain, starting from the first bridge to the last. If at least one bridge
 * करोes not accept the mode the function वापसs the error code.
 *
 * Note: the bridge passed should be the one बंदst to the encoder.
 *
 * RETURNS:
 * MODE_OK on success, drm_mode_status Enum error code on failure
 */
क्रमागत drm_mode_status
drm_bridge_chain_mode_valid(काष्ठा drm_bridge *bridge,
			    स्थिर काष्ठा drm_display_info *info,
			    स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_encoder *encoder;

	अगर (!bridge)
		वापस MODE_OK;

	encoder = bridge->encoder;
	list_क्रम_each_entry_from(bridge, &encoder->bridge_chain, chain_node) अणु
		क्रमागत drm_mode_status ret;

		अगर (!bridge->funcs->mode_valid)
			जारी;

		ret = bridge->funcs->mode_valid(bridge, info, mode);
		अगर (ret != MODE_OK)
			वापस ret;
	पूर्ण

	वापस MODE_OK;
पूर्ण
EXPORT_SYMBOL(drm_bridge_chain_mode_valid);

/**
 * drm_bridge_chain_disable - disables all bridges in the encoder chain
 * @bridge: bridge control काष्ठाure
 *
 * Calls &drm_bridge_funcs.disable op क्रम all the bridges in the encoder
 * chain, starting from the last bridge to the first. These are called beक्रमe
 * calling the encoder's prepare op.
 *
 * Note: the bridge passed should be the one बंदst to the encoder
 */
व्योम drm_bridge_chain_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_bridge *iter;

	अगर (!bridge)
		वापस;

	encoder = bridge->encoder;
	list_क्रम_each_entry_reverse(iter, &encoder->bridge_chain, chain_node) अणु
		अगर (iter->funcs->disable)
			iter->funcs->disable(iter);

		अगर (iter == bridge)
			अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_bridge_chain_disable);

/**
 * drm_bridge_chain_post_disable - cleans up after disabling all bridges in the
 *				   encoder chain
 * @bridge: bridge control काष्ठाure
 *
 * Calls &drm_bridge_funcs.post_disable op क्रम all the bridges in the
 * encoder chain, starting from the first bridge to the last. These are called
 * after completing the encoder's prepare op.
 *
 * Note: the bridge passed should be the one बंदst to the encoder
 */
व्योम drm_bridge_chain_post_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा drm_encoder *encoder;

	अगर (!bridge)
		वापस;

	encoder = bridge->encoder;
	list_क्रम_each_entry_from(bridge, &encoder->bridge_chain, chain_node) अणु
		अगर (bridge->funcs->post_disable)
			bridge->funcs->post_disable(bridge);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_bridge_chain_post_disable);

/**
 * drm_bridge_chain_mode_set - set proposed mode क्रम all bridges in the
 *			       encoder chain
 * @bridge: bridge control काष्ठाure
 * @mode: desired mode to be set क्रम the encoder chain
 * @adjusted_mode: updated mode that works क्रम this encoder chain
 *
 * Calls &drm_bridge_funcs.mode_set op क्रम all the bridges in the
 * encoder chain, starting from the first bridge to the last.
 *
 * Note: the bridge passed should be the one बंदst to the encoder
 */
व्योम drm_bridge_chain_mode_set(काष्ठा drm_bridge *bridge,
			       स्थिर काष्ठा drm_display_mode *mode,
			       स्थिर काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा drm_encoder *encoder;

	अगर (!bridge)
		वापस;

	encoder = bridge->encoder;
	list_क्रम_each_entry_from(bridge, &encoder->bridge_chain, chain_node) अणु
		अगर (bridge->funcs->mode_set)
			bridge->funcs->mode_set(bridge, mode, adjusted_mode);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_bridge_chain_mode_set);

/**
 * drm_bridge_chain_pre_enable - prepares क्रम enabling all bridges in the
 *				 encoder chain
 * @bridge: bridge control काष्ठाure
 *
 * Calls &drm_bridge_funcs.pre_enable op क्रम all the bridges in the encoder
 * chain, starting from the last bridge to the first. These are called
 * beक्रमe calling the encoder's commit op.
 *
 * Note: the bridge passed should be the one बंदst to the encoder
 */
व्योम drm_bridge_chain_pre_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_bridge *iter;

	अगर (!bridge)
		वापस;

	encoder = bridge->encoder;
	list_क्रम_each_entry_reverse(iter, &encoder->bridge_chain, chain_node) अणु
		अगर (iter->funcs->pre_enable)
			iter->funcs->pre_enable(iter);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_bridge_chain_pre_enable);

/**
 * drm_bridge_chain_enable - enables all bridges in the encoder chain
 * @bridge: bridge control काष्ठाure
 *
 * Calls &drm_bridge_funcs.enable op क्रम all the bridges in the encoder
 * chain, starting from the first bridge to the last. These are called
 * after completing the encoder's commit op.
 *
 * Note that the bridge passed should be the one बंदst to the encoder
 */
व्योम drm_bridge_chain_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा drm_encoder *encoder;

	अगर (!bridge)
		वापस;

	encoder = bridge->encoder;
	list_क्रम_each_entry_from(bridge, &encoder->bridge_chain, chain_node) अणु
		अगर (bridge->funcs->enable)
			bridge->funcs->enable(bridge);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_bridge_chain_enable);

/**
 * drm_atomic_bridge_chain_disable - disables all bridges in the encoder chain
 * @bridge: bridge control काष्ठाure
 * @old_state: old atomic state
 *
 * Calls &drm_bridge_funcs.atomic_disable (falls back on
 * &drm_bridge_funcs.disable) op क्रम all the bridges in the encoder chain,
 * starting from the last bridge to the first. These are called beक्रमe calling
 * &drm_encoder_helper_funcs.atomic_disable
 *
 * Note: the bridge passed should be the one बंदst to the encoder
 */
व्योम drm_atomic_bridge_chain_disable(काष्ठा drm_bridge *bridge,
				     काष्ठा drm_atomic_state *old_state)
अणु
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_bridge *iter;

	अगर (!bridge)
		वापस;

	encoder = bridge->encoder;
	list_क्रम_each_entry_reverse(iter, &encoder->bridge_chain, chain_node) अणु
		अगर (iter->funcs->atomic_disable) अणु
			काष्ठा drm_bridge_state *old_bridge_state;

			old_bridge_state =
				drm_atomic_get_old_bridge_state(old_state,
								iter);
			अगर (WARN_ON(!old_bridge_state))
				वापस;

			iter->funcs->atomic_disable(iter, old_bridge_state);
		पूर्ण अन्यथा अगर (iter->funcs->disable) अणु
			iter->funcs->disable(iter);
		पूर्ण

		अगर (iter == bridge)
			अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_atomic_bridge_chain_disable);

/**
 * drm_atomic_bridge_chain_post_disable - cleans up after disabling all bridges
 *					  in the encoder chain
 * @bridge: bridge control काष्ठाure
 * @old_state: old atomic state
 *
 * Calls &drm_bridge_funcs.atomic_post_disable (falls back on
 * &drm_bridge_funcs.post_disable) op क्रम all the bridges in the encoder chain,
 * starting from the first bridge to the last. These are called after completing
 * &drm_encoder_helper_funcs.atomic_disable
 *
 * Note: the bridge passed should be the one बंदst to the encoder
 */
व्योम drm_atomic_bridge_chain_post_disable(काष्ठा drm_bridge *bridge,
					  काष्ठा drm_atomic_state *old_state)
अणु
	काष्ठा drm_encoder *encoder;

	अगर (!bridge)
		वापस;

	encoder = bridge->encoder;
	list_क्रम_each_entry_from(bridge, &encoder->bridge_chain, chain_node) अणु
		अगर (bridge->funcs->atomic_post_disable) अणु
			काष्ठा drm_bridge_state *old_bridge_state;

			old_bridge_state =
				drm_atomic_get_old_bridge_state(old_state,
								bridge);
			अगर (WARN_ON(!old_bridge_state))
				वापस;

			bridge->funcs->atomic_post_disable(bridge,
							   old_bridge_state);
		पूर्ण अन्यथा अगर (bridge->funcs->post_disable) अणु
			bridge->funcs->post_disable(bridge);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_atomic_bridge_chain_post_disable);

/**
 * drm_atomic_bridge_chain_pre_enable - prepares क्रम enabling all bridges in
 *					the encoder chain
 * @bridge: bridge control काष्ठाure
 * @old_state: old atomic state
 *
 * Calls &drm_bridge_funcs.atomic_pre_enable (falls back on
 * &drm_bridge_funcs.pre_enable) op क्रम all the bridges in the encoder chain,
 * starting from the last bridge to the first. These are called beक्रमe calling
 * &drm_encoder_helper_funcs.atomic_enable
 *
 * Note: the bridge passed should be the one बंदst to the encoder
 */
व्योम drm_atomic_bridge_chain_pre_enable(काष्ठा drm_bridge *bridge,
					काष्ठा drm_atomic_state *old_state)
अणु
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_bridge *iter;

	अगर (!bridge)
		वापस;

	encoder = bridge->encoder;
	list_क्रम_each_entry_reverse(iter, &encoder->bridge_chain, chain_node) अणु
		अगर (iter->funcs->atomic_pre_enable) अणु
			काष्ठा drm_bridge_state *old_bridge_state;

			old_bridge_state =
				drm_atomic_get_old_bridge_state(old_state,
								iter);
			अगर (WARN_ON(!old_bridge_state))
				वापस;

			iter->funcs->atomic_pre_enable(iter, old_bridge_state);
		पूर्ण अन्यथा अगर (iter->funcs->pre_enable) अणु
			iter->funcs->pre_enable(iter);
		पूर्ण

		अगर (iter == bridge)
			अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_atomic_bridge_chain_pre_enable);

/**
 * drm_atomic_bridge_chain_enable - enables all bridges in the encoder chain
 * @bridge: bridge control काष्ठाure
 * @old_state: old atomic state
 *
 * Calls &drm_bridge_funcs.atomic_enable (falls back on
 * &drm_bridge_funcs.enable) op क्रम all the bridges in the encoder chain,
 * starting from the first bridge to the last. These are called after completing
 * &drm_encoder_helper_funcs.atomic_enable
 *
 * Note: the bridge passed should be the one बंदst to the encoder
 */
व्योम drm_atomic_bridge_chain_enable(काष्ठा drm_bridge *bridge,
				    काष्ठा drm_atomic_state *old_state)
अणु
	काष्ठा drm_encoder *encoder;

	अगर (!bridge)
		वापस;

	encoder = bridge->encoder;
	list_क्रम_each_entry_from(bridge, &encoder->bridge_chain, chain_node) अणु
		अगर (bridge->funcs->atomic_enable) अणु
			काष्ठा drm_bridge_state *old_bridge_state;

			old_bridge_state =
				drm_atomic_get_old_bridge_state(old_state,
								bridge);
			अगर (WARN_ON(!old_bridge_state))
				वापस;

			bridge->funcs->atomic_enable(bridge, old_bridge_state);
		पूर्ण अन्यथा अगर (bridge->funcs->enable) अणु
			bridge->funcs->enable(bridge);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_atomic_bridge_chain_enable);

अटल पूर्णांक drm_atomic_bridge_check(काष्ठा drm_bridge *bridge,
				   काष्ठा drm_crtc_state *crtc_state,
				   काष्ठा drm_connector_state *conn_state)
अणु
	अगर (bridge->funcs->atomic_check) अणु
		काष्ठा drm_bridge_state *bridge_state;
		पूर्णांक ret;

		bridge_state = drm_atomic_get_new_bridge_state(crtc_state->state,
							       bridge);
		अगर (WARN_ON(!bridge_state))
			वापस -EINVAL;

		ret = bridge->funcs->atomic_check(bridge, bridge_state,
						  crtc_state, conn_state);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अगर (bridge->funcs->mode_fixup) अणु
		अगर (!bridge->funcs->mode_fixup(bridge, &crtc_state->mode,
					       &crtc_state->adjusted_mode))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक select_bus_fmt_recursive(काष्ठा drm_bridge *first_bridge,
				    काष्ठा drm_bridge *cur_bridge,
				    काष्ठा drm_crtc_state *crtc_state,
				    काष्ठा drm_connector_state *conn_state,
				    u32 out_bus_fmt)
अणु
	काष्ठा drm_bridge_state *cur_state;
	अचिन्हित पूर्णांक num_in_bus_fmts, i;
	काष्ठा drm_bridge *prev_bridge;
	u32 *in_bus_fmts;
	पूर्णांक ret;

	prev_bridge = drm_bridge_get_prev_bridge(cur_bridge);
	cur_state = drm_atomic_get_new_bridge_state(crtc_state->state,
						    cur_bridge);

	/*
	 * If bus क्रमmat negotiation is not supported by this bridge, let's
	 * pass MEDIA_BUS_FMT_FIXED to the previous bridge in the chain and
	 * hope that it can handle this situation gracefully (by providing
	 * appropriate शेष values).
	 */
	अगर (!cur_bridge->funcs->atomic_get_input_bus_fmts) अणु
		अगर (cur_bridge != first_bridge) अणु
			ret = select_bus_fmt_recursive(first_bridge,
						       prev_bridge, crtc_state,
						       conn_state,
						       MEDIA_BUS_FMT_FIXED);
			अगर (ret)
				वापस ret;
		पूर्ण

		/*
		 * Driver करोes not implement the atomic state hooks, but that's
		 * fine, as दीर्घ as it करोes not access the bridge state.
		 */
		अगर (cur_state) अणु
			cur_state->input_bus_cfg.क्रमmat = MEDIA_BUS_FMT_FIXED;
			cur_state->output_bus_cfg.क्रमmat = out_bus_fmt;
		पूर्ण

		वापस 0;
	पूर्ण

	/*
	 * If the driver implements ->atomic_get_input_bus_fmts() it
	 * should also implement the atomic state hooks.
	 */
	अगर (WARN_ON(!cur_state))
		वापस -EINVAL;

	in_bus_fmts = cur_bridge->funcs->atomic_get_input_bus_fmts(cur_bridge,
							cur_state,
							crtc_state,
							conn_state,
							out_bus_fmt,
							&num_in_bus_fmts);
	अगर (!num_in_bus_fmts)
		वापस -ENOTSUPP;
	अन्यथा अगर (!in_bus_fmts)
		वापस -ENOMEM;

	अगर (first_bridge == cur_bridge) अणु
		cur_state->input_bus_cfg.क्रमmat = in_bus_fmts[0];
		cur_state->output_bus_cfg.क्रमmat = out_bus_fmt;
		kमुक्त(in_bus_fmts);
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < num_in_bus_fmts; i++) अणु
		ret = select_bus_fmt_recursive(first_bridge, prev_bridge,
					       crtc_state, conn_state,
					       in_bus_fmts[i]);
		अगर (ret != -ENOTSUPP)
			अवरोध;
	पूर्ण

	अगर (!ret) अणु
		cur_state->input_bus_cfg.क्रमmat = in_bus_fmts[i];
		cur_state->output_bus_cfg.क्रमmat = out_bus_fmt;
	पूर्ण

	kमुक्त(in_bus_fmts);
	वापस ret;
पूर्ण

/*
 * This function is called by &drm_atomic_bridge_chain_check() just beक्रमe
 * calling &drm_bridge_funcs.atomic_check() on all elements of the chain.
 * It perक्रमms bus क्रमmat negotiation between bridge elements. The negotiation
 * happens in reverse order, starting from the last element in the chain up to
 * @bridge.
 *
 * Negotiation starts by retrieving supported output bus क्रमmats on the last
 * bridge element and testing them one by one. The test is recursive, meaning
 * that क्रम each tested output क्रमmat, the whole chain will be walked backward,
 * and each element will have to choose an input bus क्रमmat that can be
 * transcoded to the requested output क्रमmat. When a bridge element करोes not
 * support transcoding पूर्णांकo a specअगरic output क्रमmat -ENOTSUPP is वापसed and
 * the next bridge element will have to try a dअगरferent क्रमmat. If none of the
 * combinations worked, -ENOTSUPP is वापसed and the atomic modeset will fail.
 *
 * This implementation is relying on
 * &drm_bridge_funcs.atomic_get_output_bus_fmts() and
 * &drm_bridge_funcs.atomic_get_input_bus_fmts() to gather supported
 * input/output क्रमmats.
 *
 * When &drm_bridge_funcs.atomic_get_output_bus_fmts() is not implemented by
 * the last element of the chain, &drm_atomic_bridge_chain_select_bus_fmts()
 * tries a single क्रमmat: &drm_connector.display_info.bus_क्रमmats[0] अगर
 * available, MEDIA_BUS_FMT_FIXED otherwise.
 *
 * When &drm_bridge_funcs.atomic_get_input_bus_fmts() is not implemented,
 * &drm_atomic_bridge_chain_select_bus_fmts() skips the negotiation on the
 * bridge element that lacks this hook and asks the previous element in the
 * chain to try MEDIA_BUS_FMT_FIXED. It's up to bridge drivers to decide what
 * to करो in that हाल (fail अगर they want to enक्रमce bus क्रमmat negotiation, or
 * provide a reasonable शेष अगर they need to support pipelines where not
 * all elements support bus क्रमmat negotiation).
 */
अटल पूर्णांक
drm_atomic_bridge_chain_select_bus_fmts(काष्ठा drm_bridge *bridge,
					काष्ठा drm_crtc_state *crtc_state,
					काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_connector *conn = conn_state->connector;
	काष्ठा drm_encoder *encoder = bridge->encoder;
	काष्ठा drm_bridge_state *last_bridge_state;
	अचिन्हित पूर्णांक i, num_out_bus_fmts;
	काष्ठा drm_bridge *last_bridge;
	u32 *out_bus_fmts;
	पूर्णांक ret = 0;

	last_bridge = list_last_entry(&encoder->bridge_chain,
				      काष्ठा drm_bridge, chain_node);
	last_bridge_state = drm_atomic_get_new_bridge_state(crtc_state->state,
							    last_bridge);

	अगर (last_bridge->funcs->atomic_get_output_bus_fmts) अणु
		स्थिर काष्ठा drm_bridge_funcs *funcs = last_bridge->funcs;

		/*
		 * If the driver implements ->atomic_get_output_bus_fmts() it
		 * should also implement the atomic state hooks.
		 */
		अगर (WARN_ON(!last_bridge_state))
			वापस -EINVAL;

		out_bus_fmts = funcs->atomic_get_output_bus_fmts(last_bridge,
							last_bridge_state,
							crtc_state,
							conn_state,
							&num_out_bus_fmts);
		अगर (!num_out_bus_fmts)
			वापस -ENOTSUPP;
		अन्यथा अगर (!out_bus_fmts)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		num_out_bus_fmts = 1;
		out_bus_fmts = kदो_स्मृति(माप(*out_bus_fmts), GFP_KERNEL);
		अगर (!out_bus_fmts)
			वापस -ENOMEM;

		अगर (conn->display_info.num_bus_क्रमmats &&
		    conn->display_info.bus_क्रमmats)
			out_bus_fmts[0] = conn->display_info.bus_क्रमmats[0];
		अन्यथा
			out_bus_fmts[0] = MEDIA_BUS_FMT_FIXED;
	पूर्ण

	क्रम (i = 0; i < num_out_bus_fmts; i++) अणु
		ret = select_bus_fmt_recursive(bridge, last_bridge, crtc_state,
					       conn_state, out_bus_fmts[i]);
		अगर (ret != -ENOTSUPP)
			अवरोध;
	पूर्ण

	kमुक्त(out_bus_fmts);

	वापस ret;
पूर्ण

अटल व्योम
drm_atomic_bridge_propagate_bus_flags(काष्ठा drm_bridge *bridge,
				      काष्ठा drm_connector *conn,
				      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_bridge_state *bridge_state, *next_bridge_state;
	काष्ठा drm_bridge *next_bridge;
	u32 output_flags = 0;

	bridge_state = drm_atomic_get_new_bridge_state(state, bridge);

	/* No bridge state attached to this bridge => nothing to propagate. */
	अगर (!bridge_state)
		वापस;

	next_bridge = drm_bridge_get_next_bridge(bridge);

	/*
	 * Let's try to apply the most common हाल here, that is, propagate
	 * display_info flags क्रम the last bridge, and propagate the input
	 * flags of the next bridge element to the output end of the current
	 * bridge when the bridge is not the last one.
	 * There are exceptions to this rule, like when संकेत inversion is
	 * happening at the board level, but that's something drivers can deal
	 * with from their &drm_bridge_funcs.atomic_check() implementation by
	 * simply overriding the flags value we've set here.
	 */
	अगर (!next_bridge) अणु
		output_flags = conn->display_info.bus_flags;
	पूर्ण अन्यथा अणु
		next_bridge_state = drm_atomic_get_new_bridge_state(state,
								next_bridge);
		/*
		 * No bridge state attached to the next bridge, just leave the
		 * flags to 0.
		 */
		अगर (next_bridge_state)
			output_flags = next_bridge_state->input_bus_cfg.flags;
	पूर्ण

	bridge_state->output_bus_cfg.flags = output_flags;

	/*
	 * Propage the output flags to the input end of the bridge. Again, it's
	 * not necessarily what all bridges want, but that's what most of them
	 * करो, and by करोing that by शेष we aव्योम क्रमcing drivers to
	 * duplicate the "dummy propagation" logic.
	 */
	bridge_state->input_bus_cfg.flags = output_flags;
पूर्ण

/**
 * drm_atomic_bridge_chain_check() - Do an atomic check on the bridge chain
 * @bridge: bridge control काष्ठाure
 * @crtc_state: new CRTC state
 * @conn_state: new connector state
 *
 * First trigger a bus क्रमmat negotiation beक्रमe calling
 * &drm_bridge_funcs.atomic_check() (falls back on
 * &drm_bridge_funcs.mode_fixup()) op क्रम all the bridges in the encoder chain,
 * starting from the last bridge to the first. These are called beक्रमe calling
 * &drm_encoder_helper_funcs.atomic_check()
 *
 * RETURNS:
 * 0 on success, a negative error code on failure
 */
पूर्णांक drm_atomic_bridge_chain_check(काष्ठा drm_bridge *bridge,
				  काष्ठा drm_crtc_state *crtc_state,
				  काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_connector *conn = conn_state->connector;
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_bridge *iter;
	पूर्णांक ret;

	अगर (!bridge)
		वापस 0;

	ret = drm_atomic_bridge_chain_select_bus_fmts(bridge, crtc_state,
						      conn_state);
	अगर (ret)
		वापस ret;

	encoder = bridge->encoder;
	list_क्रम_each_entry_reverse(iter, &encoder->bridge_chain, chain_node) अणु
		पूर्णांक ret;

		/*
		 * Bus flags are propagated by शेष. If a bridge needs to
		 * tweak the input bus flags क्रम any reason, it should happen
		 * in its &drm_bridge_funcs.atomic_check() implementation such
		 * that preceding bridges in the chain can propagate the new
		 * bus flags.
		 */
		drm_atomic_bridge_propagate_bus_flags(iter, conn,
						      crtc_state->state);

		ret = drm_atomic_bridge_check(iter, crtc_state, conn_state);
		अगर (ret)
			वापस ret;

		अगर (iter == bridge)
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_atomic_bridge_chain_check);

/**
 * drm_bridge_detect - check अगर anything is attached to the bridge output
 * @bridge: bridge control काष्ठाure
 *
 * If the bridge supports output detection, as reported by the
 * DRM_BRIDGE_OP_DETECT bridge ops flag, call &drm_bridge_funcs.detect क्रम the
 * bridge and वापस the connection status. Otherwise वापस
 * connector_status_unknown.
 *
 * RETURNS:
 * The detection status on success, or connector_status_unknown अगर the bridge
 * करोesn't support output detection.
 */
क्रमागत drm_connector_status drm_bridge_detect(काष्ठा drm_bridge *bridge)
अणु
	अगर (!(bridge->ops & DRM_BRIDGE_OP_DETECT))
		वापस connector_status_unknown;

	वापस bridge->funcs->detect(bridge);
पूर्ण
EXPORT_SYMBOL_GPL(drm_bridge_detect);

/**
 * drm_bridge_get_modes - fill all modes currently valid क्रम the sink पूर्णांकo the
 * @connector
 * @bridge: bridge control काष्ठाure
 * @connector: the connector to fill with modes
 *
 * If the bridge supports output modes retrieval, as reported by the
 * DRM_BRIDGE_OP_MODES bridge ops flag, call &drm_bridge_funcs.get_modes to
 * fill the connector with all valid modes and वापस the number of modes
 * added. Otherwise वापस 0.
 *
 * RETURNS:
 * The number of modes added to the connector.
 */
पूर्णांक drm_bridge_get_modes(काष्ठा drm_bridge *bridge,
			 काष्ठा drm_connector *connector)
अणु
	अगर (!(bridge->ops & DRM_BRIDGE_OP_MODES))
		वापस 0;

	वापस bridge->funcs->get_modes(bridge, connector);
पूर्ण
EXPORT_SYMBOL_GPL(drm_bridge_get_modes);

/**
 * drm_bridge_get_edid - get the EDID data of the connected display
 * @bridge: bridge control काष्ठाure
 * @connector: the connector to पढ़ो EDID क्रम
 *
 * If the bridge supports output EDID retrieval, as reported by the
 * DRM_BRIDGE_OP_EDID bridge ops flag, call &drm_bridge_funcs.get_edid to
 * get the EDID and वापस it. Otherwise वापस शून्य.
 *
 * RETURNS:
 * The retrieved EDID on success, or शून्य otherwise.
 */
काष्ठा edid *drm_bridge_get_edid(काष्ठा drm_bridge *bridge,
				 काष्ठा drm_connector *connector)
अणु
	अगर (!(bridge->ops & DRM_BRIDGE_OP_EDID))
		वापस शून्य;

	वापस bridge->funcs->get_edid(bridge, connector);
पूर्ण
EXPORT_SYMBOL_GPL(drm_bridge_get_edid);

/**
 * drm_bridge_hpd_enable - enable hot plug detection क्रम the bridge
 * @bridge: bridge control काष्ठाure
 * @cb: hot-plug detection callback
 * @data: data to be passed to the hot-plug detection callback
 *
 * Call &drm_bridge_funcs.hpd_enable अगर implemented and रेजिस्टर the given @cb
 * and @data as hot plug notअगरication callback. From now on the @cb will be
 * called with @data when an output status change is detected by the bridge,
 * until hot plug notअगरication माला_लो disabled with drm_bridge_hpd_disable().
 *
 * Hot plug detection is supported only अगर the DRM_BRIDGE_OP_HPD flag is set in
 * bridge->ops. This function shall not be called when the flag is not set.
 *
 * Only one hot plug detection callback can be रेजिस्टरed at a समय, it is an
 * error to call this function when hot plug detection is alपढ़ोy enabled क्रम
 * the bridge.
 */
व्योम drm_bridge_hpd_enable(काष्ठा drm_bridge *bridge,
			   व्योम (*cb)(व्योम *data,
				      क्रमागत drm_connector_status status),
			   व्योम *data)
अणु
	अगर (!(bridge->ops & DRM_BRIDGE_OP_HPD))
		वापस;

	mutex_lock(&bridge->hpd_mutex);

	अगर (WARN(bridge->hpd_cb, "Hot plug detection already enabled\n"))
		जाओ unlock;

	bridge->hpd_cb = cb;
	bridge->hpd_data = data;

	अगर (bridge->funcs->hpd_enable)
		bridge->funcs->hpd_enable(bridge);

unlock:
	mutex_unlock(&bridge->hpd_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(drm_bridge_hpd_enable);

/**
 * drm_bridge_hpd_disable - disable hot plug detection क्रम the bridge
 * @bridge: bridge control काष्ठाure
 *
 * Call &drm_bridge_funcs.hpd_disable अगर implemented and unरेजिस्टर the hot
 * plug detection callback previously रेजिस्टरed with drm_bridge_hpd_enable().
 * Once this function वापसs the callback will not be called by the bridge
 * when an output status change occurs.
 *
 * Hot plug detection is supported only अगर the DRM_BRIDGE_OP_HPD flag is set in
 * bridge->ops. This function shall not be called when the flag is not set.
 */
व्योम drm_bridge_hpd_disable(काष्ठा drm_bridge *bridge)
अणु
	अगर (!(bridge->ops & DRM_BRIDGE_OP_HPD))
		वापस;

	mutex_lock(&bridge->hpd_mutex);
	अगर (bridge->funcs->hpd_disable)
		bridge->funcs->hpd_disable(bridge);

	bridge->hpd_cb = शून्य;
	bridge->hpd_data = शून्य;
	mutex_unlock(&bridge->hpd_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(drm_bridge_hpd_disable);

/**
 * drm_bridge_hpd_notअगरy - notअगरy hot plug detection events
 * @bridge: bridge control काष्ठाure
 * @status: output connection status
 *
 * Bridge drivers shall call this function to report hot plug events when they
 * detect a change in the output status, when hot plug detection has been
 * enabled by drm_bridge_hpd_enable().
 *
 * This function shall be called in a context that can sleep.
 */
व्योम drm_bridge_hpd_notअगरy(काष्ठा drm_bridge *bridge,
			   क्रमागत drm_connector_status status)
अणु
	mutex_lock(&bridge->hpd_mutex);
	अगर (bridge->hpd_cb)
		bridge->hpd_cb(bridge->hpd_data, status);
	mutex_unlock(&bridge->hpd_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(drm_bridge_hpd_notअगरy);

#अगर_घोषित CONFIG_OF
/**
 * of_drm_find_bridge - find the bridge corresponding to the device node in
 *			the global bridge list
 *
 * @np: device node
 *
 * RETURNS:
 * drm_bridge control काष्ठा on success, शून्य on failure
 */
काष्ठा drm_bridge *of_drm_find_bridge(काष्ठा device_node *np)
अणु
	काष्ठा drm_bridge *bridge;

	mutex_lock(&bridge_lock);

	list_क्रम_each_entry(bridge, &bridge_list, list) अणु
		अगर (bridge->of_node == np) अणु
			mutex_unlock(&bridge_lock);
			वापस bridge;
		पूर्ण
	पूर्ण

	mutex_unlock(&bridge_lock);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(of_drm_find_bridge);
#पूर्ण_अगर

MODULE_AUTHOR("Ajay Kumar <ajaykumar.rs@samsung.com>");
MODULE_DESCRIPTION("DRM bridge infrastructure");
MODULE_LICENSE("GPL and additional rights");
