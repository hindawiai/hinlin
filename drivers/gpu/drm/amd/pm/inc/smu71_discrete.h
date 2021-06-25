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
#अगर_अघोषित SMU71_DISCRETE_H
#घोषणा SMU71_DISCRETE_H

#समावेश "smu71.h"

#अगर !defined(SMC_MICROCODE)
#आशय pack(push, 1)
#पूर्ण_अगर

#घोषणा VDDC_ON_SVI2  0x1
#घोषणा VDDCI_ON_SVI2 0x2
#घोषणा MVDD_ON_SVI2  0x4

काष्ठा SMU71_Discrete_VoltageLevel
अणु
    uपूर्णांक16_t    Voltage;
    uपूर्णांक16_t    StdVoltageHiSidd;
    uपूर्णांक16_t    StdVoltageLoSidd;
    uपूर्णांक8_t     Smio;
    uपूर्णांक8_t     padding;
पूर्ण;

प्रकार काष्ठा SMU71_Discrete_VoltageLevel SMU71_Discrete_VoltageLevel;

काष्ठा SMU71_Discrete_GraphicsLevel
अणु
    uपूर्णांक32_t    MinVddc;
    uपूर्णांक32_t    MinVddcPhases;

    uपूर्णांक32_t    SclkFrequency;

    uपूर्णांक8_t     pcieDpmLevel;
    uपूर्णांक8_t     DeepSleepDivId;
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
    uपूर्णांक8_t     UpHyst;
    uपूर्णांक8_t     DownHyst;
    uपूर्णांक8_t     VoltageDownHyst;
    uपूर्णांक8_t     PowerThrottle;
पूर्ण;

प्रकार काष्ठा SMU71_Discrete_GraphicsLevel SMU71_Discrete_GraphicsLevel;

काष्ठा SMU71_Discrete_ACPILevel
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

प्रकार काष्ठा SMU71_Discrete_ACPILevel SMU71_Discrete_ACPILevel;

काष्ठा SMU71_Discrete_Ulv
अणु
    uपूर्णांक32_t    CcPwrDynRm;
    uपूर्णांक32_t    CcPwrDynRm1;
    uपूर्णांक16_t    VddcOffset;
    uपूर्णांक8_t     VddcOffsetVid;
    uपूर्णांक8_t     VddcPhase;
    uपूर्णांक32_t    Reserved;
पूर्ण;

प्रकार काष्ठा SMU71_Discrete_Ulv SMU71_Discrete_Ulv;

काष्ठा SMU71_Discrete_MemoryLevel
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

    uपूर्णांक8_t     UpHyst;
    uपूर्णांक8_t     DownHyst;
    uपूर्णांक8_t     VoltageDownHyst;
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

प्रकार काष्ठा SMU71_Discrete_MemoryLevel SMU71_Discrete_MemoryLevel;

काष्ठा SMU71_Discrete_LinkLevel
अणु
    uपूर्णांक8_t     PcieGenSpeed;           ///< 0:PciE-gen1 1:PciE-gen2 2:PciE-gen3
    uपूर्णांक8_t     PcieLaneCount;          ///< 1=x1, 2=x2, 3=x4, 4=x8, 5=x12, 6=x16
    uपूर्णांक8_t     EnabledForActivity;
    uपूर्णांक8_t     SPC;
    uपूर्णांक32_t    DownThreshold;
    uपूर्णांक32_t    UpThreshold;
    uपूर्णांक32_t    Reserved;
पूर्ण;

प्रकार काष्ठा SMU71_Discrete_LinkLevel SMU71_Discrete_LinkLevel;


#अगर_घोषित SMU__DYNAMIC_MCARB_SETTINGS
// MC ARB DRAM Timing रेजिस्टरs.
काष्ठा SMU71_Discrete_MCArbDramTimingTableEntry
अणु
    uपूर्णांक32_t McArbDramTiming;
    uपूर्णांक32_t McArbDramTiming2;
    uपूर्णांक8_t  McArbBurstTime;
    uपूर्णांक8_t  padding[3];
