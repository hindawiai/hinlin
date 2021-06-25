<शैली गुरु>
/* Copyright 2015 Advanced Micro Devices, Inc. */
#समावेश "dm_services.h"
#समावेश "dc.h"
#समावेश "dc_link_dp.h"
#समावेश "dm_helpers.h"
#समावेश "opp.h"
#समावेश "dsc.h"
#समावेश "resource.h"

#समावेश "inc/core_types.h"
#समावेश "link_hwss.h"
#समावेश "dc_link_ddc.h"
#समावेश "core_status.h"
#समावेश "dpcd_defs.h"
#समावेश "dc_dmub_srv.h"
#समावेश "dce/dmub_hw_lock_mgr.h"

/*Travis*/
अटल स्थिर uपूर्णांक8_t DP_VGA_LVDS_CONVERTER_ID_2[] = "sivarT";
/*Nuपंचांगeg*/
अटल स्थिर uपूर्णांक8_t DP_VGA_LVDS_CONVERTER_ID_3[] = "dnomlA";

#घोषणा DC_LOGGER \
	link->ctx->logger
#घोषणा DC_TRACE_LEVEL_MESSAGE(...) /* करो nothing */

#घोषणा DP_REPEATER_CONFIGURATION_AND_STATUS_SIZE   0x50

	/* maximum pre emphasis level allowed क्रम each voltage swing level*/
	अटल स्थिर क्रमागत dc_pre_emphasis
	voltage_swing_to_pre_emphasis[] = अणु PRE_EMPHASIS_LEVEL3,
					    PRE_EMPHASIS_LEVEL2,
					    PRE_EMPHASIS_LEVEL1,
					    PRE_EMPHASIS_DISABLED पूर्ण;

क्रमागत अणु
	POST_LT_ADJ_REQ_LIMIT = 6,
	POST_LT_ADJ_REQ_TIMEOUT = 200
पूर्ण;

क्रमागत अणु
	LINK_TRAINING_MAX_RETRY_COUNT = 5,
	/* to aव्योम infinite loop where-in the receiver
	 * चयनes between dअगरferent VS
	 */
	LINK_TRAINING_MAX_CR_RETRY = 100
पूर्ण;

अटल bool decide_fallback_link_setting(
		काष्ठा dc_link_settings initial_link_settings,
		काष्ठा dc_link_settings *current_link_setting,
		क्रमागत link_training_result training_result);
अटल काष्ठा dc_link_settings get_common_supported_link_settings(
		काष्ठा dc_link_settings link_setting_a,
		काष्ठा dc_link_settings link_setting_b);

अटल uपूर्णांक32_t get_cr_training_aux_rd_पूर्णांकerval(काष्ठा dc_link *link,
		स्थिर काष्ठा dc_link_settings *link_settings)
अणु
	जोड़ training_aux_rd_पूर्णांकerval training_rd_पूर्णांकerval;
	uपूर्णांक32_t रुको_in_micro_secs = 100;

	स_रखो(&training_rd_पूर्णांकerval, 0, माप(training_rd_पूर्णांकerval));
	core_link_पढ़ो_dpcd(
			link,
			DP_TRAINING_AUX_RD_INTERVAL,
			(uपूर्णांक8_t *)&training_rd_पूर्णांकerval,
			माप(training_rd_पूर्णांकerval));
	अगर (training_rd_पूर्णांकerval.bits.TRAINIG_AUX_RD_INTERVAL)
		रुको_in_micro_secs = training_rd_पूर्णांकerval.bits.TRAINIG_AUX_RD_INTERVAL * 4000;
	वापस रुको_in_micro_secs;
पूर्ण

अटल uपूर्णांक32_t get_eq_training_aux_rd_पूर्णांकerval(
	काष्ठा dc_link *link,
	स्थिर काष्ठा dc_link_settings *link_settings)
अणु
	जोड़ training_aux_rd_पूर्णांकerval training_rd_पूर्णांकerval;
	uपूर्णांक32_t रुको_in_micro_secs = 400;

	स_रखो(&training_rd_पूर्णांकerval, 0, माप(training_rd_पूर्णांकerval));
	/* overग_लिखो the delay अगर rev > 1.1*/
	अगर (link->dpcd_caps.dpcd_rev.raw >= DPCD_REV_12) अणु
		/* DP 1.2 or later - retrieve delay through
		 * "DPCD_ADDR_TRAINING_AUX_RD_INTERVAL" रेजिस्टर */
		core_link_पढ़ो_dpcd(
			link,
			DP_TRAINING_AUX_RD_INTERVAL,
			(uपूर्णांक8_t *)&training_rd_पूर्णांकerval,
			माप(training_rd_पूर्णांकerval));

		अगर (training_rd_पूर्णांकerval.bits.TRAINIG_AUX_RD_INTERVAL)
			रुको_in_micro_secs = training_rd_पूर्णांकerval.bits.TRAINIG_AUX_RD_INTERVAL * 4000;
	पूर्ण

	वापस रुको_in_micro_secs;
पूर्ण

अटल व्योम रुको_क्रम_training_aux_rd_पूर्णांकerval(
	काष्ठा dc_link *link,
	uपूर्णांक32_t रुको_in_micro_secs)
अणु
	udelay(रुको_in_micro_secs);

	DC_LOG_HW_LINK_TRAINING("%s:\n wait = %d\n",
		__func__,
		रुको_in_micro_secs);
पूर्ण

अटल व्योम dpcd_set_training_pattern(
	काष्ठा dc_link *link,
	जोड़ dpcd_training_pattern dpcd_pattern)
अणु
	core_link_ग_लिखो_dpcd(
		link,
		DP_TRAINING_PATTERN_SET,
		&dpcd_pattern.raw,
		1);

	DC_LOG_HW_LINK_TRAINING("%s\n %x pattern = %x\n",
		__func__,
		DP_TRAINING_PATTERN_SET,
		dpcd_pattern.v1_4.TRAINING_PATTERN_SET);
पूर्ण

अटल क्रमागत dc_dp_training_pattern decide_cr_training_pattern(
		स्थिर काष्ठा dc_link_settings *link_settings)
अणु
	वापस DP_TRAINING_PATTERN_SEQUENCE_1;
पूर्ण

अटल क्रमागत dc_dp_training_pattern decide_eq_training_pattern(काष्ठा dc_link *link,
		स्थिर काष्ठा dc_link_settings *link_settings)
अणु
	क्रमागत dc_dp_training_pattern highest_tp = DP_TRAINING_PATTERN_SEQUENCE_2;
	काष्ठा encoder_feature_support *features = &link->link_enc->features;
	काष्ठा dpcd_caps *dpcd_caps = &link->dpcd_caps;

	अगर (features->flags.bits.IS_TPS3_CAPABLE)
		highest_tp = DP_TRAINING_PATTERN_SEQUENCE_3;

	अगर (features->flags.bits.IS_TPS4_CAPABLE)
		highest_tp = DP_TRAINING_PATTERN_SEQUENCE_4;

	अगर (dpcd_caps->max_करोwn_spपढ़ो.bits.TPS4_SUPPORTED &&
		highest_tp >= DP_TRAINING_PATTERN_SEQUENCE_4)
		वापस DP_TRAINING_PATTERN_SEQUENCE_4;

	अगर (dpcd_caps->max_ln_count.bits.TPS3_SUPPORTED &&
		highest_tp >= DP_TRAINING_PATTERN_SEQUENCE_3)
		वापस DP_TRAINING_PATTERN_SEQUENCE_3;

	वापस DP_TRAINING_PATTERN_SEQUENCE_2;
पूर्ण

अटल व्योम dpcd_set_link_settings(
	काष्ठा dc_link *link,
	स्थिर काष्ठा link_training_settings *lt_settings)
अणु
	uपूर्णांक8_t rate;

	जोड़ करोwn_spपढ़ो_ctrl करोwnspपढ़ो = अणु अणु0पूर्ण पूर्ण;
	जोड़ lane_count_set lane_count_set = अणु अणु0पूर्ण पूर्ण;

	करोwnspपढ़ो.raw = (uपूर्णांक8_t)
	(lt_settings->link_settings.link_spपढ़ो);

	lane_count_set.bits.LANE_COUNT_SET =
	lt_settings->link_settings.lane_count;

	lane_count_set.bits.ENHANCED_FRAMING = lt_settings->enhanced_framing;
	lane_count_set.bits.POST_LT_ADJ_REQ_GRANTED = 0;


	अगर (lt_settings->pattern_क्रम_eq < DP_TRAINING_PATTERN_SEQUENCE_4) अणु
		lane_count_set.bits.POST_LT_ADJ_REQ_GRANTED =
				link->dpcd_caps.max_ln_count.bits.POST_LT_ADJ_REQ_SUPPORTED;
	पूर्ण

	core_link_ग_लिखो_dpcd(link, DP_DOWNSPREAD_CTRL,
		&करोwnspपढ़ो.raw, माप(करोwnspपढ़ो));

	core_link_ग_लिखो_dpcd(link, DP_LANE_COUNT_SET,
		&lane_count_set.raw, 1);

	अगर (link->dpcd_caps.dpcd_rev.raw >= DPCD_REV_14 &&
			lt_settings->link_settings.use_link_rate_set == true) अणु
		rate = 0;
		/* WA क्रम some MUX chips that will घातer करोwn with eDP and lose supported
		 * link rate set क्रम eDP 1.4. Source पढ़ोs DPCD 0x010 again to ensure
		 * MUX chip माला_लो link rate set back beक्रमe link training.
		 */
		अगर (link->connector_संकेत == SIGNAL_TYPE_EDP) अणु
			uपूर्णांक8_t supported_link_rates[16];

			core_link_पढ़ो_dpcd(link, DP_SUPPORTED_LINK_RATES,
					supported_link_rates, माप(supported_link_rates));
		पूर्ण
		core_link_ग_लिखो_dpcd(link, DP_LINK_BW_SET, &rate, 1);
		core_link_ग_लिखो_dpcd(link, DP_LINK_RATE_SET,
				&lt_settings->link_settings.link_rate_set, 1);
	पूर्ण अन्यथा अणु
		rate = (uपूर्णांक8_t) (lt_settings->link_settings.link_rate);
		core_link_ग_लिखो_dpcd(link, DP_LINK_BW_SET, &rate, 1);
	पूर्ण

	अगर (rate) अणु
		DC_LOG_HW_LINK_TRAINING("%s\n %x rate = %x\n %x lane = %x framing = %x\n %x spread = %x\n",
			__func__,
			DP_LINK_BW_SET,
			lt_settings->link_settings.link_rate,
			DP_LANE_COUNT_SET,
			lt_settings->link_settings.lane_count,
			lt_settings->enhanced_framing,
			DP_DOWNSPREAD_CTRL,
			lt_settings->link_settings.link_spपढ़ो);
	पूर्ण अन्यथा अणु
		DC_LOG_HW_LINK_TRAINING("%s\n %x rate set = %x\n %x lane = %x framing = %x\n %x spread = %x\n",
			__func__,
			DP_LINK_RATE_SET,
			lt_settings->link_settings.link_rate_set,
			DP_LANE_COUNT_SET,
			lt_settings->link_settings.lane_count,
			lt_settings->enhanced_framing,
			DP_DOWNSPREAD_CTRL,
			lt_settings->link_settings.link_spपढ़ो);
	पूर्ण
पूर्ण

अटल क्रमागत dpcd_training_patterns
	dc_dp_training_pattern_to_dpcd_training_pattern(
	काष्ठा dc_link *link,
	क्रमागत dc_dp_training_pattern pattern)
अणु
	क्रमागत dpcd_training_patterns dpcd_tr_pattern =
	DPCD_TRAINING_PATTERN_VIDEOIDLE;

	चयन (pattern) अणु
	हाल DP_TRAINING_PATTERN_SEQUENCE_1:
		dpcd_tr_pattern = DPCD_TRAINING_PATTERN_1;
		अवरोध;
	हाल DP_TRAINING_PATTERN_SEQUENCE_2:
		dpcd_tr_pattern = DPCD_TRAINING_PATTERN_2;
		अवरोध;
	हाल DP_TRAINING_PATTERN_SEQUENCE_3:
		dpcd_tr_pattern = DPCD_TRAINING_PATTERN_3;
		अवरोध;
	हाल DP_TRAINING_PATTERN_SEQUENCE_4:
		dpcd_tr_pattern = DPCD_TRAINING_PATTERN_4;
		अवरोध;
	शेष:
		ASSERT(0);
		DC_LOG_HW_LINK_TRAINING("%s: Invalid HW Training pattern: %d\n",
			__func__, pattern);
		अवरोध;
	पूर्ण

	वापस dpcd_tr_pattern;
पूर्ण

अटल uपूर्णांक8_t dc_dp_initialize_scrambling_data_symbols(
	काष्ठा dc_link *link,
	क्रमागत dc_dp_training_pattern pattern)
अणु
	uपूर्णांक8_t disable_scrabled_data_symbols = 0;

	चयन (pattern) अणु
	हाल DP_TRAINING_PATTERN_SEQUENCE_1:
	हाल DP_TRAINING_PATTERN_SEQUENCE_2:
	हाल DP_TRAINING_PATTERN_SEQUENCE_3:
		disable_scrabled_data_symbols = 1;
		अवरोध;
	हाल DP_TRAINING_PATTERN_SEQUENCE_4:
		disable_scrabled_data_symbols = 0;
		अवरोध;
	शेष:
		ASSERT(0);
		DC_LOG_HW_LINK_TRAINING("%s: Invalid HW Training pattern: %d\n",
			__func__, pattern);
		अवरोध;
	पूर्ण
	वापस disable_scrabled_data_symbols;
पूर्ण

अटल अंतरभूत bool is_repeater(काष्ठा dc_link *link, uपूर्णांक32_t offset)
अणु
	वापस (link->lttpr_mode == LTTPR_MODE_NON_TRANSPARENT) && (offset != 0);
पूर्ण

अटल व्योम dpcd_set_lt_pattern_and_lane_settings(
	काष्ठा dc_link *link,
	स्थिर काष्ठा link_training_settings *lt_settings,
	क्रमागत dc_dp_training_pattern pattern,
	uपूर्णांक32_t offset)
अणु
	जोड़ dpcd_training_lane dpcd_lane[LANE_COUNT_DP_MAX] = अणु अणु अणु0पूर्ण पूर्ण पूर्ण;

	uपूर्णांक32_t dpcd_base_lt_offset;

	uपूर्णांक8_t dpcd_lt_buffer[5] = अणु0पूर्ण;
	जोड़ dpcd_training_pattern dpcd_pattern = अणु अणु0पूर्ण पूर्ण;
	uपूर्णांक32_t lane;
	uपूर्णांक32_t size_in_bytes;
	bool edp_workaround = false; /* TODO link_prop.INTERNAL */
	dpcd_base_lt_offset = DP_TRAINING_PATTERN_SET;

	अगर (is_repeater(link, offset))
		dpcd_base_lt_offset = DP_TRAINING_PATTERN_SET_PHY_REPEATER1 +
			((DP_REPEATER_CONFIGURATION_AND_STATUS_SIZE) * (offset - 1));

	/*****************************************************************
	* DpcdAddress_TrainingPatternSet
	*****************************************************************/
	dpcd_pattern.v1_4.TRAINING_PATTERN_SET =
		dc_dp_training_pattern_to_dpcd_training_pattern(link, pattern);

	dpcd_pattern.v1_4.SCRAMBLING_DISABLE =
		dc_dp_initialize_scrambling_data_symbols(link, pattern);

	dpcd_lt_buffer[DP_TRAINING_PATTERN_SET - DP_TRAINING_PATTERN_SET]
		= dpcd_pattern.raw;

	अगर (is_repeater(link, offset)) अणु
		DC_LOG_HW_LINK_TRAINING("%s\n LTTPR Repeater ID: %d\n 0x%X pattern = %x\n",
			__func__,
			offset,
			dpcd_base_lt_offset,
			dpcd_pattern.v1_4.TRAINING_PATTERN_SET);
	पूर्ण अन्यथा अणु
		DC_LOG_HW_LINK_TRAINING("%s\n 0x%X pattern = %x\n",
			__func__,
			dpcd_base_lt_offset,
			dpcd_pattern.v1_4.TRAINING_PATTERN_SET);
	पूर्ण
	/*****************************************************************
	* DpcdAddress_Lane0Set -> DpcdAddress_Lane3Set
	*****************************************************************/
	क्रम (lane = 0; lane <
		(uपूर्णांक32_t)(lt_settings->link_settings.lane_count); lane++) अणु

		dpcd_lane[lane].bits.VOLTAGE_SWING_SET =
		(uपूर्णांक8_t)(lt_settings->lane_settings[lane].VOLTAGE_SWING);
		dpcd_lane[lane].bits.PRE_EMPHASIS_SET =
		(uपूर्णांक8_t)(lt_settings->lane_settings[lane].PRE_EMPHASIS);

		dpcd_lane[lane].bits.MAX_SWING_REACHED =
		(lt_settings->lane_settings[lane].VOLTAGE_SWING ==
		VOLTAGE_SWING_MAX_LEVEL ? 1 : 0);
		dpcd_lane[lane].bits.MAX_PRE_EMPHASIS_REACHED =
		(lt_settings->lane_settings[lane].PRE_EMPHASIS ==
		PRE_EMPHASIS_MAX_LEVEL ? 1 : 0);
	पूर्ण

	/* concatenate everything पूर्णांकo one buffer*/

	size_in_bytes = lt_settings->link_settings.lane_count * माप(dpcd_lane[0]);

	 // 0x00103 - 0x00102
	स_हटाओ(
		&dpcd_lt_buffer[DP_TRAINING_LANE0_SET - DP_TRAINING_PATTERN_SET],
		dpcd_lane,
		size_in_bytes);

	अगर (is_repeater(link, offset)) अणु
		DC_LOG_HW_LINK_TRAINING("%s:\n LTTPR Repeater ID: %d\n"
				" 0x%X VS set = %x PE set = %x max VS Reached = %x  max PE Reached = %x\n",
			__func__,
			offset,
			dpcd_base_lt_offset,
			dpcd_lane[0].bits.VOLTAGE_SWING_SET,
			dpcd_lane[0].bits.PRE_EMPHASIS_SET,
			dpcd_lane[0].bits.MAX_SWING_REACHED,
			dpcd_lane[0].bits.MAX_PRE_EMPHASIS_REACHED);
	पूर्ण अन्यथा अणु
		DC_LOG_HW_LINK_TRAINING("%s:\n 0x%X VS set = %x  PE set = %x max VS Reached = %x  max PE Reached = %x\n",
			__func__,
			dpcd_base_lt_offset,
			dpcd_lane[0].bits.VOLTAGE_SWING_SET,
			dpcd_lane[0].bits.PRE_EMPHASIS_SET,
			dpcd_lane[0].bits.MAX_SWING_REACHED,
			dpcd_lane[0].bits.MAX_PRE_EMPHASIS_REACHED);
	पूर्ण
	अगर (edp_workaround) अणु
		/* क्रम eDP ग_लिखो in 2 parts because the 5-byte burst is
		* causing issues on some eDP panels (EPR#366724)
		*/
		core_link_ग_लिखो_dpcd(
			link,
			DP_TRAINING_PATTERN_SET,
			&dpcd_pattern.raw,
			माप(dpcd_pattern.raw));

		core_link_ग_लिखो_dpcd(
			link,
			DP_TRAINING_LANE0_SET,
			(uपूर्णांक8_t *)(dpcd_lane),
			size_in_bytes);

		पूर्ण अन्यथा
		/* ग_लिखो it all in (1 + number-of-lanes)-byte burst*/
			core_link_ग_लिखो_dpcd(
				link,
				dpcd_base_lt_offset,
				dpcd_lt_buffer,
				size_in_bytes + माप(dpcd_pattern.raw));

	link->cur_lane_setting = lt_settings->lane_settings[0];
पूर्ण

अटल bool is_cr_करोne(क्रमागत dc_lane_count ln_count,
	जोड़ lane_status *dpcd_lane_status)
अणु
	uपूर्णांक32_t lane;
	/*LANEx_CR_DONE bits All 1's?*/
	क्रम (lane = 0; lane < (uपूर्णांक32_t)(ln_count); lane++) अणु
		अगर (!dpcd_lane_status[lane].bits.CR_DONE_0)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल bool is_ch_eq_करोne(क्रमागत dc_lane_count ln_count,
	जोड़ lane_status *dpcd_lane_status,
	जोड़ lane_align_status_updated *lane_status_updated)
अणु
	uपूर्णांक32_t lane;
	अगर (!lane_status_updated->bits.INTERLANE_ALIGN_DONE)
		वापस false;
	अन्यथा अणु
		क्रम (lane = 0; lane < (uपूर्णांक32_t)(ln_count); lane++) अणु
			अगर (!dpcd_lane_status[lane].bits.SYMBOL_LOCKED_0 ||
				!dpcd_lane_status[lane].bits.CHANNEL_EQ_DONE_0)
				वापस false;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम update_drive_settings(
		काष्ठा link_training_settings *dest,
		काष्ठा link_training_settings src)
अणु
	uपूर्णांक32_t lane;
	क्रम (lane = 0; lane < src.link_settings.lane_count; lane++) अणु
		अगर (dest->voltage_swing == शून्य)
			dest->lane_settings[lane].VOLTAGE_SWING = src.lane_settings[lane].VOLTAGE_SWING;
		अन्यथा
			dest->lane_settings[lane].VOLTAGE_SWING = *dest->voltage_swing;

		अगर (dest->pre_emphasis == शून्य)
			dest->lane_settings[lane].PRE_EMPHASIS = src.lane_settings[lane].PRE_EMPHASIS;
		अन्यथा
			dest->lane_settings[lane].PRE_EMPHASIS = *dest->pre_emphasis;

		अगर (dest->post_cursor2 == शून्य)
			dest->lane_settings[lane].POST_CURSOR2 = src.lane_settings[lane].POST_CURSOR2;
		अन्यथा
			dest->lane_settings[lane].POST_CURSOR2 = *dest->post_cursor2;
	पूर्ण
पूर्ण

अटल uपूर्णांक8_t get_nibble_at_index(स्थिर uपूर्णांक8_t *buf,
	uपूर्णांक32_t index)
अणु
	uपूर्णांक8_t nibble;
	nibble = buf[index / 2];

	अगर (index % 2)
		nibble >>= 4;
	अन्यथा
		nibble &= 0x0F;

	वापस nibble;
पूर्ण

अटल क्रमागत dc_pre_emphasis get_max_pre_emphasis_क्रम_voltage_swing(
	क्रमागत dc_voltage_swing voltage)
अणु
	क्रमागत dc_pre_emphasis pre_emphasis;
	pre_emphasis = PRE_EMPHASIS_MAX_LEVEL;

	अगर (voltage <= VOLTAGE_SWING_MAX_LEVEL)
		pre_emphasis = voltage_swing_to_pre_emphasis[voltage];

	वापस pre_emphasis;

पूर्ण

अटल व्योम find_max_drive_settings(
	स्थिर काष्ठा link_training_settings *link_training_setting,
	काष्ठा link_training_settings *max_lt_setting)
अणु
	uपूर्णांक32_t lane;
	काष्ठा dc_lane_settings max_requested;

	max_requested.VOLTAGE_SWING =
		link_training_setting->
		lane_settings[0].VOLTAGE_SWING;
	max_requested.PRE_EMPHASIS =
		link_training_setting->
		lane_settings[0].PRE_EMPHASIS;
	/*max_requested.postCursor2 =
	 * link_training_setting->laneSettings[0].postCursor2;*/

	/* Determine what the maximum of the requested settings are*/
	क्रम (lane = 1; lane < link_training_setting->link_settings.lane_count;
			lane++) अणु
		अगर (link_training_setting->lane_settings[lane].VOLTAGE_SWING >
			max_requested.VOLTAGE_SWING)

			max_requested.VOLTAGE_SWING =
			link_training_setting->
			lane_settings[lane].VOLTAGE_SWING;

		अगर (link_training_setting->lane_settings[lane].PRE_EMPHASIS >
				max_requested.PRE_EMPHASIS)
			max_requested.PRE_EMPHASIS =
			link_training_setting->
			lane_settings[lane].PRE_EMPHASIS;

		/*
		अगर (link_training_setting->laneSettings[lane].postCursor2 >
		 max_requested.postCursor2)
		अणु
		max_requested.postCursor2 =
		link_training_setting->laneSettings[lane].postCursor2;
		पूर्ण
		*/
	पूर्ण

	/* make sure the requested settings are
	 * not higher than maximum settings*/
	अगर (max_requested.VOLTAGE_SWING > VOLTAGE_SWING_MAX_LEVEL)
		max_requested.VOLTAGE_SWING = VOLTAGE_SWING_MAX_LEVEL;

	अगर (max_requested.PRE_EMPHASIS > PRE_EMPHASIS_MAX_LEVEL)
		max_requested.PRE_EMPHASIS = PRE_EMPHASIS_MAX_LEVEL;
	/*
	अगर (max_requested.postCursor2 > PostCursor2_MaxLevel)
	max_requested.postCursor2 = PostCursor2_MaxLevel;
	*/

	/* make sure the pre-emphasis matches the voltage swing*/
	अगर (max_requested.PRE_EMPHASIS >
		get_max_pre_emphasis_क्रम_voltage_swing(
			max_requested.VOLTAGE_SWING))
		max_requested.PRE_EMPHASIS =
		get_max_pre_emphasis_क्रम_voltage_swing(
			max_requested.VOLTAGE_SWING);

	/*
	 * Post Cursor2 levels are completely independent from
	 * pre-emphasis (Post Cursor1) levels. But Post Cursor2 levels
	 * can only be applied to each allowable combination of voltage
	 * swing and pre-emphasis levels */
	 /* अगर ( max_requested.postCursor2 >
	  *  getMaxPostCursor2ForVoltageSwing(max_requested.voltageSwing))
	  *  max_requested.postCursor2 =
	  *  getMaxPostCursor2ForVoltageSwing(max_requested.voltageSwing);
	  */

	max_lt_setting->link_settings.link_rate =
		link_training_setting->link_settings.link_rate;
	max_lt_setting->link_settings.lane_count =
	link_training_setting->link_settings.lane_count;
	max_lt_setting->link_settings.link_spपढ़ो =
		link_training_setting->link_settings.link_spपढ़ो;

	क्रम (lane = 0; lane <
		link_training_setting->link_settings.lane_count;
		lane++) अणु
		max_lt_setting->lane_settings[lane].VOLTAGE_SWING =
			max_requested.VOLTAGE_SWING;
		max_lt_setting->lane_settings[lane].PRE_EMPHASIS =
			max_requested.PRE_EMPHASIS;
		/*max_lt_setting->laneSettings[lane].postCursor2 =
		 * max_requested.postCursor2;
		 */
	पूर्ण

