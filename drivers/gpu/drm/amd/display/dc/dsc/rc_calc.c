<शैली गुरु>

/*
 * Copyright 2017 Advanced Micro Devices, Inc.
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
#समावेश <drm/drm_dsc.h>

#समावेश "os_types.h"
#समावेश "rc_calc.h"
#समावेश "qp_tables.h"

#घोषणा table_hash(mode, bpc, max_min) ((mode << 16) | (bpc << 8) | max_min)

#घोषणा MODE_SELECT(val444, val422, val420) \
	(cm == CM_444 || cm == CM_RGB) ? (val444) : (cm == CM_422 ? (val422) : (val420))


#घोषणा TABLE_CASE(mode, bpc, max)   हाल (table_hash(mode, BPC_##bpc, max)): \
	table = qp_table_##mode##_##bpc##bpc_##max; \
	table_size = माप(qp_table_##mode##_##bpc##bpc_##max)/माप(*qp_table_##mode##_##bpc##bpc_##max); \
	अवरोध


अटल व्योम get_qp_set(qp_set qps, क्रमागत colour_mode cm, क्रमागत bits_per_comp bpc,
		       क्रमागत max_min max_min, भग्न bpp)
अणु
	पूर्णांक mode = MODE_SELECT(444, 422, 420);
	पूर्णांक sel = table_hash(mode, bpc, max_min);
	पूर्णांक table_size = 0;
	पूर्णांक index;
	स्थिर काष्ठा qp_entry *table = 0L;

	// alias क्रमागत
	क्रमागत अणु min = DAL_MM_MIN, max = DAL_MM_MAX पूर्ण;
	चयन (sel) अणु
		TABLE_CASE(444,  8, max);
		TABLE_CASE(444,  8, min);
		TABLE_CASE(444, 10, max);
		TABLE_CASE(444, 10, min);
		TABLE_CASE(444, 12, max);
		TABLE_CASE(444, 12, min);
		TABLE_CASE(422,  8, max);
		TABLE_CASE(422,  8, min);
		TABLE_CASE(422, 10, max);
		TABLE_CASE(422, 10, min);
		TABLE_CASE(422, 12, max);
		TABLE_CASE(422, 12, min);
		TABLE_CASE(420,  8, max);
		TABLE_CASE(420,  8, min);
		TABLE_CASE(420, 10, max);
		TABLE_CASE(420, 10, min);
		TABLE_CASE(420, 12, max);
		TABLE_CASE(420, 12, min);
	पूर्ण

	अगर (table == 0)
		वापस;

	index = (bpp - table[0].bpp) * 2;

	/* requested size is bigger than the table */
	अगर (index >= table_size) अणु
		dm_error("ERROR: Requested rc_calc to find a bpp entry that exceeds the table size\n");
		वापस;
	पूर्ण

	स_नकल(qps, table[index].qps, माप(qp_set));
पूर्ण

अटल द्विगुन dsc_roundf(द्विगुन num)
अणु
	अगर (num < 0.0)
		num = num - 0.5;
	अन्यथा
		num = num + 0.5;

	वापस (पूर्णांक)(num);
पूर्ण

अटल द्विगुन dsc_उच्चमान(द्विगुन num)
अणु
	द्विगुन retval = (पूर्णांक)num;

	अगर (retval != num && num > 0)
		retval = num + 1;

	वापस (पूर्णांक)retval;
पूर्ण

