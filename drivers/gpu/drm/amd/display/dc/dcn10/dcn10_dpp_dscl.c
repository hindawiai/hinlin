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

#समावेश "dm_services.h"

#समावेश "core_types.h"

#समावेश "reg_helper.h"
#समावेश "dcn10_dpp.h"
#समावेश "basics/conversion.h"


#घोषणा NUM_PHASES    64
#घोषणा HORZ_MAX_TAPS 8
#घोषणा VERT_MAX_TAPS 8

#घोषणा BLACK_OFFSET_RGB_Y 0x0
#घोषणा BLACK_OFFSET_CBCR  0x8000

#घोषणा REG(reg)\
	dpp->tf_regs->reg

#घोषणा CTX \
	dpp->base.ctx

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	dpp->tf_shअगरt->field_name, dpp->tf_mask->field_name

क्रमागत dcn10_coef_filter_type_sel अणु
	SCL_COEF_LUMA_VERT_FILTER = 0,
	SCL_COEF_LUMA_HORZ_FILTER = 1,
	SCL_COEF_CHROMA_VERT_FILTER = 2,
	SCL_COEF_CHROMA_HORZ_FILTER = 3,
	SCL_COEF_ALPHA_VERT_FILTER = 4,
	SCL_COEF_ALPHA_HORZ_FILTER = 5
पूर्ण;

क्रमागत dscl_स्वतःcal_mode अणु
	AUTOCAL_MODE_OFF = 0,

	/* Autocal calculate the scaling ratio and initial phase and the
	 * DSCL_MODE_SEL must be set to 1
	 */
	AUTOCAL_MODE_AUTOSCALE = 1,
	/* Autocal perक्रमm स्वतः centering without replication and the
	 * DSCL_MODE_SEL must be set to 0
	 */
	AUTOCAL_MODE_AUTOCENTER = 2,
	/* Autocal perक्रमm स्वतः centering and स्वतः replication and the
	 * DSCL_MODE_SEL must be set to 0
	 */
	AUTOCAL_MODE_AUTOREPLICATE = 3
पूर्ण;

क्रमागत dscl_mode_sel अणु
	DSCL_MODE_SCALING_444_BYPASS = 0,
	DSCL_MODE_SCALING_444_RGB_ENABLE = 1,
	DSCL_MODE_SCALING_444_YCBCR_ENABLE = 2,
	DSCL_MODE_SCALING_420_YCBCR_ENABLE = 3,
	DSCL_MODE_SCALING_420_LUMA_BYPASS = 4,
	DSCL_MODE_SCALING_420_CHROMA_BYPASS = 5,
	DSCL_MODE_DSCL_BYPASS = 6
पूर्ण;

अटल व्योम dpp1_dscl_set_overscan(
	काष्ठा dcn10_dpp *dpp,
	स्थिर काष्ठा scaler_data *data)
अणु
	uपूर्णांक32_t left = data->recout.x;
	uपूर्णांक32_t top = data->recout.y;

	पूर्णांक right = data->h_active - data->recout.x - data->recout.width;
	पूर्णांक bottom = data->v_active - data->recout.y - data->recout.height;

	अगर (right < 0) अणु
		BREAK_TO_DEBUGGER();
		right = 0;
	पूर्ण
	अगर (bottom < 0) अणु
		BREAK_TO_DEBUGGER();
		bottom = 0;
	पूर्ण

	REG_SET_2(DSCL_EXT_OVERSCAN_LEFT_RIGHT, 0,
		EXT_OVERSCAN_LEFT, left,
		EXT_OVERSCAN_RIGHT, right);

	REG_SET_2(DSCL_EXT_OVERSCAN_TOP_BOTTOM, 0,
		EXT_OVERSCAN_BOTTOM, bottom,
		EXT_OVERSCAN_TOP, top);
पूर्ण

अटल व्योम dpp1_dscl_set_otg_blank(
		काष्ठा dcn10_dpp *dpp, स्थिर काष्ठा scaler_data *data)
अणु
	uपूर्णांक32_t h_blank_start = data->h_active;
	uपूर्णांक32_t h_blank_end = 0;
	uपूर्णांक32_t v_blank_start = data->v_active;
	uपूर्णांक32_t v_blank_end = 0;

	REG_SET_2(OTG_H_BLANK, 0,
			OTG_H_BLANK_START, h_blank_start,
			OTG_H_BLANK_END, h_blank_end);

	REG_SET_2(OTG_V_BLANK, 0,
			OTG_V_BLANK_START, v_blank_start,
			OTG_V_BLANK_END, v_blank_end);
पूर्ण

