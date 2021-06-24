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
 */

#अगर_अघोषित PP_ATOMVOLTAGECTRL_H
#घोषणा PP_ATOMVOLTAGECTRL_H

#समावेश "hwmgr.h"

/* As वापसed from PowerConnectorDetectionTable. */
#घोषणा PP_ATOM_POWER_BUDGET_DISABLE_OVERDRIVE  0x80
#घोषणा PP_ATOM_POWER_BUDGET_SHOW_WARNING       0x40
#घोषणा PP_ATOM_POWER_BUDGET_SHOW_WAIVER        0x20
#घोषणा PP_ATOM_POWER_POWER_BUDGET_BEHAVIOUR    0x0F

/* New functions क्रम Evergreen and beyond. */
#घोषणा PP_ATOMCTRL_MAX_VOLTAGE_ENTRIES 32

काष्ठा pp_atomctrl_घड़ी_भागiders अणु
	uपूर्णांक32_t pll_post_भागider;
	uपूर्णांक32_t pll_feedback_भागider;
	uपूर्णांक32_t pll_ref_भागider;
	bool  enable_post_भागider;
पूर्ण;

प्रकार काष्ठा pp_atomctrl_घड़ी_भागiders pp_atomctrl_घड़ी_भागiders;

जोड़ pp_atomctrl_tcipll_fb_भागider अणु
	काष्ठा अणु
		uपूर्णांक32_t ul_fb_भाग_frac : 14;
		uपूर्णांक32_t ul_fb_भाग : 12;
		uपूर्णांक32_t un_used : 6;
	पूर्ण;
	uपूर्णांक32_t ul_fb_भागider;
पूर्ण;

प्रकार जोड़ pp_atomctrl_tcipll_fb_भागider pp_atomctrl_tcipll_fb_भागider;

काष्ठा pp_atomctrl_घड़ी_भागiders_rv730 अणु
	uपूर्णांक32_t pll_post_भागider;
	pp_atomctrl_tcipll_fb_भागider mpll_feedback_भागider;
	uपूर्णांक32_t pll_ref_भागider;
	bool  enable_post_भागider;
	bool  enable_dithen;
	uपूर्णांक32_t vco_mode;
पूर्ण;
प्रकार काष्ठा pp_atomctrl_घड़ी_भागiders_rv730 pp_atomctrl_घड़ी_भागiders_rv730;


काष्ठा pp_atomctrl_घड़ी_भागiders_kong अणु
	uपूर्णांक32_t    pll_post_भागider;
	uपूर्णांक32_t    real_घड़ी;
पूर्ण;
प्रकार काष्ठा pp_atomctrl_घड़ी_भागiders_kong pp_atomctrl_घड़ी_भागiders_kong;

काष्ठा pp_atomctrl_घड़ी_भागiders_ci अणु
	uपूर्णांक32_t    pll_post_भागider;               /* post भागider value */
	uपूर्णांक32_t    real_घड़ी;
	pp_atomctrl_tcipll_fb_भागider   ul_fb_भाग;         /* Output Parameter: PLL FB भागider */
	uपूर्णांक8_t   uc_pll_ref_भाग;                      /* Output Parameter: PLL ref भागider */
	uपूर्णांक8_t   uc_pll_post_भाग;                      /* Output Parameter: PLL post भागider */
	uपूर्णांक8_t   uc_pll_cntl_flag;                    /*Output Flags: control flag */
पूर्ण;
प्रकार काष्ठा pp_atomctrl_घड़ी_भागiders_ci pp_atomctrl_घड़ी_भागiders_ci;

काष्ठा pp_atomctrl_घड़ी_भागiders_vi अणु
	uपूर्णांक32_t    pll_post_भागider;               /* post भागider value */
	uपूर्णांक32_t    real_घड़ी;
	pp_atomctrl_tcipll_fb_भागider   ul_fb_भाग;         /*Output Parameter: PLL FB भागider */
	uपूर्णांक8_t   uc_pll_ref_भाग;                      /*Output Parameter: PLL ref भागider */
	uपूर्णांक8_t   uc_pll_post_भाग;                     /*Output Parameter: PLL post भागider */
	uपूर्णांक8_t   uc_pll_cntl_flag;                    /*Output Flags: control flag */
