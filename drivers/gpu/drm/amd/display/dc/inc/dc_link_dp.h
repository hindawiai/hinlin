<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __DC_LINK_DP_H__
#घोषणा __DC_LINK_DP_H__

#घोषणा LINK_TRAINING_ATTEMPTS 4
#घोषणा LINK_TRAINING_RETRY_DELAY 50 /* ms */
#घोषणा LINK_AUX_DEFAULT_LTTPR_TIMEOUT_PERIOD 3200 /*us*/
#घोषणा LINK_AUX_DEFAULT_TIMEOUT_PERIOD 552 /*us*/

काष्ठा dc_link;
काष्ठा dc_stream_state;
काष्ठा dc_link_settings;

bool dp_verअगरy_link_cap(
	काष्ठा dc_link *link,
	काष्ठा dc_link_settings *known_limit_link_setting,
	पूर्णांक *fail_count);

bool dp_verअगरy_link_cap_with_retries(
	काष्ठा dc_link *link,
	काष्ठा dc_link_settings *known_limit_link_setting,
	पूर्णांक attempts);

bool dp_verअगरy_mst_link_cap(
	काष्ठा dc_link *link);

bool dp_validate_mode_timing(
	काष्ठा dc_link *link,
	स्थिर काष्ठा dc_crtc_timing *timing);

bool decide_edp_link_settings(काष्ठा dc_link *link,
		काष्ठा dc_link_settings *link_setting,
		uपूर्णांक32_t req_bw);

व्योम decide_link_settings(
	काष्ठा dc_stream_state *stream,
	काष्ठा dc_link_settings *link_setting);

bool perक्रमm_link_training_with_retries(
	स्थिर काष्ठा dc_link_settings *link_setting,
	bool skip_video_pattern,
	पूर्णांक attempts,
	काष्ठा pipe_ctx *pipe_ctx,
	क्रमागत संकेत_type संकेत);

bool is_mst_supported(काष्ठा dc_link *link);

bool detect_dp_sink_caps(काष्ठा dc_link *link);

व्योम detect_edp_sink_caps(काष्ठा dc_link *link);

bool is_dp_active_करोngle(स्थिर काष्ठा dc_link *link);

bool is_edp_ilr_optimization_required(काष्ठा dc_link *link, काष्ठा dc_crtc_timing *crtc_timing);

व्योम dp_enable_mst_on_sink(काष्ठा dc_link *link, bool enable);

क्रमागत dp_panel_mode dp_get_panel_mode(काष्ठा dc_link *link);
व्योम dp_set_panel_mode(काष्ठा dc_link *link, क्रमागत dp_panel_mode panel_mode);

bool dp_overग_लिखो_extended_receiver_cap(काष्ठा dc_link *link);

व्योम dpcd_set_source_specअगरic_data(काष्ठा dc_link *link);

व्योम dp_set_fec_पढ़ोy(काष्ठा dc_link *link, bool पढ़ोy);
व्योम dp_set_fec_enable(काष्ठा dc_link *link, bool enable);
bool dp_set_dsc_enable(काष्ठा pipe_ctx *pipe_ctx, bool enable);
bool dp_set_dsc_pps_sdp(काष्ठा pipe_ctx *pipe_ctx, bool enable);
व्योम dp_set_dsc_on_stream(काष्ठा pipe_ctx *pipe_ctx, bool enable);
bool dp_update_dsc_config(काष्ठा pipe_ctx *pipe_ctx);
bool dp_set_dsc_on_rx(काष्ठा pipe_ctx *pipe_ctx, bool enable);


#पूर्ण_अगर /* __DC_LINK_DP_H__ */