पूर्ण;

प्रकार काष्ठा SMU71_Discrete_MCArbDramTimingTableEntry SMU71_Discrete_MCArbDramTimingTableEntry;

काष्ठा SMU71_Discrete_MCArbDramTimingTable
अणु
    SMU71_Discrete_MCArbDramTimingTableEntry entries[SMU__NUM_SCLK_DPM_STATE][SMU__NUM_MCLK_DPM_LEVELS];
पूर्ण;

प्रकार काष्ठा SMU71_Discrete_MCArbDramTimingTable SMU71_Discrete_MCArbDramTimingTable;
#पूर्ण_अगर

// UVD VCLK/DCLK state (level) definition.
काष्ठा SMU71_Discrete_UvdLevel
अणु
    uपूर्णांक32_t VclkFrequency;
    uपूर्णांक32_t DclkFrequency;
    uपूर्णांक16_t MinVddc;
    uपूर्णांक8_t  MinVddcPhases;
    uपूर्णांक8_t  VclkDivider;
    uपूर्णांक8_t  DclkDivider;
    uपूर्णांक8_t  padding[3];
पूर्ण;

प्रकार काष्ठा SMU71_Discrete_UvdLevel SMU71_Discrete_UvdLevel;

// Clocks क्रम other बाह्यal blocks (VCE, ACP, SAMU).
काष्ठा SMU71_Discrete_ExtClkLevel
अणु
    uपूर्णांक32_t Frequency;
    uपूर्णांक16_t MinVoltage;
    uपूर्णांक8_t  MinPhases;
    uपूर्णांक8_t  Divider;
पूर्ण;

प्रकार काष्ठा SMU71_Discrete_ExtClkLevel SMU71_Discrete_ExtClkLevel;

// Everything that we need to keep track of about the current state.
// Use this instead of copies of the GraphicsLevel and MemoryLevel काष्ठाures to keep track of state parameters
// that need to be checked later.
// We करोn't need to cache everything about a state, just a few parameters.
काष्ठा SMU71_Discrete_StateInfo
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

प्रकार काष्ठा SMU71_Discrete_StateInfo SMU71_Discrete_StateInfo;


