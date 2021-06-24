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

#अगर_अघोषित __DC_RESOURCE_DCN20_H__
#घोषणा __DC_RESOURCE_DCN20_H__

#समावेश "core_types.h"

#घोषणा TO_DCN20_RES_POOL(pool)\
	container_of(pool, काष्ठा dcn20_resource_pool, base)

काष्ठा dc;
काष्ठा resource_pool;
काष्ठा _vcs_dpi_display_pipe_params_st;

काष्ठा dcn20_resource_pool अणु
	काष्ठा resource_pool base;
पूर्ण;
काष्ठा resource_pool *dcn20_create_resource_pool(
		स्थिर काष्ठा dc_init_data *init_data,
		काष्ठा dc *dc);

काष्ठा link_encoder *dcn20_link_encoder_create(
	स्थिर काष्ठा encoder_init_data *enc_init_data);

अचिन्हित पूर्णांक dcn20_calc_max_scaled_समय(
		अचिन्हित पूर्णांक समय_per_pixel,
		क्रमागत mmhubbub_wbअगर_mode mode,
		अचिन्हित पूर्णांक urgent_watermark);
पूर्णांक dcn20_populate_dml_pipes_from_context(
		काष्ठा dc *dc,
		काष्ठा dc_state *context,
		display_e2e_pipe_params_st *pipes,
		bool fast_validate);
काष्ठा pipe_ctx *dcn20_acquire_idle_pipe_क्रम_layer(
		काष्ठा dc_state *state,
		स्थिर काष्ठा resource_pool *pool,
		काष्ठा dc_stream_state *stream);
व्योम dcn20_populate_dml_ग_लिखोback_from_context(
		काष्ठा dc *dc, काष्ठा resource_context *res_ctx, display_e2e_pipe_params_st *pipes);

काष्ठा stream_encoder *dcn20_stream_encoder_create(
	क्रमागत engine_id eng_id,
	काष्ठा dc_context *ctx);

काष्ठा dce_hwseq *dcn20_hwseq_create(
	काष्ठा dc_context *ctx);

bool dcn20_get_dcc_compression_cap(स्थिर काष्ठा dc *dc,
		स्थिर काष्ठा dc_dcc_surface_param *input,
		काष्ठा dc_surface_dcc_cap *output);

व्योम dcn20_dpp_destroy(काष्ठा dpp **dpp);

काष्ठा dpp *dcn20_dpp_create(
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst);

काष्ठा input_pixel_processor *dcn20_ipp_create(
	काष्ठा dc_context *ctx, uपूर्णांक32_t inst);


काष्ठा output_pixel_processor *dcn20_opp_create(
	काष्ठा dc_context *ctx, uपूर्णांक32_t inst);

काष्ठा dce_aux *dcn20_aux_engine_create(
	काष्ठा dc_context *ctx, uपूर्णांक32_t inst);

काष्ठा dce_i2c_hw *dcn20_i2c_hw_create(
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst);

व्योम dcn20_घड़ी_source_destroy(काष्ठा घड़ी_source **clk_src);

काष्ठा display_stream_compressor *dcn20_dsc_create(
	काष्ठा dc_context *ctx, uपूर्णांक32_t inst);
व्योम dcn20_dsc_destroy(काष्ठा display_stream_compressor **dsc);

व्योम dcn20_cap_soc_घड़ीs(
		काष्ठा _vcs_dpi_soc_bounding_box_st *bb,
		काष्ठा pp_smu_nv_घड़ी_प्रकारable max_घड़ीs);
व्योम dcn20_update_bounding_box(काष्ठा dc *dc, काष्ठा _vcs_dpi_soc_bounding_box_st *bb,
		काष्ठा pp_smu_nv_घड़ी_प्रकारable *max_घड़ीs, अचिन्हित पूर्णांक *uclk_states, अचिन्हित पूर्णांक num_states);
काष्ठा hubp *dcn20_hubp_create(
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst);
काष्ठा timing_generator *dcn20_timing_generator_create(
		काष्ठा dc_context *ctx,
		uपूर्णांक32_t instance);
काष्ठा mpc *dcn20_mpc_create(काष्ठा dc_context *ctx);
काष्ठा hubbub *dcn20_hubbub_create(काष्ठा dc_context *ctx);

