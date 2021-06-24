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

#समावेश "dccg.h"
#समावेश "clk_mgr_internal.h"

#समावेश "dcn30_clk_mgr_smu_msg.h"
#समावेश "dcn20/dcn20_clk_mgr.h"
#समावेश "dce100/dce_clk_mgr.h"
#समावेश "reg_helper.h"
#समावेश "core_types.h"
#समावेश "dm_helpers.h"

#समावेश "atomfirmware.h"


#समावेश "sienna_cichlid_ip_offset.h"
#समावेश "dcn/dcn_3_0_0_offset.h"
#समावेश "dcn/dcn_3_0_0_sh_mask.h"

#समावेश "nbio/nbio_7_4_offset.h"

#समावेश "dcn/dpcs_3_0_0_offset.h"
#समावेश "dcn/dpcs_3_0_0_sh_mask.h"

#समावेश "mmhub/mmhub_2_0_0_offset.h"
#समावेश "mmhub/mmhub_2_0_0_sh_mask.h"
/*we करोn't have clk folder yet*/
#समावेश "dcn30/dcn30_clk_mgr.h"

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	clk_mgr->clk_mgr_shअगरt->field_name, clk_mgr->clk_mgr_mask->field_name

#घोषणा REG(reg) \
	(clk_mgr->regs->reg)

#घोषणा BASE_INNER(seg) DCN_BASE__INST0_SEG ## seg

#घोषणा BASE(seg) BASE_INNER(seg)

