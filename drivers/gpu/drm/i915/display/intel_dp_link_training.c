<शैली गुरु>
/*
 * Copyright तऊ 2008-2015 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#समावेश "intel_display_types.h"
#समावेश "intel_dp.h"
#समावेश "intel_dp_link_training.h"

अटल व्योम
पूर्णांकel_dp_dump_link_status(काष्ठा drm_device *drm,
			  स्थिर u8 link_status[DP_LINK_STATUS_SIZE])
अणु
	drm_dbg_kms(drm,
		    "ln0_1:0x%x ln2_3:0x%x align:0x%x sink:0x%x adj_req0_1:0x%x adj_req2_3:0x%x\n",
		    link_status[0], link_status[1], link_status[2],
		    link_status[3], link_status[4], link_status[5]);
पूर्ण

अटल व्योम पूर्णांकel_dp_reset_lttpr_common_caps(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	स_रखो(&पूर्णांकel_dp->lttpr_common_caps, 0, माप(पूर्णांकel_dp->lttpr_common_caps));
पूर्ण

अटल व्योम पूर्णांकel_dp_reset_lttpr_count(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	पूर्णांकel_dp->lttpr_common_caps[DP_PHY_REPEATER_CNT -
				    DP_LT_TUNABLE_PHY_REPEATER_FIELD_DATA_STRUCTURE_REV] = 0;
पूर्ण

अटल स्थिर अक्षर *पूर्णांकel_dp_phy_name(क्रमागत drm_dp_phy dp_phy,
				     अक्षर *buf, माप_प्रकार buf_size)
अणु
	अगर (dp_phy == DP_PHY_DPRX)
		snम_लिखो(buf, buf_size, "DPRX");
	अन्यथा
		snम_लिखो(buf, buf_size, "LTTPR %d", dp_phy - DP_PHY_LTTPR1 + 1);

	वापस buf;
पूर्ण

अटल u8 *पूर्णांकel_dp_lttpr_phy_caps(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				   क्रमागत drm_dp_phy dp_phy)
अणु
	वापस पूर्णांकel_dp->lttpr_phy_caps[dp_phy - DP_PHY_LTTPR1];
पूर्ण

अटल व्योम पूर्णांकel_dp_पढ़ो_lttpr_phy_caps(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
					 क्रमागत drm_dp_phy dp_phy)
अणु
	u8 *phy_caps = पूर्णांकel_dp_lttpr_phy_caps(पूर्णांकel_dp, dp_phy);
	अक्षर phy_name[10];

	पूर्णांकel_dp_phy_name(dp_phy, phy_name, माप(phy_name));

	अगर (drm_dp_पढ़ो_lttpr_phy_caps(&पूर्णांकel_dp->aux, dp_phy, phy_caps) < 0) अणु
		drm_dbg_kms(&dp_to_i915(पूर्णांकel_dp)->drm,
			    "failed to read the PHY caps for %s\n",
			    phy_name);
		वापस;
	पूर्ण

	drm_dbg_kms(&dp_to_i915(पूर्णांकel_dp)->drm,
		    "%s PHY capabilities: %*ph\n",
		    phy_name,
		    (पूर्णांक)माप(पूर्णांकel_dp->lttpr_phy_caps[0]),
		    phy_caps);
पूर्ण

अटल bool पूर्णांकel_dp_पढ़ो_lttpr_common_caps(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);

	अगर (पूर्णांकel_dp_is_edp(पूर्णांकel_dp))
		वापस false;

	/*
	 * Detecting LTTPRs must be aव्योमed on platक्रमms with an AUX समयout
	 * period < 3.2ms. (see DP Standard v2.0, 2.11.2, 3.6.6.1).
	 */
	अगर (DISPLAY_VER(i915) < 10 || IS_GEMINILAKE(i915))
		वापस false;

	अगर (drm_dp_पढ़ो_lttpr_common_caps(&पूर्णांकel_dp->aux,
					  पूर्णांकel_dp->lttpr_common_caps) < 0)
		जाओ reset_caps;

	drm_dbg_kms(&dp_to_i915(पूर्णांकel_dp)->drm,
		    "LTTPR common capabilities: %*ph\n",
		    (पूर्णांक)माप(पूर्णांकel_dp->lttpr_common_caps),
		    पूर्णांकel_dp->lttpr_common_caps);

	/* The minimum value of LT_TUNABLE_PHY_REPEATER_FIELD_DATA_STRUCTURE_REV is 1.4 */
	अगर (पूर्णांकel_dp->lttpr_common_caps[0] < 0x14)
		जाओ reset_caps;

	वापस true;

reset_caps:
	पूर्णांकel_dp_reset_lttpr_common_caps(पूर्णांकel_dp);
	वापस false;
पूर्ण