काष्ठा SMU71_Discrete_DpmTable
अणु
    // Multi-DPM controller settings
    SMU71_PIDController                  GraphicsPIDController;
    SMU71_PIDController                  MemoryPIDController;
    SMU71_PIDController                  LinkPIDController;

    uपूर्णांक32_t                            SystemFlags;

    // SMIO masks क्रम voltage and phase controls
    uपूर्णांक32_t                            SmioMaskVddcVid;
    uपूर्णांक32_t                            SmioMaskVddcPhase;
    uपूर्णांक32_t                            SmioMaskVddciVid;
    uपूर्णांक32_t                            SmioMaskMvddVid;

    uपूर्णांक32_t                            VddcLevelCount;
    uपूर्णांक32_t                            VddciLevelCount;
    uपूर्णांक32_t                            MvddLevelCount;

    SMU71_Discrete_VoltageLevel          VddcLevel               [SMU71_MAX_LEVELS_VDDC];
    SMU71_Discrete_VoltageLevel          VddciLevel              [SMU71_MAX_LEVELS_VDDCI];
    SMU71_Discrete_VoltageLevel          MvddLevel               [SMU71_MAX_LEVELS_MVDD];

    uपूर्णांक8_t                             GraphicsDpmLevelCount;
    uपूर्णांक8_t                             MemoryDpmLevelCount;
    uपूर्णांक8_t                             LinkLevelCount;
    uपूर्णांक8_t                             MasterDeepSleepControl;

    uपूर्णांक32_t                            Reserved[5];

    // State table entries क्रम each DPM state
    SMU71_Discrete_GraphicsLevel         GraphicsLevel           [SMU71_MAX_LEVELS_GRAPHICS];
    SMU71_Discrete_MemoryLevel           MemoryACPILevel;
    SMU71_Discrete_MemoryLevel           MemoryLevel             [SMU71_MAX_LEVELS_MEMORY];
    SMU71_Discrete_LinkLevel             LinkLevel               [SMU71_MAX_LEVELS_LINK];
    SMU71_Discrete_ACPILevel             ACPILevel;

    uपूर्णांक32_t                            SclkStepSize;
    uपूर्णांक32_t                            Smio                    [SMU71_MAX_ENTRIES_SMIO];

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
    uपूर्णांक8_t                             MergedVddci;
    uपूर्णांक8_t                             padding2;

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

    uपूर्णांक32_t                            DisplayCac;

    uपूर्णांक16_t                            MaxPwr;
    uपूर्णांक16_t                            NomPwr;

    uपूर्णांक16_t                            FpsHighThreshold;
    uपूर्णांक16_t                            FpsLowThreshold;

    uपूर्णांक16_t                            BAPMTI_R  [SMU71_DTE_ITERATIONS][SMU71_DTE_SOURCES][SMU71_DTE_SINKS];
    uपूर्णांक16_t                            BAPMTI_RC [SMU71_DTE_ITERATIONS][SMU71_DTE_SOURCES][SMU71_DTE_SINKS];

    uपूर्णांक8_t                             DTEAmbientTempBase;
    uपूर्णांक8_t                             DTETjOffset;
    uपूर्णांक8_t                             GpuTjMax;
    uपूर्णांक8_t                             GpuTjHyst;

    uपूर्णांक16_t                            BootVddc;
    uपूर्णांक16_t                            BootVddci;

    uपूर्णांक16_t                            BootMVdd;
    uपूर्णांक16_t                            padding;

    uपूर्णांक32_t                            BAPM_TEMP_GRADIENT;

    uपूर्णांक32_t                            LowSclkInterruptThreshold;
    uपूर्णांक32_t                            VddGfxReChkWait;

    uपूर्णांक16_t                            PPM_PkgPwrLimit;
    uपूर्णांक16_t                            PPM_TemperatureLimit;

    uपूर्णांक16_t                            DefaultTdp;
    uपूर्णांक16_t                            TargetTdp;
पूर्ण;

प्रकार काष्ठा SMU71_Discrete_DpmTable SMU71_Discrete_DpmTable;

// --------------------------------------------------- AC Timing Parameters ------------------------------------------------
#घोषणा SMU71_DISCRETE_MC_REGISTER_ARRAY_SIZE 16
#घोषणा SMU71_DISCRETE_MC_REGISTER_ARRAY_SET_COUNT SMU71_MAX_LEVELS_MEMORY

काष्ठा SMU71_Discrete_MCRegisterAddress
अणु
    uपूर्णांक16_t s0;
    uपूर्णांक16_t s1;
पूर्ण;

प्रकार काष्ठा SMU71_Discrete_MCRegisterAddress SMU71_Discrete_MCRegisterAddress;

काष्ठा SMU71_Discrete_MCRegisterSet
अणु
    uपूर्णांक32_t value[SMU71_DISCRETE_MC_REGISTER_ARRAY_SIZE];
पूर्ण;

प्रकार काष्ठा SMU71_Discrete_MCRegisterSet SMU71_Discrete_MCRegisterSet;

काष्ठा SMU71_Discrete_MCRegisters
अणु
    uपूर्णांक8_t                             last;
    uपूर्णांक8_t                             reserved[3];
    SMU71_Discrete_MCRegisterAddress     address[SMU71_DISCRETE_MC_REGISTER_ARRAY_SIZE];
    SMU71_Discrete_MCRegisterSet         data[SMU71_DISCRETE_MC_REGISTER_ARRAY_SET_COUNT];
पूर्ण;

प्रकार काष्ठा SMU71_Discrete_MCRegisters SMU71_Discrete_MCRegisters;


// --------------------------------------------------- Fan Table -----------------------------------------------------------
काष्ठा SMU71_Discrete_FanTable
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