पूर्ण;
प्रकार काष्ठा pp_atomctrl_घड़ी_भागiders_vi pp_atomctrl_घड़ी_भागiders_vi;

काष्ठा pp_atomctrl_घड़ी_भागiders_ai अणु
	u16 usSclk_fcw_frac;
	u16  usSclk_fcw_पूर्णांक;
	u8   ucSclkPostDiv;
	u8   ucSclkVcoMode;
	u8   ucSclkPllRange;
	u8   ucSscEnable;
	u16  usSsc_fcw1_frac;
	u16  usSsc_fcw1_पूर्णांक;
	u16  usReserved;
	u16  usPcc_fcw_पूर्णांक;
	u16  usSsc_fcw_slew_frac;
	u16  usPcc_fcw_slew_frac;
पूर्ण;
प्रकार काष्ठा pp_atomctrl_घड़ी_भागiders_ai pp_atomctrl_घड़ी_भागiders_ai;


जोड़ pp_atomctrl_s_mpll_fb_भागider अणु
	काष्ठा अणु
		uपूर्णांक32_t cl_kf : 12;
		uपूर्णांक32_t clk_frac : 12;
		uपूर्णांक32_t un_used : 8;
	पूर्ण;
	uपूर्णांक32_t ul_fb_भागider;
पूर्ण;
प्रकार जोड़ pp_atomctrl_s_mpll_fb_भागider pp_atomctrl_s_mpll_fb_भागider;

क्रमागत pp_atomctrl_spपढ़ो_spectrum_mode अणु
	pp_atomctrl_spपढ़ो_spectrum_mode_करोwn = 0,
	pp_atomctrl_spपढ़ो_spectrum_mode_center
पूर्ण;
प्रकार क्रमागत pp_atomctrl_spपढ़ो_spectrum_mode pp_atomctrl_spपढ़ो_spectrum_mode;

काष्ठा pp_atomctrl_memory_घड़ी_param अणु
	pp_atomctrl_s_mpll_fb_भागider mpll_fb_भागider;
	uपूर्णांक32_t mpll_post_भागider;
	uपूर्णांक32_t bw_ctrl;
	uपूर्णांक32_t dll_speed;
	uपूर्णांक32_t vco_mode;
	uपूर्णांक32_t yclk_sel;
	uपूर्णांक32_t qdr;
	uपूर्णांक32_t half_rate;
पूर्ण;
प्रकार काष्ठा pp_atomctrl_memory_घड़ी_param pp_atomctrl_memory_घड़ी_param;

काष्ठा pp_atomctrl_memory_घड़ी_param_ai अणु
	uपूर्णांक32_t ulClock;
	uपूर्णांक32_t ulPostDiv;
	uपूर्णांक16_t ulMclk_fcw_frac;
	uपूर्णांक16_t ulMclk_fcw_पूर्णांक;
पूर्ण;
प्रकार काष्ठा pp_atomctrl_memory_घड़ी_param_ai pp_atomctrl_memory_घड़ी_param_ai;

काष्ठा pp_atomctrl_पूर्णांकernal_ss_info अणु
	uपूर्णांक32_t speed_spectrum_percentage;                      /* in 1/100 percentage */
	uपूर्णांक32_t speed_spectrum_rate;                            /* in KHz */
	pp_atomctrl_spपढ़ो_spectrum_mode speed_spectrum_mode;
पूर्ण;
प्रकार काष्ठा pp_atomctrl_पूर्णांकernal_ss_info pp_atomctrl_पूर्णांकernal_ss_info;

#अगर_अघोषित NUMBER_OF_M3ARB_PARAMS
#घोषणा NUMBER_OF_M3ARB_PARAMS 3
#पूर्ण_अगर

