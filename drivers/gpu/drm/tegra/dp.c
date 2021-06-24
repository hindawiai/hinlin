<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright (C) 2013-2019 NVIDIA Corporation
 * Copyright (C) 2015 Rob Clark
 */

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "dp.h"

अटल स्थिर u8 drm_dp_edp_revisions[] = अणु 0x11, 0x12, 0x13, 0x14 पूर्ण;

अटल व्योम drm_dp_link_caps_reset(काष्ठा drm_dp_link_caps *caps)
अणु
	caps->enhanced_framing = false;
	caps->tps3_supported = false;
	caps->fast_training = false;
	caps->channel_coding = false;
	caps->alternate_scrambler_reset = false;
पूर्ण

व्योम drm_dp_link_caps_copy(काष्ठा drm_dp_link_caps *dest,
			   स्थिर काष्ठा drm_dp_link_caps *src)
अणु
	dest->enhanced_framing = src->enhanced_framing;
	dest->tps3_supported = src->tps3_supported;
	dest->fast_training = src->fast_training;
	dest->channel_coding = src->channel_coding;
	dest->alternate_scrambler_reset = src->alternate_scrambler_reset;
पूर्ण

अटल व्योम drm_dp_link_reset(काष्ठा drm_dp_link *link)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!link)
		वापस;

	link->revision = 0;
	link->max_rate = 0;
	link->max_lanes = 0;

	drm_dp_link_caps_reset(&link->caps);
	link->aux_rd_पूर्णांकerval.cr = 0;
	link->aux_rd_पूर्णांकerval.ce = 0;
	link->edp = 0;

	link->rate = 0;
	link->lanes = 0;

	क्रम (i = 0; i < DP_MAX_SUPPORTED_RATES; i++)
		link->rates[i] = 0;

	link->num_rates = 0;
पूर्ण

/**
 * drm_dp_link_add_rate() - add a rate to the list of supported rates
 * @link: the link to add the rate to
 * @rate: the rate to add
 *
 * Add a link rate to the list of supported link rates.
 *
 * Returns:
 * 0 on success or one of the following negative error codes on failure:
 * - ENOSPC अगर the maximum number of supported rates has been reached
 * - EEXISTS अगर the link alपढ़ोy supports this rate
 *
 * See also:
 * drm_dp_link_हटाओ_rate()
 */
पूर्णांक drm_dp_link_add_rate(काष्ठा drm_dp_link *link, अचिन्हित दीर्घ rate)
अणु
	अचिन्हित पूर्णांक i, pivot;

	अगर (link->num_rates == DP_MAX_SUPPORTED_RATES)
		वापस -ENOSPC;

	क्रम (pivot = 0; pivot < link->num_rates; pivot++)
		अगर (rate <= link->rates[pivot])
			अवरोध;

	अगर (pivot != link->num_rates && rate == link->rates[pivot])
		वापस -EEXIST;

	क्रम (i = link->num_rates; i > pivot; i--)
		link->rates[i] = link->rates[i - 1];

	link->rates[pivot] = rate;
	link->num_rates++;

	वापस 0;
पूर्ण

/**
 * drm_dp_link_हटाओ_rate() - हटाओ a rate from the list of supported rates
 * @link: the link from which to हटाओ the rate
 * @rate: the rate to हटाओ
 *
 * Removes a link rate from the list of supported link rates.
 *
 * Returns:
 * 0 on success or one of the following negative error codes on failure:
 * - EINVAL अगर the specअगरied rate is not among the supported rates
 *
 * See also:
 * drm_dp_link_add_rate()
 */
पूर्णांक drm_dp_link_हटाओ_rate(काष्ठा drm_dp_link *link, अचिन्हित दीर्घ rate)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < link->num_rates; i++)
		अगर (rate == link->rates[i])
			अवरोध;

	अगर (i == link->num_rates)
		वापस -EINVAL;

	link->num_rates--;

	जबतक (i < link->num_rates) अणु
		link->rates[i] = link->rates[i + 1];
		i++;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * drm_dp_link_update_rates() - normalize the supported link rates array
 * @link: the link क्रम which to normalize the supported link rates
 *
 * Users should call this function after they've manually modअगरied the array
 * of supported link rates. This function हटाओs any stale entries, compacts
 * the array and updates the supported link rate count. Note that calling the
 * drm_dp_link_हटाओ_rate() function alपढ़ोy करोes this janitorial work.
 *
 * See also:
 * drm_dp_link_add_rate(), drm_dp_link_हटाओ_rate()
 */