प्रकार काष्ठा SMU71_Discrete_FanTable SMU71_Discrete_FanTable;

#घोषणा SMU7_DISCRETE_GPIO_SCLK_DEBUG             4
#घोषणा SMU7_DISCRETE_GPIO_SCLK_DEBUG_BIT         (0x1 << SMU7_DISCRETE_GPIO_SCLK_DEBUG)

काष्ठा SMU71_MclkDpmScoreboard
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

    uपूर्णांक32_t MinimumPerfMclk;

    uपूर्णांक8_t  AcpiReq;
    uपूर्णांक8_t  AcpiAck;
    uपूर्णांक8_t  MclkSwitchInProgress;
    uपूर्णांक8_t  MclkSwitchCritical;

    uपूर्णांक8_t  TargetMclkIndex;
    uपूर्णांक8_t  TargetMvddIndex;
    uपूर्णांक8_t  MclkSwitchResult;

    uपूर्णांक8_t  EnabledLevelsChange;

    uपूर्णांक16_t LevelResidencyCounters [SMU71_MAX_LEVELS_MEMORY];
    uपूर्णांक16_t LevelSwitchCounters [SMU71_MAX_LEVELS_MEMORY];

    व्योम     (*TargetStateCalculator)(uपूर्णांक8_t);
    व्योम     (*SavedTargetStateCalculator)(uपूर्णांक8_t);

    uपूर्णांक16_t AutoDpmInterval;
    uपूर्णांक16_t AutoDpmRange;

    uपूर्णांक16_t  MclkSwitchingTime;
    uपूर्णांक8_t padding[2];
पूर्ण;

प्रकार काष्ठा SMU71_MclkDpmScoreboard SMU71_MclkDpmScoreboard;

काष्ठा SMU71_UlvScoreboard
अणु
    uपूर्णांक8_t     EnterUlv;
    uपूर्णांक8_t     ExitUlv;
    uपूर्णांक8_t     UlvActive;
    uपूर्णांक8_t     WaitingForUlv;
    uपूर्णांक8_t     UlvEnable;
    uपूर्णांक8_t     UlvRunning;
    uपूर्णांक8_t     UlvMasterEnable;
    uपूर्णांक8_t     padding;
    uपूर्णांक32_t    UlvAbortedCount;
    uपूर्णांक32_t    UlvTimeStamp;
पूर्ण;

प्रकार काष्ठा SMU71_UlvScoreboard SMU71_UlvScoreboard;

काष्ठा SMU71_VddGfxScoreboard
अणु
    uपूर्णांक8_t     VddGfxEnable;
    uपूर्णांक8_t     VddGfxActive;
    uपूर्णांक8_t     padding[2];

    uपूर्णांक32_t    VddGfxEnteredCount;
    uपूर्णांक32_t    VddGfxAbortedCount;
पूर्ण;

प्रकार काष्ठा SMU71_VddGfxScoreboard SMU71_VddGfxScoreboard;

काष्ठा SMU71_AcpiScoreboard अणु
  uपूर्णांक32_t SavedInterruptMask[2];
  uपूर्णांक8_t LastACPIRequest;
  uपूर्णांक8_t CgBअगरResp;
  uपूर्णांक8_t RequestType;
  uपूर्णांक8_t Padding;
  SMU71_Discrete_ACPILevel D0Level;
पूर्ण;

प्रकार काष्ठा SMU71_AcpiScoreboard SMU71_AcpiScoreboard;


काष्ठा SMU71_Discrete_PmFuses अणु
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

  // dw9-dw12
  uपूर्णांक8_t LPMLTemperatureScaler[16];

  // dw13-dw14
  पूर्णांक16_t FuzzyFan_ErrorSetDelta;
  पूर्णांक16_t FuzzyFan_ErrorRateSetDelta;
  पूर्णांक16_t FuzzyFan_PwmSetDelta;
  uपूर्णांक16_t Reserved6;

  // dw15
  uपूर्णांक8_t GnbLPML[16];

  // dw15
  uपूर्णांक8_t GnbLPMLMaxVid;
  uपूर्णांक8_t GnbLPMLMinVid;
  uपूर्णांक8_t Reserved1[2];

  // dw16
  uपूर्णांक16_t BapmVddCBaseLeakageHiSidd;
  uपूर्णांक16_t BapmVddCBaseLeakageLoSidd;