पूर्ण

अटल व्योम get_lane_status_and_drive_settings(
	काष्ठा dc_link *link,
	स्थिर काष्ठा link_training_settings *link_training_setting,
	जोड़ lane_status *ln_status,
	जोड़ lane_align_status_updated *ln_status_updated,
	काष्ठा link_training_settings *req_settings,
	uपूर्णांक32_t offset)
अणु
	अचिन्हित पूर्णांक lane01_status_address = DP_LANE0_1_STATUS;
	uपूर्णांक8_t lane_adjust_offset = 4;
	अचिन्हित पूर्णांक lane01_adjust_address;
	uपूर्णांक8_t dpcd_buf[6] = अणु0पूर्ण;
	जोड़ lane_adjust dpcd_lane_adjust[LANE_COUNT_DP_MAX] = अणु अणु अणु0पूर्ण पूर्ण पूर्ण;
	काष्ठा link_training_settings request_settings = अणु अणु0पूर्ण पूर्ण;
	uपूर्णांक32_t lane;

	स_रखो(req_settings, '\0', माप(काष्ठा link_training_settings));

	अगर (is_repeater(link, offset)) अणु
		lane01_status_address =
				DP_LANE0_1_STATUS_PHY_REPEATER1 +
				((DP_REPEATER_CONFIGURATION_AND_STATUS_SIZE) * (offset - 1));
		lane_adjust_offset = 3;
	पूर्ण

	core_link_पढ़ो_dpcd(
		link,
		lane01_status_address,
		(uपूर्णांक8_t *)(dpcd_buf),
		माप(dpcd_buf));

	क्रम (lane = 0; lane <
		(uपूर्णांक32_t)(link_training_setting->link_settings.lane_count);
		lane++) अणु

		ln_status[lane].raw =
			get_nibble_at_index(&dpcd_buf[0], lane);
		dpcd_lane_adjust[lane].raw =
			get_nibble_at_index(&dpcd_buf[lane_adjust_offset], lane);
	पूर्ण

	ln_status_updated->raw = dpcd_buf[2];

	अगर (is_repeater(link, offset)) अणु
		DC_LOG_HW_LINK_TRAINING("%s:\n LTTPR Repeater ID: %d\n"
				" 0x%X Lane01Status = %x\n 0x%X Lane23Status = %x\n ",
			__func__,
			offset,
			lane01_status_address, dpcd_buf[0],
			lane01_status_address + 1, dpcd_buf[1]);
	पूर्ण अन्यथा अणु
		DC_LOG_HW_LINK_TRAINING("%s:\n 0x%X Lane01Status = %x\n 0x%X Lane23Status = %x\n ",
			__func__,
			lane01_status_address, dpcd_buf[0],
			lane01_status_address + 1, dpcd_buf[1]);
	पूर्ण
	lane01_adjust_address = DP_ADJUST_REQUEST_LANE0_1;

	अगर (is_repeater(link, offset))
		lane01_adjust_address = DP_ADJUST_REQUEST_LANE0_1_PHY_REPEATER1 +
				((DP_REPEATER_CONFIGURATION_AND_STATUS_SIZE) * (offset - 1));

	अगर (is_repeater(link, offset)) अणु
		DC_LOG_HW_LINK_TRAINING("%s:\n LTTPR Repeater ID: %d\n"
				" 0x%X Lane01AdjustRequest = %x\n 0x%X Lane23AdjustRequest = %x\n",
					__func__,
					offset,
					lane01_adjust_address,
					dpcd_buf[lane_adjust_offset],
					lane01_adjust_address + 1,
					dpcd_buf[lane_adjust_offset + 1]);
	पूर्ण अन्यथा अणु
		DC_LOG_HW_LINK_TRAINING("%s:\n 0x%X Lane01AdjustRequest = %x\n 0x%X Lane23AdjustRequest = %x\n",
			__func__,
			lane01_adjust_address,
			dpcd_buf[lane_adjust_offset],
			lane01_adjust_address + 1,
			dpcd_buf[lane_adjust_offset + 1]);
	पूर्ण

	/*copy to req_settings*/
	request_settings.link_settings.lane_count =
		link_training_setting->link_settings.lane_count;
	request_settings.link_settings.link_rate =
		link_training_setting->link_settings.link_rate;
	request_settings.link_settings.link_spपढ़ो =
		link_training_setting->link_settings.link_spपढ़ो;

	क्रम (lane = 0; lane <
		(uपूर्णांक32_t)(link_training_setting->link_settings.lane_count);
		lane++) अणु

		request_settings.lane_settings[lane].VOLTAGE_SWING =
			(क्रमागत dc_voltage_swing)(dpcd_lane_adjust[lane].bits.
				VOLTAGE_SWING_LANE);
		request_settings.lane_settings[lane].PRE_EMPHASIS =
			(क्रमागत dc_pre_emphasis)(dpcd_lane_adjust[lane].bits.
				PRE_EMPHASIS_LANE);
	पूर्ण

	/*Note: क्रम postcursor2, पढ़ो adjusted
	 * postcursor2 settings from*/
	/*DpcdAddress_AdjustRequestPostCursor2 =
	 *0x020C (not implemented yet)*/

	/* we find the maximum of the requested settings across all lanes*/
	/* and set this maximum क्रम all lanes*/
	find_max_drive_settings(&request_settings, req_settings);

	/* अगर post cursor 2 is needed in the future,
	 * पढ़ो DpcdAddress_AdjustRequestPostCursor2 = 0x020C
	 */

पूर्ण

अटल व्योम dpcd_set_lane_settings(
	काष्ठा dc_link *link,
	स्थिर काष्ठा link_training_settings *link_training_setting,
	uपूर्णांक32_t offset)
अणु
	जोड़ dpcd_training_lane dpcd_lane[LANE_COUNT_DP_MAX] = अणुअणुअणु0पूर्णपूर्णपूर्ण;
	uपूर्णांक32_t lane;
	अचिन्हित पूर्णांक lane0_set_address;

	lane0_set_address = DP_TRAINING_LANE0_SET;

	अगर (is_repeater(link, offset))
		lane0_set_address = DP_TRAINING_LANE0_SET_PHY_REPEATER1 +
		((DP_REPEATER_CONFIGURATION_AND_STATUS_SIZE) * (offset - 1));

	क्रम (lane = 0; lane <
		(uपूर्णांक32_t)(link_training_setting->
		link_settings.lane_count);
		lane++) अणु
		dpcd_lane[lane].bits.VOLTAGE_SWING_SET =
			(uपूर्णांक8_t)(link_training_setting->
			lane_settings[lane].VOLTAGE_SWING);
		dpcd_lane[lane].bits.PRE_EMPHASIS_SET =
			(uपूर्णांक8_t)(link_training_setting->
			lane_settings[lane].PRE_EMPHASIS);
		dpcd_lane[lane].bits.MAX_SWING_REACHED =
			(link_training_setting->
			lane_settings[lane].VOLTAGE_SWING ==
			VOLTAGE_SWING_MAX_LEVEL ? 1 : 0);
		dpcd_lane[lane].bits.MAX_PRE_EMPHASIS_REACHED =
			(link_training_setting->
			lane_settings[lane].PRE_EMPHASIS ==
			PRE_EMPHASIS_MAX_LEVEL ? 1 : 0);
	पूर्ण

	core_link_ग_लिखो_dpcd(link,
		lane0_set_address,
		(uपूर्णांक8_t *)(dpcd_lane),
		link_training_setting->link_settings.lane_count);

	/*
	अगर (LTSettings.link.rate == LinkRate_High2)
	अणु
		DpcdTrainingLaneSet2 dpcd_lane2[lane_count_DPMax] = अणु0पूर्ण;
		क्रम ( uपूर्णांक32_t lane = 0;
		lane < lane_count_DPMax; lane++)
		अणु
			dpcd_lane2[lane].bits.post_cursor2_set =
			अटल_cast<अचिन्हित अक्षर>(
			LTSettings.laneSettings[lane].postCursor2);
			dpcd_lane2[lane].bits.max_post_cursor2_reached = 0;
		पूर्ण
		m_pDpcdAccessSrv->WriteDpcdData(
		DpcdAddress_Lane0Set2,
		reपूर्णांकerpret_cast<अचिन्हित अक्षर*>(dpcd_lane2),
		LTSettings.link.lanes);
	पूर्ण
	*/

	अगर (is_repeater(link, offset)) अणु
		DC_LOG_HW_LINK_TRAINING("%s\n LTTPR Repeater ID: %d\n"
				" 0x%X VS set = %x  PE set = %x max VS Reached = %x  max PE Reached = %x\n",
			__func__,
			offset,
			lane0_set_address,
			dpcd_lane[0].bits.VOLTAGE_SWING_SET,
			dpcd_lane[0].bits.PRE_EMPHASIS_SET,
			dpcd_lane[0].bits.MAX_SWING_REACHED,
			dpcd_lane[0].bits.MAX_PRE_EMPHASIS_REACHED);

	पूर्ण अन्यथा अणु
		DC_LOG_HW_LINK_TRAINING("%s\n 0x%X VS set = %x  PE set = %x max VS Reached = %x  max PE Reached = %x\n",
			__func__,
			lane0_set_address,
			dpcd_lane[0].bits.VOLTAGE_SWING_SET,
			dpcd_lane[0].bits.PRE_EMPHASIS_SET,
			dpcd_lane[0].bits.MAX_SWING_REACHED,
			dpcd_lane[0].bits.MAX_PRE_EMPHASIS_REACHED);
	पूर्ण
	link->cur_lane_setting = link_training_setting->lane_settings[0];

पूर्ण

अटल bool is_max_vs_reached(
	स्थिर काष्ठा link_training_settings *lt_settings)
अणु
	uपूर्णांक32_t lane;
	क्रम (lane = 0; lane <
		(uपूर्णांक32_t)(lt_settings->link_settings.lane_count);
		lane++) अणु
		अगर (lt_settings->lane_settings[lane].VOLTAGE_SWING
			== VOLTAGE_SWING_MAX_LEVEL)
			वापस true;
	पूर्ण
	वापस false;

पूर्ण

अटल bool perक्रमm_post_lt_adj_req_sequence(
	काष्ठा dc_link *link,
	काष्ठा link_training_settings *lt_settings)
अणु
	क्रमागत dc_lane_count lane_count =
	lt_settings->link_settings.lane_count;

	uपूर्णांक32_t adj_req_count;
	uपूर्णांक32_t adj_req_समयr;
	bool req_drv_setting_changed;
	uपूर्णांक32_t lane;

	req_drv_setting_changed = false;
	क्रम (adj_req_count = 0; adj_req_count < POST_LT_ADJ_REQ_LIMIT;
	adj_req_count++) अणु

		req_drv_setting_changed = false;

		क्रम (adj_req_समयr = 0;
			adj_req_समयr < POST_LT_ADJ_REQ_TIMEOUT;
			adj_req_समयr++) अणु

			काष्ठा link_training_settings req_settings;
			जोड़ lane_status dpcd_lane_status[LANE_COUNT_DP_MAX];
			जोड़ lane_align_status_updated
				dpcd_lane_status_updated;

			get_lane_status_and_drive_settings(
			link,
			lt_settings,
			dpcd_lane_status,
			&dpcd_lane_status_updated,
			&req_settings,
			DPRX);

			अगर (dpcd_lane_status_updated.bits.
					POST_LT_ADJ_REQ_IN_PROGRESS == 0)
				वापस true;

			अगर (!is_cr_करोne(lane_count, dpcd_lane_status))
				वापस false;

			अगर (!is_ch_eq_करोne(
				lane_count,
				dpcd_lane_status,
				&dpcd_lane_status_updated))
				वापस false;

			क्रम (lane = 0; lane < (uपूर्णांक32_t)(lane_count); lane++) अणु

				अगर (lt_settings->
				lane_settings[lane].VOLTAGE_SWING !=
				req_settings.lane_settings[lane].
				VOLTAGE_SWING ||
				lt_settings->lane_settings[lane].PRE_EMPHASIS !=
				req_settings.lane_settings[lane].PRE_EMPHASIS) अणु

					req_drv_setting_changed = true;
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (req_drv_setting_changed) अणु
				update_drive_settings(
					lt_settings, req_settings);

				dc_link_dp_set_drive_settings(link,
						lt_settings);
				अवरोध;
			पूर्ण

			msleep(1);
		पूर्ण

		अगर (!req_drv_setting_changed) अणु
			DC_LOG_WARNING("%s: Post Link Training Adjust Request Timed out\n",
				__func__);

			ASSERT(0);
			वापस true;
		पूर्ण
	पूर्ण
	DC_LOG_WARNING("%s: Post Link Training Adjust Request limit reached\n",
		__func__);

	ASSERT(0);
	वापस true;

पूर्ण

/* Only used क्रम channel equalization */
अटल uपूर्णांक32_t translate_training_aux_पढ़ो_पूर्णांकerval(uपूर्णांक32_t dpcd_aux_पढ़ो_पूर्णांकerval)
अणु
	अचिन्हित पूर्णांक aux_rd_पूर्णांकerval_us = 400;

	चयन (dpcd_aux_पढ़ो_पूर्णांकerval) अणु
	हाल 0x01:
		aux_rd_पूर्णांकerval_us = 4000;
		अवरोध;
	हाल 0x02:
		aux_rd_पूर्णांकerval_us = 8000;
		अवरोध;
	हाल 0x03:
		aux_rd_पूर्णांकerval_us = 12000;
		अवरोध;
	हाल 0x04:
		aux_rd_पूर्णांकerval_us = 16000;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस aux_rd_पूर्णांकerval_us;
पूर्ण

अटल क्रमागत link_training_result get_cr_failure(क्रमागत dc_lane_count ln_count,
					जोड़ lane_status *dpcd_lane_status)
अणु
	क्रमागत link_training_result result = LINK_TRAINING_SUCCESS;

	अगर (ln_count >= LANE_COUNT_ONE && !dpcd_lane_status[0].bits.CR_DONE_0)
		result = LINK_TRAINING_CR_FAIL_LANE0;
	अन्यथा अगर (ln_count >= LANE_COUNT_TWO && !dpcd_lane_status[1].bits.CR_DONE_0)
		result = LINK_TRAINING_CR_FAIL_LANE1;
	अन्यथा अगर (ln_count >= LANE_COUNT_FOUR && !dpcd_lane_status[2].bits.CR_DONE_0)
		result = LINK_TRAINING_CR_FAIL_LANE23;
	अन्यथा अगर (ln_count >= LANE_COUNT_FOUR && !dpcd_lane_status[3].bits.CR_DONE_0)
		result = LINK_TRAINING_CR_FAIL_LANE23;
	वापस result;
पूर्ण

अटल क्रमागत link_training_result perक्रमm_channel_equalization_sequence(
	काष्ठा dc_link *link,
	काष्ठा link_training_settings *lt_settings,
	uपूर्णांक32_t offset)
अणु
	काष्ठा link_training_settings req_settings;
	क्रमागत dc_dp_training_pattern tr_pattern;
	uपूर्णांक32_t retries_ch_eq;
	uपूर्णांक32_t रुको_समय_microsec;
	क्रमागत dc_lane_count lane_count = lt_settings->link_settings.lane_count;
	जोड़ lane_align_status_updated dpcd_lane_status_updated = अणु अणु0पूर्ण पूर्ण;
	जोड़ lane_status dpcd_lane_status[LANE_COUNT_DP_MAX] = अणु अणु अणु0पूर्ण पूर्ण पूर्ण;

	/* Note: also check that TPS4 is a supported feature*/

	tr_pattern = lt_settings->pattern_क्रम_eq;

	अगर (is_repeater(link, offset))
		tr_pattern = DP_TRAINING_PATTERN_SEQUENCE_4;

	dp_set_hw_training_pattern(link, tr_pattern, offset);

	क्रम (retries_ch_eq = 0; retries_ch_eq <= LINK_TRAINING_MAX_RETRY_COUNT;
		retries_ch_eq++) अणु

		dp_set_hw_lane_settings(link, lt_settings, offset);

		/* 2. update DPCD*/
		अगर (!retries_ch_eq)
			/* EPR #361076 - ग_लिखो as a 5-byte burst,
			 * but only क्रम the 1-st iteration
			 */

			dpcd_set_lt_pattern_and_lane_settings(
				link,
				lt_settings,
				tr_pattern, offset);
		अन्यथा
			dpcd_set_lane_settings(link, lt_settings, offset);

		/* 3. रुको क्रम receiver to lock-on*/
		रुको_समय_microsec = lt_settings->eq_pattern_समय;

		अगर (is_repeater(link, offset))
			रुको_समय_microsec =
					translate_training_aux_पढ़ो_पूर्णांकerval(
						link->dpcd_caps.lttpr_caps.aux_rd_पूर्णांकerval[offset - 1]);

		रुको_क्रम_training_aux_rd_पूर्णांकerval(
				link,
				रुको_समय_microsec);

		/* 4. Read lane status and requested
		 * drive settings as set by the sink*/

		get_lane_status_and_drive_settings(
			link,
			lt_settings,
			dpcd_lane_status,
			&dpcd_lane_status_updated,
			&req_settings,
			offset);

		/* 5. check CR करोne*/
		अगर (!is_cr_करोne(lane_count, dpcd_lane_status))
			वापस LINK_TRAINING_EQ_FAIL_CR;

		/* 6. check CHEQ करोne*/
		अगर (is_ch_eq_करोne(lane_count,
			dpcd_lane_status,
			&dpcd_lane_status_updated))
			वापस LINK_TRAINING_SUCCESS;

		/* 7. update VS/PE/PC2 in lt_settings*/
		update_drive_settings(lt_settings, req_settings);
	पूर्ण

	वापस LINK_TRAINING_EQ_FAIL_EQ;

पूर्ण
#घोषणा TRAINING_AUX_RD_INTERVAL 100 //us

अटल व्योम start_घड़ी_recovery_pattern_early(काष्ठा dc_link *link,
		काष्ठा link_training_settings *lt_settings,
		uपूर्णांक32_t offset)
अणु
	DC_LOG_HW_LINK_TRAINING("%s\n GPU sends TPS1. Wait 400us.\n",
			__func__);
	dp_set_hw_training_pattern(link, lt_settings->pattern_क्रम_cr, offset);
	dp_set_hw_lane_settings(link, lt_settings, offset);
	udelay(400);
पूर्ण

अटल क्रमागत link_training_result perक्रमm_घड़ी_recovery_sequence(
	काष्ठा dc_link *link,
	काष्ठा link_training_settings *lt_settings,
	uपूर्णांक32_t offset)
अणु
	uपूर्णांक32_t retries_cr;
	uपूर्णांक32_t retry_count;
	uपूर्णांक32_t रुको_समय_microsec;
	काष्ठा link_training_settings req_settings;
	क्रमागत dc_lane_count lane_count = lt_settings->link_settings.lane_count;
	जोड़ lane_status dpcd_lane_status[LANE_COUNT_DP_MAX];
	जोड़ lane_align_status_updated dpcd_lane_status_updated;

	retries_cr = 0;
	retry_count = 0;

	अगर (!link->ctx->dc->work_arounds.lt_early_cr_pattern)
		dp_set_hw_training_pattern(link, lt_settings->pattern_क्रम_cr, offset);

	/* najeeb - The synaptics MST hub can put the LT in
	* infinite loop by चयनing the VS
	*/
	/* between level 0 and level 1 continuously, here
	* we try क्रम CR lock क्रम LinkTrainingMaxCRRetry count*/
	जबतक ((retries_cr < LINK_TRAINING_MAX_RETRY_COUNT) &&
		(retry_count < LINK_TRAINING_MAX_CR_RETRY)) अणु

		स_रखो(&dpcd_lane_status, '\0', माप(dpcd_lane_status));
		स_रखो(&dpcd_lane_status_updated, '\0',
		माप(dpcd_lane_status_updated));

		/* 1. call HWSS to set lane settings*/
		dp_set_hw_lane_settings(
				link,
				lt_settings,
				offset);

		/* 2. update DPCD of the receiver*/
		अगर (!retry_count)
			/* EPR #361076 - ग_लिखो as a 5-byte burst,
			 * but only क्रम the 1-st iteration.*/
			dpcd_set_lt_pattern_and_lane_settings(
					link,
					lt_settings,
					lt_settings->pattern_क्रम_cr,
					offset);
		अन्यथा
			dpcd_set_lane_settings(
					link,
					lt_settings,
					offset);

		/* 3. रुको receiver to lock-on*/
		रुको_समय_microsec = lt_settings->cr_pattern_समय;

		अगर (link->lttpr_mode == LTTPR_MODE_NON_TRANSPARENT)
			रुको_समय_microsec = TRAINING_AUX_RD_INTERVAL;

		रुको_क्रम_training_aux_rd_पूर्णांकerval(
				link,
				रुको_समय_microsec);

		/* 4. Read lane status and requested drive
		* settings as set by the sink
		*/
		get_lane_status_and_drive_settings(
				link,
				lt_settings,
				dpcd_lane_status,
				&dpcd_lane_status_updated,
				&req_settings,
				offset);

		/* 5. check CR करोne*/
		अगर (is_cr_करोne(lane_count, dpcd_lane_status))
			वापस LINK_TRAINING_SUCCESS;

		/* 6. max VS reached*/
		अगर (is_max_vs_reached(lt_settings))
			अवरोध;

		/* 7. same lane settings*/
		/* Note: settings are the same क्रम all lanes,
		 * so comparing first lane is sufficient*/
		अगर ((lt_settings->lane_settings[0].VOLTAGE_SWING ==
			req_settings.lane_settings[0].VOLTAGE_SWING)
			&& (lt_settings->lane_settings[0].PRE_EMPHASIS ==
				req_settings.lane_settings[0].PRE_EMPHASIS))
			retries_cr++;
		अन्यथा
			retries_cr = 0;

		/* 8. update VS/PE/PC2 in lt_settings*/
		update_drive_settings(lt_settings, req_settings);

		retry_count++;
	पूर्ण

	अगर (retry_count >= LINK_TRAINING_MAX_CR_RETRY) अणु
		ASSERT(0);
		DC_LOG_ERROR("%s: Link Training Error, could not get CR after %d tries. Possibly voltage swing issue",
			__func__,
			LINK_TRAINING_MAX_CR_RETRY);

	पूर्ण

	वापस get_cr_failure(lane_count, dpcd_lane_status);
पूर्ण

अटल अंतरभूत क्रमागत link_training_result perक्रमm_link_training_पूर्णांक(
	काष्ठा dc_link *link,
	काष्ठा link_training_settings *lt_settings,
	क्रमागत link_training_result status)
अणु
	जोड़ lane_count_set lane_count_set = अणु अणु0पूर्ण पूर्ण;

	/* 4. मुख्यlink output idle pattern*/
	dp_set_hw_test_pattern(link, DP_TEST_PATTERN_VIDEO_MODE, शून्य, 0);

	/*
	 * 5. post training adjust अगर required
	 * If the upstream DPTX and करोwnstream DPRX both support TPS4,
	 * TPS4 must be used instead of POST_LT_ADJ_REQ.
	 */
	अगर (link->dpcd_caps.max_ln_count.bits.POST_LT_ADJ_REQ_SUPPORTED != 1 ||
			lt_settings->pattern_क्रम_eq == DP_TRAINING_PATTERN_SEQUENCE_4)
		वापस status;

	अगर (status == LINK_TRAINING_SUCCESS &&
		perक्रमm_post_lt_adj_req_sequence(link, lt_settings) == false)
		status = LINK_TRAINING_LQA_FAIL;

	lane_count_set.bits.LANE_COUNT_SET = lt_settings->link_settings.lane_count;
	lane_count_set.bits.ENHANCED_FRAMING = lt_settings->enhanced_framing;
	lane_count_set.bits.POST_LT_ADJ_REQ_GRANTED = 0;

	core_link_ग_लिखो_dpcd(
		link,
		DP_LANE_COUNT_SET,
		&lane_count_set.raw,
		माप(lane_count_set));

	वापस status;
पूर्ण

अटल क्रमागत link_training_result check_link_loss_status(
	काष्ठा dc_link *link,
	स्थिर काष्ठा link_training_settings *link_training_setting)
