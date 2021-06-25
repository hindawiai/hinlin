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

#अगर_अघोषित DM_PP_SMU_IF__H
#घोषणा DM_PP_SMU_IF__H

/*
 * पूर्णांकerface to PPLIB/SMU to setup घड़ीs and pstate requirements on SoC
 */

क्रमागत pp_smu_ver अणु
	/*
	 * PP_SMU_INTERFACE_X should be पूर्णांकerpreted as the पूर्णांकerface defined
	 * starting from X, where X is some family of ASICs.  This is as
	 * opposed to पूर्णांकerfaces used only क्रम X.  There will be some degree
	 * of पूर्णांकerface sharing between families of ASIcs.
	 */
	PP_SMU_UNSUPPORTED,
	PP_SMU_VER_RV,
	PP_SMU_VER_NV,
	PP_SMU_VER_RN,

	PP_SMU_VER_MAX
पूर्ण;

काष्ठा pp_smu अणु
	क्रमागत pp_smu_ver ver;
	स्थिर व्योम *pp;

	/*
	 * पूर्णांकerim extra handle क्रम backwards compatibility
	 * as some existing functionality not yet implemented
	 * by ppsmu
	 */
	स्थिर व्योम *dm;
पूर्ण;

क्रमागत pp_smu_status अणु
	PP_SMU_RESULT_UNDEFINED = 0,
	PP_SMU_RESULT_OK = 1,
	PP_SMU_RESULT_FAIL,
	PP_SMU_RESULT_UNSUPPORTED
पूर्ण;

#घोषणा PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MIN 0x0
#घोषणा PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MAX 0xFFFF

क्रमागत wm_type अणु
	WM_TYPE_PSTATE_CHG = 0,
	WM_TYPE_RETRAINING = 1,
पूर्ण;

/* This काष्ठाure is a copy of WatermarkRowGeneric_t defined by smuxx_driver_अगर.h*/
काष्ठा pp_smu_wm_set_range अणु
	uपूर्णांक16_t min_fill_clk_mhz;
	uपूर्णांक16_t max_fill_clk_mhz;
	uपूर्णांक16_t min_drain_clk_mhz;
	uपूर्णांक16_t max_drain_clk_mhz;

	uपूर्णांक8_t wm_inst;
	uपूर्णांक8_t wm_type;
पूर्ण;

#घोषणा MAX_WATERMARK_SETS 4

काष्ठा pp_smu_wm_range_sets अणु
	अचिन्हित पूर्णांक num_पढ़ोer_wm_sets;
	काष्ठा pp_smu_wm_set_range पढ़ोer_wm_sets[MAX_WATERMARK_SETS];

	अचिन्हित पूर्णांक num_ग_लिखोr_wm_sets;
	काष्ठा pp_smu_wm_set_range ग_लिखोr_wm_sets[MAX_WATERMARK_SETS];
पूर्ण;

काष्ठा pp_smu_funcs_rv अणु
	काष्ठा pp_smu pp_smu;

	/* PPSMC_MSG_SetDisplayCount
	 * 0 triggers S0i2 optimization
	 */

	व्योम (*set_display_count)(काष्ठा pp_smu *pp, पूर्णांक count);

	/* पढ़ोer and ग_लिखोr WM's are sent together as part of one table*/
	/*
	 * PPSMC_MSG_SetDriverDramAddrHigh
	 * PPSMC_MSG_SetDriverDramAddrLow
	 * PPSMC_MSG_TransferTableDram2Smu
	 *
	 * */
	व्योम (*set_wm_ranges)(काष्ठा pp_smu *pp,
			काष्ठा pp_smu_wm_range_sets *ranges);

	/* PPSMC_MSG_SetHardMinDcfclkByFreq
	 * fixed घड़ी at requested freq, either from FCH bypass or DFS
	 */
	व्योम (*set_hard_min_dcfclk_by_freq)(काष्ठा pp_smu *pp, पूर्णांक mhz);

	/* PPSMC_MSG_SetMinDeepSleepDcfclk
	 * when DF is in cstate, dcf घड़ी is further भागided करोwn
	 * to just above given frequency
	 */
	व्योम (*set_min_deep_sleep_dcfclk)(काष्ठा pp_smu *pp, पूर्णांक mhz);

	/* PPSMC_MSG_SetHardMinFclkByFreq
	 * FCLK will vary with DPM, but never below requested hard min
	 */
	व्योम (*set_hard_min_fclk_by_freq)(काष्ठा pp_smu *pp, पूर्णांक mhz);

	/* PPSMC_MSG_SetHardMinSocclkByFreq
	 * Needed क्रम DWB support
	 */
	व्योम (*set_hard_min_socclk_by_freq)(काष्ठा pp_smu *pp, पूर्णांक mhz);

	/* PME w/a */
	व्योम (*set_pme_wa_enable)(काष्ठा pp_smu *pp);
