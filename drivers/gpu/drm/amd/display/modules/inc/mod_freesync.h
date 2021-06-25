<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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




/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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

#अगर_अघोषित MOD_FREESYNC_H_
#घोषणा MOD_FREESYNC_H_

#समावेश "mod_shared.h"

// Access काष्ठाures
काष्ठा mod_मुक्तsync अणु
	पूर्णांक dummy;
पूर्ण;

// TODO: References to this should be हटाओd
काष्ठा mod_मुक्तsync_caps अणु
	bool supported;
	अचिन्हित पूर्णांक min_refresh_in_micro_hz;
	अचिन्हित पूर्णांक max_refresh_in_micro_hz;
पूर्ण;

क्रमागत mod_vrr_state अणु
	VRR_STATE_UNSUPPORTED = 0,
	VRR_STATE_DISABLED,
	VRR_STATE_INACTIVE,
	VRR_STATE_ACTIVE_VARIABLE,
	VRR_STATE_ACTIVE_FIXED
पूर्ण;

काष्ठा mod_मुक्तsync_config अणु
	क्रमागत mod_vrr_state state;
	bool vsअगर_supported;
	bool ramping;
	bool btr;
	अचिन्हित पूर्णांक min_refresh_in_uhz;
	अचिन्हित पूर्णांक max_refresh_in_uhz;
	अचिन्हित पूर्णांक fixed_refresh_in_uhz;

पूर्ण;

काष्ठा mod_vrr_params_btr अणु
	bool btr_enabled;
	bool btr_active;
	uपूर्णांक32_t mid_poपूर्णांक_in_us;
	uपूर्णांक32_t inserted_duration_in_us;
	uपूर्णांक32_t frames_to_insert;
	uपूर्णांक32_t frame_counter;
	uपूर्णांक32_t margin_in_us;
पूर्ण;

काष्ठा mod_vrr_params_fixed_refresh अणु
	bool fixed_active;
	bool ramping_active;
	bool ramping_करोne;
	uपूर्णांक32_t target_refresh_in_uhz;
	uपूर्णांक32_t frame_counter;
पूर्ण;

काष्ठा mod_vrr_params अणु
	bool supported;
	bool send_info_frame;
	क्रमागत mod_vrr_state state;

	uपूर्णांक32_t min_refresh_in_uhz;
	uपूर्णांक32_t max_duration_in_us;
	uपूर्णांक32_t max_refresh_in_uhz;
	uपूर्णांक32_t min_duration_in_us;
	uपूर्णांक32_t fixed_refresh_in_uhz;

	काष्ठा dc_crtc_timing_adjust adjust;

	काष्ठा mod_vrr_params_fixed_refresh fixed;

	काष्ठा mod_vrr_params_btr btr;
पूर्ण;

काष्ठा mod_मुक्तsync *mod_मुक्तsync_create(काष्ठा dc *dc);
व्योम mod_मुक्तsync_destroy(काष्ठा mod_मुक्तsync *mod_मुक्तsync);

bool mod_मुक्तsync_get_vmin_vmax(काष्ठा mod_मुक्तsync *mod_मुक्तsync,
		स्थिर काष्ठा dc_stream_state *stream,
		अचिन्हित पूर्णांक *vmin,
		अचिन्हित पूर्णांक *vmax);

bool mod_मुक्तsync_get_v_position(काष्ठा mod_मुक्तsync *mod_मुक्तsync,
		काष्ठा dc_stream_state *stream,
		अचिन्हित पूर्णांक *nom_v_pos,
		अचिन्हित पूर्णांक *v_pos);

व्योम mod_मुक्तsync_get_settings(काष्ठा mod_मुक्तsync *mod_मुक्तsync,
		स्थिर काष्ठा mod_vrr_params *vrr,
		अचिन्हित पूर्णांक *v_total_min, अचिन्हित पूर्णांक *v_total_max,
		अचिन्हित पूर्णांक *event_triggers,
		अचिन्हित पूर्णांक *winकरोw_min, अचिन्हित पूर्णांक *winकरोw_max,
		अचिन्हित पूर्णांक *lfc_mid_poपूर्णांक_in_us,
		अचिन्हित पूर्णांक *inserted_frames,
		अचिन्हित पूर्णांक *inserted_duration_in_us);

व्योम mod_मुक्तsync_build_vrr_infopacket(काष्ठा mod_मुक्तsync *mod_मुक्तsync,
		स्थिर काष्ठा dc_stream_state *stream,
		स्थिर काष्ठा mod_vrr_params *vrr,
		क्रमागत vrr_packet_type packet_type,
		क्रमागत color_transfer_func app_tf,
		काष्ठा dc_info_packet *infopacket,
		bool pack_sdp_v1_3);

व्योम mod_मुक्तsync_build_vrr_params(काष्ठा mod_मुक्तsync *mod_मुक्तsync,
		स्थिर काष्ठा dc_stream_state *stream,
		काष्ठा mod_मुक्तsync_config *in_config,
		काष्ठा mod_vrr_params *in_out_vrr);

व्योम mod_मुक्तsync_handle_preflip(काष्ठा mod_मुक्तsync *mod_मुक्तsync,
		स्थिर काष्ठा dc_plane_state *plane,
		स्थिर काष्ठा dc_stream_state *stream,
		अचिन्हित पूर्णांक curr_समय_stamp_in_us,
		काष्ठा mod_vrr_params *in_out_vrr);

व्योम mod_मुक्तsync_handle_v_update(काष्ठा mod_मुक्तsync *mod_मुक्तsync,
		स्थिर काष्ठा dc_stream_state *stream,
		काष्ठा mod_vrr_params *in_out_vrr);

अचिन्हित दीर्घ दीर्घ mod_मुक्तsync_calc_nominal_field_rate(
			स्थिर काष्ठा dc_stream_state *stream);

अचिन्हित दीर्घ दीर्घ mod_मुक्तsync_calc_field_rate_from_timing(
		अचिन्हित पूर्णांक vtotal, अचिन्हित पूर्णांक htotal, अचिन्हित पूर्णांक pix_clk);

bool mod_मुक्तsync_is_valid_range(uपूर्णांक32_t min_refresh_cap_in_uhz,
		uपूर्णांक32_t max_refresh_cap_in_uhz,
		uपूर्णांक32_t nominal_field_rate_in_uhz);

अचिन्हित पूर्णांक mod_मुक्तsync_calc_v_total_from_refresh(
		स्थिर काष्ठा dc_stream_state *stream,
		अचिन्हित पूर्णांक refresh_in_uhz);

#पूर्ण_अगर
