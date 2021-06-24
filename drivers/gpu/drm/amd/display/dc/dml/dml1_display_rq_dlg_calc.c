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

#समावेश "dml1_display_rq_dlg_calc.h"
#समावेश "display_mode_lib.h"

#समावेश "dml_inline_defs.h"

/*
 * NOTE:
 *   This file is gcc-parseable HW gospel, coming straight from HW engineers.
 *
 * It करोesn't adhere to Linux kernel style and someबार will करो things in odd
 * ways. Unless there is something clearly wrong with it the code should
 * reमुख्य as-is as it provides us with a guarantee from HW that it is correct.
 */

अटल अचिन्हित पूर्णांक get_bytes_per_element(क्रमागत source_क्रमmat_class source_क्रमmat, bool is_chroma)
अणु
	अचिन्हित पूर्णांक ret_val = 0;

	अगर (source_क्रमmat == dm_444_16) अणु
		अगर (!is_chroma)
			ret_val = 2;
	पूर्ण अन्यथा अगर (source_क्रमmat == dm_444_32) अणु
		अगर (!is_chroma)
			ret_val = 4;
	पूर्ण अन्यथा अगर (source_क्रमmat == dm_444_64) अणु
		अगर (!is_chroma)
			ret_val = 8;
	पूर्ण अन्यथा अगर (source_क्रमmat == dm_420_8) अणु
		अगर (is_chroma)
			ret_val = 2;
		अन्यथा
			ret_val = 1;
	पूर्ण अन्यथा अगर (source_क्रमmat == dm_420_10) अणु
		अगर (is_chroma)
			ret_val = 4;
		अन्यथा
			ret_val = 2;
	पूर्ण
	वापस ret_val;
पूर्ण

अटल bool is_dual_plane(क्रमागत source_क्रमmat_class source_क्रमmat)
अणु
	bool ret_val = 0;

	अगर ((source_क्रमmat == dm_420_8) || (source_क्रमmat == dm_420_10))
		ret_val = 1;

	वापस ret_val;
पूर्ण

अटल व्योम get_blk256_size(
		अचिन्हित पूर्णांक *blk256_width,
		अचिन्हित पूर्णांक *blk256_height,
		अचिन्हित पूर्णांक bytes_per_element)
अणु
	अगर (bytes_per_element == 1) अणु
		*blk256_width = 16;
		*blk256_height = 16;
	पूर्ण अन्यथा अगर (bytes_per_element == 2) अणु
		*blk256_width = 16;
		*blk256_height = 8;
	पूर्ण अन्यथा अगर (bytes_per_element == 4) अणु
		*blk256_width = 8;
		*blk256_height = 8;
	पूर्ण अन्यथा अगर (bytes_per_element == 8) अणु
		*blk256_width = 8;
		*blk256_height = 4;
	पूर्ण
पूर्ण

अटल द्विगुन get_refcyc_per_delivery(
		काष्ठा display_mode_lib *mode_lib,
		द्विगुन refclk_freq_in_mhz,
		द्विगुन pclk_freq_in_mhz,
		अचिन्हित पूर्णांक recout_width,
		द्विगुन vratio,
		द्विगुन hscale_pixel_rate,
		अचिन्हित पूर्णांक delivery_width,
		अचिन्हित पूर्णांक req_per_swath_ub)
अणु
	द्विगुन refcyc_per_delivery = 0.0;

	अगर (vratio <= 1.0) अणु
		refcyc_per_delivery = (द्विगुन) refclk_freq_in_mhz * (द्विगुन) recout_width
				/ pclk_freq_in_mhz / (द्विगुन) req_per_swath_ub;
	पूर्ण अन्यथा अणु
		refcyc_per_delivery = (द्विगुन) refclk_freq_in_mhz * (द्विगुन) delivery_width
				/ (द्विगुन) hscale_pixel_rate / (द्विगुन) req_per_swath_ub;
	पूर्ण

	DTRACE("DLG: %s: refclk_freq_in_mhz = %3.2f", __func__, refclk_freq_in_mhz);
	DTRACE("DLG: %s: pclk_freq_in_mhz   = %3.2f", __func__, pclk_freq_in_mhz);
	DTRACE("DLG: %s: recout_width       = %d", __func__, recout_width);
	DTRACE("DLG: %s: vratio             = %3.2f", __func__, vratio);
	DTRACE("DLG: %s: req_per_swath_ub   = %d", __func__, req_per_swath_ub);
	DTRACE("DLG: %s: refcyc_per_delivery= %3.2f", __func__, refcyc_per_delivery);

	वापस refcyc_per_delivery;

पूर्ण

अटल द्विगुन get_vratio_pre(
		काष्ठा display_mode_lib *mode_lib,
		अचिन्हित पूर्णांक max_num_sw,
		अचिन्हित पूर्णांक max_partial_sw,
		अचिन्हित पूर्णांक swath_height,
		द्विगुन vinit,
		द्विगुन l_sw)
अणु
	द्विगुन prefill = dml_न्यूनमान(vinit, 1);
	द्विगुन vratio_pre = 1.0;

	vratio_pre = (max_num_sw * swath_height + max_partial_sw) / l_sw;

	अगर (swath_height > 4) अणु
		द्विगुन पंचांगp0 = (max_num_sw * swath_height) / (l_sw - (prefill - 3.0) / 2.0);

		अगर (पंचांगp0 > vratio_pre)
			vratio_pre = पंचांगp0;
	पूर्ण

	DTRACE("DLG: %s: max_num_sw        = %0d", __func__, max_num_sw);
	DTRACE("DLG: %s: max_partial_sw    = %0d", __func__, max_partial_sw);
	DTRACE("DLG: %s: swath_height      = %0d", __func__, swath_height);
	DTRACE("DLG: %s: vinit             = %3.2f", __func__, vinit);
	DTRACE("DLG: %s: vratio_pre        = %3.2f", __func__, vratio_pre);

	अगर (vratio_pre < 1.0) अणु
		DTRACE("WARNING_DLG: %s:  vratio_pre=%3.2f < 1.0, set to 1.0", __func__, vratio_pre);
		vratio_pre = 1.0;
	पूर्ण

	अगर (vratio_pre > 4.0) अणु
		DTRACE(
				"WARNING_DLG: %s:  vratio_pre=%3.2f > 4.0 (max scaling ratio). set to 4.0",
				__func__,
				vratio_pre);
		vratio_pre = 4.0;
	पूर्ण

	वापस vratio_pre;
पूर्ण

अटल व्योम get_swath_need(
		काष्ठा display_mode_lib *mode_lib,
		अचिन्हित पूर्णांक *max_num_sw,
		अचिन्हित पूर्णांक *max_partial_sw,
		अचिन्हित पूर्णांक swath_height,
		द्विगुन vinit)
अणु
	द्विगुन prefill = dml_न्यूनमान(vinit, 1);
	अचिन्हित पूर्णांक max_partial_sw_पूर्णांक;

	DTRACE("DLG: %s: swath_height      = %0d", __func__, swath_height);
	DTRACE("DLG: %s: vinit             = %3.2f", __func__, vinit);

	ASSERT(prefill > 0.0 && prefill <= 8.0);

	*max_num_sw = (अचिन्हित पूर्णांक) (dml_उच्चमान((prefill - 1.0) / (द्विगुन) swath_height, 1) + 1.0); /* prefill has to be >= 1 */
	max_partial_sw_पूर्णांक =
			(prefill == 1) ?
					(swath_height - 1) :
					((अचिन्हित पूर्णांक) (prefill - 2.0) % swath_height);
	*max_partial_sw = (max_partial_sw_पूर्णांक < 1) ? 1 : max_partial_sw_पूर्णांक; /* ensure minimum of 1 is used */

	DTRACE("DLG: %s: max_num_sw        = %0d", __func__, *max_num_sw);
	DTRACE("DLG: %s: max_partial_sw    = %0d", __func__, *max_partial_sw);
पूर्ण

अटल अचिन्हित पूर्णांक get_blk_size_bytes(स्थिर क्रमागत source_macro_tile_size tile_size)
अणु
	अगर (tile_size == dm_256k_tile)
		वापस (256 * 1024);
	अन्यथा अगर (tile_size == dm_64k_tile)
		वापस (64 * 1024);
	अन्यथा
		वापस (4 * 1024);
पूर्ण

अटल व्योम extract_rq_sizing_regs(
		काष्ठा display_mode_lib *mode_lib,
		काष्ठा _vcs_dpi_display_data_rq_regs_st *rq_regs,
		स्थिर काष्ठा _vcs_dpi_display_data_rq_sizing_params_st rq_sizing)
अणु
	DTRACE("DLG: %s: rq_sizing param", __func__);
	prपूर्णांक__data_rq_sizing_params_st(mode_lib, rq_sizing);

	rq_regs->chunk_size = dml_log2(rq_sizing.chunk_bytes) - 10;

	अगर (rq_sizing.min_chunk_bytes == 0)
		rq_regs->min_chunk_size = 0;
	अन्यथा
		rq_regs->min_chunk_size = dml_log2(rq_sizing.min_chunk_bytes) - 8 + 1;

	rq_regs->meta_chunk_size = dml_log2(rq_sizing.meta_chunk_bytes) - 10;
	अगर (rq_sizing.min_meta_chunk_bytes == 0)
		rq_regs->min_meta_chunk_size = 0;
	अन्यथा
		rq_regs->min_meta_chunk_size = dml_log2(rq_sizing.min_meta_chunk_bytes) - 6 + 1;

	rq_regs->dpte_group_size = dml_log2(rq_sizing.dpte_group_bytes) - 6;
	rq_regs->mpte_group_size = dml_log2(rq_sizing.mpte_group_bytes) - 6;
पूर्ण

व्योम dml1_extract_rq_regs(
		काष्ठा display_mode_lib *mode_lib,
		काष्ठा _vcs_dpi_display_rq_regs_st *rq_regs,
		स्थिर काष्ठा _vcs_dpi_display_rq_params_st rq_param)
अणु
	अचिन्हित पूर्णांक detile_buf_size_in_bytes = mode_lib->ip.det_buffer_size_kbytes * 1024;
	अचिन्हित पूर्णांक detile_buf_plane1_addr = 0;

	extract_rq_sizing_regs(mode_lib, &(rq_regs->rq_regs_l), rq_param.sizing.rq_l);
	अगर (rq_param.yuv420)
		extract_rq_sizing_regs(mode_lib, &(rq_regs->rq_regs_c), rq_param.sizing.rq_c);

	rq_regs->rq_regs_l.swath_height = dml_log2(rq_param.dlg.rq_l.swath_height);
	rq_regs->rq_regs_c.swath_height = dml_log2(rq_param.dlg.rq_c.swath_height);

	/* TODO: take the max between luma, chroma chunk size?
	 * okay क्रम now, as we are setting chunk_bytes to 8kb anyways
	 */
	अगर (rq_param.sizing.rq_l.chunk_bytes >= 32 * 1024) अणु /*32kb */
		rq_regs->drq_expansion_mode = 0;
	पूर्ण अन्यथा अणु
		rq_regs->drq_expansion_mode = 2;
	पूर्ण
	rq_regs->prq_expansion_mode = 1;
	rq_regs->mrq_expansion_mode = 1;
	rq_regs->crq_expansion_mode = 1;

	अगर (rq_param.yuv420) अणु
		अगर ((द्विगुन) rq_param.misc.rq_l.stored_swath_bytes
				/ (द्विगुन) rq_param.misc.rq_c.stored_swath_bytes <= 1.5) अणु
			detile_buf_plane1_addr = (detile_buf_size_in_bytes / 2.0 / 64.0); /* half to chroma */
		पूर्ण अन्यथा अणु
			detile_buf_plane1_addr = dml_round_to_multiple(
					(अचिन्हित पूर्णांक) ((2.0 * detile_buf_size_in_bytes) / 3.0),
					256,
					0) / 64.0; /* 2/3 to chroma */
		पूर्ण
	पूर्ण
	rq_regs->plane1_base_address = detile_buf_plane1_addr;
पूर्ण

अटल व्योम handle_det_buf_split(
		काष्ठा display_mode_lib *mode_lib,
		काष्ठा _vcs_dpi_display_rq_params_st *rq_param,
		स्थिर काष्ठा _vcs_dpi_display_pipe_source_params_st pipe_src_param)
