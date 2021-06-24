<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
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

#समावेश "../display_mode_lib.h"
#समावेश "../display_mode_vba.h"
#समावेश "display_rq_dlg_calc_20v2.h"

// Function: dml20v2_rq_dlg_get_rq_params
//  Calculate requestor related parameters that रेजिस्टर definition agnostic
//  (i.e. this layer करोes try to separate real values from रेजिस्टर definition)
// Input:
//  pipe_src_param - pipe source configuration (e.g. vp, pitch, etc.)
// Output:
//  rq_param - values that can be used to setup RQ (e.g. swath_height, plane1_addr, etc.)
//
अटल व्योम dml20v2_rq_dlg_get_rq_params(
		काष्ठा display_mode_lib *mode_lib,
		display_rq_params_st * rq_param,
		स्थिर display_pipe_source_params_st pipe_src_param);

// Function: dml20v2_rq_dlg_get_dlg_params
//  Calculate deadline related parameters
//
अटल व्योम dml20v2_rq_dlg_get_dlg_params(काष्ठा display_mode_lib *mode_lib,
		स्थिर display_e2e_pipe_params_st *e2e_pipe_param,
		स्थिर अचिन्हित पूर्णांक num_pipes,
		स्थिर अचिन्हित पूर्णांक pipe_idx,
		display_dlg_regs_st *disp_dlg_regs,
		display_ttu_regs_st *disp_ttu_regs,
		स्थिर display_rq_dlg_params_st rq_dlg_param,
		स्थिर display_dlg_sys_params_st dlg_sys_param,
		स्थिर bool cstate_en,
		स्थिर bool pstate_en);
/*
 * NOTE:
 *   This file is gcc-parseable HW gospel, coming straight from HW engineers.
 *
 * It करोesn't adhere to Linux kernel style and someबार will करो things in odd
 * ways. Unless there is something clearly wrong with it the code should
 * reमुख्य as-is as it provides us with a guarantee from HW that it is correct.
 */

अटल व्योम calculate_ttu_cursor(काष्ठा display_mode_lib *mode_lib,
		द्विगुन *refcyc_per_req_delivery_pre_cur,
		द्विगुन *refcyc_per_req_delivery_cur,
		द्विगुन refclk_freq_in_mhz,
		द्विगुन ref_freq_to_pix_freq,
		द्विगुन hscale_pixel_rate_l,
		द्विगुन hscl_ratio,
		द्विगुन vratio_pre_l,
		द्विगुन vratio_l,
		अचिन्हित पूर्णांक cur_width,
		क्रमागत cursor_bpp cur_bpp);

#समावेश "../dml_inline_defs.h"

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
	पूर्ण अन्यथा अगर (source_क्रमmat == dm_444_8) अणु
		ret_val = 1;
	पूर्ण
	वापस ret_val;
पूर्ण

अटल bool is_dual_plane(क्रमागत source_क्रमmat_class source_क्रमmat)
अणु
	bool ret_val = false;

	अगर ((source_क्रमmat == dm_420_8) || (source_क्रमmat == dm_420_10))
		ret_val = true;

	वापस ret_val;
पूर्ण

अटल द्विगुन get_refcyc_per_delivery(काष्ठा display_mode_lib *mode_lib,
		द्विगुन refclk_freq_in_mhz,
		द्विगुन pclk_freq_in_mhz,
		bool odm_combine,
		अचिन्हित पूर्णांक recout_width,
		अचिन्हित पूर्णांक hactive,
		द्विगुन vratio,
		द्विगुन hscale_pixel_rate,
		अचिन्हित पूर्णांक delivery_width,
		अचिन्हित पूर्णांक req_per_swath_ub)
अणु
	द्विगुन refcyc_per_delivery = 0.0;

	अगर (vratio <= 1.0) अणु
		अगर (odm_combine)
			refcyc_per_delivery = (द्विगुन) refclk_freq_in_mhz
					* dml_min((द्विगुन) recout_width, (द्विगुन) hactive / 2.0)
					/ pclk_freq_in_mhz / (द्विगुन) req_per_swath_ub;
		अन्यथा
			refcyc_per_delivery = (द्विगुन) refclk_freq_in_mhz * (द्विगुन) recout_width
					/ pclk_freq_in_mhz / (द्विगुन) req_per_swath_ub;
	पूर्ण अन्यथा अणु
		refcyc_per_delivery = (द्विगुन) refclk_freq_in_mhz * (द्विगुन) delivery_width
				/ (द्विगुन) hscale_pixel_rate / (द्विगुन) req_per_swath_ub;
	पूर्ण

	dml_prपूर्णांक("DML_DLG: %s: refclk_freq_in_mhz = %3.2f\n", __func__, refclk_freq_in_mhz);
	dml_prपूर्णांक("DML_DLG: %s: pclk_freq_in_mhz   = %3.2f\n", __func__, pclk_freq_in_mhz);
	dml_prपूर्णांक("DML_DLG: %s: recout_width       = %d\n", __func__, recout_width);
	dml_prपूर्णांक("DML_DLG: %s: vratio             = %3.2f\n", __func__, vratio);
	dml_prपूर्णांक("DML_DLG: %s: req_per_swath_ub   = %d\n", __func__, req_per_swath_ub);
	dml_prपूर्णांक("DML_DLG: %s: refcyc_per_delivery= %3.2f\n", __func__, refcyc_per_delivery);

	वापस refcyc_per_delivery;

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

अटल व्योम extract_rq_sizing_regs(काष्ठा display_mode_lib *mode_lib,
		display_data_rq_regs_st *rq_regs,
		स्थिर display_data_rq_sizing_params_st rq_sizing)
अणु
	dml_prपूर्णांक("DML_DLG: %s: rq_sizing param\n", __func__);
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

अटल व्योम extract_rq_regs(काष्ठा display_mode_lib *mode_lib,
		display_rq_regs_st *rq_regs,
		स्थिर display_rq_params_st rq_param)
अणु
	अचिन्हित पूर्णांक detile_buf_size_in_bytes = mode_lib->ip.det_buffer_size_kbytes * 1024;
	अचिन्हित पूर्णांक detile_buf_plane1_addr = 0;

	extract_rq_sizing_regs(mode_lib, &(rq_regs->rq_regs_l), rq_param.sizing.rq_l);

	rq_regs->rq_regs_l.pte_row_height_linear = dml_न्यूनमान(dml_log2(rq_param.dlg.rq_l.dpte_row_height),
			1) - 3;

	अगर (rq_param.yuv420) अणु
		extract_rq_sizing_regs(mode_lib, &(rq_regs->rq_regs_c), rq_param.sizing.rq_c);
		rq_regs->rq_regs_c.pte_row_height_linear = dml_न्यूनमान(dml_log2(rq_param.dlg.rq_c.dpte_row_height),
				1) - 3;
	पूर्ण

	rq_regs->rq_regs_l.swath_height = dml_log2(rq_param.dlg.rq_l.swath_height);
	rq_regs->rq_regs_c.swath_height = dml_log2(rq_param.dlg.rq_c.swath_height);

	// TODO: take the max between luma, chroma chunk size?
	// okay क्रम now, as we are setting chunk_bytes to 8kb anyways
	अगर (rq_param.sizing.rq_l.chunk_bytes >= 32 * 1024) अणु //32kb
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
			detile_buf_plane1_addr = (detile_buf_size_in_bytes / 2.0 / 64.0); // half to chroma
		पूर्ण अन्यथा अणु
			detile_buf_plane1_addr = dml_round_to_multiple((अचिन्हित पूर्णांक) ((2.0 * detile_buf_size_in_bytes) / 3.0),
					256,
					0) / 64.0; // 2/3 to chroma
		पूर्ण
	पूर्ण
	rq_regs->plane1_base_address = detile_buf_plane1_addr;
पूर्ण

अटल व्योम handle_det_buf_split(काष्ठा display_mode_lib *mode_lib,
		display_rq_params_st *rq_param,
		स्थिर display_pipe_source_params_st pipe_src_param)
अणु
	अचिन्हित पूर्णांक total_swath_bytes = 0;
	अचिन्हित पूर्णांक swath_bytes_l = 0;
	अचिन्हित पूर्णांक swath_bytes_c = 0;
	अचिन्हित पूर्णांक full_swath_bytes_packed_l = 0;
	अचिन्हित पूर्णांक full_swath_bytes_packed_c = 0;
	bool req128_l = false;
	bool req128_c = false;
	bool surf_linear = (pipe_src_param.sw_mode == dm_sw_linear);
	bool surf_vert = (pipe_src_param.source_scan == dm_vert);
	अचिन्हित पूर्णांक log2_swath_height_l = 0;
	अचिन्हित पूर्णांक log2_swath_height_c = 0;
	अचिन्हित पूर्णांक detile_buf_size_in_bytes = mode_lib->ip.det_buffer_size_kbytes * 1024;

	full_swath_bytes_packed_l = rq_param->misc.rq_l.full_swath_bytes;
	full_swath_bytes_packed_c = rq_param->misc.rq_c.full_swath_bytes;

	अगर (rq_param->yuv420_10bpc) अणु
		full_swath_bytes_packed_l = dml_round_to_multiple(rq_param->misc.rq_l.full_swath_bytes * 2 / 3,
				256,
				1) + 256;
		full_swath_bytes_packed_c = dml_round_to_multiple(rq_param->misc.rq_c.full_swath_bytes * 2 / 3,
				256,
				1) + 256;
	पूर्ण

	अगर (rq_param->yuv420) अणु
		total_swath_bytes = 2 * full_swath_bytes_packed_l + 2 * full_swath_bytes_packed_c;

		अगर (total_swath_bytes <= detile_buf_size_in_bytes) अणु //full 256b request
			req128_l = false;
			req128_c = false;
			swath_bytes_l = full_swath_bytes_packed_l;
			swath_bytes_c = full_swath_bytes_packed_c;
		पूर्ण अन्यथा अणु //128b request (क्रम luma only क्रम yuv420 8bpc)
			req128_l = true;
			req128_c = false;
			swath_bytes_l = full_swath_bytes_packed_l / 2;
			swath_bytes_c = full_swath_bytes_packed_c;
		पूर्ण
		// Note: assumption, the config that pass in will fit पूर्णांकo
		//       the detiled buffer.
	पूर्ण अन्यथा अणु
		total_swath_bytes = 2 * full_swath_bytes_packed_l;

		अगर (total_swath_bytes <= detile_buf_size_in_bytes)
			req128_l = false;
		अन्यथा
			req128_l = true;

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

	dml_prपूर्णांक("DML_DLG: %s: req128_l = %0d\n", __func__, req128_l);
	dml_prपूर्णांक("DML_DLG: %s: req128_c = %0d\n", __func__, req128_c);
	dml_prपूर्णांक("DML_DLG: %s: full_swath_bytes_packed_l = %0d\n",
			__func__,
			full_swath_bytes_packed_l);
	dml_prपूर्णांक("DML_DLG: %s: full_swath_bytes_packed_c = %0d\n",
			__func__,
			full_swath_bytes_packed_c);
