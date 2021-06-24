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

#समावेश "dccg.h"
#समावेश "clk_mgr_internal.h"

#समावेश "dce100/dce_clk_mgr.h"
#समावेश "dcn20_clk_mgr.h"
#समावेश "reg_helper.h"
#समावेश "core_types.h"
#समावेश "dm_helpers.h"

#समावेश "navi10_ip_offset.h"
#समावेश "dcn/dcn_2_0_0_offset.h"
#समावेश "dcn/dcn_2_0_0_sh_mask.h"
#समावेश "clk/clk_11_0_0_offset.h"
#समावेश "clk/clk_11_0_0_sh_mask.h"

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

#घोषणा CLK_BASE_INNER(seg) \
	CLK_BASE__INST0_SEG ## seg


अटल स्थिर काष्ठा clk_mgr_रेजिस्टरs clk_mgr_regs = अणु
	CLK_REG_LIST_NV10()
पूर्ण;

अटल स्थिर काष्ठा clk_mgr_shअगरt clk_mgr_shअगरt = अणु
	CLK_MASK_SH_LIST_NV10(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा clk_mgr_mask clk_mgr_mask = अणु
	CLK_MASK_SH_LIST_NV10(_MASK)
पूर्ण;

uपूर्णांक32_t dentist_get_did_from_भागider(पूर्णांक भागider)
अणु
	uपूर्णांक32_t भागider_id;

	/* we want to न्यूनमान here to get higher घड़ी than required rather than lower */
	अगर (भागider < DENTIST_DIVIDER_RANGE_2_START) अणु
		अगर (भागider < DENTIST_DIVIDER_RANGE_1_START)
			भागider_id = DENTIST_BASE_DID_1;
		अन्यथा
			भागider_id = DENTIST_BASE_DID_1
				+ (भागider - DENTIST_DIVIDER_RANGE_1_START)
					/ DENTIST_DIVIDER_RANGE_1_STEP;
	पूर्ण अन्यथा अगर (भागider < DENTIST_DIVIDER_RANGE_3_START) अणु
		भागider_id = DENTIST_BASE_DID_2
				+ (भागider - DENTIST_DIVIDER_RANGE_2_START)
					/ DENTIST_DIVIDER_RANGE_2_STEP;
	पूर्ण अन्यथा अगर (भागider < DENTIST_DIVIDER_RANGE_4_START) अणु
		भागider_id = DENTIST_BASE_DID_3
				+ (भागider - DENTIST_DIVIDER_RANGE_3_START)
					/ DENTIST_DIVIDER_RANGE_3_STEP;
	पूर्ण अन्यथा अणु
		भागider_id = DENTIST_BASE_DID_4
				+ (भागider - DENTIST_DIVIDER_RANGE_4_START)
					/ DENTIST_DIVIDER_RANGE_4_STEP;
		अगर (भागider_id > DENTIST_MAX_DID)
			भागider_id = DENTIST_MAX_DID;
	पूर्ण

	वापस भागider_id;
पूर्ण

व्योम dcn20_update_घड़ीs_update_dpp_dto(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr,
		काष्ठा dc_state *context, bool safe_to_lower)
अणु
	पूर्णांक i;

	clk_mgr->dccg->ref_dppclk = clk_mgr->base.clks.dppclk_khz;
	क्रम (i = 0; i < clk_mgr->base.ctx->dc->res_pool->pipe_count; i++) अणु
		पूर्णांक dpp_inst, dppclk_khz, prev_dppclk_khz;

		/* Loop index will match dpp->inst अगर resource exists,
		 * and we want to aव्योम dependency on dpp object
		 */
		dpp_inst = i;
		dppclk_khz = context->res_ctx.pipe_ctx[i].plane_res.bw.dppclk_khz;

		prev_dppclk_khz = clk_mgr->dccg->pipe_dppclk_khz[i];

		अगर (safe_to_lower || prev_dppclk_khz < dppclk_khz)
			clk_mgr->dccg->funcs->update_dpp_dto(
							clk_mgr->dccg, dpp_inst, dppclk_khz);
	पूर्ण
पूर्ण

व्योम dcn20_update_घड़ीs_update_dentist(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr)
अणु
	पूर्णांक dpp_भागider = DENTIST_DIVIDER_RANGE_SCALE_FACTOR
			* clk_mgr->base.dentist_vco_freq_khz / clk_mgr->base.clks.dppclk_khz;
	पूर्णांक disp_भागider = DENTIST_DIVIDER_RANGE_SCALE_FACTOR
			* clk_mgr->base.dentist_vco_freq_khz / clk_mgr->base.clks.dispclk_khz;

	uपूर्णांक32_t dppclk_wभागider = dentist_get_did_from_भागider(dpp_भागider);
	uपूर्णांक32_t dispclk_wभागider = dentist_get_did_from_भागider(disp_भागider);

	REG_UPDATE(DENTIST_DISPCLK_CNTL,
			DENTIST_DISPCLK_WDIVIDER, dispclk_wभागider);
//	REG_WAIT(DENTIST_DISPCLK_CNTL, DENTIST_DISPCLK_CHG_DONE, 1, 5, 100);
	REG_UPDATE(DENTIST_DISPCLK_CNTL,
			DENTIST_DPPCLK_WDIVIDER, dppclk_wभागider);
	REG_WAIT(DENTIST_DISPCLK_CNTL, DENTIST_DPPCLK_CHG_DONE, 1, 5, 100);
पूर्ण


व्योम dcn2_update_घड़ीs(काष्ठा clk_mgr *clk_mgr_base,
			काष्ठा dc_state *context,
			bool safe_to_lower)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);
	काष्ठा dc_घड़ीs *new_घड़ीs = &context->bw_ctx.bw.dcn.clk;
	काष्ठा dc *dc = clk_mgr_base->ctx->dc;
	काष्ठा pp_smu_funcs_nv *pp_smu = शून्य;
	पूर्णांक display_count;
	bool update_dppclk = false;
	bool update_dispclk = false;
	bool enter_display_off = false;
	bool dpp_घड़ी_lowered = false;
	काष्ठा dmcu *dmcu = clk_mgr_base->ctx->dc->res_pool->dmcu;
	bool क्रमce_reset = false;
	bool p_state_change_support;
	पूर्णांक total_plane_count;

	अगर (dc->work_arounds.skip_घड़ी_update)
		वापस;

	अगर (clk_mgr_base->clks.dispclk_khz == 0 ||
		dc->debug.क्रमce_घड़ी_mode & 0x1) अणु
		//this is from resume or boot up, अगर क्रमced_घड़ी cfg option used, we bypass program dispclk and DPPCLK, but need set them क्रम S3.
		क्रमce_reset = true;

		dcn2_पढ़ो_घड़ीs_from_hw_dentist(clk_mgr_base);

		//क्रमce_घड़ी_mode 0x1:  क्रमce reset the घड़ी even it is the same घड़ी as दीर्घ as it is in Passive level.
	पूर्ण
	display_count = clk_mgr_helper_get_active_display_cnt(dc, context);
	अगर (dc->res_pool->pp_smu)
		pp_smu = &dc->res_pool->pp_smu->nv_funcs;

	अगर (display_count == 0)
		enter_display_off = true;

	अगर (enter_display_off == safe_to_lower) अणु
		अगर (pp_smu && pp_smu->set_display_count)
			pp_smu->set_display_count(&pp_smu->pp_smu, display_count);
	पूर्ण

	अगर (dc->debug.क्रमce_min_dcfclk_mhz > 0)
		new_घड़ीs->dcfclk_khz = (new_घड़ीs->dcfclk_khz > (dc->debug.क्रमce_min_dcfclk_mhz * 1000)) ?
				new_घड़ीs->dcfclk_khz : (dc->debug.क्रमce_min_dcfclk_mhz * 1000);

	अगर (should_set_घड़ी(safe_to_lower, new_घड़ीs->dcfclk_khz, clk_mgr_base->clks.dcfclk_khz)) अणु
		clk_mgr_base->clks.dcfclk_khz = new_घड़ीs->dcfclk_khz;
		अगर (pp_smu && pp_smu->set_hard_min_dcfclk_by_freq)
			pp_smu->set_hard_min_dcfclk_by_freq(&pp_smu->pp_smu, clk_mgr_base->clks.dcfclk_khz / 1000);
	पूर्ण

	अगर (should_set_घड़ी(safe_to_lower,
			new_घड़ीs->dcfclk_deep_sleep_khz, clk_mgr_base->clks.dcfclk_deep_sleep_khz)) अणु
		clk_mgr_base->clks.dcfclk_deep_sleep_khz = new_घड़ीs->dcfclk_deep_sleep_khz;
		अगर (pp_smu && pp_smu->set_min_deep_sleep_dcfclk)
			pp_smu->set_min_deep_sleep_dcfclk(&pp_smu->pp_smu, clk_mgr_base->clks.dcfclk_deep_sleep_khz / 1000);
	पूर्ण

	अगर (should_set_घड़ी(safe_to_lower, new_घड़ीs->socclk_khz, clk_mgr_base->clks.socclk_khz)) अणु
		clk_mgr_base->clks.socclk_khz = new_घड़ीs->socclk_khz;
		अगर (pp_smu && pp_smu->set_hard_min_socclk_by_freq)
			pp_smu->set_hard_min_socclk_by_freq(&pp_smu->pp_smu, clk_mgr_base->clks.socclk_khz / 1000);
	पूर्ण

	total_plane_count = clk_mgr_helper_get_active_plane_cnt(dc, context);
	p_state_change_support = new_घड़ीs->p_state_change_support || (total_plane_count == 0);
	अगर (should_update_pstate_support(safe_to_lower, p_state_change_support, clk_mgr_base->clks.p_state_change_support)) अणु
		clk_mgr_base->clks.prev_p_state_change_support = clk_mgr_base->clks.p_state_change_support;
		clk_mgr_base->clks.p_state_change_support = p_state_change_support;
		अगर (pp_smu && pp_smu->set_pstate_handshake_support)
			pp_smu->set_pstate_handshake_support(&pp_smu->pp_smu, clk_mgr_base->clks.p_state_change_support);
	पूर्ण

	अगर (should_set_घड़ी(safe_to_lower, new_घड़ीs->dramclk_khz, clk_mgr_base->clks.dramclk_khz)) अणु
		clk_mgr_base->clks.dramclk_khz = new_घड़ीs->dramclk_khz;
		अगर (pp_smu && pp_smu->set_hard_min_uclk_by_freq)
			pp_smu->set_hard_min_uclk_by_freq(&pp_smu->pp_smu, clk_mgr_base->clks.dramclk_khz / 1000);
	पूर्ण

	अगर (should_set_घड़ी(safe_to_lower, new_घड़ीs->dppclk_khz, clk_mgr->base.clks.dppclk_khz)) अणु
		अगर (clk_mgr->base.clks.dppclk_khz > new_घड़ीs->dppclk_khz)
			dpp_घड़ी_lowered = true;
		clk_mgr->base.clks.dppclk_khz = new_घड़ीs->dppclk_khz;

		update_dppclk = true;
	पूर्ण

	अगर (should_set_घड़ी(safe_to_lower, new_घड़ीs->dispclk_khz, clk_mgr_base->clks.dispclk_khz)) अणु
		clk_mgr_base->clks.dispclk_khz = new_घड़ीs->dispclk_khz;

		update_dispclk = true;
	पूर्ण

	अगर (update_dppclk || update_dispclk) अणु
		new_घड़ीs->disp_dpp_voltage_level_khz = new_घड़ीs->dppclk_khz;

		अगर (update_dispclk)
			new_घड़ीs->disp_dpp_voltage_level_khz = new_घड़ीs->dispclk_khz > new_घड़ीs->dppclk_khz ? new_घड़ीs->dispclk_khz : new_घड़ीs->dppclk_khz;

		clk_mgr_base->clks.disp_dpp_voltage_level_khz = new_घड़ीs->disp_dpp_voltage_level_khz;
		अगर (pp_smu && pp_smu->set_voltage_by_freq)
			pp_smu->set_voltage_by_freq(&pp_smu->pp_smu, PP_SMU_NV_DISPCLK, clk_mgr_base->clks.disp_dpp_voltage_level_khz / 1000);
	पूर्ण

	अगर (dc->config.क्रमced_घड़ीs == false || (क्रमce_reset && safe_to_lower)) अणु
		अगर (dpp_घड़ी_lowered) अणु
			// अगर घड़ी is being lowered, increase DTO beक्रमe lowering refclk
			dcn20_update_घड़ीs_update_dpp_dto(clk_mgr, context, safe_to_lower);
			dcn20_update_घड़ीs_update_dentist(clk_mgr);
		पूर्ण अन्यथा अणु
			// अगर घड़ी is being उठाओd, increase refclk beक्रमe lowering DTO
			अगर (update_dppclk || update_dispclk)
				dcn20_update_घड़ीs_update_dentist(clk_mgr);
			// always update dtos unless घड़ी is lowered and not safe to lower
			dcn20_update_घड़ीs_update_dpp_dto(clk_mgr, context, safe_to_lower);
		पूर्ण
	पूर्ण

	अगर (update_dispclk &&
			dmcu && dmcu->funcs->is_dmcu_initialized(dmcu)) अणु
		/*update dmcu क्रम रुको_loop count*/
		dmcu->funcs->set_psr_रुको_loop(dmcu,
			clk_mgr_base->clks.dispclk_khz / 1000 / 7);
	पूर्ण
