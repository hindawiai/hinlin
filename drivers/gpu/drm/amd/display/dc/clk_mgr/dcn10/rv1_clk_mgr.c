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

#समावेश <linux/slab.h>

#समावेश "reg_helper.h"
#समावेश "core_types.h"
#समावेश "clk_mgr_internal.h"
#समावेश "rv1_clk_mgr.h"
#समावेश "dce100/dce_clk_mgr.h"
#समावेश "dce112/dce112_clk_mgr.h"
#समावेश "rv1_clk_mgr_vbios_smu.h"
#समावेश "rv1_clk_mgr_clk.h"

व्योम rv1_init_घड़ीs(काष्ठा clk_mgr *clk_mgr)
अणु
	स_रखो(&(clk_mgr->clks), 0, माप(काष्ठा dc_घड़ीs));
पूर्ण

अटल पूर्णांक rv1_determine_dppclk_threshold(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, काष्ठा dc_घड़ीs *new_घड़ीs)
अणु
	bool request_dpp_भाग = new_घड़ीs->dispclk_khz > new_घड़ीs->dppclk_khz;
	bool dispclk_increase = new_घड़ीs->dispclk_khz > clk_mgr->base.clks.dispclk_khz;
	पूर्णांक disp_clk_threshold = new_घड़ीs->max_supported_dppclk_khz;
	bool cur_dpp_भाग = clk_mgr->base.clks.dispclk_khz > clk_mgr->base.clks.dppclk_khz;

	/* increase घड़ी, looking क्रम भाग is 0 क्रम current, request भाग is 1*/
	अगर (dispclk_increase) अणु
		/* alपढ़ोy भागided by 2, no need to reach target clk with 2 steps*/
		अगर (cur_dpp_भाग)
			वापस new_घड़ीs->dispclk_khz;

		/* request disp clk is lower than maximum supported dpp clk,
		 * no need to reach target clk with two steps.
		 */
		अगर (new_घड़ीs->dispclk_khz <= disp_clk_threshold)
			वापस new_घड़ीs->dispclk_khz;

		/* target dpp clk not request भागided by 2, still within threshold */
		अगर (!request_dpp_भाग)
			वापस new_घड़ीs->dispclk_khz;

	पूर्ण अन्यथा अणु
		/* decrease घड़ी, looking क्रम current dppclk भागided by 2,
		 * request dppclk not भागided by 2.
		 */

		/* current dpp clk not भागided by 2, no need to ramp*/
		अगर (!cur_dpp_भाग)
			वापस new_घड़ीs->dispclk_khz;

		/* current disp clk is lower than current maximum dpp clk,
		 * no need to ramp
		 */
		अगर (clk_mgr->base.clks.dispclk_khz <= disp_clk_threshold)
			वापस new_घड़ीs->dispclk_khz;

		/* request dpp clk need to be भागided by 2 */
		अगर (request_dpp_भाग)
			वापस new_घड़ीs->dispclk_khz;
	पूर्ण

	वापस disp_clk_threshold;
पूर्ण

अटल व्योम ramp_up_dispclk_with_dpp(
		काष्ठा clk_mgr_पूर्णांकernal *clk_mgr,
		काष्ठा dc *dc,
		काष्ठा dc_घड़ीs *new_घड़ीs,
		bool safe_to_lower)