पूर्ण

अटल व्योम get_meta_and_pte_attr(काष्ठा display_mode_lib *mode_lib,
		display_data_rq_dlg_params_st *rq_dlg_param,
		display_data_rq_misc_params_st *rq_misc_param,
		display_data_rq_sizing_params_st *rq_sizing_param,
		अचिन्हित पूर्णांक vp_width,
		अचिन्हित पूर्णांक vp_height,
		अचिन्हित पूर्णांक data_pitch,
		अचिन्हित पूर्णांक meta_pitch,
		अचिन्हित पूर्णांक source_क्रमmat,
		अचिन्हित पूर्णांक tiling,
		अचिन्हित पूर्णांक macro_tile_size,
		अचिन्हित पूर्णांक source_scan,
		अचिन्हित पूर्णांक is_chroma)
अणु
	bool surf_linear = (tiling == dm_sw_linear);
	bool surf_vert = (source_scan == dm_vert);

	अचिन्हित पूर्णांक bytes_per_element;
	अचिन्हित पूर्णांक bytes_per_element_y = get_bytes_per_element((क्रमागत source_क्रमmat_class)(source_क्रमmat),
			false);
	अचिन्हित पूर्णांक bytes_per_element_c = get_bytes_per_element((क्रमागत source_क्रमmat_class)(source_क्रमmat),
			true);

	अचिन्हित पूर्णांक blk256_width = 0;
	अचिन्हित पूर्णांक blk256_height = 0;

	अचिन्हित पूर्णांक blk256_width_y = 0;
	अचिन्हित पूर्णांक blk256_height_y = 0;
	अचिन्हित पूर्णांक blk256_width_c = 0;
	अचिन्हित पूर्णांक blk256_height_c = 0;
	अचिन्हित पूर्णांक log2_bytes_per_element;
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

	//full sized meta chunk width in unit of data elements
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
	स्थिर अचिन्हित पूर्णांक log2_vmpg_bytes = dml_log2(mode_lib->soc.vmm_page_size_bytes);
	स्थिर अचिन्हित पूर्णांक dpte_buf_in_pte_reqs = mode_lib->ip.dpte_buffer_size_in_pte_reqs_luma;
	स्थिर अचिन्हित पूर्णांक pde_proc_buffer_size_64k_reqs =
			mode_lib->ip.pde_proc_buffer_size_64k_reqs;

	अचिन्हित पूर्णांक log2_vmpg_height = 0;
	अचिन्हित पूर्णांक log2_vmpg_width = 0;
	अचिन्हित पूर्णांक log2_dpte_req_height_ptes = 0;
	अचिन्हित पूर्णांक log2_dpte_req_height = 0;
	अचिन्हित पूर्णांक log2_dpte_req_width = 0;
	अचिन्हित पूर्णांक log2_dpte_row_height_linear = 0;
	अचिन्हित पूर्णांक log2_dpte_row_height = 0;
	अचिन्हित पूर्णांक log2_dpte_group_width = 0;
	अचिन्हित पूर्णांक dpte_row_width_ub = 0;
	अचिन्हित पूर्णांक dpte_req_height = 0;
	अचिन्हित पूर्णांक dpte_req_width = 0;
	अचिन्हित पूर्णांक dpte_group_width = 0;
	अचिन्हित पूर्णांक log2_dpte_group_bytes = 0;
	अचिन्हित पूर्णांक log2_dpte_group_length = 0;
	अचिन्हित पूर्णांक pde_buf_entries;
	bool yuv420 = (source_क्रमmat == dm_420_8 || source_क्रमmat == dm_420_10);

	Calculate256BBlockSizes((क्रमागत source_क्रमmat_class)(source_क्रमmat),
			(क्रमागत dm_swizzle_mode)(tiling),
			bytes_per_element_y,
			bytes_per_element_c,
			&blk256_height_y,
			&blk256_height_c,
			&blk256_width_y,
			&blk256_width_c);

	अगर (!is_chroma) अणु
		blk256_width = blk256_width_y;
		blk256_height = blk256_height_y;
		bytes_per_element = bytes_per_element_y;
	पूर्ण अन्यथा अणु
		blk256_width = blk256_width_c;
		blk256_height = blk256_height_c;
		bytes_per_element = bytes_per_element_c;
	पूर्ण

	log2_bytes_per_element = dml_log2(bytes_per_element);

	dml_prपूर्णांक("DML_DLG: %s: surf_linear        = %d\n", __func__, surf_linear);
	dml_prपूर्णांक("DML_DLG: %s: surf_vert          = %d\n", __func__, surf_vert);
	dml_prपूर्णांक("DML_DLG: %s: blk256_width       = %d\n", __func__, blk256_width);
	dml_prपूर्णांक("DML_DLG: %s: blk256_height      = %d\n", __func__, blk256_height);

	log2_blk256_width = dml_log2((द्विगुन) blk256_width);
	log2_blk256_height = dml_log2((द्विगुन) blk256_height);
	blk_bytes = surf_linear ?
			256 : get_blk_size_bytes((क्रमागत source_macro_tile_size) macro_tile_size);
	log2_blk_bytes = dml_log2((द्विगुन) blk_bytes);
	log2_blk_height = 0;
	log2_blk_width = 0;

	// remember log rule
	// "+" in log is multiply
	// "-" in log is भागide
	// "/2" is like square root
	// blk is vertical biased
	अगर (tiling != dm_sw_linear)
		log2_blk_height = log2_blk256_height
				+ dml_उच्चमान((द्विगुन) (log2_blk_bytes - 8) / 2.0, 1);
	अन्यथा
		log2_blk_height = 0;  // blk height of 1

	log2_blk_width = log2_blk_bytes - log2_bytes_per_element - log2_blk_height;

	अगर (!surf_vert) अणु
		rq_dlg_param->swath_width_ub = dml_round_to_multiple(vp_width - 1, blk256_width, 1)
				+ blk256_width;
		rq_dlg_param->req_per_swath_ub = rq_dlg_param->swath_width_ub >> log2_blk256_width;
	पूर्ण अन्यथा अणु
		rq_dlg_param->swath_width_ub = dml_round_to_multiple(vp_height - 1, blk256_height, 1)
				+ blk256_height;
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

	// -------
	// meta
	// -------
	log2_meta_req_bytes = 6; // meta request is 64b and is 8x8byte meta element

	// each 64b meta request क्रम dcn is 8x8 meta elements and
	// a meta element covers one 256b block of the the data surface.
	log2_meta_req_height = log2_blk256_height + 3; // meta req is 8x8 byte, each byte represent 1 blk256
	log2_meta_req_width = log2_meta_req_bytes + 8 - log2_bytes_per_element
			- log2_meta_req_height;
	meta_req_width = 1 << log2_meta_req_width;
	meta_req_height = 1 << log2_meta_req_height;
	log2_meta_row_height = 0;
	meta_row_width_ub = 0;

	// the dimensions of a meta row are meta_row_width x meta_row_height in elements.
	// calculate upper bound of the meta_row_width
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

	rq_dlg_param->meta_row_height = 1 << log2_meta_row_height;

	log2_meta_chunk_bytes = dml_log2(rq_sizing_param->meta_chunk_bytes);
	log2_meta_chunk_height = log2_meta_row_height;

	//full sized meta chunk width in unit of data elements
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
			* (dml_round_to_multiple(vp_height - 1, meta_blk_height, 1) + meta_blk_height)
			* bytes_per_element / 256;
	vmpg_bytes = mode_lib->soc.vmm_page_size_bytes;
	meta_pte_req_per_frame_ub = (dml_round_to_multiple(meta_surface_bytes - vmpg_bytes,
			8 * vmpg_bytes,
			1) + 8 * vmpg_bytes) / (8 * vmpg_bytes);
	meta_pte_bytes_per_frame_ub = meta_pte_req_per_frame_ub * 64; //64B mpte request
	rq_dlg_param->meta_pte_bytes_per_frame_ub = meta_pte_bytes_per_frame_ub;

	dml_prपूर्णांक("DML_DLG: %s: meta_blk_height             = %d\n", __func__, meta_blk_height);
	dml_prपूर्णांक("DML_DLG: %s: meta_blk_width              = %d\n", __func__, meta_blk_width);
	dml_prपूर्णांक("DML_DLG: %s: meta_surface_bytes          = %d\n", __func__, meta_surface_bytes);
	dml_prपूर्णांक("DML_DLG: %s: meta_pte_req_per_frame_ub   = %d\n",
			__func__,
			meta_pte_req_per_frame_ub);
	dml_prपूर्णांक("DML_DLG: %s: meta_pte_bytes_per_frame_ub = %d\n",
			__func__,
			meta_pte_bytes_per_frame_ub);

	अगर (!surf_vert)
		meta_chunk_threshold = 2 * min_meta_chunk_width - meta_req_width;
	अन्यथा
		meta_chunk_threshold = 2 * min_meta_chunk_width - meta_req_height;

	अगर (meta_row_reमुख्यder <= meta_chunk_threshold)
		rq_dlg_param->meta_chunks_per_row_ub = meta_chunk_per_row_पूर्णांक + 1;
	अन्यथा
		rq_dlg_param->meta_chunks_per_row_ub = meta_chunk_per_row_पूर्णांक + 2;

	// ------
	// dpte
	// ------
	अगर (surf_linear) अणु
		log2_vmpg_height = 0;   // one line high
	पूर्ण अन्यथा अणु
		log2_vmpg_height = (log2_vmpg_bytes - 8) / 2 + log2_blk256_height;
	पूर्ण
	log2_vmpg_width = log2_vmpg_bytes - log2_bytes_per_element - log2_vmpg_height;

	// only 3 possible shapes क्रम dpte request in dimensions of ptes: 8x1, 4x2, 2x4.
	अगर (surf_linear) अणु //one 64B PTE request वापसs 8 PTEs
		log2_dpte_req_height_ptes = 0;
		log2_dpte_req_width = log2_vmpg_width + 3;
		log2_dpte_req_height = 0;
	पूर्ण अन्यथा अगर (log2_blk_bytes == 12) अणु //4KB tile means 4kB page size
		//one 64B req gives 8x1 PTEs क्रम 4KB tile
		log2_dpte_req_height_ptes = 0;
		log2_dpte_req_width = log2_blk_width + 3;
		log2_dpte_req_height = log2_blk_height + 0;
	पूर्ण अन्यथा अगर ((log2_blk_bytes >= 16) && (log2_vmpg_bytes == 12)) अणु // tile block >= 64KB
		//two 64B reqs of 2x4 PTEs give 16 PTEs to cover 64KB
		log2_dpte_req_height_ptes = 4;
		log2_dpte_req_width = log2_blk256_width + 4; // log2_64KB_width
		log2_dpte_req_height = log2_blk256_height + 4; // log2_64KB_height
	पूर्ण अन्यथा अणु //64KB page size and must 64KB tile block
		 //one 64B req gives 8x1 PTEs क्रम 64KB tile
		log2_dpte_req_height_ptes = 0;
		log2_dpte_req_width = log2_blk_width + 3;
		log2_dpte_req_height = log2_blk_height + 0;
	पूर्ण

	// The dpte request dimensions in data elements is dpte_req_width x dpte_req_height
	// log2_vmpg_width is how much 1 pte represent, now calculating how much a 64b pte req represent
	// That depends on the pte shape (i.e. 8x1, 4x2, 2x4)
	//log2_dpte_req_height    = log2_vmpg_height + log2_dpte_req_height_ptes;
	//log2_dpte_req_width     = log2_vmpg_width + log2_dpte_req_width_ptes;
	dpte_req_height = 1 << log2_dpte_req_height;
	dpte_req_width = 1 << log2_dpte_req_width;

	// calculate pitch dpte row buffer can hold
	// round the result करोwn to a घातer of two.
	pde_buf_entries = yuv420 ? (pde_proc_buffer_size_64k_reqs >> 1) : pde_proc_buffer_size_64k_reqs;
	अगर (surf_linear) अणु
		अचिन्हित पूर्णांक dpte_row_height;

		log2_dpte_row_height_linear = dml_न्यूनमान(dml_log2(dml_min(64 * 1024 * pde_buf_entries
										/ bytes_per_element,
								dpte_buf_in_pte_reqs
										* dpte_req_width)
								/ data_pitch),
				1);

		ASSERT(log2_dpte_row_height_linear >= 3);

		अगर (log2_dpte_row_height_linear > 7)
			log2_dpte_row_height_linear = 7;

		log2_dpte_row_height = log2_dpte_row_height_linear;
		// For linear, the dpte row is pitch dependent and the pte requests wrap at the pitch boundary.
		// the dpte_row_width_ub is the upper bound of data_pitch*dpte_row_height in elements with this unique buffering.
		dpte_row_height = 1 << log2_dpte_row_height;
		dpte_row_width_ub = dml_round_to_multiple(data_pitch * dpte_row_height - 1,
				dpte_req_width,
				1) + dpte_req_width;
		rq_dlg_param->dpte_req_per_row_ub = dpte_row_width_ub / dpte_req_width;
	पूर्ण अन्यथा अणु
		// the upper bound of the dpte_row_width without dependency on viewport position follows.
		// क्रम tiled mode, row height is the same as req height and row store up to vp size upper bound
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
	पूर्ण
	अगर (log2_blk_bytes >= 16 && log2_vmpg_bytes == 12) // tile block >= 64KB
		rq_dlg_param->dpte_bytes_per_row_ub = rq_dlg_param->dpte_req_per_row_ub * 128; //2*64B dpte request
	अन्यथा
		rq_dlg_param->dpte_bytes_per_row_ub = rq_dlg_param->dpte_req_per_row_ub * 64; //64B dpte request

	rq_dlg_param->dpte_row_height = 1 << log2_dpte_row_height;

	// the dpte_group_bytes is reduced क्रम the specअगरic हाल of vertical
	// access of a tile surface that has dpte request of 8x1 ptes.
	अगर (!surf_linear & (log2_dpte_req_height_ptes == 0) & surf_vert) //reduced, in this हाल, will have page fault within a group
		rq_sizing_param->dpte_group_bytes = 512;
	अन्यथा
		//full size
		rq_sizing_param->dpte_group_bytes = 2048;

	//since pte request size is 64byte, the number of data pte requests per full sized group is as follows.
	log2_dpte_group_bytes = dml_log2(rq_sizing_param->dpte_group_bytes);
	log2_dpte_group_length = log2_dpte_group_bytes - 6; //length in 64b requests

	// full sized data pte group width in elements
	अगर (!surf_vert)
		log2_dpte_group_width = log2_dpte_group_length + log2_dpte_req_width;
	अन्यथा
		log2_dpte_group_width = log2_dpte_group_length + log2_dpte_req_height;

	//But अगर the tile block >=64KB and the page size is 4KB, then each dPTE request is 2*64B
	अगर ((log2_blk_bytes >= 16) && (log2_vmpg_bytes == 12)) // tile block >= 64KB
		log2_dpte_group_width = log2_dpte_group_width - 1;

	dpte_group_width = 1 << log2_dpte_group_width;

	// since dpte groups are only aligned to dpte_req_width and not dpte_group_width,
	// the upper bound क्रम the dpte groups per row is as follows.
	rq_dlg_param->dpte_groups_per_row_ub = dml_उच्चमान((द्विगुन) dpte_row_width_ub / dpte_group_width,
			1);