पूर्ण

व्योम dcn2_update_घड़ीs_fpga(काष्ठा clk_mgr *clk_mgr,
		काष्ठा dc_state *context,
		bool safe_to_lower)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr_पूर्णांक = TO_CLK_MGR_INTERNAL(clk_mgr);

	काष्ठा dc_घड़ीs *new_घड़ीs = &context->bw_ctx.bw.dcn.clk;
	/* Min fclk = 1.2GHz since all the extra scemi logic seems to run off of it */
	पूर्णांक fclk_adj = new_घड़ीs->fclk_khz > 1200000 ? new_घड़ीs->fclk_khz : 1200000;

	अगर (should_set_घड़ी(safe_to_lower, new_घड़ीs->phyclk_khz, clk_mgr->clks.phyclk_khz)) अणु
		clk_mgr->clks.phyclk_khz = new_घड़ीs->phyclk_khz;
	पूर्ण

	अगर (should_set_घड़ी(safe_to_lower, new_घड़ीs->dcfclk_khz, clk_mgr->clks.dcfclk_khz)) अणु
		clk_mgr->clks.dcfclk_khz = new_घड़ीs->dcfclk_khz;
	पूर्ण

	अगर (should_set_घड़ी(safe_to_lower,
			new_घड़ीs->dcfclk_deep_sleep_khz, clk_mgr->clks.dcfclk_deep_sleep_khz)) अणु
		clk_mgr->clks.dcfclk_deep_sleep_khz = new_घड़ीs->dcfclk_deep_sleep_khz;
	पूर्ण

	अगर (should_set_घड़ी(safe_to_lower, new_घड़ीs->socclk_khz, clk_mgr->clks.socclk_khz)) अणु
		clk_mgr->clks.socclk_khz = new_घड़ीs->socclk_khz;
	पूर्ण

	अगर (should_set_घड़ी(safe_to_lower, new_घड़ीs->dramclk_khz, clk_mgr->clks.dramclk_khz)) अणु
		clk_mgr->clks.dramclk_khz = new_घड़ीs->dramclk_khz;
	पूर्ण

	अगर (should_set_घड़ी(safe_to_lower, new_घड़ीs->dppclk_khz, clk_mgr->clks.dppclk_khz)) अणु
		clk_mgr->clks.dppclk_khz = new_घड़ीs->dppclk_khz;
	पूर्ण

	अगर (should_set_घड़ी(safe_to_lower, fclk_adj, clk_mgr->clks.fclk_khz)) अणु
		clk_mgr->clks.fclk_khz = fclk_adj;
	पूर्ण

	अगर (should_set_घड़ी(safe_to_lower, new_घड़ीs->dispclk_khz, clk_mgr->clks.dispclk_khz)) अणु
		clk_mgr->clks.dispclk_khz = new_घड़ीs->dispclk_khz;
	पूर्ण

	/* Both fclk and ref_dppclk run on the same scemi घड़ी.
	 * So take the higher value since the DPP DTO is typically programmed
	 * such that max dppclk is 1:1 with ref_dppclk.
	 */
	अगर (clk_mgr->clks.fclk_khz > clk_mgr->clks.dppclk_khz)
		clk_mgr->clks.dppclk_khz = clk_mgr->clks.fclk_khz;
	अगर (clk_mgr->clks.dppclk_khz > clk_mgr->clks.fclk_khz)
		clk_mgr->clks.fclk_khz = clk_mgr->clks.dppclk_khz;

	// Both fclk and ref_dppclk run on the same scemi घड़ी.
	clk_mgr_पूर्णांक->dccg->ref_dppclk = clk_mgr->clks.fclk_khz;

	dm_set_dcn_घड़ीs(clk_mgr->ctx, &clk_mgr->clks);