#अगर_अघोषित NUMBER_OF_M3ARB_PARAM_SETS
#घोषणा NUMBER_OF_M3ARB_PARAM_SETS 10
#पूर्ण_अगर

काष्ठा pp_atomctrl_kong_प्रणाली_info अणु
	uपूर्णांक32_t			ul_bootup_uma_घड़ी;          /* in 10kHz unit */
	uपूर्णांक16_t			us_max_nb_voltage;            /* high NB voltage, calculated using current VDDNB (D24F2xDC) and VDDNB offset fuse; */
	uपूर्णांक16_t			us_min_nb_voltage;            /* low NB voltage, calculated using current VDDNB (D24F2xDC) and VDDNB offset fuse; */
	uपूर्णांक16_t			us_bootup_nb_voltage;         /* boot up NB voltage */
	uपूर्णांक8_t			uc_htc_पंचांगp_lmt;               /* bit [22:16] of D24F3x64 Hardware Thermal Control (HTC) Register, may not be needed, TBD */
	uपूर्णांक8_t			uc_tj_offset;                /* bit [28:22] of D24F3xE4 Thermtrip Status Register,may not be needed, TBD */
	/* 0: शेष 1: uvd 2: fs-3d */
	uपूर्णांक32_t          ul_csr_m3_srb_cntl[NUMBER_OF_M3ARB_PARAM_SETS][NUMBER_OF_M3ARB_PARAMS];/* arrays with values क्रम CSR M3 arbiter क्रम शेष */
पूर्ण;
प्रकार काष्ठा pp_atomctrl_kong_प्रणाली_info pp_atomctrl_kong_प्रणाली_info;

काष्ठा pp_atomctrl_memory_info अणु
	uपूर्णांक8_t memory_venकरोr;
	uपूर्णांक8_t memory_type;
पूर्ण;
प्रकार काष्ठा pp_atomctrl_memory_info pp_atomctrl_memory_info;

#घोषणा MAX_AC_TIMING_ENTRIES 16

काष्ठा pp_atomctrl_memory_घड़ी_range_table अणु
	uपूर्णांक8_t   num_entries;
	uपूर्णांक8_t   rsv[3];

	uपूर्णांक32_t mclk[MAX_AC_TIMING_ENTRIES];
पूर्ण;
प्रकार काष्ठा pp_atomctrl_memory_घड़ी_range_table pp_atomctrl_memory_घड़ी_range_table;

काष्ठा pp_atomctrl_voltage_table_entry अणु
	uपूर्णांक16_t value;
	uपूर्णांक32_t smio_low;
पूर्ण;

प्रकार काष्ठा pp_atomctrl_voltage_table_entry pp_atomctrl_voltage_table_entry;

काष्ठा pp_atomctrl_voltage_table अणु
	uपूर्णांक32_t count;
	uपूर्णांक32_t mask_low;
	uपूर्णांक32_t phase_delay;   /* Used क्रम ATOM_GPIO_VOLTAGE_OBJECT_V3 and later */
	pp_atomctrl_voltage_table_entry entries[PP_ATOMCTRL_MAX_VOLTAGE_ENTRIES];
पूर्ण;

प्रकार काष्ठा pp_atomctrl_voltage_table pp_atomctrl_voltage_table;

#घोषणा VBIOS_MC_REGISTER_ARRAY_SIZE           32
#घोषणा VBIOS_MAX_AC_TIMING_ENTRIES            20

काष्ठा pp_atomctrl_mc_reg_entry अणु
	uपूर्णांक32_t           mclk_max;
	uपूर्णांक32_t mc_data[VBIOS_MC_REGISTER_ARRAY_SIZE];
पूर्ण;
प्रकार काष्ठा pp_atomctrl_mc_reg_entry pp_atomctrl_mc_reg_entry;