पूर्ण

अटल व्योम get_surf_rq_param(काष्ठा display_mode_lib *mode_lib,
		display_data_rq_sizing_params_st *rq_sizing_param,
		display_data_rq_dlg_params_st *rq_dlg_param,
		display_data_rq_misc_params_st *rq_misc_param,
		स्थिर display_pipe_source_params_st pipe_src_param,
		bool is_chroma)
अणु
	bool mode_422 = false;
	अचिन्हित पूर्णांक vp_width = 0;
	अचिन्हित पूर्णांक vp_height = 0;
	अचिन्हित पूर्णांक data_pitch = 0;
	अचिन्हित पूर्णांक meta_pitch = 0;
	अचिन्हित पूर्णांक ppe = mode_422 ? 2 : 1;

	// TODO check अगर ppe apply क्रम both luma and chroma in 422 हाल
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

	get_meta_and_pte_attr(mode_lib,
			rq_dlg_param,
			rq_misc_param,
			rq_sizing_param,
			vp_width,
			vp_height,
			data_pitch,
			meta_pitch,
			pipe_src_param.source_क्रमmat,
			pipe_src_param.sw_mode,
			pipe_src_param.macro_tile_size,
			pipe_src_param.source_scan,
			is_chroma);
पूर्ण

अटल व्योम dml20v2_rq_dlg_get_rq_params(काष्ठा display_mode_lib *mode_lib,
		display_rq_params_st *rq_param,
		स्थिर display_pipe_source_params_st pipe_src_param)
अणु
	// get param क्रम luma surface
	rq_param->yuv420 = pipe_src_param.source_क्रमmat == dm_420_8
			|| pipe_src_param.source_क्रमmat == dm_420_10;
	rq_param->yuv420_10bpc = pipe_src_param.source_क्रमmat == dm_420_10;

	get_surf_rq_param(mode_lib,
			&(rq_param->sizing.rq_l),
			&(rq_param->dlg.rq_l),
			&(rq_param->misc.rq_l),
			pipe_src_param,
			0);

	अगर (is_dual_plane((क्रमागत source_क्रमmat_class)(pipe_src_param.source_क्रमmat))) अणु
		// get param क्रम chroma surface
		get_surf_rq_param(mode_lib,
				&(rq_param->sizing.rq_c),
				&(rq_param->dlg.rq_c),
				&(rq_param->misc.rq_c),
				pipe_src_param,
				1);
	पूर्ण

	// calculate how to split the det buffer space between luma and chroma
	handle_det_buf_split(mode_lib, rq_param, pipe_src_param);
	prपूर्णांक__rq_params_st(mode_lib, *rq_param);
पूर्ण

व्योम dml20v2_rq_dlg_get_rq_reg(काष्ठा display_mode_lib *mode_lib,
		display_rq_regs_st *rq_regs,
		स्थिर display_pipe_params_st pipe_param)