अटल व्योम get_ofs_set(qp_set ofs, क्रमागत colour_mode mode, भग्न bpp)
अणु
	पूर्णांक   *p = ofs;

	अगर (mode == CM_444 || mode == CM_RGB) अणु
		*p++ = (bpp <=  6) ? (0) : ((((bpp >=  8) && (bpp <= 12))) ? (2) : ((bpp >= 15) ? (10) : ((((bpp > 6) && (bpp < 8))) ? (0 + dsc_roundf((bpp -  6) * (2 / 2.0))) : (2 + dsc_roundf((bpp - 12) * (8 / 3.0))))));
		*p++ = (bpp <=  6) ? (-2) : ((((bpp >=  8) && (bpp <= 12))) ? (0) : ((bpp >= 15) ? (8) : ((((bpp > 6) && (bpp < 8))) ? (-2 + dsc_roundf((bpp -  6) * (2 / 2.0))) : (0 + dsc_roundf((bpp - 12) * (8 / 3.0))))));
		*p++ = (bpp <=  6) ? (-2) : ((((bpp >=  8) && (bpp <= 12))) ? (0) : ((bpp >= 15) ? (6) : ((((bpp > 6) && (bpp < 8))) ? (-2 + dsc_roundf((bpp -  6) * (2 / 2.0))) : (0 + dsc_roundf((bpp - 12) * (6 / 3.0))))));
		*p++ = (bpp <=  6) ? (-4) : ((((bpp >=  8) && (bpp <= 12))) ? (-2) : ((bpp >= 15) ? (4) : ((((bpp > 6) && (bpp < 8))) ? (-4 + dsc_roundf((bpp -  6) * (2 / 2.0))) : (-2 + dsc_roundf((bpp - 12) * (6 / 3.0))))));
		*p++ = (bpp <=  6) ? (-6) : ((((bpp >=  8) && (bpp <= 12))) ? (-4) : ((bpp >= 15) ? (2) : ((((bpp > 6) && (bpp < 8))) ? (-6 + dsc_roundf((bpp -  6) * (2 / 2.0))) : (-4 + dsc_roundf((bpp - 12) * (6 / 3.0))))));
		*p++ = (bpp <= 12) ? (-6) : ((bpp >= 15) ? (0) : (-6 + dsc_roundf((bpp - 12) * (6 / 3.0))));
		*p++ = (bpp <= 12) ? (-8) : ((bpp >= 15) ? (-2) : (-8 + dsc_roundf((bpp - 12) * (6 / 3.0))));
		*p++ = (bpp <= 12) ? (-8) : ((bpp >= 15) ? (-4) : (-8 + dsc_roundf((bpp - 12) * (4 / 3.0))));
		*p++ = (bpp <= 12) ? (-8) : ((bpp >= 15) ? (-6) : (-8 + dsc_roundf((bpp - 12) * (2 / 3.0))));
		*p++ = (bpp <= 12) ? (-10) : ((bpp >= 15) ? (-8) : (-10 + dsc_roundf((bpp - 12) * (2 / 3.0))));
		*p++ = -10;
		*p++ = (bpp <=  6) ? (-12) : ((bpp >=  8) ? (-10) : (-12 + dsc_roundf((bpp -  6) * (2 / 2.0))));
		*p++ = -12;
		*p++ = -12;
		*p++ = -12;
	पूर्ण अन्यथा अगर (mode == CM_422) अणु
		*p++ = (bpp <=  8) ? (2) : ((bpp >= 10) ? (10) : (2 + dsc_roundf((bpp -  8) * (8 / 2.0))));
		*p++ = (bpp <=  8) ? (0) : ((bpp >= 10) ? (8) : (0 + dsc_roundf((bpp -  8) * (8 / 2.0))));
		*p++ = (bpp <=  8) ? (0) : ((bpp >= 10) ? (6) : (0 + dsc_roundf((bpp -  8) * (6 / 2.0))));
		*p++ = (bpp <=  8) ? (-2) : ((bpp >= 10) ? (4) : (-2 + dsc_roundf((bpp -  8) * (6 / 2.0))));
		*p++ = (bpp <=  8) ? (-4) : ((bpp >= 10) ? (2) : (-4 + dsc_roundf((bpp -  8) * (6 / 2.0))));
		*p++ = (bpp <=  8) ? (-6) : ((bpp >= 10) ? (0) : (-6 + dsc_roundf((bpp -  8) * (6 / 2.0))));
		*p++ = (bpp <=  8) ? (-8) : ((bpp >= 10) ? (-2) : (-8 + dsc_roundf((bpp -  8) * (6 / 2.0))));
		*p++ = (bpp <=  8) ? (-8) : ((bpp >= 10) ? (-4) : (-8 + dsc_roundf((bpp -  8) * (4 / 2.0))));
		*p++ = (bpp <=  8) ? (-8) : ((bpp >= 10) ? (-6) : (-8 + dsc_roundf((bpp -  8) * (2 / 2.0))));
		*p++ = (bpp <=  8) ? (-10) : ((bpp >= 10) ? (-8) : (-10 + dsc_roundf((bpp -  8) * (2 / 2.0))));
		*p++ = -10;
		*p++ = (bpp <=  6) ? (-12) : ((bpp >= 7) ? (-10) : (-12 + dsc_roundf((bpp -  6) * (2.0 / 1))));
		*p++ = -12;
		*p++ = -12;
		*p++ = -12;
	पूर्ण अन्यथा अणु
		*p++ = (bpp <=  6) ? (2) : ((bpp >=  8) ? (10) : (2 + dsc_roundf((bpp -  6) * (8 / 2.0))));
		*p++ = (bpp <=  6) ? (0) : ((bpp >=  8) ? (8) : (0 + dsc_roundf((bpp -  6) * (8 / 2.0))));
		*p++ = (bpp <=  6) ? (0) : ((bpp >=  8) ? (6) : (0 + dsc_roundf((bpp -  6) * (6 / 2.0))));
		*p++ = (bpp <=  6) ? (-2) : ((bpp >=  8) ? (4) : (-2 + dsc_roundf((bpp -  6) * (6 / 2.0))));
		*p++ = (bpp <=  6) ? (-4) : ((bpp >=  8) ? (2) : (-4 + dsc_roundf((bpp -  6) * (6 / 2.0))));
		*p++ = (bpp <=  6) ? (-6) : ((bpp >=  8) ? (0) : (-6 + dsc_roundf((bpp -  6) * (6 / 2.0))));
		*p++ = (bpp <=  6) ? (-8) : ((bpp >=  8) ? (-2) : (-8 + dsc_roundf((bpp -  6) * (6 / 2.0))));
		*p++ = (bpp <=  6) ? (-8) : ((bpp >=  8) ? (-4) : (-8 + dsc_roundf((bpp -  6) * (4 / 2.0))));
		*p++ = (bpp <=  6) ? (-8) : ((bpp >=  8) ? (-6) : (-8 + dsc_roundf((bpp -  6) * (2 / 2.0))));
		*p++ = (bpp <=  6) ? (-10) : ((bpp >=  8) ? (-8) : (-10 + dsc_roundf((bpp -  6) * (2 / 2.0))));
		*p++ = -10;
		*p++ = (bpp <=  4) ? (-12) : ((bpp >=  5) ? (-10) : (-12 + dsc_roundf((bpp -  4) * (2 / 1.0))));
		*p++ = -12;
		*p++ = -12;
		*p++ = -12;
	पूर्ण