अणु
	पूर्णांक i;
	पूर्णांक dispclk_to_dpp_threshold = rv1_determine_dppclk_threshold(clk_mgr, new_घड़ीs);
	bool request_dpp_भाग = new_घड़ीs->dispclk_khz > new_घड़ीs->dppclk_khz;

	/* this function is to change dispclk, dppclk and dprefclk according to
	 * bandwidth requirement. Its call stack is rv1_update_घड़ीs -->
	 * update_घड़ीs --> dcn10_prepare_bandwidth / dcn10_optimize_bandwidth
	 * --> prepare_bandwidth / optimize_bandwidth. beक्रमe change dcn hw,
	 * prepare_bandwidth will be called first to allow enough घड़ी,
	 * watermark क्रम change, after end of dcn hw change, optimize_bandwidth
	 * is executed to lower घड़ी to save घातer क्रम new dcn hw settings.
	 *
	 * below is sequence of commit_planes_क्रम_stream:
	 *
	 * step 1: prepare_bandwidth - उठाओ घड़ी to have enough bandwidth
	 * step 2: lock_द्विगुनbuffer_enable
	 * step 3: pipe_control_lock(true) - make dchubp रेजिस्टर change will
	 * not take effect right way
	 * step 4: apply_ctx_क्रम_surface - program dchubp
	 * step 5: pipe_control_lock(false) - dchubp रेजिस्टर change take effect
	 * step 6: optimize_bandwidth --> dc_post_update_surfaces_to_stream
	 * क्रम full_date, optimize घड़ी to save घातer
	 *
	 * at end of step 1, dcn घड़ीs (dprefclk, dispclk, dppclk) may be
	 * changed क्रम new dchubp configuration. but real dcn hub dchubps are
	 * still running with old configuration until end of step 5. this need
	 * घड़ीs settings at step 1 should not less than that beक्रमe step 1.
	 * this is checked by two conditions: 1. अगर (should_set_घड़ी(safe_to_lower
	 * , new_घड़ीs->dispclk_khz, clk_mgr_base->clks.dispclk_khz) ||
	 * new_घड़ीs->dispclk_khz == clk_mgr_base->clks.dispclk_khz)
	 * 2. request_dpp_भाग = new_घड़ीs->dispclk_khz > new_घड़ीs->dppclk_khz
	 *
	 * the second condition is based on new dchubp configuration. dppclk
	 * क्रम new dchubp may be dअगरferent from dppclk beक्रमe step 1.
	 * क्रम example, beक्रमe step 1, dchubps are as below:
	 * pipe 0: recout=(0,40,1920,980) viewport=(0,0,1920,979)
	 * pipe 1: recout=(0,0,1920,1080) viewport=(0,0,1920,1080)
	 * क्रम dppclk क्रम pipe0 need dppclk = dispclk
	 *
	 * new dchubp pipe split configuration:
	 * pipe 0: recout=(0,0,960,1080) viewport=(0,0,960,1080)
	 * pipe 1: recout=(960,0,960,1080) viewport=(960,0,960,1080)
	 * dppclk only needs dppclk = dispclk /2.
	 *
	 * dispclk, dppclk are not lock by otg master lock. they take effect
	 * after step 1. during this transition, dispclk are the same, but
	 * dppclk is changed to half of previous घड़ी क्रम old dchubp
	 * configuration between step 1 and step 6. This may cause p-state
	 * warning पूर्णांकermittently.
	 *
	 * क्रम new_घड़ीs->dispclk_khz == clk_mgr_base->clks.dispclk_khz, we
	 * need make sure dppclk are not changed to less between step 1 and 6.
	 * क्रम new_घड़ीs->dispclk_khz > clk_mgr_base->clks.dispclk_khz,
	 * new display घड़ी is उठाओd, but we करो not know ratio of
	 * new_घड़ीs->dispclk_khz and clk_mgr_base->clks.dispclk_khz,
	 * new_घड़ीs->dispclk_khz /2 करोes not guarantee equal or higher than
	 * old dppclk. we could ignore घातer saving dअगरferent between
	 * dppclk = displck and dppclk = dispclk / 2 between step 1 and step 6.
	 * as दीर्घ as safe_to_lower = false, set dpclk = dispclk to simplअगरy
	 * condition check.
	 * toकरो: review this change क्रम other asic.
	 **/
	अगर (!safe_to_lower)
		request_dpp_भाग = false;

	/* set disp clk to dpp clk threshold */

	clk_mgr->funcs->set_dispclk(clk_mgr, dispclk_to_dpp_threshold);
	clk_mgr->funcs->set_dprefclk(clk_mgr);


	/* update request dpp clk भागision option */
	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe_ctx = &dc->current_state->res_ctx.pipe_ctx[i];

		अगर (!pipe_ctx->plane_state)
			जारी;

		pipe_ctx->plane_res.dpp->funcs->dpp_dppclk_control(
				pipe_ctx->plane_res.dpp,
				request_dpp_भाग,
				true);
	पूर्ण

	/* If target clk not same as dppclk threshold, set to target घड़ी */
	अगर (dispclk_to_dpp_threshold != new_घड़ीs->dispclk_khz) अणु
		clk_mgr->funcs->set_dispclk(clk_mgr, new_घड़ीs->dispclk_khz);
		clk_mgr->funcs->set_dprefclk(clk_mgr);
	पूर्ण


	clk_mgr->base.clks.dispclk_khz = new_घड़ीs->dispclk_khz;
	clk_mgr->base.clks.dppclk_khz = new_घड़ीs->dppclk_khz;
	clk_mgr->base.clks.max_supported_dppclk_khz = new_घड़ीs->max_supported_dppclk_khz;
