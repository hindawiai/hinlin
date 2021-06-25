<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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
#अगर_अघोषित SMU71_H
#घोषणा SMU71_H

#अगर !defined(SMC_MICROCODE)
#आशय pack(push, 1)
#पूर्ण_अगर

#घोषणा SMU__NUM_PCIE_DPM_LEVELS 8
#घोषणा SMU__NUM_SCLK_DPM_STATE 8
#घोषणा SMU__NUM_MCLK_DPM_LEVELS 4
#घोषणा SMU__VARIANT__ICELAND 1
#घोषणा SMU__DGPU_ONLY 1
#घोषणा SMU__DYNAMIC_MCARB_SETTINGS 1

क्रमागत SID_OPTION अणु
  SID_OPTION_HI,
  SID_OPTION_LO,
  SID_OPTION_COUNT
पूर्ण;

प्रकार काष्ठा अणु
  uपूर्णांक32_t high;
  uपूर्णांक32_t low;
पूर्ण data_64_t;

प्रकार काष्ठा अणु
  data_64_t high;
  data_64_t low;
पूर्ण data_128_t;

#घोषणा SMU7_CONTEXT_ID_SMC        1
#घोषणा SMU7_CONTEXT_ID_VBIOS      2

#घोषणा SMU71_MAX_LEVELS_VDDC            8
#घोषणा SMU71_MAX_LEVELS_VDDCI           4
#घोषणा SMU71_MAX_LEVELS_MVDD            4
#घोषणा SMU71_MAX_LEVELS_VDDNB           8

#घोषणा SMU71_MAX_LEVELS_GRAPHICS        SMU__NUM_SCLK_DPM_STATE
#घोषणा SMU71_MAX_LEVELS_MEMORY          SMU__NUM_MCLK_DPM_LEVELS
#घोषणा SMU71_MAX_LEVELS_GIO             SMU__NUM_LCLK_DPM_LEVELS
#घोषणा SMU71_MAX_LEVELS_LINK            SMU__NUM_PCIE_DPM_LEVELS
#घोषणा SMU71_MAX_ENTRIES_SMIO           32

#घोषणा DPM_NO_LIMIT 0
#घोषणा DPM_NO_UP 1
#घोषणा DPM_GO_DOWN 2
#घोषणा DPM_GO_UP 3

#घोषणा SMU7_FIRST_DPM_GRAPHICS_LEVEL    0
#घोषणा SMU7_FIRST_DPM_MEMORY_LEVEL      0

#घोषणा GPIO_CLAMP_MODE_VRHOT      1
#घोषणा GPIO_CLAMP_MODE_THERM      2
#घोषणा GPIO_CLAMP_MODE_DC         4

#घोषणा SCRATCH_B_TARG_PCIE_INDEX_SHIFT 0
#घोषणा SCRATCH_B_TARG_PCIE_INDEX_MASK  (0x7<<SCRATCH_B_TARG_PCIE_INDEX_SHIFT)
#घोषणा SCRATCH_B_CURR_PCIE_INDEX_SHIFT 3
#घोषणा SCRATCH_B_CURR_PCIE_INDEX_MASK  (0x7<<SCRATCH_B_CURR_PCIE_INDEX_SHIFT)
#घोषणा SCRATCH_B_TARG_UVD_INDEX_SHIFT  6
#घोषणा SCRATCH_B_TARG_UVD_INDEX_MASK   (0x7<<SCRATCH_B_TARG_UVD_INDEX_SHIFT)
#घोषणा SCRATCH_B_CURR_UVD_INDEX_SHIFT  9
#घोषणा SCRATCH_B_CURR_UVD_INDEX_MASK   (0x7<<SCRATCH_B_CURR_UVD_INDEX_SHIFT)
#घोषणा SCRATCH_B_TARG_VCE_INDEX_SHIFT  12
#घोषणा SCRATCH_B_TARG_VCE_INDEX_MASK   (0x7<<SCRATCH_B_TARG_VCE_INDEX_SHIFT)
#घोषणा SCRATCH_B_CURR_VCE_INDEX_SHIFT  15
#घोषणा SCRATCH_B_CURR_VCE_INDEX_MASK   (0x7<<SCRATCH_B_CURR_VCE_INDEX_SHIFT)
#घोषणा SCRATCH_B_TARG_ACP_INDEX_SHIFT  18
#घोषणा SCRATCH_B_TARG_ACP_INDEX_MASK   (0x7<<SCRATCH_B_TARG_ACP_INDEX_SHIFT)
#घोषणा SCRATCH_B_CURR_ACP_INDEX_SHIFT  21
#घोषणा SCRATCH_B_CURR_ACP_INDEX_MASK   (0x7<<SCRATCH_B_CURR_ACP_INDEX_SHIFT)
#घोषणा SCRATCH_B_TARG_SAMU_INDEX_SHIFT 24
#घोषणा SCRATCH_B_TARG_SAMU_INDEX_MASK  (0x7<<SCRATCH_B_TARG_SAMU_INDEX_SHIFT)
#घोषणा SCRATCH_B_CURR_SAMU_INDEX_SHIFT 27
#घोषणा SCRATCH_B_CURR_SAMU_INDEX_MASK  (0x7<<SCRATCH_B_CURR_SAMU_INDEX_SHIFT)