अणु
	display_rq_params_st rq_param = अणु0पूर्ण;

	स_रखो(rq_regs, 0, माप(*rq_regs));
	dml20v2_rq_dlg_get_rq_params(mode_lib, &rq_param, pipe_param.src);
	extract_rq_regs(mode_lib, rq_regs, rq_param);

	prपूर्णांक__rq_regs_st(mode_lib, *rq_regs);
पूर्ण

// Note: currently taken in as is.
// Nice to decouple code from hw रेजिस्टर implement and extract code that are repeated क्रम luma and chroma.
अटल व्योम dml20v2_rq_dlg_get_dlg_params(काष्ठा display_mode_lib *mode_lib,
		स्थिर display_e2e_pipe_params_st *e2e_pipe_param,
		स्थिर अचिन्हित पूर्णांक num_pipes,
		स्थिर अचिन्हित पूर्णांक pipe_idx,
		display_dlg_regs_st *disp_dlg_regs,
		display_ttu_regs_st *disp_ttu_regs,
		स्थिर display_rq_dlg_params_st rq_dlg_param,
		स्थिर display_dlg_sys_params_st dlg_sys_param,
		स्थिर bool cstate_en,
		स्थिर bool pstate_en)
अणु
	स्थिर display_pipe_source_params_st *src = &e2e_pipe_param[pipe_idx].pipe.src;
	स्थिर display_pipe_dest_params_st *dst = &e2e_pipe_param[pipe_idx].pipe.dest;
	स्थिर display_output_params_st *करोut = &e2e_pipe_param[pipe_idx].करोut;
	स्थिर display_घड़ीs_and_cfg_st *clks = &e2e_pipe_param[pipe_idx].clks_cfg;
	स्थिर scaler_ratio_depth_st *scl = &e2e_pipe_param[pipe_idx].pipe.scale_ratio_depth;
	स्थिर scaler_taps_st *taps = &e2e_pipe_param[pipe_idx].pipe.scale_taps;

	// -------------------------
	// Section 1.15.2.1: OTG dependent Params
	// -------------------------
	// Timing
	अचिन्हित पूर्णांक htotal = dst->htotal;
//    अचिन्हित पूर्णांक hblank_start = dst.hblank_start; // TODO: Remove
	अचिन्हित पूर्णांक hblank_end = dst->hblank_end;
	अचिन्हित पूर्णांक vblank_start = dst->vblank_start;
	अचिन्हित पूर्णांक vblank_end = dst->vblank_end;
	अचिन्हित पूर्णांक min_vblank = mode_lib->ip.min_vblank_lines;

	द्विगुन dppclk_freq_in_mhz = clks->dppclk_mhz;
	द्विगुन dispclk_freq_in_mhz = clks->dispclk_mhz;
	द्विगुन refclk_freq_in_mhz = clks->refclk_mhz;
	द्विगुन pclk_freq_in_mhz = dst->pixel_rate_mhz;
	bool पूर्णांकerlaced = dst->पूर्णांकerlaced;

	द्विगुन ref_freq_to_pix_freq = refclk_freq_in_mhz / pclk_freq_in_mhz;

	द्विगुन min_dcfclk_mhz;
	द्विगुन t_calc_us;
	द्विगुन min_ttu_vblank;

	द्विगुन min_dst_y_ttu_vblank;
	अचिन्हित पूर्णांक dlg_vblank_start;
	bool dual_plane;
	bool mode_422;
	अचिन्हित पूर्णांक access_dir;
	अचिन्हित पूर्णांक vp_height_l;
	अचिन्हित पूर्णांक vp_width_l;
	अचिन्हित पूर्णांक vp_height_c;
	अचिन्हित पूर्णांक vp_width_c;

	// Scaling
	अचिन्हित पूर्णांक htaps_l;
	अचिन्हित पूर्णांक htaps_c;
	द्विगुन hratio_l;
	द्विगुन hratio_c;
	द्विगुन vratio_l;
	द्विगुन vratio_c;
	bool scl_enable;

	द्विगुन line_समय_in_us;
	//    द्विगुन vinit_l;
	//    द्विगुन vinit_c;
	//    द्विगुन vinit_bot_l;
	//    द्विगुन vinit_bot_c;

	//    अचिन्हित पूर्णांक swath_height_l;
	अचिन्हित पूर्णांक swath_width_ub_l;
	//    अचिन्हित पूर्णांक dpte_bytes_per_row_ub_l;
	अचिन्हित पूर्णांक dpte_groups_per_row_ub_l;
	//    अचिन्हित पूर्णांक meta_pte_bytes_per_frame_ub_l;
	//    अचिन्हित पूर्णांक meta_bytes_per_row_ub_l;

	//    अचिन्हित पूर्णांक swath_height_c;
	अचिन्हित पूर्णांक swath_width_ub_c;
	//   अचिन्हित पूर्णांक dpte_bytes_per_row_ub_c;
	अचिन्हित पूर्णांक dpte_groups_per_row_ub_c;

	अचिन्हित पूर्णांक meta_chunks_per_row_ub_l;
	अचिन्हित पूर्णांक meta_chunks_per_row_ub_c;
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
	द्विगुन dst_y_prefetch;
	द्विगुन dst_y_per_vm_vblank;
	द्विगुन dst_y_per_row_vblank;
	द्विगुन dst_y_per_vm_flip;
	द्विगुन dst_y_per_row_flip;
	द्विगुन min_dst_y_per_vm_vblank;
	द्विगुन min_dst_y_per_row_vblank;
	द्विगुन lsw;
	द्विगुन vratio_pre_l;
	द्विगुन vratio_pre_c;
	अचिन्हित पूर्णांक req_per_swath_ub_l;
	अचिन्हित पूर्णांक req_per_swath_ub_c;
	अचिन्हित पूर्णांक meta_row_height_l;
	अचिन्हित पूर्णांक meta_row_height_c;
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

	अचिन्हित पूर्णांक full_recout_width;
	द्विगुन refcyc_per_req_delivery_pre_cur0;
	द्विगुन refcyc_per_req_delivery_cur0;
	द्विगुन refcyc_per_req_delivery_pre_cur1;
	द्विगुन refcyc_per_req_delivery_cur1;

	स_रखो(disp_dlg_regs, 0, माप(*disp_dlg_regs));
	स_रखो(disp_ttu_regs, 0, माप(*disp_ttu_regs));

	dml_prपूर्णांक("DML_DLG: %s:  cstate_en = %d\n", __func__, cstate_en);
	dml_prपूर्णांक("DML_DLG: %s:  pstate_en = %d\n", __func__, pstate_en);

	dml_prपूर्णांक("DML_DLG: %s: dppclk_freq_in_mhz     = %3.2f\n", __func__, dppclk_freq_in_mhz);
	dml_prपूर्णांक("DML_DLG: %s: dispclk_freq_in_mhz    = %3.2f\n", __func__, dispclk_freq_in_mhz);
	dml_prपूर्णांक("DML_DLG: %s: refclk_freq_in_mhz     = %3.2f\n", __func__, refclk_freq_in_mhz);
	dml_prपूर्णांक("DML_DLG: %s: pclk_freq_in_mhz       = %3.2f\n", __func__, pclk_freq_in_mhz);
	dml_prपूर्णांक("DML_DLG: %s: interlaced             = %d\n", __func__, पूर्णांकerlaced);
	ASSERT(ref_freq_to_pix_freq < 4.0);

	disp_dlg_regs->ref_freq_to_pix_freq =
			(अचिन्हित पूर्णांक) (ref_freq_to_pix_freq * dml_घात(2, 19));
	disp_dlg_regs->refcyc_per_htotal = (अचिन्हित पूर्णांक) (ref_freq_to_pix_freq * (द्विगुन) htotal
			* dml_घात(2, 8));
	disp_dlg_regs->dlg_vblank_end = पूर्णांकerlaced ? (vblank_end / 2) : vblank_end; // 15 bits
	disp_dlg_regs->refcyc_h_blank_end = (अचिन्हित पूर्णांक) ((द्विगुन) hblank_end
			* (द्विगुन) ref_freq_to_pix_freq);
	ASSERT(disp_dlg_regs->refcyc_h_blank_end < (अचिन्हित पूर्णांक) dml_घात(2, 13));

	min_dcfclk_mhz = dlg_sys_param.deepsleep_dcfclk_mhz;
	t_calc_us = get_tcalc(mode_lib, e2e_pipe_param, num_pipes);
	min_ttu_vblank = get_min_ttu_vblank(mode_lib, e2e_pipe_param, num_pipes, pipe_idx);

	min_dst_y_ttu_vblank = min_ttu_vblank * pclk_freq_in_mhz / (द्विगुन) htotal;
	dlg_vblank_start = पूर्णांकerlaced ? (vblank_start / 2) : vblank_start;

	disp_dlg_regs->min_dst_y_next_start = (अचिन्हित पूर्णांक) (((द्विगुन) dlg_vblank_start
			+ min_dst_y_ttu_vblank) * dml_घात(2, 2));
	ASSERT(disp_dlg_regs->min_dst_y_next_start < (अचिन्हित पूर्णांक) dml_घात(2, 18));

	dml_prपूर्णांक("DML_DLG: %s: min_dcfclk_mhz                         = %3.2f\n",
			__func__,
			min_dcfclk_mhz);
	dml_prपूर्णांक("DML_DLG: %s: min_ttu_vblank                         = %3.2f\n",
			__func__,
			min_ttu_vblank);
	dml_prपूर्णांक("DML_DLG: %s: min_dst_y_ttu_vblank                   = %3.2f\n",
			__func__,
			min_dst_y_ttu_vblank);
	dml_prपूर्णांक("DML_DLG: %s: t_calc_us                              = %3.2f\n",
			__func__,
			t_calc_us);
	dml_prपूर्णांक("DML_DLG: %s: disp_dlg_regs->min_dst_y_next_start    = 0x%0x\n",
			__func__,
			disp_dlg_regs->min_dst_y_next_start);
	dml_prपूर्णांक("DML_DLG: %s: ref_freq_to_pix_freq                   = %3.2f\n",
			__func__,
			ref_freq_to_pix_freq);

	// -------------------------
	// Section 1.15.2.2: Prefetch, Active and TTU
	// -------------------------
	// Prefetch Calc
	// Source