#घोषणा SR(reg_name)\
		.reg_name = BASE(mm ## reg_name ## _BASE_IDX) +  \
					mm ## reg_name

#अघोषित CLK_SRI
#घोषणा CLK_SRI(reg_name, block, inst)\
	.reg_name = mm ## block ## _ ## reg_name

अटल स्थिर काष्ठा clk_mgr_रेजिस्टरs clk_mgr_regs = अणु
	CLK_REG_LIST_DCN3()
पूर्ण;

अटल स्थिर काष्ठा clk_mgr_shअगरt clk_mgr_shअगरt = अणु
	CLK_COMMON_MASK_SH_LIST_DCN20_BASE(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा clk_mgr_mask clk_mgr_mask = अणु
	CLK_COMMON_MASK_SH_LIST_DCN20_BASE(_MASK)
पूर्ण;


/* Query SMU क्रम all घड़ी states क्रम a particular घड़ी */
अटल व्योम dcn3_init_single_घड़ी(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, PPCLK_e clk, अचिन्हित पूर्णांक *entry_0, अचिन्हित पूर्णांक *num_levels)
अणु
	अचिन्हित पूर्णांक i;
	अक्षर *entry_i = (अक्षर *)entry_0;
	uपूर्णांक32_t ret = dcn30_smu_get_dpm_freq_by_index(clk_mgr, clk, 0xFF);

	अगर (ret & (1 << 31))
		/* fine-grained, only min and max */
		*num_levels = 2;
	अन्यथा
		/* discrete, a number of fixed states */
		/* will set num_levels to 0 on failure */
		*num_levels = ret & 0xFF;

	/* अगर the initial message failed, num_levels will be 0 */
	क्रम (i = 0; i < *num_levels; i++) अणु
		*((अचिन्हित पूर्णांक *)entry_i) = (dcn30_smu_get_dpm_freq_by_index(clk_mgr, clk, i) & 0xFFFF);
		entry_i += माप(clk_mgr->base.bw_params->clk_table.entries[0]);
	पूर्ण
पूर्ण

अटल noअंतरभूत व्योम dcn3_build_wm_range_table(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr)
अणु
	/* शेषs */
	द्विगुन pstate_latency_us = clk_mgr->base.ctx->dc->dml.soc.dram_घड़ी_change_latency_us;
	द्विगुन sr_निकास_समय_us = clk_mgr->base.ctx->dc->dml.soc.sr_निकास_समय_us;
	द्विगुन sr_enter_plus_निकास_समय_us = clk_mgr->base.ctx->dc->dml.soc.sr_enter_plus_निकास_समय_us;
	uपूर्णांक16_t min_uclk_mhz = clk_mgr->base.bw_params->clk_table.entries[0].memclk_mhz;

	/* Set A - Normal - शेष values*/
	clk_mgr->base.bw_params->wm_table.nv_entries[WM_A].valid = true;
	clk_mgr->base.bw_params->wm_table.nv_entries[WM_A].dml_input.pstate_latency_us = pstate_latency_us;
	clk_mgr->base.bw_params->wm_table.nv_entries[WM_A].dml_input.sr_निकास_समय_us = sr_निकास_समय_us;
	clk_mgr->base.bw_params->wm_table.nv_entries[WM_A].dml_input.sr_enter_plus_निकास_समय_us = sr_enter_plus_निकास_समय_us;
	clk_mgr->base.bw_params->wm_table.nv_entries[WM_A].pmfw_अवरोधकरोwn.wm_type = WATERMARKS_CLOCK_RANGE;
	clk_mgr->base.bw_params->wm_table.nv_entries[WM_A].pmfw_अवरोधकरोwn.min_dcfclk = 0;
	clk_mgr->base.bw_params->wm_table.nv_entries[WM_A].pmfw_अवरोधकरोwn.max_dcfclk = 0xFFFF;
	clk_mgr->base.bw_params->wm_table.nv_entries[WM_A].pmfw_अवरोधकरोwn.min_uclk = min_uclk_mhz;
	clk_mgr->base.bw_params->wm_table.nv_entries[WM_A].pmfw_अवरोधकरोwn.max_uclk = 0xFFFF;

	/* Set B - Perक्रमmance - higher minimum घड़ीs */
//	clk_mgr->base.bw_params->wm_table.nv_entries[WM_B].valid = true;
//	clk_mgr->base.bw_params->wm_table.nv_entries[WM_B].dml_input.pstate_latency_us = pstate_latency_us;
//	clk_mgr->base.bw_params->wm_table.nv_entries[WM_B].dml_input.sr_निकास_समय_us = sr_निकास_समय_us;
//	clk_mgr->base.bw_params->wm_table.nv_entries[WM_B].dml_input.sr_enter_plus_निकास_समय_us = sr_enter_plus_निकास_समय_us;
//	clk_mgr->base.bw_params->wm_table.nv_entries[WM_B].pmfw_अवरोधकरोwn.wm_type = WATERMARKS_CLOCK_RANGE;
//	clk_mgr->base.bw_params->wm_table.nv_entries[WM_B].pmfw_अवरोधकरोwn.min_dcfclk = TUNED VALUE;
//	clk_mgr->base.bw_params->wm_table.nv_entries[WM_B].pmfw_अवरोधकरोwn.max_dcfclk = 0xFFFF;
//	clk_mgr->base.bw_params->wm_table.nv_entries[WM_B].pmfw_अवरोधकरोwn.min_uclk = TUNED VALUE;
//	clk_mgr->base.bw_params->wm_table.nv_entries[WM_B].pmfw_अवरोधकरोwn.max_uclk = 0xFFFF;

	/* Set C - Dummy P-State - P-State latency set to "dummy p-state" value */
	clk_mgr->base.bw_params->wm_table.nv_entries[WM_C].valid = true;
	clk_mgr->base.bw_params->wm_table.nv_entries[WM_C].dml_input.pstate_latency_us = clk_mgr->base.ctx->dc->dml.soc.dummy_pstate_latency_us;
	clk_mgr->base.bw_params->wm_table.nv_entries[WM_C].dml_input.sr_निकास_समय_us = sr_निकास_समय_us;
	clk_mgr->base.bw_params->wm_table.nv_entries[WM_C].dml_input.sr_enter_plus_निकास_समय_us = sr_enter_plus_निकास_समय_us;
	clk_mgr->base.bw_params->wm_table.nv_entries[WM_C].pmfw_अवरोधकरोwn.wm_type = WATERMARKS_DUMMY_PSTATE;
	clk_mgr->base.bw_params->wm_table.nv_entries[WM_C].pmfw_अवरोधकरोwn.min_dcfclk = 0;
	clk_mgr->base.bw_params->wm_table.nv_entries[WM_C].pmfw_अवरोधकरोwn.max_dcfclk = 0xFFFF;
	clk_mgr->base.bw_params->wm_table.nv_entries[WM_C].pmfw_अवरोधकरोwn.min_uclk = min_uclk_mhz;
	clk_mgr->base.bw_params->wm_table.nv_entries[WM_C].pmfw_अवरोधकरोwn.max_uclk = 0xFFFF;

	/* Set D - MALL - SR enter and निकास बार adjusted क्रम MALL */
	clk_mgr->base.bw_params->wm_table.nv_entries[WM_D].valid = true;
	clk_mgr->base.bw_params->wm_table.nv_entries[WM_D].dml_input.pstate_latency_us = pstate_latency_us;
	clk_mgr->base.bw_params->wm_table.nv_entries[WM_D].dml_input.sr_निकास_समय_us = 2;
	clk_mgr->base.bw_params->wm_table.nv_entries[WM_D].dml_input.sr_enter_plus_निकास_समय_us = 4;
	clk_mgr->base.bw_params->wm_table.nv_entries[WM_D].pmfw_अवरोधकरोwn.wm_type = WATERMARKS_MALL;
	clk_mgr->base.bw_params->wm_table.nv_entries[WM_D].pmfw_अवरोधकरोwn.min_dcfclk = 0;
	clk_mgr->base.bw_params->wm_table.nv_entries[WM_D].pmfw_अवरोधकरोwn.max_dcfclk = 0xFFFF;
	clk_mgr->base.bw_params->wm_table.nv_entries[WM_D].pmfw_अवरोधकरोwn.min_uclk = min_uclk_mhz;
	clk_mgr->base.bw_params->wm_table.nv_entries[WM_D].pmfw_अवरोधकरोwn.max_uclk = 0xFFFF;
पूर्ण

व्योम dcn3_init_घड़ीs(काष्ठा clk_mgr *clk_mgr_base)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);
	अचिन्हित पूर्णांक num_levels;

	स_रखो(&(clk_mgr_base->clks), 0, माप(काष्ठा dc_घड़ीs));
	clk_mgr_base->clks.p_state_change_support = true;
	clk_mgr_base->clks.prev_p_state_change_support = true;
	clk_mgr->smu_present = false;

	अगर (!clk_mgr_base->bw_params)
		वापस;

	अगर (!clk_mgr_base->क्रमce_smu_not_present && dcn30_smu_get_smu_version(clk_mgr, &clk_mgr->smu_ver))
		clk_mgr->smu_present = true;

	अगर (!clk_mgr->smu_present)
		वापस;

	// करो we fail अगर these fail? अगर so, how? करो we not care to check?
	dcn30_smu_check_driver_अगर_version(clk_mgr);
	dcn30_smu_check_msg_header_version(clk_mgr);

	/* DCFCLK */
	dcn3_init_single_घड़ी(clk_mgr, PPCLK_DCEFCLK,
			&clk_mgr_base->bw_params->clk_table.entries[0].dcfclk_mhz,
			&num_levels);

	/* DTBCLK */
	dcn3_init_single_घड़ी(clk_mgr, PPCLK_DTBCLK,
			&clk_mgr_base->bw_params->clk_table.entries[0].dtbclk_mhz,
			&num_levels);

	// DPREFCLK ???

	/* DISPCLK */
	dcn3_init_single_घड़ी(clk_mgr, PPCLK_DISPCLK,
			&clk_mgr_base->bw_params->clk_table.entries[0].dispclk_mhz,
			&num_levels);

	/* DPPCLK */
	dcn3_init_single_घड़ी(clk_mgr, PPCLK_PIXCLK,
			&clk_mgr_base->bw_params->clk_table.entries[0].dppclk_mhz,
			&num_levels);

	/* PHYCLK */
	dcn3_init_single_घड़ी(clk_mgr, PPCLK_PHYCLK,
			&clk_mgr_base->bw_params->clk_table.entries[0].phyclk_mhz,
			&num_levels);

	/* Get UCLK, update bounding box */
	clk_mgr_base->funcs->get_memclk_states_from_smu(clk_mgr_base);

	/* WM range table */
	DC_FP_START();
	dcn3_build_wm_range_table(clk_mgr);
	DC_FP_END();
पूर्ण

अटल पूर्णांक dcn30_get_vco_frequency_from_reg(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr)
अणु
	/* get FbMult value */
	काष्ठा fixed31_32 pll_req;
	/* get FbMult value */
	uपूर्णांक32_t pll_req_reg = REG_READ(CLK0_CLK_PLL_REQ);

	/* set up a fixed-poपूर्णांक number
	 * this works because the पूर्णांक part is on the right edge of the रेजिस्टर
	 * and the frac part is on the left edge
	 */
	pll_req = dc_fixpt_from_पूर्णांक(pll_req_reg & clk_mgr->clk_mgr_mask->FbMult_पूर्णांक);
	pll_req.value |= pll_req_reg & clk_mgr->clk_mgr_mask->FbMult_frac;

	/* multiply by REFCLK period */
	pll_req = dc_fixpt_mul_पूर्णांक(pll_req, clk_mgr->dfs_ref_freq_khz);

	वापस dc_fixpt_न्यूनमान(pll_req);
पूर्ण

अटल व्योम dcn3_update_घड़ीs(काष्ठा clk_mgr *clk_mgr_base,
			काष्ठा dc_state *context,
			bool safe_to_lower)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);
	काष्ठा dc_घड़ीs *new_घड़ीs = &context->bw_ctx.bw.dcn.clk;
	काष्ठा dc *dc = clk_mgr_base->ctx->dc;
	पूर्णांक display_count;
	bool update_dppclk = false;
	bool update_dispclk = false;
	bool enter_display_off = false;
	bool dpp_घड़ी_lowered = false;
	काष्ठा dmcu *dmcu = clk_mgr_base->ctx->dc->res_pool->dmcu;
	bool क्रमce_reset = false;
	bool update_uclk = false;
	bool p_state_change_support;
	पूर्णांक total_plane_count;

	अगर (dc->work_arounds.skip_घड़ी_update || !clk_mgr->smu_present)
		वापस;

	अगर (clk_mgr_base->clks.dispclk_khz == 0 ||
			(dc->debug.क्रमce_घड़ी_mode & 0x1)) अणु
		/* this is from resume or boot up, अगर क्रमced_घड़ी cfg option used, we bypass program dispclk and DPPCLK, but need set them क्रम S3. */
		क्रमce_reset = true;

		dcn2_पढ़ो_घड़ीs_from_hw_dentist(clk_mgr_base);

		/* क्रमce_घड़ी_mode 0x1:  क्रमce reset the घड़ी even it is the same घड़ी as दीर्घ as it is in Passive level. */
	पूर्ण
	display_count = clk_mgr_helper_get_active_display_cnt(dc, context);

	अगर (display_count == 0)
		enter_display_off = true;

	अगर (enter_display_off == safe_to_lower)
		dcn30_smu_set_num_of_displays(clk_mgr, display_count);

	अगर (dc->debug.क्रमce_min_dcfclk_mhz > 0)
		new_घड़ीs->dcfclk_khz = (new_घड़ीs->dcfclk_khz > (dc->debug.क्रमce_min_dcfclk_mhz * 1000)) ?
				new_घड़ीs->dcfclk_khz : (dc->debug.क्रमce_min_dcfclk_mhz * 1000);

	अगर (should_set_घड़ी(safe_to_lower, new_घड़ीs->dcfclk_khz, clk_mgr_base->clks.dcfclk_khz)) अणु
		clk_mgr_base->clks.dcfclk_khz = new_घड़ीs->dcfclk_khz;
		dcn30_smu_set_hard_min_by_freq(clk_mgr, PPCLK_DCEFCLK, clk_mgr_base->clks.dcfclk_khz / 1000);
	पूर्ण

	अगर (should_set_घड़ी(safe_to_lower, new_घड़ीs->dcfclk_deep_sleep_khz, clk_mgr_base->clks.dcfclk_deep_sleep_khz)) अणु
		clk_mgr_base->clks.dcfclk_deep_sleep_khz = new_घड़ीs->dcfclk_deep_sleep_khz;
		dcn30_smu_set_min_deep_sleep_dcef_clk(clk_mgr, clk_mgr_base->clks.dcfclk_deep_sleep_khz / 1000);
	पूर्ण

	अगर (should_set_घड़ी(safe_to_lower, new_घड़ीs->socclk_khz, clk_mgr_base->clks.socclk_khz))
		/* We करोn't actually care about socclk, don't notअगरy SMU of hard min */
		clk_mgr_base->clks.socclk_khz = new_घड़ीs->socclk_khz;

	clk_mgr_base->clks.prev_p_state_change_support = clk_mgr_base->clks.p_state_change_support;
	total_plane_count = clk_mgr_helper_get_active_plane_cnt(dc, context);
	p_state_change_support = new_घड़ीs->p_state_change_support || (total_plane_count == 0);
	अगर (should_update_pstate_support(safe_to_lower, p_state_change_support, clk_mgr_base->clks.p_state_change_support)) अणु
		clk_mgr_base->clks.p_state_change_support = p_state_change_support;

		/* to disable P-State चयनing, set UCLK min = max */
		अगर (!clk_mgr_base->clks.p_state_change_support)
			dcn30_smu_set_hard_min_by_freq(clk_mgr, PPCLK_UCLK,
					clk_mgr_base->bw_params->clk_table.entries[clk_mgr_base->bw_params->clk_table.num_entries - 1].memclk_mhz);
	पूर्ण

	/* Always update saved value, even अगर new value not set due to P-State चयनing unsupported */
	अगर (should_set_घड़ी(safe_to_lower, new_घड़ीs->dramclk_khz, clk_mgr_base->clks.dramclk_khz)) अणु
		clk_mgr_base->clks.dramclk_khz = new_घड़ीs->dramclk_khz;
		update_uclk = true;
	पूर्ण

	/* set UCLK to requested value अगर P-State चयनing is supported, or to re-enable P-State चयनing */
	अगर (clk_mgr_base->clks.p_state_change_support &&
			(update_uclk || !clk_mgr_base->clks.prev_p_state_change_support))
		dcn30_smu_set_hard_min_by_freq(clk_mgr, PPCLK_UCLK, clk_mgr_base->clks.dramclk_khz / 1000);

	अगर (should_set_घड़ी(safe_to_lower, new_घड़ीs->dppclk_khz, clk_mgr_base->clks.dppclk_khz)) अणु
		अगर (clk_mgr_base->clks.dppclk_khz > new_घड़ीs->dppclk_khz)
			dpp_घड़ी_lowered = true;

		clk_mgr_base->clks.dppclk_khz = new_घड़ीs->dppclk_khz;
		dcn30_smu_set_hard_min_by_freq(clk_mgr, PPCLK_PIXCLK, clk_mgr_base->clks.dppclk_khz / 1000);
		update_dppclk = true;
	पूर्ण

	अगर (should_set_घड़ी(safe_to_lower, new_घड़ीs->dispclk_khz, clk_mgr_base->clks.dispclk_khz)) अणु
		clk_mgr_base->clks.dispclk_khz = new_घड़ीs->dispclk_khz;
		dcn30_smu_set_hard_min_by_freq(clk_mgr, PPCLK_DISPCLK, clk_mgr_base->clks.dispclk_khz / 1000);
		update_dispclk = true;
	पूर्ण

	अगर (dc->config.क्रमced_घड़ीs == false || (क्रमce_reset && safe_to_lower)) अणु
		अगर (dpp_घड़ी_lowered) अणु
			/* अगर घड़ी is being lowered, increase DTO beक्रमe lowering refclk */
			dcn20_update_घड़ीs_update_dpp_dto(clk_mgr, context, safe_to_lower);
			dcn20_update_घड़ीs_update_dentist(clk_mgr);
		पूर्ण अन्यथा अणु
			/* अगर घड़ी is being उठाओd, increase refclk beक्रमe lowering DTO */
			अगर (update_dppclk || update_dispclk)
				dcn20_update_घड़ीs_update_dentist(clk_mgr);
			/* There is a check inside dcn20_update_घड़ीs_update_dpp_dto which ensures
			 * that we करो not lower dto when it is not safe to lower. We करो not need to
			 * compare the current and new dppclk beक्रमe calling this function.*/
			dcn20_update_घड़ीs_update_dpp_dto(clk_mgr, context, safe_to_lower);
		पूर्ण
	पूर्ण

	अगर (update_dispclk && dmcu && dmcu->funcs->is_dmcu_initialized(dmcu))
		/*update dmcu क्रम रुको_loop count*/
		dmcu->funcs->set_psr_रुको_loop(dmcu,
				clk_mgr_base->clks.dispclk_khz / 1000 / 7);
