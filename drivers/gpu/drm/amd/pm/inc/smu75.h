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
#अगर_अघोषित SMU75_H
#घोषणा SMU75_H

#आशय pack(push, 1)

प्रकार काष्ठा अणु
	uपूर्णांक32_t high;
	uपूर्णांक32_t low;
पूर्ण data_64_t;

प्रकार काष्ठा अणु
	data_64_t high;
	data_64_t low;
पूर्ण data_128_t;

#घोषणा SMU__DGPU_ONLY

#घोषणा SMU__NUM_SCLK_DPM_STATE  8
#घोषणा SMU__NUM_MCLK_DPM_LEVELS 4
#घोषणा SMU__NUM_LCLK_DPM_LEVELS 8
#घोषणा SMU__NUM_PCIE_DPM_LEVELS 8

#घोषणा SMU7_CONTEXT_ID_SMC        1
#घोषणा SMU7_CONTEXT_ID_VBIOS      2

#घोषणा SMU75_MAX_LEVELS_VDDC            16
#घोषणा SMU75_MAX_LEVELS_VDDGFX          16
#घोषणा SMU75_MAX_LEVELS_VDDCI           8
#घोषणा SMU75_MAX_LEVELS_MVDD            4

#घोषणा SMU_MAX_SMIO_LEVELS              4

#घोषणा SMU75_MAX_LEVELS_GRAPHICS        SMU__NUM_SCLK_DPM_STATE
#घोषणा SMU75_MAX_LEVELS_MEMORY          SMU__NUM_MCLK_DPM_LEVELS
#घोषणा SMU75_MAX_LEVELS_GIO             SMU__NUM_LCLK_DPM_LEVELS
#घोषणा SMU75_MAX_LEVELS_LINK            SMU__NUM_PCIE_DPM_LEVELS
#घोषणा SMU75_MAX_LEVELS_UVD             8
#घोषणा SMU75_MAX_LEVELS_VCE             8
#घोषणा SMU75_MAX_LEVELS_ACP             8
#घोषणा SMU75_MAX_LEVELS_SAMU            8
#घोषणा SMU75_MAX_ENTRIES_SMIO           32

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

/* Virtualization Defines */
#घोषणा CG_XDMA_MASK  0x1
#घोषणा CG_XDMA_SHIFT 0
#घोषणा CG_UVD_MASK   0x2
#घोषणा CG_UVD_SHIFT  1
#घोषणा CG_VCE_MASK   0x4
#घोषणा CG_VCE_SHIFT  2
#घोषणा CG_SAMU_MASK  0x8
#घोषणा CG_SAMU_SHIFT 3
#घोषणा CG_GFX_MASK   0x10
#घोषणा CG_GFX_SHIFT  4
#घोषणा CG_SDMA_MASK  0x20
#घोषणा CG_SDMA_SHIFT 5
#घोषणा CG_HDP_MASK   0x40
#घोषणा CG_HDP_SHIFT  6
#घोषणा CG_MC_MASK    0x80
#घोषणा CG_MC_SHIFT   7
#घोषणा CG_DRM_MASK   0x100
#घोषणा CG_DRM_SHIFT  8
#घोषणा CG_ROM_MASK   0x200
#घोषणा CG_ROM_SHIFT  9
#घोषणा CG_BIF_MASK   0x400
#घोषणा CG_BIF_SHIFT  10

#अगर defined SMU__DGPU_ONLY
#घोषणा SMU75_DTE_ITERATIONS 5
#घोषणा SMU75_DTE_SOURCES 3
#घोषणा SMU75_DTE_SINKS 1
#घोषणा SMU75_NUM_CPU_TES 0
#घोषणा SMU75_NUM_GPU_TES 1
#घोषणा SMU75_NUM_NON_TES 2
#घोषणा SMU75_DTE_FAN_SCALAR_MIN 0x100
#घोषणा SMU75_DTE_FAN_SCALAR_MAX 0x166
#घोषणा SMU75_DTE_FAN_TEMP_MAX 93
#घोषणा SMU75_DTE_FAN_TEMP_MIN 83
#पूर्ण_अगर
#घोषणा SMU75_THERMAL_INPUT_LOOP_COUNT 2
#घोषणा SMU75_THERMAL_CLAMP_MODE_COUNT 2