पूर्ण

अटल व्योम rv1_update_घड़ीs(काष्ठा clk_mgr *clk_mgr_base,
			काष्ठा dc_state *context,
			bool safe_to_lower)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);
	काष्ठा dc *dc = clk_mgr_base->ctx->dc;
	काष्ठा dc_debug_options *debug = &dc->debug;
	काष्ठा dc_घड़ीs *new_घड़ीs = &context->bw_ctx.bw.dcn.clk;
	काष्ठा pp_smu_funcs_rv *pp_smu = शून्य;
	bool send_request_to_increase = false;
	bool send_request_to_lower = false;
	पूर्णांक display_count;

	bool enter_display_off = false;

	ASSERT(clk_mgr->pp_smu);

	अगर (dc->work_arounds.skip_घड़ी_update)
		वापस;

	pp_smu = &clk_mgr->pp_smu->rv_funcs;

	display_count = clk_mgr_helper_get_active_display_cnt(dc, context);

	अगर (display_count == 0)
		enter_display_off = true;

	अगर (enter_display_off == safe_to_lower) अणु
		/*
		 * Notअगरy SMU active displays
		 * अगर function poपूर्णांकer not set up, this message is
		 * sent as part of pplib_apply_display_requirements.
		 */
		अगर (pp_smu->set_display_count)
			pp_smu->set_display_count(&pp_smu->pp_smu, display_count);
	पूर्ण

	अगर (new_घड़ीs->dispclk_khz > clk_mgr_base->clks.dispclk_khz
			|| new_घड़ीs->phyclk_khz > clk_mgr_base->clks.phyclk_khz
			|| new_घड़ीs->fclk_khz > clk_mgr_base->clks.fclk_khz
			|| new_घड़ीs->dcfclk_khz > clk_mgr_base->clks.dcfclk_khz)
		send_request_to_increase = true;

	अगर (should_set_घड़ी(safe_to_lower, new_घड़ीs->phyclk_khz, clk_mgr_base->clks.phyclk_khz)) अणु
		clk_mgr_base->clks.phyclk_khz = new_घड़ीs->phyclk_khz;
		send_request_to_lower = true;
	पूर्ण

	// F Clock
	अगर (debug->क्रमce_fclk_khz != 0)
		new_घड़ीs->fclk_khz = debug->क्रमce_fclk_khz;

	अगर (should_set_घड़ी(safe_to_lower, new_घड़ीs->fclk_khz, clk_mgr_base->clks.fclk_khz)) अणु
		clk_mgr_base->clks.fclk_khz = new_घड़ीs->fclk_khz;
		send_request_to_lower = true;
	पूर्ण

	//DCF Clock
	अगर (should_set_घड़ी(safe_to_lower, new_घड़ीs->dcfclk_khz, clk_mgr_base->clks.dcfclk_khz)) अणु
		clk_mgr_base->clks.dcfclk_khz = new_घड़ीs->dcfclk_khz;
		send_request_to_lower = true;
	पूर्ण

	अगर (should_set_घड़ी(safe_to_lower,
			new_घड़ीs->dcfclk_deep_sleep_khz, clk_mgr_base->clks.dcfclk_deep_sleep_khz)) अणु
		clk_mgr_base->clks.dcfclk_deep_sleep_khz = new_घड़ीs->dcfclk_deep_sleep_khz;
		send_request_to_lower = true;
	पूर्ण

	/* make sure dcf clk is beक्रमe dpp clk to
	 * make sure we have enough voltage to run dpp clk
	 */
	अगर (send_request_to_increase) अणु
		/*use dcfclk to request voltage*/
		अगर (pp_smu->set_hard_min_fclk_by_freq &&
				pp_smu->set_hard_min_dcfclk_by_freq &&
				pp_smu->set_min_deep_sleep_dcfclk) अणु
			pp_smu->set_hard_min_fclk_by_freq(&pp_smu->pp_smu, new_घड़ीs->fclk_khz / 1000);
			pp_smu->set_hard_min_dcfclk_by_freq(&pp_smu->pp_smu, new_घड़ीs->dcfclk_khz / 1000);
			pp_smu->set_min_deep_sleep_dcfclk(&pp_smu->pp_smu, (new_घड़ीs->dcfclk_deep_sleep_khz + 999) / 1000);
		पूर्ण
	पूर्ण

	/* dcn1 dppclk is tied to dispclk */
	/* program dispclk on = as a w/a क्रम sleep resume घड़ी ramping issues */
	अगर (should_set_घड़ी(safe_to_lower, new_घड़ीs->dispclk_khz, clk_mgr_base->clks.dispclk_khz)
			|| new_घड़ीs->dispclk_khz == clk_mgr_base->clks.dispclk_khz) अणु
		ramp_up_dispclk_with_dpp(clk_mgr, dc, new_घड़ीs, safe_to_lower);
		clk_mgr_base->clks.dispclk_khz = new_घड़ीs->dispclk_khz;
		send_request_to_lower = true;
	पूर्ण

	अगर (!send_request_to_increase && send_request_to_lower) अणु
		/*use dcfclk to request voltage*/
		अगर (pp_smu->set_hard_min_fclk_by_freq &&
				pp_smu->set_hard_min_dcfclk_by_freq &&
				pp_smu->set_min_deep_sleep_dcfclk) अणु
			pp_smu->set_hard_min_fclk_by_freq(&pp_smu->pp_smu, new_घड़ीs->fclk_khz / 1000);
			pp_smu->set_hard_min_dcfclk_by_freq(&pp_smu->pp_smu, new_घड़ीs->dcfclk_khz / 1000);
			pp_smu->set_min_deep_sleep_dcfclk(&pp_smu->pp_smu, (new_घड़ीs->dcfclk_deep_sleep_khz + 999) / 1000);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rv1_enable_pme_wa(काष्ठा clk_mgr *clk_mgr_base)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);
	काष्ठा pp_smu_funcs_rv *pp_smu = शून्य;

	अगर (clk_mgr->pp_smu) अणु
		pp_smu = &clk_mgr->pp_smu->rv_funcs;

		अगर (pp_smu->set_pme_wa_enable)
			pp_smu->set_pme_wa_enable(&pp_smu->pp_smu);
	पूर्ण