अटल पूर्णांक dpp1_dscl_get_pixel_depth_val(क्रमागत lb_pixel_depth depth)
अणु
	अगर (depth == LB_PIXEL_DEPTH_30BPP)
		वापस 0; /* 10 bpc */
	अन्यथा अगर (depth == LB_PIXEL_DEPTH_24BPP)
		वापस 1; /* 8 bpc */
	अन्यथा अगर (depth == LB_PIXEL_DEPTH_18BPP)
		वापस 2; /* 6 bpc */
	अन्यथा अगर (depth == LB_PIXEL_DEPTH_36BPP)
		वापस 3; /* 12 bpc */
	अन्यथा अणु
		ASSERT(0);
		वापस -1; /* Unsupported */
	पूर्ण
पूर्ण

अटल bool dpp1_dscl_is_video_क्रमmat(क्रमागत pixel_क्रमmat क्रमmat)
अणु
	अगर (क्रमmat >= PIXEL_FORMAT_VIDEO_BEGIN
			&& क्रमmat <= PIXEL_FORMAT_VIDEO_END)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल bool dpp1_dscl_is_420_क्रमmat(क्रमागत pixel_क्रमmat क्रमmat)
अणु
	अगर (क्रमmat == PIXEL_FORMAT_420BPP8 ||
			क्रमmat == PIXEL_FORMAT_420BPP10)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल क्रमागत dscl_mode_sel dpp1_dscl_get_dscl_mode(
		काष्ठा dpp *dpp_base,
		स्थिर काष्ठा scaler_data *data,
		bool dbg_always_scale)
अणु
	स्थिर दीर्घ दीर्घ one = dc_fixpt_one.value;

	अगर (dpp_base->caps->dscl_data_proc_क्रमmat == DSCL_DATA_PRCESSING_FIXED_FORMAT) अणु
		/* DSCL is processing data in fixed क्रमmat */
		अगर (data->क्रमmat == PIXEL_FORMAT_FP16)
			वापस DSCL_MODE_DSCL_BYPASS;
	पूर्ण

	अगर (data->ratios.horz.value == one
			&& data->ratios.vert.value == one
			&& data->ratios.horz_c.value == one
			&& data->ratios.vert_c.value == one
			&& !dbg_always_scale)
		वापस DSCL_MODE_SCALING_444_BYPASS;

	अगर (!dpp1_dscl_is_420_क्रमmat(data->क्रमmat)) अणु
		अगर (dpp1_dscl_is_video_क्रमmat(data->क्रमmat))
			वापस DSCL_MODE_SCALING_444_YCBCR_ENABLE;
		अन्यथा
			वापस DSCL_MODE_SCALING_444_RGB_ENABLE;
	पूर्ण
	अगर (data->ratios.horz.value == one && data->ratios.vert.value == one)
		वापस DSCL_MODE_SCALING_420_LUMA_BYPASS;
	अगर (data->ratios.horz_c.value == one && data->ratios.vert_c.value == one)
		वापस DSCL_MODE_SCALING_420_CHROMA_BYPASS;

	वापस DSCL_MODE_SCALING_420_YCBCR_ENABLE;
पूर्ण

अटल व्योम dpp1_घातer_on_dscl(
	काष्ठा dpp *dpp_base,
	bool घातer_on)
अणु
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	अगर (dpp->tf_regs->DSCL_MEM_PWR_CTRL) अणु
		REG_UPDATE(DSCL_MEM_PWR_CTRL, LUT_MEM_PWR_FORCE, घातer_on ? 0 : 3);
		अगर (घातer_on)
			REG_WAIT(DSCL_MEM_PWR_STATUS, LUT_MEM_PWR_STATE, 0, 1, 5);
	पूर्ण
पूर्ण


अटल व्योम dpp1_dscl_set_lb(
	काष्ठा dcn10_dpp *dpp,
	स्थिर काष्ठा line_buffer_params *lb_params,
	क्रमागत lb_memory_config mem_size_config)