अणु
	क्रमागत link_training_result status = LINK_TRAINING_SUCCESS;
	जोड़ lane_status lane_status;
	uपूर्णांक8_t dpcd_buf[6] = अणु0पूर्ण;
	uपूर्णांक32_t lane;

	core_link_पढ़ो_dpcd(
			link,
			DP_SINK_COUNT,
			(uपूर्णांक8_t *)(dpcd_buf),
			माप(dpcd_buf));

	/*parse lane status*/
	क्रम (lane = 0; lane < link->cur_link_settings.lane_count; lane++) अणु
		/*
		 * check lanes status
		 */
		lane_status.raw = get_nibble_at_index(&dpcd_buf[2], lane);

		अगर (!lane_status.bits.CHANNEL_EQ_DONE_0 ||
			!lane_status.bits.CR_DONE_0 ||
			!lane_status.bits.SYMBOL_LOCKED_0) अणु
			/* अगर one of the channel equalization, घड़ी
			 * recovery or symbol lock is dropped
			 * consider it as (link has been
			 * dropped) dp sink status has changed
			 */
			status = LINK_TRAINING_LINK_LOSS;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम initialize_training_settings(
	 काष्ठा dc_link *link,
	स्थिर काष्ठा dc_link_settings *link_setting,
	स्थिर काष्ठा dc_link_training_overrides *overrides,
	काष्ठा link_training_settings *lt_settings)
अणु
	uपूर्णांक32_t lane;

	स_रखो(lt_settings, '\0', माप(काष्ठा link_training_settings));

	/* Initialize link settings */
	lt_settings->link_settings.use_link_rate_set = link_setting->use_link_rate_set;
	lt_settings->link_settings.link_rate_set = link_setting->link_rate_set;

	अगर (link->preferred_link_setting.link_rate != LINK_RATE_UNKNOWN)
		lt_settings->link_settings.link_rate = link->preferred_link_setting.link_rate;
	अन्यथा
		lt_settings->link_settings.link_rate = link_setting->link_rate;

	अगर (link->preferred_link_setting.lane_count != LANE_COUNT_UNKNOWN)
		lt_settings->link_settings.lane_count = link->preferred_link_setting.lane_count;
	अन्यथा
		lt_settings->link_settings.lane_count = link_setting->lane_count;

	/*@toकरो[vdevulap] move SS to LS, should not be handled by displaypath*/

	/* TODO hard coded to SS क्रम now
	 * lt_settings.link_settings.link_spपढ़ो =
	 * dal_display_path_is_ss_supported(
	 * path_mode->display_path) ?
	 * LINK_SPREAD_05_DOWNSPREAD_30KHZ :
	 * LINK_SPREAD_DISABLED;
	 */
	/* Initialize link spपढ़ो */
	अगर (link->dp_ss_off)
		lt_settings->link_settings.link_spपढ़ो = LINK_SPREAD_DISABLED;
	अन्यथा अगर (overrides->करोwnspपढ़ो != शून्य)
		lt_settings->link_settings.link_spपढ़ो
			= *overrides->करोwnspपढ़ो
			? LINK_SPREAD_05_DOWNSPREAD_30KHZ
			: LINK_SPREAD_DISABLED;
	अन्यथा
		lt_settings->link_settings.link_spपढ़ो = LINK_SPREAD_05_DOWNSPREAD_30KHZ;

	/* Initialize lane settings overrides */
	अगर (overrides->voltage_swing != शून्य)
		lt_settings->voltage_swing = overrides->voltage_swing;

	अगर (overrides->pre_emphasis != शून्य)
		lt_settings->pre_emphasis = overrides->pre_emphasis;

	अगर (overrides->post_cursor2 != शून्य)
		lt_settings->post_cursor2 = overrides->post_cursor2;

	/* Initialize lane settings (VS/PE/PC2) */
	क्रम (lane = 0; lane < LANE_COUNT_DP_MAX; lane++) अणु
		lt_settings->lane_settings[lane].VOLTAGE_SWING =
			lt_settings->voltage_swing != शून्य ?
			*lt_settings->voltage_swing :
			VOLTAGE_SWING_LEVEL0;
		lt_settings->lane_settings[lane].PRE_EMPHASIS =
			lt_settings->pre_emphasis != शून्य ?
			*lt_settings->pre_emphasis
			: PRE_EMPHASIS_DISABLED;
		lt_settings->lane_settings[lane].POST_CURSOR2 =
			lt_settings->post_cursor2 != शून्य ?
			*lt_settings->post_cursor2
			: POST_CURSOR2_DISABLED;
	पूर्ण

	/* Initialize training timings */
	अगर (overrides->cr_pattern_समय != शून्य)
		lt_settings->cr_pattern_समय = *overrides->cr_pattern_समय;
	अन्यथा
		lt_settings->cr_pattern_समय = get_cr_training_aux_rd_पूर्णांकerval(link, link_setting);

	अगर (overrides->eq_pattern_समय != शून्य)
		lt_settings->eq_pattern_समय = *overrides->eq_pattern_समय;
	अन्यथा
		lt_settings->eq_pattern_समय = get_eq_training_aux_rd_पूर्णांकerval(link, link_setting);

	अगर (overrides->pattern_क्रम_cr != शून्य)
		lt_settings->pattern_क्रम_cr = *overrides->pattern_क्रम_cr;
	अन्यथा
		lt_settings->pattern_क्रम_cr = decide_cr_training_pattern(link_setting);
	अगर (overrides->pattern_क्रम_eq != शून्य)
		lt_settings->pattern_क्रम_eq = *overrides->pattern_क्रम_eq;
	अन्यथा
		lt_settings->pattern_क्रम_eq = decide_eq_training_pattern(link, link_setting);

	अगर (overrides->enhanced_framing != शून्य)
		lt_settings->enhanced_framing = *overrides->enhanced_framing;
	अन्यथा
		lt_settings->enhanced_framing = 1;
पूर्ण

अटल uपूर्णांक8_t convert_to_count(uपूर्णांक8_t lttpr_repeater_count)
अणु
	चयन (lttpr_repeater_count) अणु
	हाल 0x80: // 1 lttpr repeater
		वापस 1;
	हाल 0x40: // 2 lttpr repeaters
		वापस 2;
	हाल 0x20: // 3 lttpr repeaters
		वापस 3;
	हाल 0x10: // 4 lttpr repeaters
		वापस 4;
	हाल 0x08: // 5 lttpr repeaters
		वापस 5;
	हाल 0x04: // 6 lttpr repeaters
		वापस 6;
	हाल 0x02: // 7 lttpr repeaters
		वापस 7;
	हाल 0x01: // 8 lttpr repeaters
		वापस 8;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0; // invalid value
पूर्ण

अटल व्योम configure_lttpr_mode_transparent(काष्ठा dc_link *link)
अणु
	uपूर्णांक8_t repeater_mode = DP_PHY_REPEATER_MODE_TRANSPARENT;

	core_link_ग_लिखो_dpcd(link,
			DP_PHY_REPEATER_MODE,
			(uपूर्णांक8_t *)&repeater_mode,
			माप(repeater_mode));
पूर्ण

अटल व्योम configure_lttpr_mode_non_transparent(काष्ठा dc_link *link)
अणु
	/* aux समयout is alपढ़ोy set to extended */
	/* RESET/SET lttpr mode to enable non transparent mode */
	uपूर्णांक8_t repeater_cnt;
	uपूर्णांक32_t aux_पूर्णांकerval_address;
	uपूर्णांक8_t repeater_id;
	क्रमागत dc_status result = DC_ERROR_UNEXPECTED;
	uपूर्णांक8_t repeater_mode = DP_PHY_REPEATER_MODE_TRANSPARENT;

	DC_LOG_HW_LINK_TRAINING("%s\n Set LTTPR to Transparent Mode\n", __func__);
	result = core_link_ग_लिखो_dpcd(link,
			DP_PHY_REPEATER_MODE,
			(uपूर्णांक8_t *)&repeater_mode,
			माप(repeater_mode));

	अगर (result == DC_OK) अणु
		link->dpcd_caps.lttpr_caps.mode = repeater_mode;
	पूर्ण

	अगर (link->lttpr_mode == LTTPR_MODE_NON_TRANSPARENT) अणु

		DC_LOG_HW_LINK_TRAINING("%s\n Set LTTPR to Non Transparent Mode\n", __func__);

		repeater_mode = DP_PHY_REPEATER_MODE_NON_TRANSPARENT;
		result = core_link_ग_लिखो_dpcd(link,
				DP_PHY_REPEATER_MODE,
				(uपूर्णांक8_t *)&repeater_mode,
				माप(repeater_mode));

		अगर (result == DC_OK) अणु
			link->dpcd_caps.lttpr_caps.mode = repeater_mode;
		पूर्ण

		repeater_cnt = convert_to_count(link->dpcd_caps.lttpr_caps.phy_repeater_cnt);
		क्रम (repeater_id = repeater_cnt; repeater_id > 0; repeater_id--) अणु
			aux_पूर्णांकerval_address = DP_TRAINING_AUX_RD_INTERVAL_PHY_REPEATER1 +
						((DP_REPEATER_CONFIGURATION_AND_STATUS_SIZE) * (repeater_id - 1));
			core_link_पढ़ो_dpcd(
				link,
				aux_पूर्णांकerval_address,
				(uपूर्णांक8_t *)&link->dpcd_caps.lttpr_caps.aux_rd_पूर्णांकerval[repeater_id - 1],
				माप(link->dpcd_caps.lttpr_caps.aux_rd_पूर्णांकerval[repeater_id - 1]));
			link->dpcd_caps.lttpr_caps.aux_rd_पूर्णांकerval[repeater_id - 1] &= 0x7F;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम repeater_training_करोne(काष्ठा dc_link *link, uपूर्णांक32_t offset)
अणु
	जोड़ dpcd_training_pattern dpcd_pattern = अणु अणु0पूर्ण पूर्ण;

	स्थिर uपूर्णांक32_t dpcd_base_lt_offset =
			DP_TRAINING_PATTERN_SET_PHY_REPEATER1 +
				((DP_REPEATER_CONFIGURATION_AND_STATUS_SIZE) * (offset - 1));
	/* Set training not in progress*/
	dpcd_pattern.v1_4.TRAINING_PATTERN_SET = DPCD_TRAINING_PATTERN_VIDEOIDLE;

	core_link_ग_लिखो_dpcd(
		link,
		dpcd_base_lt_offset,
		&dpcd_pattern.raw,
		1);

	DC_LOG_HW_LINK_TRAINING("%s\n LTTPR Id: %d 0x%X pattern = %x\n",
		__func__,
		offset,
		dpcd_base_lt_offset,
		dpcd_pattern.v1_4.TRAINING_PATTERN_SET);
पूर्ण

अटल व्योम prपूर्णांक_status_message(
	काष्ठा dc_link *link,
	स्थिर काष्ठा link_training_settings *lt_settings,
	क्रमागत link_training_result status)
अणु
	अक्षर *link_rate = "Unknown";
	अक्षर *lt_result = "Unknown";
	अक्षर *lt_spपढ़ो = "Disabled";

	चयन (lt_settings->link_settings.link_rate) अणु
	हाल LINK_RATE_LOW:
		link_rate = "RBR";
		अवरोध;
	हाल LINK_RATE_RATE_2:
		link_rate = "R2";
		अवरोध;
	हाल LINK_RATE_RATE_3:
		link_rate = "R3";
		अवरोध;
	हाल LINK_RATE_HIGH:
		link_rate = "HBR";
		अवरोध;
	हाल LINK_RATE_RBR2:
		link_rate = "RBR2";
		अवरोध;
	हाल LINK_RATE_RATE_6:
		link_rate = "R6";
		अवरोध;
	हाल LINK_RATE_HIGH2:
		link_rate = "HBR2";
		अवरोध;
	हाल LINK_RATE_HIGH3:
		link_rate = "HBR3";
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (status) अणु
	हाल LINK_TRAINING_SUCCESS:
		lt_result = "pass";
		अवरोध;
	हाल LINK_TRAINING_CR_FAIL_LANE0:
		lt_result = "CR failed lane0";
		अवरोध;
	हाल LINK_TRAINING_CR_FAIL_LANE1:
		lt_result = "CR failed lane1";
		अवरोध;
	हाल LINK_TRAINING_CR_FAIL_LANE23:
		lt_result = "CR failed lane23";
		अवरोध;
	हाल LINK_TRAINING_EQ_FAIL_CR:
		lt_result = "CR failed in EQ";
		अवरोध;
	हाल LINK_TRAINING_EQ_FAIL_EQ:
		lt_result = "EQ failed";
		अवरोध;
	हाल LINK_TRAINING_LQA_FAIL:
		lt_result = "LQA failed";
		अवरोध;
	हाल LINK_TRAINING_LINK_LOSS:
		lt_result = "Link loss";
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (lt_settings->link_settings.link_spपढ़ो) अणु
	हाल LINK_SPREAD_DISABLED:
		lt_spपढ़ो = "Disabled";
		अवरोध;
	हाल LINK_SPREAD_05_DOWNSPREAD_30KHZ:
		lt_spपढ़ो = "0.5% 30KHz";
		अवरोध;
	हाल LINK_SPREAD_05_DOWNSPREAD_33KHZ:
		lt_spपढ़ो = "0.5% 33KHz";
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Connectivity log: link training */
	CONN_MSG_LT(link, "%sx%d %s VS=%d, PE=%d, DS=%s",
				link_rate,
				lt_settings->link_settings.lane_count,
				lt_result,
				lt_settings->lane_settings[0].VOLTAGE_SWING,
				lt_settings->lane_settings[0].PRE_EMPHASIS,
				lt_spपढ़ो);
पूर्ण

व्योम dc_link_dp_set_drive_settings(
	काष्ठा dc_link *link,
	काष्ठा link_training_settings *lt_settings)
अणु
	/* program ASIC PHY settings*/
	dp_set_hw_lane_settings(link, lt_settings, DPRX);

	/* Notअगरy DP sink the PHY settings from source */
	dpcd_set_lane_settings(link, lt_settings, DPRX);
पूर्ण

bool dc_link_dp_perक्रमm_link_training_skip_aux(
	काष्ठा dc_link *link,
	स्थिर काष्ठा dc_link_settings *link_setting)
अणु
	काष्ठा link_training_settings lt_settings;

	initialize_training_settings(
			link,
			link_setting,
			&link->preferred_training_settings,
			&lt_settings);

	/* 1. Perक्रमm_घड़ी_recovery_sequence. */

	/* transmit training pattern क्रम घड़ी recovery */
	dp_set_hw_training_pattern(link, lt_settings.pattern_क्रम_cr, DPRX);

	/* call HWSS to set lane settings*/
	dp_set_hw_lane_settings(link, &lt_settings, DPRX);

	/* रुको receiver to lock-on*/
	रुको_क्रम_training_aux_rd_पूर्णांकerval(link, lt_settings.cr_pattern_समय);

	/* 2. Perक्रमm_channel_equalization_sequence. */

	/* transmit training pattern क्रम channel equalization. */
	dp_set_hw_training_pattern(link, lt_settings.pattern_क्रम_eq, DPRX);

	/* call HWSS to set lane settings*/
	dp_set_hw_lane_settings(link, &lt_settings, DPRX);

	/* रुको receiver to lock-on. */
	रुको_क्रम_training_aux_rd_पूर्णांकerval(link, lt_settings.eq_pattern_समय);

	/* 3. Perक्रमm_link_training_पूर्णांक. */

	/* Mainlink output idle pattern. */
	dp_set_hw_test_pattern(link, DP_TEST_PATTERN_VIDEO_MODE, शून्य, 0);

	prपूर्णांक_status_message(link, &lt_settings, LINK_TRAINING_SUCCESS);

	वापस true;
पूर्ण

क्रमागत link_training_result dc_link_dp_perक्रमm_link_training(
	काष्ठा dc_link *link,
	स्थिर काष्ठा dc_link_settings *link_setting,
	bool skip_video_pattern)
अणु
	क्रमागत link_training_result status = LINK_TRAINING_SUCCESS;
	काष्ठा link_training_settings lt_settings;
	जोड़ dpcd_training_pattern dpcd_pattern = अणु अणु 0 पूर्ण पूर्ण;

	bool fec_enable;
	uपूर्णांक8_t repeater_cnt;
	uपूर्णांक8_t repeater_id;

	initialize_training_settings(
			link,
			link_setting,
			&link->preferred_training_settings,
			&lt_settings);

	/* Configure lttpr mode */
	अगर (link->lttpr_mode == LTTPR_MODE_NON_TRANSPARENT)
		configure_lttpr_mode_non_transparent(link);
	अन्यथा अगर (link->lttpr_mode == LTTPR_MODE_TRANSPARENT)
		configure_lttpr_mode_transparent(link);

	अगर (link->ctx->dc->work_arounds.lt_early_cr_pattern)
		start_घड़ी_recovery_pattern_early(link, &lt_settings, DPRX);

	/* 1. set link rate, lane count and spपढ़ो. */
	dpcd_set_link_settings(link, &lt_settings);

	अगर (link->preferred_training_settings.fec_enable != शून्य)
		fec_enable = *link->preferred_training_settings.fec_enable;
	अन्यथा
		fec_enable = true;

	dp_set_fec_पढ़ोy(link, fec_enable);

	अगर (link->lttpr_mode == LTTPR_MODE_NON_TRANSPARENT) अणु

		/* 2. perक्रमm link training (set link training करोne
		 *  to false is करोne as well)
		 */
		repeater_cnt = convert_to_count(link->dpcd_caps.lttpr_caps.phy_repeater_cnt);

		क्रम (repeater_id = repeater_cnt; (repeater_id > 0 && status == LINK_TRAINING_SUCCESS);
				repeater_id--) अणु
			status = perक्रमm_घड़ी_recovery_sequence(link, &lt_settings, repeater_id);

			अगर (status != LINK_TRAINING_SUCCESS)
				अवरोध;

			status = perक्रमm_channel_equalization_sequence(link,
					&lt_settings,
					repeater_id);

			अगर (status != LINK_TRAINING_SUCCESS)
				अवरोध;

			repeater_training_करोne(link, repeater_id);
		पूर्ण
	पूर्ण

	अगर (status == LINK_TRAINING_SUCCESS) अणु
		status = perक्रमm_घड़ी_recovery_sequence(link, &lt_settings, DPRX);
	अगर (status == LINK_TRAINING_SUCCESS) अणु
		status = perक्रमm_channel_equalization_sequence(link,
					&lt_settings,
					DPRX);
		पूर्ण
	पूर्ण

	/* 3. set training not in progress*/
	dpcd_pattern.v1_4.TRAINING_PATTERN_SET = DPCD_TRAINING_PATTERN_VIDEOIDLE;
	dpcd_set_training_pattern(link, dpcd_pattern);
	अगर ((status == LINK_TRAINING_SUCCESS) || !skip_video_pattern) अणु
		status = perक्रमm_link_training_पूर्णांक(link,
				&lt_settings,
				status);
	पूर्ण

	/* delay 5ms after Main Link output idle pattern and then check
	 * DPCD 0202h.
	 */
	अगर (link->connector_संकेत != SIGNAL_TYPE_EDP && status == LINK_TRAINING_SUCCESS) अणु
		msleep(5);
		status = check_link_loss_status(link, &lt_settings);
	पूर्ण

	/* 6. prपूर्णांक status message*/
	prपूर्णांक_status_message(link, &lt_settings, status);

	अगर (status != LINK_TRAINING_SUCCESS)
		link->ctx->dc->debug_data.ltFailCount++;

	वापस status;
पूर्ण

अटल क्रमागत dp_panel_mode try_enable_assr(काष्ठा dc_stream_state *stream)
अणु
	काष्ठा dc_link *link = stream->link;
	क्रमागत dp_panel_mode panel_mode = dp_get_panel_mode(link);
#अगर_घोषित CONFIG_DRM_AMD_DC_HDCP
	काष्ठा cp_psp *cp_psp = &stream->ctx->cp_psp;
#पूर्ण_अगर

	/* ASSR must be supported on the panel */
	अगर (panel_mode == DP_PANEL_MODE_DEFAULT)
		वापस panel_mode;

	/* eDP or पूर्णांकernal DP only */
	अगर (link->connector_संकेत != SIGNAL_TYPE_EDP &&
		!(link->connector_संकेत == SIGNAL_TYPE_DISPLAY_PORT &&
		 link->is_पूर्णांकernal_display))
		वापस DP_PANEL_MODE_DEFAULT;

#अगर_घोषित CONFIG_DRM_AMD_DC_HDCP
	अगर (cp_psp && cp_psp->funcs.enable_assr) अणु
		अगर (!cp_psp->funcs.enable_assr(cp_psp->handle, link)) अणु
			/* since eDP implies ASSR on, change panel
			 * mode to disable ASSR
			 */
			panel_mode = DP_PANEL_MODE_DEFAULT;
		पूर्ण
	पूर्ण अन्यथा
		panel_mode = DP_PANEL_MODE_DEFAULT;

#अन्यथा
	/* turn off ASSR अगर the implementation is not compiled in */
	panel_mode = DP_PANEL_MODE_DEFAULT;
#पूर्ण_अगर
	वापस panel_mode;
पूर्ण

bool perक्रमm_link_training_with_retries(
	स्थिर काष्ठा dc_link_settings *link_setting,
	bool skip_video_pattern,
	पूर्णांक attempts,
	काष्ठा pipe_ctx *pipe_ctx,
	क्रमागत संकेत_type संकेत)
अणु
	uपूर्णांक8_t j;
	uपूर्णांक8_t delay_between_attempts = LINK_TRAINING_RETRY_DELAY;
	काष्ठा dc_stream_state *stream = pipe_ctx->stream;
	काष्ठा dc_link *link = stream->link;
	क्रमागत dp_panel_mode panel_mode;

	/* We need to करो this beक्रमe the link training to ensure the idle pattern in SST
	 * mode will be sent right after the link training
	 */
	link->link_enc->funcs->connect_dig_be_to_fe(link->link_enc,
							pipe_ctx->stream_res.stream_enc->id, true);

	क्रम (j = 0; j < attempts; ++j) अणु

		DC_LOG_HW_LINK_TRAINING("%s: Beginning link training attempt %u of %d\n",
			__func__, (अचिन्हित पूर्णांक)j + 1, attempts);

		dp_enable_link_phy(
			link,
			संकेत,
			pipe_ctx->घड़ी_source->id,
			link_setting);

		अगर (stream->sink_patches.dpघातerup_delay > 0) अणु
			पूर्णांक delay_dp_घातer_up_in_ms = stream->sink_patches.dpघातerup_delay;

			msleep(delay_dp_घातer_up_in_ms);
		पूर्ण

		panel_mode = try_enable_assr(stream);
		dp_set_panel_mode(link, panel_mode);
		DC_LOG_DETECTION_DP_CAPS("Link: %d ASSR enabled: %d\n",
			 link->link_index,
			 panel_mode != DP_PANEL_MODE_DEFAULT);

		अगर (link->aux_access_disabled) अणु
			dc_link_dp_perक्रमm_link_training_skip_aux(link, link_setting);
			वापस true;
		पूर्ण अन्यथा अणु
			क्रमागत link_training_result status = LINK_TRAINING_CR_FAIL_LANE0;

				status = dc_link_dp_perक्रमm_link_training(
										link,
										link_setting,
										skip_video_pattern);
			अगर (status == LINK_TRAINING_SUCCESS)
				वापस true;
		पूर्ण

		/* latest link training still fail, skip delay and keep PHY on
		 */
		अगर (j == (attempts - 1))
			अवरोध;

		DC_LOG_WARNING("%s: Link training attempt %u of %d failed\n",
			__func__, (अचिन्हित पूर्णांक)j + 1, attempts);

		dp_disable_link_phy(link, संकेत);

		msleep(delay_between_attempts);

		delay_between_attempts += LINK_TRAINING_RETRY_DELAY;
	पूर्ण

	वापस false;
पूर्ण

अटल क्रमागत घड़ी_source_id get_घड़ी_source_id(काष्ठा dc_link *link)
अणु
	क्रमागत घड़ी_source_id dp_cs_id = CLOCK_SOURCE_ID_UNDEFINED;
	काष्ठा घड़ी_source *dp_cs = link->dc->res_pool->dp_घड़ी_source;

	अगर (dp_cs != शून्य) अणु
		dp_cs_id = dp_cs->id;
	पूर्ण अन्यथा अणु
		/*
		 * dp घड़ी source is not initialized क्रम some reason.
		 * Should not happen, CLOCK_SOURCE_ID_EXTERNAL will be used
		 */
		ASSERT(dp_cs);
	पूर्ण

	वापस dp_cs_id;
पूर्ण

अटल व्योम set_dp_mst_mode(काष्ठा dc_link *link, bool mst_enable)
अणु
	अगर (mst_enable == false &&
		link->type == dc_connection_mst_branch) अणु
		/* Disable MST on link. Use only local sink. */
		dp_disable_link_phy_mst(link, link->connector_संकेत);

		link->type = dc_connection_single;
		link->local_sink = link->remote_sinks[0];
		link->local_sink->sink_संकेत = SIGNAL_TYPE_DISPLAY_PORT;
	पूर्ण अन्यथा अगर (mst_enable == true &&
			link->type == dc_connection_single &&
			link->remote_sinks[0] != शून्य) अणु
		/* Re-enable MST on link. */
		dp_disable_link_phy(link, link->connector_संकेत);
		dp_enable_mst_on_sink(link, true);

		link->type = dc_connection_mst_branch;
		link->local_sink->sink_संकेत = SIGNAL_TYPE_DISPLAY_PORT_MST;
	पूर्ण
पूर्ण

bool dc_link_dp_sync_lt_begin(काष्ठा dc_link *link)
अणु
	/* Begin Sync LT. During this समय,
	 * DPCD:600h must not be घातered करोwn.
	 */
	link->sync_lt_in_progress = true;

	/*Clear any existing preferred settings.*/
	स_रखो(&link->preferred_training_settings, 0,
		माप(काष्ठा dc_link_training_overrides));
	स_रखो(&link->preferred_link_setting, 0,
		माप(काष्ठा dc_link_settings));

	वापस true;
पूर्ण

क्रमागत link_training_result dc_link_dp_sync_lt_attempt(
    काष्ठा dc_link *link,
    काष्ठा dc_link_settings *link_settings,
    काष्ठा dc_link_training_overrides *lt_overrides)
