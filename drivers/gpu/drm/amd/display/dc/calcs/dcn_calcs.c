<शैली गुरु>
/*
 * Copyright 2017 Advanced Micro Devices, Inc.
 * Copyright 2019 Raptor Engineering, LLC
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
#समावेश "dc.h"
#समावेश "dcn_calcs.h"
#समावेश "dcn_calc_auto.h"
#समावेश "dal_asic_id.h"
#समावेश "resource.h"
#समावेश "dcn10/dcn10_resource.h"
#समावेश "dcn10/dcn10_hubbub.h"
#समावेश "dml/dml1_display_rq_dlg_calc.h"

#समावेश "dcn_calc_math.h"

#घोषणा DC_LOGGER \
	dc->ctx->logger

#घोषणा WM_SET_COUNT 4
#घोषणा WM_A 0
#घोषणा WM_B 1
#घोषणा WM_C 2
#घोषणा WM_D 3

/*
 * NOTE:
 *   This file is gcc-parseable HW gospel, coming straight from HW engineers.
 *
 * It करोesn't adhere to Linux kernel style and someबार will करो things in odd
 * ways. Unless there is something clearly wrong with it the code should
 * reमुख्य as-is as it provides us with a guarantee from HW that it is correct.
 */

/* Defaults from spपढ़ोsheet rev#247.
 * RV2 delta: dram_घड़ी_change_latency, max_num_dpp
 */
स्थिर काष्ठा dcn_soc_bounding_box dcn10_soc_शेषs = अणु
		/* latencies */
		.sr_निकास_समय = 17, /*us*/
		.sr_enter_plus_निकास_समय = 19, /*us*/
		.urgent_latency = 4, /*us*/
		.dram_घड़ी_change_latency = 17, /*us*/
		.ग_लिखो_back_latency = 12, /*us*/
		.percent_of_ideal_drambw_received_after_urg_latency = 80, /*%*/

		/* below शेष घड़ीs derived from STA target base on
		 * slow-slow corner + 10% margin with voltages aligned to FCLK.
		 *
		 * Use these value अगर fused value करोesn't make sense as earlier
		 * part करोn't have correct value fused */
		/* शेष DCF CLK DPM on RV*/
		.dcfclkv_max0p9 = 655,	/* MHz, = 3600/5.5 */
		.dcfclkv_nom0p8 = 626,	/* MHz, = 3600/5.75 */
		.dcfclkv_mid0p72 = 600,	/* MHz, = 3600/6, bypass */
		.dcfclkv_min0p65 = 300,	/* MHz, = 3600/12, bypass */

		/* शेष DISP CLK voltage state on RV */
		.max_dispclk_vmax0p9 = 1108,	/* MHz, = 3600/3.25 */
		.max_dispclk_vnom0p8 = 1029,	/* MHz, = 3600/3.5 */
		.max_dispclk_vmid0p72 = 960,	/* MHz, = 3600/3.75 */
		.max_dispclk_vmin0p65 = 626,	/* MHz, = 3600/5.75 */

		/* शेष DPP CLK voltage state on RV */
		.max_dppclk_vmax0p9 = 720,	/* MHz, = 3600/5 */
		.max_dppclk_vnom0p8 = 686,	/* MHz, = 3600/5.25 */
		.max_dppclk_vmid0p72 = 626,	/* MHz, = 3600/5.75 */
		.max_dppclk_vmin0p65 = 400,	/* MHz, = 3600/9 */

		/* शेष PHY CLK voltage state on RV */
		.phyclkv_max0p9 = 900, /*MHz*/
		.phyclkv_nom0p8 = 847, /*MHz*/
		.phyclkv_mid0p72 = 800, /*MHz*/
		.phyclkv_min0p65 = 600, /*MHz*/

		/* BW depend on FCLK, MCLK, # of channels */
		/* dual channel BW */
		.fabric_and_dram_bandwidth_vmax0p9 = 38.4f, /*GB/s*/
		.fabric_and_dram_bandwidth_vnom0p8 = 34.133f, /*GB/s*/
		.fabric_and_dram_bandwidth_vmid0p72 = 29.866f, /*GB/s*/
		.fabric_and_dram_bandwidth_vmin0p65 = 12.8f, /*GB/s*/
		/* single channel BW
		.fabric_and_dram_bandwidth_vmax0p9 = 19.2f,
		.fabric_and_dram_bandwidth_vnom0p8 = 17.066f,
		.fabric_and_dram_bandwidth_vmid0p72 = 14.933f,
		.fabric_and_dram_bandwidth_vmin0p65 = 12.8f,
		*/

		.number_of_channels = 2,

		.socclk = 208, /*MHz*/
		.करोwnspपढ़ोing = 0.5f, /*%*/
		.round_trip_ping_latency_cycles = 128, /*DCFCLK Cycles*/
		.urgent_out_of_order_वापस_per_channel = 256, /*bytes*/
		.vmm_page_size = 4096, /*bytes*/
		.वापस_bus_width = 64, /*bytes*/
		.max_request_size = 256, /*bytes*/

		/* Depends on user class (client vs embedded, workstation, etc) */
		.percent_disp_bw_limit = 0.3f /*%*/
पूर्ण;

स्थिर काष्ठा dcn_ip_params dcn10_ip_शेषs = अणु
		.rob_buffer_size_in_kbyte = 64,
		.det_buffer_size_in_kbyte = 164,
		.dpp_output_buffer_pixels = 2560,
		.opp_output_buffer_lines = 1,
		.pixel_chunk_size_in_kbyte = 8,
		.pte_enable = dcn_bw_yes,
		.pte_chunk_size = 2, /*kbytes*/
		.meta_chunk_size = 2, /*kbytes*/
		.ग_लिखोback_chunk_size = 2, /*kbytes*/
		.odm_capability = dcn_bw_no,
		.dsc_capability = dcn_bw_no,
		.line_buffer_size = 589824, /*bit*/
		.max_line_buffer_lines = 12,
		.is_line_buffer_bpp_fixed = dcn_bw_no,
		.line_buffer_fixed_bpp = dcn_bw_na,
		.ग_लिखोback_luma_buffer_size = 12, /*kbytes*/
		.ग_लिखोback_chroma_buffer_size = 8, /*kbytes*/
		.max_num_dpp = 4,
		.max_num_ग_लिखोback = 2,
		.max_dchub_topscl_throughput = 4, /*pixels/dppclk*/
		.max_pscl_tolb_throughput = 2, /*pixels/dppclk*/
		.max_lb_tovscl_throughput = 4, /*pixels/dppclk*/
		.max_vscl_tohscl_throughput = 4, /*pixels/dppclk*/
		.max_hscl_ratio = 4,
		.max_vscl_ratio = 4,
		.max_hscl_taps = 8,
		.max_vscl_taps = 8,
		.pte_buffer_size_in_requests = 42,
		.dispclk_ramping_margin = 1, /*%*/
		.under_scan_factor = 1.11f,
		.max_पूर्णांकer_dcn_tile_repeaters = 8,
		.can_vstartup_lines_exceed_vsync_plus_back_porch_lines_minus_one = dcn_bw_no,
		.bug_क्रमcing_luma_and_chroma_request_to_same_size_fixed = dcn_bw_no,
		.dcfclk_cstate_latency = 10 /*TODO clone of something अन्यथा? sr_enter_plus_निकास_समय?*/
पूर्ण;

अटल क्रमागत dcn_bw_defs tl_sw_mode_to_bw_defs(क्रमागत swizzle_mode_values sw_mode)
अणु
	चयन (sw_mode) अणु
	हाल DC_SW_LINEAR:
		वापस dcn_bw_sw_linear;
	हाल DC_SW_4KB_S:
		वापस dcn_bw_sw_4_kb_s;
	हाल DC_SW_4KB_D:
		वापस dcn_bw_sw_4_kb_d;
	हाल DC_SW_64KB_S:
		वापस dcn_bw_sw_64_kb_s;
	हाल DC_SW_64KB_D:
		वापस dcn_bw_sw_64_kb_d;
	हाल DC_SW_VAR_S:
		वापस dcn_bw_sw_var_s;
	हाल DC_SW_VAR_D:
		वापस dcn_bw_sw_var_d;
	हाल DC_SW_64KB_S_T:
		वापस dcn_bw_sw_64_kb_s_t;
	हाल DC_SW_64KB_D_T:
		वापस dcn_bw_sw_64_kb_d_t;
	हाल DC_SW_4KB_S_X:
		वापस dcn_bw_sw_4_kb_s_x;
	हाल DC_SW_4KB_D_X:
		वापस dcn_bw_sw_4_kb_d_x;
	हाल DC_SW_64KB_S_X:
		वापस dcn_bw_sw_64_kb_s_x;
	हाल DC_SW_64KB_D_X:
		वापस dcn_bw_sw_64_kb_d_x;
	हाल DC_SW_VAR_S_X:
		वापस dcn_bw_sw_var_s_x;
	हाल DC_SW_VAR_D_X:
		वापस dcn_bw_sw_var_d_x;
	हाल DC_SW_256B_S:
	हाल DC_SW_256_D:
	हाल DC_SW_256_R:
	हाल DC_SW_4KB_R:
	हाल DC_SW_64KB_R:
	हाल DC_SW_VAR_R:
	हाल DC_SW_4KB_R_X:
	हाल DC_SW_64KB_R_X:
	हाल DC_SW_VAR_R_X:
	शेष:
		BREAK_TO_DEBUGGER(); /*not in क्रमmula*/
		वापस dcn_bw_sw_4_kb_s;
	पूर्ण
पूर्ण

अटल पूर्णांक tl_lb_bpp_to_पूर्णांक(क्रमागत lb_pixel_depth depth)
अणु
	चयन (depth) अणु
	हाल LB_PIXEL_DEPTH_18BPP:
		वापस 18;
	हाल LB_PIXEL_DEPTH_24BPP:
		वापस 24;
	हाल LB_PIXEL_DEPTH_30BPP:
		वापस 30;
	हाल LB_PIXEL_DEPTH_36BPP:
		वापस 36;
	शेष:
		वापस 30;
	पूर्ण
पूर्ण

अटल क्रमागत dcn_bw_defs tl_pixel_क्रमmat_to_bw_defs(क्रमागत surface_pixel_क्रमmat क्रमmat)
अणु
	चयन (क्रमmat) अणु
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB1555:
	हाल SURFACE_PIXEL_FORMAT_GRPH_RGB565:
		वापस dcn_bw_rgb_sub_16;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB8888:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR8888:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010_XR_BIAS:
		वापस dcn_bw_rgb_sub_32;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616F:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F:
		वापस dcn_bw_rgb_sub_64;
	हाल SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr:
	हाल SURFACE_PIXEL_FORMAT_VIDEO_420_YCrCb:
		वापस dcn_bw_yuv420_sub_8;
	हाल SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCbCr:
	हाल SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCrCb:
		वापस dcn_bw_yuv420_sub_10;
	शेष:
		वापस dcn_bw_rgb_sub_32;
	पूर्ण
पूर्ण

क्रमागत source_macro_tile_size swizzle_mode_to_macro_tile_size(क्रमागत swizzle_mode_values sw_mode)
अणु
	चयन (sw_mode) अणु
	/* क्रम 4/8/16 high tiles */
	हाल DC_SW_LINEAR:
		वापस dm_4k_tile;
	हाल DC_SW_4KB_S:
	हाल DC_SW_4KB_S_X:
		वापस dm_4k_tile;
	हाल DC_SW_64KB_S:
	हाल DC_SW_64KB_S_X:
	हाल DC_SW_64KB_S_T:
		वापस dm_64k_tile;
	हाल DC_SW_VAR_S:
	हाल DC_SW_VAR_S_X:
		वापस dm_256k_tile;

	/* For 64bpp 2 high tiles */
	हाल DC_SW_4KB_D:
	हाल DC_SW_4KB_D_X:
		वापस dm_4k_tile;
	हाल DC_SW_64KB_D:
	हाल DC_SW_64KB_D_X:
	हाल DC_SW_64KB_D_T:
		वापस dm_64k_tile;
	हाल DC_SW_VAR_D:
	हाल DC_SW_VAR_D_X:
		वापस dm_256k_tile;

	हाल DC_SW_4KB_R:
	हाल DC_SW_4KB_R_X:
		वापस dm_4k_tile;
	हाल DC_SW_64KB_R:
	हाल DC_SW_64KB_R_X:
		वापस dm_64k_tile;
	हाल DC_SW_VAR_R:
	हाल DC_SW_VAR_R_X:
		वापस dm_256k_tile;

	/* Unsupported swizzle modes क्रम dcn */
	हाल DC_SW_256B_S:
	शेष:
		ASSERT(0); /* Not supported */
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम pipe_ctx_to_e2e_pipe_params (
		स्थिर काष्ठा pipe_ctx *pipe,
		काष्ठा _vcs_dpi_display_pipe_params_st *input)
