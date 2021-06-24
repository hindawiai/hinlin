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
 */

#अगर_अघोषित SMU10_H
#घोषणा SMU10_H

#आशय pack(push, 1)

#घोषणा ENABLE_DEBUG_FEATURES

/* Feature Control Defines */
#घोषणा FEATURE_CCLK_CONTROLLER_BIT   0
#घोषणा FEATURE_FAN_CONTROLLER_BIT    1
#घोषणा FEATURE_DATA_CALCULATION_BIT  2
#घोषणा FEATURE_PPT_BIT               3
#घोषणा FEATURE_TDC_BIT               4
#घोषणा FEATURE_THERMAL_BIT           5
#घोषणा FEATURE_FIT_BIT               6
#घोषणा FEATURE_EDC_BIT               7
#घोषणा FEATURE_PLL_POWER_DOWN_BIT    8
#घोषणा FEATURE_ULV_BIT               9
#घोषणा FEATURE_VDDOFF_BIT            10
#घोषणा FEATURE_VCN_DPM_BIT           11
#घोषणा FEATURE_ACP_DPM_BIT           12
#घोषणा FEATURE_ISP_DPM_BIT           13
#घोषणा FEATURE_FCLK_DPM_BIT          14
#घोषणा FEATURE_SOCCLK_DPM_BIT        15
#घोषणा FEATURE_MP0CLK_DPM_BIT        16
#घोषणा FEATURE_LCLK_DPM_BIT          17
#घोषणा FEATURE_SHUBCLK_DPM_BIT       18
#घोषणा FEATURE_DCEFCLK_DPM_BIT       19
#घोषणा FEATURE_GFX_DPM_BIT           20
#घोषणा FEATURE_DS_GFXCLK_BIT         21
#घोषणा FEATURE_DS_SOCCLK_BIT         22
#घोषणा FEATURE_DS_LCLK_BIT           23
#घोषणा FEATURE_DS_DCEFCLK_BIT        24
#घोषणा FEATURE_DS_SHUBCLK_BIT        25
#घोषणा FEATURE_RM_BIT                26
#घोषणा FEATURE_S0i2_BIT              27
#घोषणा FEATURE_WHISPER_MODE_BIT      28
#घोषणा FEATURE_DS_FCLK_BIT           29
#घोषणा FEATURE_DS_SMNCLK_BIT         30
#घोषणा FEATURE_DS_MP1CLK_BIT         31
#घोषणा FEATURE_DS_MP0CLK_BIT         32
#घोषणा FEATURE_MGCG_BIT              33
#घोषणा FEATURE_DS_FUSE_SRAM_BIT      34
#घोषणा FEATURE_GFX_CKS               35
#घोषणा FEATURE_PSI0_BIT              36
#घोषणा FEATURE_PROCHOT_BIT           37
#घोषणा FEATURE_CPUOFF_BIT            38
#घोषणा FEATURE_STAPM_BIT             39
#घोषणा FEATURE_CORE_CSTATES_BIT      40
#घोषणा FEATURE_SPARE_41_BIT          41
#घोषणा FEATURE_SPARE_42_BIT          42
#घोषणा FEATURE_SPARE_43_BIT          43
#घोषणा FEATURE_SPARE_44_BIT          44
#घोषणा FEATURE_SPARE_45_BIT          45
#घोषणा FEATURE_SPARE_46_BIT          46
#घोषणा FEATURE_SPARE_47_BIT          47
#घोषणा FEATURE_SPARE_48_BIT          48
#घोषणा FEATURE_SPARE_49_BIT          49
#घोषणा FEATURE_SPARE_50_BIT          50
#घोषणा FEATURE_SPARE_51_BIT          51
#घोषणा FEATURE_SPARE_52_BIT          52
#घोषणा FEATURE_SPARE_53_BIT          53
#घोषणा FEATURE_SPARE_54_BIT          54
#घोषणा FEATURE_SPARE_55_BIT          55
#घोषणा FEATURE_SPARE_56_BIT          56
#घोषणा FEATURE_SPARE_57_BIT          57
#घोषणा FEATURE_SPARE_58_BIT          58
#घोषणा FEATURE_SPARE_59_BIT          59
#घोषणा FEATURE_SPARE_60_BIT          60
#घोषणा FEATURE_SPARE_61_BIT          61
#घोषणा FEATURE_SPARE_62_BIT          62
#घोषणा FEATURE_SPARE_63_BIT          63

