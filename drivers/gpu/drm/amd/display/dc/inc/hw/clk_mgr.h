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

#अगर_अघोषित __DAL_CLK_MGR_H__
#घोषणा __DAL_CLK_MGR_H__

#समावेश "dc.h"
#समावेश "dm_pp_smu.h"

#घोषणा DCN_MINIMUM_DISPCLK_Khz 100000
#घोषणा DCN_MINIMUM_DPPCLK_Khz 100000

/* Constants */
#घोषणा DDR4_DRAM_WIDTH   64
#घोषणा WM_A 0
#घोषणा WM_B 1
#घोषणा WM_C 2
#घोषणा WM_D 3
#घोषणा WM_SET_COUNT 4

#घोषणा DCN_MINIMUM_DISPCLK_Khz 100000
#घोषणा DCN_MINIMUM_DPPCLK_Khz 100000

काष्ठा dcn3_clk_पूर्णांकernal अणु
	पूर्णांक dummy;
	/*TODO:
	uपूर्णांक32_t CLK1_CLK0_CURRENT_CNT; //dispclk
	uपूर्णांक32_t CLK1_CLK1_CURRENT_CNT; //dppclk
	uपूर्णांक32_t CLK1_CLK2_CURRENT_CNT; //dprefclk
	uपूर्णांक32_t CLK1_CLK3_CURRENT_CNT; //dcfclk
	uपूर्णांक32_t CLK1_CLK3_DS_CNTL;	//dcf_deep_sleep_भागider
	uपूर्णांक32_t CLK1_CLK3_ALLOW_DS;	//dcf_deep_sleep_allow

	uपूर्णांक32_t CLK1_CLK0_BYPASS_CNTL; //dispclk bypass
	uपूर्णांक32_t CLK1_CLK1_BYPASS_CNTL; //dppclk bypass
	uपूर्णांक32_t CLK1_CLK2_BYPASS_CNTL; //dprefclk bypass
	uपूर्णांक32_t CLK1_CLK3_BYPASS_CNTL; //dcfclk bypass
	*/
पूर्ण;

काष्ठा dcn301_clk_पूर्णांकernal अणु
	पूर्णांक dummy;
	uपूर्णांक32_t CLK1_CLK0_CURRENT_CNT; //dispclk
	uपूर्णांक32_t CLK1_CLK1_CURRENT_CNT; //dppclk
	uपूर्णांक32_t CLK1_CLK2_CURRENT_CNT; //dprefclk
	uपूर्णांक32_t CLK1_CLK3_CURRENT_CNT; //dcfclk
	uपूर्णांक32_t CLK1_CLK3_DS_CNTL;	//dcf_deep_sleep_भागider
	uपूर्णांक32_t CLK1_CLK3_ALLOW_DS;	//dcf_deep_sleep_allow

	uपूर्णांक32_t CLK1_CLK0_BYPASS_CNTL; //dispclk bypass
	uपूर्णांक32_t CLK1_CLK1_BYPASS_CNTL; //dppclk bypass
	uपूर्णांक32_t CLK1_CLK2_BYPASS_CNTL; //dprefclk bypass
	uपूर्णांक32_t CLK1_CLK3_BYPASS_CNTL; //dcfclk bypass
पूर्ण;

/* Will these bw काष्ठाures be ASIC specअगरic? */

#घोषणा MAX_NUM_DPM_LVL		8
#घोषणा WM_SET_COUNT 		4


काष्ठा clk_limit_table_entry अणु
	अचिन्हित पूर्णांक voltage; /* milivolts withh 2 fractional bits */
	अचिन्हित पूर्णांक dcfclk_mhz;
	अचिन्हित पूर्णांक fclk_mhz;
	अचिन्हित पूर्णांक memclk_mhz;
	अचिन्हित पूर्णांक socclk_mhz;
	अचिन्हित पूर्णांक dtbclk_mhz;
	अचिन्हित पूर्णांक dispclk_mhz;
	अचिन्हित पूर्णांक dppclk_mhz;
	अचिन्हित पूर्णांक phyclk_mhz;
पूर्ण;

/* This table is contiguous */
काष्ठा clk_limit_table अणु
	काष्ठा clk_limit_table_entry entries[MAX_NUM_DPM_LVL];
	अचिन्हित पूर्णांक num_entries;
पूर्ण;

काष्ठा wm_range_table_entry अणु
	अचिन्हित पूर्णांक wm_inst;
	अचिन्हित पूर्णांक wm_type;
	द्विगुन pstate_latency_us;
	द्विगुन sr_निकास_समय_us;
	द्विगुन sr_enter_plus_निकास_समय_us;
	bool valid;
पूर्ण;