#घोषणा EXP_M1_1  93
#घोषणा EXP_M2_1  195759
#घोषणा EXP_B_1   111176531

#घोषणा EXP_M1_2  67
#घोषणा EXP_M2_2  153720
#घोषणा EXP_B_2   94415767

#घोषणा EXP_M1_3  48
#घोषणा EXP_M2_3  119796
#घोषणा EXP_B_3   79195279

#घोषणा EXP_M1_4  550
#घोषणा EXP_M2_4  1484190
#घोषणा EXP_B_4   1051432828

#घोषणा EXP_M1_5  394
#घोषणा EXP_M2_5  1143049
#घोषणा EXP_B_5   864288432

काष्ठा SMU7_HystController_Data अणु
	uपूर्णांक16_t waterfall_up;
	uपूर्णांक16_t waterfall_करोwn;
	uपूर्णांक16_t waterfall_limit;
	uपूर्णांक16_t release_cnt;
	uपूर्णांक16_t release_limit;
	uपूर्णांक16_t spare;
पूर्ण;

प्रकार काष्ठा SMU7_HystController_Data SMU7_HystController_Data;

काष्ठा SMU75_PIDController अणु
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

प्रकार काष्ठा SMU75_PIDController SMU75_PIDController;

काष्ठा SMU7_LocalDpmScoreboard अणु
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

	uपूर्णांक8_t  EnableModeSwitchRLCNotअगरication;
	uपूर्णांक8_t  EnabledLevelsChange;
	uपूर्णांक8_t  DteClampMode;
	uपूर्णांक8_t  FpsClampMode;

	uपूर्णांक16_t LevelResidencyCounters [SMU75_MAX_LEVELS_GRAPHICS];
	uपूर्णांक16_t LevelSwitchCounters [SMU75_MAX_LEVELS_GRAPHICS];

	व्योम     (*TargetStateCalculator)(uपूर्णांक8_t);
	व्योम     (*SavedTargetStateCalculator)(uपूर्णांक8_t);

	uपूर्णांक16_t AutoDpmInterval;
	uपूर्णांक16_t AutoDpmRange;

	uपूर्णांक8_t  FpsEnabled;
	uपूर्णांक8_t  MaxPerfLevel;
	uपूर्णांक8_t  AllowLowClkInterruptToHost;
	uपूर्णांक8_t  FpsRunning;

	uपूर्णांक32_t MaxAllowedFrequency;

	uपूर्णांक32_t FilteredSclkFrequency;
	uपूर्णांक32_t LastSclkFrequency;
	uपूर्णांक32_t FilteredSclkFrequencyCnt;

	uपूर्णांक8_t MinPerfLevel;
#अगर_घोषित SMU__FIRMWARE_SCKS_PRESENT__1
	uपूर्णांक8_t ScksClampMode;
	uपूर्णांक8_t padding[2];
#अन्यथा
	uपूर्णांक8_t padding[3];
#पूर्ण_अगर

	uपूर्णांक16_t FpsAlpha;
	uपूर्णांक16_t DeltaTime;
	uपूर्णांक32_t CurrentFps;
	uपूर्णांक32_t FilteredFps;
	uपूर्णांक32_t FrameCount;
	uपूर्णांक32_t FrameCountLast;
	uपूर्णांक16_t FpsTargetScalar;
	uपूर्णांक16_t FpsWaterfallLimitScalar;
	uपूर्णांक16_t FpsAlphaScalar;
	uपूर्णांक16_t spare8;
	SMU7_HystController_Data HystControllerData;
पूर्ण;