अणु
	input->src.is_hsplit = false;

	/* stereo can never be split */
	अगर (pipe->plane_state->stereo_क्रमmat == PLANE_STEREO_FORMAT_SIDE_BY_SIDE ||
	    pipe->plane_state->stereo_क्रमmat == PLANE_STEREO_FORMAT_TOP_AND_BOTTOM) अणु
		/* reset the split group अगर it was alपढ़ोy considered split. */
		input->src.hsplit_grp = pipe->pipe_idx;
	पूर्ण अन्यथा अगर (pipe->top_pipe != शून्य && pipe->top_pipe->plane_state == pipe->plane_state) अणु
		input->src.is_hsplit = true;
	पूर्ण अन्यथा अगर (pipe->bottom_pipe != शून्य && pipe->bottom_pipe->plane_state == pipe->plane_state) अणु
		input->src.is_hsplit = true;
	पूर्ण

	अगर (pipe->plane_res.dpp->ctx->dc->debug.optimized_watermark) अणु
		/*
		 * this method requires us to always re-calculate watermark when dcc change
		 * between flip.
		 */
		input->src.dcc = pipe->plane_state->dcc.enable ? 1 : 0;
	पूर्ण अन्यथा अणु
		/*
		 * allow us to disable dcc on the fly without re-calculating WM
		 *
		 * extra overhead क्रम DCC is quite small.  क्रम 1080p WM without
		 * DCC is only 0.417us lower (urgent goes from 6.979us to 6.562us)
		 */
		अचिन्हित पूर्णांक bpe;

		input->src.dcc = pipe->plane_res.dpp->ctx->dc->res_pool->hubbub->funcs->
			dcc_support_pixel_क्रमmat(pipe->plane_state->क्रमmat, &bpe) ? 1 : 0;
	पूर्ण
	input->src.dcc_rate            = 1;
	input->src.meta_pitch          = pipe->plane_state->dcc.meta_pitch;
	input->src.source_scan         = dm_horz;
	input->src.sw_mode             = pipe->plane_state->tiling_info.gfx9.swizzle;

	input->src.viewport_width      = pipe->plane_res.scl_data.viewport.width;
	input->src.viewport_height     = pipe->plane_res.scl_data.viewport.height;
	input->src.data_pitch          = pipe->plane_res.scl_data.viewport.width;
	input->src.data_pitch_c        = pipe->plane_res.scl_data.viewport.width;
	input->src.cur0_src_width      = 128; /* TODO: Cursor calcs, not curently stored */
	input->src.cur0_bpp            = 32;

	input->src.macro_tile_size = swizzle_mode_to_macro_tile_size(pipe->plane_state->tiling_info.gfx9.swizzle);

	चयन (pipe->plane_state->rotation) अणु
	हाल ROTATION_ANGLE_0:
	हाल ROTATION_ANGLE_180:
		input->src.source_scan = dm_horz;
		अवरोध;
	हाल ROTATION_ANGLE_90:
	हाल ROTATION_ANGLE_270:
		input->src.source_scan = dm_vert;
		अवरोध;
	शेष:
		ASSERT(0); /* Not supported */
		अवरोध;
	पूर्ण

	/* TODO: Fix pixel क्रमmat mappings */
	चयन (pipe->plane_state->क्रमmat) अणु
	हाल SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr:
	हाल SURFACE_PIXEL_FORMAT_VIDEO_420_YCrCb:
		input->src.source_क्रमmat = dm_420_8;
		input->src.viewport_width_c    = input->src.viewport_width / 2;
		input->src.viewport_height_c   = input->src.viewport_height / 2;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCbCr:
	हाल SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCrCb:
		input->src.source_क्रमmat = dm_420_10;
		input->src.viewport_width_c    = input->src.viewport_width / 2;
		input->src.viewport_height_c   = input->src.viewport_height / 2;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616F:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F:
		input->src.source_क्रमmat = dm_444_64;
		input->src.viewport_width_c    = input->src.viewport_width;
		input->src.viewport_height_c   = input->src.viewport_height;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_RGBE_ALPHA:
		input->src.source_क्रमmat = dm_rgbe_alpha;
		input->src.viewport_width_c    = input->src.viewport_width;
		input->src.viewport_height_c   = input->src.viewport_height;
		अवरोध;
	शेष:
		input->src.source_क्रमmat = dm_444_32;
		input->src.viewport_width_c    = input->src.viewport_width;
		input->src.viewport_height_c   = input->src.viewport_height;
		अवरोध;
	पूर्ण

	input->scale_taps.htaps                = pipe->plane_res.scl_data.taps.h_taps;
	input->scale_ratio_depth.hscl_ratio    = pipe->plane_res.scl_data.ratios.horz.value/4294967296.0;
	input->scale_ratio_depth.vscl_ratio    = pipe->plane_res.scl_data.ratios.vert.value/4294967296.0;
	input->scale_ratio_depth.vinit =  pipe->plane_res.scl_data.inits.v.value/4294967296.0;
	अगर (input->scale_ratio_depth.vinit < 1.0)
			input->scale_ratio_depth.vinit = 1;
	input->scale_taps.vtaps = pipe->plane_res.scl_data.taps.v_taps;
	input->scale_taps.vtaps_c = pipe->plane_res.scl_data.taps.v_taps_c;
	input->scale_taps.htaps_c              = pipe->plane_res.scl_data.taps.h_taps_c;
	input->scale_ratio_depth.hscl_ratio_c  = pipe->plane_res.scl_data.ratios.horz_c.value/4294967296.0;
	input->scale_ratio_depth.vscl_ratio_c  = pipe->plane_res.scl_data.ratios.vert_c.value/4294967296.0;
	input->scale_ratio_depth.vinit_c       = pipe->plane_res.scl_data.inits.v_c.value/4294967296.0;
	अगर (input->scale_ratio_depth.vinit_c < 1.0)
			input->scale_ratio_depth.vinit_c = 1;
	चयन (pipe->plane_res.scl_data.lb_params.depth) अणु
	हाल LB_PIXEL_DEPTH_30BPP:
		input->scale_ratio_depth.lb_depth = 30; अवरोध;
	हाल LB_PIXEL_DEPTH_36BPP:
		input->scale_ratio_depth.lb_depth = 36; अवरोध;
	शेष:
		input->scale_ratio_depth.lb_depth = 24; अवरोध;
	पूर्ण


	input->dest.vactive        = pipe->stream->timing.v_addressable + pipe->stream->timing.v_border_top
			+ pipe->stream->timing.v_border_bottom;

	input->dest.recout_width   = pipe->plane_res.scl_data.recout.width;
	input->dest.recout_height  = pipe->plane_res.scl_data.recout.height;

	input->dest.full_recout_width   = pipe->plane_res.scl_data.recout.width;
	input->dest.full_recout_height  = pipe->plane_res.scl_data.recout.height;

	input->dest.htotal         = pipe->stream->timing.h_total;
	input->dest.hblank_start   = input->dest.htotal - pipe->stream->timing.h_front_porch;
	input->dest.hblank_end     = input->dest.hblank_start
			- pipe->stream->timing.h_addressable
			- pipe->stream->timing.h_border_left
			- pipe->stream->timing.h_border_right;

	input->dest.vtotal         = pipe->stream->timing.v_total;
	input->dest.vblank_start   = input->dest.vtotal - pipe->stream->timing.v_front_porch;
	input->dest.vblank_end     = input->dest.vblank_start
			- pipe->stream->timing.v_addressable
			- pipe->stream->timing.v_border_bottom
			- pipe->stream->timing.v_border_top;
	input->dest.pixel_rate_mhz = pipe->stream->timing.pix_clk_100hz/10000.0;
	input->dest.vstartup_start = pipe->pipe_dlg_param.vstartup_start;
	input->dest.vupdate_offset = pipe->pipe_dlg_param.vupdate_offset;
	input->dest.vupdate_offset = pipe->pipe_dlg_param.vupdate_offset;
	input->dest.vupdate_width = pipe->pipe_dlg_param.vupdate_width;

पूर्ण

अटल व्योम dcn_bw_calc_rq_dlg_ttu(
		स्थिर काष्ठा dc *dc,
		स्थिर काष्ठा dcn_bw_पूर्णांकernal_vars *v,
		काष्ठा pipe_ctx *pipe,
		पूर्णांक in_idx)
अणु
	काष्ठा display_mode_lib *dml = (काष्ठा display_mode_lib *)(&dc->dml);
	काष्ठा _vcs_dpi_display_dlg_regs_st *dlg_regs = &pipe->dlg_regs;
	काष्ठा _vcs_dpi_display_ttu_regs_st *ttu_regs = &pipe->ttu_regs;
	काष्ठा _vcs_dpi_display_rq_regs_st *rq_regs = &pipe->rq_regs;
	काष्ठा _vcs_dpi_display_rq_params_st rq_param = अणु0पूर्ण;
	काष्ठा _vcs_dpi_display_dlg_sys_params_st dlg_sys_param = अणु0पूर्ण;
	काष्ठा _vcs_dpi_display_e2e_pipe_params_st input = अणु अणु अणु 0 पूर्ण पूर्ण पूर्ण;
	भग्न total_active_bw = 0;
	भग्न total_prefetch_bw = 0;
	पूर्णांक total_flip_bytes = 0;
	पूर्णांक i;

	स_रखो(dlg_regs, 0, माप(*dlg_regs));
	स_रखो(ttu_regs, 0, माप(*ttu_regs));
	स_रखो(rq_regs, 0, माप(*rq_regs));

	क्रम (i = 0; i < number_of_planes; i++) अणु
		total_active_bw += v->पढ़ो_bandwidth[i];
		total_prefetch_bw += v->prefetch_bandwidth[i];
		total_flip_bytes += v->total_immediate_flip_bytes[i];
	पूर्ण
	dlg_sys_param.total_flip_bw = v->वापस_bw - dcn_bw_max2(total_active_bw, total_prefetch_bw);
	अगर (dlg_sys_param.total_flip_bw < 0.0)
		dlg_sys_param.total_flip_bw = 0;

	dlg_sys_param.t_mclk_wm_us = v->dram_घड़ी_change_watermark;
	dlg_sys_param.t_sr_wm_us = v->stutter_enter_plus_निकास_watermark;
	dlg_sys_param.t_urg_wm_us = v->urgent_watermark;
	dlg_sys_param.t_extra_us = v->urgent_extra_latency;
	dlg_sys_param.deepsleep_dcfclk_mhz = v->dcf_clk_deep_sleep;
	dlg_sys_param.total_flip_bytes = total_flip_bytes;

	pipe_ctx_to_e2e_pipe_params(pipe, &input.pipe);
	input.clks_cfg.dcfclk_mhz = v->dcfclk;
	input.clks_cfg.dispclk_mhz = v->dispclk;
	input.clks_cfg.dppclk_mhz = v->dppclk;
	input.clks_cfg.refclk_mhz = dc->res_pool->ref_घड़ीs.dchub_ref_घड़ी_inKhz / 1000.0;
	input.clks_cfg.socclk_mhz = v->socclk;
	input.clks_cfg.voltage = v->voltage_level;
//	dc->dml.logger = pool->base.logger;
	input.करोut.output_क्रमmat = (v->output_क्रमmat[in_idx] == dcn_bw_420) ? dm_420 : dm_444;
	input.करोut.output_type  = (v->output[in_idx] == dcn_bw_hdmi) ? dm_hdmi : dm_dp;
	//input[in_idx].करोut.output_standard;

	/*toकरो: soc->sr_enter_plus_निकास_समय??*/
	dlg_sys_param.t_srx_delay_us = dc->dcn_ip->dcfclk_cstate_latency / v->dcf_clk_deep_sleep;

	dml1_rq_dlg_get_rq_params(dml, &rq_param, input.pipe.src);
	dml1_extract_rq_regs(dml, rq_regs, rq_param);
	dml1_rq_dlg_get_dlg_params(
			dml,
			dlg_regs,
			ttu_regs,
			rq_param.dlg,
			dlg_sys_param,
			input,
			true,
			true,
			v->pte_enable == dcn_bw_yes,
			pipe->plane_state->flip_immediate);
पूर्ण

अटल व्योम split_stream_across_pipes(
		काष्ठा resource_context *res_ctx,
		स्थिर काष्ठा resource_pool *pool,
		काष्ठा pipe_ctx *primary_pipe,
		काष्ठा pipe_ctx *secondary_pipe)
अणु
	पूर्णांक pipe_idx = secondary_pipe->pipe_idx;

	अगर (!primary_pipe->plane_state)
		वापस;

	*secondary_pipe = *primary_pipe;

	secondary_pipe->pipe_idx = pipe_idx;
	secondary_pipe->plane_res.mi = pool->mis[secondary_pipe->pipe_idx];
	secondary_pipe->plane_res.hubp = pool->hubps[secondary_pipe->pipe_idx];
	secondary_pipe->plane_res.ipp = pool->ipps[secondary_pipe->pipe_idx];
	secondary_pipe->plane_res.xfm = pool->transक्रमms[secondary_pipe->pipe_idx];
	secondary_pipe->plane_res.dpp = pool->dpps[secondary_pipe->pipe_idx];
	secondary_pipe->plane_res.mpcc_inst = pool->dpps[secondary_pipe->pipe_idx]->inst;
	अगर (primary_pipe->bottom_pipe) अणु
		ASSERT(primary_pipe->bottom_pipe != secondary_pipe);
		secondary_pipe->bottom_pipe = primary_pipe->bottom_pipe;
		secondary_pipe->bottom_pipe->top_pipe = secondary_pipe;
	पूर्ण
	primary_pipe->bottom_pipe = secondary_pipe;
	secondary_pipe->top_pipe = primary_pipe;

	resource_build_scaling_params(primary_pipe);
	resource_build_scaling_params(secondary_pipe);