काष्ठा nv_wm_range_entry अणु
	bool valid;

	काष्ठा अणु
		uपूर्णांक8_t wm_type;
		uपूर्णांक16_t min_dcfclk;
		uपूर्णांक16_t max_dcfclk;
		uपूर्णांक16_t min_uclk;
		uपूर्णांक16_t max_uclk;
	पूर्ण pmfw_अवरोधकरोwn;

	काष्ठा अणु
		द्विगुन pstate_latency_us;
		द्विगुन sr_निकास_समय_us;
		द्विगुन sr_enter_plus_निकास_समय_us;
	पूर्ण dml_input;
पूर्ण;

काष्ठा clk_log_info अणु
	bool enabled;
	अक्षर *pBuf;
	अचिन्हित पूर्णांक bufSize;
	अचिन्हित पूर्णांक *sum_अक्षरs_prपूर्णांकed;
पूर्ण;

काष्ठा clk_state_रेजिस्टरs_and_bypass अणु
	uपूर्णांक32_t dcfclk;
	uपूर्णांक32_t dcf_deep_sleep_भागider;
	uपूर्णांक32_t dcf_deep_sleep_allow;
	uपूर्णांक32_t dprefclk;
	uपूर्णांक32_t dispclk;
	uपूर्णांक32_t dppclk;

	uपूर्णांक32_t dppclk_bypass;
	uपूर्णांक32_t dcfclk_bypass;
	uपूर्णांक32_t dprefclk_bypass;
	uपूर्णांक32_t dispclk_bypass;
पूर्ण;

काष्ठा rv1_clk_पूर्णांकernal अणु
	uपूर्णांक32_t CLK0_CLK8_CURRENT_CNT;  //dcfclk
	uपूर्णांक32_t CLK0_CLK8_DS_CNTL;		 //dcf_deep_sleep_भागider
	uपूर्णांक32_t CLK0_CLK8_ALLOW_DS;	 //dcf_deep_sleep_allow
	uपूर्णांक32_t CLK0_CLK10_CURRENT_CNT; //dprefclk
	uपूर्णांक32_t CLK0_CLK11_CURRENT_CNT; //dispclk

	uपूर्णांक32_t CLK0_CLK8_BYPASS_CNTL;  //dcfclk bypass
	uपूर्णांक32_t CLK0_CLK10_BYPASS_CNTL; //dprefclk bypass
	uपूर्णांक32_t CLK0_CLK11_BYPASS_CNTL; //dispclk bypass
पूर्ण;

काष्ठा rn_clk_पूर्णांकernal अणु
	uपूर्णांक32_t CLK1_CLK0_CURRENT_CNT; //dispclk
	uपूर्णांक32_t CLK1_CLK1_CURRENT_CNT; //dppclk
	uपूर्णांक32_t CLK1_CLK2_CURRENT_CNT; //dprefclk
	uपूर्णांक32_t CLK1_CLK3_CURRENT_CNT; //dcfclk
	uपूर्णांक32_t CLK1_CLK3_DS_CNTL;		//dcf_deep_sleep_भागider
	uपूर्णांक32_t CLK1_CLK3_ALLOW_DS;	//dcf_deep_sleep_allow

	uपूर्णांक32_t CLK1_CLK0_BYPASS_CNTL; //dispclk bypass
	uपूर्णांक32_t CLK1_CLK1_BYPASS_CNTL; //dppclk bypass
	uपूर्णांक32_t CLK1_CLK2_BYPASS_CNTL; //dprefclk bypass
	uपूर्णांक32_t CLK1_CLK3_BYPASS_CNTL; //dcfclk bypass

पूर्ण;

/* For dtn logging and debugging */
काष्ठा clk_state_रेजिस्टरs अणु
		uपूर्णांक32_t CLK0_CLK8_CURRENT_CNT;  //dcfclk
		uपूर्णांक32_t CLK0_CLK8_DS_CNTL;		 //dcf_deep_sleep_भागider
		uपूर्णांक32_t CLK0_CLK8_ALLOW_DS;	 //dcf_deep_sleep_allow
		uपूर्णांक32_t CLK0_CLK10_CURRENT_CNT; //dprefclk
		uपूर्णांक32_t CLK0_CLK11_CURRENT_CNT; //dispclk
पूर्ण;

/* TODO: combine this with the above */
काष्ठा clk_bypass अणु
	uपूर्णांक32_t dcfclk_bypass;
	uपूर्णांक32_t dispclk_pypass;
	uपूर्णांक32_t dprefclk_bypass;
पूर्ण;
/*
 * This table is not contiguous, can have holes, each
 * entry correspond to one set of WM. For example अगर
 * we have 2 DPM and LPDDR, we will WM set A, B and
 * D occupied, C will be emptry.
 */