पूर्ण

अटल पूर्णांक median3(पूर्णांक a, पूर्णांक b, पूर्णांक c)
अणु
	अगर (a > b)
		swap(a, b);
	अगर (b > c)
		swap(b, c);
	अगर (a > b)
		swap(b, c);

	वापस b;
पूर्ण

अटल व्योम _करो_calc_rc_params(काष्ठा rc_params *rc, क्रमागत colour_mode cm,
			       क्रमागत bits_per_comp bpc, u16 drm_bpp,
			       bool is_navite_422_or_420,
			       पूर्णांक slice_width, पूर्णांक slice_height,
			       पूर्णांक minor_version)
अणु
	भग्न bpp;
	भग्न bpp_group;
	भग्न initial_xmit_delay_factor;
	पूर्णांक padding_pixels;
	पूर्णांक i;

	bpp = ((भग्न)drm_bpp / 16.0);
	/* in native_422 or native_420 modes, the bits_per_pixel is द्विगुन the
	 * target bpp (the latter is what calc_rc_params expects)
	 */
	अगर (is_navite_422_or_420)
		bpp /= 2.0;

	rc->rc_quant_incr_limit0 = ((bpc == BPC_8) ? 11 : (bpc == BPC_10 ? 15 : 19)) - ((minor_version == 1 && cm == CM_444) ? 1 : 0);
	rc->rc_quant_incr_limit1 = ((bpc == BPC_8) ? 11 : (bpc == BPC_10 ? 15 : 19)) - ((minor_version == 1 && cm == CM_444) ? 1 : 0);

	bpp_group = MODE_SELECT(bpp, bpp * 2.0, bpp * 2.0);

	चयन (cm) अणु
	हाल CM_420:
		rc->initial_fullness_offset = (bpp >=  6) ? (2048) : ((bpp <=  4) ? (6144) : ((((bpp >  4) && (bpp <=  5))) ? (6144 - dsc_roundf((bpp - 4) * (512))) : (5632 - dsc_roundf((bpp -  5) * (3584)))));
		rc->first_line_bpg_offset   = median3(0, (12 + (पूर्णांक) (0.09 *  min(34, slice_height - 8))), (पूर्णांक)((3 * bpc * 3) - (3 * bpp_group)));
		rc->second_line_bpg_offset  = median3(0, 12, (पूर्णांक)((3 * bpc * 3) - (3 * bpp_group)));
		अवरोध;
	हाल CM_422:
		rc->initial_fullness_offset = (bpp >=  8) ? (2048) : ((bpp <=  7) ? (5632) : (5632 - dsc_roundf((bpp - 7) * (3584))));
		rc->first_line_bpg_offset   = median3(0, (12 + (पूर्णांक) (0.09 *  min(34, slice_height - 8))), (पूर्णांक)((3 * bpc * 4) - (3 * bpp_group)));
		rc->second_line_bpg_offset  = 0;
		अवरोध;
	हाल CM_444:
	हाल CM_RGB:
		rc->initial_fullness_offset = (bpp >= 12) ? (2048) : ((bpp <=  8) ? (6144) : ((((bpp >  8) && (bpp <= 10))) ? (6144 - dsc_roundf((bpp - 8) * (512 / 2))) : (5632 - dsc_roundf((bpp - 10) * (3584 / 2)))));
		rc->first_line_bpg_offset   = median3(0, (12 + (पूर्णांक) (0.09 *  min(34, slice_height - 8))), (पूर्णांक)(((3 * bpc + (cm == CM_444 ? 0 : 2)) * 3) - (3 * bpp_group)));
		rc->second_line_bpg_offset  = 0;
		अवरोध;
	पूर्ण

	initial_xmit_delay_factor = (cm == CM_444 || cm == CM_RGB) ? 1.0 : 2.0;
	rc->initial_xmit_delay = dsc_roundf(8192.0/2.0/bpp/initial_xmit_delay_factor);

	अगर (cm == CM_422 || cm == CM_420)
		slice_width /= 2;

	padding_pixels = ((slice_width % 3) != 0) ? (3 - (slice_width % 3)) * (rc->initial_xmit_delay / slice_width) : 0;
	अगर (3 * bpp_group >= (((rc->initial_xmit_delay + 2) / 3) * (3 + (cm == CM_422)))) अणु
		अगर ((rc->initial_xmit_delay + padding_pixels) % 3 == 1)
			rc->initial_xmit_delay++;
	पूर्ण

	rc->flatness_min_qp     = ((bpc == BPC_8) ?  (3) : ((bpc == BPC_10) ? (7)  : (11))) - ((minor_version == 1 && cm == CM_444) ? 1 : 0);
	rc->flatness_max_qp     = ((bpc == BPC_8) ? (12) : ((bpc == BPC_10) ? (16) : (20))) - ((minor_version == 1 && cm == CM_444) ? 1 : 0);
	rc->flatness_det_thresh = 2 << (bpc - 8);

	get_qp_set(rc->qp_min, cm, bpc, DAL_MM_MIN, bpp);
	get_qp_set(rc->qp_max, cm, bpc, DAL_MM_MAX, bpp);
	अगर (cm == CM_444 && minor_version == 1) अणु
		क्रम (i = 0; i < QP_SET_SIZE; ++i) अणु
			rc->qp_min[i] = rc->qp_min[i] > 0 ? rc->qp_min[i] - 1 : 0;
			rc->qp_max[i] = rc->qp_max[i] > 0 ? rc->qp_max[i] - 1 : 0;
		पूर्ण
	पूर्ण
	get_ofs_set(rc->ofs, cm, bpp);

	/* fixed parameters */
	rc->rc_model_size    = 8192;
	rc->rc_edge_factor   = 6;
	rc->rc_tgt_offset_hi = 3;
	rc->rc_tgt_offset_lo = 3;

	rc->rc_buf_thresh[0] = 896;
	rc->rc_buf_thresh[1] = 1792;
	rc->rc_buf_thresh[2] = 2688;
	rc->rc_buf_thresh[3] = 3584;
	rc->rc_buf_thresh[4] = 4480;
	rc->rc_buf_thresh[5] = 5376;
	rc->rc_buf_thresh[6] = 6272;
	rc->rc_buf_thresh[7] = 6720;
	rc->rc_buf_thresh[8] = 7168;
	rc->rc_buf_thresh[9] = 7616;
	rc->rc_buf_thresh[10] = 7744;
	rc->rc_buf_thresh[11] = 7872;
	rc->rc_buf_thresh[12] = 8000;
	rc->rc_buf_thresh[13] = 8064;