//             dcc_en              = src.dcc;
	dual_plane = is_dual_plane((क्रमागत source_क्रमmat_class)(src->source_क्रमmat));
	mode_422 = false; // TODO
	access_dir = (src->source_scan == dm_vert); // vp access direction: horizontal or vertical accessed
//      bytes_per_element_l = get_bytes_per_element(source_क्रमmat_class(src.source_क्रमmat), 0);
//      bytes_per_element_c = get_bytes_per_element(source_क्रमmat_class(src.source_क्रमmat), 1);
	vp_height_l = src->viewport_height;
	vp_width_l = src->viewport_width;
	vp_height_c = src->viewport_height_c;
	vp_width_c = src->viewport_width_c;

	// Scaling
	htaps_l = taps->htaps;
	htaps_c = taps->htaps_c;
	hratio_l = scl->hscl_ratio;
	hratio_c = scl->hscl_ratio_c;
	vratio_l = scl->vscl_ratio;
	vratio_c = scl->vscl_ratio_c;
	scl_enable = scl->scl_enable;

	line_समय_in_us = (htotal / pclk_freq_in_mhz);
//     vinit_l         = scl.vinit;
//     vinit_c         = scl.vinit_c;
//     vinit_bot_l     = scl.vinit_bot;
//     vinit_bot_c     = scl.vinit_bot_c;

//    अचिन्हित पूर्णांक swath_height_l                 = rq_dlg_param.rq_l.swath_height;
	swath_width_ub_l = rq_dlg_param.rq_l.swath_width_ub;
//    अचिन्हित पूर्णांक dpte_bytes_per_row_ub_l        = rq_dlg_param.rq_l.dpte_bytes_per_row_ub;
	dpte_groups_per_row_ub_l = rq_dlg_param.rq_l.dpte_groups_per_row_ub;
//    अचिन्हित पूर्णांक meta_pte_bytes_per_frame_ub_l  = rq_dlg_param.rq_l.meta_pte_bytes_per_frame_ub;
//    अचिन्हित पूर्णांक meta_bytes_per_row_ub_l        = rq_dlg_param.rq_l.meta_bytes_per_row_ub;