पूर्ण;

प्रकार काष्ठा SMU71_Discrete_PmFuses SMU71_Discrete_PmFuses;

काष्ठा SMU71_Discrete_Log_Header_Table अणु
  uपूर्णांक32_t    version;
  uपूर्णांक32_t    asic_id;
  uपूर्णांक16_t    flags;
  uपूर्णांक16_t    entry_size;
  uपूर्णांक32_t    total_size;
  uपूर्णांक32_t    num_of_entries;
  uपूर्णांक8_t     type;
  uपूर्णांक8_t     mode;
  uपूर्णांक8_t     filler_0[2];
  uपूर्णांक32_t    filler_1[2];
पूर्ण;

प्रकार काष्ठा SMU71_Discrete_Log_Header_Table SMU71_Discrete_Log_Header_Table;

काष्ठा SMU71_Discrete_Log_Cntl अणु
    uपूर्णांक8_t             Enabled;
    uपूर्णांक8_t             Type;
    uपूर्णांक8_t             padding[2];
    uपूर्णांक32_t            BufferSize;
    uपूर्णांक32_t            SamplesLogged;
    uपूर्णांक32_t            SampleSize;
    uपूर्णांक32_t            AddrL;
    uपूर्णांक32_t            AddrH;
पूर्ण;

प्रकार काष्ठा SMU71_Discrete_Log_Cntl SMU71_Discrete_Log_Cntl;

#अगर defined SMU__DGPU_ONLY
  #घोषणा CAC_ACC_NW_NUM_OF_SIGNALS 83
#पूर्ण_अगर


काष्ठा SMU71_Discrete_Cac_Collection_Table अणु
  uपूर्णांक32_t temperature;
  uपूर्णांक32_t cac_acc_nw[CAC_ACC_NW_NUM_OF_SIGNALS];
  uपूर्णांक32_t filler[4];
पूर्ण;

प्रकार काष्ठा SMU71_Discrete_Cac_Collection_Table SMU71_Discrete_Cac_Collection_Table;

काष्ठा SMU71_Discrete_Cac_Verअगरication_Table अणु
  uपूर्णांक32_t VddcTotalPower;
  uपूर्णांक32_t VddcLeakagePower;
  uपूर्णांक32_t VddcConstantPower;
  uपूर्णांक32_t VddcGfxDynamicPower;
  uपूर्णांक32_t VddcUvdDynamicPower;
  uपूर्णांक32_t VddcVceDynamicPower;
  uपूर्णांक32_t VddcAcpDynamicPower;
  uपूर्णांक32_t VddcPcieDynamicPower;
  uपूर्णांक32_t VddcDceDynamicPower;
  uपूर्णांक32_t VddcCurrent;
  uपूर्णांक32_t VddcVoltage;
  uपूर्णांक32_t VddciTotalPower;
  uपूर्णांक32_t VddciLeakagePower;
  uपूर्णांक32_t VddciConstantPower;
  uपूर्णांक32_t VddciDynamicPower;
  uपूर्णांक32_t Vddr1TotalPower;
  uपूर्णांक32_t Vddr1LeakagePower;
  uपूर्णांक32_t Vddr1ConstantPower;
  uपूर्णांक32_t Vddr1DynamicPower;
  uपूर्णांक32_t spare[8];
  uपूर्णांक32_t temperature;
पूर्ण;

प्रकार काष्ठा SMU71_Discrete_Cac_Verअगरication_Table SMU71_Discrete_Cac_Verअगरication_Table;

#अगर !defined(SMC_MICROCODE)
#आशय pack(pop)
#पूर्ण_अगर


#पूर्ण_अगर