अणु
	/* LB */
	अगर (dpp->base.caps->dscl_data_proc_क्रमmat == DSCL_DATA_PRCESSING_FIXED_FORMAT) अणु
		/* DSCL caps: pixel data processed in fixed क्रमmat */
		uपूर्णांक32_t pixel_depth = dpp1_dscl_get_pixel_depth_val(lb_params->depth);
		uपूर्णांक32_t dyn_pix_depth = lb_params->dynamic_pixel_depth;

		REG_SET_7(LB_DATA_FORMAT, 0,
			PIXEL_DEPTH, pixel_depth, /* Pixel depth stored in LB */
			PIXEL_EXPAN_MODE, lb_params->pixel_expan_mode, /* Pixel expansion mode */
			PIXEL_REDUCE_MODE, 1, /* Pixel reduction mode: Rounding */
			DYNAMIC_PIXEL_DEPTH, dyn_pix_depth, /* Dynamic expansion pixel depth */
			DITHER_EN, 0, /* Dithering enable: Disabled */
			INTERLEAVE_EN, lb_params->पूर्णांकerleave_en, /* Interleave source enable */
			LB_DATA_FORMAT__ALPHA_EN, lb_params->alpha_en); /* Alpha enable */
	पूर्ण
	अन्यथा अणु
		/* DSCL caps: pixel data processed in भग्न क्रमmat */
		REG_SET_2(LB_DATA_FORMAT, 0,
			INTERLEAVE_EN, lb_params->पूर्णांकerleave_en, /* Interleave source enable */
			LB_DATA_FORMAT__ALPHA_EN, lb_params->alpha_en); /* Alpha enable */
	पूर्ण

	REG_SET_2(LB_MEMORY_CTRL, 0,
		MEMORY_CONFIG, mem_size_config,
		LB_MAX_PARTITIONS, 63);
पूर्ण

अटल स्थिर uपूर्णांक16_t *dpp1_dscl_get_filter_coeffs_64p(पूर्णांक taps, काष्ठा fixed31_32 ratio)
अणु
	अगर (taps == 8)
		वापस get_filter_8tap_64p(ratio);
	अन्यथा अगर (taps == 7)
		वापस get_filter_7tap_64p(ratio);
	अन्यथा अगर (taps == 6)
		वापस get_filter_6tap_64p(ratio);
	अन्यथा अगर (taps == 5)
		वापस get_filter_5tap_64p(ratio);
	अन्यथा अगर (taps == 4)
		वापस get_filter_4tap_64p(ratio);
	अन्यथा अगर (taps == 3)
		वापस get_filter_3tap_64p(ratio);
	अन्यथा अगर (taps == 2)
		वापस get_filter_2tap_64p();
	अन्यथा अगर (taps == 1)
		वापस शून्य;
	अन्यथा अणु
		/* should never happen, bug */
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण
पूर्ण

अटल व्योम dpp1_dscl_set_scaler_filter(
		काष्ठा dcn10_dpp *dpp,
		uपूर्णांक32_t taps,
		क्रमागत dcn10_coef_filter_type_sel filter_type,
		स्थिर uपूर्णांक16_t *filter)
अणु
	स्थिर पूर्णांक tap_pairs = (taps + 1) / 2;
	पूर्णांक phase;
	पूर्णांक pair;
	uपूर्णांक16_t odd_coef, even_coef;

	REG_SET_3(SCL_COEF_RAM_TAP_SELECT, 0,
		SCL_COEF_RAM_TAP_PAIR_IDX, 0,
		SCL_COEF_RAM_PHASE, 0,
		SCL_COEF_RAM_FILTER_TYPE, filter_type);

	क्रम (phase = 0; phase < (NUM_PHASES / 2 + 1); phase++) अणु
		क्रम (pair = 0; pair < tap_pairs; pair++) अणु
			even_coef = filter[phase * taps + 2 * pair];
			अगर ((pair * 2 + 1) < taps)
				odd_coef = filter[phase * taps + 2 * pair + 1];
			अन्यथा
				odd_coef = 0;

			REG_SET_4(SCL_COEF_RAM_TAP_DATA, 0,
				/* Even tap coefficient (bits 1:0 fixed to 0) */
				SCL_COEF_RAM_EVEN_TAP_COEF, even_coef,
				/* Write/पढ़ो control क्रम even coefficient */
				SCL_COEF_RAM_EVEN_TAP_COEF_EN, 1,
				/* Odd tap coefficient (bits 1:0 fixed to 0) */
				SCL_COEF_RAM_ODD_TAP_COEF, odd_coef,
				/* Write/पढ़ो control क्रम odd coefficient */
				SCL_COEF_RAM_ODD_TAP_COEF_EN, 1);
		पूर्ण
	पूर्ण

पूर्ण

अटल व्योम dpp1_dscl_set_scl_filter(
		काष्ठा dcn10_dpp *dpp,
		स्थिर काष्ठा scaler_data *scl_data,
		bool chroma_coef_mode)
