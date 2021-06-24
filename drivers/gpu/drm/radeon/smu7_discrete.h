<शैली गुरु>
/*
 * Copyright 2013 Advanced Micro Devices, Inc.
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

#अगर_अघोषित SMU7_DISCRETE_H
#घोषणा SMU7_DISCRETE_H

#समावेश "smu7.h"

#आशय pack(push, 1)

#घोषणा SMU7_DTE_ITERATIONS 5
#घोषणा SMU7_DTE_SOURCES 3
#घोषणा SMU7_DTE_SINKS 1
#घोषणा SMU7_NUM_CPU_TES 0
#घोषणा SMU7_NUM_GPU_TES 1
#घोषणा SMU7_NUM_NON_TES 2

काष्ठा SMU7_SoftRegisters
अणु
    uपूर्णांक32_t        RefClockFrequency;
    uपूर्णांक32_t        PmTimerP;
    uपूर्णांक32_t        FeatureEnables;
    uपूर्णांक32_t        PreVBlankGap;
    uपूर्णांक32_t        VBlankTimeout;
    uपूर्णांक32_t        TrainTimeGap;

    uपूर्णांक32_t        MvddSwitchTime;
    uपूर्णांक32_t        LongestAcpiTrainTime;
    uपूर्णांक32_t        AcpiDelay;
    uपूर्णांक32_t        G5TrainTime;
    uपूर्णांक32_t        DelayMpllPwron;
    uपूर्णांक32_t        VoltageChangeTimeout;
    uपूर्णांक32_t        HandshakeDisables;

    uपूर्णांक8_t         DisplayPhy1Config;
    uपूर्णांक8_t         DisplayPhy2Config;
    uपूर्णांक8_t         DisplayPhy3Config;
    uपूर्णांक8_t         DisplayPhy4Config;

    uपूर्णांक8_t         DisplayPhy5Config;
    uपूर्णांक8_t         DisplayPhy6Config;
    uपूर्णांक8_t         DisplayPhy7Config;
    uपूर्णांक8_t         DisplayPhy8Config;

    uपूर्णांक32_t        AverageGraphicsA;
    uपूर्णांक32_t        AverageMemoryA;
    uपूर्णांक32_t        AverageGioA;

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
    uपूर्णांक32_t        UlvEnterC;
    uपूर्णांक32_t        UlvTime;
    uपूर्णांक32_t        Reserved[3];

पूर्ण;

प्रकार काष्ठा SMU7_SoftRegisters SMU7_SoftRegisters;

काष्ठा SMU7_Discrete_VoltageLevel
अणु
    uपूर्णांक16_t    Voltage;
    uपूर्णांक16_t    StdVoltageHiSidd;
    uपूर्णांक16_t    StdVoltageLoSidd;
    uपूर्णांक8_t     Smio;
    uपूर्णांक8_t     padding;
पूर्ण;

प्रकार काष्ठा SMU7_Discrete_VoltageLevel SMU7_Discrete_VoltageLevel;

काष्ठा SMU7_Discrete_GraphicsLevel
अणु
    uपूर्णांक32_t    Flags;
    uपूर्णांक32_t    MinVddc;
    uपूर्णांक32_t    MinVddcPhases;

    uपूर्णांक32_t    SclkFrequency;

    uपूर्णांक8_t     padding1[2];
    uपूर्णांक16_t    ActivityLevel;

    uपूर्णांक32_t    CgSpllFuncCntl3;
    uपूर्णांक32_t    CgSpllFuncCntl4;
    uपूर्णांक32_t    SpllSpपढ़ोSpectrum;
    uपूर्णांक32_t    SpllSpपढ़ोSpectrum2;
    uपूर्णांक32_t    CcPwrDynRm;
    uपूर्णांक32_t    CcPwrDynRm1;
    uपूर्णांक8_t     SclkDid;
    uपूर्णांक8_t     DisplayWatermark;
    uपूर्णांक8_t     EnabledForActivity;
    uपूर्णांक8_t     EnabledForThrottle;
    uपूर्णांक8_t     UpH;
    uपूर्णांक8_t     DownH;
    uपूर्णांक8_t     VoltageDownH;
    uपूर्णांक8_t     PowerThrottle;
    uपूर्णांक8_t     DeepSleepDivId;
    uपूर्णांक8_t     padding[3];
पूर्ण;

प्रकार काष्ठा SMU7_Discrete_GraphicsLevel SMU7_Discrete_GraphicsLevel;

काष्ठा SMU7_Discrete_ACPILevel
अणु
    uपूर्णांक32_t    Flags;
    uपूर्णांक32_t    MinVddc;
    uपूर्णांक32_t    MinVddcPhases;
    uपूर्णांक32_t    SclkFrequency;
    uपूर्णांक8_t     SclkDid;
    uपूर्णांक8_t     DisplayWatermark;
    uपूर्णांक8_t     DeepSleepDivId;
    uपूर्णांक8_t     padding;
    uपूर्णांक32_t    CgSpllFuncCntl;
    uपूर्णांक32_t    CgSpllFuncCntl2;
    uपूर्णांक32_t    CgSpllFuncCntl3;
    uपूर्णांक32_t    CgSpllFuncCntl4;
    uपूर्णांक32_t    SpllSpपढ़ोSpectrum;
    uपूर्णांक32_t    SpllSpपढ़ोSpectrum2;
    uपूर्णांक32_t    CcPwrDynRm;
    uपूर्णांक32_t    CcPwrDynRm1;
पूर्ण;

प्रकार काष्ठा SMU7_Discrete_ACPILevel SMU7_Discrete_ACPILevel;

काष्ठा SMU7_Discrete_Ulv
अणु
    uपूर्णांक32_t    CcPwrDynRm;
    uपूर्णांक32_t    CcPwrDynRm1;
    uपूर्णांक16_t    VddcOffset;
    uपूर्णांक8_t     VddcOffsetVid;
    uपूर्णांक8_t     VddcPhase;
    uपूर्णांक32_t    Reserved;
पूर्ण;

प्रकार काष्ठा SMU7_Discrete_Ulv SMU7_Discrete_Ulv;

काष्ठा SMU7_Discrete_MemoryLevel
अणु
    uपूर्णांक32_t    MinVddc;
    uपूर्णांक32_t    MinVddcPhases;
    uपूर्णांक32_t    MinVddci;
    uपूर्णांक32_t    MinMvdd;

    uपूर्णांक32_t    MclkFrequency;

    uपूर्णांक8_t     EdcReadEnable;
    uपूर्णांक8_t     EdcWriteEnable;
    uपूर्णांक8_t     RttEnable;
    uपूर्णांक8_t     StutterEnable;

    uपूर्णांक8_t     StrobeEnable;
    uपूर्णांक8_t     StrobeRatio;
    uपूर्णांक8_t     EnabledForThrottle;
    uपूर्णांक8_t     EnabledForActivity;

    uपूर्णांक8_t     UpH;
    uपूर्णांक8_t     DownH;
    uपूर्णांक8_t     VoltageDownH;
    uपूर्णांक8_t     padding;

    uपूर्णांक16_t    ActivityLevel;
    uपूर्णांक8_t     DisplayWatermark;
    uपूर्णांक8_t     padding1;

    uपूर्णांक32_t    MpllFuncCntl;
    uपूर्णांक32_t    MpllFuncCntl_1;
    uपूर्णांक32_t    MpllFuncCntl_2;
    uपूर्णांक32_t    MpllAdFuncCntl;
    uपूर्णांक32_t    MpllDqFuncCntl;
    uपूर्णांक32_t    MclkPwrmgtCntl;
    uपूर्णांक32_t    DllCntl;
    uपूर्णांक32_t    MpllSs1;
    uपूर्णांक32_t    MpllSs2;
पूर्ण;

प्रकार काष्ठा SMU7_Discrete_MemoryLevel SMU7_Discrete_MemoryLevel;

काष्ठा SMU7_Discrete_LinkLevel
अणु
    uपूर्णांक8_t     PcieGenSpeed;
    uपूर्णांक8_t     PcieLaneCount;
    uपूर्णांक8_t     EnabledForActivity;
    uपूर्णांक8_t     Padding;
    uपूर्णांक32_t    DownT;
    uपूर्णांक32_t    UpT;
    uपूर्णांक32_t    Reserved;
पूर्ण;

प्रकार काष्ठा SMU7_Discrete_LinkLevel SMU7_Discrete_LinkLevel;


काष्ठा SMU7_Discrete_MCArbDramTimingTableEntry
अणु
    uपूर्णांक32_t McArbDramTiming;
    uपूर्णांक32_t McArbDramTiming2;
    uपूर्णांक8_t  McArbBurstTime;
    uपूर्णांक8_t  padding[3];
पूर्ण;

प्रकार काष्ठा SMU7_Discrete_MCArbDramTimingTableEntry SMU7_Discrete_MCArbDramTimingTableEntry;

काष्ठा SMU7_Discrete_MCArbDramTimingTable
अणु
    SMU7_Discrete_MCArbDramTimingTableEntry entries[SMU__NUM_SCLK_DPM_STATE][SMU__NUM_MCLK_DPM_LEVELS];
पूर्ण;

प्रकार काष्ठा SMU7_Discrete_MCArbDramTimingTable SMU7_Discrete_MCArbDramTimingTable;

काष्ठा SMU7_Discrete_UvdLevel
अणु
    uपूर्णांक32_t VclkFrequency;
    uपूर्णांक32_t DclkFrequency;
    uपूर्णांक16_t MinVddc;
    uपूर्णांक8_t  MinVddcPhases;
    uपूर्णांक8_t  VclkDivider;
    uपूर्णांक8_t  DclkDivider;
    uपूर्णांक8_t  padding[3];
पूर्ण;

प्रकार काष्ठा SMU7_Discrete_UvdLevel SMU7_Discrete_UvdLevel;

काष्ठा SMU7_Discrete_ExtClkLevel
अणु
    uपूर्णांक32_t Frequency;
    uपूर्णांक16_t MinVoltage;
    uपूर्णांक8_t  MinPhases;
    uपूर्णांक8_t  Divider;
पूर्ण;

प्रकार काष्ठा SMU7_Discrete_ExtClkLevel SMU7_Discrete_ExtClkLevel;

काष्ठा SMU7_Discrete_StateInfo
अणु
    uपूर्णांक32_t SclkFrequency;
    uपूर्णांक32_t MclkFrequency;
    uपूर्णांक32_t VclkFrequency;
    uपूर्णांक32_t DclkFrequency;
    uपूर्णांक32_t SamclkFrequency;
    uपूर्णांक32_t AclkFrequency;
    uपूर्णांक32_t EclkFrequency;
    uपूर्णांक16_t MvddVoltage;
    uपूर्णांक16_t padding16;
    uपूर्णांक8_t  DisplayWatermark;
    uपूर्णांक8_t  McArbIndex;
    uपूर्णांक8_t  McRegIndex;
    uपूर्णांक8_t  SeqIndex;
    uपूर्णांक8_t  SclkDid;
    पूर्णांक8_t   SclkIndex;
    पूर्णांक8_t   MclkIndex;
    uपूर्णांक8_t  PCIeGen;

पूर्ण;

प्रकार काष्ठा SMU7_Discrete_StateInfo SMU7_Discrete_StateInfo;


काष्ठा SMU7_Discrete_DpmTable
अणु
    SMU7_PIDController                  GraphicsPIDController;
    SMU7_PIDController                  MemoryPIDController;
    SMU7_PIDController                  LinkPIDController;

    uपूर्णांक32_t                            SystemFlags;


    uपूर्णांक32_t                            SmioMaskVddcVid;
    uपूर्णांक32_t                            SmioMaskVddcPhase;
    uपूर्णांक32_t                            SmioMaskVddciVid;
    uपूर्णांक32_t                            SmioMaskMvddVid;

    uपूर्णांक32_t                            VddcLevelCount;
    uपूर्णांक32_t                            VddciLevelCount;
    uपूर्णांक32_t                            MvddLevelCount;

    SMU7_Discrete_VoltageLevel          VddcLevel               [SMU7_MAX_LEVELS_VDDC];
//    SMU7_Discrete_VoltageLevel          VddcStandardReference   [SMU7_MAX_LEVELS_VDDC];
    SMU7_Discrete_VoltageLevel          VddciLevel              [SMU7_MAX_LEVELS_VDDCI];
    SMU7_Discrete_VoltageLevel          MvddLevel               [SMU7_MAX_LEVELS_MVDD];

    uपूर्णांक8_t                             GraphicsDpmLevelCount;
    uपूर्णांक8_t                             MemoryDpmLevelCount;
    uपूर्णांक8_t                             LinkLevelCount;
    uपूर्णांक8_t                             UvdLevelCount;
    uपूर्णांक8_t                             VceLevelCount;
    uपूर्णांक8_t                             AcpLevelCount;
    uपूर्णांक8_t                             SamuLevelCount;
    uपूर्णांक8_t                             MasterDeepSleepControl;
    uपूर्णांक32_t                            Reserved[5];
//    uपूर्णांक32_t                            SamuDefaultLevel;

    SMU7_Discrete_GraphicsLevel         GraphicsLevel           [SMU7_MAX_LEVELS_GRAPHICS];
    SMU7_Discrete_MemoryLevel           MemoryACPILevel;
    SMU7_Discrete_MemoryLevel           MemoryLevel             [SMU7_MAX_LEVELS_MEMORY];
    SMU7_Discrete_LinkLevel             LinkLevel               [SMU7_MAX_LEVELS_LINK];
    SMU7_Discrete_ACPILevel             ACPILevel;
    SMU7_Discrete_UvdLevel              UvdLevel                [SMU7_MAX_LEVELS_UVD];
    SMU7_Discrete_ExtClkLevel           VceLevel                [SMU7_MAX_LEVELS_VCE];
    SMU7_Discrete_ExtClkLevel           AcpLevel                [SMU7_MAX_LEVELS_ACP];
    SMU7_Discrete_ExtClkLevel           SamuLevel               [SMU7_MAX_LEVELS_SAMU];
    SMU7_Discrete_Ulv                   Ulv;

    uपूर्णांक32_t                            SclkStepSize;
    uपूर्णांक32_t                            Smio                    [SMU7_MAX_ENTRIES_SMIO];

    uपूर्णांक8_t                             UvdBootLevel;
    uपूर्णांक8_t                             VceBootLevel;
    uपूर्णांक8_t                             AcpBootLevel;
    uपूर्णांक8_t                             SamuBootLevel;

    uपूर्णांक8_t                             UVDInterval;
    uपूर्णांक8_t                             VCEInterval;
    uपूर्णांक8_t                             ACPInterval;
    uपूर्णांक8_t                             SAMUInterval;

    uपूर्णांक8_t                             GraphicsBootLevel;
    uपूर्णांक8_t                             GraphicsVoltageChangeEnable;
    uपूर्णांक8_t                             GraphicsThermThrottleEnable;
    uपूर्णांक8_t                             GraphicsInterval;

    uपूर्णांक8_t                             VoltageInterval;
    uपूर्णांक8_t                             ThermalInterval;
    uपूर्णांक16_t                            TemperatureLimitHigh;

    uपूर्णांक16_t                            TemperatureLimitLow;
    uपूर्णांक8_t                             MemoryBootLevel;
    uपूर्णांक8_t                             MemoryVoltageChangeEnable;

    uपूर्णांक8_t                             MemoryInterval;
    uपूर्णांक8_t                             MemoryThermThrottleEnable;
    uपूर्णांक16_t                            VddcVddciDelta;

    uपूर्णांक16_t                            VoltageResponseTime;
    uपूर्णांक16_t                            PhaseResponseTime;

    uपूर्णांक8_t                             PCIeBootLinkLevel;
    uपूर्णांक8_t                             PCIeGenInterval;
    uपूर्णांक8_t                             DTEInterval;
    uपूर्णांक8_t                             DTEMode;

    uपूर्णांक8_t                             SVI2Enable;
    uपूर्णांक8_t                             VRHotGpio;
    uपूर्णांक8_t                             AcDcGpio;
    uपूर्णांक8_t                             ThermGpio;

    uपूर्णांक16_t                            PPM_PkgPwrLimit;
    uपूर्णांक16_t                            PPM_TemperatureLimit;

    uपूर्णांक16_t                            DefaultTdp;
    uपूर्णांक16_t                            TargetTdp;

    uपूर्णांक16_t                            FpsHighT;
    uपूर्णांक16_t                            FpsLowT;

    uपूर्णांक16_t                            BAPMTI_R  [SMU7_DTE_ITERATIONS][SMU7_DTE_SOURCES][SMU7_DTE_SINKS];
    uपूर्णांक16_t                            BAPMTI_RC [SMU7_DTE_ITERATIONS][SMU7_DTE_SOURCES][SMU7_DTE_SINKS];

    uपूर्णांक8_t                             DTEAmbientTempBase;
    uपूर्णांक8_t                             DTETjOffset;
    uपूर्णांक8_t                             GpuTjMax;
    uपूर्णांक8_t                             GpuTjHyst;

    uपूर्णांक16_t                            BootVddc;
    uपूर्णांक16_t                            BootVddci;

    uपूर्णांक16_t                            BootMVdd;
    uपूर्णांक16_t                            padding;

    uपूर्णांक32_t                            BAPM_TEMP_GRADIENT;

    uपूर्णांक32_t                            LowSclkInterruptT;
पूर्ण;

प्रकार काष्ठा SMU7_Discrete_DpmTable SMU7_Discrete_DpmTable;

#घोषणा SMU7_DISCRETE_MC_REGISTER_ARRAY_SIZE 16
#घोषणा SMU7_DISCRETE_MC_REGISTER_ARRAY_SET_COUNT SMU7_MAX_LEVELS_MEMORY

काष्ठा SMU7_Discrete_MCRegisterAddress
अणु
    uपूर्णांक16_t s0;
    uपूर्णांक16_t s1;
पूर्ण;

प्रकार काष्ठा SMU7_Discrete_MCRegisterAddress SMU7_Discrete_MCRegisterAddress;

काष्ठा SMU7_Discrete_MCRegisterSet
अणु
    uपूर्णांक32_t value[SMU7_DISCRETE_MC_REGISTER_ARRAY_SIZE];
पूर्ण;

प्रकार काष्ठा SMU7_Discrete_MCRegisterSet SMU7_Discrete_MCRegisterSet;

काष्ठा SMU7_Discrete_MCRegisters
अणु
    uपूर्णांक8_t                             last;
    uपूर्णांक8_t                             reserved[3];
    SMU7_Discrete_MCRegisterAddress     address[SMU7_DISCRETE_MC_REGISTER_ARRAY_SIZE];
    SMU7_Discrete_MCRegisterSet         data[SMU7_DISCRETE_MC_REGISTER_ARRAY_SET_COUNT];
पूर्ण;

प्रकार काष्ठा SMU7_Discrete_MCRegisters SMU7_Discrete_MCRegisters;

काष्ठा SMU7_Discrete_FanTable
अणु
	uपूर्णांक16_t FकरोMode;
	पूर्णांक16_t  TempMin;
	पूर्णांक16_t  TempMed;
	पूर्णांक16_t  TempMax;
	पूर्णांक16_t  Slope1;
	पूर्णांक16_t  Slope2;
	पूर्णांक16_t  FकरोMin;
	पूर्णांक16_t  HystUp;
	पूर्णांक16_t  HystDown;
	पूर्णांक16_t  HystSlope;
	पूर्णांक16_t  TempRespLim;
	पूर्णांक16_t  TempCurr;
	पूर्णांक16_t  SlopeCurr;
	पूर्णांक16_t  PwmCurr;
	uपूर्णांक32_t RefreshPeriod;
	पूर्णांक16_t  FकरोMax;
	uपूर्णांक8_t  TempSrc;
	पूर्णांक8_t   Padding;
पूर्ण;

प्रकार काष्ठा SMU7_Discrete_FanTable SMU7_Discrete_FanTable;


काष्ठा SMU7_Discrete_PmFuses अणु
  // dw0-dw1
  uपूर्णांक8_t BapmVddCVidHiSidd[8];

  // dw2-dw3
  uपूर्णांक8_t BapmVddCVidLoSidd[8];

  // dw4-dw5
  uपूर्णांक8_t VddCVid[8];

  // dw6
  uपूर्णांक8_t SviLoadLineEn;
  uपूर्णांक8_t SviLoadLineVddC;
  uपूर्णांक8_t SviLoadLineTrimVddC;
  uपूर्णांक8_t SviLoadLineOffsetVddC;

  // dw7
  uपूर्णांक16_t TDC_VDDC_PkgLimit;
  uपूर्णांक8_t TDC_VDDC_ThrottleReleaseLimitPerc;
  uपूर्णांक8_t TDC_MAWt;

  // dw8
  uपूर्णांक8_t TdcWaterfallCtl;
  uपूर्णांक8_t LPMLTemperatureMin;
  uपूर्णांक8_t LPMLTemperatureMax;
  uपूर्णांक8_t Reserved;

  // dw9-dw10
  uपूर्णांक8_t BapmVddCVidHiSidd2[8];

  // dw11-dw12
  पूर्णांक16_t FuzzyFan_ErrorSetDelta;
  पूर्णांक16_t FuzzyFan_ErrorRateSetDelta;
  पूर्णांक16_t FuzzyFan_PwmSetDelta;
  uपूर्णांक16_t CalcMeasPowerBlend;

  // dw13-dw16
  uपूर्णांक8_t GnbLPML[16];

  // dw17
  uपूर्णांक8_t GnbLPMLMaxVid;
  uपूर्णांक8_t GnbLPMLMinVid;
  uपूर्णांक8_t Reserved1[2];

  // dw18
  uपूर्णांक16_t BapmVddCBaseLeakageHiSidd;
  uपूर्णांक16_t BapmVddCBaseLeakageLoSidd;
पूर्ण;

प्रकार काष्ठा SMU7_Discrete_PmFuses SMU7_Discrete_PmFuses;


#आशय pack(pop)

#पूर्ण_अगर

