<शैली गुरु>
/*
 * Copyright 2012-14 Advanced Micro Devices, Inc.
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
 *
 * Authors: AMD
 *
 */

#अगर_अघोषित DC_LINK_H_
#घोषणा DC_LINK_H_

#समावेश "dc.h"
#समावेश "dc_types.h"
#समावेश "grph_object_defs.h"

क्रमागत dc_link_fec_state अणु
	dc_link_fec_not_पढ़ोy,
	dc_link_fec_पढ़ोy,
	dc_link_fec_enabled
पूर्ण;

क्रमागत lttpr_mode अणु
	LTTPR_MODE_NON_LTTPR,
	LTTPR_MODE_TRANSPARENT,
	LTTPR_MODE_NON_TRANSPARENT,
पूर्ण;

काष्ठा dc_link_status अणु
	bool link_active;
	काष्ठा dpcd_caps *dpcd_caps;
पूर्ण;

/* DP MST stream allocation (payload bandwidth number) */
काष्ठा link_mst_stream_allocation अणु
	/* DIG front */
	स्थिर काष्ठा stream_encoder *stream_enc;
	/* associate DRM payload table with DC stream encoder */
	uपूर्णांक8_t vcp_id;
	/* number of slots required क्रम the DP stream in transport packet */
	uपूर्णांक8_t slot_count;
पूर्ण;

/* DP MST stream allocation table */
काष्ठा link_mst_stream_allocation_table अणु
	/* number of DP video streams */
	पूर्णांक stream_count;
	/* array of stream allocations */
	काष्ठा link_mst_stream_allocation stream_allocations[MAX_CONTROLLER_NUM];
पूर्ण;

काष्ठा समय_stamp अणु
	uपूर्णांक64_t edp_घातeroff;
	uपूर्णांक64_t edp_घातeron;
पूर्ण;

काष्ठा link_trace अणु
	काष्ठा समय_stamp समय_stamp;
पूर्ण;

/* PSR feature flags */
काष्ठा psr_settings अणु
	bool psr_feature_enabled;		// PSR is supported by sink
	bool psr_allow_active;			// PSR is currently active
	क्रमागत dc_psr_version psr_version;		// Internal PSR version, determined based on DPCD

	/* These parameters are calculated in Driver,
	 * based on display timing and Sink capabilities.
	 * If VBLANK region is too small and Sink takes a दीर्घ समय
	 * to set up RFB, it may take an extra frame to enter PSR state.
	 */
	bool psr_frame_capture_indication_req;
	अचिन्हित पूर्णांक psr_sdp_transmit_line_num_deadline;
पूर्ण;

/*
 * A link contains one or more sinks and their connected status.
 * The currently active संकेत type (HDMI, DP-SST, DP-MST) is also reported.
 */
