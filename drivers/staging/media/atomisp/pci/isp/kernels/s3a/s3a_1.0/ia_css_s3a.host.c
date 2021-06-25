<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#समावेश "ia_css_types.h"
#समावेश "sh_css_defs.h"
#अगर_अघोषित IA_CSS_NO_DEBUG
#समावेश "ia_css_debug.h"
#पूर्ण_अगर
#समावेश "sh_css_frac.h"
#समावेश "assert_support.h"

#समावेश "bh/bh_2/ia_css_bh.host.h"
#समावेश "ia_css_s3a.host.h"

स्थिर काष्ठा ia_css_3a_config शेष_3a_config = अणु
	25559,
	32768,
	7209,
	65535,
	0,
	65535,
	अणु-3344, -6104, -19143, 19143, 6104, 3344, 0पूर्ण,
	अणु1027, 0, -9219, 16384, -9219, 1027, 0पूर्ण
पूर्ण;

अटल अचिन्हित पूर्णांक s3a_raw_bit_depth;

व्योम
ia_css_s3a_configure(अचिन्हित पूर्णांक raw_bit_depth)
अणु
	s3a_raw_bit_depth = raw_bit_depth;
पूर्ण

अटल व्योम
ia_css_ae_encode(
    काष्ठा sh_css_isp_ae_params *to,
    स्थिर काष्ठा ia_css_3a_config *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	/* coefficients to calculate Y */
	to->y_coef_r =
	    uDIGIT_FITTING(from->ae_y_coef_r, 16, SH_CSS_AE_YCOEF_SHIFT);
	to->y_coef_g =
	    uDIGIT_FITTING(from->ae_y_coef_g, 16, SH_CSS_AE_YCOEF_SHIFT);
	to->y_coef_b =
	    uDIGIT_FITTING(from->ae_y_coef_b, 16, SH_CSS_AE_YCOEF_SHIFT);
पूर्ण

अटल व्योम
ia_css_awb_encode(
    काष्ठा sh_css_isp_awb_params *to,
    स्थिर काष्ठा ia_css_3a_config *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	/* AWB level gate */
	to->lg_high_raw =
	    uDIGIT_FITTING(from->awb_lg_high_raw, 16, s3a_raw_bit_depth);
	to->lg_low =
	    uDIGIT_FITTING(from->awb_lg_low, 16, SH_CSS_BAYER_BITS);
	to->lg_high =
	    uDIGIT_FITTING(from->awb_lg_high, 16, SH_CSS_BAYER_BITS);
पूर्ण

अटल व्योम
ia_css_af_encode(
    काष्ठा sh_css_isp_af_params *to,
    स्थिर काष्ठा ia_css_3a_config *from,
    अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक i;
	(व्योम)size;

	/* af fir coefficients */
	क्रम (i = 0; i < 7; ++i) अणु
		to->fir1[i] =
		    sDIGIT_FITTING(from->af_fir1_coef[i], 15,
				   SH_CSS_AF_FIR_SHIFT);
		to->fir2[i] =
		    sDIGIT_FITTING(from->af_fir2_coef[i], 15,
				   SH_CSS_AF_FIR_SHIFT);
	पूर्ण
पूर्ण

व्योम
ia_css_s3a_encode(
    काष्ठा sh_css_isp_s3a_params *to,
    स्थिर काष्ठा ia_css_3a_config *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;

	ia_css_ae_encode(&to->ae,   from, माप(to->ae));
	ia_css_awb_encode(&to->awb, from, माप(to->awb));
	ia_css_af_encode(&to->af,   from, माप(to->af));
पूर्ण

#अगर 0
व्योम
ia_css_process_s3a(
    अचिन्हित पूर्णांक pipe_id,
    स्थिर काष्ठा ia_css_pipeline_stage *stage,
    काष्ठा ia_css_isp_parameters *params)
अणु
	लघु dmem_offset = stage->binary->info->mem_offsets->dmem.s3a;

	निश्चित(params);

	अगर (dmem_offset >= 0) अणु
		ia_css_s3a_encode((काष्ठा sh_css_isp_s3a_params *)
				  &stage->isp_mem_params[IA_CSS_ISP_DMEM0].address[dmem_offset],
				  &params->s3a_config);
		ia_css_bh_encode((काष्ठा sh_css_isp_bh_params *)
				 &stage->isp_mem_params[IA_CSS_ISP_DMEM0].address[dmem_offset],
				 &params->s3a_config);
		params->isp_params_changed = true;
		params->isp_mem_params_changed[pipe_id][stage->stage_num][IA_CSS_ISP_DMEM0] =
		    true;
	पूर्ण

	params->isp_params_changed = true;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित IA_CSS_NO_DEBUG
व्योम
ia_css_ae_dump(
    स्थिर काष्ठा sh_css_isp_ae_params *ae,
    अचिन्हित पूर्णांक level)
अणु
	अगर (!ae) वापस;
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "ae_y_coef_r", ae->y_coef_r);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "ae_y_coef_g", ae->y_coef_g);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "ae_y_coef_b", ae->y_coef_b);
पूर्ण

व्योम
ia_css_awb_dump(
    स्थिर काष्ठा sh_css_isp_awb_params *awb,
    अचिन्हित पूर्णांक level)
अणु
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "awb_lg_high_raw", awb->lg_high_raw);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "awb_lg_low", awb->lg_low);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "awb_lg_high", awb->lg_high);
पूर्ण