अणु
	bool h_2tap_hardcode_coef_en = false;
	bool v_2tap_hardcode_coef_en = false;
	bool h_2tap_sharp_en = false;
	bool v_2tap_sharp_en = false;
	uपूर्णांक32_t h_2tap_sharp_factor = scl_data->sharpness.horz;
	uपूर्णांक32_t v_2tap_sharp_factor = scl_data->sharpness.vert;
	bool coef_ram_current;
	स्थिर uपूर्णांक16_t *filter_h = शून्य;
	स्थिर uपूर्णांक16_t *filter_v = शून्य;
	स्थिर uपूर्णांक16_t *filter_h_c = शून्य;
	स्थिर uपूर्णांक16_t *filter_v_c = शून्य;

	h_2tap_hardcode_coef_en = scl_data->taps.h_taps < 3
					&& scl_data->taps.h_taps_c < 3
		&& (scl_data->taps.h_taps > 1 && scl_data->taps.h_taps_c > 1);
	v_2tap_hardcode_coef_en = scl_data->taps.v_taps < 3
					&& scl_data->taps.v_taps_c < 3
		&& (scl_data->taps.v_taps > 1 && scl_data->taps.v_taps_c > 1);

	h_2tap_sharp_en = h_2tap_hardcode_coef_en && h_2tap_sharp_factor != 0;
	v_2tap_sharp_en = v_2tap_hardcode_coef_en && v_2tap_sharp_factor != 0;

	REG_UPDATE_6(DSCL_2TAP_CONTROL,
		SCL_H_2TAP_HARDCODE_COEF_EN, h_2tap_hardcode_coef_en,
		SCL_H_2TAP_SHARP_EN, h_2tap_sharp_en,
		SCL_H_2TAP_SHARP_FACTOR, h_2tap_sharp_factor,
		SCL_V_2TAP_HARDCODE_COEF_EN, v_2tap_hardcode_coef_en,
		SCL_V_2TAP_SHARP_EN, v_2tap_sharp_en,
		SCL_V_2TAP_SHARP_FACTOR, v_2tap_sharp_factor);

	अगर (!v_2tap_hardcode_coef_en || !h_2tap_hardcode_coef_en) अणु
		bool filter_updated = false;

		filter_h = dpp1_dscl_get_filter_coeffs_64p(
				scl_data->taps.h_taps, scl_data->ratios.horz);
		filter_v = dpp1_dscl_get_filter_coeffs_64p(
				scl_data->taps.v_taps, scl_data->ratios.vert);

		filter_updated = (filter_h && (filter_h != dpp->filter_h))
				|| (filter_v && (filter_v != dpp->filter_v));

		अगर (chroma_coef_mode) अणु
			filter_h_c = dpp1_dscl_get_filter_coeffs_64p(
					scl_data->taps.h_taps_c, scl_data->ratios.horz_c);
			filter_v_c = dpp1_dscl_get_filter_coeffs_64p(
					scl_data->taps.v_taps_c, scl_data->ratios.vert_c);
			filter_updated = filter_updated || (filter_h_c && (filter_h_c != dpp->filter_h_c))
							|| (filter_v_c && (filter_v_c != dpp->filter_v_c));
		पूर्ण

		अगर (filter_updated) अणु
			uपूर्णांक32_t scl_mode = REG_READ(SCL_MODE);

			अगर (!h_2tap_hardcode_coef_en && filter_h) अणु
				dpp1_dscl_set_scaler_filter(
					dpp, scl_data->taps.h_taps,
					SCL_COEF_LUMA_HORZ_FILTER, filter_h);
			पूर्ण
			dpp->filter_h = filter_h;
			अगर (!v_2tap_hardcode_coef_en && filter_v) अणु
				dpp1_dscl_set_scaler_filter(
					dpp, scl_data->taps.v_taps,
					SCL_COEF_LUMA_VERT_FILTER, filter_v);
			पूर्ण
			dpp->filter_v = filter_v;
			अगर (chroma_coef_mode) अणु
				अगर (!h_2tap_hardcode_coef_en && filter_h_c) अणु
					dpp1_dscl_set_scaler_filter(
						dpp, scl_data->taps.h_taps_c,
						SCL_COEF_CHROMA_HORZ_FILTER, filter_h_c);
				पूर्ण
				अगर (!v_2tap_hardcode_coef_en && filter_v_c) अणु
					dpp1_dscl_set_scaler_filter(
						dpp, scl_data->taps.v_taps_c,
						SCL_COEF_CHROMA_VERT_FILTER, filter_v_c);
				पूर्ण
			पूर्ण
			dpp->filter_h_c = filter_h_c;
			dpp->filter_v_c = filter_v_c;

			coef_ram_current = get_reg_field_value_ex(
				scl_mode, dpp->tf_mask->SCL_COEF_RAM_SELECT_CURRENT,
				dpp->tf_shअगरt->SCL_COEF_RAM_SELECT_CURRENT);

			/* Swap coefficient RAM and set chroma coefficient mode */
			REG_SET_2(SCL_MODE, scl_mode,
					SCL_COEF_RAM_SELECT, !coef_ram_current,
					SCL_CHROMA_COEF_MODE, chroma_coef_mode);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक dpp1_dscl_get_lb_depth_bpc(क्रमागत lb_pixel_depth depth)