#घोषणा NUM_FEATURES                  64

#घोषणा FEATURE_CCLK_CONTROLLER_MASK  (1 << FEATURE_CCLK_CONTROLLER_BIT)
#घोषणा FEATURE_FAN_CONTROLLER_MASK   (1 << FEATURE_FAN_CONTROLLER_BIT)
#घोषणा FEATURE_DATA_CALCULATION_MASK (1 << FEATURE_DATA_CALCULATION_BIT)
#घोषणा FEATURE_PPT_MASK              (1 << FEATURE_PPT_BIT)
#घोषणा FEATURE_TDC_MASK              (1 << FEATURE_TDC_BIT)
#घोषणा FEATURE_THERMAL_MASK          (1 << FEATURE_THERMAL_BIT)
#घोषणा FEATURE_FIT_MASK              (1 << FEATURE_FIT_BIT)
#घोषणा FEATURE_EDC_MASK              (1 << FEATURE_EDC_BIT)
#घोषणा FEATURE_PLL_POWER_DOWN_MASK   (1 << FEATURE_PLL_POWER_DOWN_BIT)
#घोषणा FEATURE_ULV_MASK              (1 << FEATURE_ULV_BIT)
#घोषणा FEATURE_VDDOFF_MASK           (1 << FEATURE_VDDOFF_BIT)
#घोषणा FEATURE_VCN_DPM_MASK          (1 << FEATURE_VCN_DPM_BIT)
#घोषणा FEATURE_ACP_DPM_MASK          (1 << FEATURE_ACP_DPM_BIT)
#घोषणा FEATURE_ISP_DPM_MASK          (1 << FEATURE_ISP_DPM_BIT)
#घोषणा FEATURE_FCLK_DPM_MASK         (1 << FEATURE_FCLK_DPM_BIT)
#घोषणा FEATURE_SOCCLK_DPM_MASK       (1 << FEATURE_SOCCLK_DPM_BIT)
#घोषणा FEATURE_MP0CLK_DPM_MASK       (1 << FEATURE_MP0CLK_DPM_BIT)
#घोषणा FEATURE_LCLK_DPM_MASK         (1 << FEATURE_LCLK_DPM_BIT)
#घोषणा FEATURE_SHUBCLK_DPM_MASK      (1 << FEATURE_SHUBCLK_DPM_BIT)
#घोषणा FEATURE_DCEFCLK_DPM_MASK      (1 << FEATURE_DCEFCLK_DPM_BIT)
#घोषणा FEATURE_GFX_DPM_MASK          (1 << FEATURE_GFX_DPM_BIT)
#घोषणा FEATURE_DS_GFXCLK_MASK        (1 << FEATURE_DS_GFXCLK_BIT)
#घोषणा FEATURE_DS_SOCCLK_MASK        (1 << FEATURE_DS_SOCCLK_BIT)
#घोषणा FEATURE_DS_LCLK_MASK          (1 << FEATURE_DS_LCLK_BIT)
#घोषणा FEATURE_DS_DCEFCLK_MASK       (1 << FEATURE_DS_DCEFCLK_BIT)
#घोषणा FEATURE_DS_SHUBCLK_MASK       (1 << FEATURE_DS_SHUBCLK_BIT)
#घोषणा FEATURE_RM_MASK               (1 << FEATURE_RM_BIT)
#घोषणा FEATURE_DS_FCLK_MASK          (1 << FEATURE_DS_FCLK_BIT)
#घोषणा FEATURE_DS_SMNCLK_MASK        (1 << FEATURE_DS_SMNCLK_BIT)
#घोषणा FEATURE_DS_MP1CLK_MASK        (1 << FEATURE_DS_MP1CLK_BIT)
#घोषणा FEATURE_DS_MP0CLK_MASK        (1 << FEATURE_DS_MP0CLK_BIT)
#घोषणा FEATURE_MGCG_MASK             (1 << FEATURE_MGCG_BIT)
#घोषणा FEATURE_DS_FUSE_SRAM_MASK     (1 << FEATURE_DS_FUSE_SRAM_BIT)
#घोषणा FEATURE_PSI0_MASK             (1 << FEATURE_PSI0_BIT)
#घोषणा FEATURE_STAPM_MASK            (1 << FEATURE_STAPM_BIT)
#घोषणा FEATURE_PROCHOT_MASK          (1 << FEATURE_PROCHOT_BIT)
#घोषणा FEATURE_CPUOFF_MASK           (1 << FEATURE_CPUOFF_BIT)
#घोषणा FEATURE_CORE_CSTATES_MASK     (1 << FEATURE_CORE_CSTATES_BIT)