व्योम
ia_css_af_dump(
    स्थिर काष्ठा sh_css_isp_af_params *af,
    अचिन्हित पूर्णांक level)
अणु
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "af_fir1[0]", af->fir1[0]);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "af_fir1[1]", af->fir1[1]);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "af_fir1[2]", af->fir1[2]);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "af_fir1[3]", af->fir1[3]);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "af_fir1[4]", af->fir1[4]);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "af_fir1[5]", af->fir1[5]);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "af_fir1[6]", af->fir1[6]);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "af_fir2[0]", af->fir2[0]);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "af_fir2[1]", af->fir2[1]);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "af_fir2[2]", af->fir2[2]);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "af_fir2[3]", af->fir2[3]);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "af_fir2[4]", af->fir2[4]);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "af_fir2[5]", af->fir2[5]);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "af_fir2[6]", af->fir2[6]);
पूर्ण

व्योम
ia_css_s3a_dump(
    स्थिर काष्ठा sh_css_isp_s3a_params *s3a,
    अचिन्हित पूर्णांक level)
अणु
	ia_css_debug_dtrace(level, "S3A Support:\n");
	ia_css_ae_dump(&s3a->ae, level);
	ia_css_awb_dump(&s3a->awb, level);
	ia_css_af_dump(&s3a->af, level);
पूर्ण

व्योम
ia_css_s3a_debug_dtrace(
    स्थिर काष्ठा ia_css_3a_config *config,
    अचिन्हित पूर्णांक level)
अणु
	ia_css_debug_dtrace(level,
			    "config.ae_y_coef_r=%d, config.ae_y_coef_g=%d, config.ae_y_coef_b=%d, config.awb_lg_high_raw=%d, config.awb_lg_low=%d, config.awb_lg_high=%d\n",
			    config->ae_y_coef_r, config->ae_y_coef_g,
			    config->ae_y_coef_b, config->awb_lg_high_raw,
			    config->awb_lg_low, config->awb_lg_high);
पूर्ण
#पूर्ण_अगर

व्योम
ia_css_s3a_hmem_decode(
    काष्ठा ia_css_3a_statistics *host_stats,
    स्थिर काष्ठा ia_css_bh_table *hmem_buf)
अणु
#अगर defined(HAS_NO_HMEM)
	(व्योम)host_stats;
	(व्योम)hmem_buf;
#अन्यथा
	काष्ठा ia_css_3a_rgby_output	*out_ptr;
	पूर्णांक			i;

	/* pixel counts(BQ) क्रम 3A area */
	पूर्णांक count_क्रम_3a;
	पूर्णांक sum_r, dअगरf;

	निश्चित(host_stats);
	निश्चित(host_stats->rgby_data);
	निश्चित(hmem_buf);

	count_क्रम_3a = host_stats->grid.width * host_stats->grid.height
		       * host_stats->grid.bqs_per_grid_cell
		       * host_stats->grid.bqs_per_grid_cell;

	out_ptr = host_stats->rgby_data;

	ia_css_bh_hmem_decode(out_ptr, hmem_buf);

	/* Calculate sum of histogram of R,
	   which should not be less than count_क्रम_3a */
	sum_r = 0;
	क्रम (i = 0; i < HMEM_UNIT_SIZE; i++) अणु
		sum_r += out_ptr[i].r;
	पूर्ण
	अगर (sum_r < count_क्रम_3a) अणु
		/* histogram is invalid */
		वापस;
	पूर्ण

	/* Verअगरy क्रम sum of histogram of R/G/B/Y */