पूर्ण;

/* Used by pp_smu_funcs_nv.set_voltage_by_freq
 *
 */
क्रमागत pp_smu_nv_घड़ी_id अणु
	PP_SMU_NV_DISPCLK,
	PP_SMU_NV_PHYCLK,
	PP_SMU_NV_PIXELCLK
पूर्ण;

/*
 * Used by pp_smu_funcs_nv.get_maximum_sustainable_घड़ीs
 */
काष्ठा pp_smu_nv_घड़ी_प्रकारable अणु
	// voltage managed SMU, freq set by driver
	अचिन्हित पूर्णांक    displayClockInKhz;
	अचिन्हित पूर्णांक	dppClockInKhz;
	अचिन्हित पूर्णांक    phyClockInKhz;
	अचिन्हित पूर्णांक    pixelClockInKhz;
	अचिन्हित पूर्णांक	dscClockInKhz;

	// freq/voltage managed by SMU
	अचिन्हित पूर्णांक	fabricClockInKhz;
	अचिन्हित पूर्णांक	socClockInKhz;
	अचिन्हित पूर्णांक    dcfClockInKhz;
	अचिन्हित पूर्णांक    uClockInKhz;
पूर्ण;

काष्ठा pp_smu_funcs_nv अणु
	काष्ठा pp_smu pp_smu;

	/* PPSMC_MSG_SetDisplayCount
	 * 0 triggers S0i2 optimization
	 */
	क्रमागत pp_smu_status (*set_display_count)(काष्ठा pp_smu *pp, पूर्णांक count);

	/* PPSMC_MSG_SetHardMinDcfclkByFreq
	 * fixed घड़ी at requested freq, either from FCH bypass or DFS
	 */
	क्रमागत pp_smu_status (*set_hard_min_dcfclk_by_freq)(काष्ठा pp_smu *pp, पूर्णांक Mhz);

	/* PPSMC_MSG_SetMinDeepSleepDcfclk
	 * when DF is in cstate, dcf घड़ी is further भागided करोwn
	 * to just above given frequency
	 */
	क्रमागत pp_smu_status (*set_min_deep_sleep_dcfclk)(काष्ठा pp_smu *pp, पूर्णांक Mhz);

	/* PPSMC_MSG_SetHardMinUclkByFreq
	 * UCLK will vary with DPM, but never below requested hard min
	 */
	क्रमागत pp_smu_status (*set_hard_min_uclk_by_freq)(काष्ठा pp_smu *pp, पूर्णांक Mhz);

	/* PPSMC_MSG_SetHardMinSocclkByFreq
	 * Needed क्रम DWB support
	 */
	क्रमागत pp_smu_status (*set_hard_min_socclk_by_freq)(काष्ठा pp_smu *pp, पूर्णांक Mhz);

	/* PME w/a */
	क्रमागत pp_smu_status (*set_pme_wa_enable)(काष्ठा pp_smu *pp);

	/* PPSMC_MSG_SetHardMinByFreq
	 * Needed to set ASIC voltages क्रम घड़ीs programmed by DAL
	 */
	क्रमागत pp_smu_status (*set_voltage_by_freq)(काष्ठा pp_smu *pp,
			क्रमागत pp_smu_nv_घड़ी_id घड़ी_id, पूर्णांक Mhz);

	/* पढ़ोer and ग_लिखोr WM's are sent together as part of one table*/
	/*
	 * PPSMC_MSG_SetDriverDramAddrHigh
	 * PPSMC_MSG_SetDriverDramAddrLow
	 * PPSMC_MSG_TransferTableDram2Smu
	 *
	 * on DCN20:
	 * 	पढ़ोer fill clk = uclk
	 * 	पढ़ोer drain clk = dcfclk
	 * 	ग_लिखोr fill clk = socclk
	 * 	ग_लिखोr drain clk = uclk
	 * */
	क्रमागत pp_smu_status (*set_wm_ranges)(काष्ठा pp_smu *pp,
			काष्ठा pp_smu_wm_range_sets *ranges);

	/* Not a single SMU message.  This call should वापस maximum sustainable limit क्रम all
	 * घड़ीs that DC depends on.  These will be used as basis क्रम mode क्रमागतeration.
	 */
	क्रमागत pp_smu_status (*get_maximum_sustainable_घड़ीs)(काष्ठा pp_smu *pp,
			काष्ठा pp_smu_nv_घड़ी_प्रकारable *max_घड़ीs);

	/* This call should वापस the discrete uclk DPM states available
	 */
	क्रमागत pp_smu_status (*get_uclk_dpm_states)(काष्ठा pp_smu *pp,
			अचिन्हित पूर्णांक *घड़ी_values_in_khz, अचिन्हित पूर्णांक *num_states);

	/* Not a single SMU message.  This call inक्रमms PPLIB that display will not be able
	 * to perक्रमm pstate handshaking in its current state.  Typically this handshake
	 * is used to perक्रमm uCLK चयनing, so disabling pstate disables uCLK चयनing.
	 *
	 * Note that when setting handshake to unsupported, the call is pre-emptive.  That means
	 * DC will make the call BEFORE setting up the display state which would cause pstate
	 * request to go un-acked.  Only when the call completes should such a state be applied to
	 * DC hardware
	 */
	क्रमागत pp_smu_status (*set_pstate_handshake_support)(काष्ठा pp_smu *pp,
			bool pstate_handshake_supported);