प्रकार काष्ठा SMU7_LocalDpmScoreboard SMU7_LocalDpmScoreboard;

#घोषणा SMU7_MAX_VOLTAGE_CLIENTS 12

प्रकार uपूर्णांक8_t (*VoltageChangeHandler_t)(uपूर्णांक16_t, uपूर्णांक8_t);

#घोषणा VDDC_MASK    0x00007FFF
#घोषणा VDDC_SHIFT   0
#घोषणा VDDCI_MASK   0x3FFF8000
#घोषणा VDDCI_SHIFT  15
#घोषणा PHASES_MASK  0xC0000000
#घोषणा PHASES_SHIFT 30

प्रकार uपूर्णांक32_t SMU_VoltageLevel;

काष्ठा SMU7_VoltageScoreboard अणु
	SMU_VoltageLevel TargetVoltage;
	uपूर्णांक16_t MaxVid;
	uपूर्णांक8_t  HighestVidOffset;
	uपूर्णांक8_t  CurrentVidOffset;

	uपूर्णांक16_t CurrentVddc;
	uपूर्णांक16_t CurrentVddci;

	uपूर्णांक8_t  ControllerBusy;
	uपूर्णांक8_t  CurrentVid;
	uपूर्णांक8_t  CurrentVddciVid;
	uपूर्णांक8_t  padding;

	SMU_VoltageLevel RequestedVoltage[SMU7_MAX_VOLTAGE_CLIENTS];
	SMU_VoltageLevel TargetVoltageState;
	uपूर्णांक8_t  EnabledRequest[SMU7_MAX_VOLTAGE_CLIENTS];

	uपूर्णांक8_t  padding2;
	uपूर्णांक8_t  padding3;
	uपूर्णांक8_t  ControllerEnable;
	uपूर्णांक8_t  ControllerRunning;
	uपूर्णांक16_t CurrentStdVoltageHiSidd;
	uपूर्णांक16_t CurrentStdVoltageLoSidd;
	uपूर्णांक8_t  OverrideVoltage;
	uपूर्णांक8_t  padding4;
	uपूर्णांक8_t  padding5;
	uपूर्णांक8_t  CurrentPhases;

	VoltageChangeHandler_t ChangeVddc;
	VoltageChangeHandler_t ChangeVddci;
	VoltageChangeHandler_t ChangePhase;
	VoltageChangeHandler_t ChangeMvdd;

	VoltageChangeHandler_t functionLinks[6];

	uपूर्णांक16_t * VddcFollower1;
	पूर्णांक16_t  Driver_OD_RequestedVidOffset1;
	पूर्णांक16_t  Driver_OD_RequestedVidOffset2;
पूर्ण;

प्रकार काष्ठा SMU7_VoltageScoreboard SMU7_VoltageScoreboard;

#घोषणा SMU7_MAX_PCIE_LINK_SPEEDS 3

काष्ठा SMU7_PCIeLinkSpeedScoreboard अणु
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

#घोषणा SMU7_LKGE_LUT_NUM_OF_TEMP_ENTRIES 16
#घोषणा SMU7_LKGE_LUT_NUM_OF_VOLT_ENTRIES 16

#घोषणा SMU7_SCALE_I  7
#घोषणा SMU7_SCALE_R 12

काष्ठा SMU7_PowerScoreboard अणु
	uपूर्णांक32_t GpuPower;

	uपूर्णांक32_t VddcPower;
	uपूर्णांक32_t VddcVoltage;
	uपूर्णांक32_t VddcCurrent;

	uपूर्णांक32_t VddciPower;
	uपूर्णांक32_t VddciVoltage;
	uपूर्णांक32_t VddciCurrent;

	uपूर्णांक32_t RocPower;

	uपूर्णांक16_t Telemetry_1_slope;
	uपूर्णांक16_t Telemetry_2_slope;
	पूर्णांक32_t  Telemetry_1_offset;
	पूर्णांक32_t  Telemetry_2_offset;

	uपूर्णांक8_t MCLK_patch_flag;
	uपूर्णांक8_t reserved[3];