पूर्ण


अटल व्योम dcn3_notअगरy_wm_ranges(काष्ठा clk_mgr *clk_mgr_base)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);
	WatermarksExternal_t *table = (WatermarksExternal_t *) clk_mgr->wm_range_table;

	अगर (!clk_mgr->smu_present)
		वापस;

	अगर (!table)
		// should log failure
		वापस;

	स_रखो(table, 0, माप(*table));

	/* collect valid ranges, place in pmfw table */
	क्रम (i = 0; i < WM_SET_COUNT; i++)
		अगर (clk_mgr->base.bw_params->wm_table.nv_entries[i].valid) अणु
			table->Watermarks.WatermarkRow[WM_DCEFCLK][i].MinClock = clk_mgr->base.bw_params->wm_table.nv_entries[i].pmfw_अवरोधकरोwn.min_dcfclk;
			table->Watermarks.WatermarkRow[WM_DCEFCLK][i].MaxClock = clk_mgr->base.bw_params->wm_table.nv_entries[i].pmfw_अवरोधकरोwn.max_dcfclk;
			table->Watermarks.WatermarkRow[WM_DCEFCLK][i].MinUclk = clk_mgr->base.bw_params->wm_table.nv_entries[i].pmfw_अवरोधकरोwn.min_uclk;
			table->Watermarks.WatermarkRow[WM_DCEFCLK][i].MaxUclk = clk_mgr->base.bw_params->wm_table.nv_entries[i].pmfw_अवरोधकरोwn.max_uclk;
			table->Watermarks.WatermarkRow[WM_DCEFCLK][i].WmSetting = i;
			table->Watermarks.WatermarkRow[WM_DCEFCLK][i].Flags = clk_mgr->base.bw_params->wm_table.nv_entries[i].pmfw_अवरोधकरोwn.wm_type;
		पूर्ण

	dcn30_smu_set_dram_addr_high(clk_mgr, clk_mgr->wm_range_table_addr >> 32);
	dcn30_smu_set_dram_addr_low(clk_mgr, clk_mgr->wm_range_table_addr & 0xFFFFFFFF);
	dcn30_smu_transfer_wm_table_dram_2_smu(clk_mgr);