#अगर defined SMU__DGPU_ONLY
#घोषणा SMU71_DTE_ITERATIONS 5
#घोषणा SMU71_DTE_SOURCES 3
#घोषणा SMU71_DTE_SINKS 1
#घोषणा SMU71_NUM_CPU_TES 0
#घोषणा SMU71_NUM_GPU_TES 1
#घोषणा SMU71_NUM_NON_TES 2

#पूर्ण_अगर

#अगर defined SMU__FUSION_ONLY
#घोषणा SMU7_DTE_ITERATIONS 5
#घोषणा SMU7_DTE_SOURCES 5
#घोषणा SMU7_DTE_SINKS 3
#घोषणा SMU7_NUM_CPU_TES 2
#घोषणा SMU7_NUM_GPU_TES 1
#घोषणा SMU7_NUM_NON_TES 2

#पूर्ण_अगर

काष्ठा SMU71_PIDController
अणु
    uपूर्णांक32_t Ki;
    पूर्णांक32_t LFWindupUpperLim;
    पूर्णांक32_t LFWindupLowerLim;
    uपूर्णांक32_t StatePrecision;
    uपूर्णांक32_t LfPrecision;
    uपूर्णांक32_t LfOffset;
    uपूर्णांक32_t MaxState;
    uपूर्णांक32_t MaxLfFraction;
    uपूर्णांक32_t StateShअगरt;
पूर्ण;

प्रकार काष्ठा SMU71_PIDController SMU71_PIDController;

काष्ठा SMU7_LocalDpmScoreboard
अणु
    uपूर्णांक32_t PercentageBusy;

    पूर्णांक32_t  PIDError;
    पूर्णांक32_t  PIDIntegral;
    पूर्णांक32_t  PIDOutput;

    uपूर्णांक32_t SigmaDeltaAccum;
    uपूर्णांक32_t SigmaDeltaOutput;
    uपूर्णांक32_t SigmaDeltaLevel;

    uपूर्णांक32_t UtilizationSetpoपूर्णांक;

    uपूर्णांक8_t  TdpClampMode;
    uपूर्णांक8_t  TdcClampMode;
    uपूर्णांक8_t  ThermClampMode;
    uपूर्णांक8_t  VoltageBusy;

    पूर्णांक8_t   CurrLevel;
    पूर्णांक8_t   TargLevel;
    uपूर्णांक8_t  LevelChangeInProgress;
    uपूर्णांक8_t  UpHyst;

    uपूर्णांक8_t  DownHyst;
    uपूर्णांक8_t  VoltageDownHyst;
    uपूर्णांक8_t  DpmEnable;
    uपूर्णांक8_t  DpmRunning;

    uपूर्णांक8_t  DpmForce;
    uपूर्णांक8_t  DpmForceLevel;
    uपूर्णांक8_t  DisplayWatermark;
    uपूर्णांक8_t  McArbIndex;

    uपूर्णांक32_t MinimumPerfSclk;

    uपूर्णांक8_t  AcpiReq;
    uपूर्णांक8_t  AcpiAck;
    uपूर्णांक8_t  GfxClkSlow;
    uपूर्णांक8_t  GpioClampMode;

    uपूर्णांक8_t  FpsFilterWeight;
    uपूर्णांक8_t  EnabledLevelsChange;
    uपूर्णांक8_t  DteClampMode;
    uपूर्णांक8_t  FpsClampMode;

    uपूर्णांक16_t LevelResidencyCounters [SMU71_MAX_LEVELS_GRAPHICS];
    uपूर्णांक16_t LevelSwitchCounters [SMU71_MAX_LEVELS_GRAPHICS];

    व्योम     (*TargetStateCalculator)(uपूर्णांक8_t);
    व्योम     (*SavedTargetStateCalculator)(uपूर्णांक8_t);

    uपूर्णांक16_t AutoDpmInterval;
    uपूर्णांक16_t AutoDpmRange;

    uपूर्णांक8_t  FpsEnabled;
    uपूर्णांक8_t  MaxPerfLevel;
    uपूर्णांक8_t  AllowLowClkInterruptToHost;
    uपूर्णांक8_t  FpsRunning;

    uपूर्णांक32_t MaxAllowedFrequency;