अणु
	अगर (depth == LB_PIXEL_DEPTH_30BPP)
		वापस 10;
	अन्यथा अगर (depth == LB_PIXEL_DEPTH_24BPP)
		वापस 8;
	अन्यथा अगर (depth == LB_PIXEL_DEPTH_18BPP)
		वापस 6;
	अन्यथा अगर (depth == LB_PIXEL_DEPTH_36BPP)
		वापस 12;
	अन्यथा अणु
		BREAK_TO_DEBUGGER();
		वापस -1; /* Unsupported */
	पूर्ण
पूर्ण

व्योम dpp1_dscl_calc_lb_num_partitions(
		स्थिर काष्ठा scaler_data *scl_data,
		क्रमागत lb_memory_config lb_config,
		पूर्णांक *num_part_y,
		पूर्णांक *num_part_c)
अणु
	पूर्णांक lb_memory_size, lb_memory_size_c, lb_memory_size_a, num_partitions_a,
	lb_bpc, memory_line_size_y, memory_line_size_c, memory_line_size_a;

	पूर्णांक line_size = scl_data->viewport.width < scl_data->recout.width ?
			scl_data->viewport.width : scl_data->recout.width;
	पूर्णांक line_size_c = scl_data->viewport_c.width < scl_data->recout.width ?
			scl_data->viewport_c.width : scl_data->recout.width;

	अगर (line_size == 0)
		line_size = 1;

	अगर (line_size_c == 0)
		line_size_c = 1;


	lb_bpc = dpp1_dscl_get_lb_depth_bpc(scl_data->lb_params.depth);
	memory_line_size_y = (line_size * lb_bpc + 71) / 72; /* +71 to उच्चमान */
	memory_line_size_c = (line_size_c * lb_bpc + 71) / 72; /* +71 to उच्चमान */
	memory_line_size_a = (line_size + 5) / 6; /* +5 to उच्चमान */

	अगर (lb_config == LB_MEMORY_CONFIG_1) अणु
		lb_memory_size = 816;
		lb_memory_size_c = 816;
		lb_memory_size_a = 984;
	पूर्ण अन्यथा अगर (lb_config == LB_MEMORY_CONFIG_2) अणु
		lb_memory_size = 1088;
		lb_memory_size_c = 1088;
		lb_memory_size_a = 1312;
	पूर्ण अन्यथा अगर (lb_config == LB_MEMORY_CONFIG_3) अणु
		/* 420 mode: using 3rd mem from Y, Cr and Cb */
		lb_memory_size = 816 + 1088 + 848 + 848 + 848;
		lb_memory_size_c = 816 + 1088;
		lb_memory_size_a = 984 + 1312 + 456;
	पूर्ण अन्यथा अणु
		lb_memory_size = 816 + 1088 + 848;
		lb_memory_size_c = 816 + 1088 + 848;
		lb_memory_size_a = 984 + 1312 + 456;
	पूर्ण
	*num_part_y = lb_memory_size / memory_line_size_y;
	*num_part_c = lb_memory_size_c / memory_line_size_c;
	num_partitions_a = lb_memory_size_a / memory_line_size_a;

	अगर (scl_data->lb_params.alpha_en
			&& (num_partitions_a < *num_part_y))
		*num_part_y = num_partitions_a;

	अगर (*num_part_y > 64)
		*num_part_y = 64;
	अगर (*num_part_c > 64)
		*num_part_c = 64;

पूर्ण

bool dpp1_dscl_is_lb_conf_valid(पूर्णांक उच्चमान_vratio, पूर्णांक num_partitions, पूर्णांक vtaps)
अणु
	अगर (उच्चमान_vratio > 2)
		वापस vtaps <= (num_partitions - उच्चमान_vratio + 2);
	अन्यथा
		वापस vtaps <= num_partitions;
पूर्ण

/*find first match configuration which meets the min required lb size*/
अटल क्रमागत lb_memory_config dpp1_dscl_find_lb_memory_config(काष्ठा dcn10_dpp *dpp,
		स्थिर काष्ठा scaler_data *scl_data)