पूर्ण;

#घोषणा PP_SMU_NUM_SOCCLK_DPM_LEVELS  8
#घोषणा PP_SMU_NUM_DCFCLK_DPM_LEVELS  8
#घोषणा PP_SMU_NUM_FCLK_DPM_LEVELS    4
#घोषणा PP_SMU_NUM_MEMCLK_DPM_LEVELS  4

काष्ठा dpm_घड़ी अणु
  uपूर्णांक32_t  Freq;    // In MHz
  uपूर्णांक32_t  Vol;     // Millivolts with 2 fractional bits
पूर्ण;


/* this is a copy of the काष्ठाure defined in smuxx_driver_अगर.h*/
काष्ठा dpm_घड़ीs अणु
	काष्ठा dpm_घड़ी DcfClocks[PP_SMU_NUM_DCFCLK_DPM_LEVELS];
	काष्ठा dpm_घड़ी SocClocks[PP_SMU_NUM_SOCCLK_DPM_LEVELS];
	काष्ठा dpm_घड़ी FClocks[PP_SMU_NUM_FCLK_DPM_LEVELS];
	काष्ठा dpm_घड़ी MemClocks[PP_SMU_NUM_MEMCLK_DPM_LEVELS];
पूर्ण;


काष्ठा pp_smu_funcs_rn अणु
	काष्ठा pp_smu pp_smu;

	/*
	 * पढ़ोer and ग_लिखोr WM's are sent together as part of one table
	 *
	 * PPSMC_MSG_SetDriverDramAddrHigh
	 * PPSMC_MSG_SetDriverDramAddrLow
	 * PPSMC_MSG_TransferTableDram2Smu
	 *
	 */
	क्रमागत pp_smu_status (*set_wm_ranges)(काष्ठा pp_smu *pp,
			काष्ठा pp_smu_wm_range_sets *ranges);

	क्रमागत pp_smu_status (*get_dpm_घड़ी_प्रकारable) (काष्ठा pp_smu *pp,
			काष्ठा dpm_घड़ीs *घड़ी_प्रकारable);
पूर्ण;

काष्ठा pp_smu_funcs_vgh अणु
	काष्ठा pp_smu pp_smu;

	/*
	 * पढ़ोer and ग_लिखोr WM's are sent together as part of one table
	 *
	 * PPSMC_MSG_SetDriverDramAddrHigh
	 * PPSMC_MSG_SetDriverDramAddrLow
	 * PPSMC_MSG_TransferTableDram2Smu
	 *
	 */
	// TODO: Check whether this is moved to DAL, and हटाओ as needed
	क्रमागत pp_smu_status (*set_wm_ranges)(काष्ठा pp_smu *pp,
			काष्ठा pp_smu_wm_range_sets *ranges);

	// TODO: Check whether this is moved to DAL, and हटाओ as needed
	क्रमागत pp_smu_status (*get_dpm_घड़ी_प्रकारable) (काष्ठा pp_smu *pp,
			काष्ठा dpm_घड़ीs *घड़ी_प्रकारable);

	क्रमागत pp_smu_status (*notअगरy_smu_समयout) (काष्ठा pp_smu *pp);
पूर्ण;

काष्ठा pp_smu_funcs अणु
	काष्ठा pp_smu ctx;
	जोड़ अणु
		काष्ठा pp_smu_funcs_rv rv_funcs;
		काष्ठा pp_smu_funcs_nv nv_funcs;
		काष्ठा pp_smu_funcs_rn rn_funcs;
		काष्ठा pp_smu_funcs_vgh vgh_funcs;
	पूर्ण;
पूर्ण;

#पूर्ण_अगर /* DM_PP_SMU_IF__H */