व्योम drm_dp_link_update_rates(काष्ठा drm_dp_link *link)
अणु
	अचिन्हित पूर्णांक i, count = 0;

	क्रम (i = 0; i < link->num_rates; i++) अणु
		अगर (link->rates[i] != 0)
			link->rates[count++] = link->rates[i];
	पूर्ण

	क्रम (i = count; i < link->num_rates; i++)
		link->rates[i] = 0;

	link->num_rates = count;
पूर्ण

/**
 * drm_dp_link_probe() - probe a DisplayPort link क्रम capabilities
 * @aux: DisplayPort AUX channel
 * @link: poपूर्णांकer to काष्ठाure in which to वापस link capabilities
 *
 * The काष्ठाure filled in by this function can usually be passed directly
 * पूर्णांकo drm_dp_link_घातer_up() and drm_dp_link_configure() to घातer up and
 * configure the link based on the link's capabilities.
 *
 * Returns 0 on success or a negative error code on failure.
 */
पूर्णांक drm_dp_link_probe(काष्ठा drm_dp_aux *aux, काष्ठा drm_dp_link *link)
अणु
	u8 dpcd[DP_RECEIVER_CAP_SIZE], value;
	अचिन्हित पूर्णांक rd_पूर्णांकerval;
	पूर्णांक err;

	drm_dp_link_reset(link);

	err = drm_dp_dpcd_पढ़ो(aux, DP_DPCD_REV, dpcd, माप(dpcd));
	अगर (err < 0)
		वापस err;

	link->revision = dpcd[DP_DPCD_REV];
	link->max_rate = drm_dp_max_link_rate(dpcd);
	link->max_lanes = drm_dp_max_lane_count(dpcd);

	link->caps.enhanced_framing = drm_dp_enhanced_frame_cap(dpcd);
	link->caps.tps3_supported = drm_dp_tps3_supported(dpcd);
	link->caps.fast_training = drm_dp_fast_training_cap(dpcd);
	link->caps.channel_coding = drm_dp_channel_coding_supported(dpcd);

	अगर (drm_dp_alternate_scrambler_reset_cap(dpcd)) अणु
		link->caps.alternate_scrambler_reset = true;

		err = drm_dp_dpcd_पढ़ोb(aux, DP_EDP_DPCD_REV, &value);
		अगर (err < 0)
			वापस err;

		अगर (value >= ARRAY_SIZE(drm_dp_edp_revisions))
			DRM_ERROR("unsupported eDP version: %02x\n", value);
		अन्यथा
			link->edp = drm_dp_edp_revisions[value];
	पूर्ण

	/*
	 * The DPCD stores the AUX पढ़ो पूर्णांकerval in units of 4 ms. There are
	 * two special हालs:
	 *
	 *   1) अगर the TRAINING_AUX_RD_INTERVAL field is 0, the घड़ी recovery
	 *      and channel equalization should use 100 us or 400 us AUX पढ़ो
	 *      पूर्णांकervals, respectively
	 *
	 *   2) क्रम DP v1.4 and above, घड़ी recovery should always use 100 us
	 *      AUX पढ़ो पूर्णांकervals
	 */
	rd_पूर्णांकerval = dpcd[DP_TRAINING_AUX_RD_INTERVAL] &
			   DP_TRAINING_AUX_RD_MASK;

	अगर (rd_पूर्णांकerval > 4) अणु
		DRM_DEBUG_KMS("AUX interval %u out of range (max. 4)\n",
			      rd_पूर्णांकerval);
		rd_पूर्णांकerval = 4;
	पूर्ण

	rd_पूर्णांकerval *= 4 * USEC_PER_MSEC;

	अगर (rd_पूर्णांकerval == 0 || link->revision >= DP_DPCD_REV_14)
		link->aux_rd_पूर्णांकerval.cr = 100;

	अगर (rd_पूर्णांकerval == 0)
		link->aux_rd_पूर्णांकerval.ce = 400;

	link->rate = link->max_rate;
	link->lanes = link->max_lanes;

	/* Parse SUPPORTED_LINK_RATES from eDP 1.4 */
	अगर (link->edp >= 0x14) अणु
		u8 supported_rates[DP_MAX_SUPPORTED_RATES * 2];
		अचिन्हित पूर्णांक i;
		u16 rate;

		err = drm_dp_dpcd_पढ़ो(aux, DP_SUPPORTED_LINK_RATES,
				       supported_rates,
				       माप(supported_rates));
		अगर (err < 0)
			वापस err;

		क्रम (i = 0; i < DP_MAX_SUPPORTED_RATES; i++) अणु
			rate = supported_rates[i * 2 + 1] << 8 |
			       supported_rates[i * 2 + 0];

			drm_dp_link_add_rate(link, rate * 200);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * drm_dp_link_घातer_up() - घातer up a DisplayPort link
 * @aux: DisplayPort AUX channel
 * @link: poपूर्णांकer to a काष्ठाure containing the link configuration
 *
 * Returns 0 on success or a negative error code on failure.
 */
