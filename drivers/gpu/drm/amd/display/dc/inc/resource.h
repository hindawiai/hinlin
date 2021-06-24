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
 */

#अगर_अघोषित DRIVERS_GPU_DRM_AMD_DC_DEV_DC_INC_RESOURCE_H_
#घोषणा DRIVERS_GPU_DRM_AMD_DC_DEV_DC_INC_RESOURCE_H_

#समावेश "core_types.h"
#समावेश "core_status.h"
#समावेश "dal_asic_id.h"
#समावेश "dm_pp_smu.h"

#घोषणा MEMORY_TYPE_MULTIPLIER_CZ 4
#घोषणा MEMORY_TYPE_HBM 2


क्रमागत dce_version resource_parse_asic_id(
		काष्ठा hw_asic_id asic_id);

काष्ठा resource_caps अणु
	पूर्णांक num_timing_generator;
	पूर्णांक num_opp;
	पूर्णांक num_video_plane;
	पूर्णांक num_audio;
	पूर्णांक num_stream_encoder;
	पूर्णांक num_pll;
	पूर्णांक num_dwb;
	पूर्णांक num_ddc;
	पूर्णांक num_vmid;
	पूर्णांक num_dsc;
	अचिन्हित पूर्णांक num_dig_link_enc; // Total number of DIGs (digital encoders) in DIO (Display Input/Output).
	पूर्णांक num_mpc_3dlut;
पूर्ण;

काष्ठा resource_straps अणु
	uपूर्णांक32_t hdmi_disable;
	uपूर्णांक32_t dc_pinstraps_audio;
	uपूर्णांक32_t audio_stream_number;
पूर्ण;

काष्ठा resource_create_funcs अणु
	व्योम (*पढ़ो_dce_straps)(
			काष्ठा dc_context *ctx, काष्ठा resource_straps *straps);

	काष्ठा audio *(*create_audio)(
			काष्ठा dc_context *ctx, अचिन्हित पूर्णांक inst);

	काष्ठा stream_encoder *(*create_stream_encoder)(
			क्रमागत engine_id eng_id, काष्ठा dc_context *ctx);

	काष्ठा dce_hwseq *(*create_hwseq)(
			काष्ठा dc_context *ctx);
पूर्ण;

bool resource_स्थिरruct(
	अचिन्हित पूर्णांक num_भव_links,
	काष्ठा dc *dc,
	काष्ठा resource_pool *pool,
	स्थिर काष्ठा resource_create_funcs *create_funcs);

काष्ठा resource_pool *dc_create_resource_pool(काष्ठा dc  *dc,
					      स्थिर काष्ठा dc_init_data *init_data,
					      क्रमागत dce_version dc_version);

व्योम dc_destroy_resource_pool(काष्ठा dc *dc);

क्रमागत dc_status resource_map_pool_resources(
		स्थिर काष्ठा dc *dc,
		काष्ठा dc_state *context,
		काष्ठा dc_stream_state *stream);

bool resource_build_scaling_params(काष्ठा pipe_ctx *pipe_ctx);

क्रमागत dc_status resource_build_scaling_params_क्रम_context(
		स्थिर काष्ठा dc *dc,
		काष्ठा dc_state *context);

व्योम resource_build_info_frame(काष्ठा pipe_ctx *pipe_ctx);

व्योम resource_unreference_घड़ी_source(
		काष्ठा resource_context *res_ctx,
		स्थिर काष्ठा resource_pool *pool,
		काष्ठा घड़ी_source *घड़ी_source);

व्योम resource_reference_घड़ी_source(
		काष्ठा resource_context *res_ctx,
		स्थिर काष्ठा resource_pool *pool,
		काष्ठा घड़ी_source *घड़ी_source);

पूर्णांक resource_get_घड़ी_source_reference(
		काष्ठा resource_context *res_ctx,
		स्थिर काष्ठा resource_pool *pool,
		काष्ठा घड़ी_source *घड़ी_source);

bool resource_are_streams_timing_synchronizable(
		काष्ठा dc_stream_state *stream1,
		काष्ठा dc_stream_state *stream2);

bool resource_are_vblanks_synchronizable(
		काष्ठा dc_stream_state *stream1,
		काष्ठा dc_stream_state *stream2);

काष्ठा घड़ी_source *resource_find_used_clk_src_क्रम_sharing(
		काष्ठा resource_context *res_ctx,
		काष्ठा pipe_ctx *pipe_ctx);

काष्ठा घड़ी_source *dc_resource_find_first_मुक्त_pll(
		काष्ठा resource_context *res_ctx,
		स्थिर काष्ठा resource_pool *pool);

काष्ठा pipe_ctx *resource_get_head_pipe_क्रम_stream(
		काष्ठा resource_context *res_ctx,
		काष्ठा dc_stream_state *stream);

bool resource_attach_surfaces_to_context(
		काष्ठा dc_plane_state *स्थिर *plane_state,
		पूर्णांक surface_count,
		काष्ठा dc_stream_state *dc_stream,
		काष्ठा dc_state *context,
		स्थिर काष्ठा resource_pool *pool);

काष्ठा pipe_ctx *find_idle_secondary_pipe(
		काष्ठा resource_context *res_ctx,
		स्थिर काष्ठा resource_pool *pool,
		स्थिर काष्ठा pipe_ctx *primary_pipe);

bool resource_validate_attach_surfaces(
		स्थिर काष्ठा dc_validation_set set[],
		पूर्णांक set_count,
		स्थिर काष्ठा dc_state *old_context,
		काष्ठा dc_state *context,
		स्थिर काष्ठा resource_pool *pool);

व्योम resource_validate_ctx_update_poपूर्णांकer_after_copy(
		स्थिर काष्ठा dc_state *src_ctx,
		काष्ठा dc_state *dst_ctx);

क्रमागत dc_status resource_map_घड़ी_resources(
		स्थिर काष्ठा dc *dc,
		काष्ठा dc_state *context,
		काष्ठा dc_stream_state *stream);

क्रमागत dc_status resource_map_phy_घड़ी_resources(
		स्थिर काष्ठा dc *dc,
		काष्ठा dc_state *context,
		काष्ठा dc_stream_state *stream);

bool pipe_need_reprogram(
		काष्ठा pipe_ctx *pipe_ctx_old,
		काष्ठा pipe_ctx *pipe_ctx);

व्योम resource_build_bit_depth_reduction_params(काष्ठा dc_stream_state *stream,
		काष्ठा bit_depth_reduction_params *fmt_bit_depth);

व्योम update_audio_usage(
		काष्ठा resource_context *res_ctx,
		स्थिर काष्ठा resource_pool *pool,
		काष्ठा audio *audio,
		bool acquired);

अचिन्हित पूर्णांक resource_pixel_क्रमmat_to_bpp(क्रमागत surface_pixel_क्रमmat क्रमmat);

व्योम get_audio_check(काष्ठा audio_info *aud_modes,
	काष्ठा audio_check *aud_chk);

पूर्णांक get_num_mpc_splits(काष्ठा pipe_ctx *pipe);

पूर्णांक get_num_odm_splits(काष्ठा pipe_ctx *pipe);

#पूर्ण_अगर /* DRIVERS_GPU_DRM_AMD_DC_DEV_DC_INC_RESOURCE_H_ */