काष्ठा dc_link अणु
	काष्ठा dc_sink *remote_sinks[MAX_SINKS_PER_LINK];
	अचिन्हित पूर्णांक sink_count;
	काष्ठा dc_sink *local_sink;
	अचिन्हित पूर्णांक link_index;
	क्रमागत dc_connection_type type;
	क्रमागत संकेत_type connector_संकेत;
	क्रमागत dc_irq_source irq_source_hpd;
	क्रमागत dc_irq_source irq_source_hpd_rx;/* aka DP Short Pulse  */
	bool is_hpd_filter_disabled;
	bool dp_ss_off;
	bool link_state_valid;
	bool aux_access_disabled;
	bool sync_lt_in_progress;
	क्रमागत lttpr_mode lttpr_mode;
	bool is_पूर्णांकernal_display;

	/* TODO: Rename. Flag an endpoपूर्णांक as having a programmable mapping to a
	 * DIG encoder. */
	bool is_dig_mapping_flexible;

	bool edp_sink_present;

	/* caps is the same as reported_link_cap. link_traing use
	 * reported_link_cap. Will clean up.  TODO
	 */
	काष्ठा dc_link_settings reported_link_cap;
	काष्ठा dc_link_settings verअगरied_link_cap;
	काष्ठा dc_link_settings cur_link_settings;
	काष्ठा dc_lane_settings cur_lane_setting;
	काष्ठा dc_link_settings preferred_link_setting;
	काष्ठा dc_link_training_overrides preferred_training_settings;
	काष्ठा dp_audio_test_data audio_test_data;

	uपूर्णांक8_t ddc_hw_inst;

	uपूर्णांक8_t hpd_src;

	uपूर्णांक8_t link_enc_hw_inst;
	/* DIG link encoder ID. Used as index in link encoder resource pool.
	 * For links with fixed mapping to DIG, this is not changed after dc_link
	 * object creation.
	 */
	क्रमागत engine_id eng_id;

	bool test_pattern_enabled;
	जोड़ compliance_test_state compliance_test_state;

	व्योम *priv;

	काष्ठा ddc_service *ddc;

	bool aux_mode;

	/* Private to DC core */

	स्थिर काष्ठा dc *dc;

	काष्ठा dc_context *ctx;

	काष्ठा panel_cntl *panel_cntl;
	काष्ठा link_encoder *link_enc;
	काष्ठा graphics_object_id link_id;
	/* Endpoपूर्णांक type distinguishes display endpoपूर्णांकs which करो not have entries
	 * in the BIOS connector table from those that करो. Helps when tracking link
	 * encoder to display endpoपूर्णांक assignments.
	 */
	क्रमागत display_endpoपूर्णांक_type ep_type;
	जोड़ ddi_channel_mapping ddi_channel_mapping;
	काष्ठा connector_device_tag_info device_tag;
	काष्ठा dpcd_caps dpcd_caps;
	uपूर्णांक32_t करोngle_max_pix_clk;
	अचिन्हित लघु chip_caps;
	अचिन्हित पूर्णांक dpcd_sink_count;
#अगर defined(CONFIG_DRM_AMD_DC_HDCP)
	काष्ठा hdcp_caps hdcp_caps;
#पूर्ण_अगर
	क्रमागत edp_revision edp_revision;
	जोड़ dpcd_sink_ext_caps dpcd_sink_ext_caps;

	काष्ठा psr_settings psr_settings;

	/* MST record stream using this link */
	काष्ठा link_flags अणु
		bool dp_keep_receiver_घातered;
		bool dp_skip_DID2;
		bool dp_skip_reset_segment;
	पूर्ण wa_flags;
	काष्ठा link_mst_stream_allocation_table mst_stream_alloc_table;

	काष्ठा dc_link_status link_status;

	काष्ठा link_trace link_trace;
	काष्ठा gpio *hpd_gpio;
	क्रमागत dc_link_fec_state fec_state;
पूर्ण;

स्थिर काष्ठा dc_link_status *dc_link_get_status(स्थिर काष्ठा dc_link *dc_link);

/**
 * dc_get_link_at_index() - Return an क्रमागतerated dc_link.
 *
 * dc_link order is स्थिरant and determined at
 * boot समय.  They cannot be created or destroyed.
 * Use dc_get_caps() to get number of links.
 */
अटल अंतरभूत काष्ठा dc_link *dc_get_link_at_index(काष्ठा dc *dc, uपूर्णांक32_t link_index)
अणु
	वापस dc->links[link_index];
पूर्ण

अटल अंतरभूत व्योम get_edp_links(स्थिर काष्ठा dc *dc,
		काष्ठा dc_link **edp_links,
		पूर्णांक *edp_num)
अणु
	पूर्णांक i;

	*edp_num = 0;
	क्रम (i = 0; i < dc->link_count; i++) अणु
		// report any eDP links, even unconnected DDI's
		अगर (dc->links[i]->connector_संकेत == SIGNAL_TYPE_EDP) अणु
			edp_links[*edp_num] = dc->links[i];
			अगर (++(*edp_num) == MAX_NUM_EDP)
				वापस;
		पूर्ण
	पूर्ण
पूर्ण

/* Set backlight level of an embedded panel (eDP, LVDS).
 * backlight_pwm_u16_16 is अचिन्हित 32 bit with 16 bit पूर्णांकeger
 * and 16 bit fractional, where 1.0 is max backlight value.
 */
bool dc_link_set_backlight_level(स्थिर काष्ठा dc_link *dc_link,
		uपूर्णांक32_t backlight_pwm_u16_16,
		uपूर्णांक32_t frame_ramp);