पूर्ण

अटल काष्ठा clk_mgr_funcs rv1_clk_funcs = अणु
	.init_घड़ीs = rv1_init_घड़ीs,
	.get_dp_ref_clk_frequency = dce12_get_dp_ref_freq_khz,
	.update_घड़ीs = rv1_update_घड़ीs,
	.enable_pme_wa = rv1_enable_pme_wa,
पूर्ण;

अटल काष्ठा clk_mgr_पूर्णांकernal_funcs rv1_clk_पूर्णांकernal_funcs = अणु
	.set_dispclk = rv1_vbios_smu_set_dispclk,
	.set_dprefclk = dce112_set_dprefclk
पूर्ण;

व्योम rv1_clk_mgr_स्थिरruct(काष्ठा dc_context *ctx, काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, काष्ठा pp_smu_funcs *pp_smu)
अणु
	काष्ठा dc_debug_options *debug = &ctx->dc->debug;
	काष्ठा dc_bios *bp = ctx->dc_bios;

	clk_mgr->base.ctx = ctx;
	clk_mgr->pp_smu = pp_smu;
	clk_mgr->base.funcs = &rv1_clk_funcs;
	clk_mgr->funcs = &rv1_clk_पूर्णांकernal_funcs;

	clk_mgr->dfs_bypass_disp_clk = 0;

	clk_mgr->dprefclk_ss_percentage = 0;
	clk_mgr->dprefclk_ss_भागider = 1000;
	clk_mgr->ss_on_dprefclk = false;
	clk_mgr->base.dprefclk_khz = 600000;

	अगर (bp->पूर्णांकegrated_info)
		clk_mgr->base.dentist_vco_freq_khz = bp->पूर्णांकegrated_info->dentist_vco_freq;
	अगर (bp->fw_info_valid && clk_mgr->base.dentist_vco_freq_khz == 0) अणु
		clk_mgr->base.dentist_vco_freq_khz = bp->fw_info.smu_gpu_pll_output_freq;
		अगर (clk_mgr->base.dentist_vco_freq_khz == 0)
			clk_mgr->base.dentist_vco_freq_khz = 3600000;
	पूर्ण

	अगर (!debug->disable_dfs_bypass && bp->पूर्णांकegrated_info)
		अगर (bp->पूर्णांकegrated_info->gpu_cap_info & DFS_BYPASS_ENABLE)
			clk_mgr->dfs_bypass_enabled = true;

	dce_घड़ी_पढ़ो_ss_info(clk_mgr);
पूर्ण