पूर्णांक drm_dp_link_घातer_up(काष्ठा drm_dp_aux *aux, काष्ठा drm_dp_link *link)
अणु
	u8 value;
	पूर्णांक err;

	/* DP_SET_POWER रेजिस्टर is only available on DPCD v1.1 and later */
	अगर (link->revision < 0x11)
		वापस 0;

	err = drm_dp_dpcd_पढ़ोb(aux, DP_SET_POWER, &value);
	अगर (err < 0)
		वापस err;

	value &= ~DP_SET_POWER_MASK;
	value |= DP_SET_POWER_D0;

	err = drm_dp_dpcd_ग_लिखोb(aux, DP_SET_POWER, value);
	अगर (err < 0)
		वापस err;

	/*
	 * According to the DP 1.1 specअगरication, a "Sink Device must निकास the
	 * घातer saving state within 1 ms" (Section 2.5.3.1, Table 5-52, "Sink
	 * Control Field" (रेजिस्टर 0x600).
	 */
	usleep_range(1000, 2000);

	वापस 0;
पूर्ण

/**
 * drm_dp_link_घातer_करोwn() - घातer करोwn a DisplayPort link
 * @aux: DisplayPort AUX channel
 * @link: poपूर्णांकer to a काष्ठाure containing the link configuration
 *
 * Returns 0 on success or a negative error code on failure.
 */
पूर्णांक drm_dp_link_घातer_करोwn(काष्ठा drm_dp_aux *aux, काष्ठा drm_dp_link *link)
अणु
	u8 value;
	पूर्णांक err;

	/* DP_SET_POWER रेजिस्टर is only available on DPCD v1.1 and later */
	अगर (link->revision < 0x11)
		वापस 0;

	err = drm_dp_dpcd_पढ़ोb(aux, DP_SET_POWER, &value);
	अगर (err < 0)
		वापस err;

	value &= ~DP_SET_POWER_MASK;
	value |= DP_SET_POWER_D3;

	err = drm_dp_dpcd_ग_लिखोb(aux, DP_SET_POWER, value);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

/**
 * drm_dp_link_configure() - configure a DisplayPort link
 * @aux: DisplayPort AUX channel
 * @link: poपूर्णांकer to a काष्ठाure containing the link configuration
 *
 * Returns 0 on success or a negative error code on failure.
 */