पूर्ण;

प्रकार काष्ठा SMU7_LocalDpmScoreboard SMU7_LocalDpmScoreboard;

#घोषणा SMU7_MAX_VOLTAGE_CLIENTS 12

काष्ठा SMU7_VoltageScoreboard
अणु
    uपूर्णांक16_t CurrentVoltage;
    uपूर्णांक16_t HighestVoltage;
    uपूर्णांक16_t MaxVid;
    uपूर्णांक8_t  HighestVidOffset;
    uपूर्णांक8_t  CurrentVidOffset;
#अगर defined (SMU__DGPU_ONLY)
    uपूर्णांक8_t  CurrentPhases;
    uपूर्णांक8_t  HighestPhases;
#अन्यथा
    uपूर्णांक8_t  AvsOffset;
    uपूर्णांक8_t  AvsOffsetApplied;
#पूर्ण_अगर
    uपूर्णांक8_t  ControllerBusy;
    uपूर्णांक8_t  CurrentVid;
    uपूर्णांक16_t RequestedVoltage[SMU7_MAX_VOLTAGE_CLIENTS];
#अगर defined (SMU__DGPU_ONLY)
    uपूर्णांक8_t  RequestedPhases[SMU7_MAX_VOLTAGE_CLIENTS];
#पूर्ण_अगर
    uपूर्णांक8_t  EnabledRequest[SMU7_MAX_VOLTAGE_CLIENTS];
    uपूर्णांक8_t  TargetIndex;
    uपूर्णांक8_t  Delay;
    uपूर्णांक8_t  ControllerEnable;
    uपूर्णांक8_t  ControllerRunning;
    uपूर्णांक16_t CurrentStdVoltageHiSidd;
    uपूर्णांक16_t CurrentStdVoltageLoSidd;
#अगर defined (SMU__DGPU_ONLY)
    uपूर्णांक16_t RequestedVddci;
    uपूर्णांक16_t CurrentVddci;
    uपूर्णांक16_t HighestVddci;
    uपूर्णांक8_t  CurrentVddciVid;
    uपूर्णांक8_t  TargetVddciIndex;
#पूर्ण_अगर
पूर्ण;

प्रकार काष्ठा SMU7_VoltageScoreboard SMU7_VoltageScoreboard;

// -------------------------------------------------------------------------------------------------------------------------
#घोषणा SMU7_MAX_PCIE_LINK_SPEEDS 3 /* 0:Gen1 1:Gen2 2:Gen3 */

