<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
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

#अगर_अघोषित SMU12_DRIVER_IF_H
#घोषणा SMU12_DRIVER_IF_H

// *** IMPORTANT ***
// SMU TEAM: Always increment the पूर्णांकerface version अगर 
// any काष्ठाure is changed in this file
#घोषणा SMU12_DRIVER_IF_VERSION 14

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


#घोषणा NUM_DCFCLK_DPM_LEVELS 8
#घोषणा NUM_SOCCLK_DPM_LEVELS 8
#घोषणा NUM_FCLK_DPM_LEVELS   4
#घोषणा NUM_MEMCLK_DPM_LEVELS 4
#घोषणा NUM_VCN_DPM_LEVELS    8

प्रकार काष्ठा अणु
  uपूर्णांक32_t Freq;    // In MHz
  uपूर्णांक32_t Vol;     // Millivolts with 2 fractional bits
पूर्ण DpmClock_t;

प्रकार काष्ठा अणु
  DpmClock_t DcfClocks[NUM_DCFCLK_DPM_LEVELS];
  DpmClock_t SocClocks[NUM_SOCCLK_DPM_LEVELS];
  DpmClock_t FClocks[NUM_FCLK_DPM_LEVELS];
  DpmClock_t MemClocks[NUM_MEMCLK_DPM_LEVELS];
  DpmClock_t VClocks[NUM_VCN_DPM_LEVELS];
  DpmClock_t DClocks[NUM_VCN_DPM_LEVELS];

  uपूर्णांक8_t NumDcfClkDpmEnabled;
  uपूर्णांक8_t NumSocClkDpmEnabled;
  uपूर्णांक8_t NumFClkDpmEnabled;
  uपूर्णांक8_t NumMemClkDpmEnabled;
  uपूर्णांक8_t NumVClkDpmEnabled;
  uपूर्णांक8_t NumDClkDpmEnabled;
  uपूर्णांक8_t spare[2];
पूर्ण DpmClocks_t;


प्रकार क्रमागत अणु
  CLOCK_SMNCLK = 0,
  CLOCK_SOCCLK,
  CLOCK_MP0CLK,
  CLOCK_MP1CLK,
  CLOCK_MP2CLK,
  CLOCK_VCLK,
  CLOCK_LCLK,
  CLOCK_DCLK,
  CLOCK_ACLK,
  CLOCK_ISPCLK,
  CLOCK_SHUBCLK,
  CLOCK_DISPCLK,
  CLOCK_DPPCLK,
  CLOCK_DPREFCLK,
  CLOCK_DCFCLK,
  CLOCK_FCLK,
  CLOCK_UMCCLK,
  CLOCK_GFXCLK,
  CLOCK_COUNT,
पूर्ण CLOCK_IDs_e;

// Throttler Status Biपंचांगask
#घोषणा THROTTLER_STATUS_BIT_SPL            0
#घोषणा THROTTLER_STATUS_BIT_FPPT           1
#घोषणा THROTTLER_STATUS_BIT_SPPT           2
#घोषणा THROTTLER_STATUS_BIT_SPPT_APU       3
#घोषणा THROTTLER_STATUS_BIT_THM_CORE       4
#घोषणा THROTTLER_STATUS_BIT_THM_GFX        5
#घोषणा THROTTLER_STATUS_BIT_THM_SOC        6
#घोषणा THROTTLER_STATUS_BIT_TDC_VDD        7
#घोषणा THROTTLER_STATUS_BIT_TDC_SOC        8
#घोषणा THROTTLER_STATUS_BIT_PROCHOT_CPU    9
#घोषणा THROTTLER_STATUS_BIT_PROCHOT_GFX   10
#घोषणा THROTTLER_STATUS_BIT_EDC_CPU       11
#घोषणा THROTTLER_STATUS_BIT_EDC_GFX       12

प्रकार काष्ठा अणु
  uपूर्णांक16_t ClockFrequency[CLOCK_COUNT]; //[MHz]

  uपूर्णांक16_t AverageGfxclkFrequency;      //[MHz]
  uपूर्णांक16_t AverageSocclkFrequency;      //[MHz]
  uपूर्णांक16_t AverageVclkFrequency;        //[MHz]
  uपूर्णांक16_t AverageFclkFrequency;        //[MHz]

  uपूर्णांक16_t AverageGfxActivity;          //[centi]
  uपूर्णांक16_t AverageUvdActivity;          //[centi]

  uपूर्णांक16_t Voltage[2];                  //[mV] indices: VDDCR_VDD, VDDCR_SOC
  uपूर्णांक16_t Current[2];                  //[mA] indices: VDDCR_VDD, VDDCR_SOC
  uपूर्णांक16_t Power[2];                    //[mW] indices: VDDCR_VDD, VDDCR_SOC

  uपूर्णांक16_t FanPwm;                      //[milli]
  uपूर्णांक16_t CurrentSocketPower;          //[W]

  uपूर्णांक16_t CoreFrequency[8];            //[MHz]
  uपूर्णांक16_t CorePower[8];                //[mW]
  uपूर्णांक16_t CoreTemperature[8];          //[centi-Celsius]
  uपूर्णांक16_t L3Frequency[2];              //[MHz]
  uपूर्णांक16_t L3Temperature[2];            //[centi-Celsius]

  uपूर्णांक16_t GfxTemperature;              //[centi-Celsius]
  uपूर्णांक16_t SocTemperature;              //[centi-Celsius]
  uपूर्णांक16_t ThrottlerStatus;
  uपूर्णांक16_t spare;

  uपूर्णांक16_t StapmOriginalLimit;          //[W]
  uपूर्णांक16_t StapmCurrentLimit;           //[W]
  uपूर्णांक16_t ApuPower;                    //[W]
  uपूर्णांक16_t dGpuPower;                   //[W]

  uपूर्णांक16_t VddTdcValue;                 //[mA]
  uपूर्णांक16_t SocTdcValue;                 //[mA]
  uपूर्णांक16_t VddEdcValue;                 //[mA]
  uपूर्णांक16_t SocEdcValue;                 //[mA]
  uपूर्णांक16_t reserve[2];
पूर्ण SmuMetrics_t;


// Workload bits
#घोषणा WORKLOAD_PPLIB_FULL_SCREEN_3D_BIT 0
#घोषणा WORKLOAD_PPLIB_VIDEO_BIT          2
#घोषणा WORKLOAD_PPLIB_VR_BIT             3
#घोषणा WORKLOAD_PPLIB_COMPUTE_BIT        4
#घोषणा WORKLOAD_PPLIB_CUSTOM_BIT         5
#घोषणा WORKLOAD_PPLIB_COUNT              6

#घोषणा TABLE_BIOS_IF            0 // Called by BIOS
#घोषणा TABLE_WATERMARKS         1 // Called by Driver
#घोषणा TABLE_CUSTOM_DPM         2 // Called by Driver
#घोषणा TABLE_SPARE1             3
#घोषणा TABLE_DPMCLOCKS          4 // Called by Driver
#घोषणा TABLE_MOMENTARY_PM       5 // Called by Tools
#घोषणा TABLE_MODERN_STDBY       6 // Called by Tools क्रम Modern Standby Log
#घोषणा TABLE_SMU_METRICS        7 // Called by Driver
#घोषणा TABLE_COUNT              8


#पूर्ण_अगर