पूर्णांक drm_dp_link_configure(काष्ठा drm_dp_aux *aux, काष्ठा drm_dp_link *link)
अणु
	u8 values[2], value;
	पूर्णांक err;

	अगर (link->ops && link->ops->configure) अणु
		err = link->ops->configure(link);
		अगर (err < 0) अणु
			DRM_ERROR("failed to configure DP link: %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	values[0] = drm_dp_link_rate_to_bw_code(link->rate);
	values[1] = link->lanes;

	अगर (link->caps.enhanced_framing)
		values[1] |= DP_LANE_COUNT_ENHANCED_FRAME_EN;

	err = drm_dp_dpcd_ग_लिखो(aux, DP_LINK_BW_SET, values, माप(values));
	अगर (err < 0)
		वापस err;

	अगर (link->caps.channel_coding)
		value = DP_SET_ANSI_8B10B;
	अन्यथा
		value = 0;

	err = drm_dp_dpcd_ग_लिखोb(aux, DP_MAIN_LINK_CHANNEL_CODING_SET, value);
	अगर (err < 0)
		वापस err;

	अगर (link->caps.alternate_scrambler_reset) अणु
		err = drm_dp_dpcd_ग_लिखोb(aux, DP_EDP_CONFIGURATION_SET,
					 DP_ALTERNATE_SCRAMBLER_RESET_ENABLE);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * drm_dp_link_choose() - choose the lowest possible configuration क्रम a mode
 * @link: DRM DP link object
 * @mode: DRM display mode
 * @info: DRM display inक्रमmation
 *
 * According to the eDP specअगरication, a source should select a configuration
 * with the lowest number of lanes and the lowest possible link rate that can
 * match the bitrate requirements of a video mode. However it must ensure not
 * to exceed the capabilities of the sink.
 *
 * Returns: 0 on success or a negative error code on failure.
 */
पूर्णांक drm_dp_link_choose(काष्ठा drm_dp_link *link,
		       स्थिर काष्ठा drm_display_mode *mode,
		       स्थिर काष्ठा drm_display_info *info)
अणु
	/* available link symbol घड़ी rates */
	अटल स्थिर अचिन्हित पूर्णांक rates[3] = अणु 162000, 270000, 540000 पूर्ण;
	/* available number of lanes */
	अटल स्थिर अचिन्हित पूर्णांक lanes[3] = अणु 1, 2, 4 पूर्ण;
	अचिन्हित दीर्घ requirement, capacity;
	अचिन्हित पूर्णांक rate = link->max_rate;
	अचिन्हित पूर्णांक i, j;

	/* bandwidth requirement */
	requirement = mode->घड़ी * info->bpc * 3;

	क्रम (i = 0; i < ARRAY_SIZE(lanes) && lanes[i] <= link->max_lanes; i++) अणु
		क्रम (j = 0; j < ARRAY_SIZE(rates) && rates[j] <= rate; j++) अणु
			/*
			 * Capacity क्रम this combination of lanes and rate,
			 * factoring in the ANSI 8B/10B encoding.
			 *
			 * Link rates in the DRM DP helpers are really link
			 * symbol frequencies, so a tenth of the actual rate
			 * of the link.
			 */
			capacity = lanes[i] * (rates[j] * 10) * 8 / 10;

			अगर (capacity >= requirement) अणु
				DRM_DEBUG_KMS("using %u lanes at %u kHz (%lu/%lu kbps)\n",
					      lanes[i], rates[j], requirement,
					      capacity);
				link->lanes = lanes[i];
				link->rate = rates[j];
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस -दुस्फल;
पूर्ण

/**
 * DOC: Link training
 *
 * These functions contain common logic and helpers to implement DisplayPort
 * link training.
 */

/**
 * drm_dp_link_train_init() - initialize DisplayPort link training state
 * @train: DisplayPort link training state
 */
व्योम drm_dp_link_train_init(काष्ठा drm_dp_link_train *train)
अणु
	काष्ठा drm_dp_link_train_set *request = &train->request;
	काष्ठा drm_dp_link_train_set *adjust = &train->adjust;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		request->voltage_swing[i] = 0;
		adjust->voltage_swing[i] = 0;

		request->pre_emphasis[i] = 0;
		adjust->pre_emphasis[i] = 0;

		request->post_cursor[i] = 0;
		adjust->post_cursor[i] = 0;
	पूर्ण

	train->pattern = DP_TRAINING_PATTERN_DISABLE;
	train->घड़ी_recovered = false;
	train->channel_equalized = false;
पूर्ण

अटल bool drm_dp_link_train_valid(स्थिर काष्ठा drm_dp_link_train *train)
अणु
	वापस train->घड़ी_recovered && train->channel_equalized;
पूर्ण

अटल पूर्णांक drm_dp_link_apply_training(काष्ठा drm_dp_link *link)
अणु
	काष्ठा drm_dp_link_train_set *request = &link->train.request;
	अचिन्हित पूर्णांक lanes = link->lanes, *vs, *pe, *pc, i;
	काष्ठा drm_dp_aux *aux = link->aux;
	u8 values[4], pattern = 0;
	पूर्णांक err;

	err = link->ops->apply_training(link);
	अगर (err < 0) अणु
		DRM_ERROR("failed to apply link training: %d\n", err);
		वापस err;
	पूर्ण

	vs = request->voltage_swing;
	pe = request->pre_emphasis;
	pc = request->post_cursor;

	/* ग_लिखो currently selected voltage-swing and pre-emphasis levels */
	क्रम (i = 0; i < lanes; i++)
		values[i] = DP_TRAIN_VOLTAGE_SWING_LEVEL(vs[i]) |
			    DP_TRAIN_PRE_EMPHASIS_LEVEL(pe[i]);

	err = drm_dp_dpcd_ग_लिखो(aux, DP_TRAINING_LANE0_SET, values, lanes);
	अगर (err < 0) अणु
		DRM_ERROR("failed to set training parameters: %d\n", err);
		वापस err;
	पूर्ण

	/* ग_लिखो currently selected post-cursor level (अगर supported) */
	अगर (link->revision >= 0x12 && link->rate == 540000) अणु
		values[0] = values[1] = 0;

		क्रम (i = 0; i < lanes; i++)
			values[i / 2] |= DP_LANE_POST_CURSOR(i, pc[i]);

		err = drm_dp_dpcd_ग_लिखो(aux, DP_TRAINING_LANE0_1_SET2, values,
					DIV_ROUND_UP(lanes, 2));
		अगर (err < 0) अणु
			DRM_ERROR("failed to set post-cursor: %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	/* ग_लिखो link pattern */
	अगर (link->train.pattern != DP_TRAINING_PATTERN_DISABLE)
		pattern |= DP_LINK_SCRAMBLING_DISABLE;

	pattern |= link->train.pattern;

	err = drm_dp_dpcd_ग_लिखोb(aux, DP_TRAINING_PATTERN_SET, pattern);
	अगर (err < 0) अणु
		DRM_ERROR("failed to set training pattern: %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम drm_dp_link_train_रुको(काष्ठा drm_dp_link *link)
अणु
	अचिन्हित दीर्घ min = 0;

	चयन (link->train.pattern) अणु
	हाल DP_TRAINING_PATTERN_1:
		min = link->aux_rd_पूर्णांकerval.cr;
		अवरोध;

	हाल DP_TRAINING_PATTERN_2:
	हाल DP_TRAINING_PATTERN_3:
		min = link->aux_rd_पूर्णांकerval.ce;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	अगर (min > 0)
		usleep_range(min, 2 * min);
पूर्ण

अटल व्योम drm_dp_link_get_adjusपंचांगents(काष्ठा drm_dp_link *link,
					u8 status[DP_LINK_STATUS_SIZE])
अणु
	काष्ठा drm_dp_link_train_set *adjust = &link->train.adjust;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < link->lanes; i++) अणु
		adjust->voltage_swing[i] =
			drm_dp_get_adjust_request_voltage(status, i) >>
				DP_TRAIN_VOLTAGE_SWING_SHIFT;

		adjust->pre_emphasis[i] =
			drm_dp_get_adjust_request_pre_emphasis(status, i) >>
				DP_TRAIN_PRE_EMPHASIS_SHIFT;

		adjust->post_cursor[i] =
			drm_dp_get_adjust_request_post_cursor(status, i);
	पूर्ण
पूर्ण

अटल व्योम drm_dp_link_train_adjust(काष्ठा drm_dp_link_train *train)
अणु
	काष्ठा drm_dp_link_train_set *request = &train->request;
	काष्ठा drm_dp_link_train_set *adjust = &train->adjust;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < 4; i++)
		अगर (request->voltage_swing[i] != adjust->voltage_swing[i])
			request->voltage_swing[i] = adjust->voltage_swing[i];

	क्रम (i = 0; i < 4; i++)
		अगर (request->pre_emphasis[i] != adjust->pre_emphasis[i])
			request->pre_emphasis[i] = adjust->pre_emphasis[i];

	क्रम (i = 0; i < 4; i++)
		अगर (request->post_cursor[i] != adjust->post_cursor[i])
			request->post_cursor[i] = adjust->post_cursor[i];
पूर्ण

अटल पूर्णांक drm_dp_link_recover_घड़ी(काष्ठा drm_dp_link *link)
अणु
	u8 status[DP_LINK_STATUS_SIZE];
	पूर्णांक err;

	err = drm_dp_link_apply_training(link);
	अगर (err < 0)
		वापस err;

	drm_dp_link_train_रुको(link);

	err = drm_dp_dpcd_पढ़ो_link_status(link->aux, status);
	अगर (err < 0) अणु
		DRM_ERROR("failed to read link status: %d\n", err);
		वापस err;
	पूर्ण

	अगर (!drm_dp_घड़ी_recovery_ok(status, link->lanes))
		drm_dp_link_get_adjusपंचांगents(link, status);
	अन्यथा
		link->train.घड़ी_recovered = true;

	वापस 0;
पूर्ण

अटल पूर्णांक drm_dp_link_घड़ी_recovery(काष्ठा drm_dp_link *link)
अणु
	अचिन्हित पूर्णांक repeat;
	पूर्णांक err;

	/* start घड़ी recovery using training pattern 1 */
	link->train.pattern = DP_TRAINING_PATTERN_1;

	क्रम (repeat = 1; repeat < 5; repeat++) अणु
		err = drm_dp_link_recover_घड़ी(link);
		अगर (err < 0) अणु
			DRM_ERROR("failed to recover clock: %d\n", err);
			वापस err;
		पूर्ण

		अगर (link->train.घड़ी_recovered)
			अवरोध;

		drm_dp_link_train_adjust(&link->train);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक drm_dp_link_equalize_channel(काष्ठा drm_dp_link *link)
अणु
	काष्ठा drm_dp_aux *aux = link->aux;
	u8 status[DP_LINK_STATUS_SIZE];
	पूर्णांक err;

	err = drm_dp_link_apply_training(link);
	अगर (err < 0)
		वापस err;

	drm_dp_link_train_रुको(link);

	err = drm_dp_dpcd_पढ़ो_link_status(aux, status);
	अगर (err < 0) अणु
		DRM_ERROR("failed to read link status: %d\n", err);
		वापस err;
	पूर्ण

	अगर (!drm_dp_घड़ी_recovery_ok(status, link->lanes)) अणु
		DRM_ERROR("clock recovery lost while equalizing channel\n");
		link->train.घड़ी_recovered = false;
		वापस 0;
	पूर्ण

	अगर (!drm_dp_channel_eq_ok(status, link->lanes))
		drm_dp_link_get_adjusपंचांगents(link, status);
	अन्यथा
		link->train.channel_equalized = true;

	वापस 0;
पूर्ण

अटल पूर्णांक drm_dp_link_channel_equalization(काष्ठा drm_dp_link *link)
अणु
	अचिन्हित पूर्णांक repeat;
	पूर्णांक err;

	/* start channel equalization using pattern 2 or 3 */
	अगर (link->caps.tps3_supported)
		link->train.pattern = DP_TRAINING_PATTERN_3;
	अन्यथा
		link->train.pattern = DP_TRAINING_PATTERN_2;

	क्रम (repeat = 1; repeat < 5; repeat++) अणु
		err = drm_dp_link_equalize_channel(link);
		अगर (err < 0) अणु
			DRM_ERROR("failed to equalize channel: %d\n", err);
			वापस err;
		पूर्ण

		अगर (link->train.channel_equalized)
			अवरोध;

		drm_dp_link_train_adjust(&link->train);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक drm_dp_link_करोwngrade(काष्ठा drm_dp_link *link)
अणु
	चयन (link->rate) अणु
	हाल 162000:
		वापस -EINVAL;

	हाल 270000:
		link->rate = 162000;
		अवरोध;

	हाल 540000:
		link->rate = 270000;
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम drm_dp_link_train_disable(काष्ठा drm_dp_link *link)
अणु
	पूर्णांक err;

	link->train.pattern = DP_TRAINING_PATTERN_DISABLE;

	err = drm_dp_link_apply_training(link);
	अगर (err < 0)
		DRM_ERROR("failed to disable link training: %d\n", err);
पूर्ण

अटल पूर्णांक drm_dp_link_train_full(काष्ठा drm_dp_link *link)
अणु
	पूर्णांक err;

retry:
	DRM_DEBUG_KMS("full-training link: %u lane%s at %u MHz\n",
		      link->lanes, (link->lanes > 1) ? "s" : "",
		      link->rate / 100);

	err = drm_dp_link_configure(link->aux, link);
	अगर (err < 0) अणु
		DRM_ERROR("failed to configure DP link: %d\n", err);
		वापस err;
	पूर्ण

	err = drm_dp_link_घड़ी_recovery(link);
	अगर (err < 0) अणु
		DRM_ERROR("clock recovery failed: %d\n", err);
		जाओ out;
	पूर्ण

	अगर (!link->train.घड़ी_recovered) अणु
		DRM_ERROR("clock recovery failed, downgrading link\n");

		err = drm_dp_link_करोwngrade(link);
		अगर (err < 0)
			जाओ out;

		जाओ retry;
	पूर्ण

	DRM_DEBUG_KMS("clock recovery succeeded\n");

	err = drm_dp_link_channel_equalization(link);
	अगर (err < 0) अणु
		DRM_ERROR("channel equalization failed: %d\n", err);
		जाओ out;
	पूर्ण

	अगर (!link->train.channel_equalized) अणु
		DRM_ERROR("channel equalization failed, downgrading link\n");

		err = drm_dp_link_करोwngrade(link);
		अगर (err < 0)
			जाओ out;

		जाओ retry;
	पूर्ण

	DRM_DEBUG_KMS("channel equalization succeeded\n");

out:
	drm_dp_link_train_disable(link);
	वापस err;
पूर्ण

अटल पूर्णांक drm_dp_link_train_fast(काष्ठा drm_dp_link *link)
अणु
	u8 status[DP_LINK_STATUS_SIZE];
	पूर्णांक err;

	DRM_DEBUG_KMS("fast-training link: %u lane%s at %u MHz\n",
		      link->lanes, (link->lanes > 1) ? "s" : "",
		      link->rate / 100);

	err = drm_dp_link_configure(link->aux, link);
	अगर (err < 0) अणु
		DRM_ERROR("failed to configure DP link: %d\n", err);
		वापस err;
	पूर्ण

	/* transmit training pattern 1 क्रम 500 microseconds */
	link->train.pattern = DP_TRAINING_PATTERN_1;

	err = drm_dp_link_apply_training(link);
	अगर (err < 0)
		जाओ out;

	usleep_range(500, 1000);

	/* transmit training pattern 2 or 3 क्रम 500 microseconds */
	अगर (link->caps.tps3_supported)
		link->train.pattern = DP_TRAINING_PATTERN_3;
	अन्यथा
		link->train.pattern = DP_TRAINING_PATTERN_2;

	err = drm_dp_link_apply_training(link);
	अगर (err < 0)
		जाओ out;

	usleep_range(500, 1000);

	err = drm_dp_dpcd_पढ़ो_link_status(link->aux, status);
	अगर (err < 0) अणु
		DRM_ERROR("failed to read link status: %d\n", err);
		जाओ out;
	पूर्ण

	अगर (!drm_dp_घड़ी_recovery_ok(status, link->lanes)) अणु
		DRM_ERROR("clock recovery failed\n");
		err = -EIO;
	पूर्ण

	अगर (!drm_dp_channel_eq_ok(status, link->lanes)) अणु
		DRM_ERROR("channel equalization failed\n");
		err = -EIO;
	पूर्ण

out:
	drm_dp_link_train_disable(link);
	वापस err;
पूर्ण

/**
 * drm_dp_link_train() - perक्रमm DisplayPort link training
 * @link: a DP link object
 *
 * Uses the context stored in the DP link object to perक्रमm link training. It
 * is expected that drivers will call drm_dp_link_probe() to obtain the link
 * capabilities beक्रमe perक्रमming link training.
 *
 * If the sink supports fast link training (no AUX CH handshake) and valid
 * training settings are available, this function will try to perक्रमm fast
 * link training and fall back to full link training on failure.
 *
 * Returns: 0 on success or a negative error code on failure.
 */
पूर्णांक drm_dp_link_train(काष्ठा drm_dp_link *link)
अणु
	पूर्णांक err;

	drm_dp_link_train_init(&link->train);

	अगर (link->caps.fast_training) अणु
		अगर (drm_dp_link_train_valid(&link->train)) अणु
			err = drm_dp_link_train_fast(link);
			अगर (err < 0)
				DRM_ERROR("fast link training failed: %d\n",
					  err);
			अन्यथा
				वापस 0;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("training parameters not available\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		DRM_DEBUG_KMS("fast link training not supported\n");
	पूर्ण

	err = drm_dp_link_train_full(link);
	अगर (err < 0)
		DRM_ERROR("full link training failed: %d\n", err);

	वापस err;
पूर्ण