काष्ठा pp_atomctrl_mc_रेजिस्टर_address अणु
	uपूर्णांक16_t s1;
	uपूर्णांक8_t  uc_pre_reg_data;
पूर्ण;

प्रकार काष्ठा pp_atomctrl_mc_रेजिस्टर_address pp_atomctrl_mc_रेजिस्टर_address;

#घोषणा MAX_SCLK_RANGE 8

काष्ठा pp_atom_ctrl_sclk_range_table_entryअणु
	uपूर्णांक8_t  ucVco_setting;
	uपूर्णांक8_t  ucPostभाग;
	uपूर्णांक16_t usFcw_pcc;
	uपूर्णांक16_t usFcw_trans_upper;
	uपूर्णांक16_t usRcw_trans_lower;
पूर्ण;


काष्ठा pp_atom_ctrl_sclk_range_tableअणु
	काष्ठा pp_atom_ctrl_sclk_range_table_entry entry[MAX_SCLK_RANGE];
पूर्ण;

काष्ठा pp_atomctrl_mc_reg_table अणु
	uपूर्णांक8_t                         last;                    /* number of रेजिस्टरs */
	uपूर्णांक8_t                         num_entries;             /* number of AC timing entries */
	pp_atomctrl_mc_reg_entry        mc_reg_table_entry[VBIOS_MAX_AC_TIMING_ENTRIES];
	pp_atomctrl_mc_रेजिस्टर_address mc_reg_address[VBIOS_MC_REGISTER_ARRAY_SIZE];
पूर्ण;
प्रकार काष्ठा pp_atomctrl_mc_reg_table pp_atomctrl_mc_reg_table;

काष्ठा pp_atomctrl_gpio_pin_assignment अणु
	uपूर्णांक16_t                   us_gpio_pin_aindex;
	uपूर्णांक8_t                    uc_gpio_pin_bit_shअगरt;
पूर्ण;
प्रकार काष्ठा pp_atomctrl_gpio_pin_assignment pp_atomctrl_gpio_pin_assignment;

काष्ठा pp_atom_ctrl__avfs_parameters अणु
	uपूर्णांक32_t  ulAVFS_meanNsigma_Acontant0;
	uपूर्णांक32_t  ulAVFS_meanNsigma_Acontant1;
	uपूर्णांक32_t  ulAVFS_meanNsigma_Acontant2;
	uपूर्णांक16_t usAVFS_meanNsigma_DC_tol_sigma;
	uपूर्णांक16_t usAVFS_meanNsigma_Platक्रमm_mean;
	uपूर्णांक16_t usAVFS_meanNsigma_Platक्रमm_sigma;
	uपूर्णांक32_t  ulGB_VDROOP_TABLE_CKSOFF_a0;
	uपूर्णांक32_t  ulGB_VDROOP_TABLE_CKSOFF_a1;
	uपूर्णांक32_t  ulGB_VDROOP_TABLE_CKSOFF_a2;
	uपूर्णांक32_t  ulGB_VDROOP_TABLE_CKSON_a0;
	uपूर्णांक32_t  ulGB_VDROOP_TABLE_CKSON_a1;
	uपूर्णांक32_t  ulGB_VDROOP_TABLE_CKSON_a2;
	uपूर्णांक32_t  ulAVFSGB_FUSE_TABLE_CKSOFF_m1;
	uपूर्णांक16_t  usAVFSGB_FUSE_TABLE_CKSOFF_m2;
	uपूर्णांक32_t  ulAVFSGB_FUSE_TABLE_CKSOFF_b;
	uपूर्णांक32_t  ulAVFSGB_FUSE_TABLE_CKSON_m1;
	uपूर्णांक16_t  usAVFSGB_FUSE_TABLE_CKSON_m2;
	uपूर्णांक32_t  ulAVFSGB_FUSE_TABLE_CKSON_b;
	uपूर्णांक16_t  usMaxVoltage_0_25mv;
	uपूर्णांक8_t  ucEnableGB_VDROOP_TABLE_CKSOFF;
	uपूर्णांक8_t  ucEnableGB_VDROOP_TABLE_CKSON;
	uपूर्णांक8_t  ucEnableGB_FUSE_TABLE_CKSOFF;
	uपूर्णांक8_t  ucEnableGB_FUSE_TABLE_CKSON;
	uपूर्णांक16_t usPSM_Age_ComFactor;
	uपूर्णांक8_t  ucEnableApplyAVFS_CKS_OFF_Voltage;
	uपूर्णांक8_t  ucReserved;