काष्ठा SMU7_PCIeLinkSpeedScoreboard
अणु
    uपूर्णांक8_t     DpmEnable;
    uपूर्णांक8_t     DpmRunning;
    uपूर्णांक8_t     DpmForce;
    uपूर्णांक8_t     DpmForceLevel;

    uपूर्णांक8_t     CurrentLinkSpeed;
    uपूर्णांक8_t     EnabledLevelsChange;
    uपूर्णांक16_t    AutoDpmInterval;

    uपूर्णांक16_t    AutoDpmRange;
    uपूर्णांक16_t    AutoDpmCount;

    uपूर्णांक8_t     DpmMode;
    uपूर्णांक8_t     AcpiReq;
    uपूर्णांक8_t     AcpiAck;
    uपूर्णांक8_t     CurrentLinkLevel;

पूर्ण;

प्रकार काष्ठा SMU7_PCIeLinkSpeedScoreboard SMU7_PCIeLinkSpeedScoreboard;

// -------------------------------------------------------- CAC table ------------------------------------------------------
#घोषणा SMU7_LKGE_LUT_NUM_OF_TEMP_ENTRIES 16
#घोषणा SMU7_LKGE_LUT_NUM_OF_VOLT_ENTRIES 16

#घोषणा SMU7_SCALE_I  7
#घोषणा SMU7_SCALE_R 12

काष्ठा SMU7_PowerScoreboard
अणु
    uपूर्णांक16_t   MinVoltage;
    uपूर्णांक16_t   MaxVoltage;

    uपूर्णांक32_t   AvgGpuPower;

    uपूर्णांक16_t   VddcLeakagePower[SID_OPTION_COUNT];
    uपूर्णांक16_t   VddcSclkConstantPower[SID_OPTION_COUNT];
    uपूर्णांक16_t   VddcSclkDynamicPower[SID_OPTION_COUNT];
    uपूर्णांक16_t   VddcNonSclkDynamicPower[SID_OPTION_COUNT];
    uपूर्णांक16_t   VddcTotalPower[SID_OPTION_COUNT];
    uपूर्णांक16_t   VddcTotalCurrent[SID_OPTION_COUNT];
    uपूर्णांक16_t   VddcLoadVoltage[SID_OPTION_COUNT];
    uपूर्णांक16_t   VddcNoLoadVoltage[SID_OPTION_COUNT];

    uपूर्णांक16_t   DisplayPhyPower;
    uपूर्णांक16_t   PciePhyPower;

    uपूर्णांक16_t   VddciTotalPower;
    uपूर्णांक16_t   Vddr1TotalPower;

    uपूर्णांक32_t   RocPower;

    uपूर्णांक32_t   last_घातer;
    uपूर्णांक32_t   enableWinAvg;

    uपूर्णांक32_t   lkg_acc;
    uपूर्णांक16_t   VoltLkgeScaler;
    uपूर्णांक16_t   TempLkgeScaler;

    uपूर्णांक32_t   uvd_cac_dclk;
    uपूर्णांक32_t   uvd_cac_vclk;
    uपूर्णांक32_t   vce_cac_eclk;
    uपूर्णांक32_t   samu_cac_samclk;
    uपूर्णांक32_t   display_cac_dispclk;
    uपूर्णांक32_t   acp_cac_aclk;
    uपूर्णांक32_t   unb_cac;

    uपूर्णांक32_t   WinTime;

    uपूर्णांक16_t  GpuPwr_MAWt;
    uपूर्णांक16_t  FilteredVddcTotalPower;

    uपूर्णांक8_t   CalculationRepeats;
    uपूर्णांक8_t   WaterfallUp;
    uपूर्णांक8_t   WaterfallDown;
    uपूर्णांक8_t   WaterfallLimit;
पूर्ण;

प्रकार काष्ठा SMU7_PowerScoreboard SMU7_PowerScoreboard;

// --------------------------------------------------------------------------------------------------

काष्ठा SMU7_ThermalScoreboard
अणु
   पूर्णांक16_t  GpuLimit;
   पूर्णांक16_t  GpuHyst;
   uपूर्णांक16_t CurrGnbTemp;
   uपूर्णांक16_t FilteredGnbTemp;
   uपूर्णांक8_t  ControllerEnable;
   uपूर्णांक8_t  ControllerRunning;
   uपूर्णांक8_t  WaterfallUp;
   uपूर्णांक8_t  WaterfallDown;
   uपूर्णांक8_t  WaterfallLimit;
   uपूर्णांक8_t  padding[3];