अणु
	काष्ठा link_training_settings lt_settings;
	क्रमागत link_training_result lt_status = LINK_TRAINING_SUCCESS;
	क्रमागत dp_panel_mode panel_mode = DP_PANEL_MODE_DEFAULT;
	क्रमागत घड़ी_source_id dp_cs_id = CLOCK_SOURCE_ID_EXTERNAL;
	bool fec_enable = false;

	initialize_training_settings(
		link,
		link_settings,
		lt_overrides,
		&lt_settings);

	/* Setup MST Mode */
	अगर (lt_overrides->mst_enable)
		set_dp_mst_mode(link, *lt_overrides->mst_enable);

	/* Disable link */
	dp_disable_link_phy(link, link->connector_संकेत);

	/* Enable link */
	dp_cs_id = get_घड़ी_source_id(link);
	dp_enable_link_phy(link, link->connector_संकेत,
		dp_cs_id, link_settings);

	/* Set FEC enable */
	fec_enable = lt_overrides->fec_enable && *lt_overrides->fec_enable;
	dp_set_fec_पढ़ोy(link, fec_enable);

	अगर (lt_overrides->alternate_scrambler_reset) अणु
		अगर (*lt_overrides->alternate_scrambler_reset)
			panel_mode = DP_PANEL_MODE_EDP;
		अन्यथा
			panel_mode = DP_PANEL_MODE_DEFAULT;
	पूर्ण अन्यथा
		panel_mode = dp_get_panel_mode(link);

	dp_set_panel_mode(link, panel_mode);

	/* Attempt to train with given link training settings */
	अगर (link->ctx->dc->work_arounds.lt_early_cr_pattern)
		start_घड़ी_recovery_pattern_early(link, &lt_settings, DPRX);

	/* Set link rate, lane count and spपढ़ो. */
	dpcd_set_link_settings(link, &lt_settings);

	/* 2. perक्रमm link training (set link training करोne
	 *  to false is करोne as well)
	 */
	lt_status = perक्रमm_घड़ी_recovery_sequence(link, &lt_settings, DPRX);
	अगर (lt_status == LINK_TRAINING_SUCCESS) अणु
		lt_status = perक्रमm_channel_equalization_sequence(link,
						&lt_settings,
						DPRX);
	पूर्ण

	/* 3. Sync LT must skip TRAINING_PATTERN_SET:0 (video pattern)*/
	/* 4. prपूर्णांक status message*/
	prपूर्णांक_status_message(link, &lt_settings, lt_status);

	वापस lt_status;
पूर्ण

bool dc_link_dp_sync_lt_end(काष्ठा dc_link *link, bool link_करोwn)
अणु
	/* If input parameter is set, shut करोwn phy.
	 * Still shouldn't turn off dp_receiver (DPCD:600h)
	 */
	अगर (link_करोwn == true) अणु
		dp_disable_link_phy(link, link->connector_संकेत);
		dp_set_fec_पढ़ोy(link, false);
	पूर्ण

	link->sync_lt_in_progress = false;
	वापस true;
पूर्ण

अटल काष्ठा dc_link_settings get_max_link_cap(काष्ठा dc_link *link)
अणु
	काष्ठा dc_link_settings max_link_cap = अणु0पूर्ण;

	/* get max link encoder capability */
	link->link_enc->funcs->get_max_link_cap(link->link_enc, &max_link_cap);

	/* Lower link settings based on sink's link cap */
	अगर (link->reported_link_cap.lane_count < max_link_cap.lane_count)
		max_link_cap.lane_count =
				link->reported_link_cap.lane_count;
	अगर (link->reported_link_cap.link_rate < max_link_cap.link_rate)
		max_link_cap.link_rate =
				link->reported_link_cap.link_rate;
	अगर (link->reported_link_cap.link_spपढ़ो <
			max_link_cap.link_spपढ़ो)
		max_link_cap.link_spपढ़ो =
				link->reported_link_cap.link_spपढ़ो;
	/*
	 * account क्रम lttpr repeaters cap
	 * notes: repeaters करो not snoop in the DPRX Capabilities addresses (3.6.3).
	 */
	अगर (link->lttpr_mode == LTTPR_MODE_NON_TRANSPARENT) अणु
		अगर (link->dpcd_caps.lttpr_caps.max_lane_count < max_link_cap.lane_count)
			max_link_cap.lane_count = link->dpcd_caps.lttpr_caps.max_lane_count;

		अगर (link->dpcd_caps.lttpr_caps.max_link_rate < max_link_cap.link_rate)
			max_link_cap.link_rate = link->dpcd_caps.lttpr_caps.max_link_rate;

		DC_LOG_HW_LINK_TRAINING("%s\n Training with LTTPR,  max_lane count %d max_link rate %d \n",
						__func__,
						max_link_cap.lane_count,
						max_link_cap.link_rate);
	पूर्ण
	वापस max_link_cap;
पूर्ण

क्रमागत dc_status पढ़ो_hpd_rx_irq_data(
	काष्ठा dc_link *link,
	जोड़ hpd_irq_data *irq_data)
अणु
	अटल क्रमागत dc_status retval;

	/* The HW पढ़ोs 16 bytes from 200h on HPD,
	 * but अगर we get an AUX_DEFER, the HW cannot retry
	 * and this causes the CTS tests 4.3.2.1 - 3.2.4 to
	 * fail, so we now explicitly पढ़ो 6 bytes which is
	 * the req from the above mentioned test हालs.
	 *
	 * For DP 1.4 we need to पढ़ो those from 2002h range.
	 */
	अगर (link->dpcd_caps.dpcd_rev.raw < DPCD_REV_14)
		retval = core_link_पढ़ो_dpcd(
			link,
			DP_SINK_COUNT,
			irq_data->raw,
			माप(जोड़ hpd_irq_data));
	अन्यथा अणु
		/* Read 14 bytes in a single पढ़ो and then copy only the required fields.
		 * This is more efficient than करोing it in two separate AUX पढ़ोs. */

		uपूर्णांक8_t पंचांगp[DP_SINK_STATUS_ESI - DP_SINK_COUNT_ESI + 1];

		retval = core_link_पढ़ो_dpcd(
			link,
			DP_SINK_COUNT_ESI,
			पंचांगp,
			माप(पंचांगp));

		अगर (retval != DC_OK)
			वापस retval;

		irq_data->bytes.sink_cnt.raw = पंचांगp[DP_SINK_COUNT_ESI - DP_SINK_COUNT_ESI];
		irq_data->bytes.device_service_irq.raw = पंचांगp[DP_DEVICE_SERVICE_IRQ_VECTOR_ESI0 - DP_SINK_COUNT_ESI];
		irq_data->bytes.lane01_status.raw = पंचांगp[DP_LANE0_1_STATUS_ESI - DP_SINK_COUNT_ESI];
		irq_data->bytes.lane23_status.raw = पंचांगp[DP_LANE2_3_STATUS_ESI - DP_SINK_COUNT_ESI];
		irq_data->bytes.lane_status_updated.raw = पंचांगp[DP_LANE_ALIGN_STATUS_UPDATED_ESI - DP_SINK_COUNT_ESI];
		irq_data->bytes.sink_status.raw = पंचांगp[DP_SINK_STATUS_ESI - DP_SINK_COUNT_ESI];
	पूर्ण

	वापस retval;
पूर्ण

अटल bool hpd_rx_irq_check_link_loss_status(
	काष्ठा dc_link *link,
	जोड़ hpd_irq_data *hpd_irq_dpcd_data)
अणु
	uपूर्णांक8_t irq_reg_rx_घातer_state = 0;
	क्रमागत dc_status dpcd_result = DC_ERROR_UNEXPECTED;
	जोड़ lane_status lane_status;
	uपूर्णांक32_t lane;
	bool sink_status_changed;
	bool वापस_code;

	sink_status_changed = false;
	वापस_code = false;

	अगर (link->cur_link_settings.lane_count == 0)
		वापस वापस_code;

	/*1. Check that Link Status changed, beक्रमe re-training.*/

	/*parse lane status*/
	क्रम (lane = 0; lane < link->cur_link_settings.lane_count; lane++) अणु
		/* check status of lanes 0,1
		 * changed DpcdAddress_Lane01Status (0x202)
		 */
		lane_status.raw = get_nibble_at_index(
			&hpd_irq_dpcd_data->bytes.lane01_status.raw,
			lane);

		अगर (!lane_status.bits.CHANNEL_EQ_DONE_0 ||
			!lane_status.bits.CR_DONE_0 ||
			!lane_status.bits.SYMBOL_LOCKED_0) अणु
			/* अगर one of the channel equalization, घड़ी
			 * recovery or symbol lock is dropped
			 * consider it as (link has been
			 * dropped) dp sink status has changed
			 */
			sink_status_changed = true;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Check पूर्णांकerlane align.*/
	अगर (sink_status_changed ||
		!hpd_irq_dpcd_data->bytes.lane_status_updated.bits.INTERLANE_ALIGN_DONE) अणु

		DC_LOG_HW_HPD_IRQ("%s: Link Status changed.\n", __func__);

		वापस_code = true;

		/*2. Check that we can handle पूर्णांकerrupt: Not in FS DOS,
		 *  Not in "Display Timeout" state, Link is trained.
		 */
		dpcd_result = core_link_पढ़ो_dpcd(link,
			DP_SET_POWER,
			&irq_reg_rx_घातer_state,
			माप(irq_reg_rx_घातer_state));

		अगर (dpcd_result != DC_OK) अणु
			DC_LOG_HW_HPD_IRQ("%s: DPCD read failed to obtain power state.\n",
				__func__);
		पूर्ण अन्यथा अणु
			अगर (irq_reg_rx_घातer_state != DP_SET_POWER_D0)
				वापस_code = false;
		पूर्ण
	पूर्ण

	वापस वापस_code;
पूर्ण

bool dp_verअगरy_link_cap(
	काष्ठा dc_link *link,
	काष्ठा dc_link_settings *known_limit_link_setting,
	पूर्णांक *fail_count)
अणु
	काष्ठा dc_link_settings max_link_cap = अणु0पूर्ण;
	काष्ठा dc_link_settings cur_link_setting = अणु0पूर्ण;
	काष्ठा dc_link_settings *cur = &cur_link_setting;
	काष्ठा dc_link_settings initial_link_settings = अणु0पूर्ण;
	bool success;
	bool skip_link_training;
	bool skip_video_pattern;
	क्रमागत घड़ी_source_id dp_cs_id = CLOCK_SOURCE_ID_EXTERNAL;
	क्रमागत link_training_result status;
	जोड़ hpd_irq_data irq_data;

	अगर (link->dc->debug.skip_detection_link_training) अणु
		link->verअगरied_link_cap = *known_limit_link_setting;
		वापस true;
	पूर्ण

	स_रखो(&irq_data, 0, माप(irq_data));
	success = false;
	skip_link_training = false;

	max_link_cap = get_max_link_cap(link);

	/* Grant extended समयout request */
	अगर ((link->lttpr_mode == LTTPR_MODE_NON_TRANSPARENT) && (link->dpcd_caps.lttpr_caps.max_ext_समयout > 0)) अणु
		uपूर्णांक8_t grant = link->dpcd_caps.lttpr_caps.max_ext_समयout & 0x80;

		core_link_ग_लिखो_dpcd(link, DP_PHY_REPEATER_EXTENDED_WAIT_TIMEOUT, &grant, माप(grant));
	पूर्ण

	/* TODO implement override and monitor patch later */

	/* try to train the link from high to low to
	 * find the physical link capability
	 */
	/* disable PHY करोne possible by BIOS, will be करोne by driver itself */
	dp_disable_link_phy(link, link->connector_संकेत);

	dp_cs_id = get_घड़ी_source_id(link);

	/* link training starts with the maximum common settings
	 * supported by both sink and ASIC.
	 */
	initial_link_settings = get_common_supported_link_settings(
			*known_limit_link_setting,
			max_link_cap);
	cur_link_setting = initial_link_settings;

	/* Temporary Renoir-specअगरic workaround क्रम SWDEV-215184;
	 * PHY will someबार be in bad state on hotplugging display from certain USB-C करोngle,
	 * so add extra cycle of enabling and disabling the PHY beक्रमe first link training.
	 */
	अगर (link->link_enc->features.flags.bits.DP_IS_USB_C &&
			link->dc->debug.usbc_combo_phy_reset_wa) अणु
		dp_enable_link_phy(link, link->connector_संकेत, dp_cs_id, cur);
		dp_disable_link_phy(link, link->connector_संकेत);
	पूर्ण

	करो अणु
		skip_video_pattern = true;

		अगर (cur->link_rate == LINK_RATE_LOW)
			skip_video_pattern = false;

		dp_enable_link_phy(
				link,
				link->connector_संकेत,
				dp_cs_id,
				cur);


		अगर (skip_link_training)
			success = true;
		अन्यथा अणु
			status = dc_link_dp_perक्रमm_link_training(
							link,
							cur,
							skip_video_pattern);
			अगर (status == LINK_TRAINING_SUCCESS)
				success = true;
			अन्यथा
				(*fail_count)++;
		पूर्ण

		अगर (success) अणु
			link->verअगरied_link_cap = *cur;
			udelay(1000);
			अगर (पढ़ो_hpd_rx_irq_data(link, &irq_data) == DC_OK)
				अगर (hpd_rx_irq_check_link_loss_status(
						link,
						&irq_data))
					(*fail_count)++;
		पूर्ण
		/* always disable the link beक्रमe trying another
		 * setting or beक्रमe वापसing we'll enable it later
		 * based on the actual mode we're driving
		 */
		dp_disable_link_phy(link, link->connector_संकेत);
	पूर्ण जबतक (!success && decide_fallback_link_setting(
			initial_link_settings, cur, status));

	/* Link Training failed क्रम all Link Settings
	 *  (Lane Count is still unknown)
	 */
	अगर (!success) अणु
		/* If all LT fails क्रम all settings,
		 * set verअगरied = failed safe (1 lane low)
		 */
		link->verअगरied_link_cap.lane_count = LANE_COUNT_ONE;
		link->verअगरied_link_cap.link_rate = LINK_RATE_LOW;

		link->verअगरied_link_cap.link_spपढ़ो =
		LINK_SPREAD_DISABLED;
	पूर्ण


	वापस success;
पूर्ण

bool dp_verअगरy_link_cap_with_retries(
	काष्ठा dc_link *link,
	काष्ठा dc_link_settings *known_limit_link_setting,
	पूर्णांक attempts)
अणु
	uपूर्णांक8_t i = 0;
	bool success = false;

	क्रम (i = 0; i < attempts; i++) अणु
		पूर्णांक fail_count = 0;
		क्रमागत dc_connection_type type = dc_connection_none;

		स_रखो(&link->verअगरied_link_cap, 0,
				माप(काष्ठा dc_link_settings));
		अगर (!dc_link_detect_sink(link, &type) || type == dc_connection_none) अणु
			link->verअगरied_link_cap.lane_count = LANE_COUNT_ONE;
			link->verअगरied_link_cap.link_rate = LINK_RATE_LOW;
			link->verअगरied_link_cap.link_spपढ़ो = LINK_SPREAD_DISABLED;
			अवरोध;
		पूर्ण अन्यथा अगर (dp_verअगरy_link_cap(link,
				&link->reported_link_cap,
				&fail_count) && fail_count == 0) अणु
			success = true;
			अवरोध;
		पूर्ण
		msleep(10);
	पूर्ण
	वापस success;
पूर्ण

bool dp_verअगरy_mst_link_cap(
	काष्ठा dc_link *link)
अणु
	काष्ठा dc_link_settings max_link_cap = अणु0पूर्ण;

	max_link_cap = get_max_link_cap(link);
	link->verअगरied_link_cap = get_common_supported_link_settings(
		link->reported_link_cap,
		max_link_cap);

	वापस true;
पूर्ण

अटल काष्ठा dc_link_settings get_common_supported_link_settings(
		काष्ठा dc_link_settings link_setting_a,
		काष्ठा dc_link_settings link_setting_b)
अणु
	काष्ठा dc_link_settings link_settings = अणु0पूर्ण;

	link_settings.lane_count =
		(link_setting_a.lane_count <=
			link_setting_b.lane_count) ?
			link_setting_a.lane_count :
			link_setting_b.lane_count;
	link_settings.link_rate =
		(link_setting_a.link_rate <=
			link_setting_b.link_rate) ?
			link_setting_a.link_rate :
			link_setting_b.link_rate;
	link_settings.link_spपढ़ो = LINK_SPREAD_DISABLED;

	/* in DP compliance test, DPR-120 may have
	 * a अक्रमom value in its MAX_LINK_BW dpcd field.
	 * We map it to the maximum supported link rate that
	 * is smaller than MAX_LINK_BW in this हाल.
	 */
	अगर (link_settings.link_rate > LINK_RATE_HIGH3) अणु
		link_settings.link_rate = LINK_RATE_HIGH3;
	पूर्ण अन्यथा अगर (link_settings.link_rate < LINK_RATE_HIGH3
			&& link_settings.link_rate > LINK_RATE_HIGH2) अणु
		link_settings.link_rate = LINK_RATE_HIGH2;
	पूर्ण अन्यथा अगर (link_settings.link_rate < LINK_RATE_HIGH2
			&& link_settings.link_rate > LINK_RATE_HIGH) अणु
		link_settings.link_rate = LINK_RATE_HIGH;
	पूर्ण अन्यथा अगर (link_settings.link_rate < LINK_RATE_HIGH
			&& link_settings.link_rate > LINK_RATE_LOW) अणु
		link_settings.link_rate = LINK_RATE_LOW;
	पूर्ण अन्यथा अगर (link_settings.link_rate < LINK_RATE_LOW) अणु
		link_settings.link_rate = LINK_RATE_UNKNOWN;
	पूर्ण

	वापस link_settings;
पूर्ण

अटल अंतरभूत bool reached_minimum_lane_count(क्रमागत dc_lane_count lane_count)
अणु
	वापस lane_count <= LANE_COUNT_ONE;
पूर्ण

अटल अंतरभूत bool reached_minimum_link_rate(क्रमागत dc_link_rate link_rate)
अणु
	वापस link_rate <= LINK_RATE_LOW;
पूर्ण

अटल क्रमागत dc_lane_count reduce_lane_count(क्रमागत dc_lane_count lane_count)
अणु
	चयन (lane_count) अणु
	हाल LANE_COUNT_FOUR:
		वापस LANE_COUNT_TWO;
	हाल LANE_COUNT_TWO:
		वापस LANE_COUNT_ONE;
	हाल LANE_COUNT_ONE:
		वापस LANE_COUNT_UNKNOWN;
	शेष:
		वापस LANE_COUNT_UNKNOWN;
	पूर्ण
पूर्ण

अटल क्रमागत dc_link_rate reduce_link_rate(क्रमागत dc_link_rate link_rate)
अणु
	चयन (link_rate) अणु
	हाल LINK_RATE_HIGH3:
		वापस LINK_RATE_HIGH2;
	हाल LINK_RATE_HIGH2:
		वापस LINK_RATE_HIGH;
	हाल LINK_RATE_HIGH:
		वापस LINK_RATE_LOW;
	हाल LINK_RATE_LOW:
		वापस LINK_RATE_UNKNOWN;
	शेष:
		वापस LINK_RATE_UNKNOWN;
	पूर्ण
पूर्ण

अटल क्रमागत dc_lane_count increase_lane_count(क्रमागत dc_lane_count lane_count)
अणु
	चयन (lane_count) अणु
	हाल LANE_COUNT_ONE:
		वापस LANE_COUNT_TWO;
	हाल LANE_COUNT_TWO:
		वापस LANE_COUNT_FOUR;
	शेष:
		वापस LANE_COUNT_UNKNOWN;
	पूर्ण
पूर्ण

अटल क्रमागत dc_link_rate increase_link_rate(क्रमागत dc_link_rate link_rate)
अणु
	चयन (link_rate) अणु
	हाल LINK_RATE_LOW:
		वापस LINK_RATE_HIGH;
	हाल LINK_RATE_HIGH:
		वापस LINK_RATE_HIGH2;
	हाल LINK_RATE_HIGH2:
		वापस LINK_RATE_HIGH3;
	शेष:
		वापस LINK_RATE_UNKNOWN;
	पूर्ण
पूर्ण

/*
 * function: set link rate and lane count fallback based
 * on current link setting and last link training result
 * वापस value:
 *			true - link setting could be set
 *			false - has reached minimum setting
 *					and no further fallback could be करोne
 */
अटल bool decide_fallback_link_setting(
		काष्ठा dc_link_settings initial_link_settings,
		काष्ठा dc_link_settings *current_link_setting,
		क्रमागत link_training_result training_result)
अणु
	अगर (!current_link_setting)
		वापस false;

	चयन (training_result) अणु
	हाल LINK_TRAINING_CR_FAIL_LANE0:
	हाल LINK_TRAINING_CR_FAIL_LANE1:
	हाल LINK_TRAINING_CR_FAIL_LANE23:
	हाल LINK_TRAINING_LQA_FAIL:
	अणु
		अगर (!reached_minimum_link_rate
				(current_link_setting->link_rate)) अणु
			current_link_setting->link_rate =
				reduce_link_rate(
					current_link_setting->link_rate);
		पूर्ण अन्यथा अगर (!reached_minimum_lane_count
				(current_link_setting->lane_count)) अणु
			current_link_setting->link_rate =
				initial_link_settings.link_rate;
			अगर (training_result == LINK_TRAINING_CR_FAIL_LANE0)
				वापस false;
			अन्यथा अगर (training_result == LINK_TRAINING_CR_FAIL_LANE1)
				current_link_setting->lane_count =
						LANE_COUNT_ONE;
			अन्यथा अगर (training_result ==
					LINK_TRAINING_CR_FAIL_LANE23)
				current_link_setting->lane_count =
						LANE_COUNT_TWO;
			अन्यथा
				current_link_setting->lane_count =
					reduce_lane_count(
					current_link_setting->lane_count);
		पूर्ण अन्यथा अणु
			वापस false;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल LINK_TRAINING_EQ_FAIL_EQ:
	अणु
		अगर (!reached_minimum_lane_count
				(current_link_setting->lane_count)) अणु
			current_link_setting->lane_count =
				reduce_lane_count(
					current_link_setting->lane_count);
		पूर्ण अन्यथा अगर (!reached_minimum_link_rate
				(current_link_setting->link_rate)) अणु
			current_link_setting->link_rate =
				reduce_link_rate(
					current_link_setting->link_rate);
		पूर्ण अन्यथा अणु
			वापस false;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल LINK_TRAINING_EQ_FAIL_CR:
	अणु
		अगर (!reached_minimum_link_rate
				(current_link_setting->link_rate)) अणु
			current_link_setting->link_rate =
				reduce_link_rate(
					current_link_setting->link_rate);
		पूर्ण अन्यथा अणु
			वापस false;
		पूर्ण
		अवरोध;
	पूर्ण
	शेष:
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

bool dp_validate_mode_timing(
	काष्ठा dc_link *link,
	स्थिर काष्ठा dc_crtc_timing *timing)
अणु
	uपूर्णांक32_t req_bw;
	uपूर्णांक32_t max_bw;

	स्थिर काष्ठा dc_link_settings *link_setting;

	/*always DP fail safe mode*/
	अगर ((timing->pix_clk_100hz / 10) == (uपूर्णांक32_t) 25175 &&
		timing->h_addressable == (uपूर्णांक32_t) 640 &&
		timing->v_addressable == (uपूर्णांक32_t) 480)
		वापस true;

	link_setting = dc_link_get_link_cap(link);

	/* TODO: DYNAMIC_VALIDATION needs to be implemented */
	/*अगर (flags.DYNAMIC_VALIDATION == 1 &&
		link->verअगरied_link_cap.lane_count != LANE_COUNT_UNKNOWN)
		link_setting = &link->verअगरied_link_cap;
	*/

	req_bw = dc_bandwidth_in_kbps_from_timing(timing);
	max_bw = dc_link_bandwidth_kbps(link, link_setting);

	अगर (req_bw <= max_bw) अणु
		/* remember the biggest mode here, during
		 * initial link training (to get
		 * verअगरied_link_cap), LS sends event about
		 * cannot train at reported cap to upper
		 * layer and upper layer will re-क्रमागतerate modes.
		 * this is not necessary अगर the lower
		 * verअगरied_link_cap is enough to drive
		 * all the modes */

		/* TODO: DYNAMIC_VALIDATION needs to be implemented */
		/* अगर (flags.DYNAMIC_VALIDATION == 1)
			dpsst->max_req_bw_क्रम_verअगरied_linkcap = dal_max(
				dpsst->max_req_bw_क्रम_verअगरied_linkcap, req_bw); */
		वापस true;
	पूर्ण अन्यथा
		वापस false;
पूर्ण

अटल bool decide_dp_link_settings(काष्ठा dc_link *link, काष्ठा dc_link_settings *link_setting, uपूर्णांक32_t req_bw)
अणु
	काष्ठा dc_link_settings initial_link_setting = अणु
		LANE_COUNT_ONE, LINK_RATE_LOW, LINK_SPREAD_DISABLED, false, 0पूर्ण;
	काष्ठा dc_link_settings current_link_setting =
			initial_link_setting;
	uपूर्णांक32_t link_bw;

	अगर (req_bw > dc_link_bandwidth_kbps(link, &link->verअगरied_link_cap))
		वापस false;

	/* search क्रम the minimum link setting that:
	 * 1. is supported according to the link training result
	 * 2. could support the b/w requested by the timing
	 */
	जबतक (current_link_setting.link_rate <=
			link->verअगरied_link_cap.link_rate) अणु
		link_bw = dc_link_bandwidth_kbps(
				link,
				&current_link_setting);
		अगर (req_bw <= link_bw) अणु
			*link_setting = current_link_setting;
			वापस true;
		पूर्ण

		अगर (current_link_setting.lane_count <
				link->verअगरied_link_cap.lane_count) अणु
			current_link_setting.lane_count =
					increase_lane_count(
							current_link_setting.lane_count);
		पूर्ण अन्यथा अणु
			current_link_setting.link_rate =
					increase_link_rate(
							current_link_setting.link_rate);
			current_link_setting.lane_count =
					initial_link_setting.lane_count;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