पूर्ण

/* Set min memclk to minimum, either स्थिरrained by the current mode or DPM0 */
अटल व्योम dcn3_set_hard_min_memclk(काष्ठा clk_mgr *clk_mgr_base, bool current_mode)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);

	अगर (!clk_mgr->smu_present)
		वापस;

	अगर (current_mode)
		dcn30_smu_set_hard_min_by_freq(clk_mgr, PPCLK_UCLK,
				clk_mgr_base->clks.dramclk_khz / 1000);
	अन्यथा
		dcn30_smu_set_hard_min_by_freq(clk_mgr, PPCLK_UCLK,
				clk_mgr_base->bw_params->clk_table.entries[0].memclk_mhz);
पूर्ण

/* Set max memclk to highest DPM value */
अटल व्योम dcn3_set_hard_max_memclk(काष्ठा clk_mgr *clk_mgr_base)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);

	अगर (!clk_mgr->smu_present)
		वापस;

	dcn30_smu_set_hard_max_by_freq(clk_mgr, PPCLK_UCLK,
			clk_mgr_base->bw_params->clk_table.entries[clk_mgr_base->bw_params->clk_table.num_entries - 1].memclk_mhz);
पूर्ण

/* Get current memclk states, update bounding box */
अटल व्योम dcn3_get_memclk_states_from_smu(काष्ठा clk_mgr *clk_mgr_base)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);
	अचिन्हित पूर्णांक num_levels;

	अगर (!clk_mgr->smu_present)
		वापस;

	/* Refresh memclk states */
	dcn3_init_single_घड़ी(clk_mgr, PPCLK_UCLK,
			&clk_mgr_base->bw_params->clk_table.entries[0].memclk_mhz,
			&num_levels);
	clk_mgr_base->bw_params->clk_table.num_entries = num_levels ? num_levels : 1;

	/* Refresh bounding box */
	clk_mgr_base->ctx->dc->res_pool->funcs->update_bw_bounding_box(
			clk_mgr->base.ctx->dc, clk_mgr_base->bw_params);