/* Workload bits */
#घोषणा WORKLOAD_PPLIB_FULL_SCREEN_3D_BIT 0
#घोषणा WORKLOAD_PPLIB_VIDEO_BIT          2
#घोषणा WORKLOAD_PPLIB_VR_BIT             3
#घोषणा WORKLOAD_PPLIB_COMPUTE_BIT        4
#घोषणा WORKLOAD_PPLIB_CUSTOM_BIT         5
#घोषणा WORKLOAD_PPLIB_COUNT              6

प्रकार काष्ठा अणु
	/* MP1_EXT_SCRATCH0 */
	uपूर्णांक32_t CurrLevel_ACP     : 4;
	uपूर्णांक32_t CurrLevel_ISP     : 4;
	uपूर्णांक32_t CurrLevel_VCN     : 4;
	uपूर्णांक32_t CurrLevel_LCLK    : 4;
	uपूर्णांक32_t CurrLevel_MP0CLK  : 4;
	uपूर्णांक32_t CurrLevel_FCLK    : 4;
	uपूर्णांक32_t CurrLevel_SOCCLK  : 4;
	uपूर्णांक32_t CurrLevel_DCEFCLK : 4;
	/* MP1_EXT_SCRATCH1 */
	uपूर्णांक32_t TargLevel_ACP     : 4;
	uपूर्णांक32_t TargLevel_ISP     : 4;
	uपूर्णांक32_t TargLevel_VCN     : 4;
	uपूर्णांक32_t TargLevel_LCLK    : 4;
	uपूर्णांक32_t TargLevel_MP0CLK  : 4;
	uपूर्णांक32_t TargLevel_FCLK    : 4;
	uपूर्णांक32_t TargLevel_SOCCLK  : 4;
	uपूर्णांक32_t TargLevel_DCEFCLK : 4;
	/* MP1_EXT_SCRATCH2 */
	uपूर्णांक32_t CurrLevel_SHUBCLK  : 4;
	uपूर्णांक32_t TargLevel_SHUBCLK  : 4;
	uपूर्णांक32_t InUlv              : 1;
	uपूर्णांक32_t InS0i2             : 1;
	uपूर्णांक32_t InWhisperMode      : 1;
	uपूर्णांक32_t Reserved           : 21;
	/* MP1_EXT_SCRATCH3-4 */
	uपूर्णांक32_t Reserved2[2];
	/* MP1_EXT_SCRATCH5 */
	uपूर्णांक32_t FeatureStatus[NUM_FEATURES / 32];
पूर्ण FwStatus_t;

#घोषणा TABLE_BIOS_IF            0 /* Called by BIOS */
#घोषणा TABLE_WATERMARKS         1 /* Called by Driver */
#घोषणा TABLE_CUSTOM_DPM         2 /* Called by Driver */
#घोषणा TABLE_PMSTATUSLOG        3 /* Called by Tools क्रम Agm logging */
#घोषणा TABLE_DPMCLOCKS          4 /* Called by Driver */
#घोषणा TABLE_MOMENTARY_PM       5 /* Called by Tools */
#घोषणा TABLE_COUNT              6

#आशय pack(pop)

#पूर्ण_अगर
