<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __DAL_TIMING_GENERATOR_TYPES_H__
#घोषणा __DAL_TIMING_GENERATOR_TYPES_H__

#समावेश "hw_shared.h"

काष्ठा dc_bios;

/* Contains CRTC vertical/horizontal pixel counters */
काष्ठा crtc_position अणु
	पूर्णांक32_t vertical_count;
	पूर्णांक32_t horizontal_count;
	पूर्णांक32_t nominal_vcount;
पूर्ण;

काष्ठा dcp_gsl_params अणु
	पूर्णांक gsl_group;
	पूर्णांक gsl_master;
पूर्ण;

काष्ठा gsl_params अणु
	पूर्णांक gsl0_en;
	पूर्णांक gsl1_en;
	पूर्णांक gsl2_en;
	पूर्णांक gsl_master_en;
	पूर्णांक gsl_master_mode;
	पूर्णांक master_update_lock_gsl_en;
	पूर्णांक gsl_winकरोw_start_x;
	पूर्णांक gsl_winकरोw_end_x;
	पूर्णांक gsl_winकरोw_start_y;
	पूर्णांक gsl_winकरोw_end_y;
पूर्ण;

/* define the काष्ठाure of Dynamic Refresh Mode */
काष्ठा drr_params अणु
	uपूर्णांक32_t vertical_total_min;
	uपूर्णांक32_t vertical_total_max;
	uपूर्णांक32_t vertical_total_mid;
	uपूर्णांक32_t vertical_total_mid_frame_num;
	bool immediate_flip;
पूर्ण;

#घोषणा LEFT_EYE_3D_PRIMARY_SURFACE 1
#घोषणा RIGHT_EYE_3D_PRIMARY_SURFACE 0

क्रमागत crtc_state अणु
	CRTC_STATE_VBLANK = 0,
	CRTC_STATE_VACTIVE
पूर्ण;

काष्ठा vupdate_keepout_params अणु
	पूर्णांक start_offset;
	पूर्णांक end_offset;
	पूर्णांक enable;
पूर्ण;

काष्ठा crtc_stereo_flags अणु
	uपूर्णांक8_t PROGRAM_STEREO         : 1;
	uपूर्णांक8_t PROGRAM_POLARITY       : 1;
	uपूर्णांक8_t RIGHT_EYE_POLARITY     : 1;
	uपूर्णांक8_t FRAME_PACKED           : 1;
	uपूर्णांक8_t DISABLE_STEREO_DP_SYNC : 1;
पूर्ण;

क्रमागत crc_selection अणु
	/* Order must match values expected by hardware */
	UNION_WINDOW_A_B = 0,
	UNION_WINDOW_A_NOT_B,
	UNION_WINDOW_NOT_A_B,
	UNION_WINDOW_NOT_A_NOT_B,
	INTERSECT_WINDOW_A_B,
	INTERSECT_WINDOW_A_NOT_B,
	INTERSECT_WINDOW_NOT_A_B,
	INTERSECT_WINDOW_NOT_A_NOT_B,
पूर्ण;

क्रमागत otg_out_mux_dest अणु
	OUT_MUX_DIO = 0,
पूर्ण;

क्रमागत h_timing_भाग_mode अणु
	H_TIMING_NO_DIV,
	H_TIMING_DIV_BY2,
	H_TIMING_RESERVED,
	H_TIMING_DIV_BY4,
पूर्ण;

क्रमागत timing_synchronization_type अणु
	NOT_SYNCHRONIZABLE,
	TIMING_SYNCHRONIZABLE,
	VBLANK_SYNCHRONIZABLE
पूर्ण;

काष्ठा crc_params अणु
	/* Regions used to calculate CRC*/
	uपूर्णांक16_t winकरोwa_x_start;
	uपूर्णांक16_t winकरोwa_x_end;
	uपूर्णांक16_t winकरोwa_y_start;
	uपूर्णांक16_t winकरोwa_y_end;

	uपूर्णांक16_t winकरोwb_x_start;
	uपूर्णांक16_t winकरोwb_x_end;
	uपूर्णांक16_t winकरोwb_y_start;
	uपूर्णांक16_t winकरोwb_y_end;

	क्रमागत crc_selection selection;

	uपूर्णांक8_t dsc_mode;
	uपूर्णांक8_t odm_mode;

	bool continuous_mode;
	bool enable;
पूर्ण;

काष्ठा timing_generator अणु
	स्थिर काष्ठा timing_generator_funcs *funcs;
	काष्ठा dc_bios *bp;
	काष्ठा dc_context *ctx;
	पूर्णांक inst;
पूर्ण;

काष्ठा dc_crtc_timing;

काष्ठा drr_params;