पूर्ण;

प्रकार काष्ठा SMU7_ThermalScoreboard SMU7_ThermalScoreboard;

// For FeatureEnables:
#घोषणा SMU7_SCLK_DPM_CONFIG_MASK                        0x01
#घोषणा SMU7_VOLTAGE_CONTROLLER_CONFIG_MASK              0x02
#घोषणा SMU7_THERMAL_CONTROLLER_CONFIG_MASK              0x04
#घोषणा SMU7_MCLK_DPM_CONFIG_MASK                        0x08
#घोषणा SMU7_UVD_DPM_CONFIG_MASK                         0x10
#घोषणा SMU7_VCE_DPM_CONFIG_MASK                         0x20
#घोषणा SMU7_ACP_DPM_CONFIG_MASK                         0x40
#घोषणा SMU7_SAMU_DPM_CONFIG_MASK                        0x80
#घोषणा SMU7_PCIEGEN_DPM_CONFIG_MASK                    0x100

#घोषणा SMU7_ACP_MCLK_HANDSHAKE_DISABLE                  0x00000001
#घोषणा SMU7_ACP_SCLK_HANDSHAKE_DISABLE                  0x00000002
#घोषणा SMU7_UVD_MCLK_HANDSHAKE_DISABLE                  0x00000100
#घोषणा SMU7_UVD_SCLK_HANDSHAKE_DISABLE                  0x00000200
#घोषणा SMU7_VCE_MCLK_HANDSHAKE_DISABLE                  0x00010000
#घोषणा SMU7_VCE_SCLK_HANDSHAKE_DISABLE                  0x00020000

// All 'soft registers' should be uपूर्णांक32_t.
काष्ठा SMU71_SoftRegisters
अणु
    uपूर्णांक32_t        RefClockFrequency;
    uपूर्णांक32_t        PmTimerPeriod;
    uपूर्णांक32_t        FeatureEnables;
#अगर defined (SMU__DGPU_ONLY)
    uपूर्णांक32_t        PreVBlankGap;
    uपूर्णांक32_t        VBlankTimeout;
    uपूर्णांक32_t        TrainTimeGap;
    uपूर्णांक32_t        MvddSwitchTime;
    uपूर्णांक32_t        LongestAcpiTrainTime;
    uपूर्णांक32_t        AcpiDelay;
    uपूर्णांक32_t        G5TrainTime;
    uपूर्णांक32_t        DelayMpllPwron;
    uपूर्णांक32_t        VoltageChangeTimeout;
#पूर्ण_अगर
    uपूर्णांक32_t        HandshakeDisables;

    uपूर्णांक8_t         DisplayPhy1Config;
    uपूर्णांक8_t         DisplayPhy2Config;
    uपूर्णांक8_t         DisplayPhy3Config;
    uपूर्णांक8_t         DisplayPhy4Config;

    uपूर्णांक8_t         DisplayPhy5Config;
    uपूर्णांक8_t         DisplayPhy6Config;
    uपूर्णांक8_t         DisplayPhy7Config;
    uपूर्णांक8_t         DisplayPhy8Config;

    uपूर्णांक32_t        AverageGraphicsActivity;
    uपूर्णांक32_t        AverageMemoryActivity;
    uपूर्णांक32_t        AverageGioActivity;

    uपूर्णांक8_t         SClkDpmEnabledLevels;
    uपूर्णांक8_t         MClkDpmEnabledLevels;
    uपूर्णांक8_t         LClkDpmEnabledLevels;
    uपूर्णांक8_t         PCIeDpmEnabledLevels;

    uपूर्णांक32_t        DRAM_LOG_ADDR_H;
    uपूर्णांक32_t        DRAM_LOG_ADDR_L;
    uपूर्णांक32_t        DRAM_LOG_PHY_ADDR_H;
    uपूर्णांक32_t        DRAM_LOG_PHY_ADDR_L;
    uपूर्णांक32_t        DRAM_LOG_BUFF_SIZE;
    uपूर्णांक32_t        UlvEnterCount;
    uपूर्णांक32_t        UlvTime;
    uपूर्णांक32_t        UcodeLoadStatus;
    uपूर्णांक8_t         DPMFreezeAndForced;
    uपूर्णांक8_t         Activity_Weight;
    uपूर्णांक8_t         Reserved8[2];
    uपूर्णांक32_t        Reserved;
