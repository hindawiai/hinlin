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
#अगर_अघोषित __SMU11_DRIVER_IF_VANGOGH_H__
#घोषणा __SMU11_DRIVER_IF_VANGOGH_H__

// *** IMPORTANT ***
// SMU TEAM: Always increment the पूर्णांकerface version अगर
// any काष्ठाure is changed in this file
#घोषणा SMU13_DRIVER_IF_VERSION 3

प्रकार काष्ठा अणु
  पूर्णांक32_t value;
  uपूर्णांक32_t numFractionalBits;
पूर्ण FloatInIntFormat_t;

प्रकार क्रमागत अणु
  DSPCLK_DCFCLK = 0,
  DSPCLK_DISPCLK,
  DSPCLK_PIXCLK,
  DSPCLK_PHYCLK,
  DSPCLK_COUNT,
पूर्ण DSPCLK_e;

प्रकार काष्ठा अणु
  uपूर्णांक16_t Freq; // in MHz
  uपूर्णांक16_t Vid;  // min voltage in SVI2 VID
पूर्ण DisplayClockTable_t;

प्रकार काष्ठा अणु
  uपूर्णांक16_t MinClock; // This is either DCFCLK or SOCCLK (in MHz)
  uपूर्णांक16_t MaxClock; // This is either DCFCLK or SOCCLK (in MHz)
  uपूर्णांक16_t MinMclk;
  uपूर्णांक16_t MaxMclk;

  uपूर्णांक8_t  WmSetting;
  uपूर्णांक8_t  WmType;  // Used क्रम normal pstate change or memory retraining
  uपूर्णांक8_t  Padding[2];
पूर्ण WatermarkRowGeneric_t;

#घोषणा NUM_WM_RANGES 4
#घोषणा WM_PSTATE_CHG 0
#घोषणा WM_RETRAINING 1

प्रकार क्रमागत अणु
  WM_SOCCLK = 0,
  WM_DCFCLK,
  WM_COUNT,
पूर्ण WM_CLOCK_e;

प्रकार काष्ठा अणु
  // Watermarks
  WatermarkRowGeneric_t WatermarkRow[WM_COUNT][NUM_WM_RANGES];

  uपूर्णांक32_t     MmHubPadding[7]; // SMU पूर्णांकernal use
पूर्ण Watermarks_t;

प्रकार क्रमागत अणु
  CUSTOM_DPM_SETTING_GFXCLK,
  CUSTOM_DPM_SETTING_CCLK,
  CUSTOM_DPM_SETTING_FCLK_CCX,
  CUSTOM_DPM_SETTING_FCLK_GFX,
  CUSTOM_DPM_SETTING_FCLK_STALLS,
  CUSTOM_DPM_SETTING_LCLK,
  CUSTOM_DPM_SETTING_COUNT,
पूर्ण CUSTOM_DPM_SETTING_e;

प्रकार काष्ठा अणु
  uपूर्णांक8_t             ActiveHystLimit;
  uपूर्णांक8_t             IdleHystLimit;
  uपूर्णांक8_t             FPS;
  uपूर्णांक8_t             MinActiveFreqType;
  FloatInIntFormat_t  MinActiveFreq;
  FloatInIntFormat_t  PD_Data_limit;
  FloatInIntFormat_t  PD_Data_समय_स्थिरant;
  FloatInIntFormat_t  PD_Data_error_coeff;
  FloatInIntFormat_t  PD_Data_error_rate_coeff;
पूर्ण DpmActivityMonitorCoeffExt_t;

प्रकार काष्ठा अणु
  DpmActivityMonitorCoeffExt_t DpmActivityMonitorCoeff[CUSTOM_DPM_SETTING_COUNT];
पूर्ण CustomDpmSettings_t;

#घोषणा NUM_DCFCLK_DPM_LEVELS 7
#घोषणा NUM_DISPCLK_DPM_LEVELS 7
#घोषणा NUM_DPPCLK_DPM_LEVELS 7
#घोषणा NUM_SOCCLK_DPM_LEVELS 7
#घोषणा NUM_ISPICLK_DPM_LEVELS 7
#घोषणा NUM_ISPXCLK_DPM_LEVELS 7
#घोषणा NUM_VCN_DPM_LEVELS 5
#घोषणा NUM_FCLK_DPM_LEVELS 4
#घोषणा NUM_SOC_VOLTAGE_LEVELS 8

प्रकार काष्ठा अणु
  uपूर्णांक32_t fclk;
  uपूर्णांक32_t memclk;
  uपूर्णांक32_t voltage;
पूर्ण df_pstate_t;

प्रकार काष्ठा अणु
  uपूर्णांक32_t vclk;
  uपूर्णांक32_t dclk;
पूर्ण vcn_clk_t;