अणु
	पूर्णांक num_part_y, num_part_c;
	पूर्णांक vtaps = scl_data->taps.v_taps;
	पूर्णांक vtaps_c = scl_data->taps.v_taps_c;
	पूर्णांक उच्चमान_vratio = dc_fixpt_उच्चमान(scl_data->ratios.vert);
	पूर्णांक उच्चमान_vratio_c = dc_fixpt_उच्चमान(scl_data->ratios.vert_c);
	क्रमागत lb_memory_config mem_cfg = LB_MEMORY_CONFIG_0;

	अगर (dpp->base.ctx->dc->debug.use_max_lb)
		वापस mem_cfg;

	dpp->base.caps->dscl_calc_lb_num_partitions(
			scl_data, LB_MEMORY_CONFIG_1, &num_part_y, &num_part_c);

	अगर (dpp1_dscl_is_lb_conf_valid(उच्चमान_vratio, num_part_y, vtaps)
			&& dpp1_dscl_is_lb_conf_valid(उच्चमान_vratio_c, num_part_c, vtaps_c))
		वापस LB_MEMORY_CONFIG_1;

	dpp->base.caps->dscl_calc_lb_num_partitions(
			scl_data, LB_MEMORY_CONFIG_2, &num_part_y, &num_part_c);

	अगर (dpp1_dscl_is_lb_conf_valid(उच्चमान_vratio, num_part_y, vtaps)
			&& dpp1_dscl_is_lb_conf_valid(उच्चमान_vratio_c, num_part_c, vtaps_c))
		वापस LB_MEMORY_CONFIG_2;

	अगर (scl_data->क्रमmat == PIXEL_FORMAT_420BPP8
			|| scl_data->क्रमmat == PIXEL_FORMAT_420BPP10) अणु
		dpp->base.caps->dscl_calc_lb_num_partitions(
				scl_data, LB_MEMORY_CONFIG_3, &num_part_y, &num_part_c);

		अगर (dpp1_dscl_is_lb_conf_valid(उच्चमान_vratio, num_part_y, vtaps)
				&& dpp1_dscl_is_lb_conf_valid(उच्चमान_vratio_c, num_part_c, vtaps_c))
			वापस LB_MEMORY_CONFIG_3;
	पूर्ण

	dpp->base.caps->dscl_calc_lb_num_partitions(
			scl_data, LB_MEMORY_CONFIG_0, &num_part_y, &num_part_c);

	/*Ensure we can support the requested number of vtaps*/
	ASSERT(dpp1_dscl_is_lb_conf_valid(उच्चमान_vratio, num_part_y, vtaps)
			&& dpp1_dscl_is_lb_conf_valid(उच्चमान_vratio_c, num_part_c, vtaps_c));

	वापस LB_MEMORY_CONFIG_0;
पूर्ण

व्योम dpp1_dscl_set_scaler_स्वतः_scale(
	काष्ठा dpp *dpp_base,
	स्थिर काष्ठा scaler_data *scl_data)
अणु
	क्रमागत lb_memory_config lb_config;
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);
	क्रमागत dscl_mode_sel dscl_mode = dpp1_dscl_get_dscl_mode(
			dpp_base, scl_data, dpp_base->ctx->dc->debug.always_scale);
	bool ycbcr = scl_data->क्रमmat >= PIXEL_FORMAT_VIDEO_BEGIN
				&& scl_data->क्रमmat <= PIXEL_FORMAT_VIDEO_END;

	dpp1_dscl_set_overscan(dpp, scl_data);

	dpp1_dscl_set_otg_blank(dpp, scl_data);

	REG_UPDATE(SCL_MODE, DSCL_MODE, dscl_mode);

	अगर (dscl_mode == DSCL_MODE_DSCL_BYPASS)
		वापस;

	lb_config =  dpp1_dscl_find_lb_memory_config(dpp, scl_data);
	dpp1_dscl_set_lb(dpp, &scl_data->lb_params, lb_config);

	अगर (dscl_mode == DSCL_MODE_SCALING_444_BYPASS)
		वापस;

	/* TODO: v_min */
	REG_SET_3(DSCL_AUTOCAL, 0,
		AUTOCAL_MODE, AUTOCAL_MODE_AUTOSCALE,
		AUTOCAL_NUM_PIPE, 0,
		AUTOCAL_PIPE_ID, 0);

	/* Black offsets */
	अगर (ycbcr)
		REG_SET_2(SCL_BLACK_OFFSET, 0,
				SCL_BLACK_OFFSET_RGB_Y, BLACK_OFFSET_RGB_Y,
				SCL_BLACK_OFFSET_CBCR, BLACK_OFFSET_CBCR);
	अन्यथा

		REG_SET_2(SCL_BLACK_OFFSET, 0,
				SCL_BLACK_OFFSET_RGB_Y, BLACK_OFFSET_RGB_Y,
				SCL_BLACK_OFFSET_CBCR, BLACK_OFFSET_RGB_Y);

	REG_SET_4(SCL_TAP_CONTROL, 0,
		SCL_V_NUM_TAPS, scl_data->taps.v_taps - 1,
		SCL_H_NUM_TAPS, scl_data->taps.h_taps - 1,
		SCL_V_NUM_TAPS_C, scl_data->taps.v_taps_c - 1,
		SCL_H_NUM_TAPS_C, scl_data->taps.h_taps_c - 1);

	dpp1_dscl_set_scl_filter(dpp, scl_data, ycbcr);