पूर्ण

व्योम dcn2_init_घड़ीs(काष्ठा clk_mgr *clk_mgr)
अणु
	स_रखो(&(clk_mgr->clks), 0, माप(काष्ठा dc_घड़ीs));
	// Assumption is that boot state always supports pstate
	clk_mgr->clks.p_state_change_support = true;
	clk_mgr->clks.prev_p_state_change_support = true;
पूर्ण

व्योम dcn2_enable_pme_wa(काष्ठा clk_mgr *clk_mgr_base)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);
	काष्ठा pp_smu_funcs_nv *pp_smu = शून्य;

	अगर (clk_mgr->pp_smu) अणु
		pp_smu = &clk_mgr->pp_smu->nv_funcs;

		अगर (pp_smu->set_pme_wa_enable)
			pp_smu->set_pme_wa_enable(&pp_smu->pp_smu);
	पूर्ण
पूर्ण


व्योम dcn2_पढ़ो_घड़ीs_from_hw_dentist(काष्ठा clk_mgr *clk_mgr_base)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);
	uपूर्णांक32_t dispclk_wभागider;
	uपूर्णांक32_t dppclk_wभागider;
	पूर्णांक disp_भागider;
	पूर्णांक dpp_भागider;

	REG_GET(DENTIST_DISPCLK_CNTL, DENTIST_DISPCLK_WDIVIDER, &dispclk_wभागider);
	REG_GET(DENTIST_DISPCLK_CNTL, DENTIST_DPPCLK_WDIVIDER, &dppclk_wभागider);

	disp_भागider = dentist_get_भागider_from_did(dispclk_wभागider);
	dpp_भागider = dentist_get_भागider_from_did(dppclk_wभागider);

	अगर (disp_भागider && dpp_भागider) अणु
		/* Calculate the current DFS घड़ी, in kHz.*/
		clk_mgr_base->clks.dispclk_khz = (DENTIST_DIVIDER_RANGE_SCALE_FACTOR
			* clk_mgr->base.dentist_vco_freq_khz) / disp_भागider;

		clk_mgr_base->clks.dppclk_khz = (DENTIST_DIVIDER_RANGE_SCALE_FACTOR
				* clk_mgr->base.dentist_vco_freq_khz) / dpp_भागider;
	पूर्ण