//Freq in MHz
//Voltage in milli volts with 2 fractional bits

प्रकार काष्ठा अणु
  uपूर्णांक32_t DcfClocks[NUM_DCFCLK_DPM_LEVELS];
  uपूर्णांक32_t DispClocks[NUM_DISPCLK_DPM_LEVELS];
  uपूर्णांक32_t DppClocks[NUM_DPPCLK_DPM_LEVELS];
  uपूर्णांक32_t SocClocks[NUM_SOCCLK_DPM_LEVELS];
  uपूर्णांक32_t IspiClocks[NUM_ISPICLK_DPM_LEVELS];
  uपूर्णांक32_t IspxClocks[NUM_ISPXCLK_DPM_LEVELS];
  vcn_clk_t VcnClocks[NUM_VCN_DPM_LEVELS];

  uपूर्णांक32_t SocVoltage[NUM_SOC_VOLTAGE_LEVELS];

  df_pstate_t DfPstateTable[NUM_FCLK_DPM_LEVELS];

  uपूर्णांक32_t MinGfxClk;
  uपूर्णांक32_t MaxGfxClk;

  uपूर्णांक8_t NumDfPstatesEnabled;
  uपूर्णांक8_t NumDcfclkLevelsEnabled;
  uपूर्णांक8_t NumDispClkLevelsEnabled;  //applies to both dispclk and dppclk
  uपूर्णांक8_t NumSocClkLevelsEnabled;

  uपूर्णांक8_t IspClkLevelsEnabled;  //applies to both ispiclk and ispxclk
  uपूर्णांक8_t VcnClkLevelsEnabled;  //applies to both vclk/dclk
  uपूर्णांक8_t spare[2];
पूर्ण DpmClocks_t;


// Throttler Status Biपंचांगask
#घोषणा THROTTLER_STATUS_BIT_SPL 0
#घोषणा THROTTLER_STATUS_BIT_FPPT 1
#घोषणा THROTTLER_STATUS_BIT_SPPT 2
#घोषणा THROTTLER_STATUS_BIT_SPPT_APU 3
#घोषणा THROTTLER_STATUS_BIT_THM_CORE 4
#घोषणा THROTTLER_STATUS_BIT_THM_GFX 5
#घोषणा THROTTLER_STATUS_BIT_THM_SOC 6
#घोषणा THROTTLER_STATUS_BIT_TDC_VDD 7
#घोषणा THROTTLER_STATUS_BIT_TDC_SOC 8
#घोषणा THROTTLER_STATUS_BIT_TDC_GFX 9
#घोषणा THROTTLER_STATUS_BIT_TDC_CVIP 10

प्रकार काष्ठा अणु
  uपूर्णांक16_t GfxclkFrequency;      //[MHz]
  uपूर्णांक16_t SocclkFrequency;      //[MHz]
  uपूर्णांक16_t VclkFrequency;        //[MHz]
  uपूर्णांक16_t DclkFrequency;        //[MHz]
  uपूर्णांक16_t MemclkFrequency;      //[MHz]
  uपूर्णांक16_t spare;

  uपूर्णांक16_t GfxActivity;          //[centi]
  uपूर्णांक16_t UvdActivity;          //[centi]

  uपूर्णांक16_t Voltage[3];           //[mV] indices: VDDCR_VDD, VDDCR_SOC, VDDCR_GFX
  uपूर्णांक16_t Current[3];           //[mA] indices: VDDCR_VDD, VDDCR_SOC, VDDCR_GFX
  uपूर्णांक16_t Power[3];             //[mW] indices: VDDCR_VDD, VDDCR_SOC, VDDCR_GFX
  uपूर्णांक16_t CurrentSocketPower;   //[mW]

  //3rd party tools in Winकरोws need info in the हाल of APUs
  uपूर्णांक16_t CoreFrequency[8];     //[MHz]
  uपूर्णांक16_t CorePower[8];         //[mW]
  uपूर्णांक16_t CoreTemperature[8];   //[centi-Celsius]
  uपूर्णांक16_t L3Frequency[2];       //[MHz]
  uपूर्णांक16_t L3Temperature[2];     //[centi-Celsius]

  uपूर्णांक16_t GfxTemperature;       //[centi-Celsius]
  uपूर्णांक16_t SocTemperature;       //[centi-Celsius]
  uपूर्णांक16_t EdgeTemperature;
  uपूर्णांक16_t ThrottlerStatus;
पूर्ण SmuMetrics_legacy_t;