//    अचिन्हित पूर्णांक swath_height_c                 = rq_dlg_param.rq_c.swath_height;
	swath_width_ub_c = rq_dlg_param.rq_c.swath_width_ub;
	//   dpte_bytes_per_row_ub_c        = rq_dlg_param.rq_c.dpte_bytes_per_row_ub;
	dpte_groups_per_row_ub_c = rq_dlg_param.rq_c.dpte_groups_per_row_ub;

	meta_chunks_per_row_ub_l = rq_dlg_param.rq_l.meta_chunks_per_row_ub;
	meta_chunks_per_row_ub_c = rq_dlg_param.rq_c.meta_chunks_per_row_ub;
	vupdate_offset = dst->vupdate_offset;
	vupdate_width = dst->vupdate_width;
	vपढ़ोy_offset = dst->vपढ़ोy_offset;

	dppclk_delay_subtotal = mode_lib->ip.dppclk_delay_subtotal;
	dispclk_delay_subtotal = mode_lib->ip.dispclk_delay_subtotal;

	अगर (scl_enable)
		dppclk_delay_subtotal += mode_lib->ip.dppclk_delay_scl;
	अन्यथा
		dppclk_delay_subtotal += mode_lib->ip.dppclk_delay_scl_lb_only;

	dppclk_delay_subtotal += mode_lib->ip.dppclk_delay_cnvc_क्रमmatter
			+ src->num_cursors * mode_lib->ip.dppclk_delay_cnvc_cursor;

	अगर (करोut->dsc_enable) अणु
		द्विगुन dsc_delay = get_dsc_delay(mode_lib, e2e_pipe_param, num_pipes, pipe_idx);

		dispclk_delay_subtotal += dsc_delay;
	पूर्ण

	pixel_rate_delay_subtotal = dppclk_delay_subtotal * pclk_freq_in_mhz / dppclk_freq_in_mhz
			+ dispclk_delay_subtotal * pclk_freq_in_mhz / dispclk_freq_in_mhz;

	vstartup_start = dst->vstartup_start;
	अगर (पूर्णांकerlaced) अणु
		अगर (vstartup_start / 2.0
				- (द्विगुन) (vपढ़ोy_offset + vupdate_width + vupdate_offset) / htotal
				<= vblank_end / 2.0)
			disp_dlg_regs->vपढ़ोy_after_vcount0 = 1;
		अन्यथा
			disp_dlg_regs->vपढ़ोy_after_vcount0 = 0;
	पूर्ण अन्यथा अणु
		अगर (vstartup_start
				- (द्विगुन) (vपढ़ोy_offset + vupdate_width + vupdate_offset) / htotal
				<= vblank_end)
			disp_dlg_regs->vपढ़ोy_after_vcount0 = 1;
		अन्यथा
			disp_dlg_regs->vपढ़ोy_after_vcount0 = 0;
	पूर्ण

	// TODO: Where is this coming from?
	अगर (पूर्णांकerlaced)
		vstartup_start = vstartup_start / 2;

	// TODO: What अगर this min_vblank करोesn't match the value in the dml_config_settings.cpp?
	अगर (vstartup_start >= min_vblank) अणु
		dml_prपूर्णांक("WARNING: DML_DLG: %s: vblank_start=%d vblank_end=%d\n",
				__func__,
				vblank_start,
				vblank_end);
		dml_prपूर्णांक("WARNING: DML_DLG: %s: vstartup_start=%d should be less than min_vblank=%d\n",
				__func__,
				vstartup_start,
				min_vblank);
		min_vblank = vstartup_start + 1;
		dml_prपूर्णांक("WARNING: DML_DLG: %s: vstartup_start=%d should be less than min_vblank=%d\n",
				__func__,
				vstartup_start,
				min_vblank);
	पूर्ण

	dst_x_after_scaler = get_dst_x_after_scaler(mode_lib, e2e_pipe_param, num_pipes, pipe_idx);
	dst_y_after_scaler = get_dst_y_after_scaler(mode_lib, e2e_pipe_param, num_pipes, pipe_idx);

	dml_prपूर्णांक("DML_DLG: %s: htotal                                 = %d\n", __func__, htotal);
	dml_prपूर्णांक("DML_DLG: %s: pixel_rate_delay_subtotal              = %d\n",
			__func__,
			pixel_rate_delay_subtotal);
	dml_prपूर्णांक("DML_DLG: %s: dst_x_after_scaler                     = %d\n",
			__func__,
			dst_x_after_scaler);
	dml_prपूर्णांक("DML_DLG: %s: dst_y_after_scaler                     = %d\n",
			__func__,
			dst_y_after_scaler);

	// Lरुको
	line_रुको = mode_lib->soc.urgent_latency_us;
	अगर (cstate_en)
		line_रुको = dml_max(mode_lib->soc.sr_enter_plus_निकास_समय_us, line_रुको);
	अगर (pstate_en)
		line_रुको = dml_max(mode_lib->soc.dram_घड़ी_change_latency_us
						+ mode_lib->soc.urgent_latency_us,
				line_रुको);
	line_रुको = line_रुको / line_समय_in_us;

	dst_y_prefetch = get_dst_y_prefetch(mode_lib, e2e_pipe_param, num_pipes, pipe_idx);
	dml_prपूर्णांक("DML_DLG: %s: dst_y_prefetch (after rnd) = %3.2f\n", __func__, dst_y_prefetch);

	dst_y_per_vm_vblank = get_dst_y_per_vm_vblank(mode_lib,
			e2e_pipe_param,
			num_pipes,
			pipe_idx);
	dst_y_per_row_vblank = get_dst_y_per_row_vblank(mode_lib,
			e2e_pipe_param,
			num_pipes,
			pipe_idx);
	dst_y_per_vm_flip = get_dst_y_per_vm_flip(mode_lib, e2e_pipe_param, num_pipes, pipe_idx);
	dst_y_per_row_flip = get_dst_y_per_row_flip(mode_lib, e2e_pipe_param, num_pipes, pipe_idx);

	min_dst_y_per_vm_vblank = 8.0;
	min_dst_y_per_row_vblank = 16.0;

	// magic!
	अगर (htotal <= 75) अणु
		min_vblank = 300;
		min_dst_y_per_vm_vblank = 100.0;
		min_dst_y_per_row_vblank = 100.0;
	पूर्ण

	dml_prपूर्णांक("DML_DLG: %s: dst_y_per_vm_vblank    = %3.2f\n", __func__, dst_y_per_vm_vblank);
	dml_prपूर्णांक("DML_DLG: %s: dst_y_per_row_vblank   = %3.2f\n", __func__, dst_y_per_row_vblank);

	ASSERT(dst_y_per_vm_vblank < min_dst_y_per_vm_vblank);
	ASSERT(dst_y_per_row_vblank < min_dst_y_per_row_vblank);

	ASSERT(dst_y_prefetch > (dst_y_per_vm_vblank + dst_y_per_row_vblank));
	lsw = dst_y_prefetch - (dst_y_per_vm_vblank + dst_y_per_row_vblank);

	dml_prपूर्णांक("DML_DLG: %s: lsw = %3.2f\n", __func__, lsw);

	vratio_pre_l = get_vratio_prefetch_l(mode_lib, e2e_pipe_param, num_pipes, pipe_idx);
	vratio_pre_c = get_vratio_prefetch_c(mode_lib, e2e_pipe_param, num_pipes, pipe_idx);

	dml_prपूर्णांक("DML_DLG: %s: vratio_pre_l=%3.2f\n", __func__, vratio_pre_l);
	dml_prपूर्णांक("DML_DLG: %s: vratio_pre_c=%3.2f\n", __func__, vratio_pre_c);

	// Active
	req_per_swath_ub_l = rq_dlg_param.rq_l.req_per_swath_ub;
	req_per_swath_ub_c = rq_dlg_param.rq_c.req_per_swath_ub;
	meta_row_height_l = rq_dlg_param.rq_l.meta_row_height;
	meta_row_height_c = rq_dlg_param.rq_c.meta_row_height;
	swath_width_pixels_ub_l = 0;
	swath_width_pixels_ub_c = 0;
	scaler_rec_in_width_l = 0;
	scaler_rec_in_width_c = 0;
	dpte_row_height_l = rq_dlg_param.rq_l.dpte_row_height;
	dpte_row_height_c = rq_dlg_param.rq_c.dpte_row_height;

	अगर (mode_422) अणु
		swath_width_pixels_ub_l = swath_width_ub_l * 2;  // *2 क्रम 2 pixel per element
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
		अगर ((hratio_l * 2.0) > 4.0)
			min_hratio_fact_l = 4.0;
		अन्यथा
			min_hratio_fact_l = hratio_l * 2.0;
	पूर्ण अन्यथा अणु
		अगर (hratio_l > 4.0)
			min_hratio_fact_l = 4.0;
		अन्यथा
			min_hratio_fact_l = hratio_l;
	पूर्ण

	hscale_pixel_rate_l = min_hratio_fact_l * dppclk_freq_in_mhz;

	अगर (htaps_c <= 1)
		min_hratio_fact_c = 2.0;
	अन्यथा अगर (htaps_c <= 6) अणु
		अगर ((hratio_c * 2.0) > 4.0)
			min_hratio_fact_c = 4.0;
		अन्यथा
			min_hratio_fact_c = hratio_c * 2.0;
	पूर्ण अन्यथा अणु
		अगर (hratio_c > 4.0)
			min_hratio_fact_c = 4.0;
		अन्यथा
			min_hratio_fact_c = hratio_c;
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

	full_recout_width = 0;
	// In ODM
	अगर (src->is_hsplit) अणु
		// This "hack"  is only allowed (and valid) क्रम MPC combine. In ODM
		// combine, you MUST specअगरy the full_recout_width...according to Oswin
		अगर (dst->full_recout_width == 0 && !dst->odm_combine) अणु
			dml_prपूर्णांक("DML_DLG: %s: Warning: full_recout_width not set in hsplit mode\n",
					__func__);
			full_recout_width = dst->recout_width * 2; // assume half split क्रम dcn1
		पूर्ण अन्यथा
			full_recout_width = dst->full_recout_width;
	पूर्ण अन्यथा
		full_recout_width = dst->recout_width;

	// As of DCN2, mpc_combine and odm_combine are mutually exclusive
	refcyc_per_line_delivery_pre_l = get_refcyc_per_delivery(mode_lib,
			refclk_freq_in_mhz,
			pclk_freq_in_mhz,
			dst->odm_combine,
			full_recout_width,
			dst->hactive,
			vratio_pre_l,
			hscale_pixel_rate_l,
			swath_width_pixels_ub_l,
			1); // per line

	refcyc_per_line_delivery_l = get_refcyc_per_delivery(mode_lib,
			refclk_freq_in_mhz,
			pclk_freq_in_mhz,
			dst->odm_combine,
			full_recout_width,
			dst->hactive,
			vratio_l,
			hscale_pixel_rate_l,
			swath_width_pixels_ub_l,
			1); // per line

	dml_prपूर्णांक("DML_DLG: %s: full_recout_width              = %d\n",
			__func__,
			full_recout_width);
	dml_prपूर्णांक("DML_DLG: %s: hscale_pixel_rate_l            = %3.2f\n",
			__func__,
			hscale_pixel_rate_l);
	dml_prपूर्णांक("DML_DLG: %s: refcyc_per_line_delivery_pre_l = %3.2f\n",
			__func__,
			refcyc_per_line_delivery_pre_l);
	dml_prपूर्णांक("DML_DLG: %s: refcyc_per_line_delivery_l     = %3.2f\n",
			__func__,
			refcyc_per_line_delivery_l);

	अगर (dual_plane) अणु
		refcyc_per_line_delivery_pre_c = get_refcyc_per_delivery(mode_lib,
				refclk_freq_in_mhz,
				pclk_freq_in_mhz,
				dst->odm_combine,
				full_recout_width,
				dst->hactive,
				vratio_pre_c,
				hscale_pixel_rate_c,
				swath_width_pixels_ub_c,
				1); // per line

		refcyc_per_line_delivery_c = get_refcyc_per_delivery(mode_lib,
				refclk_freq_in_mhz,
				pclk_freq_in_mhz,
				dst->odm_combine,
				full_recout_width,
				dst->hactive,
				vratio_c,
				hscale_pixel_rate_c,
				swath_width_pixels_ub_c,
				1);  // per line

		dml_prपूर्णांक("DML_DLG: %s: refcyc_per_line_delivery_pre_c = %3.2f\n",
				__func__,
				refcyc_per_line_delivery_pre_c);
		dml_prपूर्णांक("DML_DLG: %s: refcyc_per_line_delivery_c     = %3.2f\n",
				__func__,
				refcyc_per_line_delivery_c);
	पूर्ण

	// TTU - Luma / Chroma
	अगर (access_dir) अणु  // vertical access
		scaler_rec_in_width_l = vp_height_l;
		scaler_rec_in_width_c = vp_height_c;
	पूर्ण अन्यथा अणु
		scaler_rec_in_width_l = vp_width_l;
		scaler_rec_in_width_c = vp_width_c;
	पूर्ण

	refcyc_per_req_delivery_pre_l = get_refcyc_per_delivery(mode_lib,
			refclk_freq_in_mhz,
			pclk_freq_in_mhz,
			dst->odm_combine,
			full_recout_width,
			dst->hactive,
			vratio_pre_l,
			hscale_pixel_rate_l,
			scaler_rec_in_width_l,
			req_per_swath_ub_l);  // per req
	refcyc_per_req_delivery_l = get_refcyc_per_delivery(mode_lib,
			refclk_freq_in_mhz,
			pclk_freq_in_mhz,
			dst->odm_combine,
			full_recout_width,
			dst->hactive,
			vratio_l,
			hscale_pixel_rate_l,
			scaler_rec_in_width_l,
			req_per_swath_ub_l);  // per req

	dml_prपूर्णांक("DML_DLG: %s: refcyc_per_req_delivery_pre_l = %3.2f\n",
			__func__,
			refcyc_per_req_delivery_pre_l);
	dml_prपूर्णांक("DML_DLG: %s: refcyc_per_req_delivery_l     = %3.2f\n",
			__func__,
			refcyc_per_req_delivery_l);

	ASSERT(refcyc_per_req_delivery_pre_l < dml_घात(2, 13));
	ASSERT(refcyc_per_req_delivery_l < dml_घात(2, 13));

	अगर (dual_plane) अणु
		refcyc_per_req_delivery_pre_c = get_refcyc_per_delivery(mode_lib,
				refclk_freq_in_mhz,
				pclk_freq_in_mhz,
				dst->odm_combine,
				full_recout_width,
				dst->hactive,
				vratio_pre_c,
				hscale_pixel_rate_c,
				scaler_rec_in_width_c,
				req_per_swath_ub_c);  // per req
		refcyc_per_req_delivery_c = get_refcyc_per_delivery(mode_lib,
				refclk_freq_in_mhz,
				pclk_freq_in_mhz,
				dst->odm_combine,
				full_recout_width,
				dst->hactive,
				vratio_c,
				hscale_pixel_rate_c,
				scaler_rec_in_width_c,
				req_per_swath_ub_c);  // per req

		dml_prपूर्णांक("DML_DLG: %s: refcyc_per_req_delivery_pre_c = %3.2f\n",
				__func__,
				refcyc_per_req_delivery_pre_c);
		dml_prपूर्णांक("DML_DLG: %s: refcyc_per_req_delivery_c     = %3.2f\n",
				__func__,
				refcyc_per_req_delivery_c);

		ASSERT(refcyc_per_req_delivery_pre_c < dml_घात(2, 13));
		ASSERT(refcyc_per_req_delivery_c < dml_घात(2, 13));
	पूर्ण

	// TTU - Cursor
	refcyc_per_req_delivery_pre_cur0 = 0.0;
	refcyc_per_req_delivery_cur0 = 0.0;
	अगर (src->num_cursors > 0) अणु
		calculate_ttu_cursor(mode_lib,
				&refcyc_per_req_delivery_pre_cur0,
				&refcyc_per_req_delivery_cur0,
				refclk_freq_in_mhz,
				ref_freq_to_pix_freq,
				hscale_pixel_rate_l,
				scl->hscl_ratio,
				vratio_pre_l,
				vratio_l,
				src->cur0_src_width,
				(क्रमागत cursor_bpp)(src->cur0_bpp));
	पूर्ण

	refcyc_per_req_delivery_pre_cur1 = 0.0;
	refcyc_per_req_delivery_cur1 = 0.0;
	अगर (src->num_cursors > 1) अणु
		calculate_ttu_cursor(mode_lib,
				&refcyc_per_req_delivery_pre_cur1,
				&refcyc_per_req_delivery_cur1,
				refclk_freq_in_mhz,
				ref_freq_to_pix_freq,
				hscale_pixel_rate_l,
				scl->hscl_ratio,
				vratio_pre_l,
				vratio_l,
				src->cur1_src_width,
				(क्रमागत cursor_bpp)(src->cur1_bpp));
	पूर्ण

	// TTU - Misc
	// all hard-coded

	// Assignment to रेजिस्टर काष्ठाures
	disp_dlg_regs->dst_y_after_scaler = dst_y_after_scaler; // in terms of line
	disp_dlg_regs->refcyc_x_after_scaler = dst_x_after_scaler * ref_freq_to_pix_freq; // in terms of refclk
	ASSERT(disp_dlg_regs->refcyc_x_after_scaler < (अचिन्हित पूर्णांक) dml_घात(2, 13));
	disp_dlg_regs->dst_y_prefetch = (अचिन्हित पूर्णांक) (dst_y_prefetch * dml_घात(2, 2));
	disp_dlg_regs->dst_y_per_vm_vblank = (अचिन्हित पूर्णांक) (dst_y_per_vm_vblank * dml_घात(2, 2));
	disp_dlg_regs->dst_y_per_row_vblank = (अचिन्हित पूर्णांक) (dst_y_per_row_vblank * dml_घात(2, 2));
	disp_dlg_regs->dst_y_per_vm_flip = (अचिन्हित पूर्णांक) (dst_y_per_vm_flip * dml_घात(2, 2));
	disp_dlg_regs->dst_y_per_row_flip = (अचिन्हित पूर्णांक) (dst_y_per_row_flip * dml_घात(2, 2));

	disp_dlg_regs->vratio_prefetch = (अचिन्हित पूर्णांक) (vratio_pre_l * dml_घात(2, 19));
	disp_dlg_regs->vratio_prefetch_c = (अचिन्हित पूर्णांक) (vratio_pre_c * dml_घात(2, 19));

	disp_dlg_regs->refcyc_per_pte_group_vblank_l =
			(अचिन्हित पूर्णांक) (dst_y_per_row_vblank * (द्विगुन) htotal
					* ref_freq_to_pix_freq / (द्विगुन) dpte_groups_per_row_ub_l);
	ASSERT(disp_dlg_regs->refcyc_per_pte_group_vblank_l < (अचिन्हित पूर्णांक) dml_घात(2, 13));

	अगर (dual_plane) अणु
		disp_dlg_regs->refcyc_per_pte_group_vblank_c = (अचिन्हित पूर्णांक) (dst_y_per_row_vblank
				* (द्विगुन) htotal * ref_freq_to_pix_freq
				/ (द्विगुन) dpte_groups_per_row_ub_c);
		ASSERT(disp_dlg_regs->refcyc_per_pte_group_vblank_c
						< (अचिन्हित पूर्णांक) dml_घात(2, 13));
	पूर्ण

	disp_dlg_regs->refcyc_per_meta_chunk_vblank_l =
			(अचिन्हित पूर्णांक) (dst_y_per_row_vblank * (द्विगुन) htotal
					* ref_freq_to_pix_freq / (द्विगुन) meta_chunks_per_row_ub_l);
	ASSERT(disp_dlg_regs->refcyc_per_meta_chunk_vblank_l < (अचिन्हित पूर्णांक) dml_घात(2, 13));

	disp_dlg_regs->refcyc_per_meta_chunk_vblank_c =
			disp_dlg_regs->refcyc_per_meta_chunk_vblank_l; // dcc क्रम 4:2:0 is not supported in dcn1.0.  asचिन्हित to be the same as _l क्रम now

	disp_dlg_regs->refcyc_per_pte_group_flip_l = (अचिन्हित पूर्णांक) (dst_y_per_row_flip * htotal
			* ref_freq_to_pix_freq) / dpte_groups_per_row_ub_l;
	disp_dlg_regs->refcyc_per_meta_chunk_flip_l = (अचिन्हित पूर्णांक) (dst_y_per_row_flip * htotal
			* ref_freq_to_pix_freq) / meta_chunks_per_row_ub_l;

	अगर (dual_plane) अणु
		disp_dlg_regs->refcyc_per_pte_group_flip_c = (अचिन्हित पूर्णांक) (dst_y_per_row_flip
				* htotal * ref_freq_to_pix_freq) / dpte_groups_per_row_ub_c;
		disp_dlg_regs->refcyc_per_meta_chunk_flip_c = (अचिन्हित पूर्णांक) (dst_y_per_row_flip
				* htotal * ref_freq_to_pix_freq) / meta_chunks_per_row_ub_c;
	पूर्ण

	disp_dlg_regs->dst_y_per_pte_row_nom_l = (अचिन्हित पूर्णांक) ((द्विगुन) dpte_row_height_l
			/ (द्विगुन) vratio_l * dml_घात(2, 2));
	ASSERT(disp_dlg_regs->dst_y_per_pte_row_nom_l < (अचिन्हित पूर्णांक) dml_घात(2, 17));

	अगर (dual_plane) अणु
		disp_dlg_regs->dst_y_per_pte_row_nom_c = (अचिन्हित पूर्णांक) ((द्विगुन) dpte_row_height_c
				/ (द्विगुन) vratio_c * dml_घात(2, 2));
		अगर (disp_dlg_regs->dst_y_per_pte_row_nom_c >= (अचिन्हित पूर्णांक) dml_घात(2, 17)) अणु
			dml_prपूर्णांक("DML_DLG: %s: Warning dst_y_per_pte_row_nom_c %u larger than supported by register format U15.2 %u\n",
					__func__,
					disp_dlg_regs->dst_y_per_pte_row_nom_c,
					(अचिन्हित पूर्णांक) dml_घात(2, 17) - 1);
		पूर्ण
	पूर्ण

	disp_dlg_regs->dst_y_per_meta_row_nom_l = (अचिन्हित पूर्णांक) ((द्विगुन) meta_row_height_l
			/ (द्विगुन) vratio_l * dml_घात(2, 2));
	ASSERT(disp_dlg_regs->dst_y_per_meta_row_nom_l < (अचिन्हित पूर्णांक) dml_घात(2, 17));

	disp_dlg_regs->dst_y_per_meta_row_nom_c = disp_dlg_regs->dst_y_per_meta_row_nom_l; // TODO: dcc क्रम 4:2:0 is not supported in dcn1.0.  asचिन्हित to be the same as _l क्रम now

	disp_dlg_regs->refcyc_per_pte_group_nom_l = (अचिन्हित पूर्णांक) ((द्विगुन) dpte_row_height_l
			/ (द्विगुन) vratio_l * (द्विगुन) htotal * ref_freq_to_pix_freq
			/ (द्विगुन) dpte_groups_per_row_ub_l);
	अगर (disp_dlg_regs->refcyc_per_pte_group_nom_l >= (अचिन्हित पूर्णांक) dml_घात(2, 23))
		disp_dlg_regs->refcyc_per_pte_group_nom_l = dml_घात(2, 23) - 1;
	disp_dlg_regs->refcyc_per_meta_chunk_nom_l = (अचिन्हित पूर्णांक) ((द्विगुन) meta_row_height_l
			/ (द्विगुन) vratio_l * (द्विगुन) htotal * ref_freq_to_pix_freq
			/ (द्विगुन) meta_chunks_per_row_ub_l);
	अगर (disp_dlg_regs->refcyc_per_meta_chunk_nom_l >= (अचिन्हित पूर्णांक) dml_घात(2, 23))
		disp_dlg_regs->refcyc_per_meta_chunk_nom_l = dml_घात(2, 23) - 1;

	अगर (dual_plane) अणु
		disp_dlg_regs->refcyc_per_pte_group_nom_c =
				(अचिन्हित पूर्णांक) ((द्विगुन) dpte_row_height_c / (द्विगुन) vratio_c
						* (द्विगुन) htotal * ref_freq_to_pix_freq
						/ (द्विगुन) dpte_groups_per_row_ub_c);
		अगर (disp_dlg_regs->refcyc_per_pte_group_nom_c >= (अचिन्हित पूर्णांक) dml_घात(2, 23))
			disp_dlg_regs->refcyc_per_pte_group_nom_c = dml_घात(2, 23) - 1;

		// TODO: Is this the right calculation? Does htotal need to be halved?
		disp_dlg_regs->refcyc_per_meta_chunk_nom_c =
				(अचिन्हित पूर्णांक) ((द्विगुन) meta_row_height_c / (द्विगुन) vratio_c
						* (द्विगुन) htotal * ref_freq_to_pix_freq
						/ (द्विगुन) meta_chunks_per_row_ub_c);
		अगर (disp_dlg_regs->refcyc_per_meta_chunk_nom_c >= (अचिन्हित पूर्णांक) dml_घात(2, 23))
			disp_dlg_regs->refcyc_per_meta_chunk_nom_c = dml_घात(2, 23) - 1;
	पूर्ण

	disp_dlg_regs->refcyc_per_line_delivery_pre_l = (अचिन्हित पूर्णांक) dml_न्यूनमान(refcyc_per_line_delivery_pre_l,
			1);
	disp_dlg_regs->refcyc_per_line_delivery_l = (अचिन्हित पूर्णांक) dml_न्यूनमान(refcyc_per_line_delivery_l,
			1);
	ASSERT(disp_dlg_regs->refcyc_per_line_delivery_pre_l < (अचिन्हित पूर्णांक) dml_घात(2, 13));
	ASSERT(disp_dlg_regs->refcyc_per_line_delivery_l < (अचिन्हित पूर्णांक) dml_घात(2, 13));

	disp_dlg_regs->refcyc_per_line_delivery_pre_c = (अचिन्हित पूर्णांक) dml_न्यूनमान(refcyc_per_line_delivery_pre_c,
			1);
	disp_dlg_regs->refcyc_per_line_delivery_c = (अचिन्हित पूर्णांक) dml_न्यूनमान(refcyc_per_line_delivery_c,
			1);
	ASSERT(disp_dlg_regs->refcyc_per_line_delivery_pre_c < (अचिन्हित पूर्णांक) dml_घात(2, 13));
	ASSERT(disp_dlg_regs->refcyc_per_line_delivery_c < (अचिन्हित पूर्णांक) dml_घात(2, 13));

	disp_dlg_regs->chunk_hdl_adjust_cur0 = 3;
	disp_dlg_regs->dst_y_offset_cur0 = 0;
	disp_dlg_regs->chunk_hdl_adjust_cur1 = 3;
	disp_dlg_regs->dst_y_offset_cur1 = 0;

	disp_dlg_regs->dst_y_delta_drq_limit = 0x7fff; // off

	disp_ttu_regs->refcyc_per_req_delivery_pre_l = (अचिन्हित पूर्णांक) (refcyc_per_req_delivery_pre_l
			* dml_घात(2, 10));
	disp_ttu_regs->refcyc_per_req_delivery_l = (अचिन्हित पूर्णांक) (refcyc_per_req_delivery_l
			* dml_घात(2, 10));
	disp_ttu_regs->refcyc_per_req_delivery_pre_c = (अचिन्हित पूर्णांक) (refcyc_per_req_delivery_pre_c
			* dml_घात(2, 10));
	disp_ttu_regs->refcyc_per_req_delivery_c = (अचिन्हित पूर्णांक) (refcyc_per_req_delivery_c
			* dml_घात(2, 10));
	disp_ttu_regs->refcyc_per_req_delivery_pre_cur0 =
			(अचिन्हित पूर्णांक) (refcyc_per_req_delivery_pre_cur0 * dml_घात(2, 10));
	disp_ttu_regs->refcyc_per_req_delivery_cur0 = (अचिन्हित पूर्णांक) (refcyc_per_req_delivery_cur0
			* dml_घात(2, 10));
	disp_ttu_regs->refcyc_per_req_delivery_pre_cur1 =
			(अचिन्हित पूर्णांक) (refcyc_per_req_delivery_pre_cur1 * dml_घात(2, 10));
	disp_ttu_regs->refcyc_per_req_delivery_cur1 = (अचिन्हित पूर्णांक) (refcyc_per_req_delivery_cur1
			* dml_घात(2, 10));
	disp_ttu_regs->qos_level_low_wm = 0;
	ASSERT(disp_ttu_regs->qos_level_low_wm < dml_घात(2, 14));
	disp_ttu_regs->qos_level_high_wm = (अचिन्हित पूर्णांक) (4.0 * (द्विगुन) htotal
			* ref_freq_to_pix_freq);
	/*ASSERT(disp_ttu_regs->qos_level_high_wm < dml_घात(2, 14));*/

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