पूर्ण

व्योम dcn2_get_घड़ी(काष्ठा clk_mgr *clk_mgr,
		काष्ठा dc_state *context,
			क्रमागत dc_घड़ी_प्रकारype घड़ी_प्रकारype,
			काष्ठा dc_घड़ी_config *घड़ी_cfg)
अणु

	अगर (घड़ी_प्रकारype == DC_CLOCK_TYPE_DISPCLK) अणु
		घड़ी_cfg->max_घड़ी_khz = context->bw_ctx.bw.dcn.clk.max_supported_dispclk_khz;
		घड़ी_cfg->min_घड़ी_khz = DCN_MINIMUM_DISPCLK_Khz;
		घड़ी_cfg->current_घड़ी_khz = clk_mgr->clks.dispclk_khz;
		घड़ी_cfg->bw_requirequired_घड़ी_khz = context->bw_ctx.bw.dcn.clk.bw_dispclk_khz;
	पूर्ण
	अगर (घड़ी_प्रकारype == DC_CLOCK_TYPE_DPPCLK) अणु
		घड़ी_cfg->max_घड़ी_khz = context->bw_ctx.bw.dcn.clk.max_supported_dppclk_khz;
		घड़ी_cfg->min_घड़ी_khz = DCN_MINIMUM_DPPCLK_Khz;
		घड़ी_cfg->current_घड़ी_khz = clk_mgr->clks.dppclk_khz;
		घड़ी_cfg->bw_requirequired_घड़ी_khz = context->bw_ctx.bw.dcn.clk.bw_dppclk_khz;
	पूर्ण