bool decide_edp_link_settings(काष्ठा dc_link *link, काष्ठा dc_link_settings *link_setting, uपूर्णांक32_t req_bw)
अणु
	काष्ठा dc_link_settings initial_link_setting;
	काष्ठा dc_link_settings current_link_setting;
	uपूर्णांक32_t link_bw;

	अगर (link->dpcd_caps.dpcd_rev.raw < DPCD_REV_14 ||
			link->dpcd_caps.edp_supported_link_rates_count == 0) अणु
		*link_setting = link->verअगरied_link_cap;
		वापस true;
	पूर्ण

	स_रखो(&initial_link_setting, 0, माप(initial_link_setting));
	initial_link_setting.lane_count = LANE_COUNT_ONE;
	initial_link_setting.link_rate = link->dpcd_caps.edp_supported_link_rates[0];
	initial_link_setting.link_spपढ़ो = LINK_SPREAD_DISABLED;
	initial_link_setting.use_link_rate_set = true;
	initial_link_setting.link_rate_set = 0;
	current_link_setting = initial_link_setting;

	/* search क्रम the minimum link setting that:
	 * 1. is supported according to the link training result
	 * 2. could support the b/w requested by the timing
	 */
	जबतक (current_link_setting.link_rate <=
			link->verअगरied_link_cap.link_rate) अणु
		link_bw = dc_link_bandwidth_kbps(
				link,
				&current_link_setting);
		अगर (req_bw <= link_bw) अणु
			*link_setting = current_link_setting;
			वापस true;
		पूर्ण

		अगर (current_link_setting.lane_count <
				link->verअगरied_link_cap.lane_count) अणु
			current_link_setting.lane_count =
					increase_lane_count(
							current_link_setting.lane_count);
		पूर्ण अन्यथा अणु
			अगर (current_link_setting.link_rate_set < link->dpcd_caps.edp_supported_link_rates_count) अणु
				current_link_setting.link_rate_set++;
				current_link_setting.link_rate =
					link->dpcd_caps.edp_supported_link_rates[current_link_setting.link_rate_set];
				current_link_setting.lane_count =
									initial_link_setting.lane_count;
			पूर्ण अन्यथा
				अवरोध;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल bool decide_mst_link_settings(स्थिर काष्ठा dc_link *link, काष्ठा dc_link_settings *link_setting)
अणु
	*link_setting = link->verअगरied_link_cap;
	वापस true;
पूर्ण

व्योम decide_link_settings(काष्ठा dc_stream_state *stream,
	काष्ठा dc_link_settings *link_setting)
अणु
	काष्ठा dc_link *link;
	uपूर्णांक32_t req_bw;

	req_bw = dc_bandwidth_in_kbps_from_timing(&stream->timing);

	link = stream->link;

	/* अगर preferred is specअगरied through AMDDP, use it, अगर it's enough
	 * to drive the mode
	 */
	अगर (link->preferred_link_setting.lane_count !=
			LANE_COUNT_UNKNOWN &&
			link->preferred_link_setting.link_rate !=
					LINK_RATE_UNKNOWN) अणु
		*link_setting =  link->preferred_link_setting;
		वापस;
	पूर्ण

	/* MST करोesn't perक्रमm link training क्रम now
	 * TODO: add MST specअगरic link training routine
	 */
	अगर (stream->संकेत == SIGNAL_TYPE_DISPLAY_PORT_MST) अणु
		अगर (decide_mst_link_settings(link, link_setting))
			वापस;
	पूर्ण अन्यथा अगर (link->connector_संकेत == SIGNAL_TYPE_EDP) अणु
		अगर (decide_edp_link_settings(link, link_setting, req_bw))
			वापस;
	पूर्ण अन्यथा अगर (decide_dp_link_settings(link, link_setting, req_bw))
		वापस;

	BREAK_TO_DEBUGGER();
	ASSERT(link->verअगरied_link_cap.lane_count != LANE_COUNT_UNKNOWN);

	*link_setting = link->verअगरied_link_cap;
पूर्ण

/*************************Short Pulse IRQ***************************/
अटल bool allow_hpd_rx_irq(स्थिर काष्ठा dc_link *link)
अणु
	/*
	 * Don't handle RX IRQ unless one of following is met:
	 * 1) The link is established (cur_link_settings != unknown)
	 * 2) We kicked off MST detection
	 * 3) We know we're dealing with an active करोngle
	 */

	अगर ((link->cur_link_settings.lane_count != LANE_COUNT_UNKNOWN) ||
		(link->type == dc_connection_mst_branch) ||
		is_dp_active_करोngle(link))
		वापस true;

	वापस false;
पूर्ण

अटल bool handle_hpd_irq_psr_sink(काष्ठा dc_link *link)
अणु
	जोड़ dpcd_psr_configuration psr_configuration;

	अगर (!link->psr_settings.psr_feature_enabled)
		वापस false;

	dm_helpers_dp_पढ़ो_dpcd(
		link->ctx,
		link,
		368,/*DpcdAddress_PSR_Enable_Cfg*/
		&psr_configuration.raw,
		माप(psr_configuration.raw));


	अगर (psr_configuration.bits.ENABLE) अणु
		अचिन्हित अक्षर dpcdbuf[3] = अणु0पूर्ण;
		जोड़ psr_error_status psr_error_status;
		जोड़ psr_sink_psr_status psr_sink_psr_status;

		dm_helpers_dp_पढ़ो_dpcd(
			link->ctx,
			link,
			0x2006, /*DpcdAddress_PSR_Error_Status*/
			(अचिन्हित अक्षर *) dpcdbuf,
			माप(dpcdbuf));

		/*DPCD 2006h   ERROR STATUS*/
		psr_error_status.raw = dpcdbuf[0];
		/*DPCD 2008h   SINK PANEL SELF REFRESH STATUS*/
		psr_sink_psr_status.raw = dpcdbuf[2];

		अगर (psr_error_status.bits.LINK_CRC_ERROR ||
				psr_error_status.bits.RFB_STORAGE_ERROR ||
				psr_error_status.bits.VSC_SDP_ERROR) अणु
			/* Acknowledge and clear error bits */
			dm_helpers_dp_ग_लिखो_dpcd(
				link->ctx,
				link,
				8198,/*DpcdAddress_PSR_Error_Status*/
				&psr_error_status.raw,
				माप(psr_error_status.raw));

			/* PSR error, disable and re-enable PSR */
			dc_link_set_psr_allow_active(link, false, true, false);
			dc_link_set_psr_allow_active(link, true, true, false);

			वापस true;
		पूर्ण अन्यथा अगर (psr_sink_psr_status.bits.SINK_SELF_REFRESH_STATUS ==
				PSR_SINK_STATE_ACTIVE_DISPLAY_FROM_SINK_RFB)अणु
			/* No error is detect, PSR is active.
			 * We should वापस with IRQ_HPD handled without
			 * checking क्रम loss of sync since PSR would have
			 * घातered करोwn मुख्य link.
			 */
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम dp_test_send_link_training(काष्ठा dc_link *link)
अणु
	काष्ठा dc_link_settings link_settings = अणु0पूर्ण;

	core_link_पढ़ो_dpcd(
			link,
			DP_TEST_LANE_COUNT,
			(अचिन्हित अक्षर *)(&link_settings.lane_count),
			1);
	core_link_पढ़ो_dpcd(
			link,
			DP_TEST_LINK_RATE,
			(अचिन्हित अक्षर *)(&link_settings.link_rate),
			1);

	/* Set preferred link settings */
	link->verअगरied_link_cap.lane_count = link_settings.lane_count;
	link->verअगरied_link_cap.link_rate = link_settings.link_rate;

	dp_retrain_link_dp_test(link, &link_settings, false);
पूर्ण

/* TODO Raven hbr2 compliance eye output is unstable
 * (toggling on and off) with debugger अवरोध
 * This caueses पूर्णांकermittent PHY स्वतःmation failure
 * Need to look पूर्णांकo the root cause */
अटल व्योम dp_test_send_phy_test_pattern(काष्ठा dc_link *link)
अणु
	जोड़ phy_test_pattern dpcd_test_pattern;
	जोड़ lane_adjust dpcd_lane_adjusपंचांगent[2];
	अचिन्हित अक्षर dpcd_post_cursor_2_adjusपंचांगent = 0;
	अचिन्हित अक्षर test_80_bit_pattern[
			(DP_TEST_80BIT_CUSTOM_PATTERN_79_72 -
			DP_TEST_80BIT_CUSTOM_PATTERN_7_0)+1] = अणु0पूर्ण;
	क्रमागत dp_test_pattern test_pattern;
	काष्ठा dc_link_training_settings link_settings;
	जोड़ lane_adjust dpcd_lane_adjust;
	अचिन्हित पूर्णांक lane;
	काष्ठा link_training_settings link_training_settings;
	पूर्णांक i = 0;

	dpcd_test_pattern.raw = 0;
	स_रखो(dpcd_lane_adjusपंचांगent, 0, माप(dpcd_lane_adjusपंचांगent));
	स_रखो(&link_settings, 0, माप(link_settings));

	/* get phy test pattern and pattern parameters from DP receiver */
	core_link_पढ़ो_dpcd(
			link,
			DP_PHY_TEST_PATTERN,
			&dpcd_test_pattern.raw,
			माप(dpcd_test_pattern));
	core_link_पढ़ो_dpcd(
			link,
			DP_ADJUST_REQUEST_LANE0_1,
			&dpcd_lane_adjusपंचांगent[0].raw,
			माप(dpcd_lane_adjusपंचांगent));

	/*get post cursor 2 parameters
	 * For DP 1.1a or eariler, this DPCD रेजिस्टर's value is 0
	 * For DP 1.2 or later:
	 * Bits 1:0 = POST_CURSOR2_LANE0; Bits 3:2 = POST_CURSOR2_LANE1
	 * Bits 5:4 = POST_CURSOR2_LANE2; Bits 7:6 = POST_CURSOR2_LANE3
	 */
	core_link_पढ़ो_dpcd(
			link,
			DP_ADJUST_REQUEST_POST_CURSOR2,
			&dpcd_post_cursor_2_adjusपंचांगent,
			माप(dpcd_post_cursor_2_adjusपंचांगent));

	/* translate request */
	चयन (dpcd_test_pattern.bits.PATTERN) अणु
	हाल PHY_TEST_PATTERN_D10_2:
		test_pattern = DP_TEST_PATTERN_D102;
		अवरोध;
	हाल PHY_TEST_PATTERN_SYMBOL_ERROR:
		test_pattern = DP_TEST_PATTERN_SYMBOL_ERROR;
		अवरोध;
	हाल PHY_TEST_PATTERN_PRBS7:
		test_pattern = DP_TEST_PATTERN_PRBS7;
		अवरोध;
	हाल PHY_TEST_PATTERN_80BIT_CUSTOM:
		test_pattern = DP_TEST_PATTERN_80BIT_CUSTOM;
		अवरोध;
	हाल PHY_TEST_PATTERN_CP2520_1:
		/* CP2520 pattern is unstable, temporarily use TPS4 instead */
		test_pattern = (link->dc->caps.क्रमce_dp_tps4_क्रम_cp2520 == 1) ?
				DP_TEST_PATTERN_TRAINING_PATTERN4 :
				DP_TEST_PATTERN_HBR2_COMPLIANCE_EYE;
		अवरोध;
	हाल PHY_TEST_PATTERN_CP2520_2:
		/* CP2520 pattern is unstable, temporarily use TPS4 instead */
		test_pattern = (link->dc->caps.क्रमce_dp_tps4_क्रम_cp2520 == 1) ?
				DP_TEST_PATTERN_TRAINING_PATTERN4 :
				DP_TEST_PATTERN_HBR2_COMPLIANCE_EYE;
		अवरोध;
	हाल PHY_TEST_PATTERN_CP2520_3:
		test_pattern = DP_TEST_PATTERN_TRAINING_PATTERN4;
		अवरोध;
	शेष:
		test_pattern = DP_TEST_PATTERN_VIDEO_MODE;
	अवरोध;
	पूर्ण

	अगर (test_pattern == DP_TEST_PATTERN_80BIT_CUSTOM)
		core_link_पढ़ो_dpcd(
				link,
				DP_TEST_80BIT_CUSTOM_PATTERN_7_0,
				test_80_bit_pattern,
				माप(test_80_bit_pattern));

	/* prepare link training settings */
	link_settings.link = link->cur_link_settings;

	क्रम (lane = 0; lane <
		(अचिन्हित पूर्णांक)(link->cur_link_settings.lane_count);
		lane++) अणु
		dpcd_lane_adjust.raw =
			get_nibble_at_index(&dpcd_lane_adjusपंचांगent[0].raw, lane);
		link_settings.lane_settings[lane].VOLTAGE_SWING =
			(क्रमागत dc_voltage_swing)
			(dpcd_lane_adjust.bits.VOLTAGE_SWING_LANE);
		link_settings.lane_settings[lane].PRE_EMPHASIS =
			(क्रमागत dc_pre_emphasis)
			(dpcd_lane_adjust.bits.PRE_EMPHASIS_LANE);
		link_settings.lane_settings[lane].POST_CURSOR2 =
			(क्रमागत dc_post_cursor2)
			((dpcd_post_cursor_2_adjusपंचांगent >> (lane * 2)) & 0x03);
	पूर्ण

	क्रम (i = 0; i < 4; i++)
		link_training_settings.lane_settings[i] =
				link_settings.lane_settings[i];
	link_training_settings.link_settings = link_settings.link;
	link_training_settings.allow_invalid_msa_timing_param = false;
	/*Usage: Measure DP physical lane संकेत
	 * by DP SI test equipment स्वतःmatically.
	 * PHY test pattern request is generated by equipment via HPD पूर्णांकerrupt.
	 * HPD needs to be active all the समय. HPD should be active
	 * all the समय. Do not touch it.
	 * क्रमward request to DS
	 */
	dc_link_dp_set_test_pattern(
		link,
		test_pattern,
		DP_TEST_PATTERN_COLOR_SPACE_UNDEFINED,
		&link_training_settings,
		test_80_bit_pattern,
		(DP_TEST_80BIT_CUSTOM_PATTERN_79_72 -
		DP_TEST_80BIT_CUSTOM_PATTERN_7_0)+1);
पूर्ण