पूर्ण

#अगर 0
अटल व्योम calc_wm_sets_and_perf_params(
		काष्ठा dc_state *context,
		काष्ठा dcn_bw_पूर्णांकernal_vars *v)
अणु
	/* Calculate set A last to keep पूर्णांकernal var state consistent क्रम required config */
	अगर (v->voltage_level < 2) अणु
		v->fabric_and_dram_bandwidth_per_state[1] = v->fabric_and_dram_bandwidth_vnom0p8;
		v->fabric_and_dram_bandwidth_per_state[0] = v->fabric_and_dram_bandwidth_vnom0p8;
		v->fabric_and_dram_bandwidth = v->fabric_and_dram_bandwidth_vnom0p8;
		dispclkdppclkdcfclk_deep_sleep_prefetch_parameters_watermarks_and_perक्रमmance_calculation(v);

		context->bw_ctx.bw.dcn.watermarks.b.cstate_pstate.cstate_निकास_ns =
			v->stutter_निकास_watermark * 1000;
		context->bw_ctx.bw.dcn.watermarks.b.cstate_pstate.cstate_enter_plus_निकास_ns =
				v->stutter_enter_plus_निकास_watermark * 1000;
		context->bw_ctx.bw.dcn.watermarks.b.cstate_pstate.pstate_change_ns =
				v->dram_घड़ी_change_watermark * 1000;
		context->bw_ctx.bw.dcn.watermarks.b.pte_meta_urgent_ns = v->ptemeta_urgent_watermark * 1000;
		context->bw_ctx.bw.dcn.watermarks.b.urgent_ns = v->urgent_watermark * 1000;

		v->dcfclk_per_state[1] = v->dcfclkv_nom0p8;
		v->dcfclk_per_state[0] = v->dcfclkv_nom0p8;
		v->dcfclk = v->dcfclkv_nom0p8;
		dispclkdppclkdcfclk_deep_sleep_prefetch_parameters_watermarks_and_perक्रमmance_calculation(v);

		context->bw_ctx.bw.dcn.watermarks.c.cstate_pstate.cstate_निकास_ns =
			v->stutter_निकास_watermark * 1000;
		context->bw_ctx.bw.dcn.watermarks.c.cstate_pstate.cstate_enter_plus_निकास_ns =
				v->stutter_enter_plus_निकास_watermark * 1000;
		context->bw_ctx.bw.dcn.watermarks.c.cstate_pstate.pstate_change_ns =
				v->dram_घड़ी_change_watermark * 1000;
		context->bw_ctx.bw.dcn.watermarks.c.pte_meta_urgent_ns = v->ptemeta_urgent_watermark * 1000;
		context->bw_ctx.bw.dcn.watermarks.c.urgent_ns = v->urgent_watermark * 1000;
	पूर्ण

	अगर (v->voltage_level < 3) अणु
		v->fabric_and_dram_bandwidth_per_state[2] = v->fabric_and_dram_bandwidth_vmax0p9;
		v->fabric_and_dram_bandwidth_per_state[1] = v->fabric_and_dram_bandwidth_vmax0p9;
		v->fabric_and_dram_bandwidth_per_state[0] = v->fabric_and_dram_bandwidth_vmax0p9;
		v->fabric_and_dram_bandwidth = v->fabric_and_dram_bandwidth_vmax0p9;
		v->dcfclk_per_state[2] = v->dcfclkv_max0p9;
		v->dcfclk_per_state[1] = v->dcfclkv_max0p9;
		v->dcfclk_per_state[0] = v->dcfclkv_max0p9;
		v->dcfclk = v->dcfclkv_max0p9;
		dispclkdppclkdcfclk_deep_sleep_prefetch_parameters_watermarks_and_perक्रमmance_calculation(v);

		context->bw_ctx.bw.dcn.watermarks.d.cstate_pstate.cstate_निकास_ns =
			v->stutter_निकास_watermark * 1000;
		context->bw_ctx.bw.dcn.watermarks.d.cstate_pstate.cstate_enter_plus_निकास_ns =
				v->stutter_enter_plus_निकास_watermark * 1000;
		context->bw_ctx.bw.dcn.watermarks.d.cstate_pstate.pstate_change_ns =
				v->dram_घड़ी_change_watermark * 1000;
		context->bw_ctx.bw.dcn.watermarks.d.pte_meta_urgent_ns = v->ptemeta_urgent_watermark * 1000;
		context->bw_ctx.bw.dcn.watermarks.d.urgent_ns = v->urgent_watermark * 1000;
	पूर्ण

	v->fabric_and_dram_bandwidth_per_state[2] = v->fabric_and_dram_bandwidth_vnom0p8;
	v->fabric_and_dram_bandwidth_per_state[1] = v->fabric_and_dram_bandwidth_vmid0p72;
	v->fabric_and_dram_bandwidth_per_state[0] = v->fabric_and_dram_bandwidth_vmin0p65;
	v->fabric_and_dram_bandwidth = v->fabric_and_dram_bandwidth_per_state[v->voltage_level];
	v->dcfclk_per_state[2] = v->dcfclkv_nom0p8;
	v->dcfclk_per_state[1] = v->dcfclkv_mid0p72;
	v->dcfclk_per_state[0] = v->dcfclkv_min0p65;
	v->dcfclk = v->dcfclk_per_state[v->voltage_level];
	dispclkdppclkdcfclk_deep_sleep_prefetch_parameters_watermarks_and_perक्रमmance_calculation(v);

	context->bw_ctx.bw.dcn.watermarks.a.cstate_pstate.cstate_निकास_ns =
		v->stutter_निकास_watermark * 1000;
	context->bw_ctx.bw.dcn.watermarks.a.cstate_pstate.cstate_enter_plus_निकास_ns =
			v->stutter_enter_plus_निकास_watermark * 1000;
	context->bw_ctx.bw.dcn.watermarks.a.cstate_pstate.pstate_change_ns =
			v->dram_घड़ी_change_watermark * 1000;
	context->bw_ctx.bw.dcn.watermarks.a.pte_meta_urgent_ns = v->ptemeta_urgent_watermark * 1000;
	context->bw_ctx.bw.dcn.watermarks.a.urgent_ns = v->urgent_watermark * 1000;
	अगर (v->voltage_level >= 2) अणु
		context->bw_ctx.bw.dcn.watermarks.b = context->bw_ctx.bw.dcn.watermarks.a;
		context->bw_ctx.bw.dcn.watermarks.c = context->bw_ctx.bw.dcn.watermarks.a;
	पूर्ण
	अगर (v->voltage_level >= 3)
		context->bw_ctx.bw.dcn.watermarks.d = context->bw_ctx.bw.dcn.watermarks.a;
पूर्ण
#पूर्ण_अगर

अटल bool dcn_bw_apply_registry_override(काष्ठा dc *dc)
अणु
	bool updated = false;

	DC_FP_START();
	अगर ((पूर्णांक)(dc->dcn_soc->sr_निकास_समय * 1000) != dc->debug.sr_निकास_समय_ns
			&& dc->debug.sr_निकास_समय_ns) अणु
		updated = true;
		dc->dcn_soc->sr_निकास_समय = dc->debug.sr_निकास_समय_ns / 1000.0;
	पूर्ण

	अगर ((पूर्णांक)(dc->dcn_soc->sr_enter_plus_निकास_समय * 1000)
				!= dc->debug.sr_enter_plus_निकास_समय_ns
			&& dc->debug.sr_enter_plus_निकास_समय_ns) अणु
		updated = true;
		dc->dcn_soc->sr_enter_plus_निकास_समय =
				dc->debug.sr_enter_plus_निकास_समय_ns / 1000.0;
	पूर्ण

	अगर ((पूर्णांक)(dc->dcn_soc->urgent_latency * 1000) != dc->debug.urgent_latency_ns
			&& dc->debug.urgent_latency_ns) अणु
		updated = true;
		dc->dcn_soc->urgent_latency = dc->debug.urgent_latency_ns / 1000.0;
	पूर्ण

	अगर ((पूर्णांक)(dc->dcn_soc->percent_of_ideal_drambw_received_after_urg_latency * 1000)
				!= dc->debug.percent_of_ideal_drambw
			&& dc->debug.percent_of_ideal_drambw) अणु
		updated = true;
		dc->dcn_soc->percent_of_ideal_drambw_received_after_urg_latency =
				dc->debug.percent_of_ideal_drambw;
	पूर्ण

	अगर ((पूर्णांक)(dc->dcn_soc->dram_घड़ी_change_latency * 1000)
				!= dc->debug.dram_घड़ी_change_latency_ns
			&& dc->debug.dram_घड़ी_change_latency_ns) अणु
		updated = true;
		dc->dcn_soc->dram_घड़ी_change_latency =
				dc->debug.dram_घड़ी_change_latency_ns / 1000.0;
	पूर्ण
	DC_FP_END();

	वापस updated;
पूर्ण

अटल व्योम hack_disable_optional_pipe_split(काष्ठा dcn_bw_पूर्णांकernal_vars *v)
अणु
	/*
	 * disable optional pipe split by lower dispclk bounding box
	 * at DPM0
	 */
	v->max_dispclk[0] = v->max_dppclk_vmin0p65;
पूर्ण

अटल व्योम hack_क्रमce_pipe_split(काष्ठा dcn_bw_पूर्णांकernal_vars *v,
		अचिन्हित पूर्णांक pixel_rate_100hz)
अणु
	भग्न pixel_rate_mhz = pixel_rate_100hz / 10000;

	/*
	 * क्रमce enabling pipe split by lower dpp घड़ी क्रम DPM0 to just
	 * below the specअगरy pixel_rate, so bw calc would split pipe.
	 */
	अगर (pixel_rate_mhz < v->max_dppclk[0])
		v->max_dppclk[0] = pixel_rate_mhz;
पूर्ण

अटल व्योम hack_bounding_box(काष्ठा dcn_bw_पूर्णांकernal_vars *v,
		काष्ठा dc_debug_options *dbg,
		काष्ठा dc_state *context)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		काष्ठा pipe_ctx *pipe = &context->res_ctx.pipe_ctx[i];

		/**
		 * Workaround क्रम aव्योमing pipe-split in हालs where we'd split
		 * planes that are too small, resulting in splits that aren't
		 * valid क्रम the scaler.
		 */
		अगर (pipe->plane_state &&
		    (pipe->plane_state->dst_rect.width <= 16 ||
		     pipe->plane_state->dst_rect.height <= 16 ||
		     pipe->plane_state->src_rect.width <= 16 ||
		     pipe->plane_state->src_rect.height <= 16)) अणु
			hack_disable_optional_pipe_split(v);
			वापस;
		पूर्ण
	पूर्ण

	अगर (dbg->pipe_split_policy == MPC_SPLIT_AVOID)
		hack_disable_optional_pipe_split(v);

	अगर (dbg->pipe_split_policy == MPC_SPLIT_AVOID_MULT_DISP &&
		context->stream_count >= 2)
		hack_disable_optional_pipe_split(v);

	अगर (context->stream_count == 1 &&
			dbg->क्रमce_single_disp_pipe_split)
		hack_क्रमce_pipe_split(v, context->streams[0]->timing.pix_clk_100hz);
पूर्ण

अचिन्हित पूर्णांक get_highest_allowed_voltage_level(uपूर्णांक32_t chip_family, uपूर्णांक32_t hw_पूर्णांकernal_rev, uपूर्णांक32_t pci_revision_id)
अणु
	/* क्रम low घातer RV2 variants, the highest voltage level we want is 0 */
	अगर ((chip_family == FAMILY_RV) &&
	     ASICREV_IS_RAVEN2(hw_पूर्णांकernal_rev))
		चयन (pci_revision_id) अणु
		हाल PRID_DALI_DE:
		हाल PRID_DALI_DF:
		हाल PRID_DALI_E3:
		हाल PRID_DALI_E4:
		हाल PRID_POLLOCK_94:
		हाल PRID_POLLOCK_95:
		हाल PRID_POLLOCK_E9:
		हाल PRID_POLLOCK_EA:
		हाल PRID_POLLOCK_EB:
			वापस 0;
		शेष:
			अवरोध;
		पूर्ण

	/* we are ok with all levels */
	वापस 4;
पूर्ण

bool dcn_validate_bandwidth(
		काष्ठा dc *dc,
		काष्ठा dc_state *context,
		bool fast_validate)