पूर्ण

अटल bool dcn2_are_घड़ी_states_equal(काष्ठा dc_घड़ीs *a,
		काष्ठा dc_घड़ीs *b)
अणु
	अगर (a->dispclk_khz != b->dispclk_khz)
		वापस false;
	अन्यथा अगर (a->dppclk_khz != b->dppclk_khz)
		वापस false;
	अन्यथा अगर (a->disp_dpp_voltage_level_khz != b->disp_dpp_voltage_level_khz)
		वापस false;
	अन्यथा अगर (a->dcfclk_khz != b->dcfclk_khz)
		वापस false;
	अन्यथा अगर (a->socclk_khz != b->socclk_khz)
		वापस false;
	अन्यथा अगर (a->dcfclk_deep_sleep_khz != b->dcfclk_deep_sleep_khz)
		वापस false;
	अन्यथा अगर (a->dramclk_khz != b->dramclk_khz)
		वापस false;
	अन्यथा अगर (a->p_state_change_support != b->p_state_change_support)
		वापस false;

	वापस true;
पूर्ण

/* Notअगरy clk_mgr of a change in link rate, update phyclk frequency अगर necessary */
अटल व्योम dcn2_notअगरy_link_rate_change(काष्ठा clk_mgr *clk_mgr_base, काष्ठा dc_link *link)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);
	अचिन्हित पूर्णांक i, max_phyclk_req = 0;
	काष्ठा pp_smu_funcs_nv *pp_smu = शून्य;

	अगर (!clk_mgr->pp_smu || !clk_mgr->pp_smu->nv_funcs.set_voltage_by_freq)
		वापस;

	pp_smu = &clk_mgr->pp_smu->nv_funcs;

	clk_mgr->cur_phyclk_req_table[link->link_index] = link->cur_link_settings.link_rate * LINK_RATE_REF_FREQ_IN_KHZ;

	क्रम (i = 0; i < MAX_PIPES * 2; i++) अणु
		अगर (clk_mgr->cur_phyclk_req_table[i] > max_phyclk_req)
			max_phyclk_req = clk_mgr->cur_phyclk_req_table[i];
	पूर्ण

	अगर (max_phyclk_req != clk_mgr_base->clks.phyclk_khz) अणु
		clk_mgr_base->clks.phyclk_khz = max_phyclk_req;
		pp_smu->set_voltage_by_freq(&pp_smu->pp_smu, PP_SMU_NV_PHYCLK, clk_mgr_base->clks.phyclk_khz / 1000);
	पूर्ण