अटल व्योम dp_test_send_link_test_pattern(काष्ठा dc_link *link)
अणु
	जोड़ link_test_pattern dpcd_test_pattern;
	जोड़ test_misc dpcd_test_params;
	क्रमागत dp_test_pattern test_pattern;
	क्रमागत dp_test_pattern_color_space test_pattern_color_space =
			DP_TEST_PATTERN_COLOR_SPACE_UNDEFINED;
	क्रमागत dc_color_depth requestColorDepth = COLOR_DEPTH_UNDEFINED;
	काष्ठा pipe_ctx *pipes = link->dc->current_state->res_ctx.pipe_ctx;
	काष्ठा pipe_ctx *pipe_ctx = शून्य;
	पूर्णांक i;

	स_रखो(&dpcd_test_pattern, 0, माप(dpcd_test_pattern));
	स_रखो(&dpcd_test_params, 0, माप(dpcd_test_params));

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		अगर (pipes[i].stream == शून्य)
			जारी;

		अगर (pipes[i].stream->link == link && !pipes[i].top_pipe && !pipes[i].prev_odm_pipe) अणु
			pipe_ctx = &pipes[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (pipe_ctx == शून्य)
		वापस;

	/* get link test pattern and pattern parameters */
	core_link_पढ़ो_dpcd(
			link,
			DP_TEST_PATTERN,
			&dpcd_test_pattern.raw,
			माप(dpcd_test_pattern));
	core_link_पढ़ो_dpcd(
			link,
			DP_TEST_MISC0,
			&dpcd_test_params.raw,
			माप(dpcd_test_params));

	चयन (dpcd_test_pattern.bits.PATTERN) अणु
	हाल LINK_TEST_PATTERN_COLOR_RAMP:
		test_pattern = DP_TEST_PATTERN_COLOR_RAMP;
	अवरोध;
	हाल LINK_TEST_PATTERN_VERTICAL_BARS:
		test_pattern = DP_TEST_PATTERN_VERTICAL_BARS;
	अवरोध; /* black and white */
	हाल LINK_TEST_PATTERN_COLOR_SQUARES:
		test_pattern = (dpcd_test_params.bits.DYN_RANGE ==
				TEST_DYN_RANGE_VESA ?
				DP_TEST_PATTERN_COLOR_SQUARES :
				DP_TEST_PATTERN_COLOR_SQUARES_CEA);
	अवरोध;
	शेष:
		test_pattern = DP_TEST_PATTERN_VIDEO_MODE;
	अवरोध;
	पूर्ण

	अगर (dpcd_test_params.bits.CLR_FORMAT == 0)
		test_pattern_color_space = DP_TEST_PATTERN_COLOR_SPACE_RGB;
	अन्यथा
		test_pattern_color_space = dpcd_test_params.bits.YCBCR_COEFS ?
				DP_TEST_PATTERN_COLOR_SPACE_YCBCR709 :
				DP_TEST_PATTERN_COLOR_SPACE_YCBCR601;

	चयन (dpcd_test_params.bits.BPC) अणु
	हाल 0: // 6 bits
		requestColorDepth = COLOR_DEPTH_666;
		अवरोध;
	हाल 1: // 8 bits
		requestColorDepth = COLOR_DEPTH_888;
		अवरोध;
	हाल 2: // 10 bits
		requestColorDepth = COLOR_DEPTH_101010;
		अवरोध;
	हाल 3: // 12 bits
		requestColorDepth = COLOR_DEPTH_121212;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (requestColorDepth != COLOR_DEPTH_UNDEFINED
			&& pipe_ctx->stream->timing.display_color_depth != requestColorDepth) अणु
		DC_LOG_DEBUG("%s: original bpc %d, changing to %d\n",
				__func__,
				pipe_ctx->stream->timing.display_color_depth,
				requestColorDepth);
		pipe_ctx->stream->timing.display_color_depth = requestColorDepth;
		dp_update_dsc_config(pipe_ctx);
	पूर्ण

	dc_link_dp_set_test_pattern(
			link,
			test_pattern,
			test_pattern_color_space,
			शून्य,
			शून्य,
			0);
पूर्ण

अटल व्योम dp_test_get_audio_test_data(काष्ठा dc_link *link, bool disable_video)
अणु
	जोड़ audio_test_mode            dpcd_test_mode = अणु0पूर्ण;
	काष्ठा audio_test_pattern_type   dpcd_pattern_type = अणु0पूर्ण;
	जोड़ audio_test_pattern_period  dpcd_pattern_period[AUDIO_CHANNELS_COUNT] = अणु0पूर्ण;
	क्रमागत dp_test_pattern test_pattern = DP_TEST_PATTERN_AUDIO_OPERATOR_DEFINED;

	काष्ठा pipe_ctx *pipes = link->dc->current_state->res_ctx.pipe_ctx;
	काष्ठा pipe_ctx *pipe_ctx = &pipes[0];
	अचिन्हित पूर्णांक channel_count;
	अचिन्हित पूर्णांक channel = 0;
	अचिन्हित पूर्णांक modes = 0;
	अचिन्हित पूर्णांक sampling_rate_in_hz = 0;

	// get audio test mode and test pattern parameters
	core_link_पढ़ो_dpcd(
		link,
		DP_TEST_AUDIO_MODE,
		&dpcd_test_mode.raw,
		माप(dpcd_test_mode));

	core_link_पढ़ो_dpcd(
		link,
		DP_TEST_AUDIO_PATTERN_TYPE,
		&dpcd_pattern_type.value,
		माप(dpcd_pattern_type));

	channel_count = dpcd_test_mode.bits.channel_count + 1;

	// पढ़ो pattern periods क्रम requested channels when sawTooth pattern is requested
	अगर (dpcd_pattern_type.value == AUDIO_TEST_PATTERN_SAWTOOTH ||
			dpcd_pattern_type.value == AUDIO_TEST_PATTERN_OPERATOR_DEFINED) अणु

		test_pattern = (dpcd_pattern_type.value == AUDIO_TEST_PATTERN_SAWTOOTH) ?
				DP_TEST_PATTERN_AUDIO_SAWTOOTH : DP_TEST_PATTERN_AUDIO_OPERATOR_DEFINED;
		// पढ़ो period क्रम each channel
		क्रम (channel = 0; channel < channel_count; channel++) अणु
			core_link_पढ़ो_dpcd(
							link,
							DP_TEST_AUDIO_PERIOD_CH1 + channel,
							&dpcd_pattern_period[channel].raw,
							माप(dpcd_pattern_period[channel]));
		पूर्ण
	पूर्ण

	// translate sampling rate
	चयन (dpcd_test_mode.bits.sampling_rate) अणु
	हाल AUDIO_SAMPLING_RATE_32KHZ:
		sampling_rate_in_hz = 32000;
		अवरोध;
	हाल AUDIO_SAMPLING_RATE_44_1KHZ:
		sampling_rate_in_hz = 44100;
		अवरोध;
	हाल AUDIO_SAMPLING_RATE_48KHZ:
		sampling_rate_in_hz = 48000;
		अवरोध;
	हाल AUDIO_SAMPLING_RATE_88_2KHZ:
		sampling_rate_in_hz = 88200;
		अवरोध;
	हाल AUDIO_SAMPLING_RATE_96KHZ:
		sampling_rate_in_hz = 96000;
		अवरोध;
	हाल AUDIO_SAMPLING_RATE_176_4KHZ:
		sampling_rate_in_hz = 176400;
		अवरोध;
	हाल AUDIO_SAMPLING_RATE_192KHZ:
		sampling_rate_in_hz = 192000;
		अवरोध;
	शेष:
		sampling_rate_in_hz = 0;
		अवरोध;
	पूर्ण

	link->audio_test_data.flags.test_requested = 1;
	link->audio_test_data.flags.disable_video = disable_video;
	link->audio_test_data.sampling_rate = sampling_rate_in_hz;
	link->audio_test_data.channel_count = channel_count;
	link->audio_test_data.pattern_type = test_pattern;

	अगर (test_pattern == DP_TEST_PATTERN_AUDIO_SAWTOOTH) अणु
		क्रम (modes = 0; modes < pipe_ctx->stream->audio_info.mode_count; modes++) अणु
			link->audio_test_data.pattern_period[modes] = dpcd_pattern_period[modes].bits.pattern_period;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम handle_स्वतःmated_test(काष्ठा dc_link *link)
अणु
	जोड़ test_request test_request;
	जोड़ test_response test_response;

	स_रखो(&test_request, 0, माप(test_request));
	स_रखो(&test_response, 0, माप(test_response));

	core_link_पढ़ो_dpcd(
		link,
		DP_TEST_REQUEST,
		&test_request.raw,
		माप(जोड़ test_request));
	अगर (test_request.bits.LINK_TRAINING) अणु
		/* ACK first to let DP RX test box monitor LT sequence */
		test_response.bits.ACK = 1;
		core_link_ग_लिखो_dpcd(
			link,
			DP_TEST_RESPONSE,
			&test_response.raw,
			माप(test_response));
		dp_test_send_link_training(link);
		/* no acknowledge request is needed again */
		test_response.bits.ACK = 0;
	पूर्ण
	अगर (test_request.bits.LINK_TEST_PATTRN) अणु
		dp_test_send_link_test_pattern(link);
		test_response.bits.ACK = 1;
	पूर्ण

	अगर (test_request.bits.AUDIO_TEST_PATTERN) अणु
		dp_test_get_audio_test_data(link, test_request.bits.TEST_AUDIO_DISABLED_VIDEO);
		test_response.bits.ACK = 1;
	पूर्ण

	अगर (test_request.bits.PHY_TEST_PATTERN) अणु
		dp_test_send_phy_test_pattern(link);
		test_response.bits.ACK = 1;
	पूर्ण

	/* send request acknowledgment */
	अगर (test_response.bits.ACK)
		core_link_ग_लिखो_dpcd(
			link,
			DP_TEST_RESPONSE,
			&test_response.raw,
			माप(test_response));
पूर्ण

bool dc_link_handle_hpd_rx_irq(काष्ठा dc_link *link, जोड़ hpd_irq_data *out_hpd_irq_dpcd_data, bool *out_link_loss)
अणु
	जोड़ hpd_irq_data hpd_irq_dpcd_data = अणु अणु अणु अणु0पूर्ण पूर्ण पूर्ण पूर्ण;
	जोड़ device_service_irq device_service_clear = अणु अणु 0 पूर्ण पूर्ण;
	क्रमागत dc_status result;
	bool status = false;
	काष्ठा pipe_ctx *pipe_ctx;
	पूर्णांक i;

	अगर (out_link_loss)
		*out_link_loss = false;
	/* For use हालs related to करोwn stream connection status change,
	 * PSR and device स्वतः test, refer to function handle_sst_hpd_irq
	 * in DAL2.1*/

	DC_LOG_HW_HPD_IRQ("%s: Got short pulse HPD on link %d\n",
		__func__, link->link_index);


	 /* All the "handle_hpd_irq_xxx()" methods
		 * should be called only after
		 * dal_dpsst_ls_पढ़ो_hpd_irq_data
		 * Order of calls is important too
		 */
	result = पढ़ो_hpd_rx_irq_data(link, &hpd_irq_dpcd_data);
	अगर (out_hpd_irq_dpcd_data)
		*out_hpd_irq_dpcd_data = hpd_irq_dpcd_data;

	अगर (result != DC_OK) अणु
		DC_LOG_HW_HPD_IRQ("%s: DPCD read failed to obtain irq data\n",
			__func__);
		वापस false;
	पूर्ण

	अगर (hpd_irq_dpcd_data.bytes.device_service_irq.bits.AUTOMATED_TEST) अणु
		device_service_clear.bits.AUTOMATED_TEST = 1;
		core_link_ग_लिखो_dpcd(
			link,
			DP_DEVICE_SERVICE_IRQ_VECTOR,
			&device_service_clear.raw,
			माप(device_service_clear.raw));
		device_service_clear.raw = 0;
		handle_स्वतःmated_test(link);
		वापस false;
	पूर्ण

	अगर (!allow_hpd_rx_irq(link)) अणु
		DC_LOG_HW_HPD_IRQ("%s: skipping HPD handling on %d\n",
			__func__, link->link_index);
		वापस false;
	पूर्ण

	अगर (handle_hpd_irq_psr_sink(link))
		/* PSR-related error was detected and handled */
		वापस true;

	/* If PSR-related error handled, Main link may be off,
	 * so करो not handle as a normal sink status change पूर्णांकerrupt.
	 */

	अगर (hpd_irq_dpcd_data.bytes.device_service_irq.bits.UP_REQ_MSG_RDY)
		वापस true;

	/* check अगर we have MST msg and वापस since we poll क्रम it */
	अगर (hpd_irq_dpcd_data.bytes.device_service_irq.bits.DOWN_REP_MSG_RDY)
		वापस false;

	/* For now we only handle 'Downstream port status' हाल.
	 * If we got sink count changed it means
	 * Downstream port status changed,
	 * then DM should call DC to करो the detection.
	 * NOTE: Do not handle link loss on eDP since it is पूर्णांकernal link*/
	अगर ((link->connector_संकेत != SIGNAL_TYPE_EDP) &&
		hpd_rx_irq_check_link_loss_status(
			link,
			&hpd_irq_dpcd_data)) अणु
		/* Connectivity log: link loss */
		CONN_DATA_LINK_LOSS(link,
					hpd_irq_dpcd_data.raw,
					माप(hpd_irq_dpcd_data),
					"Status: ");

		क्रम (i = 0; i < MAX_PIPES; i++) अणु
			pipe_ctx = &link->dc->current_state->res_ctx.pipe_ctx[i];
			अगर (pipe_ctx && pipe_ctx->stream && pipe_ctx->stream->link == link)
				अवरोध;
		पूर्ण

		अगर (pipe_ctx == शून्य || pipe_ctx->stream == शून्य)
			वापस false;


		क्रम (i = 0; i < MAX_PIPES; i++) अणु
			pipe_ctx = &link->dc->current_state->res_ctx.pipe_ctx[i];
			अगर (pipe_ctx && pipe_ctx->stream && !pipe_ctx->stream->dpms_off &&
					pipe_ctx->stream->link == link && !pipe_ctx->prev_odm_pipe)
				core_link_disable_stream(pipe_ctx);
		पूर्ण

		क्रम (i = 0; i < MAX_PIPES; i++) अणु
			pipe_ctx = &link->dc->current_state->res_ctx.pipe_ctx[i];
			अगर (pipe_ctx && pipe_ctx->stream && !pipe_ctx->stream->dpms_off &&
					pipe_ctx->stream->link == link && !pipe_ctx->prev_odm_pipe)
				core_link_enable_stream(link->dc->current_state, pipe_ctx);
		पूर्ण

		status = false;
		अगर (out_link_loss)
			*out_link_loss = true;
	पूर्ण

	अगर (link->type == dc_connection_active_करोngle &&
		hpd_irq_dpcd_data.bytes.sink_cnt.bits.SINK_COUNT
			!= link->dpcd_sink_count)
		status = true;

	/* reasons क्रम HPD RX:
	 * 1. Link Loss - ie Re-train the Link
	 * 2. MST sideband message
	 * 3. Automated Test - ie. Internal Commit
	 * 4. CP (copy protection) - (not पूर्णांकeresting क्रम DM???)
	 * 5. DRR
	 * 6. Downstream Port status changed
	 * -ie. Detect - this the only one
	 * which is पूर्णांकeresting क्रम DM because
	 * it must call dc_link_detect.
	 */
	वापस status;
पूर्ण

/*query dpcd क्रम version and mst cap addresses*/
bool is_mst_supported(काष्ठा dc_link *link)
अणु
	bool mst          = false;
	क्रमागत dc_status st = DC_OK;
	जोड़ dpcd_rev rev;
	जोड़ msपंचांग_cap cap;

	अगर (link->preferred_training_settings.mst_enable &&
		*link->preferred_training_settings.mst_enable == false) अणु
		वापस false;
	पूर्ण

	rev.raw  = 0;
	cap.raw  = 0;

	st = core_link_पढ़ो_dpcd(link, DP_DPCD_REV, &rev.raw,
			माप(rev));

	अगर (st == DC_OK && rev.raw >= DPCD_REV_12) अणु

		st = core_link_पढ़ो_dpcd(link, DP_MSTM_CAP,
				&cap.raw, माप(cap));
		अगर (st == DC_OK && cap.bits.MST_CAP == 1)
			mst = true;
	पूर्ण
	वापस mst;

पूर्ण

bool is_dp_active_करोngle(स्थिर काष्ठा dc_link *link)
अणु
	वापस link->dpcd_caps.is_branch_dev;
पूर्ण

अटल पूर्णांक translate_dpcd_max_bpc(क्रमागत dpcd_करोwnstream_port_max_bpc bpc)
अणु
	चयन (bpc) अणु
	हाल DOWN_STREAM_MAX_8BPC:
		वापस 8;
	हाल DOWN_STREAM_MAX_10BPC:
		वापस 10;
	हाल DOWN_STREAM_MAX_12BPC:
		वापस 12;
	हाल DOWN_STREAM_MAX_16BPC:
		वापस 16;
	शेष:
		अवरोध;
	पूर्ण

	वापस -1;
पूर्ण

अटल व्योम पढ़ो_dp_device_venकरोr_id(काष्ठा dc_link *link)
अणु
	काष्ठा dp_device_venकरोr_id dp_id;

	/* पढ़ो IEEE branch device id */
	core_link_पढ़ो_dpcd(
		link,
		DP_BRANCH_OUI,
		(uपूर्णांक8_t *)&dp_id,
		माप(dp_id));

	link->dpcd_caps.branch_dev_id =
		(dp_id.ieee_oui[0] << 16) +
		(dp_id.ieee_oui[1] << 8) +
		dp_id.ieee_oui[2];

	स_हटाओ(
		link->dpcd_caps.branch_dev_name,
		dp_id.ieee_device_id,
		माप(dp_id.ieee_device_id));
पूर्ण



अटल व्योम get_active_converter_info(
	uपूर्णांक8_t data, काष्ठा dc_link *link)
अणु
	जोड़ dp_करोwnstream_port_present ds_port = अणु .byte = data पूर्ण;
	स_रखो(&link->dpcd_caps.करोngle_caps, 0, माप(link->dpcd_caps.करोngle_caps));

	/* decode converter info*/
	अगर (!ds_port.fields.PORT_PRESENT) अणु
		link->dpcd_caps.करोngle_type = DISPLAY_DONGLE_NONE;
		ddc_service_set_करोngle_type(link->ddc,
				link->dpcd_caps.करोngle_type);
		link->dpcd_caps.is_branch_dev = false;
		वापस;
	पूर्ण

	/* DPCD 0x5 bit 0 = 1, it indicate it's branch device */
	link->dpcd_caps.is_branch_dev = ds_port.fields.PORT_PRESENT;

	चयन (ds_port.fields.PORT_TYPE) अणु
	हाल DOWNSTREAM_VGA:
		link->dpcd_caps.करोngle_type = DISPLAY_DONGLE_DP_VGA_CONVERTER;
		अवरोध;
	हाल DOWNSTREAM_DVI_HDMI_DP_PLUS_PLUS:
		/* At this poपूर्णांक we करोn't know is it DVI or HDMI or DP++,
		 * assume DVI.*/
		link->dpcd_caps.करोngle_type = DISPLAY_DONGLE_DP_DVI_CONVERTER;
		अवरोध;
	शेष:
		link->dpcd_caps.करोngle_type = DISPLAY_DONGLE_NONE;
		अवरोध;
	पूर्ण

	अगर (link->dpcd_caps.dpcd_rev.raw >= DPCD_REV_11) अणु
		uपूर्णांक8_t det_caps[16]; /* CTS 4.2.2.7 expects source to पढ़ो Detailed Capabilities Info : 00080h-0008F.*/
		जोड़ dwnstream_port_caps_byte0 *port_caps =
			(जोड़ dwnstream_port_caps_byte0 *)det_caps;
		अगर (core_link_पढ़ो_dpcd(link, DP_DOWNSTREAM_PORT_0,
				det_caps, माप(det_caps)) == DC_OK) अणु

			चयन (port_caps->bits.DWN_STRM_PORTX_TYPE) अणु
			/*Handle DP हाल as DONGLE_NONE*/
			हाल DOWN_STREAM_DETAILED_DP:
				link->dpcd_caps.करोngle_type = DISPLAY_DONGLE_NONE;
				अवरोध;
			हाल DOWN_STREAM_DETAILED_VGA:
				link->dpcd_caps.करोngle_type =
					DISPLAY_DONGLE_DP_VGA_CONVERTER;
				अवरोध;
			हाल DOWN_STREAM_DETAILED_DVI:
				link->dpcd_caps.करोngle_type =
					DISPLAY_DONGLE_DP_DVI_CONVERTER;
				अवरोध;
			हाल DOWN_STREAM_DETAILED_HDMI:
			हाल DOWN_STREAM_DETAILED_DP_PLUS_PLUS:
				/*Handle DP++ active converter हाल, process DP++ हाल as HDMI हाल according DP1.4 spec*/
				link->dpcd_caps.करोngle_type =
					DISPLAY_DONGLE_DP_HDMI_CONVERTER;

				link->dpcd_caps.करोngle_caps.करोngle_type = link->dpcd_caps.करोngle_type;
				अगर (ds_port.fields.DETAILED_CAPS) अणु

					जोड़ dwnstream_port_caps_byte3_hdmi
						hdmi_caps = अणु.raw = det_caps[3] पूर्ण;
					जोड़ dwnstream_port_caps_byte2
						hdmi_color_caps = अणु.raw = det_caps[2] पूर्ण;
					link->dpcd_caps.करोngle_caps.dp_hdmi_max_pixel_clk_in_khz =
						det_caps[1] * 2500;

					link->dpcd_caps.करोngle_caps.is_dp_hdmi_s3d_converter =
						hdmi_caps.bits.FRAME_SEQ_TO_FRAME_PACK;
					/*YCBCR capability only क्रम HDMI हाल*/
					अगर (port_caps->bits.DWN_STRM_PORTX_TYPE
							== DOWN_STREAM_DETAILED_HDMI) अणु
						link->dpcd_caps.करोngle_caps.is_dp_hdmi_ycbcr422_pass_through =
								hdmi_caps.bits.YCrCr422_PASS_THROUGH;
						link->dpcd_caps.करोngle_caps.is_dp_hdmi_ycbcr420_pass_through =
								hdmi_caps.bits.YCrCr420_PASS_THROUGH;
						link->dpcd_caps.करोngle_caps.is_dp_hdmi_ycbcr422_converter =
								hdmi_caps.bits.YCrCr422_CONVERSION;
						link->dpcd_caps.करोngle_caps.is_dp_hdmi_ycbcr420_converter =
								hdmi_caps.bits.YCrCr420_CONVERSION;
					पूर्ण

					link->dpcd_caps.करोngle_caps.dp_hdmi_max_bpc =
						translate_dpcd_max_bpc(
							hdmi_color_caps.bits.MAX_BITS_PER_COLOR_COMPONENT);

					अगर (link->dpcd_caps.करोngle_caps.dp_hdmi_max_pixel_clk_in_khz != 0)
						link->dpcd_caps.करोngle_caps.extendedCapValid = true;
				पूर्ण

				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	ddc_service_set_करोngle_type(link->ddc, link->dpcd_caps.करोngle_type);

	अणु
		काष्ठा dp_sink_hw_fw_revision dp_hw_fw_revision;

		core_link_पढ़ो_dpcd(
			link,
			DP_BRANCH_REVISION_START,
			(uपूर्णांक8_t *)&dp_hw_fw_revision,
			माप(dp_hw_fw_revision));

		link->dpcd_caps.branch_hw_revision =
			dp_hw_fw_revision.ieee_hw_rev;

		स_हटाओ(
			link->dpcd_caps.branch_fw_revision,
			dp_hw_fw_revision.ieee_fw_rev,
			माप(dp_hw_fw_revision.ieee_fw_rev));
	पूर्ण
पूर्ण

अटल व्योम dp_wa_घातer_up_0010FA(काष्ठा dc_link *link, uपूर्णांक8_t *dpcd_data,
		पूर्णांक length)
अणु
	पूर्णांक retry = 0;

	अगर (!link->dpcd_caps.dpcd_rev.raw) अणु
		करो अणु
			dp_receiver_घातer_ctrl(link, true);
			core_link_पढ़ो_dpcd(link, DP_DPCD_REV,
							dpcd_data, length);
			link->dpcd_caps.dpcd_rev.raw = dpcd_data[
				DP_DPCD_REV -
				DP_DPCD_REV];
		पूर्ण जबतक (retry++ < 4 && !link->dpcd_caps.dpcd_rev.raw);
	पूर्ण

	अगर (link->dpcd_caps.करोngle_type == DISPLAY_DONGLE_DP_VGA_CONVERTER) अणु
		चयन (link->dpcd_caps.branch_dev_id) अणु
		/* 0010FA active करोngles (DP-VGA, DP-DLDVI converters) घातer करोwn
		 * all पूर्णांकernal circuits including AUX communication preventing
		 * पढ़ोing DPCD table and EDID (spec violation).
		 * Encoder will skip DP RX घातer करोwn on disable_output to
		 * keep receiver घातered all the समय.*/
		हाल DP_BRANCH_DEVICE_ID_0010FA:
		हाल DP_BRANCH_DEVICE_ID_0080E1:
		हाल DP_BRANCH_DEVICE_ID_00E04C:
			link->wa_flags.dp_keep_receiver_घातered = true;
			अवरोध;

		/* TODO: May need work around क्रम other करोngles. */
		शेष:
			link->wa_flags.dp_keep_receiver_घातered = false;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा
		link->wa_flags.dp_keep_receiver_घातered = false;
पूर्ण

/* Read additional sink caps defined in source specअगरic DPCD area
 * This function currently only पढ़ोs from SinkCapability address (DP_SOURCE_SINK_CAP)
 */
अटल bool dpcd_पढ़ो_sink_ext_caps(काष्ठा dc_link *link)
अणु
	uपूर्णांक8_t dpcd_data;

	अगर (!link)
		वापस false;

	अगर (core_link_पढ़ो_dpcd(link, DP_SOURCE_SINK_CAP, &dpcd_data, 1) != DC_OK)
		वापस false;

	link->dpcd_sink_ext_caps.raw = dpcd_data;
	वापस true;
पूर्ण

अटल bool retrieve_link_cap(काष्ठा dc_link *link)
अणु
	/* DP_ADAPTER_CAP - DP_DPCD_REV + 1 == 16 and also DP_DSC_BITS_PER_PIXEL_INC - DP_DSC_SUPPORT + 1 == 16,
	 * which means size 16 will be good क्रम both of those DPCD रेजिस्टर block पढ़ोs
	 */
	uपूर्णांक8_t dpcd_data[16];
	uपूर्णांक8_t lttpr_dpcd_data[6];

	/*Only need to पढ़ो 1 byte starting from DP_DPRX_FEATURE_ENUMERATION_LIST.
	 */
	uपूर्णांक8_t dpcd_dprx_data = '\0';
	uपूर्णांक8_t dpcd_घातer_state = '\0';

	काष्ठा dp_device_venकरोr_id sink_id;
	जोड़ करोwn_stream_port_count करोwn_strm_port_count;
	जोड़ edp_configuration_cap edp_config_cap;
	जोड़ dp_करोwnstream_port_present ds_port = अणु 0 पूर्ण;
	क्रमागत dc_status status = DC_ERROR_UNEXPECTED;
	uपूर्णांक32_t पढ़ो_dpcd_retry_cnt = 3;
	पूर्णांक i;
	काष्ठा dp_sink_hw_fw_revision dp_hw_fw_revision;
	bool is_lttpr_present = false;
	स्थिर uपूर्णांक32_t post_oui_delay = 30; // 30ms
	bool vbios_lttpr_enable = false;
	bool vbios_lttpr_पूर्णांकerop = false;
	काष्ठा dc_bios *bios = link->dc->ctx->dc_bios;

	स_रखो(dpcd_data, '\0', माप(dpcd_data));
	स_रखो(lttpr_dpcd_data, '\0', माप(lttpr_dpcd_data));
	स_रखो(&करोwn_strm_port_count,
		'\0', माप(जोड़ करोwn_stream_port_count));
	स_रखो(&edp_config_cap, '\0',
		माप(जोड़ edp_configuration_cap));

	/* अगर extended समयout is supported in hardware,
	 * शेष to LTTPR समयout (3.2ms) first as a W/A क्रम DP link layer
	 * CTS 4.2.1.1 regression पूर्णांकroduced by CTS specs requirement update.
	 */
	dc_link_aux_try_to_configure_समयout(link->ddc,
			LINK_AUX_DEFAULT_LTTPR_TIMEOUT_PERIOD);

	status = core_link_पढ़ो_dpcd(link, DP_SET_POWER,
				&dpcd_घातer_state, माप(dpcd_घातer_state));

	/* Delay 1 ms अगर AUX CH is in घातer करोwn state. Based on spec
	 * section 2.3.1.2, अगर AUX CH may be घातered करोwn due to
	 * ग_लिखो to DPCD 600h = 2. Sink AUX CH is monitoring dअगरferential
	 * संकेत and may need up to 1 ms beक्रमe being able to reply.
	 */
	अगर (status != DC_OK || dpcd_घातer_state == DP_SET_POWER_D3)
		udelay(1000);

	dpcd_set_source_specअगरic_data(link);
	/* Sink may need to configure पूर्णांकernals based on venकरोr, so allow some
	 * समय beक्रमe proceeding with possibly venकरोr specअगरic transactions
	 */
	msleep(post_oui_delay);

	क्रम (i = 0; i < पढ़ो_dpcd_retry_cnt; i++) अणु
		status = core_link_पढ़ो_dpcd(
				link,
				DP_DPCD_REV,
				dpcd_data,
				माप(dpcd_data));
		अगर (status == DC_OK)
			अवरोध;
	पूर्ण

	अगर (status != DC_OK) अणु
		dm_error("%s: Read dpcd data failed.\n", __func__);
		वापस false;
	पूर्ण

	/* Query BIOS to determine अगर LTTPR functionality is क्रमced on by प्रणाली */
	अगर (bios->funcs->get_lttpr_caps) अणु
		क्रमागत bp_result bp_query_result;
		uपूर्णांक8_t is_vbios_lttpr_enable = 0;

		bp_query_result = bios->funcs->get_lttpr_caps(bios, &is_vbios_lttpr_enable);
		vbios_lttpr_enable = (bp_query_result == BP_RESULT_OK) && !!is_vbios_lttpr_enable;
	पूर्ण

	अगर (bios->funcs->get_lttpr_पूर्णांकerop) अणु
		क्रमागत bp_result bp_query_result;
		uपूर्णांक8_t is_vbios_पूर्णांकerop_enabled = 0;

		bp_query_result = bios->funcs->get_lttpr_पूर्णांकerop(bios, &is_vbios_पूर्णांकerop_enabled);
		vbios_lttpr_पूर्णांकerop = (bp_query_result == BP_RESULT_OK) && !!is_vbios_पूर्णांकerop_enabled;
	पूर्ण

	/*
	 * Logic to determine LTTPR mode
	 */
	link->lttpr_mode = LTTPR_MODE_NON_LTTPR;
	अगर (vbios_lttpr_enable && vbios_lttpr_पूर्णांकerop)
		link->lttpr_mode = LTTPR_MODE_NON_TRANSPARENT;
	अन्यथा अगर (!vbios_lttpr_enable && vbios_lttpr_पूर्णांकerop) अणु
		अगर (link->dc->config.allow_lttpr_non_transparent_mode)
			link->lttpr_mode = LTTPR_MODE_NON_TRANSPARENT;
		अन्यथा
			link->lttpr_mode = LTTPR_MODE_TRANSPARENT;
	पूर्ण अन्यथा अगर (!vbios_lttpr_enable && !vbios_lttpr_पूर्णांकerop) अणु
		अगर (!link->dc->config.allow_lttpr_non_transparent_mode
			|| !link->dc->caps.extended_aux_समयout_support)
			link->lttpr_mode = LTTPR_MODE_NON_LTTPR;
		अन्यथा
			link->lttpr_mode = LTTPR_MODE_NON_TRANSPARENT;
	पूर्ण

	अगर (link->lttpr_mode == LTTPR_MODE_NON_TRANSPARENT || link->lttpr_mode == LTTPR_MODE_TRANSPARENT) अणु
		/* By पढ़ोing LTTPR capability, RX assumes that we will enable
		 * LTTPR extended aux समयout अगर LTTPR is present.
		 */
		status = core_link_पढ़ो_dpcd(
				link,
				DP_LT_TUNABLE_PHY_REPEATER_FIELD_DATA_STRUCTURE_REV,
				lttpr_dpcd_data,
				माप(lttpr_dpcd_data));

		link->dpcd_caps.lttpr_caps.revision.raw =
				lttpr_dpcd_data[DP_LT_TUNABLE_PHY_REPEATER_FIELD_DATA_STRUCTURE_REV -
								DP_LT_TUNABLE_PHY_REPEATER_FIELD_DATA_STRUCTURE_REV];

		link->dpcd_caps.lttpr_caps.max_link_rate =
				lttpr_dpcd_data[DP_MAX_LINK_RATE_PHY_REPEATER -
								DP_LT_TUNABLE_PHY_REPEATER_FIELD_DATA_STRUCTURE_REV];

		link->dpcd_caps.lttpr_caps.phy_repeater_cnt =
				lttpr_dpcd_data[DP_PHY_REPEATER_CNT -
								DP_LT_TUNABLE_PHY_REPEATER_FIELD_DATA_STRUCTURE_REV];

		link->dpcd_caps.lttpr_caps.max_lane_count =
				lttpr_dpcd_data[DP_MAX_LANE_COUNT_PHY_REPEATER -
								DP_LT_TUNABLE_PHY_REPEATER_FIELD_DATA_STRUCTURE_REV];

		link->dpcd_caps.lttpr_caps.mode =
				lttpr_dpcd_data[DP_PHY_REPEATER_MODE -
								DP_LT_TUNABLE_PHY_REPEATER_FIELD_DATA_STRUCTURE_REV];

		link->dpcd_caps.lttpr_caps.max_ext_समयout =
				lttpr_dpcd_data[DP_PHY_REPEATER_EXTENDED_WAIT_TIMEOUT -
								DP_LT_TUNABLE_PHY_REPEATER_FIELD_DATA_STRUCTURE_REV];

		is_lttpr_present = (link->dpcd_caps.lttpr_caps.phy_repeater_cnt > 0 &&
				link->dpcd_caps.lttpr_caps.max_lane_count > 0 &&
				link->dpcd_caps.lttpr_caps.max_lane_count <= 4 &&
				link->dpcd_caps.lttpr_caps.revision.raw >= 0x14);
		अगर (is_lttpr_present)
			CONN_DATA_DETECT(link, lttpr_dpcd_data, माप(lttpr_dpcd_data), "LTTPR Caps: ");
		अन्यथा
			link->lttpr_mode = LTTPR_MODE_NON_LTTPR;
	पूर्ण

	अगर (!is_lttpr_present)
		dc_link_aux_try_to_configure_समयout(link->ddc, LINK_AUX_DEFAULT_TIMEOUT_PERIOD);


	अणु
		जोड़ training_aux_rd_पूर्णांकerval aux_rd_पूर्णांकerval;

		aux_rd_पूर्णांकerval.raw =
			dpcd_data[DP_TRAINING_AUX_RD_INTERVAL];

		link->dpcd_caps.ext_receiver_cap_field_present =
				aux_rd_पूर्णांकerval.bits.EXT_RECEIVER_CAP_FIELD_PRESENT == 1;

		अगर (aux_rd_पूर्णांकerval.bits.EXT_RECEIVER_CAP_FIELD_PRESENT == 1) अणु
			uपूर्णांक8_t ext_cap_data[16];

			स_रखो(ext_cap_data, '\0', माप(ext_cap_data));
			क्रम (i = 0; i < पढ़ो_dpcd_retry_cnt; i++) अणु
				status = core_link_पढ़ो_dpcd(
				link,
				DP_DP13_DPCD_REV,
				ext_cap_data,
				माप(ext_cap_data));
				अगर (status == DC_OK) अणु
					स_नकल(dpcd_data, ext_cap_data, माप(dpcd_data));
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (status != DC_OK)
				dm_error("%s: Read extend caps data failed, use cap from dpcd 0.\n", __func__);
		पूर्ण
	पूर्ण

	link->dpcd_caps.dpcd_rev.raw =
			dpcd_data[DP_DPCD_REV - DP_DPCD_REV];

	अगर (link->dpcd_caps.ext_receiver_cap_field_present) अणु
		क्रम (i = 0; i < पढ़ो_dpcd_retry_cnt; i++) अणु
			status = core_link_पढ़ो_dpcd(
					link,
					DP_DPRX_FEATURE_ENUMERATION_LIST,
					&dpcd_dprx_data,
					माप(dpcd_dprx_data));
			अगर (status == DC_OK)
				अवरोध;
		पूर्ण

		link->dpcd_caps.dprx_feature.raw = dpcd_dprx_data;

		अगर (status != DC_OK)
			dm_error("%s: Read DPRX caps data failed.\n", __func__);
	पूर्ण

	अन्यथा अणु
		link->dpcd_caps.dprx_feature.raw = 0;
	पूर्ण


	/* Error condition checking...
	 * It is impossible क्रम Sink to report Max Lane Count = 0.
	 * It is possible क्रम Sink to report Max Link Rate = 0, अगर it is
	 * an eDP device that is reporting specialized link rates in the
	 * SUPPORTED_LINK_RATE table.
	 */
	अगर (dpcd_data[DP_MAX_LANE_COUNT - DP_DPCD_REV] == 0)
		वापस false;

	ds_port.byte = dpcd_data[DP_DOWNSTREAMPORT_PRESENT -
				 DP_DPCD_REV];

	पढ़ो_dp_device_venकरोr_id(link);

	get_active_converter_info(ds_port.byte, link);

	dp_wa_घातer_up_0010FA(link, dpcd_data, माप(dpcd_data));

	करोwn_strm_port_count.raw = dpcd_data[DP_DOWN_STREAM_PORT_COUNT -
				 DP_DPCD_REV];

	link->dpcd_caps.allow_invalid_MSA_timing_param =
		करोwn_strm_port_count.bits.IGNORE_MSA_TIMING_PARAM;

	link->dpcd_caps.max_ln_count.raw = dpcd_data[
		DP_MAX_LANE_COUNT - DP_DPCD_REV];

	link->dpcd_caps.max_करोwn_spपढ़ो.raw = dpcd_data[
		DP_MAX_DOWNSPREAD - DP_DPCD_REV];

	link->reported_link_cap.lane_count =
		link->dpcd_caps.max_ln_count.bits.MAX_LANE_COUNT;
	link->reported_link_cap.link_rate = dpcd_data[
		DP_MAX_LINK_RATE - DP_DPCD_REV];
	link->reported_link_cap.link_spपढ़ो =
		link->dpcd_caps.max_करोwn_spपढ़ो.bits.MAX_DOWN_SPREAD ?
		LINK_SPREAD_05_DOWNSPREAD_30KHZ : LINK_SPREAD_DISABLED;

	edp_config_cap.raw = dpcd_data[
		DP_EDP_CONFIGURATION_CAP - DP_DPCD_REV];
	link->dpcd_caps.panel_mode_edp =
		edp_config_cap.bits.ALT_SCRAMBLER_RESET;
	link->dpcd_caps.dpcd_display_control_capable =
		edp_config_cap.bits.DPCD_DISPLAY_CONTROL_CAPABLE;

	link->test_pattern_enabled = false;
	link->compliance_test_state.raw = 0;

	/* पढ़ो sink count */
	core_link_पढ़ो_dpcd(link,
			DP_SINK_COUNT,
			&link->dpcd_caps.sink_count.raw,
			माप(link->dpcd_caps.sink_count.raw));

	/* पढ़ो sink ieee oui */
	core_link_पढ़ो_dpcd(link,
			DP_SINK_OUI,
			(uपूर्णांक8_t *)(&sink_id),
			माप(sink_id));

	link->dpcd_caps.sink_dev_id =
			(sink_id.ieee_oui[0] << 16) +
			(sink_id.ieee_oui[1] << 8) +
			(sink_id.ieee_oui[2]);

	स_हटाओ(
		link->dpcd_caps.sink_dev_id_str,
		sink_id.ieee_device_id,
		माप(sink_id.ieee_device_id));

	/* Quirk Apple MBP 2017 15" Retina panel: Wrong DP_MAX_LINK_RATE */
	अणु
		uपूर्णांक8_t str_mbp_2017[] = अणु 101, 68, 21, 101, 98, 97 पूर्ण;

		अगर ((link->dpcd_caps.sink_dev_id == 0x0010fa) &&
		    !स_भेद(link->dpcd_caps.sink_dev_id_str, str_mbp_2017,
			    माप(str_mbp_2017))) अणु
			link->reported_link_cap.link_rate = 0x0c;
		पूर्ण
	पूर्ण

	core_link_पढ़ो_dpcd(
		link,
		DP_SINK_HW_REVISION_START,
		(uपूर्णांक8_t *)&dp_hw_fw_revision,
		माप(dp_hw_fw_revision));

	link->dpcd_caps.sink_hw_revision =
		dp_hw_fw_revision.ieee_hw_rev;

	स_हटाओ(
		link->dpcd_caps.sink_fw_revision,
		dp_hw_fw_revision.ieee_fw_rev,
		माप(dp_hw_fw_revision.ieee_fw_rev));

	स_रखो(&link->dpcd_caps.dsc_caps, '\0',
			माप(link->dpcd_caps.dsc_caps));
	स_रखो(&link->dpcd_caps.fec_cap, '\0', माप(link->dpcd_caps.fec_cap));
	/* Read DSC and FEC sink capabilities अगर DP revision is 1.4 and up */
	अगर (link->dpcd_caps.dpcd_rev.raw >= DPCD_REV_14) अणु
		status = core_link_पढ़ो_dpcd(
				link,
				DP_FEC_CAPABILITY,
				&link->dpcd_caps.fec_cap.raw,
				माप(link->dpcd_caps.fec_cap.raw));
		status = core_link_पढ़ो_dpcd(
				link,
				DP_DSC_SUPPORT,
				link->dpcd_caps.dsc_caps.dsc_basic_caps.raw,
				माप(link->dpcd_caps.dsc_caps.dsc_basic_caps.raw));
		status = core_link_पढ़ो_dpcd(
				link,
				DP_DSC_BRANCH_OVERALL_THROUGHPUT_0,
				link->dpcd_caps.dsc_caps.dsc_branch_decoder_caps.raw,
				माप(link->dpcd_caps.dsc_caps.dsc_branch_decoder_caps.raw));
	पूर्ण

	अगर (!dpcd_पढ़ो_sink_ext_caps(link))
		link->dpcd_sink_ext_caps.raw = 0;

	/* Connectivity log: detection */
	CONN_DATA_DETECT(link, dpcd_data, माप(dpcd_data), "Rx Caps: ");

	वापस true;
पूर्ण

bool dp_overग_लिखो_extended_receiver_cap(काष्ठा dc_link *link)
अणु
	uपूर्णांक8_t dpcd_data[16];
	uपूर्णांक32_t पढ़ो_dpcd_retry_cnt = 3;
	क्रमागत dc_status status = DC_ERROR_UNEXPECTED;
	जोड़ dp_करोwnstream_port_present ds_port = अणु 0 पूर्ण;
	जोड़ करोwn_stream_port_count करोwn_strm_port_count;
	जोड़ edp_configuration_cap edp_config_cap;

	पूर्णांक i;

	क्रम (i = 0; i < पढ़ो_dpcd_retry_cnt; i++) अणु
		status = core_link_पढ़ो_dpcd(
				link,
				DP_DPCD_REV,
				dpcd_data,
				माप(dpcd_data));
		अगर (status == DC_OK)
			अवरोध;
	पूर्ण

	link->dpcd_caps.dpcd_rev.raw =
		dpcd_data[DP_DPCD_REV - DP_DPCD_REV];

	अगर (dpcd_data[DP_MAX_LANE_COUNT - DP_DPCD_REV] == 0)
		वापस false;

	ds_port.byte = dpcd_data[DP_DOWNSTREAMPORT_PRESENT -
			DP_DPCD_REV];

	get_active_converter_info(ds_port.byte, link);

	करोwn_strm_port_count.raw = dpcd_data[DP_DOWN_STREAM_PORT_COUNT -
			DP_DPCD_REV];

	link->dpcd_caps.allow_invalid_MSA_timing_param =
		करोwn_strm_port_count.bits.IGNORE_MSA_TIMING_PARAM;

	link->dpcd_caps.max_ln_count.raw = dpcd_data[
		DP_MAX_LANE_COUNT - DP_DPCD_REV];

	link->dpcd_caps.max_करोwn_spपढ़ो.raw = dpcd_data[
		DP_MAX_DOWNSPREAD - DP_DPCD_REV];

	link->reported_link_cap.lane_count =
		link->dpcd_caps.max_ln_count.bits.MAX_LANE_COUNT;
	link->reported_link_cap.link_rate = dpcd_data[
		DP_MAX_LINK_RATE - DP_DPCD_REV];
	link->reported_link_cap.link_spपढ़ो =
		link->dpcd_caps.max_करोwn_spपढ़ो.bits.MAX_DOWN_SPREAD ?
		LINK_SPREAD_05_DOWNSPREAD_30KHZ : LINK_SPREAD_DISABLED;

	edp_config_cap.raw = dpcd_data[
		DP_EDP_CONFIGURATION_CAP - DP_DPCD_REV];
	link->dpcd_caps.panel_mode_edp =
		edp_config_cap.bits.ALT_SCRAMBLER_RESET;
	link->dpcd_caps.dpcd_display_control_capable =
		edp_config_cap.bits.DPCD_DISPLAY_CONTROL_CAPABLE;

	वापस true;
पूर्ण

bool detect_dp_sink_caps(काष्ठा dc_link *link)
अणु
	वापस retrieve_link_cap(link);

	/* dc init_hw has घातer encoder using शेष
	 * संकेत क्रम connector. For native DP, no
	 * need to घातer up encoder again. If not native
	 * DP, hw_init may need check संकेत or घातer up
	 * encoder here.
	 */
	/* TODO save sink caps in link->sink */
पूर्ण

अटल क्रमागत dc_link_rate linkRateInKHzToLinkRateMultiplier(uपूर्णांक32_t link_rate_in_khz)
अणु
	क्रमागत dc_link_rate link_rate;
	// LinkRate is normally stored as a multiplier of 0.27 Gbps per lane. Do the translation.
	चयन (link_rate_in_khz) अणु
	हाल 1620000:
		link_rate = LINK_RATE_LOW;		// Rate_1 (RBR)		- 1.62 Gbps/Lane
		अवरोध;
	हाल 2160000:
		link_rate = LINK_RATE_RATE_2;	// Rate_2			- 2.16 Gbps/Lane
		अवरोध;
	हाल 2430000:
		link_rate = LINK_RATE_RATE_3;	// Rate_3			- 2.43 Gbps/Lane
		अवरोध;
	हाल 2700000:
		link_rate = LINK_RATE_HIGH;		// Rate_4 (HBR)		- 2.70 Gbps/Lane
		अवरोध;
	हाल 3240000:
		link_rate = LINK_RATE_RBR2;		// Rate_5 (RBR2)	- 3.24 Gbps/Lane
		अवरोध;
	हाल 4320000:
		link_rate = LINK_RATE_RATE_6;	// Rate_6			- 4.32 Gbps/Lane
		अवरोध;
	हाल 5400000:
		link_rate = LINK_RATE_HIGH2;	// Rate_7 (HBR2)	- 5.40 Gbps/Lane
		अवरोध;
	हाल 8100000:
		link_rate = LINK_RATE_HIGH3;	// Rate_8 (HBR3)	- 8.10 Gbps/Lane
		अवरोध;
	शेष:
		link_rate = LINK_RATE_UNKNOWN;
		अवरोध;
	पूर्ण
	वापस link_rate;
पूर्ण

व्योम detect_edp_sink_caps(काष्ठा dc_link *link)
अणु
	uपूर्णांक8_t supported_link_rates[16];
	uपूर्णांक32_t entry;
	uपूर्णांक32_t link_rate_in_khz;
	क्रमागत dc_link_rate link_rate = LINK_RATE_UNKNOWN;
	uपूर्णांक8_t backlight_adj_cap;

	retrieve_link_cap(link);
	link->dpcd_caps.edp_supported_link_rates_count = 0;
	स_रखो(supported_link_rates, 0, माप(supported_link_rates));

	अगर (link->dpcd_caps.dpcd_rev.raw >= DPCD_REV_14 &&
			(link->dc->debug.optimize_edp_link_rate ||
			link->reported_link_cap.link_rate == LINK_RATE_UNKNOWN)) अणु
		// Read DPCD 00010h - 0001Fh 16 bytes at one shot
		core_link_पढ़ो_dpcd(link, DP_SUPPORTED_LINK_RATES,
							supported_link_rates, माप(supported_link_rates));

		क्रम (entry = 0; entry < 16; entry += 2) अणु
			// DPCD रेजिस्टर reports per-lane link rate = 16-bit link rate capability
			// value X 200 kHz. Need multiplier to find link rate in kHz.
			link_rate_in_khz = (supported_link_rates[entry+1] * 0x100 +
										supported_link_rates[entry]) * 200;

			अगर (link_rate_in_khz != 0) अणु
				link_rate = linkRateInKHzToLinkRateMultiplier(link_rate_in_khz);
				link->dpcd_caps.edp_supported_link_rates[link->dpcd_caps.edp_supported_link_rates_count] = link_rate;
				link->dpcd_caps.edp_supported_link_rates_count++;

				अगर (link->reported_link_cap.link_rate < link_rate)
					link->reported_link_cap.link_rate = link_rate;
			पूर्ण
		पूर्ण
	पूर्ण
	link->verअगरied_link_cap = link->reported_link_cap;

	core_link_पढ़ो_dpcd(link, DP_EDP_BACKLIGHT_ADJUSTMENT_CAP,
						&backlight_adj_cap, माप(backlight_adj_cap));

	link->dpcd_caps.dynamic_backlight_capable_edp =
				(backlight_adj_cap & DP_EDP_DYNAMIC_BACKLIGHT_CAP) ? true:false;

	dc_link_set_शेष_brightness_aux(link);
पूर्ण

व्योम dc_link_dp_enable_hpd(स्थिर काष्ठा dc_link *link)
अणु
	काष्ठा link_encoder *encoder = link->link_enc;

	अगर (encoder != शून्य && encoder->funcs->enable_hpd != शून्य)
		encoder->funcs->enable_hpd(encoder);
पूर्ण

व्योम dc_link_dp_disable_hpd(स्थिर काष्ठा dc_link *link)
अणु
	काष्ठा link_encoder *encoder = link->link_enc;

	अगर (encoder != शून्य && encoder->funcs->enable_hpd != शून्य)
		encoder->funcs->disable_hpd(encoder);
पूर्ण

अटल bool is_dp_phy_pattern(क्रमागत dp_test_pattern test_pattern)
अणु
	अगर ((DP_TEST_PATTERN_PHY_PATTERN_BEGIN <= test_pattern &&
			test_pattern <= DP_TEST_PATTERN_PHY_PATTERN_END) ||
			test_pattern == DP_TEST_PATTERN_VIDEO_MODE)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल व्योम set_crtc_test_pattern(काष्ठा dc_link *link,
				काष्ठा pipe_ctx *pipe_ctx,
				क्रमागत dp_test_pattern test_pattern,
				क्रमागत dp_test_pattern_color_space test_pattern_color_space)
अणु
	क्रमागत controller_dp_test_pattern controller_test_pattern;
	क्रमागत dc_color_depth color_depth = pipe_ctx->
		stream->timing.display_color_depth;
	काष्ठा bit_depth_reduction_params params;
	काष्ठा output_pixel_processor *opp = pipe_ctx->stream_res.opp;
	पूर्णांक width = pipe_ctx->stream->timing.h_addressable +
		pipe_ctx->stream->timing.h_border_left +
		pipe_ctx->stream->timing.h_border_right;
	पूर्णांक height = pipe_ctx->stream->timing.v_addressable +
		pipe_ctx->stream->timing.v_border_bottom +
		pipe_ctx->stream->timing.v_border_top;

	स_रखो(&params, 0, माप(params));

	चयन (test_pattern) अणु
	हाल DP_TEST_PATTERN_COLOR_SQUARES:
		controller_test_pattern =
				CONTROLLER_DP_TEST_PATTERN_COLORSQUARES;
	अवरोध;
	हाल DP_TEST_PATTERN_COLOR_SQUARES_CEA:
		controller_test_pattern =
				CONTROLLER_DP_TEST_PATTERN_COLORSQUARES_CEA;
	अवरोध;
	हाल DP_TEST_PATTERN_VERTICAL_BARS:
		controller_test_pattern =
				CONTROLLER_DP_TEST_PATTERN_VERTICALBARS;
	अवरोध;
	हाल DP_TEST_PATTERN_HORIZONTAL_BARS:
		controller_test_pattern =
				CONTROLLER_DP_TEST_PATTERN_HORIZONTALBARS;
	अवरोध;
	हाल DP_TEST_PATTERN_COLOR_RAMP:
		controller_test_pattern =
				CONTROLLER_DP_TEST_PATTERN_COLORRAMP;
	अवरोध;
	शेष:
		controller_test_pattern =
				CONTROLLER_DP_TEST_PATTERN_VIDEOMODE;
	अवरोध;
	पूर्ण

	चयन (test_pattern) अणु
	हाल DP_TEST_PATTERN_COLOR_SQUARES:
	हाल DP_TEST_PATTERN_COLOR_SQUARES_CEA:
	हाल DP_TEST_PATTERN_VERTICAL_BARS:
	हाल DP_TEST_PATTERN_HORIZONTAL_BARS:
	हाल DP_TEST_PATTERN_COLOR_RAMP:
	अणु
		/* disable bit depth reduction */
		pipe_ctx->stream->bit_depth_params = params;
		opp->funcs->opp_program_bit_depth_reduction(opp, &params);
		अगर (pipe_ctx->stream_res.tg->funcs->set_test_pattern)
			pipe_ctx->stream_res.tg->funcs->set_test_pattern(pipe_ctx->stream_res.tg,
				controller_test_pattern, color_depth);
		अन्यथा अगर (link->dc->hwss.set_disp_pattern_generator) अणु
			काष्ठा pipe_ctx *odm_pipe;
			क्रमागत controller_dp_color_space controller_color_space;
			पूर्णांक opp_cnt = 1;
			पूर्णांक offset = 0;
			पूर्णांक dpg_width = width;

			चयन (test_pattern_color_space) अणु
			हाल DP_TEST_PATTERN_COLOR_SPACE_RGB:
				controller_color_space = CONTROLLER_DP_COLOR_SPACE_RGB;
				अवरोध;
			हाल DP_TEST_PATTERN_COLOR_SPACE_YCBCR601:
				controller_color_space = CONTROLLER_DP_COLOR_SPACE_YCBCR601;
				अवरोध;
			हाल DP_TEST_PATTERN_COLOR_SPACE_YCBCR709:
				controller_color_space = CONTROLLER_DP_COLOR_SPACE_YCBCR709;
				अवरोध;
			हाल DP_TEST_PATTERN_COLOR_SPACE_UNDEFINED:
			शेष:
				controller_color_space = CONTROLLER_DP_COLOR_SPACE_UDEFINED;
				DC_LOG_ERROR("%s: Color space must be defined for test pattern", __func__);
				ASSERT(0);
				अवरोध;
			पूर्ण

			क्रम (odm_pipe = pipe_ctx->next_odm_pipe; odm_pipe; odm_pipe = odm_pipe->next_odm_pipe)
				opp_cnt++;
			dpg_width = width / opp_cnt;
			offset = dpg_width;

			link->dc->hwss.set_disp_pattern_generator(link->dc,
					pipe_ctx,
					controller_test_pattern,
					controller_color_space,
					color_depth,
					शून्य,
					dpg_width,
					height,
					0);

			क्रम (odm_pipe = pipe_ctx->next_odm_pipe; odm_pipe; odm_pipe = odm_pipe->next_odm_pipe) अणु
				काष्ठा output_pixel_processor *odm_opp = odm_pipe->stream_res.opp;

				odm_opp->funcs->opp_program_bit_depth_reduction(odm_opp, &params);
				link->dc->hwss.set_disp_pattern_generator(link->dc,
						odm_pipe,
						controller_test_pattern,
						controller_color_space,
						color_depth,
						शून्य,
						dpg_width,
						height,
						offset);
				offset += offset;
			पूर्ण
		पूर्ण
	पूर्ण
	अवरोध;
	हाल DP_TEST_PATTERN_VIDEO_MODE:
	अणु
		/* restore bitdepth reduction */
		resource_build_bit_depth_reduction_params(pipe_ctx->stream, &params);
		pipe_ctx->stream->bit_depth_params = params;
		opp->funcs->opp_program_bit_depth_reduction(opp, &params);
		अगर (pipe_ctx->stream_res.tg->funcs->set_test_pattern)
			pipe_ctx->stream_res.tg->funcs->set_test_pattern(pipe_ctx->stream_res.tg,
				CONTROLLER_DP_TEST_PATTERN_VIDEOMODE,
				color_depth);
		अन्यथा अगर (link->dc->hwss.set_disp_pattern_generator) अणु
			काष्ठा pipe_ctx *odm_pipe;
			पूर्णांक opp_cnt = 1;
			पूर्णांक dpg_width = width;

			क्रम (odm_pipe = pipe_ctx->next_odm_pipe; odm_pipe; odm_pipe = odm_pipe->next_odm_pipe)
				opp_cnt++;

			dpg_width = width / opp_cnt;
			क्रम (odm_pipe = pipe_ctx->next_odm_pipe; odm_pipe; odm_pipe = odm_pipe->next_odm_pipe) अणु
				काष्ठा output_pixel_processor *odm_opp = odm_pipe->stream_res.opp;

				odm_opp->funcs->opp_program_bit_depth_reduction(odm_opp, &params);
				link->dc->hwss.set_disp_pattern_generator(link->dc,
						odm_pipe,
						CONTROLLER_DP_TEST_PATTERN_VIDEOMODE,
						CONTROLLER_DP_COLOR_SPACE_UDEFINED,
						color_depth,
						शून्य,
						dpg_width,
						height,
						0);
			पूर्ण
			link->dc->hwss.set_disp_pattern_generator(link->dc,
					pipe_ctx,
					CONTROLLER_DP_TEST_PATTERN_VIDEOMODE,
					CONTROLLER_DP_COLOR_SPACE_UDEFINED,
					color_depth,
					शून्य,
					dpg_width,
					height,
					0);
		पूर्ण
	पूर्ण
	अवरोध;

	शेष:
	अवरोध;
	पूर्ण
पूर्ण

bool dc_link_dp_set_test_pattern(
	काष्ठा dc_link *link,
	क्रमागत dp_test_pattern test_pattern,
	क्रमागत dp_test_pattern_color_space test_pattern_color_space,
	स्थिर काष्ठा link_training_settings *p_link_settings,
	स्थिर अचिन्हित अक्षर *p_custom_pattern,
	अचिन्हित पूर्णांक cust_pattern_size)
अणु
	काष्ठा pipe_ctx *pipes = link->dc->current_state->res_ctx.pipe_ctx;
	काष्ठा pipe_ctx *pipe_ctx = शून्य;
	अचिन्हित पूर्णांक lane;
	अचिन्हित पूर्णांक i;
	अचिन्हित अक्षर link_qual_pattern[LANE_COUNT_DP_MAX] = अणु0पूर्ण;
	जोड़ dpcd_training_pattern training_pattern;
	क्रमागत dpcd_phy_test_patterns pattern;

	स_रखो(&training_pattern, 0, माप(training_pattern));

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		अगर (pipes[i].stream == शून्य)
			जारी;

		अगर (pipes[i].stream->link == link && !pipes[i].top_pipe && !pipes[i].prev_odm_pipe) अणु
			pipe_ctx = &pipes[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (pipe_ctx == शून्य)
		वापस false;

	/* Reset CRTC Test Pattern अगर it is currently running and request is VideoMode */
	अगर (link->test_pattern_enabled && test_pattern ==
			DP_TEST_PATTERN_VIDEO_MODE) अणु
		/* Set CRTC Test Pattern */
		set_crtc_test_pattern(link, pipe_ctx, test_pattern, test_pattern_color_space);
		dp_set_hw_test_pattern(link, test_pattern,
				(uपूर्णांक8_t *)p_custom_pattern,
				(uपूर्णांक32_t)cust_pattern_size);

		/* Unblank Stream */
		link->dc->hwss.unblank_stream(
			pipe_ctx,
			&link->verअगरied_link_cap);
		/* TODO:m_pHwss->MuteAudioEndpoपूर्णांक
		 * (pPathMode->pDisplayPath, false);
		 */

		/* Reset Test Pattern state */
		link->test_pattern_enabled = false;

		वापस true;
	पूर्ण

	/* Check क्रम PHY Test Patterns */
	अगर (is_dp_phy_pattern(test_pattern)) अणु
		/* Set DPCD Lane Settings beक्रमe running test pattern */
		अगर (p_link_settings != शून्य) अणु
			dp_set_hw_lane_settings(link, p_link_settings, DPRX);
			dpcd_set_lane_settings(link, p_link_settings, DPRX);
		पूर्ण

		/* Blank stream अगर running test pattern */
		अगर (test_pattern != DP_TEST_PATTERN_VIDEO_MODE) अणु
			/*TODO:
			 * m_pHwss->
			 * MuteAudioEndpoपूर्णांक(pPathMode->pDisplayPath, true);
			 */
			/* Blank stream */
			pipes->stream_res.stream_enc->funcs->dp_blank(pipe_ctx->stream_res.stream_enc);
		पूर्ण

		dp_set_hw_test_pattern(link, test_pattern,
				(uपूर्णांक8_t *)p_custom_pattern,
				(uपूर्णांक32_t)cust_pattern_size);

		अगर (test_pattern != DP_TEST_PATTERN_VIDEO_MODE) अणु
			/* Set Test Pattern state */
			link->test_pattern_enabled = true;
			अगर (p_link_settings != शून्य)
				dpcd_set_link_settings(link,
						p_link_settings);
		पूर्ण

		चयन (test_pattern) अणु
		हाल DP_TEST_PATTERN_VIDEO_MODE:
			pattern = PHY_TEST_PATTERN_NONE;
			अवरोध;
		हाल DP_TEST_PATTERN_D102:
			pattern = PHY_TEST_PATTERN_D10_2;
			अवरोध;
		हाल DP_TEST_PATTERN_SYMBOL_ERROR:
			pattern = PHY_TEST_PATTERN_SYMBOL_ERROR;
			अवरोध;
		हाल DP_TEST_PATTERN_PRBS7:
			pattern = PHY_TEST_PATTERN_PRBS7;
			अवरोध;
		हाल DP_TEST_PATTERN_80BIT_CUSTOM:
			pattern = PHY_TEST_PATTERN_80BIT_CUSTOM;
			अवरोध;
		हाल DP_TEST_PATTERN_CP2520_1:
			pattern = PHY_TEST_PATTERN_CP2520_1;
			अवरोध;
		हाल DP_TEST_PATTERN_CP2520_2:
			pattern = PHY_TEST_PATTERN_CP2520_2;
			अवरोध;
		हाल DP_TEST_PATTERN_CP2520_3:
			pattern = PHY_TEST_PATTERN_CP2520_3;
			अवरोध;
		शेष:
			वापस false;
		पूर्ण

		अगर (test_pattern == DP_TEST_PATTERN_VIDEO_MODE
		/*TODO:&& !pPathMode->pDisplayPath->IsTargetPoweredOn()*/)
			वापस false;

		अगर (link->dpcd_caps.dpcd_rev.raw >= DPCD_REV_12) अणु
			/* tell receiver that we are sending qualअगरication
			 * pattern DP 1.2 or later - DP receiver's link quality
			 * pattern is set using DPCD LINK_QUAL_LANEx_SET
			 * रेजिस्टर (0x10B~0x10E)\
			 */
			क्रम (lane = 0; lane < LANE_COUNT_DP_MAX; lane++)
				link_qual_pattern[lane] =
						(अचिन्हित अक्षर)(pattern);

			core_link_ग_लिखो_dpcd(link,
					DP_LINK_QUAL_LANE0_SET,
					link_qual_pattern,
					माप(link_qual_pattern));
		पूर्ण अन्यथा अगर (link->dpcd_caps.dpcd_rev.raw >= DPCD_REV_10 ||
			   link->dpcd_caps.dpcd_rev.raw == 0) अणु
			/* tell receiver that we are sending qualअगरication
			 * pattern DP 1.1a or earlier - DP receiver's link
			 * quality pattern is set using
			 * DPCD TRAINING_PATTERN_SET -> LINK_QUAL_PATTERN_SET
			 * रेजिस्टर (0x102). We will use v_1.3 when we are
			 * setting test pattern क्रम DP 1.1.
			 */
			core_link_पढ़ो_dpcd(link, DP_TRAINING_PATTERN_SET,
					    &training_pattern.raw,
					    माप(training_pattern));
			training_pattern.v1_3.LINK_QUAL_PATTERN_SET = pattern;
			core_link_ग_लिखो_dpcd(link, DP_TRAINING_PATTERN_SET,
					     &training_pattern.raw,
					     माप(training_pattern));
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रमागत dc_color_space color_space = COLOR_SPACE_UNKNOWN;

		चयन (test_pattern_color_space) अणु
		हाल DP_TEST_PATTERN_COLOR_SPACE_RGB:
			color_space = COLOR_SPACE_SRGB;
			अगर (test_pattern == DP_TEST_PATTERN_COLOR_SQUARES_CEA)
				color_space = COLOR_SPACE_SRGB_LIMITED;
			अवरोध;

		हाल DP_TEST_PATTERN_COLOR_SPACE_YCBCR601:
			color_space = COLOR_SPACE_YCBCR601;
			अगर (test_pattern == DP_TEST_PATTERN_COLOR_SQUARES_CEA)
				color_space = COLOR_SPACE_YCBCR601_LIMITED;
			अवरोध;
		हाल DP_TEST_PATTERN_COLOR_SPACE_YCBCR709:
			color_space = COLOR_SPACE_YCBCR709;
			अगर (test_pattern == DP_TEST_PATTERN_COLOR_SQUARES_CEA)
				color_space = COLOR_SPACE_YCBCR709_LIMITED;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अगर (pipe_ctx->stream_res.tg->funcs->lock_द्विगुनbuffer_enable) अणु
			अगर (pipe_ctx->stream && should_use_dmub_lock(pipe_ctx->stream->link)) अणु
				जोड़ dmub_hw_lock_flags hw_locks = अणु 0 पूर्ण;
				काष्ठा dmub_hw_lock_inst_flags inst_flags = अणु 0 पूर्ण;

				hw_locks.bits.lock_dig = 1;
				inst_flags.dig_inst = pipe_ctx->stream_res.tg->inst;

				dmub_hw_lock_mgr_cmd(link->ctx->dmub_srv,
							true,
							&hw_locks,
							&inst_flags);
			पूर्ण अन्यथा
				pipe_ctx->stream_res.tg->funcs->lock_द्विगुनbuffer_enable(
						pipe_ctx->stream_res.tg);
		पूर्ण

		pipe_ctx->stream_res.tg->funcs->lock(pipe_ctx->stream_res.tg);
		/* update MSA to requested color space */
		pipe_ctx->stream_res.stream_enc->funcs->dp_set_stream_attribute(pipe_ctx->stream_res.stream_enc,
				&pipe_ctx->stream->timing,
				color_space,
				pipe_ctx->stream->use_vsc_sdp_क्रम_colorimetry,
				link->dpcd_caps.dprx_feature.bits.SST_SPLIT_SDP_CAP);

		अगर (pipe_ctx->stream->use_vsc_sdp_क्रम_colorimetry) अणु
			अगर (test_pattern == DP_TEST_PATTERN_COLOR_SQUARES_CEA)
				pipe_ctx->stream->vsc_infopacket.sb[17] |= (1 << 7); // sb17 bit 7 Dynamic Range: 0 = VESA range, 1 = CTA range
			अन्यथा
				pipe_ctx->stream->vsc_infopacket.sb[17] &= ~(1 << 7);
			resource_build_info_frame(pipe_ctx);
			link->dc->hwss.update_info_frame(pipe_ctx);
		पूर्ण

		/* CRTC Patterns */
		set_crtc_test_pattern(link, pipe_ctx, test_pattern, test_pattern_color_space);
		pipe_ctx->stream_res.tg->funcs->unlock(pipe_ctx->stream_res.tg);
		pipe_ctx->stream_res.tg->funcs->रुको_क्रम_state(pipe_ctx->stream_res.tg,
				CRTC_STATE_VACTIVE);
		pipe_ctx->stream_res.tg->funcs->रुको_क्रम_state(pipe_ctx->stream_res.tg,
				CRTC_STATE_VBLANK);
		pipe_ctx->stream_res.tg->funcs->रुको_क्रम_state(pipe_ctx->stream_res.tg,
				CRTC_STATE_VACTIVE);

		अगर (pipe_ctx->stream_res.tg->funcs->lock_द्विगुनbuffer_disable) अणु
			अगर (pipe_ctx->stream && should_use_dmub_lock(pipe_ctx->stream->link)) अणु
				जोड़ dmub_hw_lock_flags hw_locks = अणु 0 पूर्ण;
				काष्ठा dmub_hw_lock_inst_flags inst_flags = अणु 0 पूर्ण;

				hw_locks.bits.lock_dig = 1;
				inst_flags.dig_inst = pipe_ctx->stream_res.tg->inst;

				dmub_hw_lock_mgr_cmd(link->ctx->dmub_srv,
							false,
							&hw_locks,
							&inst_flags);
			पूर्ण अन्यथा
				pipe_ctx->stream_res.tg->funcs->lock_द्विगुनbuffer_disable(
						pipe_ctx->stream_res.tg);
		पूर्ण

		/* Set Test Pattern state */
		link->test_pattern_enabled = true;
	पूर्ण

	वापस true;
पूर्ण

व्योम dp_enable_mst_on_sink(काष्ठा dc_link *link, bool enable)
अणु
	अचिन्हित अक्षर msपंचांगCntl;

	core_link_पढ़ो_dpcd(link, DP_MSTM_CTRL, &msपंचांगCntl, 1);
	अगर (enable)
		msपंचांगCntl |= DP_MST_EN;
	अन्यथा
		msपंचांगCntl &= (~DP_MST_EN);

	core_link_ग_लिखो_dpcd(link, DP_MSTM_CTRL, &msपंचांगCntl, 1);
पूर्ण

व्योम dp_set_panel_mode(काष्ठा dc_link *link, क्रमागत dp_panel_mode panel_mode)
अणु
	जोड़ dpcd_edp_config edp_config_set;
	bool panel_mode_edp = false;

	स_रखो(&edp_config_set, '\0', माप(जोड़ dpcd_edp_config));

	अगर (panel_mode != DP_PANEL_MODE_DEFAULT) अणु

		चयन (panel_mode) अणु
		हाल DP_PANEL_MODE_EDP:
		हाल DP_PANEL_MODE_SPECIAL:
			panel_mode_edp = true;
			अवरोध;

		शेष:
				अवरोध;
		पूर्ण

		/*set edp panel mode in receiver*/
		core_link_पढ़ो_dpcd(
			link,
			DP_EDP_CONFIGURATION_SET,
			&edp_config_set.raw,
			माप(edp_config_set.raw));

		अगर (edp_config_set.bits.PANEL_MODE_EDP
			!= panel_mode_edp) अणु
			क्रमागत dc_status result;

			edp_config_set.bits.PANEL_MODE_EDP =
			panel_mode_edp;
			result = core_link_ग_लिखो_dpcd(
				link,
				DP_EDP_CONFIGURATION_SET,
				&edp_config_set.raw,
				माप(edp_config_set.raw));

			ASSERT(result == DC_OK);
		पूर्ण
	पूर्ण
	DC_LOG_DETECTION_DP_CAPS("Link: %d eDP panel mode supported: %d "
		 "eDP panel mode enabled: %d \n",
		 link->link_index,
		 link->dpcd_caps.panel_mode_edp,
		 panel_mode_edp);
पूर्ण

क्रमागत dp_panel_mode dp_get_panel_mode(काष्ठा dc_link *link)
अणु
	/* We need to explicitly check that connector
	 * is not DP. Some Travis_VGA get reported
	 * by video bios as DP.
	 */
	अगर (link->connector_संकेत != SIGNAL_TYPE_DISPLAY_PORT) अणु

		चयन (link->dpcd_caps.branch_dev_id) अणु
		हाल DP_BRANCH_DEVICE_ID_0022B9:
			/* alternate scrambler reset is required क्रम Travis
			 * क्रम the हाल when बाह्यal chip करोes not
			 * provide sink device id, alternate scrambler
			 * scheme will  be overriden later by querying
			 * Encoder features
			 */
			अगर (म_भेदन(
				link->dpcd_caps.branch_dev_name,
				DP_VGA_LVDS_CONVERTER_ID_2,
				माप(
				link->dpcd_caps.
				branch_dev_name)) == 0) अणु
					वापस DP_PANEL_MODE_SPECIAL;
			पूर्ण
			अवरोध;
		हाल DP_BRANCH_DEVICE_ID_00001A:
			/* alternate scrambler reset is required क्रम Travis
			 * क्रम the हाल when बाह्यal chip करोes not provide
			 * sink device id, alternate scrambler scheme will
			 * be overriden later by querying Encoder feature
			 */
			अगर (म_भेदन(link->dpcd_caps.branch_dev_name,
				DP_VGA_LVDS_CONVERTER_ID_3,
				माप(
				link->dpcd_caps.
				branch_dev_name)) == 0) अणु
					वापस DP_PANEL_MODE_SPECIAL;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (link->dpcd_caps.panel_mode_edp) अणु
		वापस DP_PANEL_MODE_EDP;
	पूर्ण

	वापस DP_PANEL_MODE_DEFAULT;
पूर्ण

व्योम dp_set_fec_पढ़ोy(काष्ठा dc_link *link, bool पढ़ोy)
अणु
	/* FEC has to be "set ready" beक्रमe the link training.
	 * The policy is to always train with FEC
	 * अगर the sink supports it and leave it enabled on link.
	 * If FEC is not supported, disable it.
	 */
	काष्ठा link_encoder *link_enc = link->link_enc;
	uपूर्णांक8_t fec_config = 0;

	अगर (!dc_link_should_enable_fec(link))
		वापस;

	अगर (link_enc->funcs->fec_set_पढ़ोy &&
			link->dpcd_caps.fec_cap.bits.FEC_CAPABLE) अणु
		अगर (पढ़ोy) अणु
			fec_config = 1;
			अगर (core_link_ग_लिखो_dpcd(link,
					DP_FEC_CONFIGURATION,
					&fec_config,
					माप(fec_config)) == DC_OK) अणु
				link_enc->funcs->fec_set_पढ़ोy(link_enc, true);
				link->fec_state = dc_link_fec_पढ़ोy;
			पूर्ण अन्यथा अणु
				link->link_enc->funcs->fec_set_पढ़ोy(link->link_enc, false);
				link->fec_state = dc_link_fec_not_पढ़ोy;
				dm_error("dpcd write failed to set fec_ready");
			पूर्ण
		पूर्ण अन्यथा अगर (link->fec_state == dc_link_fec_पढ़ोy) अणु
			fec_config = 0;
			core_link_ग_लिखो_dpcd(link,
					DP_FEC_CONFIGURATION,
					&fec_config,
					माप(fec_config));
			link->link_enc->funcs->fec_set_पढ़ोy(
					link->link_enc, false);
			link->fec_state = dc_link_fec_not_पढ़ोy;
		पूर्ण
	पूर्ण
पूर्ण

व्योम dp_set_fec_enable(काष्ठा dc_link *link, bool enable)
अणु
	काष्ठा link_encoder *link_enc = link->link_enc;

	अगर (!dc_link_should_enable_fec(link))
		वापस;

	अगर (link_enc->funcs->fec_set_enable &&
			link->dpcd_caps.fec_cap.bits.FEC_CAPABLE) अणु
		अगर (link->fec_state == dc_link_fec_पढ़ोy && enable) अणु
			/* Accord to DP spec, FEC enable sequence can first
			 * be transmitted anyसमय after 1000 LL codes have
			 * been transmitted on the link after link training
			 * completion. Using 1 lane RBR should have the maximum
			 * समय क्रम transmitting 1000 LL codes which is 6.173 us.
			 * So use 7 microseconds delay instead.
			 */
			udelay(7);
			link_enc->funcs->fec_set_enable(link_enc, true);
			link->fec_state = dc_link_fec_enabled;
		पूर्ण अन्यथा अगर (link->fec_state == dc_link_fec_enabled && !enable) अणु
			link_enc->funcs->fec_set_enable(link_enc, false);
			link->fec_state = dc_link_fec_पढ़ोy;
		पूर्ण
	पूर्ण
पूर्ण

व्योम dpcd_set_source_specअगरic_data(काष्ठा dc_link *link)
अणु
	अगर (!link->dc->venकरोr_signature.is_valid) अणु
		क्रमागत dc_status __maybe_unused result_ग_लिखो_min_hblank = DC_NOT_SUPPORTED;
		काष्ठा dpcd_amd_signature amd_signature = अणु0पूर्ण;
		काष्ठा dpcd_amd_device_id amd_device_id = अणु0पूर्ण;

		amd_device_id.device_id_byte1 =
				(uपूर्णांक8_t)(link->ctx->asic_id.chip_id);
		amd_device_id.device_id_byte2 =
				(uपूर्णांक8_t)(link->ctx->asic_id.chip_id >> 8);
		amd_device_id.dce_version =
				(uपूर्णांक8_t)(link->ctx->dce_version);
		amd_device_id.dal_version_byte1 = 0x0; // needed? where to get?
		amd_device_id.dal_version_byte2 = 0x0; // needed? where to get?

		core_link_पढ़ो_dpcd(link, DP_SOURCE_OUI,
				(uपूर्णांक8_t *)(&amd_signature),
				माप(amd_signature));

		अगर (!((amd_signature.AMD_IEEE_TxSignature_byte1 == 0x0) &&
			(amd_signature.AMD_IEEE_TxSignature_byte2 == 0x0) &&
			(amd_signature.AMD_IEEE_TxSignature_byte3 == 0x1A))) अणु

			amd_signature.AMD_IEEE_TxSignature_byte1 = 0x0;
			amd_signature.AMD_IEEE_TxSignature_byte2 = 0x0;
			amd_signature.AMD_IEEE_TxSignature_byte3 = 0x1A;

			core_link_ग_लिखो_dpcd(link, DP_SOURCE_OUI,
				(uपूर्णांक8_t *)(&amd_signature),
				माप(amd_signature));
		पूर्ण

		core_link_ग_लिखो_dpcd(link, DP_SOURCE_OUI+0x03,
				(uपूर्णांक8_t *)(&amd_device_id),
				माप(amd_device_id));

		अगर (link->ctx->dce_version >= DCN_VERSION_2_0 &&
			link->dc->caps.min_horizontal_blanking_period != 0) अणु

			uपूर्णांक8_t hblank_size = (uपूर्णांक8_t)link->dc->caps.min_horizontal_blanking_period;

			result_ग_लिखो_min_hblank = core_link_ग_लिखो_dpcd(link,
				DP_SOURCE_MINIMUM_HBLANK_SUPPORTED, (uपूर्णांक8_t *)(&hblank_size),
				माप(hblank_size));
		पूर्ण
		DC_TRACE_LEVEL_MESSAGE(DAL_TRACE_LEVEL_INFORMATION,
							WPP_BIT_FLAG_DC_DETECTION_DP_CAPS,
							"result=%u link_index=%u enum dce_version=%d DPCD=0x%04X min_hblank=%u branch_dev_id=0x%x branch_dev_name='%c%c%c%c%c%c'",
							result_ग_लिखो_min_hblank,
							link->link_index,
							link->ctx->dce_version,
							DP_SOURCE_MINIMUM_HBLANK_SUPPORTED,
							link->dc->caps.min_horizontal_blanking_period,
							link->dpcd_caps.branch_dev_id,
							link->dpcd_caps.branch_dev_name[0],
							link->dpcd_caps.branch_dev_name[1],
							link->dpcd_caps.branch_dev_name[2],
							link->dpcd_caps.branch_dev_name[3],
							link->dpcd_caps.branch_dev_name[4],
							link->dpcd_caps.branch_dev_name[5]);
	पूर्ण अन्यथा अणु
		core_link_ग_लिखो_dpcd(link, DP_SOURCE_OUI,
				link->dc->venकरोr_signature.data.raw,
				माप(link->dc->venकरोr_signature.data.raw));
	पूर्ण
पूर्ण

bool dc_link_set_backlight_level_nits(काष्ठा dc_link *link,
		bool isHDR,
		uपूर्णांक32_t backlight_millinits,
		uपूर्णांक32_t transition_समय_in_ms)
अणु
	काष्ठा dpcd_source_backlight_set dpcd_backlight_set;
	uपूर्णांक8_t backlight_control = isHDR ? 1 : 0;

	अगर (!link || (link->connector_संकेत != SIGNAL_TYPE_EDP &&
			link->connector_संकेत != SIGNAL_TYPE_DISPLAY_PORT))
		वापस false;

	// OLEDs have no PWM, they can only use AUX
	अगर (link->dpcd_sink_ext_caps.bits.oled == 1)
		backlight_control = 1;

	*(uपूर्णांक32_t *)&dpcd_backlight_set.backlight_level_millinits = backlight_millinits;
	*(uपूर्णांक16_t *)&dpcd_backlight_set.backlight_transition_समय_ms = (uपूर्णांक16_t)transition_समय_in_ms;


	अगर (core_link_ग_लिखो_dpcd(link, DP_SOURCE_BACKLIGHT_LEVEL,
			(uपूर्णांक8_t *)(&dpcd_backlight_set),
			माप(dpcd_backlight_set)) != DC_OK)
		वापस false;

	अगर (core_link_ग_लिखो_dpcd(link, DP_SOURCE_BACKLIGHT_CONTROL,
			&backlight_control, 1) != DC_OK)
		वापस false;

	वापस true;
पूर्ण

bool dc_link_get_backlight_level_nits(काष्ठा dc_link *link,
		uपूर्णांक32_t *backlight_millinits_avg,
		uपूर्णांक32_t *backlight_millinits_peak)
अणु
	जोड़ dpcd_source_backlight_get dpcd_backlight_get;

	स_रखो(&dpcd_backlight_get, 0, माप(जोड़ dpcd_source_backlight_get));

	अगर (!link || (link->connector_संकेत != SIGNAL_TYPE_EDP &&
			link->connector_संकेत != SIGNAL_TYPE_DISPLAY_PORT))
		वापस false;

	अगर (core_link_पढ़ो_dpcd(link, DP_SOURCE_BACKLIGHT_CURRENT_PEAK,
			dpcd_backlight_get.raw,
			माप(जोड़ dpcd_source_backlight_get)) != DC_OK)
		वापस false;

	*backlight_millinits_avg =
		dpcd_backlight_get.bytes.backlight_millinits_avg;
	*backlight_millinits_peak =
		dpcd_backlight_get.bytes.backlight_millinits_peak;

	/* On non-supported panels dpcd_पढ़ो usually succeeds with 0 वापसed */
	अगर (*backlight_millinits_avg == 0 ||
			*backlight_millinits_avg > *backlight_millinits_peak)
		वापस false;

	वापस true;
पूर्ण

bool dc_link_backlight_enable_aux(काष्ठा dc_link *link, bool enable)
अणु
	uपूर्णांक8_t backlight_enable = enable ? 1 : 0;

	अगर (!link || (link->connector_संकेत != SIGNAL_TYPE_EDP &&
		link->connector_संकेत != SIGNAL_TYPE_DISPLAY_PORT))
		वापस false;

	अगर (core_link_ग_लिखो_dpcd(link, DP_SOURCE_BACKLIGHT_ENABLE,
		&backlight_enable, 1) != DC_OK)
		वापस false;

	वापस true;
पूर्ण

// we पढ़ो शेष from 0x320 because we expect BIOS wrote it there
// regular get_backlight_nit पढ़ोs from panel set at 0x326
bool dc_link_पढ़ो_शेष_bl_aux(काष्ठा dc_link *link, uपूर्णांक32_t *backlight_millinits)
अणु
	अगर (!link || (link->connector_संकेत != SIGNAL_TYPE_EDP &&
		link->connector_संकेत != SIGNAL_TYPE_DISPLAY_PORT))
		वापस false;

	अगर (core_link_पढ़ो_dpcd(link, DP_SOURCE_BACKLIGHT_LEVEL,
		(uपूर्णांक8_t *) backlight_millinits,
		माप(uपूर्णांक32_t)) != DC_OK)
		वापस false;

	वापस true;
पूर्ण

bool dc_link_set_शेष_brightness_aux(काष्ठा dc_link *link)
अणु
	uपूर्णांक32_t शेष_backlight;

	अगर (link &&
		(link->dpcd_sink_ext_caps.bits.hdr_aux_backlight_control == 1 ||
		link->dpcd_sink_ext_caps.bits.sdr_aux_backlight_control == 1)) अणु
		अगर (!dc_link_पढ़ो_शेष_bl_aux(link, &शेष_backlight))
			शेष_backlight = 150000;
		// अगर < 5 nits or > 5000, it might be wrong पढ़ोback
		अगर (शेष_backlight < 5000 || शेष_backlight > 5000000)
			शेष_backlight = 150000; //

		वापस dc_link_set_backlight_level_nits(link, true,
				शेष_backlight, 0);
	पूर्ण
	वापस false;
पूर्ण

bool is_edp_ilr_optimization_required(काष्ठा dc_link *link, काष्ठा dc_crtc_timing *crtc_timing)
अणु
	काष्ठा dc_link_settings link_setting;
	uपूर्णांक8_t link_bw_set;
	uपूर्णांक8_t link_rate_set;
	uपूर्णांक32_t req_bw;
	जोड़ lane_count_set lane_count_set = अणु अणु0पूर्ण पूर्ण;

	ASSERT(link || crtc_timing); // invalid input

	अगर (link->dpcd_caps.edp_supported_link_rates_count == 0 ||
			!link->dc->debug.optimize_edp_link_rate)
		वापस false;


	// Read DPCD 00100h to find अगर standard link rates are set
	core_link_पढ़ो_dpcd(link, DP_LINK_BW_SET,
				&link_bw_set, माप(link_bw_set));

	अगर (link_bw_set) अणु
		DC_LOG_EVENT_LINK_TRAINING("eDP ILR: Optimization required, VBIOS used link_bw_set\n");
		वापस true;
	पूर्ण

	// Read DPCD 00115h to find the edp link rate set used
	core_link_पढ़ो_dpcd(link, DP_LINK_RATE_SET,
			    &link_rate_set, माप(link_rate_set));

	// Read DPCD 00101h to find out the number of lanes currently set
	core_link_पढ़ो_dpcd(link, DP_LANE_COUNT_SET,
				&lane_count_set.raw, माप(lane_count_set));

	req_bw = dc_bandwidth_in_kbps_from_timing(crtc_timing);

	decide_edp_link_settings(link, &link_setting, req_bw);

	अगर (link->dpcd_caps.edp_supported_link_rates[link_rate_set] != link_setting.link_rate ||
			lane_count_set.bits.LANE_COUNT_SET != link_setting.lane_count) अणु
		DC_LOG_EVENT_LINK_TRAINING("eDP ILR: Optimization required, VBIOS link_rate_set not optimal\n");
		वापस true;
	पूर्ण

	DC_LOG_EVENT_LINK_TRAINING("eDP ILR: No optimization required, VBIOS set optimal link_rate_set\n");
	वापस false;
पूर्ण


