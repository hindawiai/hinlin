<शैली गुरु>
/*
 * Copyright 2011 Advanced Micro Devices, Inc.
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
#अगर_अघोषित __R600_DPM_H__
#घोषणा __R600_DPM_H__

#समावेश "radeon.h"

#घोषणा R600_ASI_DFLT                                10000
#घोषणा R600_BSP_DFLT                                0x41EB
#घोषणा R600_BSU_DFLT                                0x2
#घोषणा R600_AH_DFLT                                 5
#घोषणा R600_RLP_DFLT                                25
#घोषणा R600_RMP_DFLT                                65
#घोषणा R600_LHP_DFLT                                40
#घोषणा R600_LMP_DFLT                                15
#घोषणा R600_TD_DFLT                                 0
#घोषणा R600_UTC_DFLT_00                             0x24
#घोषणा R600_UTC_DFLT_01                             0x22
#घोषणा R600_UTC_DFLT_02                             0x22
#घोषणा R600_UTC_DFLT_03                             0x22
#घोषणा R600_UTC_DFLT_04                             0x22
#घोषणा R600_UTC_DFLT_05                             0x22
#घोषणा R600_UTC_DFLT_06                             0x22
#घोषणा R600_UTC_DFLT_07                             0x22
#घोषणा R600_UTC_DFLT_08                             0x22
#घोषणा R600_UTC_DFLT_09                             0x22
#घोषणा R600_UTC_DFLT_10                             0x22
#घोषणा R600_UTC_DFLT_11                             0x22
#घोषणा R600_UTC_DFLT_12                             0x22
#घोषणा R600_UTC_DFLT_13                             0x22
#घोषणा R600_UTC_DFLT_14                             0x22
#घोषणा R600_DTC_DFLT_00                             0x24
#घोषणा R600_DTC_DFLT_01                             0x22
#घोषणा R600_DTC_DFLT_02                             0x22
#घोषणा R600_DTC_DFLT_03                             0x22
#घोषणा R600_DTC_DFLT_04                             0x22
#घोषणा R600_DTC_DFLT_05                             0x22
#घोषणा R600_DTC_DFLT_06                             0x22
#घोषणा R600_DTC_DFLT_07                             0x22
#घोषणा R600_DTC_DFLT_08                             0x22
#घोषणा R600_DTC_DFLT_09                             0x22
#घोषणा R600_DTC_DFLT_10                             0x22
#घोषणा R600_DTC_DFLT_11                             0x22
#घोषणा R600_DTC_DFLT_12                             0x22
#घोषणा R600_DTC_DFLT_13                             0x22
#घोषणा R600_DTC_DFLT_14                             0x22
#घोषणा R600_VRC_DFLT                                0x0000C003
#घोषणा R600_VOLTAGERESPONSETIME_DFLT                1000
#घोषणा R600_BACKBIASRESPONSETIME_DFLT               1000
#घोषणा R600_VRU_DFLT                                0x3
#घोषणा R600_SPLLSTEPTIME_DFLT                       0x1000
#घोषणा R600_SPLLSTEPUNIT_DFLT                       0x3
#घोषणा R600_TPU_DFLT                                0
#घोषणा R600_TPC_DFLT                                0x200
#घोषणा R600_SSTU_DFLT                               0
#घोषणा R600_SST_DFLT                                0x00C8
#घोषणा R600_GICST_DFLT                              0x200
#घोषणा R600_FCT_DFLT                                0x0400
#घोषणा R600_FCTU_DFLT                               0
#घोषणा R600_CTXCGTT3DRPHC_DFLT                      0x20
#घोषणा R600_CTXCGTT3DRSDC_DFLT                      0x40
#घोषणा R600_VDDC3DOORPHC_DFLT                       0x100
#घोषणा R600_VDDC3DOORSDC_DFLT                       0x7
#घोषणा R600_VDDC3DOORSU_DFLT                        0
#घोषणा R600_MPLLLOCKTIME_DFLT                       100
#घोषणा R600_MPLLRESETTIME_DFLT                      150
#घोषणा R600_VCOSTEPPCT_DFLT                          20
#घोषणा R600_ENDINGVCOSTEPPCT_DFLT                    5
#घोषणा R600_REFERENCEDIVIDER_DFLT                    4

#घोषणा R600_PM_NUMBER_OF_TC 15
#घोषणा R600_PM_NUMBER_OF_SCLKS 20
#घोषणा R600_PM_NUMBER_OF_MCLKS 4
#घोषणा R600_PM_NUMBER_OF_VOLTAGE_LEVELS 4
#घोषणा R600_PM_NUMBER_OF_ACTIVITY_LEVELS 3

/* XXX are these ok? */
#घोषणा R600_TEMP_RANGE_MIN (90 * 1000)
#घोषणा R600_TEMP_RANGE_MAX (120 * 1000)

