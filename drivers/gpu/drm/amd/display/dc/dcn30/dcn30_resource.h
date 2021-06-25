<शैली गुरु>
/*
 * Copyright 2020 Advanced Micro Devices, Inc.
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

#अगर_अघोषित _DCN30_RESOURCE_H_
#घोषणा _DCN30_RESOURCE_H_

#समावेश "core_types.h"

#घोषणा TO_DCN30_RES_POOL(pool)\
	container_of(pool, काष्ठा dcn30_resource_pool, base)

काष्ठा dc;
काष्ठा resource_pool;
काष्ठा _vcs_dpi_display_pipe_params_st;

काष्ठा dcn30_resource_pool अणु
	काष्ठा resource_pool base;
पूर्ण;
काष्ठा resource_pool *dcn30_create_resource_pool(
		स्थिर काष्ठा dc_init_data *init_data,
		काष्ठा dc *dc);

व्योम dcn30_set_mcअगर_arb_params(
		काष्ठा dc *dc,
		काष्ठा dc_state *context,
		display_e2e_pipe_params_st *pipes,
		पूर्णांक pipe_cnt);

अचिन्हित पूर्णांक dcn30_calc_max_scaled_समय(
		अचिन्हित पूर्णांक समय_per_pixel,
		क्रमागत mmhubbub_wbअगर_mode mode,
		अचिन्हित पूर्णांक urgent_watermark);

bool dcn30_validate_bandwidth(काष्ठा dc *dc, काष्ठा dc_state *context,
		bool fast_validate);
व्योम dcn30_calculate_wm_and_dlg(
		काष्ठा dc *dc, काष्ठा dc_state *context,
		display_e2e_pipe_params_st *pipes,
		पूर्णांक pipe_cnt,
		पूर्णांक vlevel);
व्योम dcn30_update_soc_क्रम_wm_a(काष्ठा dc *dc, काष्ठा dc_state *context);
व्योम dcn30_populate_dml_ग_लिखोback_from_context(
		काष्ठा dc *dc, काष्ठा resource_context *res_ctx, display_e2e_pipe_params_st *pipes);

पूर्णांक dcn30_populate_dml_pipes_from_context(
	काष्ठा dc *dc, काष्ठा dc_state *context,
	display_e2e_pipe_params_st *pipes,
	bool fast_validate);

bool dcn30_acquire_post_bldn_3dlut(
		काष्ठा resource_context *res_ctx,
		स्थिर काष्ठा resource_pool *pool,
		पूर्णांक mpcc_id,
		काष्ठा dc_3dlut **lut,
		काष्ठा dc_transfer_func **shaper);

bool dcn30_release_post_bldn_3dlut(
		काष्ठा resource_context *res_ctx,
		स्थिर काष्ठा resource_pool *pool,
		काष्ठा dc_3dlut **lut,
		काष्ठा dc_transfer_func **shaper);

क्रमागत dc_status dcn30_add_stream_to_ctx(
		काष्ठा dc *dc,
		काष्ठा dc_state *new_ctx,
		काष्ठा dc_stream_state *dc_stream);

व्योम dcn30_update_bw_bounding_box(काष्ठा dc *dc, काष्ठा clk_bw_params *bw_params);

#पूर्ण_अगर /* _DCN30_RESOURCE_H_ */