प्रकार काष्ठा अणु
  uपूर्णांक16_t GfxclkFrequency;      //[MHz]
  uपूर्णांक16_t SocclkFrequency;      //[MHz]
  uपूर्णांक16_t VclkFrequency;        //[MHz]
  uपूर्णांक16_t DclkFrequency;        //[MHz]
  uपूर्णांक16_t MemclkFrequency;      //[MHz]
  uपूर्णांक16_t spare;

  uपूर्णांक16_t GfxActivity;          //[centi]
  uपूर्णांक16_t UvdActivity;          //[centi]
  uपूर्णांक16_t C0Residency[4];       //percentage

  uपूर्णांक16_t Voltage[3];           //[mV] indices: VDDCR_VDD, VDDCR_SOC, VDDCR_GFX
  uपूर्णांक16_t Current[3];           //[mA] indices: VDDCR_VDD, VDDCR_SOC, VDDCR_GFX
  uपूर्णांक16_t Power[3];             //[mW] indices: VDDCR_VDD, VDDCR_SOC, VDDCR_GFX
  uपूर्णांक16_t CurrentSocketPower;   //[mW]

  //3rd party tools in Winकरोws need info in the हाल of APUs
  uपूर्णांक16_t CoreFrequency[4];     //[MHz]
  uपूर्णांक16_t CorePower[4];         //[mW]
  uपूर्णांक16_t CoreTemperature[4];   //[centi-Celsius]
  uपूर्णांक16_t L3Frequency[1];       //[MHz]
  uपूर्णांक16_t L3Temperature[1];     //[centi-Celsius]

  uपूर्णांक16_t GfxTemperature;       //[centi-Celsius]
  uपूर्णांक16_t SocTemperature;       //[centi-Celsius]
  uपूर्णांक16_t EdgeTemperature;
  uपूर्णांक16_t ThrottlerStatus;
पूर्ण SmuMetricsTable_t;

प्रकार काष्ठा अणु
  SmuMetricsTable_t Current;
  SmuMetricsTable_t Average;
  //uपूर्णांक32_t AccCnt;
  uपूर्णांक32_t SampleStartTime;
  uपूर्णांक32_t SampleStopTime;
पूर्ण SmuMetrics_t;


// Workload bits
#घोषणा WORKLOAD_PPLIB_FULL_SCREEN_3D_BIT 0
#घोषणा WORKLOAD_PPLIB_VIDEO_BIT 2
#घोषणा WORKLOAD_PPLIB_VR_BIT 3
#घोषणा WORKLOAD_PPLIB_COMPUTE_BIT 4
#घोषणा WORKLOAD_PPLIB_CUSTOM_BIT 5
#घोषणा WORKLOAD_PPLIB_COUNT 6

#घोषणा TABLE_BIOS_IF            0 // Called by BIOS
#घोषणा TABLE_WATERMARKS         1 // Called by DAL through VBIOS
#घोषणा TABLE_CUSTOM_DPM         2 // Called by Driver
#घोषणा TABLE_SPARE1             3
#घोषणा TABLE_DPMCLOCKS          4 // Called by Driver
#घोषणा TABLE_SPARE2             5 // Called by Tools
#घोषणा TABLE_MODERN_STDBY       6 // Called by Tools क्रम Modern Standby Log
#घोषणा TABLE_SMU_METRICS        7 // Called by Driver
#घोषणा TABLE_COUNT              8

//ISP tile definitions
प्रकार क्रमागत अणु
  TILE_ISPX = 0, // ISPX
  TILE_ISPM,     // ISPM
  TILE_ISPC,  // ISPCORE
  TILE_ISPPRE,   // ISPPRE
  TILE_ISPPOST,  // ISPPOST
  TILE_MAX
पूर्ण TILE_NUM_e;

// Tile Selection (Based on arguments)
#घोषणा TILE_SEL_ISPX       (1<<(TILE_ISPX))
#घोषणा TILE_SEL_ISPM       (1<<(TILE_ISPM))
#घोषणा TILE_SEL_ISPC       (1<<(TILE_ISPC))
#घोषणा TILE_SEL_ISPPRE     (1<<(TILE_ISPPRE))
#घोषणा TILE_SEL_ISPPOST    (1<<(TILE_ISPPOST))

// Mask क्रम ISP tiles in PGFSM PWR Status Registers
//Bit[1:0] maps to ISPX, (ISPX)
//Bit[3:2] maps to ISPM, (ISPM)
//Bit[5:4] maps to ISPCORE, (ISPCORE)
//Bit[7:6] maps to ISPPRE, (ISPPRE)
//Bit[9:8] maps to POST, (ISPPOST
#घोषणा TILE_ISPX_MASK      ((1<<0) | (1<<1))
#घोषणा TILE_ISPM_MASK      ((1<<2) | (1<<3))
#घोषणा TILE_ISPC_MASK      ((1<<4) | (1<<5))
#घोषणा TILE_ISPPRE_MASK    ((1<<6) | (1<<7))
#घोषणा TILE_ISPPOST_MASK   ((1<<8) | (1<<9))

#पूर्ण_अगर