पूर्ण

अटल u32 _करो_bytes_per_pixel_calc(पूर्णांक slice_width, u16 drm_bpp,
				    bool is_navite_422_or_420)
अणु
	भग्न bpp;
	u32 bytes_per_pixel;
	द्विगुन d_bytes_per_pixel;

	bpp = ((भग्न)drm_bpp / 16.0);
	d_bytes_per_pixel = dsc_उच्चमान(bpp * slice_width / 8.0) / slice_width;
	// TODO: Make sure the क्रमmula क्रम calculating this is precise (उच्चमानing
	// vs. न्यूनमान, and at what poपूर्णांक they should be applied)
	अगर (is_navite_422_or_420)
		d_bytes_per_pixel /= 2;

	bytes_per_pixel = (u32)dsc_उच्चमान(d_bytes_per_pixel * 0x10000000);

	वापस bytes_per_pixel;
पूर्ण

अटल u32 _करो_calc_dsc_bpp_x16(u32 stream_bandwidth_kbps, u32 pix_clk_100hz,
				u32 bpp_increment_भाग)
अणु
	u32 dsc_target_bpp_x16;
	भग्न f_dsc_target_bpp;
	भग्न f_stream_bandwidth_100bps;
	// bpp_increment_भाग is actually precision
	u32 precision = bpp_increment_भाग;

	f_stream_bandwidth_100bps = stream_bandwidth_kbps * 10.0f;
	f_dsc_target_bpp = f_stream_bandwidth_100bps / pix_clk_100hz;

	// Round करोwn to the nearest precision stop to bring it पूर्णांकo DSC spec
	// range
	dsc_target_bpp_x16 = (u32)(f_dsc_target_bpp * precision);
	dsc_target_bpp_x16 = (dsc_target_bpp_x16 * 16) / precision;

	वापस dsc_target_bpp_x16;
