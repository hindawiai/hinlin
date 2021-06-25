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

#अगर_अघोषित __DAL_CLK_MGR_INTERNAL_H__
#घोषणा __DAL_CLK_MGR_INTERNAL_H__

#समावेश "clk_mgr.h"
#समावेश "dc.h"

/*
 * only thing needed from here is MEMORY_TYPE_MULTIPLIER_CZ, which is also
 * used in resource, perhaps this should be defined somewhere more common.
 */
#समावेश "resource.h"


/* Starting DID क्रम each range */
क्रमागत dentist_base_भागider_id अणु
	DENTIST_BASE_DID_1 = 0x08,
	DENTIST_BASE_DID_2 = 0x40,
	DENTIST_BASE_DID_3 = 0x60,
	DENTIST_BASE_DID_4 = 0x7e,
	DENTIST_MAX_DID = 0x7f
पूर्ण;

/* Starting poपूर्णांक and step size क्रम each भागider range.*/
क्रमागत dentist_भागider_range अणु
	DENTIST_DIVIDER_RANGE_1_START = 8,   /* 2.00  */
	DENTIST_DIVIDER_RANGE_1_STEP  = 1,   /* 0.25  */
	DENTIST_DIVIDER_RANGE_2_START = 64,  /* 16.00 */
	DENTIST_DIVIDER_RANGE_2_STEP  = 2,   /* 0.50  */
	DENTIST_DIVIDER_RANGE_3_START = 128, /* 32.00 */
	DENTIST_DIVIDER_RANGE_3_STEP  = 4,   /* 1.00  */
	DENTIST_DIVIDER_RANGE_4_START = 248, /* 62.00 */
	DENTIST_DIVIDER_RANGE_4_STEP  = 264, /* 66.00 */
	DENTIST_DIVIDER_RANGE_SCALE_FACTOR = 4
पूर्ण;

/*
 ***************************************************************************************
 ****************** Clock Manager Private Macros and Defines ***************************
 ***************************************************************************************
 */

/* Macros */

#घोषणा TO_CLK_MGR_INTERNAL(clk_mgr)\
	container_of(clk_mgr, काष्ठा clk_mgr_पूर्णांकernal, base)

#घोषणा CTX \
	clk_mgr->base.ctx

#घोषणा DC_LOGGER \
	clk_mgr->base.ctx->logger




#घोषणा CLK_BASE(inst) \
	CLK_BASE_INNER(inst)

