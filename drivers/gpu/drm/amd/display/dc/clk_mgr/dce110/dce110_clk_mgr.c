<शैली गुरु>
/*
 * Copyright 2012-16 Advanced Micro Devices, Inc.
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

#समावेश "core_types.h"
#समावेश "clk_mgr_internal.h"

#समावेश "dce/dce_11_0_d.h"
#समावेश "dce/dce_11_0_sh_mask.h"
#समावेश "dce110_clk_mgr.h"
#समावेश "../clk_mgr/dce100/dce_clk_mgr.h"

/* set रेजिस्टर offset */
#घोषणा SR(reg_name)\
	.reg_name = mm ## reg_name

/* set रेजिस्टर offset with instance */
#घोषणा SRI(reg_name, block, id)\
	.reg_name = mm ## block ## id ## _ ## reg_name

अटल स्थिर काष्ठा clk_mgr_रेजिस्टरs disp_clk_regs = अणु
		CLK_COMMON_REG_LIST_DCE_BASE()
पूर्ण;

अटल स्थिर काष्ठा clk_mgr_shअगरt disp_clk_shअगरt = अणु
		CLK_COMMON_MASK_SH_LIST_DCE_COMMON_BASE(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा clk_mgr_mask disp_clk_mask = अणु
		CLK_COMMON_MASK_SH_LIST_DCE_COMMON_BASE(_MASK)
पूर्ण;

अटल स्थिर काष्ठा state_dependent_घड़ीs dce110_max_clks_by_state[] = अणु
/*ClocksStateInvalid - should not be used*/
अणु .display_clk_khz = 0, .pixel_clk_khz = 0 पूर्ण,
/*ClocksStateUltraLow - currently by HW design team not supposed to be used*/
अणु .display_clk_khz = 352000, .pixel_clk_khz = 330000 पूर्ण,
/*ClocksStateLow*/
अणु .display_clk_khz = 352000, .pixel_clk_khz = 330000 पूर्ण,
/*ClocksStateNominal*/
अणु .display_clk_khz = 467000, .pixel_clk_khz = 400000 पूर्ण,
/*ClocksStatePerक्रमmance*/
अणु .display_clk_khz = 643000, .pixel_clk_khz = 400000 पूर्ण पूर्ण;

अटल पूर्णांक determine_sclk_from_bounding_box(
		स्थिर काष्ठा dc *dc,
		पूर्णांक required_sclk)
अणु
	पूर्णांक i;

	/*
	 * Some asics करो not give us sclk levels, so we just report the actual
	 * required sclk
	 */
	अगर (dc->sclk_lvls.num_levels == 0)
		वापस required_sclk;

	क्रम (i = 0; i < dc->sclk_lvls.num_levels; i++) अणु
		अगर (dc->sclk_lvls.घड़ीs_in_khz[i] >= required_sclk)
			वापस dc->sclk_lvls.घड़ीs_in_khz[i];
	पूर्ण
	/*
	 * even maximum level could not satisfy requirement, this
	 * is unexpected at this stage, should have been caught at
	 * validation समय
	 */
	ASSERT(0);
	वापस dc->sclk_lvls.घड़ीs_in_khz[dc->sclk_lvls.num_levels - 1];
पूर्ण

uपूर्णांक32_t dce110_get_min_vblank_समय_us(स्थिर काष्ठा dc_state *context)
अणु
	uपूर्णांक8_t j;
	uपूर्णांक32_t min_vertical_blank_समय = -1;

	क्रम (j = 0; j < context->stream_count; j++) अणु
		काष्ठा dc_stream_state *stream = context->streams[j];
		uपूर्णांक32_t vertical_blank_in_pixels = 0;
		uपूर्णांक32_t vertical_blank_समय = 0;
		uपूर्णांक32_t vertical_total_min = stream->timing.v_total;
		काष्ठा dc_crtc_timing_adjust adjust = stream->adjust;
		अगर (adjust.v_total_max != adjust.v_total_min)
			vertical_total_min = adjust.v_total_min;

		vertical_blank_in_pixels = stream->timing.h_total *
			(vertical_total_min
			 - stream->timing.v_addressable);
		vertical_blank_समय = vertical_blank_in_pixels
			* 10000 / stream->timing.pix_clk_100hz;

		अगर (min_vertical_blank_समय > vertical_blank_समय)
			min_vertical_blank_समय = vertical_blank_समय;
	पूर्ण

	वापस min_vertical_blank_समय;
पूर्ण

व्योम dce110_fill_display_configs(
	स्थिर काष्ठा dc_state *context,
	काष्ठा dm_pp_display_configuration *pp_display_cfg)
अणु
	पूर्णांक j;
	पूर्णांक num_cfgs = 0;

	क्रम (j = 0; j < context->stream_count; j++) अणु
		पूर्णांक k;

		स्थिर काष्ठा dc_stream_state *stream = context->streams[j];
		काष्ठा dm_pp_single_disp_config *cfg =
			&pp_display_cfg->disp_configs[num_cfgs];
		स्थिर काष्ठा pipe_ctx *pipe_ctx = शून्य;

		क्रम (k = 0; k < MAX_PIPES; k++)
			अगर (stream == context->res_ctx.pipe_ctx[k].stream) अणु
				pipe_ctx = &context->res_ctx.pipe_ctx[k];
				अवरोध;
			पूर्ण

		ASSERT(pipe_ctx != शून्य);

		/* only notअगरy active stream */
		अगर (stream->dpms_off)
			जारी;

		num_cfgs++;
		cfg->संकेत = pipe_ctx->stream->संकेत;
		cfg->pipe_idx = pipe_ctx->stream_res.tg->inst;
		cfg->src_height = stream->src.height;
		cfg->src_width = stream->src.width;
		cfg->ddi_channel_mapping =
			stream->link->ddi_channel_mapping.raw;
		cfg->transmitter =
			stream->link->link_enc->transmitter;
		cfg->link_settings.lane_count =
			stream->link->cur_link_settings.lane_count;
		cfg->link_settings.link_rate =
			stream->link->cur_link_settings.link_rate;
		cfg->link_settings.link_spपढ़ो =
			stream->link->cur_link_settings.link_spपढ़ो;
		cfg->sym_घड़ी = stream->phy_pix_clk;
		/* Round v_refresh*/
		cfg->v_refresh = stream->timing.pix_clk_100hz * 100;
		cfg->v_refresh /= stream->timing.h_total;
		cfg->v_refresh = (cfg->v_refresh + stream->timing.v_total / 2)
							/ stream->timing.v_total;
	पूर्ण

	pp_display_cfg->display_count = num_cfgs;
पूर्ण

व्योम dce11_pplib_apply_display_requirements(
	काष्ठा dc *dc,
	काष्ठा dc_state *context)
अणु
	काष्ठा dm_pp_display_configuration *pp_display_cfg = &context->pp_display_cfg;
	पूर्णांक memory_type_multiplier = MEMORY_TYPE_MULTIPLIER_CZ;

	अगर (dc->bw_vbios && dc->bw_vbios->memory_type == bw_def_hbm)
		memory_type_multiplier = MEMORY_TYPE_HBM;

	pp_display_cfg->all_displays_in_sync =
		context->bw_ctx.bw.dce.all_displays_in_sync;
	pp_display_cfg->nb_pstate_चयन_disable =
			context->bw_ctx.bw.dce.nbp_state_change_enable == false;
	pp_display_cfg->cpu_cc6_disable =
			context->bw_ctx.bw.dce.cpuc_state_change_enable == false;
	pp_display_cfg->cpu_pstate_disable =
			context->bw_ctx.bw.dce.cpup_state_change_enable == false;
	pp_display_cfg->cpu_pstate_separation_समय =
			context->bw_ctx.bw.dce.blackout_recovery_समय_us;

	/*
	 * TODO: determine whether the bandwidth has reached memory's limitation
	 * , then change minimum memory घड़ी based on real-समय bandwidth
	 * limitation.
	 */
	अगर ((dc->ctx->asic_id.chip_family == FAMILY_AI) &&
	     ASICREV_IS_VEGA20_P(dc->ctx->asic_id.hw_पूर्णांकernal_rev) && (context->stream_count >= 2)) अणु
		pp_display_cfg->min_memory_घड़ी_khz = max(pp_display_cfg->min_memory_घड़ी_khz,
							   (uपूर्णांक32_t) भाग64_s64(
								   भाग64_s64(dc->bw_vbios->high_yclk.value,
									     memory_type_multiplier), 10000));
	पूर्ण अन्यथा अणु
		pp_display_cfg->min_memory_घड़ी_khz = context->bw_ctx.bw.dce.yclk_khz
			/ memory_type_multiplier;
	पूर्ण

	pp_display_cfg->min_engine_घड़ी_khz = determine_sclk_from_bounding_box(
			dc,
			context->bw_ctx.bw.dce.sclk_khz);

	/*
	 * As workaround क्रम >4x4K lightup set dcfघड़ी to min_engine_घड़ी value.
	 * This is not required क्रम less than 5 displays,
	 * thus करोn't request decfclk in dc to aव्योम impact
	 * on घातer saving.
	 *
	 */
	pp_display_cfg->min_dcfघड़ी_khz = (context->stream_count > 4) ?
			pp_display_cfg->min_engine_घड़ी_khz : 0;

	pp_display_cfg->min_engine_घड़ी_deep_sleep_khz
			= context->bw_ctx.bw.dce.sclk_deep_sleep_khz;

	pp_display_cfg->avail_mclk_चयन_समय_us =
						dce110_get_min_vblank_समय_us(context);
	/* TODO: dce11.2*/
	pp_display_cfg->avail_mclk_चयन_समय_in_disp_active_us = 0;

	pp_display_cfg->disp_clk_khz = dc->clk_mgr->clks.dispclk_khz;

	dce110_fill_display_configs(context, pp_display_cfg);

	/* TODO: is this still applicable?*/
	अगर (pp_display_cfg->display_count == 1) अणु
		स्थिर काष्ठा dc_crtc_timing *timing =
			&context->streams[0]->timing;

		pp_display_cfg->crtc_index =
			pp_display_cfg->disp_configs[0].pipe_idx;
		pp_display_cfg->line_समय_in_us = timing->h_total * 10000 / timing->pix_clk_100hz;
	पूर्ण

	अगर (स_भेद(&dc->current_state->pp_display_cfg, pp_display_cfg, माप(*pp_display_cfg)) !=  0)
		dm_pp_apply_display_requirements(dc->ctx, pp_display_cfg);
पूर्ण

अटल व्योम dce11_update_घड़ीs(काष्ठा clk_mgr *clk_mgr_base,
			काष्ठा dc_state *context,
			bool safe_to_lower)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr_dce = TO_CLK_MGR_INTERNAL(clk_mgr_base);
	काष्ठा dm_pp_घातer_level_change_request level_change_req;
	पूर्णांक patched_disp_clk = context->bw_ctx.bw.dce.dispclk_khz;

	/*TODO: W/A क्रम dal3 linux, investigate why this works */
	अगर (!clk_mgr_dce->dfs_bypass_active)
		patched_disp_clk = patched_disp_clk * 115 / 100;

	level_change_req.घातer_level = dce_get_required_घड़ीs_state(clk_mgr_base, context);
	/* get max घड़ी state from PPLIB */
	अगर ((level_change_req.घातer_level < clk_mgr_dce->cur_min_clks_state && safe_to_lower)
			|| level_change_req.घातer_level > clk_mgr_dce->cur_min_clks_state) अणु
		अगर (dm_pp_apply_घातer_level_change_request(clk_mgr_base->ctx, &level_change_req))
			clk_mgr_dce->cur_min_clks_state = level_change_req.घातer_level;
	पूर्ण

	अगर (should_set_घड़ी(safe_to_lower, patched_disp_clk, clk_mgr_base->clks.dispclk_khz)) अणु
		context->bw_ctx.bw.dce.dispclk_khz = dce_set_घड़ी(clk_mgr_base, patched_disp_clk);
		clk_mgr_base->clks.dispclk_khz = patched_disp_clk;
	पूर्ण
	dce11_pplib_apply_display_requirements(clk_mgr_base->ctx->dc, context);
पूर्ण

अटल काष्ठा clk_mgr_funcs dce110_funcs = अणु
	.get_dp_ref_clk_frequency = dce_get_dp_ref_freq_khz,
	.update_घड़ीs = dce11_update_घड़ीs
पूर्ण;

व्योम dce110_clk_mgr_स्थिरruct(
		काष्ठा dc_context *ctx,
		काष्ठा clk_mgr_पूर्णांकernal *clk_mgr)
अणु
	dce_clk_mgr_स्थिरruct(ctx, clk_mgr);

	स_नकल(clk_mgr->max_clks_by_state,
		dce110_max_clks_by_state,
		माप(dce110_max_clks_by_state));

	clk_mgr->regs = &disp_clk_regs;
	clk_mgr->clk_mgr_shअगरt = &disp_clk_shअगरt;
	clk_mgr->clk_mgr_mask = &disp_clk_mask;
	clk_mgr->base.funcs = &dce110_funcs;

पूर्ण