#घोषणा FDO_PWM_MODE_STATIC  1
#घोषणा FDO_PWM_MODE_STATIC_RPM 5

क्रमागत r600_घातer_level अणु
	R600_POWER_LEVEL_LOW = 0,
	R600_POWER_LEVEL_MEDIUM = 1,
	R600_POWER_LEVEL_HIGH = 2,
	R600_POWER_LEVEL_CTXSW = 3,
पूर्ण;

क्रमागत r600_td अणु
	R600_TD_AUTO,
	R600_TD_UP,
	R600_TD_DOWN,
पूर्ण;

क्रमागत r600_display_watermark अणु
	R600_DISPLAY_WATERMARK_LOW = 0,
	R600_DISPLAY_WATERMARK_HIGH = 1,
पूर्ण;

क्रमागत r600_display_gap
अणु
    R600_PM_DISPLAY_GAP_VBLANK_OR_WM = 0,
    R600_PM_DISPLAY_GAP_VBLANK       = 1,
    R600_PM_DISPLAY_GAP_WATERMARK    = 2,
    R600_PM_DISPLAY_GAP_IGNORE       = 3,
पूर्ण;

बाह्य स्थिर u32 r600_utc[R600_PM_NUMBER_OF_TC];
बाह्य स्थिर u32 r600_dtc[R600_PM_NUMBER_OF_TC];

व्योम r600_dpm_prपूर्णांक_class_info(u32 class, u32 class2);
व्योम r600_dpm_prपूर्णांक_cap_info(u32 caps);
व्योम r600_dpm_prपूर्णांक_ps_status(काष्ठा radeon_device *rdev,
			      काष्ठा radeon_ps *rps);
u32 r600_dpm_get_vblank_समय(काष्ठा radeon_device *rdev);
u32 r600_dpm_get_vrefresh(काष्ठा radeon_device *rdev);
bool r600_is_uvd_state(u32 class, u32 class2);
व्योम r600_calculate_u_and_p(u32 i, u32 r_c, u32 p_b,
			    u32 *p, u32 *u);
पूर्णांक r600_calculate_at(u32 t, u32 h, u32 fh, u32 fl, u32 *tl, u32 *th);
व्योम r600_gfx_घड़ीgating_enable(काष्ठा radeon_device *rdev, bool enable);
व्योम r600_dynamicpm_enable(काष्ठा radeon_device *rdev, bool enable);
व्योम r600_enable_thermal_protection(काष्ठा radeon_device *rdev, bool enable);
व्योम r600_enable_acpi_pm(काष्ठा radeon_device *rdev);
व्योम r600_enable_dynamic_pcie_gen2(काष्ठा radeon_device *rdev, bool enable);
bool r600_dynamicpm_enabled(काष्ठा radeon_device *rdev);
व्योम r600_enable_sclk_control(काष्ठा radeon_device *rdev, bool enable);
व्योम r600_enable_mclk_control(काष्ठा radeon_device *rdev, bool enable);
व्योम r600_enable_spll_bypass(काष्ठा radeon_device *rdev, bool enable);
व्योम r600_रुको_क्रम_spll_change(काष्ठा radeon_device *rdev);
व्योम r600_set_bsp(काष्ठा radeon_device *rdev, u32 u, u32 p);
व्योम r600_set_at(काष्ठा radeon_device *rdev,
		 u32 l_to_m, u32 m_to_h,
		 u32 h_to_m, u32 m_to_l);
व्योम r600_set_tc(काष्ठा radeon_device *rdev, u32 index, u32 u_t, u32 d_t);
व्योम r600_select_td(काष्ठा radeon_device *rdev, क्रमागत r600_td td);
व्योम r600_set_vrc(काष्ठा radeon_device *rdev, u32 vrv);
व्योम r600_set_tpu(काष्ठा radeon_device *rdev, u32 u);
व्योम r600_set_tpc(काष्ठा radeon_device *rdev, u32 c);
व्योम r600_set_sstu(काष्ठा radeon_device *rdev, u32 u);
व्योम r600_set_sst(काष्ठा radeon_device *rdev, u32 t);
व्योम r600_set_git(काष्ठा radeon_device *rdev, u32 t);
व्योम r600_set_fctu(काष्ठा radeon_device *rdev, u32 u);
व्योम r600_set_fct(काष्ठा radeon_device *rdev, u32 t);
व्योम r600_set_ctxcgtt3d_rphc(काष्ठा radeon_device *rdev, u32 p);
व्योम r600_set_ctxcgtt3d_rsdc(काष्ठा radeon_device *rdev, u32 s);
व्योम r600_set_vddc3d_oorsu(काष्ठा radeon_device *rdev, u32 u);
व्योम r600_set_vddc3d_oorphc(काष्ठा radeon_device *rdev, u32 p);
व्योम r600_set_vddc3d_oorsdc(काष्ठा radeon_device *rdev, u32 s);
व्योम r600_set_mpll_lock_समय(काष्ठा radeon_device *rdev, u32 lock_समय);
व्योम r600_set_mpll_reset_समय(काष्ठा radeon_device *rdev, u32 reset_समय);
व्योम r600_engine_घड़ी_entry_enable(काष्ठा radeon_device *rdev,
				    u32 index, bool enable);