पूर्ण

/**
 * calc_rc_params - पढ़ोs the user's cmdline mode
 * @rc: DC पूर्णांकernal DSC parameters
 * @pps: DRM काष्ठा with all required DSC values
 *
 * This function expects a drm_dsc_config data काष्ठा with all the required DSC
 * values previously filled out by our driver and based on this inक्रमmation it
 * computes some of the DSC values.
 *
 * @note This calculation requires भग्न poपूर्णांक operation, most of it executes
 * under kernel_fpu_अणुbegin,endपूर्ण.
 */
व्योम calc_rc_params(काष्ठा rc_params *rc, स्थिर काष्ठा drm_dsc_config *pps)
अणु
	क्रमागत colour_mode mode;
	क्रमागत bits_per_comp bpc;
	bool is_navite_422_or_420;
	u16 drm_bpp = pps->bits_per_pixel;
	पूर्णांक slice_width  = pps->slice_width;
	पूर्णांक slice_height = pps->slice_height;

	mode = pps->convert_rgb ? CM_RGB : (pps->simple_422  ? CM_444 :
					   (pps->native_422  ? CM_422 :
					    pps->native_420  ? CM_420 : CM_444));
	bpc = (pps->bits_per_component == 8) ? BPC_8 : (pps->bits_per_component == 10)
					     ? BPC_10 : BPC_12;

	is_navite_422_or_420 = pps->native_422 || pps->native_420;

	DC_FP_START();
	_करो_calc_rc_params(rc, mode, bpc, drm_bpp, is_navite_422_or_420,
			   slice_width, slice_height,
			   pps->dsc_version_minor);
	DC_FP_END();
पूर्ण

/**
 * calc_dsc_bytes_per_pixel - calculate bytes per pixel
 * @pps: DRM काष्ठा with all required DSC values
 *
 * Based on the inक्रमmation inside drm_dsc_config, this function calculates the
 * total of bytes per pixel.
 *
 * @note This calculation requires भग्न poपूर्णांक operation, most of it executes
 * under kernel_fpu_अणुbegin,endपूर्ण.
 *
 * Return:
 * Return the number of bytes per pixel
 */
u32 calc_dsc_bytes_per_pixel(स्थिर काष्ठा drm_dsc_config *pps)

अणु
	u32 ret;
	u16 drm_bpp = pps->bits_per_pixel;
	पूर्णांक slice_width  = pps->slice_width;
	bool is_navite_422_or_420 = pps->native_422 || pps->native_420;

	DC_FP_START();
	ret = _करो_bytes_per_pixel_calc(slice_width, drm_bpp,
				       is_navite_422_or_420);
	DC_FP_END();
	वापस ret;
पूर्ण

/**
 * calc_dsc_bpp_x16 - retrieve the dsc bits per pixel
 * @stream_bandwidth_kbps:
 * @pix_clk_100hz:
 * @bpp_increment_भाग:
 *
 * Calculate the total of bits per pixel क्रम DSC configuration.
 *
 * @note This calculation requires भग्न poपूर्णांक operation, most of it executes
 * under kernel_fpu_अणुbegin,endपूर्ण.
 */
u32 calc_dsc_bpp_x16(u32 stream_bandwidth_kbps, u32 pix_clk_100hz,
		     u32 bpp_increment_भाग)
अणु
	u32 dsc_bpp;

	DC_FP_START();
	dsc_bpp =  _करो_calc_dsc_bpp_x16(stream_bandwidth_kbps, pix_clk_100hz,
					bpp_increment_भाग);
	DC_FP_END();
	वापस dsc_bpp;
पूर्ण