पूर्ण;

प्रकार काष्ठा SMU7_PowerScoreboard SMU7_PowerScoreboard;

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

काष्ठा SMU75_SoftRegisters अणु
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

	uपूर्णांक8_t         UVDDpmEnabledLevels;
	uपूर्णांक8_t         SAMUDpmEnabledLevels;
	uपूर्णांक8_t         ACPDpmEnabledLevels;
	uपूर्णांक8_t         VCEDpmEnabledLevels;

	uपूर्णांक32_t        DRAM_LOG_ADDR_H;
	uपूर्णांक32_t        DRAM_LOG_ADDR_L;
	uपूर्णांक32_t        DRAM_LOG_PHY_ADDR_H;
	uपूर्णांक32_t        DRAM_LOG_PHY_ADDR_L;
	uपूर्णांक32_t        DRAM_LOG_BUFF_SIZE;
	uपूर्णांक32_t        UlvEnterCount;
	uपूर्णांक32_t        UlvTime;
	uपूर्णांक32_t        UcodeLoadStatus;
	uपूर्णांक32_t        AllowMvddSwitch;
	uपूर्णांक8_t         Activity_Weight;
	uपूर्णांक8_t         Reserved8[3];
पूर्ण;

प्रकार काष्ठा SMU75_SoftRegisters SMU75_SoftRegisters;

काष्ठा SMU75_Firmware_Header अणु
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
	uपूर्णांक32_t ClockStretcherTable;
	uपूर्णांक32_t VftTable;
	uपूर्णांक32_t Reserved1;
	uपूर्णांक32_t AvfsCksOff_AvfsGbvTable;
	uपूर्णांक32_t AvfsCksOff_BtcGbvTable;
	uपूर्णांक32_t MM_AvfsTable;
	uपूर्णांक32_t PowerSharingTable;
	uपूर्णांक32_t AvfsTable;
	uपूर्णांक32_t AvfsCksOffGbvTable;
	uपूर्णांक32_t AvfsMeanNSigma;
	uपूर्णांक32_t AvfsSclkOffsetTable;
	uपूर्णांक32_t Reserved[12];
	uपूर्णांक32_t Signature;
पूर्ण;

प्रकार काष्ठा SMU75_Firmware_Header SMU75_Firmware_Header;

#घोषणा SMU7_FIRMWARE_HEADER_LOCATION 0x20000

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

#घोषणा MC_BLOCK_COUNT 1
#घोषणा CPL_BLOCK_COUNT 5
#घोषणा SE_BLOCK_COUNT 15
#घोषणा GC_BLOCK_COUNT 24

काष्ठा SMU7_Local_Cac अणु
	uपूर्णांक8_t BlockId;
	uपूर्णांक8_t SignalId;
	uपूर्णांक8_t Threshold;
	uपूर्णांक8_t Padding;
पूर्ण;

प्रकार काष्ठा SMU7_Local_Cac SMU7_Local_Cac;

काष्ठा SMU7_Local_Cac_Table अणु
	SMU7_Local_Cac CplLocalCac[CPL_BLOCK_COUNT];
	SMU7_Local_Cac McLocalCac[MC_BLOCK_COUNT];
	SMU7_Local_Cac SeLocalCac[SE_BLOCK_COUNT];
	SMU7_Local_Cac GcLocalCac[GC_BLOCK_COUNT];
पूर्ण;

प्रकार काष्ठा SMU7_Local_Cac_Table SMU7_Local_Cac_Table;

#आशय pack(pop)