अणु
	अचिन्हित पूर्णांक total_swath_bytes = 0;
	अचिन्हित पूर्णांक swath_bytes_l = 0;
	अचिन्हित पूर्णांक swath_bytes_c = 0;
	अचिन्हित पूर्णांक full_swath_bytes_packed_l = 0;
	अचिन्हित पूर्णांक full_swath_bytes_packed_c = 0;
	bool req128_l = 0;
	bool req128_c = 0;
	bool surf_linear = (pipe_src_param.sw_mode == dm_sw_linear);
	bool surf_vert = (pipe_src_param.source_scan == dm_vert);
	अचिन्हित पूर्णांक log2_swath_height_l = 0;
	अचिन्हित पूर्णांक log2_swath_height_c = 0;
	अचिन्हित पूर्णांक detile_buf_size_in_bytes = mode_lib->ip.det_buffer_size_kbytes * 1024;

	full_swath_bytes_packed_l = rq_param->misc.rq_l.full_swath_bytes;
	full_swath_bytes_packed_c = rq_param->misc.rq_c.full_swath_bytes;

	अगर (rq_param->yuv420_10bpc) अणु
		full_swath_bytes_packed_l = dml_round_to_multiple(
				rq_param->misc.rq_l.full_swath_bytes * 2 / 3,
				256,
				1) + 256;
		full_swath_bytes_packed_c = dml_round_to_multiple(
				rq_param->misc.rq_c.full_swath_bytes * 2 / 3,
				256,
				1) + 256;
	पूर्ण

	अगर (rq_param->yuv420) अणु
		total_swath_bytes = 2 * full_swath_bytes_packed_l + 2 * full_swath_bytes_packed_c;

		अगर (total_swath_bytes <= detile_buf_size_in_bytes) अणु /*full 256b request */
			req128_l = 0;
			req128_c = 0;
			swath_bytes_l = full_swath_bytes_packed_l;
			swath_bytes_c = full_swath_bytes_packed_c;
		पूर्ण अन्यथा अणु /*128b request (क्रम luma only क्रम yuv420 8bpc) */
			req128_l = 1;
			req128_c = 0;
			swath_bytes_l = full_swath_bytes_packed_l / 2;
			swath_bytes_c = full_swath_bytes_packed_c;
		पूर्ण

		/* Bug workaround, luma and chroma req size needs to be the same. (see: DEGVIDCN10-137)
		 * TODO: Remove after rtl fix
		 */
		अगर (req128_l == 1) अणु
			req128_c = 1;
			DTRACE("DLG: %s: bug workaround DEGVIDCN10-137", __func__);
		पूर्ण

		/* Note: assumption, the config that pass in will fit पूर्णांकo
		 *       the detiled buffer.
		 */
	पूर्ण अन्यथा अणु
		total_swath_bytes = 2 * full_swath_bytes_packed_l;

		अगर (total_swath_bytes <= detile_buf_size_in_bytes)
			req128_l = 0;
		अन्यथा
			req128_l = 1;

		swath_bytes_l = total_swath_bytes;
		swath_bytes_c = 0;
	पूर्ण
	rq_param->misc.rq_l.stored_swath_bytes = swath_bytes_l;
	rq_param->misc.rq_c.stored_swath_bytes = swath_bytes_c;

	अगर (surf_linear) अणु
		log2_swath_height_l = 0;
		log2_swath_height_c = 0;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक swath_height_l;
		अचिन्हित पूर्णांक swath_height_c;

		अगर (!surf_vert) अणु
			swath_height_l = rq_param->misc.rq_l.blk256_height;
			swath_height_c = rq_param->misc.rq_c.blk256_height;
		पूर्ण अन्यथा अणु
			swath_height_l = rq_param->misc.rq_l.blk256_width;
			swath_height_c = rq_param->misc.rq_c.blk256_width;
		पूर्ण

		अगर (swath_height_l > 0)
			log2_swath_height_l = dml_log2(swath_height_l);

		अगर (req128_l && log2_swath_height_l > 0)
			log2_swath_height_l -= 1;

		अगर (swath_height_c > 0)
			log2_swath_height_c = dml_log2(swath_height_c);

		अगर (req128_c && log2_swath_height_c > 0)
			log2_swath_height_c -= 1;
	पूर्ण

	rq_param->dlg.rq_l.swath_height = 1 << log2_swath_height_l;
	rq_param->dlg.rq_c.swath_height = 1 << log2_swath_height_c;

	DTRACE("DLG: %s: req128_l = %0d", __func__, req128_l);
	DTRACE("DLG: %s: req128_c = %0d", __func__, req128_c);
	DTRACE("DLG: %s: full_swath_bytes_packed_l = %0d", __func__, full_swath_bytes_packed_l);
	DTRACE("DLG: %s: full_swath_bytes_packed_c = %0d", __func__, full_swath_bytes_packed_c);
पूर्ण

/* Need refactor. */
अटल व्योम dml1_rq_dlg_get_row_heights(
		काष्ठा display_mode_lib *mode_lib,
		अचिन्हित पूर्णांक *o_dpte_row_height,
		अचिन्हित पूर्णांक *o_meta_row_height,
		अचिन्हित पूर्णांक vp_width,
		अचिन्हित पूर्णांक data_pitch,
		पूर्णांक source_क्रमmat,
		पूर्णांक tiling,
		पूर्णांक macro_tile_size,
		पूर्णांक source_scan,
		पूर्णांक is_chroma)
अणु
	bool surf_linear = (tiling == dm_sw_linear);
	bool surf_vert = (source_scan == dm_vert);

	अचिन्हित पूर्णांक bytes_per_element = get_bytes_per_element(
			(क्रमागत source_क्रमmat_class) source_क्रमmat,
			is_chroma);
	अचिन्हित पूर्णांक log2_bytes_per_element = dml_log2(bytes_per_element);
	अचिन्हित पूर्णांक blk256_width = 0;
	अचिन्हित पूर्णांक blk256_height = 0;

	अचिन्हित पूर्णांक log2_blk256_height;
	अचिन्हित पूर्णांक blk_bytes;
	अचिन्हित पूर्णांक log2_blk_bytes;
	अचिन्हित पूर्णांक log2_blk_height;
	अचिन्हित पूर्णांक log2_blk_width;
	अचिन्हित पूर्णांक log2_meta_req_bytes;
	अचिन्हित पूर्णांक log2_meta_req_height;
	अचिन्हित पूर्णांक log2_meta_req_width;
	अचिन्हित पूर्णांक log2_meta_row_height;
	अचिन्हित पूर्णांक log2_vmpg_bytes;
	अचिन्हित पूर्णांक dpte_buf_in_pte_reqs;
	अचिन्हित पूर्णांक log2_vmpg_height;
	अचिन्हित पूर्णांक log2_vmpg_width;
	अचिन्हित पूर्णांक log2_dpte_req_height_ptes;
	अचिन्हित पूर्णांक log2_dpte_req_width_ptes;
	अचिन्हित पूर्णांक log2_dpte_req_height;
	अचिन्हित पूर्णांक log2_dpte_req_width;
	अचिन्हित पूर्णांक log2_dpte_row_height_linear;
	अचिन्हित पूर्णांक log2_dpte_row_height;
	अचिन्हित पूर्णांक dpte_req_width;

	अगर (surf_linear) अणु
		blk256_width = 256;
		blk256_height = 1;
	पूर्ण अन्यथा अणु
		get_blk256_size(&blk256_width, &blk256_height, bytes_per_element);
	पूर्ण

	log2_blk256_height = dml_log2((द्विगुन) blk256_height);
	blk_bytes = surf_linear ?
			256 : get_blk_size_bytes((क्रमागत source_macro_tile_size) macro_tile_size);
	log2_blk_bytes = dml_log2((द्विगुन) blk_bytes);
	log2_blk_height = 0;
	log2_blk_width = 0;

	/* remember log rule
	 * "+" in log is multiply
	 * "-" in log is भागide
	 * "/2" is like square root
	 * blk is vertical biased
	 */
	अगर (tiling != dm_sw_linear)
		log2_blk_height = log2_blk256_height
				+ dml_उच्चमान((द्विगुन) (log2_blk_bytes - 8) / 2.0, 1);
	अन्यथा
		log2_blk_height = 0; /* blk height of 1 */

	log2_blk_width = log2_blk_bytes - log2_bytes_per_element - log2_blk_height;

	/* ------- */
	/* meta    */
	/* ------- */
	log2_meta_req_bytes = 6; /* meta request is 64b and is 8x8byte meta element */

	/* each 64b meta request क्रम dcn is 8x8 meta elements and
	 * a meta element covers one 256b block of the the data surface.
	 */
	log2_meta_req_height = log2_blk256_height + 3; /* meta req is 8x8 */
	log2_meta_req_width = log2_meta_req_bytes + 8 - log2_bytes_per_element
			- log2_meta_req_height;
	log2_meta_row_height = 0;

	/* the dimensions of a meta row are meta_row_width x meta_row_height in elements.
	 * calculate upper bound of the meta_row_width
	 */
	अगर (!surf_vert)
		log2_meta_row_height = log2_meta_req_height;
	अन्यथा
		log2_meta_row_height = log2_meta_req_width;

	*o_meta_row_height = 1 << log2_meta_row_height;

	/* ------ */
	/* dpte   */
	/* ------ */
	log2_vmpg_bytes = dml_log2(mode_lib->soc.vmm_page_size_bytes);
	dpte_buf_in_pte_reqs = mode_lib->ip.dpte_buffer_size_in_pte_reqs_luma;

	log2_vmpg_height = 0;
	log2_vmpg_width = 0;
	log2_dpte_req_height_ptes = 0;
	log2_dpte_req_width_ptes = 0;
	log2_dpte_req_height = 0;
	log2_dpte_req_width = 0;
	log2_dpte_row_height_linear = 0;
	log2_dpte_row_height = 0;
	dpte_req_width = 0; /* 64b dpte req width in data element */

	अगर (surf_linear)
		log2_vmpg_height = 0; /* one line high */
	अन्यथा
		log2_vmpg_height = (log2_vmpg_bytes - 8) / 2 + log2_blk256_height;
	log2_vmpg_width = log2_vmpg_bytes - log2_bytes_per_element - log2_vmpg_height;

	/* only 3 possible shapes क्रम dpte request in dimensions of ptes: 8x1, 4x2, 2x4. */
	अगर (log2_blk_bytes <= log2_vmpg_bytes)
		log2_dpte_req_height_ptes = 0;
	अन्यथा अगर (log2_blk_height - log2_vmpg_height >= 2)
		log2_dpte_req_height_ptes = 2;
	अन्यथा
		log2_dpte_req_height_ptes = log2_blk_height - log2_vmpg_height;
	log2_dpte_req_width_ptes = 3 - log2_dpte_req_height_ptes;

	ASSERT((log2_dpte_req_width_ptes == 3 && log2_dpte_req_height_ptes == 0) || /* 8x1 */
			(log2_dpte_req_width_ptes == 2 && log2_dpte_req_height_ptes == 1) || /* 4x2 */
			(log2_dpte_req_width_ptes == 1 && log2_dpte_req_height_ptes == 2)); /* 2x4 */

	/* the dpte request dimensions in data elements is dpte_req_width x dpte_req_height
	 * log2_wmpg_width is how much 1 pte represent, now trying to calculate how much 64b pte req represent
	 */
	log2_dpte_req_height = log2_vmpg_height + log2_dpte_req_height_ptes;
	log2_dpte_req_width = log2_vmpg_width + log2_dpte_req_width_ptes;
	dpte_req_width = 1 << log2_dpte_req_width;

	/* calculate pitch dpte row buffer can hold
	 * round the result करोwn to a घातer of two.
	 */
	अगर (surf_linear) अणु
		log2_dpte_row_height_linear = dml_न्यूनमान(
				dml_log2(dpte_buf_in_pte_reqs * dpte_req_width / data_pitch),
				1);

		ASSERT(log2_dpte_row_height_linear >= 3);

		अगर (log2_dpte_row_height_linear > 7)
			log2_dpte_row_height_linear = 7;

		log2_dpte_row_height = log2_dpte_row_height_linear;
	पूर्ण अन्यथा अणु
		/* the upper bound of the dpte_row_width without dependency on viewport position follows.  */
		अगर (!surf_vert)
			log2_dpte_row_height = log2_dpte_req_height;
		अन्यथा
			log2_dpte_row_height =
					(log2_blk_width < log2_dpte_req_width) ?
							log2_blk_width : log2_dpte_req_width;
	पूर्ण

	/* From programming guide:
	 * There is a special हाल of saving only half of ptes वापसed due to buffer space limits.
	 * this हाल applies to 4 and 8bpe in horizontal access of a vp_width greater than 2560+16
	 * when the pte request is 2x4 ptes (which happens when vmpg_bytes =4kb and tile blk_bytes >=64kb).
	 */
	अगर (!surf_vert && vp_width > (2560 + 16) && bytes_per_element >= 4 && log2_vmpg_bytes == 12
			&& log2_blk_bytes >= 16)
		log2_dpte_row_height = log2_dpte_row_height - 1; /*half of the full height */

	*o_dpte_row_height = 1 << log2_dpte_row_height;
पूर्ण