पूर्ण


अटल व्योम dpp1_dscl_set_manual_ratio_init(
		काष्ठा dcn10_dpp *dpp, स्थिर काष्ठा scaler_data *data)
अणु
	uपूर्णांक32_t init_frac = 0;
	uपूर्णांक32_t init_पूर्णांक = 0;

	REG_SET(SCL_HORZ_FILTER_SCALE_RATIO, 0,
			SCL_H_SCALE_RATIO, dc_fixpt_u3d19(data->ratios.horz) << 5);

	REG_SET(SCL_VERT_FILTER_SCALE_RATIO, 0,
			SCL_V_SCALE_RATIO, dc_fixpt_u3d19(data->ratios.vert) << 5);

	REG_SET(SCL_HORZ_FILTER_SCALE_RATIO_C, 0,
			SCL_H_SCALE_RATIO_C, dc_fixpt_u3d19(data->ratios.horz_c) << 5);

	REG_SET(SCL_VERT_FILTER_SCALE_RATIO_C, 0,
			SCL_V_SCALE_RATIO_C, dc_fixpt_u3d19(data->ratios.vert_c) << 5);

	/*
	 * 0.24 क्रमmat क्रम fraction, first five bits zeroed
	 */
	init_frac = dc_fixpt_u0d19(data->inits.h) << 5;
	init_पूर्णांक = dc_fixpt_न्यूनमान(data->inits.h);
	REG_SET_2(SCL_HORZ_FILTER_INIT, 0,
		SCL_H_INIT_FRAC, init_frac,
		SCL_H_INIT_INT, init_पूर्णांक);

	init_frac = dc_fixpt_u0d19(data->inits.h_c) << 5;
	init_पूर्णांक = dc_fixpt_न्यूनमान(data->inits.h_c);
	REG_SET_2(SCL_HORZ_FILTER_INIT_C, 0,
		SCL_H_INIT_FRAC_C, init_frac,
		SCL_H_INIT_INT_C, init_पूर्णांक);

	init_frac = dc_fixpt_u0d19(data->inits.v) << 5;
	init_पूर्णांक = dc_fixpt_न्यूनमान(data->inits.v);
	REG_SET_2(SCL_VERT_FILTER_INIT, 0,
		SCL_V_INIT_FRAC, init_frac,
		SCL_V_INIT_INT, init_पूर्णांक);

	अगर (REG(SCL_VERT_FILTER_INIT_BOT)) अणु
		init_frac = dc_fixpt_u0d19(data->inits.v_bot) << 5;
		init_पूर्णांक = dc_fixpt_न्यूनमान(data->inits.v_bot);
		REG_SET_2(SCL_VERT_FILTER_INIT_BOT, 0,
			SCL_V_INIT_FRAC_BOT, init_frac,
			SCL_V_INIT_INT_BOT, init_पूर्णांक);
	पूर्ण

	init_frac = dc_fixpt_u0d19(data->inits.v_c) << 5;
	init_पूर्णांक = dc_fixpt_न्यूनमान(data->inits.v_c);
	REG_SET_2(SCL_VERT_FILTER_INIT_C, 0,
		SCL_V_INIT_FRAC_C, init_frac,
		SCL_V_INIT_INT_C, init_पूर्णांक);

	अगर (REG(SCL_VERT_FILTER_INIT_BOT_C)) अणु
		init_frac = dc_fixpt_u0d19(data->inits.v_c_bot) << 5;
		init_पूर्णांक = dc_fixpt_न्यूनमान(data->inits.v_c_bot);
		REG_SET_2(SCL_VERT_FILTER_INIT_BOT_C, 0,
			SCL_V_INIT_FRAC_BOT_C, init_frac,
			SCL_V_INIT_INT_BOT_C, init_पूर्णांक);
	पूर्ण
पूर्ण



अटल व्योम dpp1_dscl_set_recout(
			काष्ठा dcn10_dpp *dpp, स्थिर काष्ठा rect *recout)