#घोषणा CG_SYS_BITMASK_FIRST_BIT      0
#घोषणा CG_SYS_BITMASK_LAST_BIT       10
#घोषणा CG_SYS_BIF_MGLS_SHIFT         0
#घोषणा CG_SYS_ROM_SHIFT              1
#घोषणा CG_SYS_MC_MGCG_SHIFT          2
#घोषणा CG_SYS_MC_MGLS_SHIFT          3
#घोषणा CG_SYS_SDMA_MGCG_SHIFT        4
#घोषणा CG_SYS_SDMA_MGLS_SHIFT        5
#घोषणा CG_SYS_DRM_MGCG_SHIFT         6
#घोषणा CG_SYS_HDP_MGCG_SHIFT         7
#घोषणा CG_SYS_HDP_MGLS_SHIFT         8
#घोषणा CG_SYS_DRM_MGLS_SHIFT         9
#घोषणा CG_SYS_BIF_MGCG_SHIFT         10

#घोषणा CG_SYS_BIF_MGLS_MASK          0x1
#घोषणा CG_SYS_ROM_MASK               0x2
#घोषणा CG_SYS_MC_MGCG_MASK           0x4
#घोषणा CG_SYS_MC_MGLS_MASK           0x8
#घोषणा CG_SYS_SDMA_MGCG_MASK         0x10
#घोषणा CG_SYS_SDMA_MGLS_MASK         0x20
#घोषणा CG_SYS_DRM_MGCG_MASK          0x40
#घोषणा CG_SYS_HDP_MGCG_MASK          0x80
#घोषणा CG_SYS_HDP_MGLS_MASK          0x100
#घोषणा CG_SYS_DRM_MGLS_MASK          0x200
#घोषणा CG_SYS_BIF_MGCG_MASK          0x400

#घोषणा CG_GFX_BITMASK_FIRST_BIT      16
#घोषणा CG_GFX_BITMASK_LAST_BIT       24

#घोषणा CG_GFX_CGCG_SHIFT             16
#घोषणा CG_GFX_CGLS_SHIFT             17
#घोषणा CG_CPF_MGCG_SHIFT             18
#घोषणा CG_RLC_MGCG_SHIFT             19
#घोषणा CG_GFX_OTHERS_MGCG_SHIFT      20
#घोषणा CG_GFX_3DCG_SHIFT             21
#घोषणा CG_GFX_3DLS_SHIFT             22
#घोषणा CG_GFX_RLC_LS_SHIFT           23
#घोषणा CG_GFX_CP_LS_SHIFT            24

#घोषणा CG_GFX_CGCG_MASK              0x00010000
#घोषणा CG_GFX_CGLS_MASK              0x00020000
#घोषणा CG_CPF_MGCG_MASK              0x00040000
#घोषणा CG_RLC_MGCG_MASK              0x00080000
#घोषणा CG_GFX_OTHERS_MGCG_MASK       0x00100000
#घोषणा CG_GFX_3DCG_MASK              0x00200000
#घोषणा CG_GFX_3DLS_MASK              0x00400000
#घोषणा CG_GFX_RLC_LS_MASK            0x00800000
#घोषणा CG_GFX_CP_LS_MASK             0x01000000


#घोषणा VRCONF_VDDC_MASK         0x000000FF
#घोषणा VRCONF_VDDC_SHIFT        0
#घोषणा VRCONF_VDDGFX_MASK       0x0000FF00
#घोषणा VRCONF_VDDGFX_SHIFT      8
#घोषणा VRCONF_VDDCI_MASK        0x00FF0000
#घोषणा VRCONF_VDDCI_SHIFT       16
#घोषणा VRCONF_MVDD_MASK         0xFF000000
#घोषणा VRCONF_MVDD_SHIFT        24

#घोषणा VR_MERGED_WITH_VDDC      0
#घोषणा VR_SVI2_PLANE_1          1
#घोषणा VR_SVI2_PLANE_2          2
#घोषणा VR_SMIO_PATTERN_1        3
#घोषणा VR_SMIO_PATTERN_2        4
#घोषणा VR_STATIC_VOLTAGE        5

#घोषणा CLOCK_STRETCHER_MAX_ENTRIES 0x4
#घोषणा CKS_LOOKUPTable_MAX_ENTRIES 0x4