अटल व्योम get_surf_rq_param(
		काष्ठा display_mode_lib *mode_lib,
		काष्ठा _vcs_dpi_display_data_rq_sizing_params_st *rq_sizing_param,
		काष्ठा _vcs_dpi_display_data_rq_dlg_params_st *rq_dlg_param,
		काष्ठा _vcs_dpi_display_data_rq_misc_params_st *rq_misc_param,
		स्थिर काष्ठा _vcs_dpi_display_pipe_source_params_st pipe_src_param,
		bool is_chroma)
अणु
	bool mode_422 = 0;
	अचिन्हित पूर्णांक vp_width = 0;
	अचिन्हित पूर्णांक vp_height = 0;
	अचिन्हित पूर्णांक data_pitch = 0;
	अचिन्हित पूर्णांक meta_pitch = 0;
	अचिन्हित पूर्णांक ppe = mode_422 ? 2 : 1;
	bool surf_linear;
	bool surf_vert;
	अचिन्हित पूर्णांक bytes_per_element;
	अचिन्हित पूर्णांक log2_bytes_per_element;
	अचिन्हित पूर्णांक blk256_width;
	अचिन्हित पूर्णांक blk256_height;
	अचिन्हित पूर्णांक log2_blk256_width;
	अचिन्हित पूर्णांक log2_blk256_height;
	अचिन्हित पूर्णांक blk_bytes;
	अचिन्हित पूर्णांक log2_blk_bytes;
	अचिन्हित पूर्णांक log2_blk_height;
	अचिन्हित पूर्णांक log2_blk_width;
	अचिन्हित पूर्णांक log2_meta_req_bytes;
	अचिन्हित पूर्णांक log2_meta_req_height;
	अचिन्हित पूर्णांक log2_meta_req_width;
	अचिन्हित पूर्णांक meta_req_width;
	अचिन्हित पूर्णांक meta_req_height;
	अचिन्हित पूर्णांक log2_meta_row_height;
	अचिन्हित पूर्णांक meta_row_width_ub;
	अचिन्हित पूर्णांक log2_meta_chunk_bytes;
	अचिन्हित पूर्णांक log2_meta_chunk_height;
	अचिन्हित पूर्णांक log2_meta_chunk_width;
	अचिन्हित पूर्णांक log2_min_meta_chunk_bytes;
	अचिन्हित पूर्णांक min_meta_chunk_width;
	अचिन्हित पूर्णांक meta_chunk_width;
	अचिन्हित पूर्णांक meta_chunk_per_row_पूर्णांक;
	अचिन्हित पूर्णांक meta_row_reमुख्यder;
	अचिन्हित पूर्णांक meta_chunk_threshold;
	अचिन्हित पूर्णांक meta_blk_bytes;
	अचिन्हित पूर्णांक meta_blk_height;
	अचिन्हित पूर्णांक meta_blk_width;
	अचिन्हित पूर्णांक meta_surface_bytes;
	अचिन्हित पूर्णांक vmpg_bytes;
	अचिन्हित पूर्णांक meta_pte_req_per_frame_ub;
	अचिन्हित पूर्णांक meta_pte_bytes_per_frame_ub;
	अचिन्हित पूर्णांक log2_vmpg_bytes;
	अचिन्हित पूर्णांक dpte_buf_in_pte_reqs;
	अचिन्हित पूर्णांक log2_vmpg_height;
	अचिन्हित पूर्णांक log2_vmpg_width;
	अचिन्हित पूर्णांक log2_dpte_req_height_ptes;
	अचिन्हित पूर्णांक log2_dpte_req_width_ptes;
	अचिन्हित पूर्णांक log2_dpte_req_height;
	अचिन्हित पूर्णांक log2_dpte_req_width;
	अचिन्हित पूर्णांक log2_dpte_row_height_linear;
	अचिन्हित पूर्णांक log2_dpte_row_height;
	अचिन्हित पूर्णांक log2_dpte_group_width;
	अचिन्हित पूर्णांक dpte_row_width_ub;
	अचिन्हित पूर्णांक dpte_row_height;
	अचिन्हित पूर्णांक dpte_req_height;
	अचिन्हित पूर्णांक dpte_req_width;
	अचिन्हित पूर्णांक dpte_group_width;
	अचिन्हित पूर्णांक log2_dpte_group_bytes;
	अचिन्हित पूर्णांक log2_dpte_group_length;
	अचिन्हित पूर्णांक func_meta_row_height, func_dpte_row_height;

	/* TODO check अगर ppe apply क्रम both luma and chroma in 422 हाल */
	अगर (is_chroma) अणु
		vp_width = pipe_src_param.viewport_width_c / ppe;
		vp_height = pipe_src_param.viewport_height_c;
		data_pitch = pipe_src_param.data_pitch_c;
		meta_pitch = pipe_src_param.meta_pitch_c;
	पूर्ण अन्यथा अणु
		vp_width = pipe_src_param.viewport_width / ppe;
		vp_height = pipe_src_param.viewport_height;
		data_pitch = pipe_src_param.data_pitch;
		meta_pitch = pipe_src_param.meta_pitch;
	पूर्ण

	rq_sizing_param->chunk_bytes = 8192;

	अगर (rq_sizing_param->chunk_bytes == 64 * 1024)
		rq_sizing_param->min_chunk_bytes = 0;
	अन्यथा
		rq_sizing_param->min_chunk_bytes = 1024;

	rq_sizing_param->meta_chunk_bytes = 2048;
	rq_sizing_param->min_meta_chunk_bytes = 256;

	rq_sizing_param->mpte_group_bytes = 2048;

	surf_linear = (pipe_src_param.sw_mode == dm_sw_linear);
	surf_vert = (pipe_src_param.source_scan == dm_vert);

	bytes_per_element = get_bytes_per_element(
			(क्रमागत source_क्रमmat_class) pipe_src_param.source_क्रमmat,
			is_chroma);
	log2_bytes_per_element = dml_log2(bytes_per_element);
	blk256_width = 0;
	blk256_height = 0;

	अगर (surf_linear) अणु
		blk256_width = 256 / bytes_per_element;
		blk256_height = 1;
	पूर्ण अन्यथा अणु
		get_blk256_size(&blk256_width, &blk256_height, bytes_per_element);
	पूर्ण

	DTRACE("DLG: %s: surf_linear        = %d", __func__, surf_linear);
	DTRACE("DLG: %s: surf_vert          = %d", __func__, surf_vert);
	DTRACE("DLG: %s: blk256_width       = %d", __func__, blk256_width);
	DTRACE("DLG: %s: blk256_height      = %d", __func__, blk256_height);

	log2_blk256_width = dml_log2((द्विगुन) blk256_width);
	log2_blk256_height = dml_log2((द्विगुन) blk256_height);
	blk_bytes =
			surf_linear ? 256 : get_blk_size_bytes(
							(क्रमागत source_macro_tile_size) pipe_src_param.macro_tile_size);
	log2_blk_bytes = dml_log2((द्विगुन) blk_bytes);
	log2_blk_height = 0;
	log2_blk_width = 0;

	/* remember log rule
	 * "+" in log is multiply
	 * "-" in log is भागide
	 * "/2" is like square root
	 * blk is vertical biased
	 */
	अगर (pipe_src_param.sw_mode != dm_sw_linear)
		log2_blk_height = log2_blk256_height
				+ dml_उच्चमान((द्विगुन) (log2_blk_bytes - 8) / 2.0, 1);
	अन्यथा
		log2_blk_height = 0; /* blk height of 1 */

	log2_blk_width = log2_blk_bytes - log2_bytes_per_element - log2_blk_height;

	अगर (!surf_vert) अणु
		rq_dlg_param->swath_width_ub = dml_round_to_multiple(vp_width - 1, blk256_width, 1)
				+ blk256_width;
		rq_dlg_param->req_per_swath_ub = rq_dlg_param->swath_width_ub >> log2_blk256_width;
	पूर्ण अन्यथा अणु
		rq_dlg_param->swath_width_ub = dml_round_to_multiple(
				vp_height - 1,
				blk256_height,
				1) + blk256_height;
		rq_dlg_param->req_per_swath_ub = rq_dlg_param->swath_width_ub >> log2_blk256_height;
	पूर्ण

	अगर (!surf_vert)
		rq_misc_param->full_swath_bytes = rq_dlg_param->swath_width_ub * blk256_height
				* bytes_per_element;
	अन्यथा
		rq_misc_param->full_swath_bytes = rq_dlg_param->swath_width_ub * blk256_width
				* bytes_per_element;

	rq_misc_param->blk256_height = blk256_height;
	rq_misc_param->blk256_width = blk256_width;

	/* -------  */
	/* meta     */
	/* -------  */
	log2_meta_req_bytes = 6; /* meta request is 64b and is 8x8byte meta element */

	/* each 64b meta request क्रम dcn is 8x8 meta elements and
	 * a meta element covers one 256b block of the the data surface.
	 */
	log2_meta_req_height = log2_blk256_height + 3; /* meta req is 8x8 byte, each byte represent 1 blk256 */
	log2_meta_req_width = log2_meta_req_bytes + 8 - log2_bytes_per_element
			- log2_meta_req_height;
	meta_req_width = 1 << log2_meta_req_width;
	meta_req_height = 1 << log2_meta_req_height;
	log2_meta_row_height = 0;
	meta_row_width_ub = 0;

	/* the dimensions of a meta row are meta_row_width x meta_row_height in elements.
	 * calculate upper bound of the meta_row_width
	 */
	अगर (!surf_vert) अणु
		log2_meta_row_height = log2_meta_req_height;
		meta_row_width_ub = dml_round_to_multiple(vp_width - 1, meta_req_width, 1)
				+ meta_req_width;
		rq_dlg_param->meta_req_per_row_ub = meta_row_width_ub / meta_req_width;
	पूर्ण अन्यथा अणु
		log2_meta_row_height = log2_meta_req_width;
		meta_row_width_ub = dml_round_to_multiple(vp_height - 1, meta_req_height, 1)
				+ meta_req_height;
		rq_dlg_param->meta_req_per_row_ub = meta_row_width_ub / meta_req_height;
	पूर्ण
	rq_dlg_param->meta_bytes_per_row_ub = rq_dlg_param->meta_req_per_row_ub * 64;

	log2_meta_chunk_bytes = dml_log2(rq_sizing_param->meta_chunk_bytes);
	log2_meta_chunk_height = log2_meta_row_height;

	/*full sized meta chunk width in unit of data elements */
	log2_meta_chunk_width = log2_meta_chunk_bytes + 8 - log2_bytes_per_element
			- log2_meta_chunk_height;
	log2_min_meta_chunk_bytes = dml_log2(rq_sizing_param->min_meta_chunk_bytes);
	min_meta_chunk_width = 1
			<< (log2_min_meta_chunk_bytes + 8 - log2_bytes_per_element
					- log2_meta_chunk_height);
	meta_chunk_width = 1 << log2_meta_chunk_width;
	meta_chunk_per_row_पूर्णांक = (अचिन्हित पूर्णांक) (meta_row_width_ub / meta_chunk_width);
	meta_row_reमुख्यder = meta_row_width_ub % meta_chunk_width;
	meta_chunk_threshold = 0;
	meta_blk_bytes = 4096;
	meta_blk_height = blk256_height * 64;
	meta_blk_width = meta_blk_bytes * 256 / bytes_per_element / meta_blk_height;
	meta_surface_bytes = meta_pitch
			* (dml_round_to_multiple(vp_height - 1, meta_blk_height, 1)
					+ meta_blk_height) * bytes_per_element / 256;
	vmpg_bytes = mode_lib->soc.vmm_page_size_bytes;
	meta_pte_req_per_frame_ub = (dml_round_to_multiple(
			meta_surface_bytes - vmpg_bytes,
			8 * vmpg_bytes,
			1) + 8 * vmpg_bytes) / (8 * vmpg_bytes);
	meta_pte_bytes_per_frame_ub = meta_pte_req_per_frame_ub * 64; /*64B mpte request */
	rq_dlg_param->meta_pte_bytes_per_frame_ub = meta_pte_bytes_per_frame_ub;

	DTRACE("DLG: %s: meta_blk_height             = %d", __func__, meta_blk_height);
	DTRACE("DLG: %s: meta_blk_width              = %d", __func__, meta_blk_width);
	DTRACE("DLG: %s: meta_surface_bytes          = %d", __func__, meta_surface_bytes);
	DTRACE("DLG: %s: meta_pte_req_per_frame_ub   = %d", __func__, meta_pte_req_per_frame_ub);
	DTRACE("DLG: %s: meta_pte_bytes_per_frame_ub = %d", __func__, meta_pte_bytes_per_frame_ub);

	अगर (!surf_vert)
		meta_chunk_threshold = 2 * min_meta_chunk_width - meta_req_width;
	अन्यथा
		meta_chunk_threshold = 2 * min_meta_chunk_width - meta_req_height;

	अगर (meta_row_reमुख्यder <= meta_chunk_threshold)
		rq_dlg_param->meta_chunks_per_row_ub = meta_chunk_per_row_पूर्णांक + 1;
	अन्यथा
		rq_dlg_param->meta_chunks_per_row_ub = meta_chunk_per_row_पूर्णांक + 2;

	rq_dlg_param->meta_row_height = 1 << log2_meta_row_height;

	/* ------ */
	/* dpte   */
	/* ------ */
	log2_vmpg_bytes = dml_log2(mode_lib->soc.vmm_page_size_bytes);
	dpte_buf_in_pte_reqs = mode_lib->ip.dpte_buffer_size_in_pte_reqs_luma;

	log2_vmpg_height = 0;
	log2_vmpg_width = 0;
	log2_dpte_req_height_ptes = 0;
	log2_dpte_req_width_ptes = 0;
	log2_dpte_req_height = 0;
	log2_dpte_req_width = 0;
	log2_dpte_row_height_linear = 0;
	log2_dpte_row_height = 0;
	log2_dpte_group_width = 0;
	dpte_row_width_ub = 0;
	dpte_row_height = 0;
	dpte_req_height = 0; /* 64b dpte req height in data element */
	dpte_req_width = 0; /* 64b dpte req width in data element */
	dpte_group_width = 0;
	log2_dpte_group_bytes = 0;
	log2_dpte_group_length = 0;

	अगर (surf_linear)
		log2_vmpg_height = 0; /* one line high */
	अन्यथा
		log2_vmpg_height = (log2_vmpg_bytes - 8) / 2 + log2_blk256_height;
	log2_vmpg_width = log2_vmpg_bytes - log2_bytes_per_element - log2_vmpg_height;

	/* only 3 possible shapes क्रम dpte request in dimensions of ptes: 8x1, 4x2, 2x4. */
	अगर (log2_blk_bytes <= log2_vmpg_bytes)
		log2_dpte_req_height_ptes = 0;
	अन्यथा अगर (log2_blk_height - log2_vmpg_height >= 2)
		log2_dpte_req_height_ptes = 2;
	अन्यथा
		log2_dpte_req_height_ptes = log2_blk_height - log2_vmpg_height;
	log2_dpte_req_width_ptes = 3 - log2_dpte_req_height_ptes;

	/* Ensure we only have the 3 shapes */
	ASSERT((log2_dpte_req_width_ptes == 3 && log2_dpte_req_height_ptes == 0) || /* 8x1 */
			(log2_dpte_req_width_ptes == 2 && log2_dpte_req_height_ptes == 1) || /* 4x2 */
			(log2_dpte_req_width_ptes == 1 && log2_dpte_req_height_ptes == 2)); /* 2x4 */

	/* The dpte request dimensions in data elements is dpte_req_width x dpte_req_height
	 * log2_vmpg_width is how much 1 pte represent, now calculating how much a 64b pte req represent
	 * That depends on the pte shape (i.e. 8x1, 4x2, 2x4)
	 */
	log2_dpte_req_height = log2_vmpg_height + log2_dpte_req_height_ptes;
	log2_dpte_req_width = log2_vmpg_width + log2_dpte_req_width_ptes;
	dpte_req_height = 1 << log2_dpte_req_height;
	dpte_req_width = 1 << log2_dpte_req_width;

	/* calculate pitch dpte row buffer can hold
	 * round the result करोwn to a घातer of two.
	 */
	अगर (surf_linear) अणु
		log2_dpte_row_height_linear = dml_न्यूनमान(
				dml_log2(dpte_buf_in_pte_reqs * dpte_req_width / data_pitch),
				1);

		ASSERT(log2_dpte_row_height_linear >= 3);

		अगर (log2_dpte_row_height_linear > 7)
			log2_dpte_row_height_linear = 7;

		log2_dpte_row_height = log2_dpte_row_height_linear;
		rq_dlg_param->dpte_row_height = 1 << log2_dpte_row_height;

		/* For linear, the dpte row is pitch dependent and the pte requests wrap at the pitch boundary.
		 * the dpte_row_width_ub is the upper bound of data_pitch*dpte_row_height in elements with this unique buffering.
		 */
		dpte_row_width_ub = dml_round_to_multiple(
				data_pitch * dpte_row_height - 1,
				dpte_req_width,
				1) + dpte_req_width;
		rq_dlg_param->dpte_req_per_row_ub = dpte_row_width_ub / dpte_req_width;
	पूर्ण अन्यथा अणु
		/* क्रम tiled mode, row height is the same as req height and row store up to vp size upper bound */
		अगर (!surf_vert) अणु
			log2_dpte_row_height = log2_dpte_req_height;
			dpte_row_width_ub = dml_round_to_multiple(vp_width - 1, dpte_req_width, 1)
					+ dpte_req_width;
			rq_dlg_param->dpte_req_per_row_ub = dpte_row_width_ub / dpte_req_width;
		पूर्ण अन्यथा अणु
			log2_dpte_row_height =
					(log2_blk_width < log2_dpte_req_width) ?
							log2_blk_width : log2_dpte_req_width;
			dpte_row_width_ub = dml_round_to_multiple(vp_height - 1, dpte_req_height, 1)
					+ dpte_req_height;
			rq_dlg_param->dpte_req_per_row_ub = dpte_row_width_ub / dpte_req_height;
		पूर्ण
		rq_dlg_param->dpte_row_height = 1 << log2_dpte_row_height;
	पूर्ण
	rq_dlg_param->dpte_bytes_per_row_ub = rq_dlg_param->dpte_req_per_row_ub * 64;

	/* From programming guide:
	 * There is a special हाल of saving only half of ptes वापसed due to buffer space limits.
	 * this हाल applies to 4 and 8bpe in horizontal access of a vp_width greater than 2560+16
	 * when the pte request is 2x4 ptes (which happens when vmpg_bytes =4kb and tile blk_bytes >=64kb).
	 */
	अगर (!surf_vert && vp_width > (2560 + 16) && bytes_per_element >= 4 && log2_vmpg_bytes == 12
			&& log2_blk_bytes >= 16) अणु
		log2_dpte_row_height = log2_dpte_row_height - 1; /*half of the full height */
		rq_dlg_param->dpte_row_height = 1 << log2_dpte_row_height;
	पूर्ण

	/* the dpte_group_bytes is reduced क्रम the specअगरic हाल of vertical
	 * access of a tile surface that has dpte request of 8x1 ptes.
	 */
	अगर (!surf_linear && (log2_dpte_req_height_ptes == 0) && surf_vert) /*reduced, in this हाल, will have page fault within a group */
		rq_sizing_param->dpte_group_bytes = 512;
	अन्यथा
		/*full size */
		rq_sizing_param->dpte_group_bytes = 2048;

	/*since pte request size is 64byte, the number of data pte requests per full sized group is as follows.  */
	log2_dpte_group_bytes = dml_log2(rq_sizing_param->dpte_group_bytes);
	log2_dpte_group_length = log2_dpte_group_bytes - 6; /*length in 64b requests  */

	/* full sized data pte group width in elements */
	अगर (!surf_vert)
		log2_dpte_group_width = log2_dpte_group_length + log2_dpte_req_width;
	अन्यथा
		log2_dpte_group_width = log2_dpte_group_length + log2_dpte_req_height;

	dpte_group_width = 1 << log2_dpte_group_width;

	/* since dpte groups are only aligned to dpte_req_width and not dpte_group_width,
	 * the upper bound क्रम the dpte groups per row is as follows.
	 */
	rq_dlg_param->dpte_groups_per_row_ub = dml_उच्चमान(
			(द्विगुन) dpte_row_width_ub / dpte_group_width,
			1);

	dml1_rq_dlg_get_row_heights(
			mode_lib,
			&func_dpte_row_height,
			&func_meta_row_height,
			vp_width,
			data_pitch,
			pipe_src_param.source_क्रमmat,
			pipe_src_param.sw_mode,
			pipe_src_param.macro_tile_size,
			pipe_src_param.source_scan,
			is_chroma);

	/* Just a check to make sure this function and the new one give the same
	 * result. The standalone get_row_heights() function is based off of the
	 * code in this function so the same changes need to be made to both.
	 */
	अगर (rq_dlg_param->meta_row_height != func_meta_row_height) अणु
		DTRACE(
				"MISMATCH: rq_dlg_param->meta_row_height = %d",
				rq_dlg_param->meta_row_height);
		DTRACE("MISMATCH: func_meta_row_height = %d", func_meta_row_height);
		ASSERT(0);
	पूर्ण

	अगर (rq_dlg_param->dpte_row_height != func_dpte_row_height) अणु
		DTRACE(
				"MISMATCH: rq_dlg_param->dpte_row_height = %d",
				rq_dlg_param->dpte_row_height);
		DTRACE("MISMATCH: func_dpte_row_height = %d", func_dpte_row_height);
		ASSERT(0);
	पूर्ण