व्योम dml20v2_rq_dlg_get_dlg_reg(काष्ठा display_mode_lib *mode_lib,
		display_dlg_regs_st *dlg_regs,
		display_ttu_regs_st *ttu_regs,
		display_e2e_pipe_params_st *e2e_pipe_param,
		स्थिर अचिन्हित पूर्णांक num_pipes,
		स्थिर अचिन्हित पूर्णांक pipe_idx,
		स्थिर bool cstate_en,
		स्थिर bool pstate_en,
		स्थिर bool vm_en,
		स्थिर bool ignore_viewport_pos,
		स्थिर bool immediate_flip_support)
अणु
	display_rq_params_st rq_param = अणु0पूर्ण;
	display_dlg_sys_params_st dlg_sys_param = अणु0पूर्ण;

	// Get watermark and Tex.
	dlg_sys_param.t_urg_wm_us = get_wm_urgent(mode_lib, e2e_pipe_param, num_pipes);
	dlg_sys_param.deepsleep_dcfclk_mhz = get_clk_dcf_deepsleep(mode_lib,
			e2e_pipe_param,
			num_pipes);
	dlg_sys_param.t_extra_us = get_urgent_extra_latency(mode_lib, e2e_pipe_param, num_pipes);
	dlg_sys_param.mem_trip_us = get_wm_memory_trip(mode_lib, e2e_pipe_param, num_pipes);
	dlg_sys_param.t_mclk_wm_us = get_wm_dram_घड़ी_change(mode_lib, e2e_pipe_param, num_pipes);
	dlg_sys_param.t_sr_wm_us = get_wm_stutter_enter_निकास(mode_lib, e2e_pipe_param, num_pipes);
	dlg_sys_param.total_flip_bw = get_total_immediate_flip_bw(mode_lib,
			e2e_pipe_param,
			num_pipes);
	dlg_sys_param.total_flip_bytes = get_total_immediate_flip_bytes(mode_lib,
			e2e_pipe_param,
			num_pipes);
	dlg_sys_param.t_srx_delay_us = mode_lib->ip.dcfclk_cstate_latency
			/ dlg_sys_param.deepsleep_dcfclk_mhz; // TODO: Deprecated

	prपूर्णांक__dlg_sys_params_st(mode_lib, dlg_sys_param);

	// प्रणाली parameter calculation करोne

	dml_prपूर्णांक("DML_DLG: Calculation for pipe[%d] start\n\n", pipe_idx);
	dml20v2_rq_dlg_get_rq_params(mode_lib, &rq_param, e2e_pipe_param[pipe_idx].pipe.src);
	dml20v2_rq_dlg_get_dlg_params(mode_lib,
			e2e_pipe_param,
			num_pipes,
			pipe_idx,
			dlg_regs,
			ttu_regs,
			rq_param.dlg,
			dlg_sys_param,
			cstate_en,
			pstate_en);
	dml_prपूर्णांक("DML_DLG: Calculation for pipe[%d] end\n", pipe_idx);