पूर्ण;

काष्ठा _AtomCtrl_HiLoLeakageOffsetTable
अणु
    USHORT usHiLoLeakageThreshold;
    USHORT usEdcDidtLoDpm7TableOffset;
    USHORT usEdcDidtHiDpm7TableOffset;
पूर्ण;
प्रकार काष्ठा _AtomCtrl_HiLoLeakageOffsetTable AtomCtrl_HiLoLeakageOffsetTable;

काष्ठा _AtomCtrl_EDCLeakgeTable
अणु
    ULONG DIDT_REG[24];
पूर्ण;
प्रकार काष्ठा _AtomCtrl_EDCLeakgeTable AtomCtrl_EDCLeakgeTable;

बाह्य bool atomctrl_get_pp_assign_pin(काष्ठा pp_hwmgr *hwmgr, स्थिर uपूर्णांक32_t pinId, pp_atomctrl_gpio_pin_assignment *gpio_pin_assignment);
बाह्य पूर्णांक atomctrl_get_voltage_evv_on_sclk(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक8_t voltage_type, uपूर्णांक32_t sclk, uपूर्णांक16_t भव_voltage_Id, uपूर्णांक16_t *voltage);
बाह्य पूर्णांक atomctrl_get_voltage_evv(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक16_t भव_voltage_id, uपूर्णांक16_t *voltage);
बाह्य uपूर्णांक32_t atomctrl_get_mpll_reference_घड़ी(काष्ठा pp_hwmgr *hwmgr);

bool atomctrl_is_asic_पूर्णांकernal_ss_supported(काष्ठा pp_hwmgr *hwmgr);
बाह्य पूर्णांक atomctrl_get_memory_घड़ी_spपढ़ो_spectrum(काष्ठा pp_hwmgr *hwmgr, स्थिर uपूर्णांक32_t memory_घड़ी, pp_atomctrl_पूर्णांकernal_ss_info *ssInfo);
बाह्य पूर्णांक atomctrl_get_engine_घड़ी_spपढ़ो_spectrum(काष्ठा pp_hwmgr *hwmgr, स्थिर uपूर्णांक32_t engine_घड़ी, pp_atomctrl_पूर्णांकernal_ss_info *ssInfo);
बाह्य पूर्णांक atomctrl_initialize_mc_reg_table(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक8_t module_index, pp_atomctrl_mc_reg_table *table);
बाह्य पूर्णांक atomctrl_initialize_mc_reg_table_v2_2(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक8_t module_index, pp_atomctrl_mc_reg_table *table);
बाह्य पूर्णांक atomctrl_set_engine_dram_timings_rv770(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t engine_घड़ी, uपूर्णांक32_t memory_घड़ी);
बाह्य uपूर्णांक32_t atomctrl_get_reference_घड़ी(काष्ठा pp_hwmgr *hwmgr);
बाह्य पूर्णांक atomctrl_get_memory_pll_भागiders_si(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t घड़ी_value, pp_atomctrl_memory_घड़ी_param *mpll_param, bool strobe_mode);
बाह्य पूर्णांक atomctrl_get_engine_pll_भागiders_vi(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t घड़ी_value, pp_atomctrl_घड़ी_भागiders_vi *भागiders);
बाह्य पूर्णांक atomctrl_get_dfs_pll_भागiders_vi(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t घड़ी_value, pp_atomctrl_घड़ी_भागiders_vi *भागiders);
बाह्य bool atomctrl_is_voltage_controlled_by_gpio_v3(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक8_t voltage_type, uपूर्णांक8_t voltage_mode);
बाह्य पूर्णांक atomctrl_get_voltage_table_v3(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक8_t voltage_type, uपूर्णांक8_t voltage_mode, pp_atomctrl_voltage_table *voltage_table);
बाह्य पूर्णांक atomctrl_get_memory_pll_भागiders_vi(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t घड़ी_value, pp_atomctrl_memory_घड़ी_param *mpll_param);
बाह्य पूर्णांक atomctrl_get_memory_pll_भागiders_ai(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t घड़ी_value, pp_atomctrl_memory_घड़ी_param_ai *mpll_param);
बाह्य पूर्णांक atomctrl_get_engine_pll_भागiders_kong(काष्ठा pp_hwmgr *hwmgr,
						 uपूर्णांक32_t घड़ी_value,
						 pp_atomctrl_घड़ी_भागiders_kong *भागiders);