#घोषणा CLOCK_STRETCHER_SETTING_DDT_MASK             0x01
#घोषणा CLOCK_STRETCHER_SETTING_DDT_SHIFT            0x0
#घोषणा CLOCK_STRETCHER_SETTING_STRETCH_AMOUNT_MASK  0x1E
#घोषणा CLOCK_STRETCHER_SETTING_STRETCH_AMOUNT_SHIFT 0x1
#घोषणा CLOCK_STRETCHER_SETTING_ENABLE_MASK          0x80
#घोषणा CLOCK_STRETCHER_SETTING_ENABLE_SHIFT         0x7

काष्ठा SMU_ClockStretcherDataTableEntry अणु
	uपूर्णांक8_t minVID;
	uपूर्णांक8_t maxVID;

	uपूर्णांक16_t setting;
पूर्ण;
प्रकार काष्ठा SMU_ClockStretcherDataTableEntry SMU_ClockStretcherDataTableEntry;

काष्ठा SMU_ClockStretcherDataTable अणु
	SMU_ClockStretcherDataTableEntry ClockStretcherDataTableEntry[CLOCK_STRETCHER_MAX_ENTRIES];
पूर्ण;
प्रकार काष्ठा SMU_ClockStretcherDataTable SMU_ClockStretcherDataTable;

काष्ठा SMU_CKS_LOOKUPTableEntry अणु
	uपूर्णांक16_t minFreq;
	uपूर्णांक16_t maxFreq;

	uपूर्णांक8_t setting;
	uपूर्णांक8_t padding[3];
पूर्ण;
प्रकार काष्ठा SMU_CKS_LOOKUPTableEntry SMU_CKS_LOOKUPTableEntry;

काष्ठा SMU_CKS_LOOKUPTable अणु
	SMU_CKS_LOOKUPTableEntry CKS_LOOKUPTableEntry[CKS_LOOKUPTable_MAX_ENTRIES];
पूर्ण;
प्रकार काष्ठा SMU_CKS_LOOKUPTable SMU_CKS_LOOKUPTable;

काष्ठा AgmAvfsData_t अणु
	uपूर्णांक16_t avgPsmCount[28];
	uपूर्णांक16_t minPsmCount[28];
पूर्ण;
प्रकार काष्ठा AgmAvfsData_t AgmAvfsData_t;

क्रमागत VFT_COLUMNS अणु
	SCLK0,
	SCLK1,
	SCLK2,
	SCLK3,
	SCLK4,
	SCLK5,
	SCLK6,
	SCLK7,

	NUM_VFT_COLUMNS
पूर्ण;
क्रमागत अणु
  SCS_FUSE_T0,
  SCS_FUSE_T1,
  NUM_SCS_FUSE_TEMPERATURE
पूर्ण;
क्रमागत अणु
  SCKS_ON,
  SCKS_OFF,
  NUM_SCKS_STATE_TYPES
पूर्ण;

#घोषणा VFT_TABLE_DEFINED

#घोषणा TEMP_RANGE_MAXSTEPS 12
काष्ठा VFT_CELL_t अणु
	uपूर्णांक16_t Voltage;
पूर्ण;

प्रकार काष्ठा VFT_CELL_t VFT_CELL_t;
#अगर_घोषित SMU__FIRMWARE_SCKS_PRESENT__1
काष्ठा SCS_CELL_t अणु
	uपूर्णांक16_t PsmCnt[NUM_SCKS_STATE_TYPES];
पूर्ण;
प्रकार काष्ठा SCS_CELL_t SCS_CELL_t;
#पूर्ण_अगर

काष्ठा VFT_TABLE_t अणु
	VFT_CELL_t    Cell[TEMP_RANGE_MAXSTEPS][NUM_VFT_COLUMNS];
	uपूर्णांक16_t      AvfsGbv [NUM_VFT_COLUMNS];
	uपूर्णांक16_t      BtcGbv  [NUM_VFT_COLUMNS];
	पूर्णांक16_t       Temperature [TEMP_RANGE_MAXSTEPS];

