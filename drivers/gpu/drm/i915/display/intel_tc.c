<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश "i915_drv.h"
#समावेश "intel_display.h"
#समावेश "intel_display_types.h"
#समावेश "intel_dp_mst.h"
#समावेश "intel_tc.h"

अटल स्थिर अक्षर *tc_port_mode_name(क्रमागत tc_port_mode mode)
अणु
	अटल स्थिर अक्षर * स्थिर names[] = अणु
		[TC_PORT_TBT_ALT] = "tbt-alt",
		[TC_PORT_DP_ALT] = "dp-alt",
		[TC_PORT_LEGACY] = "legacy",
	पूर्ण;

	अगर (WARN_ON(mode >= ARRAY_SIZE(names)))
		mode = TC_PORT_TBT_ALT;

	वापस names[mode];
पूर्ण

अटल क्रमागत पूर्णांकel_display_घातer_करोमुख्य
tc_cold_get_घातer_करोमुख्य(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);

	अगर (IS_DISPLAY_VER(i915, 11))
		वापस पूर्णांकel_legacy_aux_to_घातer_करोमुख्य(dig_port->aux_ch);
	अन्यथा
		वापस POWER_DOMAIN_TC_COLD_OFF;
पूर्ण

अटल पूर्णांकel_wakeref_t
tc_cold_block(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य;

	अगर (IS_DISPLAY_VER(i915, 11) && !dig_port->tc_legacy_port)
		वापस 0;

	करोमुख्य = tc_cold_get_घातer_करोमुख्य(dig_port);
	वापस पूर्णांकel_display_घातer_get(i915, करोमुख्य);
पूर्ण

अटल व्योम
tc_cold_unblock(काष्ठा पूर्णांकel_digital_port *dig_port, पूर्णांकel_wakeref_t wakeref)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य;

	/*
	 * wakeref == -1, means some error happened saving save_depot_stack but
	 * घातer should still be put करोwn and 0 is a invalid save_depot_stack
	 * id so can be used to skip it क्रम non TC legacy ports.
	 */
	अगर (wakeref == 0)
		वापस;

	करोमुख्य = tc_cold_get_घातer_करोमुख्य(dig_port);
	पूर्णांकel_display_घातer_put_async(i915, करोमुख्य, wakeref);
पूर्ण

अटल व्योम
निश्चित_tc_cold_blocked(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	bool enabled;

	अगर (IS_DISPLAY_VER(i915, 11) && !dig_port->tc_legacy_port)
		वापस;

	enabled = पूर्णांकel_display_घातer_is_enabled(i915,
						 tc_cold_get_घातer_करोमुख्य(dig_port));
	drm_WARN_ON(&i915->drm, !enabled);
पूर्ण

u32 पूर्णांकel_tc_port_get_lane_mask(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	काष्ठा पूर्णांकel_uncore *uncore = &i915->uncore;
	u32 lane_mask;

	lane_mask = पूर्णांकel_uncore_पढ़ो(uncore,
				      PORT_TX_DFLEXDPSP(dig_port->tc_phy_fia));

	drm_WARN_ON(&i915->drm, lane_mask == 0xffffffff);
	निश्चित_tc_cold_blocked(dig_port);

	lane_mask &= DP_LANE_ASSIGNMENT_MASK(dig_port->tc_phy_fia_idx);
	वापस lane_mask >> DP_LANE_ASSIGNMENT_SHIFT(dig_port->tc_phy_fia_idx);
पूर्ण

u32 पूर्णांकel_tc_port_get_pin_assignment_mask(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	काष्ठा पूर्णांकel_uncore *uncore = &i915->uncore;
	u32 pin_mask;

	pin_mask = पूर्णांकel_uncore_पढ़ो(uncore,
				     PORT_TX_DFLEXPA1(dig_port->tc_phy_fia));

	drm_WARN_ON(&i915->drm, pin_mask == 0xffffffff);
	निश्चित_tc_cold_blocked(dig_port);

	वापस (pin_mask & DP_PIN_ASSIGNMENT_MASK(dig_port->tc_phy_fia_idx)) >>
	       DP_PIN_ASSIGNMENT_SHIFT(dig_port->tc_phy_fia_idx);
पूर्ण

पूर्णांक पूर्णांकel_tc_port_fia_max_lane_count(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	पूर्णांकel_wakeref_t wakeref;
	u32 lane_mask;

	अगर (dig_port->tc_mode != TC_PORT_DP_ALT)
		वापस 4;

	निश्चित_tc_cold_blocked(dig_port);

	lane_mask = 0;
	with_पूर्णांकel_display_घातer(i915, POWER_DOMAIN_DISPLAY_CORE, wakeref)
		lane_mask = पूर्णांकel_tc_port_get_lane_mask(dig_port);

	चयन (lane_mask) अणु
	शेष:
		MISSING_CASE(lane_mask);
		fallthrough;
	हाल 0x1:
	हाल 0x2:
	हाल 0x4:
	हाल 0x8:
		वापस 1;
	हाल 0x3:
	हाल 0xc:
		वापस 2;
	हाल 0xf:
		वापस 4;
	पूर्ण
पूर्ण

व्योम पूर्णांकel_tc_port_set_fia_lane_count(काष्ठा पूर्णांकel_digital_port *dig_port,
				      पूर्णांक required_lanes)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	bool lane_reversal = dig_port->saved_port_bits & DDI_BUF_PORT_REVERSAL;
	काष्ठा पूर्णांकel_uncore *uncore = &i915->uncore;
	u32 val;

	drm_WARN_ON(&i915->drm,
		    lane_reversal && dig_port->tc_mode != TC_PORT_LEGACY);

	निश्चित_tc_cold_blocked(dig_port);

	val = पूर्णांकel_uncore_पढ़ो(uncore,
				PORT_TX_DFLEXDPMLE1(dig_port->tc_phy_fia));
	val &= ~DFLEXDPMLE1_DPMLETC_MASK(dig_port->tc_phy_fia_idx);

	चयन (required_lanes) अणु
	हाल 1:
		val |= lane_reversal ?
			DFLEXDPMLE1_DPMLETC_ML3(dig_port->tc_phy_fia_idx) :
			DFLEXDPMLE1_DPMLETC_ML0(dig_port->tc_phy_fia_idx);
		अवरोध;
	हाल 2:
		val |= lane_reversal ?
			DFLEXDPMLE1_DPMLETC_ML3_2(dig_port->tc_phy_fia_idx) :
			DFLEXDPMLE1_DPMLETC_ML1_0(dig_port->tc_phy_fia_idx);
		अवरोध;
	हाल 4:
		val |= DFLEXDPMLE1_DPMLETC_ML3_0(dig_port->tc_phy_fia_idx);
		अवरोध;
	शेष:
		MISSING_CASE(required_lanes);
	पूर्ण

	पूर्णांकel_uncore_ग_लिखो(uncore,
			   PORT_TX_DFLEXDPMLE1(dig_port->tc_phy_fia), val);
पूर्ण

अटल व्योम tc_port_fixup_legacy_flag(काष्ठा पूर्णांकel_digital_port *dig_port,
				      u32 live_status_mask)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	u32 valid_hpd_mask;

	अगर (dig_port->tc_legacy_port)
		valid_hpd_mask = BIT(TC_PORT_LEGACY);
	अन्यथा
		valid_hpd_mask = BIT(TC_PORT_DP_ALT) |
				 BIT(TC_PORT_TBT_ALT);

	अगर (!(live_status_mask & ~valid_hpd_mask))
		वापस;

	/* If live status mismatches the VBT flag, trust the live status. */
	drm_dbg_kms(&i915->drm,
		    "Port %s: live status %08x mismatches the legacy port flag %08x, fixing flag\n",
		    dig_port->tc_port_name, live_status_mask, valid_hpd_mask);

	dig_port->tc_legacy_port = !dig_port->tc_legacy_port;
पूर्ण

अटल u32 tc_port_live_status_mask(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	काष्ठा पूर्णांकel_uncore *uncore = &i915->uncore;
	u32 isr_bit = i915->hotplug.pch_hpd[dig_port->base.hpd_pin];
	u32 mask = 0;
	u32 val;

	val = पूर्णांकel_uncore_पढ़ो(uncore,
				PORT_TX_DFLEXDPSP(dig_port->tc_phy_fia));

	अगर (val == 0xffffffff) अणु
		drm_dbg_kms(&i915->drm,
			    "Port %s: PHY in TCCOLD, nothing connected\n",
			    dig_port->tc_port_name);
		वापस mask;
	पूर्ण

	अगर (val & TC_LIVE_STATE_TBT(dig_port->tc_phy_fia_idx))
		mask |= BIT(TC_PORT_TBT_ALT);
	अगर (val & TC_LIVE_STATE_TC(dig_port->tc_phy_fia_idx))
		mask |= BIT(TC_PORT_DP_ALT);

	अगर (पूर्णांकel_uncore_पढ़ो(uncore, SDEISR) & isr_bit)
		mask |= BIT(TC_PORT_LEGACY);

	/* The sink can be connected only in a single mode. */
	अगर (!drm_WARN_ON_ONCE(&i915->drm, hweight32(mask) > 1))
		tc_port_fixup_legacy_flag(dig_port, mask);

	वापस mask;
पूर्ण

अटल bool icl_tc_phy_status_complete(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	काष्ठा पूर्णांकel_uncore *uncore = &i915->uncore;
	u32 val;

	val = पूर्णांकel_uncore_पढ़ो(uncore,
				PORT_TX_DFLEXDPPMS(dig_port->tc_phy_fia));
	अगर (val == 0xffffffff) अणु
		drm_dbg_kms(&i915->drm,
			    "Port %s: PHY in TCCOLD, assuming not complete\n",
			    dig_port->tc_port_name);
		वापस false;
	पूर्ण

	वापस val & DP_PHY_MODE_STATUS_COMPLETED(dig_port->tc_phy_fia_idx);
पूर्ण

अटल bool icl_tc_phy_set_safe_mode(काष्ठा पूर्णांकel_digital_port *dig_port,
				     bool enable)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	काष्ठा पूर्णांकel_uncore *uncore = &i915->uncore;
	u32 val;

	val = पूर्णांकel_uncore_पढ़ो(uncore,
				PORT_TX_DFLEXDPCSSS(dig_port->tc_phy_fia));
	अगर (val == 0xffffffff) अणु
		drm_dbg_kms(&i915->drm,
			    "Port %s: PHY in TCCOLD, can't set safe-mode to %s\n",
			    dig_port->tc_port_name, enableddisabled(enable));

		वापस false;
	पूर्ण

	val &= ~DP_PHY_MODE_STATUS_NOT_SAFE(dig_port->tc_phy_fia_idx);
	अगर (!enable)
		val |= DP_PHY_MODE_STATUS_NOT_SAFE(dig_port->tc_phy_fia_idx);

	पूर्णांकel_uncore_ग_लिखो(uncore,
			   PORT_TX_DFLEXDPCSSS(dig_port->tc_phy_fia), val);

	अगर (enable && रुको_क्रम(!icl_tc_phy_status_complete(dig_port), 10))
		drm_dbg_kms(&i915->drm,
			    "Port %s: PHY complete clear timed out\n",
			    dig_port->tc_port_name);

	वापस true;
पूर्ण

अटल bool icl_tc_phy_is_in_safe_mode(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	काष्ठा पूर्णांकel_uncore *uncore = &i915->uncore;
	u32 val;

	val = पूर्णांकel_uncore_पढ़ो(uncore,
				PORT_TX_DFLEXDPCSSS(dig_port->tc_phy_fia));
	अगर (val == 0xffffffff) अणु
		drm_dbg_kms(&i915->drm,
			    "Port %s: PHY in TCCOLD, assume safe mode\n",
			    dig_port->tc_port_name);
		वापस true;
	पूर्ण

	वापस !(val & DP_PHY_MODE_STATUS_NOT_SAFE(dig_port->tc_phy_fia_idx));
पूर्ण

/*
 * This function implements the first part of the Connect Flow described by our
 * specअगरication, Gen11 TypeC Programming chapter. The rest of the flow (पढ़ोing
 * lanes, EDID, etc) is करोne as needed in the typical places.
 *
 * Unlike the other ports, type-C ports are not available to use as soon as we
 * get a hotplug. The type-C PHYs can be shared between multiple controllers:
 * display, USB, etc. As a result, handshaking through FIA is required around
 * connect and disconnect to cleanly transfer ownership with the controller and
 * set the type-C घातer state.
 */
अटल व्योम icl_tc_phy_connect(काष्ठा पूर्णांकel_digital_port *dig_port,
			       पूर्णांक required_lanes)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	पूर्णांक max_lanes;

	अगर (!icl_tc_phy_status_complete(dig_port)) अणु
		drm_dbg_kms(&i915->drm, "Port %s: PHY not ready\n",
			    dig_port->tc_port_name);
		जाओ out_set_tbt_alt_mode;
	पूर्ण

	अगर (!icl_tc_phy_set_safe_mode(dig_port, false) &&
	    !drm_WARN_ON(&i915->drm, dig_port->tc_legacy_port))
		जाओ out_set_tbt_alt_mode;

	max_lanes = पूर्णांकel_tc_port_fia_max_lane_count(dig_port);
	अगर (dig_port->tc_legacy_port) अणु
		drm_WARN_ON(&i915->drm, max_lanes != 4);
		dig_port->tc_mode = TC_PORT_LEGACY;

		वापस;
	पूर्ण

	/*
	 * Now we have to re-check the live state, in हाल the port recently
	 * became disconnected. Not necessary क्रम legacy mode.
	 */
	अगर (!(tc_port_live_status_mask(dig_port) & BIT(TC_PORT_DP_ALT))) अणु
		drm_dbg_kms(&i915->drm, "Port %s: PHY sudden disconnect\n",
			    dig_port->tc_port_name);
		जाओ out_set_safe_mode;
	पूर्ण

	अगर (max_lanes < required_lanes) अणु
		drm_dbg_kms(&i915->drm,
			    "Port %s: PHY max lanes %d < required lanes %d\n",
			    dig_port->tc_port_name,
			    max_lanes, required_lanes);
		जाओ out_set_safe_mode;
	पूर्ण

	dig_port->tc_mode = TC_PORT_DP_ALT;

	वापस;

out_set_safe_mode:
	icl_tc_phy_set_safe_mode(dig_port, true);
out_set_tbt_alt_mode:
	dig_port->tc_mode = TC_PORT_TBT_ALT;
पूर्ण

/*
 * See the comment at the connect function. This implements the Disconnect
 * Flow.
 */
अटल व्योम icl_tc_phy_disconnect(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	चयन (dig_port->tc_mode) अणु
	हाल TC_PORT_LEGACY:
		/* Nothing to करो, we never disconnect from legacy mode */
		अवरोध;
	हाल TC_PORT_DP_ALT:
		icl_tc_phy_set_safe_mode(dig_port, true);
		dig_port->tc_mode = TC_PORT_TBT_ALT;
		अवरोध;
	हाल TC_PORT_TBT_ALT:
		/* Nothing to करो, we stay in TBT-alt mode */
		अवरोध;
	शेष:
		MISSING_CASE(dig_port->tc_mode);
	पूर्ण
पूर्ण

अटल bool icl_tc_phy_is_connected(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);

	अगर (!icl_tc_phy_status_complete(dig_port)) अणु
		drm_dbg_kms(&i915->drm, "Port %s: PHY status not complete\n",
			    dig_port->tc_port_name);
		वापस dig_port->tc_mode == TC_PORT_TBT_ALT;
	पूर्ण

	अगर (icl_tc_phy_is_in_safe_mode(dig_port)) अणु
		drm_dbg_kms(&i915->drm, "Port %s: PHY still in safe mode\n",
			    dig_port->tc_port_name);

		वापस false;
	पूर्ण

	वापस dig_port->tc_mode == TC_PORT_DP_ALT ||
	       dig_port->tc_mode == TC_PORT_LEGACY;
पूर्ण

अटल क्रमागत tc_port_mode
पूर्णांकel_tc_port_get_current_mode(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	u32 live_status_mask = tc_port_live_status_mask(dig_port);
	bool in_safe_mode = icl_tc_phy_is_in_safe_mode(dig_port);
	क्रमागत tc_port_mode mode;

	अगर (in_safe_mode ||
	    drm_WARN_ON(&i915->drm, !icl_tc_phy_status_complete(dig_port)))
		वापस TC_PORT_TBT_ALT;

	mode = dig_port->tc_legacy_port ? TC_PORT_LEGACY : TC_PORT_DP_ALT;
	अगर (live_status_mask) अणु
		क्रमागत tc_port_mode live_mode = fls(live_status_mask) - 1;

		अगर (!drm_WARN_ON(&i915->drm, live_mode == TC_PORT_TBT_ALT))
			mode = live_mode;
	पूर्ण

	वापस mode;
पूर्ण

अटल क्रमागत tc_port_mode
पूर्णांकel_tc_port_get_target_mode(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	u32 live_status_mask = tc_port_live_status_mask(dig_port);

	अगर (live_status_mask)
		वापस fls(live_status_mask) - 1;

	वापस icl_tc_phy_status_complete(dig_port) &&
	       dig_port->tc_legacy_port ? TC_PORT_LEGACY :
					  TC_PORT_TBT_ALT;
पूर्ण

अटल व्योम पूर्णांकel_tc_port_reset_mode(काष्ठा पूर्णांकel_digital_port *dig_port,
				     पूर्णांक required_lanes)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	क्रमागत tc_port_mode old_tc_mode = dig_port->tc_mode;

	पूर्णांकel_display_घातer_flush_work(i915);
	अगर (DISPLAY_VER(i915) != 11 || !dig_port->tc_legacy_port) अणु
		क्रमागत पूर्णांकel_display_घातer_करोमुख्य aux_करोमुख्य;
		bool aux_घातered;

		aux_करोमुख्य = पूर्णांकel_aux_घातer_करोमुख्य(dig_port);
		aux_घातered = पूर्णांकel_display_घातer_is_enabled(i915, aux_करोमुख्य);
		drm_WARN_ON(&i915->drm, aux_घातered);
	पूर्ण

	icl_tc_phy_disconnect(dig_port);
	icl_tc_phy_connect(dig_port, required_lanes);

	drm_dbg_kms(&i915->drm, "Port %s: TC port mode reset (%s -> %s)\n",
		    dig_port->tc_port_name,
		    tc_port_mode_name(old_tc_mode),
		    tc_port_mode_name(dig_port->tc_mode));
पूर्ण

अटल व्योम
पूर्णांकel_tc_port_link_init_refcount(काष्ठा पूर्णांकel_digital_port *dig_port,
				 पूर्णांक refcount)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);

	drm_WARN_ON(&i915->drm, dig_port->tc_link_refcount);
	dig_port->tc_link_refcount = refcount;
पूर्ण

व्योम पूर्णांकel_tc_port_sanitize(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	काष्ठा पूर्णांकel_encoder *encoder = &dig_port->base;
	पूर्णांकel_wakeref_t tc_cold_wref;
	पूर्णांक active_links = 0;

	mutex_lock(&dig_port->tc_lock);
	tc_cold_wref = tc_cold_block(dig_port);

	dig_port->tc_mode = पूर्णांकel_tc_port_get_current_mode(dig_port);
	अगर (dig_port->dp.is_mst)
		active_links = पूर्णांकel_dp_mst_encoder_active_links(dig_port);
	अन्यथा अगर (encoder->base.crtc)
		active_links = to_पूर्णांकel_crtc(encoder->base.crtc)->active;

	अगर (active_links) अणु
		अगर (!icl_tc_phy_is_connected(dig_port))
			drm_dbg_kms(&i915->drm,
				    "Port %s: PHY disconnected with %d active link(s)\n",
				    dig_port->tc_port_name, active_links);
		पूर्णांकel_tc_port_link_init_refcount(dig_port, active_links);

		जाओ out;
	पूर्ण

	अगर (dig_port->tc_legacy_port)
		icl_tc_phy_connect(dig_port, 1);

out:
	drm_dbg_kms(&i915->drm, "Port %s: sanitize mode (%s)\n",
		    dig_port->tc_port_name,
		    tc_port_mode_name(dig_port->tc_mode));

	tc_cold_unblock(dig_port, tc_cold_wref);
	mutex_unlock(&dig_port->tc_lock);
पूर्ण

अटल bool पूर्णांकel_tc_port_needs_reset(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	वापस पूर्णांकel_tc_port_get_target_mode(dig_port) != dig_port->tc_mode;
पूर्ण

/*
 * The type-C ports are dअगरferent because even when they are connected, they may
 * not be available/usable by the graphics driver: see the comment on
 * icl_tc_phy_connect(). So in our driver instead of adding the additional
 * concept of "usable" and make everything check क्रम "connected and usable" we
 * define a port as "connected" when it is not only connected, but also when it
 * is usable by the rest of the driver. That मुख्यtains the old assumption that
 * connected ports are usable, and aव्योमs exposing to the users objects they
 * can't really use.
 */
bool पूर्णांकel_tc_port_connected(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	bool is_connected;
	पूर्णांकel_wakeref_t tc_cold_wref;

	पूर्णांकel_tc_port_lock(dig_port);
	tc_cold_wref = tc_cold_block(dig_port);

	is_connected = tc_port_live_status_mask(dig_port) &
		       BIT(dig_port->tc_mode);

	tc_cold_unblock(dig_port, tc_cold_wref);
	पूर्णांकel_tc_port_unlock(dig_port);

	वापस is_connected;
पूर्ण

अटल व्योम __पूर्णांकel_tc_port_lock(काष्ठा पूर्णांकel_digital_port *dig_port,
				 पूर्णांक required_lanes)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	पूर्णांकel_wakeref_t wakeref;

	wakeref = पूर्णांकel_display_घातer_get(i915, POWER_DOMAIN_DISPLAY_CORE);

	mutex_lock(&dig_port->tc_lock);

	अगर (!dig_port->tc_link_refcount) अणु
		पूर्णांकel_wakeref_t tc_cold_wref;

		tc_cold_wref = tc_cold_block(dig_port);

		अगर (पूर्णांकel_tc_port_needs_reset(dig_port))
			पूर्णांकel_tc_port_reset_mode(dig_port, required_lanes);

		tc_cold_unblock(dig_port, tc_cold_wref);
	पूर्ण

	drm_WARN_ON(&i915->drm, dig_port->tc_lock_wakeref);
	dig_port->tc_lock_wakeref = wakeref;
पूर्ण

व्योम पूर्णांकel_tc_port_lock(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	__पूर्णांकel_tc_port_lock(dig_port, 1);
पूर्ण

व्योम पूर्णांकel_tc_port_unlock(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	पूर्णांकel_wakeref_t wakeref = fetch_and_zero(&dig_port->tc_lock_wakeref);

	mutex_unlock(&dig_port->tc_lock);

	पूर्णांकel_display_घातer_put_async(i915, POWER_DOMAIN_DISPLAY_CORE,
				      wakeref);
पूर्ण

bool पूर्णांकel_tc_port_ref_held(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	वापस mutex_is_locked(&dig_port->tc_lock) ||
	       dig_port->tc_link_refcount;
पूर्ण

व्योम पूर्णांकel_tc_port_get_link(काष्ठा पूर्णांकel_digital_port *dig_port,
			    पूर्णांक required_lanes)
अणु
	__पूर्णांकel_tc_port_lock(dig_port, required_lanes);
	dig_port->tc_link_refcount++;
	पूर्णांकel_tc_port_unlock(dig_port);
पूर्ण

व्योम पूर्णांकel_tc_port_put_link(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	mutex_lock(&dig_port->tc_lock);
	dig_port->tc_link_refcount--;
	mutex_unlock(&dig_port->tc_lock);
पूर्ण

अटल bool
tc_has_modular_fia(काष्ठा drm_i915_निजी *i915, काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	पूर्णांकel_wakeref_t wakeref;
	u32 val;

	अगर (!INTEL_INFO(i915)->display.has_modular_fia)
		वापस false;

	wakeref = tc_cold_block(dig_port);
	val = पूर्णांकel_uncore_पढ़ो(&i915->uncore, PORT_TX_DFLEXDPSP(FIA1));
	tc_cold_unblock(dig_port, wakeref);

	drm_WARN_ON(&i915->drm, val == 0xffffffff);

	वापस val & MODULAR_FIA_MASK;
पूर्ण

अटल व्योम
tc_port_load_fia_params(काष्ठा drm_i915_निजी *i915, काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	क्रमागत port port = dig_port->base.port;
	क्रमागत tc_port tc_port = पूर्णांकel_port_to_tc(i915, port);

	/*
	 * Each Modular FIA instance houses 2 TC ports. In SOC that has more
	 * than two TC ports, there are multiple instances of Modular FIA.
	 */
	अगर (tc_has_modular_fia(i915, dig_port)) अणु
		dig_port->tc_phy_fia = tc_port / 2;
		dig_port->tc_phy_fia_idx = tc_port % 2;
	पूर्ण अन्यथा अणु
		dig_port->tc_phy_fia = FIA1;
		dig_port->tc_phy_fia_idx = tc_port;
	पूर्ण
पूर्ण

व्योम पूर्णांकel_tc_port_init(काष्ठा पूर्णांकel_digital_port *dig_port, bool is_legacy)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	क्रमागत port port = dig_port->base.port;
	क्रमागत tc_port tc_port = पूर्णांकel_port_to_tc(i915, port);

	अगर (drm_WARN_ON(&i915->drm, tc_port == TC_PORT_NONE))
		वापस;

	snम_लिखो(dig_port->tc_port_name, माप(dig_port->tc_port_name),
		 "%c/TC#%d", port_name(port), tc_port + 1);

	mutex_init(&dig_port->tc_lock);
	dig_port->tc_legacy_port = is_legacy;
	dig_port->tc_link_refcount = 0;
	tc_port_load_fia_params(i915, dig_port);
पूर्ण