पूर्ण;

प्रकार काष्ठा SMU71_SoftRegisters SMU71_SoftRegisters;

काष्ठा SMU71_Firmware_Header
अणु
    uपूर्णांक32_t Digest[5];
    uपूर्णांक32_t Version;
    uपूर्णांक32_t HeaderSize;
    uपूर्णांक32_t Flags;
    uपूर्णांक32_t EntryPoपूर्णांक;
    uपूर्णांक32_t CodeSize;
    uपूर्णांक32_t ImageSize;

    uपूर्णांक32_t Rtos;
    uपूर्णांक32_t SoftRegisters;
    uपूर्णांक32_t DpmTable;
    uपूर्णांक32_t FanTable;
    uपूर्णांक32_t CacConfigTable;
    uपूर्णांक32_t CacStatusTable;

    uपूर्णांक32_t mcRegisterTable;

    uपूर्णांक32_t mcArbDramTimingTable;

    uपूर्णांक32_t PmFuseTable;
    uपूर्णांक32_t Globals;
    uपूर्णांक32_t UvdDpmTable;
    uपूर्णांक32_t AcpDpmTable;
    uपूर्णांक32_t VceDpmTable;
    uपूर्णांक32_t SamuDpmTable;
    uपूर्णांक32_t UlvSettings;
    uपूर्णांक32_t Reserved[37];
    uपूर्णांक32_t Signature;
पूर्ण;

प्रकार काष्ठा SMU71_Firmware_Header SMU71_Firmware_Header;

काष्ठा SMU7_HystController_Data
अणु
    uपूर्णांक8_t waterfall_up;
    uपूर्णांक8_t waterfall_करोwn;
    uपूर्णांक8_t pstate;
    uपूर्णांक8_t clamp_mode;
पूर्ण;

प्रकार काष्ठा SMU7_HystController_Data SMU7_HystController_Data;

#घोषणा SMU71_FIRMWARE_HEADER_LOCATION 0x20000

क्रमागत  DisplayConfig अणु
    PowerDown = 1,
    DP54x4,
    DP54x2,
    DP54x1,
    DP27x4,
    DP27x2,
    DP27x1,
    HDMI297,
    HDMI162,
    LVDS,
    DP324x4,
    DP324x2,
    DP324x1
पूर्ण;

//#घोषणा SX_BLOCK_COUNT 8
//#घोषणा MC_BLOCK_COUNT 1
//#घोषणा CPL_BLOCK_COUNT 27

#अगर defined SMU__VARIANT__ICELAND
  #घोषणा SX_BLOCK_COUNT 8
  #घोषणा MC_BLOCK_COUNT 1
  #घोषणा CPL_BLOCK_COUNT 29
#पूर्ण_अगर

काष्ठा SMU7_Local_Cac अणु
  uपूर्णांक8_t BlockId;
  uपूर्णांक8_t SignalId;
  uपूर्णांक8_t Threshold;
  uपूर्णांक8_t Padding;
पूर्ण;

प्रकार काष्ठा SMU7_Local_Cac SMU7_Local_Cac;

काष्ठा SMU7_Local_Cac_Table अणु
  SMU7_Local_Cac SxLocalCac[SX_BLOCK_COUNT];
  SMU7_Local_Cac CplLocalCac[CPL_BLOCK_COUNT];
  SMU7_Local_Cac McLocalCac[MC_BLOCK_COUNT];
पूर्ण;

प्रकार काष्ठा SMU7_Local_Cac_Table SMU7_Local_Cac_Table;

#अगर !defined(SMC_MICROCODE)
#आशय pack(pop)
#पूर्ण_अगर

#पूर्ण_अगर