व्योम r600_engine_घड़ी_entry_enable_pulse_skipping(काष्ठा radeon_device *rdev,
						   u32 index, bool enable);
व्योम r600_engine_घड़ी_entry_enable_post_भागider(काष्ठा radeon_device *rdev,
						 u32 index, bool enable);
व्योम r600_engine_घड़ी_entry_set_post_भागider(काष्ठा radeon_device *rdev,
					      u32 index, u32 भागider);
व्योम r600_engine_घड़ी_entry_set_reference_भागider(काष्ठा radeon_device *rdev,
						   u32 index, u32 भागider);
व्योम r600_engine_घड़ी_entry_set_feedback_भागider(काष्ठा radeon_device *rdev,
						  u32 index, u32 भागider);
व्योम r600_engine_घड़ी_entry_set_step_समय(काष्ठा radeon_device *rdev,
					   u32 index, u32 step_समय);
व्योम r600_vid_rt_set_ssu(काष्ठा radeon_device *rdev, u32 u);
व्योम r600_vid_rt_set_vru(काष्ठा radeon_device *rdev, u32 u);
व्योम r600_vid_rt_set_vrt(काष्ठा radeon_device *rdev, u32 rt);
व्योम r600_voltage_control_enable_pins(काष्ठा radeon_device *rdev,
				      u64 mask);
व्योम r600_voltage_control_program_voltages(काष्ठा radeon_device *rdev,
					   क्रमागत r600_घातer_level index, u64 pins);
व्योम r600_voltage_control_deactivate_अटल_control(काष्ठा radeon_device *rdev,
						    u64 mask);
व्योम r600_घातer_level_enable(काष्ठा radeon_device *rdev,
			     क्रमागत r600_घातer_level index, bool enable);
व्योम r600_घातer_level_set_voltage_index(काष्ठा radeon_device *rdev,
					क्रमागत r600_घातer_level index, u32 voltage_index);
व्योम r600_घातer_level_set_mem_घड़ी_index(काष्ठा radeon_device *rdev,
					  क्रमागत r600_घातer_level index, u32 mem_घड़ी_index);
व्योम r600_घातer_level_set_eng_घड़ी_index(काष्ठा radeon_device *rdev,
					  क्रमागत r600_घातer_level index, u32 eng_घड़ी_index);
व्योम r600_घातer_level_set_watermark_id(काष्ठा radeon_device *rdev,
				       क्रमागत r600_घातer_level index,
				       क्रमागत r600_display_watermark watermark_id);
व्योम r600_घातer_level_set_pcie_gen2(काष्ठा radeon_device *rdev,
				    क्रमागत r600_घातer_level index, bool compatible);
क्रमागत r600_घातer_level r600_घातer_level_get_current_index(काष्ठा radeon_device *rdev);
क्रमागत r600_घातer_level r600_घातer_level_get_target_index(काष्ठा radeon_device *rdev);
व्योम r600_घातer_level_set_enter_index(काष्ठा radeon_device *rdev,
				      क्रमागत r600_घातer_level index);
व्योम r600_रुको_क्रम_घातer_level_unequal(काष्ठा radeon_device *rdev,
				       क्रमागत r600_घातer_level index);
व्योम r600_रुको_क्रम_घातer_level(काष्ठा radeon_device *rdev,
			       क्रमागत r600_घातer_level index);
व्योम r600_start_dpm(काष्ठा radeon_device *rdev);
व्योम r600_stop_dpm(काष्ठा radeon_device *rdev);

bool r600_is_पूर्णांकernal_thermal_sensor(क्रमागत radeon_पूर्णांक_thermal_type sensor);

पूर्णांक r600_get_platक्रमm_caps(काष्ठा radeon_device *rdev);

पूर्णांक r600_parse_extended_घातer_table(काष्ठा radeon_device *rdev);
व्योम r600_मुक्त_extended_घातer_table(काष्ठा radeon_device *rdev);

क्रमागत radeon_pcie_gen r600_get_pcie_gen_support(काष्ठा radeon_device *rdev,
					       u32 sys_mask,
					       क्रमागत radeon_pcie_gen asic_gen,
					       क्रमागत radeon_pcie_gen शेष_gen);

u16 r600_get_pcie_lane_support(काष्ठा radeon_device *rdev,
			       u16 asic_lanes,
			       u16 शेष_lanes);
u8 r600_encode_pci_lane_width(u32 lanes);

#पूर्ण_अगर