काष्ठा wm_table अणु
	जोड़ अणु
		काष्ठा nv_wm_range_entry nv_entries[WM_SET_COUNT];
		काष्ठा wm_range_table_entry entries[WM_SET_COUNT];
	पूर्ण;
पूर्ण;

काष्ठा dummy_pstate_entry अणु
	अचिन्हित पूर्णांक dram_speed_mts;
	अचिन्हित पूर्णांक dummy_pstate_latency_us;
पूर्ण;

काष्ठा clk_bw_params अणु
	अचिन्हित पूर्णांक vram_type;
	अचिन्हित पूर्णांक num_channels;
	काष्ठा clk_limit_table clk_table;
	काष्ठा wm_table wm_table;
	काष्ठा dummy_pstate_entry dummy_pstate_table[4];
पूर्ण;
/* Public पूर्णांकerfaces */

काष्ठा clk_states अणु
	uपूर्णांक32_t dprefclk_khz;
पूर्ण;

काष्ठा clk_mgr_funcs अणु
	/*
	 * This function should set new घड़ीs based on the input "safe_to_lower".
	 * If safe_to_lower == false, then only घड़ीs which are to be increased
	 * should changed.
	 * If safe_to_lower == true, then only घड़ीs which are to be decreased
	 * should be changed.
	 */
	व्योम (*update_घड़ीs)(काष्ठा clk_mgr *clk_mgr,
			काष्ठा dc_state *context,
			bool safe_to_lower);

	पूर्णांक (*get_dp_ref_clk_frequency)(काष्ठा clk_mgr *clk_mgr);

	व्योम (*set_low_घातer_state)(काष्ठा clk_mgr *clk_mgr);

	व्योम (*init_घड़ीs)(काष्ठा clk_mgr *clk_mgr);

	व्योम (*enable_pme_wa) (काष्ठा clk_mgr *clk_mgr);
	व्योम (*get_घड़ी)(काष्ठा clk_mgr *clk_mgr,
			काष्ठा dc_state *context,
			क्रमागत dc_घड़ी_प्रकारype घड़ी_प्रकारype,
			काष्ठा dc_घड़ी_config *घड़ी_cfg);

	bool (*are_घड़ी_states_equal) (काष्ठा dc_घड़ीs *a,
			काष्ठा dc_घड़ीs *b);
	व्योम (*notअगरy_wm_ranges)(काष्ठा clk_mgr *clk_mgr);

	/* Notअगरy clk_mgr of a change in link rate, update phyclk frequency अगर necessary */
	व्योम (*notअगरy_link_rate_change)(काष्ठा clk_mgr *clk_mgr, काष्ठा dc_link *link);
	/*
	 * Send message to PMFW to set hard min memclk frequency
	 * When current_mode = false, set DPM0
	 * When current_mode = true, set required घड़ी क्रम current mode
	 */
	व्योम (*set_hard_min_memclk)(काष्ठा clk_mgr *clk_mgr, bool current_mode);

	/* Send message to PMFW to set hard max memclk frequency to highest DPM */
	व्योम (*set_hard_max_memclk)(काष्ठा clk_mgr *clk_mgr);

	/* Get current memclk states from PMFW, update relevant काष्ठाures */
	व्योम (*get_memclk_states_from_smu)(काष्ठा clk_mgr *clk_mgr);

	/* Get SMU present */
	bool (*is_smu_present)(काष्ठा clk_mgr *clk_mgr);
पूर्ण;

काष्ठा clk_mgr अणु
	काष्ठा dc_context *ctx;
	काष्ठा clk_mgr_funcs *funcs;
	काष्ठा dc_घड़ीs clks;
	bool psr_allow_active_cache;
	bool क्रमce_smu_not_present;
	पूर्णांक dprefclk_khz; // Used by program pixel घड़ी in घड़ी source funcs, need to figureout where this goes
	पूर्णांक dentist_vco_freq_khz;
	काष्ठा clk_state_रेजिस्टरs_and_bypass boot_snapshot;
	काष्ठा clk_bw_params *bw_params;
	काष्ठा pp_smu_wm_range_sets ranges;
पूर्ण;

/* क्रमward declarations */
काष्ठा dccg;

काष्ठा clk_mgr *dc_clk_mgr_create(काष्ठा dc_context *ctx, काष्ठा pp_smu_funcs *pp_smu, काष्ठा dccg *dccg);

व्योम dc_destroy_clk_mgr(काष्ठा clk_mgr *clk_mgr);

व्योम clk_mgr_निकास_optimized_pwr_state(स्थिर काष्ठा dc *dc, काष्ठा clk_mgr *clk_mgr);

व्योम clk_mgr_optimize_pwr_state(स्थिर काष्ठा dc *dc, काष्ठा clk_mgr *clk_mgr);

#पूर्ण_अगर /* __DAL_CLK_MGR_H__ */