पूर्ण

अटल काष्ठा clk_mgr_funcs dcn2_funcs = अणु
	.get_dp_ref_clk_frequency = dce12_get_dp_ref_freq_khz,
	.update_घड़ीs = dcn2_update_घड़ीs,
	.init_घड़ीs = dcn2_init_घड़ीs,
	.enable_pme_wa = dcn2_enable_pme_wa,
	.get_घड़ी = dcn2_get_घड़ी,
	.are_घड़ी_states_equal = dcn2_are_घड़ी_states_equal,
	.notअगरy_link_rate_change = dcn2_notअगरy_link_rate_change,
पूर्ण;


व्योम dcn20_clk_mgr_स्थिरruct(
		काष्ठा dc_context *ctx,
		काष्ठा clk_mgr_पूर्णांकernal *clk_mgr,
		काष्ठा pp_smu_funcs *pp_smu,
		काष्ठा dccg *dccg)
अणु
	clk_mgr->base.ctx = ctx;
	clk_mgr->pp_smu = pp_smu;
	clk_mgr->base.funcs = &dcn2_funcs;
	clk_mgr->regs = &clk_mgr_regs;
	clk_mgr->clk_mgr_shअगरt = &clk_mgr_shअगरt;
	clk_mgr->clk_mgr_mask = &clk_mgr_mask;

	clk_mgr->dccg = dccg;
	clk_mgr->dfs_bypass_disp_clk = 0;

	clk_mgr->dprefclk_ss_percentage = 0;
	clk_mgr->dprefclk_ss_भागider = 1000;
	clk_mgr->ss_on_dprefclk = false;

	clk_mgr->base.dprefclk_khz = 700000; // 700 MHz planned अगर VCO is 3.85 GHz, will be retrieved

	अगर (IS_FPGA_MAXIMUS_DC(ctx->dce_environment)) अणु
		dcn2_funcs.update_घड़ीs = dcn2_update_घड़ीs_fpga;
		clk_mgr->base.dentist_vco_freq_khz = 3850000;

	पूर्ण अन्यथा अणु
		/* DFS Slice 2 should be used क्रम DPREFCLK */
		पूर्णांक dprefclk_did = REG_READ(CLK3_CLK2_DFS_CNTL);
		/* Convert DPREFCLK DFS Slice DID to actual भागider*/
		पूर्णांक target_भाग = dentist_get_भागider_from_did(dprefclk_did);

		/* get FbMult value */
		uपूर्णांक32_t pll_req_reg = REG_READ(CLK3_CLK_PLL_REQ);
		काष्ठा fixed31_32 pll_req;

		/* set up a fixed-poपूर्णांक number
		 * this works because the पूर्णांक part is on the right edge of the रेजिस्टर
		 * and the frac part is on the left edge
		 */

		pll_req = dc_fixpt_from_पूर्णांक(pll_req_reg & clk_mgr->clk_mgr_mask->FbMult_पूर्णांक);
		pll_req.value |= pll_req_reg & clk_mgr->clk_mgr_mask->FbMult_frac;

		/* multiply by REFCLK period */
		pll_req = dc_fixpt_mul_पूर्णांक(pll_req, 100000);

		/* पूर्णांकeger part is now VCO frequency in kHz */
		clk_mgr->base.dentist_vco_freq_khz = dc_fixpt_न्यूनमान(pll_req);

		/* in हाल we करोn't get a value from the रेजिस्टर, use शेष */
		अगर (clk_mgr->base.dentist_vco_freq_khz == 0)
			clk_mgr->base.dentist_vco_freq_khz = 3850000;

		/* Calculate the DPREFCLK in kHz.*/
		clk_mgr->base.dprefclk_khz = (DENTIST_DIVIDER_RANGE_SCALE_FACTOR
			* clk_mgr->base.dentist_vco_freq_khz) / target_भाग;
	पूर्ण
	//Integrated_info table करोes not exist on dGPU projects so should not be referenced
	//anywhere in code क्रम dGPUs.
	//Also there is no plan क्रम now that DFS BYPASS will be used on NV10/12/14.
	clk_mgr->dfs_bypass_enabled = false;

	dce_घड़ी_पढ़ो_ss_info(clk_mgr);
पूर्ण