काष्ठा timing_generator_funcs अणु
	bool (*validate_timing)(काष्ठा timing_generator *tg,
							स्थिर काष्ठा dc_crtc_timing *timing);
	व्योम (*program_timing)(काष्ठा timing_generator *tg,
							स्थिर काष्ठा dc_crtc_timing *timing,
							पूर्णांक vपढ़ोy_offset,
							पूर्णांक vstartup_start,
							पूर्णांक vupdate_offset,
							पूर्णांक vupdate_width,
							स्थिर क्रमागत संकेत_type संकेत,
							bool use_vbios
	);
	व्योम (*setup_vertical_पूर्णांकerrupt0)(
			काष्ठा timing_generator *optc,
			uपूर्णांक32_t start_line,
			uपूर्णांक32_t end_line);
	व्योम (*setup_vertical_पूर्णांकerrupt1)(
			काष्ठा timing_generator *optc,
			uपूर्णांक32_t start_line);
	व्योम (*setup_vertical_पूर्णांकerrupt2)(
			काष्ठा timing_generator *optc,
			uपूर्णांक32_t start_line);

	bool (*enable_crtc)(काष्ठा timing_generator *tg);
	bool (*disable_crtc)(काष्ठा timing_generator *tg);
	bool (*is_counter_moving)(काष्ठा timing_generator *tg);
	व्योम (*get_position)(काष्ठा timing_generator *tg,
				काष्ठा crtc_position *position);

	uपूर्णांक32_t (*get_frame_count)(काष्ठा timing_generator *tg);
	व्योम (*get_scanoutpos)(
		काष्ठा timing_generator *tg,
		uपूर्णांक32_t *v_blank_start,
		uपूर्णांक32_t *v_blank_end,
		uपूर्णांक32_t *h_position,
		uपूर्णांक32_t *v_position);
	bool (*get_otg_active_size)(काष्ठा timing_generator *optc,
			uपूर्णांक32_t *otg_active_width,
			uपूर्णांक32_t *otg_active_height);
	bool (*is_matching_timing)(काष्ठा timing_generator *tg,
			स्थिर काष्ठा dc_crtc_timing *otg_timing);
	व्योम (*set_early_control)(काष्ठा timing_generator *tg,
							   uपूर्णांक32_t early_cntl);
	व्योम (*रुको_क्रम_state)(काष्ठा timing_generator *tg,
							क्रमागत crtc_state state);
	व्योम (*set_blank)(काष्ठा timing_generator *tg,
					bool enable_blanking);
	bool (*is_blanked)(काष्ठा timing_generator *tg);
	bool (*is_locked)(काष्ठा timing_generator *tg);
	व्योम (*set_overscan_blank_color) (काष्ठा timing_generator *tg, स्थिर काष्ठा tg_color *color);
	व्योम (*set_blank_color)(काष्ठा timing_generator *tg, स्थिर काष्ठा tg_color *color);
	व्योम (*set_colors)(काष्ठा timing_generator *tg,
						स्थिर काष्ठा tg_color *blank_color,
						स्थिर काष्ठा tg_color *overscan_color);

	व्योम (*disable_vga)(काष्ठा timing_generator *tg);
	bool (*did_triggered_reset_occur)(काष्ठा timing_generator *tg);
	व्योम (*setup_global_swap_lock)(काष्ठा timing_generator *tg,
							स्थिर काष्ठा dcp_gsl_params *gsl_params);
	व्योम (*unlock)(काष्ठा timing_generator *tg);
	व्योम (*lock)(काष्ठा timing_generator *tg);
	व्योम (*lock_द्विगुनbuffer_disable)(काष्ठा timing_generator *tg);
	व्योम (*lock_द्विगुनbuffer_enable)(काष्ठा timing_generator *tg);
	व्योम(*triplebuffer_unlock)(काष्ठा timing_generator *tg);
	व्योम(*triplebuffer_lock)(काष्ठा timing_generator *tg);
	व्योम (*enable_reset_trigger)(काष्ठा timing_generator *tg,
				     पूर्णांक source_tg_inst);
	व्योम (*enable_crtc_reset)(काष्ठा timing_generator *tg,
				  पूर्णांक source_tg_inst,
				  काष्ठा crtc_trigger_info *crtc_tp);
	व्योम (*disable_reset_trigger)(काष्ठा timing_generator *tg);
	व्योम (*tear_करोwn_global_swap_lock)(काष्ठा timing_generator *tg);
	व्योम (*enable_advanced_request)(काष्ठा timing_generator *tg,
					bool enable, स्थिर काष्ठा dc_crtc_timing *timing);
	व्योम (*set_drr)(काष्ठा timing_generator *tg, स्थिर काष्ठा drr_params *params);
	व्योम (*set_अटल_screen_control)(काष्ठा timing_generator *tg,
						uपूर्णांक32_t event_triggers,
						uपूर्णांक32_t num_frames);
	व्योम (*set_test_pattern)(
		काष्ठा timing_generator *tg,
		क्रमागत controller_dp_test_pattern test_pattern,
		क्रमागत dc_color_depth color_depth);

	bool (*arm_vert_पूर्णांकr)(काष्ठा timing_generator *tg, uपूर्णांक8_t width);

	व्योम (*program_global_sync)(काष्ठा timing_generator *tg,
			पूर्णांक vपढ़ोy_offset,
			पूर्णांक vstartup_start,
			पूर्णांक vupdate_offset,
			पूर्णांक vupdate_width);
	व्योम (*enable_optc_घड़ी)(काष्ठा timing_generator *tg, bool enable);
	व्योम (*program_stereo)(काष्ठा timing_generator *tg,
		स्थिर काष्ठा dc_crtc_timing *timing, काष्ठा crtc_stereo_flags *flags);
	bool (*is_stereo_left_eye)(काष्ठा timing_generator *tg);

	व्योम (*set_blank_data_द्विगुन_buffer)(काष्ठा timing_generator *tg, bool enable);

	व्योम (*tg_init)(काष्ठा timing_generator *tg);
	bool (*is_tg_enabled)(काष्ठा timing_generator *tg);
	bool (*is_optc_underflow_occurred)(काष्ठा timing_generator *tg);
	व्योम (*clear_optc_underflow)(काष्ठा timing_generator *tg);

	व्योम (*set_dwb_source)(काष्ठा timing_generator *optc,
		uपूर्णांक32_t dwb_pipe_inst);

	व्योम (*get_optc_source)(काष्ठा timing_generator *optc,
			uपूर्णांक32_t *num_of_input_segments,
			uपूर्णांक32_t *seg0_src_sel,
			uपूर्णांक32_t *seg1_src_sel);

	/**
	 * Configure CRCs क्रम the given timing generator. Return false अगर TG is
	 * not on.
	 */
	bool (*configure_crc)(काष्ठा timing_generator *tg,
			       स्थिर काष्ठा crc_params *params);

	/**
	 * Get CRCs क्रम the given timing generator. Return false अगर CRCs are
	 * not enabled (via configure_crc).
	 */
	bool (*get_crc)(काष्ठा timing_generator *tg,
			uपूर्णांक32_t *r_cr, uपूर्णांक32_t *g_y, uपूर्णांक32_t *b_cb);

	व्योम (*program_manual_trigger)(काष्ठा timing_generator *optc);
	व्योम (*setup_manual_trigger)(काष्ठा timing_generator *optc);
	bool (*get_hw_timing)(काष्ठा timing_generator *optc,
			काष्ठा dc_crtc_timing *hw_crtc_timing);

	व्योम (*set_vtg_params)(काष्ठा timing_generator *optc,
			स्थिर काष्ठा dc_crtc_timing *dc_crtc_timing, bool program_fp2);

	व्योम (*set_dsc_config)(काष्ठा timing_generator *optc,
			       क्रमागत optc_dsc_mode dsc_mode,
			       uपूर्णांक32_t dsc_bytes_per_pixel,
			       uपूर्णांक32_t dsc_slice_width);
	व्योम (*set_odm_bypass)(काष्ठा timing_generator *optc, स्थिर काष्ठा dc_crtc_timing *dc_crtc_timing);
	व्योम (*set_odm_combine)(काष्ठा timing_generator *optc, पूर्णांक *opp_id, पूर्णांक opp_cnt,
			काष्ठा dc_crtc_timing *timing);
	व्योम (*set_gsl)(काष्ठा timing_generator *optc, स्थिर काष्ठा gsl_params *params);
	व्योम (*set_gsl_source_select)(काष्ठा timing_generator *optc,
			पूर्णांक group_idx,
			uपूर्णांक32_t gsl_पढ़ोy_संकेत);
	व्योम (*set_out_mux)(काष्ठा timing_generator *tg, क्रमागत otg_out_mux_dest dest);
	व्योम (*set_vrr_m_स्थिर)(काष्ठा timing_generator *optc,
			द्विगुन vtotal_avg);
	व्योम (*set_drr_trigger_winकरोw)(काष्ठा timing_generator *optc,
			uपूर्णांक32_t winकरोw_start, uपूर्णांक32_t winकरोw_end);
	व्योम (*set_vtotal_change_limit)(काष्ठा timing_generator *optc,
			uपूर्णांक32_t limit);
	व्योम (*align_vblanks)(काष्ठा timing_generator *master_optc,
			काष्ठा timing_generator *slave_optc,
			uपूर्णांक32_t master_pixel_घड़ी_100Hz,
			uपूर्णांक32_t slave_pixel_घड़ी_100Hz,
			uपूर्णांक8_t master_घड़ी_भागider,
			uपूर्णांक8_t slave_घड़ी_भागider);
पूर्ण;

#पूर्ण_अगर