#अगर_घोषित SMU__FIRMWARE_SCKS_PRESENT__1
	SCS_CELL_t    ScksCell[TEMP_RANGE_MAXSTEPS][NUM_VFT_COLUMNS];
#पूर्ण_अगर

	uपूर्णांक8_t       NumTemperatureSteps;
	uपूर्णांक8_t       padding[3];
पूर्ण;
प्रकार काष्ठा VFT_TABLE_t VFT_TABLE_t;

#घोषणा BTCGB_VDROOP_TABLE_MAX_ENTRIES 2
#घोषणा AVFSGB_VDROOP_TABLE_MAX_ENTRIES 2

काष्ठा GB_VDROOP_TABLE_t अणु
	पूर्णांक32_t a0;
	पूर्णांक32_t a1;
	पूर्णांक32_t a2;
	uपूर्णांक32_t spare;
पूर्ण;
प्रकार काष्ठा GB_VDROOP_TABLE_t GB_VDROOP_TABLE_t;

काष्ठा SMU_QuadraticCoeffs अणु
	पूर्णांक32_t m1;
	पूर्णांक32_t b;

	पूर्णांक16_t m2;
	uपूर्णांक8_t m1_shअगरt;
	uपूर्णांक8_t m2_shअगरt;
पूर्ण;
प्रकार काष्ठा SMU_QuadraticCoeffs SMU_QuadraticCoeffs;

काष्ठा AVFS_Margin_t अणु
	VFT_CELL_t Cell[NUM_VFT_COLUMNS];
पूर्ण;
प्रकार काष्ठा AVFS_Margin_t AVFS_Margin_t;

काष्ठा AVFS_CksOff_Gbv_t अणु
	VFT_CELL_t Cell[NUM_VFT_COLUMNS];
पूर्ण;
प्रकार काष्ठा AVFS_CksOff_Gbv_t AVFS_CksOff_Gbv_t;

काष्ठा AVFS_CksOff_AvfsGbv_t अणु
	VFT_CELL_t Cell[NUM_VFT_COLUMNS];
पूर्ण;
प्रकार काष्ठा AVFS_CksOff_AvfsGbv_t AVFS_CksOff_AvfsGbv_t;

काष्ठा AVFS_CksOff_BtcGbv_t अणु
	VFT_CELL_t Cell[NUM_VFT_COLUMNS];
पूर्ण;
प्रकार काष्ठा AVFS_CksOff_BtcGbv_t AVFS_CksOff_BtcGbv_t;

काष्ठा AVFS_meanNsigma_t अणु
	uपूर्णांक32_t Aस्थिरant[3];
	uपूर्णांक16_t DC_tol_sigma;
	uपूर्णांक16_t Platक्रमm_mean;
	uपूर्णांक16_t Platक्रमm_sigma;
	uपूर्णांक16_t PSM_Age_CompFactor;
	uपूर्णांक8_t  Static_Voltage_Offset[NUM_VFT_COLUMNS];
पूर्ण;
प्रकार काष्ठा AVFS_meanNsigma_t AVFS_meanNsigma_t;

काष्ठा AVFS_Sclk_Offset_t अणु
	uपूर्णांक16_t Sclk_Offset[8];
पूर्ण;
प्रकार काष्ठा AVFS_Sclk_Offset_t AVFS_Sclk_Offset_t;

काष्ठा Power_Sharing_t अणु
	uपूर्णांक32_t EnergyCounter;
	uपूर्णांक32_t EngeryThreshold;
	uपूर्णांक64_t AM_SCLK_CNT;
	uपूर्णांक64_t AM_0_BUSY_CNT;
पूर्ण;
प्रकार काष्ठा Power_Sharing_t  Power_Sharing_t;


#पूर्ण_अगर