अटल bool
पूर्णांकel_dp_set_lttpr_transparent_mode(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, bool enable)
अणु
	u8 val = enable ? DP_PHY_REPEATER_MODE_TRANSPARENT :
			  DP_PHY_REPEATER_MODE_NON_TRANSPARENT;

	वापस drm_dp_dpcd_ग_लिखो(&पूर्णांकel_dp->aux, DP_PHY_REPEATER_MODE, &val, 1) == 1;
पूर्ण

अटल पूर्णांक पूर्णांकel_dp_init_lttpr(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	पूर्णांक lttpr_count;
	पूर्णांक i;

	अगर (!पूर्णांकel_dp_पढ़ो_lttpr_common_caps(पूर्णांकel_dp))
		वापस 0;

	lttpr_count = drm_dp_lttpr_count(पूर्णांकel_dp->lttpr_common_caps);
	/*
	 * Prevent setting LTTPR transparent mode explicitly अगर no LTTPRs are
	 * detected as this अवरोधs link training at least on the Dell WD19TB
	 * करोck.
	 */
	अगर (lttpr_count == 0)
		वापस 0;

	/*
	 * See DP Standard v2.0 3.6.6.1. about the explicit disabling of
	 * non-transparent mode and the disable->enable non-transparent mode
	 * sequence.
	 */
	पूर्णांकel_dp_set_lttpr_transparent_mode(पूर्णांकel_dp, true);

	/*
	 * In हाल of unsupported number of LTTPRs or failing to चयन to
	 * non-transparent mode fall-back to transparent link training mode,
	 * still taking पूर्णांकo account any LTTPR common lane- rate/count limits.
	 */
	अगर (lttpr_count < 0)
		वापस 0;

	अगर (!पूर्णांकel_dp_set_lttpr_transparent_mode(पूर्णांकel_dp, false)) अणु
		drm_dbg_kms(&dp_to_i915(पूर्णांकel_dp)->drm,
			    "Switching to LTTPR non-transparent LT mode failed, fall-back to transparent mode\n");

		पूर्णांकel_dp_set_lttpr_transparent_mode(पूर्णांकel_dp, true);
		पूर्णांकel_dp_reset_lttpr_count(पूर्णांकel_dp);

		वापस 0;
	पूर्ण

	क्रम (i = 0; i < lttpr_count; i++)
		पूर्णांकel_dp_पढ़ो_lttpr_phy_caps(पूर्णांकel_dp, DP_PHY_LTTPR(i));

	वापस lttpr_count;
पूर्ण

/**
 * पूर्णांकel_dp_init_lttpr_and_dprx_caps - detect LTTPR and DPRX caps, init the LTTPR link training mode
 * @पूर्णांकel_dp: Intel DP काष्ठा
 *
 * Read the LTTPR common and DPRX capabilities and चयन to non-transparent
 * link training mode अगर any is detected and पढ़ो the PHY capabilities क्रम all
 * detected LTTPRs. In हाल of an LTTPR detection error or अगर the number of
 * LTTPRs is more than is supported (8), fall back to the no-LTTPR,
 * transparent mode link training mode.
 *
 * Returns:
 *   >0  अगर LTTPRs were detected and the non-transparent LT mode was set. The
 *       DPRX capabilities are पढ़ो out.
 *    0  अगर no LTTPRs or more than 8 LTTPRs were detected or in हाल of a
 *       detection failure and the transparent LT mode was set. The DPRX
 *       capabilities are पढ़ो out.
 *   <0  Reading out the DPRX capabilities failed.
 */
पूर्णांक पूर्णांकel_dp_init_lttpr_and_dprx_caps(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	पूर्णांक lttpr_count = पूर्णांकel_dp_init_lttpr(पूर्णांकel_dp);

	/* The DPTX shall पढ़ो the DPRX caps after LTTPR detection. */
	अगर (drm_dp_पढ़ो_dpcd_caps(&पूर्णांकel_dp->aux, पूर्णांकel_dp->dpcd)) अणु
		पूर्णांकel_dp_reset_lttpr_common_caps(पूर्णांकel_dp);
		वापस -EIO;
	पूर्ण

	वापस lttpr_count;
पूर्ण
EXPORT_SYMBOL(पूर्णांकel_dp_init_lttpr_and_dprx_caps);

अटल u8 dp_voltage_max(u8 preemph)
अणु
	चयन (preemph & DP_TRAIN_PRE_EMPHASIS_MASK) अणु
	हाल DP_TRAIN_PRE_EMPH_LEVEL_0:
		वापस DP_TRAIN_VOLTAGE_SWING_LEVEL_3;
	हाल DP_TRAIN_PRE_EMPH_LEVEL_1:
		वापस DP_TRAIN_VOLTAGE_SWING_LEVEL_2;
	हाल DP_TRAIN_PRE_EMPH_LEVEL_2:
		वापस DP_TRAIN_VOLTAGE_SWING_LEVEL_1;
	हाल DP_TRAIN_PRE_EMPH_LEVEL_3:
	शेष:
		वापस DP_TRAIN_VOLTAGE_SWING_LEVEL_0;
	पूर्ण
पूर्ण

अटल u8 पूर्णांकel_dp_lttpr_voltage_max(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				     क्रमागत drm_dp_phy dp_phy)
अणु
	स्थिर u8 *phy_caps = पूर्णांकel_dp_lttpr_phy_caps(पूर्णांकel_dp, dp_phy);

	अगर (drm_dp_lttpr_voltage_swing_level_3_supported(phy_caps))
		वापस DP_TRAIN_VOLTAGE_SWING_LEVEL_3;
	अन्यथा
		वापस DP_TRAIN_VOLTAGE_SWING_LEVEL_2;
पूर्ण

अटल u8 पूर्णांकel_dp_lttpr_preemph_max(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				     क्रमागत drm_dp_phy dp_phy)
अणु
	स्थिर u8 *phy_caps = पूर्णांकel_dp_lttpr_phy_caps(पूर्णांकel_dp, dp_phy);

	अगर (drm_dp_lttpr_pre_emphasis_level_3_supported(phy_caps))
		वापस DP_TRAIN_PRE_EMPH_LEVEL_3;
	अन्यथा
		वापस DP_TRAIN_PRE_EMPH_LEVEL_2;
पूर्ण

अटल bool
पूर्णांकel_dp_phy_is_करोwnstream_of_source(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				     क्रमागत drm_dp_phy dp_phy)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	पूर्णांक lttpr_count = drm_dp_lttpr_count(पूर्णांकel_dp->lttpr_common_caps);

	drm_WARN_ON_ONCE(&i915->drm, lttpr_count <= 0 && dp_phy != DP_PHY_DPRX);

	वापस lttpr_count <= 0 || dp_phy == DP_PHY_LTTPR(lttpr_count - 1);
पूर्ण

अटल u8 पूर्णांकel_dp_phy_voltage_max(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				   क्रमागत drm_dp_phy dp_phy)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	u8 voltage_max;

	/*
	 * Get voltage_max from the DPTX_PHY (source or LTTPR) upstream from
	 * the DPRX_PHY we train.
	 */
	अगर (पूर्णांकel_dp_phy_is_करोwnstream_of_source(पूर्णांकel_dp, dp_phy))
		voltage_max = पूर्णांकel_dp->voltage_max(पूर्णांकel_dp, crtc_state);
	अन्यथा
		voltage_max = पूर्णांकel_dp_lttpr_voltage_max(पूर्णांकel_dp, dp_phy + 1);

	drm_WARN_ON_ONCE(&i915->drm,
			 voltage_max != DP_TRAIN_VOLTAGE_SWING_LEVEL_2 &&
			 voltage_max != DP_TRAIN_VOLTAGE_SWING_LEVEL_3);

	वापस voltage_max;
पूर्ण

अटल u8 पूर्णांकel_dp_phy_preemph_max(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				   क्रमागत drm_dp_phy dp_phy)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	u8 preemph_max;

	/*
	 * Get preemph_max from the DPTX_PHY (source or LTTPR) upstream from
	 * the DPRX_PHY we train.
	 */
	अगर (पूर्णांकel_dp_phy_is_करोwnstream_of_source(पूर्णांकel_dp, dp_phy))
		preemph_max = पूर्णांकel_dp->preemph_max(पूर्णांकel_dp);
	अन्यथा
		preemph_max = पूर्णांकel_dp_lttpr_preemph_max(पूर्णांकel_dp, dp_phy + 1);

	drm_WARN_ON_ONCE(&i915->drm,
			 preemph_max != DP_TRAIN_PRE_EMPH_LEVEL_2 &&
			 preemph_max != DP_TRAIN_PRE_EMPH_LEVEL_3);

	वापस preemph_max;
पूर्ण

व्योम
पूर्णांकel_dp_get_adjust_train(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			  क्रमागत drm_dp_phy dp_phy,
			  स्थिर u8 link_status[DP_LINK_STATUS_SIZE])
अणु
	u8 v = 0;
	u8 p = 0;
	पूर्णांक lane;
	u8 voltage_max;
	u8 preemph_max;

	क्रम (lane = 0; lane < crtc_state->lane_count; lane++) अणु
		v = max(v, drm_dp_get_adjust_request_voltage(link_status, lane));
		p = max(p, drm_dp_get_adjust_request_pre_emphasis(link_status, lane));
	पूर्ण

	preemph_max = पूर्णांकel_dp_phy_preemph_max(पूर्णांकel_dp, dp_phy);
	अगर (p >= preemph_max)
		p = preemph_max | DP_TRAIN_MAX_PRE_EMPHASIS_REACHED;

	v = min(v, dp_voltage_max(p));

	voltage_max = पूर्णांकel_dp_phy_voltage_max(पूर्णांकel_dp, crtc_state, dp_phy);
	अगर (v >= voltage_max)
		v = voltage_max | DP_TRAIN_MAX_SWING_REACHED;

	क्रम (lane = 0; lane < 4; lane++)
		पूर्णांकel_dp->train_set[lane] = v | p;
पूर्ण

अटल पूर्णांक पूर्णांकel_dp_training_pattern_set_reg(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
					     क्रमागत drm_dp_phy dp_phy)
अणु
	वापस dp_phy == DP_PHY_DPRX ?
		DP_TRAINING_PATTERN_SET :
		DP_TRAINING_PATTERN_SET_PHY_REPEATER(dp_phy);
पूर्ण

अटल bool
पूर्णांकel_dp_set_link_train(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			क्रमागत drm_dp_phy dp_phy,
			u8 dp_train_pat)
अणु
	पूर्णांक reg = पूर्णांकel_dp_training_pattern_set_reg(पूर्णांकel_dp, dp_phy);
	u8 buf[माप(पूर्णांकel_dp->train_set) + 1];
	पूर्णांक len;

	पूर्णांकel_dp_program_link_training_pattern(पूर्णांकel_dp, crtc_state,
					       dp_train_pat);

	buf[0] = dp_train_pat;
	/* DP_TRAINING_LANEx_SET follow DP_TRAINING_PATTERN_SET */
	स_नकल(buf + 1, पूर्णांकel_dp->train_set, crtc_state->lane_count);
	len = crtc_state->lane_count + 1;

	वापस drm_dp_dpcd_ग_लिखो(&पूर्णांकel_dp->aux, reg, buf, len) == len;
पूर्ण

अटल अक्षर dp_training_pattern_name(u8 train_pat)
अणु
	चयन (train_pat) अणु
	हाल DP_TRAINING_PATTERN_1:
	हाल DP_TRAINING_PATTERN_2:
	हाल DP_TRAINING_PATTERN_3:
		वापस '0' + train_pat;
	हाल DP_TRAINING_PATTERN_4:
		वापस '4';
	शेष:
		MISSING_CASE(train_pat);
		वापस '?';
	पूर्ण
पूर्ण

व्योम
पूर्णांकel_dp_program_link_training_pattern(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				       u8 dp_train_pat)
अणु
	काष्ठा पूर्णांकel_encoder *encoder = &dp_to_dig_port(पूर्णांकel_dp)->base;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	u8 train_pat = पूर्णांकel_dp_training_pattern_symbol(dp_train_pat);

	अगर (train_pat != DP_TRAINING_PATTERN_DISABLE)
		drm_dbg_kms(&dev_priv->drm,
			    "[ENCODER:%d:%s] Using DP training pattern TPS%c\n",
			    encoder->base.base.id, encoder->base.name,
			    dp_training_pattern_name(train_pat));

	पूर्णांकel_dp->set_link_train(पूर्णांकel_dp, crtc_state, dp_train_pat);
पूर्ण

व्योम पूर्णांकel_dp_set_संकेत_levels(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				क्रमागत drm_dp_phy dp_phy)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	u8 train_set = पूर्णांकel_dp->train_set[0];
	अक्षर phy_name[10];

	drm_dbg_kms(&dev_priv->drm, "Using vswing level %d%s, pre-emphasis level %d%s, at %s\n",
		    train_set & DP_TRAIN_VOLTAGE_SWING_MASK,
		    train_set & DP_TRAIN_MAX_SWING_REACHED ? " (max)" : "",
		    (train_set & DP_TRAIN_PRE_EMPHASIS_MASK) >>
		    DP_TRAIN_PRE_EMPHASIS_SHIFT,
		    train_set & DP_TRAIN_MAX_PRE_EMPHASIS_REACHED ?
		    " (max)" : "",
		    पूर्णांकel_dp_phy_name(dp_phy, phy_name, माप(phy_name)));

	अगर (पूर्णांकel_dp_phy_is_करोwnstream_of_source(पूर्णांकel_dp, dp_phy))
		पूर्णांकel_dp->set_संकेत_levels(पूर्णांकel_dp, crtc_state);
पूर्ण

अटल bool
पूर्णांकel_dp_reset_link_train(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			  क्रमागत drm_dp_phy dp_phy,
			  u8 dp_train_pat)
अणु
	स_रखो(पूर्णांकel_dp->train_set, 0, माप(पूर्णांकel_dp->train_set));
	पूर्णांकel_dp_set_संकेत_levels(पूर्णांकel_dp, crtc_state, dp_phy);
	वापस पूर्णांकel_dp_set_link_train(पूर्णांकel_dp, crtc_state, dp_phy, dp_train_pat);
पूर्ण

अटल bool
पूर्णांकel_dp_update_link_train(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			   क्रमागत drm_dp_phy dp_phy)
अणु
	पूर्णांक reg = dp_phy == DP_PHY_DPRX ?
			    DP_TRAINING_LANE0_SET :
			    DP_TRAINING_LANE0_SET_PHY_REPEATER(dp_phy);
	पूर्णांक ret;

	पूर्णांकel_dp_set_संकेत_levels(पूर्णांकel_dp, crtc_state, dp_phy);

	ret = drm_dp_dpcd_ग_लिखो(&पूर्णांकel_dp->aux, reg,
				पूर्णांकel_dp->train_set, crtc_state->lane_count);

	वापस ret == crtc_state->lane_count;
पूर्ण

अटल bool पूर्णांकel_dp_link_max_vswing_reached(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
					     स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	पूर्णांक lane;

	क्रम (lane = 0; lane < crtc_state->lane_count; lane++)
		अगर ((पूर्णांकel_dp->train_set[lane] &
		     DP_TRAIN_MAX_SWING_REACHED) == 0)
			वापस false;

	वापस true;
पूर्ण

/*
 * Prepare link training by configuring the link parameters. On DDI platक्रमms
 * also enable the port here.
 */
अटल bool
पूर्णांकel_dp_prepare_link_train(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	u8 link_config[2];
	u8 link_bw, rate_select;

	अगर (पूर्णांकel_dp->prepare_link_retrain)
		पूर्णांकel_dp->prepare_link_retrain(पूर्णांकel_dp, crtc_state);

	पूर्णांकel_dp_compute_rate(पूर्णांकel_dp, crtc_state->port_घड़ी,
			      &link_bw, &rate_select);

	अगर (link_bw)
		drm_dbg_kms(&i915->drm,
			    "Using LINK_BW_SET value %02x\n", link_bw);
	अन्यथा
		drm_dbg_kms(&i915->drm,
			    "Using LINK_RATE_SET value %02x\n", rate_select);

	/* Write the link configuration data */
	link_config[0] = link_bw;
	link_config[1] = crtc_state->lane_count;
	अगर (drm_dp_enhanced_frame_cap(पूर्णांकel_dp->dpcd))
		link_config[1] |= DP_LANE_COUNT_ENHANCED_FRAME_EN;
	drm_dp_dpcd_ग_लिखो(&पूर्णांकel_dp->aux, DP_LINK_BW_SET, link_config, 2);

	/* eDP 1.4 rate select method. */
	अगर (!link_bw)
		drm_dp_dpcd_ग_लिखो(&पूर्णांकel_dp->aux, DP_LINK_RATE_SET,
				  &rate_select, 1);

	link_config[0] = crtc_state->vrr.enable ? DP_MSA_TIMING_PAR_IGNORE_EN : 0;
	link_config[1] = DP_SET_ANSI_8B10B;
	drm_dp_dpcd_ग_लिखो(&पूर्णांकel_dp->aux, DP_DOWNSPREAD_CTRL, link_config, 2);

	पूर्णांकel_dp->DP |= DP_PORT_EN;

	वापस true;
पूर्ण

अटल व्योम पूर्णांकel_dp_link_training_घड़ी_recovery_delay(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
							क्रमागत drm_dp_phy dp_phy)
अणु
	अगर (dp_phy == DP_PHY_DPRX)
		drm_dp_link_train_घड़ी_recovery_delay(पूर्णांकel_dp->dpcd);
	अन्यथा
		drm_dp_lttpr_link_train_घड़ी_recovery_delay();
पूर्ण

/*
 * Perक्रमm the link training घड़ी recovery phase on the given DP PHY using
 * training pattern 1.
 */
अटल bool
पूर्णांकel_dp_link_training_घड़ी_recovery(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				      क्रमागत drm_dp_phy dp_phy)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	u8 voltage;
	पूर्णांक voltage_tries, cr_tries, max_cr_tries;
	bool max_vswing_reached = false;

	/* घड़ी recovery */
	अगर (!पूर्णांकel_dp_reset_link_train(पूर्णांकel_dp, crtc_state, dp_phy,
				       DP_TRAINING_PATTERN_1 |
				       DP_LINK_SCRAMBLING_DISABLE)) अणु
		drm_err(&i915->drm, "failed to enable link training\n");
		वापस false;
	पूर्ण

	/*
	 * The DP 1.4 spec defines the max घड़ी recovery retries value
	 * as 10 but क्रम pre-DP 1.4 devices we set a very tolerant
	 * retry limit of 80 (4 voltage levels x 4 preemphasis levels x
	 * x 5 identical voltage retries). Since the previous specs didn't
	 * define a limit and created the possibility of an infinite loop
	 * we want to prevent any sync from triggering that corner हाल.
	 */
	अगर (पूर्णांकel_dp->dpcd[DP_DPCD_REV] >= DP_DPCD_REV_14)
		max_cr_tries = 10;
	अन्यथा
		max_cr_tries = 80;

	voltage_tries = 1;
	क्रम (cr_tries = 0; cr_tries < max_cr_tries; ++cr_tries) अणु
		u8 link_status[DP_LINK_STATUS_SIZE];

		पूर्णांकel_dp_link_training_घड़ी_recovery_delay(पूर्णांकel_dp, dp_phy);

		अगर (drm_dp_dpcd_पढ़ो_phy_link_status(&पूर्णांकel_dp->aux, dp_phy,
						     link_status) < 0) अणु
			drm_err(&i915->drm, "failed to get link status\n");
			वापस false;
		पूर्ण

		अगर (drm_dp_घड़ी_recovery_ok(link_status, crtc_state->lane_count)) अणु
			drm_dbg_kms(&i915->drm, "clock recovery OK\n");
			वापस true;
		पूर्ण

		अगर (voltage_tries == 5) अणु
			drm_dbg_kms(&i915->drm,
				    "Same voltage tried 5 times\n");
			वापस false;
		पूर्ण

		अगर (max_vswing_reached) अणु
			drm_dbg_kms(&i915->drm, "Max Voltage Swing reached\n");
			वापस false;
		पूर्ण

		voltage = पूर्णांकel_dp->train_set[0] & DP_TRAIN_VOLTAGE_SWING_MASK;

		/* Update training set as requested by target */
		पूर्णांकel_dp_get_adjust_train(पूर्णांकel_dp, crtc_state, dp_phy,
					  link_status);
		अगर (!पूर्णांकel_dp_update_link_train(पूर्णांकel_dp, crtc_state, dp_phy)) अणु
			drm_err(&i915->drm,
				"failed to update link training\n");
			वापस false;
		पूर्ण

		अगर ((पूर्णांकel_dp->train_set[0] & DP_TRAIN_VOLTAGE_SWING_MASK) ==
		    voltage)
			++voltage_tries;
		अन्यथा
			voltage_tries = 1;

		अगर (पूर्णांकel_dp_link_max_vswing_reached(पूर्णांकel_dp, crtc_state))
			max_vswing_reached = true;

	पूर्ण
	drm_err(&i915->drm,
		"Failed clock recovery %d times, giving up!\n", max_cr_tries);
	वापस false;
पूर्ण

/*
 * Pick training pattern क्रम channel equalization. Training pattern 4 क्रम HBR3
 * or क्रम 1.4 devices that support it, training Pattern 3 क्रम HBR2
 * or 1.2 devices that support it, Training Pattern 2 otherwise.
 */
अटल u32 पूर्णांकel_dp_training_pattern(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				     स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				     क्रमागत drm_dp_phy dp_phy)
अणु
	bool source_tps3, sink_tps3, source_tps4, sink_tps4;

	/*
	 * Intel platक्रमms that support HBR3 also support TPS4. It is mandatory
	 * क्रम all करोwnstream devices that support HBR3. There are no known eDP
	 * panels that support TPS4 as of Feb 2018 as per VESA eDP_v1.4b_E1
	 * specअगरication.
	 * LTTPRs must support TPS4.
	 */
	source_tps4 = पूर्णांकel_dp_source_supports_hbr3(पूर्णांकel_dp);
	sink_tps4 = dp_phy != DP_PHY_DPRX ||
		    drm_dp_tps4_supported(पूर्णांकel_dp->dpcd);
	अगर (source_tps4 && sink_tps4) अणु
		वापस DP_TRAINING_PATTERN_4;
	पूर्ण अन्यथा अगर (crtc_state->port_घड़ी == 810000) अणु
		अगर (!source_tps4)
			drm_dbg_kms(&dp_to_i915(पूर्णांकel_dp)->drm,
				    "8.1 Gbps link rate without source HBR3/TPS4 support\n");
		अगर (!sink_tps4)
			drm_dbg_kms(&dp_to_i915(पूर्णांकel_dp)->drm,
				    "8.1 Gbps link rate without sink TPS4 support\n");
	पूर्ण
	/*
	 * Intel platक्रमms that support HBR2 also support TPS3. TPS3 support is
	 * also mandatory क्रम करोwnstream devices that support HBR2. However, not
	 * all sinks follow the spec.
	 */
	source_tps3 = पूर्णांकel_dp_source_supports_hbr2(पूर्णांकel_dp);
	sink_tps3 = dp_phy != DP_PHY_DPRX ||
		    drm_dp_tps3_supported(पूर्णांकel_dp->dpcd);
	अगर (source_tps3 && sink_tps3) अणु
		वापस  DP_TRAINING_PATTERN_3;
	पूर्ण अन्यथा अगर (crtc_state->port_घड़ी >= 540000) अणु
		अगर (!source_tps3)
			drm_dbg_kms(&dp_to_i915(पूर्णांकel_dp)->drm,
				    ">=5.4/6.48 Gbps link rate without source HBR2/TPS3 support\n");
		अगर (!sink_tps3)
			drm_dbg_kms(&dp_to_i915(पूर्णांकel_dp)->drm,
				    ">=5.4/6.48 Gbps link rate without sink TPS3 support\n");
	पूर्ण

	वापस DP_TRAINING_PATTERN_2;
पूर्ण

अटल व्योम
पूर्णांकel_dp_link_training_channel_equalization_delay(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
						  क्रमागत drm_dp_phy dp_phy)
अणु
	अगर (dp_phy == DP_PHY_DPRX) अणु
		drm_dp_link_train_channel_eq_delay(पूर्णांकel_dp->dpcd);
	पूर्ण अन्यथा अणु
		स्थिर u8 *phy_caps = पूर्णांकel_dp_lttpr_phy_caps(पूर्णांकel_dp, dp_phy);

		drm_dp_lttpr_link_train_channel_eq_delay(phy_caps);
	पूर्ण
पूर्ण

/*
 * Perक्रमm the link training channel equalization phase on the given DP PHY
 * using one of training pattern 2, 3 or 4 depending on the source and
 * sink capabilities.
 */
अटल bool
पूर्णांकel_dp_link_training_channel_equalization(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
					    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
					    क्रमागत drm_dp_phy dp_phy)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	पूर्णांक tries;
	u32 training_pattern;
	u8 link_status[DP_LINK_STATUS_SIZE];
	bool channel_eq = false;

	training_pattern = पूर्णांकel_dp_training_pattern(पूर्णांकel_dp, crtc_state, dp_phy);
	/* Scrambling is disabled क्रम TPS2/3 and enabled क्रम TPS4 */
	अगर (training_pattern != DP_TRAINING_PATTERN_4)
		training_pattern |= DP_LINK_SCRAMBLING_DISABLE;

	/* channel equalization */
	अगर (!पूर्णांकel_dp_set_link_train(पूर्णांकel_dp, crtc_state, dp_phy,
				     training_pattern)) अणु
		drm_err(&i915->drm, "failed to start channel equalization\n");
		वापस false;
	पूर्ण

	क्रम (tries = 0; tries < 5; tries++) अणु
		पूर्णांकel_dp_link_training_channel_equalization_delay(पूर्णांकel_dp,
								  dp_phy);
		अगर (drm_dp_dpcd_पढ़ो_phy_link_status(&पूर्णांकel_dp->aux, dp_phy,
						     link_status) < 0) अणु
			drm_err(&i915->drm,
				"failed to get link status\n");
			अवरोध;
		पूर्ण

		/* Make sure घड़ी is still ok */
		अगर (!drm_dp_घड़ी_recovery_ok(link_status,
					      crtc_state->lane_count)) अणु
			पूर्णांकel_dp_dump_link_status(&i915->drm, link_status);
			drm_dbg_kms(&i915->drm,
				    "Clock recovery check failed, cannot "
				    "continue channel equalization\n");
			अवरोध;
		पूर्ण

		अगर (drm_dp_channel_eq_ok(link_status,
					 crtc_state->lane_count)) अणु
			channel_eq = true;
			drm_dbg_kms(&i915->drm, "Channel EQ done. DP Training "
				    "successful\n");
			अवरोध;
		पूर्ण

		/* Update training set as requested by target */
		पूर्णांकel_dp_get_adjust_train(पूर्णांकel_dp, crtc_state, dp_phy,
					  link_status);
		अगर (!पूर्णांकel_dp_update_link_train(पूर्णांकel_dp, crtc_state, dp_phy)) अणु
			drm_err(&i915->drm,
				"failed to update link training\n");
			अवरोध;
		पूर्ण
	पूर्ण

	/* Try 5 बार, अन्यथा fail and try at lower BW */
	अगर (tries == 5) अणु
		पूर्णांकel_dp_dump_link_status(&i915->drm, link_status);
		drm_dbg_kms(&i915->drm,
			    "Channel equalization failed 5 times\n");
	पूर्ण

	वापस channel_eq;
पूर्ण

अटल bool पूर्णांकel_dp_disable_dpcd_training_pattern(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
						   क्रमागत drm_dp_phy dp_phy)
अणु
	पूर्णांक reg = पूर्णांकel_dp_training_pattern_set_reg(पूर्णांकel_dp, dp_phy);
	u8 val = DP_TRAINING_PATTERN_DISABLE;

	वापस drm_dp_dpcd_ग_लिखो(&पूर्णांकel_dp->aux, reg, &val, 1) == 1;
पूर्ण

/**
 * पूर्णांकel_dp_stop_link_train - stop link training
 * @पूर्णांकel_dp: DP काष्ठा
 * @crtc_state: state क्रम CRTC attached to the encoder
 *
 * Stop the link training of the @पूर्णांकel_dp port, disabling the training
 * pattern in the sink's DPCD, and disabling the test pattern symbol
 * generation on the port.
 *
 * What symbols are output on the port after this poपूर्णांक is
 * platक्रमm specअगरic: On DDI/VLV/CHV platक्रमms it will be the idle pattern
 * with the pipe being disabled, on older platक्रमms it's HW specअगरic अगर/how an
 * idle pattern is generated, as the pipe is alपढ़ोy enabled here क्रम those.
 *
 * This function must be called after पूर्णांकel_dp_start_link_train().
 */
व्योम पूर्णांकel_dp_stop_link_train(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	पूर्णांकel_dp->link_trained = true;

	पूर्णांकel_dp_disable_dpcd_training_pattern(पूर्णांकel_dp, DP_PHY_DPRX);
	पूर्णांकel_dp_program_link_training_pattern(पूर्णांकel_dp, crtc_state,
					       DP_TRAINING_PATTERN_DISABLE);
पूर्ण

अटल bool
पूर्णांकel_dp_link_train_phy(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			क्रमागत drm_dp_phy dp_phy)
अणु
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector = पूर्णांकel_dp->attached_connector;
	अक्षर phy_name[10];
	bool ret = false;

	अगर (!पूर्णांकel_dp_link_training_घड़ी_recovery(पूर्णांकel_dp, crtc_state, dp_phy))
		जाओ out;

	अगर (!पूर्णांकel_dp_link_training_channel_equalization(पूर्णांकel_dp, crtc_state, dp_phy))
		जाओ out;

	ret = true;

out:
	drm_dbg_kms(&dp_to_i915(पूर्णांकel_dp)->drm,
		    "[CONNECTOR:%d:%s] Link Training %s at link rate = %d, lane count = %d, at %s\n",
		    पूर्णांकel_connector->base.base.id,
		    पूर्णांकel_connector->base.name,
		    ret ? "passed" : "failed",
		    crtc_state->port_घड़ी, crtc_state->lane_count,
		    पूर्णांकel_dp_phy_name(dp_phy, phy_name, माप(phy_name)));

	वापस ret;
पूर्ण

अटल व्योम पूर्णांकel_dp_schedule_fallback_link_training(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
						     स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector = पूर्णांकel_dp->attached_connector;

	अगर (पूर्णांकel_dp->hobl_active) अणु
		drm_dbg_kms(&dp_to_i915(पूर्णांकel_dp)->drm,
			    "Link Training failed with HOBL active, not enabling it from now on");
		पूर्णांकel_dp->hobl_failed = true;
	पूर्ण अन्यथा अगर (पूर्णांकel_dp_get_link_train_fallback_values(पूर्णांकel_dp,
							   crtc_state->port_घड़ी,
							   crtc_state->lane_count)) अणु
		वापस;
	पूर्ण

	/* Schedule a Hotplug Uevent to userspace to start modeset */
	schedule_work(&पूर्णांकel_connector->modeset_retry_work);
पूर्ण

/* Perक्रमm the link training on all LTTPRs and the DPRX on a link. */
अटल bool
पूर्णांकel_dp_link_train_all_phys(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			     स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			     पूर्णांक lttpr_count)
अणु
	bool ret = true;
	पूर्णांक i;

	पूर्णांकel_dp_prepare_link_train(पूर्णांकel_dp, crtc_state);

	क्रम (i = lttpr_count - 1; i >= 0; i--) अणु
		क्रमागत drm_dp_phy dp_phy = DP_PHY_LTTPR(i);

		ret = पूर्णांकel_dp_link_train_phy(पूर्णांकel_dp, crtc_state, dp_phy);
		पूर्णांकel_dp_disable_dpcd_training_pattern(पूर्णांकel_dp, dp_phy);

		अगर (!ret)
			अवरोध;
	पूर्ण

	अगर (ret)
		पूर्णांकel_dp_link_train_phy(पूर्णांकel_dp, crtc_state, DP_PHY_DPRX);

	अगर (पूर्णांकel_dp->set_idle_link_train)
		पूर्णांकel_dp->set_idle_link_train(पूर्णांकel_dp, crtc_state);

	वापस ret;
पूर्ण

/**
 * पूर्णांकel_dp_start_link_train - start link training
 * @पूर्णांकel_dp: DP काष्ठा
 * @crtc_state: state क्रम CRTC attached to the encoder
 *
 * Start the link training of the @पूर्णांकel_dp port, scheduling a fallback
 * retraining with reduced link rate/lane parameters अगर the link training
 * fails.
 * After calling this function पूर्णांकel_dp_stop_link_train() must be called.
 */
व्योम पूर्णांकel_dp_start_link_train(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	/*
	 * TODO: Reiniting LTTPRs here won't be needed once proper connector
	 * HW state पढ़ोout is added.
	 */
	पूर्णांक lttpr_count = पूर्णांकel_dp_init_lttpr_and_dprx_caps(पूर्णांकel_dp);

	अगर (lttpr_count < 0)
		/* Still जारी with enabling the port and link training. */
		lttpr_count = 0;

	अगर (!पूर्णांकel_dp_link_train_all_phys(पूर्णांकel_dp, crtc_state, lttpr_count))
		पूर्णांकel_dp_schedule_fallback_link_training(पूर्णांकel_dp, crtc_state);
पूर्ण