#घोषणा CLK_SRI(reg_name, block, inst)\
	.reg_name = CLK_BASE(mm ## block ## _ ## inst ## _ ## reg_name ## _BASE_IDX) + \
					mm ## block ## _ ## inst ## _ ## reg_name

#घोषणा CLK_COMMON_REG_LIST_DCE_BASE() \
	.DPREFCLK_CNTL = mmDPREFCLK_CNTL, \
	.DENTIST_DISPCLK_CNTL = mmDENTIST_DISPCLK_CNTL

#अगर defined(CONFIG_DRM_AMD_DC_SI)
#घोषणा CLK_COMMON_REG_LIST_DCE60_BASE() \
	SR(DENTIST_DISPCLK_CNTL)
#पूर्ण_अगर

#घोषणा CLK_COMMON_REG_LIST_DCN_BASE() \
	SR(DENTIST_DISPCLK_CNTL)

#घोषणा VBIOS_SMU_MSG_BOX_REG_LIST_RV() \
	.MP1_SMN_C2PMSG_91 = mmMP1_SMN_C2PMSG_91, \
	.MP1_SMN_C2PMSG_83 = mmMP1_SMN_C2PMSG_83, \
	.MP1_SMN_C2PMSG_67 = mmMP1_SMN_C2PMSG_67

#घोषणा CLK_REG_LIST_NV10() \
	SR(DENTIST_DISPCLK_CNTL), \
	CLK_SRI(CLK3_CLK_PLL_REQ, CLK3, 0), \
	CLK_SRI(CLK3_CLK2_DFS_CNTL, CLK3, 0)

// TODO:
#घोषणा CLK_REG_LIST_DCN3()	  \
	SR(DENTIST_DISPCLK_CNTL)

#घोषणा CLK_SF(reg_name, field_name, post_fix)\
	.field_name = reg_name ## __ ## field_name ## post_fix

#घोषणा CLK_COMMON_MASK_SH_LIST_DCE_COMMON_BASE(mask_sh) \
	CLK_SF(DPREFCLK_CNTL, DPREFCLK_SRC_SEL, mask_sh), \
	CLK_SF(DENTIST_DISPCLK_CNTL, DENTIST_DPREFCLK_WDIVIDER, mask_sh)

#अगर defined(CONFIG_DRM_AMD_DC_SI)
#घोषणा CLK_COMMON_MASK_SH_LIST_DCE60_COMMON_BASE(mask_sh) \
	CLK_SF(DENTIST_DISPCLK_CNTL, DENTIST_DISPCLK_WDIVIDER, mask_sh),\
	CLK_SF(DENTIST_DISPCLK_CNTL, DENTIST_DISPCLK_CHG_DONE, mask_sh)
#पूर्ण_अगर

#घोषणा CLK_COMMON_MASK_SH_LIST_DCN_COMMON_BASE(mask_sh) \
	CLK_SF(DENTIST_DISPCLK_CNTL, DENTIST_DISPCLK_WDIVIDER, mask_sh),\
	CLK_SF(DENTIST_DISPCLK_CNTL, DENTIST_DISPCLK_CHG_DONE, mask_sh)

#घोषणा CLK_MASK_SH_LIST_RV1(mask_sh) \
	CLK_COMMON_MASK_SH_LIST_DCN_COMMON_BASE(mask_sh),\
	CLK_SF(MP1_SMN_C2PMSG_67, CONTENT, mask_sh),\
	CLK_SF(MP1_SMN_C2PMSG_83, CONTENT, mask_sh),\
	CLK_SF(MP1_SMN_C2PMSG_91, CONTENT, mask_sh),

#घोषणा CLK_COMMON_MASK_SH_LIST_DCN20_BASE(mask_sh) \
	CLK_COMMON_MASK_SH_LIST_DCN_COMMON_BASE(mask_sh),\
	CLK_SF(DENTIST_DISPCLK_CNTL, DENTIST_DPPCLK_WDIVIDER, mask_sh),\
	CLK_SF(DENTIST_DISPCLK_CNTL, DENTIST_DPPCLK_CHG_DONE, mask_sh)

#घोषणा CLK_MASK_SH_LIST_NV10(mask_sh) \
	CLK_COMMON_MASK_SH_LIST_DCN20_BASE(mask_sh),\
	CLK_SF(CLK3_0_CLK3_CLK_PLL_REQ, FbMult_पूर्णांक, mask_sh),\
	CLK_SF(CLK3_0_CLK3_CLK_PLL_REQ, FbMult_frac, mask_sh)

#घोषणा CLK_REG_FIELD_LIST(type) \
	type DPREFCLK_SRC_SEL; \
	type DENTIST_DPREFCLK_WDIVIDER; \
	type DENTIST_DISPCLK_WDIVIDER; \
	type DENTIST_DISPCLK_CHG_DONE;

/*
 ***************************************************************************************
 ****************** Clock Manager Private Structures ***********************************
 ***************************************************************************************
 */
#घोषणा CLK20_REG_FIELD_LIST(type) \
	type DENTIST_DPPCLK_WDIVIDER; \
	type DENTIST_DPPCLK_CHG_DONE; \
	type FbMult_पूर्णांक; \
	type FbMult_frac;

#घोषणा VBIOS_SMU_REG_FIELD_LIST(type) \
	type CONTENT;

काष्ठा clk_mgr_shअगरt अणु
	CLK_REG_FIELD_LIST(uपूर्णांक8_t)
	CLK20_REG_FIELD_LIST(uपूर्णांक8_t)
	VBIOS_SMU_REG_FIELD_LIST(uपूर्णांक32_t)
पूर्ण;

काष्ठा clk_mgr_mask अणु
	CLK_REG_FIELD_LIST(uपूर्णांक32_t)
	CLK20_REG_FIELD_LIST(uपूर्णांक32_t)
	VBIOS_SMU_REG_FIELD_LIST(uपूर्णांक32_t)
पूर्ण;

काष्ठा clk_mgr_रेजिस्टरs अणु
	uपूर्णांक32_t DPREFCLK_CNTL;
	uपूर्णांक32_t DENTIST_DISPCLK_CNTL;

	uपूर्णांक32_t CLK3_CLK2_DFS_CNTL;
	uपूर्णांक32_t CLK3_CLK_PLL_REQ;

	uपूर्णांक32_t CLK0_CLK2_DFS_CNTL;
	uपूर्णांक32_t CLK0_CLK_PLL_REQ;

	uपूर्णांक32_t MP1_SMN_C2PMSG_67;
	uपूर्णांक32_t MP1_SMN_C2PMSG_83;
	uपूर्णांक32_t MP1_SMN_C2PMSG_91;
पूर्ण;

क्रमागत घड़ी_प्रकारype अणु
	घड़ी_प्रकारype_dispclk = 1,
	घड़ी_प्रकारype_dcfclk,
	घड़ी_प्रकारype_socclk,
	घड़ी_प्रकारype_pixelclk,
	घड़ी_प्रकारype_phyclk,
	घड़ी_प्रकारype_dppclk,
	घड़ी_प्रकारype_fclk,
	घड़ी_प्रकारype_dcfdsclk,
	घड़ी_प्रकारype_dscclk,
	घड़ी_प्रकारype_uclk,
	घड़ी_प्रकारype_dramclk,
पूर्ण;


काष्ठा state_dependent_घड़ीs अणु
	पूर्णांक display_clk_khz;
	पूर्णांक pixel_clk_khz;
पूर्ण;

काष्ठा clk_mgr_पूर्णांकernal अणु
	काष्ठा clk_mgr base;
	पूर्णांक smu_ver;
	काष्ठा pp_smu_funcs *pp_smu;
	काष्ठा clk_mgr_पूर्णांकernal_funcs *funcs;

	काष्ठा dccg *dccg;

	/*
	 * For backwards compatbility with previous implementation
	 * TODO: हटाओ these after everything transitions to new pattern
	 * Rationale is that clk रेजिस्टरs change a lot across DCE versions
	 * and a shared data काष्ठाure करोesn't really make sense.
	 */
	स्थिर काष्ठा clk_mgr_रेजिस्टरs *regs;
	स्थिर काष्ठा clk_mgr_shअगरt *clk_mgr_shअगरt;
	स्थिर काष्ठा clk_mgr_mask *clk_mgr_mask;

	काष्ठा state_dependent_घड़ीs max_clks_by_state[DM_PP_CLOCKS_MAX_STATES];

	/*TODO: figure out which of the below fields should be here vs in asic specअगरic portion */
	/* Cache the status of DFS-bypass feature*/
	bool dfs_bypass_enabled;
	/* True अगर the DFS-bypass feature is enabled and active. */
	bool dfs_bypass_active;

	uपूर्णांक32_t dfs_ref_freq_khz;
	/*
	 * Cache the display घड़ी वापसed by VBIOS अगर DFS-bypass is enabled.
	 * This is basically "Crystal Frequency In KHz" (XTALIN) frequency
	 */
	पूर्णांक dfs_bypass_disp_clk;

	/**
	 * @ss_on_dprefclk:
	 *
	 * True अगर spपढ़ो spectrum is enabled on the DP ref घड़ी.
	 */
	bool ss_on_dprefclk;

	/**
	 * @xgmi_enabled:
	 *
	 * True अगर xGMI is enabled. On VG20, both audio and display घड़ीs need
	 * to be adjusted with the WAFL link's SS info अगर xGMI is enabled.
	 */
	bool xgmi_enabled;

	/**
	 * @dprefclk_ss_percentage:
	 *
	 * DPREFCLK SS percentage (अगर करोwn-spपढ़ो enabled).
	 *
	 * Note that अगर XGMI is enabled, the SS info (percentage and भागider)
	 * from the WAFL link is used instead. This is decided during
	 * dce_clk_mgr initialization.
	 */
	पूर्णांक dprefclk_ss_percentage;

	/**
	 * @dprefclk_ss_भागider:
	 *
	 * DPREFCLK SS percentage Divider (100 or 1000).
	 */
	पूर्णांक dprefclk_ss_भागider;

	क्रमागत dm_pp_घड़ीs_state max_clks_state;
	क्रमागत dm_pp_घड़ीs_state cur_min_clks_state;
	bool periodic_retraining_disabled;

	अचिन्हित पूर्णांक cur_phyclk_req_table[MAX_PIPES * 2];

	bool smu_present;
	व्योम *wm_range_table;
	दीर्घ दीर्घ wm_range_table_addr;
पूर्ण;

काष्ठा clk_mgr_पूर्णांकernal_funcs अणु
	पूर्णांक (*set_dispclk)(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, पूर्णांक requested_dispclk_khz);
	पूर्णांक (*set_dprefclk)(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr);
पूर्ण;


/*
 ***************************************************************************************
 ****************** Clock Manager Level Helper functions *******************************
 ***************************************************************************************
 */


अटल अंतरभूत bool should_set_घड़ी(bool safe_to_lower, पूर्णांक calc_clk, पूर्णांक cur_clk)
अणु
	वापस ((safe_to_lower && calc_clk < cur_clk) || calc_clk > cur_clk);
पूर्ण

अटल अंतरभूत bool should_update_pstate_support(bool safe_to_lower, bool calc_support, bool cur_support)
अणु
	अगर (cur_support != calc_support) अणु
		अगर (calc_support && safe_to_lower)
			वापस true;
		अन्यथा अगर (!calc_support && !safe_to_lower)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

पूर्णांक clk_mgr_helper_get_active_display_cnt(
		काष्ठा dc *dc,
		काष्ठा dc_state *context);

पूर्णांक clk_mgr_helper_get_active_plane_cnt(
		काष्ठा dc *dc,
		काष्ठा dc_state *context);



#पूर्ण_अगर //__DAL_CLK_MGR_INTERNAL_H__