bool dcn20_dwbc_create(काष्ठा dc_context *ctx, काष्ठा resource_pool *pool);
bool dcn20_mmhubbub_create(काष्ठा dc_context *ctx, काष्ठा resource_pool *pool);

व्योम dcn20_set_mcअगर_arb_params(
		काष्ठा dc *dc,
		काष्ठा dc_state *context,
		display_e2e_pipe_params_st *pipes,
		पूर्णांक pipe_cnt);
bool dcn20_validate_bandwidth(काष्ठा dc *dc, काष्ठा dc_state *context, bool fast_validate);
व्योम dcn20_merge_pipes_क्रम_validate(
		काष्ठा dc *dc,
		काष्ठा dc_state *context);
पूर्णांक dcn20_validate_apply_pipe_split_flags(
		काष्ठा dc *dc,
		काष्ठा dc_state *context,
		पूर्णांक vlevel,
		पूर्णांक *split,
		bool *merge);
व्योम dcn20_release_dsc(काष्ठा resource_context *res_ctx,
			स्थिर काष्ठा resource_pool *pool,
			काष्ठा display_stream_compressor **dsc);
bool dcn20_validate_dsc(काष्ठा dc *dc, काष्ठा dc_state *new_ctx);
व्योम dcn20_split_stream_क्रम_mpc(
		काष्ठा resource_context *res_ctx,
		स्थिर काष्ठा resource_pool *pool,
		काष्ठा pipe_ctx *primary_pipe,
		काष्ठा pipe_ctx *secondary_pipe);
bool dcn20_split_stream_क्रम_odm(
		स्थिर काष्ठा dc *dc,
		काष्ठा resource_context *res_ctx,
		काष्ठा pipe_ctx *prev_odm_pipe,
		काष्ठा pipe_ctx *next_odm_pipe);
व्योम dcn20_acquire_dsc(स्थिर काष्ठा dc *dc,
			काष्ठा resource_context *res_ctx,
			काष्ठा display_stream_compressor **dsc,
			पूर्णांक pipe_idx);
काष्ठा pipe_ctx *dcn20_find_secondary_pipe(काष्ठा dc *dc,
		काष्ठा resource_context *res_ctx,
		स्थिर काष्ठा resource_pool *pool,
		स्थिर काष्ठा pipe_ctx *primary_pipe);
bool dcn20_fast_validate_bw(
		काष्ठा dc *dc,
		काष्ठा dc_state *context,
		display_e2e_pipe_params_st *pipes,
		पूर्णांक *pipe_cnt_out,
		पूर्णांक *pipe_split_from,
		पूर्णांक *vlevel_out,
		bool fast_validate);
व्योम dcn20_calculate_dlg_params(
		काष्ठा dc *dc, काष्ठा dc_state *context,
		display_e2e_pipe_params_st *pipes,
		पूर्णांक pipe_cnt,
		पूर्णांक vlevel);

क्रमागत dc_status dcn20_build_mapped_resource(स्थिर काष्ठा dc *dc, काष्ठा dc_state *context, काष्ठा dc_stream_state *stream);
क्रमागत dc_status dcn20_add_stream_to_ctx(काष्ठा dc *dc, काष्ठा dc_state *new_ctx, काष्ठा dc_stream_state *dc_stream);
क्रमागत dc_status dcn20_add_dsc_to_stream_resource(काष्ठा dc *dc, काष्ठा dc_state *dc_ctx, काष्ठा dc_stream_state *dc_stream);
क्रमागत dc_status dcn20_हटाओ_stream_from_ctx(काष्ठा dc *dc, काष्ठा dc_state *new_ctx, काष्ठा dc_stream_state *dc_stream);
क्रमागत dc_status dcn20_patch_unknown_plane_state(काष्ठा dc_plane_state *plane_state);

व्योम dcn20_patch_bounding_box(
		काष्ठा dc *dc,
		काष्ठा _vcs_dpi_soc_bounding_box_st *bb);
व्योम dcn20_cap_soc_घड़ीs(
		काष्ठा _vcs_dpi_soc_bounding_box_st *bb,
		काष्ठा pp_smu_nv_घड़ी_प्रकारable max_घड़ीs);

#पूर्ण_अगर /* __DC_RESOURCE_DCN20_H__ */