अणु
	पूर्णांक visual_confirm_on = 0;
	अगर (dpp->base.ctx->dc->debug.visual_confirm != VISUAL_CONFIRM_DISABLE)
		visual_confirm_on = 1;

	REG_SET_2(RECOUT_START, 0,
		/* First pixel of RECOUT */
			 RECOUT_START_X, recout->x,
		/* First line of RECOUT */
			 RECOUT_START_Y, recout->y);

	REG_SET_2(RECOUT_SIZE, 0,
		/* Number of RECOUT horizontal pixels */
			 RECOUT_WIDTH, recout->width,
		/* Number of RECOUT vertical lines */
			 RECOUT_HEIGHT, recout->height
			 - visual_confirm_on * 2 * (dpp->base.inst + 1));
पूर्ण

/* Main function to program scaler and line buffer in manual scaling mode */
व्योम dpp1_dscl_set_scaler_manual_scale(
	काष्ठा dpp *dpp_base,
	स्थिर काष्ठा scaler_data *scl_data)
अणु
	क्रमागत lb_memory_config lb_config;
	काष्ठा dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);
	क्रमागत dscl_mode_sel dscl_mode = dpp1_dscl_get_dscl_mode(
			dpp_base, scl_data, dpp_base->ctx->dc->debug.always_scale);
	bool ycbcr = scl_data->क्रमmat >= PIXEL_FORMAT_VIDEO_BEGIN
				&& scl_data->क्रमmat <= PIXEL_FORMAT_VIDEO_END;

	अगर (स_भेद(&dpp->scl_data, scl_data, माप(*scl_data)) == 0)
		वापस;

	PERF_TRACE();

	dpp->scl_data = *scl_data;

	अगर (dpp_base->ctx->dc->debug.enable_mem_low_घातer.bits.dscl) अणु
		अगर (dscl_mode != DSCL_MODE_DSCL_BYPASS)
			dpp1_घातer_on_dscl(dpp_base, true);
	पूर्ण

	/* Autocal off */
	REG_SET_3(DSCL_AUTOCAL, 0,
		AUTOCAL_MODE, AUTOCAL_MODE_OFF,
		AUTOCAL_NUM_PIPE, 0,
		AUTOCAL_PIPE_ID, 0);

	/* Recout */
	dpp1_dscl_set_recout(dpp, &scl_data->recout);

	/* MPC Size */
	REG_SET_2(MPC_SIZE, 0,
		/* Number of horizontal pixels of MPC */
			 MPC_WIDTH, scl_data->h_active,
		/* Number of vertical lines of MPC */
			 MPC_HEIGHT, scl_data->v_active);

	/* SCL mode */
	REG_UPDATE(SCL_MODE, DSCL_MODE, dscl_mode);

	अगर (dscl_mode == DSCL_MODE_DSCL_BYPASS) अणु
		अगर (dpp_base->ctx->dc->debug.enable_mem_low_घातer.bits.dscl)
			dpp1_घातer_on_dscl(dpp_base, false);
		वापस;
	पूर्ण

	/* LB */
	lb_config =  dpp1_dscl_find_lb_memory_config(dpp, scl_data);
	dpp1_dscl_set_lb(dpp, &scl_data->lb_params, lb_config);

	अगर (dscl_mode == DSCL_MODE_SCALING_444_BYPASS)
		वापस;

	/* Black offsets */
	अगर (REG(SCL_BLACK_OFFSET)) अणु
		अगर (ycbcr)
			REG_SET_2(SCL_BLACK_OFFSET, 0,
					SCL_BLACK_OFFSET_RGB_Y, BLACK_OFFSET_RGB_Y,
					SCL_BLACK_OFFSET_CBCR, BLACK_OFFSET_CBCR);
		अन्यथा

			REG_SET_2(SCL_BLACK_OFFSET, 0,
					SCL_BLACK_OFFSET_RGB_Y, BLACK_OFFSET_RGB_Y,
					SCL_BLACK_OFFSET_CBCR, BLACK_OFFSET_RGB_Y);
	पूर्ण

	/* Manually calculate scale ratio and init values */
	dpp1_dscl_set_manual_ratio_init(dpp, scl_data);

	/* HTaps/VTaps */
	REG_SET_4(SCL_TAP_CONTROL, 0,
		SCL_V_NUM_TAPS, scl_data->taps.v_taps - 1,
		SCL_H_NUM_TAPS, scl_data->taps.h_taps - 1,
		SCL_V_NUM_TAPS_C, scl_data->taps.v_taps_c - 1,
		SCL_H_NUM_TAPS_C, scl_data->taps.h_taps_c - 1);

	dpp1_dscl_set_scl_filter(dpp, scl_data, ycbcr);
	PERF_TRACE();
पूर्ण