#अगर 0
	अणु
		पूर्णांक sum_g = 0;
		पूर्णांक sum_b = 0;
		पूर्णांक sum_y = 0;

		क्रम (i = 0; i < HMEM_UNIT_SIZE; i++) अणु
			sum_g += out_ptr[i].g;
			sum_b += out_ptr[i].b;
			sum_y += out_ptr[i].y;
		पूर्ण
		अगर (sum_g != sum_r || sum_b != sum_r || sum_y != sum_r) अणु
			/* histogram is invalid */
			वापस;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/*
	 * Limit the histogram area only to 3A area.
	 * In DSP, the histogram of 0 is incremented क्रम pixels
	 * which are outside of 3A area. That amount should be subtracted here.
	 *   hist[0] = hist[0] - ((sum of all hist[]) - (pixel count क्रम 3A area))
	 */
	dअगरf = sum_r - count_क्रम_3a;
	out_ptr[0].r -= dअगरf;
	out_ptr[0].g -= dअगरf;
	out_ptr[0].b -= dअगरf;
	out_ptr[0].y -= dअगरf;
#पूर्ण_अगर
पूर्ण

व्योम
ia_css_s3a_dmem_decode(
    काष्ठा ia_css_3a_statistics *host_stats,
    स्थिर काष्ठा ia_css_3a_output *isp_stats)
अणु
	पूर्णांक isp_width, host_width, height, i;
	काष्ठा ia_css_3a_output *host_ptr;

	निश्चित(host_stats);
	निश्चित(host_stats->data);
	निश्चित(isp_stats);

	isp_width  = host_stats->grid.aligned_width;
	host_width = host_stats->grid.width;
	height     = host_stats->grid.height;
	host_ptr   = host_stats->data;

	/* Getting 3A statistics from DMEM करोes not involve any
	 * transक्रमmation (like the VMEM version), we just copy the data
	 * using a dअगरferent output width. */
	क्रम (i = 0; i < height; i++) अणु
		स_नकल(host_ptr, isp_stats, host_width * माप(*host_ptr));
		isp_stats += isp_width;
		host_ptr += host_width;
	पूर्ण
पूर्ण

/* MW: this is an ISP function */
अटल अंतरभूत पूर्णांक
merge_hi_lo_14(अचिन्हित लघु hi, अचिन्हित लघु lo)
अणु
	पूर्णांक val = (पूर्णांक)((((अचिन्हित पूर्णांक)hi << 14) & 0xfffc000) |
			((अचिन्हित पूर्णांक)lo & 0x3fff));
	वापस val;
पूर्ण

व्योम
ia_css_s3a_vmem_decode(
    काष्ठा ia_css_3a_statistics *host_stats,
    स्थिर u16 *isp_stats_hi,
    स्थिर uपूर्णांक16_t *isp_stats_lo)
अणु
	पूर्णांक out_width, out_height, chunk, rest, kmax, y, x, k, elm_start, elm, ofs;
	स्थिर u16 *hi, *lo;
	काष्ठा ia_css_3a_output *output;

	निश्चित(host_stats);
	निश्चित(host_stats->data);
	निश्चित(isp_stats_hi);
	निश्चित(isp_stats_lo);

	output = host_stats->data;
	out_width  = host_stats->grid.width;
	out_height = host_stats->grid.height;
	hi = isp_stats_hi;
	lo = isp_stats_lo;

	chunk = ISP_VEC_NELEMS >> host_stats->grid.deci_factor_log2;
	chunk = max(chunk, 1);

	क्रम (y = 0; y < out_height; y++) अणु
		elm_start = y * ISP_S3ATBL_HI_LO_STRIDE;
		rest = out_width;
		x = 0;
		जबतक (x < out_width) अणु
			kmax = (rest > chunk) ? chunk : rest;
			ofs = y * out_width + x;
			elm = elm_start + x * माप(*output) / माप(पूर्णांक32_t);
			क्रम (k = 0; k < kmax; k++, elm++) अणु
				output[ofs + k].ae_y    = merge_hi_lo_14(
							      hi[elm + chunk * 0], lo[elm + chunk * 0]);
				output[ofs + k].awb_cnt = merge_hi_lo_14(
							      hi[elm + chunk * 1], lo[elm + chunk * 1]);
				output[ofs + k].awb_gr  = merge_hi_lo_14(
							      hi[elm + chunk * 2], lo[elm + chunk * 2]);
				output[ofs + k].awb_r   = merge_hi_lo_14(
							      hi[elm + chunk * 3], lo[elm + chunk * 3]);
				output[ofs + k].awb_b   = merge_hi_lo_14(
							      hi[elm + chunk * 4], lo[elm + chunk * 4]);
				output[ofs + k].awb_gb  = merge_hi_lo_14(
							      hi[elm + chunk * 5], lo[elm + chunk * 5]);
				output[ofs + k].af_hpf1 = merge_hi_lo_14(
							      hi[elm + chunk * 6], lo[elm + chunk * 6]);
				output[ofs + k].af_hpf2 = merge_hi_lo_14(
							      hi[elm + chunk * 7], lo[elm + chunk * 7]);
			पूर्ण
			x += chunk;
			rest -= chunk;
		पूर्ण
	पूर्ण
पूर्ण