पूर्ण

व्योम dml1_rq_dlg_get_rq_params(
		काष्ठा display_mode_lib *mode_lib,
		काष्ठा _vcs_dpi_display_rq_params_st *rq_param,
		स्थिर काष्ठा _vcs_dpi_display_pipe_source_params_st pipe_src_param)
अणु
	/* get param क्रम luma surface */
	rq_param->yuv420 = pipe_src_param.source_क्रमmat == dm_420_8
			|| pipe_src_param.source_क्रमmat == dm_420_10;
	rq_param->yuv420_10bpc = pipe_src_param.source_क्रमmat == dm_420_10;

	get_surf_rq_param(
			mode_lib,
			&(rq_param->sizing.rq_l),
			&(rq_param->dlg.rq_l),
			&(rq_param->misc.rq_l),
			pipe_src_param,
			0);

	अगर (is_dual_plane((क्रमागत source_क्रमmat_class) pipe_src_param.source_क्रमmat)) अणु
		/* get param क्रम chroma surface */
		get_surf_rq_param(
				mode_lib,
				&(rq_param->sizing.rq_c),
				&(rq_param->dlg.rq_c),
				&(rq_param->misc.rq_c),
				pipe_src_param,
				1);
	पूर्ण

	/* calculate how to split the det buffer space between luma and chroma */
	handle_det_buf_split(mode_lib, rq_param, pipe_src_param);
	prपूर्णांक__rq_params_st(mode_lib, *rq_param);
पूर्ण

/* Note: currently taken in as is.
 * Nice to decouple code from hw रेजिस्टर implement and extract code that are repeated क्रम luma and chroma.
 */
व्योम dml1_rq_dlg_get_dlg_params(
		काष्ठा display_mode_lib *mode_lib,
		काष्ठा _vcs_dpi_display_dlg_regs_st *disp_dlg_regs,
		काष्ठा _vcs_dpi_display_ttu_regs_st *disp_ttu_regs,
		स्थिर काष्ठा _vcs_dpi_display_rq_dlg_params_st rq_dlg_param,
		स्थिर काष्ठा _vcs_dpi_display_dlg_sys_params_st dlg_sys_param,
		स्थिर काष्ठा _vcs_dpi_display_e2e_pipe_params_st e2e_pipe_param,
		स्थिर bool cstate_en,
		स्थिर bool pstate_en,
		स्थिर bool vm_en,
		स्थिर bool अगरlip_en)