पूर्ण

अटल bool dcn3_is_smu_present(काष्ठा clk_mgr *clk_mgr_base)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);
	वापस clk_mgr->smu_present;
पूर्ण

अटल bool dcn3_are_घड़ी_states_equal(काष्ठा dc_घड़ीs *a,
					काष्ठा dc_घड़ीs *b)
अणु
	अगर (a->dispclk_khz != b->dispclk_khz)
		वापस false;
	अन्यथा अगर (a->dppclk_khz != b->dppclk_khz)
		वापस false;
	अन्यथा अगर (a->dcfclk_khz != b->dcfclk_khz)
		वापस false;
	अन्यथा अगर (a->dcfclk_deep_sleep_khz != b->dcfclk_deep_sleep_khz)
		वापस false;
	अन्यथा अगर (a->dramclk_khz != b->dramclk_khz)
		वापस false;
	अन्यथा अगर (a->p_state_change_support != b->p_state_change_support)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम dcn3_enable_pme_wa(काष्ठा clk_mgr *clk_mgr_base)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);

	अगर (!clk_mgr->smu_present)
		वापस;

	dcn30_smu_set_pme_workaround(clk_mgr);
पूर्ण

/* Notअगरy clk_mgr of a change in link rate, update phyclk frequency अगर necessary */
अटल व्योम dcn30_notअगरy_link_rate_change(काष्ठा clk_mgr *clk_mgr_base, काष्ठा dc_link *link)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);
	अचिन्हित पूर्णांक i, max_phyclk_req = clk_mgr_base->bw_params->clk_table.entries[0].phyclk_mhz * 1000;

	अगर (!clk_mgr->smu_present)
		वापस;

	clk_mgr->cur_phyclk_req_table[link->link_index] = link->cur_link_settings.link_rate * LINK_RATE_REF_FREQ_IN_KHZ;

	क्रम (i = 0; i < MAX_PIPES * 2; i++) अणु
		अगर (clk_mgr->cur_phyclk_req_table[i] > max_phyclk_req)
			max_phyclk_req = clk_mgr->cur_phyclk_req_table[i];
	पूर्ण

	अगर (max_phyclk_req != clk_mgr_base->clks.phyclk_khz) अणु
		clk_mgr_base->clks.phyclk_khz = max_phyclk_req;
		dcn30_smu_set_hard_min_by_freq(clk_mgr, PPCLK_PHYCLK, clk_mgr_base->clks.phyclk_khz / 1000);
	पूर्ण