अणु
	/*
	 * we want a अवरोधकरोwn of the various stages of validation, which the
	 * perf_trace macro करोesn't support
	 */
	BW_VAL_TRACE_SETUP();

	स्थिर काष्ठा resource_pool *pool = dc->res_pool;
	काष्ठा dcn_bw_पूर्णांकernal_vars *v = &context->dcn_bw_vars;
	पूर्णांक i, input_idx, k;
	पूर्णांक vesa_sync_start, asic_blank_end, asic_blank_start;
	bool bw_limit_pass;
	भग्न bw_limit;

	PERFORMANCE_TRACE_START();

	BW_VAL_TRACE_COUNT();

	अगर (dcn_bw_apply_registry_override(dc))
		dcn_bw_sync_calcs_and_dml(dc);

	स_रखो(v, 0, माप(*v));
	DC_FP_START();

	v->sr_निकास_समय = dc->dcn_soc->sr_निकास_समय;
	v->sr_enter_plus_निकास_समय = dc->dcn_soc->sr_enter_plus_निकास_समय;
	v->urgent_latency = dc->dcn_soc->urgent_latency;
	v->ग_लिखो_back_latency = dc->dcn_soc->ग_लिखो_back_latency;
	v->percent_of_ideal_drambw_received_after_urg_latency =
			dc->dcn_soc->percent_of_ideal_drambw_received_after_urg_latency;

	v->dcfclkv_min0p65 = dc->dcn_soc->dcfclkv_min0p65;
	v->dcfclkv_mid0p72 = dc->dcn_soc->dcfclkv_mid0p72;
	v->dcfclkv_nom0p8 = dc->dcn_soc->dcfclkv_nom0p8;
	v->dcfclkv_max0p9 = dc->dcn_soc->dcfclkv_max0p9;

	v->max_dispclk_vmin0p65 = dc->dcn_soc->max_dispclk_vmin0p65;
	v->max_dispclk_vmid0p72 = dc->dcn_soc->max_dispclk_vmid0p72;
	v->max_dispclk_vnom0p8 = dc->dcn_soc->max_dispclk_vnom0p8;
	v->max_dispclk_vmax0p9 = dc->dcn_soc->max_dispclk_vmax0p9;

	v->max_dppclk_vmin0p65 = dc->dcn_soc->max_dppclk_vmin0p65;
	v->max_dppclk_vmid0p72 = dc->dcn_soc->max_dppclk_vmid0p72;
	v->max_dppclk_vnom0p8 = dc->dcn_soc->max_dppclk_vnom0p8;
	v->max_dppclk_vmax0p9 = dc->dcn_soc->max_dppclk_vmax0p9;

	v->socclk = dc->dcn_soc->socclk;

	v->fabric_and_dram_bandwidth_vmin0p65 = dc->dcn_soc->fabric_and_dram_bandwidth_vmin0p65;
	v->fabric_and_dram_bandwidth_vmid0p72 = dc->dcn_soc->fabric_and_dram_bandwidth_vmid0p72;
	v->fabric_and_dram_bandwidth_vnom0p8 = dc->dcn_soc->fabric_and_dram_bandwidth_vnom0p8;
	v->fabric_and_dram_bandwidth_vmax0p9 = dc->dcn_soc->fabric_and_dram_bandwidth_vmax0p9;

	v->phyclkv_min0p65 = dc->dcn_soc->phyclkv_min0p65;
	v->phyclkv_mid0p72 = dc->dcn_soc->phyclkv_mid0p72;
	v->phyclkv_nom0p8 = dc->dcn_soc->phyclkv_nom0p8;
	v->phyclkv_max0p9 = dc->dcn_soc->phyclkv_max0p9;

	v->करोwnspपढ़ोing = dc->dcn_soc->करोwnspपढ़ोing;
	v->round_trip_ping_latency_cycles = dc->dcn_soc->round_trip_ping_latency_cycles;
	v->urgent_out_of_order_वापस_per_channel = dc->dcn_soc->urgent_out_of_order_वापस_per_channel;
	v->number_of_channels = dc->dcn_soc->number_of_channels;
	v->vmm_page_size = dc->dcn_soc->vmm_page_size;
	v->dram_घड़ी_change_latency = dc->dcn_soc->dram_घड़ी_change_latency;
	v->वापस_bus_width = dc->dcn_soc->वापस_bus_width;

	v->rob_buffer_size_in_kbyte = dc->dcn_ip->rob_buffer_size_in_kbyte;
	v->det_buffer_size_in_kbyte = dc->dcn_ip->det_buffer_size_in_kbyte;
	v->dpp_output_buffer_pixels = dc->dcn_ip->dpp_output_buffer_pixels;
	v->opp_output_buffer_lines = dc->dcn_ip->opp_output_buffer_lines;
	v->pixel_chunk_size_in_kbyte = dc->dcn_ip->pixel_chunk_size_in_kbyte;
	v->pte_enable = dc->dcn_ip->pte_enable;
	v->pte_chunk_size = dc->dcn_ip->pte_chunk_size;
	v->meta_chunk_size = dc->dcn_ip->meta_chunk_size;
	v->ग_लिखोback_chunk_size = dc->dcn_ip->ग_लिखोback_chunk_size;
	v->odm_capability = dc->dcn_ip->odm_capability;
	v->dsc_capability = dc->dcn_ip->dsc_capability;
	v->line_buffer_size = dc->dcn_ip->line_buffer_size;
	v->is_line_buffer_bpp_fixed = dc->dcn_ip->is_line_buffer_bpp_fixed;
	v->line_buffer_fixed_bpp = dc->dcn_ip->line_buffer_fixed_bpp;
	v->max_line_buffer_lines = dc->dcn_ip->max_line_buffer_lines;
	v->ग_लिखोback_luma_buffer_size = dc->dcn_ip->ग_लिखोback_luma_buffer_size;
	v->ग_लिखोback_chroma_buffer_size = dc->dcn_ip->ग_लिखोback_chroma_buffer_size;
	v->max_num_dpp = dc->dcn_ip->max_num_dpp;
	v->max_num_ग_लिखोback = dc->dcn_ip->max_num_ग_लिखोback;
	v->max_dchub_topscl_throughput = dc->dcn_ip->max_dchub_topscl_throughput;
	v->max_pscl_tolb_throughput = dc->dcn_ip->max_pscl_tolb_throughput;
	v->max_lb_tovscl_throughput = dc->dcn_ip->max_lb_tovscl_throughput;
	v->max_vscl_tohscl_throughput = dc->dcn_ip->max_vscl_tohscl_throughput;
	v->max_hscl_ratio = dc->dcn_ip->max_hscl_ratio;
	v->max_vscl_ratio = dc->dcn_ip->max_vscl_ratio;
	v->max_hscl_taps = dc->dcn_ip->max_hscl_taps;
	v->max_vscl_taps = dc->dcn_ip->max_vscl_taps;
	v->under_scan_factor = dc->dcn_ip->under_scan_factor;
	v->pte_buffer_size_in_requests = dc->dcn_ip->pte_buffer_size_in_requests;
	v->dispclk_ramping_margin = dc->dcn_ip->dispclk_ramping_margin;
	v->max_पूर्णांकer_dcn_tile_repeaters = dc->dcn_ip->max_पूर्णांकer_dcn_tile_repeaters;
	v->can_vstartup_lines_exceed_vsync_plus_back_porch_lines_minus_one =
			dc->dcn_ip->can_vstartup_lines_exceed_vsync_plus_back_porch_lines_minus_one;
	v->bug_क्रमcing_luma_and_chroma_request_to_same_size_fixed =
			dc->dcn_ip->bug_क्रमcing_luma_and_chroma_request_to_same_size_fixed;

	v->voltage[5] = dcn_bw_no_support;
	v->voltage[4] = dcn_bw_v_max0p9;
	v->voltage[3] = dcn_bw_v_max0p9;
	v->voltage[2] = dcn_bw_v_nom0p8;
	v->voltage[1] = dcn_bw_v_mid0p72;
	v->voltage[0] = dcn_bw_v_min0p65;
	v->fabric_and_dram_bandwidth_per_state[5] = v->fabric_and_dram_bandwidth_vmax0p9;
	v->fabric_and_dram_bandwidth_per_state[4] = v->fabric_and_dram_bandwidth_vmax0p9;
	v->fabric_and_dram_bandwidth_per_state[3] = v->fabric_and_dram_bandwidth_vmax0p9;
	v->fabric_and_dram_bandwidth_per_state[2] = v->fabric_and_dram_bandwidth_vnom0p8;
	v->fabric_and_dram_bandwidth_per_state[1] = v->fabric_and_dram_bandwidth_vmid0p72;
	v->fabric_and_dram_bandwidth_per_state[0] = v->fabric_and_dram_bandwidth_vmin0p65;
	v->dcfclk_per_state[5] = v->dcfclkv_max0p9;
	v->dcfclk_per_state[4] = v->dcfclkv_max0p9;
	v->dcfclk_per_state[3] = v->dcfclkv_max0p9;
	v->dcfclk_per_state[2] = v->dcfclkv_nom0p8;
	v->dcfclk_per_state[1] = v->dcfclkv_mid0p72;
	v->dcfclk_per_state[0] = v->dcfclkv_min0p65;
	v->max_dispclk[5] = v->max_dispclk_vmax0p9;
	v->max_dispclk[4] = v->max_dispclk_vmax0p9;
	v->max_dispclk[3] = v->max_dispclk_vmax0p9;
	v->max_dispclk[2] = v->max_dispclk_vnom0p8;
	v->max_dispclk[1] = v->max_dispclk_vmid0p72;
	v->max_dispclk[0] = v->max_dispclk_vmin0p65;
	v->max_dppclk[5] = v->max_dppclk_vmax0p9;
	v->max_dppclk[4] = v->max_dppclk_vmax0p9;
	v->max_dppclk[3] = v->max_dppclk_vmax0p9;
	v->max_dppclk[2] = v->max_dppclk_vnom0p8;
	v->max_dppclk[1] = v->max_dppclk_vmid0p72;
	v->max_dppclk[0] = v->max_dppclk_vmin0p65;
	v->phyclk_per_state[5] = v->phyclkv_max0p9;
	v->phyclk_per_state[4] = v->phyclkv_max0p9;
	v->phyclk_per_state[3] = v->phyclkv_max0p9;
	v->phyclk_per_state[2] = v->phyclkv_nom0p8;
	v->phyclk_per_state[1] = v->phyclkv_mid0p72;
	v->phyclk_per_state[0] = v->phyclkv_min0p65;
	v->synchronized_vblank = dcn_bw_no;
	v->ta_pscalculation = dcn_bw_override;
	v->allow_dअगरferent_hratio_vratio = dcn_bw_yes;

	क्रम (i = 0, input_idx = 0; i < pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe = &context->res_ctx.pipe_ctx[i];

		अगर (!pipe->stream)
			जारी;
		/* skip all but first of split pipes */
		अगर (pipe->top_pipe && pipe->top_pipe->plane_state == pipe->plane_state)
			जारी;

		v->underscan_output[input_idx] = false; /* taken care of in recout alपढ़ोy*/
		v->पूर्णांकerlace_output[input_idx] = false;

		v->htotal[input_idx] = pipe->stream->timing.h_total;
		v->vtotal[input_idx] = pipe->stream->timing.v_total;
		v->vactive[input_idx] = pipe->stream->timing.v_addressable +
				pipe->stream->timing.v_border_top + pipe->stream->timing.v_border_bottom;
		v->v_sync_plus_back_porch[input_idx] = pipe->stream->timing.v_total
				- v->vactive[input_idx]
				- pipe->stream->timing.v_front_porch;
		v->pixel_घड़ी[input_idx] = pipe->stream->timing.pix_clk_100hz/10000.0;
		अगर (pipe->stream->timing.timing_3d_क्रमmat == TIMING_3D_FORMAT_HW_FRAME_PACKING)
			v->pixel_घड़ी[input_idx] *= 2;
		अगर (!pipe->plane_state) अणु
			v->dcc_enable[input_idx] = dcn_bw_yes;
			v->source_pixel_क्रमmat[input_idx] = dcn_bw_rgb_sub_32;
			v->source_surface_mode[input_idx] = dcn_bw_sw_4_kb_s;
			v->lb_bit_per_pixel[input_idx] = 30;
			v->viewport_width[input_idx] = pipe->stream->timing.h_addressable;
			v->viewport_height[input_idx] = pipe->stream->timing.v_addressable;
			/*
			 * क्रम हालs where we have no plane, we want to validate up to 1080p
			 * source size because here we are only पूर्णांकerested in अगर the output
			 * timing is supported or not. अगर we cannot support native resolution
			 * of the high res display, we still want to support lower res up scale
			 * to native
			 */
			अगर (v->viewport_width[input_idx] > 1920)
				v->viewport_width[input_idx] = 1920;
			अगर (v->viewport_height[input_idx] > 1080)
				v->viewport_height[input_idx] = 1080;
			v->scaler_rec_out_width[input_idx] = v->viewport_width[input_idx];
			v->scaler_recout_height[input_idx] = v->viewport_height[input_idx];
			v->override_hta_ps[input_idx] = 1;
			v->override_vta_ps[input_idx] = 1;
			v->override_hta_pschroma[input_idx] = 1;
			v->override_vta_pschroma[input_idx] = 1;
			v->source_scan[input_idx] = dcn_bw_hor;

		पूर्ण अन्यथा अणु
			v->viewport_height[input_idx] =  pipe->plane_res.scl_data.viewport.height;
			v->viewport_width[input_idx] = pipe->plane_res.scl_data.viewport.width;
			v->scaler_rec_out_width[input_idx] = pipe->plane_res.scl_data.recout.width;
			v->scaler_recout_height[input_idx] = pipe->plane_res.scl_data.recout.height;
			अगर (pipe->bottom_pipe && pipe->bottom_pipe->plane_state == pipe->plane_state) अणु
				अगर (pipe->plane_state->rotation % 2 == 0) अणु
					पूर्णांक viewport_end = pipe->plane_res.scl_data.viewport.width
							+ pipe->plane_res.scl_data.viewport.x;
					पूर्णांक viewport_b_end = pipe->bottom_pipe->plane_res.scl_data.viewport.width
							+ pipe->bottom_pipe->plane_res.scl_data.viewport.x;

					अगर (viewport_end > viewport_b_end)
						v->viewport_width[input_idx] = viewport_end
							- pipe->bottom_pipe->plane_res.scl_data.viewport.x;
					अन्यथा
						v->viewport_width[input_idx] = viewport_b_end
									- pipe->plane_res.scl_data.viewport.x;
				पूर्ण अन्यथा  अणु
					पूर्णांक viewport_end = pipe->plane_res.scl_data.viewport.height
						+ pipe->plane_res.scl_data.viewport.y;
					पूर्णांक viewport_b_end = pipe->bottom_pipe->plane_res.scl_data.viewport.height
						+ pipe->bottom_pipe->plane_res.scl_data.viewport.y;

					अगर (viewport_end > viewport_b_end)
						v->viewport_height[input_idx] = viewport_end
							- pipe->bottom_pipe->plane_res.scl_data.viewport.y;
					अन्यथा
						v->viewport_height[input_idx] = viewport_b_end
									- pipe->plane_res.scl_data.viewport.y;
				पूर्ण
				v->scaler_rec_out_width[input_idx] = pipe->plane_res.scl_data.recout.width
						+ pipe->bottom_pipe->plane_res.scl_data.recout.width;
			पूर्ण

			अगर (pipe->plane_state->rotation % 2 == 0) अणु
				ASSERT(pipe->plane_res.scl_data.ratios.horz.value != dc_fixpt_one.value
					|| v->scaler_rec_out_width[input_idx] == v->viewport_width[input_idx]);
				ASSERT(pipe->plane_res.scl_data.ratios.vert.value != dc_fixpt_one.value
					|| v->scaler_recout_height[input_idx] == v->viewport_height[input_idx]);
			पूर्ण अन्यथा अणु
				ASSERT(pipe->plane_res.scl_data.ratios.horz.value != dc_fixpt_one.value
					|| v->scaler_recout_height[input_idx] == v->viewport_width[input_idx]);
				ASSERT(pipe->plane_res.scl_data.ratios.vert.value != dc_fixpt_one.value
					|| v->scaler_rec_out_width[input_idx] == v->viewport_height[input_idx]);
			पूर्ण

			अगर (dc->debug.optimized_watermark) अणु
				/*
				 * this method requires us to always re-calculate watermark when dcc change
				 * between flip.
				 */
				v->dcc_enable[input_idx] = pipe->plane_state->dcc.enable ? dcn_bw_yes : dcn_bw_no;
			पूर्ण अन्यथा अणु
				/*
				 * allow us to disable dcc on the fly without re-calculating WM
				 *
				 * extra overhead क्रम DCC is quite small.  क्रम 1080p WM without
				 * DCC is only 0.417us lower (urgent goes from 6.979us to 6.562us)
				 */
				अचिन्हित पूर्णांक bpe;

				v->dcc_enable[input_idx] = dc->res_pool->hubbub->funcs->dcc_support_pixel_क्रमmat(
						pipe->plane_state->क्रमmat, &bpe) ? dcn_bw_yes : dcn_bw_no;
			पूर्ण

			v->source_pixel_क्रमmat[input_idx] = tl_pixel_क्रमmat_to_bw_defs(
					pipe->plane_state->क्रमmat);
			v->source_surface_mode[input_idx] = tl_sw_mode_to_bw_defs(
					pipe->plane_state->tiling_info.gfx9.swizzle);
			v->lb_bit_per_pixel[input_idx] = tl_lb_bpp_to_पूर्णांक(pipe->plane_res.scl_data.lb_params.depth);
			v->override_hta_ps[input_idx] = pipe->plane_res.scl_data.taps.h_taps;
			v->override_vta_ps[input_idx] = pipe->plane_res.scl_data.taps.v_taps;
			v->override_hta_pschroma[input_idx] = pipe->plane_res.scl_data.taps.h_taps_c;
			v->override_vta_pschroma[input_idx] = pipe->plane_res.scl_data.taps.v_taps_c;
			/*
			 * Spपढ़ोsheet करोesn't handle taps_c is one properly,
			 * need to क्रमce Chroma to always be scaled to pass
			 * bandwidth validation.
			 */
			अगर (v->override_hta_pschroma[input_idx] == 1)
				v->override_hta_pschroma[input_idx] = 2;
			अगर (v->override_vta_pschroma[input_idx] == 1)
				v->override_vta_pschroma[input_idx] = 2;
			v->source_scan[input_idx] = (pipe->plane_state->rotation % 2) ? dcn_bw_vert : dcn_bw_hor;
		पूर्ण
		अगर (v->is_line_buffer_bpp_fixed == dcn_bw_yes)
			v->lb_bit_per_pixel[input_idx] = v->line_buffer_fixed_bpp;
		v->dcc_rate[input_idx] = 1; /*TODO: Worst हाल? करोes this change?*/
		v->output_क्रमmat[input_idx] = pipe->stream->timing.pixel_encoding ==
				PIXEL_ENCODING_YCBCR420 ? dcn_bw_420 : dcn_bw_444;
		v->output[input_idx] = pipe->stream->संकेत ==
				SIGNAL_TYPE_HDMI_TYPE_A ? dcn_bw_hdmi : dcn_bw_dp;
		v->output_deep_color[input_idx] = dcn_bw_encoder_8bpc;
		अगर (v->output[input_idx] == dcn_bw_hdmi) अणु
			चयन (pipe->stream->timing.display_color_depth) अणु
			हाल COLOR_DEPTH_101010:
				v->output_deep_color[input_idx] = dcn_bw_encoder_10bpc;
				अवरोध;
			हाल COLOR_DEPTH_121212:
				v->output_deep_color[input_idx]  = dcn_bw_encoder_12bpc;
				अवरोध;
			हाल COLOR_DEPTH_161616:
				v->output_deep_color[input_idx]  = dcn_bw_encoder_16bpc;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण

		input_idx++;
	पूर्ण
	v->number_of_active_planes = input_idx;

	scaler_settings_calculation(v);

	hack_bounding_box(v, &dc->debug, context);

	mode_support_and_प्रणाली_configuration(v);

	/* Unhack dppclk: करोnt bother with trying to pipe split अगर we cannot मुख्यtain dpm0 */
	अगर (v->voltage_level != 0
			&& context->stream_count == 1
			&& dc->debug.क्रमce_single_disp_pipe_split) अणु
		v->max_dppclk[0] = v->max_dppclk_vmin0p65;
		mode_support_and_प्रणाली_configuration(v);
	पूर्ण

	अगर (v->voltage_level == 0 &&
			(dc->debug.sr_निकास_समय_dpm0_ns
				|| dc->debug.sr_enter_plus_निकास_समय_dpm0_ns)) अणु

		अगर (dc->debug.sr_enter_plus_निकास_समय_dpm0_ns)
			v->sr_enter_plus_निकास_समय =
				dc->debug.sr_enter_plus_निकास_समय_dpm0_ns / 1000.0f;
		अगर (dc->debug.sr_निकास_समय_dpm0_ns)
			v->sr_निकास_समय =  dc->debug.sr_निकास_समय_dpm0_ns / 1000.0f;
		context->bw_ctx.dml.soc.sr_enter_plus_निकास_समय_us = v->sr_enter_plus_निकास_समय;
		context->bw_ctx.dml.soc.sr_निकास_समय_us = v->sr_निकास_समय;
		mode_support_and_प्रणाली_configuration(v);
	पूर्ण

	display_pipe_configuration(v);

	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर (v->source_scan[k] == dcn_bw_hor)
			v->swath_width_y[k] = v->viewport_width[k] / v->dpp_per_plane[k];
		अन्यथा
			v->swath_width_y[k] = v->viewport_height[k] / v->dpp_per_plane[k];
	पूर्ण
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर (v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_64) अणु
			v->byte_per_pixel_dety[k] = 8.0;
			v->byte_per_pixel_detc[k] = 0.0;
		पूर्ण अन्यथा अगर (v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_32) अणु
			v->byte_per_pixel_dety[k] = 4.0;
			v->byte_per_pixel_detc[k] = 0.0;
		पूर्ण अन्यथा अगर (v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_16) अणु
			v->byte_per_pixel_dety[k] = 2.0;
			v->byte_per_pixel_detc[k] = 0.0;
		पूर्ण अन्यथा अगर (v->source_pixel_क्रमmat[k] == dcn_bw_yuv420_sub_8) अणु
			v->byte_per_pixel_dety[k] = 1.0;
			v->byte_per_pixel_detc[k] = 2.0;
		पूर्ण अन्यथा अणु
			v->byte_per_pixel_dety[k] = 4.0f / 3.0f;
			v->byte_per_pixel_detc[k] = 8.0f / 3.0f;
		पूर्ण
	पूर्ण

	v->total_data_पढ़ो_bandwidth = 0.0;
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		v->पढ़ो_bandwidth_plane_luma[k] = v->swath_width_y[k] * v->dpp_per_plane[k] *
				dcn_bw_उच्चमान2(v->byte_per_pixel_dety[k], 1.0) / (v->htotal[k] / v->pixel_घड़ी[k]) * v->v_ratio[k];
		v->पढ़ो_bandwidth_plane_chroma[k] = v->swath_width_y[k] / 2.0 * v->dpp_per_plane[k] *
				dcn_bw_उच्चमान2(v->byte_per_pixel_detc[k], 2.0) / (v->htotal[k] / v->pixel_घड़ी[k]) * v->v_ratio[k] / 2.0;
		v->total_data_पढ़ो_bandwidth = v->total_data_पढ़ो_bandwidth +
				v->पढ़ो_bandwidth_plane_luma[k] + v->पढ़ो_bandwidth_plane_chroma[k];
	पूर्ण

	BW_VAL_TRACE_END_VOLTAGE_LEVEL();

	अगर (v->voltage_level != number_of_states_plus_one && !fast_validate) अणु
		भग्न bw_consumed = v->total_bandwidth_consumed_gbyte_per_second;

		अगर (bw_consumed < v->fabric_and_dram_bandwidth_vmin0p65)
			bw_consumed = v->fabric_and_dram_bandwidth_vmin0p65;
		अन्यथा अगर (bw_consumed < v->fabric_and_dram_bandwidth_vmid0p72)
			bw_consumed = v->fabric_and_dram_bandwidth_vmid0p72;
		अन्यथा अगर (bw_consumed < v->fabric_and_dram_bandwidth_vnom0p8)
			bw_consumed = v->fabric_and_dram_bandwidth_vnom0p8;
		अन्यथा
			bw_consumed = v->fabric_and_dram_bandwidth_vmax0p9;

		अगर (bw_consumed < v->fabric_and_dram_bandwidth)
			अगर (dc->debug.voltage_align_fclk)
				bw_consumed = v->fabric_and_dram_bandwidth;

		display_pipe_configuration(v);
		/*calc_wm_sets_and_perf_params(context, v);*/
		/* Only 1 set is used by dcn since no noticeable
		 * perक्रमmance improvement was measured and due to hw bug DEGVIDCN10-254
		 */
		dispclkdppclkdcfclk_deep_sleep_prefetch_parameters_watermarks_and_perक्रमmance_calculation(v);

		context->bw_ctx.bw.dcn.watermarks.a.cstate_pstate.cstate_निकास_ns =
			v->stutter_निकास_watermark * 1000;
		context->bw_ctx.bw.dcn.watermarks.a.cstate_pstate.cstate_enter_plus_निकास_ns =
				v->stutter_enter_plus_निकास_watermark * 1000;
		context->bw_ctx.bw.dcn.watermarks.a.cstate_pstate.pstate_change_ns =
				v->dram_घड़ी_change_watermark * 1000;
		context->bw_ctx.bw.dcn.watermarks.a.pte_meta_urgent_ns = v->ptemeta_urgent_watermark * 1000;
		context->bw_ctx.bw.dcn.watermarks.a.urgent_ns = v->urgent_watermark * 1000;
		context->bw_ctx.bw.dcn.watermarks.b = context->bw_ctx.bw.dcn.watermarks.a;
		context->bw_ctx.bw.dcn.watermarks.c = context->bw_ctx.bw.dcn.watermarks.a;
		context->bw_ctx.bw.dcn.watermarks.d = context->bw_ctx.bw.dcn.watermarks.a;

		context->bw_ctx.bw.dcn.clk.fclk_khz = (पूर्णांक)(bw_consumed * 1000000 /
				(ddr4_dram_factor_single_Channel * v->number_of_channels));
		अगर (bw_consumed == v->fabric_and_dram_bandwidth_vmin0p65)
			context->bw_ctx.bw.dcn.clk.fclk_khz = (पूर्णांक)(bw_consumed * 1000000 / 32);

		context->bw_ctx.bw.dcn.clk.dcfclk_deep_sleep_khz = (पूर्णांक)(v->dcf_clk_deep_sleep * 1000);
		context->bw_ctx.bw.dcn.clk.dcfclk_khz = (पूर्णांक)(v->dcfclk * 1000);

		context->bw_ctx.bw.dcn.clk.dispclk_khz = (पूर्णांक)(v->dispclk * 1000);
		अगर (dc->debug.max_disp_clk == true)
			context->bw_ctx.bw.dcn.clk.dispclk_khz = (पूर्णांक)(dc->dcn_soc->max_dispclk_vmax0p9 * 1000);

		अगर (context->bw_ctx.bw.dcn.clk.dispclk_khz <
				dc->debug.min_disp_clk_khz) अणु
			context->bw_ctx.bw.dcn.clk.dispclk_khz =
					dc->debug.min_disp_clk_khz;
		पूर्ण

		context->bw_ctx.bw.dcn.clk.dppclk_khz = context->bw_ctx.bw.dcn.clk.dispclk_khz /
				v->dispclk_dppclk_ratio;
		context->bw_ctx.bw.dcn.clk.phyclk_khz = v->phyclk_per_state[v->voltage_level];
		चयन (v->voltage_level) अणु
		हाल 0:
			context->bw_ctx.bw.dcn.clk.max_supported_dppclk_khz =
					(पूर्णांक)(dc->dcn_soc->max_dppclk_vmin0p65 * 1000);
			अवरोध;
		हाल 1:
			context->bw_ctx.bw.dcn.clk.max_supported_dppclk_khz =
					(पूर्णांक)(dc->dcn_soc->max_dppclk_vmid0p72 * 1000);
			अवरोध;
		हाल 2:
			context->bw_ctx.bw.dcn.clk.max_supported_dppclk_khz =
					(पूर्णांक)(dc->dcn_soc->max_dppclk_vnom0p8 * 1000);
			अवरोध;
		शेष:
			context->bw_ctx.bw.dcn.clk.max_supported_dppclk_khz =
					(पूर्णांक)(dc->dcn_soc->max_dppclk_vmax0p9 * 1000);
			अवरोध;
		पूर्ण

		BW_VAL_TRACE_END_WATERMARKS();

		क्रम (i = 0, input_idx = 0; i < pool->pipe_count; i++) अणु
			काष्ठा pipe_ctx *pipe = &context->res_ctx.pipe_ctx[i];

			/* skip inactive pipe */
			अगर (!pipe->stream)
				जारी;
			/* skip all but first of split pipes */
			अगर (pipe->top_pipe && pipe->top_pipe->plane_state == pipe->plane_state)
				जारी;

			pipe->pipe_dlg_param.vupdate_width = v->v_update_width_pix[input_idx];
			pipe->pipe_dlg_param.vupdate_offset = v->v_update_offset_pix[input_idx];
			pipe->pipe_dlg_param.vपढ़ोy_offset = v->v_पढ़ोy_offset_pix[input_idx];
			pipe->pipe_dlg_param.vstartup_start = v->v_startup[input_idx];

			pipe->pipe_dlg_param.htotal = pipe->stream->timing.h_total;
			pipe->pipe_dlg_param.vtotal = pipe->stream->timing.v_total;
			vesa_sync_start = pipe->stream->timing.v_addressable +
						pipe->stream->timing.v_border_bottom +
						pipe->stream->timing.v_front_porch;

			asic_blank_end = (pipe->stream->timing.v_total -
						vesa_sync_start -
						pipe->stream->timing.v_border_top)
			* (pipe->stream->timing.flags.INTERLACE ? 1 : 0);

			asic_blank_start = asic_blank_end +
						(pipe->stream->timing.v_border_top +
						pipe->stream->timing.v_addressable +
						pipe->stream->timing.v_border_bottom)
			* (pipe->stream->timing.flags.INTERLACE ? 1 : 0);

			pipe->pipe_dlg_param.vblank_start = asic_blank_start;
			pipe->pipe_dlg_param.vblank_end = asic_blank_end;

			अगर (pipe->plane_state) अणु
				काष्ठा pipe_ctx *hsplit_pipe = pipe->bottom_pipe;

				pipe->plane_state->update_flags.bits.full_update = 1;

				अगर (v->dpp_per_plane[input_idx] == 2 ||
					((pipe->stream->view_क्रमmat ==
					  VIEW_3D_FORMAT_SIDE_BY_SIDE ||
					  pipe->stream->view_क्रमmat ==
					  VIEW_3D_FORMAT_TOP_AND_BOTTOM) &&
					(pipe->stream->timing.timing_3d_क्रमmat ==
					 TIMING_3D_FORMAT_TOP_AND_BOTTOM ||
					 pipe->stream->timing.timing_3d_क्रमmat ==
					 TIMING_3D_FORMAT_SIDE_BY_SIDE))) अणु
					अगर (hsplit_pipe && hsplit_pipe->plane_state == pipe->plane_state) अणु
						/* update previously split pipe */
						hsplit_pipe->pipe_dlg_param.vupdate_width = v->v_update_width_pix[input_idx];
						hsplit_pipe->pipe_dlg_param.vupdate_offset = v->v_update_offset_pix[input_idx];
						hsplit_pipe->pipe_dlg_param.vपढ़ोy_offset = v->v_पढ़ोy_offset_pix[input_idx];
						hsplit_pipe->pipe_dlg_param.vstartup_start = v->v_startup[input_idx];

						hsplit_pipe->pipe_dlg_param.htotal = pipe->stream->timing.h_total;
						hsplit_pipe->pipe_dlg_param.vtotal = pipe->stream->timing.v_total;
						hsplit_pipe->pipe_dlg_param.vblank_start = pipe->pipe_dlg_param.vblank_start;
						hsplit_pipe->pipe_dlg_param.vblank_end = pipe->pipe_dlg_param.vblank_end;
					पूर्ण अन्यथा अणु
						/* pipe not split previously needs split */
						hsplit_pipe = find_idle_secondary_pipe(&context->res_ctx, pool, pipe);
						ASSERT(hsplit_pipe);
						split_stream_across_pipes(&context->res_ctx, pool, pipe, hsplit_pipe);
					पूर्ण

					dcn_bw_calc_rq_dlg_ttu(dc, v, hsplit_pipe, input_idx);
				पूर्ण अन्यथा अगर (hsplit_pipe && hsplit_pipe->plane_state == pipe->plane_state) अणु
					/* merge previously split pipe */
					pipe->bottom_pipe = hsplit_pipe->bottom_pipe;
					अगर (hsplit_pipe->bottom_pipe)
						hsplit_pipe->bottom_pipe->top_pipe = pipe;
					hsplit_pipe->plane_state = शून्य;
					hsplit_pipe->stream = शून्य;
					hsplit_pipe->top_pipe = शून्य;
					hsplit_pipe->bottom_pipe = शून्य;
					/* Clear plane_res and stream_res */
					स_रखो(&hsplit_pipe->plane_res, 0, माप(hsplit_pipe->plane_res));
					स_रखो(&hsplit_pipe->stream_res, 0, माप(hsplit_pipe->stream_res));
					resource_build_scaling_params(pipe);
				पूर्ण
				/* क्रम now important to करो this after pipe split क्रम building e2e params */
				dcn_bw_calc_rq_dlg_ttu(dc, v, pipe, input_idx);
			पूर्ण

			input_idx++;
		पूर्ण
	पूर्ण अन्यथा अगर (v->voltage_level == number_of_states_plus_one) अणु
		BW_VAL_TRACE_SKIP(fail);
	पूर्ण अन्यथा अगर (fast_validate) अणु
		BW_VAL_TRACE_SKIP(fast);
	पूर्ण

	अगर (v->voltage_level == 0) अणु
		context->bw_ctx.dml.soc.sr_enter_plus_निकास_समय_us =
				dc->dcn_soc->sr_enter_plus_निकास_समय;
		context->bw_ctx.dml.soc.sr_निकास_समय_us = dc->dcn_soc->sr_निकास_समय;
	पूर्ण

	/*
	 * BW limit is set to prevent display from impacting other प्रणाली functions
	 */

	bw_limit = dc->dcn_soc->percent_disp_bw_limit * v->fabric_and_dram_bandwidth_vmax0p9;
	bw_limit_pass = (v->total_data_पढ़ो_bandwidth / 1000.0) < bw_limit;

	DC_FP_END();

	PERFORMANCE_TRACE_END();
	BW_VAL_TRACE_FINISH();

	अगर (bw_limit_pass && v->voltage_level <= get_highest_allowed_voltage_level(
							dc->ctx->asic_id.chip_family,
							dc->ctx->asic_id.hw_पूर्णांकernal_rev,
							dc->ctx->asic_id.pci_revision_id))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल अचिन्हित पूर्णांक dcn_find_normalized_घड़ी_vdd_Level(
	स्थिर काष्ठा dc *dc,
	क्रमागत dm_pp_घड़ी_प्रकारype घड़ीs_type,
	पूर्णांक घड़ीs_in_khz)
अणु
	पूर्णांक vdd_level = dcn_bw_v_min0p65;

	अगर (घड़ीs_in_khz == 0)/*toकरो some घड़ी not in the considerations*/
		वापस vdd_level;

	चयन (घड़ीs_type) अणु
	हाल DM_PP_CLOCK_TYPE_DISPLAY_CLK:
		अगर (घड़ीs_in_khz > dc->dcn_soc->max_dispclk_vmax0p9*1000) अणु
			vdd_level = dcn_bw_v_max0p91;
			BREAK_TO_DEBUGGER();
		पूर्ण अन्यथा अगर (घड़ीs_in_khz > dc->dcn_soc->max_dispclk_vnom0p8*1000) अणु
			vdd_level = dcn_bw_v_max0p9;
		पूर्ण अन्यथा अगर (घड़ीs_in_khz > dc->dcn_soc->max_dispclk_vmid0p72*1000) अणु
			vdd_level = dcn_bw_v_nom0p8;
		पूर्ण अन्यथा अगर (घड़ीs_in_khz > dc->dcn_soc->max_dispclk_vmin0p65*1000) अणु
			vdd_level = dcn_bw_v_mid0p72;
		पूर्ण अन्यथा
			vdd_level = dcn_bw_v_min0p65;
		अवरोध;
	हाल DM_PP_CLOCK_TYPE_DISPLAYPHYCLK:
		अगर (घड़ीs_in_khz > dc->dcn_soc->phyclkv_max0p9*1000) अणु
			vdd_level = dcn_bw_v_max0p91;
			BREAK_TO_DEBUGGER();
		पूर्ण अन्यथा अगर (घड़ीs_in_khz > dc->dcn_soc->phyclkv_nom0p8*1000) अणु
			vdd_level = dcn_bw_v_max0p9;
		पूर्ण अन्यथा अगर (घड़ीs_in_khz > dc->dcn_soc->phyclkv_mid0p72*1000) अणु
			vdd_level = dcn_bw_v_nom0p8;
		पूर्ण अन्यथा अगर (घड़ीs_in_khz > dc->dcn_soc->phyclkv_min0p65*1000) अणु
			vdd_level = dcn_bw_v_mid0p72;
		पूर्ण अन्यथा
			vdd_level = dcn_bw_v_min0p65;
		अवरोध;

	हाल DM_PP_CLOCK_TYPE_DPPCLK:
		अगर (घड़ीs_in_khz > dc->dcn_soc->max_dppclk_vmax0p9*1000) अणु
			vdd_level = dcn_bw_v_max0p91;
			BREAK_TO_DEBUGGER();
		पूर्ण अन्यथा अगर (घड़ीs_in_khz > dc->dcn_soc->max_dppclk_vnom0p8*1000) अणु
			vdd_level = dcn_bw_v_max0p9;
		पूर्ण अन्यथा अगर (घड़ीs_in_khz > dc->dcn_soc->max_dppclk_vmid0p72*1000) अणु
			vdd_level = dcn_bw_v_nom0p8;
		पूर्ण अन्यथा अगर (घड़ीs_in_khz > dc->dcn_soc->max_dppclk_vmin0p65*1000) अणु
			vdd_level = dcn_bw_v_mid0p72;
		पूर्ण अन्यथा
			vdd_level = dcn_bw_v_min0p65;
		अवरोध;

	हाल DM_PP_CLOCK_TYPE_MEMORY_CLK:
		अणु
			अचिन्हित factor = (ddr4_dram_factor_single_Channel * dc->dcn_soc->number_of_channels);

			अगर (घड़ीs_in_khz > dc->dcn_soc->fabric_and_dram_bandwidth_vmax0p9*1000000/factor) अणु
				vdd_level = dcn_bw_v_max0p91;
				BREAK_TO_DEBUGGER();
			पूर्ण अन्यथा अगर (घड़ीs_in_khz > dc->dcn_soc->fabric_and_dram_bandwidth_vnom0p8*1000000/factor) अणु
				vdd_level = dcn_bw_v_max0p9;
			पूर्ण अन्यथा अगर (घड़ीs_in_khz > dc->dcn_soc->fabric_and_dram_bandwidth_vmid0p72*1000000/factor) अणु
				vdd_level = dcn_bw_v_nom0p8;
			पूर्ण अन्यथा अगर (घड़ीs_in_khz > dc->dcn_soc->fabric_and_dram_bandwidth_vmin0p65*1000000/factor) अणु
				vdd_level = dcn_bw_v_mid0p72;
			पूर्ण अन्यथा
				vdd_level = dcn_bw_v_min0p65;
		पूर्ण
		अवरोध;

	हाल DM_PP_CLOCK_TYPE_DCFCLK:
		अगर (घड़ीs_in_khz > dc->dcn_soc->dcfclkv_max0p9*1000) अणु
			vdd_level = dcn_bw_v_max0p91;
			BREAK_TO_DEBUGGER();
		पूर्ण अन्यथा अगर (घड़ीs_in_khz > dc->dcn_soc->dcfclkv_nom0p8*1000) अणु
			vdd_level = dcn_bw_v_max0p9;
		पूर्ण अन्यथा अगर (घड़ीs_in_khz > dc->dcn_soc->dcfclkv_mid0p72*1000) अणु
			vdd_level = dcn_bw_v_nom0p8;
		पूर्ण अन्यथा अगर (घड़ीs_in_khz > dc->dcn_soc->dcfclkv_min0p65*1000) अणु
			vdd_level = dcn_bw_v_mid0p72;
		पूर्ण अन्यथा
			vdd_level = dcn_bw_v_min0p65;
		अवरोध;

	शेष:
		 अवरोध;
	पूर्ण
	वापस vdd_level;
पूर्ण

अचिन्हित पूर्णांक dcn_find_dcfclk_suits_all(
	स्थिर काष्ठा dc *dc,
	काष्ठा dc_घड़ीs *घड़ीs)
अणु
	अचिन्हित vdd_level, vdd_level_temp;
	अचिन्हित dcf_clk;

	/*find a common supported voltage level*/
	vdd_level = dcn_find_normalized_घड़ी_vdd_Level(
		dc, DM_PP_CLOCK_TYPE_DISPLAY_CLK, घड़ीs->dispclk_khz);
	vdd_level_temp = dcn_find_normalized_घड़ी_vdd_Level(
		dc, DM_PP_CLOCK_TYPE_DISPLAYPHYCLK, घड़ीs->phyclk_khz);

	vdd_level = dcn_bw_max(vdd_level, vdd_level_temp);
	vdd_level_temp = dcn_find_normalized_घड़ी_vdd_Level(
		dc, DM_PP_CLOCK_TYPE_DPPCLK, घड़ीs->dppclk_khz);
	vdd_level = dcn_bw_max(vdd_level, vdd_level_temp);

	vdd_level_temp = dcn_find_normalized_घड़ी_vdd_Level(
		dc, DM_PP_CLOCK_TYPE_MEMORY_CLK, घड़ीs->fclk_khz);
	vdd_level = dcn_bw_max(vdd_level, vdd_level_temp);
	vdd_level_temp = dcn_find_normalized_घड़ी_vdd_Level(
		dc, DM_PP_CLOCK_TYPE_DCFCLK, घड़ीs->dcfclk_khz);

	/*find that level conresponding dcfclk*/
	vdd_level = dcn_bw_max(vdd_level, vdd_level_temp);
	अगर (vdd_level == dcn_bw_v_max0p91) अणु
		BREAK_TO_DEBUGGER();
		dcf_clk = dc->dcn_soc->dcfclkv_max0p9*1000;
	पूर्ण अन्यथा अगर (vdd_level == dcn_bw_v_max0p9)
		dcf_clk =  dc->dcn_soc->dcfclkv_max0p9*1000;
	अन्यथा अगर (vdd_level == dcn_bw_v_nom0p8)
		dcf_clk =  dc->dcn_soc->dcfclkv_nom0p8*1000;
	अन्यथा अगर (vdd_level == dcn_bw_v_mid0p72)
		dcf_clk =  dc->dcn_soc->dcfclkv_mid0p72*1000;
	अन्यथा
		dcf_clk =  dc->dcn_soc->dcfclkv_min0p65*1000;

	DC_LOG_BANDWIDTH_CALCS("\tdcf_clk for voltage = %d\n", dcf_clk);
	वापस dcf_clk;
पूर्ण

अटल bool verअगरy_घड़ी_values(काष्ठा dm_pp_घड़ी_levels_with_voltage *clks)
अणु
	पूर्णांक i;

	अगर (clks->num_levels == 0)
		वापस false;

	क्रम (i = 0; i < clks->num_levels; i++)
		/* Ensure that the result is sane */
		अगर (clks->data[i].घड़ीs_in_khz == 0)
			वापस false;

	वापस true;
पूर्ण

व्योम dcn_bw_update_from_pplib(काष्ठा dc *dc)
अणु
	काष्ठा dc_context *ctx = dc->ctx;
	काष्ठा dm_pp_घड़ी_levels_with_voltage fclks = अणु0पूर्ण, dcfclks = अणु0पूर्ण;
	bool res;
	अचिन्हित vmin0p65_idx, vmid0p72_idx, vnom0p8_idx, vmax0p9_idx;

	/* TODO: This is not the proper way to obtain fabric_and_dram_bandwidth, should be min(fclk, memclk) */
	res = dm_pp_get_घड़ी_levels_by_type_with_voltage(
			ctx, DM_PP_CLOCK_TYPE_FCLK, &fclks);

	DC_FP_START();

	अगर (res)
		res = verअगरy_घड़ी_values(&fclks);

	अगर (res) अणु
		ASSERT(fclks.num_levels);

		vmin0p65_idx = 0;
		vmid0p72_idx = fclks.num_levels -
			(fclks.num_levels > 2 ? 3 : (fclks.num_levels > 1 ? 2 : 1));
		vnom0p8_idx = fclks.num_levels - (fclks.num_levels > 1 ? 2 : 1);
		vmax0p9_idx = fclks.num_levels - 1;

		dc->dcn_soc->fabric_and_dram_bandwidth_vmin0p65 =
			32 * (fclks.data[vmin0p65_idx].घड़ीs_in_khz / 1000.0) / 1000.0;
		dc->dcn_soc->fabric_and_dram_bandwidth_vmid0p72 =
			dc->dcn_soc->number_of_channels *
			(fclks.data[vmid0p72_idx].घड़ीs_in_khz / 1000.0)
			* ddr4_dram_factor_single_Channel / 1000.0;
		dc->dcn_soc->fabric_and_dram_bandwidth_vnom0p8 =
			dc->dcn_soc->number_of_channels *
			(fclks.data[vnom0p8_idx].घड़ीs_in_khz / 1000.0)
			* ddr4_dram_factor_single_Channel / 1000.0;
		dc->dcn_soc->fabric_and_dram_bandwidth_vmax0p9 =
			dc->dcn_soc->number_of_channels *
			(fclks.data[vmax0p9_idx].घड़ीs_in_khz / 1000.0)
			* ddr4_dram_factor_single_Channel / 1000.0;
	पूर्ण अन्यथा
		BREAK_TO_DEBUGGER();

	DC_FP_END();

	res = dm_pp_get_घड़ी_levels_by_type_with_voltage(
			ctx, DM_PP_CLOCK_TYPE_DCFCLK, &dcfclks);

	DC_FP_START();

	अगर (res)
		res = verअगरy_घड़ी_values(&dcfclks);

	अगर (res && dcfclks.num_levels >= 3) अणु
		dc->dcn_soc->dcfclkv_min0p65 = dcfclks.data[0].घड़ीs_in_khz / 1000.0;
		dc->dcn_soc->dcfclkv_mid0p72 = dcfclks.data[dcfclks.num_levels - 3].घड़ीs_in_khz / 1000.0;
		dc->dcn_soc->dcfclkv_nom0p8 = dcfclks.data[dcfclks.num_levels - 2].घड़ीs_in_khz / 1000.0;
		dc->dcn_soc->dcfclkv_max0p9 = dcfclks.data[dcfclks.num_levels - 1].घड़ीs_in_khz / 1000.0;
	पूर्ण अन्यथा
		BREAK_TO_DEBUGGER();

	DC_FP_END();
पूर्ण

व्योम dcn_bw_notअगरy_pplib_of_wm_ranges(काष्ठा dc *dc)
अणु
	काष्ठा pp_smu_funcs_rv *pp = शून्य;
	काष्ठा pp_smu_wm_range_sets ranges = अणु0पूर्ण;
	पूर्णांक min_fclk_khz, min_dcfclk_khz, socclk_khz;
	स्थिर पूर्णांक overdrive = 5000000; /* 5 GHz to cover Overdrive */

	अगर (dc->res_pool->pp_smu)
		pp = &dc->res_pool->pp_smu->rv_funcs;
	अगर (!pp || !pp->set_wm_ranges)
		वापस;

	DC_FP_START();
	min_fclk_khz = dc->dcn_soc->fabric_and_dram_bandwidth_vmin0p65 * 1000000 / 32;
	min_dcfclk_khz = dc->dcn_soc->dcfclkv_min0p65 * 1000;
	socclk_khz = dc->dcn_soc->socclk * 1000;
	DC_FP_END();

	/* Now notअगरy PPLib/SMU about which Watermarks sets they should select
	 * depending on DPM state they are in. And update BW MGR GFX Engine and
	 * Memory घड़ी member variables क्रम Watermarks calculations क्रम each
	 * Watermark Set. Only one watermark set क्रम dcn1 due to hw bug DEGVIDCN10-254.
	 */
	/* SOCCLK करोes not affect anytihng but ग_लिखोback क्रम DCN so क्रम now we करोnt
	 * care what the value is, hence min to overdrive level
	 */
	ranges.num_पढ़ोer_wm_sets = WM_SET_COUNT;
	ranges.num_ग_लिखोr_wm_sets = WM_SET_COUNT;
	ranges.पढ़ोer_wm_sets[0].wm_inst = WM_A;
	ranges.पढ़ोer_wm_sets[0].min_drain_clk_mhz = min_dcfclk_khz / 1000;
	ranges.पढ़ोer_wm_sets[0].max_drain_clk_mhz = overdrive / 1000;
	ranges.पढ़ोer_wm_sets[0].min_fill_clk_mhz = min_fclk_khz / 1000;
	ranges.पढ़ोer_wm_sets[0].max_fill_clk_mhz = overdrive / 1000;
	ranges.ग_लिखोr_wm_sets[0].wm_inst = WM_A;
	ranges.ग_लिखोr_wm_sets[0].min_fill_clk_mhz = socclk_khz / 1000;
	ranges.ग_लिखोr_wm_sets[0].max_fill_clk_mhz = overdrive / 1000;
	ranges.ग_लिखोr_wm_sets[0].min_drain_clk_mhz = min_fclk_khz / 1000;
	ranges.ग_लिखोr_wm_sets[0].max_drain_clk_mhz = overdrive / 1000;

	अगर (dc->debug.pplib_wm_report_mode == WM_REPORT_OVERRIDE) अणु
		ranges.पढ़ोer_wm_sets[0].wm_inst = WM_A;
		ranges.पढ़ोer_wm_sets[0].min_drain_clk_mhz = 300;
		ranges.पढ़ोer_wm_sets[0].max_drain_clk_mhz = 5000;
		ranges.पढ़ोer_wm_sets[0].min_fill_clk_mhz = 800;
		ranges.पढ़ोer_wm_sets[0].max_fill_clk_mhz = 5000;
		ranges.ग_लिखोr_wm_sets[0].wm_inst = WM_A;
		ranges.ग_लिखोr_wm_sets[0].min_fill_clk_mhz = 200;
		ranges.ग_लिखोr_wm_sets[0].max_fill_clk_mhz = 5000;
		ranges.ग_लिखोr_wm_sets[0].min_drain_clk_mhz = 800;
		ranges.ग_लिखोr_wm_sets[0].max_drain_clk_mhz = 5000;
	पूर्ण

	ranges.पढ़ोer_wm_sets[1] = ranges.ग_लिखोr_wm_sets[0];
	ranges.पढ़ोer_wm_sets[1].wm_inst = WM_B;

	ranges.पढ़ोer_wm_sets[2] = ranges.ग_लिखोr_wm_sets[0];
	ranges.पढ़ोer_wm_sets[2].wm_inst = WM_C;

	ranges.पढ़ोer_wm_sets[3] = ranges.ग_लिखोr_wm_sets[0];
	ranges.पढ़ोer_wm_sets[3].wm_inst = WM_D;

	/* Notअगरy PP Lib/SMU which Watermarks to use क्रम which घड़ी ranges */
	pp->set_wm_ranges(&pp->pp_smu, &ranges);
पूर्ण

व्योम dcn_bw_sync_calcs_and_dml(काष्ठा dc *dc)
अणु
	DC_FP_START();
	DC_LOG_BANDWIDTH_CALCS("sr_exit_time: %f ns\n"
			"sr_enter_plus_exit_time: %f ns\n"
			"urgent_latency: %f ns\n"
			"write_back_latency: %f ns\n"
			"percent_of_ideal_drambw_received_after_urg_latency: %f %%\n"
			"max_request_size: %d bytes\n"
			"dcfclkv_max0p9: %f kHz\n"
			"dcfclkv_nom0p8: %f kHz\n"
			"dcfclkv_mid0p72: %f kHz\n"
			"dcfclkv_min0p65: %f kHz\n"
			"max_dispclk_vmax0p9: %f kHz\n"
			"max_dispclk_vnom0p8: %f kHz\n"
			"max_dispclk_vmid0p72: %f kHz\n"
			"max_dispclk_vmin0p65: %f kHz\n"
			"max_dppclk_vmax0p9: %f kHz\n"
			"max_dppclk_vnom0p8: %f kHz\n"
			"max_dppclk_vmid0p72: %f kHz\n"
			"max_dppclk_vmin0p65: %f kHz\n"
			"socclk: %f kHz\n"
			"fabric_and_dram_bandwidth_vmax0p9: %f MB/s\n"
			"fabric_and_dram_bandwidth_vnom0p8: %f MB/s\n"
			"fabric_and_dram_bandwidth_vmid0p72: %f MB/s\n"
			"fabric_and_dram_bandwidth_vmin0p65: %f MB/s\n"
			"phyclkv_max0p9: %f kHz\n"
			"phyclkv_nom0p8: %f kHz\n"
			"phyclkv_mid0p72: %f kHz\n"
			"phyclkv_min0p65: %f kHz\n"
			"downspreading: %f %%\n"
			"round_trip_ping_latency_cycles: %d DCFCLK Cycles\n"
			"urgent_out_of_order_return_per_channel: %d Bytes\n"
			"number_of_channels: %d\n"
			"vmm_page_size: %d Bytes\n"
			"dram_clock_change_latency: %f ns\n"
			"return_bus_width: %d Bytes\n",
			dc->dcn_soc->sr_निकास_समय * 1000,
			dc->dcn_soc->sr_enter_plus_निकास_समय * 1000,
			dc->dcn_soc->urgent_latency * 1000,
			dc->dcn_soc->ग_लिखो_back_latency * 1000,
			dc->dcn_soc->percent_of_ideal_drambw_received_after_urg_latency,
			dc->dcn_soc->max_request_size,
			dc->dcn_soc->dcfclkv_max0p9 * 1000,
			dc->dcn_soc->dcfclkv_nom0p8 * 1000,
			dc->dcn_soc->dcfclkv_mid0p72 * 1000,
			dc->dcn_soc->dcfclkv_min0p65 * 1000,
			dc->dcn_soc->max_dispclk_vmax0p9 * 1000,
			dc->dcn_soc->max_dispclk_vnom0p8 * 1000,
			dc->dcn_soc->max_dispclk_vmid0p72 * 1000,
			dc->dcn_soc->max_dispclk_vmin0p65 * 1000,
			dc->dcn_soc->max_dppclk_vmax0p9 * 1000,
			dc->dcn_soc->max_dppclk_vnom0p8 * 1000,
			dc->dcn_soc->max_dppclk_vmid0p72 * 1000,
			dc->dcn_soc->max_dppclk_vmin0p65 * 1000,
			dc->dcn_soc->socclk * 1000,
			dc->dcn_soc->fabric_and_dram_bandwidth_vmax0p9 * 1000,
			dc->dcn_soc->fabric_and_dram_bandwidth_vnom0p8 * 1000,
			dc->dcn_soc->fabric_and_dram_bandwidth_vmid0p72 * 1000,
			dc->dcn_soc->fabric_and_dram_bandwidth_vmin0p65 * 1000,
			dc->dcn_soc->phyclkv_max0p9 * 1000,
			dc->dcn_soc->phyclkv_nom0p8 * 1000,
			dc->dcn_soc->phyclkv_mid0p72 * 1000,
			dc->dcn_soc->phyclkv_min0p65 * 1000,
			dc->dcn_soc->करोwnspपढ़ोing * 100,
			dc->dcn_soc->round_trip_ping_latency_cycles,
			dc->dcn_soc->urgent_out_of_order_वापस_per_channel,
			dc->dcn_soc->number_of_channels,
			dc->dcn_soc->vmm_page_size,
			dc->dcn_soc->dram_घड़ी_change_latency * 1000,
			dc->dcn_soc->वापस_bus_width);
	DC_LOG_BANDWIDTH_CALCS("rob_buffer_size_in_kbyte: %f\n"
			"det_buffer_size_in_kbyte: %f\n"
			"dpp_output_buffer_pixels: %f\n"
			"opp_output_buffer_lines: %f\n"
			"pixel_chunk_size_in_kbyte: %f\n"
			"pte_enable: %d\n"
			"pte_chunk_size: %d kbytes\n"
			"meta_chunk_size: %d kbytes\n"
			"writeback_chunk_size: %d kbytes\n"
			"odm_capability: %d\n"
			"dsc_capability: %d\n"
			"line_buffer_size: %d bits\n"
			"max_line_buffer_lines: %d\n"
			"is_line_buffer_bpp_fixed: %d\n"
			"line_buffer_fixed_bpp: %d\n"
			"writeback_luma_buffer_size: %d kbytes\n"
			"writeback_chroma_buffer_size: %d kbytes\n"
			"max_num_dpp: %d\n"
			"max_num_writeback: %d\n"
			"max_dchub_topscl_throughput: %d pixels/dppclk\n"
			"max_pscl_tolb_throughput: %d pixels/dppclk\n"
			"max_lb_tovscl_throughput: %d pixels/dppclk\n"
			"max_vscl_tohscl_throughput: %d pixels/dppclk\n"
			"max_hscl_ratio: %f\n"
			"max_vscl_ratio: %f\n"
			"max_hscl_taps: %d\n"
			"max_vscl_taps: %d\n"
			"pte_buffer_size_in_requests: %d\n"
			"dispclk_ramping_margin: %f %%\n"
			"under_scan_factor: %f %%\n"
			"max_inter_dcn_tile_repeaters: %d\n"
			"can_vstartup_lines_exceed_vsync_plus_back_porch_lines_minus_one: %d\n"
			"bug_forcing_luma_and_chroma_request_to_same_size_fixed: %d\n"
			"dcfclk_cstate_latency: %d\n",
			dc->dcn_ip->rob_buffer_size_in_kbyte,
			dc->dcn_ip->det_buffer_size_in_kbyte,
			dc->dcn_ip->dpp_output_buffer_pixels,
			dc->dcn_ip->opp_output_buffer_lines,
			dc->dcn_ip->pixel_chunk_size_in_kbyte,
			dc->dcn_ip->pte_enable,
			dc->dcn_ip->pte_chunk_size,
			dc->dcn_ip->meta_chunk_size,
			dc->dcn_ip->ग_लिखोback_chunk_size,
			dc->dcn_ip->odm_capability,
			dc->dcn_ip->dsc_capability,
			dc->dcn_ip->line_buffer_size,
			dc->dcn_ip->max_line_buffer_lines,
			dc->dcn_ip->is_line_buffer_bpp_fixed,
			dc->dcn_ip->line_buffer_fixed_bpp,
			dc->dcn_ip->ग_लिखोback_luma_buffer_size,
			dc->dcn_ip->ग_लिखोback_chroma_buffer_size,
			dc->dcn_ip->max_num_dpp,
			dc->dcn_ip->max_num_ग_लिखोback,
			dc->dcn_ip->max_dchub_topscl_throughput,
			dc->dcn_ip->max_pscl_tolb_throughput,
			dc->dcn_ip->max_lb_tovscl_throughput,
			dc->dcn_ip->max_vscl_tohscl_throughput,
			dc->dcn_ip->max_hscl_ratio,
			dc->dcn_ip->max_vscl_ratio,
			dc->dcn_ip->max_hscl_taps,
			dc->dcn_ip->max_vscl_taps,
			dc->dcn_ip->pte_buffer_size_in_requests,
			dc->dcn_ip->dispclk_ramping_margin,
			dc->dcn_ip->under_scan_factor * 100,
			dc->dcn_ip->max_पूर्णांकer_dcn_tile_repeaters,
			dc->dcn_ip->can_vstartup_lines_exceed_vsync_plus_back_porch_lines_minus_one,
			dc->dcn_ip->bug_क्रमcing_luma_and_chroma_request_to_same_size_fixed,
			dc->dcn_ip->dcfclk_cstate_latency);

	dc->dml.soc.sr_निकास_समय_us = dc->dcn_soc->sr_निकास_समय;
	dc->dml.soc.sr_enter_plus_निकास_समय_us = dc->dcn_soc->sr_enter_plus_निकास_समय;
	dc->dml.soc.urgent_latency_us = dc->dcn_soc->urgent_latency;
	dc->dml.soc.ग_लिखोback_latency_us = dc->dcn_soc->ग_लिखो_back_latency;
	dc->dml.soc.ideal_dram_bw_after_urgent_percent =
			dc->dcn_soc->percent_of_ideal_drambw_received_after_urg_latency;
	dc->dml.soc.max_request_size_bytes = dc->dcn_soc->max_request_size;
	dc->dml.soc.करोwnspपढ़ो_percent = dc->dcn_soc->करोwnspपढ़ोing;
	dc->dml.soc.round_trip_ping_latency_dcfclk_cycles =
			dc->dcn_soc->round_trip_ping_latency_cycles;
	dc->dml.soc.urgent_out_of_order_वापस_per_channel_bytes =
			dc->dcn_soc->urgent_out_of_order_वापस_per_channel;
	dc->dml.soc.num_chans = dc->dcn_soc->number_of_channels;
	dc->dml.soc.vmm_page_size_bytes = dc->dcn_soc->vmm_page_size;
	dc->dml.soc.dram_घड़ी_change_latency_us = dc->dcn_soc->dram_घड़ी_change_latency;
	dc->dml.soc.वापस_bus_width_bytes = dc->dcn_soc->वापस_bus_width;

	dc->dml.ip.rob_buffer_size_kbytes = dc->dcn_ip->rob_buffer_size_in_kbyte;
	dc->dml.ip.det_buffer_size_kbytes = dc->dcn_ip->det_buffer_size_in_kbyte;
	dc->dml.ip.dpp_output_buffer_pixels = dc->dcn_ip->dpp_output_buffer_pixels;
	dc->dml.ip.opp_output_buffer_lines = dc->dcn_ip->opp_output_buffer_lines;
	dc->dml.ip.pixel_chunk_size_kbytes = dc->dcn_ip->pixel_chunk_size_in_kbyte;
	dc->dml.ip.pte_enable = dc->dcn_ip->pte_enable == dcn_bw_yes;
	dc->dml.ip.pte_chunk_size_kbytes = dc->dcn_ip->pte_chunk_size;
	dc->dml.ip.meta_chunk_size_kbytes = dc->dcn_ip->meta_chunk_size;
	dc->dml.ip.ग_लिखोback_chunk_size_kbytes = dc->dcn_ip->ग_लिखोback_chunk_size;
	dc->dml.ip.line_buffer_size_bits = dc->dcn_ip->line_buffer_size;
	dc->dml.ip.max_line_buffer_lines = dc->dcn_ip->max_line_buffer_lines;
	dc->dml.ip.IsLineBufferBppFixed = dc->dcn_ip->is_line_buffer_bpp_fixed == dcn_bw_yes;
	dc->dml.ip.LineBufferFixedBpp = dc->dcn_ip->line_buffer_fixed_bpp;
	dc->dml.ip.ग_लिखोback_luma_buffer_size_kbytes = dc->dcn_ip->ग_लिखोback_luma_buffer_size;
	dc->dml.ip.ग_लिखोback_chroma_buffer_size_kbytes = dc->dcn_ip->ग_लिखोback_chroma_buffer_size;
	dc->dml.ip.max_num_dpp = dc->dcn_ip->max_num_dpp;
	dc->dml.ip.max_num_wb = dc->dcn_ip->max_num_ग_लिखोback;
	dc->dml.ip.max_dchub_pscl_bw_pix_per_clk = dc->dcn_ip->max_dchub_topscl_throughput;
	dc->dml.ip.max_pscl_lb_bw_pix_per_clk = dc->dcn_ip->max_pscl_tolb_throughput;
	dc->dml.ip.max_lb_vscl_bw_pix_per_clk = dc->dcn_ip->max_lb_tovscl_throughput;
	dc->dml.ip.max_vscl_hscl_bw_pix_per_clk = dc->dcn_ip->max_vscl_tohscl_throughput;
	dc->dml.ip.max_hscl_ratio = dc->dcn_ip->max_hscl_ratio;
	dc->dml.ip.max_vscl_ratio = dc->dcn_ip->max_vscl_ratio;
	dc->dml.ip.max_hscl_taps = dc->dcn_ip->max_hscl_taps;
	dc->dml.ip.max_vscl_taps = dc->dcn_ip->max_vscl_taps;
	/*pte_buffer_size_in_requests missing in dml*/
	dc->dml.ip.dispclk_ramp_margin_percent = dc->dcn_ip->dispclk_ramping_margin;
	dc->dml.ip.underscan_factor = dc->dcn_ip->under_scan_factor;
	dc->dml.ip.max_पूर्णांकer_dcn_tile_repeaters = dc->dcn_ip->max_पूर्णांकer_dcn_tile_repeaters;
	dc->dml.ip.can_vstartup_lines_exceed_vsync_plus_back_porch_lines_minus_one =
		dc->dcn_ip->can_vstartup_lines_exceed_vsync_plus_back_porch_lines_minus_one == dcn_bw_yes;
	dc->dml.ip.bug_क्रमcing_LC_req_same_size_fixed =
		dc->dcn_ip->bug_क्रमcing_luma_and_chroma_request_to_same_size_fixed == dcn_bw_yes;
	dc->dml.ip.dcfclk_cstate_latency = dc->dcn_ip->dcfclk_cstate_latency;
	DC_FP_END();
पूर्ण