अणु
	/* Timing */
	अचिन्हित पूर्णांक htotal = e2e_pipe_param.pipe.dest.htotal;
	अचिन्हित पूर्णांक hblank_end = e2e_pipe_param.pipe.dest.hblank_end;
	अचिन्हित पूर्णांक vblank_start = e2e_pipe_param.pipe.dest.vblank_start;
	अचिन्हित पूर्णांक vblank_end = e2e_pipe_param.pipe.dest.vblank_end;
	bool पूर्णांकerlaced = e2e_pipe_param.pipe.dest.पूर्णांकerlaced;
	अचिन्हित पूर्णांक min_vblank = mode_lib->ip.min_vblank_lines;

	द्विगुन pclk_freq_in_mhz = e2e_pipe_param.pipe.dest.pixel_rate_mhz;
	द्विगुन refclk_freq_in_mhz = e2e_pipe_param.clks_cfg.refclk_mhz;
	द्विगुन dppclk_freq_in_mhz = e2e_pipe_param.clks_cfg.dppclk_mhz;
	द्विगुन dispclk_freq_in_mhz = e2e_pipe_param.clks_cfg.dispclk_mhz;

	द्विगुन ref_freq_to_pix_freq;
	द्विगुन prefetch_xy_calc_in_dcfclk;
	द्विगुन min_dcfclk_mhz;
	द्विगुन t_calc_us;
	द्विगुन min_ttu_vblank;
	द्विगुन min_dst_y_ttu_vblank;
	अचिन्हित पूर्णांक dlg_vblank_start;
	bool dcc_en;
	bool dual_plane;
	bool mode_422;
	अचिन्हित पूर्णांक access_dir;
	अचिन्हित पूर्णांक bytes_per_element_l;
	अचिन्हित पूर्णांक bytes_per_element_c;
	अचिन्हित पूर्णांक vp_height_l;
	अचिन्हित पूर्णांक vp_width_l;
	अचिन्हित पूर्णांक vp_height_c;
	अचिन्हित पूर्णांक vp_width_c;
	अचिन्हित पूर्णांक htaps_l;
	अचिन्हित पूर्णांक htaps_c;
	द्विगुन hratios_l;
	द्विगुन hratios_c;
	द्विगुन vratio_l;
	द्विगुन vratio_c;
	द्विगुन line_समय_in_us;
	द्विगुन vinit_l;
	द्विगुन vinit_c;
	द्विगुन vinit_bot_l;
	द्विगुन vinit_bot_c;
	अचिन्हित पूर्णांक swath_height_l;
	अचिन्हित पूर्णांक swath_width_ub_l;
	अचिन्हित पूर्णांक dpte_bytes_per_row_ub_l;
	अचिन्हित पूर्णांक dpte_groups_per_row_ub_l;
	अचिन्हित पूर्णांक meta_pte_bytes_per_frame_ub_l;
	अचिन्हित पूर्णांक meta_bytes_per_row_ub_l;
	अचिन्हित पूर्णांक swath_height_c;
	अचिन्हित पूर्णांक swath_width_ub_c;
	अचिन्हित पूर्णांक dpte_bytes_per_row_ub_c;
	अचिन्हित पूर्णांक dpte_groups_per_row_ub_c;
	अचिन्हित पूर्णांक meta_chunks_per_row_ub_l;
	अचिन्हित पूर्णांक vupdate_offset;
	अचिन्हित पूर्णांक vupdate_width;
	अचिन्हित पूर्णांक vपढ़ोy_offset;
	अचिन्हित पूर्णांक dppclk_delay_subtotal;
	अचिन्हित पूर्णांक dispclk_delay_subtotal;
	अचिन्हित पूर्णांक pixel_rate_delay_subtotal;
	अचिन्हित पूर्णांक vstartup_start;
	अचिन्हित पूर्णांक dst_x_after_scaler;
	अचिन्हित पूर्णांक dst_y_after_scaler;
	द्विगुन line_रुको;
	द्विगुन line_o;
	द्विगुन line_setup;
	द्विगुन line_calc;
	द्विगुन dst_y_prefetch;
	द्विगुन t_pre_us;
	अचिन्हित पूर्णांक vm_bytes;
	अचिन्हित पूर्णांक meta_row_bytes;
	अचिन्हित पूर्णांक max_num_sw_l;
	अचिन्हित पूर्णांक max_num_sw_c;
	अचिन्हित पूर्णांक max_partial_sw_l;
	अचिन्हित पूर्णांक max_partial_sw_c;
	द्विगुन max_vinit_l;
	द्विगुन max_vinit_c;
	अचिन्हित पूर्णांक lsw_l;
	अचिन्हित पूर्णांक lsw_c;
	अचिन्हित पूर्णांक sw_bytes_ub_l;
	अचिन्हित पूर्णांक sw_bytes_ub_c;
	अचिन्हित पूर्णांक sw_bytes;
	अचिन्हित पूर्णांक dpte_row_bytes;
	द्विगुन prefetch_bw;
	द्विगुन flip_bw;
	द्विगुन t_vm_us;
	द्विगुन t_r0_us;
	द्विगुन dst_y_per_vm_vblank;
	द्विगुन dst_y_per_row_vblank;
	द्विगुन min_dst_y_per_vm_vblank;
	द्विगुन min_dst_y_per_row_vblank;
	द्विगुन lsw;
	द्विगुन vratio_pre_l;
	द्विगुन vratio_pre_c;
	अचिन्हित पूर्णांक req_per_swath_ub_l;
	अचिन्हित पूर्णांक req_per_swath_ub_c;
	अचिन्हित पूर्णांक meta_row_height_l;
	अचिन्हित पूर्णांक swath_width_pixels_ub_l;
	अचिन्हित पूर्णांक swath_width_pixels_ub_c;
	अचिन्हित पूर्णांक scaler_rec_in_width_l;
	अचिन्हित पूर्णांक scaler_rec_in_width_c;
	अचिन्हित पूर्णांक dpte_row_height_l;
	अचिन्हित पूर्णांक dpte_row_height_c;
	द्विगुन hscale_pixel_rate_l;
	द्विगुन hscale_pixel_rate_c;
	द्विगुन min_hratio_fact_l;
	द्विगुन min_hratio_fact_c;
	द्विगुन refcyc_per_line_delivery_pre_l;
	द्विगुन refcyc_per_line_delivery_pre_c;
	द्विगुन refcyc_per_line_delivery_l;
	द्विगुन refcyc_per_line_delivery_c;
	द्विगुन refcyc_per_req_delivery_pre_l;
	द्विगुन refcyc_per_req_delivery_pre_c;
	द्विगुन refcyc_per_req_delivery_l;
	द्विगुन refcyc_per_req_delivery_c;
	द्विगुन refcyc_per_req_delivery_pre_cur0;
	द्विगुन refcyc_per_req_delivery_cur0;
	अचिन्हित पूर्णांक full_recout_width;
	द्विगुन hratios_cur0;
	अचिन्हित पूर्णांक cur0_src_width;
	क्रमागत cursor_bpp cur0_bpp;
	अचिन्हित पूर्णांक cur0_req_size;
	अचिन्हित पूर्णांक cur0_req_width;
	द्विगुन cur0_width_ub;
	द्विगुन cur0_req_per_width;
	द्विगुन hactive_cur0;

	स_रखो(disp_dlg_regs, 0, माप(*disp_dlg_regs));
	स_रखो(disp_ttu_regs, 0, माप(*disp_ttu_regs));

	DTRACE("DLG: %s: cstate_en = %d", __func__, cstate_en);
	DTRACE("DLG: %s: pstate_en = %d", __func__, pstate_en);
	DTRACE("DLG: %s: vm_en     = %d", __func__, vm_en);
	DTRACE("DLG: %s: iflip_en  = %d", __func__, अगरlip_en);

	/* ------------------------- */
	/* Section 1.5.2.1: OTG dependent Params */
	/* ------------------------- */
	DTRACE("DLG: %s: dppclk_freq_in_mhz     = %3.2f", __func__, dppclk_freq_in_mhz);
	DTRACE("DLG: %s: dispclk_freq_in_mhz    = %3.2f", __func__, dispclk_freq_in_mhz);
	DTRACE("DLG: %s: refclk_freq_in_mhz     = %3.2f", __func__, refclk_freq_in_mhz);
	DTRACE("DLG: %s: pclk_freq_in_mhz       = %3.2f", __func__, pclk_freq_in_mhz);
	DTRACE("DLG: %s: interlaced             = %d", __func__, पूर्णांकerlaced);

	ref_freq_to_pix_freq = refclk_freq_in_mhz / pclk_freq_in_mhz;
	ASSERT(ref_freq_to_pix_freq < 4.0);
	disp_dlg_regs->ref_freq_to_pix_freq =
			(अचिन्हित पूर्णांक) (ref_freq_to_pix_freq * dml_घात(2, 19));
	disp_dlg_regs->refcyc_per_htotal = (अचिन्हित पूर्णांक) (ref_freq_to_pix_freq * (द्विगुन) htotal
			* dml_घात(2, 8));
	disp_dlg_regs->refcyc_h_blank_end = (अचिन्हित पूर्णांक) ((द्विगुन) hblank_end
			* (द्विगुन) ref_freq_to_pix_freq);
	ASSERT(disp_dlg_regs->refcyc_h_blank_end < (अचिन्हित पूर्णांक) dml_घात(2, 13));
	disp_dlg_regs->dlg_vblank_end = पूर्णांकerlaced ? (vblank_end / 2) : vblank_end; /* 15 bits */

	prefetch_xy_calc_in_dcfclk = 24.0; /* TODO: ip_param */
	min_dcfclk_mhz = dlg_sys_param.deepsleep_dcfclk_mhz;
	t_calc_us = prefetch_xy_calc_in_dcfclk / min_dcfclk_mhz;
	min_ttu_vblank = dlg_sys_param.t_urg_wm_us;
	अगर (cstate_en)
		min_ttu_vblank = dml_max(dlg_sys_param.t_sr_wm_us, min_ttu_vblank);
	अगर (pstate_en)
		min_ttu_vblank = dml_max(dlg_sys_param.t_mclk_wm_us, min_ttu_vblank);
	min_ttu_vblank = min_ttu_vblank + t_calc_us;

	min_dst_y_ttu_vblank = min_ttu_vblank * pclk_freq_in_mhz / (द्विगुन) htotal;
	dlg_vblank_start = पूर्णांकerlaced ? (vblank_start / 2) : vblank_start;

	disp_dlg_regs->min_dst_y_next_start = (अचिन्हित पूर्णांक) (((द्विगुन) dlg_vblank_start
			+ min_dst_y_ttu_vblank) * dml_घात(2, 2));
	ASSERT(disp_dlg_regs->min_dst_y_next_start < (अचिन्हित पूर्णांक) dml_घात(2, 18));

	DTRACE("DLG: %s: min_dcfclk_mhz                         = %3.2f", __func__, min_dcfclk_mhz);
	DTRACE("DLG: %s: min_ttu_vblank                         = %3.2f", __func__, min_ttu_vblank);
	DTRACE(
			"DLG: %s: min_dst_y_ttu_vblank                   = %3.2f",
			__func__,
			min_dst_y_ttu_vblank);
	DTRACE("DLG: %s: t_calc_us                              = %3.2f", __func__, t_calc_us);
	DTRACE(
			"DLG: %s: disp_dlg_regs->min_dst_y_next_start    = 0x%0x",
			__func__,
			disp_dlg_regs->min_dst_y_next_start);
	DTRACE(
			"DLG: %s: ref_freq_to_pix_freq                   = %3.2f",
			__func__,
			ref_freq_to_pix_freq);

	/* ------------------------- */
	/* Section 1.5.2.2: Prefetch, Active and TTU  */
	/* ------------------------- */
	/* Prefetch Calc */
	/* Source */
	dcc_en = e2e_pipe_param.pipe.src.dcc;
	dual_plane = is_dual_plane(
			(क्रमागत source_क्रमmat_class) e2e_pipe_param.pipe.src.source_क्रमmat);
	mode_422 = 0; /* TODO */
	access_dir = (e2e_pipe_param.pipe.src.source_scan == dm_vert); /* vp access direction: horizontal or vertical accessed */
	bytes_per_element_l = get_bytes_per_element(
			(क्रमागत source_क्रमmat_class) e2e_pipe_param.pipe.src.source_क्रमmat,
			0);
	bytes_per_element_c = get_bytes_per_element(
			(क्रमागत source_क्रमmat_class) e2e_pipe_param.pipe.src.source_क्रमmat,
			1);
	vp_height_l = e2e_pipe_param.pipe.src.viewport_height;
	vp_width_l = e2e_pipe_param.pipe.src.viewport_width;
	vp_height_c = e2e_pipe_param.pipe.src.viewport_height_c;
	vp_width_c = e2e_pipe_param.pipe.src.viewport_width_c;

	/* Scaling */
	htaps_l = e2e_pipe_param.pipe.scale_taps.htaps;
	htaps_c = e2e_pipe_param.pipe.scale_taps.htaps_c;
	hratios_l = e2e_pipe_param.pipe.scale_ratio_depth.hscl_ratio;
	hratios_c = e2e_pipe_param.pipe.scale_ratio_depth.hscl_ratio_c;
	vratio_l = e2e_pipe_param.pipe.scale_ratio_depth.vscl_ratio;
	vratio_c = e2e_pipe_param.pipe.scale_ratio_depth.vscl_ratio_c;

	line_समय_in_us = (htotal / pclk_freq_in_mhz);
	vinit_l = e2e_pipe_param.pipe.scale_ratio_depth.vinit;
	vinit_c = e2e_pipe_param.pipe.scale_ratio_depth.vinit_c;
	vinit_bot_l = e2e_pipe_param.pipe.scale_ratio_depth.vinit_bot;
	vinit_bot_c = e2e_pipe_param.pipe.scale_ratio_depth.vinit_bot_c;

	swath_height_l = rq_dlg_param.rq_l.swath_height;
	swath_width_ub_l = rq_dlg_param.rq_l.swath_width_ub;
	dpte_bytes_per_row_ub_l = rq_dlg_param.rq_l.dpte_bytes_per_row_ub;
	dpte_groups_per_row_ub_l = rq_dlg_param.rq_l.dpte_groups_per_row_ub;
	meta_pte_bytes_per_frame_ub_l = rq_dlg_param.rq_l.meta_pte_bytes_per_frame_ub;
	meta_bytes_per_row_ub_l = rq_dlg_param.rq_l.meta_bytes_per_row_ub;

	swath_height_c = rq_dlg_param.rq_c.swath_height;
	swath_width_ub_c = rq_dlg_param.rq_c.swath_width_ub;
	dpte_bytes_per_row_ub_c = rq_dlg_param.rq_c.dpte_bytes_per_row_ub;
	dpte_groups_per_row_ub_c = rq_dlg_param.rq_c.dpte_groups_per_row_ub;

	meta_chunks_per_row_ub_l = rq_dlg_param.rq_l.meta_chunks_per_row_ub;
	vupdate_offset = e2e_pipe_param.pipe.dest.vupdate_offset;
	vupdate_width = e2e_pipe_param.pipe.dest.vupdate_width;
	vपढ़ोy_offset = e2e_pipe_param.pipe.dest.vपढ़ोy_offset;

	dppclk_delay_subtotal = mode_lib->ip.dppclk_delay_subtotal;
	dispclk_delay_subtotal = mode_lib->ip.dispclk_delay_subtotal;
	pixel_rate_delay_subtotal = dppclk_delay_subtotal * pclk_freq_in_mhz / dppclk_freq_in_mhz
			+ dispclk_delay_subtotal * pclk_freq_in_mhz / dispclk_freq_in_mhz;

	vstartup_start = e2e_pipe_param.pipe.dest.vstartup_start;

	अगर (पूर्णांकerlaced)
		vstartup_start = vstartup_start / 2;

	अगर (vstartup_start >= min_vblank) अणु
		DTRACE(
				"WARNING_DLG: %s:  vblank_start=%d vblank_end=%d",
				__func__,
				vblank_start,
				vblank_end);
		DTRACE(
				"WARNING_DLG: %s:  vstartup_start=%d should be less than min_vblank=%d",
				__func__,
				vstartup_start,
				min_vblank);
		min_vblank = vstartup_start + 1;
		DTRACE(
				"WARNING_DLG: %s:  vstartup_start=%d should be less than min_vblank=%d",
				__func__,
				vstartup_start,
				min_vblank);
	पूर्ण

	dst_x_after_scaler = 0;
	dst_y_after_scaler = 0;

	अगर (e2e_pipe_param.pipe.src.is_hsplit)
		dst_x_after_scaler = pixel_rate_delay_subtotal
				+ e2e_pipe_param.pipe.dest.recout_width;
	अन्यथा
		dst_x_after_scaler = pixel_rate_delay_subtotal;

	अगर (e2e_pipe_param.करोut.output_क्रमmat == dm_420)
		dst_y_after_scaler = 1;
	अन्यथा
		dst_y_after_scaler = 0;

	अगर (dst_x_after_scaler >= htotal) अणु
		dst_x_after_scaler = dst_x_after_scaler - htotal;
		dst_y_after_scaler = dst_y_after_scaler + 1;
	पूर्ण

	DTRACE("DLG: %s: htotal                                 = %d", __func__, htotal);
	DTRACE(
			"DLG: %s: pixel_rate_delay_subtotal              = %d",
			__func__,
			pixel_rate_delay_subtotal);
	DTRACE("DLG: %s: dst_x_after_scaler                     = %d", __func__, dst_x_after_scaler);
	DTRACE("DLG: %s: dst_y_after_scaler                     = %d", __func__, dst_y_after_scaler);

	line_रुको = mode_lib->soc.urgent_latency_us;
	अगर (cstate_en)
		line_रुको = dml_max(mode_lib->soc.sr_enter_plus_निकास_समय_us, line_रुको);
	अगर (pstate_en)
		line_रुको = dml_max(
				mode_lib->soc.dram_घड़ी_change_latency_us
						+ mode_lib->soc.urgent_latency_us,
				line_रुको);
	line_रुको = line_रुको / line_समय_in_us;

	line_o = (द्विगुन) dst_y_after_scaler + dst_x_after_scaler / (द्विगुन) htotal;
	line_setup = (द्विगुन) (vupdate_offset + vupdate_width + vपढ़ोy_offset) / (द्विगुन) htotal;
	line_calc = t_calc_us / line_समय_in_us;

	DTRACE(
			"DLG: %s: soc.sr_enter_plus_exit_time_us     = %3.2f",
			__func__,
			(द्विगुन) mode_lib->soc.sr_enter_plus_निकास_समय_us);
	DTRACE(
			"DLG: %s: soc.dram_clock_change_latency_us   = %3.2f",
			__func__,
			(द्विगुन) mode_lib->soc.dram_घड़ी_change_latency_us);
	DTRACE(
			"DLG: %s: soc.urgent_latency_us              = %3.2f",
			__func__,
			mode_lib->soc.urgent_latency_us);

	DTRACE("DLG: %s: swath_height_l     = %d", __func__, swath_height_l);
	अगर (dual_plane)
		DTRACE("DLG: %s: swath_height_c     = %d", __func__, swath_height_c);

	DTRACE(
			"DLG: %s: t_srx_delay_us     = %3.2f",
			__func__,
			(द्विगुन) dlg_sys_param.t_srx_delay_us);
	DTRACE("DLG: %s: line_time_in_us    = %3.2f", __func__, (द्विगुन) line_समय_in_us);
	DTRACE("DLG: %s: vupdate_offset     = %d", __func__, vupdate_offset);
	DTRACE("DLG: %s: vupdate_width      = %d", __func__, vupdate_width);
	DTRACE("DLG: %s: vready_offset      = %d", __func__, vपढ़ोy_offset);
	DTRACE("DLG: %s: line_time_in_us    = %3.2f", __func__, line_समय_in_us);
	DTRACE("DLG: %s: line_wait          = %3.2f", __func__, line_रुको);
	DTRACE("DLG: %s: line_o             = %3.2f", __func__, line_o);
	DTRACE("DLG: %s: line_setup         = %3.2f", __func__, line_setup);
	DTRACE("DLG: %s: line_calc          = %3.2f", __func__, line_calc);

	dst_y_prefetch = ((द्विगुन) min_vblank - 1.0)
			- (line_setup + line_calc + line_रुको + line_o);
	DTRACE("DLG: %s: dst_y_prefetch (before rnd) = %3.2f", __func__, dst_y_prefetch);
	ASSERT(dst_y_prefetch >= 2.0);

	dst_y_prefetch = dml_न्यूनमान(4.0 * (dst_y_prefetch + 0.125), 1) / 4;
	DTRACE("DLG: %s: dst_y_prefetch (after rnd) = %3.2f", __func__, dst_y_prefetch);

	t_pre_us = dst_y_prefetch * line_समय_in_us;
	vm_bytes = 0;
	meta_row_bytes = 0;

	अगर (dcc_en && vm_en)
		vm_bytes = meta_pte_bytes_per_frame_ub_l;
	अगर (dcc_en)
		meta_row_bytes = meta_bytes_per_row_ub_l;

	max_num_sw_l = 0;
	max_num_sw_c = 0;
	max_partial_sw_l = 0;
	max_partial_sw_c = 0;

	max_vinit_l = पूर्णांकerlaced ? dml_max(vinit_l, vinit_bot_l) : vinit_l;
	max_vinit_c = पूर्णांकerlaced ? dml_max(vinit_c, vinit_bot_c) : vinit_c;

	get_swath_need(mode_lib, &max_num_sw_l, &max_partial_sw_l, swath_height_l, max_vinit_l);
	अगर (dual_plane)
		get_swath_need(
				mode_lib,
				&max_num_sw_c,
				&max_partial_sw_c,
				swath_height_c,
				max_vinit_c);

	lsw_l = max_num_sw_l * swath_height_l + max_partial_sw_l;
	lsw_c = max_num_sw_c * swath_height_c + max_partial_sw_c;
	sw_bytes_ub_l = lsw_l * swath_width_ub_l * bytes_per_element_l;
	sw_bytes_ub_c = lsw_c * swath_width_ub_c * bytes_per_element_c;
	sw_bytes = 0;
	dpte_row_bytes = 0;

	अगर (vm_en) अणु
		अगर (dual_plane)
			dpte_row_bytes = dpte_bytes_per_row_ub_l + dpte_bytes_per_row_ub_c;
		अन्यथा
			dpte_row_bytes = dpte_bytes_per_row_ub_l;
	पूर्ण अन्यथा अणु
		dpte_row_bytes = 0;
	पूर्ण

	अगर (dual_plane)
		sw_bytes = sw_bytes_ub_l + sw_bytes_ub_c;
	अन्यथा
		sw_bytes = sw_bytes_ub_l;

	DTRACE("DLG: %s: sw_bytes_ub_l           = %d", __func__, sw_bytes_ub_l);
	DTRACE("DLG: %s: sw_bytes_ub_c           = %d", __func__, sw_bytes_ub_c);
	DTRACE("DLG: %s: sw_bytes                = %d", __func__, sw_bytes);
	DTRACE("DLG: %s: vm_bytes                = %d", __func__, vm_bytes);
	DTRACE("DLG: %s: meta_row_bytes          = %d", __func__, meta_row_bytes);
	DTRACE("DLG: %s: dpte_row_bytes          = %d", __func__, dpte_row_bytes);

	prefetch_bw = (vm_bytes + 2 * dpte_row_bytes + 2 * meta_row_bytes + sw_bytes) / t_pre_us;
	flip_bw = ((vm_bytes + dpte_row_bytes + meta_row_bytes) * dlg_sys_param.total_flip_bw)
			/ (द्विगुन) dlg_sys_param.total_flip_bytes;
	t_vm_us = line_समय_in_us / 4.0;
	अगर (vm_en && dcc_en) अणु
		t_vm_us = dml_max(
				dlg_sys_param.t_extra_us,
				dml_max((द्विगुन) vm_bytes / prefetch_bw, t_vm_us));

		अगर (अगरlip_en && !dual_plane) अणु
			t_vm_us = dml_max(mode_lib->soc.urgent_latency_us, t_vm_us);
			अगर (flip_bw > 0.)
				t_vm_us = dml_max(vm_bytes / flip_bw, t_vm_us);
		पूर्ण
	पूर्ण

	t_r0_us = dml_max(dlg_sys_param.t_extra_us - t_vm_us, line_समय_in_us - t_vm_us);

	अगर (vm_en || dcc_en) अणु
		t_r0_us = dml_max(
				(द्विगुन) (dpte_row_bytes + meta_row_bytes) / prefetch_bw,
				dlg_sys_param.t_extra_us);
		t_r0_us = dml_max((द्विगुन) (line_समय_in_us - t_vm_us), t_r0_us);

		अगर (अगरlip_en && !dual_plane) अणु
			t_r0_us = dml_max(mode_lib->soc.urgent_latency_us * 2.0, t_r0_us);
			अगर (flip_bw > 0.)
				t_r0_us = dml_max(
						(dpte_row_bytes + meta_row_bytes) / flip_bw,
						t_r0_us);
		पूर्ण
	पूर्ण

	disp_dlg_regs->dst_y_after_scaler = dst_y_after_scaler; /* in terms of line */
	disp_dlg_regs->refcyc_x_after_scaler = dst_x_after_scaler * ref_freq_to_pix_freq; /* in terms of refclk */
	ASSERT(disp_dlg_regs->refcyc_x_after_scaler < (अचिन्हित पूर्णांक) dml_घात(2, 13));
	DTRACE(
			"DLG: %s: disp_dlg_regs->dst_y_after_scaler      = 0x%0x",
			__func__,
			disp_dlg_regs->dst_y_after_scaler);
	DTRACE(
			"DLG: %s: disp_dlg_regs->refcyc_x_after_scaler   = 0x%0x",
			__func__,
			disp_dlg_regs->refcyc_x_after_scaler);

	disp_dlg_regs->dst_y_prefetch = (अचिन्हित पूर्णांक) (dst_y_prefetch * dml_घात(2, 2));
	DTRACE(
			"DLG: %s: disp_dlg_regs->dst_y_prefetch  = %d",
			__func__,
			disp_dlg_regs->dst_y_prefetch);

	dst_y_per_vm_vblank = 0.0;
	dst_y_per_row_vblank = 0.0;

	dst_y_per_vm_vblank = t_vm_us / line_समय_in_us;
	dst_y_per_vm_vblank = dml_न्यूनमान(4.0 * (dst_y_per_vm_vblank + 0.125), 1) / 4.0;
	disp_dlg_regs->dst_y_per_vm_vblank = (अचिन्हित पूर्णांक) (dst_y_per_vm_vblank * dml_घात(2, 2));

	dst_y_per_row_vblank = t_r0_us / line_समय_in_us;
	dst_y_per_row_vblank = dml_न्यूनमान(4.0 * (dst_y_per_row_vblank + 0.125), 1) / 4.0;
	disp_dlg_regs->dst_y_per_row_vblank = (अचिन्हित पूर्णांक) (dst_y_per_row_vblank * dml_घात(2, 2));

	DTRACE("DLG: %s: lsw_l                   = %d", __func__, lsw_l);
	DTRACE("DLG: %s: lsw_c                   = %d", __func__, lsw_c);
	DTRACE("DLG: %s: dpte_bytes_per_row_ub_l = %d", __func__, dpte_bytes_per_row_ub_l);
	DTRACE("DLG: %s: dpte_bytes_per_row_ub_c = %d", __func__, dpte_bytes_per_row_ub_c);

	DTRACE("DLG: %s: prefetch_bw            = %3.2f", __func__, prefetch_bw);
	DTRACE("DLG: %s: flip_bw                = %3.2f", __func__, flip_bw);
	DTRACE("DLG: %s: t_pre_us               = %3.2f", __func__, t_pre_us);
	DTRACE("DLG: %s: t_vm_us                = %3.2f", __func__, t_vm_us);
	DTRACE("DLG: %s: t_r0_us                = %3.2f", __func__, t_r0_us);
	DTRACE("DLG: %s: dst_y_per_vm_vblank    = %3.2f", __func__, dst_y_per_vm_vblank);
	DTRACE("DLG: %s: dst_y_per_row_vblank   = %3.2f", __func__, dst_y_per_row_vblank);
	DTRACE("DLG: %s: dst_y_prefetch         = %3.2f", __func__, dst_y_prefetch);

	min_dst_y_per_vm_vblank = 8.0;
	min_dst_y_per_row_vblank = 16.0;
	अगर (htotal <= 75) अणु
		min_vblank = 300;
		min_dst_y_per_vm_vblank = 100.0;
		min_dst_y_per_row_vblank = 100.0;
	पूर्ण

	ASSERT(dst_y_per_vm_vblank < min_dst_y_per_vm_vblank);
	ASSERT(dst_y_per_row_vblank < min_dst_y_per_row_vblank);

	ASSERT(dst_y_prefetch > (dst_y_per_vm_vblank + dst_y_per_row_vblank));
	lsw = dst_y_prefetch - (dst_y_per_vm_vblank + dst_y_per_row_vblank);

	DTRACE("DLG: %s: lsw = %3.2f", __func__, lsw);

	vratio_pre_l = get_vratio_pre(
			mode_lib,
			max_num_sw_l,
			max_partial_sw_l,
			swath_height_l,
			max_vinit_l,
			lsw);
	vratio_pre_c = 1.0;
	अगर (dual_plane)
		vratio_pre_c = get_vratio_pre(
				mode_lib,
				max_num_sw_c,
				max_partial_sw_c,
				swath_height_c,
				max_vinit_c,
				lsw);

	DTRACE("DLG: %s: vratio_pre_l=%3.2f", __func__, vratio_pre_l);
	DTRACE("DLG: %s: vratio_pre_c=%3.2f", __func__, vratio_pre_c);

	ASSERT(vratio_pre_l <= 4.0);
	अगर (vratio_pre_l >= 4.0)
		disp_dlg_regs->vratio_prefetch = (अचिन्हित पूर्णांक) dml_घात(2, 21) - 1;
	अन्यथा
		disp_dlg_regs->vratio_prefetch = (अचिन्हित पूर्णांक) (vratio_pre_l * dml_घात(2, 19));

	ASSERT(vratio_pre_c <= 4.0);
	अगर (vratio_pre_c >= 4.0)
		disp_dlg_regs->vratio_prefetch_c = (अचिन्हित पूर्णांक) dml_घात(2, 21) - 1;
	अन्यथा
		disp_dlg_regs->vratio_prefetch_c = (अचिन्हित पूर्णांक) (vratio_pre_c * dml_घात(2, 19));

	disp_dlg_regs->refcyc_per_pte_group_vblank_l =
			(अचिन्हित पूर्णांक) (dst_y_per_row_vblank * (द्विगुन) htotal
					* ref_freq_to_pix_freq / (द्विगुन) dpte_groups_per_row_ub_l);
	ASSERT(disp_dlg_regs->refcyc_per_pte_group_vblank_l < (अचिन्हित पूर्णांक) dml_घात(2, 13));

	disp_dlg_regs->refcyc_per_pte_group_vblank_c =
			(अचिन्हित पूर्णांक) (dst_y_per_row_vblank * (द्विगुन) htotal
					* ref_freq_to_pix_freq / (द्विगुन) dpte_groups_per_row_ub_c);
	ASSERT(disp_dlg_regs->refcyc_per_pte_group_vblank_c < (अचिन्हित पूर्णांक) dml_घात(2, 13));

	disp_dlg_regs->refcyc_per_meta_chunk_vblank_l =
			(अचिन्हित पूर्णांक) (dst_y_per_row_vblank * (द्विगुन) htotal
					* ref_freq_to_pix_freq / (द्विगुन) meta_chunks_per_row_ub_l);
	ASSERT(disp_dlg_regs->refcyc_per_meta_chunk_vblank_l < (अचिन्हित पूर्णांक) dml_घात(2, 13));

	disp_dlg_regs->refcyc_per_meta_chunk_vblank_c =
			disp_dlg_regs->refcyc_per_meta_chunk_vblank_l;/* dcc क्रम 4:2:0 is not supported in dcn1.0.  asचिन्हित to be the same as _l क्रम now */

	/* Active */
	req_per_swath_ub_l = rq_dlg_param.rq_l.req_per_swath_ub;
	req_per_swath_ub_c = rq_dlg_param.rq_c.req_per_swath_ub;
	meta_row_height_l = rq_dlg_param.rq_l.meta_row_height;
	swath_width_pixels_ub_l = 0;
	swath_width_pixels_ub_c = 0;
	scaler_rec_in_width_l = 0;
	scaler_rec_in_width_c = 0;
	dpte_row_height_l = rq_dlg_param.rq_l.dpte_row_height;
	dpte_row_height_c = rq_dlg_param.rq_c.dpte_row_height;

	disp_dlg_regs->dst_y_per_pte_row_nom_l = (अचिन्हित पूर्णांक) ((द्विगुन) dpte_row_height_l
			/ (द्विगुन) vratio_l * dml_घात(2, 2));
	ASSERT(disp_dlg_regs->dst_y_per_pte_row_nom_l < (अचिन्हित पूर्णांक) dml_घात(2, 17));

	disp_dlg_regs->dst_y_per_pte_row_nom_c = (अचिन्हित पूर्णांक) ((द्विगुन) dpte_row_height_c
			/ (द्विगुन) vratio_c * dml_घात(2, 2));
	ASSERT(disp_dlg_regs->dst_y_per_pte_row_nom_c < (अचिन्हित पूर्णांक) dml_घात(2, 17));

	disp_dlg_regs->dst_y_per_meta_row_nom_l = (अचिन्हित पूर्णांक) ((द्विगुन) meta_row_height_l
			/ (द्विगुन) vratio_l * dml_घात(2, 2));
	ASSERT(disp_dlg_regs->dst_y_per_meta_row_nom_l < (अचिन्हित पूर्णांक) dml_घात(2, 17));

	disp_dlg_regs->dst_y_per_meta_row_nom_c = disp_dlg_regs->dst_y_per_meta_row_nom_l; /* dcc क्रम 4:2:0 is not supported in dcn1.0.  asचिन्हित to be the same as _l क्रम now */

	disp_dlg_regs->refcyc_per_pte_group_nom_l = (अचिन्हित पूर्णांक) ((द्विगुन) dpte_row_height_l
			/ (द्विगुन) vratio_l * (द्विगुन) htotal * ref_freq_to_pix_freq
			/ (द्विगुन) dpte_groups_per_row_ub_l);
	अगर (disp_dlg_regs->refcyc_per_pte_group_nom_l >= (अचिन्हित पूर्णांक) dml_घात(2, 23))
		disp_dlg_regs->refcyc_per_pte_group_nom_l = dml_घात(2, 23) - 1;

	disp_dlg_regs->refcyc_per_pte_group_nom_c = (अचिन्हित पूर्णांक) ((द्विगुन) dpte_row_height_c
			/ (द्विगुन) vratio_c * (द्विगुन) htotal * ref_freq_to_pix_freq
			/ (द्विगुन) dpte_groups_per_row_ub_c);
	अगर (disp_dlg_regs->refcyc_per_pte_group_nom_c >= (अचिन्हित पूर्णांक) dml_घात(2, 23))
		disp_dlg_regs->refcyc_per_pte_group_nom_c = dml_घात(2, 23) - 1;

	disp_dlg_regs->refcyc_per_meta_chunk_nom_l = (अचिन्हित पूर्णांक) ((द्विगुन) meta_row_height_l
			/ (द्विगुन) vratio_l * (द्विगुन) htotal * ref_freq_to_pix_freq
			/ (द्विगुन) meta_chunks_per_row_ub_l);
	अगर (disp_dlg_regs->refcyc_per_meta_chunk_nom_l >= (अचिन्हित पूर्णांक) dml_घात(2, 23))
		disp_dlg_regs->refcyc_per_meta_chunk_nom_l = dml_घात(2, 23) - 1;

	अगर (mode_422) अणु
		swath_width_pixels_ub_l = swath_width_ub_l * 2; /* *2 क्रम 2 pixel per element */
		swath_width_pixels_ub_c = swath_width_ub_c * 2;
	पूर्ण अन्यथा अणु
		swath_width_pixels_ub_l = swath_width_ub_l * 1;
		swath_width_pixels_ub_c = swath_width_ub_c * 1;
	पूर्ण

	hscale_pixel_rate_l = 0.;
	hscale_pixel_rate_c = 0.;
	min_hratio_fact_l = 1.0;
	min_hratio_fact_c = 1.0;

	अगर (htaps_l <= 1)
		min_hratio_fact_l = 2.0;
	अन्यथा अगर (htaps_l <= 6) अणु
		अगर ((hratios_l * 2.0) > 4.0)
			min_hratio_fact_l = 4.0;
		अन्यथा
			min_hratio_fact_l = hratios_l * 2.0;
	पूर्ण अन्यथा अणु
		अगर (hratios_l > 4.0)
			min_hratio_fact_l = 4.0;
		अन्यथा
			min_hratio_fact_l = hratios_l;
	पूर्ण

	hscale_pixel_rate_l = min_hratio_fact_l * dppclk_freq_in_mhz;

	अगर (htaps_c <= 1)
		min_hratio_fact_c = 2.0;
	अन्यथा अगर (htaps_c <= 6) अणु
		अगर ((hratios_c * 2.0) > 4.0)
			min_hratio_fact_c = 4.0;
		अन्यथा
			min_hratio_fact_c = hratios_c * 2.0;
	पूर्ण अन्यथा अणु
		अगर (hratios_c > 4.0)
			min_hratio_fact_c = 4.0;
		अन्यथा
			min_hratio_fact_c = hratios_c;
	पूर्ण

	hscale_pixel_rate_c = min_hratio_fact_c * dppclk_freq_in_mhz;

	refcyc_per_line_delivery_pre_l = 0.;
	refcyc_per_line_delivery_pre_c = 0.;
	refcyc_per_line_delivery_l = 0.;
	refcyc_per_line_delivery_c = 0.;

	refcyc_per_req_delivery_pre_l = 0.;
	refcyc_per_req_delivery_pre_c = 0.;
	refcyc_per_req_delivery_l = 0.;
	refcyc_per_req_delivery_c = 0.;
	refcyc_per_req_delivery_pre_cur0 = 0.;
	refcyc_per_req_delivery_cur0 = 0.;

	full_recout_width = 0;
	अगर (e2e_pipe_param.pipe.src.is_hsplit) अणु
		अगर (e2e_pipe_param.pipe.dest.full_recout_width == 0) अणु
			DTRACE("DLG: %s: Warningfull_recout_width not set in hsplit mode", __func__);
			full_recout_width = e2e_pipe_param.pipe.dest.recout_width * 2; /* assume half split क्रम dcn1 */
		पूर्ण अन्यथा
			full_recout_width = e2e_pipe_param.pipe.dest.full_recout_width;
	पूर्ण अन्यथा
		full_recout_width = e2e_pipe_param.pipe.dest.recout_width;

	refcyc_per_line_delivery_pre_l = get_refcyc_per_delivery(
			mode_lib,
			refclk_freq_in_mhz,
			pclk_freq_in_mhz,
			full_recout_width,
			vratio_pre_l,
			hscale_pixel_rate_l,
			swath_width_pixels_ub_l,
			1); /* per line */

	refcyc_per_line_delivery_l = get_refcyc_per_delivery(
			mode_lib,
			refclk_freq_in_mhz,
			pclk_freq_in_mhz,
			full_recout_width,
			vratio_l,
			hscale_pixel_rate_l,
			swath_width_pixels_ub_l,
			1); /* per line */

	DTRACE("DLG: %s: full_recout_width              = %d", __func__, full_recout_width);
	DTRACE("DLG: %s: hscale_pixel_rate_l            = %3.2f", __func__, hscale_pixel_rate_l);
	DTRACE(
			"DLG: %s: refcyc_per_line_delivery_pre_l = %3.2f",
			__func__,
			refcyc_per_line_delivery_pre_l);
	DTRACE(
			"DLG: %s: refcyc_per_line_delivery_l     = %3.2f",
			__func__,
			refcyc_per_line_delivery_l);

	disp_dlg_regs->refcyc_per_line_delivery_pre_l = (अचिन्हित पूर्णांक) dml_न्यूनमान(
			refcyc_per_line_delivery_pre_l,
			1);
	disp_dlg_regs->refcyc_per_line_delivery_l = (अचिन्हित पूर्णांक) dml_न्यूनमान(
			refcyc_per_line_delivery_l,
			1);
	ASSERT(disp_dlg_regs->refcyc_per_line_delivery_pre_l < (अचिन्हित पूर्णांक) dml_घात(2, 13));
	ASSERT(disp_dlg_regs->refcyc_per_line_delivery_l < (अचिन्हित पूर्णांक) dml_घात(2, 13));

	अगर (dual_plane) अणु
		refcyc_per_line_delivery_pre_c = get_refcyc_per_delivery(
				mode_lib,
				refclk_freq_in_mhz,
				pclk_freq_in_mhz,
				full_recout_width,
				vratio_pre_c,
				hscale_pixel_rate_c,
				swath_width_pixels_ub_c,
				1); /* per line */

		refcyc_per_line_delivery_c = get_refcyc_per_delivery(
				mode_lib,
				refclk_freq_in_mhz,
				pclk_freq_in_mhz,
				full_recout_width,
				vratio_c,
				hscale_pixel_rate_c,
				swath_width_pixels_ub_c,
				1); /* per line */

		DTRACE(
				"DLG: %s: refcyc_per_line_delivery_pre_c = %3.2f",
				__func__,
				refcyc_per_line_delivery_pre_c);
		DTRACE(
				"DLG: %s: refcyc_per_line_delivery_c     = %3.2f",
				__func__,
				refcyc_per_line_delivery_c);

		disp_dlg_regs->refcyc_per_line_delivery_pre_c = (अचिन्हित पूर्णांक) dml_न्यूनमान(
				refcyc_per_line_delivery_pre_c,
				1);
		disp_dlg_regs->refcyc_per_line_delivery_c = (अचिन्हित पूर्णांक) dml_न्यूनमान(
				refcyc_per_line_delivery_c,
				1);
		ASSERT(disp_dlg_regs->refcyc_per_line_delivery_pre_c < (अचिन्हित पूर्णांक) dml_घात(2, 13));
		ASSERT(disp_dlg_regs->refcyc_per_line_delivery_c < (अचिन्हित पूर्णांक) dml_घात(2, 13));
	पूर्ण
	disp_dlg_regs->chunk_hdl_adjust_cur0 = 3;

	/* TTU - Luma / Chroma */
	अगर (access_dir) अणु /* vertical access */
		scaler_rec_in_width_l = vp_height_l;
		scaler_rec_in_width_c = vp_height_c;
	पूर्ण अन्यथा अणु
		scaler_rec_in_width_l = vp_width_l;
		scaler_rec_in_width_c = vp_width_c;
	पूर्ण

	refcyc_per_req_delivery_pre_l = get_refcyc_per_delivery(
			mode_lib,
			refclk_freq_in_mhz,
			pclk_freq_in_mhz,
			full_recout_width,
			vratio_pre_l,
			hscale_pixel_rate_l,
			scaler_rec_in_width_l,
			req_per_swath_ub_l); /* per req */
	refcyc_per_req_delivery_l = get_refcyc_per_delivery(
			mode_lib,
			refclk_freq_in_mhz,
			pclk_freq_in_mhz,
			full_recout_width,
			vratio_l,
			hscale_pixel_rate_l,
			scaler_rec_in_width_l,
			req_per_swath_ub_l); /* per req */

	DTRACE(
			"DLG: %s: refcyc_per_req_delivery_pre_l = %3.2f",
			__func__,
			refcyc_per_req_delivery_pre_l);
	DTRACE(
			"DLG: %s: refcyc_per_req_delivery_l     = %3.2f",
			__func__,
			refcyc_per_req_delivery_l);

	disp_ttu_regs->refcyc_per_req_delivery_pre_l = (अचिन्हित पूर्णांक) (refcyc_per_req_delivery_pre_l
			* dml_घात(2, 10));
	disp_ttu_regs->refcyc_per_req_delivery_l = (अचिन्हित पूर्णांक) (refcyc_per_req_delivery_l
			* dml_घात(2, 10));

	ASSERT(refcyc_per_req_delivery_pre_l < dml_घात(2, 13));
	ASSERT(refcyc_per_req_delivery_l < dml_घात(2, 13));

	अगर (dual_plane) अणु
		refcyc_per_req_delivery_pre_c = get_refcyc_per_delivery(
				mode_lib,
				refclk_freq_in_mhz,
				pclk_freq_in_mhz,
				full_recout_width,
				vratio_pre_c,
				hscale_pixel_rate_c,
				scaler_rec_in_width_c,
				req_per_swath_ub_c); /* per req  */
		refcyc_per_req_delivery_c = get_refcyc_per_delivery(
				mode_lib,
				refclk_freq_in_mhz,
				pclk_freq_in_mhz,
				full_recout_width,
				vratio_c,
				hscale_pixel_rate_c,
				scaler_rec_in_width_c,
				req_per_swath_ub_c); /* per req */

		DTRACE(
				"DLG: %s: refcyc_per_req_delivery_pre_c = %3.2f",
				__func__,
				refcyc_per_req_delivery_pre_c);
		DTRACE(
				"DLG: %s: refcyc_per_req_delivery_c     = %3.2f",
				__func__,
				refcyc_per_req_delivery_c);

		disp_ttu_regs->refcyc_per_req_delivery_pre_c =
				(अचिन्हित पूर्णांक) (refcyc_per_req_delivery_pre_c * dml_घात(2, 10));
		disp_ttu_regs->refcyc_per_req_delivery_c = (अचिन्हित पूर्णांक) (refcyc_per_req_delivery_c
				* dml_घात(2, 10));

		ASSERT(refcyc_per_req_delivery_pre_c < dml_घात(2, 13));
		ASSERT(refcyc_per_req_delivery_c < dml_घात(2, 13));
	पूर्ण

	/* TTU - Cursor */
	hratios_cur0 = e2e_pipe_param.pipe.scale_ratio_depth.hscl_ratio;
	cur0_src_width = e2e_pipe_param.pipe.src.cur0_src_width; /* cursor source width */
	cur0_bpp = (क्रमागत cursor_bpp) e2e_pipe_param.pipe.src.cur0_bpp;
	cur0_req_size = 0;
	cur0_req_width = 0;
	cur0_width_ub = 0.0;
	cur0_req_per_width = 0.0;
	hactive_cur0 = 0.0;

	ASSERT(cur0_src_width <= 256);

	अगर (cur0_src_width > 0) अणु
		अचिन्हित पूर्णांक cur0_bit_per_pixel = 0;

		अगर (cur0_bpp == dm_cur_2bit) अणु
			cur0_req_size = 64; /* byte */
			cur0_bit_per_pixel = 2;
		पूर्ण अन्यथा अणु /* 32bit */
			cur0_bit_per_pixel = 32;
			अगर (cur0_src_width >= 1 && cur0_src_width <= 16)
				cur0_req_size = 64;
			अन्यथा अगर (cur0_src_width >= 17 && cur0_src_width <= 31)
				cur0_req_size = 128;
			अन्यथा
				cur0_req_size = 256;
		पूर्ण

		cur0_req_width = (द्विगुन) cur0_req_size / ((द्विगुन) cur0_bit_per_pixel / 8.0);
		cur0_width_ub = dml_उच्चमान((द्विगुन) cur0_src_width / (द्विगुन) cur0_req_width, 1)
				* (द्विगुन) cur0_req_width;
		cur0_req_per_width = cur0_width_ub / (द्विगुन) cur0_req_width;
		hactive_cur0 = (द्विगुन) cur0_src_width / hratios_cur0; /* TODO: oswin to think about what to करो क्रम cursor */

		अगर (vratio_pre_l <= 1.0) अणु
			refcyc_per_req_delivery_pre_cur0 = hactive_cur0 * ref_freq_to_pix_freq
					/ (द्विगुन) cur0_req_per_width;
		पूर्ण अन्यथा अणु
			refcyc_per_req_delivery_pre_cur0 = (द्विगुन) refclk_freq_in_mhz
					* (द्विगुन) cur0_src_width / hscale_pixel_rate_l
					/ (द्विगुन) cur0_req_per_width;
		पूर्ण

		disp_ttu_regs->refcyc_per_req_delivery_pre_cur0 =
				(अचिन्हित पूर्णांक) (refcyc_per_req_delivery_pre_cur0 * dml_घात(2, 10));
		ASSERT(refcyc_per_req_delivery_pre_cur0 < dml_घात(2, 13));

		अगर (vratio_l <= 1.0) अणु
			refcyc_per_req_delivery_cur0 = hactive_cur0 * ref_freq_to_pix_freq
					/ (द्विगुन) cur0_req_per_width;
		पूर्ण अन्यथा अणु
			refcyc_per_req_delivery_cur0 = (द्विगुन) refclk_freq_in_mhz
					* (द्विगुन) cur0_src_width / hscale_pixel_rate_l
					/ (द्विगुन) cur0_req_per_width;
		पूर्ण

		DTRACE("DLG: %s: cur0_req_width                     = %d", __func__, cur0_req_width);
		DTRACE(
				"DLG: %s: cur0_width_ub                      = %3.2f",
				__func__,
				cur0_width_ub);
		DTRACE(
				"DLG: %s: cur0_req_per_width                 = %3.2f",
				__func__,
				cur0_req_per_width);
		DTRACE(
				"DLG: %s: hactive_cur0                       = %3.2f",
				__func__,
				hactive_cur0);
		DTRACE(
				"DLG: %s: refcyc_per_req_delivery_pre_cur0   = %3.2f",
				__func__,
				refcyc_per_req_delivery_pre_cur0);
		DTRACE(
				"DLG: %s: refcyc_per_req_delivery_cur0       = %3.2f",
				__func__,
				refcyc_per_req_delivery_cur0);

		disp_ttu_regs->refcyc_per_req_delivery_cur0 =
				(अचिन्हित पूर्णांक) (refcyc_per_req_delivery_cur0 * dml_घात(2, 10));
		ASSERT(refcyc_per_req_delivery_cur0 < dml_घात(2, 13));
	पूर्ण अन्यथा अणु
		disp_ttu_regs->refcyc_per_req_delivery_pre_cur0 = 0;
		disp_ttu_regs->refcyc_per_req_delivery_cur0 = 0;
	पूर्ण

	/* TTU - Misc */
	disp_ttu_regs->qos_level_low_wm = 0;
	ASSERT(disp_ttu_regs->qos_level_low_wm < dml_घात(2, 14));
	disp_ttu_regs->qos_level_high_wm = (अचिन्हित पूर्णांक) (4.0 * (द्विगुन) htotal
			* ref_freq_to_pix_freq);
	ASSERT(disp_ttu_regs->qos_level_high_wm < dml_घात(2, 14));

	disp_ttu_regs->qos_level_flip = 14;
	disp_ttu_regs->qos_level_fixed_l = 8;
	disp_ttu_regs->qos_level_fixed_c = 8;
	disp_ttu_regs->qos_level_fixed_cur0 = 8;
	disp_ttu_regs->qos_ramp_disable_l = 0;
	disp_ttu_regs->qos_ramp_disable_c = 0;
	disp_ttu_regs->qos_ramp_disable_cur0 = 0;

	disp_ttu_regs->min_ttu_vblank = min_ttu_vblank * refclk_freq_in_mhz;
	ASSERT(disp_ttu_regs->min_ttu_vblank < dml_घात(2, 24));

	prपूर्णांक__ttu_regs_st(mode_lib, *disp_ttu_regs);
	prपूर्णांक__dlg_regs_st(mode_lib, *disp_dlg_regs);
पूर्ण