पूर्ण

अटल काष्ठा clk_mgr_funcs dcn3_funcs = अणु
		.get_dp_ref_clk_frequency = dce12_get_dp_ref_freq_khz,
		.update_घड़ीs = dcn3_update_घड़ीs,
		.init_घड़ीs = dcn3_init_घड़ीs,
		.notअगरy_wm_ranges = dcn3_notअगरy_wm_ranges,
		.set_hard_min_memclk = dcn3_set_hard_min_memclk,
		.set_hard_max_memclk = dcn3_set_hard_max_memclk,
		.get_memclk_states_from_smu = dcn3_get_memclk_states_from_smu,
		.are_घड़ी_states_equal = dcn3_are_घड़ी_states_equal,
		.enable_pme_wa = dcn3_enable_pme_wa,
		.notअगरy_link_rate_change = dcn30_notअगरy_link_rate_change,
		.is_smu_present = dcn3_is_smu_present
पूर्ण;

अटल व्योम dcn3_init_घड़ीs_fpga(काष्ठा clk_mgr *clk_mgr)
अणु
	dcn2_init_घड़ीs(clk_mgr);

/* TODO: Implement the functions and हटाओ the अगरndef guard */
पूर्ण

काष्ठा clk_mgr_funcs dcn3_fpga_funcs = अणु
	.get_dp_ref_clk_frequency = dce12_get_dp_ref_freq_khz,
	.update_घड़ीs = dcn2_update_घड़ीs_fpga,
	.init_घड़ीs = dcn3_init_घड़ीs_fpga,
