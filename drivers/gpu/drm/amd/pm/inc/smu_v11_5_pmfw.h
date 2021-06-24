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
 */

#अगर_अघोषित __SMU_V11_5_0_PMFW_H__
#घोषणा __SMU_V11_5_0_PMFW_H__

#समावेश "smu11_driver_if_vangogh.h"

#आशय pack(push, 1)

#घोषणा ENABLE_DEBUG_FEATURES

// Feature Control Defines
#घोषणा FEATURE_CCLK_DPM_BIT           0
#घोषणा FEATURE_FAN_CONTROLLER_BIT     1
#घोषणा FEATURE_DATA_CALCULATION_BIT   2
#घोषणा FEATURE_PPT_BIT                3
#घोषणा FEATURE_TDC_BIT                4
#घोषणा FEATURE_THERMAL_BIT            5
#घोषणा FEATURE_FIT_BIT                6
#घोषणा FEATURE_EDC_BIT                7
#घोषणा FEATURE_PLL_POWER_DOWN_BIT     8
#घोषणा FEATURE_ULV_BIT                9
#घोषणा FEATURE_VDDOFF_BIT            10
#घोषणा FEATURE_VCN_DPM_BIT           11
#घोषणा FEATURE_CSTATE_BOOST_BIT      12
#घोषणा FEATURE_FCLK_DPM_BIT          13
#घोषणा FEATURE_SOCCLK_DPM_BIT        14
#घोषणा FEATURE_MP0CLK_DPM_BIT        15
#घोषणा FEATURE_LCLK_DPM_BIT          16
#घोषणा FEATURE_SHUBCLK_DPM_BIT       17
#घोषणा FEATURE_DCFCLK_DPM_BIT        18
#घोषणा FEATURE_GFX_DPM_BIT           19
#घोषणा FEATURE_DS_GFXCLK_BIT         20
#घोषणा FEATURE_DS_SOCCLK_BIT         21
#घोषणा FEATURE_DS_LCLK_BIT           22
#घोषणा FEATURE_DS_DCFCLK_BIT         23
#घोषणा FEATURE_DS_SHUBCLK_BIT        24
#घोषणा FEATURE_GFX_TEMP_VMIN_BIT     25
#घोषणा FEATURE_S0I2_BIT              26
#घोषणा FEATURE_WHISPER_MODE_BIT      27
#घोषणा FEATURE_DS_FCLK_BIT           28
#घोषणा FEATURE_DS_SMNCLK_BIT         29
#घोषणा FEATURE_DS_MP1CLK_BIT         30
#घोषणा FEATURE_DS_MP0CLK_BIT         31
#घोषणा FEATURE_SMU_LOW_POWER_BIT     32
#घोषणा FEATURE_FUSE_PG_BIT           33
#घोषणा FEATURE_GFX_DEM_BIT           34
#घोषणा FEATURE_PSI_BIT               35
#घोषणा FEATURE_PROCHOT_BIT           36
#घोषणा FEATURE_CPUOFF_BIT            37
#घोषणा FEATURE_STAPM_BIT             38
#घोषणा FEATURE_S0I3_BIT              39
#घोषणा FEATURE_DF_CSTATES_BIT        40
#घोषणा FEATURE_PERF_LIMIT_BIT        41
#घोषणा FEATURE_CORE_DLDO_BIT         42
#घोषणा FEATURE_RSMU_LOW_POWER_BIT    43
#घोषणा FEATURE_SMN_LOW_POWER_BIT     44
#घोषणा FEATURE_THM_LOW_POWER_BIT     45
#घोषणा FEATURE_SMUIO_LOW_POWER_BIT   46
#घोषणा FEATURE_MP1_LOW_POWER_BIT     47
#घोषणा FEATURE_DS_VCN_BIT            48
#घोषणा FEATURE_CPPC_BIT              49
#घोषणा FEATURE_OS_CSTATES_BIT        50
#घोषणा FEATURE_ISP_DPM_BIT           51
#घोषणा FEATURE_A55_DPM_BIT           52
#घोषणा FEATURE_CVIP_DSP_DPM_BIT      53
#घोषणा FEATURE_MSMU_LOW_POWER_BIT    54
#घोषणा FEATURE_SOC_VOLTAGE_MON_BIT   55
#घोषणा FEATURE_ATHUB_PG_BIT          56
#घोषणा FEATURE_ECO_DEEPCSTATE_BIT    57
#घोषणा FEATURE_CC6_BIT               58
#घोषणा FEATURE_GFX_EDC_BIT           59
#घोषणा NUM_FEATURES                  60

प्रकार काष्ठा अणु
  // MP1_EXT_SCRATCH0
  uपूर्णांक32_t DpmHandlerID         : 8;
  uपूर्णांक32_t ActivityMonitorID    : 8;
  uपूर्णांक32_t DpmTimerID           : 8;
  uपूर्णांक32_t DpmHubID             : 4;
  uपूर्णांक32_t DpmHubTask           : 4;
  // MP1_EXT_SCRATCH1
  uपूर्णांक32_t GfxStatus            : 2;
  uपूर्णांक32_t GfxoffStatus         : 8;
  uपूर्णांक32_t CpuOff               : 1;
  uपूर्णांक32_t VddOff               : 1;
  uपूर्णांक32_t InUlv                : 1;
  uपूर्णांक32_t InS0i2               : 2;
  uपूर्णांक32_t InWhisperMode        : 1;
  uपूर्णांक32_t spare1               : 16;
  // MP1_EXT_SCRATCH2
  uपूर्णांक32_t P2JobHandler			: 32;
  // MP1_EXT_SCRATCH3: used क्रम postcodes

  // MP1_EXT_SCRATCH4:6 are used by Kernel
  // MP1_EXT_SCRATCH7: used by HW
पूर्ण FwStatus_t;


#आशय pack(pop)

#पूर्ण_अगर