/* Set/get nits-based backlight level of an embedded panel (eDP, LVDS). */
bool dc_link_set_backlight_level_nits(काष्ठा dc_link *link,
		bool isHDR,
		uपूर्णांक32_t backlight_millinits,
		uपूर्णांक32_t transition_समय_in_ms);

bool dc_link_get_backlight_level_nits(काष्ठा dc_link *link,
		uपूर्णांक32_t *backlight_millinits,
		uपूर्णांक32_t *backlight_millinits_peak);

bool dc_link_backlight_enable_aux(काष्ठा dc_link *link, bool enable);

bool dc_link_पढ़ो_शेष_bl_aux(काष्ठा dc_link *link, uपूर्णांक32_t *backlight_millinits);
bool dc_link_set_शेष_brightness_aux(काष्ठा dc_link *link);

पूर्णांक dc_link_get_backlight_level(स्थिर काष्ठा dc_link *dc_link);

पूर्णांक dc_link_get_target_backlight_pwm(स्थिर काष्ठा dc_link *link);

bool dc_link_set_psr_allow_active(काष्ठा dc_link *dc_link, bool enable,
		bool रुको, bool क्रमce_अटल);

bool dc_link_get_psr_state(स्थिर काष्ठा dc_link *dc_link, क्रमागत dc_psr_state *state);

bool dc_link_setup_psr(काष्ठा dc_link *dc_link,
		स्थिर काष्ठा dc_stream_state *stream, काष्ठा psr_config *psr_config,
		काष्ठा psr_context *psr_context);

व्योम dc_link_get_psr_residency(स्थिर काष्ठा dc_link *link, uपूर्णांक32_t *residency);

/* Request DC to detect अगर there is a Panel connected.
 * boot - If this call is during initial boot.
 * Return false क्रम any type of detection failure or MST detection
 * true otherwise. True meaning further action is required (status update
 * and OS notअगरication).
 */
क्रमागत dc_detect_reason अणु
	DETECT_REASON_BOOT,
	DETECT_REASON_HPD,
	DETECT_REASON_HPDRX,
	DETECT_REASON_FALLBACK,
	DETECT_REASON_RETRAIN
पूर्ण;

bool dc_link_detect(काष्ठा dc_link *dc_link, क्रमागत dc_detect_reason reason);
bool dc_link_get_hpd_state(काष्ठा dc_link *dc_link);
क्रमागत dc_status dc_link_allocate_mst_payload(काष्ठा pipe_ctx *pipe_ctx);

/* Notअगरy DC about DP RX Interrupt (aka Short Pulse Interrupt).
 * Return:
 * true - Downstream port status changed. DM should call DC to करो the
 * detection.
 * false - no change in Downstream port status. No further action required
 * from DM. */
bool dc_link_handle_hpd_rx_irq(काष्ठा dc_link *dc_link,
		जोड़ hpd_irq_data *hpd_irq_dpcd_data, bool *out_link_loss);

/*
 * On eDP links this function call will stall until T12 has elapsed.
 * If the panel is not in घातer off state, this function will वापस
 * immediately.
 */
bool dc_link_रुको_क्रम_t12(काष्ठा dc_link *link);

क्रमागत dc_status पढ़ो_hpd_rx_irq_data(
	काष्ठा dc_link *link,
	जोड़ hpd_irq_data *irq_data);

काष्ठा dc_sink_init_data;

काष्ठा dc_sink *dc_link_add_remote_sink(
		काष्ठा dc_link *dc_link,
		स्थिर uपूर्णांक8_t *edid,
		पूर्णांक len,
		काष्ठा dc_sink_init_data *init_data);

व्योम dc_link_हटाओ_remote_sink(
	काष्ठा dc_link *link,
	काष्ठा dc_sink *sink);

/* Used by diagnostics क्रम भव link at the moment */

व्योम dc_link_dp_set_drive_settings(
	काष्ठा dc_link *link,
	काष्ठा link_training_settings *lt_settings);

bool dc_link_dp_perक्रमm_link_training_skip_aux(
	काष्ठा dc_link *link,
	स्थिर काष्ठा dc_link_settings *link_setting);

क्रमागत link_training_result dc_link_dp_perक्रमm_link_training(
	काष्ठा dc_link *link,
	स्थिर काष्ठा dc_link_settings *link_setting,
	bool skip_video_pattern);