पूर्ण;

/*toकरो क्रम dcn30 क्रम clk रेजिस्टर offset*/
व्योम dcn3_clk_mgr_स्थिरruct(
		काष्ठा dc_context *ctx,
		काष्ठा clk_mgr_पूर्णांकernal *clk_mgr,
		काष्ठा pp_smu_funcs *pp_smu,
		काष्ठा dccg *dccg)
अणु
	clk_mgr->base.ctx = ctx;
	clk_mgr->base.funcs = &dcn3_funcs;
	clk_mgr->regs = &clk_mgr_regs;
	clk_mgr->clk_mgr_shअगरt = &clk_mgr_shअगरt;
	clk_mgr->clk_mgr_mask = &clk_mgr_mask;

	clk_mgr->dccg = dccg;
	clk_mgr->dfs_bypass_disp_clk = 0;

	clk_mgr->dprefclk_ss_percentage = 0;
	clk_mgr->dprefclk_ss_भागider = 1000;
	clk_mgr->ss_on_dprefclk = false;
	clk_mgr->dfs_ref_freq_khz = 100000;

	clk_mgr->base.dprefclk_khz = 730000; // 700 MHz planned अगर VCO is 3.85 GHz, will be retrieved

	अगर (IS_FPGA_MAXIMUS_DC(ctx->dce_environment)) अणु
		clk_mgr->base.funcs  = &dcn3_fpga_funcs;
		clk_mgr->base.dentist_vco_freq_khz = 3650000;

	पूर्ण अन्यथा अणु
		काष्ठा clk_state_रेजिस्टरs_and_bypass s = अणु 0 पूर्ण;

		/* पूर्णांकeger part is now VCO frequency in kHz */
		clk_mgr->base.dentist_vco_freq_khz = dcn30_get_vco_frequency_from_reg(clk_mgr);

		/* in हाल we करोn't get a value from the रेजिस्टर, use शेष */
		अगर (clk_mgr->base.dentist_vco_freq_khz == 0)
			clk_mgr->base.dentist_vco_freq_khz = 3650000;
		/* Convert dprefclk units from MHz to KHz */
		/* Value alपढ़ोy भागided by 10, some resolution lost */

		/*TODO: uncomment निश्चित once dcn3_dump_clk_रेजिस्टरs is implemented */
		//ASSERT(s.dprefclk != 0);
		अगर (s.dprefclk != 0)
			clk_mgr->base.dprefclk_khz = s.dprefclk * 1000;
	पूर्ण

	clk_mgr->dfs_bypass_enabled = false;

	clk_mgr->smu_present = false;

	dce_घड़ी_पढ़ो_ss_info(clk_mgr);

	clk_mgr->base.bw_params = kzalloc(माप(*clk_mgr->base.bw_params), GFP_KERNEL);

	/* need physical address of table to give to PMFW */
	clk_mgr->wm_range_table = dm_helpers_allocate_gpu_mem(clk_mgr->base.ctx,
			DC_MEM_ALLOC_TYPE_GART, माप(WatermarksExternal_t),
			&clk_mgr->wm_range_table_addr);
पूर्ण

व्योम dcn3_clk_mgr_destroy(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr)
अणु
	kमुक्त(clk_mgr->base.bw_params);

	अगर (clk_mgr->wm_range_table)
		dm_helpers_मुक्त_gpu_mem(clk_mgr->base.ctx, DC_MEM_ALLOC_TYPE_GART,
				clk_mgr->wm_range_table);
पूर्ण