पूर्ण

अटल व्योम calculate_ttu_cursor(काष्ठा display_mode_lib *mode_lib,
		द्विगुन *refcyc_per_req_delivery_pre_cur,
		द्विगुन *refcyc_per_req_delivery_cur,
		द्विगुन refclk_freq_in_mhz,
		द्विगुन ref_freq_to_pix_freq,
		द्विगुन hscale_pixel_rate_l,
		द्विगुन hscl_ratio,
		द्विगुन vratio_pre_l,
		द्विगुन vratio_l,
		अचिन्हित पूर्णांक cur_width,
		क्रमागत cursor_bpp cur_bpp)
अणु
	अचिन्हित पूर्णांक cur_src_width = cur_width;
	अचिन्हित पूर्णांक cur_req_size = 0;
	अचिन्हित पूर्णांक cur_req_width = 0;
	द्विगुन cur_width_ub = 0.0;
	द्विगुन cur_req_per_width = 0.0;
	द्विगुन hactive_cur = 0.0;

	ASSERT(cur_src_width <= 256);

	*refcyc_per_req_delivery_pre_cur = 0.0;
	*refcyc_per_req_delivery_cur = 0.0;
	अगर (cur_src_width > 0) अणु
		अचिन्हित पूर्णांक cur_bit_per_pixel = 0;

		अगर (cur_bpp == dm_cur_2bit) अणु
			cur_req_size = 64; // byte
			cur_bit_per_pixel = 2;
		पूर्ण अन्यथा अणु // 32bit
			cur_bit_per_pixel = 32;
			अगर (cur_src_width >= 1 && cur_src_width <= 16)
				cur_req_size = 64;
			अन्यथा अगर (cur_src_width >= 17 && cur_src_width <= 31)
				cur_req_size = 128;
			अन्यथा
				cur_req_size = 256;
		पूर्ण

		cur_req_width = (द्विगुन) cur_req_size / ((द्विगुन) cur_bit_per_pixel / 8.0);
		cur_width_ub = dml_उच्चमान((द्विगुन) cur_src_width / (द्विगुन) cur_req_width, 1)
				* (द्विगुन) cur_req_width;
		cur_req_per_width = cur_width_ub / (द्विगुन) cur_req_width;
		hactive_cur = (द्विगुन) cur_src_width / hscl_ratio; // TODO: oswin to think about what to करो क्रम cursor

		अगर (vratio_pre_l <= 1.0) अणु
			*refcyc_per_req_delivery_pre_cur = hactive_cur * ref_freq_to_pix_freq
					/ (द्विगुन) cur_req_per_width;
		पूर्ण अन्यथा अणु
			*refcyc_per_req_delivery_pre_cur = (द्विगुन) refclk_freq_in_mhz
					* (द्विगुन) cur_src_width / hscale_pixel_rate_l
					/ (द्विगुन) cur_req_per_width;
		पूर्ण

		ASSERT(*refcyc_per_req_delivery_pre_cur < dml_घात(2, 13));

		अगर (vratio_l <= 1.0) अणु
			*refcyc_per_req_delivery_cur = hactive_cur * ref_freq_to_pix_freq
					/ (द्विगुन) cur_req_per_width;
		पूर्ण अन्यथा अणु
			*refcyc_per_req_delivery_cur = (द्विगुन) refclk_freq_in_mhz
					* (द्विगुन) cur_src_width / hscale_pixel_rate_l
					/ (द्विगुन) cur_req_per_width;
		पूर्ण

		dml_prपूर्णांक("DML_DLG: %s: cur_req_width                     = %d\n",
				__func__,
				cur_req_width);
		dml_prपूर्णांक("DML_DLG: %s: cur_width_ub                      = %3.2f\n",
				__func__,
				cur_width_ub);
		dml_prपूर्णांक("DML_DLG: %s: cur_req_per_width                 = %3.2f\n",
				__func__,
				cur_req_per_width);
		dml_prपूर्णांक("DML_DLG: %s: hactive_cur                       = %3.2f\n",
				__func__,
				hactive_cur);
		dml_prपूर्णांक("DML_DLG: %s: refcyc_per_req_delivery_pre_cur   = %3.2f\n",
				__func__,
				*refcyc_per_req_delivery_pre_cur);
		dml_prपूर्णांक("DML_DLG: %s: refcyc_per_req_delivery_cur       = %3.2f\n",
				__func__,
				*refcyc_per_req_delivery_cur);

		ASSERT(*refcyc_per_req_delivery_cur < dml_घात(2, 13));
	पूर्ण
पूर्ण