बाह्य पूर्णांक atomctrl_पढ़ो_efuse(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक16_t start_index,
		uपूर्णांक16_t end_index, uपूर्णांक32_t *efuse);
बाह्य पूर्णांक atomctrl_calculate_voltage_evv_on_sclk(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक8_t voltage_type,
		uपूर्णांक32_t sclk, uपूर्णांक16_t भव_voltage_Id, uपूर्णांक16_t *voltage, uपूर्णांक16_t dpm_level, bool debug);
बाह्य पूर्णांक atomctrl_get_engine_pll_भागiders_ai(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t घड़ी_value, pp_atomctrl_घड़ी_भागiders_ai *भागiders);
बाह्य पूर्णांक atomctrl_set_ac_timing_ai(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t memory_घड़ी,
								uपूर्णांक8_t level);
बाह्य पूर्णांक atomctrl_get_voltage_evv_on_sclk_ai(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक8_t voltage_type,
				uपूर्णांक32_t sclk, uपूर्णांक16_t भव_voltage_Id, uपूर्णांक32_t *voltage);
बाह्य पूर्णांक atomctrl_get_smc_sclk_range_table(काष्ठा pp_hwmgr *hwmgr, काष्ठा pp_atom_ctrl_sclk_range_table *table);

बाह्य पूर्णांक atomctrl_get_avfs_inक्रमmation(काष्ठा pp_hwmgr *hwmgr, काष्ठा pp_atom_ctrl__avfs_parameters *param);

बाह्य पूर्णांक  atomctrl_get_svi2_info(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक8_t voltage_type,
				uपूर्णांक8_t *svd_gpio_id, uपूर्णांक8_t *svc_gpio_id,
				uपूर्णांक16_t *load_line);

बाह्य पूर्णांक atomctrl_get_leakage_vddc_base_on_leakage(काष्ठा pp_hwmgr *hwmgr,
					uपूर्णांक16_t *vddc, uपूर्णांक16_t *vddci,
					uपूर्णांक16_t भव_voltage_id,
					uपूर्णांक16_t efuse_voltage_id);
बाह्य पूर्णांक atomctrl_get_leakage_id_from_efuse(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक16_t *भव_voltage_id);

बाह्य व्योम atomctrl_get_voltage_range(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t *max_vddc,
							uपूर्णांक32_t *min_vddc);

बाह्य पूर्णांक atomctrl_get_edc_hilo_leakage_offset_table(काष्ठा pp_hwmgr *hwmgr,
						      AtomCtrl_HiLoLeakageOffsetTable *table);

बाह्य पूर्णांक atomctrl_get_edc_leakage_table(काष्ठा pp_hwmgr *hwmgr,
					  AtomCtrl_EDCLeakgeTable *table,
					  uपूर्णांक16_t offset);

बाह्य पूर्णांक atomctrl_get_vddc_shared_railinfo(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक8_t *shared_rail);
#पूर्ण_अगर