bool dc_link_dp_sync_lt_begin(काष्ठा dc_link *link);

क्रमागत link_training_result dc_link_dp_sync_lt_attempt(
	काष्ठा dc_link *link,
	काष्ठा dc_link_settings *link_setting,
	काष्ठा dc_link_training_overrides *lt_settings);

bool dc_link_dp_sync_lt_end(काष्ठा dc_link *link, bool link_करोwn);

व्योम dc_link_dp_enable_hpd(स्थिर काष्ठा dc_link *link);

व्योम dc_link_dp_disable_hpd(स्थिर काष्ठा dc_link *link);

bool dc_link_dp_set_test_pattern(
	काष्ठा dc_link *link,
	क्रमागत dp_test_pattern test_pattern,
	क्रमागत dp_test_pattern_color_space test_pattern_color_space,
	स्थिर काष्ठा link_training_settings *p_link_settings,
	स्थिर अचिन्हित अक्षर *p_custom_pattern,
	अचिन्हित पूर्णांक cust_pattern_size);

व्योम dc_link_enable_hpd_filter(काष्ठा dc_link *link, bool enable);

bool dc_link_is_dp_sink_present(काष्ठा dc_link *link);

bool dc_link_detect_sink(काष्ठा dc_link *link, क्रमागत dc_connection_type *type);
/*
 * DPCD access पूर्णांकerfaces
 */

#अगर_घोषित CONFIG_DRM_AMD_DC_HDCP
bool dc_link_is_hdcp14(काष्ठा dc_link *link, क्रमागत संकेत_type संकेत);
bool dc_link_is_hdcp22(काष्ठा dc_link *link, क्रमागत संकेत_type संकेत);
#पूर्ण_अगर
व्योम dc_link_set_drive_settings(काष्ठा dc *dc,
				काष्ठा link_training_settings *lt_settings,
				स्थिर काष्ठा dc_link *link);
व्योम dc_link_perक्रमm_link_training(काष्ठा dc *dc,
				   काष्ठा dc_link_settings *link_setting,
				   bool skip_video_pattern);
व्योम dc_link_set_preferred_link_settings(काष्ठा dc *dc,
					 काष्ठा dc_link_settings *link_setting,
					 काष्ठा dc_link *link);
व्योम dc_link_set_preferred_training_settings(काष्ठा dc *dc,
					काष्ठा dc_link_settings *link_setting,
					काष्ठा dc_link_training_overrides *lt_overrides,
					काष्ठा dc_link *link,
					bool skip_immediate_retrain);
व्योम dc_link_enable_hpd(स्थिर काष्ठा dc_link *link);
व्योम dc_link_disable_hpd(स्थिर काष्ठा dc_link *link);
व्योम dc_link_set_test_pattern(काष्ठा dc_link *link,
			क्रमागत dp_test_pattern test_pattern,
			क्रमागत dp_test_pattern_color_space test_pattern_color_space,
			स्थिर काष्ठा link_training_settings *p_link_settings,
			स्थिर अचिन्हित अक्षर *p_custom_pattern,
			अचिन्हित पूर्णांक cust_pattern_size);
uपूर्णांक32_t dc_link_bandwidth_kbps(
	स्थिर काष्ठा dc_link *link,
	स्थिर काष्ठा dc_link_settings *link_setting);

स्थिर काष्ठा dc_link_settings *dc_link_get_link_cap(
		स्थिर काष्ठा dc_link *link);

व्योम dc_link_overग_लिखो_extended_receiver_cap(
		काष्ठा dc_link *link);

bool dc_submit_i2c(
		काष्ठा dc *dc,
		uपूर्णांक32_t link_index,
		काष्ठा i2c_command *cmd);

bool dc_submit_i2c_oem(
		काष्ठा dc *dc,
		काष्ठा i2c_command *cmd);

uपूर्णांक32_t dc_bandwidth_in_kbps_from_timing(
	स्थिर काष्ठा dc_crtc_timing *timing);

bool dc_link_is_fec_supported(स्थिर काष्ठा dc_link *link);
bool dc_link_should_enable_fec(स्थिर काष्ठा dc_link *link);

#पूर्ण_अगर /* DC_LINK_H_ */
